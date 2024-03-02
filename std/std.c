#include "std.h"

wchar HexWchar[0x10] = L"0123456789ABCDEF";

typedef struct SARG
{
    uint32 strlen;
    uint32 size;
    wchar str[0x10];
} SARG;

SARG sArg[] = {
    {3, 8, L"x64"},
    {3, 4, L"x32"},
    {3, 2, L"x16"},
    {3, 1, L"x08"},
};

/***************************
 * @brief 查找字符串
 * @param str1 被查找的字符串
 * @param str2 字符串
 * @return 相同=TRUE,不同=FALSE
 ***************************/
uint32 cstrstr(char *str1, char *str2)
{
    while (*str1)
    {
        char *pstr1 = str1;
        char *pstr2 = str2;
        while (*pstr1 && *pstr2 && (*pstr1 == *pstr2))
        {
            pstr1++;
            pstr2++;
        }
        if (*pstr2 == '\0')
        {
            return TRUE;
        }
        str1++;
    }
    return FALSE;
}
/***************************
 * @brief 查找字符串
 * @param str1 被查找的字符串
 * @param str2 字符串
 * @return 相同=TRUE,不同=FALSE
 ***************************/
uint32 wstrstr(wchar *str1, wchar *str2)
{
    while (*str1)
    {
        wchar *pstr1 = str1;
        wchar *pstr2 = str2;
        while (*pstr1 && *pstr2 && (*pstr1 == *pstr2))
        {
            pstr1++;
            pstr2++;
        }
        if (*pstr2 == '\0')
        {
            return TRUE;
        }
        str1++;
    }
    return FALSE;
}


uint32 cstristr(char *str1, char *str2)
{
    while (*str1)
    {
        char *pstr1 = str1;
        char *pstr2 = str2;
        while (*pstr1 && *pstr2 && (cstrtolower(*pstr1) == cstrtolower(*pstr2)))
        {
            pstr1++;
            pstr2++;
        }
        if (*pstr2 == '\0')
        {
            return TRUE;
        }
        str1++;
    }
    return FALSE;
}

/***************************
 * @brief 查找字符串,忽略大小写
 * @param str1 被查找的字符串
 * @param str2 字符串
 * @return 相同=TRUE,不同=FALSE
 ***************************/
uint32 wstristr(wchar *str1, wchar *str2)
{
    while (*str1)
    {
        wchar *pstr1 = str1;
        wchar *pstr2 = str2;
        while (*pstr1 && *pstr2 && (wstrtolower(*pstr1) == wstrtolower(*pstr2)))
        {
            pstr1++;
            pstr2++;
        }
        if (*pstr2 == '\0')
        {
            return TRUE;
        }
        str1++;
    }
    return FALSE;
}

uint32 cstrlen(char *str)
{
    uint32 len = 0;
    while (str[len] != 0)
        len++;

    return len;
}
uint32 wstrlen(wchar *str)
{
    uint32 len = 0;
    while (str[len] != 0)
        len++;

    return len;
}
uint32 CodeToWchar(wchar *buffer, void *hex, uint32 size)
{
    buffer[size * 2] = 0;
    uint32 i, j;
    for (i = 0, j = 0; i < size; i++)
    {
        buffer[j++] = HexWchar[((char *)hex)[i] >> 4 & 0xF];
        buffer[j++] = HexWchar[((char *)hex)[i] & 0xF];
    }
    return i;
}
uint64 HexToWchar(wchar *buffer, uint64 hex, uint64 size)
{
    size *= 2;
    buffer[size] = 0;
    uint64 i;
    for (i = 0; i < size; i++)
    {
        buffer[size - i - 1] = HexWchar[hex >> (i * 4) & 0xF];
    }
    return i;
}
/***************************
 * @brief 合成字符串
 * @param buffer 存放的缓存
 * @param str1   字符串1
 * @param str2   字符串2
 * @return 返回合成后的字节数
 ***************************/
uint32 wstrcat(wchar *buffer, wchar *str1, wchar *str2)
{
    uint32 index = 0;
    for (uint32 i = 0; str1[i] != 0; i++)
    {
        if (str1[i] == 0)
            break;
        buffer[index++] = str1[i];
    }
    for (uint32 i = 0; str2[i] != 0; i++)
    {
        if (str2[i] == 0)
            break;
        buffer[index++] = str2[i];
    }
    buffer[index] = 0;
    return index;
}
/***************************
 * @brief 合成字符串
 * @param buffer 存放的缓存
 * @param str1   字符串1
 * @param str2   字符串2
 * @return 返回合成后的字节数
 ***************************/
