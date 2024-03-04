#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <memory>
#include <string_view>
#include <cstdint>
#include <vector>

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

uintptr_t base_address = 0;
uint32_t process_id = 0;

template<typename ... Arg>
uint64_t CallHook(const Arg ... args)
{
    // Экспорт функции
    void* hooked_func = GetProcAddress(LoadLibrary("win32u.dll"), "NtOpenCompositionSurfaceSwapChainHandleInfo");

    // Делаем стат првидение и вызов
    auto func = static_cast<uint64_t(_stdcall*)(Arg...)>(hooked_func);

    return func(args ...);
}


// Получаем индификатор процесса
struct HandleDisposer
{
    using pointere = HANDLE;
    void operator()(HANDLE handle) const
    {
        if (handle != NULL || handle != INVALID_HANDLE_VALUE)
        {
            CloseHandle(handle);
        }
    }
};

using unique_handle = std::unique_ptr<HANDLE, HandleDisposer>;

static std::uint32_t GetProcessId(std::string_view process_name)
{
    PROCESSENTRY32 entry;
    HANDLE process = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    const unique_handle snapshot_handle(&process);

    if (snapshot_handle.get() == INVALID_HANDLE_VALUE)
        return NULL;

    entry.dwSize = sizeof(MODULEENTRY32);

    while (Process32Next(snapshot_handle.get(), &entry) == TRUE)
    {
        if (process_name.compare(entry.szExeFile) == NULL)
            return entry.th32ProcessID;
    }
}

int main()
{
    std::cout << "Hello World!\n";
}