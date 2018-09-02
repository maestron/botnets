

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
