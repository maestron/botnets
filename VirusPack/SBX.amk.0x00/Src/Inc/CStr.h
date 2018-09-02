#ifndef __CSTR_H__
#define __CSTR_H__

class CStr
{
public:
	CStr(int len);
	~CStr();

public:
	char *Str	();
	int   Len	();
	char *Gettok(int i, char sep);
	void  Set	(char *str);
	char *Mid	(int i, int len);
	int   WildM (const char* pattern, const char *string);

public:
	char *String;
	char *tmp;
};

#endif