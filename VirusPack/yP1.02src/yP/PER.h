/* PER.h --

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

#define  InitRandom				ASHKBIZ20078891
#define  _ror					ASHKBIZ20078892
#define  _rol					ASHKBIZ20078893
#define  random					ASHKBIZ20078894
#define  EncryptBuff			ASHKBIZ20078895
#define  MakePER				ASHKBIZ20078896

extern bool ProceedBar;

void InitRandom();
void _ror(DWORD *Value,UCHAR Shift);
void _rol(DWORD *Value,UCHAR Shift);
DWORD random(DWORD dwRange);
void EncryptBuff(char* Base,DWORD dwRV,DWORD Size);
void MakePER(char* pDecryptBuff,DWORD dwSize);
