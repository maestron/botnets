#pragma comment(lib, "Version")
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "ver.h"

int tcpipVersion(char *szPath) {

	//no version checked: return 0
	//version 2600.2180: return 1
	//version 2600.2892: return 2
	//other versions: return 0

	DWORD dwHandle, dwLen;
	UINT BufLen;
	LPTSTR lpData;
	VS_FIXEDFILEINFO *pFileInfo;

	dwLen = GetFileVersionInfoSize (szPath, &dwHandle);
	if (!dwLen) {
		return 0;
	}

	lpData = (LPTSTR) malloc (dwLen);
	if (!lpData) {
		return 0;
	}

	if (!GetFileVersionInfo(szPath, dwHandle, dwLen, lpData)) {
		free (lpData);
		return 0;
	}

	if (VerQueryValue (lpData, "\\", (LPVOID) &pFileInfo, (PUINT) &BufLen)) {
	//	printf ("TCPIP.SYS version: %d.%d\n\n", HIWORD(pFileInfo->dwFileVersionLS), LOWORD(pFileInfo->dwFileVersionLS));
		if (HIWORD(pFileInfo->dwFileVersionLS) == 2600) {
			switch (LOWORD(pFileInfo->dwFileVersionLS)) {
				case 2180:
					free(lpData);
					return 1;
				case 2892: 
					free(lpData);
					return 2;
//				case 2505:
//					free(lpData);
//					return 3;
//				case 2685:
//					free(lpData);
//					return 4;
				default: 
					free(lpData);
					return 0;
			}
		}
	}

	free(lpData);

	return 0;
}