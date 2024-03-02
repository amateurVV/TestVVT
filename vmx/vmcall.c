#include "type.h"
#include "vmx.h"
#include "vasm.h"
#include "vmcs.h"
#include "msr.h"
#include "intel.h"
#include "std.h"
#include "handler.h"
#include "debug.h"
#include "vmcall.h"
#include "winfunc.h"
#include "ept.h"

uint64 (*HandlerVmCall[VMCALL_MAX])(PGUESTREG);

uint64 VmcallNoHandler(PGUESTREG GuestRegs)
{
    int3p("VmcallNoHandler", GuestRegs->rax);
    return TRUE;
}

uint64 VmCallEnableEptModeHook(PGUESTREG GuestReg)
{
    TargetProcessCR3(GuestReg->EProcess);
    MSR_IA32_VMX_PROCBASED_CTLS2_REGISTER Secondry = {0}, SecondrySet = {0};
    Secondry.value = rdmsr(MSR_IA32_VMX_PROCBASED_CTLS2);

    vmx_read(SECONDARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS, &SecondrySet.value);

    SecondrySet.Bits->EPT = TRUE;

    // int3p("VmCallEnableEptModeHook");
    if (!SetControls(&SecondrySet.value, Secondry.value))
    {
        int3p("SetVmxExecutionCTLS SetSecondry", SecondrySet.value, Secondry.value, 0);
        return FALSE;
    }

    vmx_write(SECONDARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS, SecondrySet.value);

    // vmx_invept(2, &gvt->Eptp.value);

    return TRUE;
}

uint64 VmCallHookEPT(PGUESTREG GuestReg)
{
    PEPT_HOOK_CONTEXT HookContext = (void *)GuestReg->rcx;
    DebugBreak("VmCallHookEPT", HookContext);

    GuestReg->rax = EptHook(HookContext);

    return TRUE;
}
uint64 VmCallUnHookEPT(PGUESTREG GuestReg)
{
    return TRUE;
}
uint64 VmCallHookLsatr(PGUESTREG GuestReg)
{
    uint64 CpuIndex = GuestReg->CpuIndex;

    gvt->vm[CpuIndex].syscall.new = (uint64)HandlerSystemCall;
    gvt->vm[CpuIndex].syscall.old = rdmsr(MSR_IA32_LSTAR);

    mbts((void *)((uint64)gvt->vm[CpuIndex].MsrBitMap.vir + 0x400), MSR_IA32_LSTAR & 0x1FFF);
    mbts((void *)((uint64)gvt->vm[CpuIndex].MsrBitMap.vir + 0xC00), MSR_IA32_LSTAR & 0x1FFF);

    wrmsr(MSR_IA32_LSTAR, gvt->vm[CpuIndex].syscall.new);

    gvt->vm[CpuIndex].syscall.Hooked = TRUE;
    GuestReg->rax = TRUE;

    return TRUE;
}

uint64 VmCallUnHookLsatr(PGUESTREG GuestReg)
{
    uint64 CpuIndex = GuestReg->CpuIndex;

    wrmsr(MSR_IA32_LSTAR, gvt->vm[CpuIndex].syscall.old);

    mbtr((void *)((uint64)gvt->vm[CpuIndex].MsrBitMap.vir + 0x400), MSR_IA32_LSTAR & 0x1FFF);
    mbtr((void *)((uint64)gvt->vm[CpuIndex].MsrBitMap.vir + 0xC00), MSR_IA32_LSTAR & 0x1FFF);

    gvt->vm[CpuIndex].syscall.Hooked = FALSE;
    GuestReg->rax = TRUE;

    return TRUE;
}

