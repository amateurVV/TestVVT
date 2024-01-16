#include "type.h"
#include "intel.h"
#include "msr.h"
#include "vmx.h"
#include "vasm.h"
#include "winfunc.h"
#include "winsys.h"
#include "wintype.h"
#include "vmcs.h"
#include "std.h"
#include "ept.h"

PLIST_EPT_HOOK_CONTEXT ListEptHook;
uint64 g_lock;

PEPT_HOOK_CONTEXT FindHookContext(void *HookAddrVir, void *EProcess)
{
    uint64 Cr3 = TargetProcessCR3(EProcess);
    void *HookAddrPhy = gvt->Os.Api.MmGetPhysicalAddress(HookAddrVir);
    writeCR3(Cr3);

    if (!HookAddrPhy)
        return NULL;

    PLIST_EPT_HOOK_CONTEXT Header = ListEptHook;
    if (Header)
    {
        PLIST_EPT_HOOK_CONTEXT element = Header->Flink;
        while (element != Header)
        {
            if (element->context->TargetCodeAddrPhy == HookAddrPhy)
                return element->context;
            element = element->Flink;
        }
    }
    return NULL;
}

PEPT_HOOK_PROCESS FindHookProcess(PEPT_HOOK_CONTEXT HookContext, void *EProcess)
{
    void *HookAddrPhy = HookContext->TargetCodeAddrPhy;

    PLIST_EPT_HOOK_PROCESS element = &HookContext->ListProcess;

    do
    {
        if (element->Process.Process == EProcess)
            return &element->Process;
        element = element->Next;
    } while (element);

    return NULL;
}

PEPT_HOOK_CONTEXT FindHookPage(void *HookAddrVir, void *EProcess)
{
    uint64 Cr3 = TargetProcessCR3(EProcess);
    uint64 HookAddrPage = (uint64)gvt->Os.Api.MmGetPhysicalAddress(HookAddrVir) >> 12;
    writeCR3(Cr3);

    if (!HookAddrPage)
        return NULL;

    PLIST_EPT_HOOK_CONTEXT Header = ListEptHook;
    if (Header)
    {
        PLIST_EPT_HOOK_CONTEXT element = Header->Flink;

        while (element != Header)
        {
            uint64 ContextPage = (uint64)element->context->TargetCodeAddrPhy >> 12;
            if (ContextPage == HookAddrPage)
                return element->context;
            element = element->Flink;
        }
    }
    return NULL;
}

uint64 InsertHookProcess(PEPT_HOOK_CONTEXT context, PLIST_EPT_HOOK_PROCESS ListProcess)
{
    ListProcess->Next = context->ListProcess.Next;
    context->ListProcess.Next = ListProcess;
    return TRUE;
}

uint64 InsertHookContext(PEPT_HOOK_CONTEXT context)
{
    PLIST_EPT_HOOK_CONTEXT Header = ListEptHook;
    if (Header)
    {
        PLIST_EPT_HOOK_CONTEXT element = gvt->Os.Api.ExAllocatePool2(POOL_FLAG_NON_PAGED, sizeof(LIST_EPT_HOOK_CONTEXT), TAG_HOOK_LIST);
        if (element)
        {
            element->context = context;
            while (InterlockedCmpExchange64(&g_lock, 1, 0))
                ; // 空转
            element->Blink = Header->Blink;
            element->Flink = Header;
            Header->Blink->Flink = element;
            Header->Blink = element;
            InterlockedCmpExchange64(&g_lock, 0, 1);
            return TRUE;
        }
    }
    else
    {
        ListEptHook = gvt->Os.Api.ExAllocatePool2(POOL_FLAG_NON_PAGED, sizeof(LIST_EPT_HOOK_CONTEXT), TAG_HOOK_LIST);
        ListEptHook->Blink = ListEptHook->Flink = ListEptHook;
        InsertHookContext(context);
    }

    return FALSE;
}

uint64 IsSupportEPT()
{
    ULONG64 EptVpidCap = rdmsr(MSR_IA32_VMX_EPT_VPID_CAP);

    uint8 isExecuteOnly = (EptVpidCap & EPT_EXECUTE_ONLY) ? 1 : 0;
    uint8 isLevel4 = (EptVpidCap & EPT_PAGE_WALK_4) ? 1 : 0;

    return isExecuteOnly && isLevel4;
}

