#include "type.h"
#include "std.h"
#include "file.h"
#include "intel.h"
#include "debug.h"
#include "disasm.h"
#include "vasm.h"
#include "winfunc.h"
#include "winsys.h"
#include "ssdt.h"

typedef NTSTATUS (*NTQUERYSYSTEMINFORMATION)();
NTSTATUS HandlerNtQuerySystemInformation(
    SYSTEM_INFORMATION_CLASS SystemInformationClass,
    PVOID SystemInformation,
    ULONG SystemInformationLength,
    PULONG ReturnLength)
{
    NTQUERYSYSTEMINFORMATION func = GetSysCallAddr();
    uint64 callnr = GetSysCallNumber();

    /*
    vmtoolsd.exe
    vm3dservice.exe
    VGAuthService.exe
    */

    NTSTATUS ret = func(SystemInformationClass, SystemInformation, SystemInformationLength, ReturnLength);

    PLIST_MONITOR monitor = IsMonitorProcess(VmGetCurrentProcess());
    if (monitor)
    {
        // wchar *buffer = gvt->Os.Api.ExAllocatePool2(POOL_FLAG_NON_PAGED, sizeof(DBGMSG), 0x2322134);
        //  void *CurrentProcess = VmGetCurrentProcess();
        //  void *CurrentThread = VmGetCurrentThread();

        // sprint(buffer, L"%S-->%s-->%d", monitor->name, ssdt[callnr].name, SystemInformationClass);
        // InsertMsg(1, CurrentProcess, CurrentThread, buffer);

        // if (SystemInformationClass == SystemProcessInformation)
        // {
        //     // int3p("NtQuerySystemInformation SystemProcessInformation", SystemInformation, SystemInformationLength, ReturnLength);
        //     SYSTEM_PROCESS_INFORMATION *pre = SystemInformation;
        //     SYSTEM_PROCESS_INFORMATION *cur = (SYSTEM_PROCESS_INFORMATION *)((uint64)pre + pre->NextEntryOffset);
        //     while (cur->NextEntryOffset)
        //     {
        //         if (std_wstricmp(cur->ImageName.Buffer, L"vmtoolsd.exe") || std_wstricmp(cur->ImageName.Buffer, L"vm3dservice.exe") || std_wstricmp(cur->ImageName.Buffer, L"VGAuthService.exe"))
        //         {
        //             pre->NextEntryOffset += cur->NextEntryOffset;
        //             cur = (SYSTEM_PROCESS_INFORMATION *)((uint64)pre + pre->NextEntryOffset);
        //             continue;
        //         }
        //         wchar *buffer1 = gvt->Os.Api.ExAllocatePool2(POOL_FLAG_NON_PAGED, sizeof(DBGMSG), 0x2322134);

        //         void *CurrentProcess = VmGetCurrentProcess();
        //         void *CurrentThread = VmGetCurrentThread();
        //         sprint(buffer, L"SystemProcessInformation-->%S", cur->ImageName.Buffer);
        //         InsertMsg(1, CurrentProcess, CurrentThread, buffer);

        //         gvt->Os.Api.ExFreePool(buffer1);

        //         pre = cur;
        //         cur = (SYSTEM_PROCESS_INFORMATION *)((uint64)cur + cur->NextEntryOffset);
        //     }
        // }
        // else
        if (SystemInformationClass == SystemKernelDebuggerInformation)
        {
            // wchar *buffer1 = gvt->Os.Api.ExAllocatePool2(POOL_FLAG_NON_PAGED, sizeof(DBGMSG), 0x2322134);

            // void *CurrentProcess = VmGetCurrentProcess();
            // void *CurrentThread = VmGetCurrentThread();
            // sprint(buffer, L"SystemKernelDebuggerInformation-->%x64", *(uint64 *)SystemInformation);
            // InsertMsg(1, CurrentProcess, CurrentThread, buffer);

            // gvt->Os.Api.ExFreePool(buffer1);
            PSYSTEM_KERNEL_DEBUGGER_INFORMATION pDebug = SystemInformation;
            pDebug->KernelDebuggerEnabled = TRUE;
            pDebug->KernelDebuggerNotPresent = TRUE;
        }
        else if (SystemInformationClass == SystemKernelDebuggerInformationEx)
        {
            // wchar *buffer1 = gvt->Os.Api.ExAllocatePool2(POOL_FLAG_NON_PAGED, sizeof(DBGMSG), 0x2322134);

            // void *CurrentProcess = VmGetCurrentProcess();
            // void *CurrentThread = VmGetCurrentThread();
            // sprint(buffer, L"SystemKernelDebuggerInformationEx-->%x64", *(uint64 *)SystemInformation);
            // InsertMsg(1, CurrentProcess, CurrentThread, buffer);

            // gvt->Os.Api.ExFreePool(buffer1);
        }
        else if (SystemInformationClass == SystemCodeIntegrityInformation)
        {
            // wchar *buffer1 = gvt->Os.Api.ExAllocatePool2(POOL_FLAG_NON_PAGED, sizeof(DBGMSG), 0x2322134);

            // void *CurrentProcess = VmGetCurrentProcess();
            // void *CurrentThread = VmGetCurrentThread();
            // sprint(buffer, L"SystemCodeIntegrityInformation-->%x64", *(uint64 *)SystemInformation);
            // InsertMsg(1, CurrentProcess, CurrentThread, buffer);

            // gvt->Os.Api.ExFreePool(buffer1);

            *(uint32 *)((uint64)SystemInformation + 4) = 1; // 0x80测试模式，1正常模式
        }
        else if (SystemInformationClass == SystemModuleInformation)
        {
            // int3p("NtQuerySystemInformation SystemModuleInformation", SystemInformation, SystemInformationLength, ReturnLength);
            // PSYSTEM_MODULE_INFORMATION_ENTRY64 pModules = SystemInformation;
            // for (int i = 0; i < pModules->Count; i++)
            // {
            // wchar *buffer1 = gvt->Os.Api.ExAllocatePool2(POOL_FLAG_NON_PAGED, sizeof(DBGMSG), 0x2322134);

            // void *CurrentProcess = VmGetCurrentProcess();
            // void *CurrentThread = VmGetCurrentThread();
            // sprint(buffer, L"SystemModuleInformation-->%s", pModules->Module[i].ImageName);
            // InsertMsg(1, CurrentProcess, CurrentThread, buffer);

            // gvt->Os.Api.ExFreePool(buffer1);
            // std_memset(pModules->Module[i].ImageName, cstrlen(pModules->Module[i].ImageName), 0);
            //}
        }
        else if (SystemInformationClass == SystemModuleInformationEx)
        {
            // int3p("NtQuerySystemInformation SystemModuleInformationEx", SystemInformation, SystemInformationLength, ReturnLength);
            // if (SystemInformation)
            // {
            // PSYSTEM_MODULE_INFORMATION_ENTRY64 pModules = SystemInformation;
            // while (pModules->Count)
            //{
            // wchar *buffer1 = gvt->Os.Api.ExAllocatePool2(POOL_FLAG_NON_PAGED, sizeof(DBGMSG), 0x2322134);

            // void *CurrentProcess = VmGetCurrentProcess();
            // void *CurrentThread = VmGetCurrentThread();
            // sprint(buffer, L"SystemModuleInformationEx-->%s", pModules->Module->ImageName);
            // InsertMsg(1, CurrentProcess, CurrentThread, buffer);

            // gvt->Os.Api.ExFreePool(buffer1);

            // std_memset(pModules->Module->ImageName, cstrlen(pModules->Module->ImageName), 0);
            // pModules++;
            //}
            // std_memset(SystemInformation, sizeof(SYSTEM_MODULE_INFORMATION_ENTRY64), 0);
            //}
        }

        // gvt->Os.Api.ExFreePool(buffer);
    }

    return ret;
}

