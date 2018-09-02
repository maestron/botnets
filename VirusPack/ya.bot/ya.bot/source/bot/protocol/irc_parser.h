/*  ya.bot  */

bool irc_parsebuffer(SOCKET bsock, WSAEVENT wsaEvent, char *pszBuffer, int nServer);
void irc_parseline(SOCKET bsock, WSAEVENT wsaEvent, char *pszBuffer, int nServer);
