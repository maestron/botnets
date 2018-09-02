/*************************** TCPIP.H ********************************/
#ifndef _TCPIP_H_
#define _TCPIP_H_

// Standard TCP flags
#define URG 0x20
#define ACK 0x10
#define PSH 0x08
#define RST 0x04
#define SYN 0x02
#define FIN 0x01

// Our tcp header struct
typedef struct tcp_hdr
	{
	unsigned short	sport;
	unsigned short	dport;
	unsigned int	seqnum;
	unsigned int	acknum;
	unsigned char	DataOffset;
	unsigned char	Flags;
	unsigned short	Windows;
	unsigned short	Checksum;
	unsigned short	UrgPointer;
	}TCP_HDR;

// Our ip header struct
typedef struct ip_hdr
{
    unsigned char  ip_verlen;        // IP version & length
    unsigned char  ip_tos;           // IP type of service
    unsigned short ip_totallength;   // Total length
    unsigned short ip_id;            // Unique identifier 
    unsigned short ip_offset;        // Fragment offset field
    unsigned char  ip_ttl;           // Time to live
    unsigned char  ip_protocol;      // Protocol(TCP, UDP, etc.)
    unsigned short ip_checksum;      // IP checksum
    unsigned int   ip_srcaddr;       // Source address
    unsigned int   ip_destaddr;      // Destination address

} IP_HDR; 

// Our pseudo header struct
typedef struct ps_hdr
   {
      unsigned int source_address;
      unsigned int dest_address;
      unsigned char placeholder;
      unsigned char protocol;
      unsigned short tcp_length;
      struct tcp_hdr tcp;
   }PS_HDR;

// Standard TCP/UDP checksum function.
USHORT checksum(USHORT *buffer, int size)
{
    unsigned long cksum=0;
    while (size > 1)
    {
        cksum += *buffer++;
        size  -= sizeof(USHORT);   
    }
    if (size)
    {
        cksum += *(UCHAR*)buffer;   
    }
    cksum = (cksum >> 16) + (cksum & 0xffff);
    cksum += (cksum >>16); 
    return (USHORT)(~cksum); 
}
#endif

/********************** END TCPIP.H *************************************/