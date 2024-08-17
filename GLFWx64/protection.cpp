#include "protection.h"

void logDetection(const std::string& method, const std::string& detail = "") {
    std::ofstream logFile("debug_detection.log", std::ios_base::app);
    if (logFile.is_open()) {
        logFile << "Debugger detected by method: " << method;
        if (!detail.empty()) {
            logFile << ", Detail: " << detail;
        }
        logFile << std::endl;
        logFile.close();
    }
}

// Typedef for NtQueryInformationProcess, used to query process information
typedef NTSTATUS(NTAPI* pNtQueryInformationProcess)(
    HANDLE ProcessHandle,               // Handle to the process
    UINT ProcessInformationClass,       // Information class being queried
    PVOID ProcessInformation,           // Buffer to receive the information
    ULONG ProcessInformationLength,     // Size of the buffer
    PULONG ReturnLength                 // Optional pointer to receive the actual size of the information
    );

// Define NT_SUCCESS if not already defined, used to check status codes
#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif

// Define PROCESSINFOCLASS if not already defined, used for querying process information
typedef enum _PROCESSINFOCLASS {
    ProcessBasicInformation = 0,   // Basic information about the process
    ProcessDebugPort = 7           // Debug port information
} PROCESSINFOCLASS;

// Define the PEB structure (Process Environment Block)
typedef struct _PEB {
    BOOLEAN InheritedAddressSpace;
    BOOLEAN ReadImageFileExecOptions;
    BOOLEAN BeingDebugged;             // Flag indicating if the process is being debugged
    BOOLEAN Spare;
    HANDLE Mutant;
    PVOID ImageBaseAddress;
    PVOID LoaderData;
    PVOID ProcessParameters;
    PVOID SubSystemData;
    PVOID ProcessHeap;
    PVOID FastPebLock;
    PVOID AtlThunkSListPtr;
    PVOID SparePtr2;
    ULONG EnvironmentUpdateCount;
    PVOID KernelCallbackTable;
    PVOID EventLogSection;
    PVOID EventLog;
    PVOID FreeList;
    ULONG TlsExpansionCounter;
    PVOID TlsBitmap;
    ULONG TlsBitmapBits[2];
    PVOID ReadOnlySharedMemoryBase;
    PVOID ReadOnlySharedMemoryHeap;
    PVOID ReadOnlyStaticServerData;
    PVOID AnsiCodePageData;
    PVOID OemCodePageData;
    PVOID UnicodeCaseTableData;
    ULONG NumberOfProcessors;
    ULONG NtGlobalFlag;
    LARGE_INTEGER CriticalSectionTimeout;
    SIZE_T HeapSegmentReserve;
    SIZE_T HeapSegmentCommit;
    SIZE_T HeapDeCommitTotalFreeThreshold;
    SIZE_T HeapDeCommitFreeBlockThreshold;
    ULONG NumberOfHeaps;
    ULONG MaximumNumberOfHeaps;
    PVOID ProcessHeaps;
    PVOID GdiSharedHandleTable;
    PVOID ProcessStarterHelper;
    ULONG GdiDCAttributeList;
    PVOID LoaderLock;
    ULONG OSMajorVersion;
    ULONG OSMinorVersion;
    ULONG OSBuildNumber;
    ULONG OSPlatformId;
    ULONG ImageSubsystem;
    ULONG ImageSubsystemMajorVersion;
    ULONG ImageSubsystemMinorVersion;
    ULONG ActiveProcessAffinityMask;
    ULONG GdiHandleBuffer[34];
    PVOID PostProcessInitRoutine;
    PVOID TlsExpansionBitmap;
    ULONG TlsExpansionBitmapBits[32];
    ULONG SessionId;
} PEB, * PPEB;

bool checkRunningProcesses(const std::vector<std::string>& processNames) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        logDetection("CreateToolhelp32Snapshot failed");
        return false;
    }

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &pe)) {
        do {
            char exeFileName[MAX_PATH];
            size_t convertedChars = 0;
            wcstombs_s(&convertedChars, exeFileName, pe.szExeFile, MAX_PATH);

            for (const auto& processName : processNames) {
                if (_stricmp(exeFileName, processName.c_str()) == 0) {
                    //std::cout << "Detected forbidden process: " << processName << std::endl;
                    //logDetection("Process", processName);
                    CloseHandle(hSnapshot);
                    return true;
                }
            }
        } while (Process32Next(hSnapshot, &pe));
    }

    CloseHandle(hSnapshot);
    return false;
}


// Function to check if the current process is being debugged using IsDebuggerPresent API
bool CheckIsDebuggerPresent() {
    return IsDebuggerPresent() != 0;  // Returns true if a debugger is present
}

