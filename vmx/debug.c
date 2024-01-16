#include "type.h"
#include "std.h"
#include "file.h"
#include "intel.h"
#include "debug.h"
#include "vmx.h"
#include "disasm.h"
#include "vasm.h"
#include "winfunc.h"

DEBUG_OBJECT DebugObject;
uint64 (**HandlerDebugService)();

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

    int3p("HandlerNtCreateUserProcess", ProcessParameters, AttributeList);

    ULONG CallNumber = GetSysCallNumber();
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

// NTSTATUS HandlerNtMapViewOfSection(
//   [in]                HANDLE          SectionHandle,
//   [in]                HANDLE          ProcessHandle,
//   [in, out]           PVOID           *BaseAddress,
//   [in]                ULONG_PTR       ZeroBits,
//   [in]                SIZE_T          CommitSize,
//   [in, out, optional] PLARGE_INTEGER  SectionOffset,
//   [in, out]           PSIZE_T         ViewSize,
//   [in]                SECTION_INHERIT InheritDisposition,
//   [in]                ULONG           AllocationType,
//   [in]                ULONG           Win32Protect
// );
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

    int3p("HandlerNtMapViewOfSection", SectionHandle, ProcessHandle, BaseAddress);

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

void InitHandlerDebugService()
{
    DebugBreak("InitHandlerDebugService", ServiceTableCount, HandlerDebugService, ssdt);
    ssdt[NR_NtCreateUserProcess].handler = HandlerNtCreateUserProcess;
    ssdt[NR_NtMapViewOfSection].handler = HandlerNtMapViewOfSection;
}
