int IRC_ProtocolParse(char *line, SOCKET sock, char *server, char *channel, char *chanpass, char *nick, char *host, char masters[MAXLOGINS][MAXIDENT], int *in_channel, int repeat, int clone);
