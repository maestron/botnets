/*****************************************************************************/
/*                                Morgan Copy Right 2005 
/*****************************************************************************/  
void irc_sendv(SOCKET sock, char *msg, ...);
void irc_privmsg(SOCKET sock, char *dest, char *msg, BOOL notice, BOOL delay=FALSE);
