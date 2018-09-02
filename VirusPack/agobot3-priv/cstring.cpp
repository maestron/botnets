/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (C) 2003 Ago

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

#include "main.h"
#include "cstring.h"
#include "utility.h"

#include <vector>

CString::CString() { m_szString=NULL; m_iLength=0; m_bIsCryptStr=false; m_szTemp=NULL; }
CString::CString(const char *szString) { m_szString=NULL; m_iLength=0; Assign(szString); m_bIsCryptStr=false; m_szTemp=NULL; }
CString::CString(const CString &pString) { m_szString=NULL; m_iLength=0; Assign(pString); m_bIsCryptStr=false; m_szTemp=NULL; }
CString::CString(const int iValue) { char szTemp[16]; sprintf(szTemp, "%d", iValue); m_szString=NULL; m_iLength=0; Assign(szTemp); m_bIsCryptStr=false; m_szTemp=NULL; }

CString::~CString() { if(m_szString) free(m_szString); m_szString=NULL; if(m_szTemp) free(m_szTemp); m_szTemp=NULL; m_iLength=0; }

void CString::Assign(const char *szString)
{	if(m_szString) free(m_szString); m_iLength=::strlen(szString);
	m_szString=(char*)malloc(m_iLength+1); memset(m_szString, 0, m_iLength+1); ::strncpy(m_szString, szString, m_iLength); }
void CString::Assign(const CString &pString) { Assign(pString.CStr()); }
void CString::Assign(const int iValue) { char szTemp[16]; sprintf(szTemp, "%d", iValue); Assign(szTemp); }

void CString::Append(const char *szString)
{	m_iLength+=::strlen(szString); char *szTemp=(char*)malloc(m_iLength+1);
	::strcpy(szTemp, m_szString); ::strcat(szTemp, szString);
	if(m_szString) free(m_szString); m_szString=szTemp; }
void CString::Append(const CString &pString) { Append(pString.CStr()); }
void CString::Append(const int iValue) { char szTemp[16]; sprintf(szTemp, "%d", iValue); Append(szTemp); }

int CString::Compare(const char *szString) const
{	if(m_bIsCryptStr) return Decrypt().Compare(szString);
	else return ::strcmp(m_szString, szString); }
int CString::Compare(const CString &pString) const { return Compare(pString.CStr()); }
int CString::CompareNoCase(const char *szString) const
{	if(m_bIsCryptStr) return Decrypt().CompareNoCase(szString);
	else return stricmp(m_szString, szString); }
int CString::CompareNoCase(const CString &pString) const { return Compare(pString.CStr()); }

CString CString::Decrypt() const
{	if(!m_iCryptKey) return CString(""); CString sRetVal;
	char *pTemp=sRetVal.GetBuffer(GetLength());
	for(int i=0; i<GetLength(); i++) pTemp[i]=m_szString[i]^(m_iCryptKey+(i*(m_iCryptKey%10)+1));
	return sRetVal; }

void CString::Empty() { if(m_szString) free(m_szString); m_szString=NULL; }

void CString::Format(const char *szFormat, ...)
{	va_list va_alist; char formatbuf[8192]; va_start(va_alist, szFormat);
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
{	if(m_bIsCryptStr) return Decrypt().Find(szString, iStart);
	if(::strstr(m_szString, szString)==NULL) return 0;
	return (int)((char*)::strstr(m_szString, szString)-(char*)m_szString)+1; }

char *CString::GetBuffer(int iBufLen)
{	m_iLength=iBufLen; if(m_szString) free(m_szString); m_szString=(char*)malloc(iBufLen+1);
	memset(m_szString, 0, iBufLen+1); return m_szString; }

int CString::GetLength() const { return m_iLength; }

CString CString::Mid(int iFirst, int iCount) const
{	if(m_bIsCryptStr) return Decrypt().Mid(iFirst, iCount);
	CString sTemp; char *szBuf=(char*)malloc(iCount+1);
	memset(szBuf, 0, iCount+1); memcpy(szBuf, &m_szString[iFirst], iCount);
	sTemp.Assign(szBuf); return sTemp; }
CString CString::Mid(int iFirst) const
{	int iCount=GetLength()-iFirst; return Mid(iFirst, iCount); }

CString CString::Token(int iNum, const char *szDelim, bool bUseQuotes)
{	if(m_bIsCryptStr) return Decrypt().Token(iNum, szDelim, bUseQuotes);
	std::vector<char*> vTokens; CString sTemp(m_szString); char *szText=sTemp.Str();
	bool bInQuotes=false; while(*szText)
	{	while(*szText==szDelim[0]) szText++;	// skip leading whitespace
		bInQuotes=(*szText=='\"');				// see if this token is quoted
		if(bInQuotes) szText++;					// skip leading quote
		vTokens.push_back(szText);				// store position of current token
		if(bInQuotes)
		{	// find next quote followed by a space or terminator
			while(*szText&&!(*szText=='\"'&&(szText[1]==' '||szText[1]=='\0'))) szText++;
			if(*szText)
			{	*szText='\0'; if(szText[1]) szText+=2; }
		}
		else // !bInQuotes
		{	// skip to next non-whitespace/delimiter character
			while(*szText&&*szText!=szDelim[0]) szText++;
			if(*szText&&*szText==szDelim[0])
			{	*szText='\0'; szText++; }
		} // if(bInQuotes)
	} // while(*szText)
	if(iNum>=vTokens.size()) return CString("");
	return CString(vTokens.at(iNum)); }
CString CString::Token(int iNum, const char *szDelim) { return Token(iNum, szDelim, false); }

void CString::operator=(const CString &sStr) { Assign(sStr); }
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
	{	if(!m_szTemp) free(m_szTemp); CString sDecrypt=Decrypt();
		m_szTemp=(char*)malloc(sDecrypt.GetLength());
		strcpy(m_szTemp, sDecrypt.CStr()); return (const char *)m_szTemp; }
	return (const char *)m_szString; }
char *CString::Str()
{	if(m_bIsCryptStr)
	{	if(!m_szTemp) free(m_szTemp); CString sDecrypt=Decrypt();
		m_szTemp=(char*)malloc(sDecrypt.GetLength());
		strcpy(m_szTemp, sDecrypt.CStr()); return m_szTemp; }
	return m_szString; }
