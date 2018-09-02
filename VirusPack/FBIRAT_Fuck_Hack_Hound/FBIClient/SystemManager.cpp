#include "Main.h"
#include "resource.h"
#include "PacketHead.h"

void SystemResize(HWND hwnd)
{
RECT rc;

GetClientRect(hwnd, &rc);
MoveWindow(GetDlgItem(hwnd, IDC_SYSTEMTAB), 0, 0, rc.right, rc.bottom - 20, TRUE);
MoveWindow(GetDlgItem(hwnd, IDC_PROCESSES), 0,25, rc.right - 10, rc.bottom - 50, TRUE);
MoveWindow(GetDlgItem(hwnd, IDC_WINDOWS), 0,25, rc.right - 10, rc.bottom - 50, TRUE);
MoveWindow(GetDlgItem(hwnd, IDC_INSTALLED), 0,25, rc.right - 10, rc.bottom - 50, TRUE);
MoveWindow(GetDlgItem(hwnd, IDC_SERVICES), 0,25, rc.right - 10, rc.bottom - 50, TRUE);
//MoveWindow(GetDlgItem(hwnd, IDC_SYSTEM_STATUS), 0,rc.bottom - 20, rc.right, 20, TRUE);
}
LRESULT CALLBACK SystemWndProc(HWND Dlg,UINT Mes,WPARAM wParam,LPARAM lParam)
{
	TCITEM tie;
	LV_COLUMN	col;
	LV_ITEM		item;	
	HMENU hmenu;            // menu template          
    HMENU hmenuTrackPopup;  // shortcut menu   
    POINT  pt;   // location of mouse click 
	char WindowId [12] = "";
	char Data [256] = "";
	DWORD thread;
	HICON hIcon;
	HIMAGELIST hImageList;
	switch(Mes)
	{
	case WM_INITDIALOG:
		
		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0);
		SendMessage(Dlg, WM_SETICON,ICON_SMALL,(LPARAM)hIcon);
		DeleteObject(hIcon);
		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 64, 64, 0);
		SendMessage(Dlg, WM_SETICON,ICON_BIG,(LPARAM)hIcon);

		tie.mask = TCIF_TEXT | TCIF_IMAGE;  
		tie.pszText = "Process Manager";
	
		TabCtrl_InsertItem(GetDlgItem(Dlg, IDC_SYSTEMTAB), 0, &tie);

		tie.mask = TCIF_TEXT | TCIF_IMAGE;  
		tie.pszText = "Window Manager";
	
		TabCtrl_InsertItem(GetDlgItem(Dlg, IDC_SYSTEMTAB), 1, &tie);

		tie.mask = TCIF_TEXT | TCIF_IMAGE;  
		tie.pszText = "Installed Programs";
	
		TabCtrl_InsertItem(GetDlgItem(Dlg, IDC_SYSTEMTAB), 2, &tie);

		tie.mask = TCIF_TEXT | TCIF_IMAGE;  
		tie.pszText = "Installed Services";
	
		TabCtrl_InsertItem(GetDlgItem(Dlg, IDC_SYSTEMTAB), 3, &tie);
		/////////////////////////////////////////////////////////////
		//initiating list.
	    ListView_SetExtendedListViewStyle(GetDlgItem(Dlg,IDC_PROCESSES),LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		col.mask=LVCF_TEXT|LVCF_WIDTH|LVIF_IMAGE;
		col.cx=150;

		col.pszText="Process";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_PROCESSES),0,&col);
		col.cx=100;
		col.pszText="PID";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_PROCESSES),1,&col);
		col.cx=100;
		col.pszText="Threads";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_PROCESSES),2,&col);
		col.cx=100;
		col.pszText="Parent PID";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_PROCESSES),3,&col);
		col.cx=100;
		col.pszText="priority";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_PROCESSES),4,&col);
///////////////////////////////////////////////////////////////////////
	    ListView_SetExtendedListViewStyle(GetDlgItem(Dlg,IDC_WINDOWS),LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		col.mask=LVCF_TEXT|LVCF_WIDTH|LVIF_IMAGE;
		col.cx=300;

		col.pszText="Window";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_WINDOWS),0,&col);
		col.cx=100;
		col.pszText="ID";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_WINDOWS),1,&col);
