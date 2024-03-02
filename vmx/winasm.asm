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


global VmGetCurrentProcess
VmGetCurrentProcess:
    mov rax, gs:[ETHREAD]
    mov rax, [rax+EPROCESS]
    ret

global VmGetCurrentThread
VmGetCurrentThread:
    mov rax, gs:[ETHREAD]
    ret

global VmGetProcessFullName
VmGetProcessFullName:
    mov rax, [rcx+EPROCESS_FULL_NAME]
    ret

global VmGetProcessName
VmGetProcessName:
    lea rax, [rcx+EPROCESS_NAME]
    ret

global VmGetProcessCR3
VmGetProcessCR3:
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