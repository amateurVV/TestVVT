bits 64

section .data

%include "./vmx/data.asm"

extern VmmEntry
extern OldSystemCall64
extern NewSystemCall64
extern GetSystemServiceFuncAddr
extern GetDebugServiceFuncAddr
extern DebugObject
extern IsEnableDebug
extern Driver_StartVT

section .text

global AsmCallForDriverEntry
AsmCallForDriverEntry:
	jmp .Entry
	db 0xDE,0xAD,0xC0,0xDE
.Entry:
	push rcx
	call Driver_StartVT
	pop rcx
	ret
	int3


global CallBackStartVM
CallBackStartVM:
  	pushfq
	pushaq
	sub rsp,20h
  	mov rax,rcx
  	mov rcx,rdx
	mov r8,rsp			;GuestRsp	
	mov rdx,.succeed	;GuestRip	
	call rax
	jmp .fail
.succeed:
	add rsp,20h
	popaq
	popfq
	mov rax,1	
	ret	
.fail:
	add rsp,20h
	popaq
	popfq
	xor rax,rax
	ret	
	

global HostEntry
HostEntry:
	lfence
	sub rsp,40h	;GuestRegs 结构预留
	pushfq
	pushaq	
	mov rcx,rsp	;GuestRegs		

	sub rsp,78h				
	movups [rsp + 0x00], xmm0
	movups [rsp + 0x10], xmm1
	movups [rsp + 0x20], xmm2
	movups [rsp + 0x30], xmm3
	movups [rsp + 0x40], xmm4
	movups [rsp + 0x50], xmm5

	sub rsp,100h
	call VmmEntry
	add rsp,100h

	movups xmm0, [rsp + 0x00]
	movups xmm1, [rsp + 0x10]
	movups xmm2, [rsp + 0x20]
	movups xmm3, [rsp + 0x30]
	movups xmm4, [rsp + 0x40]
	movups xmm5, [rsp + 0x50]
	add rsp, 78h
		
	cmp rax,VMX_EXIT
	jz .leave_vmx
	popaq		
	popfq		
	add rsp,40h
	nop
	vmresume
	nop
	int3
.leave_vmx:
	popaq
	popfq	
	add rsp,40h
	mov rsp,rcx
	jmp rax
	int3


global vmx_rdmsr
vmx_rdmsr:
	push r8
	mov r8,rcx
	mov rcx,[r8+GUEST_RCX]
  	rdmsr
	mov [r8+GUEST_RDX],rdx
	mov [r8+GUEST_RAX],rax
	pop r8
  	ret

global vmx_wrmsr
vmx_wrmsr:
	push r8
	mov r8,rcx
	mov rax,[r8+GUEST_RAX]
	mov rdx,[r8+GUEST_RDX]
	mov rcx,[r8+GUEST_RCX]
  	wrmsr
	pop r8
  	ret

global vmx_rdtsc
vmx_rdtsc:
	push r8
	mov r8,rcx	
	rdtsc
	mov [r8+GUEST_RAX],rax
	mov [r8+GUEST_RDX],rdx
	pop r8
	ret

global vmx_rdtscp
vmx_rdtscp:
	push r8	
	mov r8,rcx
	rdtscp
	mov [r8+GUEST_RAX],rax
	mov [r8+GUEST_RCX],rcx
	mov [r8+GUEST_RDX],rdx
	pop r8
	ret

global vmx_cpuid
vmx_cpuid:
	push r8
  	mov r8,rcx
	mov rax,[r8+GUEST_RAX]
	mov rcx,[r8+GUEST_RCX]
 	cpuid
 	mov [r8+GUEST_RAX],rax
 	mov [r8+GUEST_RCX],rcx
 	mov [r8+GUEST_RDX],rdx
 	mov [r8+GUEST_RBX],rbx
	pop r8
 	ret


global vmx_write
vmx_write:
	vmwrite rcx,rdx
	ReturnErrorCode

global vmx_read
vmx_read:
	vmread [rdx],rcx
	ReturnErrorCode

global vmx_on
vmx_on:
	vmxon [rcx]
	ReturnErrorCode

global vmx_off
vmx_off:
	vmxoff
	ReturnErrorCode

global vmx_ptrst
vmx_ptrst:
	vmptrst [rcx]
	ReturnErrorCode

global vmx_ptrld
vmx_ptrld:
	vmptrld [rcx]
	ReturnErrorCode

global vmx_launch
vmx_launch:
	vmlaunch
	ReturnErrorCode

global vmx_resume
vmx_resume:
	vmresume
	ReturnErrorCode

global vmx_func
vmx_func:
	vmfunc
	ReturnErrorCode

global vmx_call
vmx_call:
	vmcall
	ReturnErrorCode

global vmx_clear
vmx_clear:
	vmclear [rcx]
	ReturnErrorCode

global vmx_invvpid
vmx_invvpid:
	invvpid rcx,[rdx]
	ReturnErrorCode

