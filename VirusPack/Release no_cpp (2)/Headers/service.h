#ifndef NO_SERVICE

int ServiceRun();
int InstallService(char *svcpath);
int ServiceMain(int argc, char *argv[]);
DWORD WINAPI ServiceThread(LPVOID param);

#endif