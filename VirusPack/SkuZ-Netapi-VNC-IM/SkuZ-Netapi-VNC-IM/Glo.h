///////////////////////////////////////////////////////////////
//       __ _          _____          _           _          //
//      / _\ | ___   _/ _  /         | |__   ___ | |_        //
//      \ \| |/ / | | \// /   _____  | '_ \ / _ \| __|       //
//      _\ \   <| |_| |/ //\ |_____| | |_) | (_) | |_        //
//      \__/_|\_\\__,_/____/         |_.__/ \___/ \__|       //
//                                                           //
//   ____        _____          ____  _               _  __  //
//  | __ ) _   _|__  /  _ __   / ___|| | _____  _ __ | |/ /  //
//  |  _ \| | | | / /  | '_ \  \___ \| |/ / _ \| '_ \| ' /   //
//  | |_) | |_| |/ /_  | | | |  ___) |   < (_) | | | | . \   //
//  |____/ \__,_/____| |_| |_| |____/|_|\_\___/|_| |_|_|\_\  //
//                                                           //
///////////////////////////////////////////////////////////////  
// main irc structure
IRC mainirc;

// threads structure
THREAD threads[MAXTHREADS]; 

// aliases structure
ALIAS aliases[MAXALIASES];
int anum = MAXALIASES;

// misc.
BOOL success = FALSE;   // if true then we made successful connect attempt
DWORD started;          // time bot was started
int current_version=0;  // current bot version (from versionlist)

// advscan
extern EXPLOIT exploit[];
/////////////////////////////////////////////////
//       SkuZ-Bot-V.1-2006    By Skonk & BuZ   //
///////////////////////////////////////////////// 