#pragma once

#pragma pack(1)

#define EPT_READ 1
#define EPT_WRITE 2
#define EPT_EXECUTE 4

#define EPT_ACCESS_ALL (EPT_READ | EPT_WRITE | EPT_EXECUTE)

#define PML4E_COUNT 512
#define PDPTE_COUNT 512
#define PDE_COUNT 512
#define PTE_COUNT 512

#define EPT_EXECUTE_ONLY (1 << 0)
#define EPT_PAGE_WALK_4 (1 << 6)
#define EPT_WRITE_BACK (1 << 14)
#define EPT_SUPPORT_DIRTY (1 << 21)

typedef union _EptViolation
{
	struct
	{
		uint64 read : 1;
		uint64 wrire : 1;
		uint64 exec : 1;
		uint64 readable : 1;
		uint64 wrireable : 1;
		uint64 executeable : 1;
		uint64 un1 : 1;
		uint64 vaild : 1;
		uint64 translation : 1;
		uint64 un2 : 3;
		uint64 NMIUnblocking : 1;
		uint64 un3 : 51;
	};
	uint64 value;
} EptViolation, *PEptViolation;

typedef union _EPML4E
{
	struct
	{
		uint64 Attribute : 3;		// bit 0:2
		uint64 : 5;					// bit 3:7
		uint64 Accessed : 1;		// bit 8
		uint64 : 1;					// bit 9
		uint64 UserModeExecute : 1; // bit 10
		uint64 : 1;					// bit 11
		uint64 PageFrame : 40;		// bit 12:51
		uint64 : 12;				// bit 52:63
	};

	uint64 value;
} EPML4E, *PEPML4E;

// typedef union _EPDPTE_1GB
// {
// 	struct
// 	{
// 		uint64 Attribute : 3;			  // bit 0:2
// 		uint64 MemoryType : 3;			  // bit 3:5
// 		uint64 IgnorePAT : 1;			  // bit 6
// 		uint64 Page1GB : 1;				  // bit 7
// 		uint64 Accessed : 1;			  // bit 8
// 		uint64 Ditry : 1;				  // bit 9
// 		uint64 UserModeExecute : 1;		  // bit 10
// 		uint64 : 1;						  // bit 11
// 		uint64 : 18;					  // bit 12:29
// 		uint64 PageFrame : 22;			  // bit 30:51
// 		uint64 : 5;						  // bit 52:56
// 		uint64 VerifyGuestPaging : 1;	  // bit 57
// 		uint64 GuestWritePaging : 1;	  // bit 58
// 		uint64 : 1;						  // bit 59
// 		uint64 SupervisorShadowStack : 1; // bit 60
// 		uint64 : 2;						  // bit 61:62
// 		uint64 SuppressVE : 1;			  // bit 63
// 	};
// 	uint64 value;
// } EPDPTE_1GB, *PEPDPTE_1GB;

typedef union _EPDPTE
{
	struct
	{
		uint64 Attribute : 3;		// bit 0:2
		uint64 : 5;					// bit 3:7
		uint64 Accessed : 1;		// bit 8
		uint64 : 1;					// bit 9
		uint64 UserModeExecute : 1; // bit 10
		uint64 : 1;					// bit 11
		uint64 PageFrame : 40;		// bit 12:51
		uint64 : 12;				// bit 52:63
	};

	/// @brief PDPTE_1GB
	struct
	{
		uint64 Attribute : 3;			  // bit 0:2
		uint64 MemoryType : 3;			  // bit 3:5
		uint64 IgnorePAT : 1;			  // bit 6
		uint64 Page1GB : 1;				  // bit 7
		uint64 Accessed : 1;			  // bit 8
		uint64 Ditry : 1;				  // bit 9
		uint64 UserModeExecute : 1;		  // bit 10
		uint64 : 1;						  // bit 11
		uint64 : 18;					  // bit 12:29
		uint64 PageFrame : 22;			  // bit 30:51
		uint64 : 5;						  // bit 52:56
		uint64 VerifyGuestPaging : 1;	  // bit 57
		uint64 GuestWritePaging : 1;	  // bit 58
		uint64 : 1;						  // bit 59
		uint64 SupervisorShadowStack : 1; // bit 60
		uint64 : 2;						  // bit 61:62
		uint64 SuppressVE : 1;			  // bit 63
	} s;
	uint64 value;
} EPDPTE, *PEPDPTE;

