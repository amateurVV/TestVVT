#include "type.h"
#include "wintype.h"
#include "disasm.h"
#include "vmx.h"
#include "msr.h"
#include "intel.h"
#include "std.h"
#include "hook.h"

typedef struct LIST
{
    struct LIST *pre;
    struct LIST *next;
} LIST, *PLIST;

typedef struct _DecodeList
{
    LIST list;
    DisInstr *instr;
    uint8 repair;
    uint8 insert;
    uint8 jnject;
    uint8 bits;
    uint64 id;
    uint64 jmpId;
    uint64 newAddr;
    uint64 jmpAddr;
    uint8 code[0x30];
} DecodeList;

#define IMME8 0
#define IMME16 0, 0
#define IMME32 0, 0, 0, 0
#define IMME64 0, 0, 0, 0, 0, 0, 0, 0

#define PUSH_RAX 0x50
#define PUSH_RCX 0x51
#define PUSH_RDX 0x52
#define PUSH_RBX 0x53
#define PUSH_RSP 0x54
#define PUSH_RBP 0x55
#define PUSH_RSI 0x56
#define PUSH_RDI 0x57

#define POP_RAX 0x58
#define POP_RCX 0x59
#define POP_RDX 0x5A
#define POP_RBX 0x5B
#define POP_RSP 0x5C
#define POP_RBP 0x5D
#define POP_RSI 0x5E
#define POP_RDI 0x5F

char code_jne_0F85[] = {0xE9, 0x0E, 0x00, 0x00, 0x00, IMME64, 0xFF, 0x25, 0xF2, 0xFF, 0xFF, 0xFF, 0x0F, 0x85, 0xF4, 0xFF, 0xFF, 0xFF};
char code_jne_0F84[] = {0xE9, 0x0E, 0x00, 0x00, 0x00, IMME64, 0xFF, 0x25, 0xF2, 0xFF, 0xFF, 0xFF, 0x0F, 0x84, 0xF4, 0xFF, 0xFF, 0xFF};
char code_jne_0F83[] = {0xE9, 0x0E, 0x00, 0x00, 0x00, IMME64, 0xFF, 0x25, 0xF2, 0xFF, 0xFF, 0xFF, 0x0F, 0x83, 0xF4, 0xFF, 0xFF, 0xFF};

char code_call_E8[] = {0xE9, 0x08, 0x00, 0x00, 0x00, IMME64, 0xFF, 0x15, 0xF2, 0xFF, 0xFF, 0xFF};
char code_jmp_E9[] = {0xE9, 0x08, 0x00, 0x00, 0x00, IMME64, 0xFF, 0x25, 0xF2, 0xFF, 0xFF, 0xFF};

char code_test_F605[] = {PUSH_RAX, 0x48, 0xB8, IMME64, 0xF6, 0x00, IMME8, POP_RAX};
char code_test_F705[] = {PUSH_RAX, 0x48, 0xB8, IMME64, 0xF7, 0x00, IMME32, POP_RAX};

char code_cmp_483B05[] = {PUSH_RCX, 0x48, 0xB9, IMME64, 0x48, 0x3B, 0x01, POP_RCX};
char code_cmp_483B35[] = {PUSH_RAX, 0x48, 0xB8, IMME64, 0x48, 0x3B, 0x30, POP_RAX};

char code_cmovnb_480F4305[] = {PUSH_RCX, 0x48, 0xB9, IMME64, 0x48, 0x0F, 0x43, 0x01, POP_RCX};
char code_cmovnb_480F4335[] = {PUSH_RAX, 0x48, 0xB8, IMME64, 0x48, 0x0F, 0x43, 0x30, POP_RAX};

char code_lea_4C8D15[] = {0x49, 0xBA, IMME64};
char code_lea_4C8D1D[] = {0x49, 0xBB, IMME64};
char code_lea_488D3D[] = {0x48, 0xBF, IMME64};

