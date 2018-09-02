#define test

static unsigned char const k8[16] = {
	14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7 }; 
static unsigned char const k7[16] = {
	15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10 };
static unsigned char const k6[16] = {
	10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8 };
static unsigned char const k5[16] = {
	 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15 };
static unsigned char const k4[16] = {
	 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9 };
static unsigned char const k3[16] = {
	12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11 };
static unsigned char const k2[16] = {
	 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1 };
static unsigned char const k1[16] = {
	13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7 };

/* Byte-at-a-time substitution boxes */
static unsigned char k87[256];
static unsigned char k65[256];
static unsigned char k43[256];
static unsigned char k21[256];

typedef struct _gost_key {
    // gost 256 bit key
    unsigned long key[8];
} gost_key;

void kboxinit(void);
void gostcrypt(unsigned long const in[2],unsigned long out[2],unsigned long const key[8]);
void gostdecrypt(unsigned long const in[2],unsigned long out[2],unsigned long const key[8]);
void gostmac(unsigned long const *in,int len,unsigned long out[2],unsigned long const key[8]);
void
kboxinit(void){
	int i;
	for (i = 0; i < 256; i++) {
		k87[i] = k8[i >> 4] << 4 | k7[i & 15];
		k65[i] = k6[i >> 4] << 4 | k5[i & 15];
		k43[i] = k4[i >> 4] << 4 | k3[i & 15];
		k21[i] = k2[i >> 4] << 4 | k1[i & 15];
	}
}
#if __GNUC__
__inline__
#endif
static unsigned long f(unsigned long x)
{
	/* Do substitutions */
#if 0
	/* This is annoyingly slow */
	x = k8[x>>28 & 15] << 28 | k7[x>>24 & 15] << 24 |
	    k6[x>>20 & 15] << 20 | k5[x>>16 & 15] << 16 |
	    k4[x>>12 & 15] << 12 | k3[x>> 8 & 15] <<  8 |
	    k2[x>> 4 & 15] <<  4 | k1[x     & 15];
#else
	/* This is faster */
	x = k87[x>>24 & 255] << 24 | k65[x>>16 & 255] << 16 |
	    k43[x>> 8 & 255] <<  8 | k21[x & 255];
#endif
	return x<<11 | x>>(32-11);
}

void
gostcrypt(
    unsigned long const in[2],
    unsigned long out[2],
    unsigned long const key[8])
{
	register unsigned long n1, n2; /* As named in the GOST */
	n1 = in[0];
	n2 = in[1];

	/* Instead of swapping halves, swap names each round */
	n2 ^= f(n1+key[0]);
	n1 ^= f(n2+key[1]);
	n2 ^= f(n1+key[2]);
	n1 ^= f(n2+key[3]);
	n2 ^= f(n1+key[4]);
	n1 ^= f(n2+key[5]);
	n2 ^= f(n1+key[6]);
	n1 ^= f(n2+key[7]);

	n2 ^= f(n1+key[0]);
	n1 ^= f(n2+key[1]);
	n2 ^= f(n1+key[2]);
	n1 ^= f(n2+key[3]);
	n2 ^= f(n1+key[4]);
	n1 ^= f(n2+key[5]);
	n2 ^= f(n1+key[6]);
	n1 ^= f(n2+key[7]);

	n2 ^= f(n1+key[0]);
	n1 ^= f(n2+key[1]);
	n2 ^= f(n1+key[2]);
	n1 ^= f(n2+key[3]);
	n2 ^= f(n1+key[4]);
	n1 ^= f(n2+key[5]);
	n2 ^= f(n1+key[6]);
	n1 ^= f(n2+key[7]);

	n2 ^= f(n1+key[7]);
	n1 ^= f(n2+key[6]);
	n2 ^= f(n1+key[5]);
	n1 ^= f(n2+key[4]);
	n2 ^= f(n1+key[3]);
	n1 ^= f(n2+key[2]);
	n2 ^= f(n1+key[1]);
	n1 ^= f(n2+key[0]);

	/* There is no swap after the last round */
	out[0] = n2;
	out[1] = n1;
}

void
gostdecrypt(
    unsigned long const in[2],
    unsigned long out[2],
    unsigned long const key[8])
{
	register unsigned long n1, n2; /* As named in the GOST */
	n1 = in[0];
	n2 = in[1];

	n2 ^= f(n1+key[0]);
	n1 ^= f(n2+key[1]);
	n2 ^= f(n1+key[2]);
	n1 ^= f(n2+key[3]);
	n2 ^= f(n1+key[4]);
	n1 ^= f(n2+key[5]);
	n2 ^= f(n1+key[6]);
	n1 ^= f(n2+key[7]);

	n2 ^= f(n1+key[7]);
	n1 ^= f(n2+key[6]);
	n2 ^= f(n1+key[5]);
	n1 ^= f(n2+key[4]);
	n2 ^= f(n1+key[3]);
	n1 ^= f(n2+key[2]);
	n2 ^= f(n1+key[1]);
	n1 ^= f(n2+key[0]);

	n2 ^= f(n1+key[7]);
	n1 ^= f(n2+key[6]);
	n2 ^= f(n1+key[5]);
	n1 ^= f(n2+key[4]);
	n2 ^= f(n1+key[3]);
	n1 ^= f(n2+key[2]);
	n2 ^= f(n1+key[1]);
	n1 ^= f(n2+key[0]);

	n2 ^= f(n1+key[7]);
	n1 ^= f(n2+key[6]);
	n2 ^= f(n1+key[5]);
	n1 ^= f(n2+key[4]);
	n2 ^= f(n1+key[3]);
	n1 ^= f(n2+key[2]);
	n2 ^= f(n1+key[1]);
	n1 ^= f(n2+key[0]);

	out[0] = n2;
	out[1] = n1;
}

void
gostmac(unsigned long const *in, int len, unsigned long out[2], unsigned long const key[8])
{
	register unsigned long n1, n2; /* As named in the GOST */

	n1 = 0;
	n2 = 0;

	while (len--) {
		n1 ^= *in++;
		n2 = *in++;

		/* Instead of swapping halves, swap names each round */
		n2 ^= f(n1+key[0]);
		n1 ^= f(n2+key[1]);
		n2 ^= f(n1+key[2]);
		n1 ^= f(n2+key[3]);
		n2 ^= f(n1+key[4]);
		n1 ^= f(n2+key[5]);
		n2 ^= f(n1+key[6]);
		n1 ^= f(n2+key[7]);

		n2 ^= f(n1+key[0]);
		n1 ^= f(n2+key[1]);
		n2 ^= f(n1+key[2]);
		n1 ^= f(n2+key[3]);
		n2 ^= f(n1+key[4]);
		n1 ^= f(n2+key[5]);
		n2 ^= f(n1+key[6]);
		n1 ^= f(n2+key[7]);
	}

	out[0] = n1;
	out[1] = n2;
}

/* Designed to cope with 15-bit rand() implementations */
#define RAND32 ((unsigned long)rand() << 17 ^ (unsigned long)rand() << 9 ^ rand())



