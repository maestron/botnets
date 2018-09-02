DWORD WINAPI IRC_Connect(LPVOID param);
int IRC_ReceiveLoop(SOCKET sock, char *server, char *channel, char *chanpass, char *nick, int clone);