uint64 MarkRepairJmp(LIST *List)
{
    DecodeList *CodeList = (DecodeList *)List->next;
    while (CodeList != 0)
    {
        if (CodeList->repair)
        {
            /*如果是1字节跳转，替换成4字节跳转*/
            if ((CodeList->instr->DisHex.Op.Opcode[0] < 0x80) && (CodeList->instr->DisHex.Op.Opcode[0] >= 0x70))
            {
                char JccCode[] = {0x0F, 0, 0, 0, 0, 0};
                JccCode[1] = (CodeList->instr->DisHex.Op.Opcode[0] & 0x0F) + 0x80;
                JccCode[2] = CodeList->instr->DisHex.Disp->disp8;

                CodeList->instr->DisType.Arg->dispSize = 4;
                CodeList->instr->DisType.ctx.oplen = 2;
                CodeList->instr->Ex.instrLen = 6;

                CodeList->jnject = TRUE;
                CodeList->bits = sizeof(JccCode);
                std_memcpy(CodeList->code, JccCode, sizeof(JccCode));
            }

            DecodeList *TempList = (DecodeList *)List->next;
            while (TempList != 0)
            {
                if (CodeList->instr->Ex.DestAddr.u64 == TempList->instr->Ex.Rip.u64)
                {
                    CodeList->jmpId = TempList->id;
                    break;
                }
                else
                {
                    TempList = (DecodeList *)TempList->list.next;
                }
            }
        }
        CodeList = (DecodeList *)CodeList->list.next;
    }
    return TRUE;
}
uint64 InsertCode(DecodeList *List, uint8 *code, uint8 bits)
{
    List->jnject = TRUE;
    List->bits = bits;
    std_memcpy(List->code, code, bits);

    return TRUE;
}
uint64 RepairJmp(LIST *List)
{
    DecodeList *codelist = (DecodeList *)List->next;
    while (codelist != 0)
    {
        if (codelist->repair)
        {
            DecodeList *temp = (DecodeList *)List->next;
            while (temp != 0)
            {
                if (codelist->jmpId == temp->id)
                {
                    codelist->jmpAddr = temp->newAddr;
                    break;
                }
                temp = (DecodeList *)temp->list.next;
            }
            uint64 offset = codelist->jmpAddr - (codelist->newAddr + codelist->instr->Ex.instrLen);
            for (int i = 0; i < codelist->instr->DisType.ctx.argc; i++)
            {
                if (codelist->instr->DisType.Arg[i].use_disp)
                {
                    uint8 *addr = (uint8 *)codelist->newAddr +
                                  codelist->instr->DisType.ctx.oplen +
                                  codelist->instr->DisType.Flags.rex +
                                  codelist->instr->DisType.Flags.modrm +
                                  codelist->instr->DisType.Flags.sib;
                    std_memcpy(addr, (uint8 *)&offset, codelist->instr->DisType.Arg[i].dispSize);
                }
            }
        }

        codelist = (DecodeList *)codelist->list.next;
    }
    return TRUE;
}
uint64 InsertBinary(LIST *List)
{
    DecodeList *CodeList = (DecodeList *)List->next;

    while (CodeList != 0)
    {
        if (CodeList->insert)
        {
            uint8 op0 = *(uint8 *)(CodeList->instr->Ex.CodeRip.u64 + 0);
            uint8 op1 = *(uint8 *)(CodeList->instr->Ex.CodeRip.u64 + 1);
            uint8 op2 = *(uint8 *)(CodeList->instr->Ex.CodeRip.u64 + 2);
            uint8 op3 = *(uint8 *)(CodeList->instr->Ex.CodeRip.u64 + 3);

            switch (op0)
            {
            case 0xE8:
            {
                InsertCode(CodeList, code_call_E8, sizeof(code_call_E8));
                *(uint64 *)&CodeList->code[5] = CodeList->instr->Ex.DestAddr.u64;

                break;
            }
            case 0xE9:
            {
                InsertCode(CodeList, code_jmp_E9, sizeof(code_jmp_E9));
                *(uint64 *)&CodeList->code[5] = CodeList->instr->Ex.DestAddr.u64;
                break;
            }
            case 0x0F:
            {
                if (op1 == 0x85)
                {
                    InsertCode(CodeList, code_jne_0F85, sizeof(code_jne_0F85));
                    *(uint64 *)&CodeList->code[5] = CodeList->instr->Ex.DestAddr.u64;

                    break;
                }
                else if (op1 == 0x84)
                {
                    InsertCode(CodeList, code_jne_0F84, sizeof(code_jne_0F84));
                    *(uint64 *)&CodeList->code[5] = CodeList->instr->Ex.DestAddr.u64;

                    break;
                }
                else if (op1 == 0x83)
                {
                    InsertCode(CodeList, code_jne_0F83, sizeof(code_jne_0F83));
                    *(uint64 *)&CodeList->code[5] = CodeList->instr->Ex.DestAddr.u64;

                    break;
                }
                else
                {
                    DebugBreak("InsertBinary", __FUNCTION__, __LINE__);
                }
            }
            case 0xF6:
            {
                if (op1 == 0x05)
                {
                    InsertCode(CodeList, code_test_F605, sizeof(code_test_F605));
                    *(uint64 *)&CodeList->code[3] = CodeList->instr->Ex.DestAddr.u64;
                    for (int i = 0; i < CodeList->instr->DisType.ctx.argc; i++)
                    {
                        if (CodeList->instr->DisType.Arg[i].use_imme)
                        {
                            std_memcpy(&CodeList->code[13], &CodeList->instr->DisHex.Imme[i].imm64, CodeList->instr->DisType.Arg[i].immeSize);
                        }
                    }

                    break;
                }
                DebugBreak("InsertBinary", __FUNCTION__, __LINE__);
            }
            case 0xF7:
            {
                if (op1 == 0x05)
                {
                    InsertCode(CodeList, code_test_F705, sizeof(code_test_F705));
                    *(uint64 *)&CodeList->code[3] = CodeList->instr->Ex.DestAddr.u64;
                    for (int i = 0; i < CodeList->instr->DisType.ctx.argc; i++)
                    {
                        if (CodeList->instr->DisType.Arg[i].use_imme)
                        {
                            std_memcpy(&CodeList->code[13], &CodeList->instr->DisHex.Imme[i].imm64, CodeList->instr->DisType.Arg[i].immeSize);
                        }
                    }

                    break;
                }
                DebugBreak("InsertBinary", __FUNCTION__, __LINE__);
            }
            case 0x48:
            {
                if (op1 == 0x8D && op2 == 0x3D)
                {
                    InsertCode(CodeList, code_lea_488D3D, sizeof(code_lea_488D3D));
                    *(uint64 *)&CodeList->code[2] = CodeList->instr->Ex.DestAddr.u64;
                }
                else if (op1 == 0x3B && op2 == 0x05)
                {
                    InsertCode(CodeList, code_cmp_483B05, sizeof(code_cmp_483B05));
                    *(uint64 *)&CodeList->code[3] = CodeList->instr->Ex.DestAddr.u64;
                }
                else if (op1 == 0x3B && op2 == 0x35)
                {
                    InsertCode(CodeList, code_cmp_483B35, sizeof(code_cmp_483B35));
                    *(uint64 *)&CodeList->code[3] = CodeList->instr->Ex.DestAddr.u64;
                }
                else if (op1 == 0x0F && op2 == 0x43 && op3 == 0x05)
                {
                    InsertCode(CodeList, code_cmovnb_480F4305, sizeof(code_cmovnb_480F4305));
                    *(uint64 *)&CodeList->code[3] = CodeList->instr->Ex.DestAddr.u64;
                }
                else if (op1 == 0x0F && op2 == 0x43 && op3 == 0x35)
                {
                    InsertCode(CodeList, code_cmovnb_480F4335, sizeof(code_cmovnb_480F4335));
                    *(uint64 *)&CodeList->code[3] = CodeList->instr->Ex.DestAddr.u64;
                }
                else
                {
                    DebugBreak("InsertBinary", __FUNCTION__, __LINE__);
                }

                break;
            }
            case 0x4C:
            {
                if (op1 == 0x8D && op2 == 0x15)
                {
                    InsertCode(CodeList, code_lea_4C8D15, sizeof(code_lea_4C8D15));
                    *(uint64 *)&CodeList->code[2] = CodeList->instr->Ex.DestAddr.u64;
                }
                else if (op1 == 0x8D && op2 == 0x1D)
                {
                    InsertCode(CodeList, code_lea_4C8D1D, sizeof(code_lea_4C8D1D));
                    *(uint64 *)&CodeList->code[2] = CodeList->instr->Ex.DestAddr.u64;
                }
                else
                {
                    DebugBreak("InsertBinary", __FUNCTION__, __LINE__);
                }
                break;
            }
            default:
            {
                DebugBreak("InsertBinary", __FUNCTION__, __LINE__);
                break;
            }
            }
        }
        CodeList = (DecodeList *)CodeList->list.next;
    }
    return TRUE;
}
uint64 CopyBinary(LIST *List, void *buffer)
{
    char *str = buffer;
    int i = 0;

    DecodeList *codelist = (DecodeList *)List->next;

    while (codelist != 0)
    {
        codelist->newAddr = (uint64)&str[i];

        if (codelist->jnject)
        {
            std_memcpy(&str[i], codelist->code, codelist->bits);
            i += codelist->bits;
        }
        else
        {
            std_memcpy(&str[i], (uint8 *)codelist->instr->Ex.CodeRip.u64, codelist->instr->Ex.instrLen);
            i += codelist->instr->Ex.instrLen;
        }

        codelist = (DecodeList *)codelist->list.next;
    }
    return i;
}

