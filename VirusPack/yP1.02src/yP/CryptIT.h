/* CryptIT.h --

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

#define  ReadStringFrom			ASHKBIZ20078691
#define  EnDeCryptString		ASHKBIZ20078692
#define  ProcessOrgIT			ASHKBIZ20078693
#define  AssembleIT				ASHKBIZ20078694
#define  ITMaker				ASHKBIZ20078695
#define  RetrieveIT				ASHKBIZ20078696
#define  GetITSize				ASHKBIZ20078697
#define  RebuiltIT				ASHKBIZ20078698

char* ReadStringFrom(char* Base,DWORD VA);
DWORD EnDeCryptString(char* Base,DWORD dwRO);
DWORD ProcessOrgIT(char* pFileImage,DWORD pITBaseRO);
void AssembleIT(char* Base,DWORD dwNewSectionRO,DWORD dwNewSectionVA);

bool CheckifForwarderChain(char* pFileImage,DWORD pITBaseRO);

void ITMaker(char* pFileImage,DWORD pITBaseRO);
DWORD RetrieveIT(char* pFileImage,DWORD pITBaseRO);
DWORD GetITSize(char* pFileImage,DWORD pITBaseRO);
void RebuiltIT(char* pFileImage,DWORD pITBaseRO,char *pImport);