
#include < windows.h >
#include < stdio.h >
#include "rebel-strings.cpp"

int
main ( )
{
	static char szApis[ ]	=
	"================[ kernel32 ]=======================\0"
	"CloseHandle\0CopyFileA\0CreatePipe\0"
	"CreateProcessA\0CreateRemoteThread\0"
	"CreateToolhelp32Snapshot\0CreateThread\0"
	"ExitProcess\0ExitThread\0GetCurrentProcess\0"
	"GetCurrentProcessId\0GetCurrentThreadId\0"
	"GetExitCodeProcess\0GetFileAttributesA\0"
	"GetLastError\0GetModuleFileNameA\0"
	"GetModuleHandleA\0GetProcAddress\0"
	"GetStartupInfoA\0GetVersionExA\0"
	"GetWindowsDirectoryA\0LoadLibraryA\0"
	"OpenProcess\0OpenThread\0PeekNamedPipe\0"
	"Process32First\0Process32Next\0ReadFile\0"
	"ResumeThread\0Sleep\0SuspendThread\0"
	"TerminateProcess\0Thread32First\0"
	"Thread32Next\0VirtualAllocEx\0VirtualFreeEx\0"
	"VirtualQueryEx\0VirtualProtect\0VirtualProtectEx\0"
	"WideCharToMultiByte\0WriteFile\0WriteProcessMemory\0"
	"=================[ advapi 32 ]=====================\0"
	"AdjustTokenPrivileges\0LookupPrivilegeValueA\0"
	"OpenProcessToken\0RegSetValueExA\0RegCreateKeyA\0"
	"=================[ ws2_32 ]========================\0"
	"WSACleanup\0WSAStartup\0accept\0bind\0closesocket\0"
	"htons\0ioctlsocket\0listen\0recv\0send\0socket\0";

	char *pPnt = szApis;
	char szBuf[ 256 ];
	DWORD	dwCrc;

	printf( "typedef struct _apis {\n" );
	while ( pPnt != NULL )
	{
		eL_StrCpy( szBuf, pPnt );
		eL_UpperCase( szBuf );
		printf( "\tP%s\t\tp%s;\n",szBuf, pPnt );
		pPnt = eL_NextStr( pPnt );
	} // end while
	printf( "} APIS; // end _apis\n" );


	return 0;
}