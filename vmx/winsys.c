#include "type.h"
#include "std.h"
#include "vmx.h"
#include "vasm.h"
#include "vmcs.h"
#include "msr.h"
#include "intel.h"
#include "debug.h"
#include "file.h"
#include "winfunc.h"
#include "winsys.h"
#include "ept.h"
#include "vad.h"
#include "disasm.h"
#include "vmcall.h"
#include "util.h"

PVOID MakeSyscall64();

uint64 NewSystemCall64;
PSERVICE_TABLE ssdt;
uint64 ServiceTableCount;

uint64 (*HandlerSystemService[SERVICE_MAX])();

uint64 ServiceEnableEptHook()
{
    if (gvt->EnableEPT)
        return TRUE;

    uint64 CR3 = readCR3();
    writeCR3(gvt->Os.Data.kernelCR3);

    gvt->Os.Api.KeIpiGenericCall(KipiVmcall, (void *)VMCALL_ENABLE_MODE_EPT);

    writeCR3(CR3);
    gvt->EnableEPT = TRUE;

    return TRUE;
}
uint64 ServiceInitDebug()
{
    if (!gvt->Debug)
    {
        ssdt = gvt->Os.Api.ExAllocatePool2(POOL_FLAG_NON_PAGED, 0x300 * sizeof(SERVICE_TABLE), (uint32)0x234567);
        NewSystemCall64 = (uint64)MakeSyscall64();
        ServiceTableCount = InitSystemServiceTable(ssdt, L"\\SystemRoot\\System32\\ntdll.dll");

        DebugBreak("ServiceInitDebug", NewSystemCall64, ServiceTableCount, ssdt);
        InitHandlerDebugService();
        return TRUE;
    }

    return FALSE;
}

uint64 ServiceCreateThread(HANDLE Pid, PTHREAD_START_ROUTINE ThreadProc, PVOID ThreadBuffer)
{
    CLIENT_ID Cid = {0};
    OBJECT_ATTRIBUTES objectAttributes = {0};
    HANDLE hThread = NULL;
    HANDLE hProcess = NULL;

    Cid.UniqueProcess = Pid;

    InitializeObjectAttributes(&objectAttributes, NULL, OBJ_CASE_INSENSITIVE, NULL, NULL);

    uint64 ret = gvt->Os.Api.ZwOpenProcess(&hProcess, PROCESS_ALL_ACCESS, &objectAttributes, &Cid);
    if (ret)
        int3p("ZwOpenProcess", Pid);

    NTSTATUS status = gvt->Os.Api.ZwCreateThreadEx(&hThread, 0x1FFFFF, NULL, hProcess, ThreadProc, ThreadBuffer, FALSE, NULL, NULL, NULL, NULL);

    DebugBreak("ServiceCreateThread", hThread, status);
    return status;
}

uint64 ServiceDebugProcess(HANDLE Pid)
{
    void *eproc;
    uint64 ret = gvt->Os.Api.PsLookupProcessByProcessId(Pid, &eproc);
    if (ret)
        return ret;

    DebugObject.DebugED = (void *)eproc;
    gvt->Os.Api.ObDereferenceObjectDeferDelete(eproc);

    DebugBreak("ServiceDebugToProcess", Pid, DebugObject);

    return TRUE;
}

uint64 ServiceCreateDebug(HANDLE Pid)
{
    void *eproc;
    uint64 ret = gvt->Os.Api.PsLookupProcessByProcessId(Pid, &eproc);
    if (ret)
        return ret;

    DebugObject.DebugER = (void *)eproc;
    gvt->Os.Api.ObDereferenceObjectDeferDelete(eproc);

    DebugBreak("ServiceCreateDebug", Pid, DebugObject);

    return TRUE;
}

