#include "type.h"
#include "vmx.h"
#include "vasm.h"
#include "vmcs.h"
#include "msr.h"
#include "std.h"
#include "intel.h"
#include "handler.h"
#include "vmcall.h"
#include "winfunc.h"
#include "debug.h"
#include "winsys.h"
#include "ept.h"

uint64 (*HandlerExit[EXIT_MAX])(PGUESTREG);

/// @brief 处理完成指令后调用,GuestRip跳过指令长度
void GuestIncrementRIP(PGUESTREG GuestRegs)
{
    GuestRegs->GuestRip += GuestRegs->InstrLen;
    vmx_write(GUEST_RIP, GuestRegs->GuestRip);
}

void InjectException(uint32 Type, uint32 Vector, uint32 DeliverErrorCode, uint32 ErrorCode, uint32 Instrlen)
{
    EXIT_INTR_INFO EntryEvent = {0};
    EntryEvent.Type = Type;
    EntryEvent.Vector = Vector;
    EntryEvent.ErrorCode = DeliverErrorCode;
    EntryEvent.IsValid = TRUE;
    vmx_write(VM_ENTRY_INTERRUPTION_INFORMATION_FIELD, EntryEvent.value);
    if (DeliverErrorCode)
        vmx_write(VM_ENTRY_EXCEPTION_ERROR_CODE, ErrorCode);
    if (Instrlen)
        vmx_write(VM_ENTRY_INSTRUCTION_LENGTH, Instrlen);
}

void PushExcption(EXIT_INTR_INFO *Event)
{
    ULONG ErrorCode = 0;
    vmx_read(VM_EXIT_INTERRUPTION_ERROR_CODE, &ErrorCode);

    vmx_write(VM_ENTRY_EXCEPTION_ERROR_CODE, ErrorCode);
    vmx_write(VM_ENTRY_INTERRUPTION_INFORMATION_FIELD, Event->value);
}

uint64 HandlerCRX(PGUESTREG GuestRegs)
{

    EXIT_QUALIFICATION_CR_ACCESS Exit = {0};
    vmx_read(VM_EXIT_QUALIFICATION, &Exit.value);

    enum ACCESSTYPE
    {
        MOV_TO_CR,
        MOV_FROM_CR,
        CLTS,
        LMSW
    };

    uint64 CR[] = {GUEST_CR0, 1, 2, GUEST_CR3, GUEST_CR4};

    // char *strType[] = {"MOV_TO_CR", "MOV_FROM_CR", "CLTS", "LMSW"};
    // char *strCR[] = {"GUEST_CR0", "1", "2", "GUEST_CR3", "GUEST_CR4"};

    // if (DebugObject.DebugER)
    // {
    //     wchar msg[0x100] = {0};
    //     char name[0x12] = {0};
    //     std_memcpy(name, VmGetProcessName(GuestRegs->EProcess), 0x10);

    //     sprint(msg, L"%s,Handler CRX : %s,%s", name, strType[Exit.AccessType], strCR[Exit.NumCR]);

    //     InsertMsg(1, GuestRegs, msg);
    // }
    int3p("HandlerCRX", Exit, GuestRegs);

    if (Exit.AccessType == MOV_TO_CR)
    {
        vmx_write(CR[Exit.NumCR], *((uint64 *)GuestRegs + Exit.NumReg) | CR4_VMXE);
        // vmx_write(CR4_READ_SHADOW, *((uint64 *)GuestRegs + Exit.NumReg) & ~CR4_VMXE);

        uint64 cr4 = 0;
        vmx_read(CR[Exit.NumCR], &cr4);
        int3p("MOV_TO_CR", Exit, cr4, GuestRegs);
        return TRUE;
    }
    else if (Exit.AccessType == MOV_FROM_CR)
    {
        if (Exit.NumCR == 4)
        {
            vmx_read(GUEST_CR4, ((uint64 *)GuestRegs + Exit.NumReg));
            *((uint64 *)GuestRegs + Exit.NumReg) &= ~CR4_VMXE;
            int3p("MOV_FROM_CR", Exit, GuestRegs);
            return TRUE;
        }
        vmx_read(CR[Exit.NumCR], ((uint64 *)GuestRegs + Exit.NumReg));
        int3p("MOV_FROM_CR", Exit, GuestRegs);
    }
    else if (Exit.AccessType == CLTS)
        int3p("HandlerCRX CLTS");
    else if (Exit.AccessType == LMSW)
        int3p("HandlerCRX LMSW");

    return TRUE;
}

