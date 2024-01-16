#include "type.h"
#include "vmx.h"
#include "intel.h"
#include "vasm.h"
#include "msr.h"
#include "vmcs.h"
#include "handler.h"
#include "vmcall.h"
#include "winsys.h"
#include "debug.h"
#include "winfunc.h"
#include "pe64.h"
#include "std.h"
#include "ept.h"

uint64 OldSystemCall64;
PVT gvt;

uint64 IsSupportVT()
{
    uint64 arg[4] = {0};
    cpuid(1, 0, arg);

    if (!(arg[ECX] & CPUID_1_ECX_SUPPORT_VMX))
        return FALSE;

    uint64 msr = rdmsr(MSR_IA32_FEATURE_CONTROL);
    return ((PMSR_IA32_FEATURE_CONTROL_REGISTER)&msr)->Bits.Lock;
}
uint64 IsSupportRDTSCP()
{
    uint64 arg[4] = {0};
    cpuid(0x80000001, 0, arg);
    return (arg[EDX] & CPUID_80000001_EDX_SUPPORT_RDTSCP) ? TRUE : FALSE;
}
uint64 IsSupportINVPCID()
{
    uint64 arg[4] = {0};
    cpuid(7, 0, arg);
    return (arg[EBX] & CPUID_7_EBX_SUPPORT_INVPCID) ? TRUE : FALSE;
}
uint64 IsSupportXSAVE()
{
    uint64 arg[4] = {0};
    cpuid(1, 0, arg);
    if (arg[ECX] & CPUID_1_ECX_SUPPORT_XSAVE)
    {
        cpuid(0xD, 1, arg);
        if (arg[EAX] & CPUID_D_EAX_SUPPORT_XSAVE)
            return TRUE;
    }
    return FALSE;
}

/*

// uint64 IsEnablex2APIC(PVT vt)
// {
//     uint64 arg[4] = {0};
//     cpuid(1, 0, arg);

//     uint64 apic = rdmsr(0x1B);
//     uint8 xapic = 0, x2apic = 0;

//     if (arg[2] & CPUID_1_ECX_SUPPORT_X2APIC)
//         x2apic = (apic & MSR_1B_ENABLE_X2APIC) == 3 ? 1 : 0;

//     xapic = apic & MSR_1B_ENABLE_XAPIC ? 1 : 0;

//     vt->CpuAPICMode = xapic + x2apic;

//     return vt->CpuAPICMode;
// }

// uint64 IsEnableSMT(PVT vt)
// {
//     uint64 arg[4] = {0};

//     if (vt->CpuidMax > 0x1F)
//     {
//     }
//     else if (vt->CpuidMax > 0xB)
//     {
//         cpuid(0xB, 0, arg);
//         if (arg[2] & 0xFF00)
//         {
//             uint32 Mask_SMT_shift = arg[0] & 0xF;
//             uint32 SMT_MASK = ~((-1) << Mask_SMT_shift);
//             vt->CpuSMT = SMT_MASK;
//             return vt->CpuSMT;
//         }
//     }
//     return FALSE;
// }

// uint64 GetApicMsr(PVT vt)
// {
//     uint64 apic = rdmsr(0x1B);
//     vt->ApicMsr.Base = ((PIA32_APIC_BASE_MSR)&apic)->Base;
//     vt->ApicMsr.BSP = ((PIA32_APIC_BASE_MSR)&apic)->BSP;
//     vt->ApicMsr.x2APIC = ((PIA32_APIC_BASE_MSR)&apic)->x2APIC;
//     vt->ApicMsr.xAPIC = ((PIA32_APIC_BASE_MSR)&apic)->xAPIC;
//     return apic;
// }

// char *GetCpuName(PVT vt)
// {
//     uint64 arg[4] = {0};
//     uint64 arr[] = {0x80000002, 0x80000003, 0x80000004};
//     for (uint32 i = 0; i < sizeof(arr) / sizeof(uint64); i++)
//     {
//         cpuid(arr[i], 0, arg);
//         *((uint32 *)&vt->CpuName[i * 0x10 + 0x0]) = arg[0];
//         *((uint32 *)&vt->CpuName[i * 0x10 + 0x4]) = arg[1];
//         *((uint32 *)&vt->CpuName[i * 0x10 + 0x8]) = arg[2];
//         *((uint32 *)&vt->CpuName[i * 0x10 + 0xC]) = arg[3];
//     }
//     return vt->CpuName;
// }

// char *GetCpuSign(PVT vt)
// {
//     uint64 arg[4] = {0};
//     cpuid(0, 0, arg);
//     vt->CpuidMax = arg[0];

//     *((uint32 *)&vt->CpuSign[0]) = arg[1];
//     *((uint32 *)&vt->CpuSign[4]) = arg[3];
//     *((uint32 *)&vt->CpuSign[8]) = arg[2];

//     return vt->CpuSign;
// }

*/

