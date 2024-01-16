#include "type.h"
#include "intel.h"
#include "vmx.h"
#include "std.h"
#include "pe64.h"
#include "ssdt.h"

uint8 ZwFunctionBinaryCode[] = {"48 8b c4 fa 48 83 ec ?? 50 9c 6a ?? 48 8d 05 ?? ?? ?? ?? 50 b8 00 00 00 00 e9 ?? ?? ?? ?? c3 90"};

PVOID FindZwFuncAddr(void *NtosKernelBase, uint32 number)
{
	char str[2];

	std_itoa((number >> 0) & 0xFF, str, 16);
	std_memcpy(&ZwFunctionBinaryCode[63], str, cstrlen(str));

	std_itoa((number >> 8) & 0xFF, str, 16);
	std_memcpy(&ZwFunctionBinaryCode[66], str, cstrlen(str));

	std_itoa((number >> 16) & 0xFF, str, 16);
	std_memcpy(&ZwFunctionBinaryCode[69], str, cstrlen(str));

	std_itoa((number >> 24) & 0xFF, str, 16);
	std_memcpy(&ZwFunctionBinaryCode[72], str, cstrlen(str));

	PVOID addr = std_FindCode(NtosKernelBase, GetSizeOfImage(NtosKernelBase), ZwFunctionBinaryCode);
	// 直接返回PVOID 有问题

	return addr;
}

uint64 InitOsApi(PVT ospvt, void *NtosKernelBase)
{

	ospvt->Os.Api.MmAllocateContiguousMemorySpecifyCache = GetExportFunctionByName(NtosKernelBase, "MmAllocateContiguousMemorySpecifyCache");
	ospvt->Os.Api.MmFreeContiguousMemorySpecifyCache = GetExportFunctionByName(NtosKernelBase, "MmFreeContiguousMemorySpecifyCache");
	ospvt->Os.Api.MmLoadSystemImage = GetExportFunctionByName(NtosKernelBase, "MmLoadSystemImage");
	ospvt->Os.Api.MmMapIoSpace = GetExportFunctionByName(NtosKernelBase, "MmMapIoSpace");
	ospvt->Os.Api.MmUnmapIoSpace = GetExportFunctionByName(NtosKernelBase, "MmUnmapIoSpace");
	ospvt->Os.Api.ExAllocatePool2 = GetExportFunctionByName(NtosKernelBase, "ExAllocatePool2");
	ospvt->Os.Api.ExFreePool = GetExportFunctionByName(NtosKernelBase, "ExFreePool");
	ospvt->Os.Api.MmGetPhysicalAddress = GetExportFunctionByName(NtosKernelBase, "MmGetPhysicalAddress");
	ospvt->Os.Api.MmGetVirtualForPhysical = GetExportFunctionByName(NtosKernelBase, "MmGetVirtualForPhysical");
	ospvt->Os.Api.MmIsAddressValid = GetExportFunctionByName(NtosKernelBase, "MmIsAddressValid");
	ospvt->Os.Api.KeIpiGenericCall = GetExportFunctionByName(NtosKernelBase, "KeIpiGenericCall");
	ospvt->Os.Api.RtlInitUnicodeString = GetExportFunctionByName(NtosKernelBase, "RtlInitUnicodeString");
	ospvt->Os.Api.PsLookupProcessByProcessId = GetExportFunctionByName(NtosKernelBase, "PsLookupProcessByProcessId");
	ospvt->Os.Api.ObDereferenceObjectDeferDelete = GetExportFunctionByName(NtosKernelBase, "ObDereferenceObjectDeferDelete");
	ospvt->Os.Api.ZwCreateFile = GetExportFunctionByName(NtosKernelBase, "ZwCreateFile");
	ospvt->Os.Api.ZwReadFile = GetExportFunctionByName(NtosKernelBase, "ZwReadFile");
	ospvt->Os.Api.ZwClose = GetExportFunctionByName(NtosKernelBase, "ZwClose");
	ospvt->Os.Api.ZwQueryInformationFile = GetExportFunctionByName(NtosKernelBase, "ZwQueryInformationFile");
	ospvt->Os.Api.ZwOpenProcess = GetExportFunctionByName(NtosKernelBase, "ZwOpenProcess");
	ospvt->Os.Api.ZwAllocateVirtualMemory = GetExportFunctionByName(NtosKernelBase, "ZwAllocateVirtualMemory");
	ospvt->Os.Api.MmAllocateContiguousMemory = GetExportFunctionByName(NtosKernelBase, "MmAllocateContiguousMemory");
	ospvt->Os.Api.MmFreeContiguousMemory = GetExportFunctionByName(NtosKernelBase, "MmFreeContiguousMemory");

	ospvt->Os.Api.ZwCreateThreadEx = FindZwFuncAddr(NtosKernelBase, NR_NtCreateThreadEx);
	ospvt->Os.Api.ZwWriteVirtualMemory = FindZwFuncAddr(NtosKernelBase, NR_NtWriteVirtualMemory);

	return TRUE;
}
