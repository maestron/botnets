
#include < windows.h >
#include < stdio.h >
//#include "rebel-strings.cpp"

DWORD WINAPI CRC32( char *szApi, DWORD dwApiLen );
char *WINAPI eL_NextStr( char *szPointer );
DWORD WINAPI eL_StrLen( char *szPointer );


int
main ( )
{
	static char szApis[ ]	=
	"================[ kernel32 ]=======================\0"
	"FindFirstFileW\0FindNextFileW\0CreateProcessW\0RegEnumValueW\0"
	
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
	DWORD	dwCrc;

	printf( "static DWORD dwApiCrc[ ] = {\n" );
	while ( pPnt != NULL )
	{
		dwCrc = CRC32( pPnt, eL_StrLen( pPnt ) );
		printf( "\t0x%.8x,\t// %s\n", dwCrc, pPnt );
		pPnt = eL_NextStr( pPnt );
	} // end while
	printf( "};\n" );


	return 0;
}


/*
================
CRC32
================
*/
DWORD 
WINAPI CRC32( char *szApi, DWORD dwApiLen )
{
	DWORD dwCRC;

	__asm
	{
		// (c) crc32 by billy belcebu 'hz
		pushad
		mov esi,[szApi]
		mov edi,[dwApiLen]
		cld
		xor ecx,ecx
		dec ecx
		mov edx,ecx
	NextByteCRC:
			xor eax,eax
			xor ebx,ebx
			lodsb
			xor al,cl
			mov cl,ch
			mov ch,dl
			mov dl,dh
			mov dh,8
		NextBitCRC:
				shr bx,1
				rcr ax,1
				jnc NoCRC
				xor ax,08320h
				xor bx,0EDB8h
			NoCRC:
				dec dh
				jnz NextBitCRC

			xor ecx,eax
			xor edx,ebx
			dec edi

		jnz NextByteCRC
		not edx
		not ecx
		mov eax,edx
		rol eax,10h
		mov ax,cx
		mov [dwCRC],eax
		popad
	}
	
	return dwCRC;
} // end of function CRC32

/*
================
eL_NextStr
================
*/
char *
WINAPI eL_NextStr( char *szPointer )
{
	__asm
	{
		pushad
		mov		esi,[szPointer]
		push	esi
		call	eL_StrLen
		add		esi,eax
		inc		esi
		lodsb
		dec		esi
		test	al,al
		jnz		__to_exit
		xor		esi,esi
	__to_exit:
		mov		[szPointer],esi
		popad
	} // end asm

	return szPointer;
} // end of fucntion eL_NextStr


/*
================
eL_StrLen
================
*/
DWORD 
WINAPI eL_StrLen( char *szPointer )
{
	DWORD iCounter;

	__asm
	{
		pushad
		xor		ecx,ecx
		mov		esi,[szPointer]
	__again:
			lodsb
			test	al,al
			jz		__to_exit
			inc		ecx
			jmp		__again
	__to_exit:
		mov		[iCounter], ecx
		popad
	}// end asm

	return iCounter;
} // end of fucntion eL_StrLen