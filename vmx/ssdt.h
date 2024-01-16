#pragma once



typedef struct _SERVICE_TABLE
{
    unsigned long long number;
    unsigned long long addr;
    char *name;
    void *handler;
} SERVICE_TABLE, *PSERVICE_TABLE;

#define NR_NtCreateUserProcess  0xC9
#define NR_NtOpenFile           0x33
#define NR_NtMapViewOfSection   0x28
#define NR_NtCreateThreadEx     0xC2
#define NR_NtWriteVirtualMemory 0x3A