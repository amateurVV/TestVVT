#include "type.h"
#include "vmx.h"
#include "vasm.h"
#include "vmcs.h"
#include "msr.h"
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
    EntryEvent.Bits.Type = Type;
    EntryEvent.Bits.Vector = Vector;
    EntryEvent.Bits.ErrorCode = DeliverErrorCode;
    EntryEvent.Bits.Valid = TRUE;
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
    enum ACCESSTYPE
    {
        MOV_TO_CR,
        MOV_FROM_CR,
        CLTS,
        LMSW
    };

    long CR[] = {GUEST_CR0, 1, 2, GUEST_CR3, GUEST_CR4};

    EXIT_QUALIFICATION_CR_ACCESS Exit = {0};
    vmx_read(VM_EXIT_QUALIFICATION, &Exit.value);

    int3p("HandlerCRX Exit. Set up VMXE");

    if (Exit.Bits.AccessType == MOV_TO_CR)
        vmx_write(CR[Exit.Bits.NumCR], *((uint64 *)GuestRegs + Exit.Bits.NumReg));
    else if (Exit.Bits.AccessType == MOV_FROM_CR)
        vmx_read(CR[Exit.Bits.NumCR], ((uint64 *)GuestRegs + Exit.Bits.NumReg));
    else if (Exit.Bits.AccessType == CLTS)
        int3p("HandlerCRX CLTS");
    else if (Exit.Bits.AccessType == LMSW)
        int3p("HandlerCRX LMSW");

    return TRUE;
}

uint64 HandlerCPUID(PGUESTREG GuestRegs)
{

    switch (GuestRegs->rax)
    {
    case 1:
    {
        vmx_cpuid(GuestRegs);
        if (gvt->HideVMX)
            GuestRegs->rcx &= ~CPUID_1_ECX_SUPPORT_VMX;
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

uint64 ExitNoHandler(PGUESTREG GuestRegs)
{
    int3p("ExitNoHandler", GuestRegs->ExitReason, GuestRegs);
    return TRUE;
}

uint64 HandlerMisconfigEPT(PGUESTREG GuestRegs)
{
    int3p("ExitNoHandler", GuestRegs->ExitReason, gvt->Eptp.value);
    return TRUE;
}

uint64 HandlerRDMSR(PGUESTREG GuestRegs)
{
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
            GuestRegs->rax &= 0xFFFFFFFF00000000;
            GuestRegs->rax |= value.LowPart;
            GuestRegs->rdx &= 0xFFFFFFFF00000000;
            GuestRegs->rdx |= value.HighPart;
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
    switch (GuestRegs->rcx)
    {
    case MSR_IA32_FEATURE_CONTROL:
    {
        if (gvt->HideVMX)
            if (GuestRegs->rax & 1)
            {
                // 注入GP
                return TRUE;
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

    switch (Exit.Bits.Vector)
    {
    // case 0xE:
    // {

    //     PushExcption(&Exit);
    //     writeCR2(ExitQualification);
    //     break;
    // }
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
        PEPT_HOOK_CONTEXT context = FindHookPage(VirAddr, GuestRegs->EProcess);
        if (context)
        {
            PEPTE DestPTE = EptGetGpaPTE((PADDR_PACK)&PhyAddr);
            DestPTE->Attribute = EPT_READ | EPT_WRITE;
            DestPTE->PageFrame4KB = (uint64)context->TargetCodeAddrPhy >> 12;
            vmx_invept(2, &gvt->Eptp.value);
        }
    }
    if (eptve.wrire)
    {
        DebugBreak("HandlerViolationEPT Write", eptve);
        DebugBreak("HandlerViolationEPT Write", GuestRegs, PhyAddr, VirAddr);
        PEPT_HOOK_CONTEXT context = FindHookPage(VirAddr, GuestRegs->EProcess);
        if (context)
        {
            PEPTE DestPTE = EptGetGpaPTE((PADDR_PACK)&PhyAddr);
            DestPTE->Attribute = EPT_READ | EPT_WRITE;
            DestPTE->PageFrame4KB = (uint64)context->TargetCodeAddrPhy >> 12;
            vmx_invept(2, &gvt->Eptp.value);
        }
    }
    if (eptve.exec)
    {
        DebugBreak("HandlerViolationEPT Exec", eptve);
        DebugBreak("HandlerViolationEPT Exec", GuestRegs, PhyAddr, VirAddr);
        PEPT_HOOK_CONTEXT context = FindHookPage(VirAddr, GuestRegs->EProcess);
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
}

uint64 DispatchHandlerVmExit(PGUESTREG GuestRegs)
{
    EXIT_REASON_FIELDS *Exit = (EXIT_REASON_FIELDS *)&GuestRegs->ExitReason;

    if (HandlerExit[Exit->Bits.Basic](GuestRegs))
    {
        GuestIncrementRIP(GuestRegs);
    }

    return TRUE;
}
