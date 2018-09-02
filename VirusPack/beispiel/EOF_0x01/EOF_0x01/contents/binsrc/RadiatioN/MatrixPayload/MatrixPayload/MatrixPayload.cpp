// MatrixPayload.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MatrixPayload.h"

HFONT BuildFont(wchar_t *wszFontFace, int nFontSize, BOOL fBold)
{
	HDC hDC;
	int nHeight;

	hDC = GetDC(NULL);
	nHeight = -MulDiv(nFontSize, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	ReleaseDC(NULL, hDC);

	return CreateFont(nHeight,
						0,
						0,
						0,
						fBold ? FW_BOLD: FW_NORMAL,
						0,
						0,
						0,
						DEFAULT_CHARSET,
						OUT_DEFAULT_PRECIS,
						CLIP_DEFAULT_PRECIS,
						DEFAULT_QUALITY,
						DEFAULT_PITCH,
						wszFontFace);
} 

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	wchar_t wszTemp[512]=TEXT("A");
	HDC dc;
	COLORREF crBlack = RGB(0, 0, 0), crGreen = RGB(73, 144, 66);
	HPEN hPen;
	HBRUSH hBrush;
	DWORD dwStart, dwRandomAdd, dwLastDraw, dwLastRedraw;
	int iPositionArray[MATRIX_ELEMENTS][5], iScreenX, iScreenY, iRasterX=24, iRasterY=32, iRandomDelay=1503;

	srand(GetTickCount());
	for(int i=0; i<MATRIX_ELEMENTS; i++)
	{
		iPositionArray[i][0]=-1;
		iPositionArray[i][1]=-1;
		iPositionArray[i][2]=-1;
	}

	dc = GetDC(NULL);

	iScreenX=GetSystemMetrics(SM_CXSCREEN);
	iScreenY=GetSystemMetrics(SM_CYSCREEN);

	hPen = CreatePen(PS_SOLID, 1, crBlack);
	hBrush = CreateSolidBrush(crBlack);
	SelectObject(dc, hPen);
	SelectObject(dc, hBrush);

	SetBkMode(dc, OPAQUE);
	SetBkColor(dc, crBlack);
	SetTextColor(dc, crGreen);

	SelectObject(dc, BuildFont(TEXT("Lucida Console"), 30, true));

	dwStart=GetTickCount();
	dwRandomAdd=dwStart;
	dwLastDraw=dwStart;
	dwLastRedraw=dwStart;

	BlockInput(true);
	SetCursorPos(iScreenX, iScreenY);

	while(dwStart+60000>GetTickCount())
	{		
		if(dwLastDraw+80<GetTickCount())
		{
			Rectangle(dc, 0, 0, iScreenX, iScreenY);
			
			for(int i=0; i<MATRIX_ELEMENTS; i++)
			{
				if(iPositionArray[i][2]==1)
				{
					for(int c=0; c<iPositionArray[i][3]; c++)
					{
						wszTemp[0]=rand()%253+1;
						TextOut(dc, iPositionArray[i][0], iPositionArray[i][1]+(c*(iScreenY/iRasterY)), wszTemp, 1);
					}
					iPositionArray[i][1]+=(iScreenY/iRasterY);

					if(iPositionArray[i][1]>iScreenY)
					{
						iPositionArray[i][2]=-1;
					}
				}
			}
			dwLastDraw=GetTickCount();
		}

		if(dwRandomAdd+iRandomDelay<GetTickCount())
		{
			for(int i=0; i<MATRIX_ELEMENTS; i++)
			{
				if(iPositionArray[i][2]==-1)
				{
					iPositionArray[i][0]=(rand()%(iScreenX/iRasterX))*iRasterX;
					iPositionArray[i][1]=(rand()%(iScreenY/iRasterY))*iRasterY;
					iPositionArray[i][2]=1;
					iPositionArray[i][3]=(rand()%10)+3;

					break;
				}
			}

			dwRandomAdd=GetTickCount();
			if(iRandomDelay>5)iRandomDelay-=(iRandomDelay/5);
		}
	}

	BlockInput(false);
	InvalidateRect(NULL, NULL, true);
	
	ReleaseDC(NULL, dc);
	
	return 0;
}
