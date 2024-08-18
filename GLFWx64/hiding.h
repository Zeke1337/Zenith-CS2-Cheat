#pragma once
#include <windows.h>
#include <iostream>
#include <tlhelp32.h>
#include <winternl.h>
#include <string>
#include <stdexcept>  // Für Ausnahmebehandlung
#include <psapi.h> // Include psapi.h for GetModuleFileNameExA and EnumProcessModules
#include <chrono>
#include <thread>

#pragma comment(lib, "psapi.lib") // Link against psapi.lib

int InitDebug();