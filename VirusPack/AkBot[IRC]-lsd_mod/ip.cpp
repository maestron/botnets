#include "include.h"
#include "extern.h"

unsigned short checksum(unsigned short *buf, int len)
/* generate a checksum */
{
	int sum = 0;
	int nleft = len;
	unsigned short answer = 0;
	unsigned short *w = buf;
	while(nleft > 1)
	{
		sum += *w++;
		nleft -= 2;
	}
	if(nleft == 1)
	{
		*(u_char *)(&answer) = *(u_char *)w ;
		sum += answer;
	}
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;
	return answer;
}

void makeicmp(struct icmpp *p, unsigned long src_ip, unsigned long dst_ip)
/* make a ICMP (ping) packet and store it in p */
{
	char *chkbuf = (char *)malloc(sizeof(p->icmph) + sizeof(p->payload));
	memset(p->payload, rrand(0, 255), sizeof(p->payload));
	p->iph.ip_hl = 5;
	p->iph.ip_v = 4;
	p->iph.ip_tos = 0;
	p->iph.ip_len = htons(sizeof(p));
	p->iph.ip_id = htons(rand());
	p->iph.ip_off = 0;
	p->iph.ip_ttl = 128;
	p->iph.ip_p = IPPROTO_ICMP;
	p->iph.ip_sum = 0;
	p->iph.ip_src = src_ip;
	p->iph.ip_dst = dst_ip;
	p->iph.ip_sum = checksum((unsigned short *)&p->iph, sizeof(p->iph));
	p->icmph.icmp_type = 8;
	p->icmph.icmp_code = 0;
	p->icmph.icmp_id = htons(rand());
	p->icmph.icmp_cksum = 0;
	p->icmph.icmp_seq = htons((rand() << 16) | rand());
	memcpy(chkbuf, &p->icmph, sizeof(p->icmph));
	memcpy(chkbuf + sizeof(p->icmph), p->payload, sizeof(p->payload));
	p->icmph.icmp_cksum = checksum((unsigned short *)chkbuf, sizeof(p->icmph) + sizeof(p->payload));
	free(chkbuf);
}

void makeudp(struct udpp *p, unsigned long src_ip, unsigned long dst_ip, unsigned short src_port, unsigned short dst_port)
/* make a UDP packet and store it in p */
{
	char *chkbuf = (char *)malloc(sizeof(struct psd_hdr) + sizeof(p->udph) + sizeof(p->payload));
	struct psd_hdr psdh;
	memset(p->payload, rrand(0, 255), sizeof(p->payload));
	p->iph.ip_hl = 5;
	p->iph.ip_v = 4;
	p->iph.ip_tos = 0;
	p->iph.ip_len = htons(sizeof(p));
	p->iph.ip_id = htons(rand());
	p->iph.ip_off = 0;
	p->iph.ip_ttl = 128;
	p->iph.ip_p = IPPROTO_UDP;
	p->iph.ip_sum = 0;
	p->iph.ip_src = src_ip;
	p->iph.ip_dst = dst_ip;
	p->iph.ip_sum = checksum((unsigned short *)&p->iph, sizeof(p->iph));
	p->udph.uh_sport = htons(src_port);
	p->udph.uh_dport = htons(dst_port);
	p->udph.uh_len = htons(sizeof(p->udph) + sizeof(p->payload));
	p->udph.uh_sum = 0;
	psdh.ph_src = p->iph.ip_src;
	psdh.ph_dst = p->iph.ip_dst;
	psdh.ph_zero = 0;
	psdh.ph_p = p->iph.ip_p;
	psdh.ph_len = htons(sizeof(p->udph) + sizeof(p->payload));
	memcpy(chkbuf, &psdh, sizeof(psdh));
	memcpy(chkbuf + sizeof(psdh), &p->udph, sizeof(p->udph));
	memcpy(chkbuf + sizeof(psdh) + sizeof(p->udph), p->payload, sizeof(p->payload));
	p->udph.uh_sum = checksum((unsigned short *)chkbuf, sizeof(psdh) + sizeof(p->udph) + sizeof(p->payload));
	free(chkbuf);
}

void makesyn(struct tcpp *p, unsigned long src_ip, unsigned long dst_ip, unsigned short src_port, unsigned short dst_port)
/* make a TCP SYN packet and store it in p */
{
	char *chkbuf = (char *)malloc(sizeof(struct psd_hdr) + sizeof(struct tcp_hdr));
	struct psd_hdr psdh;
	p->iph.ip_hl = 5;
	p->iph.ip_v = 4;
	p->iph.ip_tos = 0;
	p->iph.ip_len = htons(sizeof(p));
	p->iph.ip_id = htons(rand());
	p->iph.ip_off = 0;
	p->iph.ip_ttl = 128;
	p->iph.ip_p = IPPROTO_TCP;
	p->iph.ip_sum = 0;
	p->iph.ip_src = src_ip;
	p->iph.ip_dst = dst_ip;
	p->iph.ip_sum = checksum((unsigned short *)&p->iph, sizeof(p->iph));
	p->tcph.th_sport = htons(src_port);
	p->tcph.th_dport = htons(dst_port);
	p->tcph.th_ack = 0;
	p->tcph.th_x2 = 0;
	p->tcph.th_off = 5;
	p->tcph.th_flags = SYN;
	p->tcph.th_win = htons(16384);
	p->tcph.th_sum = 0;
	p->tcph.th_urp = 0;
	p->tcph.th_seq = htons((rand() << 16) | rand());
	psdh.ph_src = p->iph.ip_src;
	psdh.ph_dst = p->iph.ip_dst;
	psdh.ph_zero = 0;
	psdh.ph_p = p->iph.ip_p;
	psdh.ph_len = htons(sizeof(p->tcph));
	memcpy(chkbuf, &psdh, sizeof(psdh));
	memcpy(chkbuf + sizeof(psdh), &p->tcph, sizeof(p->tcph));
	p->tcph.th_sum = checksum((unsigned short *)chkbuf, sizeof(psdh) + sizeof(p->tcph));
	free(chkbuf);
}