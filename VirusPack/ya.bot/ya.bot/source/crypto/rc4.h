/*  ya.bot  */

#ifndef NO_CRYPTORC4
void rc4_crypt(struct rc4_state *s, unsigned char *data, int length);
void rc4_setup(struct rc4_state *s, unsigned char *key,  int length);

struct rc4_state
{
	int x, y, m[256];
};
#endif