uint64 GetSegInfo(PSEG seg, uint16 selector, uint64 gdtBase)
{
    PSELECTOR pSel = (PSELECTOR)&selector;
    uint32 tempBase = 0;
    if (!seg)
        return FALSE;
    if (!gdtBase)
        return FALSE;
    if (!pSel->Bits.Index)
        return FALSE;

    /*这一顿操作就是把GDT表的项，分解，组合，因为是历史遗留的原因，表项数据七零八落*/
    if (pSel->Bits.TI == 0)
    { // GDT
        seg->sel.value = selector;
        seg->descriptor = (PSEG_DESCRIPTOR)(gdtBase + (selector & ~0x7));

        tempBase = seg->descriptor->base0 | (seg->descriptor->base1 << 16) | (seg->descriptor->base2 << 24);
        if (!seg->descriptor->attr.Bits.S)
        {
            seg->Base = seg->descriptor->base3;
            seg->Base = seg->Base << 32;
        }
        seg->Base |= tempBase;

        seg->Limit = seg->descriptor->attr.Bits.limit1;
        seg->Limit = seg->Limit << 16;
        seg->Limit |= seg->descriptor->limit0;
        if (seg->descriptor->attr.Bits.G & seg->descriptor->attr.Bits.DB)
        {
            seg->Limit = (seg->Limit << 12) | 0xFFF;
        }
        else
        {
            seg->Limit &= 0xFFFF;
        }
    }
    else
    { // LDT
        DebugBreak("LDT");
        seg->sel.value = selector;
        seg->descriptor = (PSEG_DESCRIPTOR)(gdtBase + (selector & ~0x7));
        seg->Base = seg->descriptor->base3;
        seg->Base = seg->Base << 32;
        tempBase = seg->descriptor->base0 | (seg->descriptor->base1 << 16) | (seg->descriptor->base2 << 24);
        seg->Base |= tempBase;

        seg->Limit = seg->descriptor->attr.Bits.limit1;
        seg->Limit = seg->Limit << 16;
        seg->Limit |= seg->descriptor->limit0;
    }

    return TRUE;
}

uint64 SetGuestSeg(uint64 seg, uint16 selector, uint64 gdtBase)
{
    SEG TmpSeg = {0};
    uint64 ret = 0;
    GetSegInfo(&TmpSeg, selector, gdtBase);

    ret += vmx_write(GUEST_ES_SELECTOR + (seg * 2), selector & 0xFFF8);
    ret += vmx_write(GUEST_ES_BASE + (seg * 2), TmpSeg.Base);
    ret += vmx_write(GUEST_ES_LIMIT + (seg * 2), TmpSeg.Limit);
    ret += vmx_write(GUEST_ES_ACCESS_RIGHTS + (seg * 2),
                     TmpSeg.descriptor ? (TmpSeg.descriptor->attr.value) : 0x10000); //(&0xF0FF)?

    return ret;
}

uint64 SetControls(uint64 *value, uint64 msr)
{
    uint32 check = (uint32)*value;
    if ((check & (msr >> 32)) == check) // 该位能被设置成1
    {
        check |= msr; // 和必须设置成1值的位按位或
        *value = check;
        return TRUE;
    }
    return FALSE;
}

