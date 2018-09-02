#ifndef DDOS_H
#define DDOS_H

#include "Includes.h"

class Ddos
{
public:

	void PingFlood(char *ip, int PacketSize);

private:
	/* ping flood */

	struct sockaddr_in dest, from; // dve strukturi za informacije
	
	int bread, sock, datasize, bwrote;
	
	unsigned int PacketSize;
	unsigned short seq_no;
	
	char	*dest_ip;
	char	*icmp_data;
	char	*recvbuf;
	
#define ICMP_ECHO 8
#define ICMP_ECHOREPLY 0
#define ICMP_MIN 8 // minimum 8 byte icmp packet (just header)
	
#define STATUS_FAILED 0xFFFF
//#define DEF_PACKET_SIZE 32
#define MAX_PACKET 65535  // 65536
	
	typedef struct iphdr 
	{
		unsigned int h_len:4;          // length of the header
		unsigned int version:4;        // Version of IP
		unsigned char tos;             // Type of service
		unsigned short total_len;      // total length of the packet
		unsigned short ident;          // unique identifier
		unsigned short frag_and_flags; // flags
		unsigned char  ttl; 
		unsigned char proto;           // protocol (TCP, UDP etc)
		unsigned short checksum;       // IP checksum
		
		unsigned int sourceIP;
		unsigned int destIP;
		
	}IpHeader;
	
	//
	// ICMP header
	//
	typedef struct _ihdr 
	{
		BYTE i_type;
		BYTE i_code; /* type sub code */
		USHORT i_cksum;
		USHORT i_id;
		USHORT i_seq;
		/* This is not the std header, but we reserve space for time */
		ULONG timestamp;
	} IcmpHeader;
	
#define xmalloc(s) HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,(s))
#define xfree(p)   HeapFree (GetProcessHeap(),0,(p))
	
	void Fill_Icmp_Data(char * icmp_data, int datasize);
	USHORT Checksum(USHORT * buffer, int size);

	/*  END PING FLOOD */
};

#endif // DDOS_H