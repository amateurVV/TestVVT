#pragma once

#ifndef WIN_VS_EVN

#define WIN_VS_EVN

/*
typedef unsigned short USHORT;
typedef short CSHORT;
typedef float FLOAT;
typedef void *HANDLE;
typedef long LONG;
typedef unsigned long ULONG;
typedef long long LONGLONG;
typedef long NTSTATUS;
typedef long ACCESS_MASK;
typedef unsigned long long ULONG64;
typedef long long LONG64;
typedef ACCESS_MASK *PACCESS_MASK;
typedef HANDLE *PHANDLE;
typedef void *PVOID;
typedef ULONG64 ULONG64;
typedef ULONG64 POOL_FLAGS;
typedef const unsigned short *LPCWSTR, *PCWSTR;
typedef unsigned char UCHAR;
typedef unsigned long long ULONG_PTR;
typedef ULONG_PTR *PULONG_PTR;
typedef long long LONG_PTR;
typedef LONG_PTR *PLONG_PTR;
typedef UCHAR *PUCHAR;
typedef unsigned long *PULONG;
typedef long *PLONG; // winnt
typedef char CCHAR;
typedef CCHAR KPROCESSOR_MODE;
typedef UCHAR BOOLEAN;     // winnt
typedef BOOLEAN *PBOOLEAN; // winnt
typedef ULONG_PTR SIZE_T, *PSIZE_T;
typedef LONG_PTR SSIZE_T, *PSSIZE_T;
typedef ULONG64 PHYSICAL_ADDRESS, *PPHYSICAL_ADDRESS;

#define PROCESS_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0xFFFF)
#define CONTAINING_RECORD(address, type, field) ((type *)((char *)(address) - (unsigned long long)(&((type *)0)->field)))

#ifndef CONST
#define CONST const
#endif

#define IN
#define OUT
#define NTAPI __stdcall
#define WINAPI __stdcall

#define NtCurrentProcess() ((HANDLE)(LONG_PTR)-1)
#define ZwCurrentProcess() NtCurrentProcess()
#define NtCurrentThread() ((HANDLE)(LONG_PTR)-2)
#define ZwCurrentThread() NtCurrentThread()
#define NtCurrentSession() ((HANDLE)(LONG_PTR)-3)
#define ZwCurrentSession() NtCurrentSession()

#define DELETE (0x00010000L)
#define READ_CONTROL (0x00020000L)
#define WRITE_DAC (0x00040000L)
#define WRITE_OWNER (0x00080000L)
#define SYNCHRONIZE (0x00100000L)

#define STANDARD_RIGHTS_REQUIRED (0x000F0000L)

#define STANDARD_RIGHTS_READ (READ_CONTROL)
#define STANDARD_RIGHTS_WRITE (READ_CONTROL)
#define STANDARD_RIGHTS_EXECUTE (READ_CONTROL)

#define STANDARD_RIGHTS_ALL (0x001F0000L)

#define SPECIFIC_RIGHTS_ALL (0x0000FFFFL)

//
// AccessSystemAcl access type
//

#define ACCESS_SYSTEM_SECURITY (0x01000000L)

//
// MaximumAllowed access type
//

#define MAXIMUM_ALLOWED (0x02000000L)
//
//  These are the generic rights.
//
#define GENERIC_READ (0x80000000L)
#define GENERIC_WRITE (0x40000000L)
#define GENERIC_EXECUTE (0x20000000L)
#define GENERIC_ALL (0x10000000L)

#define FILE_SHARE_READ 0x00000001
#define FILE_SHARE_WRITE 0x00000002
#define FILE_SHARE_DELETE 0x00000004
#define FILE_SHARE_VALID_FLAGS 0x00000007

//
// Define the file attributes values
//
// Note:  0x00000008 is reserved for use for the old DOS VOLID (volume ID)
//        and is therefore not considered valid in NT.
//
// Note:  Note also that the order of these flags is set to allow both the
//        FAT and the Pinball File Systems to directly set the attributes
//        flags in attributes words without having to pick each flag out
//        individually.  The order of these flags should not be changed!
//

#define FILE_ATTRIBUTE_READONLY 0x00000001
#define FILE_ATTRIBUTE_HIDDEN 0x00000002
#define FILE_ATTRIBUTE_SYSTEM 0x00000004
// OLD DOS VOLID                             0x00000008

#define FILE_ATTRIBUTE_DIRECTORY 0x00000010
#define FILE_ATTRIBUTE_ARCHIVE 0x00000020
#define FILE_ATTRIBUTE_DEVICE 0x00000040
#define FILE_ATTRIBUTE_NORMAL 0x00000080

#define FILE_ATTRIBUTE_TEMPORARY 0x00000100
#define FILE_ATTRIBUTE_SPARSE_FILE 0x00000200
#define FILE_ATTRIBUTE_REPARSE_POINT 0x00000400
#define FILE_ATTRIBUTE_COMPRESSED 0x00000800

#define FILE_ATTRIBUTE_OFFLINE 0x00001000
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED 0x00002000
#define FILE_ATTRIBUTE_ENCRYPTED 0x00004000

//
// Define the create disposition values
//

#define FILE_SUPERSEDE 0x00000000
#define FILE_OPEN 0x00000001
#define FILE_CREATE 0x00000002
#define FILE_OPEN_IF 0x00000003
#define FILE_OVERWRITE 0x00000004
#define FILE_OVERWRITE_IF 0x00000005
#define FILE_MAXIMUM_DISPOSITION 0x00000005

//
// Define the create/open option flags
//

#define FILE_DIRECTORY_FILE 0x00000001
#define FILE_WRITE_THROUGH 0x00000002
#define FILE_SEQUENTIAL_ONLY 0x00000004
#define FILE_NO_INTERMEDIATE_BUFFERING 0x00000008

#define FILE_SYNCHRONOUS_IO_ALERT 0x00000010
#define FILE_SYNCHRONOUS_IO_NONALERT 0x00000020
#define FILE_NON_DIRECTORY_FILE 0x00000040
#define FILE_CREATE_TREE_CONNECTION 0x00000080

#define FILE_COMPLETE_IF_OPLOCKED 0x00000100
#define FILE_NO_EA_KNOWLEDGE 0x00000200
#define FILE_OPEN_REMOTE_INSTANCE 0x00000400
#define FILE_RANDOM_ACCESS 0x00000800

#define FILE_DELETE_ON_CLOSE 0x00001000
#define FILE_OPEN_BY_FILE_ID 0x00002000
#define FILE_OPEN_FOR_BACKUP_INTENT 0x00004000
#define FILE_NO_COMPRESSION 0x00008000

#define POOL_FLAG_REQUIRED_START 0x0000000000000001
#define POOL_FLAG_USE_QUOTA 0x0000000000000001            // Charge quota
#define POOL_FLAG_UNINITIALIZED 0x0000000000000002        // Don't zero-initialize allocation
#define POOL_FLAG_SESSION 0x0000000000000004              // Use session specific pool
#define POOL_FLAG_CACHE_ALIGNED 0x0000000000000008        // Cache aligned allocation
#define POOL_FLAG_RESERVED1 0x0000000000000010            // Reserved for system use
#define POOL_FLAG_RAISE_ON_FAILURE 0x0000000000000020     // Raise exception on failure
#define POOL_FLAG_NON_PAGED 0x0000000000000040            // Non paged pool NX
#define POOL_FLAG_NON_PAGED_EXECUTE 0x0000000000000080    // Non paged pool executable
#define POOL_FLAG_PAGED 0x0000000000000100                // Paged pool
#define POOL_FLAG_RESERVED2 0x0000000000000200            // Reserved for system use
#define POOL_FLAG_RESERVED3 0x0000000000000400            // Reserved for system use
#define POOL_FLAG_LAST_KNOWN_REQUIRED POOL_FLAG_RESERVED3 // Must be set to the last known required entry.
#define POOL_FLAG_REQUIRED_END 0x0000000080000000

#define POOL_FLAG_OPTIONAL_START 0x0000000100000000
#define POOL_FLAG_SPECIAL_POOL 0x0000000100000000 // Make special pool allocation
#define POOL_FLAG_OPTIONAL_END 0x8000000000000000

#define POOL_FLAG_REQUIRED_MASK 0x00000000FFFFFFFF

//
// Bits from the "required" flags that are currently not used.
//

#define POOL_FLAG_UNUSED_REQUIRED_BITS (POOL_FLAG_REQUIRED_MASK & ~(POOL_FLAG_LAST_KNOWN_REQUIRED | (POOL_FLAG_LAST_KNOWN_REQUIRED - 1)))

#define PAGE_NOACCESS 0x01
#define PAGE_READONLY 0x02
#define PAGE_READWRITE 0x04
#define PAGE_WRITECOPY 0x08

#define PAGE_EXECUTE 0x10
#define PAGE_EXECUTE_READ 0x20
#define PAGE_EXECUTE_READWRITE 0x40
#define PAGE_EXECUTE_WRITECOPY 0x80

#define PAGE_GUARD 0x100
#define PAGE_NOCACHE 0x200
#define PAGE_WRITECOMBINE 0x400

#define PAGE_GRAPHICS_NOACCESS 0x0800
#define PAGE_GRAPHICS_READONLY 0x1000
#define PAGE_GRAPHICS_READWRITE 0x2000
#define PAGE_GRAPHICS_EXECUTE 0x4000
#define PAGE_GRAPHICS_EXECUTE_READ 0x8000
#define PAGE_GRAPHICS_EXECUTE_READWRITE 0x10000
#define PAGE_GRAPHICS_COHERENT 0x20000
#define PAGE_GRAPHICS_NOCACHE 0x40000

//
// PAGE_REVERT_TO_FILE_MAP can be combined with other protection
// values to specify to VirtualProtect that the argument range
// should be reverted to point back to the backing file.  This
// means the contents of any private (copy on write) pages in the
// range will be discarded.  Any reverted pages that were locked
// into the working set are unlocked as well.
//

#define PAGE_ENCLAVE_THREAD_CONTROL 0x80000000
#define PAGE_REVERT_TO_FILE_MAP 0x80000000
#define PAGE_TARGETS_NO_UPDATE 0x40000000
#define PAGE_TARGETS_INVALID 0x40000000
#define PAGE_ENCLAVE_UNVALIDATED 0x20000000
#define PAGE_ENCLAVE_NO_CHANGE 0x20000000
#define PAGE_ENCLAVE_MASK 0x10000000
#define PAGE_ENCLAVE_DECOMMIT (PAGE_ENCLAVE_MASK | 0)
#define PAGE_ENCLAVE_SS_FIRST (PAGE_ENCLAVE_MASK | 1)
#define PAGE_ENCLAVE_SS_REST (PAGE_ENCLAVE_MASK | 2)

#define MEM_COMMIT 0x00001000
#define MEM_RESERVE 0x00002000
#define MEM_RESET 0x00080000
#define MEM_TOP_DOWN 0x00100000
#define MEM_RESET_UNDO 0x01000000
#define MEM_LARGE_PAGES 0x20000000
#define MEM_4MB_PAGES 0x80000000
#define MEM_64K_PAGES (MEM_LARGE_PAGES | MEM_PHYSICAL)
#define MEM_DECOMMIT 0x00004000
#define MEM_RELEASE 0x00008000
#define MEM_FREE 0x00010000

#define OBJ_INHERIT 0x00000002L
#define OBJ_PERMANENT 0x00000010L
#define OBJ_EXCLUSIVE 0x00000020L
#define OBJ_CASE_INSENSITIVE 0x00000040L
#define OBJ_OPENIF 0x00000080L
#define OBJ_OPENLINK 0x00000100L
#define OBJ_KERNEL_HANDLE 0x00000200L
#define OBJ_FORCE_ACCESS_CHECK 0x00000400L
#define OBJ_IGNORE_IMPERSONATED_DEVICEMAP 0x00000800L
#define OBJ_DONT_REPARSE 0x00001000L
#define OBJ_VALID_ATTRIBUTES 0x00001FF2L

#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

typedef enum _FILE_INFORMATION_CLASS
{
    FileDirectoryInformation = 1,
    FileFullDirectoryInformation,            // 2
    FileBothDirectoryInformation,            // 3
    FileBasicInformation,                    // 4
    FileStandardInformation,                 // 5
    FileInternalInformation,                 // 6
    FileEaInformation,                       // 7
    FileAccessInformation,                   // 8
    FileNameInformation,                     // 9
    FileRenameInformation,                   // 10
    FileLinkInformation,                     // 11
    FileNamesInformation,                    // 12
    FileDispositionInformation,              // 13
    FilePositionInformation,                 // 14
    FileFullEaInformation,                   // 15
    FileModeInformation,                     // 16
    FileAlignmentInformation,                // 17
    FileAllInformation,                      // 18
    FileAllocationInformation,               // 19
    FileEndOfFileInformation,                // 20
    FileAlternateNameInformation,            // 21
    FileStreamInformation,                   // 22
    FilePipeInformation,                     // 23
    FilePipeLocalInformation,                // 24
    FilePipeRemoteInformation,               // 25
    FileMailslotQueryInformation,            // 26
    FileMailslotSetInformation,              // 27
    FileCompressionInformation,              // 28
    FileObjectIdInformation,                 // 29
    FileCompletionInformation,               // 30
    FileMoveClusterInformation,              // 31
    FileQuotaInformation,                    // 32
    FileReparsePointInformation,             // 33
    FileNetworkOpenInformation,              // 34
    FileAttributeTagInformation,             // 35
    FileTrackingInformation,                 // 36
    FileIdBothDirectoryInformation,          // 37
    FileIdFullDirectoryInformation,          // 38
    FileValidDataLengthInformation,          // 39
    FileShortNameInformation,                // 40
    FileIoCompletionNotificationInformation, // 41
    FileIoStatusBlockRangeInformation,       // 42
    FileIoPriorityHintInformation,           // 43
    FileSfioReserveInformation,              // 44
    FileSfioVolumeInformation,               // 45
    FileHardLinkInformation,                 // 46
    FileProcessIdsUsingFileInformation,      // 47
    FileNormalizedNameInformation,           // 48
    FileNetworkPhysicalNameInformation,      // 49
    FileIdGlobalTxDirectoryInformation,      // 50
    FileIsRemoteDeviceInformation,           // 51
    FileUnusedInformation,                   // 52
    FileNumaNodeInformation,                 // 53
    FileStandardLinkInformation,             // 54
    FileRemoteProtocolInformation,           // 55

    //
    //  These are special versions of these operations (defined earlier)
    //  which can be used by kernel mode drivers only to bypass security
    //  access checks for Rename and HardLink operations.  These operations
    //  are only recognized by the IOManager, a file system should never
    //  receive these.
    //

    FileRenameInformationBypassAccessCheck, // 56
    FileLinkInformationBypassAccessCheck,   // 57

    //
    // End of special information classes reserved for IOManager.
    //

    FileVolumeNameInformation,                    // 58
    FileIdInformation,                            // 59
    FileIdExtdDirectoryInformation,               // 60
    FileReplaceCompletionInformation,             // 61
    FileHardLinkFullIdInformation,                // 62
    FileIdExtdBothDirectoryInformation,           // 63
    FileDispositionInformationEx,                 // 64
    FileRenameInformationEx,                      // 65
    FileRenameInformationExBypassAccessCheck,     // 66
    FileDesiredStorageClassInformation,           // 67
    FileStatInformation,                          // 68
    FileMemoryPartitionInformation,               // 69
    FileStatLxInformation,                        // 70
    FileCaseSensitiveInformation,                 // 71
    FileLinkInformationEx,                        // 72
    FileLinkInformationExBypassAccessCheck,       // 73
    FileStorageReserveIdInformation,              // 74
    FileCaseSensitiveInformationForceAccessCheck, // 75
    FileKnownFolderInformation,                   // 76
    FileStatBasicInformation,                     // 77
    FileId64ExtdDirectoryInformation,             // 78
    FileId64ExtdBothDirectoryInformation,         // 79
    FileIdAllExtdDirectoryInformation,            // 80
    FileIdAllExtdBothDirectoryInformation,        // 81

    FileMaximumInformation
} FILE_INFORMATION_CLASS,
    *PFILE_INFORMATION_CLASS;

typedef enum _MEMORY_CACHING_TYPE_ORIG
{
    MmFrameBufferCached = 2
} MEMORY_CACHING_TYPE_ORIG;

typedef enum _MEMORY_CACHING_TYPE
{
    MmNonCached,
    MmCached,
    MmWriteCombined = MmFrameBufferCached,
    MmHardwareCoherentCached,
    MmNonCachedUnordered, // IA64
    MmUSWCCached,
    MmMaximumCacheType,
    MmNotMapped = -1
} MEMORY_CACHING_TYPE;

typedef enum _SECTION_INHERIT
{
    ViewShare = 1,
    ViewUnmap = 2
} SECTION_INHERIT;

typedef struct _CLIENT_ID
{
    HANDLE UniqueProcess;
    HANDLE UniqueThread;
} CLIENT_ID;
typedef CLIENT_ID *PCLIENT_ID;

typedef struct _LIST_ENTRY
{
    struct _LIST_ENTRY *Flink;
    struct _LIST_ENTRY *Blink;
} LIST_ENTRY, *PLIST_ENTRY;

typedef struct _UNICODE_STRING
{
    short Length;
    short MaximumLength;
    short *Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef enum _MODE
{
    KernelMode,
    UserMode,
    MaximumMode
} MODE;

typedef struct _IRP
{
    ULONG64 *resver;
} IRP, *PIRP;

typedef struct _DRIVER_OBJECT
{
    USHORT Type;
    USHORT Size;
    struct _DEVICE_OBJECT *DeviceObject;
    LONG Flags;
    void *DriverStart;
    LONG DriverSize;
    void *DriverSection;
    struct _DRIVER_EXTENSION *DriverExtension;
    struct _UNICODE_STRING DriverName;
    struct _UNICODE_STRING *HardwareDatabase;
    struct _FAST_IO_DISPATCH *FastIoDispatch;
    LONG(*DriverInit)
    (struct _DRIVER_OBJECT *arg1, PUNICODE_STRING arg2);
    void (*DriverStartIo)(struct _DEVICE_OBJECT *arg1, PIRP pirp);
    void (*DriverUnload)(struct _DRIVER_OBJECT *arg1);
    LONG(*MajorFunction[28])
    (struct _DEVICE_OBJECT *arg1, PIRP pirp);
} DRIVER_OBJECT, *PDRIVER_OBJECT;

typedef struct _OBJECT_TYPE *POBJECT_TYPE;

typedef struct _MDL
{
    struct _MDL *Next;
    CSHORT Size;
    CSHORT MdlFlags;

    struct _EPROCESS *Process;
    PVOID MappedSystemVa;
    PVOID StartVa;
    ULONG ByteCount;
    ULONG ByteOffset;
} MDL, *PMDL;

typedef struct _NDIS_M_DRIVER_BLOCK
{
    union
    {
        struct
        {
            void *Header;
            void *NextDriver;
        };
        struct
        {
            char Space[0x028]; // 0x028 DriverObject
            PDRIVER_OBJECT DriverObject;
        };
    };
} NDIS_M_DRIVER_BLOCK, *PNDIS_M_DRIVER_BLOCK;

typedef union _LARGE_INTEGER
{
    struct
    {
        ULONG LowPart;
        LONG HighPart;
    } DUMMYSTRUCTNAME;
    struct
    {
        ULONG LowPart;
        LONG HighPart;
    } u;
    LONGLONG QuadPart;
} LARGE_INTEGER;

typedef LARGE_INTEGER *PLARGE_INTEGER;

typedef struct _FILE_STANDARD_INFORMATION
{
    LARGE_INTEGER AllocationSize;
    LARGE_INTEGER EndOfFile;
    ULONG NumberOfLinks;
    BOOLEAN DeletePending;
    BOOLEAN Directory;
} FILE_STANDARD_INFORMATION, *PFILE_STANDARD_INFORMATION;

typedef struct _IO_STATUS_BLOCK
{
    union
    {
        NTSTATUS Status;
        PVOID Pointer;
    };

    ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef struct _OBJECT_ATTRIBUTES
{
    ULONG Length;
    HANDLE RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG Attributes;
    PVOID SecurityDescriptor;       // Points to type SECURITY_DESCRIPTOR
    PVOID SecurityQualityOfService; // Points to type SECURITY_QUALITY_OF_SERVICE
} OBJECT_ATTRIBUTES;
typedef OBJECT_ATTRIBUTES *POBJECT_ATTRIBUTES;
typedef CONST OBJECT_ATTRIBUTES *PCOBJECT_ATTRIBUTES;

#define InitializeObjectAttributes(p, n, a, r, s) \
                                                  \
    (p)->Length = sizeof(OBJECT_ATTRIBUTES);      \
    (p)->RootDirectory = r;                       \
    (p)->Attributes = a;                          \
    (p)->ObjectName = n;                          \
    (p)->SecurityDescriptor = s;                  \
    (p)->SecurityQualityOfService = NULL;

typedef struct _BL_APPLICATION_ENTRY
{
    ULONG64 Signature;
    ULONG Flags;
    struct
    {
        unsigned long Data1;
        unsigned short Data2;
        unsigned short Data3;
        unsigned char Data4[8];
    } GUID;
    ULONG Unknown[4];
    ULONG64 BcdData;
} BL_APPLICATION_ENTRY, *PBL_APPLICATION_ENTRY;

typedef const UNICODE_STRING *PCUNICODE_STRING;

typedef struct _KLDR_DATA_TABLE_ENTRY
{
    struct _LIST_ENTRY InLoadOrderLinks;
    void *ExceptionTable;
    ULONG64 ExceptionTableSize;
    void *GpValue;
    struct _NON_PAGED_DEBUG_INFO *NonPagedDebugInfo;
    void *DllBase;
    void *EntryPoint;
    ULONG64 SizeOfImage;
    struct _UNICODE_STRING FullDllName;
    struct _UNICODE_STRING BaseDllName;
    ULONG Flags;
    short LoadCount;
    union
    {
        short SignatureLevel : 4;
        short SignatureType : 3;
        short Unused : 9;
        short EntireField;
    } u1;
    void *SectionPointer;
    ULONG CheckSum;
    ULONG CoverageSectionSize;
    void *CoverageSection;
    void *LoadedImports;
    void *Spare;
    ULONG SizeOfImageNotRounded;
    ULONG TimeDateStamp;
} KLDR_DATA_TABLE_ENTRY, *PKLDR_DATA_TABLE_ENTRY;

typedef struct _LOADER_PARAMETER_BLOCK
{
    LONG OsMajorVersion;
    LONG OsMinorVersion;
    LONG Size;
    LONG OsLoaderSecurityVersion;
    LIST_ENTRY LoadOrderListHead;
    LIST_ENTRY MemoryDescriptorListHead; // dt nt!_memory_allocation_descriptor
    LIST_ENTRY BootDriverListHead;
    LIST_ENTRY EarlyLaunchListHead;
    LIST_ENTRY CoreDriverListHead;
    LIST_ENTRY CoreExtensionsDriverListHead;
    LIST_ENTRY TpmCoreDriverListHead;
    LONG64 KernelStack;
    LONG64 Prcb;
    LONG64 Process;
    LONG64 Thread;
    LONG KernelStackSize;
    LONG RegistryLength;
    LONG64 RegistryBase;
} LOADER_PARAMETER_BLOCK, *PLOADER_PARAMETER_BLOCK;

*/