uint64 HandlerCPUID(PGUESTREG GuestRegs)
{
    PLIST_MONITOR monitor = IsMonitorProcess(GuestRegs->EProcess);
    if (monitor)
    {
        if (readCS() & 1)
        {
            InjectExceptionGP();
            return FALSE;
        }
        if (((PSLONG64)&GuestRegs->rax)->LowPart >= 0x40000000 && ((PSLONG64)&GuestRegs->rax)->LowPart < 0x50000000)
        {
            InjectExceptionGP();
            return FALSE;
        }
    }
    switch (GuestRegs->rax)
    {
    case 1:
    {
        vmx_cpuid(GuestRegs);
        if (gvt->HideVMX)
        {
            GuestRegs->rcx &= ~(1 << 31);
        }
        break;
    }
    case 0x5555:
    {
        GuestRegs->rax = 0x11111111;
        GuestRegs->rcx = 0x22222222;
        GuestRegs->rdx = 0x33333333;
        GuestRegs->rbx = 0x44444444;
        break;
    }
    default:
        vmx_cpuid(GuestRegs);
        return TRUE;
    }

    return TRUE;
}

uint64 ExitHandlerVmx(PGUESTREG GuestRegs)
{
    // PLIST_MONITOR monitor = IsMonitorProcess(GuestRegs->EProcess);
    // if (monitor)
    // {
    //     int3p("ExitHandlerVmx", GuestRegs);
    //     if (readCS() & 1)
    //     {
    //         // int3p("EXIT_REASON_WRMSR CPL 3", GuestRegs->GuestRip);
    //         InjectExceptionGP();
    //         return FALSE;
    //     }
    //     if (((PSLONG64)&GuestRegs->rcx)->LowPart >= 0x40000000 && ((PSLONG64)&GuestRegs->rcx)->LowPart < 0x50000000)
    //     {
    //         // int3p("EXIT_REASON_WRMSR RCX", GuestRegs->rcx);
    //         InjectExceptionGP();
    //         return FALSE;
    //     }
    // }

    return FALSE;
}
uint64 ExitNoHandler(PGUESTREG GuestRegs)
{
    // int3p("ExitNoHandler", GuestRegs->ExitReason, GuestRegs);
    InjectExceptionGP();
    return TRUE;
}

uint64 HandlerMisconfigEPT(PGUESTREG GuestRegs)
{
    int3p("ExitNoHandler", GuestRegs->ExitReason, gvt->Eptp.value);
    return TRUE;
}

