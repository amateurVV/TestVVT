#pragma once

#define MSR_IA32_APIC_BASE 0x1B
#define MSR_IA32_FEATURE_CONTROL 0x3A
#define MSR_IA32_SPEC_CTRL 0x48
#define MSR_IA32_PRED_CMD 0x49
#define MSR_IA32_SMM_MONITOR_CTL 0x9B
#define MSR_IA32_SMBASE 0x9E
#define MSR_IA32_MISC_PACKAGE_CTLS 0xBC
#define MSR_IA32_CORE_CAPABILITIES 0xCF
#define MSR_IA32_TSX_CTRL 0x122
#define MSR_IA32_SYSENTER_CS 0x174
#define MSR_IA32_SYSENTER_ESP 0x175
#define MSR_IA32_SYSENTER_EIP 0x176
#define MSR_IA32_DEBUGCTL 0x1D9
#define MSR_IA32_MISC_ENABLE 0x1A0
#define MSR_IA32_SMRR_PHYSBASE 0x1F2
#define MSR_IA32_SMRR_PHYSMASK 0x1F3
#define MSR_IA32_PAT 0x277
#define MSR_IA32_PERF_CAPABILITIES 0x345
#define MSR_IA32_FIXED_CTR_CTRL 0x38D
#define MSR_IA32_PERF_GLOBAL_STATUS 0x38E
#define MSR_IA32_PERF_GLOBAL_CTRL 0x38F
#define MSR_IA32_PERF_GLOBAL_OVF_CTRL 0x390
#define MSR_IA32_PERF_GLOBAL_STATUS_RESET 0x390
#define MSR_IA32_PERF_GLOBAL_STATUS_SET 0x391
#define MSR_IA32_PERF_GLOBAL_INUSE 0x392
#define MSR_IA32_PEBS_ENABLE 0x3F1
#define MSR_IA32_RTIT_OUTPUT_BASE 0x560
#define MSR_IA32_RTIT_OUTPUT_MASK_PTRS 0x0561
#define MSR_IA32_RTIT_CTL 0x570
#define MSR_IA32_RTIT_STATUS 0x571
#define MSR_IA32_RTIT_CR3_MATCH 0x572

#define MSR_IA32_RTIT_ADDR0_A 0x580
#define MSR_IA32_RTIT_ADDR1_A 0x582
#define MSR_IA32_RTIT_ADDR2_A 0x584
#define MSR_IA32_RTIT_ADDR3_A 0x586
#define MSR_IA32_RTIT_ADDR0_B 0x581
#define MSR_IA32_RTIT_ADDR1_B 0x583
#define MSR_IA32_RTIT_ADDR2_B 0x585
#define MSR_IA32_RTIT_ADDR3_B 0x587

#define MSR_IA32_DS_AREA 0x600
#define MSR_IA32_U_CET 0x6A0
#define MSR_IA32_S_CET 0x6A2
#define MSR_IA32_PL0_SSP 0x6A4
#define MSR_IA32_INTERRUPT_SSP_TABLE_ADDR 0x6A8
#define MSR_IA32_TSC_DEADLINE 0x6E0
#define MSR_IA32_PKRS 0x6E1
#define MSR_IA32_PM_ENABLE 0x770
#define MSR_IA32_HWP_REQUEST 0x774
#define MSR_IA32_X2APIC_APICID 0x802
#define MSR_IA32_TME_CAPABILITY 0x981
#define MSR_IA32_DEBUG_INTERFACE 0xC80
#define MSR_IA32_BNDCFGS 0xD90

// #define x2APIC 0x802 - 0x83F

