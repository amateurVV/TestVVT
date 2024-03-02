#include "type.h"
#include "std.h"
#include "file.h"
#include "intel.h"
#include "debug.h"
#include "vmx.h"
#include "disasm.h"
#include "vasm.h"
#include "winfunc.h"

uint64 g_lock_msg = 0;
DEBUG_OBJECT DebugObject = {0};

// 复制消息到应用层传来的地址
uint64 ServiceGetMsg(PDBGMSG pMsg)
{
    while (InterlockedCmpExchange64(&g_lock_msg, 1, 0))
        ;
    PLIST_MSG HeadMsg = DebugObject.HeadMsg;
    if (HeadMsg)
    {
        PLIST_MSG takeMsg = HeadMsg->Flink;

        if (takeMsg != HeadMsg)
        {
            TargetProcessCR3(VmGetCurrentProcess());

            // if (!MmIsAddressValid((PVOID)GuestRegs->rdx))
            //     __invlpg((PVOID)GuestRegs->rdx);

            std_memcpy(pMsg, &takeMsg->msg, sizeof(DBGMSG));

            HeadMsg->Flink = takeMsg->Flink;
            HeadMsg->Flink->Blink = takeMsg->Blink;
            gvt->Os.Api.ExFreePool(takeMsg);

            InterlockedCmpExchange64(&g_lock_msg, 0, 1);
            return TRUE;
        }
    }
    InterlockedCmpExchange64(&g_lock_msg, 0, 1);
    return FALSE;
}

uint64 VmcallGetMsg(PGUESTREG GuestRegs)
{
    while (InterlockedCmpExchange64(&g_lock_msg, 1, 0))
        ;
    PLIST_MSG HeadMsg = DebugObject.HeadMsg;
    if (HeadMsg)
    {
        PLIST_MSG takeMsg = HeadMsg->Flink;

        if (takeMsg != HeadMsg)
        {
            TargetProcessCR3(VmGetCurrentProcess());

            // if (!MmIsAddressValid((PVOID)GuestRegs->rdx))
            //     __invlpg((PVOID)GuestRegs->rdx);

            std_memcpy((void *)GuestRegs->rcx, &takeMsg->msg, sizeof(DBGMSG));

            HeadMsg->Flink = takeMsg->Flink;
            HeadMsg->Flink->Blink = takeMsg->Blink;
            gvt->Os.Api.ExFreePool(takeMsg);

            InterlockedCmpExchange64(&g_lock_msg, 0, 1);
            return TRUE;
        }
    }
    InterlockedCmpExchange64(&g_lock_msg, 0, 1);
    return FALSE;
}

// 创建消息并加入链表
uint64 InsertMsg(uint64 type, void *eProcess, void *eThread, wchar *buffer)
{
    PLIST_MSG HeadMsg = DebugObject.HeadMsg;
    if (HeadMsg)
    {
        LIST_MSG *pMsg = gvt->Os.Api.ExAllocatePool2(POOL_FLAG_NON_PAGED, sizeof(LIST_MSG), 0x4342344);
        if (pMsg)
        {
            pMsg->msg.type = type;
            pMsg->msg.Thread = eThread;
            pMsg->msg.Process = eProcess;
            wstrcpy(pMsg->msg.buffer, buffer, wstrlen(buffer));
            pMsg->msg.buffer[wstrlen(buffer)] = L'\0';

            while (InterlockedCmpExchange64(&g_lock_msg, 1, 0))
                ;
            pMsg->Blink = HeadMsg->Blink;
            pMsg->Flink = HeadMsg;
            HeadMsg->Blink->Flink = pMsg;
            HeadMsg->Blink = pMsg;
            InterlockedCmpExchange64(&g_lock_msg, 0, 1);

            return TRUE;
        }
    }
    else
    {
        CreateMsg(eProcess, eThread);
    }

    return FALSE;
}

// 清空消息队列
uint64 DeleteMsg()
{
    while (InterlockedCmpExchange64(&g_lock_msg, 1, 0))
        ;
    PLIST_MSG HeadMsg = DebugObject.HeadMsg;
    if (HeadMsg)
    {
        LIST_MSG *IsRead = HeadMsg->Flink;
        while (IsRead != HeadMsg)
        {
            HeadMsg->Flink = IsRead->Flink;
            HeadMsg->Flink->Blink = IsRead->Blink;
            gvt->Os.Api.ExFreePool(IsRead);
            IsRead = HeadMsg->Flink;
        }
        gvt->Os.Api.ExFreePool(HeadMsg);
    }
    DebugObject.HeadMsg = 0;
    InterlockedCmpExchange64(&g_lock_msg, 0, 1);
    return TRUE;
}

uint64 CreateMsg(void *eProcess, void *eThread)
{
    PLIST_MSG HeadMsg = DebugObject.HeadMsg;
    if (HeadMsg == 0)
    {
        HeadMsg = gvt->Os.Api.ExAllocatePool2(POOL_FLAG_NON_PAGED, sizeof(LIST_MSG), 0x4342344);
        if (HeadMsg == 0)
            return FALSE;

        HeadMsg->Blink = HeadMsg->Flink = HeadMsg;
        DebugObject.HeadMsg = HeadMsg;

        InsertMsg(1, eProcess, eThread, L"开启消息处理");
        return TRUE;
    }
    return FALSE;
}

uint64 IsEnableDebug(uint64 CallNumber)
{
    if (gvt->DebugON)
    {
        if (IsMonitorProcess(VmGetCurrentProcess()))
            return TRUE;
        if (CallNumber == NR_NtCreateUserProcess)
            return TRUE;
    }

    return FALSE;
}

PLIST_MONITOR IsMonitorProcess(void *EProcess)
{
    PLIST_MONITOR monitor = DebugObject.MonitorProcess;
    while (monitor)
    {
        if (monitor->Process == EProcess)
            return monitor;
        monitor = monitor->Next;
    }
    return FALSE;
}

PLIST_MONITOR IsDebugProcess(wchar *ProcessName)
{
    PLIST_MONITOR monitor = DebugObject.MonitorProcess;
    
    while (monitor)
    {
        if (wstristr(ProcessName, monitor->name))
            return monitor;
        monitor = monitor->Next;
    }
    return FALSE;
}