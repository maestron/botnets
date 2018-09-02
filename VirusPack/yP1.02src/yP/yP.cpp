/* yP.cpp : Defines the entry point for the application.

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
//#define  WIN32_LEAN_AND_MEAN
#include "stdafx.h"
#include "yP.h"
#include "PER.h"
#include "CryptMain.h"
#include "CryptFunc.h"
#include "TabCtrl.h"
#include "LangData.h"
#include <commdlg.h>
#include <commctrl.h>
#include <shellapi.h>
#include <winuser.h>
#include "TrackCtrl.h"
#include ".\Thanks\Thanks.h"

#pragma comment(linker,"/BASE:0x400000 /FILEALIGN:0x200 /MERGE:.rdata=.text /MERGE:.data=.text /SECTION:.text,EWR /IGNORE:4078")
#pragma pack(1)

// Global Variables:

HINSTANCE hInst;	// current instance


char g_achTemp[256];// temporary buffer for strings 

HDROP	hDrop;
HICON	hIcon;
HBITMAP	hBitmap;
HWND	hButton;

HWND	hwndMain;      // main application window 
HMENU	hMenu;
HACCEL	hAccel;

HWND	hwndTab;	// tab control 
HWND	hwndDisplay;// handle to static control in 
					//   tab control's display area 
// Global variables 



// Forward declarations of functions included in this code module:
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT DlgProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam);
void SetLanguage(DWORD dwLangID);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	MSG msg;
	char* szFileComment;
	hInst=GetModuleHandle(0);
	cFnameOpen[0]=0x00;
	if(strlen(lpCmdLine)!=0)
	{
		if((lpCmdLine[1]='O')||(lpCmdLine[1]='o'))
		{
			szFileComment=lpCmdLine+3;
			CopyMemory(cFnameOpen,szFileComment,(DWORD)strlen(szFileComment)+1);
		}
	}
	DialogBoxParam(hInst,MAKEINTRESOURCE(IDD_MAINDLG),0,(DLGPROC)DlgProc,0);
	//DoPropertySheet(hInst);
	ExitProcess(0);
	return (int) msg.wParam;
}

//  FUNCTION: DlgProc(HWND, unsigned, WORD, LONG)
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
LRESULT DlgProc(HWND hDlg,UINT uiMsg,WPARAM wParam,LPARAM lParam)
{
	UINT wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	switch (uiMsg) 
	{
	case WM_INITDIALOG:
#if(ANTIDEBUGACTIVE	== 1)
		AntiDebug();
#endif
		CopyMemory(lpszSectionName,DEPACKER_SECTION_NAME,(DWORD)strlen(DEPACKER_SECTION_NAME)+1);
		LoadFromRegistry(&dwProtectFlags,
						 &dwAdvancedFlags,
					     &dwCompressLevel,
						 lpszSectionName,
						 &dwLanguageID);

		hwndMain=hDlg;

		hIcon=LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON));
		SendMessage(hDlg,WM_SETICON,TRUE,(WPARAM)hIcon);
		hwndTab=OnTabbedDialogInit(hDlg);
	
		hwndDisplay=OnSelChanged(hDlg);
		hMenu=GetMenu(hDlg);

		hAccel=LoadAccelerators(hInst,MAKEINTRESOURCE(IDC_YC));

		if((dwProtectFlags&CHECK_SI_FLAG)==CHECK_SI_FLAG) CheckSI=TRUE;
		else CheckSI=FALSE;
			
		if((dwProtectFlags&DESTROY_IMPORT_FLAG)==DESTROY_IMPORT_FLAG) DestroyImport=TRUE;
		else DestroyImport=FALSE;
			
		if((dwProtectFlags&CHECK_HEADER_CRC)==CHECK_HEADER_CRC) CheckCRC=TRUE;
		else CheckCRC=FALSE;
			
		if((dwProtectFlags&ANTI_DUMP_FLAG)==ANTI_DUMP_FLAG) AntiDump=TRUE;
		else AntiDump=FALSE;

		if((dwProtectFlags&API_REDIRECT_FLAG)==API_REDIRECT_FLAG) ApiRedirect=TRUE;
		else ApiRedirect=FALSE;

		if((dwProtectFlags&ERASE_HEADER_FLAG)==ERASE_HEADER_FLAG) EraseHeader=TRUE;
		else EraseHeader=FALSE;

//		if((dwProtectFlags&COMPRESS_RSRC_FLAG)==COMPRESS_RSRC_FLAG) CompressRsrc=TRUE;
//		else CompressRsrc=FALSE;


		if((dwAdvancedFlags&REMOVE_RELOC)==REMOVE_RELOC) RemoveReloc=TRUE;
		else RemoveReloc=FALSE;

		if((dwAdvancedFlags&REMOVE_DEBUG)==REMOVE_DEBUG) RemoveDebug=TRUE;
		else RemoveDebug=FALSE;

		if((dwAdvancedFlags&REMOVE_DOS_HEADER)==REMOVE_DOS_HEADER) RemoveDOS=TRUE;
		else RemoveDOS=FALSE;

		if((dwAdvancedFlags&OPTIMIZED_DOS_HEADER)==OPTIMIZED_DOS_HEADER) OptmizeDOS=TRUE;
		else OptmizeDOS=FALSE;

		if((dwAdvancedFlags&CREATE_BACKUP)==CREATE_BACKUP) MakeBackUp=TRUE;
		else MakeBackUp=FALSE;

		if((dwAdvancedFlags&AUTO_RUN)==AUTO_RUN) AutoRun=TRUE;
		else AutoRun=FALSE;

		if((dwAdvancedFlags&EXIT_WHEN_DONE)==EXIT_WHEN_DONE) ExitWhenDone=TRUE;
		else ExitWhenDone=FALSE;

		/*hBitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_OPEN));
		SendDlgItemMessage(hDlg,ID_FILE_OPEN,BM_SETIMAGE,
						   IMAGE_BITMAP,(WPARAM)hBitmap);
		hBitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_SAVE));
		SendDlgItemMessage(hDlg,ID_FILE_SAVEAS,BM_SETIMAGE,
						   IMAGE_BITMAP,(WPARAM)hBitmap);

		hBitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_PROTECT));
		SendDlgItemMessage(hDlg,ID_FILE_PROTECT,BM_SETIMAGE,
						   IMAGE_BITMAP,(WPARAM)hBitmap);

		hBitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_HELP));
		SendDlgItemMessage(hDlg,ID_HELP_HELPCONTENTS,BM_SETIMAGE,
						   IMAGE_BITMAP,(WPARAM)hBitmap);*/
		SetLanguage(dwLanguageID);

		break;   

	/*case WM_DROPFILES:
		hDrop=HDROP(wParam);
		DragQueryFile(hDrop,0,cFnameOpen,sizeof(cFnameOpen));
		DragFinish(hDrop);
		SetDlgItemText(hwndDisplay,IDC_FILE_OPEN,cFnameOpen);
		break;*/
 	   
	case WM_NOTIFY: 
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam);
		wmEvent=TCN_SELCHANGE;
		switch (wmEvent) 
		{ 
		case 0: 
			// menu command processing 
		case TCN_SELCHANGE: 
			int iPage = TabCtrl_GetCurSel(hwndTab); 
			LoadString(hInst,IDC_TABS + iPage, 
					g_achTemp,
					sizeof(g_achTemp)/sizeof(g_achTemp[0])); 
			hwndDisplay=OnSelChanged(hDlg);
			SendMessage(hwndDisplay, WM_SETTEXT, 0,
					(LPARAM) g_achTemp);
			switch(iPage)
			{
			case 0:
				SendDlgItemMessage(hwndDisplay,IDC_COMMENT,
					   WM_SETTEXT, 
					   0, (LPARAM)szComment);
				break;
			case 1:
				CreateTrackbar(hwndDisplay);
				break;
			}
			break; 
		} 
		break; 

	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_FILE_OPEN:
			TabCtrl_SetCurSel(hwndTab,0);
			SendMessage(hwndMain,WM_NOTIFY,0x03f0,0);
			SendMessage(hwndDisplay,WM_COMMAND,ID_FILE_OPEN,0);
			break;

		case ID_FILE_SAVE:
			TabCtrl_SetCurSel(hwndTab,0);
			SendMessage(hwndMain,WM_NOTIFY,0x03f0,0);
			SendMessage(hwndDisplay,WM_COMMAND,ID_FILE_SAVE,0);
			break;

		case ID_FILE_PROTECT:
			SendMessage(hwndDisplay,WM_COMMAND,ID_FILE_PROTECT,0);
			break;

		case ID_OPTIONS_PROTECTION:
			TabCtrl_SetCurSel(hwndTab,1);
			SendMessage(hwndMain,WM_NOTIFY,0x03f0,0);
			break;

		case IDCLOSE:
			SendMessage(hDlg,WM_CLOSE,NULL,NULL);
			break;
              	                  
		case IDOK:
			EndDialog(hDlg,0);
			break;

		case ID_HELP_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hDlg, (DLGPROC)About);
			break;

		case ID_LNG_ENGLISH:
			SetLanguage(_LANG_ENGLISH);
			break;

		case ID_LNG_GERMAN:
			SetLanguage(_LANG_GERMAN);
			break;
			
		case ID_LNG_FRENCH:
			SetLanguage(_LANG_FRENCH);
			break;

		case ID_LNG_ITALIAN:
			SetLanguage(_LANG_ITALIAN);
			break;

		case ID_LNG_SPANISH:
			SetLanguage(_LANG_SPANISH);
			break;
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hDlg, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hDlg, &ps);
		break;

	case WM_DESTROY:
		SaveToRegistry(dwProtectFlags,
				   dwAdvancedFlags,
				   dwCompressLevel,
				   lpszSectionName,
				   dwLanguageID);
		PostQuitMessage(0);
		break;

	case WM_CLOSE:
		EndDialog(hDlg,0);
		break;
	}
	return 0;
}

LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UINT wmId, wmEvent;
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Parse the menu selections:
		switch (wmId)
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
			break;
		case IDC_WEB:
			WinExec("Explorer http://yodap.cjb.net/", SW_SHOWMAXIMIZED);
			break;
		case IDC_THANKS:
			//EndDialog(hDlg,nResult);
			hButton=GetDlgItem(hDlg,IDC_THANKS); 
			EnableWindow(hButton,FALSE);
			InitWindow(hInst,1);
			hButton=GetDlgItem(hDlg,IDC_THANKS); 
			EnableWindow(hButton,TRUE);
			//DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hDlg, (DLGPROC)About);
			break;
		}
		break;
	}
	return FALSE;
}


void SetLanguage(DWORD dwLangID)
{
	TCHAR  szTmp[64];
	sViewLang ViewLanguage;
	switch(dwLangID)
	{
	case _LANG_ENGLISH:
		CheckMenuRadioItem(hMenu,ID_LNG_ENGLISH,ID_LNG_SPANISH,ID_LNG_ENGLISH,MF_BYCOMMAND);
		break;

	case _LANG_GERMAN:
		CheckMenuRadioItem(hMenu,ID_LNG_ENGLISH,ID_LNG_SPANISH,ID_LNG_GERMAN,MF_BYCOMMAND);
		break;
			
	case _LANG_FRENCH:
		CheckMenuRadioItem(hMenu,ID_LNG_ENGLISH,ID_LNG_SPANISH,ID_LNG_FRENCH,MF_BYCOMMAND);
		break;

	case _LANG_ITALIAN:
		CheckMenuRadioItem(hMenu,ID_LNG_ENGLISH,ID_LNG_SPANISH,ID_LNG_ITALIAN,MF_BYCOMMAND);
		break;

	case _LANG_SPANISH:
		CheckMenuRadioItem(hMenu,ID_LNG_ENGLISH,ID_LNG_SPANISH,ID_LNG_SPANISH,MF_BYCOMMAND);
		break;

	default:
		CheckMenuRadioItem(hMenu,ID_LNG_ENGLISH,ID_LNG_SPANISH,ID_LNG_ENGLISH,MF_BYCOMMAND);
		dwLangID=0;
	}
	//--------------------------------------------------------
	dwLanguageID=dwLangID;
	ViewLanguage=ViewLangPERTable[dwLangID];
	
	CopyMemory(szTmp,ViewLanguage.szMenuFile,64);
	ModifyMenu(hMenu,0,MF_BYPOSITION|MF_STRING,ID_FILE_OPEN,(LPTSTR)&szTmp);

	CopyMemory(szTmp,ViewLanguage.szMenuFileOpen,64);
	ModifyMenu(hMenu,ID_FILE_OPEN,MF_BYCOMMAND|MF_STRING,ID_FILE_OPEN,(LPTSTR)&szTmp);

	CopyMemory(szTmp,ViewLanguage.szMenuFileSaveAs,64);
	ModifyMenu(hMenu,ID_FILE_SAVE,MF_BYCOMMAND|MF_STRING,ID_FILE_SAVE,(LPTSTR)&szTmp);
	EnableMenuItem(hMenu,ID_FILE_SAVE,MF_GRAYED);

	CopyMemory(szTmp,ViewLanguage.szMenuFileProtect,64);
	ModifyMenu(hMenu,ID_FILE_PROTECT,MF_BYCOMMAND|MF_STRING,ID_FILE_PROTECT,(LPTSTR)&szTmp);
	EnableMenuItem(hMenu,ID_FILE_PROTECT,MF_GRAYED);

	CopyMemory(szTmp,ViewLanguage.szMenuFileExit,64);
	ModifyMenu(hMenu,IDOK,MF_BYCOMMAND|MF_STRING,IDOK,(LPTSTR)&szTmp);

	//---------------------------------------------------------
	CopyMemory(szTmp,ViewLanguage.szMenuOptions,64);
	ModifyMenu(hMenu,1,MF_BYPOSITION|MF_STRING,ID_FILE_OPEN,(LPTSTR)&szTmp);

	CopyMemory(szTmp,ViewLanguage.szMenuOptionsProtection,64);
	ModifyMenu(hMenu,ID_OPTIONS_PROTECTION,MF_BYCOMMAND|MF_STRING,ID_OPTIONS_PROTECTION,(LPTSTR)&szTmp);

	//---------------------------------------------------------
	CopyMemory(szTmp,ViewLanguage.szMenuView,64);
	ModifyMenu(hMenu,2,MF_BYPOSITION|MF_STRING,ID_FILE_OPEN,(LPTSTR)&szTmp);

	HMENU hSubMenu=GetSubMenu(hMenu,2);
	CopyMemory(szTmp,ViewLanguage.szMenuViewInterfaceLanguage,64);
	ModifyMenu(hSubMenu,0,MF_BYPOSITION|MF_STRING,ID_FILE_OPEN,(LPTSTR)&szTmp);

	//---------------------------------------------------------
	CopyMemory(szTmp,ViewLanguage.szMenuHelp,64);
	ModifyMenu(hMenu,3,MF_BYPOSITION|MF_STRING,ID_FILE_OPEN,(LPTSTR)&szTmp);

	CopyMemory(szTmp,ViewLanguage.szMenuHelpHelpContents,64);
	ModifyMenu(hMenu,ID_HELP_HELPCONTENTS,MF_BYCOMMAND|MF_STRING,ID_HELP_HELPCONTENTS,(LPTSTR)&szTmp);
	EnableMenuItem(hMenu,ID_HELP_HELPCONTENTS,MF_GRAYED);

	CopyMemory(szTmp,ViewLanguage.szMenuHelpAbout,64);
	ModifyMenu(hMenu,ID_HELP_ABOUT,MF_BYCOMMAND|MF_STRING,ID_HELP_ABOUT,(LPTSTR)&szTmp);

	DrawMenuBar(hwndMain);

	TCITEM item;
	item.mask= TCIF_TEXT;

	item.pszText=ViewLanguage.szProtectTab;
	item.cchTextMax=strlen(ViewLanguage.szProtectTab)+1;
	TabCtrl_SetItem(hwndTab, 0, &item);

	item.pszText=ViewLanguage.szOptionsTab;
	item.cchTextMax=strlen(ViewLanguage.szOptionsTab)+1;
	TabCtrl_SetItem(hwndTab, 1, &item);

	SendMessage(hwndDisplay,WM_INITDIALOG,NULL,NULL);
}

//

