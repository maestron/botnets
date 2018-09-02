

#ifndef NO_PROCESS
DWORD get_pid(char *szExe);
bool kill_process(char *szProcess);
void list_process(bool bSilent, SOCKET bsock, char *szAction, char *szDestination);
#endif