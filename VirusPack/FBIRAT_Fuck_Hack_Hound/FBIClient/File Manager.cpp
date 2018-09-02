#include "Main.h"
#include "PacketHead.h"
#include "Settings.h"
#include "resource.h"

void FileResize(HWND hwnd)
{
RECT rc;
GetClientRect(hwnd, &rc);
MoveWindow(GetDlgItem(hwnd, IDC_DRIVES), 0, 0, 115, rc.bottom - 25, TRUE);
MoveWindow(GetDlgItem(hwnd, IDC_FOLDERLIST),120, 25, rc.right - 125, rc.bottom - 55, TRUE);
MoveWindow(GetDlgItem(hwnd, IDC_DIRECTORY), 120,0, rc.right - 125, 20, TRUE);
MoveWindow(GetDlgItem(hwnd, IDC_TRANSFER), 0,0, rc.right - 10, rc.bottom - 25, TRUE);
MoveWindow(GetDlgItem(hwnd, IDC_SEARCH), 0,20, rc.right - 5, rc.bottom - 50, TRUE);
MoveWindow(GetDlgItem(hwnd, IDC_DIR), 0,0, rc.right / 2, 20, TRUE);
MoveWindow(GetDlgItem(hwnd, IDC_NAME), 5 + (rc.right / 2),0,200, 20, TRUE);
MoveWindow(GetDlgItem(hwnd, IDC_GO), 210 + (rc.right / 2),0,50, 20, TRUE);
MoveWindow(GetDlgItem(hwnd, IDC_FILETAB), 0,0, rc.right, rc.bottom, TRUE);
}
/////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK RenameProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	int  Select = 0;
	int K = 0;
	int W = 0;
    char WindowOut [10] = "";
	char WindowOutY [10] = "";
	char NewName [256] =  "";
	char OldName [256] =  "";
	char FinalName [256] =  "";
	HWND file = 0;
    
	switch(message)
	{
		////////////////////////////////////////////////////////////////////////////////
	case WM_INITDIALOG:
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT2), SW_HIDE);
		ShowWindow(GetDlgItem(hwnd, IDC_ID), SW_HIDE);
		break;
		
	case WM_COMMAND:
		Select=LOWORD(wParam);
		switch(Select)
		{
		case IDC_SETNAME:
			GetWindowText(GetDlgItem(hwnd, IDC_NAME), NewName, 256);
			GetWindowText(GetDlgItem(hwnd, IDC_EDIT2), OldName, 256);
			GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 256);
			
			sprintf(FinalName, "%s|%s",OldName, NewName);
			FBISend(Server[atoi(WindowOut)], FinalName, atoi(WindowOut), 0,0,PACKET_FILE_MANAGER_FILE_RENAME);
			
			EndDialog(hwnd,Select);
			break;
		case IDCANCEL:
			EndDialog(hwnd,Select);
			break;
		}
		return TRUE;
	}
	return 0;
}
DWORD WINAPI NameWindow(LPVOID lpParam)
{
    int LID = (int)lpParam;
	char WindowText [20] = "";
	char Data [1024] = "";
	char Temp [256] = "";
	POINT pt;
	RECT rc;

	GetWindowText(GetDlgItem(File[LID], IDC_DIRECTORY), Data, sizeof(Data));
	GetWindowText(GetDlgItem(File[LID], IDC_WINTEXT), Temp, sizeof(Temp));
	strcat(Data, Temp);

    GetCursorPos(&pt);
	GetWindowRect(File[LID], &rc);
	pt.y -= 5;
	pt.x = rc.right;
	RenameF[LID]=CreateDialog(SysInst,(LPCTSTR)IDD_RENAME,NULL,(DLGPROC)RenameProc);
	ShowWindow(RenameF[LID],SW_SHOW);
	SetWindowPos(RenameF[LID], HWND_TOP, pt.x, pt.y, 0, 0, SWP_NOSIZE);
	InitCommonControls();
	
	SetWindowText(GetDlgItem(RenameF[LID],IDC_NAME), Data);
	SetWindowText(GetDlgItem(RenameF[LID],IDC_EDIT2), Data);
	ZeroMemory(&WindowText[0],10);
	sprintf(&WindowText[0],"%d", LID);
	SetWindowText(GetDlgItem(RenameF[LID], IDC_ID), WindowText);
	
	MSG msg;
	while(GetMessage(&msg,RenameF[LID],0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
LRESULT CALLBACK FileWndProc(HWND Dlg,UINT Mes,WPARAM wParam,LPARAM lParam)
{
	TCITEM tie;
	LV_COLUMN	col;
	LV_ITEM		item;	
	HMENU hmenu;            // menu template          
    HMENU hmenuTrackPopup;  // shortcut menu   
    POINT  pt;   // location of mouse click 
	char WindowId [12] = "";
	char Data [1024] = "";
	char achTemp[1024] = ""; 
	char Temp [1024] = "";
	DWORD thread;
	HICON hIcon;
	HIMAGELIST hImageList;
	HIMAGELIST hImageListA;
	int X = 0;
	int i = 0;
	int j = 0;
	FileTransfer FileUp;
	switch(Mes)
	{
	case WM_INITDIALOG:
		
		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0);
		SendMessage(Dlg, WM_SETICON,ICON_SMALL,(LPARAM)hIcon);
		DeleteObject(hIcon);
		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 64, 64, 0);
		SendMessage(Dlg, WM_SETICON,ICON_BIG,(LPARAM)hIcon);

		tie.mask = TCIF_TEXT | TCIF_IMAGE;  
		tie.pszText = "File Manager";
		
		TabCtrl_InsertItem(GetDlgItem(Dlg, IDC_FILETAB), 0, &tie);

		tie.mask = TCIF_TEXT | TCIF_IMAGE;  
		tie.pszText = "Transfer's";
		
		TabCtrl_InsertItem(GetDlgItem(Dlg, IDC_FILETAB), 1, &tie);

		tie.mask = TCIF_TEXT | TCIF_IMAGE;  
		tie.pszText = "Search";
		
		TabCtrl_InsertItem(GetDlgItem(Dlg, IDC_FILETAB), 2, &tie);
		/////////////////////////////////////////////////////////////
		//initiating list.
	    ListView_SetExtendedListViewStyle(GetDlgItem(Dlg,IDC_DRIVES),LVS_EX_FULLROWSELECT);
		col.mask=LVCF_TEXT|LVCF_WIDTH|LVIF_IMAGE;
		col.cx=100;

		col.pszText="Drives";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_DRIVES),0,&col);
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    	ListView_SetExtendedListViewStyle(GetDlgItem(Dlg,IDC_FOLDERLIST),LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		col.mask=LVCF_TEXT|LVCF_WIDTH|LVIF_IMAGE;
		col.cx=150;
		
		col.pszText="Name";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_FOLDERLIST),0,&col);

		col.mask=LVCF_TEXT|LVCF_WIDTH|LVIF_IMAGE;
		col.cx=100;
		
		col.pszText="Type";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_FOLDERLIST),1,&col);

		col.mask=LVCF_TEXT|LVCF_WIDTH|LVIF_IMAGE;
		col.cx=100;
		
		col.pszText="Size";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_FOLDERLIST),2,&col);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		ListView_SetExtendedListViewStyle(GetDlgItem(Dlg,IDC_SEARCH),LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		col.mask=LVCF_TEXT|LVCF_WIDTH|LVIF_IMAGE;
		col.cx=150;
		
		col.pszText="File";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_SEARCH),0,&col);
		
		col.mask=LVCF_TEXT|LVCF_WIDTH|LVIF_IMAGE;
		col.cx=100;
		
		col.pszText="Directory";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_SEARCH),1,&col);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		ListView_SetExtendedListViewStyle(GetDlgItem(Dlg,IDC_TRANSFER),LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		col.mask=LVCF_TEXT|LVCF_WIDTH|LVIF_IMAGE;

		col.cx=150;
		
		col.pszText="File Name";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_TRANSFER),0,&col);
		
		
		col.cx=150;
		
		col.pszText="Upload / Download";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_TRANSFER),1,&col);

		col.cx=150;
		
		col.pszText="Status";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_TRANSFER),2,&col);

		hImageList=ImageList_Create(16,16,ILC_COLORDDB,20, 30);
		ImageList_SetBkColor(hImageList,CLR_NONE);// Macro: 16x16:16bit with 2 pics [array]
		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DRIVE), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
		ImageList_AddIcon(hImageList, hIcon);							      // Macro: Attach the image, to the image list
		DeleteObject(hIcon);
		
		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FLOP), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
		ImageList_AddIcon(hImageList, hIcon);							      // Macro: Attach the image, to the image list
		DeleteObject(hIcon);
		
		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_CD), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
		ImageList_AddIcon(hImageList, hIcon);							      // Macro: Attach the image, to the image list
		DeleteObject(hIcon);
		
		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DEFAULT), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
		ImageList_AddIcon(hImageList, hIcon);							      // Macro: Attach the image, to the image list
		DeleteObject(hIcon);

		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FILM), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
		ImageList_AddIcon(hImageList, hIcon);							      // Macro: Attach the image, to the image list
		DeleteObject(hIcon);

		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_PIC), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
		ImageList_AddIcon(hImageList, hIcon);							      // Macro: Attach the image, to the image list
		DeleteObject(hIcon);

		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_TEXT), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
		ImageList_AddIcon(hImageList, hIcon);							      // Macro: Attach the image, to the image list
		DeleteObject(hIcon);

		
		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_EXE), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
		ImageList_AddIcon(hImageList, hIcon);							      // Macro: Attach the image, to the image list
		DeleteObject(hIcon);

		
		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FOLDER), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
		ImageList_AddIcon(hImageList, hIcon);							      // Macro: Attach the image, to the image list
		DeleteObject(hIcon);

		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_BACK), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
		ImageList_AddIcon(hImageList, hIcon);							      // Macro: Attach the image, to the image list
		DeleteObject(hIcon);
		
		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DOWN), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
		ImageList_AddIcon(hImageList, hIcon);							      // Macro: Attach the image, to the image list
		DeleteObject(hIcon);

		hImageListA=ImageList_Create(16,16,ILC_COLORDDB,20, 30);
		ImageList_SetBkColor(hImageListA,CLR_NONE);// Macro: 16x16:16bit with 2 pics [array]
		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DOWN), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
		ImageList_AddIcon(hImageListA, hIcon);							      // Macro: Attach the image, to the image list
		DeleteObject(hIcon);

		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_UP), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
		ImageList_AddIcon(hImageListA, hIcon);							      // Macro: Attach the image, to the image list
		DeleteObject(hIcon);
		ListView_SetImageList(GetDlgItem(Dlg, IDC_DRIVES),hImageList, LVSIL_SMALL);
		ListView_SetImageList(GetDlgItem(Dlg, IDC_FOLDERLIST),hImageList, LVSIL_SMALL);
		ListView_SetImageList(GetDlgItem(Dlg, IDC_TRANSFER),hImageListA, LVSIL_SMALL);
		
		ShowWindow(GetDlgItem(Dlg, IDC_SEARCH), SW_HIDE);
		ShowWindow(GetDlgItem(Dlg, IDC_ID), SW_HIDE);
		ShowWindow(GetDlgItem(Dlg, IDC_TRANSFER), SW_HIDE);
		ShowWindow(GetDlgItem(Dlg, IDC_WINTEXT), SW_HIDE);
		ShowWindow(GetDlgItem(Dlg, IDC_FILE), SW_HIDE);
		ShowWindow(GetDlgItem(Dlg, IDC_SIZEWIN), SW_HIDE);
		ShowWindow(GetDlgItem(Dlg, IDC_FILENAME), SW_HIDE);
		ShowWindow(GetDlgItem(Dlg, IDC_DIR), SW_HIDE);
		ShowWindow(GetDlgItem(Dlg, IDC_NAME), SW_HIDE);
		ShowWindow(GetDlgItem(Dlg, IDC_GO), SW_HIDE);
		ShowWindow(GetDlgItem(Dlg, IDC_FOLDERLIST), SW_SHOW);
		ShowWindow(GetDlgItem(Dlg, IDC_DRIVES), SW_SHOW);
		ShowWindow(GetDlgItem(Dlg, IDC_DIRECTORY), SW_SHOW);
		FileResize(Dlg);
		case WM_SIZING:
			switch(wParam)
			{
			case WMSZ_BOTTOM:
				FileResize(Dlg);
			break;
			case WMSZ_BOTTOMLEFT:
				FileResize(Dlg);
			break;
			case WMSZ_BOTTOMRIGHT:
				FileResize(Dlg);
			break;
			case WMSZ_LEFT:
				FileResize(Dlg);
            break;
			case WMSZ_RIGHT:
				FileResize(Dlg);
			break;
			case WMSZ_TOP:
				FileResize(Dlg);
			break;
			case WMSZ_TOPLEFT:
				FileResize(Dlg);
			break;
			case WMSZ_TOPRIGHT:
				FileResize(Dlg);
			break;
			}
			break;
			case WM_NOTIFY:
		switch(wParam)
		{
		case IDC_FILETAB:
            switch (((LPNMHDR)lParam)->code)
            {
            case TCN_SELCHANGE:
                   int iPage = TabCtrl_GetCurSel(GetDlgItem(Dlg, IDC_FILETAB)); 
                   switch(iPage)
					{
					 case 0:
					 ShowWindow(GetDlgItem(Dlg, IDC_SEARCH), SW_HIDE);
					 ShowWindow(GetDlgItem(Dlg, IDC_TRANSFER), SW_HIDE);
					 ShowWindow(GetDlgItem(Dlg, IDC_DIR), SW_HIDE);
					 ShowWindow(GetDlgItem(Dlg, IDC_NAME), SW_HIDE);
					 ShowWindow(GetDlgItem(Dlg, IDC_GO), SW_HIDE);
					 ShowWindow(GetDlgItem(Dlg, IDC_FOLDERLIST), SW_SHOW);
					 ShowWindow(GetDlgItem(Dlg, IDC_DRIVES), SW_SHOW);
					 ShowWindow(GetDlgItem(Dlg, IDC_DIRECTORY), SW_SHOW);
					 break;

					 case 1:
					 ShowWindow(GetDlgItem(Dlg, IDC_SEARCH), SW_HIDE);
					 ShowWindow(GetDlgItem(Dlg, IDC_FOLDERLIST), SW_HIDE);
					 ShowWindow(GetDlgItem(Dlg, IDC_DRIVES), SW_HIDE);
					 ShowWindow(GetDlgItem(Dlg, IDC_DIRECTORY), SW_HIDE);
					 ShowWindow(GetDlgItem(Dlg, IDC_DIR), SW_HIDE);
					 ShowWindow(GetDlgItem(Dlg, IDC_NAME), SW_HIDE);
					 ShowWindow(GetDlgItem(Dlg, IDC_GO), SW_HIDE);
					 ShowWindow(GetDlgItem(Dlg, IDC_TRANSFER), SW_SHOW);
					 break;

					 case 2:
					 ShowWindow(GetDlgItem(Dlg, IDC_DIRECTORY), SW_HIDE);
					 ShowWindow(GetDlgItem(Dlg, IDC_FOLDERLIST), SW_HIDE);
					 ShowWindow(GetDlgItem(Dlg, IDC_DRIVES), SW_HIDE);
					 ShowWindow(GetDlgItem(Dlg, IDC_TRANSFER), SW_HIDE);
					 ShowWindow(GetDlgItem(Dlg, IDC_SEARCH), SW_SHOW);
					 ShowWindow(GetDlgItem(Dlg, IDC_DIR), SW_SHOW);
					 ShowWindow(GetDlgItem(Dlg, IDC_NAME), SW_SHOW);
					 ShowWindow(GetDlgItem(Dlg, IDC_GO), SW_SHOW);
					 GetWindowText(GetDlgItem(Dlg, IDC_DIRECTORY), Data, 12);
					 SetWindowText(GetDlgItem(Dlg, IDC_DIR), Data);
					 SetWindowText(GetDlgItem(Dlg, IDC_NAME), "*.jpeg");
					 break;
					}
				
				break;
	
			}
					break;
			case IDC_DRIVES:
				switch (((LPNMHDR)lParam)->code)
				{
				case NM_RCLICK:

					break;

				case NM_DBLCLK:
					GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
					item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_DRIVES),-1,LVNI_SELECTED);
					item.mask=LVIF_TEXT;
					item.iSubItem=0;
					item.pszText=Data;
					item.cchTextMax=sizeof(Data);
					ListView_GetItem(GetDlgItem(Dlg,IDC_DRIVES),&item);  
					ListView_DeleteAllItems(GetDlgItem(Dlg, IDC_FOLDERLIST));
					SetWindowText(GetDlgItem(Dlg, IDC_DIRECTORY), Data);
					FBISend(Server[atoi(WindowId)], Data, atoi(WindowId), 0,0, PACKET_FILE_MANAGER_FILE);
					break;
				}
				break;
				case IDC_FOLDERLIST:
					switch (((LPNMHDR)lParam)->code)
					{
						
				case NM_RCLICK:
						// Get the client coordinates for the mouse click.
						pt.x = 0;
						pt.y = 0;
						GetCursorPos(&pt);
						
						item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_FOLDERLIST),-1,LVNI_SELECTED);
						item.mask=LVIF_TEXT;
						item.iSubItem=1;
						item.pszText=Data;
						item.cchTextMax=sizeof(Data);
				     	ListView_GetItem(GetDlgItem(Dlg,IDC_FOLDERLIST),&item);  
						if(!strcmp(Data, "Directory"))
						{
						//hmenu = LoadMenu(GInstance, MAKEINTRESOURCE(IDR_FILE_FOLDER));
						}
						else
						{
						hmenu = LoadMenu(GInstance, MAKEINTRESOURCE(IDR_FILE_FILE));
						}
						if (hmenu == NULL) 
						{
							break;
						}
						
						hmenuTrackPopup = GetSubMenu(hmenu, 0); 
						
						//ClientToScreen(Dlg, (LPPOINT) &pt);   
						
						TrackPopupMenu(hmenuTrackPopup, TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, 0, Dlg, NULL);
						break;
						
				case NM_DBLCLK:	
					
					item.iItem=0;
					item.mask=LVIF_TEXT;
					item.iSubItem=1;
					item.pszText=Data;
					item.cchTextMax=sizeof(Data);
				    ListView_GetItem(GetDlgItem(Dlg,IDC_FOLDERLIST),&item);
					
					GetWindowText(GetDlgItem(Dlg, IDC_DIRECTORY), achTemp, sizeof(achTemp));
					if(!strcmp(Data, "Back") || !strcmp(Data, "Completed"))
					{
					}
					else
					{
					 break;
					}
					

					item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_FOLDERLIST),-1,LVNI_SELECTED);
					item.mask=LVIF_TEXT;
					item.iSubItem=1;
					item.pszText=Data;
					item.cchTextMax=sizeof(Data);
				    ListView_GetItem(GetDlgItem(Dlg,IDC_FOLDERLIST),&item);

					if(!strcmp(Data, "Directory"))
					{						
						GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
						item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_FOLDERLIST),-1,LVNI_SELECTED);
						item.mask=LVIF_TEXT;
						item.iSubItem=0;
						item.pszText=Data;
						item.cchTextMax=sizeof(Data);
						ListView_GetItem(GetDlgItem(Dlg,IDC_FOLDERLIST),&item); 
						GetWindowText(GetDlgItem(Dlg, IDC_DIRECTORY), achTemp, sizeof(achTemp));
						strcat(achTemp, Data);
						strcat(achTemp, "\\");
						SetWindowText(GetDlgItem(Dlg, IDC_DIRECTORY), achTemp);
						ListView_DeleteAllItems(GetDlgItem(Dlg, IDC_FOLDERLIST));
						FBISend(Server[atoi(WindowId)], achTemp, atoi(WindowId), 0,0, PACKET_FILE_MANAGER_FILE);
						break;
					}
					
					if(!strcmp(Data, "Back"))
					{
						GetWindowText(GetDlgItem(Dlg, IDC_DIRECTORY), achTemp, sizeof(achTemp));
						X = strlen(achTemp);
						  X--;						
						achTemp[X] = '\0';
						while(achTemp[X] != '\\')
						{			
						achTemp[X] = '\0';
						  X--;
						}
						SetWindowText(GetDlgItem(Dlg, IDC_DIRECTORY), achTemp);
						ListView_DeleteAllItems(GetDlgItem(Dlg, IDC_FOLDERLIST));
						FBISend(Server[atoi(WindowId)], achTemp, atoi(WindowId), 0,0, PACKET_FILE_MANAGER_FILE);
						break;
					}
					if(!strcmp(Data, "Completed"))
					{
					break;
					}
					if(!strcmp(Data, "File"))
					{
					GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
					EndDialog(RenameF[atoi(WindowId)], 0);
					
					ZeroMemory(Data, sizeof(Data));
					GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);

					item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_FOLDERLIST),-1,LVNI_SELECTED);
					item.mask=LVIF_TEXT;
					item.iSubItem=0;
					item.pszText=Data;
					item.cchTextMax=sizeof(Data);
				    ListView_GetItem(GetDlgItem(Dlg,IDC_FOLDERLIST),&item);

					SetWindowText(GetDlgItem(Dlg,IDC_WINTEXT), Data);
					CreateThread(NULL, 0, NameWindow,(LPVOID)atoi(WindowId), 0, &thread);
					break;
					}
					
					if(!strcmp(Data, "Refresh"))
					{
						GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
						GetWindowText(GetDlgItem(Dlg, IDC_DIRECTORY), achTemp, sizeof(achTemp));
						ListView_DeleteAllItems(GetDlgItem(Dlg, IDC_FOLDERLIST));
						FBISend(Server[atoi(WindowId)], achTemp, atoi(WindowId), 0,0, PACKET_FILE_MANAGER_FILE);
						break;
					}
					break;
					
			case NM_CLICK:
					GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
					EndDialog(RenameF[atoi(WindowId)], 0);
			break;
					}
		break;	
	/*
	case IDC_SERVICES:
        if(((LPNMHDR)lParam)->code == NM_RCLICK) // Right Click
		{	 
            // Get the client coordinates for the mouse click.
			pt.x = 0;
			pt.y = 0;
			GetCursorPos(&pt);
			
            // If the mouse click took place inside the client 
            // area, execute the application-defined function 
            // that displays the shortcut menu. 
			
			
			hmenu = LoadMenu(GInstance, MAKEINTRESOURCE(IDR_SERVICES));
			
			if (hmenu == NULL) 
			{
				break;
			}
			
			hmenuTrackPopup = GetSubMenu(hmenu, 0); 
			
            //ClientToScreen(Dlg, (LPPOINT) &pt);   
			
            TrackPopupMenu(hmenuTrackPopup, TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, 0, Dlg, NULL);
		}
		break;*/
		}
		break;
				break;
	case WM_LBUTTONDOWN:
		GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
		EndDialog(RenameF[atoi(WindowId)], 0);
		break;
	case WM_NCLBUTTONDOWN:
		GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
		EndDialog(RenameF[atoi(WindowId)], 0);
		break;
	case WM_COMMAND:
		switch(wParam)
		{
		case IDC_NORMAL:
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_FOLDERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Data;
			item.cchTextMax=sizeof(Data);
			ListView_GetItem(GetDlgItem(Dlg,IDC_FOLDERLIST),&item);			
			GetWindowText(GetDlgItem(Dlg, IDC_DIRECTORY), achTemp, sizeof(achTemp));
			strcat(achTemp, Data);
			FBISend(Server[atoi(WindowId)], achTemp, atoi(WindowId), 1, 0, PACKET_FILE_MANAGER_FILE_EXECUTE);
			break;
		case IDC_HIDDEN:
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_FOLDERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Data;
			item.cchTextMax=sizeof(Data);
			ListView_GetItem(GetDlgItem(Dlg,IDC_FOLDERLIST),&item);		
			GetWindowText(GetDlgItem(Dlg, IDC_DIRECTORY), achTemp, sizeof(achTemp));
			strcat(achTemp, Data);
			FBISend(Server[atoi(WindowId)], achTemp, atoi(WindowId), 2, 0, PACKET_FILE_MANAGER_FILE_EXECUTE);
			break;
		case IDC_DELETE:
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_FOLDERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Data;
			item.cchTextMax=sizeof(Data);
			ListView_GetItem(GetDlgItem(Dlg,IDC_FOLDERLIST),&item);		
			GetWindowText(GetDlgItem(Dlg, IDC_DIRECTORY), achTemp, sizeof(achTemp));
			strcat(achTemp, Data);
			FBISend(Server[atoi(WindowId)], achTemp, atoi(WindowId), 0, 0, PACKET_FILE_MANAGER_DELETE_FILE);
			ListView_DeleteItem(GetDlgItem(Dlg,IDC_FOLDERLIST),ListView_GetNextItem(GetDlgItem(Dlg,IDC_FOLDERLIST),-1,LVNI_SELECTED));
			break;
		case IDC_COPY:
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_FOLDERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Data;
			item.cchTextMax=sizeof(Data);
			ListView_GetItem(GetDlgItem(Dlg,IDC_FOLDERLIST),&item);		
			GetWindowText(GetDlgItem(Dlg, IDC_DIRECTORY), achTemp, sizeof(achTemp));
			strcat(achTemp, Data);
			SetWindowText(GetDlgItem(Dlg, IDC_FILE), achTemp);
			SetWindowText(GetDlgItem(Dlg, IDC_FILENAME), Data);

			ZeroMemory(Data, sizeof(Data));
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_FOLDERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=2;
			item.pszText=Data;
			item.cchTextMax=sizeof(Data);
			ListView_GetItem(GetDlgItem(Dlg,IDC_FOLDERLIST),&item);	
			SetWindowText(GetDlgItem(Dlg, IDC_SIZEWIN), Data);
			break;
		case IDC_PASTE:
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);			
			GetWindowText(GetDlgItem(Dlg, IDC_FILENAME), Data, sizeof(achTemp));
			GetWindowText(GetDlgItem(Dlg, IDC_DIRECTORY), achTemp, sizeof(achTemp));
			strcat(achTemp, Data);
			GetWindowText(GetDlgItem(Dlg, IDC_FILE), Temp, sizeof(achTemp));
			sprintf(Data, "%s|%s", Temp, achTemp);
			FBISend(Server[atoi(WindowId)], Data, atoi(WindowId), 2, 0, PACKET_FILE_MANAGER_FILE_COPY);
			
			ZeroMemory(achTemp, sizeof(achTemp));
			ZeroMemory(Data, sizeof(Data));

			GetWindowText(GetDlgItem(Dlg, IDC_FILENAME), achTemp, sizeof(achTemp));
			GetWindowText(GetDlgItem(Dlg, IDC_SIZEWIN), Data, sizeof(Data));

			SetFileWindow(achTemp, Data, 3, atoi(WindowId));
			break;
		case IDC_UPLOAD:
			OPENFILENAME ofn;	
			
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 10);
			
			ZeroMemory(&ofn, sizeof(ofn));

			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = Dlg;
			ofn.lpstrFilter = "All Files (*.*)\0*.*\0";
			ofn.lpstrFile = Temp;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
			ofn.lpstrDefExt = "";
			
			
            if(GetOpenFileName(&ofn))
            {
				ZeroMemory(achTemp, sizeof(achTemp));
				i = strlen(Temp);
				j = 0;
				
				while(Temp[i] != '\\') 
				{
					i--;
				}
				i++; 
				
				for(;i<(strlen(Temp));i++)
				{
					achTemp[j] = Temp[i];
					j++;
                }
				
				///////////////////////////////////////////////////////////////////
				IC = ListView_GetItemCount(GetDlgItem(Dlg,IDC_TRANSFER));
				item.mask=TVIF_TEXT | TVIF_IMAGE;
				item.iItem=ListView_GetItemCount(GetDlgItem(Dlg,IDC_TRANSFER));//ListView_GetItemCount(GetDlgItem(Dlg,IDC_TRANSFER));
				item.iImage = 1;
				item.iSubItem=0;
				item.pszText=achTemp;
				item.iItem=ListView_InsertItem(GetDlgItem(Dlg,IDC_TRANSFER),&item);
				
				item.iSubItem=1;
				item.pszText="Upload";
				ListView_SetItem(GetDlgItem(Dlg,IDC_TRANSFER),&item);
				
				item.iSubItem=2;
				item.pszText="";
				ListView_SetItem(GetDlgItem(Dlg,IDC_TRANSFER),&item);

				
				strcpy(FileUp.Path, Temp);
				GetWindowText(GetDlgItem(Dlg, IDC_DIRECTORY), Data, sizeof(Data));
				strcat(Data, achTemp);
				strcpy(FileUp.Name, Data);
				FileUp.FileID = A;
				FileUp.ID = atoi(WindowId);
			    CreateThread(NULL, 0, SendFile,(LPVOID)&FileUp, 0, &thread);
				
			    A++;
				CUNT++;

			}  

			//PACKET_FILE_MANAGER_FILE_OPEN
			break;
		case IDC_DOWNLOAD:

			GetWindowText(GetDlgItem(Dlg,IDC_DIRECTORY), achTemp, 512);
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 10);
				
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_FOLDERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_FOLDERLIST),&item);
			
			/*	strcpy(Buffer, "");
				sprintf(Buffer, "Downloading: %s", Text);
				GetTime();
				SetLogs(Time, "Download", Buffer , "Pass");*/

			strcat(achTemp, Data);

            sprintf(Temp, "%s|%s", achTemp, Data);

			FBISend(Server[atoi(WindowId)], Temp,atoi(WindowId), D, ListView_GetItemCount(GetDlgItem(Dlg,IDC_TRANSFER)), PACKET_FILE_MANAGER_FILE_DOWN);
			if(D == 1025)
			{
			D = 0;
			}
		 //  Head.PacketType = PACKET_FILE_MANAGER_FILE_DOWN; ListView_GetItemCount(GetDlgItem(hWnd,IDC_DOWNLOADS));

		   DOWN[D] = fopen(Data, "wb");
		   if(DOWN[D] == NULL)
		   {
			//MessageBox(NULL, "NULL", "NULL", MB_OK);
			   break;
		   }
		   else
		   {
			//MessageBox(NULL, "Success Opening", "Success", MB_OK);
		   }
		   item.mask=TVIF_TEXT | TVIF_IMAGE; //
		   item.iItem=ListView_GetItemCount(GetDlgItem(Dlg,IDC_TRANSFER));//
		   item.iImage = 0;
		   item.iSubItem=0;
		   item.pszText=Data;
		   item.iItem=ListView_InsertItem(GetDlgItem(Dlg,IDC_TRANSFER),&item);
		   
		   item.iSubItem=1;
		   item.pszText="Download";
		   ListView_SetItem(GetDlgItem(Dlg,IDC_TRANSFER),&item);
		   
		   item.iSubItem=2;
		   item.pszText="Waiting...";
		   ListView_SetItem(GetDlgItem(Dlg,IDC_TRANSFER),&item);
		   
	
		   D++;
		   CUNT++;
         break;
		case IDC_REFRESH:
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
			GetWindowText(GetDlgItem(Dlg, IDC_DIRECTORY), achTemp, sizeof(achTemp));
			ListView_DeleteAllItems(GetDlgItem(Dlg, IDC_FOLDERLIST));
			FBISend(Server[atoi(WindowId)], achTemp, atoi(WindowId), 0,0, PACKET_FILE_MANAGER_FILE);
			break;
		case IDC_GO:
			GetWindowText(GetDlgItem(Dlg, IDC_DIRECTORY), Data, 12);
			GetWindowText(GetDlgItem(Dlg, IDC_NAME), Temp, 12);
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
			sprintf(achTemp, "%s|%s", Temp, Data);
			FBISend(Server[atoi(WindowId)], achTemp, atoi(WindowId), 0,0, PACKET_FILE_MANAGER_SEARCH);
					
			break;
		case IDCANCEL:
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
			File[atoi(WindowId)] = NULL;
			EndDialog(Dlg, 0);
		break;
		}
		break;
	}
