#pragma once
#include "type.h"
#include "wintype.h"

typedef union _EXPUSHLOCK
{
    struct
    {
        uint64 Locked : 1;
        uint64 Waiting : 1;
        uint64 Waking : 1;
        uint64 MultipleShared : 1;
        uint64 Shared : 60;
    } s;
    uint64 Value;
    void *Ptr;
} EXPUSHLOCK, *PEXPUSHLOCK;

typedef union _EX_FAST_REF
{
    uint8 RefCnt : 4;
    uint8 Value;
    void* Object;
} EX_FAST_REF;
typedef struct _MI_VAD_SEQUENTIAL_INFO
{
    uint64 Length : 13;
    uint64 Vpn : 41;
} MI_VAD_SEQUENTIAL_INFO, *PMI_VAD_SEQUENTIAL_INFO;

typedef struct _MMEXTEND_INFO
{
    uint64 CommittedSize;
    uint32 ReferenceCount;
} MMEXTEND_INFO, *PMMEXTEND_INFO;


typedef void* _MI_VAD_EVENT_BLOCK;

typedef struct _SECTION_IMAGE_INFORMATION
{
    void *TransferAddress;
    uint64 ZeroBits;
    uint64 MaximumStackSize;
    uint64 CommittedStackSize;
    uint32 SubSystemType;
    struct
    {
        uint16 SubSystemMinorVersion;
        uint16 SubSystemMajorVersion;
    } SubSystemVersion;

    struct
    {
        uint16 MajorOperatingSystemVersion;
        uint16 MinorOperatingSystemVersion;
    } OperatingSystemVersion;

    uint16 ImageCharacteristics;
    uint16 DllCharacteristics;

    uint16 Machine;
    uint8 ImageContainsCode;
    uint8 ImageFlags;

    uint8 ComPlusNativeReady : 1;
    uint8 ComPlusILOnly : 1;
    uint8 ImageDynamicallyRelocated : 1;
    uint8 ImageMappedFlat : 1;
    uint8 BaseBelow4gb : 1;
    uint8 ComPlusPrefer32bit : 1;
    uint8 Reserved : 2;
    uint32 LoaderFlags;
    uint32 ImageFileSize;
    uint32 CheckSum;
   
} SECTION_IMAGE_INFORMATION, *PSECTION_IMAGE_INFORMATION;

typedef struct _MI_EXTRA_IMAGE_INFORMATION
{
    uint32 SizeOfHeaders;
    uint32 SizeOfImage;
    uint32 TimeDateStamp;
    uint32 ImageCetShadowStacksReady : 1;
    uint32 ImageCetShadowStacksStrictMode : 1;
    uint32 ImageCetSetContextIpValidationRelaxedMode : 1;
    uint32 ImageCetDynamicApisAllowInProc : 1;
    uint32 ImageCetDowngradeReserved1 : 1;
    uint32 ImageCetDowngradeReserved2 : 1;
    uint32 Spare : 26;
} MI_EXTRA_IMAGE_INFORMATION, *PMI_EXTRA_IMAGE_INFORMATION;
typedef struct _MI_SECTION_IMAGE_INFORMATION
{
    struct _SECTION_IMAGE_INFORMATION ExportedImageInformation;
    struct _MI_EXTRA_IMAGE_INFORMATION InternalImageInformation;

} MI_SECTION_IMAGE_INFORMATION, *PMI_SECTION_IMAGE_INFORMATION;

typedef struct _SEGMENT
{
    struct _CONTROL_AREA *ControlArea;
    uint32 TotalNumberOfPtes;
    struct _SEGMENT_FLAGS
    {
        uint32 TotalNumberOfPtes4132 : 10;
        uint32 Spare0 : 1;
        uint32 SessionDriverProtos : 1;
        uint32 LargePages : 1;
        uint32 DebugSymbolsLoaded : 1;
        uint32 WriteCombined : 1;
        uint32 NoCache : 1;
        uint32 Spare : 1;
        uint32 DefaultProtectionMask : 5;
        uint32 Binary32 : 1;
        uint32 ContainsDebug : 1;
        uint32 ForceCollision : 1;
        uint32 ImageSigningType : 3;
        uint32 ImageSigningLevel : 4;
    } SegmentFlags;
    uint64 NumberOfCommittedPages;
    uint64 SizeOfSegment;
    union
    {
        struct _MMEXTEND_INFO *ExtendInfo;
        void *BasedAddress;
    } u;

    EXPUSHLOCK SegmentLock;
    union
    {
        uint64 ImageCommitment;
        int32 CreatingProcessId;
    } u1;
    union
    {
        void *FirstMappedVa;
        struct _MI_SECTION_IMAGE_INFORMATION *ImageInfomation;
    } u2;

} SEGMENT, *PSEGMENT;