uint32 cstrcat(char *buffer, char *str1, char *str2)
{
    uint32 index = 0;
    for (uint32 i = 0; str1[i] != 0; i++)
    {
        if (str1[i] == 0)
            break;
        buffer[index++] = str1[i];
    }
    for (uint32 i = 0; str2[i] != 0; i++)
    {
        if (str2[i] == 0)
            break;
        buffer[index++] = str2[i];
    }
    buffer[index] = 0;
    return index;
}
/***************************
 * @brief 比较字符串
 * @param str1 字符串1
 * @param str2 字符串2
 * @return 相同=TRUE,不同=FALSE
 ***************************/
uint32 wstrcmp(wchar *str1, wchar *str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    return (*str2 | *str1) == 0 ? TRUE : FALSE;
}
/***************************
 * @brief 比较字符串
 * @param str1 字符串1
 * @param str2 字符串2
 * @return 相同=TRUE,不同=FALSE
 ***************************/
uint32 cstrcmp(char *str1, char *str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    return (*str2 | *str1) == 0 ? TRUE : FALSE;
}
/***************************
 * @brief 大写转小写
 * @param c 要转换的字符
 * @return 转换后的字符
 ***************************/
uint32 wstrtolower(wchar c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return c + 32;
    }
    else
    {
        return c;
    }
}
/***************************
 * @brief 大写转小写
 * @param c 要转换的字符
 * @return 转换后的字符
 ***************************/
uint32 cstrtolower(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return c + 32;
    }
    else
    {
        return c;
    }
}
/***************************
 * @brief 比较字符串,忽略大小写
 * @param str1 字符串1
 * @param str2 字符串2
 * @return 相同=TRUE,不同=FALSE
 ***************************/
uint32 std_wstricmp(wchar *str1, wchar *str2)
{
    while (*str1 != '\0' && *str2 != '\0')
    {
        int diff = wstrtolower(*str1) - wstrtolower(*str2);
        if (diff != 0)
        {
            return FALSE;
        }
        str1++;
        str2++;
    }

    return wstrtolower(*str1) == wstrtolower(*str2);
}

/// @brief 比较字符串,忽略大小写
/// @param str1 字符串1
/// @param str2 字符串2
/// @return 相同返回 TRUE \
/// @return 不同返回 FALSE
uint32 std_cstricmp(char *str1, char *str2)
{
    while (*str1 != '\0' && *str2 != '\0')
    {
        int diff = cstrtolower(*str1) - cstrtolower(*str2);
        if (diff != 0)
        {
            return FALSE;
        }
        str1++;
        str2++;
    }

    return cstrtolower(*str1) == cstrtolower(*str2);
}
/***************************
 * @brief 字符串拷贝
 * @param dst 目标地址
 * @param src 源地址
 * @param len 拷贝的字节数
 * @return 拷贝完成的字节数
 ***************************/
uint32 wstrcpy(wchar *dst, wchar *src, uint32 len)
{
    uint32 i;
    for (i = 0; i < len; i++)
    {
        dst[i] = src[i];
    }
    dst[i] = 0;
    return i;
}
/***************************
 * @brief 字符串拷贝
 * @param dst 目标地址
 * @param src 源地址
 * @param len 拷贝的字节数
 * @return 拷贝完成的字节数
 ***************************/
uint32 cstrcpy(char *dst, char *src, uint32 len)
{
    uint32 i;
    for (i = 0; i < len; i++)
    {
        dst[i] = src[i];
    }
    dst[i] = 0;
    return i;
}

uint32 std_memcpy(void *dst, void *src, uint32 len)
{
    uint32 i = 0;
    while (i < len)
    {
        ((char *)dst)[i] = ((char *)src)[i];
        i++;
    }

    return i;
}
uint32 std_memset(void *buffer, uint32 size, uint8 value)
{
    for (uint32 i = 0; i < size; i++)
    {
        ((char *)buffer)[i] = value;
    }
}
uint32 wsprint(wchar *buffer, wchar *str, void *args)
{
    uint32 argIndex = -1;
    uint32 strIndex = 0;
    uint32 BufferIndex = 0;
    while (str[strIndex] != 0)
    {
        if (str[strIndex] == L'%')
        {
            strIndex++;
            argIndex++;
        }
        else
        {
            buffer[BufferIndex++] = str[strIndex++];
            continue;
        }
        switch (str[strIndex])
        {
        case L'd':
        {
            char cstr[0x20] = {0};
            wchar wstr[0x10] = {0};
            std_itoa(((uint64 *)args)[argIndex], cstr, 10);
            cstrTowstr(wstr, cstr);
            uint32 len = wstrlen(wstr);
            wstrcpy(&buffer[BufferIndex], wstr, len);
            BufferIndex += len;
            strIndex += 1;

            break;
        }
        case L'x':
        {
            for (char x = 0; x < sizeof(sArg); x++)
            {
                if (str[strIndex] == sArg[x].str[0] && str[strIndex + 1] == sArg[x].str[1])
                {
                    strIndex += sArg[x].strlen;

                    HexToWchar(&buffer[BufferIndex], ((uint64 *)args)[argIndex], sArg[x].size);
                    BufferIndex += sArg[x].size * 2;
                    break;
                }
            }
            break;
        }
        case L'S':
        {
            wchar *string = (wchar *)((uint64 *)args)[argIndex];
            uint32 len = wstrlen(string);
            wstrcpy(&buffer[BufferIndex], string, len);
            BufferIndex += len;
            strIndex += 1;
            break;
        }
        case L's':
        {
            wchar wstr[0x100] = {0};
            char *astr = (char *)((uint64 *)args)[argIndex];
            cstrTowstr(wstr, astr);
            uint32 len = wstrlen(wstr);
            wstrcpy(&buffer[BufferIndex], wstr, len);
            BufferIndex += len;
            strIndex += 1;
            break;
        }

        default:
            break;
        }
    }

    return argIndex + 1;
}
/***************************
 * @brief 多字符串转宽字符串
 * @param unicode 宽字符串指针
 * @param ansi   多字符串指针
 * @return 无
 ***************************/
