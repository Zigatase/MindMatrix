#ifndef MEMORY_H_
#define MEMORY_H_

#include "definitions.h"

typedef struct _NULL_MEMORY
{
    void* buffer_address;

    UINT_PTR address;
    ULONGLONG size;
    ULONG pid;
    BOOLEAN write;
    BOOLEAN read;
    BOOLEAN req_base;

    void* output;
    const char* module_name;
} NULL_MEMORY;

PVOID GetSystemModuleBase(const char* module_name);
PVOID GetSystemModuleExport(const char* module_name, LPCSTR routine_name);

BOOL WriteMemory(void* address, void* buffer, size_t size);
BOOL WriteToReadOnlyMemory(void* address, void* buffer, size_t size);

#endif // !MEMORY_H_
