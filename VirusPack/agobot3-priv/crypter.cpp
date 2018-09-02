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
#include "crypter.h"

CCryptStr::CCryptStr(int iKey) { m_iKey=iKey; m_szDecStr=NULL; }
CCryptStr::~CCryptStr() { Release(); }
void CCryptStr::Decrypt()
{	if(!m_iKey) return; if(m_szDecStr) free(m_szDecStr); m_szDecStr=(char*)malloc(GetLength());
	for(char i=0; i<GetLength(); i++) m_szDecStr[i]=m_szString[i]^(m_iKey+(i*(m_iKey%10)+1)); }
char *CCryptStr::Str() { Decrypt(); return m_szDecStr; }
void CCryptStr::Release() { if(m_szDecStr) { free(m_szDecStr); m_szDecStr=NULL; } }
