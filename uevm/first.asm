bits 64

section .data

extern HookStartFirstUserProcess

%macro pushaq 0
	push r15;
	push r14;
	push r13;
	push r12;
	push r11;
	push r10;
	push r9;
	push r8;
	push rdi;
	push rsi;
	push rbp;
    push rsp;
	push rbx;
	push rdx;
	push rcx;
	push rax;	
%endmacro

%macro popaq 0
	pop rax;
	pop rcx;
	pop rdx;
	pop rbx;
    pop rsp;
	pop rbp;
	pop rsi;
	pop rdi;
	pop r8;
	pop r9;
	pop r10;
	pop r11;
	pop r12;
	pop r13;
	pop r14;
	pop r15;
%endmacro

section .text

global HookFirstTransit
HookFirstTransit:
	jmp .start	
.FirstProcess:
    dq 0;StartFirstUserProcess 的绝对地址
.start:
    pushaq
    pushfq
    call HookStartFirstUserProcess;函数中必须实现还原Hook代码
    popfq
    popaq
    jmp qword [rel .FirstProcess]
    ret

global HookStartFirst
HookStartFirst:
	jmp .start	
.Transit:
    dq 0;HookFirstTransit 的绝对地址
.start:
    jmp qword [rel .Transit]
    ret
