#pragma once

typedef enum _INTERRUPT_TYPE
{
	INTERRUPT_TYPE_EXTERNAL_INTERRUPT = 0,
	INTERRUPT_TYPE_RESERVED = 1,
	INTERRUPT_TYPE_NMI = 2,
	INTERRUPT_TYPE_HARDWARE_EXCEPTION = 3,
	INTERRUPT_TYPE_SOFTWARE_INTERRUPT = 4,
	INTERRUPT_TYPE_PRIVILEGED_SOFTWARE_INTERRUPT = 5,
	INTERRUPT_TYPE_SOFTWARE_EXCEPTION = 6,
	INTERRUPT_TYPE_OTHER_EVENT = 7
} INTERRUPT_TYPE;

typedef enum _EXCEPTION_VECTORS
{
	EXCEPTION_VECTOR_DIVIDE_ERROR,
	EXCEPTION_VECTOR_DEBUG_BREAKPOINT,
	EXCEPTION_VECTOR_NMI,
	EXCEPTION_VECTOR_BREAKPOINT,
	EXCEPTION_VECTOR_OVERFLOW,
	EXCEPTION_VECTOR_BOUND_RANGE_EXCEEDED,
	EXCEPTION_VECTOR_UNDEFINED_OPCODE,
	EXCEPTION_VECTOR_NO_MATH_COPROCESSOR,
	EXCEPTION_VECTOR_DOUBLE_FAULT,
	EXCEPTION_VECTOR_RESERVED0,
	EXCEPTION_VECTOR_INVALID_TASK_SEGMENT_SELECTOR,
	EXCEPTION_VECTOR_SEGMENT_NOT_PRESENT,
	EXCEPTION_VECTOR_STACK_SEGMENT_FAULT,
	EXCEPTION_VECTOR_GENERAL_PROTECTION_FAULT,
	EXCEPTION_VECTOR_PAGE_FAULT,
	EXCEPTION_VECTOR_RESERVED1,
	EXCEPTION_VECTOR_MATH_FAULT,
	EXCEPTION_VECTOR_ALIGNMENT_CHECK,
	EXCEPTION_VECTOR_MACHINE_CHECK,
	EXCEPTION_VECTOR_SIMD_FLOATING_POINT_NUMERIC_ERROR,
	EXCEPTION_VECTOR_VIRTUAL_EXCEPTION,
	EXCEPTION_VECTOR_RESERVED2,
	EXCEPTION_VECTOR_RESERVED3,
	EXCEPTION_VECTOR_RESERVED4,
	EXCEPTION_VECTOR_RESERVED5,
	EXCEPTION_VECTOR_RESERVED6,
	EXCEPTION_VECTOR_RESERVED7,
	EXCEPTION_VECTOR_RESERVED8,
	EXCEPTION_VECTOR_RESERVED9,
	EXCEPTION_VECTOR_RESERVED10,
	EXCEPTION_VECTOR_RESERVED11,
	EXCEPTION_VECTOR_RESERVED12,

	//
	// NT (Windows) specific exception vectors.
	//
	APC_INTERRUPT = 31,
	DPC_INTERRUPT = 47,
	CLOCK_INTERRUPT = 209,
	IPI_INTERRUPT = 225,
	PMI_INTERRUPT = 254,

} EXCEPTION_VECTORS;

