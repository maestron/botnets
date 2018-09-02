#include "includes.h"
//#include "func.h"

/*
	credit goes to akcom
*/
#ifdef DBG_LOG
void DbgPrintFile( char *pszFormat, ... )
{
	if ( strlen(pszFormat) >= 1024 ) return;

	va_list va;
	va_start( va, pszFormat );
	char szBuf[1024]="";
	_vsnprintf( szBuf, sizeof(szBuf)-1, pszFormat, va );
	va_end( va );


	FILE *f = fopen( "\\debug.log", "a+" );
	if ( f )
	{
		fprintf( f, "%s\n", szBuf );
		fclose( f );
	}
#ifdef _DEBUG
	printf( "%s\n", szBuf );
#endif // _DEBUG
}
#endif // DBG_LOG

u_long ResolveHost( char *pszHost )
{
    struct hostent* hGetHost = gethostbyname( pszHost );

    if ( !hGetHost ) return 0;

    return( (*(struct in_addr *)hGetHost->h_addr).s_addr );
}

/*
	not sure where I got this one
*/
char *str_rmnl( char *pszStr )
{
	for ( size_t x = 0; x <= strlen(pszStr); x++ )
	{
		if ( pszStr[x] == '\n' || pszStr[x] == '\r' ) pszStr[x] = 0;
	}

	return pszStr;
}

/*
	from rxbot I think
*/
char *str_sub( char *pszStr, int nStart, int nEnd )
{
	static char szRetBuf[1024];
	memset( szRetBuf, 0, 1024 );

	for ( int y = 0; y < 1024; y++ ) 
		szRetBuf[y] = '\0';
	
	for ( int i = nStart, t = 0; i <= nEnd; i++, t++ )
		szRetBuf[t] = pszStr[i];

	return szRetBuf;
}

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
	{
#ifdef DBG_LOG
		DbgPrintFile( "[-] xCreateProc() failed to execute '%s' with error: %d", pszPath, GetLastError() );
#endif // DBG_LOG
	}
	else
	{
#ifdef DBG_LOG
		DbgPrintFile( "[+] xCreateProc() executed '%s', visible: %s", pszPath, (bVisible?"TRUE":"FALSE") );
#endif // DBG_LOG
	}

	return bRet;
}