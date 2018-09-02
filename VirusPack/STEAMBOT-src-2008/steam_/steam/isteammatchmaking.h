//====== Copyright © 1996-2004, Valve Corporation, All rights reserved. =======
//
// Purpose: interface to steam managing game server/client match making
//
//=============================================================================
#ifndef ISTEAMMATCHMAKING
#define ISTEAMMATCHMAKING
#ifdef _WIN32
#pragma once
#endif

#include "steamtypes.h"
#include "steamclientpublic.h"
#include "matchmakingtypes.h" 
#include "isteamclient.h"
#include "isteamfriends.h"

// 32KB max size on chat messages
enum { k_cchFriendChatMsgMax = 32 * 1024 };

//-----------------------------------------------------------------------------
// Purpose: Functions for match making services for clients to get to favorites
//-----------------------------------------------------------------------------
class ISteamMatchmaking
{
public:
	virtual int GetFavoriteGameCount() = 0;
	
	// Obsolete. Use the ...2 versions of these functions, which take separate connection and query ports.
	virtual bool GetFavoriteGame( int iGame, uint32 *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint32 *punFlags, uint32 *pRTime32LastPlayedOnServer ) = 0;
	virtual int AddFavoriteGame( uint32 nAppID, uint32 nIP, uint16 nConnPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer ) =0;
    virtual bool RemoveFavoriteGame( uint32 nAppID, uint32 nIP, uint16 nConnPort, uint32 unFlags ) = 0;


	// returns the details of the game server
	// iGame is of range [0,iGame)
	virtual bool GetFavoriteGame2( int iGame, uint32 *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint16 *pnQueryPort, uint32 *punFlags, uint32 *pRTime32LastPlayedOnServer ) = 0;

    // returns the new index of the game
	virtual int AddFavoriteGame2( uint32 nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer ) =0;
	
	// removes the game; returns true if one was removed
    virtual bool RemoveFavoriteGame2( uint32 nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags ) = 0;

	///////
	// Game lobby functions

	// Get a list of relevant lobbies
	virtual void RequestLobbyList( uint64 ulGameID, MatchMakingKeyValuePair_t *pFilters, uint32 nFilters ) = 0;
	virtual CSteamID GetLobbyByIndex( int iLobby ) = 0;
	// Create a lobby - you'll get the SteamID of it on success
	virtual void CreateLobby( uint64 ulGameID, bool bPrivate ) = 0;
	// Join a lobby
	virtual void JoinLobby( CSteamID steamIDLobby ) = 0;
	// Leave a lobby
	virtual void LeaveLobby( CSteamID steamIDLobby ) = 0;
	// Invite someone to the lobby
	virtual bool InviteUserToLobby( CSteamID steamIDLobby, CSteamID steamIDInvitee ) = 0;
	// List users in this lobby
	virtual int GetNumLobbyMembers( CSteamID steamIDLobby ) = 0;
	virtual CSteamID GetLobbyMemberByIndex( CSteamID steamIDLobby, int iMember ) = 0;
	// Get data associated with this lobby
	virtual const char *GetLobbyData( CSteamID SteamIDLobby, const char *pchKey ) = 0;
	// Update lobby data (Admin only)
	virtual void SetLobbyData( CSteamID steamIDLobby, const char *pchKey, const char *pchValue ) = 0;
	// Get per-user data for someone in this lobby
	virtual const char *GetLobbyMemberData( CSteamID steamIDLobby, CSteamID steamIDUser, const char *pchKey ) = 0;
	// Update user data (for you only)
	virtual void SetLobbyMemberData( CSteamID steamIDLobby, const char *pchKey, const char *pchValue ) = 0;
	// change the lobby Admin (Admin only)
	virtual void ChangeLobbyAdmin( CSteamID steamIDLobby, CSteamID steamIDNewAdmin ) = 0;
	// Send a chat message to the lobby
	virtual bool SendLobbyChatMsg( CSteamID steamIDLobby, const void *pvMsgBody, int cubMsgBody ) = 0;
	// Get a chat message entry
	virtual int GetLobbyChatEntry( CSteamID steamIDLobby, int iChatID, CSteamID *pSteamIDUser, void *pvData, int cubData, EChatEntryType *peChatEntryType ) = 0;

};
#define STEAMMATCHMAKING_INTERFACE_VERSION "SteamMatchMaking001"