#define NTAPI __stdcall
#define VOID void
#define IN
#define OUT

#define OBJ_INHERIT 0x00000002L
#define OBJ_PERMANENT 0x00000010L
#define OBJ_EXCLUSIVE 0x00000020L
#define OBJ_CASE_INSENSITIVE 0x00000040L
#define OBJ_OPENIF 0x00000080L
#define OBJ_OPENLINK 0x00000100L
#define OBJ_KERNEL_HANDLE 0x00000200L
#define OBJ_FORCE_ACCESS_CHECK 0x00000400L
#define OBJ_IGNORE_IMPERSONATED_DEVICEMAP 0x00000800L
#define OBJ_DONT_REPARSE 0x00001000L
#define OBJ_VALID_ATTRIBUTES 0x00001FF2L

#define FILE_ATTRIBUTE_READONLY 0x00000001
#define FILE_ATTRIBUTE_HIDDEN 0x00000002
#define FILE_ATTRIBUTE_SYSTEM 0x00000004
// OLD DOS VOLID                             0x00000008

#define FILE_ATTRIBUTE_DIRECTORY 0x00000010
#define FILE_ATTRIBUTE_ARCHIVE 0x00000020
#define FILE_ATTRIBUTE_DEVICE 0x00000040
#define FILE_ATTRIBUTE_NORMAL 0x00000080