uint64 SetGuestState(uint64 GuestRip, uint64 GuestRsp)
{
    uint64 ret = 0;

    uint64 GdtBase = readBaseGDT();
    uint64 IdtBase = readBaseIDT();

    ret += vmx_write(GUEST_CR0, readCR0());
    ret += vmx_write(GUEST_CR3, readCR3());
    ret += vmx_write(GUEST_CR4, readCR4());
    ret += vmx_write(GUEST_DR7, readDR7());

    ret += SetGuestSeg(ES, readES(), GdtBase);
    ret += SetGuestSeg(FS, readFS(), GdtBase);
    ret += SetGuestSeg(DS, readDS(), GdtBase);
    ret += SetGuestSeg(CS, readCS(), GdtBase);
    ret += SetGuestSeg(SS, readSS(), GdtBase);
    ret += SetGuestSeg(GS, readGS(), GdtBase);
    ret += SetGuestSeg(TR, readTR(), GdtBase);
    ret += SetGuestSeg(LDTR, readLDTR(), GdtBase);

    ret += vmx_write(GUEST_FS_BASE, rdmsr(MSR_IA32_FS_BASE));
    ret += vmx_write(GUEST_GS_BASE, rdmsr(MSR_IA32_GS_BASE));
    ret += vmx_write(GUEST_GDTR_BASE, GdtBase);
    ret += vmx_write(GUEST_GDTR_LIMIT, readLimitGDT());
    ret += vmx_write(GUEST_IDTR_BASE, IdtBase);
    ret += vmx_write(GUEST_IDTR_LIMIT, readLimitIDT());

    ret += vmx_write(GUEST_RFLAGS, readrflags());
    ret += vmx_write(GUEST_RIP, GuestRip);
    ret += vmx_write(GUEST_RSP, GuestRsp);

    ret += vmx_write(GUEST_IA32_SYSENTER_CS, rdmsr(MSR_IA32_SYSENTER_CS));
    ret += vmx_write(GUEST_IA32_SYSENTER_ESP, rdmsr(MSR_IA32_SYSENTER_ESP));
    ret += vmx_write(GUEST_IA32_SYSENTER_EIP, rdmsr(MSR_IA32_SYSENTER_EIP));

    return ret;
}

uint64 SetHostState(uint64 HostRip, uint64 HostRsp)
{
    SEG seg = {0};
    uint64 ret = 0;
    uint64 GdtBase = readBaseGDT();
    uint64 IdtBase = readBaseIDT();
    uint64 TR = GetSegInfo(&seg, readTR(), GdtBase);

    ret += vmx_write(HOST_CR0, readCR0());
    ret += vmx_write(HOST_CR3, readCR3());
    ret += vmx_write(HOST_CR4, readCR4());

    ret += vmx_write(HOST_RIP, HostRip);
    ret += vmx_write(HOST_RSP, HostRsp);

    ret += vmx_write(HOST_CS_SELECTOR, readCS() & 0xF8);
    ret += vmx_write(HOST_SS_SELECTOR, readSS() & 0xF8);
    ret += vmx_write(HOST_DS_SELECTOR, readDS() & 0xF8);
    ret += vmx_write(HOST_ES_SELECTOR, readES() & 0xF8);
    ret += vmx_write(HOST_FS_SELECTOR, readFS() & 0xF8);
    ret += vmx_write(HOST_GS_SELECTOR, readGS() & 0xF8);
    ret += vmx_write(HOST_TR_SELECTOR, readTR() & 0xF8);

    ret += vmx_write(HOST_FS_BASE, rdmsr(MSR_IA32_FS_BASE));
    ret += vmx_write(HOST_GS_BASE, rdmsr(MSR_IA32_GS_BASE));
    ret += vmx_write(HOST_TR_BASE, TR ? seg.Base : 0);
    ret += vmx_write(HOST_GDTR_BASE, GdtBase);
    ret += vmx_write(HOST_IDTR_BASE, IdtBase);

    ret += vmx_write(HOST_IA32_SYSENTER_CS, rdmsr(MSR_IA32_SYSENTER_CS));
    ret += vmx_write(HOST_IA32_SYSENTER_ESP, rdmsr(MSR_IA32_SYSENTER_ESP));
    ret += vmx_write(HOST_IA32_SYSENTER_EIP, rdmsr(MSR_IA32_SYSENTER_EIP));

    return ret;
}