uint64 Os_InitEpt(PVT vt)
{
    PVMX_EPT_PAGES VirMemEPT = (void *)vt->MemBaseEPT.vir;
    PVMX_EPT_PAGES PhyMemEPT = (void *)vt->MemBaseEPT.phy;

    ULONG64 EptVpidCap = rdmsr(MSR_IA32_VMX_EPT_VPID_CAP);

    ULONG MemoryType = (EptVpidCap & EPT_WRITE_BACK) ? 6 : 0;
    ULONG Dirty = (EptVpidCap & EPT_SUPPORT_DIRTY) ? 1 : 0;

    VirMemEPT->pml4e[0].value = 0;
    VirMemEPT->pml4e[0].Attribute = EPT_ACCESS_ALL;
    VirMemEPT->pml4e[0].PageFrame = (uint64)&PhyMemEPT->pdpte[0] >> 12;

    for (int IndexPDE = 0; IndexPDE < PDE_COUNT; IndexPDE++)
    {
        VirMemEPT->pdpte[IndexPDE].value = 0;
        VirMemEPT->pdpte[IndexPDE].Attribute = EPT_ACCESS_ALL;
        VirMemEPT->pdpte[IndexPDE].PageFrame = (uint64)&PhyMemEPT->pde[IndexPDE] >> 12;

        for (int IndexPTE = 0; IndexPTE < PTE_COUNT; IndexPTE++)
        {

            VirMemEPT->pde[IndexPDE][IndexPTE].value = 0;
            VirMemEPT->pde[IndexPDE][IndexPTE].s.Attribute = EPT_ACCESS_ALL;
            VirMemEPT->pde[IndexPDE][IndexPTE].s.PageFrame2MB = IndexPDE * PTE_COUNT + IndexPTE;
            VirMemEPT->pde[IndexPDE][IndexPTE].s.MemoryType = MemoryType;
            VirMemEPT->pde[IndexPDE][IndexPTE].s.LargePage = TRUE;
        }
    }

    EPTP eptp = {0};
    eptp.PML4E = (uint64)vt->MemBaseEPT.phy >> 12;
    eptp.MemoryType = MemoryType;
    eptp.PageWalk = 3;
    eptp.Dirty = Dirty;

    DebugBreak("InitEpt Done", eptp);
    return eptp.value;
}

uint64 Driver_InitEpt(PVT vt)
{
    PVMX_EPT_PAGES VirMemEPT = (void *)vt->MemBaseEPT.vir;
    PVMX_EPT_PAGES PhyMemEPT = (void *)vt->MemBaseEPT.phy;

    ULONG64 EptVpidCap = rdmsr(MSR_IA32_VMX_EPT_VPID_CAP);

    ULONG MemoryType = (EptVpidCap & EPT_WRITE_BACK) ? 6 : 0;
    ULONG Dirty = (EptVpidCap & EPT_SUPPORT_DIRTY) ? 1 : 0;

    VirMemEPT->pml4e[0].value = 0;
    VirMemEPT->pml4e[0].Attribute = EPT_ACCESS_ALL;
    VirMemEPT->pml4e[0].PageFrame = ((uint64)vt->Os.Api.MmGetPhysicalAddress(&VirMemEPT->pdpte[0])) >> 12;

    for (int IndexPDE = 0; IndexPDE < PDE_COUNT; IndexPDE++)
    {
        VirMemEPT->pdpte[IndexPDE].value = 0;
        VirMemEPT->pdpte[IndexPDE].Attribute = EPT_ACCESS_ALL;
        VirMemEPT->pdpte[IndexPDE].PageFrame = ((uint64)vt->Os.Api.MmGetPhysicalAddress(&VirMemEPT->pde[IndexPDE])) >> 12;

        for (int IndexPTE = 0; IndexPTE < PTE_COUNT; IndexPTE++)
        {

            VirMemEPT->pde[IndexPDE][IndexPTE].value = 0;
            VirMemEPT->pde[IndexPDE][IndexPTE].s.Attribute = EPT_ACCESS_ALL;
            VirMemEPT->pde[IndexPDE][IndexPTE].s.PageFrame2MB = IndexPDE * PTE_COUNT + IndexPTE;
            VirMemEPT->pde[IndexPDE][IndexPTE].s.MemoryType = MemoryType;
            VirMemEPT->pde[IndexPDE][IndexPTE].s.LargePage = TRUE;
        }
    }

    EPTP eptp = {0};
    eptp.PML4E = ((uint64)vt->Os.Api.MmGetPhysicalAddress(&VirMemEPT->pml4e[0])) >> 12;
    eptp.MemoryType = MemoryType;
    eptp.PageWalk = 3;
    eptp.Dirty = Dirty;

    DebugBreak("InitEpt Done", eptp);
    return eptp.value;
}

