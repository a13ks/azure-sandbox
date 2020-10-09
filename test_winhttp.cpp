#include <stdio.h>
#include <windows.h>
#include <winhttp.h>

#include <chrono>
#include <thread>

#pragma comment(lib, "winhttp.lib")

static void CALLBACK callback(HINTERNET hInternet, DWORD_PTR dwContext, DWORD dwInternetStatus, _In_ void* lpvStatusInfo, DWORD dwStatusInfoLength)
{
    printf("dwInternetStatus = %x\n", dwInternetStatus);

    if (dwInternetStatus == WINHTTP_CALLBACK_STATUS_DATA_AVAILABLE)
    {
        const DWORD data_sz = *((DWORD*)lpvStatusInfo);
        char* buf = new char [data_sz];
        if (!WinHttpReadData(hInternet, (LPVOID)buf, data_sz, nullptr))
        {
            printf("WinHttpReadData failed %d.\n", GetLastError());
        }
        delete[] buf;
    }
    else if (dwInternetStatus == WINHTTP_CALLBACK_STATUS_SENDREQUEST_COMPLETE)
    {
        if (!WinHttpReceiveResponse(hInternet, nullptr))
        {
            printf("WinHttpReceiveResponse failed %d.\n", GetLastError());
        }
    }
    else if (dwInternetStatus == WINHTTP_CALLBACK_STATUS_HEADERS_AVAILABLE)
    {
        if (!WinHttpQueryDataAvailable(hInternet, nullptr))
        {
            printf("WinHttpQueryDataAvailable failed %d.\n", GetLastError());
        }
    }
    else if (dwInternetStatus == WINHTTP_CALLBACK_STATUS_REDIRECT)
    {
        printf("REDIRECT SPOTTED!\n");
    }
}

int main(int argc, char **argv)
{
    BOOL  bResults = FALSE;
    HINTERNET hSession = NULL,
              hConnect = NULL,
              hRequest = NULL;

    // Use WinHttpOpen to obtain a session handle.
    hSession = WinHttpOpen(  L"A WinHTTP Example Program/1.0", 
                             WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                             WINHTTP_NO_PROXY_NAME, 
                             WINHTTP_NO_PROXY_BYPASS, 
                             WINHTTP_FLAG_ASYNC);

    // Specify an HTTP server.
    if (hSession)
        hConnect = WinHttpConnect( hSession, L"gmail.com",
                                   INTERNET_DEFAULT_HTTP_PORT, 0);

    // Create an HTTP Request handle.
    if (hConnect)
        hRequest = WinHttpOpenRequest( hConnect, L"GET", 
                                       L"/", 
                                       NULL, WINHTTP_NO_REFERER, 
                                       WINHTTP_DEFAULT_ACCEPT_TYPES, 
                                       0);

    // Send a Request.
    if (hRequest) 
    {
        if (!WinHttpSetStatusCallback( hRequest, &callback, WINHTTP_CALLBACK_FLAG_ALL_COMPLETIONS | 
            WINHTTP_CALLBACK_FLAG_SECURE_FAILURE | WINHTTP_CALLBACK_FLAG_SEND_REQUEST | WINHTTP_CALLBACK_STATUS_REDIRECT, NULL))
        {
            printf("WinHttpSetStatusCallback failed %d.\n", GetLastError());
        }

        bResults = WinHttpSendRequest( hRequest, 
                                       WINHTTP_NO_ADDITIONAL_HEADERS,
                                       0, WINHTTP_NO_REQUEST_DATA, 0, 
                                       0, 0);

    }


    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Place additional code here.


    // Report errors.
    if (!bResults)
        printf("Error %d has occurred.\n",GetLastError());

    // Close open handles.
    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);
    return 0;
}
