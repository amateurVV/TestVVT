#pragma once
#include "type.h"

#define IAT_HOOK 1
#define INLINE_HOOK 2

enum HOOK_TYPE
{
    HOOK_TYPE_INLINE,
    HOOK_TYPE_OFFSET,
    HOOK_TYPE_IAT,
};

typedef struct HOOKDATA
{
    char *HookAddr;      // 要hook的函数地址 (在IatHook下保存着callback,回到原先的调用)
    char *HookCode;      // 要替换的代码
    char *SaveCode;      // 保存原来的代码
    void *HookFunc;      // 想要执行的函数地址
    uint16 HookByte;     // hook的字节数
    uint16 HookType;     // hook的类型,inline 或 offset
    uint16 IsHooked;     // hook的标志位
    uint16 Offset;       // 替换的代码的字节起始地址,得到地址后填写
    void *FuncForReturn; // 给IATHook专用返回地址
} HOOKDATA, *PHOOKDATA;

typedef struct _HOOKCONTEXT
{
    char *Binary;
    char *HookCode;
    char *HookAddr;
    void *HookFunc;
    void *OriFunc;
    uint16 HookByte;
    uint16 HookType;
    uint16 IsHooked;
    char SaveCode[0x40];

} HOOKCONTEXT, *PHOOKCONTEXT;

static HOOKCONTEXT StartBoot =
    {"48 8B C4 48 89 58 ?? 44 89 40 ?? 48 89 50 ?? 48 89 48 ?? 55 56 57 41 54 41 55 41 56 41 57 48 8D 68 A9 48 81 EC ?? ?? ?? ?? 48 8B",
     "FF 25 00 00 00 00 11 22 33 44 55 66 77 88"};
static HOOKCONTEXT CiOptions = {"89 0D ?? ?? ?? ?? 49 8B D8 48 8B F2 44 8B F1 48 FF 15 ?? ?? ?? ?? 0F 1F 44 00 00 48 89 05"};
static HOOKCONTEXT SwitchContext = {"40 53 48 83 EC 20 48 8B 15 ?? ?? ?? ?? 48 8D 05 ?? ?? ?? ?? 83 F9 01 48 8D 1D ?? ?? ?? ?? 48 0F 45 D8 39 0A"};
static HOOKCONTEXT LoaderBlock = {"48 8B EC 48 83 EC ?? 8B 35 ?? ?? ?? ?? ?? ?? ?? 48 8B 3D"};
static HOOKCONTEXT StartFirst = {"48 89 5C 24 ?? 55 56 57 41 56 41 57 48 8D 6C 24 ?? 48 81 EC ?? ?? ?? ?? 45 33 FF 48 8D 4D"};

static char KeInitAmd64SpecificStateBinary[] = {
    0x48, 0x83, 0xEC, '*', 0x0F, 0xAE, 0xE8, 0x83, 0x3D, '*', '*', '*', '*', 0x00, 0x0F, 0x85, '*', '*', '*', '*'};

// static HOOKCONTEXT StartFirst = {"33 C9 E8 ?? ?? ?? ?? B9 04 00 00 00 E8"};//KeInitSystem,调用后已经清空了kernelModule

void Hook(PHOOKCONTEXT pHook);
void UnHook(PHOOKCONTEXT pHook);

// void *std_FindCode(char *Base, uint64 size, char *binary);

/*  CiOptions
89 0D D3 45 FF FF                       mov     cs:g_CiOptions, ecx
49 8B D8                                mov     rbx, r8
48 8B F2                                mov     rsi, rdx
44 8B F1                                mov     r14d, ecx
48 FF 15 DB C2 FF FF                    call    cs:__imp_PsGetCurrentProcess
0F 1F 44 00 00                          nop     dword ptr [rax+rax+00h]
48 89 05 F7 45 FF FF                    mov     cs:g_CiSystemProcess, rax
*/
/*  SwitchContext BlpArchSwitchContext
40 53                                   push    rbx
48 83 EC 20                             sub     rsp, 20h
48 8B 15 5B EE 1B 00                    mov     rdx, cs:CurrentExecutionContext
48 8D 05 B4 EE 1B 00                    lea     rax, ApplicationExecutionContext
83 F9 01                                cmp     ecx, 1
48 8D 1D 6A EE 1B 00                    lea     rbx, FirmwareExecutionContext
48 0F 45 D8                             cmovnz  rbx, rax
39 0A                                   cmp     [rdx], ecx
74 20                                   jz      short loc_18002D1FE
48 83 3D CA ED 1B 00 00                 cmp     cs:EfiBS, 0
75 07                                   jnz     short loc_18002D1EF
B9 30 00 00 00                          mov     ecx, 30h ; '0'
CD 29                                   int     29h             ; Win8: RtlFailFast(ecx)
48 8B CB                                mov     rcx, rbx
E8 1D 01 00 00                          call    ArchSwitchContext
48 89 1D 22 EE 1B 00                    mov     cs:CurrentExecutionContext, rbx
48 83 C4 20                             add     rsp, 20h
5B                                      pop     rbx
C3                                      retn
CC                                      db 0CCh
*/
/*  LoaderBlock OslInitializeLoaderBlock
48 8B EC                                mov     rbp, rsp
48 83 EC 40                             sub     rsp, 40h
8B 35 05 79 19 00                       mov     esi, cs:OslSystemHiveHandle
44 8B F1                                mov     r14d, ecx
48 8B 3D 8F A5 1D 00                    mov     rdi, cs:OslLoaderBlock
33 D2                                   xor     edx, edx
48 8B CF                                mov     rcx, rdi
*/
/*  StartFirst StartFirstUserProcess WIN10
48 89 5C 24 18                          mov     [rsp-8+arg_10], rbx
55                                      push    rbp
56                                      push    rsi
57                                      push    rdi
41 56                                   push    r14
41 57                                   push    r15
48 8D 6C 24 C9                          lea     rbp, [rsp-37h]
48 81 EC B0 00 00 00                    sub     rsp, 0B0h
45 33 FF                                xor     r15d, r15d
48 8D 4D C7                             lea     rcx, [rbp+57h+var_90]
*/

/*
48 8B C4                                mov     rax, rsp
48 89 58 20                             mov     [rax+20h], rbx
44 89 40 18                             mov     [rax+18h], r8d
48 89 50 10                             mov     [rax+10h], rdx
48 89 48 08                             mov     [rax+8], rcx
55                                      push    rbp
56                                      push    rsi
57                                      push    rdi
41 54                                   push    r12
41 55                                   push    r13
41 56                                   push    r14
41 57                                   push    r15
48 8D 68 A9                             lea     rbp, [rax-57h]
48 81 EC C0 00 00 00                    sub     rsp, 0C0h
48 8B F1                                mov     rsi, rcx
*/
