//====== Copyright © 1996-2004, Valve Corporation, All rights reserved. =======
//
// Purpose: interface to user account information in Steam
//
//=============================================================================

#ifndef ISTEAMUSER_H
#define ISTEAMUSER_H
#ifdef _WIN32
#pragma once
#endif

#include "isteamclient.h"

// structure that contains client callback data
struct CallbackMsg_t
{
	HSteamUser m_hSteamUser;
	int m_iCallback;
	uint8 *m_pubParam;
	int m_cubParam;
};

// reference to a steam call, to filter results by
typedef int32 HSteamCall;

enum ERegistrySubTree
{
	k_ERegistrySubTreeNews = 0,
	k_ERegistrySubTreeApps = 1,
	k_ERegistrySubTreeSubscriptions = 2,
	k_ERegistrySubTreeGameServers = 3,
	k_ERegistrySubTreeFriends = 4,
	k_ERegistrySubTreeSystem = 5,
};

enum EAppUsageEvent
{
	k_EAppUsageEventGameLaunch = 1,
	k_EAppUsageEventGameLaunchTrial = 2,
	k_EAppUsageEventMedia = 3,
	k_EAppUsageEventPreloadStart = 4,
	k_EAppUsageEventPreloadFinish = 5,
	k_EAppUsageEventMarketingMessageView = 6,	// deprecated, do not use
	k_EAppUsageEventInGameAdViewed = 7,
	k_EAppUsageEventGameLaunchFreeWeekend = 8,
};


//-----------------------------------------------------------------------------
// Purpose: Functions for accessing and manipulating a steam account
//			associated with one client instance
//-----------------------------------------------------------------------------
class ISteamUser
{
public:
	// returns the HSteamUser this interface represents
	virtual HSteamUser GetHSteamUser() = 0;

	// steam account management functions
	virtual bool BLoggedOn() = 0;
	virtual CSteamID GetSteamID() = 0;

	// notify of connection to game server
	virtual int InitiateGameConnection( void *pBlob, int cbMaxBlob, CSteamID steamID, CGameID gameID, uint32 unIPServer, uint16 usPortServer, bool bSecure, void *pvSteam2GetEncryptionKey, int cbSteam2GetEncryptionKey ) = 0;
	// notify of disconnect
	virtual void TerminateGameConnection( uint32 unIPServer, uint16 usPortServer ) = 0;

	// game info
	virtual void TrackAppUsageEvent( CGameID gameID, int eAppUsageEvent, const char *pchExtraInfo = "" ) = 0;

	// legacy authentication support - need to be called if the game server rejects the user with a 'bad ticket' error
	virtual void RefreshSteam2Login() = 0;
};

#define STEAMUSER_INTERFACE_VERSION "SteamUser008"


// callbacks


//-----------------------------------------------------------------------------
// Purpose: called when a logon attempt has succeeded
//-----------------------------------------------------------------------------
struct LogonSuccess_t
{
	enum { k_iCallback = k_iSteamUserCallbacks + 1 };
};


//-----------------------------------------------------------------------------
// Purpose: called when a logon attempt has failed
//-----------------------------------------------------------------------------
struct LogonFailure_t
{
	enum { k_iCallback = k_iSteamUserCallbacks + 2 };
	EResult m_eResult;
};


//-----------------------------------------------------------------------------
// Purpose: called when the user logs off
//-----------------------------------------------------------------------------
struct LoggedOff_t
{
	enum { k_iCallback = k_iSteamUserCallbacks + 3 };
	EResult m_eResult;
};


//-----------------------------------------------------------------------------
// Purpose: called when the client is trying to retry logon after being unintentionally logged off
//-----------------------------------------------------------------------------
struct BeginLogonRetry_t
{
	enum { k_iCallback = k_iSteamUserCallbacks + 4 };
};


//-----------------------------------------------------------------------------
// Purpose: connect to game server denied
//-----------------------------------------------------------------------------
struct ClientGameServerDeny_t
{
	enum { k_iCallback = k_iSteamUserCallbacks + 13 };

	uint32 m_uAppID;
	uint32 m_unGameServerIP;
	uint16 m_usGameServerPort;
	uint16 m_bSecure;
	uint32 m_uReason;
};


//-----------------------------------------------------------------------------
// Purpose: called when the callback system for this client is in an error state (and has flushed pending callbacks)
//			When getting this message the client should disconnect from Steam, reset any stored Steam state and reconnect
//-----------------------------------------------------------------------------
struct CallbackPipeFailure_t
{
	enum { k_iCallback = k_iSteamUserCallbacks + 17 };
};


//-----------------------------------------------------------------------------
// Purpose: connect to game server denied
//-----------------------------------------------------------------------------
struct GSPolicyResponse_t
{
	enum { k_iCallback = k_iSteamUserCallbacks + 15 };
	uint8 m_bSecure;
};


// C API bindings for GoldSRC, see isteamclient.h for details
extern "C"
{	
	// C functions we export for the C API, maps to ISteamUser functions 
	DLL_EXPORT void Steam_LogOn( HSteamUser hUser, HSteamPipe hSteamPipe, uint64 ulSteamID );
	DLL_EXPORT void Steam_LogOff( HSteamUser hUser, HSteamPipe hSteamPipe );
	DLL_EXPORT bool Steam_BLoggedOn( HSteamUser hUser, HSteamPipe hSteamPipe );
	DLL_EXPORT bool Steam_BConnected( HSteamUser hUser, HSteamPipe hSteamPipe );
	DLL_EXPORT bool Steam_BGetCallback( HSteamPipe hSteamPipe, CallbackMsg_t *pCallbackMsg, HSteamCall *phSteamCall );
	DLL_EXPORT void Steam_FreeLastCallback( HSteamPipe hSteamPipe );
	DLL_EXPORT int Steam_GSGetSteamGameConnectToken( HSteamUser hUser, HSteamPipe hSteamPipe, void *pBlob, int cbBlobMax );
	DLL_EXPORT int Steam_InitiateGameConnection( HSteamUser hUser, HSteamPipe hSteamPipe, void *pBlob, int cbMaxBlob, uint64 steamID, int nGameAppID, uint32 unIPServer, uint16 usPortServer, bool bSecure );
	DLL_EXPORT void Steam_TerminateGameConnection( HSteamUser hUser, HSteamPipe hSteamPipe, uint32 unIPServer, uint16 usPortServer );


	typedef bool (*PFNSteam_BGetCallback)( HSteamPipe hSteamPipe, CallbackMsg_t *pCallbackMsg, HSteamCall *phSteamCall );
	typedef void (*PFNSteam_FreeLastCallback)( HSteamPipe hSteamPipe );
}

#endif // ISTEAMUSER_H
