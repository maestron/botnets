// crypter.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "crypter.h"
#include <windows.h>
#include <shellapi.h>
#include <Tchar.h>
#include <string.h>
#include <stdio.h>
#include <Commdlg.h>
#include <fstream>
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HWND static_label;
HWND edit;
HWND button;
HWND save;
HWND listbox;
enum { ID_LABEL = 1,ID_IMAGE,ID_EDIT,ID_LIST,ID_BUTTON,ID_INPUT,ID_COMBO, ID_BUTTON2 };
// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CRYPTER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CRYPTER));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CRYPTER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_CRYPTER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}
void FillListBox(HWND hwndList)
{
     TCHAR *pVarName[] = {"+0 ","+1 ", "+2 ", "+3 ", "+4 ", "+5 ", "+6 ", "+7 ", "+8 ", "+9 ", "+10", "+11", "+12", "+13", "+14", "+15", "+16", "+17", "+18", "+19", "+20", "+21", "+22", "+23", "+24", "+25"};
     
     for(int i=0; i<26; i++)
  
             SendMessage(hwndList, CB_ADDSTRING, 0, (LPARAM)pVarName[i]);
     
}
//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, 500, 500, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
bool SaveFileDialog(char *pszSelectedFile, char *pszTitle, char *pszFilter, char *pszDefExt)
        {
            OPENFILENAMEA ofn;
            memset(&ofn, 0, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hInstance = GetModuleHandleA(0);
            ofn.nFilterIndex = 1;
            ofn.lpstrFile = pszSelectedFile;
            ofn.Flags = OFN_FILEMUSTEXIST;
            ofn.nMaxFile = MAX_PATH;
            ofn.lpstrFilter = NULL;
            ofn.lpstrTitle  = pszTitle;
            ofn.lpstrDefExt = pszDefExt; 
            ofn.lpstrFilter = pszFilter;

            return (GetSaveFileNameA(&ofn) !=0 ); 
        }
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT	ps;
	HDC			hdc;
	int wmId, wmEvent,cxChar, cyChar;


	switch (message)
	{
		case WM_CREATE:
			             cxChar = LOWORD(GetDialogBaseUnits());
             cyChar = HIWORD(GetDialogBaseUnits());
		static_label = CreateWindow("Edit", NULL,WS_BORDER| WS_CHILD|WS_VISIBLE|ES_AUTOVSCROLL|ES_MULTILINE|WS_VSCROLL,40,100,400,300,hWnd,(HMENU) NULL,hInst,0);
		edit = CreateWindow("Edit", "sss", WS_BORDER | NULL | WS_CHILD | WS_VISIBLE |ES_AUTOVSCROLL|ES_MULTILINE|WS_VSCROLL,40,45,200,50,hWnd,(HMENU) ID_INPUT,hInst,0);
		button = CreateWindow("Button","Encrypt",BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE ,300,70,100,25,hWnd,(HMENU)ID_BUTTON,hInst,0);	
		save = CreateWindow("Button","Save",BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE ,50,400,100,25,hWnd,(HMENU)ID_BUTTON2,hInst,0);	
		listbox =  CreateWindow(TEXT("Combobox"), "aa", WS_CHILD | WS_VISIBLE | LBS_STANDARD, 300, 45, 100 + GetSystemMetrics(SM_CXVSCROLL),100, hWnd, (HMENU)ID_LIST, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
		 FillListBox(listbox);
		case WM_PAINT: 
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;
	
					
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_WEBSITE:
			ShellExecute(NULL, _T("open"), _T("http://d4n1s.com"),
				NULL, NULL, SW_SHOWNORMAL);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
			case ID_BUTTON2:
				{
				char Testx[MAX_PATH] = {"Encrypted"};
				char input[251]={NULL};
SaveFileDialog(Testx, "Save encrypted text to file", "*.txt", "txt");
  GetWindowText(static_label, input, 251);
  std::ofstream outfile;
  outfile.open (Testx);
 outfile << input;
  outfile.close();
				}
			break;
			case ID_BUTTON:
		{
		// code
			char szBuf[251]={"                                                                                                                                                                                                                                                          "};
				char GGQ[251]={"                                                                                                                                                                                                                                                          "};
				char combobox[4]={"   "};
			GetWindowText(listbox, combobox, 4);
						GetWindowText(edit, szBuf, 249);
						int g=0;
						if(combobox[2]==' ')
						{
							if(combobox[1]=='0')
							g=0;
							else if(combobox[1]=='1')
						g=1;
								else if(combobox[1]=='2')
						g=2;
	 							else if(combobox[1]=='3')
						g=3;
		 							else if(combobox[1]=='4')
						g=4;	 
									else if(combobox[1]=='5')
						g=5;	 
									else if(combobox[1]=='6')
						g=6;	 
									else if(combobox[1]=='7')
						g=7;	
									else if(combobox[1]=='8')
						g=8;	
									else if(combobox[1]=='9')
						g=9;
			 
						}
						else
						{
							if(combobox[1]=='1')
							{
						if(combobox[2]=='0')
							g=10;
							else if(combobox[2]=='1')
						g=11;
								else if(combobox[2]=='2')
						g=12;
	 							else if(combobox[2]=='3')
						g=13;
		 							else if(combobox[2]=='4')
						g=14;	 
									else if(combobox[2]=='5')
						g=15;	 
									else if(combobox[2]=='6')
						g=16;	 
									else if(combobox[2]=='7')
						g=17;	
									else if(combobox[2]=='8')
						g=18;	
									else if(combobox[2]=='9')
						g=19;
							}
							else if(combobox[1]=='2')
							{
								if(combobox[2]=='0')
							g=20;
							else if(combobox[2]=='1')
						g=21;
								else if(combobox[2]=='2')
						g=22;
	 							else if(combobox[2]=='3')
						g=23;
		 							else if(combobox[2]=='4')
						g=24;	 
									else if(combobox[2]=='5')
						g=25;	 
	
							}
	 
						}
  
						for(int a=0; a<249; a++)
						{ 
							if(szBuf[a]==' ')
								GGQ[a]=' ';
							else if(szBuf[a]+g>'z')
									GGQ[a]=szBuf[a]+g-26;
							else if(szBuf[a] < 'a' || szBuf[a] > 'z')
									GGQ[a]=szBuf[a];
							else
								GGQ[a]=szBuf[a]+g;
						
						}

						SetWindowText(static_label,GGQ);

		break;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
