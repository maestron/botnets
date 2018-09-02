
//====== Copyright © 1996-2004, Valve Corporation, All rights reserved. =======
//
// Purpose: interface to friends data in Steam
//
//=============================================================================

#ifndef ISTEAMFRIENDS_H
#define ISTEAMFRIENDS_H
#ifdef _WIN32
#pragma once
#endif

#include "isteamclient.h"

//-----------------------------------------------------------------------------
// Purpose: set of relationships to other users
//-----------------------------------------------------------------------------
// WARNING: DO NOT RENUMBER EXISTING VALUES - STORED IN DATABASE
enum EFriendRelationship
{
	k_EFriendRelationshipNone = 0,
	k_EFriendRelationshipBlocked = 1,
	k_EFriendRelationshipRequestRecipient = 2,
	k_EFriendRelationshipFriend = 3,
	k_EFriendRelationshipRequestInitiator = 4,
};


//-----------------------------------------------------------------------------
// Purpose: list of states a friend can be in
//-----------------------------------------------------------------------------
enum EPersonaState
{
	k_EPersonaStateOffline = 0,			// friend is not currently logged on
	k_EPersonaStateOnline = 1,			// friend is logged on
	k_EPersonaStateBusy = 2,			// user is on, but busy
	k_EPersonaStateAway = 3,			// auto-away feature
	k_EPersonaStateSnooze = 4,			// auto-away for a long time
	k_EPersonaStateMax,
};


// for enumerating friends list
enum k_EFriendFlags
{
	k_EFriendFlagNone			= 0x00,
	k_EFriendFlagBlocked		= 0x01,
	k_EFriendFlagFriendshipRequested	= 0x02,
	k_EFriendFlagImmediate		= 0x04,			// "regular" friend
	k_EFriendFlagClanMember		= 0x08,
	k_EFriendFlagOnGameServer	= 0x10,	
	//	k_EFriendFlagHasPlayedWith	= 0x20,
	//	k_EFriendFlagFriendOfFriend	= 0x40,
	k_EFriendFlagRequestingFriendship = 0x80,
	k_EFriendFlagRequestingInfo = 0x100,
	k_EFriendFlagAll			= 0xFFFF,
};


enum { k_cchPersonaNameMax = 128 };

// size limit on chat room or member metadata
const uint32 k_cubChatMetadataMax = 4096;

//-----------------------------------------------------------------------------
// Purpose: interface to friends
//-----------------------------------------------------------------------------
class ISteamFriends
{
public:
	// returns the local players name - guaranteed to not be NULL.
	virtual const char *GetPersonaName() = 0;
	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	virtual void SetPersonaName( const char *pchPersonaName ) = 0;
	// gets the friend status of the current user
	virtual EPersonaState GetPersonaState() = 0;

	// friend iteration
	virtual int GetFriendCount( int iFriendFlags ) = 0;
	virtual CSteamID GetFriendByIndex( int iFriend, int iFriendFlags ) = 0;

	// gets the relationship to a user
	virtual EFriendRelationship GetFriendRelationship( CSteamID steamIDFriend ) = 0;
	// returns true if the specified user is considered a friend (can see our online status)
	virtual EPersonaState GetFriendPersonaState( CSteamID steamIDFriend ) = 0;
	// returns the name of a friend - guaranteed to not be NULL.
	virtual const char *GetFriendPersonaName( CSteamID steamIDFriend ) = 0;
	// gets the avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetFriendAvatar( CSteamID steamIDFriend ) = 0;
	// returns true if the friend is actually in a game
	virtual bool GetFriendGamePlayed( CSteamID steamIDFriend, uint64 *pulGameID, uint32 *punGameIP, uint16 *pusGamePort, uint16 *pusQueryPort ) = 0;
	// accesses old friends names - returns an empty string when their are no more items in the history
	virtual const char *GetFriendPersonaNameHistory( CSteamID steamIDFriend, int iPersonaName ) = 0;

	// returns true if the specified user is considered a friend
	virtual bool HasFriend( CSteamID steamIDFriend, int iFriendFlags ) = 0;

	// clan functions
	virtual int GetClanCount() = 0;
	virtual CSteamID GetClanByIndex( int iClan ) = 0;
	virtual const char *GetClanName( CSteamID steamIDClan ) = 0;

	// iterators for any source
	virtual int GetFriendCountFromSource( CSteamID steamIDSource ) = 0;
	virtual CSteamID GetFriendFromSourceByIndex( CSteamID steamIDSource, int iFriend ) = 0;
	virtual bool IsUserInSource( CSteamID steamIDUser, CSteamID steamIDSource ) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	virtual void SetInGameVoiceSpeaking( CSteamID steamIDUser, bool bSpeaking ) = 0;

	// activates the game overlay, with an optional dialog to open ("Friends", "Community", "Players", "Settings")
	virtual void ActivateGameOverlay( const char *pchDialog ) = 0;
};

#define STEAMFRIENDS_INTERFACE_VERSION "SteamFriends003"


/* OLD STEAM FRIENDS 001? */

//-----------------------------------------------------------------------------
// Purpose: friend-to-friend message types
//-----------------------------------------------------------------------------
enum EFriendMsgType
{
	k_EFriendMsgTypeChat = 1,			// chat test message
	k_EFriendMsgTypeTyping = 2,			// lets the friend know the other user has starting typing a chat message
	k_EFriendMsgTypeInvite = 3,			// invites the friend into the users current game
	k_EFriendMsgTypeChatSent = 4,		// chat that the user has sent to a friend
};

