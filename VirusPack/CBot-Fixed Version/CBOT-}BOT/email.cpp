#include "Include.h"
#include "Hell.h"
/*
#ifndef NO_EMAIL

DWORD WINAPI SearchEmail(LPVOID param) {
	int threadnum = (int)param;
	HANDLE tHandle;
	DWORD tid;
	
	MassMailInit();
	tHandle = CreateThread(NULL, 0, &MassMailThread, NULL, 0, &tid);
	if (!tHandle) return (EXIT_FAILURE);
	
	SearchInit();
	Search(); 
	
	clearthread(threadnum);
	ExitThread(EXIT_SUCCESS);
}

#endif*/