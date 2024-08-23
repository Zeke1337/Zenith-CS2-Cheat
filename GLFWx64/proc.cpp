#include "proc.h"

HANDLE hProc;


DWORD GetProcId(const wchar_t* procName)
{
    DWORD procId = 0;

    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnap != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 procEntry;

        procEntry.dwSize = sizeof(procEntry);

        if (Process32First(hSnap, &procEntry))
        {
            do
            {
                if (!_wcsicmp(procName, procEntry.szExeFile))
                {
                    procId = procEntry.th32ProcessID;
                    break;
                }

            } while (Process32Next(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);

    return procId;
}

uintptr_t GetModuleBaseAddr(DWORD procId, const wchar_t* modName)
{
    uintptr_t moduleBase = 0;

    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32 | TH32CS_SNAPMODULE, procId);

    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);

        if (Module32First(hSnap, &modEntry))
        {
            do
            {
                if (!_wcsicmp(modName, modEntry.szModule))
                {
                    moduleBase = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }

            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);

    return moduleBase;
}

uintptr_t FinDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int>offsets)
{
    uintptr_t addr = ptr;
    for (unsigned int i = 0; i < offsets.size(); ++i)
    {
        ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
        addr += offsets[i];
    }
    return addr;
}

// Specialized function for reading an array of characters (a string)
void Memory::ReadString(const uintptr_t& address, char* buffer, SIZE_T size)
{
    ReadProcessMemory(hProc, reinterpret_cast<const void*>(address), buffer, size, 0);
    buffer[size - 1] = '\0';  // Ensure null-termination
}


