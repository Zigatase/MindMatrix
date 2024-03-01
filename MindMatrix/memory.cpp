#include "memory.h"


PVOID GetSystemModuleBase(const char* module_name)
{
	ULONG bytes = 0;
	NTSTATUS status = ZwQuerySystemInformation(SystemModuleInformation, NULL, bytes, &bytes);

	if (!bytes)
		return NULL;

	PRTL_PROCESS_MODULES modules = (PRTL_PROCESS_MODULES)ExAllocatePoolWithTag(NonPagedPool, bytes, 0x4e554c4c);

	status = ZwQuerySystemInformation(SystemModuleInformation, modules, bytes, &bytes);

	if (!NT_SUCCESS(status))
		return NULL;

	PRTL_PROCESS_MODULE_INFORMATION module = modules->Modules;
	PVOID module_base = 0, module_size = 0;

	for (ULONG i = 0; i < modules->NumberOfModules; i++)
	{
		if (strcmp((char*)module[i].FullPathName, module_name) == 0)
		{
			module_base = module[i].ImageBase;
			module_size = (PVOID)module[i].ImageSize;
			break;
		}
	}

	if (module)
		ExFreePoolWithTag(modules, NULL);

	if (module_base <= NULL)
		return NULL;

	return module_base;
}

PVOID GetSystemModuleExport(const char* module_name, LPCSTR routine_name)
{
	PVOID lpModule = GetSystemModuleBase(module_name);

	if (!lpModule)
		return NULL;

	return RtlFindRxporedRoutineByName(lpModule, routine_name);
}


bool WriteMemory(void* address, void* buffer, size_t size)
{
	if (!RtlCopyMemory(address, buffer, size))
		return FALSE;
	else
		return TRUE;
}

bool WriteToReadOnlyMemory(void* address, void* buffer, size_t size)
{
	PMDL Mdl = IoAllocateMdl(address, size, FALSE, FALSE, NULL);

	if (!Mdl)
		return FALSE;


	// Сопостовляем память и меняем вид доступа памяти с записи на чтение-запись
	MmProbeAndLockPages(Mdl, KernelMode, IoReadAccess);
	PVOID Mapping = MmMapLockedPagesSpecifyCache(Mdl, KernelMode, MmNonCached, NULL, FALSE, NormalPagePriority);
	MmProtectMdlSystemAddress(Mdl, PAGE_READWRITE);

	// Записываем память
	WriteMemory(Mapping, buffer, size);

	// Очищаем все после себя
	MmUnmapLockedPages(Mapping, Mdl);
	MmUnlockPages(Mdl);

	// Освобождаем дискриптор памяти
	IoFreeMdl(Mdl);

	return TRUE;
}