uint64 SetVmxExtend(uint8 cpunr)
{
    uint64 ret = 0;

    gvt->vm[cpunr].ExecptBitMap = 0;

    if (gvt->EnableEPT)
        gvt->vm[cpunr].ExecptBitMap |= 1 << 3;

    ret += vmx_write(EXCEPTION_BITMAP, gvt->vm[cpunr].ExecptBitMap);

    ret += vmx_write(VMCS_LINK_POINTER_FULL, ~0Ull);
    ret += vmx_write(VIRTUAL_PROCESSOR_IDENTIFIER, cpunr);

    ret += vmx_write(ADDRESS_OF_MSR_BITMAPS_FULL, (uint64)gvt->vm[cpunr].MsrBitMap.phy);

    if (gvt->EnableEPT)
        ret += vmx_write(EPT_POINTER_EPTP_FULL, gvt->Eptp.value);

    return ret;
}

uint64 SetVmxExitCTLS(uint8 cpunr, uint64 vmxctrl)
{
    uint64 ret = 0;

    MSR_IA32_VMX_EXIT_CTLS_REGISTER VmExit = {0}, SetExit = {0};
    VmExit.value = vmxctrl ? rdmsr(MSR_IA32_VMX_TRUE_EXIT_CTLS) : rdmsr(MSR_IA32_VMX_EXIT_CTLS);
    /*在这里设置《VmExit》*/
    SetExit.Bits->HOST_addr_size = TRUE;

    if (!SetControls(&SetExit.value, VmExit.value))
    {
        int3p("SetVmxExitCTLS");
        return 0xC1;
    }
    ret += vmx_write(PRIMARY_VM_EXIT_CONTROLS, SetExit.value);

    return ret;
}

uint64 SetVmxEntryCTLS(uint8 cpunr, uint64 vmxctrl)
{
    uint64 ret = 0;

    MSR_IA32_VMX_ENTRY_CTLS_REGISTER VmEntry = {0}, SetEntry = {0};
    VmEntry.value = vmxctrl ? rdmsr(MSR_IA32_VMX_TRUE_ENTRY_CTLS) : rdmsr(MSR_IA32_VMX_ENTRY_CTLS);
    /*在这里设置《VmEntry》*/
    SetEntry.Bits->Guest_IA32e = TRUE;

    if (!SetControls(&SetEntry.value, VmEntry.value))
    {
        int3p("SetVmxEntryCTLS");
        return 0xC2;
    }
    ret += vmx_write(VM_ENTRY_CONTROLS, SetEntry.value);

    return ret;
}

