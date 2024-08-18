#include "server.h"




std::string SendPostRequest(const std::wstring& server, const std::wstring& path, const std::string& data) {
    
    std::string response;

    // Initialize WinHTTP
    HINTERNET hSession = WinHttpOpen(L"A WinHTTP Example Program/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (hSession) {
        // Connect to the server
        HINTERNET hConnect = WinHttpConnect(hSession, server.c_str(), INTERNET_DEFAULT_HTTP_PORT, 0);
        if (hConnect) {
            // Create an HTTP request handle
            HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"POST", path.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
            if (hRequest) {
                // Set request headers
                const wchar_t* headers = L"Content-Type: application/x-www-form-urlencoded";
                WinHttpAddRequestHeaders(hRequest, headers, (ULONG)-1L, WINHTTP_ADDREQ_FLAG_ADD);

                // Send the request
                BOOL bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, (LPVOID)data.c_str(), (DWORD)data.size(), (DWORD)data.size(), 0);
                if (bResults) {
                    // Receive the response
                    bResults = WinHttpReceiveResponse(hRequest, NULL);
                    if (bResults) {
                        // Keep checking for data until there is nothing left.
                        DWORD dwSize = 0;
                        DWORD dwDownloaded = 0;
                        LPSTR pszOutBuffer;
                        do {
                            dwSize = 0;
                            if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) {
                                std::cerr << "Error " << GetLastError() << " in WinHttpQueryDataAvailable.\n";
                            }

                            // Allocate space for the buffer.
                            pszOutBuffer = new char[dwSize + 1];
                            if (!pszOutBuffer) {
                                std::cerr << "Out of memory\n";
                                dwSize = 0;
                            }
                            else {
                                // Read the data.
                                ZeroMemory(pszOutBuffer, dwSize + 1);

                                if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded)) {
                                    std::cerr << "Error " << GetLastError() << " in WinHttpReadData.\n";
                                }
                                else {
                                    response.append(pszOutBuffer, dwDownloaded);
                                }

                                // Free the memory allocated to the buffer.
                                delete[] pszOutBuffer;
                            }
                        } while (dwSize > 0);
                    }
                }
                else {
                    std::cerr << "WinHttpSendRequest failed: " << GetLastError() << "\n";
                }
                // Close the request handle.
                WinHttpCloseHandle(hRequest);
            }
            // Close the connect handle.
            WinHttpCloseHandle(hConnect);
        }
        // Close the session handle.
        WinHttpCloseHandle(hSession);
    }
    return response;
}

bool valid()
{
    
    std::wstring server = L"Your Website";
    std::wstring path = L"/Your Website´s php Login Page (login.php)";
    std::string motherboardId = optain();
    std::string userInput1;
    printf("Enter Username:");
    std::getline(std::cin, userInput1);
    printf("\n");
    std::string userInput2;
    printf("Enter Password:");
    std::getline(std::cin, userInput2);
    printf("\n");

    std::string data = "username=" + userInput1 + "&password=" + userInput2 + "&motherboardId=" + motherboardId;

    std::string response = SendPostRequest(server, path, data);

    if (response.find("\"status\":\"success\"") != std::string::npos) {
        std::cout << "Login Successful!" << std::endl;
        std::cout << "Press any key to continue" << std::endl;
        getchar();
        return true;
    }
    else {
        std::cout << "Username or Password is incorrect." << std::endl;
        getchar();
        return false;
    }
    
    return false;
}
