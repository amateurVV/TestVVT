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
    printf_s("Hook ThreadStart Hook Bit : %X\n", *(char*)ThreadStart);
}

void TestSuperHook()
{
    HANDLE pid = 0;
    printf_s("%s", "SuperHook Enter PID : ");
    scanf_s("%d", &pid, sizeof(HANDLE));
    ServiceSuperHook(pid, ThreadStart, HookThreadStart);
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

int main(int argc, char *argv[])
{
    // ServiceInitDebug();
    // TestEnumProcess();
    //ServiceEnableEptHook();

    DWORD pid = GetCurrentProcessId();

    printf_s("%s%d\n", "Current Process ID : ", pid);
    TestCreateThread();

    TestSuperHook();
    TestCreateThread();

    system("pause");
    return (0);
}