typedef NTSTATUS (*NTQUERYINFORMATIONPROCESS)();
NTSTATUS HandlerNtQueryInformationProcess(
    HANDLE ProcessHandle,
    PROCESSINFOCLASS ProcessInformationClass,
    PVOID ProcessInformation,
    ULONG ProcessInformationLength,
    PULONG ReturnLength)
{
    NTQUERYINFORMATIONPROCESS func = GetSysCallAddr();
    uint64 callnr = GetSysCallNumber();

    NTSTATUS ret = func(ProcessHandle, ProcessInformationClass, ProcessInformation, ProcessInformationLength, ReturnLength);

    // PLIST_MONITOR monitor = IsMonitorProcess(VmGetCurrentProcess());
    // if (monitor)
    // {
    //     wchar buffer[sizeof(DBGMSG)] = {0};
    //     void *CurrentProcess = VmGetCurrentProcess();
    //     void *CurrentThread = VmGetCurrentThread();

    //     sprint(buffer, L"%S-->%s-->%d", monitor->name, ssdt[callnr].name, ProcessInformationClass);
    //     InsertMsg(1, CurrentProcess, CurrentThread, buffer);
    // }

    return ret;
}

typedef NTSTATUS (*NTLOADDRIVER)();
NTSTATUS HandlerNtLoadDriver(PUNICODE_STRING DriverServiceName)
{
    NTLOADDRIVER func = GetSysCallAddr();

    NTSTATUS ret = func(DriverServiceName);

    // wchar *buffer = gvt->Os.Api.ExAllocatePool2(POOL_FLAG_NON_PAGED, 0x200, 0x8733749);

    // void *CurrentProcess = VmGetCurrentProcess();
    // void *CurrentThread = VmGetCurrentThread();
    // UCHAR name[0x12] = {0};
    // std_memcpy(name, VmGetProcessName(CurrentProcess), 0x10);
    // sprint(buffer, L"%s->LoadDriver->%S", name, DriverServiceName->Buffer);

    // InsertMsg(1, CurrentProcess, CurrentThread, buffer);

    // gvt->Os.Api.ExFreePool(buffer);

    return ret;
}
typedef NTSTATUS (*NTCREATEUSERPROCESS)();
NTSTATUS HandlerNtCreateUserProcess(
    PVOID ProcessHandle,
    PVOID ThreadHandle,
    PVOID ProcessDesiredAccess,
    PVOID ThreadDesiredAccess,
    PVOID ProcessObjectAttributes,
    PVOID ThreadObjectAttributes,
    PVOID ProcessFlags,
    PVOID ThreadFlags,
    PVOID ProcessParameters,
    PVOID CreateInfo,
    PVOID AttributeList)
{

    // int3p("HandlerNtCreateUserProcess", ProcessParameters, AttributeList);

    NTCREATEUSERPROCESS func = GetSysCallAddr();

    NTSTATUS ret = func(
        ProcessHandle,
        ThreadHandle,
        ProcessDesiredAccess,
        ThreadDesiredAccess,
        ProcessObjectAttributes,
        ThreadObjectAttributes,
        ProcessFlags,
        ThreadFlags,
        ProcessParameters,
        CreateInfo,
        AttributeList);

    PUNICODE_STRING pwCreateName = (PUNICODE_STRING)((ULONG64)ProcessParameters + 0x60);

    PLIST_MONITOR monitor = IsDebugProcess(pwCreateName->Buffer);
    if (monitor)
        gvt->Os.Api.PsLookupProcessByProcessId((PVOID)(*(PULONG64)(*(PULONG64)((ULONG64)AttributeList + 0x38))), &monitor->Process);

    monitor = IsMonitorProcess(VmGetCurrentProcess());
    if (monitor)
    {
        wchar buffer[MSG_BUFFER_SIZE] = {0};
        void *CurrentProcess = VmGetCurrentProcess();
        void *CurrentThread = VmGetCurrentThread();

        sprint(buffer, L"%S->open->%S", monitor->name, pwCreateName->Buffer);
        InsertMsg(1, CurrentProcess, CurrentThread, buffer);
    }

    return ret;

    // //ProcessParameters+0x60==PUNICODE_STRING 全路径
    // //ProcessParameters+0x70==PUNICODE_STRING 全路径+命令行参数
    // //AttributeList+0x10==PUNICODE_STRING \??\全路径
    // //[AttributeList+0x38]==CID
    // //[AttributeList+0x58]==EntryPoint
    // PUNICODE_STRING pwCreateName = (PUNICODE_STRING)((ULONG64)ProcessParameters + 0x60);

    // if (pDebug->DebugState == DEBUG_STATE_WAIT_FOR_NAME)
    // {
    // 	/*注意:此函数ZwCreateUserProcess不是由被调试进程的线程调用的*/

    // 	_wcslwr(pDebug->DebugName);
    // 	_wcslwr(pwCreateName->Buffer);

    // 	pDebug->DbgEvent.u.Event_CreateProcess.ProcessID = (PVOID)(*(PULONG64)(*(PULONG64)((ULONG64)AttributeList + 0x38)));
    // 	pDebug->DbgEvent.u.Event_CreateProcess.EntryPoint = (PVOID)(*(PULONG64)(*(PULONG64)((ULONG64)AttributeList + 0x58)));
    // 	pDebug->DbgEvent.u.Event_CreateProcess.hProcess = (HANDLE)(*(PULONG)ProcessHandle);
    // 	pDebug->DbgEvent.u.Event_CreateProcess.hThread = (HANDLE)(*(PULONG)ThreadHandle);
    // 	UCHAR name[0x11]={ 0 };
    // 	std_memcpy(name, PsGetProcessImageFileName(IoGetCurrentProcess()),0x10);
    // 	sprint(pDebug->DbgEvent.u.Event_CreateProcess.wName, L"%s->打开->%S", name, pwCreateName->Buffer);

    // 	pDebug->EntryPoint = pDebug->DbgEvent.u.Event_CreateProcess.EntryPoint;

    // 	pDebug->DbgEvent.EventCode = EVENT_CREATE_PROCESS;

    // 	DbgBreakPoint();

    // 	if (wcsstr(pwCreateName->Buffer, pDebug->DebugName))
    // 	{
    // 		//if (strcmp(name, "svchost.exe") != 0)
    // 		//	return ret;

    // 		/*pDebug->DbgEvent.u.Event_CreateProcess.ProcessID = (PVOID)(*(PULONG64)(*(PULONG64)((ULONG64)AttributeList + 0x38)));
    // 		pDebug->DbgEvent.u.Event_CreateProcess.EntryPoint = (PVOID) (*(PULONG64)(*(PULONG64)((ULONG64)AttributeList + 0x58)));
    // 		pDebug->DbgEvent.u.Event_CreateProcess.hProcess = (HANDLE)(*(PULONG)ProcessHandle);
    // 		pDebug->DbgEvent.u.Event_CreateProcess.hThread = (HANDLE)(*(PULONG)ThreadHandle);
    // 		sprint(pDebug->DbgEvent.u.Event_CreateProcess.wName, L"%S", pwCreateName->Buffer);*/

    // 		PsLookupProcessByProcessId((HANDLE)pDebug->DbgEvent.u.Event_CreateProcess.ProcessID, (PEPROCESS*)&pDebug->DebugED);
    // 		//PsSuspendProcess(pDebug->DebugED);
    // 		//pDebug->IsSuspend = TRUE;
    // 		//pDebug->EntryPoint = pDebug->DbgEvent.u.Event_CreateProcess.EntryPoint;

    // 		//pDebug->DbgEvent.EventCode = EVENT_CREATE_PROCESS;
    // 		pDebug->DebugState = DEBUG_STATE_DEBUGING;
    // 	}
    // }
}

