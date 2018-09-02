#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Inc/CStr.h"

CStr::CStr(int len)
{
	String	= new char[len + 1];
	tmp		= new char[len + 1];
}

CStr::~CStr()
{
	delete [] String;
	delete [] tmp;
}

char *CStr::Str()
{
	return String;
}

int CStr::Len()
{
	return strlen(String);
}

char *CStr::Gettok(int i, char sep)
{
	if (i <= 0)
		return "";
	int x = 0, a = 0, f = 1;
	for (x = 0; String[x] != '\0'; x++)
	{
		if (String[x] == sep)
		{
			f++;
			x++;
		}
		if (f == i)
			tmp[a++] = String[x];
	}
	tmp[a] = '\0';
	return tmp;
}

void CStr::Set(char *str)
{
	if (str == NULL)
		return;
	strcpy(String, str);
}

char *CStr::Mid(int i, int len)
{
	if (i <= 0 || len < 1)
		return "";
	int x, y = 0;
	for (x = (i - 1); y < len; x++)
		tmp[y++] = String[x];
	tmp[y] = '\0';
	return tmp;
}

int CStr::WildM(const char *pattern, const char *string)
{
	switch(*pattern)
	{
		case '\0': return *string;
		case '*' : return !(!WildM(pattern+1, string) || *string && !WildM(pattern, string+1));
		case '?' : return !(*string && !WildM(pattern+1, string+1));
		default  : return !((toupper(*pattern) == toupper(*string)) && !WildM(pattern+1, string+1));
	}
}