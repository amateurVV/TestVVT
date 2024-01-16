bits 64

section .data

section .text


global cpuid
cpuid:
    push rbx
    mov rax,rcx
    mov rcx,rdx
    cpuid
    mov [r8+0x00],eax
    mov [r8+0x08],ebx
    mov [r8+0x10],ecx
    mov [r8+0x18],edx
    pop rbx
    ret


global rdmsr
rdmsr:
    rdmsr
    shl rdx,0x20
	or rax,rdx
    ret

global wrmsr
wrmsr:
    mov eax,edx
    shr rdx,0x20
    wrmsr
    ret

global getapicID
getapicID:
    push rbx
    mov eax,1
    cpuid
    mov eax,ebx
    shr eax,24
    and eax,0xFF
    pop rbx
    ret

global int3
int3:
    int3
    ret

global int3p
int3p:
    int3
    ret

global cli
cli:
    cli
    ret

global sti
sti:
    sti
    ret

global invlpg
invlpg:
    invlpg [rcx]
    ret

global readCR0
readCR0:
    mov rax,cr0
    ret

global readCR2
readCR2:
    mov rax,cr2
    ret

global readCR3
readCR3:
    mov rax,cr3
    ret

global readCR4
readCR4:
    mov rax,cr4
    ret

global writeCR0
writeCR0:
    mov cr0,rcx
    ret

global writeCR2
writeCR2:
    mov cr2,rcx
    ret

global writeCR3
writeCR3:
    mov cr3,rcx
    ret

global writeCR4
writeCR4:
    mov cr4,rcx
    ret

global readBaseGDT
readBaseGDT:
    sub rsp,20
    sgdt [rsp]
    mov rax,[rsp+2]
    add rsp,20
    ret 

global readBaseIDT
readBaseIDT:
    sub rsp,20
    sidt [rsp]
    mov rax,[rsp+2]
    add rsp,20
    ret 

global readLimitGDT
readLimitGDT:
	sub rsp,20
	sgdt [rsp]
	mov ax,[rsp]
	add rsp,20
	ret

global readLimitIDT
readLimitIDT:
	sub rsp,20
	sidt [rsp]
	mov ax,[rsp]
	add rsp,20
	ret

global writeGDTR
writeGDTR:
	lgdt [rcx]
	ret

global writeIDTR
writeIDTR:
	lidt [rcx]
	ret

global readDR0
readDR0:
    mov rax,dr0
    ret

global readDR1
readDR1:
    mov rax,dr1
    ret

global readDR2
readDR2:
    mov rax,dr2
    ret

global readDR3
readDR3:
    mov rax,dr3
    ret

global readDR4
readDR4:
    mov rax,dr4
    ret

global readDR5
readDR5:
    mov rax,dr5
    ret

global readDR6
readDR6:
    mov rax,dr6
    ret

global readDR7
readDR7:
    mov rax,dr7
    ret

global writeDR0
writeDR0:
    mov dr0,rcx
    ret

global writeDR1
writeDR1:
    mov dr1,rcx
    ret

global writeDR2
writeDR2:
    mov dr2,rcx
    ret

global writeDR3
writeDR3:
    mov dr3,rcx
    ret

global writeDR4
writeDR4:
    mov dr4,rcx
    ret

global writeDR5
writeDR5:
    mov dr5,rcx
    ret

global writeDR6
writeDR6:
    mov dr6,rcx
    ret

global writeDR7
writeDR7:
    mov dr7,rcx
    ret

global readCS
readCS:
    mov ax,cs
    ret

global readSS
readSS:
    mov ax,ss
    ret

global readDS
readDS:
    mov ax,ds
    ret

global readES
readES:
    mov ax,es
    ret

global readFS
readFS:
    mov ax,fs
    ret

global readGS
readGS:
    mov ax,gs
    ret

global readTR
readTR:
    str ax
    ret

global readLDTR
readLDTR:
    sldt ax
    ret

global readrflags
readrflags:
    pushfq
    pop rax
    ret;

global mbts
mbts:
	bts [rcx],rdx
	ret

global mbtr
mbtr:
	btr [rcx],rdx
	ret


global LockAdd64
LockAdd64:
    lock add qword [rcx],rdx
    ret

global InterlockedCmpExchange64
InterlockedCmpExchange64:
    mov rax,r8
    lock cmpxchg [rcx], rdx
    ret