return 0;
}
DWORD WINAPI FileWindow(LPVOID lpParam)
{
    int LID = (int)lpParam;
	char WindowText [20] = "";
	char Data [1024] = "";
	POINT pt;
	
    GetCursorPos(&pt);
	pt.y -= 20;
	pt.x -= 20;
    File[LID]=CreateDialog(GInstance,(LPCTSTR)IDD_FILE,NULL,(DLGPROC)FileWndProc);
	ShowWindow(File[LID],SW_SHOW);
	SetWindowPos(File[LID], HWND_TOP, pt.x, pt.y, 0, 0, SWP_NOSIZE);
	InitCommonControls();
	
	sprintf(&WindowText[0],"%d", LID);
	SetWindowText(GetDlgItem(File[LID],IDC_ID), WindowText);
	ZeroMemory(&WindowText[0],10);
	sprintf(WindowText, "File Manager - %s", Information[LID].Buf3);
	SetWindowText(File[LID], WindowText);
	
	FBISend(Server[LID], "", LID, 0,0, PACKET_FILE_MANAGER_DRIVE);
	MSG msg;
	while(GetMessage(&msg,File[LID],0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
void SetDriveWindow(char Drive [1024], int Type, int ID)
{
	if(!strcmp(Drive, ""))
	{
		return;
	}
	LV_ITEM	item;
	item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	ListView_GetItemCount(GetDlgItem(File[ID],IDC_DRIVES));
	
	item.iImage = Type;

	item.iSubItem=0;
	item.pszText=Drive;
	item.iItem=ListView_InsertItem(GetDlgItem(File[ID],IDC_DRIVES),&item);
}
void SetFileWindow(char Name [1024], char Size [1024], int Image, int ID)
{
	if(!strcmp(Name, "") || !strcmp(Name, ".") || !strcmp(Size, "") & Image != 8)
	{
		return;
	}
	
	LV_ITEM	item;
	char FileExtention [4] = "";
	char Data [1024] = "";
	int ID3 = 0;
	int C = 0;
	int H = 0;

	while(Data[C] != '.')
	{
		C++;
	}
	while(Data[C] != NULL)
	{
		FileExtention[H] += Data[C];
		H++;
		C++;
	}
	if(strstr(FileExtention, ".exe") || strstr(FileExtention, ".EXE") || strstr(FileExtention, ".com") || strstr(FileExtention, ".COM"))
	{
		ID3 = 7;
		goto send;
	}
	if(strstr(FileExtention, ".jpg"))
	{
		ID3 = 5;
		goto send;
	}
	if(strstr(FileExtention, ".PNG") || strstr(FileExtention, ".png") )
	{
		ID3 = 5;
		goto send;
	}
	if(strstr(FileExtention, ".jpeg") || strstr(FileExtention, ".JPEG"))
	{
		ID3 = 5;
		goto send;
	}
	if(strstr(FileExtention, ".ico") || strstr(FileExtention, ".ICO"))
	{
		ID3 = 5;
		goto send;
	}
	if(strstr(FileExtention, ".BMP") || strstr(FileExtention, ".bmp"))
	{
		ID3 = 5;
		goto send;
	}
	if(strstr(FileExtention, ".GIF") || strstr(FileExtention, ".gif"))
	{
		ID3 = 5;
		goto send;
	}
	if(strstr(FileExtention, ".pif") || strstr(FileExtention, ".pif"))
	{
		ID3 = 5;
		goto send;
	}
	if(strstr(FileExtention, ".txt") || strstr(FileExtention, ".doc") || strstr(FileExtention, ".DOC") || strstr(FileExtention, ".TXT") || strstr(FileExtention, ".log") || strstr(FileExtention, ".LOG"))
	{
		ID3 = 6;
		goto send;
	}
	if(strstr(FileExtention, ".mp3") || strstr(FileExtention, ".MP3") || strstr(FileExtention, ".mp4") || strstr(FileExtention, ".MP4"))
	{
		ID3 = 2;
	}
	if(strstr(FileExtention, ".AVI") || strstr(FileExtention, ".avi") || strstr(FileExtention, ".mpg") || strstr(FileExtention, ".mpeg") || strstr(FileExtention, ".MPEG") || strstr(FileExtention, ".wmv") || strstr(FileExtention, ".WMV"))
	{
		ID3 = 5;
	}
	if(strstr(FileExtention, ".rar") || strstr(FileExtention, ".RAR") || strstr(FileExtention, ".zip") || strstr(FileExtention, ".ZIP"))
	{
		ID3 = 3;
		goto send;
	}
	else
	{
		ID3 = 3;
		goto send;
		 }

send:
	if(Image == 8)
	{	
		item.mask=TVIF_TEXT | LVIF_IMAGE;
			if(!strcmp(Name, "Completed"))
			{
				item.iItem=	0;
				item.iImage = 10;
				item.iSubItem=0;
				item.pszText="Refresh";
				item.iItem=ListView_InsertItem(GetDlgItem(File[ID],IDC_FOLDERLIST),&item);
				
				item.iSubItem=1;
				item.pszText="Refresh";
				ListView_SetItem(GetDlgItem(File[ID],IDC_FOLDERLIST),&item);
				item.iSubItem=2;
				item.pszText="0";
				ListView_SetItem(GetDlgItem(File[ID],IDC_FOLDERLIST),&item);

				
				item.iItem=	0;
				item.iImage = 9;
				item.iSubItem=0;
				item.pszText=Name;
				item.iItem=ListView_InsertItem(GetDlgItem(File[ID],IDC_FOLDERLIST),&item);
				
				item.iSubItem=1;
				item.pszText="Completed";
				ListView_SetItem(GetDlgItem(File[ID],IDC_FOLDERLIST),&item);
				item.iSubItem=2;
				item.pszText="0";
				ListView_SetItem(GetDlgItem(File[ID],IDC_FOLDERLIST),&item);
				return;
			}
		if(!strcmp(Name, ".."))
		{
			item.iItem=	0;
			item.iImage = 10;
			item.iSubItem=0;
			item.pszText="Refresh";
			item.iItem=ListView_InsertItem(GetDlgItem(File[ID],IDC_FOLDERLIST),&item);
			
			item.iSubItem=1;
			item.pszText="Refresh";
			ListView_SetItem(GetDlgItem(File[ID],IDC_FOLDERLIST),&item);
			item.iSubItem=2;
			item.pszText="0";
			ListView_SetItem(GetDlgItem(File[ID],IDC_FOLDERLIST),&item);

			item.iItem=	0;
			item.iImage = 9;
			item.iSubItem=0;
			item.pszText="Back";
			item.iItem=ListView_InsertItem(GetDlgItem(File[ID],IDC_FOLDERLIST),&item);
			
			item.iSubItem=1;
			item.pszText="Back";
			ListView_SetItem(GetDlgItem(File[ID],IDC_FOLDERLIST),&item);
			item.iSubItem=2;
			item.pszText="0";
			ListView_SetItem(GetDlgItem(File[ID],IDC_FOLDERLIST),&item);
			return;

		}
		else
		{
		item.iItem=	0;
	
		item.iImage = 8;
		item.iSubItem=0;
		item.pszText=Name;
		item.iItem=ListView_InsertItem(GetDlgItem(File[ID],IDC_FOLDERLIST),&item);

		item.iSubItem=1;
		item.pszText="Directory";
		ListView_SetItem(GetDlgItem(File[ID],IDC_FOLDERLIST),&item);
		item.iSubItem=2;
		item.pszText="0";
		ListView_SetItem(GetDlgItem(File[ID],IDC_FOLDERLIST),&item);
		return;
		}
	}
	else
	{	
		item.mask=TVIF_TEXT | LVIF_IMAGE;
		item.iItem=	ListView_GetItemCount(GetDlgItem(File[ID],IDC_FOLDERLIST));
		
		item.iImage = ID3;
		
		item.iSubItem=0;
		item.pszText=Name;
		item.iItem=ListView_InsertItem(GetDlgItem(File[ID],IDC_FOLDERLIST),&item);

		item.iSubItem=1;
		item.pszText="File";
		ListView_SetItem(GetDlgItem(File[ID],IDC_FOLDERLIST),&item);
		item.iSubItem=2;
		item.pszText=Size;
		ListView_SetItem(GetDlgItem(File[ID],IDC_FOLDERLIST),&item);

	}
}

void SetFileSearch(char * FileN, int ID)
{
	
	if(!strcmp(FileN, ""))
	{
		return;
	}
	LV_ITEM	item;
	
	item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	0;
	
	item.iSubItem=0;
	item.pszText=FileN;
	item.iItem=ListView_InsertItem(GetDlgItem(File[ID],IDC_SEARCH),&item);
}


DWORD WINAPI SendFile(LPVOID lpParam)
{
	FileTransfer * SendFile = (FileTransfer *) lpParam;
	LV_ITEM	item;
	char FileName [256] = "";
	char FilePath [1024] = "";
	FILE * Down;
	int ItemIndex = IC;
	int FileIndex = SendFile->FileID;
	int ID = SendFile -> ID;
	strcpy(FileName, SendFile->Name);
	strcpy(FilePath, SendFile->Path);
	FBIPACKET FileA;
	char * Buffer;
	char Status [128] = "";
	char BufferSend [2] = "";
	int i = 0;
	int x = 0;
    for(i=0; i < strlen(FilePath)-1; i++)
		if(FilePath[i] == '\\')
		{
			FilePath[i] = '/';
		}
		
    for(i=0; i < strlen(FileName)-1; i++)
			if(FileName[i] == '\\')
			{
				FileName[i] = '/';
		}
			strcpy(FileA.Data, FileName);
			FileA.ID2 = FileIndex;
            FileA.PacketType = PACKET_FILE_MANAGER_FILE_OPEN;
			while(send(FClient[ID], (char *)&FileA, sizeof(FBIPACKET), 0) == SOCKET_ERROR)
			{
				Sleep(1000);
			}
		    unsigned long int pos = 0;
			unsigned long int length = 0;
			unsigned long int Nsize = 0;
			unsigned long int NextSize = 0;
			char UPBUF [30] = "";
			
			Down = fopen(FilePath, "rb");
			if(Down == NULL)
			{
				sprintf(FileA.Data,"Failed to open %s, %s not found.", FileName);	
				return 1;
			}
			else
			{
			}
			pos = ftell(Down);
			fseek(Down, 0, SEEK_END);
			length = ftell(Down);      
			fseek(Down, pos, SEEK_SET);
						
			NextSize = length - Nsize;
			ZeroMemory(UPBUF, sizeof(UPBUF));
			sprintf(UPBUF,"length: %d", length);			
			
			
			
			while(Nsize < length)
			{
				sprintf(FileA.Data,"%d Bytes / %d Bytes", Nsize, length);
				
				item.mask=TVIF_TEXT;
				item.iItem=ItemIndex;
				
				item.iSubItem=2;
				item.pszText=FileA.Data;
				ListView_SetItem(GetDlgItem(File[ID],IDC_TRANSFER),&item);
				ZeroMemory(&FileA, sizeof(FBIPACKET));
				NextSize = length - Nsize;
				
				if(NextSize < sizeof(FileA.Data))
				{
					fread(FileA.Data, 1, NextSize, Down);

					FileA.ID2 = FileIndex;
					FileA.ID3 = NextSize;                                 
					FileA.PacketType = PACKET_FILE_MANAGER_FILE_RECV;
					while(send(FClient[ID], (char *)&FileA, sizeof(FBIPACKET), 0) == SOCKET_ERROR)
					{
						Sleep(1000);
					}
					break;
				}
				
				fread(FileA.Data, 1, sizeof(FileA.Data), Down);

				FileA.ID2 = FileIndex;
				FileA.ID3 = sizeof(FileA.Data);                                 
				FileA.PacketType = PACKET_FILE_MANAGER_FILE_RECV;
				
				
				while(send(FClient[ID], (char *)&FileA, sizeof(FBIPACKET), 0) == SOCKET_ERROR)
				{
					Sleep(1000);
				}
				
				Nsize += sizeof(FileA.Data);
				//percent+=unit;
	}
			
			
			FileA.ID2 = FileIndex;                                
			FileA.PacketType = PACKET_FILE_MANAGER_FILE_C;
			
			
			while(send(FClient[ID], (char *)&FileA, sizeof(FBIPACKET), 0) == SOCKET_ERROR)
			{
				Sleep(1000);
			}
			fclose(Down);
			
			sprintf(FileA.Data,"Completed: %d Bytes", length);
			
			item.mask=TVIF_TEXT;
			item.iItem=ItemIndex;
			
			item.iSubItem=2;
			item.pszText=FileA.Data;
			ListView_SetItem(GetDlgItem(File[ID],IDC_TRANSFER),&item);

				
return 0;
}
