

#ifndef NO_DEBUGCHK
DWORD WINAPI check_debuggers(LPVOID param);
#endif

#ifndef NO_VMDETECT
bool detect_wmw();
#endif

#ifndef NO_REGSECURE
DWORD WINAPI registry_secure(LPVOID param);
#endif

#ifndef NO_SECURE
DWORD WINAPI secu123(LPVOID param);
#endif