#define MSR_IA32_VMX_BASIC 0x480
#define MSR_IA32_VMX_PINBASED_CTLS 0x481
#define MSR_IA32_VMX_PROCBASED_CTLS 0x482
#define MSR_IA32_VMX_EXIT_CTLS 0x483
#define MSR_IA32_VMX_ENTRY_CTLS 0x484
#define MSR_IA32_VMX_MISC 0x485
#define MSR_IA32_VMX_CR0_FIXED0 0x486
#define MSR_IA32_VMX_CR0_FIXED1 0x487
#define MSR_IA32_VMX_CR4_FIXED0 0x488
#define MSR_IA32_VMX_CR4_FIXED1 0x489
#define MSR_IA32_VMX_VMCS_ENUM 0x48A
#define MSR_IA32_VMX_PROCBASED_CTLS2 0x48B
#define MSR_IA32_VMX_EPT_VPID_CAP 0x48C
#define MSR_IA32_VMX_TRUE_PINBASED_CTLS 0x48D
#define MSR_IA32_VMX_TRUE_PROCBASED_CTLS 0x48E
#define MSR_IA32_VMX_TRUE_EXIT_CTLS 0x48F
#define MSR_IA32_VMX_TRUE_ENTRY_CTLS 0x490
#define MSR_IA32_VMX_VMFUNC 0x491
#define MSR_IA32_VMX_PROCBASED_CTLS3 0x492
#define MSR_IA32_VMX_EXIT_CTLS2 0x493

#define MSR_IA32_EFER 0xC0000080
#define MSR_IA32_STAR 0xC0000081
#define MSR_IA32_LSTAR 0xC0000082
#define MSR_IA32_CSTAR 0xC0000083
#define MSR_IA32_FMASK 0xC0000084
#define MSR_IA32_FS_BASE 0xC0000100
#define MSR_IA32_GS_BASE 0xC0000101
#define MSR_IA32_KERNEL_GS_BASE 0xC0000102
#define MSR_IA32_TSC_AUX 0xC0000103


#define MSR_IA32_PERF_CTL           0x199
#define MSR_IA32_CLOCK_MODULATION   0x19A
#define MSR_IA32_MPERF              0xE7
#define MSR_IA32_APERF              0xE8
#define MSR_PP0_ENERGY_STATUS       0x639


#pragma pack(1)

typedef union
{
    ///
    /// Individual bit fields
    ///
    struct
    {
        ///
        /// [Bit 0] TraceEn.
        ///
        unsigned long long TraceEn : 1;
        ///
        /// [Bit 1] CYCEn. If (CPUID.(EAX=07H, ECX=0):EBX[1] = 1).
        ///
        unsigned long long CYCEn : 1;
        ///
        /// [Bit 2] OS.
        ///
        unsigned long long OS : 1;
        ///
        /// [Bit 3] User.
        ///
        unsigned long long User : 1;
        ///
        /// [Bit 4] PwrEvtEn.
        ///
        unsigned long long PwrEvtEn : 1;
        ///
        /// [Bit 5] FUPonPTW.
        ///
        unsigned long long FUPonPTW : 1;
        ///
        /// [Bit 6] FabricEn. If (CPUID.(EAX=07H, ECX=0):ECX[3] = 1).
        ///
        unsigned long long FabricEn : 1;
        ///
        /// [Bit 7] CR3 filter.
        ///
        unsigned long long CR3 : 1;
        ///
        /// [Bit 8] ToPA.
        ///
        unsigned long long ToPA : 1;
        ///
        /// [Bit 9] MTCEn. If (CPUID.(EAX=07H, ECX=0):EBX[3] = 1).
        ///
        unsigned long long MTCEn : 1;
        ///
        /// [Bit 10] TSCEn.
        ///
        unsigned long long TSCEn : 1;
        ///
        /// [Bit 11] DisRETC.
        ///
        unsigned long long DisRETC : 1;
        ///
        /// [Bit 12] PTWEn.
        ///
        unsigned long long PTWEn : 1;
        ///
        /// [Bit 13] BranchEn.
        ///
        unsigned long long BranchEn : 1;
        ///
        /// [Bits 17:14] MTCFreq. If (CPUID.(EAX=07H, ECX=0):EBX[3] = 1).
        ///
        unsigned long long MTCFreq : 4;
        unsigned long long Reserved3 : 1;
        ///
        /// [Bits 22:19] CYCThresh. If (CPUID.(EAX=07H, ECX=0):EBX[1] = 1).
        ///
        unsigned long long CYCThresh : 4;
        unsigned long long Reserved4 : 1;
        ///
        /// [Bits 27:24] PSBFreq. If (CPUID.(EAX=07H, ECX=0):EBX[1] = 1).
        ///
        unsigned long long PSBFreq : 4;
        unsigned long long Reserved5 : 4;
        ///
        /// [Bits 35:32] ADDR0_CFG. If (CPUID.(EAX=07H, ECX=1):EAX[2:0] > 0).
        ///
        unsigned long long ADDR0_CFG : 4;
        ///
        /// [Bits 39:36] ADDR1_CFG. If (CPUID.(EAX=07H, ECX=1):EAX[2:0] > 1).
        ///
        unsigned long long ADDR1_CFG : 4;
        ///
        /// [Bits 43:40] ADDR2_CFG. If (CPUID.(EAX=07H, ECX=1):EAX[2:0] > 2).
        ///
        unsigned long long ADDR2_CFG : 4;
        ///
        /// [Bits 47:44] ADDR3_CFG. If (CPUID.(EAX=07H, ECX=1):EAX[2:0] > 3).
        ///
        unsigned long long ADDR3_CFG : 4;
        unsigned long long Reserved6 : 16;
    } Bits;
    ///
    /// All bit fields as a 64-bit value
    ///
    unsigned long long value;
} MSR_IA32_RTIT_CTL_REGISTER;
typedef union
{
    ///
    /// Individual bit fields
    ///
    struct
    {
        ///
        /// [Bit 0] FilterEn, (writes ignored).
        /// If (CPUID.(EAX=07H, ECX=0):EBX[2] = 1).
        ///
        unsigned long long FilterEn : 1;
        ///
        /// [Bit 1] ContexEn, (writes ignored).
        ///
        unsigned long long ContexEn : 1;
        ///
        /// [Bit 2] TriggerEn, (writes ignored).
        ///
        unsigned long long TriggerEn : 1;
        unsigned long long Reserved1 : 1;
        ///
        /// [Bit 4] Error.
        ///
        unsigned long long Error : 1;
        ///
        /// [Bit 5] Stopped.
        ///
        unsigned long long Stopped : 1;
        unsigned long long Reserved2 : 26;
        ///
        /// [Bits 48:32] PacketByteCnt. If (CPUID.(EAX=07H, ECX=0):EBX[1] > 3).
        ///
        unsigned long long PacketByteCnt : 17;
        unsigned long long Reserved3 : 15;
    } Bits;
    ///
    /// All bit fields as a 64-bit value
    ///
    unsigned long long value;
} MSR_IA32_RTIT_STATUS_REGISTER;