uint64 Efi_InitEpt(PVT vt)
{
    PVMX_EPT_PAGES MemEPT = (void *)vt->MemBaseEPT.phy;

    ULONG64 EptVpidCap = rdmsr(MSR_IA32_VMX_EPT_VPID_CAP);

    ULONG MemoryType = (EptVpidCap & EPT_WRITE_BACK) ? 6 : 0;
    ULONG Dirty = (EptVpidCap & EPT_SUPPORT_DIRTY) ? 1 : 0;

    MemEPT->pml4e[0].value = 0;
    MemEPT->pml4e[0].Attribute = EPT_ACCESS_ALL;
    MemEPT->pml4e[0].PageFrame = ((uint64)&MemEPT->pdpte[0]) >> 12;

    for (int IndexPDE = 0; IndexPDE < PDE_COUNT; IndexPDE++)
    {
        MemEPT->pdpte[IndexPDE].value = 0;
        MemEPT->pdpte[IndexPDE].Attribute = EPT_ACCESS_ALL;
        MemEPT->pdpte[IndexPDE].PageFrame = ((uint64)&MemEPT->pde[IndexPDE]) >> 12;

        for (int IndexPTE = 0; IndexPTE < PTE_COUNT; IndexPTE++)
        {
            MemEPT->pde[IndexPDE][IndexPTE].value = 0;
            MemEPT->pde[IndexPDE][IndexPTE].s.Attribute = EPT_ACCESS_ALL;
            MemEPT->pde[IndexPDE][IndexPTE].s.PageFrame2MB = IndexPDE * PTE_COUNT + IndexPTE;
            MemEPT->pde[IndexPDE][IndexPTE].s.MemoryType = MemoryType;
            MemEPT->pde[IndexPDE][IndexPTE].s.LargePage = TRUE;
        }
    }

    EPTP eptp = {0};
    eptp.PML4E = (uint64)vt->MemBaseEPT.phy >> 12;
    eptp.MemoryType = MemoryType;
    eptp.PageWalk = 3;
    eptp.Dirty = Dirty;

    return eptp.value;
}

PEPDE EptGetGpaPDE(PADDR_PACK GPA)
{
    DebugBreak("EptGetGpaPDE", GPA);
    PVMX_EPT_PAGES EptBase = (void *)gvt->MemBaseEPT.vir;
    if (GPA->pml4e > 0)
        return NULL;

    return &EptBase->pde[GPA->pdpte][GPA->pde];
}

PEPTE EptGetGpaPTE(PADDR_PACK GPA)
{
    DebugBreak("EptGetGpaPTE", GPA);
    PVMX_EPT_PAGES EptBase = (void *)gvt->MemBaseEPT.vir;
    if (GPA->pml4e > 0)
        return NULL;

    PEPDE pde = EptGetGpaPDE(GPA);
    if (pde->s.LargePage)
        return NULL;
    uint64 page = pde->PageFrame * PAGE_SIZE;
    PEPTE pte = gvt->Os.Api.MmGetVirtualForPhysical((void *)page);

    return &pte[GPA->pte];
}

