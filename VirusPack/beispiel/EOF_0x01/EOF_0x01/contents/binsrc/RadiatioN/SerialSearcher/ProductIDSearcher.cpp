/*

With this small code you can get windows and office serials which are stored in the registry.
This code also decodes and formats them to a real serial.
The code will show you:
- Serial
- Product Name (if it exists)
- ProductId

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

*/

#include "stdafx.h"

void ConvertProductKey(char *szKey)
{
	char szTemp[35]="";
	int iPos=0;

	strcpy(szTemp,szKey);

	memset(szKey, 0, 30);
	
	szKey[5]='-';
	szKey[11]='-';
	szKey[17]='-';
	szKey[23]='-';

	for(int i=0; i<5; i++)
	{
		szKey[i]=szTemp[iPos];
		iPos+=1;
	}

	for(int i=6; i<11; i++)
	{
		szKey[i]=szTemp[iPos];
		iPos+=1;
	}

	for(int i=12; i<17; i++)
	{
		szKey[i]=szTemp[iPos];
		iPos+=1;
	}

	for(int i=18; i<23; i++)
	{
		szKey[i]=szTemp[iPos];
		iPos+=1;
	}

	for(int i=24; i<=29; i++)
	{
		szKey[i]=szTemp[iPos];
		iPos+=1;
	}
}

void DecodeMSKey(HKEY hKey, char *szSubkey)
{
    char szDigits[] = {'B','C','D','F','G','H','J','K','M','P','Q','R','T','V','W','X','Y','2','3','4','6','7','8','9'},
		szResult[35]="\0",
		szProductName[250]="", 
		szProductID[250]="";
    PUCHAR wszBuf = new UCHAR[200];
    HKEY key = NULL;
    DWORD dwDatasize = 200, dwRet = 0;

    for(int a=0; a<200; a++)
	{
		wszBuf[a]=0;
	}

    dwRet = RegOpenKeyEx(hKey, szSubkey, 0, KEY_READ, &key);
    dwRet = RegQueryValueEx(key, "DigitalProductID", NULL, NULL, (LPBYTE)wszBuf, &dwDatasize);
   
    if (dwRet != ERROR_SUCCESS) 
	{
	   return;
    }

    for (int i=24; i>=0; i--) 
	{
        int x=0;

        for (int j=14; j>=0; j--) 
		{
            x = (x<<8) + (wszBuf+0x34)[j];
            (wszBuf+0x34)[j] = x / 24;
            x = x % 24;
        }
        szResult[i]=szDigits[x];
    }

	ConvertProductKey(szResult);

    dwDatasize=250;
	RegQueryValueEx(key, "ProductName", NULL, NULL, (LPBYTE)szProductName, &dwDatasize);

    dwDatasize=250;
	RegQueryValueEx(key, "ProductId", NULL, NULL, (LPBYTE)szProductID, &dwDatasize);
    
	printf("Serial:      %s\r\n", szResult);
	printf("ProductName: %s\r\n", szProductName);
	printf("ProductId:   %s\r\n\r\n", szProductID);

	RegCloseKey(key);
}

void EnumOfficeKey(char *szSubkey)
{
	HKEY hMainKey;
	LONG lRetVal;
	int iPos=0;
	char szKeyName[512]="", szNewKey[512]="";
	DWORD dwKeyNameLen;

	lRetVal = RegOpenKeyEx(HKEY_LOCAL_MACHINE, szSubkey, 0, KEY_ALL_ACCESS, &hMainKey);

	if(lRetVal == ERROR_SUCCESS)
	{
		dwKeyNameLen=512;
		
		if(RegEnumKeyEx(hMainKey, iPos, szKeyName, &dwKeyNameLen, NULL, NULL, NULL, NULL)!=ERROR_NO_MORE_ITEMS)
		{
			do
			{
				if(strcmp(szSubkey, "")!=0)
				{
					strcpy(szNewKey, szSubkey);
					strcat(szNewKey, "\\");
					strcat(szNewKey, szKeyName);
				}
				else
				{					
					strcpy(szNewKey, szKeyName);
				}

				DecodeMSKey(HKEY_LOCAL_MACHINE, szNewKey);

				iPos+=1;
				dwKeyNameLen=512;

			}while(RegEnumKeyEx(hMainKey, iPos, szKeyName, &dwKeyNameLen, NULL, NULL, NULL, NULL)!=ERROR_NO_MORE_ITEMS);
		}
	}

	RegCloseKey(hMainKey);
}

void GetMSProductKeys(void)
{
	//WINDOWS serials
	DecodeMSKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion");
	DecodeMSKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\WindowsNT\\CurrentVersion");

	//OFFICE serials
	EnumOfficeKey("SOFTWARE\\Microsoft\\Office\\8.0\\Registration");
	EnumOfficeKey("SOFTWARE\\Microsoft\\Office\\9.0\\Registration");
	EnumOfficeKey("SOFTWARE\\Microsoft\\Office\\10.0\\Registration");
	EnumOfficeKey("SOFTWARE\\Microsoft\\Office\\11.0\\Registration");
}

int main(int argc, char* argv[])
{
	GetMSProductKeys();

	_getch();

	return 0;
}

