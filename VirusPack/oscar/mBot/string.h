#ifndef INC_STRING_H
#define INC_STRING_H

#include <string>
#include <vector>
#include <cstddef>
#include <exception>
#include <sstream>

// function declaractions

bool tokenize (const std::string& pString, const std::string& pDelims,
			   std::vector<std::string>& pV, bool pRest = false);
std::string token (const std::string& pString, const std::string& pDelims,
				   std::ptrdiff_t pIndex, bool pRest = false);
std::string::size_type numtok (const std::string& pString, const std::string& pDelims);

std::string upper (const std::string& pString);
std::string lower (const std::string& pString);
std::string lft (const std::string& pString, std::ptrdiff_t pIndex);
std::string rt (const std::string& pString, std::ptrdiff_t pIndex);

std::string trimLeadingSpaces (const std::string& pString);
std::string trimTrailingSpaces (const std::string& pString);
std::string trimBothSpaces (const std::string& pString);

std::string strfind (const std::string& pStringOne, const std::string& pStringTwo);
std::string strfindi (const std::string& pStringOne, const std::string& pStringTwo);

std::string replace (const std::string& pSrc, const std::string& pFrom,
					 const std::string& pTo, bool pExact = false);
std::string replacei (const std::string& pSrc, const std::string& pFrom,
					 const std::string& pTo, bool pExact = false);
std::string remove (const std::string& pSrc, const std::string& pRemove,
				    bool pExact = false);
std::string removei (const std::string& pSrc, const std::string& pRemove,
					 bool pExact = false);

std::string reverse (const std::string& pString);

bool wildmatch (const std::string& pWildStr, const std::string& pString);
bool wildmatchi (const std::string& pWildStr, const std::string& pString);

bool istok (const std::string& pString, const std::string& pToken,
		    const std::string& pDelims);
bool istoki (const std::string& pString, const std::string& pToken,
			 const std::string& pDelims);
bool isnumstr (const std::string& pString);

// exception classes

class bad_lex : public std::exception
{
	std::string mS;
public:
	bad_lex() : std::exception(""), mS("") {}
	bad_lex(const char *pStr) : std::exception(pStr), mS(pStr) {}
	virtual ~bad_lex() {}
	virtual const char *what() const { return mS.c_str(); }
};


// inline functions

inline int scmp (const std::string& pStringOne, const std::string& pStringTwo)
{
	if (pStringOne < pStringTwo)
		return -1;
	else if (pStringOne == pStringTwo)
		return 0;
	else
		return 1;
}
inline int scmpi (const std::string& pStringOne, const std::string& pStringTwo)
{
	std::string upperOne = upper(pStringOne);
	std::string upperTwo = upper(pStringTwo);
	if (upperOne < upperTwo)
		return -1;
	else if (upperOne == upperTwo)
		return 0;
	else
		return 1;
}

template <typename To, typename From> inline To lex (const From& pFrom)
{
	std::stringstream stringStream;
	To ret;

	if ( !(stringStream << pFrom) ||
		 !(stringStream >> ret)   ||
		 !( (stringStream >> std::ws).eof())
		)
		throw bad_lex("lex(): could not convert from source to target");
	return ret;
}

#endif // INC_STRINGHELPER_H