// Function to check if a debugger is present using CheckRemoteDebuggerPresent API
bool CheckRemoteDebugger() {
    BOOL debuggerPresent = FALSE;
    // Checks if a remote debugger is present for the current process
    CheckRemoteDebuggerPresent(GetCurrentProcess(), &debuggerPresent);
    return debuggerPresent != 0;  // Returns true if a debugger is present
}

// Function to check if the process is being debugged using NtQueryInformationProcess to query the ProcessDebugPort
bool CheckNtQueryInformationProcess() {
    HMODULE hNtDll = LoadLibrary(TEXT("ntdll.dll"));  // Load the ntdll library
    if (!hNtDll) return false;  // If loading fails, return false

    // Get the address of NtQueryInformationProcess
    pNtQueryInformationProcess NtQIP = (pNtQueryInformationProcess)GetProcAddress(hNtDll, "NtQueryInformationProcess");
    if (!NtQIP) return false;  // If the function is not found, return false

    ULONG debugPort = 0;
    // Query the ProcessDebugPort information class
    NTSTATUS status = NtQIP(GetCurrentProcess(), ProcessDebugPort, &debugPort, sizeof(debugPort), NULL);

    FreeLibrary(hNtDll);  // Free the library
    return (status == 0 && debugPort != 0);  // Return true if a debug port is found
}

// Function to check the PEB (Process Environment Block) for the BeingDebugged flag
bool CheckPEB() {
    __try {
        // Read the PEB address from the GS segment and check the BeingDebugged flag
        PPEB pPeb = (PPEB)__readgsqword(0x60);
        return pPeb->BeingDebugged != 0;  // Return true if BeingDebugged is set
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;  // If an exception occurs, return false
    }
}

// Function to check if closing an invalid handle causes an exception, indicating a debugger
bool CheckCloseHandleException() {
    __try {
        CloseHandle((HANDLE)0xDEADBEEF);  // Try to close an invalid handle
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return GetExceptionCode() == EXCEPTION_INVALID_HANDLE;  // Return true if the exception code is EXCEPTION_INVALID_HANDLE
    }
    return false;
}

// Function to check if OutputDebugString changes the last error, indicating a debugger
bool CheckOutputDebugString() {
    SetLastError(ERROR_SUCCESS);  // Clear the last error
    OutputDebugString(TEXT("DebuggerCheck"));  // Output a debug string
    return GetLastError() != ERROR_SUCCESS;  // Return true if the last error is changed
}

// Function to check if the process has the SeDebugPrivilege enabled
bool CheckSeDebugPrivilege() {
    HANDLE hToken;
    TOKEN_PRIVILEGES tp;
    LUID luid;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {  // Open the process token
        return false;
    }
    if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid)) {  // Lookup the LUID for SeDebugPrivilege
        CloseHandle(hToken);
        return false;
    }
    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = 0;

    // Get the token information
    if (!GetTokenInformation(hToken, TokenPrivileges, &tp, sizeof(tp), NULL)) {
        CloseHandle(hToken);
        return false;
    }

    CloseHandle(hToken);  // Close the token handle
    return (tp.Privileges[0].Attributes & SE_PRIVILEGE_ENABLED) != 0;  // Return true if SeDebugPrivilege is enabled
}

// Function to check if any hardware breakpoints are set
bool CheckHardwareBreakpoints() {
    CONTEXT ctx = {};
    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
    if (!GetThreadContext(GetCurrentThread(), &ctx)) {  // Get the thread context
        return false;
    }
    // Return true if any of the debug registers are set
    return ctx.Dr0 != 0 || ctx.Dr1 != 0 || ctx.Dr2 != 0 || ctx.Dr3 != 0;
}

// Function to check for VEH (Vectored Exception Handling) debuggers
bool CheckVEH() {
    ULONG handlers[32];
    ULONG count = 0;

    // NtQueryInformationProcess is used to query the process information
    HMODULE ntdll = GetModuleHandle(TEXT("ntdll.dll"));
    if (!ntdll) return false;

    typedef NTSTATUS(NTAPI* pNtQueryInformationProcess)(HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG);
    pNtQueryInformationProcess NtQueryInformationProcess = (pNtQueryInformationProcess)GetProcAddress(ntdll, "NtQueryInformationProcess");

    if (!NtQueryInformationProcess) return false;

    // Query for vectored exception handlers
    NTSTATUS status = NtQueryInformationProcess(GetCurrentProcess(), ProcessBasicInformation, &handlers, sizeof(handlers), &count);
    if (!NT_SUCCESS(status)) return false;

    // Check if there are more handlers than expected (0-2 is typical for a normal process)
    return count > 2;
}

// Function to check for Kernel Debuggers
bool CheckKernelDebugger() {
    BOOL debuggerPresent = FALSE;
    if (CheckRemoteDebuggerPresent(GetCurrentProcess(), &debuggerPresent)) {  // Checks if a remote debugger is present for the current process
        return debuggerPresent;
    }
    return false;
}