global vmx_invept
vmx_invept:
	invept rcx,[rdx]
	ReturnErrorCode




global HandlerSystemCall
HandlerSystemCall:
	swapgs
	mov gs:[GS_R3_RSP],rsp
	mov rsp,gs:[GS_R0_RSP]
	push qword gs:[GS_R3_RSP]	;保存R3->RSP,调用API过程中有可能会改变TrapFrame的值

	;判断是不是自定义函数
	test rax,SERVICEBASE	;如果是自定义的系统服务函数
	jnz .HandlerStart		;跳转到自定义处理函数

	push rax
	push rcx
	mov rcx,rax
	sub rsp,0x20
	call IsEnableDebug
	add rsp,0x20
	cmp rax,0
	pop rcx
	pop rax
	jnz .GotoNewSysCall64

.GotoOldSysCall64:				;原路返回
	add rsp,8					;丢弃保存的R3->RSP
	mov gs:[GS_R0_RSP],rsp
	mov rsp,gs:[GS_R3_RSP]
	swapgs
	jmp [rel OldSystemCall64]	;调用原来的系统服务函数入口
	int3

.GotoNewSysCall64:
	add rsp,8					;丢弃保存的R3->RSP
	mov gs:[GS_R0_RSP],rsp
	mov rsp,gs:[GS_R3_RSP]
	swapgs
	jmp [rel NewSystemCall64]	;调用Hook系统服务函数入口
	int3

.HandlerStart:					;调试器进程执行处理函数前的准备
	pushaq						;保存所有寄存器
	sub rsp,ARG_STACK			;开栈保存R3的参数
	mov rcx,r10					;r10是R3的rcx参数,syscall用了rcx做为R3返回地址
	mov [rsp+0x00],rcx
	mov [rsp+0x08],rdx
	mov [rsp+0x10],r8
	mov [rsp+0x18],r9

	mov r10,gs:[GS_R3_RSP]

	stac

	mov rcx,[r10+0x28]
	mov [rsp+0x20],rcx
	mov rcx,[r10+0x30]
	mov [rsp+0x28],rcx
	mov rcx,[r10+0x38]
	mov [rsp+0x30],rcx
	mov rcx,[r10+0x40]
	mov [rsp+0x38],rcx
	mov rcx,[r10+0x48]
	mov [rsp+0x40],rcx
	mov rcx,[r10+0x50]
	mov [rsp+0x48],rcx
	mov rcx,[r10+0x58]
	mov [rsp+0x50],rcx
	mov rcx,[r10+0x60]
	mov [rsp+0x58],rcx
	mov rcx,[r10+0x68]
	mov [rsp+0x60],rcx
	mov rcx,[r10+0x70]
	mov [rsp+0x68],rcx
	mov rcx,[r10+0x78]
	mov [rsp+0x70],rcx

	push rax						;写MSR前先保存

	;关闭分支预测
	mov ecx,0x48
	mov rax,1
	xor rdx,rdx
	wrmsr

	mov ecx,0x49
	mov rax,1
	xor rdx,rdx
	wrmsr

	pop rax	

	lfence
	
	mov rcx,rax
	sub rsp,0x20
	call GetSystemServiceFuncAddr	;获取自定义函数的处理函数地址
	add rsp,0x20
	cmp rax,0						;比较是不是有处理函数
	jz .ServiceNotHandler			;没有自定义处理函数,则什么也不做返回R3	
	jmp .Handler					;跳转到统一处理函数,执行完直接返回R3

.ServiceNotHandler:					;没有自定义的函数
	mov rax,-1						;错误码-1
	jmp .GoBackR3					;跳转返回R3

.Handler:							;统一处理入口,处理完返回R3
	mov rcx,[rsp+0x00]				;执行处理函数前,传参数
	mov rdx,[rsp+0x08]
	mov r8, [rsp+0x10]
	mov r9, [rsp+0x18]
	call rax						;执行处理函数
	
.GoBackR3:
	add rsp,ARG_STACK				;平参数栈
	mov [rsp],rax					;保存RAX
	popaq							;恢复所有寄存器,和已经修改的RAX返回值
	pop rdx							;取回保存的R3->RSP
	mov gs:[GS_R0_RSP],rsp			;交换RSP,保存R0栈
	mov rsp,rdx						;交换RSP,取出R3栈
	swapgs
	sysretq							;返回R3




global HookerEngine
HookerEngine:
	pushaq
	pushfq

	sub rsp,0x20
	call rax
	add rsp,0x20

	popfq
	popaq
	pop rax
	ret

global HookerEngineLen
HookerEngineLen:
	dq $-HookerEngine

;;;;;;;;;;;;;;;;;;;;;;;;;VMCALL;;;;;;;;;;;;;;;;;;;;;;;;;;;
global KipiVmcall
KipiVmcall:
	cli
	mov rax,rcx
	vmcall
	sti
	ret

