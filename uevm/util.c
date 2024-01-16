#include "util.h"

extern EFI_SYSTEM_TABLE *gST;
extern EFI_HANDLE *gIH;
extern UINTN OsMode;

typedef UINTN (*BLPARCHSWITCHCONTEXT)(int target);
extern BLPARCHSWITCHCONTEXT BlpArchSwitchContext;

EFI_STATUS efi_Print(wchar *format, ...)
{
    if (OsMode == ApplicationContext)
    {
        if (BlpArchSwitchContext)
            BlpArchSwitchContext(FirmwareContext);
    }
    wchar buffer[0x200];
    std_memset(buffer, 0x200, 0);
    void *args = (void *)((UINTN)&format + 8);
    wsprint(buffer, format, args);

    gST->ConOut->OutputString(gST->ConOut, buffer);
    if (OsMode == ApplicationContext)
    {
        if (BlpArchSwitchContext)
            BlpArchSwitchContext(ApplicationContext);
    }
}

EFI_STATUS efi_WaiteForAnyKey(wchar *str)
{
    EFI_STATUS status;
    EFI_INPUT_KEY key;
    UINTN WaitIndex;
    efi_Print(L"%S\r\n", str);
    while (1)
    {
        gST->BootServices->WaitForEvent(1, &gST->ConIn->WaitForKey, &WaitIndex);
        gST->ConIn->ReadKeyStroke(gST->ConIn, &key);
        break;
    }

    return EFI_SUCCESS;
}
/// @brief 获取文件的设备全路径
/// @param FileDevicePath 返回文件的设备全路径
/// @param IoDevicePath
/// @param FileName
/// @return
EFI_STATUS efi_GetFileDevicePath(OUT EFI_DEVICE_PATH_PROTOCOL **FileDevicePath, IN EFI_DEVICE_PATH_PROTOCOL *IoDevicePath, wchar *FileName)
{
    EFI_STATUS status;

    EFI_DEVICE_PATH_PROTOCOL *IoDeviceNode;

    EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL *pDevicePathFromText;
    EFI_GUID DEV_PATH_FROM_TEXT_GUID = EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL_GUID;

    EFI_DEVICE_PATH_TO_TEXT_PROTOCOL *pDevicePathToText;
    EFI_GUID DEV_PATH_TO_TEXT_GUID = EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID;

    EFI_DEVICE_PATH_UTILITIES_PROTOCOL *pDevPathUtil;
    EFI_GUID DEV_PATH_UTIL_GUID = EFI_DEVICE_PATH_UTILITIES_PROTOCOL_GUID;

    status = gST->BootServices->LocateProtocol(&DEV_PATH_FROM_TEXT_GUID, NULL, (void **)&pDevicePathFromText);
    EFI_DEBUG(status);

    status = gST->BootServices->LocateProtocol(&DEV_PATH_TO_TEXT_GUID, NULL, (void **)&pDevicePathToText);
    EFI_DEBUG(status);

    status = gST->BootServices->LocateProtocol(&DEV_PATH_UTIL_GUID, NULL, (void **)&pDevPathUtil);
    EFI_DEBUG(status);

    IoDeviceNode = pDevicePathFromText->ConvertTextToDeviceNode(FileName);
    *FileDevicePath = pDevPathUtil->AppendDeviceNode(IoDevicePath, IoDeviceNode);

    EFI_PRINT(L"%S\r\n", pDevicePathToText->ConvertDevicePathToText(*FileDevicePath, FALSE, FALSE));

    return EFI_SUCCESS;
}
/// @brief 打开文件
/// @param FileHandle 返回文件名柄
/// @param IoDevicePath 返回文件设备路径
/// @param FileName 全路径文件名 例L"\\EFI\\Boot\\File.efi"
/// @param mode 以读写方式打开
/// @return
EFI_STATUS efi_OpenFile(OUT EFI_FILE_PROTOCOL **FileHandle, OUT EFI_DEVICE_PATH_PROTOCOL **IoDevicePath, IN wchar *FileName, IN UINTN mode)
{
    EFI_STATUS status;

    UINTN HandleCount;
    EFI_HANDLE *Handles;
    EFI_GUID S_FILE_GUID = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    status = gST->BootServices->LocateHandleBuffer(ByProtocol, &S_FILE_GUID, NULL, &HandleCount, &Handles);
    EFI_DEBUG(status);

    for (UINTN i = 0; i < HandleCount; i++)
    {
        EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *IoDevice;
        EFI_FILE_PROTOCOL *Root;

        status = gST->BootServices->OpenProtocol(
            Handles[i],
            &S_FILE_GUID,
            (void **)&IoDevice,
            gIH,
            NULL,
            EFI_OPEN_PROTOCOL_GET_PROTOCOL);

        EFI_DEBUG(status);

        status = IoDevice->OpenVolume(IoDevice, &Root);
        EFI_DEBUG(status);

        status = Root->Open(Root, FileHandle, FileName, mode, 0);
        if (status == EFI_SUCCESS)
        {
            gST->ConOut->SetAttribute(gST->ConOut, EFI_GREEN);
            EFI_PRINT(L"Found!%S\r\n", FileName);

            EFI_GUID S_PATH_GUID = EFI_DEVICE_PATH_PROTOCOL_GUID;
            status = gST->BootServices->OpenProtocol(
                Handles[i],
                &S_PATH_GUID,
                (void **)IoDevicePath,
                gIH,
                NULL,
                EFI_OPEN_PROTOCOL_GET_PROTOCOL);

            EFI_DEBUG(status);

            Root->Close(Root);
            return status;
        }
        else
        {
            Root->Close(Root);
        }
    }
    return status;
}

