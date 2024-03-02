#pragma once

char vmx_write(unsigned long long rcx, unsigned long long rdx);
char vmx_read(unsigned long long rcx, void *rdx);
char vmx_on(void *rcx);
char vmx_off();
char vmx_launch();
char vmx_resume();
char vmx_clear(void *rcx);
char vmx_ptrst(void *rcx);
char vmx_ptrld(void *rcx);
char vmx_func(void *rcx, void *rdx, void *r8, void *r9);
char vmx_call(void *rcx, void *rdx, void *r8, void *r9);
char vmx_invvpid(void *rcx, void *m128);
char vmx_invept(char rcx, void *m128);

/// @brief for VMM
char vmx_rdtsc(void *GuestRegs);
/// @brief for VMM
char vmx_rdtscp(void *GuestRegs);
/// @brief for VMM
char vmx_rdmsr(void *GuestRegs);
/// @brief for VMM
char vmx_wrmsr(void *GuestRegs);
/// @brief for VMM
char vmx_cpuid(void *GuestRegs);

/// @brief VMM 入口函数
unsigned long long HostEntry();

//// @brief 回调CALL 启动VM
//// @return TRUE:<<成功>>;FALSE:<<错误>>
char CallBackStartVM(void *StartVM, char cpunr);

/// @brief Hook SystemCall64 的替换函数
void HandlerSystemCall();

void HookerEngine();
extern unsigned long long HookerEngineLen;

/// @brief asm vmcall for Kipi
unsigned long long  KipiVmcall(void *Context);

/// @brief 搜索特征码调用
unsigned long long AsmCallForDriverEntry(void *NtosKernelBase);