#define FILE_ATTRIBUTE_TEMPORARY 0x00000100
#define FILE_ATTRIBUTE_SPARSE_FILE 0x00000200
#define FILE_ATTRIBUTE_REPARSE_POINT 0x00000400
#define FILE_ATTRIBUTE_COMPRESSED 0x00000800

#define FILE_ATTRIBUTE_OFFLINE 0x00001000
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED 0x00002000
#define FILE_ATTRIBUTE_ENCRYPTED 0x00004000

#define GENERIC_READ (0x80000000L)
#define GENERIC_WRITE (0x40000000L)
#define GENERIC_EXECUTE (0x20000000L)
#define GENERIC_ALL (0x10000000L)

#define FILE_SHARE_READ 0x00000001
#define FILE_SHARE_WRITE 0x00000002
#define FILE_SHARE_DELETE 0x00000004
#define FILE_SHARE_VALID_FLAGS 0x00000007

#define DELETE (0x00010000L)
#define READ_CONTROL (0x00020000L)
#define WRITE_DAC (0x00040000L)
#define WRITE_OWNER (0x00080000L)
#define SYNCHRONIZE (0x00100000L)

#define STANDARD_RIGHTS_REQUIRED (0x000F0000L)
#define STANDARD_RIGHTS_READ (READ_CONTROL)
#define STANDARD_RIGHTS_WRITE (READ_CONTROL)
#define STANDARD_RIGHTS_EXECUTE (READ_CONTROL)
#define STANDARD_RIGHTS_ALL (0x001F0000L)
#define SPECIFIC_RIGHTS_ALL (0x0000FFFFL)

