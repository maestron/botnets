int Irc_Connect(char *Server, unsigned int Port, BOOL UsePassword, char *Password);
int Irc_Parse(char *Line);
int Irc_Parse_Command(char *CurrentChannel, char *Line);
void IrcPrivmsg(SOCKET sock, char *channel, char *text);