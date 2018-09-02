
#define NO_IDENT       
#define NO_AUSCAN
#define NO_CAPTURE     
#define NO_CRASH       
#define NO_REALNICK    
#define NO_AVFW_KILL   
#define NO_REGISTRY    
#define NO_SECSYSTEM   
#define NO_CRYPT       
#define DEBUG_CRYPT    


#undef NO_HIDE
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

#define AMPM(x) ((x>12)?("PM"):("AM"))
#define HOUR(x) ((x>12)?(x-12):(x))

#define fFD_ISSET(fd, set) __fWSAFDIsSet((SOCKET)(fd), (fd_set FAR *)(set))

#define addpredefinedaliases()
