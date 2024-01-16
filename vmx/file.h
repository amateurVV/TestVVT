#pragma once
#include "ssdt.h"
#include "type.h"
#include "wintype.h"

extern void *ReadFile(wchar *wFileFullPath);
extern uint64 GetServiceTable(PSERVICE_TABLE psdt, void* ModuleBase);
uint64 InitSystemServiceTable(PSERVICE_TABLE psdt, wchar *file);