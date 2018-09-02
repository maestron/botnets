/* CryptMain.h --

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
#include "CryptVar.h"

#pragma once

#define  CryptFile				ASHKBIZ20078293
#define  ShowComment			ASHKBIZ20078294
#define  SaveToRegistry			ASHKBIZ20078295
#define  LoadFromRegistry		ASHKBIZ20078296
#define  ProcessTlsTable		ASHKBIZ20078297
#define  ShowPreComment			ASHKBIZ20078298
#define  ShowPostComment		ASHKBIZ20078299
#define  OpenFileName			ASHKBIZ20078391
#define  UpdateHeaders			ASHKBIZ20078392
#define  UpdateHeadersSections	ASHKBIZ20078393
#define  AddSection				ASHKBIZ20078393
#define  RemoveSection			ASHKBIZ20078394
#define  RemoveSectionNames		ASHKBIZ20078395
#define  CryptPE				ASHKBIZ20078396
#define  CompressPE				ASHKBIZ20078397
#define  CryptResource			ASHKBIZ20078593
#define  CompressResource		ASHKBIZ20078594
#define  Free					ASHKBIZ20078398
#define  CheckifProtect			ASHKBIZ20078491
#define  CheckifSectionName		ASHKBIZ20078492
#define  CheckifPEvalid			ASHKBIZ20078493
#define  CheckCOMRuntime		ASHKBIZ20078494
#define  CheckifDLL				ASHKBIZ20078495
#define  CheckifSYS				ASHKBIZ20078496
#define  OptimizeDOSHeader		ASHKBIZ20078497
#define  EliminateDOSHeader		ASHKBIZ20078498
#define  EliminateReloc			ASHKBIZ20078499
#define  EliminateDebug			ASHKBIZ20078591
#define  GetSectionNume			ASHKBIZ20078592

extern char	DEPACKER_SECTION_NAME[9];
extern char szComment[1024];

void ShowComment(DWORD dwProtFlags,DWORD dwAdvnFlags);

void CryptFile(char* szFnameOpen,char* szFnameSave,
			   DWORD dwProtFlags,DWORD dwAdvnFlags,
			   DWORD dwLevel,char* CrypterSectionName);

bool SaveToRegistry(DWORD dwProtectFlags,
					DWORD dwAdvancedFlags,
					DWORD dwCompressLevel,
					char* CrypterSectionName,
					DWORD dwLangID);
bool LoadFromRegistry(DWORD *dwProtectFlags,
					  DWORD *dwAdvancedFlags,
					  DWORD *dwCompressLevel,
					  char* CrypterSectionName,
					  DWORD *dwLangID);