typedef union
{
    ///
    /// Individual bit fields
    ///
    struct
    {
        unsigned long long Reserved : 5;
        ///
        /// [Bits 31:5] CR3[63:5] value to match.
        ///
        unsigned long long Cr3 : 27;
        ///
        /// [Bits 63:32] CR3[63:5] value to match.
        ///
        unsigned long long Cr3Hi : 32;
    } Bits;
    ///
    /// All bit fields as a 64-bit value
    ///
    unsigned long long value;
} MSR_IA32_RTIT_CR3_MATCH_REGISTER;

typedef union
{
    ///
    /// Individual bit fields
    ///
    struct
    {
        ///
        /// [Bits 31:0] Virtual Address.
        ///
        unsigned long long VirtualAddress : 32;
        ///
        /// [Bits 47:32] Virtual Address.
        ///
        unsigned long long VirtualAddressHi : 16;
        ///
        /// [Bits 63:48] SignExt_VA.
        ///
        unsigned long long SignExt_VA : 16;
    } Bits;
    ///
    /// All bit fields as a 64-bit value
    ///
    unsigned long long value;
} MSR_IA32_RTIT_ADDR_REGISTER;

typedef union
{
    struct
    {
        unsigned long Lock : 1;                       // bit-0			Lock bit (0 = unlocked, 1 = locked). When set to '1' further writes to this MSR are blocked.
        unsigned long EnableVmxInsideSmx : 1;         // bit-1			Enable VMX in SMX operation.
        unsigned long EnableVmxOutsideSmx : 1;        // bit-2			Enable VMX outside SMX operation.
        unsigned long : 5;                            // bit-3:7		Reserved
        unsigned long SenterLocalFunctionEnables : 7; // bit-8:14		SENTER Local Function Enables: When set, each bit in the field represents an enable control for a corresponding SENTER function.
        unsigned long SenterGlobalEnable : 1;         // bit-15		SENTER Global Enable: Must be set to ‘1’ to enable operation of GETSEC[SENTER].
        unsigned long : 1;                            // bit-16		Reserved
        unsigned long SgxLaunchControlEnable : 1;     // bit-17		SGX Launch Control Enable: Must be set to ‘1’ to enable runtime re-configuration of SGX Launch Control via the IA32_SGXLEPUBKEYHASHn MSR.
        unsigned long SgxEnable : 1;                  // bit-18		SGX Global Enable: Must be set to ‘1’ to enable Intel SGX leaf functions.
        unsigned long : 1;                            // bit-19		Reserved
        unsigned long LmceOn : 1;                     // bit-20		LMCE On: When set, system software can program the MSRs associated with LMCE to configure delivery of some machine check exceptions to a single logical processor.
        unsigned long : 11;                           // bit-21:31		Reserved
        unsigned long : 32;                           // bit-32:64		Reserved
    } ;
    unsigned long long value;
} MSR_IA32_FEATURE_CONTROL_REGISTER, *PMSR_IA32_FEATURE_CONTROL_REGISTER;

