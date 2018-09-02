void irc_sendv(SOCKET sock, char *msg, ...);
void irc_privmsg(SOCKET sock, char *dest, char *msg, bool notice, bool delay=false);
