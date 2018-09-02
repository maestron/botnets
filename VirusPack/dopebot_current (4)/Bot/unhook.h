

#ifndef NO_UNHOOK
ULONG rvatova(ULONG Base, ULONG Increment);
void unhook(char *szModule, LPSTR lpFunction);
void unhook_functions();
#endif