#ifndef _SYNC_LIB_H_
#define _SYNC_LIB_H_

char rot13c(char c);
void rot13(char *buf, const char *in);
void mk_smtpdate(FILETIME *in_ft, char *buf);
void xrand_init(void);
WORD xrand16(void);
DWORD xrand32(void);
char *xstrstr(const char *str, const char *pat);
char *xstrrchr(const char *str, char ch);
char *xstrchr(const char *str, char ch);
int xsystem(char *cmd, int wait);
int xmemcmpi(unsigned char *, unsigned char *, int);
int xstrncmp(const char *first, const char *last, size_t count);
int html_replace(char *);
int html_replace2(char *);
int is_online(void);
int cat_wsprintf(LPTSTR lpOutput, LPCTSTR lpFormat, ...);

#endif
