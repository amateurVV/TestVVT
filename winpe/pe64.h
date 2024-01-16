#pragma once
#include "type.h"



void *GetNtHeader(void *addr);
void *GetSection(void *addr, char *name);
void *GetDirectory(void *addr, char index);

uint64 GetSizeOfImage(void* ModuleBase);

void *GetImportFunctionByName(void *base, char *ModuleName, char *FunctionName);
void *GetExportFunctionByName(void *base, char *FunctionName);
uint64 GetSectionVirtualSize(void *base, char *name);
uint64 GetSectionVirtualAddress(void *base, char *name);


uint64 GetExportVA(void* ModuleBase);
void* ImageRvaToFoa(uint64 ModuleBase, uint64 Rva);


