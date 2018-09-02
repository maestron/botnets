
#ifndef __CRYPTER_H__
#define __CRYPTER_H__

#include "cstring.h"

class CCryptStr : public CString
{
public:
	CCryptStr(int iKey);
	~CCryptStr();

	char *Str();

	void Release();

protected:
	void Decrypt();
	int m_iKey;
	char *m_szDecStr;
};

#endif // __CRYPTER_H__
