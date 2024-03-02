#include <windows.h>
#include "ssdt.h"
#include "pe64.h"
#include "intel.h"
#include "std.h"

void *GetNtHeader(void *base)
{
    PIMAGE_DOS_HEADER pDos = base;
    if (pDos->e_magic != IMAGE_DOS_SIGNATURE)
        return NULL;

    PIMAGE_NT_HEADERS64 pNt = (PIMAGE_NT_HEADERS64)((uint64)pDos + pDos->e_lfanew);
    if (pNt->Signature != IMAGE_NT_SIGNATURE)
        return NULL;

    return pNt;
}

void *GetSection(void *base, char *name)
{
    PIMAGE_DOS_HEADER pDos = base;
    PIMAGE_NT_HEADERS64 pNt = GetNtHeader(pDos);
    PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNt);

    for (uint8 index = 0; index < pNt->FileHeader.NumberOfSections; index++)
    {
        for (uint8 byte = 0; byte < 10; byte++)
        {
            if (std_cstricmp(pSection[index].Name, name) == TRUE)
                return pSection + index;
        }
    }
    return NULL;
}

uint64 GetSectionVirtualAddress(void *base, char *name)
{
    PIMAGE_DOS_HEADER pDos = base;
    PIMAGE_NT_HEADERS64 pNt = GetNtHeader(pDos);
    PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNt);

    for (uint8 index = 0; index < pNt->FileHeader.NumberOfSections; index++)
    {
        for (uint8 byte = 0; byte < 10; byte++)
        {
            if (std_cstricmp(pSection[index].Name, name) == TRUE)
                return pSection[index].VirtualAddress;
        }
    }
    return 0;
}
uint64 GetSectionVirtualSize(void *base, char *name)
{
    PIMAGE_DOS_HEADER pDos = base;
    PIMAGE_NT_HEADERS64 pNt = GetNtHeader(pDos);
    PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNt);

    for (uint8 index = 0; index < pNt->FileHeader.NumberOfSections; index++)
    {
        for (uint8 byte = 0; byte < 10; byte++)
        {
            if (std_cstricmp(pSection[index].Name, name) == TRUE)
                return pSection[index].Misc.VirtualSize;
        }
    }
    return 0;
}

void *GetDirectory(void *base, char index)
{
    PIMAGE_DOS_HEADER pDos = base;
    PIMAGE_NT_HEADERS64 pNt = GetNtHeader(pDos);
    if (pNt == NULL)
        return NULL;

    return &pNt->OptionalHeader.DataDirectory[index];
}

/// @brief 取内存中进程的导入表所指定模块的指定函数地址
/// @param base 基址
/// @param ModuleName 模块名
/// @param FunctionName 函数名
/// @return 如果模块名为 NULL ,遍历所有模块.\
/// @return 成功返回该函数地址.\
/// @return 失败返回 NULL.
void *GetImportFunctionByName(void *base, char *ModuleName, char *FunctionName)
{
    PIMAGE_DOS_HEADER pDos = base;
    PIMAGE_NT_HEADERS64 pNt = GetNtHeader(pDos);
    if (pNt == NULL)
        return 0;

    PIMAGE_DATA_DIRECTORY pDirectory = GetDirectory(base, IMAGE_DIRECTORY_ENTRY_IMPORT);
    if (pDirectory->VirtualAddress == 0)
        return 0;

    PIMAGE_IMPORT_DESCRIPTOR pImport = (PIMAGE_IMPORT_DESCRIPTOR)((uint64)base + pDirectory->VirtualAddress);

    for (uint32 ImportCount = 0; pImport[ImportCount].Name != 0; ImportCount++)
    {
        if (ModuleName)
        {
            if (!std_cstricmp((char *)((uint64)base + pImport[ImportCount].Name), ModuleName))
                continue;
        }
        PIMAGE_THUNK_DATA64 ThunkOriginal = (PIMAGE_THUNK_DATA64)((uint64)base + pImport[ImportCount].OriginalFirstThunk);
        PIMAGE_THUNK_DATA64 ThunkFunction = (PIMAGE_THUNK_DATA64)((uint64)base + pImport[ImportCount].FirstThunk);
        uint32 index = 0;
        while (ThunkOriginal[index].u1.AddressOfData != 0)
        {
            if (!(ThunkOriginal[index].u1.Ordinal & IMAGE_ORDINAL_FLAG64))
            {
                PIMAGE_IMPORT_BY_NAME importName = (PIMAGE_IMPORT_BY_NAME)((uint64)base + ThunkOriginal[index].u1.AddressOfData);
                if (std_cstricmp(importName->Name, FunctionName))
                    return (void *)(ThunkFunction[index].u1.Function);
            }
            index++;
        }
    }
    return 0;
}