uint64 EptSplitPde(PEPDE pde, PSMEMORY pte)
{
    DebugBreak("EptSplitPde", pde);
    if (!pde->s.LargePage)
        return NULL;

    pte->vir = gvt->Os.Api.ExAllocatePool2(POOL_FLAG_NON_PAGED_EXECUTE, PAGE_SIZE, TAG_NEW_PAGE);
    pte->phy = gvt->Os.Api.MmGetPhysicalAddress(pte->vir);

    PEPTE tempPTE = pte->vir;
    for (int IndexPTE = 0; IndexPTE < PTE_COUNT; IndexPTE++)
    {
        tempPTE[IndexPTE].Attribute = EPT_ACCESS_ALL;
        tempPTE[IndexPTE].MemoryType = pde->s.MemoryType;
        tempPTE[IndexPTE].PageFrame4KB = (pde->s.PageFrame2MB << 9) + IndexPTE;
    }
    pde->value = 0;
    pde->PageFrame = (uint64)pte->phy >> 12;
    pde->Attribute = EPT_ACCESS_ALL;

    vmx_invept(2, &gvt->Eptp.value);

    return TRUE;
}

/// @brief 处理Hook触发时的断点
/// @return TRUE:命中断并处理成功，FALSE:未命中断点
uint64 EptHandlerBreakPoint(PGUESTREG GuestRegs)
{
    PEPT_HOOK_CONTEXT context = FindHookContext((void *)GuestRegs->GuestRip, GuestRegs->EProcess);
    if (!context)
        return FALSE;

    PEPT_HOOK_PROCESS hasProcess = &context->ListProcess.Process;
    if (hasProcess->Process != GuestRegs->EProcess)
    {
        hasProcess = FindHookProcess(context, GuestRegs->EProcess);
        if (!hasProcess)
        {
            uint64 CR3 = TargetProcessCR3(GuestRegs->EProcess);

            PLIST_EPT_HOOK_PROCESS ListProcess = gvt->Os.Api.ExAllocatePool2(POOL_FLAG_NON_PAGED_EXECUTE, sizeof(LIST_EPT_HOOK_PROCESS), TAG_HOOK_LIST);
            hasProcess = &ListProcess->Process;

            PSHELLCODE pShellCode = 0;
            SIZE_T CodeSize = sizeof(SHELLCODE);

            if (NT_SUCCESS(gvt->Os.Api.ZwAllocateVirtualMemory(NtCurrentProcess(), (void*)&pShellCode, 0, &CodeSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE)))
            {
                ULONG bits = 0;
                std_memcpy(pShellCode, &context->ShellCode, sizeof(SHELLCODE));
            }
            else
            {
                int3p("ZwAllocateVirtualMemory Error");
            }

            hasProcess->Process = GuestRegs->EProcess;
            hasProcess->RetAddr = &pShellCode->SaveCode;
            hasProcess->HookerEngine = &pShellCode->Engine;
            InsertHookProcess(context, ListProcess);
        }
    }

    uint64 CR3 = TargetProcessCR3(GuestRegs->EProcess);

    uint64 rsp;
    vmx_read(GUEST_RSP, &rsp);
    rsp -= 8;
    *(uint64 *)rsp = (uint64)hasProcess->RetAddr;
    rsp -= 8;
    *(uint64 *)rsp = (uint64)GuestRegs->rax;
    vmx_write(GUEST_RSP, rsp);
    GuestRegs->rax = (uint64)context->HookCodeAddr;
    vmx_write(GUEST_RIP, (uint64)hasProcess->HookerEngine);

    return TRUE;
}

uint64 EptHook(PEPT_HOOK_CONTEXT HookContext)
{
    uint64 CR3 = TargetProcessCR3(HookContext->ListProcess.Process.Process);
    uint64 DstCodePhyAddr = (uint64)gvt->Os.Api.MmGetPhysicalAddress(HookContext->TargetCodeAddrVir);
    writeCR3(CR3);

    PEPDE DestPDE = EptGetGpaPDE((PADDR_PACK)&DstCodePhyAddr);

    if (DestPDE->s.LargePage)
        EptSplitPde(DestPDE, &HookContext->PTE);

    PEPTE DestPTE = EptGetGpaPTE((PADDR_PACK)&DstCodePhyAddr);

    if (DestPTE)
    {
        HookContext->TargetCodeAddrPhy = (void *)DstCodePhyAddr;
        DebugBreak("InsertHookContext", DstCodePhyAddr, DestPTE, HookContext);

        InsertHookContext(HookContext);

        DestPTE->Attribute = EPT_EXECUTE;
        DestPTE->PageFrame4KB = (uint64)gvt->Os.Api.MmGetPhysicalAddress(HookContext->NewPage) >> 12;

        vmx_invept(2, &gvt->Eptp.value);
    }

    return TRUE;
}
