#pragma once
#include "msr.h"
#include "ssdt.h"
#include "type.h"
#include "wintype.h"

#ifdef DEBUG
#include "intel.h"
#define DebugBreak int3p
#else
#define DebugBreak
#endif

#define CPUID_80000001_EDX_SUPPORT_RDTSCP (1 << 27)
#define CPUID_1_ECX_SUPPORT_XSAVE (1 << 26)
#define CPUID_7_EBX_SUPPORT_INVPCID (1 << 10)
#define CPUID_1_ECX_SUPPORT_VMX (1 << 5)
#define CPUID_1_ECX_SUPPORT_SMX (1 << 6)
#define SUPPORT_U_CET (1 << 11)
#define SUPPORT_S_CET (1 << 12)
#define CPUID_1_ECX_SUPPORT_X2APIC (1 << 21)

#define CPUID_D_EAX_SUPPORT_XSAVE (1 << 3)

#define MSR_1B_ENABLE_X2APIC (3 << 10)
#define MSR_1B_ENABLE_XAPIC (1 << 11)

#define CR4_VMXE (1 << 13)

#define PAGE_SIZE 0x1000
#define STACK_SIZE (8 * PAGE_SIZE)

#define TAG_EPT_HOOK 0x80010010
#define TAG_NEW_PAGE 0x80011010
#define TAG_HOOK_LIST 0x80012010
#define TAG_VMX_VM 0x80112010

#pragma pack(1)

typedef union _EPTP
{
    uint64 value;
    struct
    {
        uint64 MemoryType : 3; // bit 2:0 (0 = Uncacheable (UC) - 6 = Write - back(WB))
        uint64 PageWalk : 3;   // bit 5:3 (This value is 1 less than the EPT page-walk length)
        uint64 Dirty : 1;      // bit 6  (Setting this control to 1 enables accessed and dirty flags for EPT)
        uint64 Reserved1 : 5;  // bit 11:7
        uint64 PML4E : 36;
        uint64 Reserved2 : 16;
    };
} EPTP, *PEPTP;

typedef struct _SMEMORY
{
    void *phy;
    void *vir;
} SMEMORY, *PSMEMORY;

typedef union _SLONG64
{
    struct
    {
        unsigned long LowPart;
        unsigned long HighPart;
    };
    unsigned long long QuadPart;
} SLONG64,*PSLONG64;

typedef struct _OS
{
    struct
    {
        void (*MmFreeContiguousMemorySpecifyCache)(PVOID BaseAddress, SIZE_T NumberOfBytes, MEMORY_CACHING_TYPE CacheType);
        void *(*MmAllocateContiguousMemorySpecifyCache)(SIZE_T NumberOfBytes, uint64 LowestAcceptableAddress, uint64 HighestAcceptableAddress, uint64 BoundaryAddressMultiple, MEMORY_CACHING_TYPE CacheType);
        int32 (*MmLoadSystemImage)(IN PUNICODE_STRING ImageFileName, IN PUNICODE_STRING NamePrefix, IN PUNICODE_STRING LoadedBaseName, IN uint64 LoadFlags, OUT PVOID *ImageHandle, OUT PVOID *ImageBaseAddress);
        void *(*MmMapIoSpace)(void *PhysicalAddress, SIZE_T NumberOfBytes, MEMORY_CACHING_TYPE CacheType);
        void (*MmUnmapIoSpace)(PVOID BaseAddress, SIZE_T NumberOfBytes);
        void *(*ExAllocatePool2)(uint64 Flags, uint64 NumberOfBytes, uint32 Tag);
        void (*ExFreePool)(PVOID addr);
        void *(*MmAllocateContiguousMemory)(SIZE_T NumberOfBytes, uint64 HighestAcceptableAddress);
        void (*MmFreeContiguousMemory)(PVOID BaseAddress);
        void *(*MmGetPhysicalAddress)(PVOID BaseAddress);
        void *(*MmGetVirtualForPhysical)(PVOID BaseAddress);
        uint64 (*KeIpiGenericCall)(void *func, void *Context);
        void (*RtlInitUnicodeString)(PUNICODE_STRING DestinationString, wchar *SourceString);
        int32 (*PsLookupProcessByProcessId)(HANDLE ProcessId, void *Process);
        void (*ObDereferenceObjectDeferDelete)(PVOID Object);
        int32 (*ZwCreateFile)(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions, PVOID EaBuffer, ULONG EaLength);
        int32 (*ZwReadFile)(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID Buffer, ULONG Length, PLARGE_INTEGER ByteOffset, PULONG Key);
        int32 (*ZwClose)(HANDLE Handle);
        int32 (*ZwQueryInformationFile)(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass);
        int32 (*ZwCreateThreadEx)(HANDLE ThreadHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PHANDLE ProcessHandle, LPTHREAD_START_ROUTINE StartRoutine, PVOID StartContext, ULONG64 CreateThreadFlags, ULONG64 ZeroBits, ULONG64 StackSize, ULONG64 MaximumStackSize, PVOID AttributeList);
        int32 (*ZwOpenProcess)(PHANDLE ProcessHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PCLIENT_ID ClientId);
        int32 (*ZwAllocateVirtualMemory)(HANDLE ProcessHandle, PVOID *BaseAddress, ULONG_PTR ZeroBits, PSIZE_T RegionSize, ULONG AllocationType, ULONG Protect);
        int32 (*ZwWriteVirtualMemory)(HANDLE ProcessHandle, PVOID BaseAddress, PVOID Buffer, ULONG NumberOfBytesToWrite, PULONG NumberOfBytesWritten);
        uint8 (*MmIsAddressValid)(PVOID VirtualAddress);
        int32 (*KeQueryActiveProcessorCountEx)(USHORT GroupNumber);
    } Api;

    struct
    {
        struct _LOADER_PARAMETER_BLOCK *pOslLoaderBlock;
        struct _LDR_DATA_TABLE_ENTRY *kernelModule;
        struct _LDR_DATA_TABLE_ENTRY* PsLoadedModuleList;
        uint32 *g_CiOptions;
        uint64 kernelCR3;
    } Data;

} OS, *POS;

