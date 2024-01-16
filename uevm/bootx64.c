#include <Uefi.h>
#include <PiMultiPhase.h>
#include <MpService.h>
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

EFI_SYSTEM_TABLE *gST;
EFI_HANDLE *gIH;

UINTN OsMode = FirmwareContext;

typedef UINTN (*BLPARCHSWITCHCONTEXT)(int target);
BLPARCHSWITCHCONTEXT BlpArchSwitchContext = 0;

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS status;

    gST = SystemTable;
    gIH = ImageHandle;

    gST->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
    gST->ConOut->ClearScreen(gST->ConOut);
    gST->ConOut->SetAttribute(gST->ConOut, EFI_RED);

    efi_WaiteForAnyKey(L"Booting...");

    return efi_CallBackStartImage(L"\\EFI\\BOOT\\Loader.efi", efi_StartImage);
    // return efi_CallBackStartImage(L"\\EFI\\Microsoft\\Boot\\bootmgfw.efi", efi_StartImage);
}

EFI_STATUS EFIAPI UefiUnload(EFI_HANDLE ImageHandle)
{
    return EFI_ABORTED;
}