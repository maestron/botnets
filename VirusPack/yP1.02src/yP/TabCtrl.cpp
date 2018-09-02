/* TabCtrl.cpp : Defines the entry point for the application.

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
#include "stdafx.h"
#include "yP.h"
#include "TabCtrl.h"
#include "TrackCtrl.h"
#include "CryptMain.h"
#include "LangData.h"
#include <commdlg.h>
#include <commctrl.h>
#include <shellapi.h>
#include <winuser.h>


char cFname[256];
char cFnameOpen[256];
char cFnameSave[256];
char cExecute[256];
char *szExtension;

HIMAGELIST hImageList;
BOOL fStatus;
OPENFILENAME openfn;
OPENFILENAME savefn;
DWORD nFilterIndex=1;
char szCurDir[]=".";
char szFilter[]=TEXT("Executable files (*.exe)\0*.exe\0Dynamic Link Libraries (*.dll)\0*.dll\0OLE-ActiveX Controls (*.ocx)\0*.ocx\0Screen Savers (*.scr)\0*.scr\0All files (*.*)\0*.*\0\0");

DWORD dwProtectFlags	= 0x3D;
DWORD dwAdvancedFlags	= 0x13;
DWORD dwCompressLevel	=	10;
CHAR lpszSectionName[16]; 


int iSectionName=2;

bool CheckSI		= TRUE;
bool DestroyImport	= TRUE;
bool CheckCRC		= TRUE;
bool AntiDump		= TRUE;
bool ApiRedirect	= TRUE;
//bool CompressRsrc	= FALSE;
bool EraseHeader	= FALSE;

bool RemoveReloc	= TRUE;
bool RemoveDebug	= TRUE;
bool RemoveDOS		= FALSE;
bool OptmizeDOS		= FALSE;

bool MakeBackUp		= TRUE;
bool AutoRun		= FALSE;
bool ExitWhenDone	= FALSE;


typedef VOID (*MYPROC)(LPTSTR); 
char cExtend[5];
char *szTemp;
HINSTANCE hModule;
MYPROC ProcAdd;

HWND WINAPI OnTabbedDialogInit(HWND hwndDlg);
DLGTEMPLATE * WINAPI DoLockDlgRes(LPCSTR lpszResName);
HWND WINAPI OnSelChanged(HWND hwndDlg);
VOID WINAPI OnChildDialogInit(HWND hwndDlg);
LRESULT CALLBACK ChildDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

// AddIconsToImageList - creates a masked image list and adds some 
// icons to it. 
// Returns the handle to the new image list. 
// hinst - handle to the application instance. 
// 
// Global variables and constants 
//     g_nBird and g_nTree - indexes of the images. 
//     cx_icon and cy_icon - width and height of the icon. 
//     num_icons - number of icons to add to the image list. 
#define NUM_ICONS 2
#define CX_ICON  16 
#define CY_ICON  16 
HIMAGELIST AddIconsToImageList() 
{ 
    HIMAGELIST himlIcons;  // handle to new image list 
    HICON hicon;           // handle to icon 
 
    // Ensure that the common control DLL is loaded. 
    InitCommonControls(); 

    // Create a masked image list large enough to hold the icons. 
    himlIcons = ImageList_Create(CX_ICON, CY_ICON, ILC_MASK, NUM_ICONS, 0); 
 
    // Load the icon resources, and add the icons to the image list. 
    hicon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_SECUR));
    ImageList_AddIcon(himlIcons, hicon);
	hicon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_OPTION));
	ImageList_AddIcon(himlIcons, hicon);
	//hicon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_OPEN));
	//ImageList_AddIcon(himlIcons, hicon);
	//ImageList_AddIcon(himlIcons, hicon); 
 
    return himlIcons; 
} 

#define C_PAGES 2
LPSTR szTabName[C_PAGES];
/*{
	"Protect",
	"Options",
};*/
 typedef struct tag_dlghdr { 
    HWND hwndTab;       // tab control 
    HWND hwndDisplay;   // current child dialog box 
    RECT rcDisplay;     // display rectangle for the tab control 
    DLGTEMPLATE *apRes[C_PAGES]; 
} DLGHDR; 
DLGHDR *pHdr;