uint64 SetVmxExecutionCTLS(uint8 cpunr, uint64 vmxctrl)
{
    uint64 ret = 0;
    uint64 value = 0;

    MSR_IA32_VMX_PINBASED_CTLS_REGISTER PinBased = {0}, PinBaseSet = {0};
    MSR_IA32_VMX_PROCBASED_CTLS_REGISTER Primary = {0}, PrimarySet = {0};
    MSR_IA32_VMX_PROCBASED_CTLS2_REGISTER Secondry = {0}, SecondrySet = {0};
    MSR_IA32_VMX_PROCBASED_CTLS3_REGISTER Tertiary = {0};

    PinBased.value = vmxctrl ? rdmsr(MSR_IA32_VMX_TRUE_PINBASED_CTLS) : rdmsr(MSR_IA32_VMX_PINBASED_CTLS);
    /*在这里设置《PinBased》*/
    // PinBaseSet.Bits->ExIDT = TRUE;

    if (!SetControls(&PinBaseSet.value, PinBased.value))
    {
        int3p("SetVmxExecutionCTLS PinBaseSet", PinBaseSet.value, PinBased.value, 0);
        return 0xC3;
    }
    ret += vmx_write(PIN_BASED_VM_EXECUTION_CONTROLS, PinBaseSet.value);

    Primary.value = vmxctrl ? rdmsr(MSR_IA32_VMX_TRUE_PROCBASED_CTLS) : rdmsr(MSR_IA32_VMX_PROCBASED_CTLS);
    /*在这里设置《Primary》*/
    // PrimarySet.Bits->ExIDT = TRUE;

    PrimarySet.Bits->MSRmap = TRUE; // 如果为 FALSE，代表拦截所有MSR读写
    // PrimarySet.Bits->RDTSC = TRUE;
    PrimarySet.Bits->Secondary = TRUE;

    if (!SetControls(&PrimarySet.value, Primary.value))
    {
        int3p("SetVmxExecutionCTLS PrimarySet", PrimarySet.value, PrimarySet.value, 0);
        return 0xC4;
    }
    ret += vmx_write(PRIMARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS, PrimarySet.value);

    if (PrimarySet.Bits->Secondary)
    {
        Secondry.value = rdmsr(MSR_IA32_VMX_PROCBASED_CTLS2);

        /*在这里设置《Secondry》*/
        SecondrySet.Bits->XSAVES_XRSTORS = IsSupportXSAVE();
        SecondrySet.Bits->INVPCID = IsSupportINVPCID();
        SecondrySet.Bits->RDTSCP = IsSupportRDTSCP();

        SecondrySet.Bits->EPT = gvt->EnableEPT;

        // SecondrySet.Bits->VPID=TRUE;

        if (!SetControls(&SecondrySet.value, Secondry.value))
        {
            int3p("SetVmxExecutionCTLS SecondrySet", SecondrySet.value, Secondry.value, 0);

            return 0xC5;
        }

        ret += vmx_write(SECONDARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS, SecondrySet.value);
    }
    return ret;
}

uint64 SetVMXCS(uint8 cpunr, uint64 GuestRip, uint64 GuestRsp, uint64 HostRip, uint64 HostRsp, uint64 vmxctrl)
{
    if (SetVmxExecutionCTLS(cpunr, vmxctrl))
        return FALSE;
    if (SetVmxEntryCTLS(cpunr, vmxctrl))
        return FALSE;
    if (SetVmxExitCTLS(cpunr, vmxctrl))
        return FALSE;
    if (SetVmxExtend(cpunr))
        return FALSE;

    if (SetHostState(HostRip, HostRsp))
        return FALSE;
    if (SetGuestState(GuestRip, GuestRsp))
        return FALSE;

    return TRUE;
}

uint64 InitVmxCS(uint8 cpunr, uint32 RevisonId)
{
    *((uint32 *)gvt->vm[cpunr].VmxCS.vir) = RevisonId;

    if (vmx_clear(&gvt->vm[cpunr].VmxCS.phy))
        return FALSE;
    if (vmx_ptrld(&gvt->vm[cpunr].VmxCS.phy))
        return FALSE;

    return TRUE;
}

uint64 InitVmxON(uint8 cpunr, uint32 RevisonId)
{
    *((uint32 *)gvt->vm[cpunr].VmxON.vir) = RevisonId;

    if (vmx_on(&gvt->vm[cpunr].VmxON.phy))
        return FALSE;

    return TRUE;
}

uint64 StartVM(uint8 cpunr, uint64 GuestRip, uint64 GuestRsp)
{
    uint64 ret = 0;
    MSR_IA32_VMX_BASIC_REGISTER VmxBasic = {0};
    VmxBasic.value = rdmsr(MSR_IA32_VMX_BASIC);

    if (!InitVmxON(cpunr, VmxBasic.Bits.VmcsRevisonId))
    {
        int3p("InitVmxON");
        return FALSE;
    }
    if (!InitVmxCS(cpunr, VmxBasic.Bits.VmcsRevisonId))
    {
        int3p("InitVmxCS");
        return FALSE;
    }

    uint64 HostRip = (uint64)HostEntry;
    uint64 HostRsp = (uint64)gvt->vm[cpunr].Stack + STACK_SIZE;
    if (!SetVMXCS(cpunr, GuestRip, GuestRsp, HostRip, HostRsp, VmxBasic.Bits.VmxControls))
    {
        int3p("SetVMXCS");
        return FALSE;
    }
    // 此处如有返回值,代表出错,如果成功GuestRip已经被改变
    if (vmx_launch())
        int3p("vmx_launch error");

    return FALSE;
}