#define FILE_SUPERSEDE 0x00000000
#define FILE_OPEN 0x00000001
#define FILE_CREATE 0x00000002
#define FILE_OPEN_IF 0x00000003
#define FILE_OVERWRITE 0x00000004
#define FILE_OVERWRITE_IF 0x00000005
#define FILE_MAXIMUM_DISPOSITION 0x00000005

#define FILE_DIRECTORY_FILE 0x00000001
#define FILE_WRITE_THROUGH 0x00000002
#define FILE_SEQUENTIAL_ONLY 0x00000004
#define FILE_NO_INTERMEDIATE_BUFFERING 0x00000008
#define FILE_SYNCHRONOUS_IO_ALERT 0x00000010
#define FILE_SYNCHRONOUS_IO_NONALERT 0x00000020
#define FILE_NON_DIRECTORY_FILE 0x00000040
#define FILE_CREATE_TREE_CONNECTION 0x00000080
#define FILE_COMPLETE_IF_OPLOCKED 0x00000100
#define FILE_NO_EA_KNOWLEDGE 0x00000200
#define FILE_OPEN_REMOTE_INSTANCE 0x00000400
#define FILE_RANDOM_ACCESS 0x00000800
#define FILE_DELETE_ON_CLOSE 0x00001000
#define FILE_OPEN_BY_FILE_ID 0x00002000
#define FILE_OPEN_FOR_BACKUP_INTENT 0x00004000
#define FILE_NO_COMPRESSION 0x00008000

