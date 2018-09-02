//
// PING.C -- Ping program using ICMP and RAW Sockets
//
#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include <process.h>
#include "ping.h"

// static char *_CMSID = "$CmsFile: PING $ $Date:2001.5.3.5.34.35   $";
// Internal Functions
void Ping(char *);
void ReportError(LPCSTR pstrFrom);
u_short in_cksum(u_short *addr, int len);

// ICMP Echo Request/Reply functions
int		SendEchoRequest(SOCKET, LPSOCKADDR_IN);


void Ping(char * bad_dog)        //<IP> <TIME>
{
	DWORD pklen;           //time were supposed to packet this ip
	DWORD ping_done;
	char pstrHost[200];
	char abcc[30];
	SOCKET	  rawSocket;
	LPHOSTENT lpHost;
	struct    sockaddr_in saDest;
	struct    sockaddr_in saSrc;
	DWORD	  dwTimeSent;
	DWORD	  dwElapsed;
	u_char    cTTL;
	int       nLoop;
	int       nRet;
	char *u;



	ZeroMemory(pstrHost,200);
	ZeroMemory(abcc,30);
	u = (char *) strtok(bad_dog,"; ");
	if (u != NULL)
	{
		lstrcat(pstrHost,u);
		u = (char *) strtok(0,"; ");
		if (u != NULL)
		{
			lstrcat(abcc,u);
			pklen = atoi(abcc);
		}
	}


	// Create a Raw socket
	rawSocket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (rawSocket == SOCKET_ERROR)
	{
		return;
	}

	// Lookup host
	lpHost = gethostbyname(pstrHost);
	if (lpHost == NULL)
	{
		return;
	}
	saDest.sin_addr.s_addr = *((u_long FAR *) (lpHost->h_addr));
	saDest.sin_family = AF_INET;
	saDest.sin_port = 0;


	//------
	ping_done = (GetTickCount() + (1000 * pklen));
	while(GetTickCount() < ping_done)
	{
		// Send ICMP echo request
		SendEchoRequest(rawSocket, &saDest);
		Sleep(10);

	}

	nRet = closesocket(rawSocket);
	if (nRet == SOCKET_ERROR)
		ReportError("closesocket()");
}


// SendEchoRequest()
// Fill in echo request header
// and send to destination
int SendEchoRequest(SOCKET s,LPSOCKADDR_IN lpstToAddr)
{
	static ECHOREQUEST echoReq;
	static nId = 1;
	static nSeq = 1;
	int nRet;

	// Fill in echo request
	echoReq.icmpHdr.Type		= ICMP_ECHOREQ;
	echoReq.icmpHdr.Code		= 0;
	echoReq.icmpHdr.Checksum	= 0;
	echoReq.icmpHdr.ID			= nId++;
	echoReq.icmpHdr.Seq			= nSeq++;

	// Fill in some data to send
	for (nRet = 0; nRet < REQ_DATASIZE; nRet++)
		echoReq.cData[nRet] = ' '+nRet;

	// Save tick count when sent
	echoReq.dwTime				= GetTickCount();

	// Put data in packet and compute checksum
	echoReq.icmpHdr.Checksum = in_cksum((u_short *)&echoReq, sizeof(ECHOREQUEST));

	// Send the echo request
	nRet = sendto(s,						/* socket */
				 (LPSTR)&echoReq,			/* buffer */
				 sizeof(ECHOREQUEST),
				 0,							/* flags */
				 (LPSOCKADDR)lpstToAddr, /* destination */
				 sizeof(SOCKADDR_IN));   /* address length */

	if (nRet == SOCKET_ERROR)
		ReportError("sendto()");
	return (nRet);
}



// What happened?
void ReportError(LPCSTR pWhere)
{
	fprintf(stderr,"\n%s error: %d\n",
		WSAGetLastError());
}


//
// Mike Muuss' in_cksum() function
// and his comments from the original
// ping program
//
// * Author -
// *	Mike Muuss
// *	U. S. Army Ballistic Research Laboratory
// *	December, 1983

/*
 *			I N _ C K S U M
 *
 * Checksum routine for Internet Protocol family headers (C Version)
 *
 */
u_short in_cksum(u_short *addr, int len)
{
	register int nleft = len;
	register u_short *w = addr;
	register u_short answer;
	register int sum = 0;

	/*
	 *  Our algorithm is simple, using a 32 bit accumulator (sum),
	 *  we add sequential 16 bit words to it, and at the end, fold
	 *  back all the carry bits from the top 16 bits into the lower
	 *  16 bits.
	 */
	while( nleft > 1 )  {
		sum += *w++;
		nleft -= 2;
	}

	/* mop up an odd byte, if necessary */
	if( nleft == 1 ) {
		u_short	u = 0;

		*(u_char *)(&u) = *(u_char *)w ;
		sum += u;
	}

	/*
	 * add back carry outs from top 16 bits to low 16 bits
	 */
	sum = (sum >> 16) + (sum & 0xffff);	/* add hi 16 to low 16 */
	sum += (sum >> 16);			/* add carry */
	answer = ~sum;				/* truncate to 16 bits */
	return (answer);
}