uint64 Efi_KipiStartVT(void *Context)
{
    PVT vt = Context;
    uint64 cpunr = getapicID();

    uint64 CR0 = readCR0();
    CR0 |= rdmsr(MSR_IA32_VMX_CR0_FIXED0);
    CR0 &= rdmsr(MSR_IA32_VMX_CR0_FIXED1);
    writeCR0(CR0);

    uint64 CR4 = readCR4();
    CR4 |= rdmsr(MSR_IA32_VMX_CR4_FIXED0);
    CR4 &= rdmsr(MSR_IA32_VMX_CR4_FIXED1);
    CR4 |= CR4_VMXE;
    writeCR4(CR4);

    uint64 BaseAddrVir = (uint64)vt->MemBaseVM.vir + (0x10 * PAGE_SIZE * cpunr);
    uint64 BaseAddrPhy = (uint64)vt->MemBaseVM.phy + (0x10 * PAGE_SIZE * cpunr);

    vt->vm[cpunr].VmxON.vir = (void *)(BaseAddrVir + PAGE_SIZE * 0);
    vt->vm[cpunr].VmxON.phy = (void *)(BaseAddrPhy + PAGE_SIZE * 0);

    vt->vm[cpunr].VmxCS.vir = (void *)(BaseAddrVir + PAGE_SIZE * 1);
    vt->vm[cpunr].VmxCS.phy = (void *)(BaseAddrPhy + PAGE_SIZE * 1);

    vt->vm[cpunr].MsrBitMap.vir = (void *)(BaseAddrVir + PAGE_SIZE * 2);
    vt->vm[cpunr].MsrBitMap.phy = (void *)(BaseAddrPhy + PAGE_SIZE * 2);

    vt->vm[cpunr].Stack = BaseAddrVir + PAGE_SIZE * 3;

    DebugBreak("StartVM", cpunr);

    if (!CallBackStartVM(StartVM, cpunr))
        int3p("StartVM is Fail...");

    return TRUE;
}

uint64 Efi_StartVT(PVT ospvt)
{
    if (!IsSupportVT())
        return FALSE;

    gvt = ospvt;

    InitOsApi(gvt, ospvt->Os.Data.kernelModule->DllBase);

    InitHandlerVmExit();
    InitHandlerVmCall();
    InitHandlerSystemService();

    gvt->Os.Api.KeIpiGenericCall(Efi_KipiStartVT, gvt);

    OldSystemCall64 = rdmsr(MSR_IA32_LSTAR);
    gvt->Os.Api.KeIpiGenericCall(KipiVmcall, (void *)VMCALL_HOOK_LSTAR);
    gvt->Os.Api.KeIpiGenericCall(KipiVmcall, (void *)VMCALL_HIDE_VMX);

    return FALSE;
}

uint64 Driver_KipiStartVT(void *Context)
{
    PVT vt = Context;
    uint64 cpunr = getapicID();

    uint64 CR0 = readCR0();
    CR0 |= rdmsr(MSR_IA32_VMX_CR0_FIXED0);
    CR0 &= rdmsr(MSR_IA32_VMX_CR0_FIXED1);
    writeCR0(CR0);

    uint64 CR4 = readCR4();
    CR4 |= rdmsr(MSR_IA32_VMX_CR4_FIXED0);
    CR4 &= rdmsr(MSR_IA32_VMX_CR4_FIXED1);
    CR4 |= CR4_VMXE;
    writeCR4(CR4);

    uint64 BaseAddrVir = (uint64)vt->MemBaseVM.vir + (0x10 * PAGE_SIZE * cpunr);
    uint64 BaseAddrPhy = (uint64)vt->Os.Api.MmGetPhysicalAddress((void *)BaseAddrVir);

    vt->vm[cpunr].VmxON.vir = (void *)(BaseAddrVir + PAGE_SIZE * 0);
    vt->vm[cpunr].VmxON.phy = vt->Os.Api.MmGetPhysicalAddress(vt->vm[cpunr].VmxON.vir);

    vt->vm[cpunr].VmxCS.vir = (void *)(BaseAddrVir + PAGE_SIZE * 1);
    vt->vm[cpunr].VmxCS.phy = vt->Os.Api.MmGetPhysicalAddress(vt->vm[cpunr].VmxCS.vir);

    vt->vm[cpunr].MsrBitMap.vir = (void *)(BaseAddrVir + PAGE_SIZE * 2);
    vt->vm[cpunr].MsrBitMap.phy = vt->Os.Api.MmGetPhysicalAddress(vt->vm[cpunr].MsrBitMap.vir);

    vt->vm[cpunr].Stack = BaseAddrVir + PAGE_SIZE * 3;

    DebugBreak("StartVM", cpunr);

    if (!CallBackStartVM(StartVM, cpunr))
        int3p("StartVM is Fail...");

    return TRUE;
}

