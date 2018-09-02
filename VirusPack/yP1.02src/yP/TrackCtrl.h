/* TrackCtrl.h --
  
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
#pragma once

#include "resource.h"

extern HWND		hwndTrack;

extern CHAR lpszSectionName[16]; 

HWND WINAPI CreateTrackbar( 
    HWND hwndDlg	// handle of dialog box (parent window) 
	);

VOID WINAPI TBNotifications( 
    WPARAM wParam,	// wParam of WM_HSCROLL message 
    HWND hwndTrack	// handle of trackbar window 
	);