/// @brief 取内存中进程的导出表函数地址
/// @param base 基址
/// @param FunctionName 函数名
/// @return 成功返回该函数地址.\
/// @return 失败返回 NULL.
void *GetExportFunctionByName(void *base, char *FunctionName)
{
    PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)base;
    PIMAGE_NT_HEADERS64 pNt = GetNtHeader(pDos);
    if (pNt == NULL)
        return 0;

    PIMAGE_DATA_DIRECTORY pDirectory = GetDirectory(base, IMAGE_DIRECTORY_ENTRY_EXPORT);
    if (pDirectory->VirtualAddress == 0)
        return 0;

    PIMAGE_EXPORT_DIRECTORY pExport = (PIMAGE_EXPORT_DIRECTORY)((uint64)base + pDirectory->VirtualAddress);

    if (!pExport)
        return 0;

    uint32 *offsetFunc = (uint32 *)((uint64)base + pExport->AddressOfFunctions);
    uint32 *offsetName = (uint32 *)((uint64)base + pExport->AddressOfNames);
    uint16 *offsetOrd = (uint16 *)((uint64)base + pExport->AddressOfNameOrdinals);

    for (uint32 index = 0; index < pExport->NumberOfNames; index++)
    {
        char *name = (char *)base + offsetName[index]; // 取名称地址

        if (std_cstricmp(name, FunctionName))
        {
            return (void *)((uint64)base + offsetFunc[offsetOrd[index]]); // 取函数地址
        }
    }

    return 0;
}

uint64 GetExportVA(void *ModuleBase)
{
    uint64 base = (uint64)ModuleBase;

    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)base;

    PIMAGE_NT_HEADERS64 pNtHeader = (PIMAGE_NT_HEADERS64)(base + pDosHeader->e_lfanew);

    if (!pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size)
    {
        return FALSE;
    }

    if (!pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress)
    {
        return FALSE;
    }

    return pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
}

void *ImageRvaToFoa(uint64 ModuleBase, uint64 Rva)
{
    uint64 base = ModuleBase;

    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)base;

    PIMAGE_NT_HEADERS64 pNtHeader = (PIMAGE_NT_HEADERS64)(base + pDosHeader->e_lfanew);

    PIMAGE_SECTION_HEADER pSection = (PIMAGE_SECTION_HEADER)((uint64)pNtHeader + pNtHeader->FileHeader.SizeOfOptionalHeader + 0x18);

    for (size_t i = 0; i < pNtHeader->FileHeader.NumberOfSections; i++)
    {
        if (pSection[i].VirtualAddress > Rva)
        {
            return (void *)(base + (pSection[i - 1].PointerToRawData) + (Rva - pSection[i - 1].VirtualAddress));
        }
    }
    return NULL;
}

uint64 GetSizeOfImage(void *ModuleBase)
{
    PIMAGE_NT_HEADERS64 pNt = GetNtHeader(ModuleBase);
    return pNt->OptionalHeader.SizeOfImage;
}

uint64 GetServiceTable(PSERVICE_TABLE psdt, void *ModuleBase)
{
    uint64 base = (uint64)ModuleBase;
    uint64 ExportVa = GetExportVA(ModuleBase);
    PIMAGE_EXPORT_DIRECTORY pExport = ImageRvaToFoa(base, ExportVa);

    if (!pExport)
        return FALSE;

    PULONG offsetFunc = ImageRvaToFoa(base, pExport->AddressOfFunctions);
    PULONG offsetName = ImageRvaToFoa(base, pExport->AddressOfNames);
    PSHORT offsetOrd = ImageRvaToFoa(base, pExport->AddressOfNameOrdinals);

    uint64 count = 0;
    for (int index = 0; index < pExport->NumberOfNames; index++)
    {
        /*方案1, 遍历名称表*/
        char *name = ImageRvaToFoa(base, offsetName[index]);             // 取名称地址
        PULONG addr = ImageRvaToFoa(base, offsetFunc[offsetOrd[index]]); // 取函数地址
        if (*addr == 0xB8D18B4C)                                         // 检测机器码
        {
            if (cstrnicmp(name, "Nt", 2) == 0)
            {
                count++;
                ULONG num = *(addr + 1); // 机器码取编号
                psdt[num].number = num;
                psdt[num].addr = (uint64)addr;
                psdt[num].name = (char *)name;
            }
        }
    }

    return count;
}
