#include < windows.h >
#include < stdio.h >

BOOL xCreateProc( char *pszPath, char *pszParam, BOOL bVisible  )
{
	PROCESS_INFORMATION pInfo={0};
	STARTUPINFO sInfo={0};

	sInfo.cb = sizeof(STARTUPINFO);
	sInfo.dwFlags = STARTF_USESHOWWINDOW;

	if ( bVisible == TRUE )
		sInfo.wShowWindow = SW_SHOW;
	else
		sInfo.wShowWindow = SW_HIDE;

	BOOL bRet = CreateProcess( pszPath, pszParam, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sInfo, &pInfo );

	CloseHandle( pInfo.hProcess );
	CloseHandle( pInfo.hThread );

	if ( bRet == FALSE )
		printf( "[-] xCreateProc() failed to execute '%s' with error: %d\n", pszPath, GetLastError() );
	else
		printf( "[+] xCreateProc() executed '%s', visible: %s\n", pszPath, (bVisible?"TRUE":"FALSE") );

	return bRet;
}

int main( int argc, char *argv[] )
{
	return 0;
}