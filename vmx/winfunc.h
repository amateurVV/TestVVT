#pragma once
#include "wintype.h"
// @brief 获取系统调用号的函数地址. 注:只能在特定地方使用
void *GetSysCallAddr();

// @brief 获取系统调用号. 注:只能在特定地方使用
unsigned long GetSysCallNumber();

unsigned long long TargetProcessCR3(void *EProcess);

void *VmGetCurrentProcess();
void *VmGetCurrentThread();
void *VmGetProcessCR3(void *EProcess);

void *VmGetProcessFullName(void *EProcess);
void *VmGetProcessName(void *EProcess);

void *VmcallHookEPT(void *HookContext);

uint64 InitOsApi(PVT vt, void *NtosKernelBase);
PLDR_DATA_TABLE_ENTRY GetModules(PLDR_DATA_TABLE_ENTRY ListEntry, wchar *name);