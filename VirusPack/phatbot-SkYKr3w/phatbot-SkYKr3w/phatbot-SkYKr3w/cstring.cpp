

#include "main.h"
#include "cstring.h"
#include "mainctrl.h"
#include "cthread.h"

#include <vector>

// Token cache
token_data	 g_tData[128];
CMutex		 g_mMutex;
bool		 g_bInited=false;

CString::CString() {
	if(!g_bInited) {
		for(int i=0;i<128; i++) {
			token_data *pData=&g_tData[i]; pData->szDelim=NULL; pData->szString=NULL;
		}
		g_bInited=true; }

	m_szString=NULL;
	m_iLength=0;
	m_bIsCryptStr=false;
	m_szTemp=NULL; }

CString::CString(const char *szString) {
	if(!g_bInited) {
		for(int i=0;i<128; i++) {
			token_data *pData=&g_tData[i]; pData->szDelim=NULL; pData->szString=NULL;
		}
		g_bInited=true; }

	m_szString=NULL;
	m_iLength=0;
	Assign(szString);
	m_bIsCryptStr=false;
	m_szTemp=NULL; }

CString::CString(const CString &pString) {
	if(!g_bInited) {
		for(int i=0;i<128; i++) {
			token_data *pData=&g_tData[i]; pData->szDelim=NULL; pData->szString=NULL;
		}
		g_bInited=true; }

	m_szString=NULL;
	m_iLength=0;
	Assign(pString);
	m_bIsCryptStr=false;
	m_szTemp=NULL; }

CString::CString(const int iValue) {
	if(!g_bInited) {
		for(int i=0;i<128; i++) {
			token_data *pData=&g_tData[i]; pData->szDelim=NULL; pData->szString=NULL;
		}
		g_bInited=true; }

	char szTemp[16];
	sprintf(szTemp, "%d", iValue);
	m_szString=NULL;
	m_iLength=0;
	Assign(szTemp);
	m_bIsCryptStr=false;
	m_szTemp=NULL; }

CString::~CString() {
	if(m_szString!=NULL) { delete [] m_szString; m_szString=NULL; }
	if(m_szTemp!=NULL) { delete [] m_szTemp; m_szTemp=NULL; }
	m_iLength=0; }

void CString::Assign(const char *szString)
{	if(!szString) return;

	int iLength=::strlen(szString);
	if(m_szString) { delete [] m_szString; m_szString=NULL; }

	m_szString=new char [iLength+2]; if(!m_szString) return; m_iLength=iLength;
	memset(m_szString, 0, m_iLength+2); ::strncpy(m_szString, szString, m_iLength); }
void CString::Assign(const CString &pString) { Assign(pString.CStr()); }
void CString::Assign(const int iValue) { char szTemp[16]; sprintf(szTemp, "%d", iValue); Assign(szTemp); }

void CString::Append(const char *szString)
{	if(!szString || !m_szString) return;
	int iLength=m_iLength+strlen(szString); char *szTemp=new char[iLength+20];
	if(!szTemp) return;
 	m_iLength=iLength; strncpy(szTemp, m_szString, iLength+1);
	strncat(szTemp, szString, iLength+1);
	if(m_szString) delete [] m_szString;
	m_szString=szTemp; }
void CString::Append(const CString &pString) { Append(pString.CStr()); }
void CString::Append(const int iValue) { char szTemp[16]; sprintf(szTemp, "%d", iValue); Append(szTemp); }

int CString::Compare(const char *szString) const
{	if(!szString && !m_szString) return 0; if(!szString) return 1;
	if(m_bIsCryptStr) return Decrypt().Compare(szString);
	else return ::strcmp(m_szString, szString); }
int CString::Compare(const CString &pString) const { return Compare(pString.CStr()); }
int CString::CompareNoCase(const char *szString) const
{	if(!szString && !m_szString) return 0; if(!szString) return 1;
	if(m_bIsCryptStr) return Decrypt().CompareNoCase(szString);
	else return stricmp(m_szString, szString); }