//-----------------------------------------------------------------------------
// Purpose: Callback interfaces for server list functions
//-----------------------------------------------------------------------------
class ISteamMatchmakingServerListResponse
{
public:
	virtual void ServerResponded( int iServer ) = 0;
	virtual void ServerFailedToRespond( int iServer ) = 0;
	virtual void RefreshComplete( EMatchMakingServerResponse response ) = 0;
};

class ISteamMatchmakingPingResponse
{
public:
	virtual void ServerResponded( gameserveritem_t &server ) = 0;
	virtual void ServerFailedToRespond() = 0;
};

class ISteamMatchmakingPlayersResponse
{
public:
	virtual void AddPlayerToList( const char *pchName, int nScore, float flTimePlayed ) = 0;
	virtual void PlayersFailedToRespond() = 0;
	virtual void PlayersRefreshComplete() = 0;
};


class ISteamMatchmakingRulesResponse
{
public:
	virtual void RulesResponded( const char *pchRule, const char *pchValue ) = 0;
	virtual void RulesFailedToRespond() = 0;
	virtual void RulesRefreshComplete() = 0;
};

typedef int HServerQuery;
const int HSERVERQUERY_INVALID = 0xffffffff;

//-----------------------------------------------------------------------------
// Purpose: Functions for match making services for clients to get to game servers
//-----------------------------------------------------------------------------
class ISteamMatchmakingServers
{
public:
	// request a new list of servers of a particular type
	virtual void RequestInternetServerList( uint32 iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse ) = 0;
	virtual void RequestLANServerList( uint32 iApp, ISteamMatchmakingServerListResponse *pRequestServersResponse ) = 0;
	virtual void RequestFriendsServerList( uint32 iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse ) = 0;
	virtual void RequestFavoritesServerList( uint32 iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse ) = 0;
	virtual void RequestHistoryServerList( uint32 iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse ) = 0;
	virtual void RequestSpectatorServerList( uint32 iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse ) = 0;

	virtual gameserveritem_t *GetServerDetails( EMatchMakingType eType, int iServer ) = 0; 

	virtual void CancelQuery( EMatchMakingType eType ) = 0; // stop getting new servers from an earlier query
	virtual void RefreshQuery( EMatchMakingType eType ) = 0; // ping every server in your list again but don't update the list of servers
	virtual bool IsRefreshing( EMatchMakingType eType ) = 0; // returns true if the list is currently refreshing its server list
	virtual int GetServerCount( EMatchMakingType eType ) = 0; // how many servers in this list, GetServerDetails takes 0... GetServerCount() - 1
	virtual void RefreshServer( EMatchMakingType eType, int iServer ) = 0; // refresh a single server inside of a query (rather than all the servers )

	// queries to individual servers
	virtual HServerQuery PingServer( uint32 unIP, uint16 usPort, ISteamMatchmakingPingResponse *pRequestServersResponse ) = 0; // request details from a single server
	virtual HServerQuery PlayerDetails( uint32 unIP, uint16 usPort, ISteamMatchmakingPlayersResponse *pRequestServersResponse ) = 0; // get a list of players from a server
	virtual HServerQuery ServerRules( uint32 unIP, uint16 usPort, ISteamMatchmakingRulesResponse *pRequestServersResponse ) = 0; // get the rules that server is running
	virtual void CancelServerQuery( HServerQuery hServerQuery ) = 0; // cancel an outstanding query from above
};
#define STEAMMATCHMAKINGSERVERS_INTERFACE_VERSION "SteamMatchMakingServers001"

//-----------------------------------------------------------------------------
// Callbacks
//-----------------------------------------------------------------------------

// game server flags
const uint32 k_unFavoriteFlagNone			= 0x00;
const uint32 k_unFavoriteFlagFavorite		= 0x01; // this game favorite entry is for the favorites list
const uint32 k_unFavoriteFlagHistory		= 0x02; // this game favorite entry is for the history list

// callbacks


