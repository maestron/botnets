//====== Copyright © 1996-2004, Valve Corporation, All rights reserved. =======
//
// Purpose: 
//
//=============================================================================

#ifndef STEAM_API_H
#define STEAM_API_H
#ifdef _WIN32
#pragma once
#endif

#include "isteamclient.h"
#include "isteamuser.h"
#include "isteamfriends.h"
#include "isteamutils.h"
#include "isteammatchmaking.h"
#include "isteamuserstats.h"
#include "isteamapps.h"

//OLD
#include "isteambilling.h"
#include "isteamvac.h"

// Steam API export macro
#if defined( _WIN32 ) && !defined( _X360 )
	#if defined( STEAM_API_EXPORTS )
	#define S_API extern "C" __declspec( dllexport ) 
	#elif defined( STEAM_API_NODLL )
	#define S_API extern "C"
	#else
	#define S_API extern "C" __declspec( dllimport ) 
	#endif // STEAM_API_EXPORTS
#else // !WIN32
	#if defined( STEAM_API_EXPORTS )
	#define S_API extern "C"  
	#else
	#define S_API extern "C" 
	#endif // STEAM_API_EXPORTS
#endif

//----------------------------------------------------------------------------------------------------------------------------------------------------------//
//	Steam API setup & teardown
//
//	These functions manage loading, initializing and shutdown of the steamclient.dll
//
//  bugbug johnc: seperate defining these to defining game server interface more cleanly
//
//----------------------------------------------------------------------------------------------------------------------------------------------------------//

S_API bool SteamAPI_Init();
S_API void SteamAPI_Shutdown();

S_API void SteamAPI_WriteMiniDump( uint32 uStructuredExceptionCode, void* pvExceptionInfo, uint32 uBuildID );
S_API void SteamAPI_SetMiniDumpComment( const char *pchMsg );

// interface pointers, configured by SteamAPI_Init()
S_API ISteamUser *SteamUser();
S_API ISteamFriends *SteamFriends();
S_API ISteamClient *SteamClient();
S_API ISteamUtils *SteamUtils();
S_API ISteamMatchmaking *SteamMatchmaking();
S_API ISteamUserStats *SteamUserStats();
S_API ISteamApps *SteamApps();

S_API ISteamMatchmakingServers *SteamMatchmakingServers();


//----------------------------------------------------------------------------------------------------------------------------------------------------------//
//	steam callback helper functions
//
//	These following classes/macros are used to be able to easily multiplex callbacks 
//	from the Steam API into various objects in the app in a thread-safe manner
//
//	This functors are triggered via the SteamAPI_RunCallbacks() function, mapping the callback
//  to as many functions/objects as are registered to it
//----------------------------------------------------------------------------------------------------------------------------------------------------------//

S_API void SteamAPI_RunCallbacks();



// functions used by the utility CCallback objects to receive callbacks
S_API void SteamAPI_RegisterCallback( class CCallbackBase *pCallback, int iCallback );
S_API void SteamAPI_UnregisterCallback( class CCallbackBase *pCallback );

//-----------------------------------------------------------------------------
// Purpose: base for callbacks, 
//			used only by CCallback, shouldn't be used directly
//-----------------------------------------------------------------------------
class CCallbackBase
{
public:
	CCallbackBase() { m_nCallbackFlags = 0; }
	// don't add a virtual destructor because we export this binary interface across dll's
	virtual void Run( void *pvParam ) = 0;

protected:
	enum { k_ECallbackFlagsRegistered = 0x01, k_ECallbackFlagsGameServer = 0x02 };
	uint8 m_nCallbackFlags;
private:
	int m_iCallback;
	friend class CCallbackMgr;
};


//-----------------------------------------------------------------------------
// Purpose: maps a steam callback to a class member function
//			template params: T = local class, P = parameter struct
//-----------------------------------------------------------------------------
template< class T, class P, bool bGameServer >
class CCallback : private CCallbackBase
{
public:
	typedef void (T::*func_t)( P* );

	// If you can't support constructing a callback with the correct parameters
	// then uncomment the empty constructor below and manually call
	// ::Register() for your object
	//CCallback() {}
	
	// constructor for initializing this object in owner's constructor
	CCallback( T *pObj, func_t func ) : m_pObj( pObj ), m_Func( func )
	{
		if ( bGameServer )
		{
			m_nCallbackFlags |= k_ECallbackFlagsGameServer;
		}

		Register( pObj, func );
	}

	~CCallback()
	{
		SteamAPI_UnregisterCallback( this );
	}

	// manual registration of the callback
	void Register( T *pObj, func_t func )
	{
		m_pObj = pObj;
		m_Func = func;
		SteamAPI_RegisterCallback( this, P::k_iCallback );
	}

private:
	virtual void Run( void *pvParam )
	{
		(m_pObj->*m_Func)( (P *)pvParam );
	}

	T *m_pObj;
	func_t m_Func;
};


// utility macro for declaring the function and callback object together
#define STEAM_CALLBACK( thisclass, func, param, var ) CCallback< thisclass, param, false > var; void func( param *pParam )




//----------------------------------------------------------------------------------------------------------------------------------------------------------//
//	steamclient.dll private wrapper functions
//
//	The following functions are part of abstracting API access to the steamclient.dll, but should only be used in very specific cases
//----------------------------------------------------------------------------------------------------------------------------------------------------------//

// pumps out all the steam messages, calling the register callback
S_API void Steam_RunCallbacks( HSteamPipe hSteamPipe, bool bGameServerCallbacks );

// register the callback funcs to use to interact with the steam dll
S_API void Steam_RegisterInterfaceFuncs( void *hModule );

// returns the HSteamUser of the last user to dispatch a callback
S_API HSteamUser Steam_GetHSteamUserCurrent();


#endif // STEAM_API_H
