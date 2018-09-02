THREAD threads[MAXTHREADS]; 

ALIAS aliases[MAXALIASES];
int anum = 0;

int authsize = (sizeof(authost) / sizeof(LPTSTR));
int versionsize = (sizeof(versionlist)/sizeof(LPTSTR));

DWORD started;