///////////////////////////////////////////////////////////////////////
		ListView_SetExtendedListViewStyle(GetDlgItem(Dlg,IDC_INSTALLED),LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		col.mask=LVCF_TEXT|LVCF_WIDTH|LVIF_IMAGE;
		col.cx=100;

		col.pszText="Program";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_INSTALLED),0,&col);
		col.cx=300;
		col.pszText="Path";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_INSTALLED),1,&col);
///////////////////////////////////////////////////////////////////////
		ListView_SetExtendedListViewStyle(GetDlgItem(Dlg,IDC_SERVICES),LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		col.mask=LVCF_TEXT|LVCF_WIDTH|LVIF_IMAGE;
		col.cx=150;

		col.pszText="Service Name";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_SERVICES),0,&col);
		col.cx=100;
		col.pszText="Display Name";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_SERVICES),1,&col);
		col.cx=100;
		col.pszText="Status";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_SERVICES),2,&col);
		col.cx=100;
		col.pszText="Start Up Type";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_SERVICES),3,&col);
		SystemResize(Dlg);

		ShowWindow(GetDlgItem(Dlg, IDC_WINDOWS),SW_HIDE);
		ShowWindow(GetDlgItem(Dlg, IDC_INSTALLED),SW_HIDE);
		ShowWindow(GetDlgItem(Dlg, IDC_SERVICES),SW_HIDE);
		hImageList=ImageList_Create(16,16,ILC_COLOR16,20,30);
		ImageList_SetBkColor(hImageList,CLR_NONE);// Macro: 16x16:16bit with 2 pics [array]
		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_EXE), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
		ImageList_AddIcon(hImageList, hIcon);							      // Macro: Attach the image, to the image list
		DeleteObject(hIcon);
		
		ListView_SetImageList(GetDlgItem(Dlg, IDC_INSTALLED),hImageList, LVSIL_SMALL);
		ListView_SetImageList(GetDlgItem(Dlg, IDC_WINDOWS),hImageList, LVSIL_SMALL);
		ListView_SetImageList(GetDlgItem(Dlg, IDC_PROCESSES),hImageList, LVSIL_SMALL);
		break;

		case WM_SIZING:
			switch(wParam)
			{
			case WMSZ_BOTTOM:
				SystemResize(Dlg);
			break;
			case WMSZ_BOTTOMLEFT:
				SystemResize(Dlg);
			break;
			case WMSZ_BOTTOMRIGHT:
				SystemResize(Dlg);
			break;
			case WMSZ_LEFT:
				SystemResize(Dlg);
            break;
			case WMSZ_RIGHT:
				SystemResize(Dlg);
			break;
			case WMSZ_TOP:
				SystemResize(Dlg);
			break;
			case WMSZ_TOPLEFT:
				SystemResize(Dlg);
			break;
			case WMSZ_TOPRIGHT:
				SystemResize(Dlg);
			break;
			}
			break;
			case WM_NOTIFY:
		switch(wParam)
		{
		case IDC_SYSTEMTAB:
            switch (((LPNMHDR)lParam)->code)
            {
            case TCN_SELCHANGE:
                   int iPage = TabCtrl_GetCurSel(GetDlgItem(Dlg, IDC_SYSTEMTAB)); 
                   switch(iPage)
					{
					 case 0:
					 ShowWindow(GetDlgItem(Dlg, IDC_WINDOWS), FALSE);
					 
					 ShowWindow(GetDlgItem(Dlg, IDC_INSTALLED), FALSE);				 
					 ShowWindow(GetDlgItem(Dlg, IDC_SERVICES), FALSE);
					 ShowWindow(GetDlgItem(Dlg, IDC_PROCESSES), TRUE);
					 break;

					 case 1:
					 ShowWindow(GetDlgItem(Dlg, IDC_PROCESSES), FALSE);
					 ShowWindow(GetDlgItem(Dlg, IDC_INSTALLED), FALSE);				 
					 ShowWindow(GetDlgItem(Dlg, IDC_SERVICES), FALSE);
					 ShowWindow(GetDlgItem(Dlg, IDC_WINDOWS), TRUE);
					 GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
					 if(ListView_GetItemCount(GetDlgItem(System[atoi(WindowId)],IDC_WINDOWS)) == 0)
					 {
						 
					FBISend(Server[atoi(WindowId)], Data, atoi(WindowId), 0,0, PACKET_TASK_MANAGER_TASKS);
					 }
					 break;

					 case 2:
					 ShowWindow(GetDlgItem(Dlg, IDC_PROCESSES), FALSE);					 
					 ShowWindow(GetDlgItem(Dlg, IDC_WINDOWS), FALSE);			 
					 ShowWindow(GetDlgItem(Dlg, IDC_SERVICES), FALSE);
					 ShowWindow(GetDlgItem(Dlg, IDC_INSTALLED), TRUE);	
					 GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
					 if(ListView_GetItemCount(GetDlgItem(System[atoi(WindowId)],IDC_INSTALLED)) == 0)
					 {
						 
						 FBISend(Server[atoi(WindowId)], Data, atoi(WindowId), 0,0, PACKET_PROGRAM_FILES);
					 }
					 break;

					 case 3:
					 ShowWindow(GetDlgItem(Dlg, IDC_PROCESSES), FALSE);					 
					 ShowWindow(GetDlgItem(Dlg, IDC_WINDOWS), FALSE);
					 ShowWindow(GetDlgItem(Dlg, IDC_INSTALLED), FALSE);				 
					 ShowWindow(GetDlgItem(Dlg, IDC_SERVICES), TRUE);
					 GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
					 if(ListView_GetItemCount(GetDlgItem(System[atoi(WindowId)],IDC_SERVICES)) == 0)
					 {
						 FBISend(Server[atoi(WindowId)], Data, atoi(WindowId), 0,0, PACKET_SERVICE_MAN);						 
					 }
					 break;
					}
				
				break;
			}
					break;
	case IDC_PROCESSES:
        if(((LPNMHDR)lParam)->code == NM_RCLICK) // Right Click
			{	 
            // Get the client coordinates for the mouse click.
			  pt.x = 0;
			  pt.y = 0;
			  GetCursorPos(&pt);
		
            // If the mouse click took place inside the client 
            // area, execute the application-defined function 
            // that displays the shortcut menu. 

        
			hmenu = LoadMenu(GInstance, MAKEINTRESOURCE(IDR_TASK));

			if (hmenu == NULL) 
			{
             break;
			}
 
			hmenuTrackPopup = GetSubMenu(hmenu, 0); 

            //ClientToScreen(Dlg, (LPPOINT) &pt);   
 
            TrackPopupMenu(hmenuTrackPopup, TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, 0, Dlg, NULL);
            }
			break;

	case IDC_WINDOWS:
        switch(((LPNMHDR)lParam)->code) // Right Click
			{	 
		case  NM_RCLICK:
            // Get the client coordinates for the mouse click.
			  pt.x = 0;
			  pt.y = 0;
			  GetCursorPos(&pt);
		
            // If the mouse click took place inside the client 
            // area, execute the application-defined function 
            // that displays the shortcut menu. 

        
			hmenu = LoadMenu(GInstance, MAKEINTRESOURCE(IDR_WIN));

			if (hmenu == NULL) 
			{
             break;
			}
 
			hmenuTrackPopup = GetSubMenu(hmenu, 0); 

            //ClientToScreen(Dlg, (LPPOINT) &pt);   
 
            TrackPopupMenu(hmenuTrackPopup, TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, 0, Dlg, NULL);
            
		break;
		case NM_CLICK:
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
			EndDialog(Rename[atoi(WindowId)], 0);
			break;

			}
		break;
	case IDC_INSTALLED:
        if(((LPNMHDR)lParam)->code == NM_RCLICK) // Right Click
		{	 
            // Get the client coordinates for the mouse click.
			pt.x = 0;
			pt.y = 0;
			GetCursorPos(&pt);
			
            // If the mouse click took place inside the client 
            // area, execute the application-defined function 
            // that displays the shortcut menu. 
			
			
			hmenu = LoadMenu(GInstance, MAKEINTRESOURCE(IDR_INSTALLED));
			
			if (hmenu == NULL) 
			{
				break;
			}
			
			hmenuTrackPopup = GetSubMenu(hmenu, 0); 
			
            //ClientToScreen(Dlg, (LPPOINT) &pt);   
			
            TrackPopupMenu(hmenuTrackPopup, TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, 0, Dlg, NULL);
		}
		break;
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
		break;
		}
		break;
	case WM_COMMAND:
		switch(wParam)
		{
		case IDC_KILL:			
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_PROCESSES),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Data;
			item.cchTextMax=sizeof(Data);
			ListView_GetItem(GetDlgItem(Dlg,IDC_PROCESSES),&item);  
			ListView_DeleteItem(GetDlgItem(Dlg, IDC_PROCESSES),ListView_GetNextItem(GetDlgItem(Dlg,IDC_PROCESSES),-1,LVNI_SELECTED));
			FBISend(Server[atoi(WindowId)], Data, atoi(WindowId), 0,0, PACKET_TASK_MANAGER_KILL);
			break;
		case IDC_REFRESH:			
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
			ListView_DeleteAllItems(GetDlgItem(Dlg, IDC_PROCESSES));
			FBISend(Server[atoi(WindowId)], Data, atoi(WindowId), 0,0, PACKET_TASK_MANAGER);
			break;
		case IDC_REFRESHS:
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
			ListView_DeleteAllItems(GetDlgItem(Dlg, IDC_SERVICES));
			FBISend(Server[atoi(WindowId)], Data, atoi(WindowId), 0,0, PACKET_SERVICE_MAN);
			break;
		case IDC_REFRESHP:
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
			ListView_DeleteAllItems(GetDlgItem(Dlg, IDC_INSTALLED));
			FBISend(Server[atoi(WindowId)], Data, atoi(WindowId), 0,0, PACKET_PROGRAM_FILES);
			break;
		case IDC_REFRESHT:
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
			ListView_DeleteAllItems(GetDlgItem(Dlg, IDC_WINDOWS));
			FBISend(Server[atoi(WindowId)], Data, atoi(WindowId), 0,0, PACKET_TASK_MANAGER_TASKS);
			break;
		case IDC_CLOSE:
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_WINDOWS),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Data;
			item.cchTextMax=sizeof(Data);
			ListView_GetItem(GetDlgItem(Dlg,IDC_WINDOWS),&item);  
			ListView_DeleteItem(GetDlgItem(Dlg, IDC_WINDOWS),ListView_GetNextItem(GetDlgItem(Dlg,IDC_WINDOWS),-1,LVNI_SELECTED));
			FBISend(Server[atoi(WindowId)], Data, atoi(WindowId), 0,0, PACKET_TASK_MANAGER_TKILL);
			break;
		case IDC_STOP:
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVICES),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Data;
			item.cchTextMax=sizeof(Data);
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVICES),&item);  
			FBISend(Server[atoi(WindowId)], Data, atoi(WindowId), 0,0, PACKET_SERVICE_STOPA);			
			break;
		case IDC_START:
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVICES),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Data;
			item.cchTextMax=sizeof(Data);
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVICES),&item);  

			FBISend(Server[atoi(WindowId)], Data, atoi(WindowId), 0,0, PACKET_SERVICE_STARTA);			
			break;
		case IDCANCEL:
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
			System[atoi(WindowId)] = NULL;
			EndDialog(Dlg, 0);
			EndDialog(Rename[atoi(WindowId)], 0);

		break;
		}
		break;
	}