#define POOL_FLAG_REQUIRED_START 0x0000000000000001
#define POOL_FLAG_USE_QUOTA 0x0000000000000001            // Charge quota
#define POOL_FLAG_UNINITIALIZED 0x0000000000000002        // Don't zero-initialize allocation
#define POOL_FLAG_SESSION 0x0000000000000004              // Use session specific pool
#define POOL_FLAG_CACHE_ALIGNED 0x0000000000000008        // Cache aligned allocation
#define POOL_FLAG_RESERVED1 0x0000000000000010            // Reserved for system use
#define POOL_FLAG_RAISE_ON_FAILURE 0x0000000000000020     // Raise exception on failure
#define POOL_FLAG_NON_PAGED 0x0000000000000040            // Non paged pool NX
#define POOL_FLAG_NON_PAGED_EXECUTE 0x0000000000000080    // Non paged pool executable
#define POOL_FLAG_PAGED 0x0000000000000100                // Paged pool
#define POOL_FLAG_RESERVED2 0x0000000000000200            // Reserved for system use
#define POOL_FLAG_RESERVED3 0x0000000000000400            // Reserved for system use
#define POOL_FLAG_LAST_KNOWN_REQUIRED POOL_FLAG_RESERVED3 // Must be set to the last known required entry.
#define POOL_FLAG_REQUIRED_END 0x0000000080000000

