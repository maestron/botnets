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

	m_szString=NULL; m_iLength=0;
	Assign(szString); m_bIsCryptStr=false;
	m_szTemp=NULL; }

CString::CString(const CString &pString) {
	if(!g_bInited) {
		for(int i=0;i<128; i++) {
			token_data *pData=&g_tData[i]; pData->szDelim=NULL; pData->szString=NULL;
		}
		g_bInited=true; }

	m_szString=NULL; m_iLength=0;
	Assign(pString); m_szTemp=NULL; }

CString::CString(const int iValue) {
	if(!g_bInited) {
		for(int i=0;i<128; i++) {
			token_data *pData=&g_tData[i]; pData->szDelim=NULL; pData->szString=NULL;
		}
		g_bInited=true; }

	char szTemp[16];
	sprintf(szTemp, "%d", iValue);
	m_szString=NULL; m_iLength=0;
	Assign(szTemp); m_bIsCryptStr=false;
	m_szTemp=NULL; }

CString::~CString() {
	if(m_szString!=NULL) { delete [] m_szString; m_szString=NULL; }
	if(m_szTemp!=NULL) { delete [] m_szTemp; m_szTemp=NULL; }
	m_iLength=0; }

void CString::Assign(const char *szString)
{	if(!szString) return;

	int iLength=::strlen(szString);
	if(m_szString) { delete [] m_szString; m_szString=NULL; }
	m_bIsCryptStr=false;

	m_szString=new char [iLength+2]; if(!m_szString) return; m_iLength=iLength;
	memset(m_szString, 0, m_iLength+2); ::strncpy(m_szString, szString, m_iLength); }
void CString::Assign(const CString &pString) {
	Assign(pString.CStr());
	m_bIsCryptStr=pString.m_bIsCryptStr;
	strncpy(m_szKey, pString.m_szKey, sizeof(m_szKey));
}
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
{	if(!szString || !m_szString) return 0; if(!szString) return 1;
	if(m_bIsCryptStr) return Decrypt().Compare(szString);
	else return ::strcmp(m_szString, szString); }
int CString::Compare(const CString &pString) const { return Compare(pString.CStr()); }
int CString::CompareNoCase(const char *szString) const
{	if(!szString || !m_szString) return 0; if(!szString) return 1;
	if(m_bIsCryptStr) return Decrypt().CompareNoCase(szString);
	else return stricmp(m_szString, szString); }
int CString::CompareNoCase(const CString &pString) const { return Compare(pString.CStr()); }

// Returns the current string in decrypted form
CString CString::Decrypt() const {
	if(!m_bIsCryptStr) return CString("");
	CString sRetVal; sRetVal.Assign("");
	
	strncpy(sRetVal.m_szKey, m_szKey, sizeof(sRetVal.m_szKey));
	sRetVal.m_cSapphire.initialize((unsigned char*)sRetVal.m_szKey, strlen(sRetVal.m_szKey));

	for(int i=0;i<strlen(m_szString);i++) {
		char cDecrypted=sRetVal.m_cSapphire.decrypt(*(m_szString+i));
		char szDecStr[3]={cDecrypted,0,0};
		sRetVal.Append(szDecStr); }

	sRetVal.m_cSapphire.burn();
	sRetVal.m_bIsCryptStr=false;

	return sRetVal; }

