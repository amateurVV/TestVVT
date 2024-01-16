#include "type.h"
#include "std.h"
#include "pe64.h"
#include "vmx.h"
#include "intel.h"
#include "wintype.h"
#include "file.h"


void *ReadFile(wchar *wFileFullPath)
{
    OBJECT_ATTRIBUTES objectAttributes = {0};
    FILE_STANDARD_INFORMATION fsi = {0};
    IO_STATUS_BLOCK iostatus = {0};
    UNICODE_STRING logFileUnicodeString = {0};
    HANDLE hfile;
    NTSTATUS ntStatus;
    LARGE_INTEGER offset = {0};
    PVOID pBuffer = 0;

    // 初始化UNICODE_STRING字符串
    gvt->Os.Api.RtlInitUnicodeString(&logFileUnicodeString, wFileFullPath);

    // 初始化objectAttributes
    InitializeObjectAttributes(&objectAttributes, &logFileUnicodeString, OBJ_CASE_INSENSITIVE, NULL, NULL);

    ntStatus = gvt->Os.Api.ZwCreateFile(&hfile, GENERIC_READ | SYNCHRONIZE, &objectAttributes, &iostatus, NULL,
                                         FILE_ATTRIBUTE_NORMAL, FILE_SHARE_READ, FILE_OPEN_IF,
                                         FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_ALERT,
                                         NULL, 0);

    if (!NT_SUCCESS(ntStatus))
    {
        DebugBreak("ReadFile ZwCreateFile", ntStatus);
        return FALSE;
    }
    // 读取文件长度
    ntStatus = gvt->Os.Api.ZwQueryInformationFile(hfile, &iostatus, &fsi, sizeof(FILE_STANDARD_INFORMATION), FileStandardInformation);
    if (!NT_SUCCESS(ntStatus))
    {
        DebugBreak("ReadFile ZwQueryInformationFile", ntStatus);
        goto Exit;
    }
    // 为读取的文件分配缓冲区
    pBuffer = gvt->Os.Api.ExAllocatePool2(POOL_FLAG_NON_PAGED, fsi.AllocationSize.QuadPart, 0x523424);
    if (!pBuffer)
    {
        DebugBreak("ReadFile ExAllocatePool2", fsi, pBuffer);
        goto Exit;
    }
    // 读文件
    ntStatus = gvt->Os.Api.ZwReadFile(hfile, NULL, NULL, NULL, &iostatus, pBuffer, fsi.EndOfFile.LowPart, &offset, NULL);
    if (!NT_SUCCESS(ntStatus))
    {
        gvt->Os.Api.ExFreePool(pBuffer);
        pBuffer = NULL;
        DebugBreak("ReadFile ZwReadFile", ntStatus);
        goto Exit;
    }

Exit:
    // 关闭文件句柄
    if (hfile)
        gvt->Os.Api.ZwClose(hfile);

    DebugBreak("ReadFile OK", pBuffer);
    return pBuffer;
}

uint64 InitSystemServiceTable(PSERVICE_TABLE psdt, wchar *file)
{
    PVOID pBuffer = 0;
    uint64 count = 0;
    pBuffer = ReadFile(file);
    if (!pBuffer)
    {
        DebugBreak("InitSystemServiceTable");
        return FALSE;
    }
    count = GetServiceTable(psdt, pBuffer);

    //gvt->Os.Api.ExFreePool(pBuffer);

    return count;
}