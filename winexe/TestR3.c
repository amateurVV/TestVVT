#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "Service.h"

#pragma pack(8)
typedef union _ADDR_PACK
{
    struct
    {
        unsigned long long offset : 12;
        unsigned long long pte : 9;
        unsigned long long pde : 9;
        unsigned long long pdpte : 9;
        unsigned long long pml4e : 9;
        unsigned long long sym : 16;
    } s;
    ULONG64 value;

} ADDR_PACK, *PADDR_PACK;
#pragma pcak()

DWORD ThreadStart(PVOID Context)
{
    printf_s("ThreadStart,arg:%d\n", Context);
}

DWORD HookThreadStart(PVOID Context)
{
    printf_s("Hook ThreadStart Hook Bit : %X\n", *(char *)ThreadStart);
}

void TestSuperHook()
{
    HANDLE pid = 0;
    printf_s("%s", "SuperHook Enter PID : ");
    scanf_s("%d", &pid, sizeof(HANDLE));
    ServiceSuperHook(pid, ThreadStart, HookThreadStart, EPT_EXECUTE);
}

void TestEnumProcess()
{
    PPROC_INFO buffer = calloc(sizeof(PROC_INFO), 0x100);
    ServiceEnumProcess(buffer);
    for (size_t i = 0; i < 0x100; i++)
    {
        if (buffer[i].pid)
        {
            if (wcsstr(buffer[i].name, L"TestR3.exe"))
            {
                printf_s("ord:%03d,pid:%05d,name:%S\n", i, buffer[i].pid, buffer[i].name);
                break;
            }
        }
    }
    free(buffer);
}

void TestCreateThread()
{
    HANDLE pid = 0;
    ULONG64 num;
    printf_s("%s", "CreateThread Enter PID : ");
    scanf_s("%d", &pid, sizeof(HANDLE));
    printf_s("%s", "CreateThread Enter Number : ");
    scanf_s("%d", &num, sizeof(ULONG64));
    ServiceCreateThread(pid, (PTHREAD_START_ROUTINE)ThreadStart, (PVOID)num);
}

typedef struct _LIST_THREAD
{
    struct _LIST_THREAD *Next;
    void *Thread;
    HANDLE hwFile;
} LIST_THREAD, *PLIST_THREAD;

PLIST_THREAD gListThread = 0;

PLIST_THREAD InsertListThread(void *EThread)
{
    PLIST_THREAD Thread = calloc(1, sizeof(LIST_THREAD));
    Thread->Next = gListThread;
    Thread->Thread = EThread;
    char str[0x30] = {0};
    sprintf(str, "C:\\Users\\Sylar\\Desktop\\%llX.txt", EThread);
    Thread->hwFile = CreateFileA(str,                   // 要打开的文件名
                                 GENERIC_WRITE,         // 以写方式打开开
                                 0,                     // 可共享读
                                 NULL,                  // 默认安全设置
                                 CREATE_ALWAYS,         // 打开已经存在的文件
                                 FILE_ATTRIBUTE_NORMAL, // 常规属性打开
                                 NULL);                 // 无模板
    // 判断是否成功打开
    if (Thread->hwFile == INVALID_HANDLE_VALUE)
    {
        printf("open file %d\n", GetLastError());
    }

    gListThread = Thread;
    return Thread;
}

PLIST_THREAD FindListProcess(void *EThread)
{
    PLIST_THREAD Thread = gListThread;
    while (Thread)
    {
        if (Thread->Thread == EThread)
            return Thread;

        Thread = Thread->Next;
    }
    return InsertListThread(EThread);
}

DWORD SaveDataToFile(PDBGMSG pMsg)
{
    PLIST_THREAD Thread = FindListProcess(pMsg->Thread);
    // 成功写入的数据大小
    DWORD dwWritedDateSize;

    char str[0x200] = {0};
    sprintf_s(str, 0x200, "Type:%d,Process:%016llX,Thread:%016llX,%S\n", pMsg->type, pMsg->Process, pMsg->Thread, pMsg->buffer);

    // 设置文件指针到文件为
    // SetFilePointer(Thread->hwFile, 0, 0, FILE_END);
    // 将数据写入文件
    if (!WriteFile(Thread->hwFile, str, strlen(str), &dwWritedDateSize, NULL))
    {
        printf("write file %d\n", GetLastError());
    }
    else
    {
        printf("write ok %d\n", dwWritedDateSize);
    }

    return 0;
}

DWORD MsgLoop(PVOID Context)
{

    PDBGMSG pMsg = calloc(1, sizeof(DBGMSG));
    while (1)
    {
        if (ServiceGetMsg(pMsg))
        {
            SaveDataToFile(pMsg);
        }
    }
}

void TestEPTHOOK()
{
    // 开启EPT HOOK
    // ServiceEnableEptHook();

    DWORD pid = GetCurrentProcessId();
    printf_s("Current Process ID :%d\n", pid);

    HANDLE tarPID = 0;
    ULONG64 arg;
    printf_s("%s", "Hook PID : ");
    scanf_s("%d", &tarPID, sizeof(HANDLE));
    printf_s("%s", "Thread arg : ");
    scanf_s("%d", &arg, sizeof(ULONG64));
    ServiceCreateThread(tarPID, (PTHREAD_START_ROUTINE)ThreadStart, (PVOID)arg);

    system("pause");

    ServiceSuperHook(tarPID, ThreadStart, HookThreadStart, EPT_EXECUTE);

    ServiceSetCI(0);

    ServiceCreateThread(tarPID, (PTHREAD_START_ROUTINE)ThreadStart, (PVOID)arg);
}
int main(int argc, char *argv[])
{
    // ServiceHideDriver(L"TestVT");

    ServiceInitDebug();

    // ServiceCreateDebug(GetCurrentProcessId());

    ServiceDebugProcessForName(L"Lostark.exe");
    ServiceDebugProcessForName(L"ACE-Helper.exe");
    ServiceDebugProcessForName(L"client_launcher.exe");
    ServiceDebugProcessForName(L"wegame.exe");
    ServiceDebugProcessForName(L"tcls_core.exe");
    ServiceDebugProcessForName(L"la_helper_main.exe");
    
    CreateThread(0, 0, MsgLoop, NULL, 0, 0);

    // TestEnumProcess();

    // DWORD pid = GetCurrentProcessId();

    // printf_s("%s%d\n", "Current Process ID : ", pid);
    // TestCreateThread();

    // TestEPTHOOK();
    //  TestCreateThread();

    system("pause");
    return (0);
}
