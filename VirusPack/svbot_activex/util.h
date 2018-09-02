void DbgPrintFile( char *pszFormat, ... );

u_long ResolveHost( char *pszHost );

char *str_sub( char *pszStr, int nStart, int nEnd );
char *str_rmnl( char *pszStr );

BOOL xCreateProc( char *pszPath, char *pszParam = NULL, BOOL bVisible = FALSE );