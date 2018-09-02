//====== Copyright © 1996-2007, Valve Corporation, All rights reserved. =======
//
// Purpose: interface to app data in Steam
//
//=============================================================================

#ifndef ISTEAMAPPS_H
#define ISTEAMAPPS_H
#ifdef _WIN32
#pragma once
#endif

#include "steam/isteamapps.h"

//-----------------------------------------------------------------------------
// Purpose: interface to app data
//-----------------------------------------------------------------------------
class ISteamApps
{
public:
	// returns 0 if the key does not exist
	// this may be true on first call, since the app data may not be cached locally yet
	// If you expect it to exists wait for the AppDataChanged_t after the first failure and ask again
	virtual int GetAppData( uint32 nAppID, const char *pchKey, char *pchValue, int cchValueMax ) = 0;
};

#define STEAMAPPS_INTERFACE_VERSION "STEAMAPPS_INTERFACE_VERSION001"

//-----------------------------------------------------------------------------
// Purpose: called when new information about an app has arrived
//-----------------------------------------------------------------------------
struct AppDataChanged_t
{
	enum { k_iCallback = k_iSteamAppsCallbacks + 1 };
	uint32 m_nAppID;
	bool m_bWebDataChanged;
};

#endif // ISTEAMAPPS_H
