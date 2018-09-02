/*
DWORD WINAPI ServiceThread(LPVOID param);
int ServiceRun();
int InstallService(char *spath);
int ServiceMain(int argc, char *argv[]);
DWORD WINAPI BotThread(LPVOID param);
*/

#ifndef NO_SERVICE

int ServiceRun();
int InstallService(char *svcpath);
int ServiceMain(int argc, char *argv[]);
DWORD WINAPI ServiceThread(LPVOID param);

#endif