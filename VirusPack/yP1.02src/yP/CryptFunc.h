/* CryptFunc.h --

   This file is part of the "yoda's Protector".

   Copyright (C) 2004-2005 Ashkbiz Danehkar
   Copyright (C) 2000-2001 yoda/FReAK2FReAK
   All Rights Reserved.

   yoda's Protector library are free software; you can redistribute them
   and/or modify them under the terms of the GNU General Public License as
   published by the Free Software Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYRIGHT.TXT.
   If not, write to the Free Software Foundation, Inc.,
   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

   Ashkbiz Danehkar
   <ashkbiz@yahoo.com>
*/
#pragma once

#define ANTIDEBUGACTIVE			0

#define  FillWithShit			ASHKBIZ20078594
#define  GetEncryptRO			ASHKBIZ20078595
#define  GetOepJumpCodeRO		ASHKBIZ20078596
#define  OepJumpEncrypt			ASHKBIZ20078597
#define  CrypterPackerwithCall	ASHKBIZ20078598

#if(ANTIDEBUGACTIVE	== 1)
void AntiDebug();
#endif

void FillWithShit(char* Base,DWORD dwSize);
void GetEncryptRO(char* pFuncBody);
void GetOepJumpCodeRO(char* pFuncBody);
void OepJumpEncrypt(char* Base);
void CrypterPackerwithCall(char* pFuncBody,DWORD dwSize);

extern	DWORD	dwRO_PackEncrypt;
extern	DWORD   dwRO_VariableEncrypt;
extern	DWORD   dwRO_SectionInfoEncrypt;
extern	DWORD   dwRO_SectionEncrypt;
extern	DWORD   dwRO_CODESectionEncrypt;
extern  DWORD   dwRO_DATASectionEncrypt;
extern	DWORD   dwRO_RSRCSectionEncrypt;
extern	DWORD   dwRO_IDATASectionEncrypt;
extern	DWORD   dwRO_EDATASectionEncrypt;
extern	DWORD   dwRO_OEPEncrypt;
extern	DWORD	dwRO_OEP_JUMP_CODE_START;
extern	DWORD	dwRO_OEP_JUMP_CODE_END;
extern	DWORD	OEP_JUMP_CODE_SIZE; 