struct _CONTROL_AREA
{
    struct _SEGMENT *Segment;
     LIST_ENTRY ListHead;
    uint64 NumberOfSectionReferences;
    uint64 NumberOfPfnReferences;
    uint64 NumberOfMappedViews;
    uint64 NumberOfUserReferences;
    union
    {
        struct _MMSECTION_FLAGS
        {
            uint32 BeingDeleted : 1;
            uint32 BeingCreated : 1;
            uint32 BeingPurged : 1;
            uint32 NoModifiedWriting : 1;
            uint32 FailAllIo : 1;
            uint32 Image : 1;
            uint32 Based : 1;
            uint32 File : 1;
            uint32 AttemptingDelete : 1;
            uint32 PrefetchCreated : 1;
            uint32 PhysicalMemory : 1;
            uint32 ImageControlAreaOnRemovableMedia : 1;
            uint32 Reserve : 1;
            uint32 Commit : 1;
            uint32 NoChange : 1;
            uint32 WasPurged : 1;
            uint32 UserReference : 1;
            uint32 GlobalMemory : 1;
            uint32 DeleteOnClose : 1;
            uint32 FilePointerNull : 1;
            uint32 PreferredNode : 6;
            uint32 GlobalOnlyPerSession : 1;
            uint32 UserWritable : 1;
            uint32 SystemVaAllocated : 1;
            uint32 PreferredFsCompressionBoundary : 1;
            uint32 UsingFileExtents : 1;
            uint32 PageSize64K : 1;
        } Flags;
        uint32 LongFlags;
    } u;
    union
    {
        struct _MMSECTION_FLAGS2
        {
            uint32 PartitionId : 10;
            uint32 : 6;
            uint32 NoCrossPartitionAccess : 1;
            uint32 SubsectionCrossPartitionReferenceOverflow : 1;
        } Flags;
        uint32 LongFlags;
    } u1;

    union _EX_FAST_REF FilePointer;
    int32 ControlAreaLock;
    uint32 ModifiedWriteCount;
    uint64 WaitList; // Type:_MI_CONTROL_AREA_WAIT_BLOCK*
    union
    {
        struct
        {
            union
            {
                uint32 NumberOfSystemCacheViews;
                uint32 ImageRelocationStartBit;
            } u1;
            union
            {
                int32 WritableUserReferences;
                struct
                {
                    uint32 ImageRelocationSizeIn64k : 16;
                    uint32 SystemImage : 1;
                    uint32 CantMove : 1;
                    uint32 StrongCode : 2;
                    uint32 BitMap : 2;
                    uint32 ImageActive : 1;
                    uint32 ImageBaseOkToReuse : 1;
                } s;
            } u2;
            union
            {
                uint32 FlushInProgressCount;
                uint32 NumberOfSubsections;
                void *SeImageStub; // Type:_MI_IMAGE_SECURITY_REFERENCE*
            } u3;
        } e2;
    } u2;
    EXPUSHLOCK FileObjectLock; // Type: EX_PUSH_LOCK
    uint64 LockedPages;
    union
    {
        uint64 ImageCrossPartitionCharge;
        uint64 CommittedPageCount : 36;
        struct
        {
            uint64 IoAttributionContext : 61;
            uint64 Spare : 3;
        } s;
    } u3;
};

typedef struct _SUBSECTION
{
    struct _CONTROL_AREA *ControlArea;
    struct _MMPTE *SubsectionBase;
    struct _SUBSECTION *NextSubsection;
    void *GlobalPerSessionHead;

    union
    {
        struct _MMSUBSECTION_FLAGS
        {
            uint32 SubsectionAccessed : 1;
            uint32 Protection : 5;
            uint32 StartingSector4132 : 10;
            uint32 SubsectionStatic : 1;
            uint32 GlobalMemory : 1;
            uint32 Spare : 1;
            uint32 OnDereferenceList : 1;
            uint32 SectorEndOffset : 12;
        } SubsectionFlags;
        uint32 LongFlags;
    } u;
    uint32 StartingSector;
    uint32 NumberOfFullSectors;
    uint32 PtesInSubsection;
    union
    {
        struct _MI_SUBSECTION_ENTRY1
        {
            uint32 CrossPartitionReferences : 30;
            uint32 SubsectionMappedLarge : 2;
        } e1;
    } u1;

    uint32 UnusedPtes : 30;
    uint32 ExtentQueryNeeded : 1;
    uint32 DirtyPages : 1;
} SUBSECTION, *PSUBSECTION;