#define POOL_FLAG_OPTIONAL_START 0x0000000100000000
#define POOL_FLAG_SPECIAL_POOL 0x0000000100000000 // Make special pool allocation
#define POOL_FLAG_OPTIONAL_END 0x8000000000000000

#define POOL_FLAG_REQUIRED_MASK 0x00000000FFFFFFFF

#define PAGE_ENCLAVE_THREAD_CONTROL 0x80000000
#define PAGE_REVERT_TO_FILE_MAP 0x80000000
#define PAGE_TARGETS_NO_UPDATE 0x40000000
#define PAGE_TARGETS_INVALID 0x40000000
#define PAGE_ENCLAVE_UNVALIDATED 0x20000000
#define PAGE_ENCLAVE_NO_CHANGE 0x20000000
#define PAGE_ENCLAVE_MASK 0x10000000
#define PAGE_ENCLAVE_DECOMMIT (PAGE_ENCLAVE_MASK | 0)
#define PAGE_ENCLAVE_SS_FIRST (PAGE_ENCLAVE_MASK | 1)
#define PAGE_ENCLAVE_SS_REST (PAGE_ENCLAVE_MASK | 2)

#define MEM_COMMIT 0x00001000
#define MEM_RESERVE 0x00002000
#define MEM_RESET 0x00080000
#define MEM_TOP_DOWN 0x00100000
#define MEM_RESET_UNDO 0x01000000
#define MEM_LARGE_PAGES 0x20000000
#define MEM_4MB_PAGES 0x80000000
#define MEM_64K_PAGES (MEM_LARGE_PAGES | MEM_PHYSICAL)
#define MEM_DECOMMIT 0x00004000
#define MEM_RELEASE 0x00008000
#define MEM_FREE 0x00010000

#define SEGMENT_ALL_ACCESS SECTION_ALL_ACCESS

#define PAGE_NOACCESS           0x01    
#define PAGE_READONLY           0x02    
#define PAGE_READWRITE          0x04    
#define PAGE_WRITECOPY          0x08    

#define PAGE_EXECUTE            0x10    
#define PAGE_EXECUTE_READ       0x20    
#define PAGE_EXECUTE_READWRITE  0x40    
#define PAGE_EXECUTE_WRITECOPY  0x80    

#define PAGE_GUARD             0x100    
#define PAGE_NOCACHE           0x200    
#define PAGE_WRITECOMBINE      0x400    

#define PAGE_GRAPHICS_NOACCESS           0x0800    
#define PAGE_GRAPHICS_READONLY           0x1000    
#define PAGE_GRAPHICS_READWRITE          0x2000    
#define PAGE_GRAPHICS_EXECUTE            0x4000    
#define PAGE_GRAPHICS_EXECUTE_READ       0x8000    
#define PAGE_GRAPHICS_EXECUTE_READWRITE 0x10000    
#define PAGE_GRAPHICS_COHERENT          0x20000    
#define PAGE_GRAPHICS_NOCACHE           0x40000    

#define PROCESS_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0xFFFF)

#define POOL_FLAG_UNUSED_REQUIRED_BITS (POOL_FLAG_REQUIRED_MASK & ~(POOL_FLAG_LAST_KNOWN_REQUIRED | (POOL_FLAG_LAST_KNOWN_REQUIRED - 1)))

#define ALL_PROCESSOR_GROUPS        0xffff


#define MAXULONG64  ((ULONG64)~((ULONG64)0))
#define MAXLONG64   ((LONG64)(MAXULONG64 >> 1))
#define MINLONG64   ((LONG64)~MAXLONG64)

#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

typedef long LONG;
typedef void *PVOID;
typedef void *LPVOID;

typedef void *HANDLE;
typedef HANDLE *PHANDLE;
typedef LONG NTSTATUS;
/*lint -save -e624 */ // Don't complain about different typedefs.
typedef NTSTATUS *PNTSTATUS;

typedef char CHAR;
typedef short SHORT;
typedef long LONG;

typedef SHORT *PSHORT; // winnt
typedef LONG *PLONG;   // winnt

typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef unsigned long ULONG;

typedef UCHAR *PUCHAR;
typedef USHORT *PUSHORT;
typedef ULONG *PULONG;