typedef union
{
    struct
    {
        unsigned long VmcsRevisonId : 31; // bit-0:30	VMCS版本标识符
        unsigned long MustBeZero : 1;     // bit-31	始终为0

        unsigned long VmcsSize : 13; // bit-32:44	VMON 或 VMCS 分配的字节数
        unsigned long : 3;           // bit-45:47	保留

        unsigned long VmcsAddressWidth : 1; // bit-48	VMON 或 VMCS （I/O 位图、虚拟 APIC 页面、用于 VMX 转换的 MSR 区域）的物理地址的宽度。
        //			如果位为 0，则这些地址限制为处理器的物理地址宽度。
        //			如果位为 1，则这些地址限制为 32 位。
        //			对于支持英特尔 64 位架构的处理器，此位始终为 0。

        unsigned long DualMonitor : 1; // bit-49	如果位为 1，则逻辑处理器支持系统管理中断和系统管理模式的双监视器处理。

        unsigned long MemoryType : 4; // bit-50:53	VMCS、VMCS 中指针引用的数据结构（I/O 位图、虚拟 APIC 页面、用于 VMX 转换的 MSR 区域）和 MSEG 标头的内存类型。
        //			如果 软件需要访问这些数据结构（例如，修改 MSR 位图的内容），它可以配置分页结构以将它们映射到线性地址空间中。
        //			如果这样做，则应建立使用此 MSR 中报告的内存类型位 53：50 的映射。
        //			值   0		Uncacheable(UC)
        //			值	 1-5	Not Used
        //			值	 6		Write Back(WB)
        //			值	 7-15	Not Used

        unsigned long InsOutsReporting : 1; // bit-54	如果位为 1，则处理器将报告由于执行 INS 和 OUTS 指令而导致的虚拟机退出指令字段中的虚拟机出口信息

        unsigned long VmxControls : 1; // bit-55	如果位为 0，控件是默认0组，不使用以下MSR:(带TRUE控件)
        //			IA32_VMX_TRUE_PINBASED_CTLS
        //			IA32_VMX_TRUE_PROCBASED_CTLS
        //			IA32_VMX_TRUE_EXIT_CTLS
        //			IA32_VMX_TRUE_ENTRY_CTLS
        unsigned long HardwareException : 1; // bit-56	如果位为 1，则软件可以使用虚拟机Entry在有或没有错误代码的情况下提供硬件异常，而不管向量如何
        unsigned long : 7;                   // bit-57:63	保留
    } Bits;

    unsigned long long value;
} MSR_IA32_VMX_BASIC_REGISTER, *PMSR_IA32_VMX_BASIC_REGISTER;

typedef union
{
    struct
    {
        unsigned long ExIDT : 1;      // Bit-0		外部中断		External-interrupt exiting
        unsigned long Reserved1 : 2;  // Bit-1:2				Reserved
        unsigned long ExNMI : 1;      // Bit-3					NMI exiting
        unsigned long Reserved2 : 1;  // Bit-4		保留
        unsigned long V_NMI : 1;      // Bit-5					Virtual NMIs
        unsigned long A_VMXpt : 1;    // Bit-6		抢占定时器	Activate VMXpreemption timer
        unsigned long Ppi : 1;        // Bit-7		发布中断		Process posted interrupts
        unsigned long Reserved3 : 24; // Bit-8-31
    } Bits[2];
    unsigned long long value;
} MSR_IA32_VMX_PINBASED_CTLS_REGISTER, *PMSR_IA32_VMX_PINBASED_CTLS_REGISTER;