std::vector<std::string> processNames = {
    // Common debuggers
    "Cheat Engine.exe", "Cheat Engine 7.5.exe", "cheatengine-x86_64-SSE4-AVX2.exe",
    "ollydbg.exe", "x64dbg.exe", "x32dbg.exe", "ida.exe", "ida64.exe",
    "windbg.exe", "ImmunityDebugger.exe",

    // Reverse engineering tools
    "ghidra.exe", "radare2.exe", "binaryninja.exe", "ghidra.exe", "radare2.exe",
    "Hopper.exe", "Hopper Disassembler.exe", "Cutter.exe", "dnSpy.exe",
    "dnSpy-x86.exe", "dnSpy-x64.exe",

    // Decompilers
    "JD-GUI.exe", "Decompiler.exe", "JEB.exe", "JEB4.exe", "dotPeek.exe",
    "ILSpy.exe", "RetDec.exe", "CFR.exe", "Procyon.exe", "Fernflower.exe",
    "Jadx.exe", "AndroChef.exe", "JavaDecompilers.net.exe", "Mocha.exe",

    // Hex editors
    "HxD.exe", "Hex Fiend.exe", "010 Editor.exe", "Bless.exe", "GHex.exe",
    "Hex Workshop.exe", "Hexinator.exe", "Hexplorer.exe", "XVI32.exe",
    "WinHex.exe", "HxED.exe", "Frhed.exe", "ImHex.exe",

    // Memory editors
    "ArtMoney.exe", "GameConqueror.exe", "Scanmem.exe", "TSearch.exe",
    "L. Spiro Memory Hacking Software.exe", "MHS.exe",

    // Packet sniffers
    "Wireshark.exe", "tcpdump.exe", "Npcap.exe", "WinPcap.exe", "Ettercap.exe",
    "Kismet.exe", "Aircrack-ng.exe",

    // Scripting tools
    "AutoIt3.exe", "AutoHotkey.exe", "WinAutomation.exe", "Macro Express.exe",
    "AutoMe.exe", "Macro Toolworks.exe",

    // Debugger extensions and plugins
    "Scylla.exe", "TitanHide.exe", "xAnalyzer.exe", "xAnalyzer.x32.dbg.exe",
    "xAnalyzer.x64.dbg.exe",

    // System monitoring tools
    "Process Hacker.exe", "Process Explorer.exe", "Process Monitor.exe",
    "System Explorer.exe", "AnVir Task Manager.exe", "Security Task Manager.exe",

    // Virtualization tools
    "VMware.exe", "VMwareTray.exe", "vmwareuser.exe", "vmware-vmx.exe",
    "VirtualBox.exe", "VBoxTray.exe", "VBoxService.exe",

    // Debugger detection tools
    "ScyllaHide.exe", "TitanHide.exe", "VMwareTray.exe", "VBoxTray.exe",
    "vmtoolsd.exe",

    // Other
    "Debugger.exe", "debugger64.exe", "WinDbgX.exe", "syser.exe", "ollydbg64.exe",
    "de4dot.exe", "x64dbg64.exe", "x32dbg64.exe", "DbgView.exe"
};


bool IsBeingDebugged() {
    if (checkRunningProcesses(processNames))
    {
        return true;
    }
    if (CheckIsDebuggerPresent()) {
        //logDetection("CheckIsDebuggerPresent detected a debugger.");
        return true;
    }
    if (CheckRemoteDebugger()) {
        //logDetection("CheckRemoteDebugger detected a debugger.");
        return true;
    }
    if (CheckNtQueryInformationProcess()) {
        //logDetection("CheckNtQueryInformationProcess detected a debugger.");
        return true;
    }
    if (CheckPEB()) {
        //PEB();
        //logDetection("CheckPEB detected a debugger.");
        return true;
    }
    if (CheckCloseHandleException()) {
        //logDetection("CheckCloseHandleException detected a debugger.");
        return true;
    }
    if (CheckOutputDebugString()) {
        //logDetection("CheckOutputDebugString detected a debugger.");
        return true;
    }
    if (CheckSeDebugPrivilege()) {
        //logDetection("CheckSeDebugPrivilege detected a debugger.");
        return true;
    }
    if (CheckHardwareBreakpoints()) {
        //logDetection("CheckHardwareBreakpoints detected a debugger.");
        return true;
    }
    if (CheckVEH()) {
        //logDetection("CheckVEH detected a debugger.");
        return true;
    }
    if (CheckKernelDebugger()) {
        //logDetection("CheckKernelDebugger detected a debugger.");
        return true;
    }
    return false;
}

int Checking() {
    while (true) {
        if (IsBeingDebugged()) {
            //logDetection("DEBUG DETECTED");
            std::exit(0);
        }
        else {
        }
        std::this_thread::sleep_for(std::chrono::seconds(5)); // Sleep for 10 seconds
    }

    return 0;
}
