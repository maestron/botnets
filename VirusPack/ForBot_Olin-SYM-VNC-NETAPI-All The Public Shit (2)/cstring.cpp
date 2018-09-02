#include "main.h"
#include "cstring.h"
#include "mainctrl.h"

#include <vector>

CString::CString() {m_szString=NULL;m_iLength=0;m_bIsCryptStr=false;m_szTemp=NULL; }
CString::CString(const char *szString){
	m_szString=NULL;
	m_iLength=0;
	Assign(szString);
	m_bIsCryptStr=false;
	m_szTemp=NULL; 
}

CString::CString(const CString &pString) {
	m_szString=NULL;
	m_iLength=0;
	Assign(pString);
	m_bIsCryptStr=false;
	m_szTemp=NULL; 
}

CString::CString(const int iValue) {
	char szTemp[16];
	sprintf(szTemp, "%d", iValue);
	m_szString=NULL;
	m_iLength=0;
	Assign(szTemp);
	m_bIsCryptStr=false;
	m_szTemp=NULL; 
}

CString::~CString() {
	#ifdef _DEBUG
		_CrtCheckMemory();
	#endif
	if(m_szString!=NULL) delete [] m_szString;
	m_szString=NULL;
	if(m_szTemp!=NULL) delete [] m_szTemp; 
	m_szTemp=NULL;
	m_iLength=0; 
}

void CString::Assign(const char *szString)
{	
	if(!szString) return;

	#ifdef _DEBUG
		_CrtCheckMemory();
	#endif

	int iLength=::strlen(szString);

	if(m_szString) {
		delete [] m_szString;
	}

	m_szString=new char [iLength+2]; 
	if(!m_szString) return; 
	m_iLength=iLength;
	memset(m_szString, 0, m_iLength+2); 
	::strncpy(m_szString, szString, m_iLength); 
}

void CString::Assign(const CString &pString) { 	Assign(pString.CStr()); }

void CString::Assign(const int iValue) { 
	char szTemp[16]; 
	sprintf(szTemp, "%d", iValue); 
	Assign(szTemp); 
}

void CString::Append(const char *szString){	
	if(!szString) return;
		#ifdef _DEBUG
			_CrtCheckMemory();
		#endif
		int iLength=m_iLength+::strlen(szString); 
		char *szTemp=new char[iLength+1];
 		if(!m_szString) return; 
		m_iLength=iLength; 
		::strcpy(szTemp, m_szString);
		::strcat(szTemp, szString); if(m_szString) delete [] m_szString; m_szString=szTemp; 
}

void CString::Append(const CString &pString) { 	Append(pString.CStr()); }

void CString::Append(const int iValue) { 	char szTemp[16]; sprintf(szTemp, "%d", iValue); 
	Append(szTemp); }

int CString::Compare(const char *szString) const
{	
	if(!szString && !m_szString) return 0; 
	if(!szString) return 1;
	return strcmp(m_szString, szString); 
	//return 1;
}

int CString::Compare(const CString &pString) const { 
	return Compare(pString.CStr()); 
}

int CString::CompareNoCase(const char *szString) const {	
	if(!szString && !m_szString) return 0; 
	if(!szString) return 1;
	return stricmp(m_szString, szString); 
	//return 2;
}

int CString::CompareNoCase(const CString &pString) const { 	return Compare(pString.CStr()); }

void CString::Empty() { 
	if(m_szString) delete [] m_szString; 
	m_szString=NULL; 
}

void CString::Format(const char *szFormat, ...) {	
	if(!szFormat) return;
	va_list va_alist; 
	char formatbuf[8192];
	va_start(va_alist, szFormat);
	vsnprintf(formatbuf, sizeof(formatbuf), szFormat, va_alist); 
	va_end(va_alist);
	Assign(formatbuf); 
}

int CString::Find(const char cChar) const { 
	return Find(cChar, 0); 
}

int CString::Find(const char cChar, int iStart) const
{	
	if(::strchr(m_szString, cChar)==NULL) return 0;
	return (int)((char*)::strchr(m_szString, cChar)-(char*)m_szString)+1; 
}

int CString::Find(const CString &pString) const 
{ 
	return Find(pString, 0); 
}

int CString::Find(const CString &pString, int iStart) const
{ 
	return Find(pString.CStr(), iStart);
}

int CString::Find(const char *szString) const 
{ 
	return Find(szString, 0); 
}

int CString::Find(const char *szString, int iStart) const
{	
	if(!szString) return 0;
	if(::strstr(m_szString, szString)==NULL) return 0;
	return (int)((char*)::strstr(m_szString, szString)-(char*)m_szString)+1; 
}

char *CString::GetBuffer(int iBufLen)
{	
	if(!iBufLen) return NULL;
	m_iLength=iBufLen; 
	if(m_szString) delete [] m_szString;
	m_szString=new char[iBufLen+1];
	memset(m_szString, 0, iBufLen+1); 
	return m_szString; 
}

int CString::GetLength() const 
{ 
	return m_iLength; 
}

CString CString::Mid(int iFirst, int iCount) const
{	
	if(iCount<1) return CString("");
	CString sTemp; 
	char *szBuf=new char[iCount+1];
	memset(szBuf, 0, iCount+1); 
	memcpy(szBuf, &m_szString[iFirst], iCount);
	#ifdef _DEBUG
		_CrtCheckMemory();
	#endif
		sTemp.Assign(szBuf);
	#ifdef _DEBUG
		_CrtCheckMemory();
	#endif
	delete [] szBuf;
	return sTemp; 
}

CString CString::Mid(int iFirst) const
{
	int iCount=GetLength()-iFirst; 
	return Mid(iFirst, iCount); 
}

CString CString::Split() const
{
	return 1;
}

CString CString::Token(int iNum, const char *szDelim, bool bUseQuotes)
{	
	if(!szDelim) return CString("");
	#ifdef _DEBUG
		_CrtCheckMemory();
	#endif
	std::vector<char*> vTokens; CString sTemp(m_szString); 
	char *szText=sTemp.Str();
	bool bInQuotes=false; 
	while(*szText)
	{	
		while(*szText==szDelim[0]) szText++;	// skip leading whitespace
		bInQuotes=(*szText=='\"');				// see if this token is quoted
		if(bInQuotes) szText++;					// skip leading quote
		vTokens.push_back(szText);				// store position of current token
		if(bInQuotes)
		{
			while(*szText&&!(*szText=='\"'&&(szText[1]==' '||szText[1]=='\0'))) szText++;
			if(*szText)
			{	
				*szText='\0'; 
				if(szText[1]) szText+=2; 
			}
		} else {
			while(*szText&&*szText!=szDelim[0]) szText++;
			if(*szText&&*szText==szDelim[0])
			{
				*szText='\0'; 
				szText++; 
			}
		}
	}
	if(iNum>=vTokens.size()) return CString("");
	#ifdef _DEBUG
		_CrtCheckMemory();
	#endif
	return CString(vTokens.at(iNum)); 
}

CString CString::Token(int iNum, const char *szDelim) 
{ 
	return Token(iNum, szDelim, false);
}

void CString::operator=(const CString &sStr)
 { 
	Assign(sStr.CStr()); 
}

void CString::operator=(const char *szStr) 
{ 
	Assign(szStr); 
}

char &CString::operator[](int iPos)
{
	return m_szString[iPos]; 
}

const char &CString::operator[](int iPos) const
{	
	return m_szString[iPos]; 
}

const char *CString::CStr() const
{
	return (const char *)m_szString;
}

const char *CString::CStr()
{	
	return (const char *)m_szString; 
}

char *CString::Str()
{	
	return m_szString; 
}