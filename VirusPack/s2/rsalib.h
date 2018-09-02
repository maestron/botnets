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

#ifndef __RSALIB_H__
#define __RSALIB_H__

namespace rsa
{
#include "rsa/global.h"
#include "rsa/rsaref.h"
}

class CRSALib
{
public:
	CRSALib();
	virtual ~CRSALib();

	bool VerifyFile(const char *szFile, const char *szSigFile);
private:
	void InitRandomStruct(rsa::R_RANDOM_STRUCT *pRandomStruct);
	int ReadInit(FILE **pfp, const char *szFile);
	int ReadUpdate(FILE *fp, unsigned char *szPartOut, unsigned int *iPartOutLen, unsigned int iMaxPartOutLen);
	void ReadFinal(FILE *fp);
	int ReadBlock(const char *szFile, unsigned char *szBlock, unsigned int *iBlockLen, unsigned int iMaxBlockLen);

	void WritePublicKey(rsa::R_RSA_PUBLIC_KEY *prsaKey, const char *szFile);
	void WritePrivateKey(rsa::R_RSA_PRIVATE_KEY *prsaKey, const char *szFile);

	rsa::R_RANDOM_STRUCT m_rsaRandomStruct;
	rsa::R_RSA_PUBLIC_KEY m_rsaPublicKey;
};

#endif // __RSALIB_H__
