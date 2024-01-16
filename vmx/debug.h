#pragma once
#include "ssdt.h"

// #define EXCEPTION_DEBUG_EVENT 1
// #define CREATE_THREAD_DEBUG_EVENT 2
// #define CREATE_PROCESS_DEBUG_EVENT 3
// #define EXIT_THREAD_DEBUG_EVENT 4
// #define EXIT_PROCESS_DEBUG_EVENT 5
// #define LOAD_DLL_DEBUG_EVENT 6
// #define UNLOAD_DLL_DEBUG_EVENT 7
// #define OUTPUT_DEBUG_STRING_EVENT 8
// #define RIP_EVENT 9

// #define EXCEPTION_MAXIMUM_PARAMETERS 15

// typedef struct _EXCEPTION_RECORD
// {
//     unsigned long ExceptionCode;
//     unsigned long ExceptionFlags;
//     struct _EXCEPTION_RECORD *ExceptionRecord;
//     void *ExceptionAddress;
//     unsigned long NumberParameters;
//     void *ExceptionInformation[EXCEPTION_MAXIMUM_PARAMETERS];
// } EXCEPTION_RECORD;

// typedef unsigned long (*PTHREAD_START_ROUTINE)(void *lpThreadParameter);
// typedef PTHREAD_START_ROUTINE LPTHREAD_START_ROUTINE;

// typedef void *(*PENCLAVE_ROUTINE)(void *lpThreadParameter);
// typedef PENCLAVE_ROUTINE LPENCLAVE_ROUTINE;

// typedef struct _EXCEPTION_DEBUG_INFO
// {
//     EXCEPTION_RECORD ExceptionRecord;
//     unsigned long dwFirstChance;
// } EXCEPTION_DEBUG_INFO, *LPEXCEPTION_DEBUG_INFO;

// typedef struct _CREATE_THREAD_DEBUG_INFO
// {
//     void *hThread;
//     void *lpThreadLocalBase;
//     LPTHREAD_START_ROUTINE lpStartAddress;
// } CREATE_THREAD_DEBUG_INFO, *LPCREATE_THREAD_DEBUG_INFO;

// typedef struct _CREATE_PROCESS_DEBUG_INFO
// {
//     void *hFile;
//     void *hProcess;
//     void *hThread;
//     void *lpBaseOfImage;
//     unsigned long dwDebugInfoFileOffset;
//     unsigned long nDebugInfoSize;
//     void *lpThreadLocalBase;
//     LPTHREAD_START_ROUTINE lpStartAddress;
//     void *lpImageName;
//     short fUnicode;
// } CREATE_PROCESS_DEBUG_INFO, *LPCREATE_PROCESS_DEBUG_INFO;

// typedef struct _EXIT_THREAD_DEBUG_INFO
// {
//     unsigned long dwExitCode;
// } EXIT_THREAD_DEBUG_INFO, *LPEXIT_THREAD_DEBUG_INFO;

// typedef struct _EXIT_PROCESS_DEBUG_INFO
// {
//     unsigned long dwExitCode;
// } EXIT_PROCESS_DEBUG_INFO, *LPEXIT_PROCESS_DEBUG_INFO;

// typedef struct _LOAD_DLL_DEBUG_INFO
// {
//     void *hFile;
//     void *lpBaseOfDll;
//     unsigned long dwDebugInfoFileOffset;
//     unsigned long nDebugInfoSize;
//     void *lpImageName;
//     short fUnicode;
// } LOAD_DLL_DEBUG_INFO, *LPLOAD_DLL_DEBUG_INFO;

// typedef struct _UNLOAD_DLL_DEBUG_INFO
// {
//     void *lpBaseOfDll;
// } UNLOAD_DLL_DEBUG_INFO, *LPUNLOAD_DLL_DEBUG_INFO;

// typedef struct _OUTPUT_DEBUG_STRING_INFO
// {
//     char *lpDebugStringData;
//     short fUnicode;
//     short nDebugStringLength;
// } OUTPUT_DEBUG_STRING_INFO, *LPOUTPUT_DEBUG_STRING_INFO;

// typedef struct _RIP_INFO
// {
//     unsigned long dwError;
//     unsigned long dwType;
// } RIP_INFO, *LPRIP_INFO;

// typedef struct _DEBUG_EVENT
// {
//     unsigned long dwDebugEventCode;
//     unsigned long dwProcessId;
//     unsigned long dwThreadId;
//     union
//     {
//         EXCEPTION_DEBUG_INFO Exception;
//         CREATE_THREAD_DEBUG_INFO CreateThread;
//         CREATE_PROCESS_DEBUG_INFO CreateProcessInfo;
//         EXIT_THREAD_DEBUG_INFO ExitThread;
//         EXIT_PROCESS_DEBUG_INFO ExitProcess;
//         LOAD_DLL_DEBUG_INFO LoadDll;
//         UNLOAD_DLL_DEBUG_INFO UnloadDll;
//         OUTPUT_DEBUG_STRING_INFO DebugString;
//         RIP_INFO RipInfo;
//     } u;
// } DEBUG_EVENT, *LPDEBUG_EVENT;

typedef struct _DEBUG_OBJECT
{
    void *DebugER; // 调试器
    void *DebugED; // 被调试
    // DEBUG_EVENT DebugEvent;

} DEBUG_OBJECT, *PDEBUG_OBJECT;

extern uint64 (**HandlerDebugService)();
extern void InitHandlerDebugService();

extern DEBUG_OBJECT DebugObject;