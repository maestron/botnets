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

#ifndef __CSTRING_H__
#define __CSTRING_H__

class CString
{
public:
	CString();
	CString(const char *szString);
	CString(const CString &pString);
	CString(const int iValue);
	virtual ~CString();

	void Assign(const char *szString);
	void Assign(const CString &pString);
	void Assign(const int iValue);

	void Append(const char *szString);
	void Append(const CString &pString);
	void Append(const int iValue);

	int Compare(const char *szString) const;
	int Compare(const CString &pString) const;

	int CompareNoCase(const char *szString) const;
	int CompareNoCase(const CString &pString) const;

	CString Decrypt() const;

	void Empty();

	int Find(const char cChar) const;
	int Find(const char cChar, int iStart) const;
	int Find(const CString &pString) const;
	int Find(const CString &pString, int iStart) const;
	int Find(const char *szString) const;
	int Find(const char *szString, int iStart) const;

	void Format(const char *szFormat, ...);

	char *GetBuffer(int iBufLen);

	int GetLength() const;
	int GetLength();
	
	CString Mid(int iFirst, int iCount) const;
	CString Mid(int iFirst) const;

	CString Token(int iNum, const char *szDelim, bool bUseQuotes);
	CString Token(int iNum, const char *szDelim);

	void operator=(const CString &sStr);
	void operator=(const char *szStr);
	char &operator[](int iPos);
	const char &operator[](int iPos) const;
	operator const char *() const { return m_szString; }
	operator char *() { return m_szString; }

	const char *CStr() const;
	const char *CStr();
	char *Str();

	bool	 m_bIsCryptStr;
	int		 m_iCryptKey;
	char	*m_szString;
	char	*m_szTemp;
	int		 m_iLength;
};

typedef struct token_data_s {
	unsigned char		 szMD5[16];
	char				*szString;
	char				*szDelim;
	std::vector<char*>	 vTokens;
} token_data;

#endif // __CSTRING_H__
