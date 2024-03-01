#include "hook.h"


NTSTATUS DriverEntry(IN PDRIVER_OBJECT driver_object, IN PUNICODE_STRING register_path)
{
	UNREFERENCED_PARAMETER(driver_object);
	UNREFERENCED_PARAMETER(register_path);

	CallKernelFunction(&HookHandler);

	return STATUS_SUCCESS;
}