typedef union
{
    struct
    {
        unsigned long Reserved1 : 2;     // bit-0:1
        unsigned long ExIDT : 1;         // bit-2
        unsigned long TSC : 1;           // bit-3
        unsigned long Reserved2 : 3;     // bit-4:6
        unsigned long HLT : 1;           // bit-7
        unsigned long Reserved3 : 1;     // bit-8
        unsigned long INVLPG : 1;        // bit-9
        unsigned long MWAIT : 1;         // bit-10
        unsigned long RDPMC : 1;         // bit-11
        unsigned long RDTSC : 1;         // bit-12
        unsigned long Reserved4 : 2;     // bit-13:14
        unsigned long LCR3 : 1;          // bit-15
        unsigned long SCR3 : 1;          // bit-16
        unsigned long Tertiary : 1;      // bit-17
        unsigned long Reserved5 : 1;     // bit-18
        unsigned long LCR8 : 1;          // bit-19
        unsigned long SCR8 : 1;          // bit-20
        unsigned long TPR : 1;           // bit-21
        unsigned long NMI : 1;           // bit-22
        unsigned long MOV_DR : 1;        // bit-23
        unsigned long UnconditionIO : 1; // bit-24
        unsigned long IOmap : 1;         // bit-25
        unsigned long Reserved6 : 1;     // bit-26
        unsigned long MonitorTrap : 1;   // bit-27
        unsigned long MSRmap : 1;        // bit-28
        unsigned long MONITOR : 1;       // bit-29
        unsigned long PAUSE : 1;         // bit-30
        unsigned long Secondary : 1;     // bit-31

    } Bits[2];
    unsigned long long value;
} MSR_IA32_VMX_PROCBASED_CTLS_REGISTER, *PMSR_IA32_VMX_PROCBASED_CTLS_REGISTER;

typedef union
{
    struct
    {
        unsigned long VirtualAPIC : 1;        // bit-0
        unsigned long EPT : 1;                // bit-1
        unsigned long DescriptTable : 1;      // bit-2
        unsigned long RDTSCP : 1;             // bit-3
        unsigned long Virtualx2APIC : 1;      // bit-4
        unsigned long VPID : 1;               // bit-5
        unsigned long WBINVD : 1;             // bit-6
        unsigned long UnGuest : 1;            // bit-7
        unsigned long APIC : 1;               // bit-8
        unsigned long VirInterrupt : 1;       // bit-9
        unsigned long PAUSE : 1;              // bit-10
        unsigned long RDRAND : 1;             // bit-11
        unsigned long INVPCID : 1;            // bit-12
        unsigned long VMFUNC : 1;             // bit-13
        unsigned long ShadowVMCS : 1;         // bit-14
        unsigned long ENCLS : 1;              // bit-15
        unsigned long RDSEED : 1;             // bit-16
        unsigned long PML : 1;                // bit-17
        unsigned long EPT_VE : 1;             // bit-18
        unsigned long ConcealVMX : 1;         // bit-19
        unsigned long XSAVES_XRSTORS : 1;     // bit-20
        unsigned long Reserved1 : 1;          // bit-21
        unsigned long ModeBaseEPT : 1;        // bit-22
        unsigned long SubPageEPT : 1;         // bit-23
        unsigned long GuestUsePhysicalPT : 1; // bit-24
        unsigned long TSC : 1;                // bit-25
        unsigned long UserWaitPause : 1;      // bit-26
        unsigned long PCONFIG : 1;            // bit-27
        unsigned long ENCLV : 1;              // bit-28
        unsigned long Reserved3 : 3;          // bit-29:31
    } Bits[2];
    unsigned long long value;
} MSR_IA32_VMX_PROCBASED_CTLS2_REGISTER, *PMSR_IA32_VMX_PROCBASED_CTLS2_REGISTER;