// typedef union _EPDE_2MB
// {
// 	struct
// 	{
// 		uint64 Attribute : 3;			  // bit 0:2
// 		uint64 MemoryType : 3;			  // bit 3:5
// 		uint64 IgnorePAT : 1;			  // bit 6
// 		uint64 LargePage : 1;			  // bit 7
// 		uint64 Accessed : 1;			  // bit 8
// 		uint64 Ditry : 1;				  // bit 9
// 		uint64 UserModeExecute : 1;		  // bit 10
// 		uint64 : 1;						  // bit 11
// 		uint64 : 9;						  // bit 12:20
// 		uint64 PageFrame2MB : 31;		  // bit 21:51
// 		uint64 : 5;						  // bit 52:56
// 		uint64 VerifyGuestPaging : 1;	  // bit 57
// 		uint64 GuestWritePaging : 1;	  // bit 58
// 		uint64 : 1;						  // bit 59
// 		uint64 SupervisorShadowStack : 1; // bit 60
// 		uint64 : 2;						  // bit 61:62
// 		uint64 SuppressVE : 1;			  // bit 63
// 	};
// 	uint64 value;
// } EPDE_2MB, *PEPDE_2MB;

typedef union _EPDE
{
	struct
	{
		uint64 Attribute : 3;		// bit 0:2
		uint64 : 5;					// bit 3:7
		uint64 Accessed : 1;		// bit 8
		uint64 : 1;					// bit 9
		uint64 UserModeExecute : 1; // bit 10
		uint64 : 1;					// bit 11
		uint64 PageFrame : 40;		// bit 12:51
		uint64 : 12;				// bit 52:63
	};
	/// @brief PDE_2MB
	struct
	{
		uint64 Attribute : 3;			  // bit 0:2
		uint64 MemoryType : 3;			  // bit 3:5
		uint64 IgnorePAT : 1;			  // bit 6
		uint64 LargePage : 1;			  // bit 7
		uint64 Accessed : 1;			  // bit 8
		uint64 Ditry : 1;				  // bit 9
		uint64 UserModeExecute : 1;		  // bit 10
		uint64 : 1;						  // bit 11
		uint64 : 9;						  // bit 12:20
		uint64 PageFrame2MB : 31;		  // bit 21:51
		uint64 : 5;						  // bit 52:56
		uint64 VerifyGuestPaging : 1;	  // bit 57
		uint64 GuestWritePaging : 1;	  // bit 58
		uint64 : 1;						  // bit 59
		uint64 SupervisorShadowStack : 1; // bit 60
		uint64 : 2;						  // bit 61:62
		uint64 SuppressVE : 1;			  // bit 63
	} s;
	uint64 value;
} EPDE, *PEPDE;

typedef union _EPTE
{
	struct
	{
		uint64 Attribute : 3;				// bit 0:2
		uint64 MemoryType : 3;				// bit 3:5
		uint64 IgnorePAT : 1;				// bit 6
		uint64 : 1;							// bit 7
		uint64 Accessed : 1;				// bit 8
		uint64 Ditry : 1;					// bit 9
		uint64 UserModeExecute : 1;			// bit 10
		uint64 : 1;							// bit 11
		uint64 PageFrame4KB : 40;			// bit 12:51
		uint64 : 5;							// bit 52:56
		uint64 VerifyGuestPaging : 1;		// bit 57
		uint64 GuestWritePaging : 1;		// bit 58
		uint64 : 1;							// bit 59
		uint64 SupervisorShadowStack : 1;	// bit 60
		uint64 SubPageWritePermissions : 1; // bit 61
		uint64 : 1;							// bit 62
		uint64 SuppressVE : 1;				// bit 63
	};

	uint64 value;
} EPTE, *PEPTE;

typedef struct _VMX_EPT_PAGES
{
	EPML4E pml4e[PML4E_COUNT];
	EPDPTE pdpte[PDPTE_COUNT];
	EPDE pde[PDPTE_COUNT][PDE_COUNT];

} VMX_EPT_PAGES, *PVMX_EPT_PAGES;