int CString::CompareNoCase(const CString &pString) const { return Compare(pString.CStr()); }

CString CString::Decrypt() const
{	if(!m_iCryptKey) return CString(""); CString sRetVal;
	char *pTemp=sRetVal.GetBuffer(GetLength()+1);
	for(int i=0; i<GetLength(); i++) pTemp[i]=m_szString[i]^(m_iCryptKey+(i*(m_iCryptKey%10)+1));
	return sRetVal; }

void CString::Empty() { if(m_szString) delete [] m_szString; m_szString=NULL; }

void CString::Format(const char *szFormat, ...)
{	if(!szFormat) return;
	va_list va_alist; char formatbuf[8192]; va_start(va_alist, szFormat);
	vsnprintf(formatbuf, sizeof(formatbuf), szFormat, va_alist); va_end(va_alist);
	Assign(formatbuf); }

int CString::Find(const char cChar) const { return Find(cChar, 0); }
int CString::Find(const char cChar, int iStart) const
{	if(m_bIsCryptStr) return Decrypt().Find(cChar, iStart);
	if(::strchr(m_szString, cChar)==NULL) return 0;
	return (int)((char*)::strchr(m_szString, cChar)-(char*)m_szString)+1; }
int CString::Find(const CString &pString) const { return Find(pString, 0); }
int CString::Find(const CString &pString, int iStart) const { return Find(pString.CStr(), iStart); }
int CString::Find(const char *szString) const { return Find(szString, 0); }
int CString::Find(const char *szString, int iStart) const
{	if(!szString) return 0;
	if(m_bIsCryptStr) return Decrypt().Find(szString, iStart);
	if(::strstr(m_szString, szString)==NULL) return 0;
	return (int)((char*)::strstr(m_szString, szString)-(char*)m_szString)+1; }

char *CString::GetBuffer(int iBufLen)
{	if(!iBufLen) return NULL;
	m_iLength=iBufLen;
	char *szNewString=new char[iBufLen+1]; if(!szNewString) return NULL;
	if(m_szString) delete [] m_szString; m_szString=szNewString;
	memset(m_szString, 0, iBufLen+1); return m_szString; }

int CString::GetLength() const
{	if(!m_szString) return NULL;
	return strlen(m_szString); }

int CString::GetLength()
{	if(!m_szString) return NULL;
	m_iLength=strlen(m_szString);
	return m_iLength; }

CString CString::Mid(int iFirst, int iCount) const
{	if(iCount<1) return CString("");
	if(m_bIsCryptStr) return Decrypt().Mid(iFirst, iCount);
	CString sTemp; char *szBuf=new char[iCount+1]; if(!szBuf) return CString("");
	memset(szBuf, 0, iCount+1); memcpy(szBuf, &m_szString[iFirst], iCount);
	sTemp.Assign(szBuf);
	delete [] szBuf; return sTemp; }
CString CString::Mid(int iFirst) const
{	int iCount=GetLength()-iFirst; return Mid(iFirst, iCount); }

/*
typedef struct token_data_s {
	unsigned char		 szMD5[16];
	char				*szString;
	char				*szDelim;
	std::vector<char*>	 vTokens;
} token_data;
*/

