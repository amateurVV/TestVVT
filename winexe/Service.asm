section .data

SERVICE_BASE EQU 0x8000

section .code


global ServiceEnumProcess
ServiceEnumProcess:
    mov r10,rcx
    mov rax,SERVICE_BASE + 1
    syscall
    ret

global ServiceInitDebug
ServiceInitDebug:
    mov r10,rcx
    mov rax,SERVICE_BASE + 2
    syscall
    ret


global ServiceCreateDebug
ServiceCreateDebug:
    mov r10,rcx
    mov rax,SERVICE_BASE + 3
    syscall
    ret

global ServiceCreateThread
ServiceCreateThread:
    mov r10,rcx
    mov rax,SERVICE_BASE + 4
    syscall
    ret

global ServiceDebugProcessForName
ServiceDebugProcessForName:
    mov r10,rcx
    mov rax,SERVICE_BASE + 5
    syscall
    ret

global ServiceDebugReadMemory
ServiceDebugReadMemory:
    mov r10,rcx
    mov rax,SERVICE_BASE + 6
    syscall
    ret

global ServiceDebugWriteMemory
ServiceDebugWriteMemory:
    mov r10,rcx
    mov rax,SERVICE_BASE + 7
    syscall
    ret

global ServiceDebugBreakPoint
ServiceDebugBreakPoint:
    mov r10,rcx
    mov rax,SERVICE_BASE + 8
    syscall
    ret

global ServiceDebugEnumVad
ServiceDebugEnumVad:
    mov r10,rcx
    mov rax,SERVICE_BASE + 9
    syscall
    ret

global ServiceSuperHook
ServiceSuperHook:
    mov r10,rcx
    mov rax,SERVICE_BASE + 10
    syscall
    ret

global ServiceEnableEptHook
ServiceEnableEptHook:
    mov r10,rcx
    mov rax,SERVICE_BASE + 11
    syscall
    ret


global ServiceGetMsg
ServiceGetMsg:
    mov r10,rcx
    mov rax,SERVICE_BASE + 12
    syscall
    ret

global ServiceHideDriver
ServiceHideDriver:
    mov r10,rcx
    mov rax,SERVICE_BASE + 13
    syscall
    ret

global ServiceUnHideDriver
ServiceUnHideDriver:
    mov r10,rcx
    mov rax,SERVICE_BASE + 14
    syscall
    ret

global ServiceSetCI
ServiceSetCI:
    mov r10,rcx
    mov rax,SERVICE_BASE + 15
    syscall
    ret










global VmcallGetMsg
VmcallGetMsg:
    mov rax,9
    syscall
    ret