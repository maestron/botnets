#include "includes.h"
#include "extern.h"

#ifdef NO_BLOWFISH

unsigned long P[16 + 2], S[4][256];
char szBase64[] = "./0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

static unsigned long F(unsigned long x)
{
	unsigned short a, b, c, d;
	unsigned long  y;

	d = (unsigned short)(x & 0xFF); 
	x >>= 8;
	c = (unsigned short)(x & 0xFF); 
	x >>= 8;
	b = (unsigned short)(x & 0xFF); 
	x >>= 8;
	a = (unsigned short)(x & 0xFF);
	y = S[0][a] + S[1][b];
	y = y ^ S[2][c];
	y = y + S[3][d];

	return (y);
}

void BlowfishCipher(unsigned long *lLeft, unsigned long *lRight, bool bEncrypt)
{
	unsigned long lTemp = 0, lTempL = 0, lTempR = 0;

	lTempL = *lLeft;
	lTempR = *lRight;

	if (bEncrypt)
	{
		for (int iCipherCount = 0; iCipherCount < 16; ++iCipherCount)
		{
			lTempL = lTempL ^ P[iCipherCount];
			lTempR = F(lTempL) ^ lTempR;
			lTemp = lTempL;
			lTempL = lTempR;
			lTempR = lTemp;
		}
		lTemp = lTempL;
		lTempL = lTempR;
		lTempR = lTemp;
		lTempR = lTempR ^ P[16 + 0];
		lTempL = lTempL ^ P[16 + 1];
	}
	else
	{
		for (int iCipherCount = 16 + 1; iCipherCount > 1; --iCipherCount) 
		{
			lTempL = lTempL ^ P[iCipherCount];
			lTempR = F(lTempL) ^ lTempR;
			lTemp = lTempL;
			lTempL = lTempR;
			lTempR = lTemp;
		}
		lTemp = lTempL;
		lTempL = lTempR;
		lTempR = lTemp;
		lTempR = lTempR ^ P[1];
		lTempL = lTempL ^ P[0];
	}

	*lLeft = lTempL;
	*lRight = lTempR;

	return;
}

void InitializeBlowfish(char *szKey)
{
	int i = 0, j = 0, k = 0;
	unsigned long lInfo = 0, lLeft = 0, lRight = 0;

	for (i = 0; i < 4; i++) 
	{
		for (j = 0; j < 256; j++)
		S[i][j] = ORIG_S[i][j];
	}

	j = 0;

	for (i = 0; i < 16 + 2; ++i) 
	{
		for (k = 0; k < 4; ++k) 
		{
			lInfo = (lInfo << 8) | szKey[j];
			j = j + 1;
			if (j >= (int)strlen(szKey))
				j = 0;
		}
		P[i] = ORIG_P[i] ^ lInfo;
	}

	for (i = 0; i < 16 + 2; i += 2) 
	{
		BlowfishCipher(&lLeft, &lRight, true);
		P[i + 0] = lLeft;
		P[i + 1] = lRight;
	}

	for (i = 0; i < 4; ++i) 
	{
		for (j = 0; j < 256; j += 2) 
		{
			BlowfishCipher(&lLeft, &lRight, true);
			S[i][j + 0] = lLeft;
			S[i][j + 1] = lRight;
		}
	}
	return;
}

int CryptoBase64(char szCharacter)
{
	for (int iBaseCount = 0; iBaseCount < 64; iBaseCount++)
	{
		if (szBase64[iBaseCount] == szCharacter)
			return (iBaseCount);
	}
	return 0;
}

char *CryptoBlowfish(char *szString, bool bEncrypt)
{
	int iBaseCount = 0;
	char *szCheck = NULL, *szBuffer = NULL;
	unsigned long lLeft = 0, lRight = 0;
	unsigned char *szCurrentPointer = NULL;

	szBuffer = (char *)malloc((strlen(szString) + 9) * 2); 
	
	InitializeBlowfish(szBlowfishKey);

	szCheck = szBuffer;

	szCurrentPointer = (unsigned char *)szString;

	while (*szCurrentPointer) 
	{
		if (bEncrypt)
		{
			lLeft = ((*szCurrentPointer++) << 24);
			lLeft += ((*szCurrentPointer++) << 16);
			lLeft += ((*szCurrentPointer++) << 8);
			lLeft += (*szCurrentPointer++);

			lRight = ((*szCurrentPointer++) << 24);
			lRight += ((*szCurrentPointer++) << 16);
			lRight += ((*szCurrentPointer++) << 8);
			lRight += (*szCurrentPointer++);

			BlowfishCipher(&lLeft, &lRight, true);

			for (iBaseCount = 0; iBaseCount < 6; iBaseCount++) 
			{
				*szCheck++ = szBase64[lRight & 0x3F];
				lRight = (lRight >> 6);
			}

			for (iBaseCount = 0; iBaseCount < 6; iBaseCount++) 
			{
				*szCheck++ = szBase64[lLeft & 0x3F];
				lLeft = (lLeft >> 6);
			}
		}
		else
		{
			lRight = 0; lLeft = 0;

			for (iBaseCount = 0; iBaseCount < 6; iBaseCount++)
				lRight |= (CryptoBase64(*szCurrentPointer++)) << (iBaseCount * 6);

			for (iBaseCount = 0; iBaseCount < 6; iBaseCount++)
				lLeft |= (CryptoBase64(*szCurrentPointer++)) << (iBaseCount * 6);

			BlowfishCipher(&lLeft, &lRight, false);

			for (iBaseCount = 0; iBaseCount < 4; iBaseCount++)
				*szCheck++ = (lLeft & (0xFF << ((3 - iBaseCount) * 8))) >> ((3 - iBaseCount) * 8);

			for (iBaseCount = 0; iBaseCount < 4; iBaseCount++)
				*szCheck++ = (lRight & (0xFF << ((3 - iBaseCount) * 8))) >> ((3 - iBaseCount) * 8);
		}
	}
	*szCheck = '\0';
	return (szBuffer);
}

void BlowfishCrypt(char *szBuffer, bool bEncrypt)
{
	char *szString = NULL;

	if (bEncrypt)
	{
		szString = CryptoBlowfish(szBuffer, true);
		sprintf(szBuffer, "+OK %s", szString);
	}
	else
	{
		if (strstr(szBuffer, "+OK"))
		{
			for (int iStripCount = 0; iStripCount < (int)strlen(szBuffer); iStripCount++) 
			{
				if (iStripCount > 3) {
					szBuffer[iStripCount - 4] = szBuffer[iStripCount]; 
				}
			}

			szBuffer[iStripCount - 4] = '\0';

			szString = CryptoBlowfish(szBuffer, false);
			sprintf(szBuffer, "%s", szString);
		}
		else
		{
			szString = CryptoBlowfish(szBuffer, false);
			sprintf(szBuffer, "%s", szString);
		}
	}
	return;
}
#endif