typedef struct _MMVAD_SHORT
{
    struct _MMVAD *NextVad;
    void *ExtraCreateInfo;
    struct _RTL_BALANCED_NODE *VadNode;
    uint32 StartingVpn;
    uint32 EndingVpn;
    uint8 StartingVpnHigh;
    uint8 EndingVpnHigh;
    uint8 CommitChargeHigh;
    uint8 SpareNT64VadUChar;
    int32 ReferenceCount;
    EXPUSHLOCK PushLock;
    union
    {
        struct _MMVAD_FLAGS
        {
            uint32 Lock : 1;
            uint32 LockContended : 1;
            uint32 DeleteInProgress : 1;
            uint32 NoChange : 1;
            uint32 VadType : 3;
            uint32 Protection : 5;
            uint32 PreferredNode : 6;
            uint32 PageSize : 2;
            uint32 PrivateMemory : 1;
        } VadFlags;

        struct _MM_PRIVATE_VAD_FLAGS
        {
            uint32 Lock : 1;
            uint32 LockContended : 1;
            uint32 DeleteInProgress : 1;
            uint32 NoChange : 1;
            uint32 VadType : 3;
            uint32 Protection : 5;
            uint32 PreferredNode : 6;
            uint32 PageSize : 2;
            uint32 PrivateMemoryAlwaysSet : 1;
            uint32 WriteWatch : 1;
            uint32 FixedLargePageSize : 1;
            uint32 ZeroFillPagesOptional : 1;
            uint32 Graphics : 1;
            uint32 Enclave : 1;
            uint32 ShadowStack : 1;
            uint32 PhysicalMemoryPfnsReferenced : 1;
        } PrivateVadFlags;
        struct _MM_GRAPHICS_VAD_FLAGS
        {
            uint32 Lock : 1;
            uint32 LockContended : 1;
            uint32 DeleteInProgress : 1;
            uint32 NoChange : 1;
            uint32 VadType : 3;
            uint32 Protection : 5;
            uint32 PreferredNode : 6;
            uint32 PageSize : 2;
            uint32 PrivateMemoryAlwaysSet : 1;
            uint32 WriteWatch : 1;
            uint32 FixedLargePageSize : 1;
            uint32 ZeroFillPagesOptional : 1;
            uint32 GraphicsAlwaysSet : 1;
            uint32 GraphicsUseCoherentBus : 1;
            uint32 GraphicsNoCache : 1;
            uint32 GraphicsPageProtection : 1;
        } GraphicsVadFlags;
        struct _MM_SHARED_VAD_FLAGS
        {
            uint32 Lock : 1;
            uint32 LockContended : 1;
            uint32 DeleteInProgress : 1;
            uint32 NoChange : 1;
            uint32 VadType : 3;
            uint32 Protection : 5;
            uint32 PreferredNode : 6;
            uint32 PageSize : 2;
            uint32 PrivateMemoryAlwaysSet : 1;
            uint32 PrivateFixup : 1;
            uint32 HotPatchAllowed : 1;
        } SharedVadFlags;
        uint32 LongFlags;
    } u;
    union
    {
        struct _MMVAD_FLAGS1
        {
            uint32 CommitCharge : 31;
            uint32 MemCommit : 1;
        } VadFlags1;
        uint32 LongFlags1;
    } u1;

    struct _MI_VAD_EVENT_BLOCK *EventList;
} MMVAD_SHORT, *PMMVAD_SHORT;

typedef struct _MMVAD
{
    struct _MMVAD_SHORT Core;
    union
    {
        struct _MMVAD_FLAGS2
        {
            uint64 FileOffset : 24;
            uint64 Large : 1;
            uint64 TrimBehind : 1;
            uint64 Inherit : 1;
            uint64 NoValidationNeeded : 1;
            uint64 PrivateDemandZero : 1;
            uint64 Spare : 3;
        } VadFlags2;
        uint32 LongFlags2;
    } u2;

    struct _SUBSECTION *Subsection;
    struct _MMPTE *FirstPrototypePte;
    struct _MMPTE *LastContiguousPte;
     LIST_ENTRY ViewLinks;
    struct _EPROCESS *VadsProcess; // 低位有标志位，需要清0
    union
    {
        struct _MI_VAD_SEQUENTIAL_INFO SequentialVa;
        struct _MMEXTEND_INFO *ExtendedInfo;
    } u4;
    uint64 FileObject;
} MMVAD;

typedef struct _RTL_BALANCED_NODE
{
    struct
    {
        struct _RTL_BALANCED_NODE *Left;
        struct _RTL_BALANCED_NODE *Right;

    } Children;
    union
    {
        uint64 Red : 1;
        uint64 Balance : 2;
        uint64 value;
    } Parent;
} RTL_BALANCED_NODE, *PRTL_BALANCED_NODE;

typedef struct _RTL_AVL_TREE
{
    struct _RTL_BALANCED_NODE *Root;
} RTL_AVL_TREE, *PRTL_AVL_TREE;



uint64 test();