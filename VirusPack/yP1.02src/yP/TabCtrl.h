/* TabCtrl.h --
  
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

#include "resource.h"

extern bool CheckSI;
extern bool DestroyImport;
extern bool CheckCRC;
extern bool AntiDump;
extern bool ApiRedirect;
extern bool CompressRsrc;
extern bool EraseHeader;

extern bool RemoveReloc;
extern bool RemoveDebug;
extern bool RemoveDOS;
extern bool OptmizeDOS;

extern bool MakeBackUp;
extern bool AutoRun;
extern bool ExitWhenDone;

extern char cFnameOpen[256];
extern char cFnameSave[256];

extern DWORD dwProtectFlags;
extern DWORD dwAdvancedFlags;
extern DWORD dwCompressLevel;
extern CHAR lpszSectionName[16]; 

HWND WINAPI OnTabbedDialogInit(HWND hwndDlg);
HWND WINAPI OnSelChanged(HWND hwndDlg) ;
