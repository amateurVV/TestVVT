#pragma once

typedef struct _PROC_INFO
{
    uint64 Pid;
    wchar name[0x200];

} PROC_INFO, *PPROC_INFO;

typedef enum _SERVICE_CLASS
{
    SERVICE_BASE = 0,
    SERVICE_ENUM_PROCESS,
    SERVICE_INIT_DEBUG,
    SERVICE_CREATE_DEBUG,
    SERVICE_CREATE_TRHEAD,
    SERVICE_DEBUG_PROCESS,
    SERVICE_DEBUG_READMEMORY,
    SERVICE_DEBUG_WRITEMEMORY,
    SERVICE_DEBUG_BREAKPOINT,
    SERVICE_DEBUG_ENUMVAD,
    SERVICE_SUPER_HOOK,
    SERVICE_ENABLE_EPT_HOOK,
    SERVICE_GET_MESSAGE,
    SERVICE_HIDE_DRIVER,
    SERVICE_UN_HIDE_DRIVER,
    SERVICE_SET_CI,


    



    SERVICE_MAX
} SERVICE_CLASS;

extern uint64 (*HandlerSystemService[SERVICE_MAX])();

void InitHandlerSystemService();
uint64 GetSystemServiceFuncAddr(uint64 number);

