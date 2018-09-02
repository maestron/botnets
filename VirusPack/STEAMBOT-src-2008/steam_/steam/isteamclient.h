//====== Copyright © 1996-2004, Valve Corporation, All rights reserved. =======
//
// Purpose: 
//
//=============================================================================

#ifndef ISTEAMCLIENT_H
#define ISTEAMCLIENT_H
#ifdef _WIN32
#pragma once
#endif

#include "steamtypes.h"
#include "steamclientpublic.h"

// handle to a communication pipe to the Steam client
typedef int32 HSteamPipe;
// handle to single instance of a steam user
typedef int32 HSteamUser;

#ifndef DLL_EXPORT
#define DLL_EXPORT 
#endif

// interface predec
class ISteamUser;
class ISteamGameServer;
class ISteamFriends;
class ISteamUtils;
class ISteamMatchmaking;
class ISteamContentServer;
class ISteamMasterServerUpdater;
class ISteamMatchmakingServers;
class ISteam2Bridge;
class ISteamUserStats;
class ISteamApps;

//OLD SHIT
class IVAC;
class ISteamBilling;

//-----------------------------------------------------------------------------
// Purpose: Interface to creating a new steam instance, or to
//			connect to an existing steam instance, whether it's in a
//			different process or is local
//-----------------------------------------------------------------------------
class ISteamClient
{
public:
	// Creates a communication pipe to the Steam client
	virtual HSteamPipe CreateSteamPipe() = 0;

	// Releases a previously created communications pipe
	virtual bool BReleaseSteamPipe( HSteamPipe hSteamPipe ) = 0;

	// connects to an existing global user, failing if none exists
	// used by the game to coordinate with the steamUI
	virtual HSteamUser ConnectToGlobalUser( HSteamPipe hSteamPipe ) = 0;

	// used by game servers, create a steam user that won't be shared with anyone else
	virtual HSteamUser CreateLocalUser( HSteamPipe *phSteamPipe ) = 0;

	// removes an allocated user
	virtual void ReleaseUser( HSteamPipe hSteamPipe, HSteamUser hUser ) = 0;

	// retrieves the ISteamUser interface associated with the handle
	virtual ISteamUser *GetISteamUser( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion ) = 0;

	// retrieves the ISteamGameServer interface associated with the handle
	virtual ISteamGameServer *GetISteamGameServer( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion ) = 0;

	// set the local IP and Port to bind to
	// this must be set before CreateLocalUser()
	virtual void SetLocalIPBinding( uint32 unIP, uint16 usPort ) = 0; 

	// returns the ISteamFriends interface
	virtual ISteamFriends *GetISteamFriends( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion ) = 0;

	// returns the ISteamUtils interface
	virtual ISteamUtils *GetISteamUtils( HSteamPipe hSteamPipe, const char *pchVersion ) = 0;

	// returns the ISteamMatchmaking interface
	virtual ISteamMatchmaking *GetISteamMatchmaking( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion ) = 0;

	// returns the ISteamContentServer interface
	virtual ISteamContentServer *GetISteamContentServer( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion ) = 0;

	// returns the ISteamMasterServerUpdater interface
	virtual ISteamMasterServerUpdater *GetISteamMasterServerUpdater( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion ) = 0;

	// returns the ISteamMatchmakingServers interface
	virtual ISteamMatchmakingServers *GetISteamMatchmakingServers( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion ) = 0;

	// returns the ISteam2Bridge interface
	virtual ISteam2Bridge *GetISteam2Bridge( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion ) = 0;

	virtual void RunFrame() = 0;

	// returns the number of IPC calls made since the last time this function was called
	// Used for perf debugging so you can understand how many IPC calls your game makes per frame
	// Every IPC call is at minimum a thread context switch if not a process one so you want to rate
	// control how often you do them.
	virtual uint32 GetIPCCallCount() = 0;

	// returns the ISteamUserStats interface
	virtual ISteamUserStats *GetISteamUserStats( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion ) = 0;

	// returns apps interface
	virtual ISteamApps *GetISteamApps( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion ) = 0;
};

#define STEAMCLIENT_INTERFACE_VERSION		"SteamClient007"