uint64 Driver_StartVT(void *NtosKernelBase)
{
    if (!IsSupportVT())
        return FALSE;

    void *(*TempExAllocatePool2)();
    TempExAllocatePool2 = GetExportFunctionByName(NtosKernelBase, "ExAllocatePool2");

    gvt = TempExAllocatePool2(POOL_FLAG_NON_PAGED, sizeof(VT), 0x847586);

    InitOsApi(gvt, NtosKernelBase);
    gvt->vm = gvt->Os.Api.ExAllocatePool2(POOL_FLAG_NON_PAGED, sizeof(VM) * 0x100, 0x847588);

    uint64 VmBaseSize = 0x100 * PAGE_SIZE * 0x10;
    gvt->MemBaseVM.vir = gvt->Os.Api.MmAllocateContiguousMemorySpecifyCache(VmBaseSize, 0, MAXULONG64, 0, MmCached);
    if (!gvt->MemBaseVM.vir)
        int3p("Alloc MemBaseVM Error");
    gvt->MemBaseVM.phy = gvt->Os.Api.MmGetPhysicalAddress(gvt->MemBaseVM.vir);
    std_memset(gvt->MemBaseVM.vir, VmBaseSize, 0);

    if (IsSupportEPT())
    {
        uint64 EptSize = 0x205 * PAGE_SIZE;
        gvt->MemBaseEPT.vir = gvt->Os.Api.MmAllocateContiguousMemorySpecifyCache(EptSize, 0, MAXULONG64, 0, MmCached);
        if (!gvt->MemBaseEPT.vir)
            int3p("Alloc MemBaseEPT Error");
        gvt->MemBaseEPT.phy = gvt->Os.Api.MmGetPhysicalAddress(gvt->MemBaseEPT.vir);
        std_memset(gvt->MemBaseEPT.vir, EptSize, 0);

        gvt->Eptp.value = Driver_InitEpt(gvt);
        gvt->EnableEPT = TRUE;
    }

    InitHandlerVmExit();
    InitHandlerVmCall();
    InitHandlerSystemService();
    gvt->Os.Api.KeIpiGenericCall(Driver_KipiStartVT, gvt);
    OldSystemCall64 = rdmsr(MSR_IA32_LSTAR);
    gvt->Os.Api.KeIpiGenericCall(KipiVmcall, (void *)VMCALL_HOOK_LSTAR);
    gvt->Os.Api.KeIpiGenericCall(KipiVmcall, (void *)VMCALL_HIDE_VMX);

    return TRUE;
}


uint64 VmmEntry(PGUESTREG GuestRegs)
{
    GuestRegs->CpuIndex = getapicID();
    vmx_read(VM_EXIT_REASON, &GuestRegs->ExitReason);

    vmx_read(GUEST_RIP, &GuestRegs->GuestRip);
    vmx_read(GUEST_RSP, &GuestRegs->GuestRsp);
    vmx_read(GUEST_RFLAGS, &GuestRegs->GuestFlag);
    vmx_read(VM_EXIT_INSTRUCTION_LENGTH, &GuestRegs->InstrLen);

    GuestRegs->EProcess = PsGetCurrentProcess();
    GuestRegs->EThread = PsGetCurrentThread();

    return DispatchHandlerVmExit(GuestRegs);
}