typedef union _ADDR_PACK
{
	struct
	{
		uint64 offset : 12;
		uint64 pte : 9;
		uint64 pde : 9;
		uint64 pdpte : 9;
		uint64 pml4e : 9;
		uint64 sym : 16;
	};
	uint64 value;
} ADDR_PACK, *PADDR_PACK;

typedef struct _EPT_HOOK_PROCESS
{
	void *Process;
	void *RetAddr;		// Hcak 返回到原函数 exec->hook处的代码;ret->hook处的下一条代码
	void *HookerEngine; // Hack 引擎:call->要执行的代码地址,ret->RetAddr
} EPT_HOOK_PROCESS, *PEPT_HOOK_PROCESS;

typedef struct _LIST_EPT_HOOK_PROCESS
{
	struct _LIST_EPT_HOOK_PROCESS *Next;
	EPT_HOOK_PROCESS Process;
} LIST_EPT_HOOK_PROCESS, *PLIST_EPT_HOOK_PROCESS;

typedef struct _SHELLCODE
{
	char SaveCode[0x20];
	char Engine[0x100];

} SHELLCODE, *PSHELLCODE;

typedef struct _EPT_HOOK_CONTEXT
{
	/*
	 HOOK执行流程:

	 1.原页,修改页,int3 hook,修改页只可执行,VE读写时换成原页,VE执行时换成修改页

	 2.HookerEngine,Asm构造一个引擎
		PUSH ALL
		拷贝参数
		CALL RAX
		POP ALL
		POP	RAX
		RET

	 3.RetAddr
		EXEC HOOK处的一条指令
		FF25 00000000
		原函数的下一条指令

	 4.触发int3,查找,命中
		PUSH 	RetAddr
		PUSH 	RAX
		MOV		RAX,HookCodeAddr
		JMP		HookerEngine
	*/

	void *TargetCodeAddrVir; // 要Hook的目标代码(虚拟地址)
	void *TargetCodeAddrPhy; // 要Hook的目标代码(物理地址)

	void *NewPage;		  // 替换的页面(虚拟地址)
	void *HookCodeAddr;	  // Hack 要执行的函数
	uint64 TargetCodeLen; // hook处的指令长度

	SHELLCODE ShellCode;

	// char TargetCode[0x100]; // Hook处的原代码+跳转至原代码的下一条指令
	SMEMORY PTE;
	LIST_EPT_HOOK_PROCESS ListProcess;
} EPT_HOOK_CONTEXT, *PEPT_HOOK_CONTEXT;

typedef struct _LIST_EPT_HOOK_CONTEXT
{
	struct _LIST_EPT_HOOK_CONTEXT *Blink;
	struct _LIST_EPT_HOOK_CONTEXT *Flink;
	PEPT_HOOK_CONTEXT context;
} LIST_EPT_HOOK_CONTEXT, *PLIST_EPT_HOOK_CONTEXT;

#pragma pcak()

uint64 IsSupportEPT();

/// @brief for windows driver virtual memory
uint64 Driver_InitEpt(PVT vt);
/// @brief for uefi physical memory
uint64 Efi_InitEpt(PVT vt);
/// @brief for first process physical and virtual memory
uint64 Os_InitEpt(PVT vt);

PEPDE EptGetGpaPDE(PADDR_PACK GPA);
PEPTE EptGetGpaPTE(PADDR_PACK GPA);

uint64 EptHook(PEPT_HOOK_CONTEXT HookContext);
uint64 EptHandlerBreakPoint(PGUESTREG GuestRegs);

uint64 InsertHookContext(PEPT_HOOK_CONTEXT context);
uint64 InsertHookProcess(PEPT_HOOK_CONTEXT context, PLIST_EPT_HOOK_PROCESS Process);

PEPT_HOOK_CONTEXT FindHookContext(void *HookAddrVir, void *EProcess);
PEPT_HOOK_CONTEXT FindHookPage(void *HookAddrVir, void *EProcess);
PEPT_HOOK_PROCESS FindHookProcess(PEPT_HOOK_CONTEXT HookContext, void *EProcess);