HWND WINAPI OnTabbedDialogInit(HWND hwndDlg) 
{ 
	RECT rcClient; 
    pHdr = (DLGHDR *) LocalAlloc(LPTR, sizeof(DLGHDR)); 
    TCITEM tie; 
    RECT rcTab; 
    int i; 
	// Save a pointer to the DLGHDR structure. 

    SetWindowLong(hwndDlg, GWL_USERDATA, (LONG) pHdr); 
	
	// Initialize the tab control.
	//InitCommonControls();
	pHdr->hwndTab = GetDlgItem(hwndDlg, IDC_TABS); 
	if (pHdr->hwndTab == NULL)// handle error 
	{
        return NULL;
    }
    // Determine the bounding rectangle for all child dialog boxes. 
	SetRectEmpty(&rcTab);
	GetClientRect(pHdr->hwndTab, &rcTab); 
	GetClientRect(hwndDlg, &rcClient); 
	rcTab.top=rcClient.bottom-rcTab.bottom+8;
	rcTab.left=5;
	rcTab.right=rcTab.right-4;
	rcTab.bottom=rcTab.top+rcTab.bottom-31;

	// Add a tab for each of the three child dialog boxes.
    tie.mask = TCIF_TEXT | TCIF_IMAGE; 

	szTabName[0]=ViewLangPERTable[dwLanguageID].szProtectTab;
	szTabName[1]=ViewLangPERTable[dwLanguageID].szOptionsTab;
    for (i=0;i<C_PAGES;i++) 
	{ 
        LoadString(hInst, IDC_TABS + i, 
                g_achTemp, sizeof(g_achTemp)/sizeof(g_achTemp[0])); 
		tie.pszText = szTabName[i]; 
		tie.iImage = i;
        if(TabCtrl_InsertItem(pHdr->hwndTab, i, &tie)== -1) 
		{ 
            DestroyWindow(pHdr->hwndTab); 
            return NULL; 
		}
	} 

    // Lock the resources for the three child dialog boxes. 
    pHdr->apRes[0] = DoLockDlgRes(MAKEINTRESOURCE(DLG_PROTECT));
    pHdr->apRes[1] = DoLockDlgRes(MAKEINTRESOURCE(DLG_OPTIONS));
	//pHdr->apRes[2] = DoLockDlgRes(MAKEINTRESOURCE(DLG_PROJECT)); 
	// Calculate the display rectangle. 
    CopyRect(&pHdr->rcDisplay, &rcTab); 

	// Simulate selection of the first item. 
    OnSelChanged(hwndDlg); 

    return pHdr->hwndTab; 
} 

// DoLockDlgRes - loads and locks a dialog template resource. 
// Returns a pointer to the locked resource. 
// lpszResName - name of the resource  
DLGTEMPLATE * WINAPI DoLockDlgRes(LPCSTR lpszResName) 
{ 
    HRSRC hrsrc = FindResource(NULL, lpszResName, RT_DIALOG); 
    HGLOBAL hglb = LoadResource(hInst, hrsrc); 

    return (DLGTEMPLATE *) LockResource(hglb); 
} 

// OnSelChanged - processes the TCN_SELCHANGE notification. 
// hwndDlg - handle to the parent dialog box. 
HWND WINAPI OnSelChanged(HWND hwndDlg) 
{ 
    DLGHDR *pHdr = (DLGHDR *) GetWindowLong(hwndDlg, GWL_USERDATA);
    int iSel = TabCtrl_GetCurSel(pHdr->hwndTab); 
 
    // Destroy the current child dial!og box, if any. 
    if (pHdr->hwndDisplay != NULL) 
        DestroyWindow(pHdr->hwndDisplay); 
 
    // Create the new child dialog box. 
	pHdr->hwndDisplay = CreateDialogIndirect(hInst, 
        pHdr->apRes[iSel], hwndDlg,(DLGPROC) ChildDialogProc);
	return(pHdr->hwndDisplay);
} 
 
// OnChildDialogInit - Positions the child dialog box to fall 
//     within the display area of the tab control. 
 VOID WINAPI OnChildDialogInit(HWND hwndDlg) 
{ 
    HWND hwndParent = GetParent(hwndDlg); 
    DLGHDR *pHdr = (DLGHDR *) GetWindowLong( 
        hwndParent, GWL_USERDATA); 
    SetWindowPos(hwndDlg, HWND_TOP, 
		pHdr->rcDisplay.left, 
		pHdr->rcDisplay.top, 
		pHdr->rcDisplay.right-pHdr->rcDisplay.left, 
		pHdr->rcDisplay.bottom-pHdr->rcDisplay.top, 
		SWP_DRAWFRAME); 
}

