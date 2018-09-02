#include "includes.h"
#include "functions.h"
#include "externs.h"

unsigned long ResolveAddress(char *szHost)
{
	unsigned long ip = finet_addr(szHost);
	if (ip==INADDR_NONE) {
		hostent *pHE = fgethostbyname(szHost);
		if (pHE == 0) 
			return INADDR_NONE;
		ip = *((unsigned long *)pHE->h_addr_list[0]);	
	}

	return ip;
}

BOOL FlushDNSCache(void)
{
	BOOL bRet = FALSE;
	if (fDnsFlushResolverCache)
		bRet = fDnsFlushResolverCache();

	return (bRet);
}

BOOL FlushARPCache(void)
{
    char logbuf[LOGLINE];
    PMIB_IPNETTABLE arp = 0;
    ULONG tsize = 0;
	BOOL bRet = TRUE;
	
    DWORD result = fGetIpNetTable(NULL, &tsize, TRUE);
	switch(result) {
	case ERROR_SUCCESS:
		break;
	case ERROR_INSUFFICIENT_BUFFER:
		arp=(PMIB_IPNETTABLE)malloc(tsize);
		memset((void *)arp, 0, tsize);

		if (arp != NULL) {
			if ((result = fGetIpNetTable(arp, &tsize, TRUE)) != ERROR_SUCCESS) {
				sprintf(logbuf,"[FLUSHDNS]: Error getting ARP cache: <%d>.",result);
				bRet = FALSE;
			}
		} else {
			sprintf(logbuf,"[FLUSHDNS]: Unable to allocation ARP cache.");
			bRet = FALSE;
		}
		break;
	case ERROR_NO_DATA:
		sprintf(logbuf,"[FLUSHDNS]: ARP cache is empty.");
		bRet = FALSE;
		break;
	case ERROR_NOT_SUPPORTED:
		sprintf(logbuf,"[FLUSHDNS]: Not supported by this system.");
		bRet = FALSE;
		break;
	default:
		sprintf(logbuf,"[FLUSHDNS]: Error getting ARP cache: <%d>.",result);
		bRet = FALSE;
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
