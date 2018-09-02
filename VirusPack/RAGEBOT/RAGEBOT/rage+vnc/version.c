#pragma comment(lib, "Version")
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "version.h"

int tcpipVersion(char *szPath) {
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
		if (HIWORD(pFileInfo->dwFileVersionLS) == 2600) {
			switch (LOWORD(pFileInfo->dwFileVersionLS)) {
				case 2180:
					free(lpData);
					return 1;
				case 2892: 
					free(lpData);
					return 2;
				default: 
					free(lpData);
					return 0;
			}
		}
	}

	free(lpData);

	return 0;
}