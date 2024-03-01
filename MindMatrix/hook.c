#include "hook.h"


BOOL CallKernelFunction(void* kernel_function_address)
{
	if (!kernel_function_address)
		return FALSE;

	// Пример хука https://github.com/23splat/NtOpenCompositionSurfaceSwapChainHandleInfo/blob/main/main.cpp
	// Путь к драйверу который хотим хукнуть | название функции в драйвере
	PVOID* function = (PVOID*)(GetSystemModuleExport("\\SystemRoot\\System32\\drivers\\dxgkrnl.sys",
																	"NtOpenCompositionSurfaceSwapChainHandleInfo")); // NtQueryCompositionSurfaceStatistics

	if (!function)
		return FALSE;

	// 12 byte для хука
	BYTE orig[] = { 0x4C, 0x89, 0x44, 0x24, 0x18, 0x48, 0x89, 0xC2, 0x40, 0x08, 0x53, 0x56 };
	// mov    QWORD PTR[rsp + 0x18], r8 [4c 89 44 24 18]
	// mov    QWORD PTR[rsp + 0x8], rcx [48 89 4c 24 08]
	// push   rbx                       [53]
	// push   rsi                       [56]

	// За данными изминениями очень внимательно следят все анти-читы (для андетекта нужно менять shellCode)
	BYTE shell_code[] = { 0x48, 0xBA }; // mov .. 8bd8  { 0x8B, 0xD8 }
	BYTE shell_code_end[] = { 0xFF, 0xE2 }; // jmp .. eb29 { 0xEB, 0x29 }

	// Подготавливаем инструкции к написанию
	RtlSecureZeroMemory(&orig, sizeof(orig));
	memcpy((PVOID)((ULONG_PTR)orig), &shell_code, sizeof(shell_code));

	// Получаем адресс перехвата
	uintptr_t hook_address = (uintptr_t)(kernel_function_address);
	memcpy((PVOID)((ULONG_PTR)orig + sizeof(shell_code)), &hook_address, sizeof(void*));
	memcpy((PVOID)((ULONG_PTR)orig + sizeof(shell_code) + sizeof(void*)), &shell_code_end, sizeof(shell_code_end));

	// Хук
	WriteToReadOnlyMemory(function, &orig, sizeof(orig));

	return TRUE;
}


NTSTATUS HookHandler(PVOID called_param)
{
	return STATUS_SUCCESS;
}