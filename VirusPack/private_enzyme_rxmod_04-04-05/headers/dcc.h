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

typedef struct DCC
{
	SOCKET sock;
	SOCKET csock;
	char host[20];
	char filename[MAX_PATH];
	char sendto[128];
	int port;
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} DCC;

SOCKET CreateSock(char *host, int port);
DWORD WINAPI DCCSendThread(LPVOID param);
DWORD WINAPI DCCChatThread(LPVOID param);
DWORD WINAPI DCCGetThread(LPVOID param);
