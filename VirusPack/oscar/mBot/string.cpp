#include <vector>
#include <string>
#include <cstddef>
#include <cctype>
#include <stdexcept>
#include <exception>
#include "string.h"
using std::string;
using std::vector;

typedef string::size_type ssize_t;

bool tokenize (const string& pString, const string& pDelims,
			   vector<string>& pV, bool pRest /* = false */)
{
	if (
		pString.empty() ||
		pDelims.empty() ||
		!numtok(pString,pDelims)
		)
		return false;

	pV.clear();

	ssize_t beg, end;
	beg = pString.find_first_not_of(pDelims);
	while (beg != string::npos)
	{
		end = pString.find_first_of(pDelims,beg);
		if (end == string::npos)
			end = pString.size();
		pV.push_back(pString.substr(beg, (pRest) ? string::npos : end - beg));
		beg = pString.find_first_not_of(pDelims,end);
	}
	return true;
}

string token (const string& pString, const string& pDelims,ptrdiff_t pIndex,
			 bool pRest /* = false */)
{
	if (
		pString.empty() ||
		pDelims.empty() ||
		!numtok(pString,pDelims)
		)
		return "";
	if (pIndex < 0)
		pIndex = numtok(pString,pDelims) - (-pIndex);
	ssize_t beg, end;
	beg = pString.find_first_not_of(pDelims);
	ptrdiff_t x = 0;
	string ret;
	while (beg != string::npos)
	{
		end = pString.find_first_of(pDelims,beg);
		if (end == string::npos)
			end = pString.size();
		if (x == pIndex)
		{
			ret = pString.substr(beg, (pRest) ? string::npos : end - beg);
			break;
		}
		beg = pString.find_first_not_of(pDelims,end);
		++x;
	}
	return ret;
}

ssize_t numtok (const string& pString, const string& pDelims)
{
	if (pString.empty() || pDelims.empty())
		return 0;
	ssize_t retVal = 0;
	size_t beg, end;
	beg = pString.find_first_not_of(pDelims);
	while(beg != string::npos)
	{
		++retVal;
		end = pString.find_first_of(pDelims,beg);
		beg = pString.find_first_not_of(pDelims,end);
	}
	return retVal;
}

string upper (const string& pString)
{
	if (pString.empty())
		return "";
	ssize_t len = pString.size();
	string ret = pString;

	for(ssize_t x=0;x<len;++x)
		ret[x] = ::toupper(pString[x]);
	return ret;
}

string lower (const string& pString)
{
	if (pString.empty())
		return "";
	ssize_t len = pString.size();
	string ret = pString;
	for(ssize_t x=0;x<len;++x)
		ret[x] = ::tolower(pString[x]);
	return ret;
}

string lft (const string& pString, ptrdiff_t pIndex)
{
	if (pString.empty())
		return "";
	if (pIndex < 0)
		pIndex = pString.size() - (-pIndex);
	return pString.substr(0, pIndex);
}

string rt (const string& pString, ptrdiff_t pIndex)
{
	if (pString.empty())
		return "";
	ssize_t len = pString.size();
	if (pIndex < 0)
		pIndex = len - (-pIndex);
	return pString.substr(len - pIndex, string::npos);
}

string trimLeadingSpaces (const string& pString)
{
	if (pString.empty())
		return "";
	ssize_t len = pString.size();
	ssize_t x=0;
	while (x < len)
	{
		if ( ::isspace(pString[x]) )
		{
			++x;
			continue;
		}
		else
			break;
	}
	return pString.substr(x,string::npos);
}

string trimTrailingSpaces (const string& pString)
{
	if (pString.empty())
		return "";
	ssize_t len = pString.size();
	ssize_t x=len-1;
	while (x >= 0)
	{
		if ( ::isspace(pString[x]) )
		{
			--x;
			continue;
		}
		else
			break;
	}
	printf("returning \"%s\"\n", pString.substr(0,x+1).c_str());
	return pString.substr(0,x + 1);
}

string trimBothSpaces (const string& pString)
{
	if (pString.empty())
		return "";
	return ( trimLeadingSpaces(trimTrailingSpaces(pString)) );
}

string strfind (const string& pStringOne, const string& pStringTwo)
{
	if (pStringOne.empty() || pStringTwo.empty())
		return "";
	ssize_t findRes = pStringOne.find(pStringTwo);
	if (findRes == string::npos)
		return "";
	return pStringOne.substr(findRes,string::npos);
}

string strfindi (const string& pStringOne, const string& pStringTwo)
{
	if (pStringOne.empty() || pStringTwo.empty())
		return "";
	string oneUpper = upper(pStringOne);
	string twoUpper = upper(pStringTwo);
	ssize_t findRes = oneUpper.find(twoUpper);
	if (findRes == string::npos)
		return "";
	return pStringOne.substr(findRes,string::npos);
}