VOID UpdateFlags()
{
	// ---- build the protection flag -----
	dwProtectFlags=0;
	//IsDlgButtonChecked(hDlg,IDC_APIREDIRECT)== BST_CHECKED
	if(CheckSI)			dwProtectFlags=dwProtectFlags|CHECK_SI_FLAG;
	if(DestroyImport)	dwProtectFlags=dwProtectFlags|DESTROY_IMPORT_FLAG;
	if(CheckCRC)		dwProtectFlags=dwProtectFlags|CHECK_HEADER_CRC;
	if(AntiDump)		dwProtectFlags=dwProtectFlags|ANTI_DUMP_FLAG;
	if(ApiRedirect)		dwProtectFlags=dwProtectFlags|API_REDIRECT_FLAG;
	if(EraseHeader)		dwProtectFlags=dwProtectFlags|ERASE_HEADER_FLAG;
//	if(CompressRsrc)	dwProtectFlags=dwProtectFlags|COMPRESS_RSRC_FLAG;

	dwAdvancedFlags=0;
	if(RemoveReloc)		dwAdvancedFlags=dwAdvancedFlags|REMOVE_RELOC;
	if(RemoveDebug)		dwAdvancedFlags=dwAdvancedFlags|REMOVE_DEBUG;
	if(RemoveDOS)		dwAdvancedFlags=dwAdvancedFlags|REMOVE_DOS_HEADER;
	if(OptmizeDOS)		dwAdvancedFlags=dwAdvancedFlags|OPTIMIZED_DOS_HEADER;

	if(MakeBackUp)		dwAdvancedFlags=dwAdvancedFlags|CREATE_BACKUP;
	if(AutoRun)			dwAdvancedFlags=dwAdvancedFlags|AUTO_RUN;
	if(ExitWhenDone)	dwAdvancedFlags=dwAdvancedFlags|EXIT_WHEN_DONE;
	SaveToRegistry(dwProtectFlags,
				   dwAdvancedFlags,
				   dwCompressLevel,
				   lpszSectionName,
				   dwLanguageID);
}

char* GetFileExtension(char* szFileName)
{
	char *szTemp=strrchr(szFileName,'.');
	if(szTemp!=NULL)
	{
		szTemp++;
		return(szTemp);
	}
	else return(NULL);
}

