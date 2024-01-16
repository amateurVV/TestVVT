#pragma once
#include "type.h"

#define EAX 0
#define EBX 1
#define ECX 2
#define EDX 3

uint64 cpuid(uint64 num, uint64 leaf, void *arg);
uint64 rdmsr(uint64 rcx);
uint64 wrmsr(uint64 rcx, uint64 rdx);

uint8 getapicID();

void int3p(void *, ...);
void int3();

void sti();
void cli();
void invlpg(void *rcx);
void mbts(void *mem, uint64 rdx);
void mbtr(void *mem, uint64 rdx);

void LockAdd64(uint64 *rcx, uint64 rdx);
uint64 InterlockedCmpExchange64(uint64 *rcx, uint64 rdx, uint64 r8);

uint64 readCR0();
uint64 readCR2();
uint64 readCR3();
uint64 readCR4();

uint64 writeCR0();
uint64 writeCR2();
uint64 writeCR3();
uint64 writeCR4();

uint64 readDR0();
uint64 readDR1();
uint64 readDR2();
uint64 readDR3();
uint64 readDR4();
uint64 readDR5();
uint64 readDR6();
uint64 readDR7();

uint64 writeDR0();
uint64 writeDR1();
uint64 writeDR2();
uint64 writeDR3();
uint64 writeDR4();
uint64 writeDR5();
uint64 writeDR6();
uint64 writeDR7();

uint64 readCS();
uint64 readSS();
uint64 readDS();
uint64 readES();
uint64 readFS();
uint64 readGS();
uint64 readTR();
uint64 readLDTR();

uint64 readBaseGDT();
uint64 readBaseIDT();
uint64 readLimitGDT();
uint64 readLimitIDT();

uint64 readrflags();