int DecodeToList(LIST *List, uint64 startRIP, uint64 addr, uint64 disByte, uint8 bits)
{
    LIST *head = List;
    uint64 start = startRIP;
    int CodeByte = 0;
    int id = 0;
    while (1)
    {
        if (CodeByte > disByte)
            break;
        DecodeList *mContext = 0;
        DisInstr *mInstr = 0;

        while (1)
        {
            mContext = gvt->Os.Api.ExAllocatePool2(POOL_FLAG_NON_PAGED, sizeof(DecodeList), 0x236545);
            if (mContext)
                break;
        }
        while (1)
        {
            mInstr = gvt->Os.Api.ExAllocatePool2(POOL_FLAG_NON_PAGED, sizeof(DisInstr), 0x336545);
            if (mInstr)
                break;
        }
        mContext->instr = mInstr;
        char str[0x100] = {0};

        if (Decode(mInstr, start, 0, Bit64) == 0)
        {
            InstrToHex(mInstr);
            InstrToAsm(mInstr);
            if (mInstr->Ex.isAddr)
            {
                if (mInstr->Ex.DestAddr.u64 < startRIP || mInstr->Ex.DestAddr.u64 > (startRIP + disByte))
                {
                    mContext->insert = 1; // 标记需要替换代码的语句
                }
                else
                {
                    mContext->repair = 1; // 标记需要修正跳转的语句
                }
            }
        }
        if (*(uint16 *)mInstr->Ex.CodeRip.u64 == 0xD0FF) // FF D0 == call rax
        {
            // 此处可以把rax改成call函数,减轻VMM切换造成的损耗
            /*
            mov rax,3;这个是VmCall的处理函数编号
            vmcall
            mov rax,r10
            jmp save addr
            */
            char VmxCall[] = {
                0x48, 0xB8, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x0F, 0x01, 0xC1,
                0x49, 0x8B, 0xC2,
                0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
            *(uint64 *)&VmxCall[22] = start;

            mContext->id = id;
            mContext->insert = 0;
            mContext->repair = 0;
            mContext->jnject = TRUE;
            mContext->bits = sizeof(VmxCall);

            std_memcpy(mContext->code, VmxCall, sizeof(VmxCall));
            head->next = &mContext->list;
            mContext->list.pre = head;

            // SysCallReturnAddr = start;
            break;
        }
        if (((*(uint32 *)mInstr->Ex.CodeRip.u64) & 0xFFFFFF) == 0x158D4C) // lea r10,[addr];
        {
            // 如果要替换SSDT,修改此处R10
            /*if (!pSSDTAddr)
            {
                pSSDTAddr = mInstr->Ex.DestAddr.u64;
            }*/
        }
        if (((*(uint32 *)mInstr->Ex.CodeRip.u64) & 0xFFFFFF) == 0x1D8D4C) // lea r11,[addr]
        {
            // 如果要替换SSSDT,修改此处R11
            /*if (!pSSSDTAddr)
            {
                pSSSDTAddr = mInstr->Ex.DestAddr.u64;
            }*/
        }

        mContext->id = id++;
        CodeByte += mInstr->Ex.instrLen;
        start += mInstr->Ex.instrLen;
        addr += mInstr->Ex.instrLen;

        head->next = &mContext->list;
        mContext->list.pre = head;
        head = head->next;
    }
    return TRUE;
}
uint64 DeleteList(LIST *list)
{
    DecodeList *temp;
    list = list->next;
    while (list != 0)
    {
        temp = (DecodeList *)list;
        list = list->next;
        gvt->Os.Api.ExFreePool(temp);
    }
    return TRUE;
}

PVOID MakeSyscall64()
{
    uint64 SysCall64 = rdmsr(MSR_IA32_LSTAR);
    if (*(char *)(SysCall64 + 9) == 0x90)
    {
        DebugBreak("需要关闭KPTI");
        return NULL;
    }
    PVOID addr = std_FindCode((char *)SysCall64, 0x1000, "49 8B C2 FF D0");

    LIST list = {0};

    uint64 Rip = SysCall64;

    /*解码到LIST*/
    uint64 bits = ((uint64)addr + 5) - SysCall64;
    DecodeToList(&list, Rip, 0, bits, Bit64);

    /*标记需要修改的跳转*/
    MarkRepairJmp(&list);

    /*插入需要替换的二进制代码*/
    InsertBinary(&list);

    /*拷贝到新的可执行的非分页内存*/
    PVOID FuncSysCall = gvt->Os.Api.ExAllocatePool2(POOL_FLAG_NON_PAGED_EXECUTE, 0x1000, 0x32321123);
    uint64 bytes = CopyBinary(&list, FuncSysCall);

    /*修正跳转*/
    RepairJmp(&list);

    /*释放LIST*/
    DeleteList(&list);

    return FuncSysCall;
}