LRESULT CALLBACK ChildDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UINT wmId, wmEvent;
	switch (message)
	{
	case WM_INITDIALOG:
		OnChildDialogInit(hDlg);
		// check the checkboxes :)
		SetDlgItemText(hDlg,IDC_FILE_OPEN,cFnameOpen);
		strcpy(cFnameSave,cFnameOpen);
		SetDlgItemText(hDlg,IDC_FILE_SAVE,cFnameSave);

		if(CheckSI)		 CheckDlgButton(hDlg,IDC_SICHECK,TRUE);
		if(EraseHeader)	 CheckDlgButton(hDlg,IDC_ERASEPEHEADER,TRUE);
		if(DestroyImport)CheckDlgButton(hDlg,IDC_DESTROYIMPORT,TRUE);
		if(CheckCRC)	 CheckDlgButton(hDlg,IDC_CHECKHEADERCRC,TRUE);
		if(AntiDump)	 CheckDlgButton(hDlg,IDC_ANTIDUMP,TRUE);
		if(ApiRedirect)	 CheckDlgButton(hDlg,IDC_APIREDIRECT,TRUE);

		if(RemoveReloc)	CheckDlgButton(hDlg,IDC_REMOVERELOC,TRUE);
		if(RemoveDebug)	CheckDlgButton(hDlg,IDC_RMDEBUG,TRUE);
		if(RemoveDOS)   CheckDlgButton(hDlg,IDC_REMOVEDOS,TRUE);
		if(OptmizeDOS)	CheckDlgButton(hDlg,IDC_OPTIMIZEDOS,TRUE);
		hButton=GetDlgItem(hDlg,IDC_OPTIMIZEDOS); 
		if(RemoveDOS)EnableWindow(hButton,FALSE);
		else EnableWindow(hButton,TRUE);
		if((nFilterIndex==2)||(nFilterIndex==3))
		{
			hButton=GetDlgItem(hDlg,IDC_REMOVERELOC);
			EnableWindow(hButton,FALSE);
			hButton=GetDlgItem(hDlg,IDC_REMOVEDOS);
			EnableWindow(hButton,FALSE);
			hButton=GetDlgItem(hDlg,IDC_OPTIMIZEDOS);
			EnableWindow(hButton,FALSE);
		}
		else 
		{
			hButton=GetDlgItem(hDlg,IDC_REMOVERELOC);
			EnableWindow(hButton,TRUE);
			hButton=GetDlgItem(hDlg,IDC_REMOVEDOS);
			EnableWindow(hButton,TRUE);
			hButton=GetDlgItem(hDlg,IDC_OPTIMIZEDOS); 
			if(RemoveDOS)EnableWindow(hButton,FALSE);
			else EnableWindow(hButton,TRUE);
		}


		if(MakeBackUp)	CheckDlgButton(hDlg,IDC_MAKEBACKUP,TRUE);
		if(AutoRun)		CheckDlgButton(hDlg,IDC_AUTORUN,TRUE);
		if(ExitWhenDone)CheckDlgButton(hDlg,IDC_EXITDONE,TRUE);
		DragAcceptFiles(hDlg,TRUE);
		SetDlgItemText(hDlg,IDC_FILE_OPEN,cFnameOpen);
		SetDlgItemText(hDlg,IDC_FILE_SAVE,cFnameSave);
		if(cFnameSave[0]!=0x00)
		{
			hButton=GetDlgItem(hDlg,ID_FILE_SAVE); 
			EnableWindow(hButton,TRUE);
			hButton=GetDlgItem(hDlg,ID_FILE_PROTECT); 
			EnableWindow(hButton,TRUE);
			hButton=GetDlgItem(hDlg,IDC_STATIC2); 
			EnableWindow(hButton,TRUE);
			UpdateWindow(hDlg); 
			EnableMenuItem(hMenu,ID_FILE_SAVE,MF_ENABLED);
			EnableMenuItem(hMenu,ID_FILE_PROTECT,MF_ENABLED);
			UpdateWindow(hwndMain);
		}
		hImageList=AddIconsToImageList();
		TabCtrl_SetImageList(hwndTab,hImageList);
		SetDlgItemInt(hDlg,IDC_COMPRESSRATE,dwCompressLevel,FALSE);
		SetDlgItemText(hDlg,IDC_SECTIONNAME,lpszSectionName);
		SendDlgItemMessage(hDlg,
			               IDC_SECTIONNAME,
						   EM_SETLIMITTEXT,8, 0);
		/*CreateTrackbar(hwndDisplay,
				iMinTrack,iMaxTrack,
				iMinTrack,iMaxTrack,
				iPageSizeTrack);*/
		SetDlgItemText(hDlg,IDC_STATIC1,ViewLangPERTable[dwLanguageID].szProtectTabFileToProtect);
		SetDlgItemText(hDlg,IDC_STATIC2,ViewLangPERTable[dwLanguageID].szProtectTabOutputToFileName);
		SetDlgItemText(hDlg,ID_FILE_PROTECT,ViewLangPERTable[dwLanguageID].szProtectTabProtect);
		SetDlgItemText(hDlg,ID_FILE_TEST,ViewLangPERTable[dwLanguageID].szProtectTabTest);

		SetDlgItemText(hDlg,IDC_STATIC3,ViewLangPERTable[dwLanguageID].szOptionsTabProtection);
		SetDlgItemText(hDlg,IDC_SICHECK,ViewLangPERTable[dwLanguageID].szOptionsTabAntiSoftICEProtection);
		SetDlgItemText(hDlg,IDC_CHECKHEADERCRC,ViewLangPERTable[dwLanguageID].szOptionsTabChecksumProtection);
		SetDlgItemText(hDlg,IDC_APIREDIRECT,ViewLangPERTable[dwLanguageID].szOptionsTabAPIRedirection);
		SetDlgItemText(hDlg,IDC_ANTIDUMP,ViewLangPERTable[dwLanguageID].szOptionsTabAntiDumpProtection);
		SetDlgItemText(hDlg,IDC_DESTROYIMPORT,ViewLangPERTable[dwLanguageID].szOptionsTabClearImportInformation);
		SetDlgItemText(hDlg,IDC_ERASEPEHEADER,ViewLangPERTable[dwLanguageID].szOptionsTabClearPEheader);

		SetDlgItemText(hDlg,IDC_STATIC4,ViewLangPERTable[dwLanguageID].szOptionsTabCompressOption);

		SetDlgItemText(hDlg,IDC_STATIC5,ViewLangPERTable[dwLanguageID].szOptionsTabAdvanced);
		SetDlgItemText(hDlg,IDC_REMOVERELOC,ViewLangPERTable[dwLanguageID].szOptionsTabRemoveRelocSection);
		SetDlgItemText(hDlg,IDC_RMDEBUG,ViewLangPERTable[dwLanguageID].szOptionsTabRemoveDebugInformation);
		SetDlgItemText(hDlg,IDC_REMOVEDOS,ViewLangPERTable[dwLanguageID].szOptionsTabEliminateMSDOSheader);
		SetDlgItemText(hDlg,IDC_OPTIMIZEDOS,ViewLangPERTable[dwLanguageID].szOptionsTabOptimizeMSDOSheader);
		SetDlgItemText(hDlg,IDC_STATIC6,ViewLangPERTable[dwLanguageID].szOptionsTabOther);
		SetDlgItemText(hDlg,IDC_MAKEBACKUP,ViewLangPERTable[dwLanguageID].szOptionsTabCreateBackupCopy);
		SetDlgItemText(hDlg,IDC_AUTORUN,ViewLangPERTable[dwLanguageID].szOptionsTabAutoRunAfterLoading);
		SetDlgItemText(hDlg,IDC_EXITDONE,ViewLangPERTable[dwLanguageID].szOptionsTabExitWhenDone);
		SetDlgItemText(hDlg,IDC_STATIC7,ViewLangPERTable[dwLanguageID].szOptionsTabSectionName);
		return TRUE;

	case WM_DROPFILES:
		HDROP	hDrop;
		hDrop=HDROP(wParam);
		DragQueryFile(hDrop,0,cFnameOpen,sizeof(cFnameOpen));
		DragFinish(hDrop);
		SetDlgItemText(hDlg,IDC_FILE_OPEN,cFnameOpen);
		strcpy(cFnameSave,cFnameOpen);
		SetDlgItemText(hDlg,IDC_FILE_SAVE,cFnameSave);
		SendMessage(hDlg, WM_INITDIALOG, 0, 0);
		szExtension=GetFileExtension(cFnameOpen);
		CopyMemory(cExtend,szExtension,4);
		CharUpperBuff(cExtend,3);
		if(szExtension==NULL)
		{
			MessageBox(hDlg,
				       "This File do not illustrate to be Portable Execuatble File!",
					   "Warning", 
					   MB_OK | MB_ICONWARNING );
			nFilterIndex = 4;
		}
		else
		{
			if(strcmp(cExtend,"EXE")==0)
			{
				nFilterIndex = 1;
			}
			else
			if(strcmp(cExtend,"DLL")==0)
			{
				nFilterIndex = 2;
			}
			else
			if(strcmp(cExtend,"OCX")==0)
			{
				nFilterIndex = 3;
			}
			else
			if(strcmp(cExtend,"SCR")==0)
			{
				nFilterIndex = 4;
			}
			else
			{
				nFilterIndex = 5;
			}
			hButton=GetDlgItem(hDlg,ID_FILE_TEST); 
			EnableWindow(hButton,FALSE);
		}
		break;

	case WM_HSCROLL:
		TBNotifications(wParam,hwndTrack);
		SetDlgItemInt(hDlg,IDC_COMPRESSRATE,dwCompressLevel,FALSE);
		break;

	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Parse the menu selections:
		switch (wmId)
		{
		case IDC_SECTIONNAME:
			switch(wmEvent)
			{
			case EN_CHANGE:
				iSectionName = (WORD) SendDlgItemMessage(hDlg, 
								IDC_SECTIONNAME, 
								EM_LINELENGTH, 
								(WPARAM) 0, 
								(LPARAM) 0); 
				*((LPWORD)lpszSectionName) = iSectionName; 
				SendDlgItemMessage(hDlg, 
                               IDC_SECTIONNAME, 
                               EM_GETLINE, 
                               (WPARAM) 0,       // line 0 
                               (LPARAM)lpszSectionName);
				lpszSectionName[iSectionName] = 0; 
				break;
			}
			break;
		case ID_FILE_OPEN:
			// get a file path
 			cFname[0]=0x00;
			ZeroMemory(&openfn, sizeof(openfn));
			openfn.hwndOwner=GetActiveWindow();
			openfn.lpstrFile=cFname;
			openfn.nMaxFile=sizeof(cFname);
			openfn.lStructSize=sizeof(openfn);
			openfn.lpstrFilter=szFilter; 
			openfn.nFilterIndex=nFilterIndex;
			//openfn.lpstrInitialDir=szCurDir;
			openfn.Flags=OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_LONGNAMES | OFN_HIDEREADONLY;
			fStatus =GetOpenFileName(&openfn);//(LPOPENFILENAME
			if(!fStatus)
			{
				return 0;
			}
			strcpy(cFnameOpen,cFname);
			SetDlgItemText(hDlg,IDC_FILE_OPEN,cFnameOpen);
			strcpy(cFnameSave,cFnameOpen);
			SetDlgItemText(hDlg,IDC_FILE_SAVE,cFnameSave);
			SendMessage(hDlg, WM_INITDIALOG, 0, 0);
			nFilterIndex=openfn.nFilterIndex;
			if(AutoRun)
			{
				SendMessage(hDlg,WM_COMMAND,ID_FILE_PROTECT, 0);
			}
			hButton=GetDlgItem(hDlg,ID_FILE_TEST); 
			EnableWindow(hButton,FALSE);
			break;

		case ID_FILE_SAVE:
			// get a file path
			cFnameSave[0]=0x00;
			strcpy(cFnameSave,cFnameOpen);
			ZeroMemory(&savefn, sizeof(savefn));
			savefn.hwndOwner=GetActiveWindow();
			savefn.lpstrFile=cFnameSave;
			savefn.nMaxFile=sizeof(cFnameSave);
			savefn.lStructSize=sizeof(savefn);
			savefn.lpstrFilter=szFilter;
			savefn.nFilterIndex = openfn.nFilterIndex; 
			//savefn.lpstrInitialDir=szCurDir;
			savefn.Flags=OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_LONGNAMES | OFN_HIDEREADONLY;
			fStatus =GetSaveFileName(&savefn);//(LPOPENFILENAME
			if(!fStatus)
			{
				return 0;
			}
			SetDlgItemText(hDlg,IDC_FILE_SAVE,cFnameSave);
			break;

		case ID_FILE_PROTECT:
			// ----- was a file selected ? -----
			if(cFnameOpen==NULL)
			{
				MessageBox(hDlg,"No file selected up to now !","ERROR",MB_ICONERROR);
				return 0;
			}
			if(cFnameSave==NULL)
			{
				MessageBox(hDlg,"No file selected up to save !","ERROR",MB_ICONERROR);
				return 0;
			}
			UpdateFlags();
			SetPriorityClass(GetCurrentProcess(),HIGH_PRIORITY_CLASS);
			CryptFile(cFnameOpen,cFnameSave,dwProtectFlags,
					  dwAdvancedFlags,dwCompressLevel,
					  lpszSectionName);
			SetPriorityClass(GetCurrentProcess(),NORMAL_PRIORITY_CLASS);
			if(ExitWhenDone)
			{
				PostQuitMessage(0);
			}
			hButton=GetDlgItem(hDlg,ID_FILE_TEST); 
			EnableWindow(hButton,TRUE);
			break;

		case ID_FILE_TEST:
			STARTUPINFO si;
			PROCESS_INFORMATION pi;

			ZeroMemory( &si, sizeof(si) );
			si.cb = sizeof(si);
			ZeroMemory( &pi, sizeof(pi) );

			szTemp=strrchr(cFnameSave,'.');
			CopyMemory(cExtend,szTemp,5);
			//WinExec(cFnameSave,SW_SHOW);
			CharUpperBuff(cExtend,4);
			if((!strcmp(cExtend,".EXE"))||(!strcmp(cExtend,".SCR")))
			{
				if( !CreateProcess( cFnameSave,	// No module name (use command line). 
									NULL,		// Command line. 
									NULL,		// Process handle not inheritable. 
									NULL,		// Thread handle not inheritable. 
									FALSE,		// Set handle inheritance to FALSE. 
									NORMAL_PRIORITY_CLASS,	// No creation flags. 
									NULL,		// Use parent's environment block. 
									NULL,		// Use parent's starting directory. 
									&si,		// Pointer to STARTUPINFO structure.
									&pi )		// Pointer to PROCESS_INFORMATION structure.
					) 
				{
					//ErrorExit( "CreateProcess failed." );
					Beep(100,100);
				}
				break;
			}
			if(!strcmp(cExtend,".OCX"))
			{
				hModule=LoadLibraryEx(cFnameSave,NULL,DONT_RESOLVE_DLL_REFERENCES);
				if(hModule!=0)
				{
					ProcAdd=(MYPROC)GetProcAddress(hModule,_T("DllRegisterServer"));
					if(ProcAdd!=0)
					{
						MessageBox(hDlg,"OLE-ActiveX Control was registered successfully.","Yoda's Protector",MB_ICONINFORMATION);
					}
					else
					{
						MessageBox(hDlg,"Error! OLE-ActiveX Control was not registered successfully!","Yoda's Protector",MB_ICONINFORMATION);
					}
					FreeLibrary(hModule);
				}
				else 
				{
					MessageBox(hDlg,"Error! OLE-ActiveX Control was not loaded successfully!","Yoda's Protector",MB_ICONINFORMATION);
				}
			}

			if(!strcmp(cExtend,".DLL"))
			{
				hModule=LoadLibraryEx(cFnameSave,NULL,DONT_RESOLVE_DLL_REFERENCES);
				if(hModule!=0)
				{
					MessageBox(hDlg,"Dynamic Link Library was loaded successfully.","Yoda's Protector",MB_ICONINFORMATION);
					FreeLibrary(hModule);
				}
				else 
				{
					MessageBox(hDlg,"Error! Dynamic Link Library was not loaded successfully!","Yoda's Protector",MB_ICONINFORMATION);
				}
			}
			break;

		case IDC_SICHECK:
			CheckSI=!CheckSI;
			UpdateFlags();
			break;

		case IDC_ERASEPEHEADER:
			EraseHeader=!EraseHeader;
			if(EraseHeader)
			{
				MessageBox(hDlg,
					"Be careful, This option does not perform in most PE files.\nIt is possible to corrupt your PE files!",
					"Warning", 
					MB_OK | MB_ICONWARNING);
			}
			UpdateFlags();
			break;

		case IDC_DESTROYIMPORT:
			DestroyImport=!DestroyImport;
			UpdateFlags();
			break;

		case IDC_ANTIDUMP:
			AntiDump=!AntiDump;
			UpdateFlags();
			break;

		case IDC_APIREDIRECT:
			ApiRedirect=!ApiRedirect;
			UpdateFlags();
			break;

		case IDC_CHECKHEADERCRC:
			CheckCRC=!CheckCRC;
			UpdateFlags();
			break;

		case IDC_REMOVERELOC:
			RemoveReloc=!RemoveReloc;
			UpdateFlags();
			break;

		case IDC_RMDEBUG:
			RemoveDebug=!RemoveDebug;
			UpdateFlags();
			break;
		
		case IDC_REMOVEDOS:
			RemoveDOS=!RemoveDOS;
			hButton=GetDlgItem(hDlg,IDC_OPTIMIZEDOS); 
			if(RemoveDOS)EnableWindow(hButton,FALSE);
			else EnableWindow(hButton,TRUE);
			UpdateFlags();
			break;

		case IDC_OPTIMIZEDOS:
			OptmizeDOS=!OptmizeDOS;
			UpdateFlags();
			break;
		
		case IDC_MAKEBACKUP:
			MakeBackUp=!MakeBackUp;
			UpdateFlags();
			break;

		case IDC_AUTORUN:
			AutoRun=!AutoRun;
			UpdateFlags();
			break;

		case IDC_EXITDONE:
			ExitWhenDone=!ExitWhenDone;
			UpdateFlags();
			break;
		}
		break;

	}
	return FALSE;
}