uint64 HandlerRDMSR(PGUESTREG GuestRegs)
{
    // PLIST_MONITOR monitor = IsMonitorProcess(GuestRegs->EProcess);
    // if (monitor)
    // {
    if (readCS() & 1)
    {
        // int3p("EXIT_REASON_WRMSR CPL 3", GuestRegs->GuestRip);
        InjectExceptionGP();
        return FALSE;
    }
    if (((PSLONG64)&GuestRegs->rcx)->LowPart >= 0x40000000 && ((PSLONG64)&GuestRegs->rcx)->LowPart < 0x50000000)
    {
        // int3p("EXIT_REASON_WRMSR RCX", GuestRegs->rcx);
        InjectExceptionGP();
        return FALSE;
    }
    //}

    switch (GuestRegs->rcx)
    {
    case MSR_IA32_FEATURE_CONTROL:
    {
        vmx_rdmsr(GuestRegs);
        if (gvt->HideVMX)
            GuestRegs->rax &= ~1;
        return TRUE;
    }
    case MSR_IA32_LSTAR:
    {
        if (gvt->vm[GuestRegs->CpuIndex].syscall.Hooked)
        {
            SLONG64 value;
            value.QuadPart = gvt->vm[GuestRegs->CpuIndex].syscall.old;
            // GuestRegs->rax &= 0xFFFFFFFF00000000;
            // GuestRegs->rax |= value.LowPart;
            ((PSLONG64)&GuestRegs->rax)->LowPart = value.LowPart;
            ((PSLONG64)&GuestRegs->rdx)->LowPart = value.HighPart;

            // GuestRegs->rdx &= 0xFFFFFFFF00000000;
            // GuestRegs->rdx |= value.HighPart;
            // int3p("MSR_IA32_LSTAR", GuestRegs->rax, GuestRegs->rdx, value.QuadPart);
            return TRUE;
        }
        break;
    }
    default:
        break;
    }

    vmx_rdmsr(GuestRegs);
    return TRUE;
}

uint64 HandlerWRMSR(PGUESTREG GuestRegs)
{
    // PLIST_MONITOR monitor = IsMonitorProcess(GuestRegs->EProcess);
    // if (monitor)
    // {
    if (readCS() & 1)
    {
        // int3p("EXIT_REASON_WRMSR CPL 3", GuestRegs->GuestRip);
        InjectExceptionGP();
        return FALSE;
    }
    if (((PSLONG64)&GuestRegs->rcx)->LowPart >= 0x40000000 && ((PSLONG64)&GuestRegs->rcx)->LowPart < 0x50000000)
    {
        // int3p("EXIT_REASON_WRMSR RCX", GuestRegs->rcx);
        InjectExceptionGP();
        return FALSE;
    }
    //}

    switch (GuestRegs->rcx)
    {
    case MSR_IA32_FEATURE_CONTROL:
    {
        if (gvt->HideVMX)
            if (GuestRegs->rax & 1)
            {
                // InjectExceptionGP();
                // return FALSE;
                break;
            }
        break;
    }
    case MSR_IA32_LSTAR:
    {
        if (gvt->vm[GuestRegs->CpuIndex].syscall.Hooked)
        {
            SLONG64 value;
            value.LowPart = GuestRegs->rax;
            value.HighPart = GuestRegs->rdx;
            gvt->vm[GuestRegs->CpuIndex].syscall.old = value.QuadPart;
            return TRUE;
        }
        break;
    }
    default:
        break;
    }
    vmx_wrmsr(GuestRegs);
    return TRUE;
}

uint64 HandlerRDTSC(PGUESTREG GuestRegs)
{
    vmx_rdtsc(GuestRegs);
    return TRUE;
}
uint64 HandlerRDTSCP(PGUESTREG GuestRegs)
{
    vmx_rdtscp(GuestRegs);
    return TRUE;
}

uint64 HandlerEXCPTION(PGUESTREG GuestRegs)
{
    EXIT_INTR_INFO Exit = {0};
    vmx_read(VM_EXIT_INTERRUPTION_INFORMATION, &Exit.value);
    uint64 ExitQualification = 0;
    vmx_read(VM_EXIT_QUALIFICATION, &ExitQualification);

    // int3p("HandlerEXCPTION", GuestRegs, Exit, ExitQualification);

    switch (Exit.Vector)
    {
    case 0xE:
    {
        PushExcption(&Exit);
        writeCR2(ExitQualification);
        return FALSE;
    }
    case 1:
    {
        InjectExceptionInt1();
        return FALSE; // 返回FALSE不需要增加RIP
    }
    case 3:
    {
        if (EptHandlerBreakPoint(GuestRegs))
        {
            DebugBreak("EptHandlerBreakPoint", GuestRegs->GuestRip);
            return FALSE;
        }

        InjectExceptionInt3();
        return FALSE; // 返回FALSE不需要增加RIP
    }
    default:

        break;
    }

    return TRUE;
}