typedef struct _VM
{
    SMEMORY VmxON;     // 1页
    SMEMORY VmxCS;     // 1页
    SMEMORY MsrBitMap; // 2页
    uint64 Stack;      // 8页
    uint32 ExecptBitMap;

    struct
    {
        uint8 Hooked;
        uint64 old;
        uint64 new;
    } syscall;
    struct
    {
        uint8 Hooked;
        uint64 old;
        uint64 new;
    } sysenter;

} VM, *PVM;

typedef struct _VT
{
    OS Os;
    SMEMORY MemBaseVM;
    SMEMORY MemBaseEPT;
    EPTP Eptp;
    uint64 TotalMemGB;
    uint64 CpuCount;
    uint64 EnableEPT;
    uint64 DebugON;
    uint64 HideVMX;
    PLDR_DATA_TABLE_ENTRY thisDrv;
    PVM vm;
} VT, *PVT;

typedef struct _GUESTREG
{
    uint64 rax;
    uint64 rcx;
    uint64 rdx;
    uint64 rbx;
    uint64 rsp; // 对齐用,无效数据
    uint64 rbp;
    uint64 rsi;
    uint64 rdi;
    uint64 r8;
    uint64 r9;
    uint64 r10;
    uint64 r11;
    uint64 r12;
    uint64 r13;
    uint64 r14;
    uint64 r15;
    uint64 rflags;

    PVOID EProcess;
    PVOID EThread;
    EXIT_REASON_FIELDS ExitReason;
    uint64 GuestRip;
    uint64 GuestRsp;
    uint64 GuestFlag;
    uint64 CpuIndex;
    uint64 InstrLen;
} GUESTREG, *PGUESTREG;

#pragma pack()

extern PVT gvt;

extern uint64 OldSystemCall64;
extern uint64 NewSystemCall64;
extern uint64 ServiceTableCount;
extern PSERVICE_TABLE ssdt;

uint64 IsSupportVT();
uint64 SetControls(uint64 *value, uint64 msr);

// uint64 IsEnableSMT(PVT vt);
// uint64 IsEnablex2APIC(PVT vt);
// char *GetCpuName(PVT vt);
// char *GetCpuSign(PVT vt);
// uint64 GetApicMsr(PVT vt);

uint64 Efi_StartVT(PVT ospvt);
uint64 Driver_StartVT(void *NtosKernelBase);
PLDR_DATA_TABLE_ENTRY HideDriver(PLDR_DATA_TABLE_ENTRY ListEntry,wchar*sysname);
void* UnHideDriver(PLDR_DATA_TABLE_ENTRY ListEntry, PLDR_DATA_TABLE_ENTRY insert);