uint32 cstrTowstr(wchar *unicode, char *ansi)
{
    for (uint32 i = 0; ansi[i] != 0; i++)
    {
        unicode[i] = ansi[i];
    }
}
/***************************
 * @brief 宽字符串转多字符串
 * @param ansi   多字符串指针
 * @param unicode 宽字符串指针
 * @return 无
 ***************************/
uint32 wstrTocstr(char *ansi, wchar *unicode)
{
    for (uint32 i = 0; unicode[i] != 0; i++)
    {
        ansi[i] = unicode[i];
    }
}

uint32 sprint(wchar *buffer, wchar *format, ...)
{
    void *args = (void *)((uint64)&format + 8);
    return wsprint(buffer, format, args);
}

void reverse(char str[], int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

char *std_itoa(int num, char *str, int base)
{
    int i = 0;
    int isNegative = 0;

    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    if (num < 0 && base == 10)
    {
        isNegative = 1;
        num = -num;
    }

    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    if (isNegative)
    {
        str[i++] = '-';
    }

    str[i] = '\0';

    reverse(str, i);

    return str;
}

uint32 cstrnicmp(const char *s1, const char *s2, uint32 n)
{
    for (uint32 i = 0; i < n; i++)
    {
        char c1 = cstrtolower(s1[i]);
        char c2 = cstrtolower(s2[i]);
        if (c1 != c2)
            return c1 - c2;
        else if (c1 == '\0')
            break;
    }
    return 0;
}

uint32 wstrnicmp(const wchar *s1, const wchar *s2, uint32 n)
{
    for (uint32 i = 0; i < n; i++)
    {
        wchar c1 = wstrtolower(s1[i]);
        wchar c2 = wstrtolower(s2[i]);
        if (c1 != c2)
            return c1 - c2;
        else if (c1 == '\0')
            break;
    }
    return 0;
}

/***************************
 * @brief 字符串转十六进制数组
 * @param code IN 字符串
 * @param pHex OUT 十六进制数组
 * @return 成功-返回长度,失败-返回NULL
 ***************************/
int StrToBinary(char *code, char *pHex)
{
    int len = 0;
    char *pcode = code;
    char *pstr = 0;
    while (*pcode)
    {
        if (*pcode == ' ')
        {
            pcode++;
            continue;
        }
        else
        {
            pstr = pcode;
            char byte[2] = {0};
            for (int i = 0; i < 2; i++)
            {
                if (*pstr >= '0' && *pstr <= '9')
                    byte[i] = (*pstr - '0');
                else if (*pstr >= 'A' && *pstr <= 'F')
                    byte[i] = (*pstr - 'A' + 0xA);
                else if (*pstr >= 'a' && *pstr <= 'f')
                    byte[i] = (*pstr - 'a' + 0xA);
                else if (*pstr == '?' || *pstr == '*')
                {
                    byte[0] = 0x0C;
                    byte[1] = 0x0C;
                    break;
                }
                else
                {
                    return FALSE;
                }
                pstr++;
            }
            pHex[len++] = (byte[0] << 4) + byte[1];
            pcode += 2;
        }
    }
    return len;
}

/***************************
 * @brief 查找特征码
 * @param Base IN 要查找的内存起始位置
 * @param size IN 要查找的内存大小
 * @param code IN 特征码字符串
 * @return 成功-返回地址,失败-返回 NULL
 ***************************/
void *std_FindCode(char *Base, int size, char *code)
{

    int len = 0, index = 0;
    char universal = 0xCC;
    char hex[0x40] = {0};
    char *pHex = hex;

    len = StrToBinary(code, pHex);

    if (len)
    {
        while (index < size)
        {
            if (Base[index] == hex[0])
            {
                int i = 0;
                char *pTemp = Base + index;
                while (pTemp[i] == hex[i])
                {
                    i++;
                    while (hex[i] == universal)
                        i++;

                    if (i >= len)
                    {
                        return pTemp;
                    }
                }
            }
            index++;
        }
    }

    return NULL;
}