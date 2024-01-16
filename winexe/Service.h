#pragma once
#include <windows.h>

typedef struct _PROC_INFO
{
    ULONG64 pid;
    WCHAR name[0x200];

} PROC_INFO, *PPROC_INFO;

long ServiceEnumProcess(PPROC_INFO buffer);
long ServiceInitDebug();
long ServiceCreateDebug(HANDLE pid);
long ServiceDebugProcess(HANDLE pid);
long ServiceDebugReadMemory(ULONG64 VirtualAdderss, PVOID ReadBuffer, ULONG64 ReadSize);
long ServiceDebugWriteMemory(ULONG64 VirtualAdderss, PVOID WriteBuffer, ULONG64 WriteSize);
long ServiceDebugBreakPoint(ULONG64 VirtualAdderss);
long ServiceDebugEnumVad();
long ServiceSuperHook(HANDLE DestPid,void* TargetCodeAddrVir,void* HookCodeAddr);
long ServiceEnableEptHook();

long ServiceCreateThread(HANDLE hProcess, PTHREAD_START_ROUTINE ThreadProc, PVOID ThreadBuffer);
