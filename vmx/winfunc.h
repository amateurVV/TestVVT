#pragma once

// @brief 获取系统调用号的函数地址. 注:只能在特定地方使用
void *GetSysCallAddr();

// @brief 获取系统调用号. 注:只能在特定地方使用
unsigned long GetSysCallNumber();

unsigned long long TargetProcessCR3(void *EProcess);

void *PsGetCurrentProcess();
void *PsGetCurrentThread();
void *PsGetProcessCR3(void *EProcess);

void *PsGetProcessFullName(void *EProcess);
void *PsGetProcessName(void *EProcess);

void *VmcallHookEPT(void *HookContext);

uint64 InitOsApi(PVT vt, void *NtosKernelBase);
