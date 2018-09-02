#include "main.h"
#include "redir_socks5.h"
#include "mainctrl.h"
#include "utility.h"

#ifdef _WIN32

static CSocks5* socks;

u_long WINAPI SocksThread(LPVOID pParam);

bool CSocks::DNSAddrLookup(char* sHost, struct in_addr* addr)
{
	struct hostent* ht = NULL;

	ht = gethostbyname(sHost);
	if(ht)
	{
		memcpy(addr,ht->h_addr, 4);
		return(true);
	}
	return(false);
};

bool CSocks::SocksTCPTunneling(u_int sres, u_int sdest)
{
	register u_int sockr, sockw, ret;
	register u_int uread, uwrote;
	char szBuffer[1024];
	fd_set fd;
	timeval tv = {0,0};
	
	do
	{
		FD_ZERO(&fd);
		FD_SET(sres,&fd);
		FD_SET(sdest,&fd);

		
		if((ret = select(2,&fd,NULL,NULL,&tv))>0 && VALID_SOCKET(ret))
		{
			if(FD_ISSET(sres,&fd))
			{
				sockr = sres;
				sockw = sdest;
			}
			else
			{
				sockr = sdest;
				sockw = sres;
			}

			uread = recv(sockr,szBuffer,1023,0);
			szBuffer[uread] = 0;
			uwrote = 0;
			if(!VALID_SOCKET(uread) || uread==0) break;

			while(uwrote<uread)
			{
				ret = send(sockw,szBuffer+uwrote,uread-uwrote,0);
				if(!VALID_SOCKET(ret)) goto __quit;
				uwrote += ret;
			}
		}

		FD_ZERO(&fd);
		FD_SET(sres,&fd);
		FD_SET(sdest,&fd);
		if(select(2,NULL,NULL,&fd,&tv)>0) break;
	} while(1);
	
__quit:
	return(true);
}

bool CSocks::SocksUDPTunneling(void* sares, char* sData, u_int len)
{
	register u_int sdest, pos;
	register u_int sres;
	struct sockaddr_in sadest;
	struct timeval tv;
	struct fd_set fd;
	char szBuffer[1024];

	tv.tv_usec = 0;
	tv.tv_sec = 7;
	sadest.sin_family = AF_INET;
	switch(sData[3])
	{
		case 1: memcpy(szBuffer,sData+4,4);
				sadest.sin_addr.s_addr = *(u_long*)szBuffer;
				sadest.sin_port = *(u_short*)(sData+8);
				pos = 10;
				break;
		case 2: memcpy(szBuffer,sData+5,sData[4]);
				szBuffer[sData[4]] = 0;
				if(!DNSAddrLookup(szBuffer,&sadest.sin_addr)) return(false);
				sadest.sin_port = *(u_short*)(sData+5+sData[4]);
				pos = 7+sData[4];
				break;
		case 3: memcpy(szBuffer,sData+4,16);
				szBuffer[16] = 0;
				return(true);
		default: return(false);
	}
	
	sdest = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	sres = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(!VALID_SOCKET(sdest) || VALID_SOCKET(sres)) return(false);
	sendto(sdest,sData+pos,len-pos,0,(struct sockaddr*)&sadest,sizeof(sadest));
	if(bind(sdest,(struct sockaddr*)sares,sizeof(struct sockaddr))) return(false);

	do
	{
		FD_ZERO(&fd);
		FD_SET(sres,&fd);
		select(1,&fd,NULL,NULL,&tv);
		pos = recvfrom(sdest,szBuffer,1023,0,NULL,NULL);
		sendto(sres,szBuffer,pos,0,(struct sockaddr*)sares,sizeof(struct sockaddr));
	} while(pos>0 && VALID_SOCKET(pos));

	closesocket(sdest);
	closesocket(sres);
	return(true);
};