uint64 VmCallHideVMX(PGUESTREG GuestReg)
{
    uint64 CpuIndex = GuestReg->CpuIndex;

    uint64 cr4 = 0;
    vmx_read(GUEST_CR4, &cr4);
    vmx_write(CR4_GUEST_HOST_MASK, CR4_VMXE);
    vmx_write(CR4_READ_SHADOW, cr4 & ~CR4_VMXE);

    mbts((void *)((uint64)gvt->vm[CpuIndex].MsrBitMap.vir + 0x000), MSR_IA32_FEATURE_CONTROL & 0x1FFF);
    mbts((void *)((uint64)gvt->vm[CpuIndex].MsrBitMap.vir + 0x800), MSR_IA32_FEATURE_CONTROL & 0x1FFF);

    gvt->HideVMX = TRUE;
    GuestReg->rax = TRUE;

    return TRUE;
}

uint64 VmCallUnHideVMX(PGUESTREG GuestReg)
{
    uint64 CpuIndex = GuestReg->CpuIndex;

    uint64 cr4 = 0;
    vmx_read(GUEST_CR4, &cr4);
    vmx_write(CR4_GUEST_HOST_MASK, 0);
    vmx_write(CR4_READ_SHADOW, -1);

    mbtr((void *)((uint64)gvt->vm[CpuIndex].MsrBitMap.vir + 0x000), MSR_IA32_FEATURE_CONTROL & 0x1FFF);
    mbtr((void *)((uint64)gvt->vm[CpuIndex].MsrBitMap.vir + 0x800), MSR_IA32_FEATURE_CONTROL & 0x1FFF);

    gvt->HideVMX = FALSE;
    GuestReg->rax = TRUE;

    return TRUE;
}

/// @brief 来自己syscall64 的 vmcall. 获取 SSDT HOOK 函数
uint64 VmCallGetServiceHandler(PGUESTREG GuestReg)
{
    uint64 callnr = GetSysCallNumber();
    DebugBreak("VmCallGetServiceHandler", callnr, GuestReg);
    if (callnr > ServiceTableCount)
        return FALSE;

    // PLIST_MONITOR monitor = IsMonitorProcess(GuestReg->EProcess);
    // if (monitor)
    // {
    //     wchar buffer[0x200] = {0};
    //     sprint(buffer, L"%S-->%s", monitor->name, ssdt[callnr].name);
    //     InsertMsg(1, GuestReg->EProcess, GuestReg->EThread, buffer);
    // }

    uint64 handler = (uint64)ssdt[callnr].handler;
    if (handler)
    {
        GuestReg->GuestRip += 3;
        GuestReg->rax = handler;
        return TRUE;
    }
    return FALSE;
}

void InitHandlerVmCall()
{
    for (uint8 i = 0; i < VMCALL_MAX; i++)
        HandlerVmCall[i] = VmcallNoHandler;

    HandlerVmCall[VMCALL_HOOK_LSTAR] = VmCallHookLsatr;
    HandlerVmCall[VMCALL_UN_HOOK_LSTAR] = VmCallUnHookLsatr;
    HandlerVmCall[VMCALL_HANDLER_SYSTEMCALL64] = VmCallGetServiceHandler;
    HandlerVmCall[VMCALL_HIDE_VMX] = VmCallHideVMX;
    HandlerVmCall[VMCALL_UN_HIDE_VMX] = VmCallUnHideVMX;
    HandlerVmCall[VMCALL_HOOK_EPT] = VmCallHookEPT;
    HandlerVmCall[VMCALL_UN_HOOK_EPT] = VmCallUnHookEPT;
    HandlerVmCall[VMCALL_ENABLE_MODE_EPT] = VmCallEnableEptModeHook;
    HandlerVmCall[VMCALL_GET_MSG] = VmcallGetMsg;
}

/// @brief 返回TRUE,GUEST_RIP,自动加指令长度,返回FALSE要自己加指令长度
uint64 DispatchHandlerVmCall(PGUESTREG GuestRegs)
{
    if (GuestRegs->rax < VMCALL_MAX)
    {
        // 返回值已放在RAX.
        HandlerVmCall[GuestRegs->rax](GuestRegs);
    }
    else
    {
        InjectExceptionGP();
    }

    return TRUE;
}
