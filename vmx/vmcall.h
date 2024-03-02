#pragma once

typedef enum _VMCALL_CLASS
{
    VMCALL_BASE = 0,
    VMCALL_HOOK_LSTAR,
    VMCALL_UN_HOOK_LSTAR,
    VMCALL_HANDLER_SYSTEMCALL64,
    VMCALL_HIDE_VMX,
    VMCALL_UN_HIDE_VMX,
    VMCALL_HOOK_EPT,
    VMCALL_UN_HOOK_EPT,
    VMCALL_ENABLE_MODE_EPT,
    VMCALL_GET_MSG,

    VMCALL_MAX
} VMCALL_CLASS;

extern uint64 (*HandlerVmCall[VMCALL_MAX])(PGUESTREG);
extern void InitHandlerVmCall();
uint64 DispatchHandlerVmCall(PGUESTREG GuestRegs);
