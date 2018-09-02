#include "include.h"
#include "extern.h"

char *http_filetohtml(char *file)
/* replace '\\' with '/' */
{
	unsigned int c;
	for(c = 0; c < strlen(file); c++)
	{
		if(file[c] == '\\') 
			file[c] = '/';
	}
	return file;
}

void http_checkfile(struct httpds httpd, char *rFile)
/* check if file can be sent */
{
	unsigned long c;
	unsigned long d;
	char file[256];
	char nFile[256];
	char tFile[256];
	bool directory = false;
	memset(nFile, 0, sizeof(nFile));
	if(rFile[0] != '/') 
		_snprintf(file, sizeof(file) - 1, "\\%s", rFile);
	else
	{
		rFile[0] = '\\';
		strncpy(file, rFile, sizeof(file) - 1);
	}
	for(c = 0, d = 0; c < strlen(file); c++, d++)
	{
		if((((c + 2 < strlen(file) && file[c] == '%' && file[c+1] == '2' && file[c+2] == '0'))))
		{
			nFile[d] = ' ';
			c += 2;
		}
		else
			nFile[d] = (file[c] == '/') ? '\\': file[c];
	}
	_snprintf(tFile, sizeof(tFile) - 1, "%s%s", httpd.dir, nFile);
	strtok(tFile, "\n");
	switch(GetFileAttributes(tFile))
	{
		case FILE_ATTRIBUTE_DIRECTORY:
			directory = true;
			break;
		case 0xFFFFFFFF:
			closesocket(httpd.sock);
			return;
		default:
			break;
	}
	if(nFile[d-1] == '\\') 
		directory = true;
	if(directory)
	{
		strncat(tFile, "*", sizeof(tFile) - 1);
		strncpy(httpd.file, tFile, sizeof(tFile) - 1);
		http_filetohtml(nFile);
		strncpy(httpd.path, nFile, sizeof(httpd.path) - 1);
		httpd.type = true;
		httpd.length = -1;
	}
	else
	{
		HANDLE testfile = CreateFile(tFile, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
      	if(testfile != INVALID_HANDLE_VALUE)
		{
			strncpy(httpd.file, tFile, sizeof(httpd.file) - 1);
			httpd.type = false;
			httpd.length = GetFileSize(testfile, 0);
			CloseHandle(testfile);
		}
	}
	httpd.gotinfo = false;
	if(!CreateThread(0, 131072, http_header, &httpd, 0, 0))
		return;
	while(!httpd.gotinfo)
		Sleep(10);
}

void http_getfiles(SOCKET sock, char *current, const char *url)
/* send list of files in the directory */
{
	int count = 0;
	int count2 = 0;
	unsigned int COL1 = 230;
	unsigned int COL2 = 150;
	unsigned int COL3 = 60;
	unsigned int FILESIZE = 30;
	char parent[256];
	char tmpDate[40];
	char tmpDir[256];
	char buf[512];
	HANDLE Hnd;
	FILETIME ftBuf;
	SYSTEMTIME stBuf;
	WIN32_FIND_DATA WFD;
	memset(parent, 0, sizeof(parent));
	strtok(current, "\n");
	if(url)
	{
		current[(strlen(current)-1)] = 0;
		_snprintf(buf, sizeof(buf), "<HTML>\r\n<HEAD>\r\n<TITLE>Index of %s</TITLE>\r\n</HEAD>\r\n<BODY>\r\n", current);
		send(sock, buf, strlen(buf), 0);
		_snprintf(buf, sizeof(buf), "<H1>Index of %s</H1>\r\n<TABLE BORDER=\"0\">\r\n", current);
		send(sock, buf, strlen(buf), 0);
		current[(strlen(current))] = '*';
		_snprintf(buf, sizeof(buf), "<TR>\r\n<TD WIDTH=\"%d\"><CODE>Name</CODE></TD>\r\n<TD WIDTH=\"%d\"><CODE>Last Modified</CODE></TD>\r\n<TD WIDTH=\"%d\" ALIGN=\"right\"><CODE>Size</CODE></TD>\r\n</TR>\r\n", COL1, COL2, COL3);
		send(sock, buf, strlen(buf), 0);
		_snprintf(buf, sizeof(buf), "<TR>\r\n<TD COLSPAN=\"3\"><HR></TD>\r\n</TR>\r\n");
		send(sock, buf, strlen(buf), 0);
	}
	else
	{
		_snprintf(buf, sizeof(buf), "Searching for: %s\r\n", current);
		send(sock, buf, strlen(buf), 0);
	}
	if(url && strlen(url) > 2)
	{
		unsigned int c;
		for(c = strlen(url) - 3; c != 0; c--)
		{
			if(url[c] == '/') 
				break;
		}
		strncpy(parent, url, c + 1);
		_snprintf(buf, sizeof(buf), "<TR>\r\n<TD COLSPAN=\"3\"><A HREF=\"%s\"><CODE>Parent Directory</CODE></A></TD>\r\n</TR>\r\n", parent);
		send(sock, buf, strlen(buf), 0);
	}
	Hnd = FindFirstFile(current, &WFD);
	while(FindNextFile(Hnd, &WFD))
	{
		if(WFD.dwFileAttributes && strcmp(WFD.cFileName, "..") && strcmp(WFD.cFileName, "."))
		{
			FileTimeToLocalFileTime(&WFD.ftLastWriteTime, &ftBuf);
			FileTimeToSystemTime(&ftBuf, &stBuf);
			_snprintf(tmpDate, sizeof(tmpDate), "%2.2d/%2.2d/%4d  %2.2d:%2.2d %s",
				stBuf.wMonth, stBuf.wDay, stBuf.wYear, HOUR(stBuf.wHour), stBuf.wMinute, AMPM(stBuf.wHour));
			if(WFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				count2++;
				if(url)
				{
					_snprintf(buf, sizeof(buf), "<TR>\r\n<TD WIDTH=\"%d\"><A HREF=\"", COL1);
	 				send(sock, buf, strlen(buf), 0);
					_snprintf(buf, sizeof(buf), "%s%s/", url, WFD.cFileName);
 					send(sock, buf, strlen(buf), 0);
					if(strlen(WFD.cFileName) > FILESIZE)
						_snprintf(buf, sizeof(buf), "\"><CODE>%.29s&gt;/</CODE></A>", WFD.cFileName);
					else
						_snprintf(buf, sizeof(buf), "\"><CODE>%s/</CODE></A>", WFD.cFileName);
					send(sock, buf, strlen(buf), 0);
					_snprintf(buf, sizeof(buf), "</TD>\r\n<TD WIDTH=\"%d\"><CODE>%s</CODE></TD>\r\n<TD WIDTH=\"%d\" ALIGN=\"right\"><CODE>-</CODE></TD>\r\n</TR>\r\n",
						COL2, tmpDate, COL3);
					send(sock, buf, strlen(buf), 0);
				}
				else
				{
					_snprintf(tmpDir, sizeof(tmpDir), "<%s>", WFD.cFileName);
					_snprintf(buf, sizeof(buf), "%-31s  %-21s\r\n", tmpDir, tmpDate);
					send(sock, buf, strlen(buf), 0);
				}
			}
			else
			{
				count++;
				if(url)
				{
					_snprintf(buf, sizeof(buf), "<TR>\r\n<TD WIDTH=\"%d\"><A HREF=\"", COL1);
 					send(sock, buf, strlen(buf), 0);
					_snprintf(buf, sizeof(buf), "%s%s", url, WFD.cFileName);
 					send(sock, buf, strlen(buf), 0);
					if(strlen(WFD.cFileName) > FILESIZE + 1)
						_snprintf(buf, sizeof(buf), "\"><CODE>%.30s&gt;</CODE></A>", WFD.cFileName);
					else
						_snprintf(buf, sizeof(buf), "\"><CODE>%s</CODE></A>", WFD.cFileName);
 					send(sock, buf, strlen(buf), 0);
					_snprintf(buf, sizeof(buf), "</TD>\r\n<TD WIDTH=\"%d\"><CODE>%s</CODE></TD>\r\n<TD WIDTH=\"%d\" ALIGN=\"right\"><CODE>%dk</CODE></TD>\r\n</TR>\r\n",
						COL2, tmpDate, COL3, WFD.nFileSizeLow / 1024);
					send(sock, buf, strlen(buf), 0);
				}
				else
				{
					_snprintf(buf, sizeof(buf), "%-31s  %-21s (%i bytes)\r\n", WFD.cFileName,tmpDate, WFD.nFileSizeLow);
					send(sock, buf, strlen(buf), 0);
				}
			}
		}
	}
	FindClose(Hnd);
	if(url)
		_snprintf(buf, sizeof(buf), "<TR>\r\n<TD COLSPAN=\"3\"><HR></TD>\r\n</TR>\r\n</TABLE>\r\n</BODY>\r\n</HTML>\r\n");
	else 
		_snprintf(buf, sizeof(buf), "Found: %i Files and %i Directories\r\n", count, count2);
	send(sock, buf, strlen(buf), 0);
}

void http_sendfile(struct httpds httpd, const char *file)
/* send file to remote host */
{
	unsigned int Fsize;
	unsigned int fsend = 1024;
	unsigned int move;
	unsigned long mode = 0;
	char buffer[1024];
	HANDLE testfile = CreateFile(file, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	if(testfile == INVALID_HANDLE_VALUE) 
		return;
	Fsize = GetFileSize(testfile, 0);
	while(Fsize)
	{
		int bytes_sent;
		memset(buffer, 0, sizeof(buffer));
		if(fsend > Fsize) 
			fsend = Fsize;
		move = 0 - Fsize;
		SetFilePointer(testfile, move, 0, FILE_END);
		ReadFile(testfile, buffer, fsend, &mode, 0);
		bytes_sent = send(httpd.sock, buffer, fsend, 0);
		if(bytes_sent == -1)
		{
			if(WSAGetLastError() != WSAEWOULDBLOCK) 
				break;
			else 
				bytes_sent = 0;
		}
		Fsize -= bytes_sent;
	}
	if(testfile != INVALID_HANDLE_VALUE) 
		CloseHandle(testfile);
}

DWORD WINAPI http_start(void *param)
/* main httpd function */
{
	int gsin_len;
    unsigned int i;
	unsigned int r;
	unsigned int b;
	unsigned int max;
	unsigned long mode = 1;
	char buffer[4096];
	char rBuffer[4096];
	char file[256];
	char *file_to_send = "";
	struct sockaddr_in gsin;
	struct sockaddr_in ssin;
	struct httpds httpd = *(struct httpds *)param;
	struct httpds *phttpd = (struct httpds *)param;
	SOCKET gsock;
	SOCKET ssock;
	phttpd->gotinfo = true;
	ssin.sin_family = AF_INET;
	ssin.sin_port = htons((unsigned short)httpd.port);
	ssin.sin_addr.s_addr = INADDR_ANY;
	memset(ssin.sin_zero, 0, 8);
	if((ssock = socket(AF_INET, SOCK_STREAM, 0)) != -1)
	{
		if(bind(ssock, (struct sockaddr *)&ssin, sizeof(ssin)) != -1)
		{
			if(listen(ssock, SOMAXCONN) != -1)
			{
				if(ioctlsocket(ssock, FIONBIO, &mode) != -1)
				{
					fd_set master;
					fd_set temp; 
					FD_ZERO(&master); 
					FD_ZERO(&temp);
					FD_SET(ssock, &master);
					max = ssock;
					while(1)
					{
						temp = master;
						if(select(max + 1, &temp, 0, 0, 0) == -1)
							break;
						for(i = 0; i <= max; i++)
						{
							if(FD_ISSET(i, &temp))
							{
								if(i == ssock)
								{
									gsin_len = sizeof(gsin);
									if((gsock = accept(ssock, (struct sockaddr *)&gsin, &gsin_len)) == -1)
										continue; 
									else
									{
										FD_SET(gsock, &master);
										if(gsock > (unsigned int)max)  
											max = gsock;
									}
								}
								else
								{
    								memset(buffer, 0, sizeof(buffer));
									memset(rBuffer, 0, sizeof(rBuffer));
									if(recv(i, buffer, sizeof(buffer), 0) <= 0)
									{
										closesocket(i); 
										FD_CLR(i, &master);
									}
									else
									{
										memset(file, 0, sizeof(file));
										for(b = 0, r = 0; b < strlen(buffer); b++, r++)
										{
											rBuffer[r] = buffer[b];
											if(buffer[b] == '\n')
											{
												if(strstr(rBuffer, "GET ") != 0 && strlen(rBuffer) > 5)
												{
													file_to_send = strtok(strstr(strstr(rBuffer, "GET "), " "), " ");
													strncpy(file, file_to_send, sizeof(file) - 1);
												}
												else if(!strcmp(rBuffer, "\r\n"))
												{
													FD_CLR(i, &master);
													if(file)
													{
														if(strlen(file) + strlen(httpd.dir) < 256)
														{ 
															unsigned long mode2 = 0;
															ioctlsocket(i, FIONBIO, &mode2);
															httpd.sock = i;
															http_checkfile(httpd, file);
														}
														else 
															closesocket(i);
													}
													else 
														closesocket(i);
													break;
												}
												memset(rBuffer, 0, sizeof(rBuffer));
												r = -1;
											}
										}
									}
								}
							}
                		} 
        			}
				}
			}
		}
	}
	closesocket(ssock);
	clearthread(httpd.tnum);
	ExitThread(0);
return 0;
}

DWORD WINAPI http_header(void *param)
/* send http header */
{
	struct httpds httpd = *(struct httpds *)param;
	struct httpds *phttpd = (struct httpds *)param;
	char tFile[256];
	char nFile[256];
	char content[50];
	char buffer[4096];
	char date[70];
	char time[30];
	phttpd->gotinfo = true;
	strncpy(tFile, httpd.file, sizeof(httpd.file) - 1);
	strncpy(nFile, httpd.path, sizeof(httpd.path) - 1);
	if(httpd.type) 
		strncpy(content, "text/html", sizeof(content) - 1);
	else 
		strncpy(content,"application/octet-stream", sizeof(content) - 1);
	GetDateFormat(0x409, 0, 0, "ddd, dd MMM yyyy", date, 70);
	GetTimeFormat(0x409, 0, 0, "HH:mm:ss", time, 30);
	if(httpd.length == -1)
		_snprintf(buffer, sizeof(buffer) - 1, "HTTP/1.0 200 OK\r\nServer: HTTPd\r\nCache-Control: no-cache,no-store,max-age=0\r\npragma: no-cache\r\nContent-Type: %s\r\nAccept-Ranges: bytes\r\nDate: %s %s GMT\r\nLast-Modified: %s %s GMT\r\nExpires: %s %s GMT\r\nConnection: close\r\n\r\n",
		content, date, time, date, time, date, time);
	else
		_snprintf(buffer, sizeof(buffer) - 1, "HTTP/1.0 200 OK\r\nServer: HTTPd\r\nCache-Control: no-cache,no-store,max-age=0\r\npragma: no-cache\r\nContent-Type: %s\r\nContent-Length: %i\r\nAccept-Ranges: bytes\r\nDate: %s %s GMT\r\nLast-Modified: %s %s GMT\r\nExpires: %s %s GMT\r\nConnection: close\r\n\r\n",
		content, httpd.length, date, time, date, time, date, time);
	send(httpd.sock, buffer, strlen(buffer), 0);
	if(!httpd.type) 
		http_sendfile(httpd, tFile);
	else
		http_getfiles(httpd.sock, tFile, nFile);
	closesocket(httpd.sock);
	clearthread(httpd.tnum);
	ExitThread(0);
return 0;
}