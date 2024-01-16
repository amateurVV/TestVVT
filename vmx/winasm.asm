bits 64

section .data

%include "./vmx/data.asm"

section .text


global GetSysCallAddr
GetSysCallAddr:
    mov rax,r10
    ret

global GetSysCallNumber
GetSysCallNumber:
    mov rax,gs:[ETHREAD]
    mov eax,[rax+CALLNUMBER]
    ret


global PsGetCurrentProcess
PsGetCurrentProcess:
    mov rax, gs:[ETHREAD]
    mov rax, [rax+EPROCESS]
    ret

global PsGetCurrentThread
PsGetCurrentThread:
    mov rax, gs:[ETHREAD]
    ret

global PsGetProcessFullName
PsGetProcessFullName:
    mov rax, [rcx+EPROCESS_FULL_NAME]
    ret

global PsGetProcessName
PsGetProcessName:
    mov rax, [rcx+EPROCESS_NAME]
    ret

global PsGetProcessCR3
PsGetProcessCR3:
    mov rax, [rcx+DATABASE]
    ret

global TargetProcessCR3
TargetProcessCR3:
    mov rax,cr3
    mov rcx,[rcx+DATABASE]
    mov cr3,rcx
    stac
    ret


global VmcallHookEPT
VmcallHookEPT:
	mov rax,6
    vmcall
    ret