uint64 HandlerViolationEPT(PGUESTREG GuestRegs)
{
    EptViolation eptve;

    vmx_read(VM_EXIT_QUALIFICATION, &eptve);

    void *PhyAddr = 0;
    void *VirAddr = 0;
    vmx_read(GUEST_PHYSICAL_ADDRESS_FULL, &PhyAddr);
    vmx_read(GUEST_LINEAR_ADDRESS, &VirAddr);

    if (eptve.read)
    {
        DebugBreak("HandlerViolationEPT Read", eptve);
        DebugBreak("HandlerViolationEPT Read", GuestRegs, PhyAddr, VirAddr);
        PEPT_HOOK_CONTEXT context = FindHookPage(PhyAddr, GuestRegs->EProcess);
        if (context)
        {
            PEPTE DestPTE = EptGetGpaPTE((PADDR_PACK)&PhyAddr);

            if (context->HookType == EPT_EXECUTE)
            {
                DestPTE->Attribute = EPT_READ | EPT_WRITE;
                DestPTE->PageFrame4KB = (uint64)context->TargetCodeAddrPhy >> 12;
            }
            else if (context->HookType == EPT_READ)
            {
                DestPTE->Attribute = EPT_READ | EPT_EXECUTE;
                *(uint32 *)VirAddr = 0;
            }
            vmx_invept(2, &gvt->Eptp.value);
        }
    }
    if (eptve.wrire)
    {
        DebugBreak("HandlerViolationEPT Write", eptve);
        DebugBreak("HandlerViolationEPT Write", GuestRegs, PhyAddr, VirAddr);
        PEPT_HOOK_CONTEXT context = FindHookPage(PhyAddr, GuestRegs->EProcess);
        if (context)
        {
            PEPTE DestPTE = EptGetGpaPTE((PADDR_PACK)&PhyAddr);

            if (context->HookType == EPT_EXECUTE)
            {
                DestPTE->Attribute = EPT_READ | EPT_WRITE;
                DestPTE->PageFrame4KB = (uint64)context->TargetCodeAddrPhy >> 12;
            }
            else if (context->HookType == EPT_READ)
            {
                DestPTE->Attribute = EPT_WRITE | EPT_EXECUTE;
            }

            vmx_invept(2, &gvt->Eptp.value);
        }
    }
    if (eptve.exec)
    {
        DebugBreak("HandlerViolationEPT Exec", eptve);
        DebugBreak("HandlerViolationEPT Exec", GuestRegs, PhyAddr, VirAddr);
        PEPT_HOOK_CONTEXT context = FindHookPage(PhyAddr, GuestRegs->EProcess);
        if (context)
        {
            PEPTE DestPTE = EptGetGpaPTE((PADDR_PACK)&PhyAddr);
            DestPTE->Attribute = EPT_EXECUTE;
            DestPTE->PageFrame4KB = (uint64)gvt->Os.Api.MmGetPhysicalAddress(context->NewPage) >> 12;
            vmx_invept(2, &gvt->Eptp.value);
        }
    }

    vmx_invept(2, &gvt->Eptp);
    return TRUE;
}