typedef unsigned int DWORD;
typedef void *LPVOID;
typedef long long INT_PTR, *PINT_PTR;
typedef long long LONGLONG;
typedef unsigned long long UINT_PTR, ULONG64, *PUINT_PTR, *PULONG64;

typedef long long LONG_PTR, *PLONG_PTR;
typedef unsigned long long ULONG_PTR, *PULONG_PTR;

typedef ULONG_PTR SIZE_T, *PSIZE_T;
typedef LONG_PTR SSIZE_T, *PSSIZE_T;

typedef enum _FILE_INFORMATION_CLASS
{
    FileDirectoryInformation = 1,
    FileFullDirectoryInformation,            // 2
    FileBothDirectoryInformation,            // 3
    FileBasicInformation,                    // 4
    FileStandardInformation,                 // 5
    FileInternalInformation,                 // 6
    FileEaInformation,                       // 7
    FileAccessInformation,                   // 8
    FileNameInformation,                     // 9
    FileRenameInformation,                   // 10
    FileLinkInformation,                     // 11
    FileNamesInformation,                    // 12
    FileDispositionInformation,              // 13
    FilePositionInformation,                 // 14
    FileFullEaInformation,                   // 15
    FileModeInformation,                     // 16
    FileAlignmentInformation,                // 17
    FileAllInformation,                      // 18
    FileAllocationInformation,               // 19
    FileEndOfFileInformation,                // 20
    FileAlternateNameInformation,            // 21
    FileStreamInformation,                   // 22
    FilePipeInformation,                     // 23
    FilePipeLocalInformation,                // 24
    FilePipeRemoteInformation,               // 25
    FileMailslotQueryInformation,            // 26
    FileMailslotSetInformation,              // 27
    FileCompressionInformation,              // 28
    FileObjectIdInformation,                 // 29
    FileCompletionInformation,               // 30
    FileMoveClusterInformation,              // 31
    FileQuotaInformation,                    // 32
    FileReparsePointInformation,             // 33
    FileNetworkOpenInformation,              // 34
    FileAttributeTagInformation,             // 35
    FileTrackingInformation,                 // 36
    FileIdBothDirectoryInformation,          // 37
    FileIdFullDirectoryInformation,          // 38
    FileValidDataLengthInformation,          // 39
    FileShortNameInformation,                // 40
    FileIoCompletionNotificationInformation, // 41
    FileIoStatusBlockRangeInformation,       // 42
    FileIoPriorityHintInformation,           // 43
    FileSfioReserveInformation,              // 44
    FileSfioVolumeInformation,               // 45
    FileHardLinkInformation,                 // 46
    FileProcessIdsUsingFileInformation,      // 47
    FileNormalizedNameInformation,           // 48
    FileNetworkPhysicalNameInformation,      // 49
    FileIdGlobalTxDirectoryInformation,      // 50
    FileIsRemoteDeviceInformation,           // 51
    FileUnusedInformation,                   // 52
    FileNumaNodeInformation,                 // 53
    FileStandardLinkInformation,             // 54
    FileRemoteProtocolInformation,           // 55

    //
    //  These are special versions of these operations (defined earlier)
    //  which can be used by kernel mode drivers only to bypass security
    //  access checks for Rename and HardLink operations.  These operations
    //  are only recognized by the IOManager, a file system should never
    //  receive these.
    //

    FileRenameInformationBypassAccessCheck, // 56
    FileLinkInformationBypassAccessCheck,   // 57

    //
    // End of special information classes reserved for IOManager.
    //

    FileVolumeNameInformation,                    // 58
    FileIdInformation,                            // 59
    FileIdExtdDirectoryInformation,               // 60
    FileReplaceCompletionInformation,             // 61
    FileHardLinkFullIdInformation,                // 62
    FileIdExtdBothDirectoryInformation,           // 63
    FileDispositionInformationEx,                 // 64
    FileRenameInformationEx,                      // 65
    FileRenameInformationExBypassAccessCheck,     // 66
    FileDesiredStorageClassInformation,           // 67
    FileStatInformation,                          // 68
    FileMemoryPartitionInformation,               // 69
    FileStatLxInformation,                        // 70
    FileCaseSensitiveInformation,                 // 71
    FileLinkInformationEx,                        // 72
    FileLinkInformationExBypassAccessCheck,       // 73
    FileStorageReserveIdInformation,              // 74
    FileCaseSensitiveInformationForceAccessCheck, // 75
    FileKnownFolderInformation,                   // 76
    FileStatBasicInformation,                     // 77
    FileId64ExtdDirectoryInformation,             // 78
    FileId64ExtdBothDirectoryInformation,         // 79
    FileIdAllExtdDirectoryInformation,            // 80
    FileIdAllExtdBothDirectoryInformation,        // 81

    FileMaximumInformation
} FILE_INFORMATION_CLASS,
    *PFILE_INFORMATION_CLASS;

typedef enum _MEMORY_CACHING_TYPE_ORIG
{
    MmFrameBufferCached = 2
} MEMORY_CACHING_TYPE_ORIG;

typedef enum _MEMORY_CACHING_TYPE
{
    MmNonCached,
    MmCached,
    MmWriteCombined = MmFrameBufferCached,
    MmHardwareCoherentCached,
    MmNonCachedUnordered, // IA64
    MmUSWCCached,
    MmMaximumCacheType,
    MmNotMapped = -1
} MEMORY_CACHING_TYPE;

typedef ULONG_PTR KIPI_BROADCAST_WORKER(ULONG_PTR Argument);
typedef KIPI_BROADCAST_WORKER *PKIPI_BROADCAST_WORKER;

