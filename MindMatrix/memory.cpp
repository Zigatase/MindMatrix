#include "memory.h"


PVOID GetSystemModuleBase(const char* module_name)
{
	ULONG bytes = 0;
	NTSTATUS status = ZwQuerySystemInformation(SystemModuleInformation, NULL, bytes, &bytes);
}

PVOID GetSystemModuleExport(const char* module_name, LPCSTR routine_name)
{

}


bool WriteMemory(void* address, void* buffer, size_t size)
{

}

bool WriteToReadOnlyMemory(void* address, void* buffer, size_t size)
{

}