// Returns the current string encrypted with szKey
CString CString::Encrypt(const char *szKey) const {
	if(m_bIsCryptStr) return CString("");
	CString sRetVal; sRetVal.Assign("");

	strncpy(sRetVal.m_szKey, szKey, sizeof(sRetVal.m_szKey));
	sRetVal.m_cSapphire.initialize((unsigned char*)sRetVal.m_szKey, strlen(sRetVal.m_szKey));

	int i;
	for(i=0;i<strlen(m_szString);i++) {
		char cEncrypted=sRetVal.m_cSapphire.encrypt(*(m_szString+i));
		char szEncStr[3]={cEncrypted,0,0};
		sRetVal.Append(szEncStr); }

	sRetVal.m_cSapphire.burn();
	sRetVal.m_bIsCryptStr=true;

	CString sCheckStr("");
	sRetVal.m_cSapphire.initialize((unsigned char*)sRetVal.m_szKey, strlen(sRetVal.m_szKey));

	for(i=0;i<sRetVal.GetLength();i++) {
		char cDecrypted=sRetVal.m_cSapphire.decrypt(sRetVal.operator [](i));
		char szDecStr[3]={cDecrypted,0,0};
		sCheckStr.Append(szDecStr); }

	sRetVal.m_cSapphire.burn();

//	if(sRetVal.Compare(sCheckStr)) {
//		init_random();
//	}

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
{	if(!m_szString) return 0;
	if(m_bIsCryptStr) return Decrypt().GetLength();
	return strlen(m_szString); }

int CString::GetLength()
{	if(!m_szString) return 0;
	if(m_bIsCryptStr) return Decrypt().GetLength();
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
{	static int iCacheIndex=0; int i; char *szStrCopy;

	if(!szDelim) return CString("");

	try {
		if(m_bIsCryptStr) return Decrypt().Token(iNum, szDelim, bUseQuotes);
	
		szStrCopy=new char[strlen(m_szString)+2];
		memset(szStrCopy, 0, strlen(m_szString)+2);
		strncpy(szStrCopy, m_szString, strlen(m_szString)+1);
	} catch(...) {
		return CString("");
	}

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
#ifdef _WIN32
			} catch(out_of_range) {
#else
			} catch(...) {
#endif // _WIN32
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

void CString::operator=(const CString &sStr) { Assign(sStr); }
void CString::operator=(const char *szStr) { Assign(szStr); }
char &CString::operator[](int iPos)
{	if(m_bIsCryptStr) return Decrypt().operator[](iPos);
	return m_szString[iPos]; }
const char &CString::operator[](int iPos) const
{	if(m_bIsCryptStr) return Decrypt().operator[](iPos);
	return m_szString[iPos]; }

CString::operator const char *() const {
	return CStr(); }
CString::operator char *() {
	return Str(); }

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

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//// Sapphire implementation starts here
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

/*
	from sapphire.cpp -- the Saphire II stream cipher class.
	Dedicated to the Public Domain the author and inventor:
	(Michael Paul Johnson).  This code comes with no warranty.
	Use it at your own risk.
*/


unsigned char CSapphire::keyrand(int limit, unsigned char *user_key, unsigned char keysize,
								unsigned char *rsum, unsigned *keypos) {
	unsigned u,				// Value from 0 to limit to return.
		retry_limiter=0,	// No infinite loops allowed.
        mask=1;				// Select just enough bits.

	while(mask<limit)		// the desired range.
		mask=(mask<<1)+1;
	
	do {
		*rsum=cards[*rsum]+user_key[(*keypos)++];
		if(*keypos>=keysize) {
			*keypos=0;		// Recycle the user key.
			*rsum+=keysize;	// key "aaaa" != key "aaaaaaaa"
		}
		u=mask&*rsum;
		if(++retry_limiter>11)
			u%=limit;		// Prevent very rare long loops.
	} while(u>limit);
	
	return u; }

void CSapphire::initialize(unsigned char *key, unsigned char keysize) {
	// Key size may be up to 256 bytes.
	// Pass phrases may be used directly, with longer length
	// compensating for the low entropy expected in such keys.
	// Alternatively, shorter keys hashed from a pass phrase or
	// generated randomly may be used. For random keys, lengths
	// of from 4 to 16 bytes are recommended, depending on how
	// secure you want this to be.

	int i; unsigned char toswap, swaptemp, rsum; unsigned keypos;

	// If we have been given no key, assume the default hash setup.
	if(keysize<1) { hash_init(); return; }

	// Start with cards all in order, one of each.
	for(i=0;i<256;i++) cards[i]=i;

	// Swap the card at each position with some other card.
	toswap=0; keypos=0;	rsum=0; // Start with first byte of user key.
	for(i=255;i>=0;i--) {
		toswap=keyrand(i, key, keysize, &rsum, &keypos);
		swaptemp=cards[i]; cards[i]=cards[toswap]; cards[toswap]=swaptemp; }

	// Initialize the indices and data dependencies.
	// Indices are set to different values instead of all 0
	// to reduce what is known about the state of the cards
	// when the first byte is emitted.
	rotor=cards[1]; ratchet=cards[3]; avalanche=cards[5];
	last_plain=cards[7]; last_cipher=cards[rsum];

	toswap=swaptemp=rsum=0; keypos=0; }

void CSapphire::hash_init(void) {
	// This function is used to initialize non-keyed hash computation.
	// Initialize the indices and data dependencies.
	rotor=1; ratchet=3; avalanche=5; last_plain=7; last_cipher=11;

	// Start with cards all in inverse order.
	for(int i=0,j=255;i<256;i++,j--) cards[i]=(unsigned char)j; }

CSapphire::CSapphire(unsigned char *key, unsigned char keysize) {
	if(key&&keysize) initialize(key, keysize); }

void CSapphire::burn(void) {
	// Destroy the key and state information in RAM.
	memset(cards, 0, 256); rotor=ratchet=avalanche=last_plain=last_cipher=0; }

CSapphire::~CSapphire() { burn(); }

unsigned char CSapphire::encrypt(unsigned char b) {
	// Picture a single enigma rotor with 256 positions, rewired
	// on the fly by card-shuffling.
	
	// This cipher is a variant of one invented and written
	// by Michael Paul Johnson in November, 1993.

	unsigned char swaptemp;

	// Shuffle the deck a little more.
	ratchet+=cards[rotor++]; swaptemp=cards[last_cipher]; cards[last_cipher]=cards[ratchet];
	cards[ratchet]=cards[last_plain]; cards[last_plain]=cards[rotor]; cards[rotor]=swaptemp;
	avalanche+=cards[swaptemp];

	// Output one byte from the state in such a way as to make it
	// very hard to figure out which one you are looking at.
	last_cipher=b^cards[(cards[ratchet]+cards[rotor])&0xFF]^
		cards[cards[(cards[last_plain]+cards[last_cipher]+cards[avalanche])&0xFF]];
	last_plain=b; return last_cipher; }

unsigned char CSapphire::decrypt(unsigned char b) {
	unsigned char swaptemp;

	// Shuffle the deck a little more.
	ratchet+=cards[rotor++]; swaptemp=cards[last_cipher]; cards[last_cipher]=cards[ratchet];
	cards[ratchet]=cards[last_plain]; cards[last_plain]=cards[rotor]; cards[rotor]=swaptemp;
	avalanche+=cards[swaptemp];

	// Output one byte from the state in such a way as to make it
	// very hard to figure out which one you are looking at.
	last_plain=b^cards[(cards[ratchet]+cards[rotor])&0xFF]^
		cards[cards[(cards[last_plain]+cards[last_cipher]+cards[avalanche])&0xFF]];
	last_cipher=b; return last_plain; }

void CSapphire::hash_final(unsigned char *hash, unsigned char hashlength) {
	int i; for(i=255;i>=0;i--) encrypt((unsigned char)i);
	for(i=0;i<hashlength;i++) hash[i]=encrypt(0); }
