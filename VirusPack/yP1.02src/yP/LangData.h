/* CryptErr.h --

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

#define _LANG_ENGLISH		0
#define _LANG_GERMAN		1
#define _LANG_FRENCH		2
#define _LANG_ITALIAN		3
#define _LANG_SPANISH		4

extern DWORD dwLanguageID;

struct sViewLang
{
	TCHAR *szMenuFile;
	TCHAR *szMenuFileOpen;
	TCHAR *szMenuFileSaveAs;
	TCHAR *szMenuFileProtect;
	TCHAR *szMenuFileExit;
	TCHAR *szMenuOptions;
	TCHAR *szMenuOptionsProtection;
	TCHAR *szMenuView;
	TCHAR *szMenuViewInterfaceLanguage;
	TCHAR *szMenuHelp;
	TCHAR *szMenuHelpHelpContents;
	TCHAR *szMenuHelpAbout;
	TCHAR *szProtectTab;
	TCHAR *szProtectTabFileToProtect;
	TCHAR *szProtectTabOutputToFileName;
	TCHAR *szProtectTabProtect;
	TCHAR *szProtectTabTest;
	TCHAR *szOptionsTab;
	TCHAR *szOptionsTabProtection;
	TCHAR *szOptionsTabAntiSoftICEProtection;
	TCHAR *szOptionsTabChecksumProtection;
	TCHAR *szOptionsTabAPIRedirection;
	TCHAR *szOptionsTabAntiDumpProtection;
	TCHAR *szOptionsTabClearImportInformation;
	TCHAR *szOptionsTabClearPEheader;
	TCHAR *szOptionsTabCompressOption;
	TCHAR *szOptionsTabAdvanced;
	TCHAR *szOptionsTabRemoveRelocSection;
	TCHAR *szOptionsTabRemoveDebugInformation;
	TCHAR *szOptionsTabEliminateMSDOSheader;
	TCHAR *szOptionsTabOptimizeMSDOSheader;
	TCHAR *szOptionsTabOther;
	TCHAR *szOptionsTabCreateBackupCopy;
	TCHAR *szOptionsTabAutoRunAfterLoading;
	TCHAR *szOptionsTabExitWhenDone;
	TCHAR *szOptionsTabSectionName;	
};
//----- EQUs -----
#define ViewLangNum		6
//----- CONST ----
// all opcodes are in reverse order
extern sViewLang ViewLangPERTable[ViewLangNum];