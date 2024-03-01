#ifndef HOOK_H_
#define HOOK_H_

#include "memory.h"

BOOL CallKernelFunction(void* kernel_function_address);
NTSTATUS HookHandler(PVOID called_param);

#endif // !HOOK_H_
