bool irc_start( void );
void irc_parse( SOCKET sSocket, char* szLine, char *pszBotNick );
int irc_raw( SOCKET sSocket, char* szPacket, ... );
int irc_msg( SOCKET sock, char *pszFmt, ... );