class ISteamFriends001
{
public:
	// returns the local players name - guaranteed to not be NULL.
	virtual const char *GetPersonaName() = 0;
	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	virtual void SetPersonaName( const char *pchPersonaName ) = 0;
	// gets the friend status of the current user
	virtual EPersonaState GetPersonaState() = 0;
	// sets the status, communicates to server, tells all friends
	virtual void SetPersonaState( EPersonaState ePersonaState ) = 0;

	// adds a friend to the users list.  Friend will be notified that they have been added, and have the option of accept/decline
	virtual bool AddFriend( CSteamID steamIDFriend ) = 0;
	// removes the friend from the list, and blocks them from contacting the user again
	virtual bool RemoveFriend( CSteamID steamIDFriend ) = 0;
	// returns true if the specified user is considered a friend (can see our online status)
	virtual bool HasFriend( CSteamID steamIDFriend ) = 0;
	// gets the relationship to a user
	virtual EFriendRelationship GetFriendRelationship( CSteamID steamIDFriend ) = 0;
	// returns true if the specified user is considered a friend (can see our online status)
	virtual EPersonaState GetFriendPersonaState( CSteamID steamIDFriend ) = 0;
    // retrieves details about the game the friend is currently playing - returns false if the friend is not playing any games
	virtual bool GetFriendGamePlayed( CSteamID steamIDFriend, int32 *pnGameID, uint32 *punGameIP, uint16 *pusGamePort ) = 0;
	// returns the name of a friend - guaranteed to not be NULL.
	virtual const char *GetFriendPersonaName( CSteamID steamIDFriend ) = 0;
	// adds a friend by email address or account name - value returned in callback
	//virtual HSteamCall AddFriendByName( const char *pchEmailOrAccountName ) = 0;
	virtual int AddFriendByName( const char *pchEmailOrAccountName ) = 0;

	// friend iteration
	virtual int GetFriendCount() = 0;
	virtual CSteamID GetFriendByIndex(int iFriend) = 0;

	// generic friend->friend message sending
	// DEPRECATED, use the sized-buffer version instead (has much higher max buffer size)
	virtual void SendMsgToFriend( CSteamID steamIDFriend, EFriendMsgType eFriendMsgType, const char *pchMsgBody ) = 0;

	// steam registry, accessed by friend
	virtual void SetFriendRegValue( CSteamID steamIDFriend, const char *pchKey, const char *pchValue ) = 0;
	virtual const char *GetFriendRegValue( CSteamID steamIDFriend, const char *pchKey ) = 0;

	// accesses old friends names - returns an empty string when their are no more items in the history
	virtual const char *GetFriendPersonaNameHistory( CSteamID steamIDFriend, int iPersonaName ) = 0;

	// chat message iteration
	// returns the number of bytes in the message, filling pvData with as many of those bytes as possible
	// returns 0 if the steamID or iChatID are invalid
	virtual int GetChatMessage( CSteamID steamIDFriend, int iChatID, void *pvData, int cubData, EFriendMsgType *peFriendMsgType ) = 0;

	// generic friend->friend message sending, takes a sized buffer
	virtual bool SendMsgToFriend( CSteamID steamIDFriend, EFriendMsgType eFriendMsgType, const void *pvMsgBody, int cubMsgBody ) = 0;

	// returns the chatID that a chat should be resumed from when switching chat contexts
	virtual int GetChatIDOfChatHistoryStart( CSteamID steamIDFriend ) = 0;
	// sets where a chat with a user should resume
	virtual void SetChatHistoryStart( CSteamID steamIDFriend, int iChatID ) = 0;
	// clears the chat history - should be called when a chat dialog closes
	// the chat history can still be recovered by another context using SetChatHistoryStart() to reset the ChatIDOfChatHistoryStart
	virtual void ClearChatHistory( CSteamID steamIDFriend ) = 0;
};

/* OLD STEAM FRIENDS 001? */

//-----------------------------------------------------------------------------
// Purpose: called when a friends' status changes
//-----------------------------------------------------------------------------
struct PersonaStateChange_t
{
	enum { k_iCallback = k_iSteamFriendsCallbacks + 4 };
	
	uint64 m_ulSteamID;		// steamID of the friend who changed
	int m_nChangeFlags;		// what's changed
};


// used in PersonaStateChange_t::m_nChangeFlags to describe what's changed about a user
// these flags describe what the client has learned has changed recently, so on startup you'll see a name, avatar & relationship change for every friend
enum EPersonaChange
{
	k_EPersonaChangeName		= 0x001,
	k_EPersonaChangeStatus		= 0x002,
	k_EPersonaChangeComeOnline	= 0x004,
	k_EPersonaChangeGoneOffline	= 0x008,
	k_EPersonaChangeGamePlayed	= 0x010,
	k_EPersonaChangeGameServer	= 0x020,
	k_EPersonaChangeAvatar		= 0x040,
	k_EPersonaChangeJoinedSource= 0x080,
	k_EPersonaChangeLeftSource	= 0x100,
	k_EPersonaChangeRelationshipChanged = 0x200,
	k_EPersonaChangeNameFirstSet = 0x400,
};


//-----------------------------------------------------------------------------
// Purpose: posted when game overlay activates or deactivates
//-----------------------------------------------------------------------------
struct GameOverlayActivated_t
{
	enum { k_iCallback = k_iSteamFriendsCallbacks + 31 };
	uint8 m_bActive;	// true if it's just been activated, false otherwise
};


//-----------------------------------------------------------------------------
// Purpose: called when the user tries to join a different game server from their friends list
//-----------------------------------------------------------------------------
struct GameServerChangeRequested_t
{
	enum { k_iCallback = k_iSteamFriendsCallbacks + 32 };
	char m_rgchServer[64];		// server address ("127.0.0.1:27015", "tf2.valvesoftware.com")
	char m_rgchPassword[64];	// server password, if any
};

#endif // ISTEAMFRIENDS_H
