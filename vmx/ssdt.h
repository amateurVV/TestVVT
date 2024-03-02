#pragma once
#include "type.h"


typedef struct _SERVICE_TABLE
{
    unsigned long long number;
    unsigned long long addr;
    char *name;
    void *handler;
} SERVICE_TABLE, *PSERVICE_TABLE;

#define NR_NtCreateUserProcess          0xC9
#define NR_NtOpenFile                   0x33
#define NR_NtMapViewOfSection           0x28
#define NR_NtCreateThreadEx             0xC2
#define NR_NtWriteVirtualMemory         0x3A
#define NR_NtLoadDriver                 0x106
#define NR_NtQueryInformationProcess    0x19
#define NR_NtQuerySystemInformation     0x36


// extern uint64 (**HandlerSSDT)();
extern void InitHandlerSSDT();