//OLD INTERFACE HACK, ADDED FROM OLD SOURCE CODES
//BELONGING TO VALVE
class ISteamClient006
{
public:
	// Creates a communication pipe to the Steam client
	virtual HSteamPipe CreateSteamPipe() = 0;

	// Releases a previously created communications pipe
	virtual bool BReleaseSteamPipe( HSteamPipe hSteamPipe ) = 0;

	// creates a global instance of a steam user, so that other processes can share it
	// used by the steam UI, to share it's account info/connection with any games it launches
	// fails (returns NULL) if an existing instance already exists
	virtual HSteamUser CreateGlobalUser( HSteamPipe *phSteamPipe ) = 0;

	// connects to an existing global user, failing if none exists
	// used by the game to coordinate with the steamUI
	virtual HSteamUser ConnectToGlobalUser( HSteamPipe hSteamPipe ) = 0;

	// used by game servers, create a steam user that won't be shared with anyone else
	virtual HSteamUser CreateLocalUser( HSteamPipe *phSteamPipe ) = 0;

	// removes an allocated user
	virtual void ReleaseUser( HSteamPipe hSteamPipe, HSteamUser hUser ) = 0;

	// retrieves the ISteamUser interface associated with the handle
	virtual ISteamUser *GetISteamUser( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion ) = 0;

	// retrieves the IVac interface associated with the handle
	// there is normally only one instance of VAC running, but using this connects it to the right user/account
	virtual IVAC *GetIVAC( HSteamUser hSteamUser ) = 0;

	// retrieves the ISteamGameServer interface associated with the handle
	virtual ISteamGameServer *GetISteamGameServer( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion ) = 0;

	// set the local IP and Port to bind to
	// this must be set before CreateLocalUser()
	virtual void SetLocalIPBinding( uint32 unIP, uint16 usPort ) = 0; 

	// returns the name of a universe
	virtual const char *GetUniverseName( EUniverse eUniverse ) = 0;

	// returns the ISteamFriends interface
	virtual ISteamFriends *GetISteamFriends( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion ) = 0;

	// returns the ISteamUtils interface
	virtual ISteamUtils *GetISteamUtils( HSteamPipe hSteamPipe, const char *pchVersion ) = 0;

	// returns the ISteamBilling interface
	virtual ISteamBilling *GetISteamBilling( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion ) = 0;
};


//-----------------------------------------------------------------------------
// Purpose: Base values for callback identifiers, each callback must
//			have a unique ID.
//-----------------------------------------------------------------------------
enum { k_iSteamUserCallbacks = 100 };
enum { k_iSteamGameServerCallbacks = 200 };
enum { k_iSteamFriendsCallbacks = 300 };
enum { k_iSteamBillingCallbacks = 400 };
enum { k_iSteamMatchmakingCallbacks = 500 };
enum { k_iSteamContentServerCallbacks = 600 };
enum { k_iSteamUtilsCallbacks = 700 };
enum { k_iClientFriendsCallbacks = 800 };
enum { k_iClientUserCallbacks = 900 };
enum { k_iSteamAppsCallbacks = 1000 };
enum { k_iSteamUserStatsCallbacks = 1100 };

// For GoldSRC we need a C API as the C++ ABI changed from the GoldSRC compiler 
// (GCC 2.95.3) to the Source/Steam3 one (GCC 3.4.1)
// C functions we export for the C API, maps to ISteamClient functions 
DLL_EXPORT HSteamPipe Steam_CreateSteamPipe();
DLL_EXPORT bool Steam_BReleaseSteamPipe( HSteamPipe hSteamPipe );
DLL_EXPORT HSteamUser Steam_CreateLocalUser( HSteamPipe *phSteamPipe );
DLL_EXPORT HSteamUser Steam_ConnectToGlobalUser( HSteamPipe hSteamPipe );
DLL_EXPORT void Steam_ReleaseUser( HSteamPipe hSteamPipe, HSteamUser hUser );
DLL_EXPORT void Steam_SetLocalIPBinding( uint32 unIP, uint16 usLocalPort );


#endif // ISTEAMCLIENT_H
