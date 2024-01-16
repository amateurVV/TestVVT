bits 64

%ifndef MACROS_WIN_DATA
%define MACROS_WIN_DATA

DATABASE    equ 0x28
ETHREAD     equ 0x188
EPROCESS    equ 0xB8
CALLNUMBER  equ 0x80

GS_R3_RSP   equ 0x10
GS_R0_RSP   equ 0x1A8

ARG_STACK   equ 0xA8

EPROCESS_FULL_NAME 	equ 0x5C0
EPROCESS_NAME 		equ 0x5A8

%endif


%ifndef MACROS_VMM_DATA
%define MACROS_VMM_DATA

GUEST_RAX   EQU 0x00
GUEST_RCX   EQU 0x08
GUEST_RDX   EQU 0x10
GUEST_RBX   EQU 0x18

VMX_EXIT    EQU 0xDEAD
SERVICEBASE EQU 0x8000

DEBUGER     EQU 0x00
DEBUGED     EQU 0x08

%endif


%ifndef MACROS_PUSHAQ
%define MACROS_PUSHAQ

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

%endif



%ifndef MACROS_POPAQ
%define MACROS_POPAQ

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

%endif

%ifndef MACROS_VMX_ERROR
%define MACROS_VMX_ERROR

%macro ReturnErrorCode 0
	jc .err1
	jz .err2
	xor eax,eax
	ret
.err1:
	mov eax,1
	ret	
.err2:
	mov eax,2
	ret
%endmacro

%endif

%ifndef MACROS_SYSRETQ
%define MACROS_SYSRETQ

%macro sysretq 0
	DB 0x48
	sysret
%endmacro

%endif
