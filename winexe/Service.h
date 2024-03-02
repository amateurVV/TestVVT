#pragma once
#include <windows.h>

#define EPT_READ 1
#define EPT_WRITE 2
#define EPT_EXECUTE 4

#define MSG_BUFFER_SIZE 0xEC

typedef struct _PROC_INFO
{
    ULONG64 pid;
    WCHAR name[0x200];

} PROC_INFO, *PPROC_INFO;

typedef struct _DBGMSG {
	ULONG64 type;
	void* Process;
	void* Thread;
	WCHAR buffer[MSG_BUFFER_SIZE];
}DBGMSG, * PDBGMSG;

long ServiceEnumProcess(PPROC_INFO buffer);
long ServiceInitDebug();
long ServiceCreateDebug(DWORD pid);
long ServiceDebugProcessForName(PWCHAR name);
long ServiceDebugReadMemory(ULONG64 VirtualAdderss, PVOID ReadBuffer, ULONG64 ReadSize);
long ServiceDebugWriteMemory(ULONG64 VirtualAdderss, PVOID WriteBuffer, ULONG64 WriteSize);
long ServiceDebugBreakPoint(ULONG64 VirtualAdderss);
long ServiceDebugEnumVad();
long ServiceSuperHook(HANDLE DestPid,void* TargetCodeAddrVir,void* HookCodeAddr,char mode);
long ServiceEnableEptHook();
long ServiceGetMsg(PDBGMSG pMsg);
long ServiceHideDriver(WCHAR* SysName);
long ServiceUnHideDriver();
long ServiceSetCI(char data);

long ServiceCreateThread(HANDLE hProcess, PTHREAD_START_ROUTINE ThreadProc, PVOID ThreadBuffer);

long VmcallGetMsg(PDBGMSG pMsg);
