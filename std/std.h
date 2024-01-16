#pragma once
#include "type.h"

uint64 HexToWchar(wchar *buffer, uint64 hex, uint64 size);
uint32 CodeToWchar(wchar *buffer, void *hex, uint32 size);

uint32 wstrcat(wchar *buffer, wchar *str1, wchar *str2);
uint32 cstrcat(char *buffer, char *str1, char *str2);

uint32 wstrstr(wchar *str1, wchar *str2);
uint32 cstrstr(char *str1, char *str2);

uint32 wstrtolower(wchar c);
uint32 cstrtolower(char c);

uint32 cstrnicmp(const char *s1, const char *s2, uint32 n);
uint32 wstrnicmp(const wchar *s1, const wchar *s2, uint32 n);

uint32 wstrcmp(wchar *str1, wchar *str2);
uint32 cstrcmp(char *str1, char *str2);

uint32 wstricmp(wchar *str1, wchar *str2);
uint32 cstricmp(char *str1, char *str2);

uint32 wstrlen(wchar *str);
uint32 cstrlen(char *str);

uint32 wstrcpy(wchar *dst, wchar *src, uint32 len);
uint32 cstrcpy(char *dst, char *src, uint32 len);

uint32 std_memcpy(void *dst, void *src, uint32 len);
uint32 std_memset(void *buffer, uint32 size, uint8 value);

uint32 wsprint(wchar *buffer, wchar *str, void *args);
/*格式化字符串*/
uint32 sprint(wchar *buffer, wchar *format, ...);

uint32 wstrTocstr(char *ansi, wchar *unicode);
uint32 cstrTowstr(wchar *unicode, char *ansi);

char *std_itoa(int num, char *str, int base);


void *std_FindCode(char *Base, int size, char *code);
int StrToBinary(char *code, char *pHex);