#pragma once
#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>   
#include "datatypes.h"

DWORD GetProcId(const wchar_t* procName);

uintptr_t GetModuleBaseAddr(DWORD procId, const wchar_t* modName);

uintptr_t FinDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int>offsets);

extern HANDLE hProc;

namespace Memory
{

    template <typename T>
    const T RPM(const uintptr_t& address)
    {
        T value = {};
        ReadProcessMemory(hProc, reinterpret_cast<const void*>(address), &value, sizeof(T), 0);
        return value;
    }

    template <typename U>
    const void WPM(const uintptr_t& address, const U& value)
    {
        WriteProcessMemory(hProc, reinterpret_cast<void*>(address), &value, sizeof(U), 0);
    }

    void ReadString(const uintptr_t& address, char* buffer, SIZE_T size);


}