return 0;
}
DWORD WINAPI SystemWindow(LPVOID lpParam)
{
	int LID = (int)lpParam;
	char WindowText [50] = "";
    char TID [12] = "";
	System[LID]=CreateDialog(SysInst,(LPCTSTR)IDD_SYSTEMMANAGER,NULL,(DLGPROC)SystemWndProc);
	ShowWindow(System[LID],SW_SHOW);
	ShowWindow(GetDlgItem(System[LID], IDC_ID),SW_HIDE);
	
	sprintf(WindowText, "System Manager - %s", Information[LID].Buf3);
	SetWindowText(System[LID], WindowText);

	sprintf(TID, "%d", LID);
	SetWindowText(GetDlgItem(System[LID], IDC_ID), TID);

	MSG msg;
	InitCommonControls();
	FBISend(Server[LID],"", LID, 0, 0, PACKET_TASK_MANAGER);
	while(GetMessage(&msg,System[LID],0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
return 0;
}

void SetProcess(char * Proc, char * PID, char * Threads, char * PPID, char * Priority, int ID)
{
if(!strcmp(Proc, "") || !strcmp(PID, "") || !strcmp(Threads, "") || !strcmp(PPID, "") || !strcmp(Priority, ""))
{
return;
}
    LV_ITEM	item;
	item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	ListView_GetItemCount(GetDlgItem(System[ID],IDC_PROCESSES));
	item.iImage = 0;

	item.iSubItem=0;
	item.pszText=Proc;
	item.iItem=ListView_InsertItem(GetDlgItem(System[ID],IDC_PROCESSES),&item);

	item.iSubItem=1;
	item.pszText=PID;
	ListView_SetItem(GetDlgItem(System[ID],IDC_PROCESSES),&item);
	
	item.iSubItem=2;
	item.pszText=Threads;
	ListView_SetItem(GetDlgItem(System[ID],IDC_PROCESSES),&item);
		
	item.iSubItem=3;
	item.pszText=PPID;
	ListView_SetItem(GetDlgItem(System[ID],IDC_PROCESSES),&item);

	item.iSubItem=4;
	item.pszText=Priority;
	ListView_SetItem(GetDlgItem(System[ID],IDC_PROCESSES),&item);
///////////////////////////////////////////////////////////////
}
void SetWindow(char * Window, int ID2, int ID)
{
	LV_ITEM	item;
	if(!strcmp(Window, ""))
	{
		return;
	}
	switch(ID2)
	{
	case 1:
	item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	0;	
	item.iImage = 0;

	item.iSubItem=0;
	item.pszText=Window;
	item.iItem=ListView_InsertItem(GetDlgItem(System[ID],IDC_WINDOWS),&item);

	item.iSubItem=1;
	item.pszText="Displayed";
	ListView_SetItem(GetDlgItem(System[ID],IDC_WINDOWS),&item);
	break;
	case 2:	
	item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	ListView_GetItemCount(GetDlgItem(System[ID],IDC_WINDOWS));
	item.iImage = 0;

	item.iSubItem=0;
	item.pszText=Window;
	item.iItem=ListView_InsertItem(GetDlgItem(System[ID],IDC_WINDOWS),&item);

	item.iSubItem=1;
	item.pszText="Hidden";
	ListView_SetItem(GetDlgItem(System[ID],IDC_WINDOWS),&item);
	break;
	}
}
void SetServiceGui(char * ServiceName, char * DisplayName, char * Status, char * StartType, int ID2, int ID)
{
	if(!strcmp(ServiceName, "") || !strcmp(DisplayName, "") || !strcmp(Status, "") || !strcmp(StartType, ""))
	{
	return;
	}
	LV_ITEM	item;
	switch(ID2)
	{
	case 1:
	item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	0;
	break;
	case 2:
	item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	ListView_GetItemCount(GetDlgItem(System[ID],IDC_SERVICES));
	break;
	}
	item.iSubItem=0;
	item.pszText=ServiceName;
	item.iItem=ListView_InsertItem(GetDlgItem(System[ID],IDC_SERVICES),&item);
	item.iSubItem=1;
	item.pszText=DisplayName;
	ListView_SetItem(GetDlgItem(System[ID],IDC_SERVICES),&item);
	item.iSubItem=2;
	item.pszText=Status;
	ListView_SetItem(GetDlgItem(System[ID],IDC_SERVICES),&item);
	item.iSubItem=3;
	item.pszText=StartType;
	ListView_SetItem(GetDlgItem(System[ID],IDC_SERVICES),&item);
}
void SetProgramGui(char * Path, char * Program, int ID)
{
	if(!strcmp(Path, "") || !strcmp(Program, ""))
	{
	return;
	}
	LV_ITEM	item;
	item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	ListView_GetItemCount(GetDlgItem(System[ID],IDC_INSTALLED));

	item.iSubItem=0;
	item.pszText=Program;
	item.iItem=ListView_InsertItem(GetDlgItem(System[ID],IDC_INSTALLED),&item);
	item.iSubItem=1;
	item.pszText=Path;
	ListView_SetItem(GetDlgItem(System[ID],IDC_INSTALLED),&item);
}