typedef NTSTATUS (*NTMAPVIEWOFSECTION)();
NTSTATUS HandlerNtMapViewOfSection(
    PVOID SectionHandle,
    PVOID ProcessHandle,
    PVOID BaseAddress,
    PVOID ZeroBits,
    PVOID CommitSize,
    PVOID SectionOffset,
    PVOID ViewSize,
    PVOID InheritDisposition,
    PVOID AllocationType,
    PVOID Win32Protect)
{

    // int3p("HandlerNtMapViewOfSection", SectionHandle, ProcessHandle, BaseAddress);

    NTMAPVIEWOFSECTION func = GetSysCallAddr();

    NTSTATUS ret = func(
        SectionHandle,
        ProcessHandle,
        BaseAddress,
        ZeroBits,
        CommitSize,
        SectionOffset,
        ViewSize,
        InheritDisposition,
        AllocationType,
        Win32Protect);
    return ret;
}

void InitHandlerSSDT()
{
    DebugBreak("InitHandlerSSDT", ServiceTableCount, ssdt);
    ssdt[NR_NtCreateUserProcess].handler = HandlerNtCreateUserProcess;
    ssdt[NR_NtLoadDriver].handler = HandlerNtLoadDriver;
    ssdt[NR_NtQueryInformationProcess].handler = HandlerNtQueryInformationProcess;
    ssdt[NR_NtQuerySystemInformation].handler = HandlerNtQuerySystemInformation;
    // ssdt[NR_NtMapViewOfSection].handler = HandlerNtMapViewOfSection;
}