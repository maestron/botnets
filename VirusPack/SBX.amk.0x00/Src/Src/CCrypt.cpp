#include <string.h>
#include "../Inc/CCrypt.h"

CCrypt::CCrypt()
{
	BFKey = new char[1024];
}

CCrypt::~CCrypt()
{
	delete BFKey;
}

void CCrypt::SetSKey(int k)
{
	SKey = k;
}

void CCrypt::SCrypt(char *str)
{
	if (str == NULL)
		return;

	for (int i = 0; str[i] != '\0'; i++)
		str[i] = str[i] ^ (SKey + (i * (SKey % 10) + 1));
}

void CCrypt::SetBFKey(const char *key)
{
	if (key != NULL)
		strcpy(BFKey, key);
	else
		strcpy(BFKey, "");
}

void CCrypt::BFEncrypt(const char *str, char *out)
{
	bfEncrypt(BFKey, str, out);
}

void CCrypt::BFDecrypt(const char *str, char *out)
{
	bfDecrypt(BFKey, str, out);
}
