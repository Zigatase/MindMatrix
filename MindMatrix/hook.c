#include "hook.h"


BOOL CallKernelFunction(void* kernel_function_address)
{
	if (!kernel_function_address)
		return FALSE;

	// ������ ���� https://github.com/23splat/NtOpenCompositionSurfaceSwapChainHandleInfo/blob/main/main.cpp
	// ���� � �������� ������� ����� ������� | �������� ������� � ��������
	PVOID* function = (PVOID*)(GetSystemModuleExport("\\SystemRoot\\System32\\drivers\\dxgkrnl.sys",
																	"NtOpenCompositionSurfaceSwapChainHandleInfo")); // NtQueryCompositionSurfaceStatistics

	if (!function)
		return FALSE;

	// 12 byte ��� ����
	BYTE orig[] = { 0x4C, 0x89, 0x44, 0x24, 0x18, 0x48, 0x89, 0xC2, 0x40, 0x08, 0x53, 0x56 };

	// �� ������� ����������� ����� ����������� ������ ��� ����-���� (��� ��������� ����� ������ shell code)
	BYTE shell_code[] = { 0x48, 0xB8 }; // mov rax, xxx
	BYTE shell_code_end[] = { 0xFF, 0xE0 }; // jmp rax

	// �������������� ���������� � ���������
	RtlSecureZeroMemory(&orig, sizeof(orig));
	memcpy((PVOID)((ULONG_PTR)orig), &shell_code, sizeof(shell_code));

	// �������� ������ ���������
	uintptr_t hook_address = (uintptr_t)(kernel_function_address);
	memcpy((PVOID)((ULONG_PTR)orig + sizeof(shell_code)), &hook_address, sizeof(void*));
	memcpy((PVOID)((ULONG_PTR)orig + sizeof(shell_code) + sizeof(void*)), &shell_code_end, sizeof(shell_code_end));

	// ���
	WriteToReadOnlyMemory(function, &orig, sizeof(orig));

	return TRUE;
}


NTSTATUS HookHandler(PVOID called_param)
{
	return STATUS_SUCCESS;
}