typedef union
{
    struct
    {
        unsigned long LOADIWKEY : 1;         // bit-0
        unsigned long HLAT : 1;              // bit-1
        unsigned long EPT_write_control : 1; // bit-2		EPT paging-write control
        unsigned long Guest_page : 1;        // bit-3		Guest-paging verification

    } Bits;
    unsigned long long value;
} MSR_IA32_VMX_PROCBASED_CTLS3_REGISTER, *PMSR_IA32_VMX_PROCBASED_CTLS3_REGISTER;

typedef union
{
    struct
    {
        unsigned long Reserved1 : 2;                  // bit-0:1
        unsigned long SaveDebug : 1;                  // bit-2
        unsigned long Reserved2 : 6;                  // bit-3:8
        unsigned long HOST_addr_size : 1;             // bit-9
        unsigned long Reserved3 : 2;                  // bit-10:11
        unsigned long Load_IA32_PERF_GLOBAL_CTRL : 1; // bit-12
        unsigned long Reserved4 : 2;                  // bit-13:14
        unsigned long InterruptExit : 1;              // bit-15
        unsigned long Reserved5 : 2;                  // bit-16:17
        unsigned long Save_IA32_PAT : 1;              // bit-18
        unsigned long Load_IA32_PAT : 1;              // bit-19
        unsigned long Save_IA32_EFER : 1;             // bit-20
        unsigned long Load_IA32_EFER : 1;             // bit-21
        unsigned long SaveVMXpt : 1;                  // bit-22	抢占定时器
        unsigned long Clear_IA32_BNDCFGS : 1;         // bit-23
        unsigned long Conceal_VMX_from_PT : 1;        // bit-24
        unsigned long Clear_IA32_RTIT_CTL : 1;        // bit-25
        unsigned long Clear_IA32_LBR_CTL : 1;         // bit-26
        unsigned long Reserved6 : 1;                  // bit-27
        unsigned long Load_CET_state : 1;             // bit-28
        unsigned long Load_PKRS : 1;                  // bit-29
        unsigned long Reserved7 : 1;                  // bit-30
        unsigned long Secondary : 1;                  // bit-31
    } Bits[2];
    unsigned long long value;
} MSR_IA32_VMX_EXIT_CTLS_REGISTER, *PMSR_IA32_VMX_EXIT_CTLS_REGISTER;

typedef union
{
    struct
    {
        unsigned long Reserved1 : 2;                   // bit-0:1
        unsigned long LoadDebug : 1;                   // bit-2
        unsigned long Reserved2 : 6;                   // bit-3:8
        unsigned long Guest_IA32e : 1;                 // bit-9
        unsigned long EntrySMM : 1;                    // bit-10
        unsigned long Dual_Monitor : 1;                // bit-11
        unsigned long Reserved3 : 1;                   // bit-12
        unsigned long Load_IA32_PERF_GLOBA_L_CTRL : 1; // bit-13
        unsigned long Load_IA32_PAT : 1;               // bit-14
        unsigned long Load_IA32_EFER : 1;              // bit-15
        unsigned long Load_IA32_BNDCFGS : 1;           // bit-16
        unsigned long Conceal_VMX_from_PT : 1;         // bit-17
        unsigned long Load_IA32_RTIT_CTL : 1;          // bit-18
        unsigned long Reserved4 : 1;                   // bit-19
        unsigned long Load_CET_state : 1;              // bit-20
        unsigned long Load_guest_IA32_LBR_CTL : 1;     // bit-21
        unsigned long Load_PKRS : 1;                   // bit-22
        unsigned long Reserved5 : 9;                   // bit-23:31
    } Bits[2];
    unsigned long long value;
} MSR_IA32_VMX_ENTRY_CTLS_REGISTER, *PMSR_IA32_VMX_ENTRY_CTLS_REGISTER;

