#include "hook.h"


bool nullHook::CallKernelFunction(void* kernel_function_address)
{
	if (!kernel_function_address)
		return FALSE;

	// ���� � �������� ������� ����� ������� | �������� ������� � ��������
	PVOID* function = reinterpret_cast<PVOID*>(GetSystemModuleExport("\\SystemRoot\\System32\\drivers\\dxgkrnl.sys",
																	"NtSetCompositionSurfaceStatistics"));

	if (!function)
		return FALSE;

	// 12 byte ��� ����
	BYTE orig[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	// �� ������� ����������� ����� ����������� ������ ��� ����-���� (��� ��������� ����� ������ shell code)
	BYTE shell_code[] = { 0x48, 0xB8 }; // mov rax, xxx
	BYTE shell_code_end[] = { 0xFF, 0xE0 }; // jmp rax

	// �������������� ���������� � ���������
	RtlSecureZeroMemory(&orig, sizeof(orig));
	memcpy((PVOID)((ULONG_PTR)orig), &shell_code, sizeof(shell_code));

	// �������� ������ ���������
	uintptr_t hook_address = reinterpret_cast<uintptr_t>(kernel_function_address);
	memcpy((PVOID)((ULONG_PTR)orig + sizeof(shell_code)), &hook_address, sizeof(void*));
	memcpy((PVOID)((ULONG_PTR)orig + sizeof(shell_code) + sizeof(void*)), &shell_code_end, sizeof(shell_code_end));

	// ���
	WriteToReadOnlyMemory(function, &orig, sizeof(orig));

	return TRUE;
}


NTSTATUS nullHook::HookHandler(PVOID called_param)
{
	return STATUS_SUCCESS;
}