#include "pe64.h"
#include "hook.h"
#include "std.h"

// /***************************
//  * @brief 字符串转十六进制数组
//  * @param code IN 字符串
//  * @param pHex OUT 十六进制数组
//  * @return 成功-返回长度,失败-返回NULL
//  ***************************/
// int StrToBinary(char *code, char *pHex)
// {
//     int len = 0;
//     char *pcode = code;
//     char *pstr = 0;
//     while (*pcode)
//     {
//         if (*pcode == ' ')
//         {
//             pcode++;
//             continue;
//         }
//         else
//         {
//             pstr = pcode;
//             char byte[2] = {0};
//             for (int i = 0; i < 2; i++)
//             {
//                 if (*pstr >= '0' && *pstr <= '9')
//                     byte[i] = (*pstr - '0');
//                 else if (*pstr >= 'A' && *pstr <= 'F')
//                     byte[i] = (*pstr - 'A' + 0xA);
//                 else if (*pstr >= 'a' && *pstr <= 'f')
//                     byte[i] = (*pstr - 'a' + 0xA);
//                 else if (*pstr == '?' || *pstr == '*')
//                 {
//                     byte[0] = 0x0C;
//                     byte[1] = 0x0C;
//                     break;
//                 }
//                 else
//                 {
//                     return FALSE;
//                 }
//                 pstr++;
//             }
//             pHex[len++] = (byte[0] << 4) + byte[1];
//             pcode += 2;
//         }
//     }
//     return len;
// }

// /***************************
//  * @brief 查找特征码
//  * @param Base IN 要查找的内存起始位置
//  * @param size IN 要查找的内存大小
//  * @param code IN 特征码字符串
//  * @return 成功-返回地址,失败-返回 NULL
//  ***************************/
// void *std_FindCode(char *Base, uint64 size, char *code)
// {
//     int len = 0, index = 0;
//     char universal = 0xCC;
//     char hex[0x40] = {0};
//     char *pHex = hex;

//     len = StrToBinary(code, pHex);

//     if (len)
//     {
//         while (index < size)
//         {
//             if (Base[index] == hex[0])
//             {
//                 int i = 0;
//                 char *pTemp = Base + index;
//                 while (pTemp[i] == hex[i])
//                 {
//                     i++;
//                     while (hex[i] == universal)
//                         i++;

//                     if (i >= len)
//                     {
//                         return pTemp;
//                     }
//                 }
//             }
//             index++;
//         }
//     }

//     return NULL;
// }

void OffsetHook(PHOOKCONTEXT pHook)
{
    // 取出原来的偏移值
    uint32 offset = *(uint32 *)pHook->HookAddr;

    // 保存原来的偏移值
    *(uint32 *)pHook->SaveCode = offset;
    //(L"offset:%x32\r\n", offset);

    // 计算修改前指向的地址,以便调用原来的函数
    pHook->OriFunc = (pHook->HookAddr + pHook->HookByte + offset);
    //(L"StartBoot.HookAddr:%x64\r\n", pHook->OriFunc);

    ////(L"My:%x64,Os:%x64\r\n", pHook->HookFunc, (uint64)pHook->HookAddr + pHook->HookByte);

    *(uint32 *)pHook->HookAddr = (uint32)((uint64)pHook->HookFunc - ((uint64)pHook->HookAddr + pHook->HookByte));
    //(L"Hooked offset:%x32\r\n", *(uint64 *)pHook->HookAddr);

    pHook->IsHooked = TRUE;
}

void OffsetUnHook(PHOOKCONTEXT pHook)
{
    // 执行UnHook修改偏移值
    *(uint32 *)pHook->HookAddr = *(uint32 *)pHook->SaveCode;
    //(L"UnHook offset:%x32\r\n", *(uint64 *)pHook->HookAddr);

    pHook->IsHooked = FALSE;
}

void InlineHook(PHOOKCONTEXT pHook)
{
    // 将代码字符串转为十六进制代码
    char HookCode[0x40] = {0};
    char *pHex = HookCode;

    pHook->HookByte = StrToBinary(pHook->HookCode, pHex);

    if (!pHook->HookByte)
    {
        return;
    }

    // 保存原来的代码
    std_memcpy(pHook->SaveCode, pHook->HookAddr, pHook->HookByte);

    // 修改hook代码,把hook函数地址填充进十六进制代码
    *((uint64 *)&HookCode[6]) = (uint64)pHook->HookFunc;

    // 执行Hook修改内存代码
    std_memcpy(pHook->HookAddr, HookCode, pHook->HookByte);

    // 记录下原函数地址
    pHook->OriFunc = pHook->HookAddr;

    pHook->IsHooked = TRUE;
}

void InlineUnHook(PHOOKCONTEXT pHook)
{
    // 还原Hook前的代码
    std_memcpy(pHook->HookAddr, pHook->SaveCode, pHook->HookByte);

    pHook->IsHooked = FALSE;
}

void Hook(PHOOKCONTEXT pHook)
{
    if (pHook->IsHooked)
        return;
    if (pHook->HookType == HOOK_TYPE_OFFSET)
        OffsetHook(pHook);
    if (pHook->HookType == HOOK_TYPE_INLINE)
        InlineHook(pHook);
}
void UnHook(PHOOKCONTEXT pHook)
{
    if (!pHook->IsHooked)
        return;
    if (pHook->HookType == HOOK_TYPE_OFFSET)
        OffsetUnHook(pHook);
    if (pHook->HookType == HOOK_TYPE_INLINE)
        InlineUnHook(pHook);
}