uint64 ServiceSuperHook(HANDLE TargetPid, void *TargetCodeAddrVir, void *HookCodeAddr)
{
    void *TargetProcess;
    uint64 ret = 0;
    CLIENT_ID Cid = {0};
    OBJECT_ATTRIBUTES objectAttributes = {0};
    HANDLE hProcess = NULL;
    PSHELLCODE pShellCode = 0;
    SIZE_T CodeSize = sizeof(SHELLCODE);
    char *NewPage;
    PEPT_HOOK_CONTEXT context, SamePage;
    DisInstr instr = {0};

    ret = gvt->Os.Api.PsLookupProcessByProcessId(TargetPid, &TargetProcess);
    if (ret)
        return ret;

    Cid.UniqueProcess = TargetPid;

    InitializeObjectAttributes(&objectAttributes, NULL, OBJ_CASE_INSENSITIVE, NULL, NULL);

    ret = gvt->Os.Api.ZwOpenProcess(&hProcess, PROCESS_ALL_ACCESS, &objectAttributes, &Cid);
    if (ret)
    {
        DebugBreak("ZwOpenProcess", TargetPid);
        return FALSE;
    }

    DebugBreak("ServiceSuperHook", TargetProcess, TargetCodeAddrVir, HookCodeAddr);

    context = FindHookContext(TargetCodeAddrVir, TargetProcess);

    if (context)
        return TRUE; // 已经存在

    context = gvt->Os.Api.ExAllocatePool2(POOL_FLAG_NON_PAGED_EXECUTE, sizeof(EPT_HOOK_CONTEXT), TAG_EPT_HOOK);

    SamePage = FindHookPage(TargetCodeAddrVir, TargetProcess);
    if (SamePage)
    {
        NewPage = SamePage->NewPage;
        *(NewPage + ((uint64)TargetCodeAddrVir & 0x0FFFull)) = 0xCC;
    }
    else
    {
        // 复制页内容
        NewPage = gvt->Os.Api.ExAllocatePool2(POOL_FLAG_NON_PAGED_EXECUTE, PAGE_SIZE, TAG_NEW_PAGE);
        std_memcpy(NewPage, (void *)((uint64)TargetCodeAddrVir & ~0x0FFFull), PAGE_SIZE);
        *(NewPage + ((uint64)TargetCodeAddrVir & 0x0FFFull)) = 0xCC;
    }

    char JmpCodeAddr[] = {0xFF, 0x25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    Decode(&instr, (uint64)TargetCodeAddrVir, (uint64)TargetCodeAddrVir, Bit64);
    std_memcpy(context->ShellCode.SaveCode, TargetCodeAddrVir, instr.Ex.instrLen);
    *((uint64 *)&JmpCodeAddr[6]) = (uint64)TargetCodeAddrVir + instr.Ex.instrLen;
    std_memcpy(&context->ShellCode.SaveCode[instr.Ex.instrLen], JmpCodeAddr, sizeof(JmpCodeAddr));
    std_memcpy(context->ShellCode.Engine, HookerEngine, HookerEngineLen);

    context->ListProcess.Process.HookerEngine = &context->ShellCode.Engine;
    context->TargetCodeLen = instr.Ex.instrLen;

    if (((uint64)TargetCodeAddrVir >> 48) & 1) // 判断是R0还是R3,<R0代码,无需更改> or <R3代码,需申请空间复制执行代码>
    {
        context->ListProcess.Process.RetAddr = &context->ShellCode.SaveCode;
    }
    else
    {
        uint64 CR3 = TargetProcessCR3(TargetProcess);
        if (NT_SUCCESS(gvt->Os.Api.ZwAllocateVirtualMemory(hProcess, (void*)&pShellCode, 0, &CodeSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE)))
        {
            ULONG bits = 0;
            uint32 r = gvt->Os.Api.ZwWriteVirtualMemory(hProcess, pShellCode, &context->ShellCode.SaveCode, sizeof(SHELLCODE), &bits);

            context->ListProcess.Process.RetAddr = &pShellCode->SaveCode;
            context->ListProcess.Process.HookerEngine = &pShellCode->Engine;

            writeCR3(CR3);
        }
        else
        {
            int3p("ZwAllocateVirtualMemory", pShellCode);
        }
    }
    context->ListProcess.Process.Process = TargetProcess;
    context->TargetCodeAddrVir = TargetCodeAddrVir;

    context->HookCodeAddr = HookCodeAddr;
    context->NewPage = NewPage;

    DebugBreak("ServiceSuperHook Setting Done", context);

    gvt->Os.Api.ObDereferenceObjectDeferDelete(TargetProcess);

    VmcallHookEPT(context);
}

uint64 ServiceDebugEnumVad()
{
    test();
}
uint64 ServiceEnumProcess(PPROC_INFO Info)
{
    void *eproc = NULL;
    int i = 0;
    for (uint64 Pid = 0; Pid < 100000; Pid += 4)
    {
        NTSTATUS Status = gvt->Os.Api.PsLookupProcessByProcessId((HANDLE)Pid, &eproc);
        if (NT_SUCCESS(Status))
        {
            if (eproc != NULL)
            {
                PUNICODE_STRING name = PsGetProcessFullName(eproc);
                Info[i].Pid = Pid;
                if (name->Length)
                {
                    wstrcpy(Info[i].name, name->Buffer, name->Length);
                    i++;
                }
                else
                {
                    if (Pid == 4)
                        wstrcpy(Info[i].name, L"System", wstrlen(L"System"));
                    i++;
                }
                gvt->Os.Api.ObDereferenceObjectDeferDelete(eproc);
            }
        }
    }

    return TRUE;
}

uint64 SystemServiceNoHandler()
{
    int3p("SystemServiceNoHandler");
    return TRUE;
}

uint64 GetSystemServiceFuncAddr(uint64 number)
{
    uint64 n = number & 0x7FFF;
    if (n > SERVICE_MAX)
        return FALSE;
    return (uint64)HandlerSystemService[n];
}

void InitHandlerSystemService()
{
    for (uint8 i = 0; i < SERVICE_MAX; i++)
        HandlerSystemService[i] = SystemServiceNoHandler;

    HandlerSystemService[SERVICE_ENUM_PROCESS] = ServiceEnumProcess;
    HandlerSystemService[SERVICE_INIT_DEBUG] = ServiceInitDebug;
    HandlerSystemService[SERVICE_CREATE_DEBUG] = ServiceCreateDebug;
    HandlerSystemService[SERVICE_CREATE_TRHEAD] = ServiceCreateThread;
    HandlerSystemService[SERVICE_DEBUG_PROCESS] = ServiceDebugProcess;
    HandlerSystemService[SERVICE_DEBUG_ENUMVAD] = ServiceDebugEnumVad;
    HandlerSystemService[SERVICE_SUPER_HOOK] = ServiceSuperHook;
    // HandlerSystemService[SERVICE_ENABLE_EPT_HOOK] = ServiceEnableEptHook;
}