void InitHandlerVmExit()
{
    for (uint8 i = 0; i < EXIT_MAX; i++)
        HandlerExit[i] = ExitNoHandler;

    HandlerExit[EXIT_REASON_EXCEPTION_NMI] = HandlerEXCPTION;
    HandlerExit[EXIT_REASON_CPUID] = HandlerCPUID;
    HandlerExit[EXIT_REASON_CR_ACCESS] = HandlerCRX;

    HandlerExit[EXIT_REASON_RDMSR] = HandlerRDMSR;
    HandlerExit[EXIT_REASON_WRMSR] = HandlerWRMSR;

    HandlerExit[EXIT_REASON_RDTSC] = HandlerRDTSC;
    HandlerExit[EXIT_REASON_RDTSCP] = HandlerRDTSCP;

    HandlerExit[EXIT_REASON_EPT_VIOLATION] = HandlerViolationEPT;
    HandlerExit[EXIT_REASON_EPT_MISCONFIG] = HandlerMisconfigEPT;

    HandlerExit[EXIT_REASON_VMCALL] = DispatchHandlerVmCall;

    HandlerExit[EXIT_REASON_VMCLEAR] = ExitHandlerVmx;
    HandlerExit[EXIT_REASON_VMLAUNCH] = ExitHandlerVmx;
    HandlerExit[EXIT_REASON_VMPTRLD] = ExitHandlerVmx;
    HandlerExit[EXIT_REASON_VMPTRST] = ExitHandlerVmx;
    HandlerExit[EXIT_REASON_VMREAD] = ExitHandlerVmx;
    HandlerExit[EXIT_REASON_VMRESUME] = ExitHandlerVmx;
    HandlerExit[EXIT_REASON_VMWRITE] = ExitHandlerVmx;
    HandlerExit[EXIT_REASON_VMXOFF] = ExitHandlerVmx;
    HandlerExit[EXIT_REASON_VMXON] = ExitHandlerVmx;
    HandlerExit[EXIT_REASON_VMFUNC] = ExitHandlerVmx;
}

uint64 DispatchHandlerVmExit(PGUESTREG GuestRegs)
{

    wchar msg[MSG_BUFFER_SIZE] = {0};

    char name[0x12] = {0};

    PLIST_MONITOR monitor = IsMonitorProcess(GuestRegs->EProcess);
    if (monitor)
    {
        if (GuestRegs->ExitReason.Basic == EXIT_REASON_VMCALL && GuestRegs->rax == 3)
        {
        }
        else
        {
            if (GuestRegs->ExitReason.Basic != EXIT_REASON_CPUID)
            {

                if (GuestRegs->ExitReason.Basic == EXIT_REASON_WRMSR || GuestRegs->ExitReason.Basic == EXIT_REASON_RDMSR)
                {
                    switch (GuestRegs->rcx)
                    {
                    case MSR_IA32_GS_BASE:
                    case MSR_IA32_FS_BASE:
                    case MSR_IA32_KERNEL_GS_BASE:
                    case MSR_IA32_LSTAR:
                    case MSR_IA32_CLOCK_MODULATION:
                    case MSR_IA32_MPERF:
                    case MSR_IA32_APERF:
                    case MSR_PP0_ENERGY_STATUS:
                    case MSR_IA32_PERF_CTL:
                        break;

                    default:
                        sprint(msg, L"%S --> %s --> :rax:%x32,:rcx:%x32", monitor->name, strExit[GuestRegs->ExitReason.Basic], GuestRegs->rax, GuestRegs->rcx);
                        InsertMsg(1, GuestRegs->EProcess, GuestRegs->EThread, msg);

                        int3p("DispatchHandlerVmExit", strExit[GuestRegs->ExitReason.Basic], GuestRegs);
                        break;
                    }
                }
                else
                {
                    sprint(msg, L"%S --> %s --> :rax:%x32,:rcx:%x32", monitor->name, strExit[GuestRegs->ExitReason.Basic], GuestRegs->rax, GuestRegs->rcx);
                    InsertMsg(1, GuestRegs->EProcess, GuestRegs->EThread, msg);

                    int3p("DispatchHandlerVmExit", strExit[GuestRegs->ExitReason.Basic], GuestRegs);
                }
            }
        }
    }

    if (HandlerExit[GuestRegs->ExitReason.Basic](GuestRegs))
    {
        GuestIncrementRIP(GuestRegs);
    }

    return TRUE;
}
