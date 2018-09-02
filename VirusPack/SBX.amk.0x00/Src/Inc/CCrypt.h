#ifndef __CCRYPT_H__
#define __CCRYPT_H__

#include "Defines.h"
#include "blowfish.h"

class CCrypt
{
public:
	CCrypt();
	~CCrypt();

public:
	void	SetSKey		(int k);
	void	SCrypt		(char *str);

	void	SetBFKey	(const char *key);
	void	BFEncrypt	(const char *str, char *out);
	void	BFDecrypt	(const char *str, char *out);

private:
	int		SKey;
	char   *BFKey;
};

#endif