enum vm_exit_reason
{
	EXIT_REASON_EXCEPTION_NMI = 0,
	EXIT_REASON_EXTERNAL_INTERRUPT = 1,
	EXIT_REASON_TRIPLE_FAULT = 2,
	EXIT_REASON_INIT = 3,
	EXIT_REASON_SIPI = 4,
	EXIT_REASON_IO_SMI = 5,
	EXIT_REASON_OTHER_SMI = 6,
	EXIT_REASON_INTERRUPT_WINDOW = 7,
	EXIT_REASON_PENDING_VIRT_NMI = 8,
	EXIT_REASON_TASK_SWITCH = 9,
	EXIT_REASON_CPUID = 10,
	EXIT_REASON_GETSEC = 11,
	EXIT_REASON_HLT = 12,
	EXIT_REASON_INVD = 13,
	EXIT_REASON_INVLPG = 14,
	EXIT_REASON_RDPMC = 15,
	EXIT_REASON_RDTSC = 16,
	EXIT_REASON_RSM = 17,
	EXIT_REASON_VMCALL = 18,
	EXIT_REASON_VMCLEAR = 19,
	EXIT_REASON_VMLAUNCH = 20,
	EXIT_REASON_VMPTRLD = 21,
	EXIT_REASON_VMPTRST = 22,
	EXIT_REASON_VMREAD = 23,
	EXIT_REASON_VMRESUME = 24,
	EXIT_REASON_VMWRITE = 25,
	EXIT_REASON_VMXOFF = 26,
	EXIT_REASON_VMXON = 27,
	EXIT_REASON_CR_ACCESS = 28,
	EXIT_REASON_DR_ACCESS = 29,
	EXIT_REASON_IO_INSTRUCTION = 30,
	EXIT_REASON_RDMSR = 31,
	EXIT_REASON_WRMSR = 32,
	EXIT_REASON_ENTRY_INVALID_GUEST_STATE = 33,
	EXIT_REASON_ENTRY_MSR_LOADING = 34,
	EXIT_REASON_MWAIT = 36,
	EXIT_REASON_MTF_TRAP_FLAG = 37,
	EXIT_REASON_MONITOR = 39,
	EXIT_REASON_PAUSE = 40,
	EXIT_REASON_MACHINE_CHECK = 41,
	EXIT_REASON_TPR_BELOW_THRESHOLD = 43,
	EXIT_REASON_APIC_ACCESS = 44,
	EXIT_REASON_VIR_EOI = 45,
	EXIT_REASON_GDTR_IDTR = 46,
	EXIT_REASON_TR_ACCESS = 47,
	EXIT_REASON_EPT_VIOLATION = 48,
	EXIT_REASON_EPT_MISCONFIG = 49,
	EXIT_REASON_INVEPT = 50,
	EXIT_REASON_RDTSCP = 51,
	EXIT_REASON_VMX_TIMER = 52,
	EXIT_REASON_INVVPID = 53,
	EXIT_REASON_WBINVD = 54,
	EXIT_REASON_XSETBV = 55,
	EXIT_REASON_APIC_WRITE = 56,
	EXIT_REASON_RDRAND = 57,
	EXIT_REASON_INVPCID = 58,
	EXIT_REASON_VMFUNC = 59,
	EXIT_REASON_ENCLS = 60,
	EXIT_REASON_RDSEED = 61,
	EXIT_REASON_PAGE_FULL = 62,
	EXIT_REASON_XSAVES = 63,
	EXIT_REASON_XRSTORS = 64,
	EXIT_REASON_SPP_RELATED_EVENT = 66,
	EXIT_REASON_UMWAIT = 67,
	EXIT_REASON_TPAUSE = 68,
	EXIT_REASON_LOADIWKEY = 69,
	EXIT_REASON_ENCLV = 70,
	EXIT_REASON_ENQCMD_PASID = 71,
	EXIT_REASON_ENQCMDS_PASID = 72,

	EXIT_MAX
};

