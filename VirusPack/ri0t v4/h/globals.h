// threads structure
THREAD threads[MAXTHREADS]; 

// aliases structure
ALIAS aliases[MAXALIASES];
int anum = 0;

// array sizes
int authsize = (sizeof(authost) / sizeof(LPTSTR));
int versionsize = (sizeof(versionlist)/sizeof(LPTSTR));

// misc.
DWORD started;
