/* TrackCtrl.cpp : Defines the entry point for the application.

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
#include <commdlg.h>
#include <commctrl.h>
#include <shellapi.h>
#include <winuser.h>

HWND	hwndTrack;

UINT iPageSize=1;
UINT iMin=1;	// minimum value in trackbar range 
UINT iMax=10;	// maximum value in trackbar range 
UINT iSelMin=1;	// minimum value in trackbar selection 
UINT iSelMax=10;	// maximum value in trackbar selection 

// CreateTrackbar - creates and initializes a trackbar. 
// 
// Global variable 
//     g_hinst - instance handle 
HWND WINAPI CreateTrackbar( 
    HWND hwndDlg	// handle of dialog box (parent window) 
	)
{ 

	hwndTrack=GetDlgItem(hwndDlg, IDC_COMPRESSLEVEL); 

	SendMessage(hwndTrack, TBM_SETRANGE, 
			(WPARAM) TRUE,					// redraw flag 
			(LPARAM) MAKELONG(iMin, iMax)); // min. & max. positions 

	SendMessage(hwndTrack, TBM_SETPAGESIZE, 
			0, (LPARAM) iPageSize);			// new page size 

	SendMessage(hwndTrack, TBM_SETSEL, 
			(WPARAM) FALSE,					// redraw flag 
			(LPARAM) MAKELONG(iSelMin, iSelMax)); 

	SendMessage(hwndTrack, TBM_SETPOS, 
			(WPARAM) TRUE,					// redraw flag 
			(LPARAM) dwCompressLevel); 
    //SetFocus(hwndTrack); 

    return hwndTrack; 
} 

// TBNotifications - handles trackbar notifications received 
// in the wParam parameter of WM_HSCROLL. This function simply 
// ensures that the slider remains within the selection range. 

VOID WINAPI TBNotifications( 
    WPARAM wParam,  // wParam of WM_HSCROLL message 
    HWND hwndTrack) // handle of trackbar window 
    { 
    switch (LOWORD(wParam)) { 
        case TB_ENDTRACK: 
            dwCompressLevel = SendMessage(hwndTrack, TBM_GETPOS, 0, 0); 
            if (dwCompressLevel > iSelMax) 
                SendMessage(hwndTrack, TBM_SETPOS, 
                    (WPARAM) TRUE,       // redraw flag 
                    (LPARAM) iSelMax); 
            else if (dwCompressLevel < iSelMin) 
                SendMessage(hwndTrack, TBM_SETPOS, 
                    (WPARAM) TRUE,       // redraw flag 
                    (LPARAM) iSelMin); 
            break; 

        default: 
            break; 

        } 
} 