typedef union _EXIT_QUALIFICATION_CR_ACCESS
{
    struct
    {
        unsigned long long NumCR : 4;       // bit-0:3	    控制寄存器的编号（CLTS 和 LMSW 为 0）
        unsigned long long AccessType : 2;  // bit-4:5	    0 = MOV to CR;	1 = MOV from CR;	2 = CLTS;3 = LMSW
        unsigned long long LMSW : 1;        // bit-6	    0 = register;	1 = memory
        unsigned long long : 1;             // bit-7
        unsigned long long NumReg : 4;      // bit-8:11	    NumReg 0-F,rax-r15
        unsigned long long : 4;             // bit-12:15
        unsigned long long SourceData : 16; // bit-16:31	LMSW, the LMSW source data (CLTSand MOV CR, cleared to 0)
        unsigned long long : 32;            // bit-32:63
    };
    unsigned long long value;
} EXIT_QUALIFICATION_CR_ACCESS, *PEXIT_QUALIFICATION_CR_ACCESS;

typedef union _EXIT_REASON_FIELDS
{
    struct
    {
        unsigned long Basic : 16;     // bit-0:15	退出基本信息
        unsigned long AlwaysZero : 1; // bit-16
        unsigned long Undefine1 : 10; // bit-17:26
        unsigned long Enclave : 1;    // bit-27
        unsigned long MTF : 1;        // bit-28
        unsigned long VMXroot : 1;    // bit-29
        unsigned long Undefine2 : 1;  // bit-30
        unsigned long IsValid : 1;    // bit-31
    };
    unsigned long long value;
} EXIT_REASON_FIELDS, *PEXIT_REASON_FIELDS;

typedef union _EXIT_INTR_INFO
{
    struct
    {
        unsigned long Vector : 8;    // bit-0:7
        unsigned long Type : 3;      // bit-8:10
        unsigned long ErrorCode : 1; // bit-11	(0 = invalid; 1 = valid)
        unsigned long NMIToIRET : 1; // bit-12
        unsigned long Undefine : 18; // bit-13:30
        unsigned long IsValid : 1;   // bit-31
    };
    unsigned long long value;
} EXIT_INTR_INFO, *PEXIT_INTR_INFO;

typedef struct _VPID_EPT_CAPABILITIES
{
    unsigned long long ExecuteOnly : 1;

} VPID_EPT_CAPABILITIES, *PVPID_EPT_CAPABILITIES;

typedef union _IA32_APIC_BASE_MSR
{
    struct
    {
        unsigned long long : 8;
        unsigned long long BSP : 1;
        unsigned long long : 1;
        unsigned long long x2APIC : 1;
        unsigned long long APIC : 1;
        unsigned long long ApicBase : 52;
    };
    unsigned long long value;
} IA32_APIC_BASE_MSR, *PIA32_APIC_BASE_MSR;

typedef union _CPU_INFO
{
    struct
    {
        unsigned long long SteppingID : 4;
        unsigned long long Model : 4;
        unsigned long long FamilyID : 4;
        unsigned long long ProcessorType : 2;
        unsigned long long : 2;
        unsigned long long ExtendedModelID : 4;
        unsigned long long ExtendedFamilyID : 8;
        unsigned long long : 4;
    };
    unsigned long long value;
} CPU_INFO, *PCPU_INFO;

typedef union
{
    struct
    {
        unsigned short RPL : 2;
        unsigned short TI : 1;
        unsigned short Index : 13;
    } Bits;
    unsigned short value;
} SELECTOR, *PSELECTOR;

typedef struct _SEGMENT_DESCRIPTOR
{
    unsigned short limit0;
    unsigned short base0;
    unsigned char base1;
    union
    {
        struct
        {
            unsigned char TYPE : 4;
            unsigned char S : 1;
            unsigned char DPL : 2;
            unsigned char P : 1;
            unsigned char limit1 : 4;
            unsigned char AVL : 1;
            unsigned char L : 1;
            unsigned char DB : 1;
            unsigned char G : 1;
        } Bits;
        unsigned short value;
    } attr;
    unsigned char base2;
    unsigned long base3;
    unsigned long reserved;
} SEG_DESCRIPTOR, *PSEG_DESCRIPTOR;

typedef struct _SEG
{
    SELECTOR sel;
    PSEG_DESCRIPTOR descriptor;
    unsigned long long Base;
    unsigned long long Limit;
} SEG, *PSEG;

enum SEGREGS
{
    ES = 0,
    CS,
    SS,
    DS,
    FS,
    GS,
    LDTR,
    TR
};

#pragma pack()