EFI_STATUS efi_WriteToFile(IN EFI_FILE_HANDLE FileHandle, char *buffer)
{
    EFI_STATUS status;

    FileHandle->SetPosition(FileHandle, -1);
    UINTN DataSize = cstrlen(buffer) * sizeof(char);
    status = FileHandle->Write(FileHandle, &DataSize, buffer);

    if (EFI_ERROR(status))
        return status;

    return status;
}

EFI_STATUS efi_ReadToFile(IN EFI_FILE_HANDLE FileHandle, wchar *buffer)
{
    EFI_STATUS status = EFI_SUCCESS;
    EFI_GUID FILE_INFO_GUID = EFI_FILE_INFO_ID;

    EFI_FILE_INFO *FileInfo;
    UINTN FileInfoSize = 0;

    status = FileHandle->GetInfo(FileHandle, &FILE_INFO_GUID, &FileInfoSize, NULL);
    if (status == EFI_BUFFER_TOO_SMALL)
    {
        status = gST->BootServices->AllocatePool(EfiLoaderData, FileInfoSize, (void **)&FileInfo);

        status = FileHandle->GetInfo(FileHandle, &FILE_INFO_GUID, &FileInfoSize, FileInfo);

        UINTN size = FileInfo->FileSize;
        status = gST->BootServices->AllocatePool(EfiLoaderData, size, (void **)&buffer);

        status = FileHandle->Read(FileHandle, &size, buffer);

        EFI_PRINT(L"efi_ReadFile:\r\nsize->%x32\r\nbuffer->%S\r\n", FileInfoSize, buffer);
    }

    return status;
}

/***************************
 * @brief 读取文件数据
 * @param FileName   文件名
 * @param buffer     保存数据的内存地址
 * @param
 * @param
 * @return EFI_STATUS
 ***************************/
EFI_STATUS efi_ReadFile(IN wchar *FileName, OUT wchar *buffer)
{
    EFI_STATUS status;
    EFI_FILE_PROTOCOL *FileHandle;
    EFI_DEVICE_PATH_PROTOCOL *IoDevicePath;
    status = efi_OpenFile(&FileHandle, &IoDevicePath, FileName, EFI_FILE_MODE_READ);

    if (!status)
    {
        efi_ReadToFile(FileHandle, buffer);
    }
    FileHandle->Close(FileHandle);

    return status;
}

/***************************
 * @brief 写入文件数据
 * @param FileName   文件名
 * @param buffer     要写入数据的内存地址
 * @return EFI_STATUS
 ***************************/
EFI_STATUS efi_WriteFile(IN wchar *FileName, IN char *buffer)
{
    EFI_STATUS status;
    EFI_FILE_PROTOCOL *FileHandle;
    EFI_DEVICE_PATH_PROTOCOL *IoDevicePath;
    status = efi_OpenFile(&FileHandle, &IoDevicePath, FileName, EFI_FILE_MODE_WRITE | EFI_FILE_MODE_READ | EFI_FILE_MODE_CREATE);

    if (!status)
    {
        efi_WriteToFile(FileHandle, buffer);
    }
    FileHandle->Close(FileHandle);

    return status;
}

EFI_STATUS efi_StartImage(IN EFI_DEVICE_PATH_PROTOCOL *IoFilePath)
{
    EFI_STATUS status = EFI_SUCCESS;

    EFI_HANDLE ImageHandle;
    EFI_LOADED_IMAGE *LoadImage;
    EFI_GUID LOAD_IMAGE_GUID = EFI_LOADED_IMAGE_PROTOCOL_GUID;

    status = gST->BootServices->LoadImage(FALSE, gIH, IoFilePath, NULL, 0, &ImageHandle);
    EFI_DEBUG(status);

    status = gST->BootServices->HandleProtocol(ImageHandle, &LOAD_IMAGE_GUID, (void **)&LoadImage);
    EFI_DEBUG(status);

    return gST->BootServices->StartImage(ImageHandle, NULL, NULL);
}

EFI_STATUS efi_CallBackStartImage(IN wchar *FileName, CallBack callback)
{
    EFI_PRINT(L"efi_StartImage\r\n");

    if (!callback)
        return RETURN_LOAD_ERROR;

    EFI_STATUS status;
    EFI_FILE_PROTOCOL *FileHandle;
    EFI_DEVICE_PATH_PROTOCOL *IoDevicePath;
    EFI_DEVICE_PATH_PROTOCOL *FileDevicePath;

    status = efi_OpenFile(&FileHandle, &IoDevicePath, FileName, EFI_FILE_MODE_READ);
    EFI_DEBUG(status);

    status = efi_GetFileDevicePath(&FileDevicePath, IoDevicePath, FileName);
    EFI_DEBUG(status);

    status = callback(FileDevicePath);
    EFI_DEBUG(status);

    FileHandle->Close(FileHandle);

    return status;
}
