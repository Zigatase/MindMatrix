#ifndef MEMORY_H_
#define MEMORY_H_

#include "definitions.h"

PVOID GetSystemModuleBase(const char* module_name);
PVOID GetSystemModuleExport(const char* module_name, LPCSTR routine_name);

bool WriteMemory(void* address, void* buffer, size_t size);
bool WriteToReadOnlyMemory(void* address, void* buffer, size_t size);

#endif // !MEMORY_H_