CString CString::Token(int iNum, const char *szDelim, bool bUseQuotes)
{	static int iCacheIndex=0; int i;

	if(!szDelim) return CString("");

	if(m_bIsCryptStr) return Decrypt().Token(iNum, szDelim, bUseQuotes);

	char *szStrCopy=new char[strlen(m_szString)+2];
	memset(szStrCopy, 0, strlen(m_szString)+2);
	strncpy(szStrCopy, m_szString, strlen(m_szString)+1);

	//! Compute MD5 of input token
	md5::MD5_CTX md5; md5::MD5Init(&md5); unsigned char szMD5[16];
	md5::MD5Update(&md5, (unsigned char*)szStrCopy, strlen(szStrCopy));
	md5::MD5Final(szMD5, &md5);

	g_mMutex.Lock();
	for(i=0; i<128; i++) {
		token_data *pData=&g_tData[i]; if(!pData->szDelim) continue;

		if(	!memcmp(pData->szMD5,	szMD5,		sizeof(pData->szMD5)) &&
			!memcmp(pData->szDelim, szDelim,	strlen(szDelim))) {
			g_mMutex.Unlock();
			try {
				if(iNum>pData->vTokens.size()) return CString("");
				return pData->vTokens.at(iNum);
			} catch(out_of_range) {
				return CString("");
			};
		}
	}
		
	iCacheIndex++; if(iCacheIndex>=128) iCacheIndex=0;
	memcpy(g_tData[iCacheIndex].szMD5, szMD5, sizeof(szMD5));
	g_tData[iCacheIndex].vTokens.clear();
	
	//! Copy the string

	if(g_tData[iCacheIndex].szString) delete [] g_tData[iCacheIndex].szString;
	if(g_tData[iCacheIndex].szDelim) delete [] g_tData[iCacheIndex].szDelim;
	g_tData[iCacheIndex].szString=szStrCopy;
	g_tData[iCacheIndex].szDelim=new char[strlen(szDelim)+2];
	memset(g_tData[iCacheIndex].szDelim, 0, strlen(szDelim)+2);
	strcpy(g_tData[iCacheIndex].szDelim, szDelim);

	char *szText=g_tData[iCacheIndex].szString;
	bool bInQuotes=false; while(*szText)
	{	while(*szText==szDelim[0]) szText++;			// skip leading whitespace
		bInQuotes=(*szText=='\"');						// see if this token is quoted
		if(bInQuotes) szText++;							// skip leading quote
		g_tData[iCacheIndex].vTokens.push_back(szText);	// store position of current token
		if(bInQuotes)
		{	// find next quote followed by a space or terminator
			while(*szText&&*szText!='\"') szText++;
			if(*szText)
			{	*szText='\0'; if(szText[1]) szText+=2; }
		}
		else // !bInQuotes
		{	// skip to next non-whitespace/delimiter character
			while(*szText&&*szText!=szDelim[0]) szText++;
			if(*szText&&*szText==szDelim[0])
			{	*szText='\0'; szText++; }
		}
	} // while(*szText)

	if(iNum>=g_tData[iCacheIndex].vTokens.size()) {
		g_mMutex.Unlock(); return CString(""); }

	g_mMutex.Unlock(); return CString(g_tData[iCacheIndex].vTokens.at(iNum)); }
CString CString::Token(int iNum, const char *szDelim) { return Token(iNum, szDelim, false); }

void CString::operator=(const CString &sStr) { Assign(sStr.CStr()); }
void CString::operator=(const char *szStr) { Assign(szStr); }
char &CString::operator[](int iPos)
{	if(m_bIsCryptStr) return Decrypt().operator[](iPos);
	return m_szString[iPos]; }
const char &CString::operator[](int iPos) const
{	if(m_bIsCryptStr) return Decrypt().operator[](iPos);
	return m_szString[iPos]; }

const char *CString::CStr() const
{	return (const char *)m_szString; }
const char *CString::CStr()
{	if(m_bIsCryptStr)
	{	if(m_szTemp) delete [] m_szTemp; m_szTemp=NULL;
		CString sDecrypt=Decrypt(); m_szTemp=new char[sDecrypt.GetLength()+1];
		if(!m_szTemp) return NULL; strcpy(m_szTemp, sDecrypt.CStr());
		return (const char *)m_szTemp; }
	return (const char *)m_szString; }
char *CString::Str()
{	if(m_bIsCryptStr)
	{	if(!m_szTemp) delete [] m_szTemp; m_szTemp=NULL; 
		CString sDecrypt=Decrypt(); m_szTemp=new char[sDecrypt.GetLength()+1];
		if(!m_szTemp) return NULL; strcpy(m_szTemp, sDecrypt.CStr());
		return m_szTemp; }
	return m_szString; }