// a server was added/removed from the favorites list, you should refresh now
struct FavoritesListChanged_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 2 }; // +2 as +1 was a previous version of this call with a different layout
	uint32 m_nIP; // an IP of 0 means reload the whole list, any other value means just one server
	uint32 m_nQueryPort;
	uint32 m_nConnPort;
	uint32 m_nAppID;
	uint32 m_nFlags;
	bool m_bAdd; // true if this is adding the entry, otherwise it is a remove
};

//-----------------------------------------------------------------------------
// Purpose: Someone has invited you to join a Lobby
//-----------------------------------------------------------------------------
struct LobbyInvite_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 3 };

	uint64 m_ulSteamIDUser;		// Steam ID of the person making the invite
	uint64 m_ulSteamIDLobby;	// Steam ID of the Lobby
};

//-----------------------------------------------------------------------------
// Purpose: You have entered a Lobby
//-----------------------------------------------------------------------------
struct LobbyEnter_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 4 };

	uint64 m_ulSteamIDLobby;							// SteamID of the Lobby you have entered
	uint32 m_rgfChatPermissions;						// Permissions of the current user
	bool m_bLocked;										// If true, then only invited users may join
	uint32 m_EChatRoomEnterResponse;	// EChatRoomEnterResponse
};

//-----------------------------------------------------------------------------
// Purpose: The lobby data has changed
//-----------------------------------------------------------------------------
struct LobbyDataUpdate_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 5 };

	uint64 m_ulSteamIDLobby;		// steamID of the Lobby
	uint64 m_ulSteamIDMember;		// steamID of the member whose data changed, or the room itself
};


//-----------------------------------------------------------------------------
// Purpose: The lobby chat room state has changed
//-----------------------------------------------------------------------------
struct LobbyChatUpdate_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 6 };

	uint64 m_ulSteamIDLobby;			// Lobby ID
	uint64 m_ulSteamIDUserChanged;		// user who's status in the lobby just changed - can be recipient
	uint64 m_ulSteamIDMakingChange;		// Chat member who made the change (different from SteamIDUserChange if kicking, muting, etc.)
	uint32 m_rgfChatMemberStateChange;	// bitfield of EChatMemberStateChange values
};

//-----------------------------------------------------------------------------
// Purpose: A chat message for this lobby
//-----------------------------------------------------------------------------
struct LobbyChatMsg_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 7 };

	uint64 m_ulSteamIDLobby;			// the lobby id this is in
	uint64 m_ulSteamIDUser;			// steamID of the user who has sent this message
	uint8 m_eChatEntryType;			// type of message
	uint32 m_iChatID;				// index of the chat entry to lookup
};

//-----------------------------------------------------------------------------
// Purpose: There's a change of Admin in this Lobby
//-----------------------------------------------------------------------------
struct LobbyAdminChange_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 8 };

	uint64 m_ulSteamIDLobby;
	uint64 m_ulSteamIDNewAdmin;
};


//-----------------------------------------------------------------------------
// Purpose: The Admin of a Lobby has created a game to join
//-----------------------------------------------------------------------------
struct LobbyGameCreated_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 9 };

	uint64 m_ulSteamIDLobby;
	uint32 m_unIP;
	uint16 m_usPort;
};

//-----------------------------------------------------------------------------
// Purpose: Number of matching lobbies found, iterate with GetLobbyByIndex
//-----------------------------------------------------------------------------
struct LobbyMatchList_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 10 };
	uint32 m_nLobbiesMatching;		// Number of lobbies that matched search criteria and we have SteamIDs for
};


//-----------------------------------------------------------------------------
// Purpose: The Lobby is closing
//-----------------------------------------------------------------------------
struct LobbyClosing_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 11 };
	uint64 m_ulSteamIDLobby;			// Lobby
};


//-----------------------------------------------------------------------------
// Purpose: You have been kicked from the lobby
//-----------------------------------------------------------------------------
struct LobbyKicked_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 12 };
	uint64 m_ulSteamIDLobby;			// Lobby
	uint64 m_ulSteamIDAdmin;			// User who kicked you
};


//-----------------------------------------------------------------------------
// Purpose: Result of our request to create a Lobby
//-----------------------------------------------------------------------------
struct LobbyCreate_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 13 };
	EResult m_eResult;				// Result
	uint64 m_ulSteamIDLobby;		// chat room, zero if failed
};

#endif // ISTEAMMATCHMAKING