typedef ULONG ACCESS_MASK;
typedef ACCESS_MASK *PACCESS_MASK;

typedef struct _IO_STATUS_BLOCK
{
    union
    {
        NTSTATUS Status;
        PVOID Pointer;
    };

    ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef VOID(NTAPI *PIO_APC_ROUTINE)(PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, ULONG Reserved);


typedef struct _CLIENT_ID
{
    HANDLE UniqueProcess;
    HANDLE UniqueThread;
} CLIENT_ID;
typedef CLIENT_ID *PCLIENT_ID;

typedef struct _UNICODE_STRING
{
    USHORT Length;
    USHORT MaximumLength;
    USHORT *Buffer;
} UNICODE_STRING;

typedef UNICODE_STRING *PUNICODE_STRING;
typedef const UNICODE_STRING *PCUNICODE_STRING;

typedef union _LARGE_INTEGER
{
    struct
    {
        ULONG LowPart;
        LONG HighPart;
    };
    LONGLONG QuadPart;
} LARGE_INTEGER;

typedef LARGE_INTEGER *PLARGE_INTEGER;

// typedef LARGE_INTEGER PHYSICAL_ADDRESS, *PPHYSICAL_ADDRESS;

typedef struct _LIST_ENTRY
{
    struct _LIST_ENTRY *Flink;
    struct _LIST_ENTRY *Blink;
} LIST_ENTRY, *PLIST_ENTRY, *PRLIST_ENTRY;

typedef struct _OBJECT_ATTRIBUTES
{
    ULONG Length;
    HANDLE RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG Attributes;
    PVOID SecurityDescriptor;       // Points to type SECURITY_DESCRIPTOR
    PVOID SecurityQualityOfService; // Points to type SECURITY_QUALITY_OF_SERVICE
} OBJECT_ATTRIBUTES;
typedef OBJECT_ATTRIBUTES *POBJECT_ATTRIBUTES;

#define InitializeObjectAttributes(p, n, a, r, s) \
    {                                             \
        (p)->Length = sizeof(OBJECT_ATTRIBUTES);  \
        (p)->RootDirectory = r;                   \
        (p)->Attributes = a;                      \
        (p)->ObjectName = n;                      \
        (p)->SecurityDescriptor = s;              \
        (p)->SecurityQualityOfService = NULL;     \
    }

typedef struct _FILE_STANDARD_INFORMATION
{
    LARGE_INTEGER AllocationSize;
    LARGE_INTEGER EndOfFile;
    ULONG NumberOfLinks;
    char DeletePending;
    char Directory;
} FILE_STANDARD_INFORMATION, *PFILE_STANDARD_INFORMATION;

#define NtCurrentProcess() ( (HANDLE)(LONG_PTR) -1 )  
#define ZwCurrentProcess() NtCurrentProcess()         
#define NtCurrentThread() ( (HANDLE)(LONG_PTR) -2 )   
#define ZwCurrentThread() NtCurrentThread()           
#define NtCurrentSession() ( (HANDLE)(LONG_PTR) -3 )  
#define ZwCurrentSession() NtCurrentSession()      


typedef struct _BL_APPLICATION_ENTRY
{
    uint64 Signature;
    uint32 Flags;
    struct
    {
        unsigned long Data1;
        unsigned short Data2;
        unsigned short Data3;
        unsigned char Data4[8];
    } GUID;
    uint32 Unknown[4];
    uint64 BcdData;
} BL_APPLICATION_ENTRY, *PBL_APPLICATION_ENTRY;

typedef struct _LOADER_PARAMETER_BLOCK
{
    int32 OsMajorVersion;
    int32 OsMinorVersion;
    int32 Size;
    int32 OsLoaderSecurityVersion;
    LIST_ENTRY LoadOrderListHead;
    LIST_ENTRY MemoryDescriptorListHead; // dt nt!_memory_allocation_descriptor
    LIST_ENTRY BootDriverListHead;
    LIST_ENTRY EarlyLaunchListHead;
    LIST_ENTRY CoreDriverListHead;
    LIST_ENTRY CoreExtensionsDriverListHead;
    LIST_ENTRY TpmCoreDriverListHead;
    int64 KernelStack;
    int64 Prcb;
    int64 Process;
    int64 Thread;
    int32 KernelStackSize;
    int32 RegistryLength;
    int64 RegistryBase;
} LOADER_PARAMETER_BLOCK, *PLOADER_PARAMETER_BLOCK;

typedef struct _KLDR_DATA_TABLE_ENTRY
{
    struct _LIST_ENTRY InLoadOrderLinks;
    void *ExceptionTable;
    uint64 ExceptionTableSize;
    void *GpValue;
    struct _NON_PAGED_DEBUG_INFO *NonPagedDebugInfo;
    void *DllBase;
    void *EntryPoint;
    uint64 SizeOfImage;
    struct _UNICODE_STRING FullDllName;
    struct _UNICODE_STRING BaseDllName;
    uint32 Flags;
    short LoadCount;
    union
    {
        short SignatureLevel : 4;
        short SignatureType : 3;
        short Unused : 9;
        short EntireField;
    } u1;
    void *SectionPointer;
    uint32 CheckSum;
    uint32 CoverageSectionSize;
    void *CoverageSection;
    void *LoadedImports;
    void *Spare;
    uint32 SizeOfImageNotRounded;
    uint32 TimeDateStamp;
} KLDR_DATA_TABLE_ENTRY, *PKLDR_DATA_TABLE_ENTRY;


#endif


typedef LONG ( *PTHREAD_START_ROUTINE)(PVOID lpThreadParameter);
typedef PTHREAD_START_ROUTINE LPTHREAD_START_ROUTINE;