#ifndef __DEFINES__
#define __DEFINES__
#define IRCLINE			512
#define MAXTHREADS		512
#define MAXALIASES		16
#define LOGSIZE			128
#define LOGLINE			128
#define MAXLOGINS		3
#define MAX_LINES		500
#define MAXSCANTHRD		200
#define MAXSCANTIME		2400
#define MAXHOSTNAME		255
#define BLOCKSIZE		512
#define FLOOD_DELAY		2000
#define MAXSTRLEN		500
#define MAXNICKLEN		28
#define MAXPINGSIZE		65500
#define MAXTOKENS		32

#define AMPM(x) ((x>12)?("PM"):("AM"))
#define HOUR(x) ((x>12)?(x-12):(x))
#endif