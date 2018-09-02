/*
/
// link  -  scanner/ source file
// 
// Copyright   2004 by loco
// All Rights Reserved
//
//

*/

#include "include.h"


enum 
{
	HTTP_TYPE_UNKNOWN,				// Unknown httpd respond... 
	HTTP_TYPE_IIS_60,				// IIS 6.0 httpd running...
	HTTP_TYPE_IIS_55,				// IIS 5.5 httpd running...
	HTTP_TYPE_IIS_50,				// IIS 5.0 httpd running...
	HTTP_TYPE_IIS_40,				// IIS 4.0 httpd running...
	HTTP_TYPE_APACHE_1X_UNIX,		// Apache 1.x on (Unix) ...
	HTTP_TYPE_APACHE_1X_WIN32,		// Apache 1.x on (Win32)...
	HTTP_TYPE_APACHE_2X_UNIX,		// Apache 2.x on (Unix) ...
	HTTP_TYPE_APACHE_2X_WIN32,		// Apache 2.x on (Win32)...
	HTTP_OPTION_UNKNOWN,			// Unknown option responded...
	HTTP_OPTION_WEBDAV				// Webdav option responded ...
};

void SplitRetVal(char *szInput)
{
	char *szSplit;
	
	if(szSplit = strchr(szInput, '\n'))
    	*szSplit = '\0';
	
	if(szSplit = strchr(szInput, '\r'))
    	*szSplit = '\0';
}

int HttpServerType(DWORD dwIpAddress, int iPort)
{
	
	char szReceiveBuffer[2048], *szReplyStart;
	int iRetVal = HTTP_TYPE_UNKNOWN;
	SOCKADDR_IN sinSockAddrIn;


	memset(&sinSockAddrIn, 0, sizeof(sinSockAddrIn));
	sinSockAddrIn.sin_family		= AF_INET;
	sinSockAddrIn.sin_addr.s_addr	= dwIpAddress;
	sinSockAddrIn.sin_port			= htons(iPort);
		SOCKET sSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, NULL);
	if(!(sSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, NULL)))
		return iRetVal;
	
	if(connect(sSocket, (LPSOCKADDR)&sinSockAddrIn, sizeof(sinSockAddrIn)) == SOCKET_ERROR)
		return iRetVal;

	if(send(sSocket, "HEAD / HTTP/1.0\n\n", 17, 0) == SOCKET_ERROR)
		return iRetVal;

	if(recv(sSocket, szReceiveBuffer, sizeof(szReceiveBuffer), 0) == SOCKET_ERROR)
		return iRetVal;

	if(!(szReplyStart = strstr(szReceiveBuffer, "Server:")))
		return 0;

	SplitRetVal(szReplyStart);

	closesocket(sSocket);
	return iRetVal;
}

int HTTPCheckOptions(DWORD dwIpAddress, int iPort)
{
	char szReceiveBuffer[2048], *szReplyStart;
	int iRetVal = HTTP_OPTION_UNKNOWN;
	SOCKADDR_IN sinSockAddrIn;
	SOCKET sSocket;
	
	memset(&sinSockAddrIn, 0, sizeof(sinSockAddrIn));
	sinSockAddrIn.sin_family		= AF_INET;
	sinSockAddrIn.sin_addr.s_addr	= dwIpAddress;
	sinSockAddrIn.sin_port			= htons(iPort);

	if(!(sSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, NULL)))
		return iRetVal;
	
	if(connect(sSocket, (LPSOCKADDR)&sinSockAddrIn, sizeof(sinSockAddrIn)) == SOCKET_ERROR)
		return iRetVal;

	if(send(sSocket, "OPTIONS * HTTP/1.0\n\n", 20, 0) == SOCKET_ERROR)
		return iRetVal;

	if(recv(sSocket, szReceiveBuffer, sizeof(szReceiveBuffer), 0) == SOCKET_ERROR)
		return iRetVal;

	if(!(szReplyStart = strstr(szReceiveBuffer, "Allow:")))
		return 0;

	SplitRetVal(szReplyStart);
			
	if (strstr(szReplyStart, "PROPFIND") || strstr(szReplyStart, "SEARCH"))
		iRetVal = HTTP_OPTION_WEBDAV;

	closesocket(sSocket);
	return iRetVal;
}