string replace(const string& pSrc, const string& pFrom, const string& pTo,
			   bool pExact /* = false */ )
{
	if (pSrc.empty() || pFrom.empty())
		return "";
	ssize_t beg;
	string ret = pSrc;
	if (!pExact)
	{
		beg = ret.find(pFrom);
		while (beg != string::npos)
		{
			ret.replace(beg,pFrom.size(),pTo);
			beg = ret.find(pFrom, beg + pTo.size());
		}
	}
	else
	{
		beg = ret.find_first_of(pFrom);
		while (beg != string::npos)
		{
			ret.replace(beg,1,pTo);
			beg = ret.find_first_of(pFrom,beg + pTo.size());
		}
	}
	return ret;
}

string replacei (const string& pSrc, const string& pFrom, const string& pTo,
				 bool pExact /* = false */)
{
	if (pSrc.empty() || pFrom.empty())
		return "";
	string ret = pSrc;
	string srcUpper  = upper(pSrc);
	string fromUpper = upper(pFrom);

	if (!pExact)
	{
		ssize_t beg = srcUpper.find(fromUpper);
		while (beg != string::npos)
		{
			ret.replace(beg, pFrom.size(), pTo);
			srcUpper.replace(beg,fromUpper.size(),pTo);
			beg = srcUpper.find(fromUpper,beg + pTo.size());
		}
	}
	else
	{
		ssize_t beg = srcUpper.find_first_of(fromUpper);
		while (beg != string::npos)
		{
			ret.replace(beg,1,pTo);
			srcUpper.replace(beg,1,pTo);
			beg = srcUpper.find(fromUpper, beg + pTo.size());
		}
	}
	return ret;
}

string remove (const string& pSrc, const string& pRemove, bool pExact /* = false */)
{
	if (pSrc.empty() || pRemove.empty())
		return "";
	string ret = pSrc;
	if (!pExact)
	{
		ssize_t beg = pSrc.find(pRemove);
		while (beg != string::npos)
		{
			ret.erase(beg,pRemove.size());
			beg = ret.find(pRemove, beg);
		}
	}
	else
	{
		ssize_t beg = pSrc.find_first_of(pRemove);
		while (beg != string::npos)
		{
			ret.erase(beg,1);
			beg = ret.find_first_of(pRemove,beg);
		}
	}
	return ret;
}

string removei (const string& pSrc, const string& pRemove, bool pExact /* = false */ )
{
	if (pSrc.empty() || pRemove.empty())
		return "";
	string ret = pSrc;
	string srcUpper = upper(pSrc);
	string removeUpper = upper(pRemove);
	if (!pExact)
	{
		ssize_t beg = srcUpper.find(removeUpper);
		while (beg != string::npos)
		{
			ret.erase(beg,pRemove.size());
			srcUpper.erase(beg,pRemove.size());
			beg = srcUpper.find(removeUpper,beg);
		}
	}
	else
	{
		ssize_t beg = srcUpper.find_first_of(removeUpper);
		while (beg != string::npos)
		{
			ret.erase(beg,1);
			srcUpper.erase(beg,1);
			beg = srcUpper.find_first_of(removeUpper,beg);
		}
	}
	return ret;
}

string reverse (const string& pString)
{
	string ret;
	ssize_t len = pString.size();
	ssize_t x=len - 1;
	ssize_t y=0;
	while (y<len)
	{
		ret += pString[x];
		--x;
		++y;
	}
	return ret;
}

bool wildmatch (const string& pWildStr, const string& pStr)
{
	if (pWildStr.empty() || pStr.empty())
		return false;

	const char *wild = pWildStr.c_str();
	const char *str  = pStr.c_str();

	const char *wildhold = 0;
	const char *strhold = 0;

	const char a = '*';
	const char q = '?';

	// look for any leading ? or non-special characters
	while ( *str )
	{
		if (*wild == a)
			break;
		if (*wild != *str && *wild != q)
			return false;
		++str;
		++wild;
	}

	while ( *str )
	{
		if (*wild == a)
		{
			if (!*(wild+1)) // last star in string so it will match anything
				return true;
			// take note of where the last wildcard was
			wildhold = ++wild;
			strhold  = str + 1;
		}
		else if (*wild == *str || *wild == q)
		{
			// it is just a single character match... continue walking string
			++str;
			++wild;
		}
		else
		{
			// its not an asterisk, nor a regular string match
			wild = wildhold;
			str = strhold;
			++strhold;
		}
	}
	while (*wild == a)
		++wild;
	return (*wild) ? false : true;
}

bool wildmatchi (const string& pWild, const string& pStr)
{
	return wildmatch ( upper(pWild), upper(pStr) );
}

bool istok (const string& pString, const string& pToken, const string& pDelims)
{
	vector<string> v;
	if (!tokenize(pString,pDelims,v))
		return false;
	typedef vector<string>::size_type vsize;
	vsize size = v.size();
	if (!size)
		return false;
	for(vsize x=0;x<size;++x)
		if (pToken == v[x])
			return true;
	return false;
}
bool istoki (const string& pString, const string& pToken, const string& pDelims)
{
	return istok( upper(pString), upper(pToken), upper(pDelims) );
}

bool isnumstr (const string& pString)
{
	ssize_t len = pString.size();
	for(ssize_t x=0;x<len;++x)
		if (! ::isdigit(pString[x]) )
			return false;
	return true;
}