static char *strExit[] = {
	"EXIT_REASON_EXCEPTION_NMI",
	"EXIT_REASON_EXTERNAL_INTERRUPT",
	"EXIT_REASON_TRIPLE_FAULT",
	"EXIT_REASON_INIT",
	"EXIT_REASON_SIPI",
	"EXIT_REASON_IO_SMI",
	"EXIT_REASON_OTHER_SMI",
	"EXIT_REASON_INTERRUPT_WINDOW",
	"EXIT_REASON_PENDING_VIRT_NMI",
	"EXIT_REASON_TASK_SWITCH",
	"EXIT_REASON_CPUID",
	"EXIT_REASON_GETSEC",
	"EXIT_REASON_HLT",
	"EXIT_REASON_INVD",
	"EXIT_REASON_INVLPG",
	"EXIT_REASON_RDPMC",
	"EXIT_REASON_RDTSC",
	"EXIT_REASON_RSM",
	"EXIT_REASON_VMCALL",
	"EXIT_REASON_VMCLEAR",
	"EXIT_REASON_VMLAUNCH",
	"EXIT_REASON_VMPTRLD",
	"EXIT_REASON_VMPTRST",
	"EXIT_REASON_VMREAD",
	"EXIT_REASON_VMRESUME",
	"EXIT_REASON_VMWRITE",
	"EXIT_REASON_VMXOFF",
	"EXIT_REASON_VMXON",
	"EXIT_REASON_CR_ACCESS",
	"EXIT_REASON_DR_ACCESS",
	"EXIT_REASON_IO_INSTRUCTION",
	"EXIT_REASON_RDMSR",
	"EXIT_REASON_WRMSR",
	"EXIT_REASON_ENTRY_INVALID_GUEST_STATE",
	"EXIT_REASON_ENTRY_MSR_LOADING",
	"EXIT_REASON_MWAIT",
	"EXIT_REASON_MTF_TRAP_FLAG",
	"EXIT_REASON_MONITOR",
	"EXIT_REASON_PAUSE",
	"EXIT_REASON_MACHINE_CHECK",
	"EXIT_REASON_TPR_BELOW_THRESHOLD",
	"EXIT_REASON_APIC_ACCESS",
	"EXIT_REASON_VIR_EOI",
	"EXIT_REASON_GDTR_IDTR",
	"EXIT_REASON_TR_ACCESS",
	"EXIT_REASON_EPT_VIOLATION",
	"EXIT_REASON_EPT_MISCONFIG",
	"EXIT_REASON_INVEPT",
	"EXIT_REASON_RDTSCP",
	"EXIT_REASON_VMX_TIMER",
	"EXIT_REASON_INVVPID",
	"EXIT_REASON_WBINVD",
	"EXIT_REASON_XSETBV",
	"EXIT_REASON_APIC_WRITE",
	"EXIT_REASON_RDRAND",
	"EXIT_REASON_INVPCID",
	"EXIT_REASON_VMFUNC",
	"EXIT_REASON_ENCLS",
	"EXIT_REASON_RDSEED",
	"EXIT_REASON_PAGE_FULL",
	"EXIT_REASON_XSAVES",
	"EXIT_REASON_XRSTORS",
	"EXIT_REASON_SPP_RELATED_EVENT",
	"EXIT_REASON_UMWAIT",
	"EXIT_REASON_TPAUSE",
	"EXIT_REASON_LOADIWKEY",
	"EXIT_REASON_ENCLV",
	"EXIT_REASON_ENQCMD_PASID",
	"EXIT_REASON_ENQCMDS_PASID"};

extern void InjectException(uint32 Type, uint32 Vector, uint32 DeliverErrorCode, uint32 ErrorCode, uint32 Instrlen);

#define InjectExceptionInt1() InjectException(INTERRUPT_TYPE_HARDWARE_EXCEPTION, EXCEPTION_VECTOR_DEBUG_BREAKPOINT, FALSE, 0, 0)
#define InjectExceptionInt3() InjectException(INTERRUPT_TYPE_SOFTWARE_EXCEPTION, EXCEPTION_VECTOR_BREAKPOINT, FALSE, 0, 1)

#define InjectExceptionGP() InjectException(INTERRUPT_TYPE_HARDWARE_EXCEPTION, EXCEPTION_VECTOR_GENERAL_PROTECTION_FAULT, FALSE, 0, 0)
#define InjectExceptionUD() InjectException(INTERRUPT_TYPE_HARDWARE_EXCEPTION, EXCEPTION_VECTOR_UNDEFINED_OPCODE, FALSE, 0, 0)

#define InjectExceptionPF(ErrorCode) InjectException(INTERRUPT_TYPE_HARDWARE_EXCEPTION, EXCEPTION_VECTOR_PAGE_FAULT, TRUE, ErrorCode, 0)

extern void GuestIncrementRIP(PGUESTREG GuestRegs);

extern uint64 (*HandlerExit[EXIT_MAX])(PGUESTREG);
extern void InitHandlerVmExit();
extern uint64 DispatchHandlerVmExit(PGUESTREG GuestRegs);
