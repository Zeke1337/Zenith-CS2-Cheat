#include "hiding.h"

// Definitionen für den direkten Zugriff auf die NT-API
typedef NTSTATUS(NTAPI* NtSetInformationProcessPtr)(
    HANDLE ProcessHandle,
    ULONG ProcessInformationClass,
    PVOID ProcessInformation,
    ULONG ProcessInformationLength
    );

typedef NTSTATUS(NTAPI* NtQueryInformationProcessPtr)(
    HANDLE ProcessHandle,
    ULONG ProcessInformationClass,
    PVOID ProcessInformation,
    ULONG ProcessInformationLength,
    PULONG ReturnLength
    );

void HideThread(HANDLE hThread) {
    HMODULE hNtDll = LoadLibraryA("ntdll.dll");
    if (!hNtDll) return;

    auto NtSetInformationThread = (NtSetInformationProcessPtr)GetProcAddress(hNtDll, "NtSetInformationThread");
    if (NtSetInformationThread) {
        NTSTATUS status = NtSetInformationThread(hThread, 0x11, nullptr, 0);
        if (status == 0) {
            //std::cout << "Thread hidden successfully." << std::endl;
        }
    }
}

void ProtectProcess() {
    HMODULE hNtDll = LoadLibraryA("ntdll.dll");
    if (!hNtDll) return;

    NtSetInformationProcessPtr NtSetInformationProcess =
        (NtSetInformationProcessPtr)GetProcAddress(hNtDll, "NtSetInformationProcess");

    ULONG NoDebugInherit = 1;
    if (NtSetInformationProcess) {
        NTSTATUS status = NtSetInformationProcess(GetCurrentProcess(),
            0x1F,  // ProcessDebugFlags
            &NoDebugInherit,
            sizeof(NoDebugInherit));
        if (status == 0) {
            //std::cout << "Process protection enabled." << std::endl;
        }
    }
}

bool IsDebuggerPresentInternal() {
    BOOL processFlags = FALSE;
    CheckRemoteDebuggerPresent(GetCurrentProcess(), &processFlags);
    return processFlags != 0;
}

bool BeingDebugged() {
#ifdef _WIN64
    PEB* peb = (PEB*)__readgsqword(0x60);  // Use __readgsqword for 64-bit architecture
#else
    PEB* peb = (PEB*)__readfsdword(0x30);  // Use __readfsdword for 32-bit architecture
#endif
    return peb->BeingDebugged;
}

void AntiDebuggingTechniques() {
    if (IsDebuggerPresent() || IsDebuggerPresentInternal() || BeingDebugged()) {
        std::cerr << "Debugger detected! Terminating process." << std::endl;
        ExitProcess(0);
    }
}



void ObfuscateCode() {
#ifdef _WIN64
    // x64 does not support inline assembly; this is just a placeholder function.
    // You could apply code virtualization or other techniques.
#else
    __asm {
        xor eax, eax
        mov eax, fs: [0x30]
        movzx eax, byte ptr[eax + 2]
        test eax, eax
        jz no_debug
        int 3
        no_debug :
        nop
    }
#endif
}

void RemoveDebugger() {
    HMODULE hNtDll = LoadLibraryA("ntdll.dll");
    if (!hNtDll) return;

    NtQueryInformationProcessPtr NtQueryInformationProcess =
        (NtQueryInformationProcessPtr)GetProcAddress(hNtDll, "NtQueryInformationProcess");

    ULONG debugPort = 0;
    if (NtQueryInformationProcess) {
        NTSTATUS status = NtQueryInformationProcess(GetCurrentProcess(), 0x07, &debugPort, sizeof(debugPort), nullptr);
        if (status == 0 && debugPort) {
            std::cerr << "Debugger port detected! Terminating process." << std::endl;
            ExitProcess(0);
        }
    }
}

void HideModules() {
    HMODULE hMods[1024];
    HANDLE hProcess = GetCurrentProcess();
    DWORD cbNeeded;

    if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
        for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
            char szModName[MAX_PATH];
            if (GetModuleFileNameExA(hProcess, hMods[i], szModName, sizeof(szModName) / sizeof(char))) {
                if (strstr(szModName, "dbghelp.dll") || strstr(szModName, "ntdll.dll")) {
                    //std::cerr << "Debugger-related module detected! Terminating process." << std::endl;
                    ExitProcess(0);
                }
            }
        }
    }
}

int InitDebug() {
    ProtectProcess();
    HideThread(GetCurrentThread());
    AntiDebuggingTechniques();
    //ObfuscateCode();
    RemoveDebugger();
    //HideModules();

    return 0;
}