bool CSocks5::ForceConnection(u_int sock)
{
	register u_int schain, ret, i;
	char szBuffer[1024];
	struct fd_set fd;
	struct timeval tv;
	struct sockaddr_in sain;
	SOCKS5REQ req;

	tv.tv_usec = 0;
	tv.tv_sec = 11;
	FD_ZERO(&fd);
	FD_SET(sock,&fd);

	if(!VALID_SOCKET(sock)) return(false);

	if(mode==SOCKS_MODE_TCP)
	{
		if(select(1,&fd,NULL,NULL,&tv)>0 && FD_ISSET(sock,&fd))
		{
			schain = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);
			if(!VALID_SOCKET(schain)) return(false);

			recv(sock,szBuffer,2,0);
			if(szBuffer[0]!=5) return(false);
			ret = szBuffer[1];
			memset(szBuffer,0,11);
			recv(sock,szBuffer,ret,0);
			
			char szLogin[256], szPassword[256];
			send(sock,"\x05\x02",2,0);
			tv.tv_usec = 0;
			tv.tv_sec = 7;
			FD_ZERO(&fd);
			FD_SET(sock,&fd);
			select(1,&fd,NULL,NULL,&tv);
			memset(szBuffer,0,128);
			recv(sock,szBuffer,2,0);
			if(szBuffer[0]!=1) return(false);
			recv(sock,szLogin,szBuffer[1],0);
			szLogin[szBuffer[1]] = 0;
			recv(sock,szBuffer,1,0);
			recv(sock,szPassword,szBuffer[0],0);
			szPassword[szBuffer[0]] = 0;
			
			if(strcmp(szLogin,m_sUser.CStr()) && strcmp(szPassword,m_sPass.CStr()))
			{
				closesocket(sock);
				return false;
			}

			send(sock,"\x05\x00",2,0);

			FD_ZERO(&fd);
			FD_SET(sock,&fd);
			select(1,&fd,NULL,NULL,&tv);
			if(!FD_ISSET(sock,&fd)) return(false);
			recv(sock,(char*)&req,4,0);
			switch(req.uAddrType) {
				case 1: recv(sock,(char*)szBuffer,4,0); break;
				case 3: recv(sock,(char*)szBuffer,1,0);
						recv(sock,(char*)req.uDstAddr,szBuffer[0],0);
						req.uDstAddr[szBuffer[0]] = 0;
						if(!DNSAddrLookup((char*)req.uDstAddr,(struct in_addr*)szBuffer))
						{
							return(false);
						}
						break;
				case 4: return(false);
				default: ;
			}
			recv(sock,(char*)&req.uDstPort,sizeof(req.uDstPort),0);


			if(req.uCommand==1)
			{
				sain.sin_family = AF_INET;
				sain.sin_port = req.uDstPort;
				sain.sin_addr.s_addr = *(u_long*)szBuffer;
				if(connect(schain,(struct sockaddr*)&sain,sizeof(sain))!=0)
				{
					return(false);
				}
			}
			else
			{
				return(false);
			}

			send(sock,"\x05\x00\x00\x01",4,0);	// succeeded
			send(sock,szBuffer,4,0);
			send(sock,(char*)&req.uDstPort,2,0);
			SocksTCPTunneling(sock,schain);
			closesocket(schain);
		}
	}
	else if(mode==SOCKS_MODE_UDP)
	{
		do
		{
			FD_ZERO(&fd);
			FD_SET(sock,&fd);
			select(1,&fd,NULL,NULL,&tv);
			i = sizeof(sain);
			ret = recvfrom(sock,szBuffer,1023,0,(struct sockaddr*)&sain,(int*)&i);
			SocksUDPTunneling(&sain,szBuffer,ret);
		} while(ret!=0 && VALID_SOCKET(ret) && FD_ISSET(sock,&fd));
	}
	return(true);
};

bool CSocks::PrepareListening()
{
	register u_int uType, uProto;
	struct sockaddr_in sain;

	if(uAccept) return(false);

	switch(mode)
	{
		case SOCKS_MODE_TCP:
			uType = SOCK_STREAM; uProto = IPPROTO_TCP; break;
		case SOCKS_MODE_UDP:
			uType = SOCK_DGRAM; uProto = IPPROTO_UDP; break;
		default:
			mode = SOCKS_MODE_TCP;
			uType = SOCK_STREAM; uProto = IPPROTO_TCP;
	}

	uAccept = socket(AF_INET,uType,uProto);
	if(uAccept==0) return false;
	
	sain.sin_family = AF_INET;
	sain.sin_addr.s_addr = INADDR_ANY;
	sain.sin_port = htons(uPort);
	if(bind(uAccept,(struct sockaddr*)&sain,sizeof(sain))!=0)
	{
		closesocket(uAccept);
		return false;
	}

	if(mode==SOCKS_MODE_TCP)
		if(listen(uAccept,3)!=0)
		{
			closesocket(uAccept);
			return false;
		}


	return(true);
};

bool CSocks::StartChaining()
{
	register u_int sock, uTmp;
	struct sockaddr_in sain;
	bool bret;

	if(mode==SOCKS_MODE_TCP)
	{
		uTmp = sizeof(sain);
		if(uAccept==0) return(false);
		while((sock = accept(uAccept,(struct sockaddr*)&sain,(int*)&uTmp))==0);
		try {
				bret = ForceConnection(sock);
				closesocket(sock);
				if(!bret) return false;
			}
		catch(...) {return false;}
	}
	else if(mode==SOCKS_MODE_UDP)
	{
		bret = ForceConnection(uAccept);
		closesocket(uAccept);
		if(!bret) return false;
	}
	else return false;

	return(true);
}

u_long WINAPI SocksThread(LPVOID pParam)
{
	CSocks5* pSocks = (CSocks5*)pParam;

	try {
		pSocks->ForceConnection(pSocks->uAccept);
		closesocket(pSocks->uAccept);
	}
	catch(...) {
	};
	return(1);
}

void StartSocks5(int port, CString username, CString password)
{
WSAData wsadata;
if(WSAStartup(0x002,&wsadata)) return;
socks = new CSocks5();
socks->uPort=port;
socks->m_sUser=username;
socks->m_sPass=password;
if(!socks->PrepareListening()) return;
for(;;) socks->StartChaining();
return;
}

#endif // _WIN32
