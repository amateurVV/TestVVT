#pragma once

#include <Uefi.h>
#include <FileInfo.h>
#include <SimpleFileSystem.h>
#include <DevicePathFromText.h>
#include <DevicePathToText.h>
#include <DevicePathFromText.h>
#include <DevicePathUtilities.h>
#include <LoadedImage.h>

#include "type.h"
#include "std.h"
#include "util.h"

#ifdef DEBUG
#include "intel.h"
#define EFI_PRINT efi_Print
#else
#define EFI_PRINT
#endif

#define EFI_DEBUG(status) \
    if (status)           \
        efi_Print(L"Error Status Code:%x64 , file:%s , line:%d , func:%s\r\n", status, __FILE__, __LINE__, __FUNCTION__);

enum EnvContext
{
    ApplicationContext,
    FirmwareContext
};



EFI_STATUS efi_Print(wchar *format, ...);
EFI_STATUS efi_WaiteForAnyKey(wchar *str);

EFI_STATUS efi_GetFileDevicePath(OUT EFI_DEVICE_PATH_PROTOCOL **FileDevicePath, IN EFI_DEVICE_PATH_PROTOCOL *IoDevicePath, wchar *FileName);
EFI_STATUS efi_OpenFile(OUT EFI_FILE_PROTOCOL **FileHandle, OUT EFI_DEVICE_PATH_PROTOCOL **IoDevicePath, IN wchar *FilePath, IN UINTN mode);
EFI_STATUS efi_WriteToFile(IN EFI_FILE_HANDLE FileHandle, char *buffer);
EFI_STATUS efi_ReadToFile(IN EFI_FILE_HANDLE FileHandle, wchar *buffer);

EFI_STATUS efi_ReadFile(IN wchar *FileName, OUT wchar *buffer);
EFI_STATUS efi_WriteFile(IN wchar *FileName, IN char *buffer);

typedef EFI_STATUS (*CallBack)(EFI_DEVICE_PATH_PROTOCOL *IoFilePath);
EFI_STATUS efi_StartImage(IN EFI_DEVICE_PATH_PROTOCOL *IoFilePath);
EFI_STATUS efi_CallBackStartImage(IN wchar *FileName, CallBack callback);