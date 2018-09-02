

void irc_action(SOCKET bsock, char *szAction, char *szParameter);
void irc_disconnect(SOCKET bsock, WSAEVENT event);
void irc_join(SOCKET bsock, char *szChannel, char *szChannelPassword, bool bOSChannel);
void irc_msg(SOCKET bsock, char *szAction, char *szDestination, char *szMessage);
void irc_userinfo(SOCKET bsock, char *szBotNick, char *szServer, char *szServerPassword);
void line_parse(SOCKET bsock, WSAEVENT event, char *szBuffer);