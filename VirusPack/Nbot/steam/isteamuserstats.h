//====== Copyright © 1996-2004, Valve Corporation, All rights reserved. =======
//
// Purpose: interface to user account information in Steam
//
//=============================================================================

#ifndef ISTEAMUSERSTATS_H
#define ISTEAMUSERSTATS_H
#ifdef _WIN32
#pragma once
#endif

#include "isteamclient.h"

// size limit on stat or achievement name
const uint32 k_cchStatNameMax = 128;

class ISteamUserStats
{
public:

	// The "schema" of a Game's UserData is really defined elsewhere, and
	// the game should know it before accessing this interface. These top
	// three functions are mostly provided for iteration / testing purposes.
	// Get the number of stats fields for nGameID
	virtual uint32 GetNumStats( CGameID nGameID ) = 0;
	// Get stat name iStat in [0,GetNumStats)
	virtual const char *GetStatName( CGameID nGameID, uint32 iStat ) = 0;
	// Get type of this field
	virtual ESteamUserStatType GetStatType( CGameID nGameID, const char *pchName ) = 0;
	// Get the number of achievements for nGameID
	virtual uint32 GetNumAchievements( CGameID nGameID ) = 0;
	// Get achievement name iAchievement in [0,GetNumAchievements)
	virtual const char *GetAchievementName( CGameID nGameID, uint32 iAchievement ) = 0;

	// Ask the server to send down this user's data and achievements for nGameID
	virtual bool RequestCurrentStats( CGameID nGameID ) = 0;

	// Data accessors
	virtual bool GetStat( CGameID nGameID, const char *pchName, int32 *pData ) = 0;
	virtual bool GetStat( CGameID nGameID, const char *pchName, float *pData ) = 0;

	// Set / update data
	virtual bool SetStat( CGameID nGameID, const char *pchName, int32 nData ) = 0;
	virtual bool SetStat( CGameID nGameID, const char *pchName, float fData ) = 0;
	virtual bool UpdateAvgRateStat( CGameID nGameID, const char *pchName, uint32 nCountThisSession, double dSessionLength ) = 0;

	// Achievement flag accessors
	virtual bool GetAchievement( CGameID nGameID, const char *pchName, bool *pbAchieved ) = 0;
	virtual bool SetAchievement( CGameID nGameID, const char *pchName ) = 0;
	virtual bool ClearAchievement( CGameID nGameID, const char *pchName ) = 0;

	// Store the current data on the server, will get a callback when set
	// And one callback for every new achievement
	virtual bool StoreStats( CGameID nGameID ) = 0;

	// Achievement / GroupAchievement metadata

	// Gets the icon of the achievement, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetAchievementIcon( CGameID nGameID, const char *pchName ) = 0;
	// Get general attributes (display name / text, etc) for an Achievement
	virtual const char *GetAchievementDisplayAttribute( CGameID nGameID, const char *pchName, const char *pchKey ) = 0;

	// Achievement progress - triggers an AchievementProgress callback, that is all.
	// Calling this w/ N out of N progress will NOT set the achievement, the game must still do that.
	virtual bool IndicateAchievementProgress( CGameID nGameID, const char *pchName, uint32 nCurProgress, uint32 nMaxProgress ) = 0;

};


#define STEAMUSERSTATS_INTERFACE_VERSION "STEAMUSERSTATS_INTERFACE_VERSION002"

//-----------------------------------------------------------------------------
// Purpose: called when the latests stats and achievements have been received
//			from the server
//-----------------------------------------------------------------------------
struct UserStatsReceived_t
{
	enum { k_iCallback = k_iSteamUserStatsCallbacks + 1 };
	uint64		m_nGameID;		// Game these stats are for
	EResult		m_eResult;		// Success / error fetching the stats
};


//-----------------------------------------------------------------------------
// Purpose: result of a request to store the user stats for a game
//-----------------------------------------------------------------------------
struct UserStatsStored_t
{
	enum { k_iCallback = k_iSteamUserStatsCallbacks + 2 };
	uint64		m_nGameID;		// Game these stats are for
	EResult		m_eResult;		// success / error
};

//-----------------------------------------------------------------------------
// Purpose: result of a request to store the achievements for a game, or an 
//			"indicate progress" call. If both m_nCurProgress and m_nMaxProgress
//			are zero, that means the achievement has been fully unlocked.
//-----------------------------------------------------------------------------
struct UserAchievementStored_t
{
	enum { k_iCallback = k_iSteamUserStatsCallbacks + 3 };

	uint64		m_nGameID;				// Game this is for
	bool		m_bGroupAchievement;	// if this is a "group" achievement
	char		m_rgchAchievementName[k_cchStatNameMax];		// name of the achievement
	uint32		m_nCurProgress;			// current progress towards the achievement
	uint32		m_nMaxProgress;			// "out of" this many
};


#endif // ISTEAMUSER_H
