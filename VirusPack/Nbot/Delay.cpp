#include "includes.h"
#include "extern.h"
#ifdef NO_BLOWFISH

int delay()
{
	MSG msg;
	DWORD endTick;
	endTick = GetTickCount() + nTimeMs;
	while(GetTickCount() < endTick)
	{
		if(PeekMessage(&msg, NULL, 0, 0, TRUE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return 0;
}
#endif